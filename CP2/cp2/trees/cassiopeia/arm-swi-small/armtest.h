/*
 * armtest.h
 *
 *  Created on: Mar 16, 2018
 *      Author: abby
 *
 *  Modified on: May 24, 2018
 *      Author: Crystal
 */

#ifndef ARMTEST_H_
#define ARMTEST_H_

#include <stdint.h>

#define MAX_INSTR_LEN 512
#define NUM_INSTRS 8
#define NUM_REGS 9
#define MEM_SIZE 1 // in 32-bit integers
#define NUM_TESTS 100 // total number of tests to be run

struct state {
	uint32_t regs[NUM_REGS];
	uint32_t mem[MEM_SIZE];
	uint32_t cpsr;
};
struct splr_state{
	uint32_t sp_pre;
	uint32_t lr_pre;
	uint32_t sp_post;
	uint32_t lr_post;
};

enum instr_type {
	ADD_imm,
	STR_imm,
	STMIA_wtback_usr,
	STMDA_wtback,
	POP
};

struct instr {
	enum instr_type type; // instruction to be tested
	uint32_t dest; // destination register number
	uint32_t src; // source register number
	uint32_t num; // number of set bit in register list
	uint32_t imm; // immediate value
};

// machine dependent
typedef struct state *state_ptr;
typedef struct splr_state *splr_state_ptr;
typedef struct instr *instr_ptr;
int run_tests();
void generate_test(const state_ptr s, const instr_ptr instr_asm,
	char *instr_casp);
void run_asm(state_ptr s, splr_state_ptr splr, const instr_ptr instr, int num);
void run_casp(state_ptr s, splr_state_ptr splr, const char *instr);

// machine independent
void init_state(state_ptr s);
void start_reg_state(state_ptr s);
void generate_instr(state_ptr s, instr_ptr instr_asm, uint32_t dest, uint32_t src, uint32_t imm, uint32_t num);
int run_and_cmp(state_ptr s_real, instr_ptr instr_asm,
	state_ptr s_exp, splr_state_ptr splr, const char *instr_casp, int num);
int cmp_state(const state_ptr s1, const state_ptr s2);

#endif /* ARMTEST_H_ */
