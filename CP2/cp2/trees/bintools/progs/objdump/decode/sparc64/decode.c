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

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>  // for snprintf
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "mem.h"
#include "genfmt.h"

#include "targetopcode.h"

#include "dumptbl.h"
#include "disasm.h"

/*
 * MIPS disassembler.
 */

struct disasm {
   unsigned ds_section;
   uint8_t *ds_data;
   u_machword ds_basevaddr;
   u_machword ds_size;

   u_machword ds_pos;
};

struct disbuf {
   struct disasm *ds;
   char *buf;
   size_t pos;
   size_t max;
};

/*
 * Basic format of a mips instruction is
 *
 *    opcode:6 a:5 b:5 c:5 d:5 e:6
 *
 * where e is often a secondary opcode, and the a-d fields tend to
 * be registers. Most often when there's an immediate it's the 16
 * bits c|d|e, but not always... sometimes a|b|c|d is a 20-bit
 * immediate. And there are other combinations, and a few
 * instructions use subfields of these slices.
 */

#define FIELD_opcode(insn)	((insn) >> 26)
#define FIELD_a(insn)		(((insn) >> 21) & 31)
#define FIELD_b(insn)		(((insn) >> 16) & 31)
#define FIELD_c(insn)		(((insn) >> 11) & 31)
#define FIELD_d(insn)		(((insn) >> 6) & 31)
#define FIELD_e(insn)		((insn) & 63)

#define FIELD_abcde(insn)	((insn) & 0x3ffffff)
#define FIELD_abcd(insn)	(((insn) >> 6) & 0xfffff)
#define FIELD_ab(insn)		(((insn) >> 16) & 0x3ff)
#define FIELD_cd(insn)		(((insn) >> 6) & 0x3ff)
#define FIELD_cde(insn)		((insn) & 0xffff)

////////////////////////////////////////////////////////////

struct disasm *ds_create(struct binfile *bf, struct gensect *gsx,
			 unsigned sectindex) {
   struct disasm *ds;

   (void)bf;

   ds = domalloc(sizeof(*ds));

   ds->ds_section = sectindex;
   ds->ds_data = (uint8_t *)gsx->gsx_data;
   ds->ds_basevaddr = gsx->gsx_vaddr;
   ds->ds_size = gsx->gsx_size;

   ds->ds_pos = 0;

   return ds;
}

void ds_destroy(struct disasm *ds) {
   dofree(ds, sizeof(*ds));
}

int ds_done(struct disasm *ds) {
   return ds->ds_pos >= ds->ds_size;
}

u_machword ds_getvaddr(struct disasm *ds) {
   return ds->ds_basevaddr + ds->ds_pos;
}

static uint8_t ds_getbyte(struct disasm *ds) {
   uint8_t val;
   u_machword rounded_size;

   /* avoid crashing trying to disassemble odd-sized sections */
   rounded_size = 4*((ds->ds_size + 3)/4);
   assert(ds->ds_pos < rounded_size);

   if (ds->ds_pos < ds->ds_size) {
      val = ds->ds_data[ds->ds_pos];
   }
   else {
      val = 0;
   }
   ds->ds_pos++;
   return val;
}

static uint32_t ds_getword(struct disasm *ds) {
   uint32_t val;

   val = ds_getbyte(ds) << 24;
   val |= ds_getbyte(ds) << 16;
   val |= ds_getbyte(ds) << 8;
   val |= ds_getbyte(ds);
   return val;
}

////////////////////////////////////////////////////////////
// disbuf

static void disbuf_init(struct disbuf *d, struct disasm *ds, char *buf, size_t max) {
   d->ds = ds;
   d->buf = buf;
   d->pos = 0;
   d->max = max;
}

static void disbuf_cleanup(struct disbuf *d) {
   (void)d;
}

static PF(2, 3) void disprint(struct disbuf *d, const char *fmt, ...) {
   va_list ap;

   va_start(ap, fmt);
   assert(d->max > d->pos);
   vsnprintf(d->buf + d->pos, d->max - d->pos, fmt, ap);
   va_end(ap);
   d->pos = strlen(d->buf);
}

////////////////////////////////////////////////////////////

