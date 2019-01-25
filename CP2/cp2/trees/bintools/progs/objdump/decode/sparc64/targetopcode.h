/*
 * Copyright (c) 2002, 2016
 *	The President and Fellows of Harvard College.
 *
 * Written by David A. Holland.
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

#ifndef MIPS_TOPCODE_H
#define MIPS_TOPCODE_H

/*
 * Instruction name to opcode number mapping.
 */

/* main opcodes */
#define OPC_SPECIAL		0
#define OPC_BCOND		1
#define OPC_J			2
#define OPC_JAL			3
#define OPC_BEQ			4
#define OPC_BNE			5
#define OPC_BLEZ		6
#define OPC_BGTZ		7
#define OPC_ADDI		8
#define OPC_ADDIU		9
#define OPC_SLTI		10
#define OPC_SLTIU		11
#define OPC_ANDI		12
#define OPC_ORI			13
#define OPC_XORI		14
#define OPC_LUI			15
#define OPC_COP0		16
#define OPC_COP1		17
#define OPC_COP2		18
#define OPC_COP3		19
#define OPC_BEQL		20
#define OPC_BNEL		21
#define OPC_BLEZL		22
#define OPC_BGTZL		23
#define OPC_SPECIAL2		28
#define OPC_LB			32
#define OPC_LH			33
#define OPC_LWL			34
#define OPC_LW			35
#define OPC_LBU			36
#define OPC_LHU			37
#define OPC_LWR			38
#define OPC_SB			40
#define OPC_SH			41
#define OPC_SWL			42
#define OPC_SW			43
#define OPC_SWR			46
#define OPC_CACHE		47
#define OPC_LWC0		48
#define OPC_LWC1		49
#define OPC_LWC2		50
#define OPC_LWC3		51
#define OPC_LDC0		52
#define OPC_LDC1		53
#define OPC_LDC2		54
#define OPC_LDC3		55
#define OPC_SWC0		56
#define OPC_SWC1		57
#define OPC_SWC2		58
#define OPC_SWC3		59
#define OPC_SDC0		60
#define OPC_SDC1		61
#define OPC_SDC2		62
#define OPC_SDC3		63

/* sub-opcodes for OPC_SPECIAL (field 6) */
#define SPEC_SLL		0
#define SPEC_MOVC		1	/* move if floating point condition */
#define SPEC_SRL		2
#define SPEC_SRA		3
#define SPEC_SLLV		4
#define SPEC_SRLV		6
#define SPEC_SRAV		7
#define SPEC_JR			8
#define SPEC_JALR		9
#define SPEC_MOVZ		10
#define SPEC_MOVN		11
#define SPEC_SYSCALL		12
#define SPEC_BREAK		13
#define SPEC_SYNC		15
#define SPEC_MFHI		16
#define SPEC_MTHI		17
#define SPEC_MFLO		18
#define SPEC_MTLO		19
#define SPEC_MULT		24
#define SPEC_MULTU		25
#define SPEC_DIV		26
#define SPEC_DIVU		27
#define SPEC_ADD		32
#define SPEC_ADDU		33
#define SPEC_SUB		34
#define SPEC_SUBU		35
#define SPEC_AND		36
#define SPEC_OR			37
#define SPEC_XOR		38
#define SPEC_NOR		39
#define SPEC_SLT		42
#define SPEC_SLTU		43
#define SPEC_TGE		48
#define SPEC_TGEU		49
#define SPEC_TLT		50
#define SPEC_TLTU		51
#define SPEC_TEQ		52
#define SPEC_TNE		54

/* sub-opcodes for OPC_SPECIAL2 (field 6) */
#define SPEC2_MADD		0
#define SPEC2_MADDU		1
#define SPEC2_MUL		2
#define SPEC2_MSUB		4
#define SPEC2_MSUBU		5
#define SPEC2_CLZ		32
#define SPEC2_CLO		33
#define SPEC2_SDBBP		63

/* sub-opcodes for OPC_BCOND (field 6) */
#define BCOND_BLTZ		0
#define BCOND_BGEZ		1
#define BCOND_BLTZL		2
#define BCOND_BGEZL		3
#define BCOND_TGEI		8
#define BCOND_TGEIU		9
#define BCOND_TLTI		10
#define BCOND_TLTIU		11
#define BCOND_TEQI		12
#define BCOND_TNEI		14
#define BCOND_BLTZAL		16
#define BCOND_BGEZAL		17
#define BCOND_BLTZALL		18
#define BCOND_BGEZALL		19

/* coprocessor codes for OPC_COP[0-3] (field 2) */
#define COP_MF			0	/* move from coprocessor */
#define COP_CF			2	/* control word from coprocessor */
#define COP_MT			4	/* move to coprocessor */
#define COP_CT			6	/* control word to coprocessor */
#define COP_BC			8	/* branch on coprocessor condition */

/* supervisor opcodes for OPC_COP0 (field 6) with bit 4 of field 2 set */
#define COP0_TLBR		1
#define COP0_TLBWI		2
#define COP0_TLBWR		6
#define COP0_TLBP		8
#define COP0_RFE		16	/* mipsI only */
#define COP0_ERET		24
#define COP0_DERET		31
#define COP0_WAIT		32

/* coprocessor 1 (fpu) codes for OPC_COP1 (field 2) */
#define COP1_FLOATFMT_S		16
#define COP1_FLOATFMT_D		17
#define COP1_FLOATFMT_W		20
#define COP1_FLOATFMT_L		21
#define COP1_FLOATFMT_F		22	/* XXX: ? */

/* floating point opcodes for OPC_COP1 (field 6) */
#define COP1_ADD		0
#define COP1_SUB		1
#define COP1_MUL		2
#define COP1_DIV		3
#define COP1_SQRT		4
#define COP1_ABS		5
#define COP1_MOV		6
#define COP1_NEG		7
#define COP1_ROUND		12
#define COP1_TRUNC		13
#define COP1_CEIL		14
#define COP1_FLOOR		15
#define COP1_MOVC		17	/* move if condition code */
#define COP1_MOVZ		18	/* move if general reg zero */
#define COP1_MOVN		19	/* move if general reg nonzero */
#define COP1_CVT_S		32
#define COP1_CVT_D		33
#define COP1_CVT_W		36
/*	COP1_C.cond		48-63 */

#endif /* MIPS_TOPCODE_H */
