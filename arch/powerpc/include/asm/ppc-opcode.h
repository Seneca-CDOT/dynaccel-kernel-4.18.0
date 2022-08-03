/*
 * Copyright 2009 Freescale Semiconductor, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 * provides masks and opcode images for use by code generation, emulation
 * and for instructions that older assemblers might not know about
 */
#ifndef _ASM_POWERPC_PPC_OPCODE_H
#define _ASM_POWERPC_PPC_OPCODE_H

#include <linux/stringify.h>
#include <asm/asm-compat.h>

#define	__REG_R0	0
#define	__REG_R1	1
#define	__REG_R2	2
#define	__REG_R3	3
#define	__REG_R4	4
#define	__REG_R5	5
#define	__REG_R6	6
#define	__REG_R7	7
#define	__REG_R8	8
#define	__REG_R9	9
#define	__REG_R10	10
#define	__REG_R11	11
#define	__REG_R12	12
#define	__REG_R13	13
#define	__REG_R14	14
#define	__REG_R15	15
#define	__REG_R16	16
#define	__REG_R17	17
#define	__REG_R18	18
#define	__REG_R19	19
#define	__REG_R20	20
#define	__REG_R21	21
#define	__REG_R22	22
#define	__REG_R23	23
#define	__REG_R24	24
#define	__REG_R25	25
#define	__REG_R26	26
#define	__REG_R27	27
#define	__REG_R28	28
#define	__REG_R29	29
#define	__REG_R30	30
#define	__REG_R31	31

#define	__REGA0_0	0
#define	__REGA0_R1	1
#define	__REGA0_R2	2
#define	__REGA0_R3	3
#define	__REGA0_R4	4
#define	__REGA0_R5	5
#define	__REGA0_R6	6
#define	__REGA0_R7	7
#define	__REGA0_R8	8
#define	__REGA0_R9	9
#define	__REGA0_R10	10
#define	__REGA0_R11	11
#define	__REGA0_R12	12
#define	__REGA0_R13	13
#define	__REGA0_R14	14
#define	__REGA0_R15	15
#define	__REGA0_R16	16
#define	__REGA0_R17	17
#define	__REGA0_R18	18
#define	__REGA0_R19	19
#define	__REGA0_R20	20
#define	__REGA0_R21	21
#define	__REGA0_R22	22
#define	__REGA0_R23	23
#define	__REGA0_R24	24
#define	__REGA0_R25	25
#define	__REGA0_R26	26
#define	__REGA0_R27	27
#define	__REGA0_R28	28
#define	__REGA0_R29	29
#define	__REGA0_R30	30
#define	__REGA0_R31	31

/* For use with PPC_RAW_() macros */
#define	_R0	0
#define	_R1	1
#define	_R2	2
#define	_R3	3
#define	_R4	4
#define	_R5	5
#define	_R6	6
#define	_R7	7
#define	_R8	8
#define	_R9	9
#define	_R10	10
#define	_R11	11
#define	_R12	12
#define	_R13	13
#define	_R14	14
#define	_R15	15
#define	_R16	16
#define	_R17	17
#define	_R18	18
#define	_R19	19
#define	_R20	20
#define	_R21	21
#define	_R22	22
#define	_R23	23
#define	_R24	24
#define	_R25	25
#define	_R26	26
#define	_R27	27
#define	_R28	28
#define	_R29	29
#define	_R30	30
#define	_R31	31

#define IMM_L(i)               ((uintptr_t)(i) & 0xffff)
#define IMM_DS(i)              ((uintptr_t)(i) & 0xfffc)
#define IMM_DQ(i)              ((uintptr_t)(i) & 0xfff0)
#define IMM_D0(i)              (((uintptr_t)(i) >> 16) & 0x3ffff)
#define IMM_D1(i)              IMM_L(i)

/*
 * 16-bit immediate helper macros: HA() is for use with sign-extending instrs
 * (e.g. LD, ADDI).  If the bottom 16 bits is "-ve", add another bit into the
 * top half to negate the effect (i.e. 0xffff + 1 = 0x(1)0000).
 */
#define IMM_H(i)                ((uintptr_t)(i)>>16)
#define IMM_HA(i)               (((uintptr_t)(i)>>16) +                       \
					(((uintptr_t)(i) & 0x8000) >> 15))


/* opcode and xopcode for instructions */
#define OP_TRAP 3
#define OP_TRAP_64 2

#define OP_31_XOP_TRAP      4
#define OP_31_XOP_LDX       21
#define OP_31_XOP_LWZX      23
#define OP_31_XOP_LDUX      53
#define OP_31_XOP_DCBST     54
#define OP_31_XOP_LWZUX     55
#define OP_31_XOP_TRAP_64   68
#define OP_31_XOP_DCBF      86
#define OP_31_XOP_LBZX      87
#define OP_31_XOP_STDX      149
#define OP_31_XOP_STWX      151
#define OP_31_XOP_STDUX     181
#define OP_31_XOP_STWUX     183
#define OP_31_XOP_STBX      215
#define OP_31_XOP_LBZUX     119
#define OP_31_XOP_STBUX     247
#define OP_31_XOP_LHZX      279
#define OP_31_XOP_LHZUX     311
#define OP_31_XOP_MSGSNDP   142
#define OP_31_XOP_MSGCLRP   174
#define OP_31_XOP_TLBIE     306
#define OP_31_XOP_MFSPR     339
#define OP_31_XOP_LWAX      341
#define OP_31_XOP_LHAX      343
#define OP_31_XOP_LWAUX     373
#define OP_31_XOP_LHAUX     375
#define OP_31_XOP_STHX      407
#define OP_31_XOP_STHUX     439
#define OP_31_XOP_MTSPR     467
#define OP_31_XOP_DCBI      470
#define OP_31_XOP_LDBRX     532
#define OP_31_XOP_LWBRX     534
#define OP_31_XOP_TLBSYNC   566
#define OP_31_XOP_STDBRX    660
#define OP_31_XOP_STWBRX    662
#define OP_31_XOP_STFSX	    663
#define OP_31_XOP_STFSUX    695
#define OP_31_XOP_STFDX     727
#define OP_31_XOP_STFDUX    759
#define OP_31_XOP_LHBRX     790
#define OP_31_XOP_LFIWAX    855
#define OP_31_XOP_LFIWZX    887
#define OP_31_XOP_STHBRX    918
#define OP_31_XOP_STFIWX    983

/* VSX Scalar Load Instructions */
#define OP_31_XOP_LXSDX         588
#define OP_31_XOP_LXSSPX        524
#define OP_31_XOP_LXSIWAX       76
#define OP_31_XOP_LXSIWZX       12

/* VSX Scalar Store Instructions */
#define OP_31_XOP_STXSDX        716
#define OP_31_XOP_STXSSPX       652
#define OP_31_XOP_STXSIWX       140

/* VSX Vector Load Instructions */
#define OP_31_XOP_LXVD2X        844
#define OP_31_XOP_LXVW4X        780

/* VSX Vector Load and Splat Instruction */
#define OP_31_XOP_LXVDSX        332