#if 0 /* notyet */
static const char *regname(int reg) {
   static const char *regs[32] = {
      "z0",
      "AT",
      "v0", "v1",
      "a0", "a1", "a2", "a3",
      "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
      "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
      "t8", "t9",
      "k0", "k1",
      "gp",
      "sp", "s8", "ra"
   };

   assert(reg < 32);
   return regs[reg];
}
#endif

static void ds_xxRx(struct disbuf *d, const char *op, uint32_t insn) {
   disprint(d, "%s $%u", op, FIELD_c(insn));
}

static void ds_Rxxx(struct disbuf *d, const char *op, uint32_t insn) {
   disprint(d, "%s $%u", op, FIELD_a(insn));
}

static void ds_RRRx(struct disbuf *d, const char *op, uint32_t insn) {
   disprint(d, "%s $%u, $%u, $%u", op,
	    FIELD_c(insn), FIELD_a(insn), FIELD_b(insn));
}

static void ds_RRRx_shift(struct disbuf *d, const char *op, uint32_t insn) {
   disprint(d, "%s $%u, $%u, $%u", op,
	    FIELD_c(insn), FIELD_b(insn), FIELD_a(insn));
}

static void ds_RxRx(struct disbuf *d, const char *op, uint32_t insn) {
   disprint(d, "%s $%u, $%u", op,
	    FIELD_c(insn), FIELD_a(insn));
}

static void ds_RRxx(struct disbuf *d, const char *op, uint32_t insn) {
   disprint(d, "%s $%u, $%u", op,
	    FIELD_b(insn), FIELD_a(insn));
}

static void ds_RR_s16(struct disbuf *d, const char *op, uint32_t insn) {
   disprint(d, "%s $%u, $%u, %d", op,
	    FIELD_b(insn), FIELD_a(insn), (int)(int16_t)FIELD_cde(insn));
}

static void ds_RR_u16(struct disbuf *d, const char *op, uint32_t insn) {
   disprint(d, "%s $%u, $%u, %u", op,
	    FIELD_b(insn), FIELD_a(insn), (unsigned)(uint16_t)FIELD_cde(insn));
}

static void ds_shift(struct disbuf *d, const char *op, uint32_t insn) {
   disprint(d, "%s $%u, $%u, %u", op,
	    FIELD_c(insn), FIELD_b(insn), FIELD_d(insn));
}

static void ds_ill(struct disbuf *d, uint32_t insn) {
   disprint(d, ".word 0x%lx", (unsigned long) insn);
}

static void ds_absaddress(struct disbuf *d, uint32_t addr) {
   struct gensym *gsm;

   gsm = get_nearest_sym_byaddr(addr);
   if (gsm && gsm->gsm_value == addr) {
      disprint(d, "# 0x%lx (%s)",
	       (unsigned long) addr, gsm->gsm_name);
   }
   else if (gsm) {
      disprint(d, "# 0x%lx (%s + 0x%lx)",
	       (unsigned long) addr, gsm->gsm_name,
	       (unsigned long) (addr - gsm->gsm_value));
   }
   else {
      disprint(d, "# 0x%lx (?)", (unsigned long)addr);
   }
}

static void ds_reladdress(struct disbuf *d, int32_t offset) {
   uint32_t addr;

   addr = ds_getvaddr(d->ds);
   addr += offset;
   ds_absaddress(d, addr);
}

static void ds_jump(struct disbuf *d, const char *op, uint32_t insn) {
   uint32_t target;

   target = ds_getvaddr(d->ds) & 0xfc000000;
   target |= FIELD_abcde(insn);

   disprint(d, "%s %u ", op, target);
   ds_absaddress(d, target);
}

static void ds_branch(struct disbuf *d, const char *op, uint32_t insn) {
   int16_t offset;

   offset = FIELD_cde(insn);

   disprint(d, "%s $%u, $%u, %d ", op, FIELD_a(insn), FIELD_b(insn), offset);
   ds_reladdress(d, (int32_t)offset * 4);
}

static void ds_mem(struct disbuf *d, const char *op, uint32_t insn) {
   disprint(d, "%s $%u, %d($%u)", op,
	    FIELD_b(insn), (int)(int16_t)FIELD_cde(insn), FIELD_a(insn));
}

static void ds_specmem(struct disbuf *d, const char *op, uint32_t insn) {
   disprint(d, "%s %u, %d($%u)", op,
	    FIELD_b(insn), (int)(int16_t)FIELD_cde(insn), FIELD_a(insn));
}

