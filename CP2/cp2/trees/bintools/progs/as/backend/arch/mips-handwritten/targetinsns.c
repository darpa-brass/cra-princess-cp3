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
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "mem.h"

#include "utils.h"
#include "targetopcode.h"
#include "expr.h"
#include "load.h"
#include "label.h"
#include "reloc.h"
#include "section.h"
#include "as.h"
#include "modeinfo.h"
#include "targetmatch.h"

/* turn this on when diffing output against gas */
//#define MATCH_GAS_EXACTLY

/* register used in some macros */
#define AT_REG	1

////////////////////////////////////////////////////////////
// crap for .reginfo data

struct reginfo {
   uint32_t r_gpregs;
   uint32_t r_copregs[4];
   uint32_t r_gp;
};

static struct reginfo myreginfo;

static void reginfo_use_gp_reg(unsigned reg) {
   assert(reg < 32);
   if (reg != 0) {
      myreginfo.r_gpregs |= (1U << reg);
   }
}

static void reginfo_use_cop_reg(unsigned cop, unsigned reg) {
   assert(cop < 4);
   assert(reg < 32);
   myreginfo.r_copregs[cop] |= (1U << reg);
}

static void reginfo_use_COP0_reg(unsigned reg) {
   reginfo_use_cop_reg(0, reg);
}
static void reginfo_use_COP1_reg(unsigned reg) {
   reginfo_use_cop_reg(1, reg);
}
static void reginfo_use_COP2_reg(unsigned reg) {
   reginfo_use_cop_reg(2, reg);
}
//static void reginfo_use_COP3_reg(unsigned reg) {
//   reginfo_use_cop_reg(3, reg);
//}

static void reginfo_use_2gp_regs(unsigned r1, unsigned r2) {
   reginfo_use_gp_reg(r1);
   reginfo_use_gp_reg(r2);
}

static void reginfo_use_3gp_regs(unsigned r1, unsigned r2, unsigned r3) {
   reginfo_use_gp_reg(r1);
   reginfo_use_gp_reg(r2);
   reginfo_use_gp_reg(r3);
}

static void reginfo_use_fp_reg(unsigned reg) {
   reginfo_use_COP1_reg(reg);
}

static void reginfo_use_2fp_regs(unsigned r1, unsigned r2) {
   reginfo_use_fp_reg(r1);
   reginfo_use_fp_reg(r2);
}

static void reginfo_use_3fp_regs(unsigned r1, unsigned r2, unsigned r3) {
   reginfo_use_fp_reg(r1);
   reginfo_use_fp_reg(r2);
   reginfo_use_fp_reg(r3);
}

////////////////////////////////////////////////////////////
// generate .reginfo

void target_generate_special_sections(void) {
#ifdef MIPS_ISSUE_REGINFO
   unsigned snum;
   unsigned char *p;
   size_t i;

   snum = getsection(".reginfo", false, true, false);

   align_section(snum, 2 /* 2^2 */);

   assert(sizeof(struct reginfo) == 24);
   p = (unsigned char *)&myreginfo;

   for (i=0; i<sizeof(myreginfo); i++) {
      section_addbyte(snum, -1, p[i]);
   }
#endif
}

////////////////////////////////////////////////////////////
// annoying helper functions

static bool isreg(struct expr *x) {
   return x->x_type == EXPR_TARGET && x->x_target.ttok == TTOK_REGISTER;
}

static int getreg(struct expr *x) {
   assert(isreg(x));
   return atoi(x->x_target.val);
}

////////////////////////////////////////////////////////////
// values/fields

static bool fits_field(u_machlarge val, enum reloc_field f) {
   switch (f) {
    case RELOC_FIELD_32: return true;
    case RELOC_FIELD_S16: return fits_s16(val); break;
    case RELOC_FIELD_U16: return fits_u16(val); break;
    case RELOC_FIELD_ANY16: return fits_any16(val); break;
    case RELOC_FIELD_BRANCH16: return fits_s16(val); break;
     /* XXX not actually used */
    case RELOC_FIELD_JUMP26: return true /*fits_jump26(val)*/; break;
   }
   assert(0);
   return 0;
}

static const char *describe_field(enum reloc_field f) {
   switch (f) {
    case RELOC_FIELD_32: return "32-bit";
    case RELOC_FIELD_S16: return "signed 16-bit";
    case RELOC_FIELD_U16: return "unsigned 16-bit";
    case RELOC_FIELD_ANY16: return "16-bit";
    case RELOC_FIELD_BRANCH16: return "16-bit branch offset";
    case RELOC_FIELD_JUMP26: return "26-bit jump target";
   }
   assert(0);
   return 0;
}

////////////////////////////////////////////////////////////
// mips instruction formats

static int in_branch_delay_slot = 0;

static void check_insn(int linenum) {
   unsigned sect = getcursection(linenum);
   unsigned alignment = 2;  /* 2^2 == 4 bytes */

   if (!section_isaligned(sect, alignment)) {
      file_warn(linenum, "Warning: Unaligned instruction");
   }

   if (in_branch_delay_slot) {
      /* XXX future: warn about instructions not allowed here? */
      in_branch_delay_slot = 0;
   }
}

/*
 * bit fields 6-5-5-16 (e.g. ADDI)
 */
static void addinsn_6_5_5_16(int linenum,
			     unsigned f1, unsigned f2,
			     unsigned f3, unsigned f4) {
   uint32_t insn;

   assert((f1 & 63) == f1);
   assert((f2 & 31) == f2);
   assert((f3 & 31) == f3);
   assert((f4 & 65535) == f4);

   check_insn(linenum);
   insn = (uint32_t)(f1 & 63) << 26;
   insn |= (uint32_t)(f2 & 31) << 21;
   insn |= (uint32_t)(f3 & 31) << 16;
   insn |= (uint32_t)(f4 & 65535);
   add32(linenum, insn);
}

/*
 * bit fields 6-5-5-5-5-6, e.g. ADD
 */
static void addinsn_6_5_5_5_5_6(int linenum,
				unsigned f1, unsigned f2,
				unsigned f3, unsigned f4,
				unsigned f5, unsigned f6) {
   uint32_t insn;

   assert((f1 & 63) == f1);
   assert((f2 & 31) == f2);
   assert((f3 & 31) == f3);
   assert((f4 & 31) == f4);
   assert((f5 & 31) == f5);
   assert((f6 & 63) == f6);

   check_insn(linenum);
   insn = (uint32_t)(f1 & 63) << 26;
   insn |= (uint32_t)(f2 & 31) << 21;
   insn |= (uint32_t)(f3 & 31) << 16;
   insn |= (uint32_t)(f4 & 31) << 11;
   insn |= (uint32_t)(f5 & 31) << 6;
   insn |= (uint32_t)(f6 & 63);
   add32(linenum, insn);
}

/*
 * bit fields 6-5-5-10-6, e.g. TEQ
 */
static void addinsn_6_5_5_10_6(int linenum,
				unsigned f1, unsigned f2,
				unsigned f3, unsigned f4,
				unsigned f6) {
   uint32_t insn;

   assert((f1 & 63) == f1);
   assert((f2 & 31) == f2);
   assert((f3 & 31) == f3);
   assert((f4 & 1023) == f4);
   assert((f6 & 63) == f6);

   check_insn(linenum);
   insn = (uint32_t)(f1 & 63) << 26;
   insn |= (uint32_t)(f2 & 31) << 21;
   insn |= (uint32_t)(f3 & 31) << 16;
   insn |= (uint32_t)(f4 & 1023) << 6;
   insn |= (uint32_t)(f6 & 63);
   add32(linenum, insn);
}

/*
 * bit fields 6-20-6, e.g. SYSCALL
 */
static void addinsn_6_20_6(int linenum,
			   unsigned f1, unsigned f2,
			   unsigned f6) {
   uint32_t insn;

   assert((f1 & 63) == f1);
   assert((f2 & 0xfffff) == f2);
   assert((f6 & 63) == f6);

   check_insn(linenum);
   insn = (uint32_t)(f1 & 63) << 26;
   insn |= (uint32_t)(f2 & 0xfffff) << 6;
   insn |= (uint32_t)(f6 & 63);
   add32(linenum, insn);
}

/*
 * bit fields 6-10-10-6, e.g. BREAK
 */
static void addinsn_6_10_10_6(int linenum,
			      unsigned f1, unsigned f2, unsigned f4,
			      unsigned f6) {
   uint32_t insn;

   assert((f1 & 63) == f1);
   assert((f2 & 0x3ff) == f2);
   assert((f4 & 0x3ff) == f4);
   assert((f6 & 63) == f6);

   check_insn(linenum);
   insn = (uint32_t)(f1 & 63) << 26;
   insn |= (uint32_t)(f2 & 0x3ff) << 16;
   insn |= (uint32_t)(f4 & 0x3ff) << 6;
   insn |= (uint32_t)(f6 & 63);
   add32(linenum, insn);
}

/*
 * bit fields 6-26, e.g. JAL
 */
static void addinsn_6_26(int linenum,
			 unsigned f1, unsigned f2) {
   uint32_t insn;

   assert((f1 & 63) == f1);
   assert((f2 & 0x3ffffff) == f2);

   check_insn(linenum);
   insn = (uint32_t)(f1 & 63) << 26;
   insn |= (uint32_t)(f2 & 0x3ffffff);
   add32(linenum, insn);
}

/*
 * SPECIAL:6 rs:5 rt:5 rd:5 -:5 op:5, e.g. ADD
 */
static void addinsn_spec_RRR(int linenum,
			     unsigned op, int rs, int rt, int rd) {
   addinsn_6_5_5_5_5_6(linenum, OPC_SPECIAL, rs, rt, rd, 0, op);
}

