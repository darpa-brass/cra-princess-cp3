/*
 * armtest.c
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
#include <time.h>

int main(void)
{
	srand(time(NULL));
	remove("test.prog");
	remove("out.txt");
	if (!run_tests()) {
		fprintf(stderr, "All states passed!\n");
	}
	return 0;
}

int run_tests() {
	int failed = 0;
	struct state s_real;
	struct state s_exp;
	init_state(&s_real);
	init_state(&s_exp);
	struct instr instr_asm;
	char instr_casp[MAX_INSTR_LEN];
	memset(instr_casp, 0, MAX_INSTR_LEN);
	int test = 0;

	// this struct stores the temporary sp and lr
	struct splr_state splr;

	start_reg_state(&s_real);

	// (STR_imm R3 R0 0x000)
	instr_asm.type = STR_imm;
	generate_instr(&s_real, &instr_asm, 3, 0, 0, 0);
	generate_test(&s_real, &instr_asm, instr_casp);
	memcpy(&s_exp, &s_real, sizeof(struct state));
	if (run_and_cmp(&s_real, &instr_asm, &s_exp, &splr, instr_casp, 1))  failed = 1;
	if (++test == NUM_TESTS)  return failed;

	// (STR_imm R14 R0 0x040)
	instr_asm.type = STR_imm;
	generate_instr(&s_real, &instr_asm, 14, 0, 64, 0);
	generate_test(&s_real, &instr_asm, instr_casp);
	memcpy(&s_exp, &s_real, sizeof(struct state));
	if (run_and_cmp(&s_real, &instr_asm, &s_exp, &splr, instr_casp, 2))  failed = 1;
	if (++test == NUM_TESTS)  return failed;

	// (ADD_imm R3 R0 0x014)
	instr_asm.type = ADD_imm;
	generate_instr(&s_real, &instr_asm, 3, 0, 20, 0);
	generate_test(&s_real, &instr_asm, instr_casp);
	memcpy(&s_exp, &s_real, sizeof(struct state));
	if (run_and_cmp(&s_real, &instr_asm, &s_exp, &splr, instr_casp, 3))  failed = 1;
	if (++test == NUM_TESTS)  return failed;

	// (STMIA_wtback_usr R3 11 0x00f0)
	instr_asm.type = STMIA_wtback_usr;
	generate_instr(&s_real, &instr_asm, 3, 0, 240, 4);
	generate_test(&s_real, &instr_asm, instr_casp);
	memcpy(&s_exp, &s_real, sizeof(struct state));
	if (run_and_cmp(&s_real, &instr_asm, &s_exp, &splr, instr_casp, 4))  failed = 1;
	if (++test == NUM_TESTS)  return failed;

	// (ADD_imm R3 R3 0x008)
	instr_asm.type = ADD_imm;
	generate_instr(&s_real, &instr_asm, 3, 3, 8, 0);
	generate_test(&s_real, &instr_asm, instr_casp);
	memcpy(&s_exp, &s_real, sizeof(struct state));
	if (run_and_cmp(&s_real, &instr_asm, &s_exp, &splr, instr_casp, 5))  failed = 1;
	if (++test == NUM_TESTS)  return failed;

	// // (VSTMIA_wtback_64 R3 16 0x0000ffff)
	// // (VSTMIA_wtback_64 R3 16 0xffff0000)

	// (ADD_imm R3 R0 0x010)
	instr_asm.type = ADD_imm;
	generate_instr(&s_real, &instr_asm, 3, 0, 16, 0);
	generate_test(&s_real, &instr_asm, instr_casp);
	memcpy(&s_exp, &s_real, sizeof(struct state));
	if (run_and_cmp(&s_real, &instr_asm, &s_exp, &splr, instr_casp, 6))  failed = 1;
	if (++test == NUM_TESTS)  return failed;

	// (POP 0x30)
	instr_asm.type = POP;
	generate_instr(&s_real, &instr_asm, 0, 0, 48, 0);
	generate_test(&s_real, &instr_asm, instr_casp);
	memcpy(&s_exp, &s_real, sizeof(struct state));
	if (run_and_cmp(&s_real, &instr_asm, &s_exp, &splr, instr_casp, 7))  failed = 1;
	if (++test == NUM_TESTS)  return failed;

	// (STMDA_wtback R3 4 0x0030)
	instr_asm.type = STMDA_wtback;
	generate_instr(&s_real, &instr_asm, 3, 0, 48, 2);
	generate_test(&s_real, &instr_asm, instr_casp);
	memcpy(&s_exp, &s_real, sizeof(struct state));
	if (run_and_cmp(&s_real, &instr_asm, &s_exp, &splr, instr_casp, 8))  failed = 1;
	if (++test == NUM_TESTS)  return failed;

	//final state
	return failed;
}

void run_casp(state_ptr s, splr_state_ptr splr, const char *instr) {
	// write test.prog for the interpreter
	// completing test.prog tells armtest_casp to run
	FILE *casp_input = fopen("test.prog", "w");
	assert(casp_input);
	char buffer[MAX_INSTR_LEN];
	for (int i = 0; i < 6; ++i) {
		if (s->regs[i] == 0) {
			continue;
		}
		memset(buffer, 0, MAX_INSTR_LEN);
		sprintf(buffer, "(SETREG R%d 0x%08x)\n", i, s->regs[i]);
		fputs(buffer, casp_input);
	}
	memset(buffer, 0, MAX_INSTR_LEN);
	sprintf(buffer, "(SETREG R%d 0x%08x)\n", 13, splr->sp_pre);
	fputs(buffer, casp_input);
	memset(buffer, 0, MAX_INSTR_LEN);
	sprintf(buffer, "(SETREG R%d 0x%08x)\n", 14, splr->lr_pre);
	fputs(buffer, casp_input);


	memset(buffer, 0, MAX_INSTR_LEN);
	sprintf(buffer, "(SETBIT N 0x%x)\n", s->cpsr >> 31);
	fputs(buffer, casp_input);
	memset(buffer, 0, MAX_INSTR_LEN);
	sprintf(buffer, "(SETBIT Z 0x%x)\n", (s->cpsr >> 30) & 1);
	fputs(buffer, casp_input);
	memset(buffer, 0, MAX_INSTR_LEN);
	sprintf(buffer, "(SETBIT C 0x%x)\n", (s->cpsr >> 29) & 1);
	fputs(buffer, casp_input);
	memset(buffer, 0, MAX_INSTR_LEN);
	sprintf(buffer, "(SETBIT V 0x%x)\n", (s->cpsr >> 28) & 1);
	fputs(buffer, casp_input);

	fputs(instr, casp_input);

	fclose(casp_input);

	system("./cassiopeia arm-swi.casp -interp test.prog > out.txt\n");
	//remove("test.prog");

	// parse the output file
	FILE *casp_output = fopen("out.txt", "r");
	assert(casp_output);

	memset(buffer, MAX_INSTR_LEN, 0);
	// skip over irrelevant stuff
	while (buffer[0] != 'C') {
		fgets(buffer, MAX_INSTR_LEN, casp_output);
	}
	// get C
	char *c = strchr(buffer, ':');
	++c;
	char *c_end = strchr(c, ',');
	*c_end = '\0';
	uint32_t res = strtoul(c, NULL, 16);
	if (res) {
		s->cpsr |= 1 << 29;
	}
	// get M
	// fgets(buffer, MAX_INSTR_LEN, casp_output);
	// c = strchr(buffer, ':');
	// ++c;
	// c_end = strchr(c, ',');
	// *c_end = '\0';
	// res = strtoul(c, NULL, 16);
	// s->mem[0] = res;

	// get N
	while (buffer[0] != 'N') {
		fgets(buffer, MAX_INSTR_LEN, casp_output);
	}
	c = strchr(buffer, ':');
	++c;
	c_end = strchr(c, ',');
	*c_end = '\0';
	res = strtoul(c, NULL, 16);
	if (res) {
		s->cpsr |= 1 << 31;
	}
	// ger rid of Q
	fgets(buffer, MAX_INSTR_LEN, casp_output);
	// get registers
	for (int i = 0; i < NUM_REGS; ++i) {
		fgets(buffer, MAX_INSTR_LEN, casp_output);
		c = strchr(buffer, ':');
		++c;
		c_end = strchr(c, ',');
		*c_end = '\0';
		res = strtoul(c, NULL, 16);
		if (i == 0) s->regs[0] = res;
		if (i == 1) s->regs[1] = res;
		if (i == 2) s->regs[6] = res;
		if (i == 3) s->regs[7] = res;
		if (i == 4) s->regs[2] = res;
		if (i == 5) s->regs[3] = res;
		if (i == 6) s->regs[4] = res;
		if (i == 7) s->regs[5] = res;
	}
	// get V
	fgets(buffer, MAX_INSTR_LEN, casp_output);
	c = strchr(buffer, ':');
	++c;
	c_end = strchr(c, ',');
	*c_end = '\0';
	res = strtoul(c, NULL, 16);
	if (res) {
		s->cpsr |= 1 << 28;
	}
	// get Z
	fgets(buffer, MAX_INSTR_LEN, casp_output);
	c = strchr(buffer, ':');
	++c;
	c_end = strchr(c, ',');
	*c_end = '\0';
	res = strtoul(c, NULL, 16);
	if (res) {
		s->cpsr |= 1 << 30;
	}
	fclose(casp_output);
	//remove("out.txt");
}

/********** machine independent stuff below **********/