static void ds_special(struct disbuf *d, uint32_t insn) {
   /* secondary opcode is bottom 6 bits */
   switch (FIELD_e(insn)) {
    case SPEC_SLL: 
     if (FIELD_b(insn) == 0 && FIELD_c(insn) == 0 && FIELD_d(insn) == 0) {
	disprint(d, "nop");
     }
     else if (FIELD_b(insn) == 0 && FIELD_c(insn) == 0 && FIELD_d(insn) == 1) {
	disprint(d, "ssnop");
     }
     else {
	ds_shift(d, "sll", insn);
     }
     break;
    case SPEC_MOVC:
     if (FIELD_b(insn) & 1) {
	disprint(d, "movt $%u, $%u, $cc%u", FIELD_c(insn), FIELD_a(insn),
		 FIELD_b(insn) >> 2);
     }
     else {
	disprint(d, "movf $%u, $%u, $cc%u", FIELD_c(insn), FIELD_a(insn),
		 FIELD_b(insn) >> 2);
     }
     break;
    case SPEC_SRL: ds_shift(d, "srl", insn); break;
    case SPEC_SRA: ds_shift(d, "sra", insn); break;
    case SPEC_SLLV: ds_RRRx_shift(d, "sllv", insn); break;
    case SPEC_SRLV: ds_RRRx_shift(d, "srlv", insn); break;
    case SPEC_SRAV: ds_RRRx_shift(d, "srav", insn); break;
    case SPEC_JR:
     disprint(d, "jr $%u", FIELD_a(insn));
     break;
    case SPEC_JALR: 
     if (FIELD_c(insn) == 31) {
	disprint(d, "jalr $%u", FIELD_a(insn));
     }
     else {
	disprint(d, "jalr $%u, $%u", FIELD_c(insn), FIELD_a(insn));
     }
     break;
    case SPEC_MOVZ: ds_RRRx(d, "movz", insn); break;
    case SPEC_MOVN: ds_RRRx(d, "movn", insn); break;
    case SPEC_SYSCALL: disprint(d, "syscall %u", FIELD_abcd(insn)); break;
    case SPEC_BREAK:
     if (FIELD_cd(insn) != 0) {
	disprint(d, "break %u, %u", FIELD_ab(insn), FIELD_cd(insn));
     }
     else if (FIELD_ab(insn) != 0) {
	disprint(d, "break %u", FIELD_ab(insn));
     }
     else {
	disprint(d, "break");
     }
     break;
    case SPEC_SYNC: disprint(d, "sync"); break;
    case SPEC_MFHI: ds_xxRx(d, "mfhi", insn); break;
    case SPEC_MTHI: ds_Rxxx(d, "mthi", insn); break;
    case SPEC_MFLO: ds_xxRx(d, "mflo", insn); break;
    case SPEC_MTLO: ds_Rxxx(d, "mtlo", insn); break;
    case SPEC_MULT: ds_RRxx(d, "mult", insn); break;
    case SPEC_MULTU: ds_RRxx(d, "multu", insn); break;
    case SPEC_DIV: ds_RRxx(d, "div", insn); break;
    case SPEC_DIVU: ds_RRxx(d, "divu", insn); break;
    case SPEC_ADD: ds_RRRx(d, "add", insn); break;
    case SPEC_ADDU: ds_RRRx(d, "addu", insn); break;
    case SPEC_SUB: ds_RRRx(d, "sub", insn); break;
    case SPEC_SUBU: ds_RRRx(d, "subu", insn); break;
    case SPEC_AND: ds_RRRx(d, "and", insn); break;
    case SPEC_OR: ds_RRRx(d, "or", insn); break;
    case SPEC_XOR: ds_RRRx(d, "xor", insn); break;
    case SPEC_NOR:
     if (FIELD_a(insn) == 0) {
	disprint(d, "not $%u, $%u", FIELD_c(insn), FIELD_b(insn));
     }
     else if (FIELD_b(insn) == 0) {
	disprint(d, "not $%u, $%u", FIELD_c(insn), FIELD_a(insn));
     }
     else {
	ds_RRRx(d, "nor", insn);
     }
     break;
    case SPEC_SLT: ds_RRRx(d, "slt", insn); break;
    case SPEC_SLTU: ds_RRRx(d, "sltu", insn); break;
    case SPEC_TGE:
     disprint(d, "tge $%u, $%u, %u", FIELD_a(insn), FIELD_b(insn),
	      FIELD_cd(insn));
     break;
    case SPEC_TGEU:
     disprint(d, "tgeu $%u, $%u, %u", FIELD_a(insn), FIELD_b(insn),
	      FIELD_cd(insn));
     break;
    case SPEC_TLT:
     disprint(d, "tlt $%u, $%u, %u", FIELD_a(insn), FIELD_b(insn),
	      FIELD_cd(insn));
     break;
    case SPEC_TLTU:
     disprint(d, "tltu $%u, $%u, %u", FIELD_a(insn), FIELD_b(insn),
	      FIELD_cd(insn));
     break;
    case SPEC_TEQ:
     disprint(d, "teq $%u, $%u, %u", FIELD_a(insn), FIELD_b(insn),
	      FIELD_cd(insn));
     break;
    case SPEC_TNE:
     disprint(d, "tne $%u, $%u, %u", FIELD_a(insn), FIELD_b(insn),
	      FIELD_cd(insn));
     break;
    default: ds_ill(d, insn); break;
   }
}