/*
 * SPECIAL2:6 rs:5 rt:5 rd:5 -:5 op:5, e.g. MUL
 */
static void addinsn_spec2_RRR(int linenum,
			     unsigned op, int rs, int rt, int rd) {
   addinsn_6_5_5_5_5_6(linenum, OPC_SPECIAL2, rs, rt, rd, 0, op);
}

/*
 * BCOND:6 rs:5 op:5 offset:16, e.g. BGEZAL
 */
static void addinsn_bcond_RI(int linenum,
			     unsigned op, int rs, unsigned offset) {
   addinsn_6_5_5_16(linenum, OPC_BCOND, rs, op, offset);
}

/*
 * COP1:6 fmt:5 -:5 fs:5 fd:5 op:6, e.g. ABS.D
 */
static void addinsn_cop1_RR(int linenum,
			    unsigned op, unsigned fmt, int fs, int fd) {
   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, fmt, 0, fs, fd, op);
}

/*
 * COP1:6 fmt:5 ft:5 fs:5 fd:5 op:6, e.g. ABS.D
 */
static void addinsn_cop1_RRR(int linenum,
			    unsigned op, unsigned fmt,
			    int ft, int fs, int fd) {
   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, fmt, ft, fs, fd, op);
}

/*
 * opcode:6 rs:5 rt:5 imm:16, e.g. ADDI
 */
static void addinsn_RRI(int linenum,
			unsigned op, int rs, int rt, unsigned imm) {
   addinsn_6_5_5_16(linenum, op, rs, rt, imm);
}

static void addreloc(struct reloc *r) {
   unsigned sect = getcursection(r->r_linenum);
   reloc_add(r, sect);
}

////////////////////////////////////////////////////////////
// settings

static int nest_at=0;

static void checkmacro(int linenum, const char *what) {
   if (!modeison("macro")) {
      file_warn(linenum, "Warning: macro %s with .set nomacro in effect", what);
   }
}

static void useat(int linenum) {
   if (nest_at) {
      file_err(linenum, "Internal error - recursive use of AT register");
   }
   nest_at = 1;
}

static void doneat(void) {
   assert(nest_at==1);
   nest_at = 0;
}

static void checkat(int linenum, const char *what) {
   if (!modeison("at")) {
      file_warn(linenum, "Warning: macro %s with .set noat in effect", what);
   }
   useat(linenum);
}

static void branch_delay_slot(int linenum) {
   if (modeison("reorder")) {
      /*
       * We could check if the instruction before the branch can be
       * moved into the delay slot. The original MIPS assembler did
       * this quite aggressively. The GNU as doesn't, though, so
       * nobody expects it and in particular compiler output deals
       * with delay slots itself, so we don't need to bother. Always
       * issue a nop.
       */
      insn_nop_(linenum);
   }
   else {
      in_branch_delay_slot = 1;
   }
}

////////////////////////////////////////////////////////////
// expressions and relocations

/*
 * Munge expression X for insertion into a field of type F at offset
 * OFFSET from the current section end. (Not the offset from the
 * section start; that's added in implicitly.) Return the value to
 * insert into the section (often 0) after adding any/all needed
 * relocations. The value is range-checked.
 *
 * Because this is called before anything is added to the section, the
 * offset should be 0 if the field to be used is in the first byte of
 * what's added. In particular, for the 16-bit immediate field of MIPS
 * instructions, which is in the low-order 16 bits of an instruction
 * word, the offset should be either 2 (if big-endian) or 0 (if
 * little-endian). The macro IMM_OFFSET provides this value.
 */
static u_machlarge process_expr(int linenum, struct expr *x,
			 enum reloc_field f, unsigned offset) {
   u_machlarge val;
   struct reloc *r;

   r = compile_expr(linenum, x, &val);
   if (r) {
      r->r_field = f;
      r->r_offset = section_getsize(getcursection(linenum)) + offset;
      addreloc(r);
   }
   if (!fits_field(val, f)) {
      file_err(linenum, "Immediate value out of range: 0x%llx in %s field",
	       (unsigned long long)val, describe_field(f));
   }
   return val;
}

u_machword process_expr_word(int linenum, struct expr *x, unsigned offset) {
   return process_expr(linenum, x, RELOC_FIELD_32, offset);
}

u_machword process_expr_hword(int linenum, struct expr *x, unsigned offset) {
   return process_expr(linenum, x, RELOC_FIELD_ANY16, offset);
}

#if TARGET_ENDIANNESS == MY_BIG_ENDIAN
#define IMM_OFFSET	2
#else
#define IMM_OFFSET	0
#endif

static struct expr *mkexpr_lo(struct expr *sub) {
   return mkexpr_operator("lo", sub);
}

static struct expr *mkexpr_hi(struct expr *sub) {
   return mkexpr_operator("hi", sub);
}

////////////////////////////////////////////////////////////
// branch instruction support

static u_machlarge process_branch_target(int linenum, struct label *target) {
   struct label *here;
   struct expr *here_expr, *target_expr, *minusfour;
   struct expr *basedistance, *distance, *count;

   here = label_declaredot(linenum);

   /*
    * Since the instruction hasn't been added yet, . at this point is
    * the address of the branch instruction. But we need the address of
    * the delay slot, so we need to add 4.
    *
    * Thus the expression we want is
    *    (target - (. + 4))/4
    *
    * But because (for now at least) pcomp.c is very restricted in
    * what it can cope with, instead issue
    *    ((target - .) + (-4))/4
    *
    * and issue the /4 not as /4 or >>2 but as a machine-dependent
    * reloc operator "branchoffset".
    */

   here_expr = mkexpr_label(here);
   target_expr = mkexpr_label(target);
   minusfour = mkexpr_number(-4);

   basedistance = mkexpr_binary(target_expr, TOK_MINUS, here_expr);
   distance = mkexpr_binary(basedistance, TOK_PLUS, minusfour);
   count = mkexpr_operator("branchoffset", distance);

   return process_expr(linenum, count, RELOC_FIELD_BRANCH16, IMM_OFFSET);
}

#define LIKELY file_warn(linenum, "Branch-likely instruction");

////////////////////////////////////////////////////////////
// instructions

/*
 * 1. Basic three-operand instructions using the spec_RRR format.
 *
 * (note: this is the point where the source form ADD rd, rs, rt gets
 * reordered to the binary field ordering rs-rt-rd)
 */

#define OP_RRR(OP, op) \
  void insn_##op##_rrr(int linenum, int rd, int rs, int rt) {	\
     addinsn_spec_RRR(linenum, SPEC_##OP, rs, rt, rd);		\
     reginfo_use_3gp_regs(rs, rt, rd);				\
  }
#define OP_RRR2(OP, op) \
  void insn_##op##_rrr(int linenum, int rd, int rs, int rt) {	\
     addinsn_spec2_RRR(linenum, SPEC2_##OP, rs, rt, rd);	\
     reginfo_use_3gp_regs(rs, rt, rd);				\
  }

OP_RRR(ADD, add);
OP_RRR(ADDU, addu);
OP_RRR(AND, and);
OP_RRR(MOVN, movn)
OP_RRR(MOVZ, movz)
OP_RRR2(MUL, mul);
OP_RRR(NOR, nor)
OP_RRR(OR, or);
OP_RRR(SLT, slt);
OP_RRR(SLTU, sltu);
OP_RRR(SUB, sub);
OP_RRR(SUBU, subu);
OP_RRR(XOR, xor);

void insn_neg_rr(int linenum, int rd, int rt) {
   insn_sub_rrr(linenum, rd, 0, rt);
}

void insn_neg_r(int linenum, int rd) {
   insn_neg_rr(linenum, rd, rd);
}

void insn_negu_rr(int linenum, int rd, int rt) {
   insn_subu_rrr(linenum, rd, 0, rt);
}

void insn_negu_r(int linenum, int rd) {
   insn_negu_rr(linenum, rd, rd);
}

void insn_not_rr(int linenum, int rd, int rs) {
   checkmacro(linenum, "not");
   insn_nor_rrr(linenum, rd, rs, 0);
}

void insn_not_r(int linenum, int rd) {
   checkmacro(linenum, "not");
   insn_not_rr(linenum, rd, rd);
}

void insn_abs_rr(int linenum, int rd, int rs) {
   checkmacro(linenum, "abs");
   checkat(linenum, "abs");
#ifdef MATCH_GAS_EXACTLY
   /*
    * gas emits a 3-instruction branching macro for abs; the
    * 3-instruction nonbranching one used below by default is clearly
    * superior.
    */
   /* bgez rs, 2 */
   addinsn_bcond_RI(linenum, BCOND_BGEZ, rs, 2);
   reginfo_use_gp_reg(rs);
   if (rd != rs) {
      insn_move_rr(linenum, rd, rs); /* in delay slot */
      insn_neg_rr(linenum, rd, rs);
   }
   else {
      insn_nop_(linenum); /* in delay slot */
      insn_neg_r(linenum, rd);
   }
#else
   insn_sra_rrn(linenum, AT_REG, rs, 31);
   insn_xor_rrr(linenum, rd, rs, AT_REG);
   insn_sub_rrr(linenum, rd, rd, AT_REG);
#endif
   doneat();
}

void insn_abs_r(int linenum, int rd) {
   insn_abs_rr(linenum, rd, rd);
}

/*
 * related macros
 */

void insn_seq_rrr(int linenum, int rd, int rs, int rt) {
   /* rs == rt -> (rs ^ rt) == 0 -> (rs ^ rt) <_u 1 */
   checkmacro(linenum, "seq");
   insn_xor_rrr(linenum, rd, rs, rt);
   insn_sltu_rrn(linenum, rd, rd, 1);
}

