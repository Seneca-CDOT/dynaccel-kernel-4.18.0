// SPDX-License-Identifier: GPL-2.0
#include <linux/fanotify.h>
#include <linux/fdtable.h>
#include <linux/fsnotify_backend.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/kernel.h> /* UINT_MAX */
#include <linux/mount.h>
#include <linux/sched.h>
#include <linux/sched/user.h>
#include <linux/sched/signal.h>
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/audit.h>
#include <linux/sched/mm.h>

#include "fanotify.h"

static bool should_merge(struct fsnotify_event *old_fsn,
			 struct fsnotify_event *new_fsn)
{
	struct fanotify_event *old, *new;

	pr_debug("%s: old=%p new=%p\n", __func__, old_fsn, new_fsn);
	old = FANOTIFY_E(old_fsn);
	new = FANOTIFY_E(new_fsn);

	if (old_fsn->inode == new_fsn->inode && old->pid == new->pid &&
	    old->path.mnt == new->path.mnt &&
	    old->path.dentry == new->path.dentry)
		return true;
	return false;
}

/* and the list better be locked by something too! */
static int fanotify_merge(struct list_head *list, struct fsnotify_event *event)
{
	struct fsnotify_event *test_event;

	pr_debug("%s: list=%p event=%p\n", __func__, list, event);

	/*
	 * Don't merge a permission event with any other event so that we know
	 * the event structure we have created in fanotify_handle_event() is the
	 * one we should check for permission response.
	 */
	if (fanotify_is_perm_event(event->mask))
		return 0;

	list_for_each_entry_reverse(test_event, list, list) {
		if (should_merge(test_event, event)) {
			test_event->mask |= event->mask;
			return 1;
		}
	}

	return 0;
}

/*
 * Wait for response to permission event. The function also takes care of
 * freeing the permission event (or offloads that in case the wait is canceled
 * by a signal). The function returns 0 in case access got allowed by userspace,
 * -EPERM in case userspace disallowed the access, and -ERESTARTSYS in case
 * the wait got interrupted by a signal.
 */
static int fanotify_get_response(struct fsnotify_group *group,
				 struct fanotify_perm_event *event,
				 struct fsnotify_iter_info *iter_info)
{
	int ret;

	pr_debug("%s: group=%p event=%p\n", __func__, group, event);

	ret = wait_event_killable(group->fanotify_data.access_waitq,
				  event->state == FAN_EVENT_ANSWERED);
	/* Signal pending? */
	if (ret < 0) {
		spin_lock(&group->notification_lock);
		/* Event reported to userspace and no answer yet? */
		if (event->state == FAN_EVENT_REPORTED) {
			/* Event will get freed once userspace answers to it */
			event->state = FAN_EVENT_CANCELED;
			spin_unlock(&group->notification_lock);
			return ret;
		}
		/* Event not yet reported? Just remove it. */
		if (event->state == FAN_EVENT_INIT)
			fsnotify_remove_queued_event(group, &event->fae.fse);
		/*
		 * Event may be also answered in case signal delivery raced
		 * with wakeup. In that case we have nothing to do besides
		 * freeing the event and reporting error.
		 */
		spin_unlock(&group->notification_lock);
		goto out;
	}

	/* userspace responded, convert to something usable */
	switch (event->response & ~FAN_AUDIT) {
	case FAN_ALLOW:
		ret = 0;
		break;
	case FAN_DENY:
	default:
		ret = -EPERM;
	}

	/* Check if the response should be audited */
	if (event->response & FAN_AUDIT)
		audit_fanotify(event->response & ~FAN_AUDIT);

	pr_debug("%s: group=%p event=%p about to return ret=%d\n", __func__,
		 group, event, ret);
out:
	fsnotify_destroy_event(group, &event->fae.fse);

	return ret;
}

/*
 * This function returns a mask for an event that only contains the flags
 * that have been specifically requested by the user. Flags that may have
 * been included within the event mask, but have not been explicitly
 * requested by the user, will not be present in the returned mask.
 */