/* VSX Vector Store Instructions */
#define OP_31_XOP_STXVD2X       972
#define OP_31_XOP_STXVW4X       908

#define OP_31_XOP_LFSX          535
#define OP_31_XOP_LFSUX         567
#define OP_31_XOP_LFDX          599
#define OP_31_XOP_LFDUX		631

/* VMX Vector Load Instructions */
#define OP_31_XOP_LVX           103

/* VMX Vector Store Instructions */
#define OP_31_XOP_STVX          231

/* Prefixed Instructions */
#define OP_PREFIX		1

#define OP_31   31
#define OP_LWZ  32
#define OP_STFS 52
#define OP_STFSU 53
#define OP_STFD 54
#define OP_STFDU 55
#define OP_LD   58
#define OP_LWZU 33
#define OP_LBZ  34
#define OP_LBZU 35
#define OP_STW  36
#define OP_STWU 37
#define OP_STD  62
#define OP_STB  38
#define OP_STBU 39
#define OP_LHZ  40
#define OP_LHZU 41
#define OP_LHA  42
#define OP_LHAU 43
#define OP_STH  44
#define OP_STHU 45
#define OP_LMW  46
#define OP_STMW 47
#define OP_LFS  48
#define OP_LFSU 49
#define OP_LFD  50
#define OP_LFDU 51
#define OP_STFS 52
#define OP_STFSU 53
#define OP_STFD  54
#define OP_STFDU 55
#define OP_LQ    56

/* sorted alphabetically */
#define PPC_INST_BCCTR_FLUSH		0x4c400420
#define PPC_INST_BHRBE			0x7c00025c
#define PPC_INST_CLRBHRB		0x7c00035c
#define PPC_INST_COPY			0x7c20060c
#define PPC_INST_CP_ABORT		0x7c00068c
#define PPC_INST_DARN			0x7c0005e6
#define PPC_INST_DCBA			0x7c0005ec
#define PPC_INST_DCBA_MASK		0xfc0007fe
#define PPC_INST_DCBAL			0x7c2005ec
#define PPC_INST_DCBZL			0x7c2007ec
#define PPC_INST_ICBT			0x7c00002c
#define PPC_INST_ICSWX			0x7c00032d
#define PPC_INST_ICSWEPX		0x7c00076d
#define PPC_INST_ISEL			0x7c00001e
#define PPC_INST_ISEL_MASK		0xfc00003e
#define PPC_INST_LDARX			0x7c0000a8
#define PPC_INST_STDCX			0x7c0001ad
#define PPC_INST_LQARX			0x7c000228
#define PPC_INST_STQCX			0x7c00016d
#define PPC_INST_LSWI			0x7c0004aa
#define PPC_INST_LSWX			0x7c00042a
#define PPC_INST_LWARX			0x7c000028
#define PPC_INST_STWCX			0x7c00012d
#define PPC_INST_LWSYNC			0x7c2004ac
#define PPC_INST_SYNC			0x7c0004ac
#define PPC_INST_PHWSYNC		0x7c8004ac
#define PPC_INST_PLWSYNC		0x7ca004ac
#define PPC_INST_SYNC_MASK		0xfc0007fe
#define PPC_INST_ISYNC			0x4c00012c
#define PPC_INST_LXVD2X			0x7c000698
#define PPC_INST_MCRXR			0x7c000400
#define PPC_INST_MCRXR_MASK		0xfc0007fe
#define PPC_INST_MFSPR_PVR		0x7c1f42a6
#define PPC_INST_MFSPR_PVR_MASK		0xfc1ffffe
#define PPC_INST_MFTMR			0x7c0002dc
#define PPC_INST_MSGSND			0x7c00019c
#define PPC_INST_MSGCLR			0x7c0001dc
#define PPC_INST_MSGSYNC		0x7c0006ec
#define PPC_INST_MSGSNDP		0x7c00011c
#define PPC_INST_MSGCLRP		0x7c00015c
#define PPC_INST_MTMSRD			0x7c000164
#define PPC_INST_MTTMR			0x7c0003dc
#define PPC_INST_NOP			0x60000000
#define PPC_INST_PASTE			0x7c20070d
#define PPC_INST_PASTE_MASK		0xfc2007ff
#define PPC_INST_POPCNTB		0x7c0000f4
#define PPC_INST_POPCNTB_MASK		0xfc0007fe
#define PPC_INST_POPCNTD		0x7c0003f4
#define PPC_INST_POPCNTW		0x7c0002f4
#define PPC_INST_RFEBB			0x4c000124
#define PPC_INST_RFCI			0x4c000066
#define PPC_INST_RFDI			0x4c00004e
#define PPC_INST_RFID			0x4c000024
#define PPC_INST_RFMCI			0x4c00004c
#define PPC_INST_MFSPR			0x7c0002a6
#define PPC_INST_MFSPR_DSCR		0x7c1102a6
#define PPC_INST_MFSPR_DSCR_MASK	0xfc1ffffe
#define PPC_INST_MTSPR_DSCR		0x7c1103a6
#define PPC_INST_MTSPR_DSCR_MASK	0xfc1ffffe
#define PPC_INST_MFSPR_DSCR_USER	0x7c0302a6
#define PPC_INST_MFSPR_DSCR_USER_MASK	0xfc1ffffe
#define PPC_INST_MTSPR_DSCR_USER	0x7c0303a6
#define PPC_INST_MTSPR_DSCR_USER_MASK	0xfc1ffffe
#define PPC_INST_MFVSRD			0x7c000066
#define PPC_INST_MTVSRD			0x7c000166
#define PPC_INST_SLBFEE			0x7c0007a7
#define PPC_INST_SLBIA			0x7c0003e4

#define PPC_INST_STRING			0x7c00042a
#define PPC_INST_STRING_MASK		0xfc0007fe
#define PPC_INST_STRING_GEN_MASK	0xfc00067e

#define PPC_INST_STSWI			0x7c0005aa
#define PPC_INST_STSWX			0x7c00052a
#define PPC_INST_STXVD2X		0x7c000798
#define PPC_INST_TLBIE			0x7c000264
#define PPC_INST_TLBIEL			0x7c000224
#define PPC_INST_TLBILX			0x7c000024
#define PPC_INST_WAIT			0x7c00007c
#define PPC_INST_TLBIVAX		0x7c000624
#define PPC_INST_TLBSRX_DOT		0x7c0006a5
#define PPC_INST_VPMSUMW		0x10000488
#define PPC_INST_VPMSUMD		0x100004c8
#define PPC_INST_VPERMXOR		0x1000002d
#define PPC_INST_XXLOR			0xf0000490
#define PPC_INST_XXSWAPD		0xf0000250
#define PPC_INST_XVCPSGNDP		0xf0000780
#define PPC_INST_TRECHKPT		0x7c0007dd
#define PPC_INST_TRECLAIM		0x7c00075d
#define PPC_INST_TABORT			0x7c00071d
#define PPC_INST_TSR			0x7c0005dd

#define PPC_INST_DCBF			0x7c0000ac

