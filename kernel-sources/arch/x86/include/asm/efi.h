/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_EFI_H
#define _ASM_X86_EFI_H

#include <asm/fpu/api.h>
#include <asm/pgtable.h>
#include <asm/processor-flags.h>
#include <asm/tlb.h>
#include <asm/nospec-branch.h>
#include <asm/mmu_context.h>

/*
 * We map the EFI regions needed for runtime services non-contiguously,
 * with preserved alignment on virtual addresses starting from -4G down
 * for a total max space of 64G. This way, we provide for stable runtime
 * services addresses across kernels so that a kexec'd kernel can still
 * use them.
 *
 * This is the main reason why we're doing stable VA mappings for RT
 * services.
 */

#define EFI32_LOADER_SIGNATURE	"EL32"
#define EFI64_LOADER_SIGNATURE	"EL64"

#define MAX_CMDLINE_ADDRESS	UINT_MAX

#define ARCH_EFI_IRQ_FLAGS_MASK	X86_EFLAGS_IF

static inline void efi_fpu_begin(void)
{
	/*
	 * The UEFI calling convention (UEFI spec 2.3.2 and 2.3.4) requires
	 * that FCW and MXCSR (64-bit) must be initialized prior to calling
	 * UEFI code.  (Oddly the spec does not require that the FPU stack
	 * be empty.)
	 */
	kernel_fpu_begin_mask(KFPU_387 | KFPU_MXCSR);
}

static inline void efi_fpu_end(void)
{
	kernel_fpu_end();
}

#ifdef CONFIG_X86_32

extern asmlinkage unsigned long efi_call_phys(void *, ...);

#define arch_efi_call_virt_setup()					\
({									\
	efi_fpu_begin();						\
	firmware_restrict_branch_speculation_start();			\
})

#define arch_efi_call_virt_teardown()					\
({									\
	firmware_restrict_branch_speculation_end();			\
	efi_fpu_end();							\
})


/*
 * Wrap all the virtual calls in a way that forces the parameters on the stack.
 */
