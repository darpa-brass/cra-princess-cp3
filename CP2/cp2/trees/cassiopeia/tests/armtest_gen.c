/*
 * armtest_gen.c
 *
 *  Created on: Mar 16, 2018
 *      Author: abby
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
	// caller should have set s and instr_asm
	if (instr_asm->type == ADD) {
		// set up cassiopeia instruction
		sprintf(instr_casp, "(ADD R%d R%d 0x%08x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		// print the test that's being run
		fprintf(stderr, "ADD r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	} else if (instr_asm->type == LSL) {
		sprintf(instr_casp, "(LSL R%d R%d 0x%08x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		fprintf(stderr, "LSL r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	} else if (instr_asm->type == LSR) {
		sprintf(instr_casp, "(LSR R%d R%d 0x%08x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		fprintf(stderr, "LSR r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	} else if (instr_asm->type == AND) {
		sprintf(instr_casp, "(AND R%d R%d 0x%08x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		fprintf(stderr, "AND r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	} else if (instr_asm->type == LDR) {
		sprintf(instr_casp, "(LDR R%d R%d 0x%08x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		fprintf(stderr, "LDR r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	} else {
		sprintf(instr_casp, "(STR R%d R%d 0x%08x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		fprintf(stderr, "STR r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	}
}

void generate_test_random(
	state_ptr s, instr_ptr instr_asm, char *instr_casp) {
	// generate a random instruction
	memset(instr_casp, 0, MAX_INSTR_LEN);
	generate_state_random(s, instr_asm);
	int instr_num = rand() % NUM_INSTRS;
	s->cpsr = 0;

	if (instr_num == 0) {
		// set up assembly instruction
		instr_asm->type = ADD;
		// set up cassiopeia instruction
		sprintf(instr_casp, "(ADD R%d R%d 0x%08x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		// print the test that's being run
		fprintf(stderr, "ADD r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	} else if (instr_num == 1) {
		instr_asm->type = LSL;
		instr_asm->imm %= 32;
		sprintf(instr_casp, "(LSL R%d R%d 0x%08x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		fprintf(stderr, "LSL r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	} else if (instr_num == 2) {
		instr_asm->type = LSR;
		instr_asm->imm = (instr_asm->imm % 32) + 1;
		sprintf(instr_casp, "(LSR R%d R%d 0x%08x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		fprintf(stderr, "LSR r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	} else if (instr_num == 3) {
		instr_asm->type = AND;
		sprintf(instr_casp, "(AND R%d R%d 0x%08x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		fprintf(stderr, "AND r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	} else if (instr_num == 4) {
		instr_asm->type = LDR;
		int offset = rand() % MEM_SIZE;
		s->regs[instr_asm->src] = (uint32_t)(s->mem + offset);
		instr_asm->imm %= (MEM_SIZE - offset);
		sprintf(instr_casp, "(LDR R%d R%d 0x%08x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		fprintf(stderr, "LDR r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	} else {
		instr_asm->type = STR;
		int offset = rand() % MEM_SIZE;
		s->regs[instr_asm->src] = (uint32_t)(s->mem + offset);
		instr_asm->imm %= (MEM_SIZE - offset);
		sprintf(instr_casp, "(STR R%d R%d 0x%08x)\n",
			instr_asm->dest, instr_asm->src, instr_asm->imm);
		fprintf(stderr, "STR r%d=%x r%d=%x %x\n",
			instr_asm->dest, s->regs[instr_asm->dest],
			instr_asm->src, s->regs[instr_asm->src], instr_asm->imm);
	}
}