#define PPC_INST_NAP			0x4c000364
#define PPC_INST_SLEEP			0x4c0003a4
#define PPC_INST_WINKLE			0x4c0003e4

#define PPC_INST_STOP			0x4c0002e4

/* A2 specific instructions */
#define PPC_INST_ERATWE			0x7c0001a6
#define PPC_INST_ERATRE			0x7c000166
#define PPC_INST_ERATILX		0x7c000066
#define PPC_INST_ERATIVAX		0x7c000666
#define PPC_INST_ERATSX			0x7c000126
#define PPC_INST_ERATSX_DOT		0x7c000127

/* Misc instructions for BPF compiler */
#define PPC_INST_LBZ			0x88000000
#define PPC_INST_LD			0xe8000000
#define PPC_INST_LDX			0x7c00002a
#define PPC_INST_LHZ			0xa0000000
#define PPC_INST_LWZ			0x80000000
#define PPC_INST_LHBRX			0x7c00062c
#define PPC_INST_LDBRX			0x7c000428
#define PPC_INST_STB			0x98000000
#define PPC_INST_STH			0xb0000000
#define PPC_INST_STD			0xf8000000
#define PPC_INST_STDX			0x7c00012a
#define PPC_INST_STDU			0xf8000001
#define PPC_INST_STW			0x90000000
#define PPC_INST_STWU			0x94000000
#define PPC_INST_MFLR			0x7c0802a6
#define PPC_INST_MTLR			0x7c0803a6
#define PPC_INST_MTCTR			0x7c0903a6
#define PPC_INST_CMPWI			0x2c000000
#define PPC_INST_CMPDI			0x2c200000
#define PPC_INST_CMPW			0x7c000000
#define PPC_INST_CMPD			0x7c200000
#define PPC_INST_CMPLW			0x7c000040
#define PPC_INST_CMPLD			0x7c200040
#define PPC_INST_CMPLWI			0x28000000
#define PPC_INST_CMPLDI			0x28200000
#define PPC_INST_ADDI			0x38000000
#define PPC_INST_ADDIS			0x3c000000
#define PPC_INST_ADD			0x7c000214
#define PPC_INST_ADDC			0x7c000014
#define PPC_INST_SUB			0x7c000050
#define PPC_INST_BLR			0x4e800020
#define PPC_INST_BLRL			0x4e800021
#define PPC_INST_BCTR			0x4e800420
#define PPC_INST_MULLD			0x7c0001d2
#define PPC_INST_MULLW			0x7c0001d6
#define PPC_INST_MULHWU			0x7c000016
#define PPC_INST_MULLI			0x1c000000
#define PPC_INST_MADDHD			0x10000030
#define PPC_INST_MADDHDU		0x10000031
#define PPC_INST_MADDLD			0x10000033
#define PPC_INST_DIVWU			0x7c000396
#define PPC_INST_DIVD			0x7c0003d2
#define PPC_INST_DIVDU			0x7c000392
#define PPC_INST_RLWINM			0x54000000
#define PPC_INST_RLWINM_DOT		0x54000001
#define PPC_INST_RLWIMI			0x50000000
#define PPC_INST_RLDICL			0x78000000
#define PPC_INST_RLDICR			0x78000004
#define PPC_INST_SLW			0x7c000030
#define PPC_INST_SLD			0x7c000036
#define PPC_INST_SRW			0x7c000430
#define PPC_INST_SRAW			0x7c000630
#define PPC_INST_SRAWI			0x7c000670
#define PPC_INST_SRD			0x7c000436
#define PPC_INST_SRAD			0x7c000634
#define PPC_INST_SRADI			0x7c000674
#define PPC_INST_AND			0x7c000038
#define PPC_INST_ANDDOT			0x7c000039
#define PPC_INST_OR			0x7c000378
#define PPC_INST_XOR			0x7c000278
#define PPC_INST_ANDI			0x70000000
#define PPC_INST_ORI			0x60000000
#define PPC_INST_ORIS			0x64000000
#define PPC_INST_XORI			0x68000000
#define PPC_INST_XORIS			0x6c000000
#define PPC_INST_NEG			0x7c0000d0
#define PPC_INST_EXTSW			0x7c0007b4
#define PPC_INST_BRANCH			0x48000000
#define PPC_INST_BL			0x48000001
#define PPC_INST_BRANCH_COND		0x40800000
#define PPC_INST_LBZCIX			0x7c0006aa
#define PPC_INST_STBCIX			0x7c0007aa
#define PPC_INST_LWZX			0x7c00002e
#define PPC_INST_LFSX			0x7c00042e
#define PPC_INST_STFSX			0x7c00052e
#define PPC_INST_LFDX			0x7c0004ae
#define PPC_INST_STFDX			0x7c0005ae
#define PPC_INST_LVX			0x7c0000ce
#define PPC_INST_STVX			0x7c0001ce

/* Prefixes */
#define PPC_INST_LFS			0xc0000000
#define PPC_INST_STFS			0xd0000000
#define PPC_INST_LFD			0xc8000000
#define PPC_INST_STFD			0xd8000000
#define PPC_PREFIX_MLS			0x06000000
#define PPC_PREFIX_8LS			0x04000000

/* Prefixed instructions */
#define PPC_INST_PLD			0xe4000000
#define PPC_INST_PSTD			0xf4000000

/* macros to insert fields into opcodes */
#define ___PPC_RA(a)	(((a) & 0x1f) << 16)
#define ___PPC_RB(b)	(((b) & 0x1f) << 11)
#define ___PPC_RC(c)	(((c) & 0x1f) << 6)
#define ___PPC_RS(s)	(((s) & 0x1f) << 21)
#define ___PPC_RT(t)	___PPC_RS(t)
#define ___PPC_R(r)	(((r) & 0x1) << 16)
#define ___PPC_PRS(prs)	(((prs) & 0x1) << 17)
#define ___PPC_RIC(ric)	(((ric) & 0x3) << 18)
#define __PPC_RA(a)	___PPC_RA(__REG_##a)
#define __PPC_RA0(a)	___PPC_RA(__REGA0_##a)
#define __PPC_RB(b)	___PPC_RB(__REG_##b)
#define __PPC_RS(s)	___PPC_RS(__REG_##s)
#define __PPC_RT(t)	___PPC_RT(__REG_##t)
#define __PPC_XA(a)	((((a) & 0x1f) << 16) | (((a) & 0x20) >> 3))
#define __PPC_XB(b)	((((b) & 0x1f) << 11) | (((b) & 0x20) >> 4))
#define __PPC_XS(s)	((((s) & 0x1f) << 21) | (((s) & 0x20) >> 5))
#define __PPC_XT(s)	__PPC_XS(s)
#define __PPC_XSP(s)	((((s) & 0x1e) | (((s) >> 5) & 0x1)) << 21)
#define __PPC_XTP(s)	__PPC_XSP(s)
#define __PPC_T_TLB(t)	(((t) & 0x3) << 21)
#define __PPC_WC(w)	(((w) & 0x3) << 21)
#define __PPC_WS(w)	(((w) & 0x1f) << 11)
#define __PPC_SH(s)	__PPC_WS(s)
#define __PPC_SH64(s)	(__PPC_SH(s) | (((s) & 0x20) >> 4))
#define __PPC_MB(s)	___PPC_RC(s)
#define __PPC_ME(s)	(((s) & 0x1f) << 1)
#define __PPC_MB64(s)	(__PPC_MB(s) | ((s) & 0x20))
#define __PPC_ME64(s)	__PPC_MB64(s)
#define __PPC_BI(s)	(((s) & 0x1f) << 16)
#define __PPC_CT(t)	(((t) & 0x0f) << 21)
#define __PPC_SPR(r)	((((r) & 0x1f) << 16) | ((((r) >> 5) & 0x1f) << 11))
#define __PPC_PRFX_R(r)	(((r) & 0x1) << 20)