#define arch_efi_call_virt(p, f, args...)				\
({									\
	((efi_##f##_t __attribute__((regparm(0)))*) p->f)(args);	\
})

#define efi_ioremap(addr, size, type, attr)	ioremap_cache(addr, size)

#else /* !CONFIG_X86_32 */

#define EFI_LOADER_SIGNATURE	"EL64"

extern asmlinkage u64 efi_call(void *fp, ...);

/*
 * struct efi_scratch - Scratch space used while switching to/from efi_mm
 * @phys_stack: stack used during EFI Mixed Mode
 * @prev_mm:    store/restore stolen mm_struct while switching to/from efi_mm
 */
struct efi_scratch {
	u64			phys_stack;
	struct mm_struct	*prev_mm;
} __packed;

#define arch_efi_call_virt_setup()					\
({									\
	efi_sync_low_kernel_mappings();					\
	efi_fpu_begin();						\
	firmware_restrict_branch_speculation_start();			\
	efi_switch_mm(&efi_mm);						\
})

#define arch_efi_call_virt(p, f, args...)				\
	efi_call((void *)p->f, args)					\

#define arch_efi_call_virt_teardown()					\
({									\
	efi_switch_mm(efi_scratch.prev_mm);				\
	firmware_restrict_branch_speculation_end();			\
	efi_fpu_end();							\
})

extern void __iomem *__init efi_ioremap(unsigned long addr, unsigned long size,
					u32 type, u64 attribute);

#ifdef CONFIG_KASAN
/*
 * CONFIG_KASAN may redefine memset to __memset.  __memset function is present
 * only in kernel binary.  Since the EFI stub linked into a separate binary it
 * doesn't have __memset().  So we should use standard memset from
 * arch/x86/boot/compressed/string.c.  The same applies to memcpy and memmove.
 */
#undef memcpy
#undef memset
#undef memmove
#endif

#endif /* CONFIG_X86_32 */

extern struct efi_scratch efi_scratch;
extern void __init efi_set_executable(efi_memory_desc_t *md, bool executable);
extern int __init efi_memblock_x86_reserve_range(void);
extern void __init efi_print_memmap(void);
extern void __init efi_memory_uc(u64 addr, unsigned long size);
extern void __init efi_map_region(efi_memory_desc_t *md);
extern void __init efi_map_region_fixed(efi_memory_desc_t *md);
extern void efi_sync_low_kernel_mappings(void);
extern int __init efi_alloc_page_tables(void);
extern int __init efi_setup_page_tables(unsigned long pa_memmap, unsigned num_pages);
extern void __init old_map_region(efi_memory_desc_t *md);
extern void __init runtime_code_page_mkexec(void);
extern void __init efi_runtime_update_mappings(void);
extern void __init efi_dump_pagetable(void);
extern void __init efi_apply_memmap_quirks(void);
extern int __init efi_reuse_config(u64 tables, int nr_tables);
extern void efi_delete_dummy_variable(void);
extern void efi_switch_mm(struct mm_struct *mm);
extern void efi_recover_from_page_fault(unsigned long phys_addr);
extern void efi_free_boot_services(void);

struct efi_setup_data {
	u64 fw_vendor;
	u64 runtime;
	u64 tables;
	u64 smbios;
	u64 reserved[8];
};

extern u64 efi_setup;

#ifdef CONFIG_EFI

static inline bool efi_is_mixed(void)
{
	if (!IS_ENABLED(CONFIG_EFI_MIXED))
		return false;
	return IS_ENABLED(CONFIG_X86_64) && !efi_enabled(EFI_64BIT);
}

static inline bool efi_runtime_supported(void)
{
	if (IS_ENABLED(CONFIG_X86_64) == efi_enabled(EFI_64BIT))
		return true;

	return IS_ENABLED(CONFIG_EFI_MIXED);
}

extern struct console early_efi_console;
extern void parse_efi_setup(u64 phys_addr, u32 data_len);

extern void efifb_setup_from_dmi(struct screen_info *si, const char *opt);

extern void efi_thunk_runtime_setup(void);
efi_status_t efi_set_virtual_address_map(unsigned long memory_map_size,
					 unsigned long descriptor_size,
					 u32 descriptor_version,
					 efi_memory_desc_t *virtual_map);

/* arch specific definitions used by the stub code */

struct efi_config {
	u64 image_handle;
	u64 table;
	u64 runtime_services;
	u64 boot_services;
	u64 text_output;
	efi_status_t (*call)(unsigned long, ...);
	bool is64;
} __packed;

__pure const struct efi_config *__efi_early(void);

static inline bool efi_is_64bit(void)
{
	if (!IS_ENABLED(CONFIG_X86_64))
		return false;

	if (!IS_ENABLED(CONFIG_EFI_MIXED))
		return true;

	return __efi_early()->is64;
}

static inline bool efi_is_native(void)
{
	if (!IS_ENABLED(CONFIG_X86_64))
		return true;
	return efi_is_64bit();
}

#define efi_mixed_mode_cast(attr)					\
	__builtin_choose_expr(						\
		__builtin_types_compatible_p(u32, __typeof__(attr)),	\
			(unsigned long)(attr), (attr))

#define efi_table_attr(table, attr, instance) ({			\
	__typeof__(((table##_t *)0)->attr) __ret;			\
	if (efi_is_native()) {						\
		__ret = ((table##_t *)(unsigned long)instance)->attr;	\
	} else {							\
		__ret = (__typeof__(__ret))efi_mixed_mode_cast(		\
		((table##_t *)(unsigned long)instance)->mixed_mode.attr);\
	}								\
	__ret;								\
})

#define efi_call_proto(protocol, f, instance, ...)			\
	__efi_early()->call((unsigned long)				\
				efi_table_attr(protocol, f, instance),	\
		instance, ##__VA_ARGS__)

#define efi_call_early(f, ...)						\
	__efi_early()->call((unsigned long)				\
				efi_table_attr(efi_boot_services, f,	\
		__efi_early()->boot_services), __VA_ARGS__)

#define efi_call_runtime(f, ...)					\
	__efi_early()->call((unsigned long)				\
				efi_table_attr(efi_runtime_services, f,	\
		__efi_early()->runtime_services), __VA_ARGS__)

extern bool efi_reboot_required(void);
extern bool efi_is_table_address(unsigned long phys_addr);

extern void efi_find_mirror(void);
extern void efi_reserve_boot_services(void);
#else
static inline void parse_efi_setup(u64 phys_addr, u32 data_len) {}
static inline bool efi_reboot_required(void)
{
	return false;
}
static inline  bool efi_is_table_address(unsigned long phys_addr)
{
	return false;
}
static inline void efi_find_mirror(void)
{
}
static inline void efi_reserve_boot_services(void)
{
}
#endif /* CONFIG_EFI */

#endif /* _ASM_X86_EFI_H */
