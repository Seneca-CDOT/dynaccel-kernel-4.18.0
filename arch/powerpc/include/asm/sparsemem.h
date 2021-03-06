/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_POWERPC_SPARSEMEM_H
#define _ASM_POWERPC_SPARSEMEM_H 1
#ifdef __KERNEL__

#ifdef CONFIG_SPARSEMEM
/*
 * SECTION_SIZE_BITS		2^N: how big each section will be
 * MAX_PHYSMEM_BITS		2^N: how much memory we can have in that space
 */
#define SECTION_SIZE_BITS       24
/*
 * If we store section details in page->flags we can't increase the MAX_PHYSMEM_BITS
 * if we increase SECTIONS_WIDTH we will not store node details in page->flags and
 * page_to_nid does a page->section->node lookup
 * Hence only increase for VMEMMAP.
 */
#ifdef CONFIG_SPARSEMEM_VMEMMAP
#define MAX_PHYSMEM_BITS        47
#else
#define MAX_PHYSMEM_BITS        46
#endif

#endif /* CONFIG_SPARSEMEM */

#ifdef CONFIG_MEMORY_HOTPLUG
extern int create_section_mapping(unsigned long start, unsigned long end,
				  int nid, pgprot_t prot);
extern int remove_section_mapping(unsigned long start, unsigned long end);

#ifdef CONFIG_NUMA
extern int hot_add_scn_to_nid(unsigned long scn_addr);
#else
static inline int hot_add_scn_to_nid(unsigned long scn_addr)
{
	return 0;
}
#endif /* CONFIG_NUMA */
#endif /* CONFIG_MEMORY_HOTPLUG */

#endif /* __KERNEL__ */
#endif /* _ASM_POWERPC_SPARSEMEM_H */