/*
 * Only use the larx hint bit on 64bit CPUs. e500v1/v2 based CPUs will treat a
 * larx with EH set as an illegal instruction.
 */
#ifdef CONFIG_PPC64
#define __PPC_EH(eh)	(((eh) & 0x1) << 0)
#else
#define __PPC_EH(eh)	0
#endif

/* Base instruction encoding */
#define PPC_RAW_CP_ABORT		(PPC_INST_CP_ABORT)
#define PPC_RAW_COPY(a, b)		(PPC_INST_COPY | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_DARN(t, l)		(PPC_INST_DARN | ___PPC_RT(t) | (((l) & 0x3) << 16))
#define PPC_RAW_DCBAL(a, b)		(PPC_INST_DCBAL | __PPC_RA(a) | __PPC_RB(b))
#define PPC_RAW_DCBZL(a, b)		(PPC_INST_DCBZL | __PPC_RA(a) | __PPC_RB(b))
#define PPC_RAW_LQARX(t, a, b, eh)	(PPC_INST_LQARX | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | __PPC_EH(eh))
#define PPC_RAW_LDARX(t, a, b, eh)	(PPC_INST_LDARX | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | __PPC_EH(eh))
#define PPC_RAW_LWARX(t, a, b, eh)	(PPC_INST_LWARX | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | __PPC_EH(eh))
#define PPC_RAW_PHWSYNC			(PPC_INST_PHWSYNC)
#define PPC_RAW_PLWSYNC			(PPC_INST_PLWSYNC)
#define PPC_RAW_STQCX(t, a, b)		(PPC_INST_STQCX | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_MADDHD(t, a, b, c)	(PPC_INST_MADDHD | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | ___PPC_RC(c))
#define PPC_RAW_MADDHDU(t, a, b, c)	(PPC_INST_MADDHDU | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | ___PPC_RC(c))
#define PPC_RAW_MADDLD(t, a, b, c)	(PPC_INST_MADDLD | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | ___PPC_RC(c))
#define PPC_RAW_MSGSND(b)		(PPC_INST_MSGSND | ___PPC_RB(b))
#define PPC_RAW_MSGSYNC			(PPC_INST_MSGSYNC)
#define PPC_RAW_MSGCLR(b)		(PPC_INST_MSGCLR | ___PPC_RB(b))
#define PPC_RAW_MSGSNDP(b)		(PPC_INST_MSGSNDP | ___PPC_RB(b))
#define PPC_RAW_MSGCLRP(b)		(PPC_INST_MSGCLRP | ___PPC_RB(b))
#define PPC_RAW_PASTE(a, b)		(PPC_INST_PASTE | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_POPCNTB(a, s)		(PPC_INST_POPCNTB | __PPC_RA(a) | __PPC_RS(s))
#define PPC_RAW_POPCNTD(a, s)		(PPC_INST_POPCNTD | __PPC_RA(a) | __PPC_RS(s))
#define PPC_RAW_POPCNTW(a, s)		(PPC_INST_POPCNTW | __PPC_RA(a) | __PPC_RS(s))
#define PPC_RAW_RFCI			(PPC_INST_RFCI)
#define PPC_RAW_RFDI			(PPC_INST_RFDI)
#define PPC_RAW_RFMCI			(PPC_INST_RFMCI)
#define PPC_RAW_TLBILX(t, a, b)		(PPC_INST_TLBILX | __PPC_T_TLB(t) | __PPC_RA0(a) | __PPC_RB(b))
#define PPC_RAW_WAIT(w)			(PPC_INST_WAIT | __PPC_WC(w))
#define PPC_RAW_TLBIE(lp, a)		(PPC_INST_TLBIE | ___PPC_RB(a) | ___PPC_RS(lp))
#define PPC_RAW_TLBIE_5(rb, rs, ric, prs, r) \
	(PPC_INST_TLBIE | ___PPC_RB(rb) | ___PPC_RS(rs) | ___PPC_RIC(ric) | ___PPC_PRS(prs) | ___PPC_R(r))
#define PPC_RAW_TLBIEL(rb, rs, ric, prs, r) \
	(PPC_INST_TLBIEL | ___PPC_RB(rb) | ___PPC_RS(rs) | ___PPC_RIC(ric) | ___PPC_PRS(prs) | ___PPC_R(r))
#define PPC_RAW_TLBSRX_DOT(a, b)	(PPC_INST_TLBSRX_DOT | __PPC_RA0(a) | __PPC_RB(b))
#define PPC_RAW_TLBIVAX(a, b)		(PPC_INST_TLBIVAX | __PPC_RA0(a) | __PPC_RB(b))
#define PPC_RAW_ERATWE(s, a, w)		(PPC_INST_ERATWE | __PPC_RS(s) | __PPC_RA(a) | __PPC_WS(w))
#define PPC_RAW_ERATRE(s, a, w)		(PPC_INST_ERATRE | __PPC_RS(s) | __PPC_RA(a) | __PPC_WS(w))
#define PPC_RAW_ERATILX(t, a, b)	(PPC_INST_ERATILX | __PPC_T_TLB(t) | __PPC_RA0(a) | __PPC_RB(b))
#define PPC_RAW_ERATIVAX(s, a, b)	(PPC_INST_ERATIVAX | __PPC_RS(s) | __PPC_RA0(a) | __PPC_RB(b))
#define PPC_RAW_ERATSX(t, a, w)		(PPC_INST_ERATSX | __PPC_RS(t) | __PPC_RA0(a) | __PPC_RB(b))
#define PPC_RAW_ERATSX_DOT(t, a, w)	(PPC_INST_ERATSX_DOT | __PPC_RS(t) | __PPC_RA0(a) | __PPC_RB(b))
#define PPC_RAW_SLBFEE_DOT(t, b)	(PPC_INST_SLBFEE | __PPC_RT(t) | __PPC_RB(b))
#define __PPC_RAW_SLBFEE_DOT(t, b)	(PPC_INST_SLBFEE | ___PPC_RT(t) | ___PPC_RB(b))
#define PPC_RAW_ICBT(c, a, b)		(PPC_INST_ICBT | __PPC_CT(c) | __PPC_RA0(a) | __PPC_RB(b))
#define PPC_RAW_LBZCIX(t, a, b)		(PPC_INST_LBZCIX | __PPC_RT(t) | __PPC_RA(a) | __PPC_RB(b))
#define PPC_RAW_STBCIX(s, a, b)		(PPC_INST_STBCIX | __PPC_RS(s) | __PPC_RA(a) | __PPC_RB(b))
#define PPC_RAW_DCBFPS(a, b)		(PPC_INST_DCBF | ___PPC_RA(a) | ___PPC_RB(b) | (4 << 21))
#define PPC_RAW_DCBSTPS(a, b)		(PPC_INST_DCBF | ___PPC_RA(a) | ___PPC_RB(b) | (6 << 21))
/*
 * Define what the VSX XX1 form instructions will look like, then add
 * the 128 bit load store instructions based on that.
 */