static void ds_bcond(struct disbuf *d, uint32_t insn) {
   const char *op;
   int16_t offset;

   /* secondary opcode is in field B */
   switch (FIELD_b(insn)) {
    case BCOND_BGEZ: op = "bgez"; break;
    case BCOND_BGEZL: op = "bgezl"; break;
    case BCOND_BGEZAL: op = "bgezal"; break;
    case BCOND_BGEZALL: op = "bgezall"; break;
    case BCOND_BLTZ: op = "bltz"; break;
    case BCOND_BLTZL: op = "bltzl"; break;
    case BCOND_BLTZAL: op = "bltzal"; break;
    case BCOND_BLTZALL: op = "bltzall"; break;
    case BCOND_TGEI: op = "tgei"; break;
    case BCOND_TGEIU: op = "tgeiu"; break;
    case BCOND_TLTI: op = "tlti"; break;
    case BCOND_TLTIU: op = "tltiu"; break;
    case BCOND_TEQI: op = "teqi"; break;
    case BCOND_TNEI: op = "tnei"; break;
    default: ds_ill(d, insn); return;
   }

   offset = FIELD_cde(insn);

   disprint(d, "%s $%u, %d ", op, FIELD_a(insn), offset);
   ds_reladdress(d, (int32_t)offset * 4);
}

static void ds_mfc(struct disbuf *d, unsigned cop, uint32_t insn) {
   unsigned sel;

   sel = FIELD_e(insn) & 7;
   if (sel) {
      disprint(d, "mfc%u $%u $%u %u", cop, FIELD_b(insn), FIELD_c(insn), sel);
   }
   else {
      disprint(d, "mfc%u $%u $%u", cop, FIELD_b(insn), FIELD_c(insn));
   }
}

static void ds_mtc(struct disbuf *d, unsigned cop, uint32_t insn) {
   unsigned sel;

   sel = FIELD_e(insn) & 7;
   if (sel) {
      disprint(d, "mtc%u $%u $%u %u", cop, FIELD_b(insn), FIELD_c(insn), sel);
   }
   else {
      disprint(d, "mtc%u $%u $%u", cop, FIELD_b(insn), FIELD_c(insn));
   }
}

static void ds_cfc(struct disbuf *d, unsigned cop, uint32_t insn) {
   disprint(d, "cfc%u $%u $%u", cop, FIELD_b(insn), FIELD_c(insn));
}

static void ds_ctc(struct disbuf *d, unsigned cop, uint32_t insn) {
   disprint(d, "ctc%u $%u $%u", cop, FIELD_b(insn), FIELD_c(insn));
}

static void ds_bc(struct disbuf *d, unsigned cop, uint32_t insn) {
   unsigned code, likely, ontrue;
   int16_t offset;

   code = FIELD_b(insn) >> 2;
   likely = FIELD_b(insn) & 2;
   ontrue = FIELD_b(insn) & 1;
   offset = FIELD_cde(insn);

   disprint(d, "bc%u%c%s %u, %d ", cop,
	    ontrue ? 't' : 'f',
	    likely ? "l" : "",
	    code, (int)offset);
   ds_reladdress(d, (int32_t)offset * 4);
}

