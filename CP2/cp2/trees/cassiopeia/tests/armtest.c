/*
 * armtest.c
 *
 *  Created on: Mar 16, 2018
 *      Author: abby
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
#ifdef RANDOM_SUITE
	if (!run_tests_random()) {
		fprintf(stderr, "All tests passed!\n");
	}
#else
	if (!run_tests_set()) {
		fprintf(stderr, "All tests passed!\n");
	}
#endif
	return 0;
}

int run_tests_set() {
	int failed = 0;
	struct state s_real;
	struct state s_exp;
	init_state(&s_real);
	init_state(&s_exp);
	struct instr instr_asm;
	char instr_casp[MAX_INSTR_LEN];
	memset(instr_casp, 0, MAX_INSTR_LEN);
	int test = 0;

	// generate ADD and AND tests
	instr_asm.type = ADD;
	for (int i = 0; i < 2; ++i) {
		// Test 1: imm = 0
		generate_state_random(&s_real, &instr_asm);
		instr_asm.imm = 0;
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;
		// Test 2: Rn = 0
		generate_state_random(&s_real, &instr_asm);
		s_real.regs[instr_asm.src] = 0;
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;
		// Test 3: imm and Rn = 0
		generate_state_random(&s_real, &instr_asm);
		instr_asm.imm = 0;
		s_real.regs[instr_asm.src] = 0;
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;
		// Test 4: high imm and high Rn
		generate_state_random(&s_real, &instr_asm);
		instr_asm.imm |= (1 << 31);
		s_real.regs[instr_asm.src] |= (1 << 31);
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;
		// Test 5: high imm and low Rn
		generate_state_random(&s_real, &instr_asm);
		instr_asm.imm |= (1 << 31);
		s_real.regs[instr_asm.src] &= ~(1 << 31);
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;
		// Test 6: low imm and high Rn
		generate_state_random(&s_real, &instr_asm);
		instr_asm.imm &= ~(1 << 31);
		s_real.regs[instr_asm.src] |= (1 << 31);
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;
		// Test 7: low imm and low Rn
		generate_state_random(&s_real, &instr_asm);
		instr_asm.imm &= ~(1 << 31);
		s_real.regs[instr_asm.src] &= ~(1 << 31);
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;

		instr_asm.type = AND;
	}

	// generate LSL and LSR tests
	instr_asm.type = LSL;
	for (int i = 0; i < 2; ++i) {
		// Test 1: 0 imm and high Rn
		generate_state_random(&s_real, &instr_asm);
		instr_asm.imm = 0;
		s_real.regs[instr_asm.src] |= (1 << 31);
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;
		// Test 2: 0 imm and low Rn
		generate_state_random(&s_real, &instr_asm);
		instr_asm.imm = 0;
		s_real.regs[instr_asm.src] &= ~(1 << 31);
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;
		// Test 3: 0 imm and 0 Rn
		generate_state_random(&s_real, &instr_asm);
		instr_asm.imm = 0;
		s_real.regs[instr_asm.src] = 0;
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;
		// Test 4: 31 imm and high Rn
		generate_state_random(&s_real, &instr_asm);
		instr_asm.imm = 31;
		s_real.regs[instr_asm.src] |= (1 << 31);
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;
		// Test 5: 31 imm and low Rn
		generate_state_random(&s_real, &instr_asm);
		instr_asm.imm = 31;
		s_real.regs[instr_asm.src] &= ~(1 << 31);
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;
		// Test 6: 31 imm and 0 Rn
		generate_state_random(&s_real, &instr_asm);
		instr_asm.imm = 31;
		s_real.regs[instr_asm.src] = 0;
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;

		instr_asm.type = LSR;
	}

	// generate LDR and STR tests
	instr_asm.type = LDR;
	for (int i = 0; i < 2; ++i) {
		// Test 1: 0 Rd
		do {
			generate_state_random(&s_real, &instr_asm);
		} while (instr_asm.dest == instr_asm.src);
		s_real.regs[instr_asm.dest] = 0;
		int offset = rand() % MEM_SIZE;
		s_real.regs[instr_asm.src] = (uint32_t)(s_real.mem + offset);
		instr_asm.imm %= (MEM_SIZE - offset);
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;
		// Test 2: high Rd
		do {
			generate_state_random(&s_real, &instr_asm);
		} while (instr_asm.dest == instr_asm.src);
		s_real.regs[instr_asm.dest] |= (1 << 31);
		offset = rand() % MEM_SIZE;
		s_real.regs[instr_asm.src] = (uint32_t)(s_real.mem + offset);
		instr_asm.imm %= (MEM_SIZE - offset);
		generate_test(&s_real, &instr_asm, instr_casp);
		memcpy(&s_exp, &s_real, sizeof(struct state));
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp))  failed = 1;
		if (++test == NUM_TESTS)  return failed;

		instr_asm.type = STR;
	}

	// fill rest of quota with random tests
	for (; test < NUM_TESTS; ++test) {
		// generate a random test
		generate_test_random(&s_real, &instr_asm, instr_casp);

		// init the expected state
		memcpy(&s_exp, &s_real, sizeof(struct state));

		// run asm and casp instructions
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp)) {
			failed = 1;
		}
	}
	return failed;
}

int run_tests_random() {
	int failed = 0;
	struct state s_real;
	struct state s_exp;
	init_state(&s_real);
	struct instr instr_asm;
	char instr_casp[MAX_INSTR_LEN];
	memset(instr_casp, 0, MAX_INSTR_LEN);

	for (int t = 0; t < NUM_TESTS; ++t) {
		// generate a random test
		generate_test_random(&s_real, &instr_asm, instr_casp);

		// init the expected state
		memcpy(&s_exp, &s_real, sizeof(struct state));

		// run asm and casp instructions
		if (run_and_cmp(&s_real, &instr_asm, &s_exp, instr_casp)) {
			failed = 1;
		}
	}
	return failed;
}

void run_casp(state_ptr s, const char *instr) {
	// write test.prog for the interpreter
	// completing test.prog tells armtest_casp to run
	FILE *casp_input = fopen("test.prog", "w");
	assert(casp_input);
	char buffer[MAX_INSTR_LEN];
	for (int i = 0; i < NUM_REGS; ++i) {
		if (s->regs[i] == 0) {
			continue;
		}
		memset(buffer, 0, MAX_INSTR_LEN);
		sprintf(buffer, "(SETREG R%d 0x%08x)\n", i, s->regs[i]);
		fputs(buffer, casp_input);
	}
	for (int i = 0; i < MEM_SIZE; ++i) {
		memset(buffer, 0, MAX_INSTR_LEN);
		char *bufptr = buffer;
		sprintf(bufptr, "(SETREG MEM 0x%08x", s->mem[i]);
		bufptr += 22;
		for (int j = 0; j < i; ++j) {
			sprintf(bufptr, "00000000");
			bufptr += 8;
		}
		sprintf(bufptr, ")\n");
		fputs(buffer, casp_input);
	}
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

	// run cassiopeia interpreter in foreground
#ifdef BUGGY
	system("./cassiopeia arm-buggy.casp -interp test.prog > out.txt\n");
#else
	system("./cassiopeia arm.casp -interp test.prog > out.txt\n");
#endif
	remove("test.prog");

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
	fgets(buffer, MAX_INSTR_LEN, casp_output);
	c = strchr(buffer, ':');
	++c;
	c_end = strchr(c, ',');
	*c_end = '\0';
	res = strtoul(c, NULL, 16);
	s->mem[0] = res;

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
	// get registers
	for (int i = 0; i < 16; ++i) {
		fgets(buffer, MAX_INSTR_LEN, casp_output);
		c = strchr(buffer, ':');
		++c;
		c_end = strchr(c, ',');
		*c_end = '\0';
		res = strtoul(c, NULL, 16);
		// s->regs[i] = res;

		if (i == 0) s->regs[0] = res;
		if (i == 1) s->regs[1] = res;
		if (i == 8) s->regs[2] = res;
		if (i == 9) s->regs[3] = res;
		if (i == 10) s->regs[4] = res;
		if (i == 11) s->regs[5] = res;
		if (i == 12) s->regs[6] = res;
		if (i == 13) s->regs[7] = res;
		if (i == 14) s->regs[8] = res;
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
	remove("out.txt");
}

/********** machine independent stuff below **********/

void init_state(state_ptr s) {
	memset(s, 0, sizeof(struct state));
}

void generate_state_random(state_ptr s, instr_ptr instr_asm) {
	// reset old variables
	init_state(s);

	// generate a random state
	for (int i = 0; i < sizeof(struct state); ++i) {
		((uint8_t*)s)[i] = rand() % 0xff;
	}

	// pick random registers for the instruction
	instr_asm->dest = rand() % NUM_REGS;
	instr_asm->src = rand() % NUM_REGS;
	instr_asm->imm = rand();
	instr_asm->imm |= (rand() % 2 << 31); // fixes rand_max bound

	// Does not set instruction type
}

int run_and_cmp(state_ptr s_real, instr_ptr instr_asm,
	state_ptr s_exp, const char *instr_casp) {
	run_asm(s_real, instr_asm);
	run_casp(s_exp, instr_casp);
	return cmp_state(s_real, s_exp);
}

int cmp_state(const state_ptr s1, const state_ptr s2) {
	if (!memcmp(s1, s2, sizeof(struct state))) {
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