#define VSX_XX1(s, a, b)		(__PPC_XS(s) | __PPC_RA(a) | __PPC_RB(b))
#define VSX_XX3(t, a, b)		(__PPC_XT(t) | __PPC_XA(a) | __PPC_XB(b))
#define PPC_RAW_STXVD2X(s, a, b)	(PPC_INST_STXVD2X | VSX_XX1((s), a, b))
#define PPC_RAW_LXVD2X(s, a, b)		(PPC_INST_LXVD2X | VSX_XX1((s), a, b))
#define PPC_RAW_MFVRD(a, t)		(PPC_INST_MFVSRD | VSX_XX1((t) + 32, a, R0))
#define PPC_RAW_MTVRD(t, a)		(PPC_INST_MTVSRD | VSX_XX1((t) + 32, a, R0))
#define PPC_RAW_VPMSUMW(t, a, b)	(PPC_INST_VPMSUMW | VSX_XX3((t), a, b))
#define PPC_RAW_VPMSUMD(t, a, b)	(PPC_INST_VPMSUMD | VSX_XX3((t), a, b))
#define PPC_RAW_XXLOR(t, a, b)		(PPC_INST_XXLOR | VSX_XX3((t), a, b))
#define PPC_RAW_XXSWAPD(t, a)		(PPC_INST_XXSWAPD | VSX_XX3((t), a, a))
#define PPC_RAW_XVCPSGNDP(t, a, b)	((PPC_INST_XVCPSGNDP | VSX_XX3((t), (a), (b))))
#define PPC_RAW_VPERMXOR(vrt, vra, vrb, vrc) \
	((PPC_INST_VPERMXOR | ___PPC_RT(vrt) | ___PPC_RA(vra) | ___PPC_RB(vrb) | (((vrc) & 0x1f) << 6)))
#define PPC_RAW_LXVP(xtp, a, i)		(0x18000000 | __PPC_XTP(xtp) | ___PPC_RA(a) | IMM_DQ(i))
#define PPC_RAW_STXVP(xsp, a, i)	(0x18000001 | __PPC_XSP(xsp) | ___PPC_RA(a) | IMM_DQ(i))
#define PPC_RAW_LXVPX(xtp, a, b)	(0x7c00029a | __PPC_XTP(xtp) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_STXVPX(xsp, a, b)	(0x7c00039a | __PPC_XSP(xsp) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_PLXVP(xtp, i, a, pr) \
	((PPC_PREFIX_8LS | __PPC_PRFX_R(pr) | IMM_D0(i)) << 32 | (0xe8000000 | __PPC_XTP(xtp) | ___PPC_RA(a) | IMM_D1(i)))
#define PPC_RAW_PSTXVP(xsp, i, a, pr) \
	((PPC_PREFIX_8LS | __PPC_PRFX_R(pr) | IMM_D0(i)) << 32 | (0xf8000000 | __PPC_XSP(xsp) | ___PPC_RA(a) | IMM_D1(i)))
#define PPC_RAW_NAP			(PPC_INST_NAP)
#define PPC_RAW_SLEEP			(PPC_INST_SLEEP)
#define PPC_RAW_WINKLE			(PPC_INST_WINKLE)
#define PPC_RAW_STOP			(PPC_INST_STOP)
#define PPC_RAW_CLRBHRB			(PPC_INST_CLRBHRB)
#define PPC_RAW_MFBHRBE(r, n)		(PPC_INST_BHRBE | __PPC_RT(r) | (((n) & 0x3ff) << 11))
#define PPC_RAW_TRECHKPT		(PPC_INST_TRECHKPT)
#define PPC_RAW_TRECLAIM(r)		(PPC_INST_TRECLAIM | __PPC_RA(r))
#define PPC_RAW_TABORT(r)		(PPC_INST_TABORT | __PPC_RA(r))
#define TMRN(x)				((((x) & 0x1f) << 16) | (((x) & 0x3e0) << 6))
#define PPC_RAW_MTTMR(tmr, r)		(PPC_INST_MTTMR | TMRN(tmr) | ___PPC_RS(r))
#define PPC_RAW_MFTMR(tmr, r)		(PPC_INST_MFTMR | TMRN(tmr) | ___PPC_RT(r))
#define PPC_RAW_ICSWX(s, a, b)		(PPC_INST_ICSWX | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_ICSWEPX(s, a, b)	(PPC_INST_ICSWEPX | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_SLBIA(IH)		(PPC_INST_SLBIA | (((IH) & 0x7) << 21))
#define PPC_RAW_VCMPEQUD_RC(vrt, vra, vrb) \
	(PPC_INST_VCMPEQUD | ___PPC_RT(vrt) | ___PPC_RA(vra) | ___PPC_RB(vrb) | __PPC_RC21)
#define PPC_RAW_VCMPEQUB_RC(vrt, vra, vrb) \
	(PPC_INST_VCMPEQUB | ___PPC_RT(vrt) | ___PPC_RA(vra) | ___PPC_RB(vrb) | __PPC_RC21)