void insn_sne_rrr(int linenum, int rd, int rs, int rt) {
   /* rs != rt -> (rs ^ rt) != 0 -> (rs ^ rt) >_u 0 -> 0 <_u (rs ^ rt) */
   checkmacro(linenum, "sne");
   insn_xor_rrr(linenum, rd, rs, rt);
   insn_sltu_rrr(linenum, rd, 0, rd);
}

void insn_sgt_rrr(int linenum, int rd, int rs, int rt) {
   /* rs > rt -> rt < rs */
   insn_slt_rrr(linenum, rd, rt, rs);
}

void insn_sgtu_rrr(int linenum, int rd, int rs, int rt) {
   /* rs > rt -> rt < rs */
   insn_sltu_rrr(linenum, rd, rt, rs);
}

void insn_sge_rrr(int linenum, int rd, int rs, int rt) {
   /* rs >= rt -> !(rs < rt) -> (rs < rt) ^ 1 */
   insn_slt_rrr(linenum, rd, rs, rt);
   insn_xor_rrn(linenum, rd, rd, 1);
}

void insn_sgeu_rrr(int linenum, int rd, int rs, int rt) {
   /* rs >= rt -> !(rs < rt) -> (rs < rt) ^ 1 */
   insn_sltu_rrr(linenum, rd, rs, rt);
   insn_xor_rrn(linenum, rd, rd, 1);
}

void insn_sle_rrr(int linenum, int rd, int rs, int rt) {
   /* rs <= rt -> !(rs > rt) -> !(rt < rs) -> (rt < rs) ^ 1 */
   insn_slt_rrr(linenum, rd, rt, rs);
   insn_xor_rrn(linenum, rd, rd, 1);
}

void insn_sleu_rrr(int linenum, int rd, int rs, int rt) {
   /* rs <= rt -> !(rs > rt) -> !(rt < rs) */
   insn_sltu_rrr(linenum, rd, rt, rs);
   insn_xor_rrn(linenum, rd, rd, 1);
}

/*
 * For some reason the rs/rt fields of the shift instructions are
 * flipped.
 */
#define OP_RRRshift(OP, op, op2) \
  void insn_##op##_rrr(int linenum, int rd, int rt, int rs) {	\
     addinsn_spec_RRR(linenum, SPEC_##OP, rs, rt, rd);		\
     reginfo_use_3gp_regs(rs, rt, rd);				\
  }								\
  void insn_##op2##_rrr(int linenum, int rd, int rt, int rs) {	\
     addinsn_spec_RRR(linenum, SPEC_##OP, rs, rt, rd);		\
     reginfo_use_3gp_regs(rs, rt, rd);				\
  }

OP_RRRshift(SLLV, sllv, sll);
OP_RRRshift(SRAV, srav, sra);
OP_RRRshift(SRLV, srlv, srl);

