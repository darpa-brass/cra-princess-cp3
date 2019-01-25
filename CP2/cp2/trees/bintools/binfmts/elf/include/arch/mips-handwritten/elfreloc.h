/*
 * Copyright (c) 2002, 2016
 *	The President and Fellows of Harvard College.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef ELF_MIPS_RELOC_H
#define ELF_MIPS_RELOC_H

/* MIPS relocation types (all rel, not rela) */
#define R_MIPS_NONE	0	/* nothing */
#define R_MIPS_16	1	/* u16 += sym */
#define R_MIPS_32	2	/* u32 += sym */
#define R_MIPS_REL32	3	/* u32 += sym - . */
#define R_MIPS_26	4	/* u26 += sym % 2^26 (jmp insn) */
#define R_MIPS_HI16	5	/* u16 = %hi(sym) */
#define R_MIPS_LO16	6	/* u16 = %lo(sym) */
#define R_MIPS_GPREL16	7	/* u16 = sym - _GP */
#define R_MIPS_LITERAL	8	/* ? */
#define R_MIPS_GOT16	9	/* u16 = GOT_ENTRY(sym) */
#define R_MIPS_PC16	10	/* u16 = sym - . */
#define R_MIPS_CALL16	11	/* u16 = GOT_ENTRY(sym) (???) */
#define R_MIPS_GPREL32	12	/* u32 = ? */

/* 64-bit */
#define R_MIPS_64		16
#define R_MIPS_SHIFT5		17
#define R_MIPS_SHIFT6		18
#define R_MIPS_GOT_DISP		19
#define R_MIPS_GOT_PAGE		20
#define R_MIPS_GOT_OFST		21
#define R_MIPS_GOT_HI16		22
#define R_MIPS_GOT_LO16		23
#define R_MIPS_SUB		24
#define R_MIPS_INSERT_A		25
#define R_MIPS_INSERT_B		26
#define R_MIPS_DELETE		27
#define R_MIPS_HIGHER		28
#define R_MIPS_HIGHEST		29
#define R_MIPS_CALL_HI16	30
#define R_MIPS_CALL_LO16	31
#define R_MIPS_SCN_DISP		32
#define R_MIPS_REL16		33
#define R_MIPS_ADD_IMMEDIATE	34
#define R_MIPS_PJUMP		35
#define R_MIPS_ADD_RELGOT	36
#define R_MIPS_JALR		37

/* TLS */
#define R_MIPS_TLS_DTPMOD32	38
#define R_MIPS_TLS_DTPREL32	39
#define R_MIPS_TLS_DTPMOD64	40
#define R_MIPS_TLS_DTPREL64	41
#define R_MIPS_TLS_GD		42
#define R_MIPS_TLS_LDM		43
#define R_MIPS_TLS_DTPREL_HI16	44
#define R_MIPS_TLS_DTPREL_LO16	45
#define R_MIPS_TLS_GOTTPREL	46
#define R_MIPS_TLS_TPREL32	47
#define R_MIPS_TLS_TPREL64	48
#define R_MIPS_TLS_TPREL_HI16	59
#define R_MIPS_TLS_TPREL_LO16	50

/* mips16 */
#define R_MIPS16_26		100
#define R_MIPS16_GPREL		101
#define R_MIPS16_GOT16		102
#define R_MIPS16_CALL16		103
#define R_MIPS16_HI16		104
#define R_MIPS16_LO16		105

/* ? */
#define R_MIPS16_COPY		126
#define R_MIPS16_JUMP_SLOT	127

#endif /* ELF_MIPS_RELOC_H */
