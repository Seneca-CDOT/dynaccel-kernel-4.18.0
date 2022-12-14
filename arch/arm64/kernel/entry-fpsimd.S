/*
 * FP/SIMD state saving and restoring
 *
 * Copyright (C) 2012 ARM Ltd.
 * Author: Catalin Marinas <catalin.marinas@arm.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/linkage.h>

#include <asm/assembler.h>
#include <asm/fpsimdmacros.h>

/*
 * Save the FP registers.
 *
 * x0 - pointer to struct fpsimd_state
 */
SYM_FUNC_START(fpsimd_save_state)
	fpsimd_save x0, 8
	ret
SYM_FUNC_END(fpsimd_save_state)

/*
 * Load the FP registers.
 *
 * x0 - pointer to struct fpsimd_state
 */
SYM_FUNC_START(fpsimd_load_state)
	fpsimd_restore x0, 8
	ret
SYM_FUNC_END(fpsimd_load_state)

#ifdef CONFIG_ARM64_SVE

SYM_FUNC_START(sve_save_state)
	sve_save 0, x1, 2
	ret
SYM_FUNC_END(sve_save_state)

SYM_FUNC_START(sve_load_state)
	sve_load 0, x1, x2, 3, x4
	ret
SYM_FUNC_END(sve_load_state)

SYM_FUNC_START(sve_get_vl)
	_sve_rdvl	0, 1
	ret
SYM_FUNC_END(sve_get_vl)

SYM_FUNC_START(sve_set_vq)
	sve_load_vq x0, x1, x2
	ret
SYM_FUNC_END(sve_set_vq)

/*
 * Load SVE state from FPSIMD state.
 *
 * x0 = pointer to struct fpsimd_state
 * x1 = VQ - 1
 *
 * Each SVE vector will be loaded with the first 128-bits taken from FPSIMD
 * and the rest zeroed. All the other SVE registers will be zeroed.
 */
SYM_FUNC_START(sve_load_from_fpsimd_state)
	sve_load_vq	x1, x2, x3
	fpsimd_restore	x0, 8
	sve_flush_p_ffr
	ret
SYM_FUNC_END(sve_load_from_fpsimd_state)

/*
 * Zero all SVE registers but the first 128-bits of each vector
 *
 * VQ must already be configured by caller, any further updates of VQ
 * will need to ensure that the register state remains valid.
 *
 * x0 = VQ - 1
 */
SYM_FUNC_START(sve_flush_live)
	cbz		x0, 1f	// A VQ-1 of 0 is 128 bits so no extra Z state
	sve_flush_z
1:	sve_flush_p_ffr
	ret
SYM_FUNC_END(sve_flush_live)

#endif /* CONFIG_ARM64_SVE */
