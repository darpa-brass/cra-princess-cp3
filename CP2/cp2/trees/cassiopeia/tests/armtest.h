/*
 * armtest.h
 *
 *  Created on: Mar 16, 2018
 *      Author: abby
 */

#ifndef ARMTEST_H_
#define ARMTEST_H_

#include <stdint.h>

#define MAX_INSTR_LEN 512
#define NUM_INSTRS 6
#define NUM_REGS 9
#define MEM_SIZE 1 // in 32-bit integers
#define NUM_TESTS 100 // total number of tests to be run
// #define BUGGY // defined if buggy ARM cassiopeia should be tested
// #define RANDOM_SUITE // defined if tests should be completely randomized

struct state {
	uint32_t regs[NUM_REGS];
	uint32_t mem[MEM_SIZE];
	uint32_t cpsr;
};

enum instr_type {
	ADD,
	LSL,
	LSR,
	AND,
	LDR,
	STR
};

struct instr {
	enum instr_type type; // instruction to be tested
	uint32_t dest; // destination register number
	uint32_t src; // source register number
	uint32_t imm; // immediate value
};

// machine dependent
typedef struct state *state_ptr;
typedef struct instr *instr_ptr;
int run_tests_set();
int run_tests_random();
void generate_test(const state_ptr s, const instr_ptr instr_asm, 
	char *instr_casp);
void generate_test_random(
	state_ptr s, instr_ptr instr_asm, char *instr_casp);
void run_asm(state_ptr s, const instr_ptr instr);
void run_casp(state_ptr s, const char *instr);

// machine independent
void init_state(state_ptr s);
void generate_state_random(state_ptr s, instr_ptr instr_asm);
int run_and_cmp(state_ptr s_real, instr_ptr instr_asm, 
	state_ptr s_exp, const char *instr_casp);
int cmp_state(const state_ptr s1, const state_ptr s2);

#endif /* ARMTEST_H_ */
