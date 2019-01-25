/*
 * armtest_gen.c
 *
 *  Created on: Mar 16, 2018
 *      Author: abby
 *      
 *  Modified on: May 25, 2018
 *      Author: Crystal
 */

#include "armtest.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_test(const state_ptr s, const instr_ptr instr_asm, 
	char *instr_casp) {
	memset(instr_casp, 0, MAX_INSTR_LEN);
	s->cpsr = 0;

	// generate test, set s and instr_asm

	// caller should have set s and instr_asm
	if (instr_asm->type == ADD_imm) {
		// set up cassiopeia instruction
		sprintf(instr_casp, "(ADD_imm R%d R%d 0x%012x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		// print the test that's being run
		fprintf(stderr, "ADD_imm r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	} else if (instr_asm->type == STR_imm) {
		sprintf(instr_casp, "(STR_imm R%d R%d 0x%012x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		fprintf(stderr, "STR_imm r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	} else if (instr_asm->type == STMIA_wtback_usr) {
		sprintf(instr_casp, "(STMIA_wtback_usr R%d %d 0x%016x)\n",
			instr_asm->dest, instr_asm->num, instr_asm->imm);
		fprintf(stderr, "STMIA_wtback_usr r%d=%x num=%d %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->num, instr_asm->imm);
	} else if (instr_asm->type == STMDA_wtback) {
		sprintf(instr_casp, "(STMDA_wtback R%d %d 0x%016x)\n",
			instr_asm->dest, instr_asm->num, instr_asm->imm);
		fprintf(stderr, "STMDA_wtback r%d=%x num=%d %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->num, instr_asm->imm);
	} else if (instr_asm->type == POP) {
		sprintf(instr_casp, "(POP 0x%08x)\n",
			instr_asm->imm);
		fprintf(stderr, "POP %x\n",
			instr_asm->imm);
	}
}