static void ds_cop0(struct disbuf *d, uint32_t insn) {
   uint32_t code;

   switch (FIELD_a(insn)) {
    case COP_MF: ds_mfc(d, 0, insn); return;
    case COP_CF: ds_cfc(d, 0, insn); return;
    case COP_MT: ds_mtc(d, 0, insn); return;
    case COP_CT: ds_ctc(d, 0, insn); return;
    case COP_BC: ds_bc(d, 0, insn); return;
    default: break;
   }
   if ((FIELD_a(insn) & 0x10) == 0) {
      ds_ill(d, insn);
      return;
   }
   switch (FIELD_e(insn)) {
    case COP0_TLBR: disprint(d, "tlbr"); break;
    case COP0_TLBWI: disprint(d, "tlbwi"); break;
    case COP0_TLBWR: disprint(d, "tlbwr"); break;
    case COP0_TLBP: disprint(d, "tlbp"); break;
    case COP0_RFE: disprint(d, "rfe"); break;
    case COP0_ERET: disprint(d, "eret"); break;
    case COP0_DERET: disprint(d, "deret"); break;
    case COP0_WAIT:
     disprint(d, "wait");
     code = FIELD_abcd(insn) & 0x7ffff;
     if (code) {
	disprint(d, " %u", code);
     }
     break;
    default:
     ds_ill(d, insn);
     break;
   }
}

static void ds_float_RRR(struct disbuf *d, const char *op, const char *fmt,
			 uint32_t insn) {
   disprint(d, "%s.%s $%u, $%u, $%u", op, fmt,
	    FIELD_d(insn), FIELD_c(insn), FIELD_b(insn));
}

static void ds_float_xRR(struct disbuf *d, const char *op, const char *fmt,
			 uint32_t insn) {
   disprint(d, "%s.%s $%u, $%u", op, fmt,
	    FIELD_d(insn), FIELD_c(insn));
}

static void ds_float_movc(struct disbuf *d, const char *fmt, uint32_t insn) {
   unsigned cc, iftrue;

   cc = FIELD_b(insn) >> 2;
   iftrue = FIELD_b(insn) & 1;
   disprint(d, "mov%c.%s $%u, $%u, %u", iftrue ? 't' : 'f', fmt,
	    FIELD_d(insn), FIELD_c(insn), cc);
}

static void ds_cop1(struct disbuf *d, uint32_t insn) {
   const char *fmt;

   /*
    * XXX review this when we find out what the format codes really are
    */

   switch (FIELD_a(insn)) {
    case COP_MF: ds_mfc(d, 1, insn); return;
    case COP_CF: ds_cfc(d, 1, insn); return;
    case COP_MT: ds_mtc(d, 1, insn); return;
    case COP_CT: ds_ctc(d, 1, insn); return;
    case COP_BC: ds_bc(d, 1, insn); return;
    case COP1_FLOATFMT_F: fmt = "f"; break;
    case COP1_FLOATFMT_D: fmt = "d"; break;
    case COP1_FLOATFMT_S: fmt = "s"; break;
    case COP1_FLOATFMT_L: fmt = "l"; break;
    case COP1_FLOATFMT_W: fmt = "w"; break;
    default: ds_ill(d, insn); return;
   }
   
   switch (FIELD_e(insn)) {
    case COP1_ADD: ds_float_RRR(d, "add", fmt, insn); return;
    case COP1_SUB: ds_float_RRR(d, "sub", fmt, insn); return;
    case COP1_MUL: ds_float_RRR(d, "mul", fmt, insn); return;
    case COP1_DIV: ds_float_RRR(d, "div", fmt, insn); return;
    case COP1_SQRT: ds_float_xRR(d, "sqrt", fmt, insn); return;
    case COP1_ABS: ds_float_xRR(d, "abs", fmt, insn); return;
    case COP1_MOV: ds_float_xRR(d, "mov", fmt, insn); return;
    case COP1_NEG: ds_float_xRR(d, "neg", fmt, insn); return;
    case COP1_ROUND: ds_float_xRR(d, "round", fmt, insn); return;
    case COP1_TRUNC: ds_float_xRR(d, "trunc", fmt, insn); return;
    case COP1_CEIL: ds_float_xRR(d, "ceil", fmt, insn); return;
    case COP1_FLOOR: ds_float_xRR(d, "floor", fmt, insn); return;
    case COP1_MOVC: ds_float_movc(d, fmt, insn); return;
    case COP1_MOVZ: ds_float_RRR(d, "movz", fmt, insn); return;
    case COP1_MOVN: ds_float_RRR(d, "movn", fmt, insn); return;
    case COP1_CVT_S: ds_float_xRR(d, "cvt.s", fmt, insn); return;
    case COP1_CVT_D: ds_float_xRR(d, "cvt.d", fmt, insn); return;
    case COP1_CVT_W: ds_float_xRR(d, "cvt.w", fmt, insn); return;
    default:
     /* blah we should make this more symbolic */
     if (FIELD_e(insn) >= 48 && FIELD_e(insn) < 63) {
	break;
     }
     ds_ill(d, insn);
     return;
   }

   /* C.foo.bar */
   unsigned cc, cond;
   cc = FIELD_d(insn) >> 2;
   cond = FIELD_e(insn) & 0xf;

   static const char *const condstrs[16] = {
      "f", "un", "eq", "ueq",
      "olt", "ult", "ole", "ule",
      "sf", "ngle", "seq", "ngl",
      "lt", "nge", "le", "ngt",
   };

   disprint(d, "C.%s.%s %u, $%u, $%u",
	    condstrs[cond], fmt, cc, FIELD_c(insn), FIELD_b(insn));
}

