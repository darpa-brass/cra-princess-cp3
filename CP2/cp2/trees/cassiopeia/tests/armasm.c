/*
 * armasm.c
 *
 *  Created on: Mar 22, 2018
 *      Author: abby
 */

// This file is just for the run_asm function, which has lots of junky
// assembly code, most of which was generated in armgen.py.

#include "armtest.h"

void run_asm(state_ptr s, const instr_ptr instr) {
	// assign state variables to actual registers
	register uint32_t r0_ asm("r0") = s->regs[0];
	register uint32_t r1_ asm("r1") = s->regs[1];
	register uint32_t r2_ asm("r2") = s->regs[2];
	register uint32_t r3_ asm("r3") = s->regs[3];
	register uint32_t r4_ asm("r4") = s->regs[4];
	register uint32_t r5_ asm("r5") = s->regs[5];
	register uint32_t r6_ asm("r6") = s->regs[6];
	register uint32_t r7_ asm("r7") = s->regs[7];
	register uint32_t r8_ asm("r8") = s->regs[8];
	uint32_t cpsr_ = 0;

	// Run no-ops to explicitly set registers
	// Keep track of CPSR in a separate variable
	// Then run the actual instruction

/************************ DISGUSTING STUFF STARTS HERE ***********************/
if (instr->type == ADD) {
    if (instr->dest == 0) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg0],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg0],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg0],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg0],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg0],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg0],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg0],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg0],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg0],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 1) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg1],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg1],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg1],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg1],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg1],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg1],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg1],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg1],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg1],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 2) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg2],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg2],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg2],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg2],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg2],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg2],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg2],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg2],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg2],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 3) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg3],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg3],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg3],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg3],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg3],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg3],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg3],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg3],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg3],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 4) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg4],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg4],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg4],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg4],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg4],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg4],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg4],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg4],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg4],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 5) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg5],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg5],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg5],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg5],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg5],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg5],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg5],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg5],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg5],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 6) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg6],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg6],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg6],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg6],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg6],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg6],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg6],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg6],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg6],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 7) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg7],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg7],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg7],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg7],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg7],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg7],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg7],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg7],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg7],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 8) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg8],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg8],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg8],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg8],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg8],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg8],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg8],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg8],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "adds %[reg8],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
}
if (instr->type == LSL) {
    if (instr->dest == 0) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg0],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg0],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg0],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg0],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg0],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg0],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg0],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg0],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg0],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 1) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg1],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg1],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg1],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg1],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg1],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg1],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg1],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg1],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg1],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 2) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg2],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg2],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg2],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg2],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg2],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg2],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg2],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg2],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg2],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 3) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg3],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg3],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg3],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg3],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg3],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg3],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg3],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg3],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg3],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 4) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg4],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg4],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg4],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg4],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg4],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg4],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg4],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg4],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg4],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 5) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg5],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg5],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg5],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg5],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg5],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg5],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg5],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg5],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg5],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 6) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg6],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg6],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg6],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg6],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg6],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg6],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg6],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg6],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg6],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 7) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg7],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg7],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg7],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg7],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg7],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg7],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg7],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg7],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg7],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 8) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg8],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg8],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg8],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg8],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg8],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg8],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg8],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg8],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsls %[reg8],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
}
if (instr->type == LSR) {
    if (instr->dest == 0) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg0],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg0],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg0],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg0],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg0],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg0],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg0],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg0],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg0],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 1) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg1],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg1],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg1],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg1],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg1],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg1],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg1],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg1],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg1],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 2) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg2],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg2],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg2],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg2],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg2],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg2],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg2],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg2],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg2],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 3) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg3],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg3],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg3],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg3],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg3],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg3],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg3],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg3],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg3],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 4) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg4],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg4],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg4],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg4],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg4],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg4],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg4],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg4],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg4],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 5) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg5],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg5],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg5],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg5],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg5],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg5],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg5],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg5],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg5],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 6) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg6],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg6],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg6],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg6],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg6],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg6],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg6],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg6],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg6],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 7) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg7],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg7],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg7],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg7],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg7],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg7],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg7],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg7],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg7],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 8) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg8],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg8],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg8],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg8],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg8],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg8],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg8],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg8],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "lsrs %[reg8],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
}
if (instr->type == AND) {
    if (instr->dest == 0) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg0],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg0],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg0],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg0],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg0],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg0],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg0],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg0],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg0],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 1) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg1],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg1],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg1],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg1],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg1],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg1],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg1],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg1],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg1],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 2) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg2],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg2],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg2],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg2],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg2],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg2],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg2],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg2],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg2],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 3) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg3],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg3],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg3],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg3],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg3],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg3],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg3],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg3],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg3],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 4) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg4],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg4],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg4],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg4],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg4],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg4],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg4],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg4],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg4],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 5) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg5],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg5],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg5],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg5],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg5],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg5],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg5],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg5],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg5],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 6) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg6],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg6],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg6],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg6],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg6],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg6],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg6],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg6],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg6],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 7) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg7],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg7],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg7],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg7],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg7],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg7],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg7],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg7],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg7],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 8) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg8],%[reg0],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg8],%[reg1],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg8],%[reg2],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg8],%[reg3],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg8],%[reg4],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg8],%[reg5],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg8],%[reg6],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg8],%[reg7],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ands %[reg8],%[reg8],%[imm]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
}
if (instr->type == LDR) {
    if (instr->dest == 0) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg0],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg0],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg0],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg0],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg0],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg0],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg0],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg0],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg0],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 1) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg1],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg1],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg1],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg1],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg1],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg1],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg1],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg1],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg1],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 2) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg2],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg2],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg2],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg2],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg2],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg2],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg2],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg2],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg2],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 3) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg3],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg3],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg3],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg3],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg3],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg3],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg3],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg3],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg3],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 4) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg4],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg4],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg4],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg4],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg4],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg4],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg4],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg4],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg4],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 5) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg5],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg5],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg5],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg5],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg5],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg5],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg5],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg5],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg5],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 6) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg6],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg6],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg6],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg6],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg6],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg6],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg6],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg6],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg6],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 7) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg7],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg7],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg7],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg7],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg7],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg7],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg7],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg7],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg7],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 8) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg8],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg8],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg8],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg8],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg8],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg8],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg8],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg8],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "ldr %[reg8],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
}
if (instr->type == STR) {
    if (instr->dest == 0) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg0],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg0],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg0],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg0],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg0],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg0],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg0],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg0],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg0],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 1) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg1],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg1],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg1],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg1],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg1],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg1],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg1],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg1],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg1],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 2) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg2],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg2],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg2],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg2],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg2],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg2],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg2],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg2],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg2],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 3) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg3],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg3],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg3],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg3],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg3],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg3],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg3],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg3],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg3],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 4) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg4],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg4],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg4],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg4],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg4],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg4],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg4],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg4],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg4],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 5) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg5],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg5],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg5],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg5],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg5],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg5],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg5],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg5],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg5],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 6) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg6],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg6],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg6],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg6],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg6],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg6],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg6],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg6],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg6],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 7) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg7],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg7],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg7],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg7],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg7],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg7],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg7],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg7],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg7],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
    if (instr->dest == 8) {
        if (instr->src == 0) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg8],[%[reg0],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 1) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg8],[%[reg1],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 2) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg8],[%[reg2],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 3) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg8],[%[reg3],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 4) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg8],[%[reg4],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 5) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg8],[%[reg5],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 6) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg8],[%[reg6],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 7) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg8],[%[reg7],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
        if (instr->src == 8) {
            asm volatile(
                "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmov %[reg6],%[reg6]\n\tmov %[reg7],%[reg7]\n\tmov %[reg8],%[reg8]\n\tmrs %[f1],cpsr\n\t"
                "str %[reg8],[%[reg8],%[imm]]\n\t"
                "mrs %[f2],cpsr\n\t"
                : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_),[reg6] "=r" (r6_),[reg7] "=r" (r7_),[reg8] "=r" (r8_)
                : [imm] "r" (instr->imm),[reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg6] "r" (r6_),[reg7] "r" (r7_),[reg8] "r" (r8_)
                : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"
            );
        }
    }
}

/************************ DISGUSTING STUFF ENDS HERE *************************/

	// extract the new state
	s->regs[0] = r0_;
	s->regs[1] = r1_;
	s->regs[2] = r2_;
	s->regs[3] = r3_;
	s->regs[4] = r4_;
	s->regs[5] = r5_;
	s->regs[6] = r6_;
	s->regs[7] = r7_;
	s->regs[8] = r8_;

	// deal with other machine-dependent crap, like
	// tracking changes in cpsr
	for (int i = 31; i > 27; --i) {
		if (cpsr_ >> i == 1 && s->cpsr >> i == 0) {
			s->cpsr |= 1 << i;
		}
		else {
			s->cpsr &= ~(1 << i);
		}
	}
	s->cpsr &= 0xF0000000;
}