#define PPC_RAW_LD(r, base, i)		(PPC_INST_LD | ___PPC_RT(r) | ___PPC_RA(base) | IMM_DS(i))
#define PPC_RAW_LWZ(r, base, i)		(PPC_INST_LWZ | ___PPC_RT(r) | ___PPC_RA(base) | IMM_L(i))
#define PPC_RAW_LWZX(t, a, b)		(PPC_INST_LWZX | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_STD(r, base, i)		(PPC_INST_STD | ___PPC_RS(r) | ___PPC_RA(base) | IMM_DS(i))
#define PPC_RAW_STDCX(s, a, b)		(PPC_INST_STDCX | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_LFSX(t, a, b)		(PPC_INST_LFSX | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_STFSX(s, a, b)		(PPC_INST_STFSX | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_LFDX(t, a, b)		(PPC_INST_LFDX | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_STFDX(s, a, b)		(PPC_INST_STFDX | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_LVX(t, a, b)		(PPC_INST_LVX | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_STVX(s, a, b)		(PPC_INST_STVX | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_ADD(t, a, b)		(PPC_INST_ADD | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_ADD_DOT(t, a, b)	(PPC_INST_ADD | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | 0x1)
#define PPC_RAW_ADDC(t, a, b)		(PPC_INST_ADDC | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_ADDC_DOT(t, a, b)	(PPC_INST_ADDC | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | 0x1)
#define PPC_RAW_NOP()			(PPC_INST_NOP)
#define PPC_RAW_BLR()			(PPC_INST_BLR)
#define PPC_RAW_BLRL()			(PPC_INST_BLRL)
#define PPC_RAW_MTLR(r)			(PPC_INST_MTLR | ___PPC_RT(r))
#define PPC_RAW_MFLR(t)			(0x7c0802a6 | ___PPC_RT(t))
#define PPC_RAW_BCTR()			(PPC_INST_BCTR)
#define PPC_RAW_BCTRL()			(0x4e800421)
#define PPC_RAW_MTCTR(r)		(PPC_INST_MTCTR | ___PPC_RT(r))
#define PPC_RAW_ADDI(d, a, i)		(PPC_INST_ADDI | ___PPC_RT(d) | ___PPC_RA(a) | IMM_L(i))
#define PPC_RAW_LI(r, i)		PPC_RAW_ADDI(r, 0, i)
#define PPC_RAW_ADDIS(d, a, i)		(PPC_INST_ADDIS | ___PPC_RT(d) | ___PPC_RA(a) | IMM_L(i))
#define PPC_RAW_LIS(r, i)		PPC_RAW_ADDIS(r, 0, i)
#define PPC_RAW_STDX(r, base, b)	(PPC_INST_STDX | ___PPC_RS(r) | ___PPC_RA(base) | ___PPC_RB(b))
#define PPC_RAW_STDU(r, base, i)	(PPC_INST_STDU | ___PPC_RS(r) | ___PPC_RA(base) | ((i) & 0xfffc))
#define PPC_RAW_STW(r, base, i)		(PPC_INST_STW | ___PPC_RS(r) | ___PPC_RA(base) | IMM_L(i))
#define PPC_RAW_STWU(r, base, i)	(PPC_INST_STWU | ___PPC_RS(r) | ___PPC_RA(base) | IMM_L(i))
#define PPC_RAW_STH(r, base, i)		(PPC_INST_STH | ___PPC_RS(r) | ___PPC_RA(base) | IMM_L(i))
#define PPC_RAW_STB(r, base, i)		(PPC_INST_STB | ___PPC_RS(r) | ___PPC_RA(base) | IMM_L(i))
#define PPC_RAW_LBZ(r, base, i)		(PPC_INST_LBZ | ___PPC_RT(r) | ___PPC_RA(base) | IMM_L(i))
#define PPC_RAW_LDX(r, base, b)		(PPC_INST_LDX | ___PPC_RT(r) | ___PPC_RA(base) | ___PPC_RB(b))
#define PPC_RAW_LHZ(r, base, i)		(PPC_INST_LHZ | ___PPC_RT(r) | ___PPC_RA(base) | IMM_L(i))
#define PPC_RAW_LHBRX(r, base, b)	(PPC_INST_LHBRX | ___PPC_RT(r) | ___PPC_RA(base) | ___PPC_RB(b))
#define PPC_RAW_LDBRX(r, base, b)	(PPC_INST_LDBRX | ___PPC_RT(r) | ___PPC_RA(base) | ___PPC_RB(b))
#define PPC_RAW_STWCX(s, a, b)		(PPC_INST_STWCX | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_CMPWI(a, i)		(PPC_INST_CMPWI | ___PPC_RA(a) | IMM_L(i))
#define PPC_RAW_CMPDI(a, i)		(PPC_INST_CMPDI | ___PPC_RA(a) | IMM_L(i))
#define PPC_RAW_CMPW(a, b)		(PPC_INST_CMPW | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_CMPD(a, b)		(PPC_INST_CMPD | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_CMPLWI(a, i)		(PPC_INST_CMPLWI | ___PPC_RA(a) | IMM_L(i))
#define PPC_RAW_CMPLDI(a, i)		(PPC_INST_CMPLDI | ___PPC_RA(a) | IMM_L(i))
#define PPC_RAW_CMPLW(a, b)		(PPC_INST_CMPLW | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_CMPLD(a, b)		(PPC_INST_CMPLD | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_SUB(d, a, b)		(PPC_INST_SUB | ___PPC_RT(d) | ___PPC_RB(a) | ___PPC_RA(b))
#define PPC_RAW_MULD(d, a, b)		(PPC_INST_MULLD | ___PPC_RT(d) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_MULW(d, a, b)		(PPC_INST_MULLW | ___PPC_RT(d) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_MULHWU(d, a, b)		(PPC_INST_MULHWU | ___PPC_RT(d) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_MULI(d, a, i)		(PPC_INST_MULLI | ___PPC_RT(d) | ___PPC_RA(a) | IMM_L(i))
#define PPC_RAW_DIVWU(d, a, b)		(PPC_INST_DIVWU | ___PPC_RT(d) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_DIVDU(d, a, b)		(PPC_INST_DIVDU | ___PPC_RT(d) | ___PPC_RA(a) | ___PPC_RB(b))
#define PPC_RAW_AND(d, a, b)		(PPC_INST_AND | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(b))
#define PPC_RAW_ANDI(d, a, i)		(PPC_INST_ANDI | ___PPC_RA(d) | ___PPC_RS(a) | IMM_L(i))
#define PPC_RAW_AND_DOT(d, a, b)	(PPC_INST_ANDDOT | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(b))
#define PPC_RAW_OR(d, a, b)		(PPC_INST_OR | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(b))
#define PPC_RAW_MR(d, a)		PPC_RAW_OR(d, a, a)
#define PPC_RAW_ORI(d, a, i)		(PPC_INST_ORI | ___PPC_RA(d) | ___PPC_RS(a) | IMM_L(i))
#define PPC_RAW_ORIS(d, a, i)		(PPC_INST_ORIS | ___PPC_RA(d) | ___PPC_RS(a) | IMM_L(i))
#define PPC_RAW_XOR(d, a, b)		(PPC_INST_XOR | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(b))
#define PPC_RAW_XORI(d, a, i)		(PPC_INST_XORI | ___PPC_RA(d) | ___PPC_RS(a) | IMM_L(i))
#define PPC_RAW_XORIS(d, a, i)		(PPC_INST_XORIS | ___PPC_RA(d) | ___PPC_RS(a) | IMM_L(i))
#define PPC_RAW_EXTSW(d, a)		(PPC_INST_EXTSW | ___PPC_RA(d) | ___PPC_RS(a))
#define PPC_RAW_SLW(d, a, s)		(PPC_INST_SLW | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(s))
#define PPC_RAW_SLD(d, a, s)		(PPC_INST_SLD | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(s))
#define PPC_RAW_SRW(d, a, s)		(PPC_INST_SRW | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(s))
#define PPC_RAW_SRAW(d, a, s)		(PPC_INST_SRAW | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(s))
#define PPC_RAW_SRAWI(d, a, i)		(PPC_INST_SRAWI | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH(i))
#define PPC_RAW_SRD(d, a, s)		(PPC_INST_SRD | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(s))
#define PPC_RAW_SRAD(d, a, s)		(PPC_INST_SRAD | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(s))
#define PPC_RAW_SRADI(d, a, i)		(PPC_INST_SRADI | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH64(i))
#define PPC_RAW_RLWINM(d, a, i, mb, me)	\
	(PPC_INST_RLWINM | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH(i) | __PPC_MB(mb) | __PPC_ME(me))
