/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_TRAPS_H
#define _ASM_X86_TRAPS_H

#include <linux/context_tracking_state.h>
#include <linux/kprobes.h>

#include <asm/debugreg.h>
#include <asm/siginfo.h>			/* TRAP_TRACE, ... */
#include <asm/trap_pf.h>
#include <asm/trapnr.h>

#define dotraplinkage __visible

asmlinkage void divide_error(void);
asmlinkage void debug(void);
asmlinkage void nmi(void);
asmlinkage void int3(void);
asmlinkage void overflow(void);
asmlinkage void bounds(void);
asmlinkage void invalid_op(void);
asmlinkage void device_not_available(void);
#ifdef CONFIG_X86_64
asmlinkage void double_fault(void);
#endif
asmlinkage void coprocessor_segment_overrun(void);
asmlinkage void invalid_TSS(void);
asmlinkage void segment_not_present(void);
asmlinkage void stack_segment(void);
asmlinkage void general_protection(void);
#if IS_ENABLED(CONFIG_KVM_INTEL)
asmlinkage void nmi_noist(void);
#endif
asmlinkage void page_fault(void);
asmlinkage void async_page_fault(void);
asmlinkage void spurious_interrupt_bug(void);
asmlinkage void coprocessor_error(void);
asmlinkage void alignment_check(void);
#ifdef CONFIG_X86_MCE
asmlinkage void machine_check(void);
#endif /* CONFIG_X86_MCE */
asmlinkage void simd_coprocessor_error(void);
#ifdef CONFIG_AMD_MEM_ENCRYPT
asmlinkage void vmm_communication(void);
#endif

#if defined(CONFIG_X86_64) && defined(CONFIG_XEN_PV)
asmlinkage void xen_divide_error(void);
asmlinkage void xen_xennmi(void);
asmlinkage void xen_xendebug(void);
asmlinkage void xen_xenint3(void);
asmlinkage void xen_overflow(void);
asmlinkage void xen_bounds(void);
asmlinkage void xen_invalid_op(void);
asmlinkage void xen_device_not_available(void);
asmlinkage void xen_double_fault(void);
asmlinkage void xen_coprocessor_segment_overrun(void);
asmlinkage void xen_invalid_TSS(void);
asmlinkage void xen_segment_not_present(void);
asmlinkage void xen_stack_segment(void);
asmlinkage void xen_general_protection(void);
asmlinkage void xen_page_fault(void);
asmlinkage void xen_spurious_interrupt_bug(void);
asmlinkage void xen_coprocessor_error(void);
asmlinkage void xen_alignment_check(void);
#ifdef CONFIG_X86_MCE
asmlinkage void xen_machine_check(void);
#endif /* CONFIG_X86_MCE */
asmlinkage void xen_simd_coprocessor_error(void);
#endif

dotraplinkage void do_divide_error(struct pt_regs *regs, long error_code);
dotraplinkage void do_debug(struct pt_regs *regs, long error_code);
dotraplinkage void do_nmi(struct pt_regs *regs, long error_code);
dotraplinkage void do_int3(struct pt_regs *regs, long error_code);
dotraplinkage void do_overflow(struct pt_regs *regs, long error_code);
dotraplinkage void do_bounds(struct pt_regs *regs, long error_code);
dotraplinkage void do_invalid_op(struct pt_regs *regs, long error_code);
dotraplinkage void do_device_not_available(struct pt_regs *regs, long error_code);
dotraplinkage void do_coprocessor_segment_overrun(struct pt_regs *regs, long error_code);
dotraplinkage void do_invalid_TSS(struct pt_regs *regs, long error_code);
dotraplinkage void do_segment_not_present(struct pt_regs *regs, long error_code);
dotraplinkage void do_stack_segment(struct pt_regs *regs, long error_code);
#ifdef CONFIG_X86_64
dotraplinkage void do_double_fault(struct pt_regs *regs, long error_code);
asmlinkage __visible notrace struct pt_regs *sync_regs(struct pt_regs *eregs);
asmlinkage __visible notrace
struct bad_iret_stack *fixup_bad_iret(struct bad_iret_stack *s);
void __init trap_init(void);
asmlinkage __visible noinstr struct pt_regs *vc_switch_off_ist(struct pt_regs *eregs);
#endif
dotraplinkage void do_general_protection(struct pt_regs *regs, long error_code);
dotraplinkage void do_page_fault(struct pt_regs *regs, unsigned long error_code);
dotraplinkage void do_spurious_interrupt_bug(struct pt_regs *regs, long error_code);
dotraplinkage void do_coprocessor_error(struct pt_regs *regs, long error_code);
dotraplinkage void do_alignment_check(struct pt_regs *regs, long error_code);
#ifdef CONFIG_X86_MCE
dotraplinkage void do_machine_check(struct pt_regs *regs, long error_code);
#endif
dotraplinkage void do_simd_coprocessor_error(struct pt_regs *regs, long error_code);
#ifdef CONFIG_X86_32
dotraplinkage void do_iret_error(struct pt_regs *regs, long error_code);
#endif
dotraplinkage void do_mce(struct pt_regs *regs, long error_code);
#ifdef CONFIG_AMD_MEM_ENCRYPT
dotraplinkage void do_vmm_communication(struct pt_regs *, long);
#endif

static inline int get_si_code(unsigned long condition)
{
	if (condition & DR_STEP)
		return TRAP_TRACE;
	else if (condition & (DR_TRAP0|DR_TRAP1|DR_TRAP2|DR_TRAP3))
		return TRAP_HWBKPT;
	else
		return TRAP_BRKPT;
}

extern int panic_on_unrecovered_nmi;

void math_emulate(struct math_emu_info *);
#ifndef CONFIG_X86_32
asmlinkage void smp_thermal_interrupt(struct pt_regs *regs);
asmlinkage void smp_threshold_interrupt(struct pt_regs *regs);
asmlinkage void smp_deferred_error_interrupt(struct pt_regs *regs);
#endif

#ifdef CONFIG_VMAP_STACK
void __noreturn handle_stack_overflow(const char *message,
				      struct pt_regs *regs,
				      unsigned long fault_address);
#endif

#endif /* _ASM_X86_TRAPS_H */