static u32 fanotify_group_event_mask(struct fsnotify_iter_info *iter_info,
				       u32 event_mask, const void *data,
				       int data_type)
{
	__u32 marks_mask = 0, marks_ignored_mask = 0;
	const struct path *path = data;
	struct fsnotify_mark *mark;
	int type;

	pr_debug("%s: report_mask=%x mask=%x data=%p data_type=%d\n",
		 __func__, iter_info->report_mask, event_mask, data, data_type);

	/* If we don't have enough info to send an event to userspace say no */
	if (data_type != FSNOTIFY_EVENT_PATH)
		return 0;

	/* Sorry, fanotify only gives a damn about files and dirs */
	if (!d_is_reg(path->dentry) &&
	    !d_can_lookup(path->dentry))
		return 0;

	fsnotify_foreach_obj_type(type) {
		if (!fsnotify_iter_should_report_type(iter_info, type))
			continue;
		mark = iter_info->marks[type];
		/*
		 * If the event is on dir and this mark doesn't care about
		 * events on dir, don't send it!
		 */
		if (event_mask & FS_ISDIR && !(mark->mask & FS_ISDIR))
			continue;

		/*
		 * If the event is for a child and this mark doesn't care about
		 * events on a child, don't send it!
		 */
		if (event_mask & FS_EVENT_ON_CHILD &&
		    (type != FSNOTIFY_OBJ_TYPE_INODE ||
		     !(mark->mask & FS_EVENT_ON_CHILD)))
			continue;

		marks_mask |= mark->mask;
		marks_ignored_mask |= mark->ignored_mask;
	}

	return event_mask & FANOTIFY_OUTGOING_EVENTS & marks_mask &
		~marks_ignored_mask;
}

struct fanotify_event *fanotify_alloc_event(struct fsnotify_group *group,
						 struct inode *inode, u32 mask,
						 const struct path *path)
{
	struct fanotify_event *event = NULL;
	gfp_t gfp = GFP_KERNEL_ACCOUNT;
	struct mem_cgroup *old_memcg;

	/*
	 * For queues with unlimited length lost events are not expected and
	 * can possibly have security implications. Avoid losing events when
	 * memory is short. For the limited size queues, avoid OOM killer in the
	 * target monitoring memcg as it may have security repercussion.
	 */
	if (group->max_events == UINT_MAX)
		gfp |= __GFP_NOFAIL;
	else
		gfp |= __GFP_RETRY_MAYFAIL;

	/* Whoever is interested in the event, pays for the allocation. */
	old_memcg = set_active_memcg(group->memcg);

	if (fanotify_is_perm_event(mask)) {
		struct fanotify_perm_event *pevent;

		pevent = kmem_cache_alloc(fanotify_perm_event_cachep, gfp);
		if (!pevent)
			goto out;
		event = &pevent->fae;
		pevent->response = 0;
		pevent->state = FAN_EVENT_INIT;
		goto init;
	}
	event = kmem_cache_alloc(fanotify_event_cachep, gfp);
	if (!event)
		goto out;
init: __maybe_unused
	fsnotify_init_event(&event->fse, inode, mask);
	if (FAN_GROUP_FLAG(group, FAN_REPORT_TID))
		event->pid = get_pid(task_pid(current));
	else
		event->pid = get_pid(task_tgid(current));
	if (path) {
		event->path = *path;
		path_get(&event->path);
	} else {
		event->path.mnt = NULL;
		event->path.dentry = NULL;
	}
out:
	set_active_memcg(old_memcg);
	return event;
}

static int fanotify_handle_event(struct fsnotify_group *group,
				 struct inode *inode,
				 u32 mask, const void *data, int data_type,
				 const struct qstr *file_name, u32 cookie,
				 struct fsnotify_iter_info *iter_info)
{
	int ret = 0;
	struct fanotify_event *event;
	struct fsnotify_event *fsn_event;

