/*
 * armasm.c
 *
 *  Created on: Mar 22, 2018
 *      Author: abby
 *
 *  Modified on: May 24, 2018
 *      Author: Crystal
 */

#include "armtest.h"

void run_asm(state_ptr s, splr_state_ptr splr, const instr_ptr instr, int num) {
	// assign state variables to actual registers
	register uint32_t r0_ asm("r0") = s->regs[0];
	register uint32_t r1_ asm("r1") = s->regs[1];
	register uint32_t r2_ asm("r2") = s->regs[2];
	register uint32_t r3_ asm("r3") = s->regs[3];
	register uint32_t r4_ asm("r4") = s->regs[4];
	register uint32_t r5_ asm("r5") = s->regs[5];
	register uint32_t r6_ asm("r13");
	register uint32_t r7_ asm("r14");
	uint32_t cpsr_ = 0;


	// Run no-ops to explicitly set registers
	// Keep track of CPSR in a separate variable
	// Then run the actual instruction

    // get the sp and lr here
    splr->sp_pre = r6_;
    splr->lr_pre = r7_;

		// str %[reg3], [%[reg0], #0x000]
    if (num == 1) {
        asm volatile(
            "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmrs %[f1],cpsr\n\t"
            "str %[reg3], [%[reg0], #0x000]\n\t"
            "mrs %[f2],cpsr\n\t"
            : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_)
            : [reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg7] "r" (r7_)
            : "r0", "r1", "r2", "r3", "r4", "r5", "r7"
            );
    }
    // str %[reg7], [%[reg0], #0x040]
    if (num == 2) {
        asm volatile(
            "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmrs %[f1],cpsr\n\t"
            "str %[reg7], [%[reg0], #0x040]\n\t"
            "mrs %[f2],cpsr\n\t"
            : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_)
            : [reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg7] "r" (r7_)
            : "r0", "r1", "r2", "r3", "r4", "r5", "r7"
            );
    }
    // add %[reg3], %[reg0], #0x014
    if (num == 3) {
        asm volatile(
            "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmrs %[f1],cpsr\n\t"
            "add %[reg3], %[reg0], #0x014\n\t"
            "mrs %[f2],cpsr\n\t"
            : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_)
            : [reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg7] "r" (r7_)
            : "r0", "r1", "r2", "r3", "r4", "r5", "r7"
            );
    }
    // stmia %[reg3]!, {%[reg4]-%[reg7]}
    if (num == 4) {
        asm volatile(
            "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmrs %[f1],cpsr\n\t"
            "stmia %[reg3]!, {%[reg4]-%[reg7]}\n\t"
            "mrs %[f2],cpsr\n\t"
            : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_)
            : [reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg7] "r" (r7_)
            : "r0", "r1", "r2", "r3", "r4", "r5", "r7"
            );
    }
    // add %[reg3], %[reg3], #0x008
    if (num == 5) {
        asm volatile(
            "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmrs %[f1],cpsr\n\t"
            "add %[reg3], %[reg3], #0x008\n\t"
            "mrs %[f2],cpsr\n\t"
            : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_)
            : [reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg7] "r" (r7_)
            : "r0", "r1", "r2", "r3", "r4", "r5", "r7"
            );
    }
    // add %[reg3], %[reg0], #0x010
    if (num == 6) {
        asm volatile(
            "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmrs %[f1],cpsr\n\t"
            "add %[reg3], %[reg0], #0x010\n\t"
            "mrs %[f2],cpsr\n\t"
            : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_)
            : [reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg7] "r" (r7_)
            : "r0", "r1", "r2", "r3", "r4", "r5", "r7"
            );
    }
    // pop {%[reg4]-%[reg5]}
    if (num == 7) {
        asm volatile(
            "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmrs %[f1],cpsr\n\t"
            "pop {%[reg4]-%[reg5]}\n\t"
            "push {%[reg4]-%[reg5]}\n\t"
            "mrs %[f2],cpsr\n\t"
            : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_)
            : [reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg7] "r" (r7_)
            : "r0", "r1", "r2", "r3", "r4", "r5", "r7"
            );
    }
    // stmda %[reg3]!, {%[reg4]-%[reg5]}
    if (num == 8) {
        asm volatile(
            "mov %[reg0],%[reg0]\n\tmov %[reg1],%[reg1]\n\tmov %[reg2],%[reg2]\n\tmov %[reg3],%[reg3]\n\tmov %[reg4],%[reg4]\n\tmov %[reg5],%[reg5]\n\tmrs %[f1],cpsr\n\t"
            "stmda %[reg3]!, {%[reg4]-%[reg5]}\n\t"
            "mrs %[f2],cpsr\n\t"
            : [f1] "=r" (s->cpsr),[f2] "=r" (cpsr_),[reg0] "=r" (r0_),[reg1] "=r" (r1_), [reg2] "=r" (r2_), [reg3] "=r" (r3_),[reg4] "=r" (r4_),[reg5] "=r" (r5_)
            : [reg0] "r" (r0_),[reg1] "r" (r1_),[reg2] "r" (r2_), [reg3] "r" (r3_), [reg4] "r" (r4_),[reg5] "r" (r5_),[reg7] "r" (r7_)
            : "r0", "r1", "r2", "r3", "r4", "r5", "r7"
            );
    }

    // get sp and lr here
    splr->sp_post = r6_;
    splr->lr_post = r7_;

	// extract the new state
	s->regs[0] = r0_;
	s->regs[1] = r1_;
	s->regs[2] = r2_;
	s->regs[3] = r3_;
	s->regs[4] = r4_;
	s->regs[5] = r5_;

	s->regs[6] = r6_;
	s->regs[7] = r7_;

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