static void ds_cop2(struct disbuf *d, uint32_t insn) {
   uint32_t code;

   switch (FIELD_a(insn)) {
    case COP_MF: ds_mfc(d, 2, insn); return;
    case COP_CF: ds_cfc(d, 2, insn); return;
    case COP_MT: ds_mtc(d, 2, insn); return;
    case COP_CT: ds_ctc(d, 2, insn); return;
    case COP_BC: ds_bc(d, 2, insn); return;
    default: break;
   }
   if ((FIELD_a(insn) & 0x10) == 0) {
      ds_ill(d, insn);
      return;
   }
   code = FIELD_abcde(insn) & 0x3ffffff;
   disprint(d, "cop2 %u", code);
}

static void ds_cop3(struct disbuf *d, uint32_t insn) {
   uint32_t code;

   switch (FIELD_a(insn)) {
    case COP_MF: ds_mfc(d, 3, insn); return;
    case COP_CF: ds_cfc(d, 3, insn); return;
    case COP_MT: ds_mtc(d, 3, insn); return;
    case COP_CT: ds_ctc(d, 3, insn); return;
    case COP_BC: ds_bc(d, 3, insn); return;
    default: break;
   }
   if ((FIELD_a(insn) & 0x10) == 0) {
      ds_ill(d, insn);
      return;
   }
   code = FIELD_abcde(insn) & 0x3ffffff;
   disprint(d, "cop3 %u", code);
}

static void ds_special2(struct disbuf *d, uint32_t insn) {
   /* secondary opcode is bottom 6 bits */
   switch (FIELD_e(insn)) {
    case SPEC2_MADD: ds_RRxx(d, "madd", insn); break;
    case SPEC2_MADDU: ds_RRxx(d, "maddu", insn); break;
    case SPEC2_MUL: ds_RRRx(d, "mul", insn); break;
    case SPEC2_MSUB: ds_RRxx(d, "msub", insn); break;
    case SPEC2_MSUBU: ds_RRxx(d, "msubu", insn); break;
    case SPEC2_CLZ: ds_RxRx(d, "clz", insn); break;
    case SPEC2_CLO: ds_RxRx(d, "clo", insn); break;
    case SPEC2_SDBBP: disprint(d, "sdbbp %u", FIELD_abcd(insn)); break;
    default: ds_ill(d, insn); break;
   }
}