	BUILD_BUG_ON(FAN_ACCESS != FS_ACCESS);
	BUILD_BUG_ON(FAN_MODIFY != FS_MODIFY);
	BUILD_BUG_ON(FAN_CLOSE_NOWRITE != FS_CLOSE_NOWRITE);
	BUILD_BUG_ON(FAN_CLOSE_WRITE != FS_CLOSE_WRITE);
	BUILD_BUG_ON(FAN_OPEN != FS_OPEN);
	BUILD_BUG_ON(FAN_EVENT_ON_CHILD != FS_EVENT_ON_CHILD);
	BUILD_BUG_ON(FAN_Q_OVERFLOW != FS_Q_OVERFLOW);
	BUILD_BUG_ON(FAN_OPEN_PERM != FS_OPEN_PERM);
	BUILD_BUG_ON(FAN_ACCESS_PERM != FS_ACCESS_PERM);
	BUILD_BUG_ON(FAN_ONDIR != FS_ISDIR);
	BUILD_BUG_ON(FAN_OPEN_EXEC != FS_OPEN_EXEC);
	BUILD_BUG_ON(FAN_OPEN_EXEC_PERM != FS_OPEN_EXEC_PERM);

	BUILD_BUG_ON(HWEIGHT32(ALL_FANOTIFY_EVENT_BITS) != 12);

	mask = fanotify_group_event_mask(iter_info, mask, data, data_type);
	if (!mask)
		return 0;

	pr_debug("%s: group=%p inode=%p mask=%x\n", __func__, group, inode,
		 mask);

	if (fanotify_is_perm_event(mask)) {
		/*
		 * fsnotify_prepare_user_wait() fails if we race with mark
		 * deletion.  Just let the operation pass in that case.
		 */
		if (!fsnotify_prepare_user_wait(iter_info))
			return 0;
	}

	event = fanotify_alloc_event(group, inode, mask, data);
	ret = -ENOMEM;
	if (unlikely(!event)) {
		/*
		 * We don't queue overflow events for permission events as
		 * there the access is denied and so no event is in fact lost.
		 */
		if (!fanotify_is_perm_event(mask))
			fsnotify_queue_overflow(group);
		goto finish;
	}

	fsn_event = &event->fse;
	ret = fsnotify_add_event(group, fsn_event, fanotify_merge);
	if (ret) {
		/* Permission events shouldn't be merged */
		BUG_ON(ret == 1 && mask & FANOTIFY_PERM_EVENTS);
		/* Our event wasn't used in the end. Free it. */
		fsnotify_destroy_event(group, fsn_event);

		ret = 0;
	} else if (fanotify_is_perm_event(mask)) {
		ret = fanotify_get_response(group, FANOTIFY_PE(fsn_event),
					    iter_info);
	}
finish:
	if (fanotify_is_perm_event(mask))
		fsnotify_finish_user_wait(iter_info);

	return ret;
}

static void fanotify_free_group_priv(struct fsnotify_group *group)
{
	struct user_struct *user;

	user = group->fanotify_data.user;
	atomic_dec(&user->fanotify_listeners);
	free_uid(user);
}

static void fanotify_free_event(struct fsnotify_event *fsn_event)
{
	struct fanotify_event *event;

	event = FANOTIFY_E(fsn_event);
	path_put(&event->path);
	put_pid(event->pid);
	if (fanotify_is_perm_event(fsn_event->mask)) {
		kmem_cache_free(fanotify_perm_event_cachep,
				FANOTIFY_PE(fsn_event));
		return;
	}
	kmem_cache_free(fanotify_event_cachep, event);
}

static void fanotify_free_mark(struct fsnotify_mark *fsn_mark)
{
	kmem_cache_free(fanotify_mark_cache, fsn_mark);
}

const struct fsnotify_ops fanotify_fsnotify_ops = {
	.handle_event = fanotify_handle_event,
	.free_group_priv = fanotify_free_group_priv,
	.free_event = fanotify_free_event,
	.free_mark = fanotify_free_mark,
};