#define PPC_RAW_RLWINM_DOT(d, a, i, mb, me) \
	(PPC_INST_RLWINM_DOT | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH(i) | __PPC_MB(mb) | __PPC_ME(me))
#define PPC_RAW_RLWIMI(d, a, i, mb, me) \
	(PPC_INST_RLWIMI | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH(i) | __PPC_MB(mb) | __PPC_ME(me))
#define PPC_RAW_RLDICL(d, a, i, mb)     (PPC_INST_RLDICL | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH64(i) | __PPC_MB64(mb))
#define PPC_RAW_RLDICR(d, a, i, me)     (PPC_INST_RLDICR | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH64(i) | __PPC_ME64(me))

/* slwi = rlwinm Rx, Ry, n, 0, 31-n */
#define PPC_RAW_SLWI(d, a, i)		PPC_RAW_RLWINM(d, a, i, 0, 31-(i))
/* srwi = rlwinm Rx, Ry, 32-n, n, 31 */
#define PPC_RAW_SRWI(d, a, i)		PPC_RAW_RLWINM(d, a, 32-(i), i, 31)
/* sldi = rldicr Rx, Ry, n, 63-n */
#define PPC_RAW_SLDI(d, a, i)		PPC_RAW_RLDICR(d, a, i, 63-(i))
/* sldi = rldicl Rx, Ry, 64-n, n */
#define PPC_RAW_SRDI(d, a, i)		PPC_RAW_RLDICL(d, a, 64-(i), i)

#define PPC_RAW_NEG(d, a)		(PPC_INST_NEG | ___PPC_RT(d) | ___PPC_RA(a))

/* Deal with instructions that older assemblers aren't aware of */
#define	PPC_BCCTR_FLUSH		stringify_in_c(.long PPC_INST_BCCTR_FLUSH)
#define	PPC_CP_ABORT		stringify_in_c(.long PPC_INST_CP_ABORT)
#define	PPC_COPY(a, b)		stringify_in_c(.long PPC_INST_COPY | \
					___PPC_RA(a) | ___PPC_RB(b))
#define PPC_DARN(t, l)		stringify_in_c(.long PPC_INST_DARN |  \
						___PPC_RT(t)	   |  \
						(((l) & 0x3) << 16))
#define	PPC_DCBAL(a, b)		stringify_in_c(.long PPC_INST_DCBAL | \
					__PPC_RA(a) | __PPC_RB(b))
#define	PPC_DCBZL(a, b)		stringify_in_c(.long PPC_INST_DCBZL | \
					__PPC_RA(a) | __PPC_RB(b))
#define PPC_LQARX(t, a, b, eh)	stringify_in_c(.long PPC_INST_LQARX | \
					___PPC_RT(t) | ___PPC_RA(a) | \
					___PPC_RB(b) | __PPC_EH(eh))
#define PPC_LDARX(t, a, b, eh)	stringify_in_c(.long PPC_INST_LDARX | \
					___PPC_RT(t) | ___PPC_RA(a) | \
					___PPC_RB(b) | __PPC_EH(eh))
#define PPC_LWARX(t, a, b, eh)	stringify_in_c(.long PPC_INST_LWARX | \
					___PPC_RT(t) | ___PPC_RA(a) | \
					___PPC_RB(b) | __PPC_EH(eh))
#define PPC_STQCX(t, a, b)	stringify_in_c(.long PPC_INST_STQCX | \
					___PPC_RT(t) | ___PPC_RA(a) | \
					___PPC_RB(b))
#define PPC_MADDHD(t, a, b, c)	stringify_in_c(.long PPC_INST_MADDHD | \
					___PPC_RT(t) | ___PPC_RA(a)  | \
					___PPC_RB(b) | ___PPC_RC(c))
#define PPC_MADDHDU(t, a, b, c)	stringify_in_c(.long PPC_INST_MADDHDU | \
					___PPC_RT(t) | ___PPC_RA(a)   | \
					___PPC_RB(b) | ___PPC_RC(c))
#define PPC_MADDLD(t, a, b, c)	stringify_in_c(.long PPC_INST_MADDLD | \
					___PPC_RT(t) | ___PPC_RA(a)  | \
					___PPC_RB(b) | ___PPC_RC(c))
#define PPC_MSGSND(b)		stringify_in_c(.long PPC_INST_MSGSND | \
					___PPC_RB(b))
#define PPC_MSGSYNC		stringify_in_c(.long PPC_INST_MSGSYNC)
#define PPC_MSGCLR(b)		stringify_in_c(.long PPC_INST_MSGCLR | \
					___PPC_RB(b))
#define PPC_MSGSNDP(b)		stringify_in_c(.long PPC_INST_MSGSNDP | \
					___PPC_RB(b))
#define PPC_MSGCLRP(b)		stringify_in_c(.long PPC_INST_MSGCLRP | \
					___PPC_RB(b))
#define PPC_PASTE(a, b)		stringify_in_c(.long PPC_INST_PASTE | \
					___PPC_RA(a) | ___PPC_RB(b))
#define PPC_POPCNTB(a, s)	stringify_in_c(.long PPC_INST_POPCNTB | \
					__PPC_RA(a) | __PPC_RS(s))
#define PPC_POPCNTD(a, s)	stringify_in_c(.long PPC_INST_POPCNTD | \
					__PPC_RA(a) | __PPC_RS(s))
#define PPC_POPCNTW(a, s)	stringify_in_c(.long PPC_INST_POPCNTW | \
					__PPC_RA(a) | __PPC_RS(s))
#define PPC_RFCI		stringify_in_c(.long PPC_INST_RFCI)
#define PPC_RFDI		stringify_in_c(.long PPC_INST_RFDI)
#define PPC_RFMCI		stringify_in_c(.long PPC_INST_RFMCI)
#define PPC_TLBILX(t, a, b)	stringify_in_c(.long PPC_INST_TLBILX | \
					__PPC_T_TLB(t) | __PPC_RA0(a) | __PPC_RB(b))
#define PPC_TLBILX_ALL(a, b)	PPC_TLBILX(0, a, b)
#define PPC_TLBILX_PID(a, b)	PPC_TLBILX(1, a, b)
#define PPC_TLBILX_VA(a, b)	PPC_TLBILX(3, a, b)
#define PPC_WAIT(w)		stringify_in_c(.long PPC_INST_WAIT | \
					__PPC_WC(w))
#define PPC_TLBIE(lp,a) 	stringify_in_c(.long PPC_INST_TLBIE | \
					       ___PPC_RB(a) | ___PPC_RS(lp))
#define	PPC_TLBIE_5(rb,rs,ric,prs,r) \
				stringify_in_c(.long PPC_INST_TLBIE | \
					___PPC_RB(rb) | ___PPC_RS(rs) | \
					___PPC_RIC(ric) | ___PPC_PRS(prs) | \
					___PPC_R(r))