void ds_getinsn(struct disasm *ds, char *buf, size_t buflen) {
   uint32_t insn, opcode;
   struct disbuf d;

   disbuf_init(&d, ds, buf, buflen);

   insn = ds_getword(ds);

   opcode = FIELD_opcode(insn);
   switch (opcode) {
    case OPC_SPECIAL: ds_special(&d, insn); break;
    case OPC_BCOND: ds_bcond(&d, insn); break;
    case OPC_J: ds_jump(&d, "j", insn); break;
    case OPC_JAL: ds_jump(&d, "jal", insn); break;
    case OPC_BEQ: ds_branch(&d, "beq", insn); break;
    case OPC_BNE: ds_branch(&d, "bne", insn); break;
    case OPC_BLEZ: ds_branch(&d, "blez", insn); break;
    case OPC_BGTZ: ds_branch(&d, "bgtz", insn); break;
    case OPC_ADDI: ds_RR_s16(&d, "addi", insn); break;
    case OPC_ADDIU: ds_RR_s16(&d, "addiu", insn); break;
    case OPC_SLTI: ds_RR_s16(&d, "slti", insn); break;
    case OPC_SLTIU: ds_RR_s16(&d, "sltiu", insn); break;
    case OPC_ANDI: ds_RR_u16(&d, "andi", insn); break;
    case OPC_ORI: ds_RR_u16(&d, "ori", insn); break;
    case OPC_XORI: ds_RR_u16(&d, "xori", insn); break;
    case OPC_LUI: snprintf(buf, buflen, "lui $%u, %u", FIELD_b(insn),
			   FIELD_cde(insn)); break;
    case OPC_COP0: ds_cop0(&d, insn); break;
    case OPC_COP1: ds_cop1(&d, insn); break;
    case OPC_COP2: ds_cop2(&d, insn); break;
    case OPC_COP3: ds_cop3(&d, insn); break;
    case OPC_BEQL: ds_branch(&d, "beql", insn); break;
    case OPC_BNEL: ds_branch(&d, "bnel", insn); break;
    case OPC_BLEZL: ds_branch(&d, "blezl", insn); break;
    case OPC_BGTZL: ds_branch(&d, "bgtzl", insn); break;
    case OPC_SPECIAL2: ds_special2(&d, insn); break;
    case OPC_LB: ds_mem(&d, "lb", insn); break;
    case OPC_LH: ds_mem(&d, "lh", insn); break;
    case OPC_LWL: ds_mem(&d, "lwl", insn); break;
    case OPC_LW: ds_mem(&d, "lw", insn); break;
    case OPC_LBU: ds_mem(&d, "lbu", insn); break;
    case OPC_LHU: ds_mem(&d, "lhu", insn); break;
    case OPC_LWR: ds_mem(&d, "lwr", insn); break;
    case OPC_SB: ds_mem(&d, "sb", insn); break;
    case OPC_SH: ds_mem(&d, "sh", insn); break;
    case OPC_SWL: ds_mem(&d, "swl", insn); break;
    case OPC_SW: ds_mem(&d, "sw", insn); break;
    case OPC_SWR: ds_mem(&d, "swr", insn); break;
    case OPC_CACHE: ds_specmem(&d, "cache", insn); break;
    case OPC_LWC0: ds_mem(&d, "ll", insn); break;
    case OPC_LWC1: ds_mem(&d, "lwc1", insn); break;
    case OPC_LWC2: ds_mem(&d, "lwc2", insn); break;
    case OPC_LWC3: ds_specmem(&d, "pref", insn); break;
    case OPC_LDC0: ds_mem(&d, "ldc0", insn); break;
    case OPC_LDC1: ds_mem(&d, "ldc1", insn); break;
    case OPC_LDC2: ds_mem(&d, "ldc2", insn); break;
    case OPC_LDC3: ds_mem(&d, "ldc3", insn); break;
    case OPC_SWC0: ds_mem(&d, "sc", insn); break;
    case OPC_SWC1: ds_mem(&d, "swc1", insn); break;
    case OPC_SWC2: ds_mem(&d, "swc2", insn); break;
    case OPC_SWC3: ds_mem(&d, "swc3", insn); break;
    case OPC_SDC0: ds_mem(&d, "sdc0", insn); break;
    case OPC_SDC1: ds_mem(&d, "sdc1", insn); break;
    case OPC_SDC2: ds_mem(&d, "sdc2", insn); break;
    case OPC_SDC3: ds_mem(&d, "sdc3", insn); break;
    default: ds_ill(&d, insn); break;
   }

   disbuf_cleanup(&d);
}