/* rotate macros */
#define OP_rotate(op, same, other) \
   void insn_##op##_rrr(int linenum, int rd, int rt, int rs) {	\
      checkmacro(linenum, #op);					\
      checkat(linenum, #op);					\
      insn_negu_rr(linenum, AT_REG, rs);			\
      insn_##other##_rrr(linenum, AT_REG, rt, AT_REG);		\
      insn_##same##_rrr(linenum, rd, rt, rs);			\
      insn_or_rrr(linenum, rd, rd, AT_REG);			\
      doneat();							\
   }								\
   void insn_##op##_rrn(int linenum, int rd, int rt, u_machlarge shift) { \
      checkmacro(linenum, #op);					\
      checkat(linenum, #op);					\
      insn_##same##_rrn(linenum, AT_REG, rt, shift);		\
      insn_##other##_rrn(linenum, rd, rt, (-shift)&31);		\
      insn_or_rrr(linenum, rd, rd, AT_REG);			\
      doneat();							\
   }

OP_rotate(rol, sll, srl);
OP_rotate(ror, srl, sll);

/*
 * 1a. Likewise but where rd is 0
 */
#define OP_RR(op, OP) \
   void insn_##op##_rr(int linenum, int rs, int rt) {		\
      addinsn_spec_RRR(linenum, SPEC_##OP, rs, rt, 0);		\
      reginfo_use_2gp_regs(rs, rt);				\
   }

#define OP_RR2(op, OP) \
   void insn_##op##_rr(int linenum, int rs, int rt) {		\
      addinsn_spec2_RRR(linenum, SPEC2_##OP, rs, rt, 0);	\
      reginfo_use_2gp_regs(rs, rt);				\
   }

OP_RR2(madd, MADD);
OP_RR2(maddu, MADDU);
OP_RR2(msub, MSUB);
OP_RR2(msubu, MSUBU);
OP_RR(mult, MULT);
OP_RR(multu, MULTU);

/*
 * The raw divide instructions are the same but are only accessible as
 * a special case of the macros.
 */
#define OP_RRdiv(op, OP) \
   static void insn_##op##_raw(int linenum, int rs, int rt) {	\
      addinsn_spec_RRR(linenum, SPEC_##OP, rs, rt, 0);		\
      reginfo_use_2gp_regs(rs, rt);				\
   }

OP_RRdiv(div, DIV);
OP_RRdiv(divu, DIVU);

/*
 * 1b. Likewise but where rt == rd (required for CLO/CLZ for some reason)
 */
#define OP_RR2a(op, OP) \
   void insn_##op##_rr(int linenum, int rd, int rs) {		\
      addinsn_spec2_RRR(linenum, SPEC2_##OP, rs, rd, rd);	\
      reginfo_use_2gp_regs(rd, rs);				\
   }
OP_RR2a(clo, CLO);
OP_RR2a(clz, CLZ);

/*
 * 1c. Where rs == rd (2-operand versions of 3-operand instructions)
 */
#define OP_RRb(op, OP) \
   void insn_##op##_rr(int linenum, int rd, int rt) {		\
      addinsn_spec_RRR(linenum, SPEC_##OP, rd, rt, rd);		\
      reginfo_use_2gp_regs(rd, rt);				\
   }

OP_RRb(add, ADD);
OP_RRb(addu, ADDU);
OP_RRb(and, AND);
OP_RRb(nor, NOR);
OP_RRb(or, OR);
OP_RRb(slt, SLT);
OP_RRb(sltu, SLTU);
OP_RRb(sub, SUB);
OP_RRb(subu, SUBU);
OP_RRb(xor, XOR);

void insn_seq_rr(int linenum, int rd, int rt) {
   insn_seq_rrr(linenum, rd, rd, rt);
}

void insn_sne_rr(int linenum, int rd, int rt) {
   insn_sne_rrr(linenum, rd, rd, rt);
}

void insn_sgt_rr(int linenum, int rd, int rt) {
   insn_sgt_rrr(linenum, rd, rd, rt);
}

void insn_sgtu_rr(int linenum, int rd, int rt) {
   insn_sgtu_rrr(linenum, rd, rd, rt);
}

void insn_sge_rr(int linenum, int rd, int rt) {
   insn_sge_rrr(linenum, rd, rd, rt);
}

void insn_sgeu_rr(int linenum, int rd, int rt) {
   insn_sgeu_rrr(linenum, rd, rd, rt);
}

void insn_sle_rr(int linenum, int rd, int rt) {
   insn_sle_rrr(linenum, rd, rd, rt);
}

void insn_sleu_rr(int linenum, int rd, int rt) {
   insn_sleu_rrr(linenum, rd, rd, rt);
}

/*
 * 2. Three-operand immediate instructions using the RRI format.
 *
 * (note: this is the point where the source form ADDI rt, rs, imm gets
 * reordered to the binary field ordering rs-rt-imm)
 *
 * Also, if there's an immediate and the 'i' is left off the
 * instruction name, we're supposed to infer it.
 */

#define OP_RRI(OP, op, op2, FIELD) \
  void insn_##op##_rrx(int linenum, int rt, int rs, struct expr *imm) {	\
     u_machlarge val;							\
     val = process_expr(linenum, imm, RELOC_FIELD_##FIELD, IMM_OFFSET); \
     addinsn_RRI(linenum, OPC_##OP, rs, rt, val & 0xffff);		\
     reginfo_use_2gp_regs(rt, rs);					\
  }									\
  void insn_##op2##_rrn(int linenum, int rt, int rs, u_machlarge imm) {	\
     if (!fits_field(imm, RELOC_FIELD_##FIELD)) {			\
        checkmacro(linenum, #op);					\
        checkat(linenum, #op);						\
	insn_li_rn(linenum, AT_REG, imm);				\
	insn_##op2##_rrr(linenum, rt, rs, AT_REG);			\
        doneat();							\
     }									\
     else {								\
	addinsn_RRI(linenum, OPC_##OP, rs, rt, imm & 0xffff);		\
        reginfo_use_2gp_regs(rt, rs);					\
     }									\
  }

OP_RRI(ADDI, addi, add, S16);
OP_RRI(ADDIU, addiu, addu, S16);
OP_RRI(ANDI, andi, and, U16);
OP_RRI(ORI, ori, or, U16);
OP_RRI(SLTI, slti, slt, S16);
OP_RRI(SLTIU, sltiu, sltu, S16);
OP_RRI(XORI, xori, xor, U16);

/*
 * These look like the above but are only macros.
 */

#define OP_RRI_sub(op, op2, FIELD, altop2) \
  void insn_##op2##_rrn(int linenum, int rt, int rs, u_machlarge imm) {	\
     if (fits_field(-imm, RELOC_FIELD_##FIELD)) {			\
	imm = -imm;							\
        insn_##altop2##_rrn(linenum, rt, rs, imm);			\
     }									\
     else {								\
        checkmacro(linenum, #op);					\
        checkat(linenum, #op);						\
	insn_li_rn(linenum, AT_REG, imm);				\
        insn_##op2##_rrr(linenum, rt, rs, AT_REG);			\
        doneat();							\
     }									\
  }									\
  void insn_##op##_rrx(int linenum, int rt, int rs, struct expr *imm) {	\
     if (imm->x_type == EXPR_NUM) {					\
        insn_##op2##_rrn(linenum, rt, rs, imm->x_num);			\
     }									\
     else {								\
        checkmacro(linenum, #op);					\
        checkat(linenum, #op);						\
        insn_addiu_rrx(linenum, AT_REG, 0, imm);			\
        insn_##op2##_rrr(linenum, rt, rs, AT_REG);			\
        doneat();							\
     }									\
  }

OP_RRI_sub(subi, sub, S16, add);
OP_RRI_sub(subiu, subu, S16, addu);

void insn_nori_rrx(int linenum, int rt, int rs, struct expr *imm) {
   checkmacro(linenum, "nori");
   checkat(linenum, "nori");
   if (imm->x_type == EXPR_NUM) {
      insn_li_rn(linenum, AT_REG, imm->x_num);
   }
   else {
      insn_addiu_rrx(linenum, AT_REG, 0, imm);
   }
   insn_nor_rrr(linenum, rt, rs, AT_REG);
   doneat();
}

void insn_nor_rrn(int linenum, int rt, int rs, u_machlarge imm) {
   if (fits_u16(imm)) {
      insn_or_rrn(linenum, rt, rs, imm);
      insn_not_r(linenum, rt);
   }
   else {
      checkmacro(linenum, "nor");
      checkat(linenum, "nor");
      insn_li_rn(linenum, AT_REG, imm);
      insn_nor_rrr(linenum, rt, rs, AT_REG);
      doneat();
   }
}

void insn_seqi_rrx(int linenum, int rt, int rs, struct expr *imm) {
   /* rs == imm -> (rs ^ imm) == 0 -> (rs ^ imm) <_u 1 */
   checkmacro(linenum, "seqi");
   insn_xori_rrx(linenum, rt, rs, imm);
   insn_sltu_rrn(linenum, rt, rt, 1);
}

void insn_seq_rrn(int linenum, int rt, int rs, u_machlarge imm) {
   /*
    * rs == imm -> (rs ^ imm) == 0 -> (rs ^ imm) <_u 1
    * ...except if -imm fits s16 but imm doesn't fit u16; then we do
    *    (rs - imm) == 0 -> (rs + (-imm)) <_u 1
    */
   checkmacro(linenum, "seq");
   if (!fits_u16(imm) && fits_s16(-imm)) {
      insn_addu_rrn(linenum, rt, rs, -imm);
   }
   else {
      insn_xor_rrn(linenum, rt, rs, imm);
   }
   insn_sltu_rrn(linenum, rt, rt, 1);
}

void insn_snei_rrx(int linenum, int rt, int rs, struct expr *imm) {
   /* rs != imm -> (rs ^ imm) != 0 -> (rs ^ imm) >_u 0 -> 0 <_u (rs ^ imm) */
   checkmacro(linenum, "snei");
   insn_xori_rrx(linenum, rt, rs, imm);
   insn_sltu_rrr(linenum, rt, 0, rt);
}

void insn_sne_rrn(int linenum, int rt, int rs, u_machlarge imm) {
   /*
    * rs != imm -> (rs ^ imm) != 0 -> (rs ^ imm) >_u 0 -> 0 <_u (rs ^ imm)
    * ...except if -imm fits s16 but imm doesn't fit u16; then we do
    *    (rs - imm) != 0 -> 0 <_u (rs + (-imm))
    */
   checkmacro(linenum, "snei");
   if (!fits_u16(imm) && fits_s16(-imm)) {
      insn_addu_rrn(linenum, rt, rs, -imm);
   }
   else {
      insn_xor_rrn(linenum, rt, rs, imm);
   }
   insn_sltu_rrr(linenum, rt, 0, rt);
}

void insn_sgti_rrx(int linenum, int rt, int rs, struct expr *imm) {
   /* rs > imm -> imm < rs, but we have to use $AT for that */
   checkmacro(linenum, "sgti");
   checkat(linenum, "sgti");
   insn_addiu_rrx(linenum, AT_REG, 0, imm);
   insn_slt_rrr(linenum, rt, AT_REG, rs);
   doneat();
}

void insn_sgt_rrn(int linenum, int rt, int rs, u_machlarge imm) {
   /* rs > imm -> imm < rs, but we have to use $AT for that */
   checkmacro(linenum, "sgt");
   checkat(linenum, "sgt");
   insn_li_rn(linenum, AT_REG, imm);
   insn_slt_rrr(linenum, rt, AT_REG, rs);
   doneat();
}

void insn_sgtiu_rrx(int linenum, int rt, int rs, struct expr *imm) {
   /* rs > imm -> imm < rs, but we have to use $AT for that */
   checkmacro(linenum, "sgtiu");
   checkat(linenum, "sgtiu");
   insn_addiu_rrx(linenum, AT_REG, 0, imm);
   insn_sltu_rrr(linenum, rt, AT_REG, rs);
   doneat();
}

void insn_sgtu_rrn(int linenum, int rt, int rs, u_machlarge imm) {
   /* rs > imm -> imm < rs, but we have to use $AT for that */
   checkmacro(linenum, "sgtu");
   checkat(linenum, "sgtu");
   insn_li_rn(linenum, AT_REG, imm);
   insn_sltu_rrr(linenum, rt, AT_REG, rs);
   doneat();
}

void insn_sgei_rrx(int linenum, int rt, int rs, struct expr *imm) {
   /* rs >= imm -> !(rs < imm) -> (rs < imm) ^ 1 */
   checkmacro(linenum, "sgei");
   insn_slti_rrx(linenum, rt, rs, imm);
   insn_xor_rrn(linenum, rt, rt, 1);
}

void insn_sge_rrn(int linenum, int rt, int rs, u_machlarge imm) {
   /* rs >= imm -> !(rs < imm) -> (rs < imm) ^ 1 */
   checkmacro(linenum, "sge");
   insn_slt_rrn(linenum, rt, rs, imm);
   insn_xor_rrn(linenum, rt, rt, 1);
}

void insn_sgeiu_rrx(int linenum, int rt, int rs, struct expr *imm) {
   /* rs >= imm -> !(rs < imm) -> (rs < imm) ^ 1 */
   checkmacro(linenum, "sgeiu");
   insn_sltiu_rrx(linenum, rt, rs, imm);
   insn_xor_rrn(linenum, rt, rt, 1);
}

void insn_sgeu_rrn(int linenum, int rt, int rs, u_machlarge imm) {
   /* rs >= imm -> !(rs < imm) -> (rs < imm) ^ 1 */
   checkmacro(linenum, "sgeu");
   insn_sltu_rrn(linenum, rt, rs, imm);
   insn_xor_rrn(linenum, rt, rt, 1);
}

void insn_slei_rrx(int linenum, int rt, int rs, struct expr *imm) {
   /* rs <= imm -> !(rs > imm) -> !(imm < rs), but that needs $AT */
   checkmacro(linenum, "slei");
   insn_sgti_rrx(linenum, rt, rs, imm);
   insn_xor_rrn(linenum, rt, rt, 1);
}

void insn_sle_rrn(int linenum, int rt, int rs, u_machlarge imm) {
   /* rs <= imm -> !(rs > imm) -> !(imm < rs), but that needs $AT */
   checkmacro(linenum, "sle");
   insn_sgt_rrn(linenum, rt, rs, imm);
   insn_xor_rrn(linenum, rt, rt, 1);
}

void insn_sleiu_rrx(int linenum, int rt, int rs, struct expr *imm) {
   /* rs <= imm -> !(rs > imm) -> !(imm < rs), but that needs $AT */
   checkmacro(linenum, "sleiu");
   insn_sgtiu_rrx(linenum, rt, rs, imm);
   insn_xor_rrn(linenum, rt, rt, 1);
}

void insn_sleu_rrn(int linenum, int rt, int rs, u_machlarge imm) {
   /* rs <= imm -> !(rs > imm) -> !(imm < rs), but that needs $AT */
   checkmacro(linenum, "sleu");
   insn_sgtu_rrn(linenum, rt, rs, imm);
   insn_xor_rrn(linenum, rt, rt, 1);
}

/*
 * Constant shift instructions
 */
#define OP_SHIFT(op, OP) \
   void insn_##op##_rrn(int linenum, int rd, int rt, u_machlarge shift) { \
      addinsn_6_5_5_5_5_6(linenum, OPC_SPECIAL, 0, rt, rd, shift, SPEC_##OP); \
      reginfo_use_2gp_regs(rd, rt);					\
   }

OP_SHIFT(sll, SLL);
OP_SHIFT(sra, SRA);
OP_SHIFT(srl, SRL);

/*
 * 3. Branch instructions that also use the RRI format.
 * (note: same argument reordering as 2.)
 */
#define OP_RRI_branch(op, OP, LIKELY) \
   void insn_##op##_rrs(int linenum, int rs, int rt, struct label *target) { \
     u_machlarge imm;						\
     imm = process_branch_target(linenum, target);		\
     LIKELY;							\
     addinsn_RRI(linenum, OPC_##OP, rs, rt, imm);		\
     reginfo_use_gp_reg(rs);					\
     reginfo_use_gp_reg(rt);					\
     branch_delay_slot(linenum);				\
   }

OP_RRI_branch(beq, BEQ, );
OP_RRI_branch(beql, BEQL, LIKELY);
OP_RRI_branch(bne, BNE, );
OP_RRI_branch(bnel, BNEL, LIKELY);

/*
 * Raw bne used by the div/divu macros. The offset is dropped directly
 * into the branch offset field; it's counted in instructions (not bytes)
 * and it's relative to the location of the delay slot.
 *
 * This function does *NOT* fill the branch delay slot, regardless of
 * reorder mode.
 */
static void insn_bne_raw(int linenum, int rt, int rs, s_machword offset) {
   addinsn_RRI(linenum, OPC_BNE, rs, rt, offset);
   reginfo_use_gp_reg(rs);
   reginfo_use_gp_reg(rt);
}

/*
 * 3a. Branch instructions that use the RRI format with rt = 0.
 */
#define OP_RI_branch(op, OP, LIKELY) \
   void insn_##op##_rs(int linenum, int rs, struct label *offset) {	\
     u_machlarge imm;						\
     imm = process_branch_target(linenum, offset);		\
     LIKELY;							\
     addinsn_RRI(linenum, OPC_##OP, rs, 0, imm);		\
     reginfo_use_gp_reg(rs);					\
     branch_delay_slot(linenum);				\
   }

OP_RI_branch(bgtz, BGTZ, );
OP_RI_branch(bgtzl, BGTZL, LIKELY);
OP_RI_branch(blez, BLEZ, );
OP_RI_branch(blezl, BLEZL, LIKELY);

/*
 * 4. Branch instructions using the bcond_RI format
 */
#define OP_RRI_bcond(op, OP, LIKELY) \
   void insn_##op##_rs(int linenum, int rs, struct label *offset) {	\
     u_machlarge imm;						\
     imm = process_branch_target(linenum, offset);		\
     LIKELY;							\
     addinsn_bcond_RI(linenum, BCOND_##OP, rs, imm);		\
     reginfo_use_gp_reg(rs);					\
     branch_delay_slot(linenum);				\
   }

OP_RRI_bcond(bgez, BGEZ, );
OP_RRI_bcond(bgezl, BGEZL, LIKELY);
OP_RRI_bcond(bgezal, BGEZAL, );
OP_RRI_bcond(bgezall, BGEZALL, LIKELY);
OP_RRI_bcond(bltz, BLTZ, );
OP_RRI_bcond(bltzl, BLTZL, LIKELY);
OP_RRI_bcond(bltzal, BLTZAL, );
OP_RRI_bcond(bltzall, BLTZALL, LIKELY);

/*
 * Conditional traps using the bcond_RI format; except note that
 * the immediate is the value for the test condition and *not* a
 * branch offset.
 *
 * Like with e.g. slti, if the i is left off we're supposed to infer
 * it.
 */
#define OP_CTRAP_bcond(op, op2, OP) \
   void insn_##op##_rx(int linenum, int rs, struct expr *imm) {	\
      u_machlarge val;						\
      val = process_expr(linenum, imm, RELOC_FIELD_S16, IMM_OFFSET); \
      addinsn_bcond_RI(linenum, BCOND_##OP, rs, val);		\
      reginfo_use_gp_reg(rs);					\
   }								\
   void insn_##op2##_rx(int linenum, int rs, struct expr *imm) {	\
      insn_##op##_rx(linenum, rs, imm);				\
   }

OP_CTRAP_bcond(teqi, teq, TEQI);
OP_CTRAP_bcond(tgei, tge, TGEI);
OP_CTRAP_bcond(tgeiu, tgeu, TGEIU);
OP_CTRAP_bcond(tlti, tlt, TLTI);
OP_CTRAP_bcond(tltiu, tltu, TLTIU);
OP_CTRAP_bcond(tnei, tne, TNEI);


/*
 * divide macros (that use conditional traps and/or branch instructions)
 */

void insn_div_rrr(int linenum, int rd, int rs, int rt) {
   if (rd == 0) {
      insn_div_raw(linenum, rs, rt);
      return;
   }

   /*
    * The full macro for signed divide is:
    *    bne rt, $0, 1f
    *      raw_div rs, rt	(in delay slot)
    *    break 7		(divide by zero trap)
    *  1:
    *    li $AT, -1
    *    bne $AT, rt, 2f
    *      nop			(delay slot)
    *    lui $AT, 0x8000
    *    bne $AT, rs, 2f
    *      nop			(delay slot)
    *    break 6		(integer overflow trap);
    *  2:
    *    mflo rd
    *
    * That is, first it checks for division by zero, and then it
    * checks for 0x80000000 / -1, which isn't representable.
    *
    * Much as the branches are annoying, I can't think of a better
    * expansion, especially since we can't destroy rd as rd == rs or
    * rd == rt is possible.
    *
    * XXX: when the architecture-revision mode says conditional traps
    * can be used, this should use them.
    */

   checkmacro(linenum, "div");
   checkat(linenum, "div");
   insn_bne_raw(linenum, 0, rt, 2 /* skip 1 insn after delay slot */);
   insn_div_raw(linenum, rs, rt);	/* in delay slot of bne */
   insn_break_n(linenum, 7);		/* divide by zero trap */
   insn_li_rn(linenum, AT_REG, -1);
#ifdef MATCH_GAS_EXACTLY
   insn_bne_raw(linenum, AT_REG, rt, 4 /* skip 3 insns */);
#else
   insn_bne_raw(linenum, AT_REG, rt, 5 /* skip 4 insns */);
   insn_nop_(linenum);			/* delay slot */
#endif
   insn_li_rn(linenum, AT_REG, 0x80000000);
   insn_bne_raw(linenum, AT_REG, rs, 2 /* skip 1 insn */);
   insn_nop_(linenum);			/* delay slot */
   insn_break_n(linenum, 6);		/* integer overflow trap */
   insn_mflo_r(linenum, rd);
   doneat();
}

void insn_divu_rrr(int linenum, int rd, int rs, int rt) {
   if (rd == 0) {
      insn_divu_raw(linenum, rs, rt);
      return;
   }

   /*
    * Unsigned divide is like signed divide (except for using the divu
    * raw instrction instead of div) but doesn't have the overflow
    * test.
    */

   checkmacro(linenum, "divu");
   checkat(linenum, "divu");
   insn_bne_raw(linenum, 0, rt, 2 /* skip 1 insn after delay slot */);
   insn_divu_raw(linenum, rs, rt);	/* in delay slot of bne */
   insn_break_n(linenum, 7);		/* divide by zero trap */
   insn_mflo_r(linenum, rd);
   doneat();
}

void insn_div_rr(int linenum, int rd, int rt) {
   insn_div_rrr(linenum, rd, rd, rt);
}

void insn_divu_rr(int linenum, int rd, int rt) {
   insn_divu_rrr(linenum, rd, rd, rt);
}


/*
 * Memory instructions that use the RRI format (which is all of them)
 */

/*
 * Base form of memory instructions: op reg, offset(reg)
 */
#define OP_RRI_regoffset(op, OP, RGI) \
   static void insn_##op##_regoffset(int line, int rt, struct expr *offset, int rs) {\
      u_machlarge offsetval;					\
								\
      offsetval = process_expr(line, offset, RELOC_FIELD_S16, IMM_OFFSET); \
      addinsn_RRI(line, OP, rs, rt, offsetval);			\
      reginfo_use_##RGI##_reg(rt);				\
      reginfo_use_gp_reg(rs);					\
   }								\
   void insn_##op##_rx(int linenum, int rt, struct expr *addr) {	\
      struct expr *offset, *reg;					\
								\
      if (addr->x_type == EXPR_BINARY && !strcmp(addr->x_strop, "")) { \
	 offset = addr->x_arg1;					\
	 reg = addr->x_arg2;					\
         /* reg is supposed to be in parentheses */		\
         if (reg->x_type == EXPR_UNARY && reg->x_tokop == TOK_LPAREN) { \
	    reg = reg->x_arg1;					\
	    if (isreg(reg)) {					\
	       insn_##op##_regoffset(linenum, rt, offset, getreg(reg)); \
	       return;						\
	    }							\
	 }							\
      }								\
      file_err(linenum, "Unknown/invalid addressing mode");	\
   }

/*
 * load rt, sym  =>  lui rt, %hi(sym); load rt, %lo(sym)(rt)
 */
#define OP_RRI_loadsym(op) \
   void insn_##op##_rs(int linenum, int rt, struct label *sym) {	\
      struct expr *hi, *lo;						\
								\
      checkmacro(linenum, #op);					\
      hi = mkexpr_hi(mkexpr_label(sym));			\
      lo = mkexpr_lo(mkexpr_label(sym));				\
      insn_lui_rx(linenum, rt, hi);				\
      insn_##op##_regoffset(linenum, rt, lo, rt);		\
   }

/*
 * store rt, sym  =>  lui AT, %hi(sym); store rt, %lo(sym)(AT)
 */
#define OP_RRI_storesym(op) \
   void insn_##op##_rs(int linenum, int rt, struct label *sym) {	\
      struct expr *hi, *lo;						\
								\
      checkmacro(linenum, #op);					\
      checkat(linenum, #op);					\
      hi = mkexpr_hi(mkexpr_label(sym));			\
      lo = mkexpr_lo(mkexpr_label(sym));			\
      insn_lui_rx(linenum, AT_REG, hi);				\
      insn_##op##_regoffset(linenum, rt, lo, AT_REG);		\
      doneat();							\
   }

#define OP_RRI_load(op, OP, RGI) \
   OP_RRI_regoffset(op, OPC_##OP, RGI); OP_RRI_loadsym(op)

#define OP_RRI_store(op, OP, RGI) \
   OP_RRI_regoffset(op, OPC_##OP, RGI); OP_RRI_storesym(op)

OP_RRI_load(lb, LB, gp);
OP_RRI_load(lbu, LBU, gp);
OP_RRI_load(ldc1, LDC1, COP1);
OP_RRI_load(ldc2, LDC2, COP2);
OP_RRI_load(lh, LH, gp);
OP_RRI_load(lhu, LHU, gp);
OP_RRI_load(ll, LWC0, gp);	/* LL is encoded as LWC0 */
OP_RRI_load(lw, LW, gp);
OP_RRI_load(lwc1, LWC1, COP1);
OP_RRI_load(lwc2, LWC2, COP2);
OP_RRI_load(lwl, LWL, gp);
OP_RRI_load(lwr, LWR, gp);
OP_RRI_store(sb, SB, gp);
OP_RRI_store(sc, SWC0, gp);	/* SC is encoded as SWC0 */
OP_RRI_store(sdc1, SDC1, COP1);
OP_RRI_store(sdc2, SDC2, COP2);
OP_RRI_store(sh, SH, gp);
OP_RRI_store(sw, SW, gp);
OP_RRI_store(swc1, SWC1, COP1);
OP_RRI_store(swc2, SWC2, COP2);
OP_RRI_store(swl, SWL, gp);
OP_RRI_store(swr, SWR, gp);

#define OP_unaligned(op, ls) \
   static void insn_u##ls##w_common(int linenum, int rt) {		\
      struct expr *e0, *e3;						\
									\
      e0 = mkexpr_number(0);						\
      e3 = mkexpr_number(3);						\
									\
      insn_##ls##wl_regoffset(linenum, rt, e0, AT_REG);			\
      insn_##ls##wr_regoffset(linenum, rt, e3, AT_REG);			\
									\
      expr_destroy(e0);							\
      expr_destroy(e3);							\
   }									\
   void insn_u##ls##w_rs(int linenum, int rt, struct label *sym) {	\
      checkmacro(linenum, #op);						\
      checkat(linenum, #op);						\
      insn_la_rs(linenum, AT_REG, sym);					\
      insn_u##ls##w_common(linenum, rt);				\
      doneat();								\
   }									\
   void insn_u##ls##w_rx(int linenum, int rt, struct expr *addr) {	\
      struct expr *offset, *reg;					\
									\
      if (addr->x_type != EXPR_BINARY || strcmp(addr->x_strop, "") != 0) { \
	 file_err(linenum, "Unknown/invalid addressing mode");		\
      }									\
									\
      offset = addr->x_arg1;						\
      reg = addr->x_arg2;						\
      /* reg is supposed to be in parentheses */			\
      if (reg->x_type != EXPR_UNARY || reg->x_tokop != TOK_LPAREN) {	\
	 file_err(linenum, "Unknown/invalid addressing mode");		\
      }									\
      reg = reg->x_arg1;						\
      if (!isreg(reg)) {						\
	 file_err(linenum, "Unknown/invalid addressing mode");		\
      }									\
									\
      checkmacro(linenum, "ulw");					\
      if (offset->x_type == EXPR_NUM && fits_s16(offset->x_num + 3)) {	\
         struct expr *o3 = expr_clone(offset);				\
	 o3->x_num += 3;						\
         insn_##ls##wl_regoffset(linenum, rt, offset, getreg(reg));	\
         insn_##ls##wr_regoffset(linenum, rt, o3, getreg(reg));		\
         expr_destroy(o3);						\
      }									\
      else {								\
         checkat(linenum, "ulw");					\
         insn_addiu_rrx(linenum, AT_REG, getreg(reg), offset);		\
         insn_u##ls##w_common(linenum, rt);				\
         doneat();							\
      }									\
   }

OP_unaligned(ulw, l);
OP_unaligned(usw, s);

/*
 * 26-bit jumps
 */
#define OP_JUMP(op, OP) \
   void insn_##op##_s(int linenum, struct label *target) {		\
      struct expr *targetx = mkexpr_label(target);			\
      u_machlarge val;						\
      val = process_expr(linenum, targetx, RELOC_FIELD_JUMP26, 0); \
      addinsn_6_26(linenum, OPC_##OP, val);			\
      branch_delay_slot(linenum);				\
   }

OP_JUMP(j, J);
OP_JUMP(jal, JAL);

/*
 * Break/trap instructions with a 20-bit code.
 */
#define OP_CODE20(op, OP) \
   void insn_##op##_n(int linenum, u_machlarge code) {		\
      if ((code & 0xfffff) != code) {					\
         file_err(linenum, "Out of range operation code for %s instruction", \
                  #op);							\
      }									\
      addinsn_6_20_6(linenum, OPC_SPECIAL, code, SPEC_##OP);	\
   }								\
   void insn_##op##_(int linenum) {				\
      insn_##op##_n(linenum, 0);				\
   }

OP_CODE20(syscall, SYSCALL);
//OP_CODE20(break, BREAK);

/*
 * break turns out to be two 10-bit codes, not one 20-bit code.
 */
void insn_break_nn(int linenum, u_machlarge code1, u_machlarge code2) {
   if ((code1 & 1023) != code1) {
      file_err(linenum, "Out of range first code for break instruction");
   }
   if ((code2 & 1023) != code2) {
      file_err(linenum, "Out of range second code for break instruction");
   }
   addinsn_6_10_10_6(linenum, OPC_SPECIAL, code1, code2, SPEC_BREAK);
}

void insn_break_n(int linenum, u_machlarge code) {
   insn_break_nn(linenum, code, 0);
}

void insn_break_(int linenum) {
   insn_break_nn(linenum, 0, 0);
}

void insn_sdbbp_n(int linenum, u_machlarge code) {
   if ((code & 0xfffff) != code) {
      file_err(linenum, "Out of range operation code for sdbbp instruction");
   }
   addinsn_6_20_6(linenum, OPC_SPECIAL2, code, SPEC2_SDBBP);
}

void insn_sdbbp_(int linenum) {
   insn_sdbbp_n(linenum, 0);
}

void insn_sync_(int linenum) {
   addinsn_6_20_6(linenum, OPC_SPECIAL, 0, SPEC_SYNC);
}

/*
 * Conditional trap instructions with a 10-bit code
 */
#define OP_CTRAP_code10(op, OP) \
   void insn_##op##_rrn(int linenum, int rs, int rt, u_machlarge code) { \
      if ((code & 1023) != code) {					\
         file_err(linenum, "Out of range operation code for %s instruction", \
                  #op);							\
      }									\
      addinsn_6_5_5_10_6(linenum, OPC_SPECIAL, rs, rt, code, SPEC_##OP); \
      reginfo_use_2gp_regs(rs, rt);					\
   }									\
   void insn_##op##_rr(int linenum, int rs, int rt) {			\
      insn_##op##_rrn(linenum, rs, rt, 0);				\
   }

OP_CTRAP_code10(teq, TEQ);
OP_CTRAP_code10(tge, TGE);
OP_CTRAP_code10(tgeu, TGEU);
OP_CTRAP_code10(tlt, TLT);
OP_CTRAP_code10(tltu, TLTU);
OP_CTRAP_code10(tne, TNE);


/*
 * Stuff with idiosyncratic format
 */

/*
 * XXX this should share all the forms of memory ops, and without the
 * cutpaste.
 */
static void insn_cache_regoffset(int linenum,
				 unsigned op, struct expr *offset, int rs) {
   u_machlarge val;
   val = process_expr(linenum, offset, RELOC_FIELD_S16, IMM_OFFSET);
   addinsn_RRI(linenum, OPC_CACHE, rs, op, val);
}

void insn_cache_nx(int linenum, u_machlarge op, struct expr *addr) {
   struct expr *offset, *reg;

   if ((op & 0x1f) != op) {
      file_err(linenum, "Out of range operation code for cache instruction");
   }

   if (addr->x_type == EXPR_BINARY && !strcmp(addr->x_strop, "")) {
      offset = addr->x_arg1;
      reg = addr->x_arg2;
      /* reg is supposed to be in parentheses */
      if (reg->x_type == EXPR_UNARY && reg->x_tokop == TOK_LPAREN) {
	 reg = reg->x_arg1;
	 if (isreg(reg)) {
	    insn_cache_regoffset(linenum, op, offset, getreg(reg));
	    return;
	 }
      }
   }
   file_err(linenum, "Unknown/invalid addressing mode");
}

void insn_cache_ns(int linenum, u_machlarge op, struct label *sym) {
   struct expr *hi, *lo;

   if ((op & 0x1f) != op) {
      file_err(linenum, "Out of range operation code for cache instruction");
   }

   checkmacro(linenum, "cache");
   checkat(linenum, "cache");
   hi = mkexpr_hi(mkexpr_label(sym));
   lo = mkexpr_lo(mkexpr_label(sym));
   insn_lui_rx(linenum, AT_REG, hi);
   insn_cache_regoffset(linenum, op, lo, AT_REG);
   doneat();
}

/*
 * ditto
 */
static void insn_pref_regoffset(int linenum,
				unsigned op, struct expr *offset, int rs) {
   u_machlarge val;
   val = process_expr(linenum, offset, RELOC_FIELD_S16, IMM_OFFSET);
   /* PREF is actually LWC3 */
   addinsn_RRI(linenum, OPC_LWC3, rs, op, val);
}

void insn_pref_nx(int linenum, u_machlarge op, struct expr *addr) {
   struct expr *offset, *reg;

   if ((op & 0x1f) != op) {
      file_err(linenum, "Out of range operation code for pref instruction");
   }

   if (addr->x_type == EXPR_BINARY && !strcmp(addr->x_strop, "")) {
      offset = addr->x_arg1;
      reg = addr->x_arg2;
      /* reg is supposed to be in parentheses */
      if (reg->x_type == EXPR_UNARY && reg->x_tokop == TOK_LPAREN) {
	 reg = reg->x_arg1;
	 if (isreg(reg)) {
	    insn_pref_regoffset(linenum, op, offset, getreg(reg));
	    return;
	 }
      }
   }
   file_err(linenum, "Unknown/invalid addressing mode");
}

void insn_pref_ns(int linenum, u_machlarge op, struct label *sym) {
   struct expr *hi, *lo;

   if ((op & 0x1f) != op) {
      file_err(linenum, "Out of range operation code for pref instruction");
   }

   checkmacro(linenum, "pref");
   checkat(linenum, "pref");
   hi = mkexpr_hi(mkexpr_label(sym));
   lo = mkexpr_lo(mkexpr_label(sym));
   insn_lui_rx(linenum, AT_REG, hi);
   insn_pref_regoffset(linenum, op, lo, AT_REG);
   doneat();
}

void insn_deret_(int linenum) {
   addinsn_6_20_6(linenum, OPC_COP0, 0x80000, COP0_DERET);
}

void insn_eret_(int linenum) {
   addinsn_6_20_6(linenum, OPC_COP0, 0x80000, COP0_ERET);
}

void insn_jr_r(int linenum, int rs) {
   addinsn_6_5_5_5_5_6(linenum, OPC_SPECIAL, rs, 0, 0, 0, SPEC_JR);
   branch_delay_slot(linenum);
   reginfo_use_gp_reg(rs);
}

void insn_j_r(int linenum, int rs) {
   insn_jr_r(linenum, rs);
   reginfo_use_gp_reg(rs);
}

void insn_jalr_rr(int linenum, int rd, int rs) {
   addinsn_6_5_5_5_5_6(linenum, OPC_SPECIAL, rs, 0, rd, 0, SPEC_JALR);
   branch_delay_slot(linenum);
   reginfo_use_2gp_regs(rd, rs);
}

void insn_jalr_r(int linenum, int rs) {
   insn_jalr_rr(linenum, 31, rs);
}

void insn_jal_r(int linenum, int rs) {
   insn_jalr_r(linenum, rs);
   reginfo_use_gp_reg(rs);
}

void insn_jal_rs(int linenum, int rs, struct label *target) {
   if (rs == 0) {
      checkmacro(linenum, "jal");
      checkat(linenum, "jal");
      insn_la_rs(linenum, AT_REG, target);
      insn_jalr_rr(linenum, rs, AT_REG);
      doneat();
   }
   else {
      insn_la_rs(linenum, rs, target);
      insn_jalr_rr(linenum, rs, rs);
   }
}

void insn_lui_rx(int linenum, int rt, struct expr *imm) {
   u_machlarge val;
   val = process_expr(linenum, imm, RELOC_FIELD_U16, IMM_OFFSET);
   addinsn_RRI(linenum, OPC_LUI, 0, rt, val);
   reginfo_use_gp_reg(rt);
}

void insn_mfhi_r(int linenum, int rd) {
   addinsn_spec_RRR(linenum, SPEC_MFHI, 0, 0, rd);
}

void insn_mflo_r(int linenum, int rd) {
   addinsn_spec_RRR(linenum, SPEC_MFLO, 0, 0, rd);
}

void insn_mthi_r(int linenum, int rs) {
   addinsn_spec_RRR(linenum, SPEC_MTHI, rs, 0, 0);
}

void insn_mtlo_r(int linenum, int rs) {
   addinsn_spec_RRR(linenum, SPEC_MTLO, rs, 0, 0);
}

void insn_rfe_(int linenum) {
   /* XXX check that mipsI is in effect */
   addinsn_6_20_6(linenum, OPC_COP0, 0x80000, COP0_RFE);
}

void insn_tlbp_(int linenum) {
   addinsn_6_20_6(linenum, OPC_COP0, 0x80000, COP0_TLBP);
}

void insn_tlbr_(int linenum) {
   addinsn_6_20_6(linenum, OPC_COP0, 0x80000, COP0_TLBR);
}

void insn_tlbwi_(int linenum) {
   addinsn_6_20_6(linenum, OPC_COP0, 0x80000, COP0_TLBWI);
}

void insn_tlbwr_(int linenum) {
   addinsn_6_20_6(linenum, OPC_COP0, 0x80000, COP0_TLBWR);
}

void insn_wait_n(int linenum, u_machlarge code) {
   /* 19-bit code */
   if ((code & 0x7ffff) != code) {
      file_err(linenum, "Invalid code for wait instruction");
   }
   /* set CO bit */
   code |= 0x80000;
   addinsn_6_20_6(linenum, OPC_COP0, code, COP0_WAIT);
}

void insn_wait_(int linenum) {
   insn_wait_n(linenum, 0);
}

/*
 * Integer macros
 */

void insn_b_s(int linenum, struct label *offset) {
   insn_beq_rrs(linenum, 0, 0, offset);
}

void insn_bal_s(int linenum, struct label *offset) {
   insn_bgezal_rs(linenum, 0, offset);
}

void insn_nop_(int linenum) {
   insn_sll_rrn(linenum, 0, 0, 0);
}

void insn_ssnop_(int linenum) {
   insn_sll_rrn(linenum, 0, 0, 1);
}

void insn_move_rr(int linenum, int rd, int rs) {
   insn_addu_rrr(linenum, rd, rs, 0);
}

void insn_la_rs(int linenum, int reg, struct label *sym) {
   struct expr *hi, *lo;

   checkmacro(linenum, "la");
   hi = mkexpr_hi(mkexpr_label(sym));
   lo = mkexpr_lo(mkexpr_label(sym));
   insn_lui_rx(linenum, reg, hi);
   insn_addiu_rrx(linenum, reg, reg, lo);
}

void insn_li_rn(int linenum, int reg, u_machlarge val) {
   u_machlarge hi, lo;

   if ((val & 0xffff0000) == 0) {
      lo = val & 0xffff;
      insn_ori_rrx(linenum, reg, 0, mkexpr_number(lo));
   }
   else if ((val & 0xffff) == 0) {
      hi = (val & 0xffff0000) >> 16;
      insn_lui_rx(linenum, reg, mkexpr_number(hi));
   }
   else if (!fits_s16(val)) {
      lo = val & 0xffff;
      hi = (val & 0xffff0000) >> 16;

      checkmacro(linenum, "li");
      insn_lui_rx(linenum, reg, mkexpr_number(hi));
      insn_ori_rrx(linenum, reg, reg, mkexpr_number(lo));
   }
   else {
      lo = (u_machlarge)(s_machlarge)(int16_t)(uint16_t)(val & 0xffff);
      hi = ((val - lo) >> 16) & 0xffff;

      assert(hi == 0);
      insn_addiu_rrx(linenum, reg, 0, mkexpr_number(lo));
   }
}

/*
 * Coprocessor branches
 */
#define OP_COP_BRANCH(op, COP, nd, tf, LIKELY) \
   void insn_##op##_ns(int linenum, u_machlarge cc, struct label *offset) { \
      u_machlarge imm;						\
      unsigned ccfield;						\
								\
      assert((cc & 7) == cc);					\
      assert((nd & 1) == nd);					\
      assert((tf & 1) == tf);					\
								\
      ccfield = (cc << 2) | (nd << 1) | tf;			\
								\
      imm = process_branch_target(linenum, offset);		\
      addinsn_6_5_5_16(linenum, OPC_##COP, COP_BC, ccfield, imm); \
      LIKELY;							\
      branch_delay_slot(linenum);				\
   }								\
   void insn_##op##_s(int linenum, struct label *offset) {	\
      insn_##op##_ns(linenum, 0, offset);			\
   }

OP_COP_BRANCH(bc1f,  COP1, 0, 0, );
OP_COP_BRANCH(bc1fl, COP1, 1, 0, LIKELY);
OP_COP_BRANCH(bc1t,  COP1, 0, 1, );
OP_COP_BRANCH(bc1tl, COP1, 1, 1, LIKELY);
OP_COP_BRANCH(bc2f,  COP2, 0, 0, );
OP_COP_BRANCH(bc2fl, COP2, 1, 0, LIKELY);
OP_COP_BRANCH(bc2t,  COP2, 0, 1, );
OP_COP_BRANCH(bc2tl, COP2, 1, 1, LIKELY);

/*
 * other coprocessor ops
 */

void insn_cfc1_rr(int linenum, int rt, int fs) {
   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, COP_CF, rt, fs, 0, 0);
   reginfo_use_gp_reg(rt);
   reginfo_use_fp_reg(fs);
}

void insn_cfc2_rr(int linenum, int rt, int fs) {
   addinsn_6_5_5_5_5_6(linenum, OPC_COP2, COP_CF, rt, fs, 0, 0);
   reginfo_use_gp_reg(rt);
   reginfo_use_fp_reg(fs);
}

void insn_ctc1_rr(int linenum, int rt, int fs) {
   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, COP_CT, rt, fs, 0, 0);
   reginfo_use_gp_reg(rt);
   reginfo_use_fp_reg(fs);
}

void insn_ctc2_rr(int linenum, int rt, int fs) {
   addinsn_6_5_5_5_5_6(linenum, OPC_COP2, COP_CT, rt, fs, 0, 0);
   reginfo_use_gp_reg(rt);
   reginfo_use_fp_reg(fs);
}

void insn_cop2_n(int linenum, u_machlarge func) {
   /* 25-bit field */
   assert((func & 0x1ffffff) == func);
   func |= 0x2000000;
   addinsn_6_26(linenum, OPC_COP2, func);
}

#define OP_COPz(op, COP, OP, RGI_RT, RGI_RD) \
   void insn_##op##_rr(int linenum, int rt, int rd) {		\
      addinsn_6_5_5_5_5_6(linenum, OPC_##COP, COP_##OP, rt, rd, 0, 0);	\
      reginfo_use_##RGI_RT##_reg(rt);					\
      reginfo_use_##RGI_RD##_reg(rd);					\
   }
#define OP_COPzsel(op, COP, OP, RGI_RT, RGI_RD) \
   void insn_##op##_rrn(int linenum, int rt, int rd, u_machlarge sel) {	\
      if ((sel & 7) != sel) {						\
         file_err(linenum, "Out of range register select");		\
      }									\
      addinsn_6_5_5_5_5_6(linenum, OPC_##COP, COP_##OP, rt, rd, 0, sel); \
      reginfo_use_##RGI_RT##_reg(rt);					\
      reginfo_use_##RGI_RD##_reg(rd);					\
   }

OP_COPz(mfc0, COP0, MF, gp, COP0);
OP_COPz(mfc1, COP1, MF, gp, COP1);
OP_COPz(mfc2, COP2, MF, gp, COP2);
OP_COPzsel(mfc0, COP0, MF, gp, COP0);
OP_COPzsel(mfc2, COP2, MF, gp, COP2);

OP_COPz(mtc0, COP0, MT, COP0, gp);
OP_COPz(mtc1, COP1, MT, COP0, gp);
OP_COPz(mtc2, COP2, MT, COP0, gp);
OP_COPzsel(mtc0, COP0, MT, COP0, gp);
OP_COPzsel(mtc2, COP2, MT, COP0, gp);

/*
 * Floating point ops using the cop1_RR format
 *
 * Note: this is where the assembler order ABS.D fd, fs turns into the
 * bit order fs-fd.
 */
#define OP_F_RR(op, fmt, OP) \
  void insn_##op##_rr(int linenum, int fd, int fs) {			\
     addinsn_cop1_RR(linenum, COP1_##OP, COP1_##fmt, fs, fd);		\
     reginfo_use_2fp_regs(fd, fs);					\
  }

/*
 * and the cop1_RRR format
 */
#define OP_F_RRR(op, fmt, OP) \
  void insn_##op##_rrr(int linenum, int fd, int fs, int ft) {		\
     addinsn_cop1_RRR(linenum, COP1_##OP, COP1_##fmt, ft, fs, fd);	\
     reginfo_use_3fp_regs(fd, fs, ft);					\
  }

OP_F_RR(abs_s, FLOATFMT_S, ABS);
OP_F_RR(abs_d, FLOATFMT_D, ABS);
OP_F_RR(ceil_w_s, FLOATFMT_S, CEIL);
OP_F_RR(ceil_w_d, FLOATFMT_D, CEIL);
OP_F_RR(cvt_d_s, FLOATFMT_S, CVT_D);
OP_F_RR(cvt_d_w, FLOATFMT_W, CVT_D);
OP_F_RR(cvt_d_l, FLOATFMT_L, CVT_D);
OP_F_RR(cvt_s_d, FLOATFMT_D, CVT_S);
OP_F_RR(cvt_s_w, FLOATFMT_W, CVT_S);
OP_F_RR(cvt_s_l, FLOATFMT_L, CVT_S);
OP_F_RR(cvt_w_s, FLOATFMT_S, CVT_W);
OP_F_RR(cvt_w_d, FLOATFMT_D, CVT_W);
OP_F_RR(floor_w_s, FLOATFMT_S, FLOOR);
OP_F_RR(floor_w_d, FLOATFMT_D, FLOOR);
OP_F_RR(mov_s, FLOATFMT_S, MOV);
OP_F_RR(mov_d, FLOATFMT_D, MOV);
OP_F_RR(neg_s, FLOATFMT_S, NEG);
OP_F_RR(neg_d, FLOATFMT_D, NEG);
OP_F_RR(round_w_s, FLOATFMT_S, ROUND);
OP_F_RR(round_w_d, FLOATFMT_D, ROUND);
OP_F_RR(sqrt_s, FLOATFMT_S, SQRT);
OP_F_RR(sqrt_d, FLOATFMT_D, SQRT);
OP_F_RR(trunc_w_s, FLOATFMT_S, TRUNC);
OP_F_RR(trunc_w_d, FLOATFMT_D, TRUNC);

OP_F_RRR(add_s, FLOATFMT_S, ADD);
OP_F_RRR(add_d, FLOATFMT_D, ADD);
OP_F_RRR(div_s, FLOATFMT_S, DIV);
OP_F_RRR(div_d, FLOATFMT_D, DIV);
OP_F_RRR(mul_s, FLOATFMT_S, MUL);
OP_F_RRR(mul_d, FLOATFMT_D, MUL);
OP_F_RRR(sub_s, FLOATFMT_S, SUB);
OP_F_RRR(sub_d, FLOATFMT_D, SUB);

/*
 * Other floating point ops
 */

static void insn_c(int linenum,
		   u_machlarge cond, u_machlarge fmt, u_machlarge cc, int fs, int ft) {
   unsigned ccfield, condfield;

   assert((cc & 7) == cc);
   assert((cond & 15) == cond);

   ccfield = cc << 2;
   condfield = cond | 0x30;

   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, fmt, ft, fs, ccfield, condfield);
}

/*
 * XXX note that there should also be versions where the cc operand
 * is implicit (and 0)... need to figure out how to handle overloaded
 * assembler-level opcode names.
 */

#define OP_Cx(cond, COND, fmt, FMT) \
   void insn_c_##cond##_##fmt##_nrr(int linenum, u_machlarge cc, int fs, int ft) { \
      insn_c(linenum, COND, FMT, cc, fs, ft);				\
      reginfo_use_2fp_regs(fs, ft);					\
   }									\
   void insn_c_##cond##_##fmt##_rr(int linenum, int fs, int ft) {		\
      insn_c(linenum, COND, FMT, 0, fs, ft);				\
      reginfo_use_2fp_regs(fs, ft);					\
   }

#define OP_C(cond, COND) \
   OP_Cx(cond, COND, s, COP1_FLOATFMT_S); \
   OP_Cx(cond, COND, d, COP1_FLOATFMT_D)

OP_C(f,    0);
OP_C(un,   1);
OP_C(eq,   2);
OP_C(ueq,  3);
OP_C(olt,  4);
OP_C(ult,  5);
OP_C(ole,  6);
OP_C(ule,  7);
OP_C(sf,   8);
OP_C(ngle, 9);
OP_C(seq,  10);
OP_C(ngl,  11);
OP_C(lt,   12);
OP_C(nge,  13);
OP_C(le,   14);
OP_C(ngt,  15);

void insn_movf_rrn(int linenum, int rd, int rs, u_machlarge cc) {
   unsigned ccfield;

   assert((cc & 7) == cc);

   ccfield = (cc << 2) | 0 /* false */;
   addinsn_6_5_5_5_5_6(linenum, OPC_SPECIAL, rs, ccfield, rd, 0, SPEC_MOVC);
   reginfo_use_2gp_regs(rd, rs);
}

void insn_movt_rrn(int linenum, int rd, int rs, u_machlarge cc) {
   unsigned ccfield;

   assert((cc & 7) == cc);

   ccfield = (cc << 2) | 1 /* true */;
   addinsn_6_5_5_5_5_6(linenum, OPC_SPECIAL, rs, ccfield, rd, 0, SPEC_MOVC);
   reginfo_use_2gp_regs(rd, rs);
}

void insn_movf_s_rrn(int linenum, int fd, int fs, u_machlarge cc) {
   unsigned ccfield;

   assert((cc & 7) == cc);

   ccfield = (cc << 2) | 0 /* false */;
   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, COP1_FLOATFMT_S, ccfield, fs, fd, COP1_MOVC);
   reginfo_use_2fp_regs(fd, fs);
}

void insn_movf_d_rrn(int linenum, int fd, int fs, u_machlarge cc) {
   unsigned ccfield;

   assert((cc & 7) == cc);

   ccfield = (cc << 2) | 0 /* false */;
   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, COP1_FLOATFMT_D, ccfield, fs, fd, COP1_MOVC);
   reginfo_use_2fp_regs(fd, fs);
}