#define	PPC_TLBIEL(rb,rs,ric,prs,r) \
				stringify_in_c(.long PPC_INST_TLBIEL | \
					___PPC_RB(rb) | ___PPC_RS(rs) | \
					___PPC_RIC(ric) | ___PPC_PRS(prs) | \
					___PPC_R(r))
#define PPC_TLBSRX_DOT(a,b)	stringify_in_c(.long PPC_INST_TLBSRX_DOT | \
					__PPC_RA0(a) | __PPC_RB(b))
#define PPC_TLBIVAX(a,b)	stringify_in_c(.long PPC_INST_TLBIVAX | \
					__PPC_RA0(a) | __PPC_RB(b))

#define PPC_ERATWE(s, a, w)	stringify_in_c(.long PPC_INST_ERATWE | \
					__PPC_RS(s) | __PPC_RA(a) | __PPC_WS(w))
#define PPC_ERATRE(s, a, w)	stringify_in_c(.long PPC_INST_ERATRE | \
					__PPC_RS(s) | __PPC_RA(a) | __PPC_WS(w))
#define PPC_ERATILX(t, a, b)	stringify_in_c(.long PPC_INST_ERATILX | \
					__PPC_T_TLB(t) | __PPC_RA0(a) | \
					__PPC_RB(b))
#define PPC_ERATIVAX(s, a, b)	stringify_in_c(.long PPC_INST_ERATIVAX | \
					__PPC_RS(s) | __PPC_RA0(a) | __PPC_RB(b))
#define PPC_ERATSX(t, a, w)	stringify_in_c(.long PPC_INST_ERATSX | \
					__PPC_RS(t) | __PPC_RA0(a) | __PPC_RB(b))
#define PPC_ERATSX_DOT(t, a, w)	stringify_in_c(.long PPC_INST_ERATSX_DOT | \
					__PPC_RS(t) | __PPC_RA0(a) | __PPC_RB(b))
#define PPC_SLBFEE_DOT(t, b)	stringify_in_c(.long PPC_INST_SLBFEE | \
					__PPC_RT(t) | __PPC_RB(b))
#define PPC_ICBT(c,a,b)		stringify_in_c(.long PPC_INST_ICBT | \
				       __PPC_CT(c) | __PPC_RA0(a) | __PPC_RB(b))
/* PASemi instructions */
#define LBZCIX(t,a,b)		stringify_in_c(.long PPC_INST_LBZCIX | \
				       __PPC_RT(t) | __PPC_RA(a) | __PPC_RB(b))
#define STBCIX(s,a,b)		stringify_in_c(.long PPC_INST_STBCIX | \
				       __PPC_RS(s) | __PPC_RA(a) | __PPC_RB(b))

#define	PPC_DCBFPS(a, b)	stringify_in_c(.long PPC_INST_DCBF |	\
				       ___PPC_RA(a) | ___PPC_RB(b) | (4 << 21))
#define	PPC_DCBSTPS(a, b)	stringify_in_c(.long PPC_INST_DCBF |	\
				       ___PPC_RA(a) | ___PPC_RB(b) | (6 << 21))

#define	PPC_PHWSYNC		stringify_in_c(.long PPC_INST_PHWSYNC)
#define	PPC_PLWSYNC		stringify_in_c(.long PPC_INST_PLWSYNC)

#define STXVD2X(s, a, b)	stringify_in_c(.long PPC_INST_STXVD2X | \
					       VSX_XX1((s), a, b))
#define LXVD2X(s, a, b)		stringify_in_c(.long PPC_INST_LXVD2X | \
					       VSX_XX1((s), a, b))
#define MFVRD(a, t)		stringify_in_c(.long PPC_INST_MFVSRD | \
					       VSX_XX1((t)+32, a, R0))
#define MTVRD(t, a)		stringify_in_c(.long PPC_INST_MTVSRD | \
					       VSX_XX1((t)+32, a, R0))
#define VPMSUMW(t, a, b)	stringify_in_c(.long PPC_INST_VPMSUMW | \
					       VSX_XX3((t), a, b))
#define VPMSUMD(t, a, b)	stringify_in_c(.long PPC_INST_VPMSUMD | \
					       VSX_XX3((t), a, b))
#define XXLOR(t, a, b)		stringify_in_c(.long PPC_INST_XXLOR | \
					       VSX_XX3((t), a, b))
#define XXSWAPD(t, a)		stringify_in_c(.long PPC_INST_XXSWAPD | \
					       VSX_XX3((t), a, a))
#define XVCPSGNDP(t, a, b)	stringify_in_c(.long (PPC_INST_XVCPSGNDP | \
					       VSX_XX3((t), (a), (b))))

#define VPERMXOR(vrt, vra, vrb, vrc)				\
	stringify_in_c(.long (PPC_INST_VPERMXOR |		\
			      ___PPC_RT(vrt) | ___PPC_RA(vra) | \
			      ___PPC_RB(vrb) | (((vrc) & 0x1f) << 6)))

#define PPC_NAP			stringify_in_c(.long PPC_INST_NAP)
#define PPC_SLEEP		stringify_in_c(.long PPC_INST_SLEEP)
#define PPC_WINKLE		stringify_in_c(.long PPC_INST_WINKLE)

#define PPC_STOP		stringify_in_c(.long PPC_INST_STOP)

/* BHRB instructions */
#define PPC_CLRBHRB		stringify_in_c(.long PPC_INST_CLRBHRB)
#define PPC_MFBHRBE(r, n)	stringify_in_c(.long PPC_INST_BHRBE | \
						__PPC_RT(r) | \
							(((n) & 0x3ff) << 11))

/* Transactional memory instructions */
#define TRECHKPT		stringify_in_c(.long PPC_INST_TRECHKPT)
#define TRECLAIM(r)		stringify_in_c(.long PPC_INST_TRECLAIM \
					       | __PPC_RA(r))
#define TABORT(r)		stringify_in_c(.long PPC_INST_TABORT \
					       | __PPC_RA(r))

/* book3e thread control instructions */
#define MTTMR(tmr, r)		stringify_in_c(.long PPC_INST_MTTMR | \
					       TMRN(tmr) | ___PPC_RS(r))
#define MFTMR(tmr, r)		stringify_in_c(.long PPC_INST_MFTMR | \
					       TMRN(tmr) | ___PPC_RT(r))

/* Coprocessor instructions */
#define PPC_ICSWX(s, a, b)	stringify_in_c(.long PPC_INST_ICSWX |	\
					       ___PPC_RS(s) |		\
					       ___PPC_RA(a) |		\
					       ___PPC_RB(b))
#define PPC_ICSWEPX(s, a, b)	stringify_in_c(.long PPC_INST_ICSWEPX | \
					       ___PPC_RS(s) |		\
					       ___PPC_RA(a) |		\
					       ___PPC_RB(b))

#define PPC_SLBIA(IH)	stringify_in_c(.long PPC_INST_SLBIA | \
				       ((IH & 0x7) << 21))
#define PPC_INVALIDATE_ERAT	PPC_SLBIA(7)

#endif /* _ASM_POWERPC_PPC_OPCODE_H */