void init_state(state_ptr s) {
	memset(s, 0, sizeof(struct state));
}

void start_reg_state(state_ptr s){
	// we don't set cpsr
	for (int i = 0; i < 6; i ++){
		s->regs[i] = i * 4;
	}
}

void generate_instr(state_ptr s, instr_ptr instr_asm, uint32_t dest, uint32_t src, uint32_t imm, uint32_t num) {
	instr_asm->dest = dest;
	instr_asm->src = src;
	instr_asm->imm = imm;
	instr_asm->num = num;
	//Does not set instruction type here

}

int run_and_cmp(state_ptr s_real, instr_ptr instr_asm,
	state_ptr s_exp, splr_state_ptr splr, const char *instr_casp, int num) {
	run_asm(s_real, splr, instr_asm, num);
	run_casp(s_exp, splr, instr_casp);
	return cmp_state(s_real, s_exp);
}

int cmp_state(const state_ptr s1, const state_ptr s2) {
	if (!memcmp(s1, s2, sizeof(struct state))) {
		fprintf(stderr, "\n");// print both states
		fprintf(stderr, "Actual   Expected\n");
		for (int i = 0; i < sizeof(struct state) / 4; ++i) {
			fprintf(stderr, "%08x %08x",
				((uint32_t*)s1)[i], ((uint32_t*)s2)[i]);
			if (((uint32_t*)s1)[i] != ((uint32_t*)s2)[i]) {
				fprintf(stderr, "  <----\n");
			} else {
				fprintf(stderr, "\n");
			}
		}
		fprintf(stderr, "\n");
		return 0;
	}

	// print both states
	fprintf(stderr, "Actual   Expected\n");
	for (int i = 0; i < sizeof(struct state) / 4; ++i) {
		fprintf(stderr, "%08x %08x",
			((uint32_t*)s1)[i], ((uint32_t*)s2)[i]);
		if (((uint32_t*)s1)[i] != ((uint32_t*)s2)[i]) {
			fprintf(stderr, "  <----\n");
		} else {
			fprintf(stderr, "\n");
		}
	}
	fprintf(stderr, "\n");
	return 1;
}