void insn_movt_s_rrn(int linenum, int fd, int fs, u_machlarge cc) {
   unsigned ccfield;

   assert((cc & 7) == cc);

   ccfield = (cc << 2) | 1 /* true */;
   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, COP1_FLOATFMT_S, ccfield, fs, fd, COP1_MOVC);
   reginfo_use_2fp_regs(fd, fs);
}

void insn_movt_d_rrn(int linenum, int fd, int fs, u_machlarge cc) {
   unsigned ccfield;

   assert((cc & 7) == cc);

   ccfield = (cc << 2) | 1 /* true */;
   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, COP1_FLOATFMT_D, ccfield, fs, fd, COP1_MOVC);
   reginfo_use_2fp_regs(fd, fs);
}

void insn_movn_s_rrr(int linenum, int fd, int fs, int rt) {
   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, COP1_FLOATFMT_S, rt, fs, fd, COP1_MOVN);
   reginfo_use_2fp_regs(fd, fs);
   reginfo_use_gp_reg(rt);
}

void insn_movn_d_rrr(int linenum, int fd, int fs, int rt) {
   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, COP1_FLOATFMT_D, rt, fs, fd, COP1_MOVN);
   reginfo_use_2fp_regs(fd, fs);
   reginfo_use_gp_reg(rt);
}

void insn_movz_s_rrr(int linenum, int fd, int fs, int rt) {
   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, COP1_FLOATFMT_S, rt, fs, fd, COP1_MOVZ);
   reginfo_use_2fp_regs(fd, fs);
   reginfo_use_gp_reg(rt);
}

void insn_movz_d_rrr(int linenum, int fd, int fs, int rt) {
   addinsn_6_5_5_5_5_6(linenum, OPC_COP1, COP1_FLOATFMT_D, rt, fs, fd, COP1_MOVZ);
   reginfo_use_2fp_regs(fd, fs);
   reginfo_use_gp_reg(rt);
}
