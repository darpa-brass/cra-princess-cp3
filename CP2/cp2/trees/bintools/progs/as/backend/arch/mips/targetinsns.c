/* Automatically generated; do not edit */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "mem.h"

#include "expr.h"
#include "load.h"
#include "label.h"
#include "section.h"
#include "reloc.h"
#include "sectionops.h"
#include "relocops.h"
#include "as.h"
#include "modeinfo.h"
#include "targetoper.h"
#include "targetmatch.h"

struct reginfo{
   uint32_t r_gpregs;
   uint32_t r_cop0regs;
   uint32_t r_fpregs;
   uint32_t r_cop2regs;
   uint32_t r_cop3regs;
   uint32_t r_gp;
};
static struct reginfo myreginfo;
static void reginfo_use_reg(uint32_t * info, unsigned int reg) {
   assert((reg < 32));
   *info =((*info)|(1U << reg));
}
static void reginfo_use_gp_reg(unsigned int reg) {
   if ((reg == 0U))return;
   reginfo_use_reg(&myreginfo.r_gpregs, reg);
}
static void reginfo_use_cop0_reg(unsigned int reg) {
   reginfo_use_reg(&myreginfo.r_cop0regs, reg);
}
static void reginfo_use_fp_reg(unsigned int reg) {
   reginfo_use_reg(&myreginfo.r_fpregs, reg);
}
static void reginfo_use_cop2_reg(unsigned int reg) {
   reginfo_use_reg(&myreginfo.r_cop2regs, reg);
}
static void reginfo_use_cop3_reg(unsigned int reg) {
   reginfo_use_reg(&myreginfo.r_cop3regs, reg);
}
void target_generate_special_sections(void) {
   unsigned int snum;
   unsigned char * p;
   size_t i;
   
   snum = getsection(".reginfo", true, false, true, false);
   align_section(snum, 2);
   assert((sizeof(struct reginfo)== 24));
   p =(unsigned char *)&myreginfo;
   for(i = 0;
   (i < sizeof(struct reginfo)); i =(i + 1)) {
      section_addbyte(snum, -1,(p [i]));
   }
}

u_machword process_expr_qword(int linenum, struct expr * x, unsigned int offset) {
   (void)x;
   (void)offset;
   file_err(linenum, "No 64-bit relocations on this architecture");
}
u_machword process_expr_word(int linenum, struct expr * x, unsigned int offset) {
   return process_expr(linenum, x, RELOC_FIELD_DATA32, offset);
}
u_machword process_expr_hword(int linenum, struct expr * x, unsigned int offset) {
   return process_expr(linenum, x, RELOC_FIELD_DATA16, offset);
}


static void arith_e13e13e13(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void shiftv_e13e13e13(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rt, uint8_t var_rs);
static void muldivraw_e13e13(int line, uint8_t var_specop, uint8_t var_rs, uint8_t var_rt);
static void movnz_e13e13e13(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void mfhilo_e13(int line, uint8_t var_specop, uint8_t var_rd);
static void mthilo_e13(int line, uint8_t var_specop, uint8_t var_rs);
static void sync_u5(int line, uint8_t var_code);
static void jr_raw_e13(int line, uint8_t var_rs);
static void jalr_raw_e13e13(int line, uint8_t var_rd, uint8_t var_rs);
static void shift_e13e13u32(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rt, uint32_t var_bits);
static void clo_e13e13(int line, uint8_t var_rd, uint8_t var_rs);
static void clz_e13e13(int line, uint8_t var_rd, uint8_t var_rs);
static void madd_e13e13(int line, uint8_t var_rs, uint8_t var_rt);
static void maddu_e13e13(int line, uint8_t var_rs, uint8_t var_rt);
static void msub_e13e13(int line, uint8_t var_rs, uint8_t var_rt);
static void msubu_e13e13(int line, uint8_t var_rs, uint8_t var_rt);
static void mul_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void break_u10u10(int line, uint16_t var_code10a, uint16_t var_code10b);
static void syscall_u32(int line, uint32_t var_code32);
static void sdbbp_u32(int line, uint32_t var_code32);
static void ctrap_e13e13u32(int line, uint8_t var_specop, uint8_t var_rs, uint8_t var_rt, uint32_t var_code32);
static void ctrapiraw_e13i16(int line, uint8_t var_bcondop, uint8_t var_rs, int16_t var_imm);
static void ctrapi_e13xi16(int line, uint8_t var_bcondop, uint8_t var_rs, struct expr * var_immexpr);
static void bcondraw_e13xu32(int line, uint8_t var_bcondop, uint8_t var_rs, struct expr * var_branchtargetsym);
static void j_raw_xu32(int line, struct expr * var_jumptargetsym);
static void jal_raw_xu32(int line, struct expr * var_jumptargetsym);
static void branchraw_e13e13xu32(int line, uint8_t var_op, uint8_t var_rs, uint8_t var_rt, struct expr * var_branchtargetsym);
static void branch0raw_e13xu32(int line, uint8_t var_op, uint8_t var_rs, struct expr * var_branchtargetsym);
static void bneplain_e13e13i16(int line, uint8_t var_rs, uint8_t var_rt, int16_t var_branchtarget);
static void arithimm_e13e13xi16(int line, uint8_t var_op, uint8_t var_rt, uint8_t var_rs, struct expr * var_immexpr);
static void arithimmraw_e13e13i16(int line, uint8_t var_op, uint8_t var_rt, uint8_t var_rs, int16_t var_imm);
static void loadraw_e13e13i16(int line, uint8_t var_op, uint8_t var_rt, uint8_t var_rs, int16_t var_imm);
static void load_e13mem(int line, uint8_t var_op, uint8_t var_rt, struct compound_mem * var_addr);
static void storeraw_e13e13i16(int line, uint8_t var_op, uint8_t var_rt, uint8_t var_rs, int16_t var_imm);
static void store_e13mem(int line, uint8_t var_op, uint8_t var_rt, struct compound_mem * var_addr);
static void cache_u32mem(int line, uint32_t var_cacheop32, struct compound_mem * var_addr);
static void pref_u32mem(int line, uint32_t var_prefop32, struct compound_mem * var_addr);
static void bitimm_e13e13xu16(int line, uint8_t var_op, uint8_t var_rt, uint8_t var_rs, struct expr * var_uimmexpr);
static void bitimmraw_e13e13u16(int line, uint8_t var_op, uint8_t var_rt, uint8_t var_rs, uint16_t var_uimm);
static void luiraw_e13u16(int line, uint8_t var_rt, uint16_t var_uimm);
static void lui_e13xu16(int line, uint8_t var_rt, struct expr * var_uimmexpr);
static void mfc0_e13e8u3(int line, uint8_t var_rt, uint8_t var_rd_cop0, uint8_t var_sel);
static void mfc0_e13e8(int line, uint8_t var_rt, uint8_t var_rd_cop0);
static void mtc0_e13e8u3(int line, uint8_t var_rt, uint8_t var_rd_cop0, uint8_t var_sel);
static void mtc0_e13e8(int line, uint8_t var_rt, uint8_t var_rd_cop0);
static void cop0_(int line, uint8_t var_cop0op);
static void wait_u32(int line, uint32_t var_code32);
static void mfc2_e13e9u3(int line, uint8_t var_rt, uint8_t var_rd_cop2, uint8_t var_sel);
static void mfc2_e13e9(int line, uint8_t var_rt, uint8_t var_rd_cop2);
static void mtc2_e13e9u3(int line, uint8_t var_rt, uint8_t var_rd_cop2, uint8_t var_sel);
static void mtc2_e13e9(int line, uint8_t var_rt, uint8_t var_rd_cop2);
static void cfc2_e13e9(int line, uint8_t var_rt, uint8_t var_rd_cop2);
static void ctc2_e13e9(int line, uint8_t var_rt, uint8_t var_rd_cop2);
static void bc2rawraw_e11xu32(int line, uint8_t var_nd, uint8_t var_tf, uint8_t var_cc, struct expr * var_branchtargetsym);
static void lwc2_e9mem(int line, uint8_t var_rt_cop2, struct compound_mem * var_addr);
static void ldc2_e9mem(int line, uint8_t var_rt_cop2, struct compound_mem * var_addr);
static void swc2_e9mem(int line, uint8_t var_rt_cop2, struct compound_mem * var_addr);
static void sdc2_e9mem(int line, uint8_t var_rt_cop2, struct compound_mem * var_addr);
static void cop2_u32(int line, uint32_t var_cofunraw);
static void mfc3_e13e10u3(int line, uint8_t var_rt, uint8_t var_rd_cop3, uint8_t var_sel);
static void mfc3_e13e10(int line, uint8_t var_rt, uint8_t var_rd_cop3);
static void mtc3_e13e10u3(int line, uint8_t var_rt, uint8_t var_rd_cop3, uint8_t var_sel);
static void mtc3_e13e10(int line, uint8_t var_rt, uint8_t var_rd_cop3);
static void cfc3_e13e10(int line, uint8_t var_rt, uint8_t var_rd_cop3);
static void ctc3_e13e10(int line, uint8_t var_rt, uint8_t var_rd_cop3);
static void bc3rawraw_e11xu32(int line, uint8_t var_nd, uint8_t var_tf, uint8_t var_cc, struct expr * var_branchtargetsym);
static void lwc3_e10mem(int line, uint8_t var_rt_cop3, struct compound_mem * var_addr);
static void ldc3_e10mem(int line, uint8_t var_rt_cop3, struct compound_mem * var_addr);
static void swc3_e10mem(int line, uint8_t var_rt_cop3, struct compound_mem * var_addr);
static void sdc3_e10mem(int line, uint8_t var_rt_cop3, struct compound_mem * var_addr);
static void cop3_u32(int line, uint32_t var_cofunraw);
static void mfc1_e13e12(int line, uint8_t var_rt, uint8_t var_fs);
static void mtc1_e13e12(int line, uint8_t var_rt, uint8_t var_fs);
static void cfc1_e13e12(int line, uint8_t var_rt, uint8_t var_fs);
static void ctc1_e13e12(int line, uint8_t var_rt, uint8_t var_fs);
static void bc1rawraw_e11xu32(int line, uint8_t var_nd, uint8_t var_tf, uint8_t var_cc, struct expr * var_branchtargetsym);
static void lwc1_e12mem(int line, uint8_t var_ft, struct compound_mem * var_addr);
static void ldc1_e12mem(int line, uint8_t var_ft, struct compound_mem * var_addr);
static void swc1_e12mem(int line, uint8_t var_ft, struct compound_mem * var_addr);
static void sdc1_e12mem(int line, uint8_t var_ft, struct compound_mem * var_addr);
static void fparith_e12e12e12(int line, uint8_t var_cop1op, uint8_t var_fmt, uint8_t var_fd, uint8_t var_fs, uint8_t var_ft);
static void fparith_e12e12(int line, uint8_t var_cop1op, uint8_t var_fmt, uint8_t var_fd, uint8_t var_fs);
static void fmovnz_e12e12e13(int line, uint8_t var_cop1op, uint8_t var_fmt, uint8_t var_fd, uint8_t var_fs, uint8_t var_rt);
static void fmovf_e12e12e11(int line, uint8_t var_fmt, uint8_t var_fd, uint8_t var_fs, uint8_t var_cc);
static void fmovt_e12e12e11(int line, uint8_t var_fmt, uint8_t var_fd, uint8_t var_fs, uint8_t var_cc);
static void movf_e13e13e11(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_cc);
static void movt_e13e13e11(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_cc);
static void c_e11e12e12(int line, uint8_t var_cop1op, uint8_t var_fmt, uint8_t var_cc_alt, uint8_t var_fs, uint8_t var_ft);
static void arith_e13e13(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rs);
static void addiu_e13e13i16(int line, uint8_t var_rt, uint8_t var_rs, int16_t var_imm);
static void ori_e13e13u16(int line, uint8_t var_rt, uint8_t var_rs, uint16_t var_uimm);
static void li_e13u32(int line, uint8_t var_rd, uint32_t var_val);
static void arithval_plain_e13e13u32(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rt, uint32_t var_val);
static void arithval_u_e13e13u32(int line, uint8_t var_specop, uint8_t var_immop, uint8_t var_rd, uint8_t var_rt, uint32_t var_val);
static void arithval_s_e13e13u32(int line, uint8_t var_specop, uint8_t var_immop, uint8_t var_rd, uint8_t var_rt, uint32_t var_val);
static void arithval_sub_e13e13u32(int line, uint8_t var_specop, uint8_t var_addop, uint8_t var_rd, uint8_t var_rt, uint32_t var_val);
static void addiu_e13e13xi16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void arithval_subi_e13e13xi16(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rt, struct expr * var_expr);
static void nop_(int line);
static void mflo_e13(int line, uint8_t var__op0);
static void div_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void div_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void divu_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void divu_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void sync_(int line);
static void jr_e13(int line, uint8_t var_rs);
static void jalr_e13e13(int line, uint8_t var_rd, uint8_t var_rs);
static void jalr_e13(int line, uint8_t var_rs);
static void ssnop_(int line);
static void move_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void sub_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void neg_e13e13(int line, uint8_t var_rd, uint8_t var_rs);
static void neg_e13(int line, uint8_t var_rd);
static void subu_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void negu_e13e13(int line, uint8_t var_rd, uint8_t var_rs);
static void negu_e13(int line, uint8_t var_rd);
static void nor_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void not_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void not_e13(int line, uint8_t var_rd);
static void sra_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void xor_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void abs_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void abs_e13(int line, uint8_t var_rd);
static void sltu_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void seq_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void seq_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void subu_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void xor_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void seq_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val);
static void xori_e13e13xu16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void seqi_e13e13xu16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr);
static void sltu_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sne_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void sne_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void sne_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val);
static void snei_e13e13xu16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr);
static void slt_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sgt_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void sgt_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void sgt_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val);
static void sgti_e13e13xi16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr);
static void sgtu_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void sgtu_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void sgtu_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val);
static void sgtiu_e13e13xi16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr);
static void sge_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void sge_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void slt_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void sge_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val);
static void slti_e13e13xi16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void sgei_e13e13xi16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr);
static void sgeu_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void sgeu_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void sgeu_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val);
static void sltiu_e13e13xi16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void sgeiu_e13e13xi16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr);
static void sle_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void sle_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void sle_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val);
static void slei_e13e13xi16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr);
static void sleu_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt);
static void sleu_e13e13(int line, uint8_t var_rd, uint8_t var_rt);
static void sleu_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val);
static void sleiu_e13e13xi16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr);
static void srl_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void sll_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void or_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void ror_e13e13u32(int line, uint8_t var_rd, uint8_t var_rt, uint32_t var_bits);
static void rol_e13e13u32(int line, uint8_t var_rd, uint8_t var_rt, uint32_t var_bits);
static void sll_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void srl_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void ror_e13e13e13(int line, uint8_t var_rd, uint8_t var_rt, uint8_t var_rs);
static void rol_e13e13e13(int line, uint8_t var_rd, uint8_t var_rt, uint8_t var_rs);
static void la_e13xu32(int line, uint8_t var_rd, struct expr * var_sym);
static void break_u32u32(int line, uint32_t var_a, uint32_t var_b);
static void break_u32(int line, uint32_t var_a);
static void break_(int line);
static void syscall_(int line);
static void sdbbp_(int line);
static void ctrap_e13e13(int line, uint8_t var_specop, uint8_t var_rs, uint8_t var_rt);
static void ctrapval_e13u32(int line, uint8_t var_specop, uint8_t var_bcondop, uint8_t var_rs, uint32_t var_val);
static void bcond_e13xu32(int line, uint8_t var_bcondop, uint8_t var_rs, struct expr * var_branchtargetsym);
static void bal_xu32(int line, struct expr * var_sym);
static void j_xu32(int line, struct expr * var_sym);
static void jal_xu32(int line, struct expr * var_sym);
static void jal_e13xu32(int line, uint8_t var_rd, struct expr * var_jumptargetsym);
static void branch_e13e13xu32(int line, uint8_t var_op, uint8_t var_rs, uint8_t var_rt, struct expr * var_branchtargetsym);
static void branch0_e13xu32(int line, uint8_t var_op, uint8_t var_rs, struct expr * var_branchtargetsym);
static void branchN_e13u32xu32(int line, uint8_t var_op, uint8_t var_rs, uint32_t var_val, struct expr * var_branchtargetsym);
static void b_xu32(int line, struct expr * var_sym);
static void load_e13xu32(int line, uint8_t var_op, uint8_t var_rt, struct expr * var_sym);
static void store_e13xu32(int line, uint8_t var_op, uint8_t var_rt, struct expr * var_sym);
static void ulw_e13mem(int line, uint8_t var_rt, struct compound_mem * var_addr);
static void usw_e13mem(int line, uint8_t var_rt, struct compound_mem * var_addr);
static void ulw_e13xu32(int line, uint8_t var_rt, struct expr * var_sym);
static void usw_e13xu32(int line, uint8_t var_rt, struct expr * var_sym);
static void cache_u32xu32(int line, uint32_t var_cacheop32, struct expr * var_sym);
static void pref_u32xu32(int line, uint32_t var_prefop32, struct expr * var_sym);
static void ori_e13e13xu16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void nori_e13e13xu16(int line, uint8_t var_rt, uint8_t var_rs, struct expr * var_uimmexpr);
static void bc2raw_e11xu32(int line, uint8_t var_nd, uint8_t var_tf, uint8_t var_cc, struct expr * var_branchtargetsym);
static void bc2f_e11xu32(int line, uint8_t var_cc, struct expr * var_sym);
static void bc2fl_e11xu32(int line, uint8_t var_cc, struct expr * var_sym);
static void bc2t_e11xu32(int line, uint8_t var_cc, struct expr * var_sym);
static void bc2tl_e11xu32(int line, uint8_t var_cc, struct expr * var_sym);
static void bc2f_xu32(int line, struct expr * var_sym);
static void bc2fl_xu32(int line, struct expr * var_sym);
static void bc2t_xu32(int line, struct expr * var_sym);
static void bc2tl_xu32(int line, struct expr * var_sym);
static void lwc2_e9xu32(int line, uint8_t var_rt_cop2, struct expr * var_sym);
static void ldc2_e9xu32(int line, uint8_t var_rt_cop2, struct expr * var_sym);
static void swc2_e9xu32(int line, uint8_t var_rt_cop2, struct expr * var_sym);
static void sdc2_e9xu32(int line, uint8_t var_rt_cop2, struct expr * var_sym);
static void bc3raw_e11xu32(int line, uint8_t var_nd, uint8_t var_tf, uint8_t var_cc, struct expr * var_branchtargetsym);
static void bc3f_e11xu32(int line, uint8_t var_cc, struct expr * var_sym);
static void bc3fl_e11xu32(int line, uint8_t var_cc, struct expr * var_sym);
static void bc3t_e11xu32(int line, uint8_t var_cc, struct expr * var_sym);
static void bc3tl_e11xu32(int line, uint8_t var_cc, struct expr * var_sym);
static void bc3f_xu32(int line, struct expr * var_sym);
static void bc3fl_xu32(int line, struct expr * var_sym);
static void bc3t_xu32(int line, struct expr * var_sym);
static void bc3tl_xu32(int line, struct expr * var_sym);
static void lwc3_e10xu32(int line, uint8_t var_rt_cop3, struct expr * var_sym);
static void ldc3_e10xu32(int line, uint8_t var_rt_cop3, struct expr * var_sym);
static void swc3_e10xu32(int line, uint8_t var_rt_cop3, struct expr * var_sym);
static void sdc3_e10xu32(int line, uint8_t var_rt_cop3, struct expr * var_sym);
static void bc1raw_e11xu32(int line, uint8_t var_nd, uint8_t var_tf, uint8_t var_cc, struct expr * var_branchtargetsym);
static void bc1f_e11xu32(int line, uint8_t var_cc, struct expr * var_sym);
static void bc1fl_e11xu32(int line, uint8_t var_cc, struct expr * var_sym);
static void bc1t_e11xu32(int line, uint8_t var_cc, struct expr * var_sym);
static void bc1tl_e11xu32(int line, uint8_t var_cc, struct expr * var_sym);
static void bc1f_xu32(int line, struct expr * var_sym);
static void bc1fl_xu32(int line, struct expr * var_sym);
static void bc1t_xu32(int line, struct expr * var_sym);
static void bc1tl_xu32(int line, struct expr * var_sym);
static void lwc1_e12xu32(int line, uint8_t var_ft, struct expr * var_sym);
static void ldc1_e12xu32(int line, uint8_t var_ft, struct expr * var_sym);
static void swc1_e12xu32(int line, uint8_t var_ft, struct expr * var_sym);
static void sdc1_e12xu32(int line, uint8_t var_ft, struct expr * var_sym);
static void fparith2_e12e12(int line, uint8_t var_cop1op, uint8_t var_fmt, uint8_t var_fd, uint8_t var_ft);
static void c_e12e12(int line, uint8_t var_cop1op, uint8_t var_fmt, uint8_t var_fs, uint8_t var_ft);
static void add_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void add_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void add_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void addi_e13e13xi16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void addu_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void addu_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void addu_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void and_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void and_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void and_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void andi_e13e13xu16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void beq_e13e13xu32(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void beq_e13u32xu32(int line, uint8_t var__op0, uint32_t var__op1, struct expr * var__op2);
static void beql_e13e13xu32(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void beql_e13u32xu32(int line, uint8_t var__op0, uint32_t var__op1, struct expr * var__op2);
static void beqz_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void beqzl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void bgez_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void bgezl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void bgezal_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void bgezall_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void bgtz_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void bgtzl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void blez_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void blezl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void bltz_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void bltzl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void bltzal_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void bltzall_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void bne_e13e13xu32(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void bne_e13u32xu32(int line, uint8_t var__op0, uint32_t var__op1, struct expr * var__op2);
static void bnel_e13e13xu32(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void bnel_e13u32xu32(int line, uint8_t var__op0, uint32_t var__op1, struct expr * var__op2);
static void bnez_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void bnezl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void deret_(int line);
static void eret_(int line);
static void j_e13(int line, uint8_t var__op0);
static void jal_e13(int line, uint8_t var__op0);
static void lb_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void lb_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void lbu_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void lbu_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void lh_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void lh_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void lhu_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void lhu_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void ll_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void ll_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void lw_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void lw_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void lwl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void lwl_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void lwr_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void lwr_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void mfhi_e13(int line, uint8_t var__op0);
static void movn_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movz_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void mthi_e13(int line, uint8_t var__op0);
static void mtlo_e13(int line, uint8_t var__op0);
static void mult_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void multu_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void nor_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void nor_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void or_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void or_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void rfe_(int line);
static void sb_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void sb_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void sc_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void sc_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void sh_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void sh_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void sllv_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void slt_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void sltu_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void sra_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void srav_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void srlv_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sub_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void sub_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void subi_e13e13xi16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void subu_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void subiu_e13e13xi16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2);
static void sw_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void sw_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void swl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void swl_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void swr_e13xu32(int line, uint8_t var__op0, struct expr * var__op1);
static void swr_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1);
static void teq_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void teq_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void teq_e13u32(int line, uint8_t var__op0, uint32_t var__op1);
static void teqi_e13xi16(int line, uint8_t var__op0, struct expr * var__op1);
static void tge_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void tge_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void tge_e13u32(int line, uint8_t var__op0, uint32_t var__op1);
static void tgei_e13xi16(int line, uint8_t var__op0, struct expr * var__op1);
static void tgeu_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void tgeu_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void tgeu_e13u32(int line, uint8_t var__op0, uint32_t var__op1);
static void tgeiu_e13xi16(int line, uint8_t var__op0, struct expr * var__op1);
static void tlbp_(int line);
static void tlbr_(int line);
static void tlbwi_(int line);
static void tlbwr_(int line);
static void tlt_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void tlt_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void tlt_e13u32(int line, uint8_t var__op0, uint32_t var__op1);
static void tlti_e13xi16(int line, uint8_t var__op0, struct expr * var__op1);
static void tltu_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void tltu_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void tltu_e13u32(int line, uint8_t var__op0, uint32_t var__op1);
static void tltiu_e13xi16(int line, uint8_t var__op0, struct expr * var__op1);
static void tne_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void tne_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2);
static void tne_e13u32(int line, uint8_t var__op0, uint32_t var__op1);
static void tnei_e13xi16(int line, uint8_t var__op0, struct expr * var__op1);
static void wait_(int line);
static void xor_e13e13(int line, uint8_t var__op0, uint8_t var__op1);
static void abs_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void abs_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void add_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void add_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void add_s_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void add_d_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void ceil_w_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void ceil_w_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void cvt_d_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void cvt_d_w_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void cvt_d_l_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void cvt_s_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void cvt_s_w_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void cvt_s_l_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void cvt_w_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void cvt_w_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void div_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void div_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void div_s_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void div_d_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void floor_w_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void floor_w_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void mov_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void mov_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void movf_s_e12e12e11(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movf_d_e12e12e11(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movt_s_e12e12e11(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movt_d_e12e12e11(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movn_s_e12e12e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movn_d_e12e12e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movz_s_e12e12e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movz_d_e12e12e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void mul_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void mul_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void mul_s_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void mul_d_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void neg_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void neg_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void round_w_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void round_w_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void sqrt_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void sqrt_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void sub_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void sub_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void sub_s_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sub_d_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void trunc_w_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void trunc_w_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_f_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_un_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_eq_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ueq_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_olt_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ult_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ole_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ule_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_sf_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ngle_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_seq_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ngl_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_lt_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_nge_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_le_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ngt_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_f_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_un_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_eq_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ueq_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_olt_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ult_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ole_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ule_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_sf_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ngle_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_seq_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ngl_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_lt_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_nge_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_le_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_ngt_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1);
static void c_f_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_un_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_eq_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ueq_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_olt_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ult_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ole_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ule_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_sf_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ngle_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_seq_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ngl_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_lt_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_nge_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_le_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ngt_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_f_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_un_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_eq_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ueq_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_olt_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ult_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ole_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ule_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_sf_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ngle_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_seq_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ngl_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_lt_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_nge_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_le_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void c_ngt_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
/*
 * Encoding arith defined at ../../../targets/mips/encoding.def:230:4-232:6
 */
static void arith_e13e13e13(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   uint8_t var_op;
   uint8_t var_code;
   
   if ((!((var_specop < 42U)||(43U < var_specop))|| !((var_specop < 32U)||(39U < var_specop)))/* specarith3 */) {
      var_op = 0U /* SPECIAL */;
      var_code = 0U;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding shiftv defined at ../../../targets/mips/encoding.def:234:4-236:6
 */
static void shiftv_e13e13e13(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rt, uint8_t var_rs) {
   uint8_t var_op;
   uint8_t var_code;
   
   if ((!((var_specop < 6U)||(7U < var_specop))||(var_specop == 4U))/* specshift3 */) {
      var_op = 0U /* SPECIAL */;
      var_code = 0U;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding muldivraw defined at ../../../targets/mips/encoding.def:349:4-352:6
 */
static void muldivraw_e13e13(int line, uint8_t var_specop, uint8_t var_rs, uint8_t var_rt) {
   uint8_t var_op;
   uint8_t var_rd;
   uint8_t var_code;
   
   if (((((var_specop == 24U /* MULT */)||(var_specop == 25U /* MULTU */))||(var_specop == 26U /* DIV */))||(var_specop == 27U /* DIVU */))) {
      var_op = 0U /* SPECIAL */;
      var_rd = 0U /* z0 */;
      var_code = 0U;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding movnz defined at ../../../targets/mips/encoding.def:414:4-416:6
 */
static void movnz_e13e13e13(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   uint8_t var_op;
   uint8_t var_code;
   
   if (((var_specop == 10U /* MOVZ */)||(var_specop == 11U /* MOVN */))) {
      var_op = 0U /* SPECIAL */;
      var_code = 0U;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding mfhilo defined at ../../../targets/mips/encoding.def:419:4-423:6
 */
static void mfhilo_e13(int line, uint8_t var_specop, uint8_t var_rd) {
   uint8_t var_op;
   uint8_t var_rs;
   uint8_t var_rt;
   uint8_t var_code;
   
   if (((var_specop == 16U /* MFHI */)||(var_specop == 18U /* MFLO */))) {
      var_op = 0U /* SPECIAL */;
      var_rs = 0U /* z0 */;
      var_rt = 0U /* z0 */;
      var_code = 0U;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding mthilo defined at ../../../targets/mips/encoding.def:425:4-429:6
 */
static void mthilo_e13(int line, uint8_t var_specop, uint8_t var_rs) {
   uint8_t var_op;
   uint8_t var_rt;
   uint8_t var_rd;
   uint8_t var_code;
   
   if (((var_specop == 17U /* MTHI */)||(var_specop == 19U /* MTLO */))) {
      var_op = 0U /* SPECIAL */;
      var_rt = 0U /* z0 */;
      var_rd = 0U /* z0 */;
      var_code = 0U;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding sync defined at ../../../targets/mips/encoding.def:432:4-437:6
 */
static void sync_u5(int line, uint8_t var_code) {
   uint8_t var_op;
   uint8_t var_rs;
   uint8_t var_rt;
   uint8_t var_rd;
   uint8_t var_specop;
   
   if (true) {
      var_op = 0U /* SPECIAL */;
      var_rs = 0U /* z0 */;
      var_rt = 0U /* z0 */;
      var_rd = 0U /* z0 */;
      var_specop = 15U /* SYNC */;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding jr_raw defined at ../../../targets/mips/encoding.def:443:4-448:6
 */
static void jr_raw_e13(int line, uint8_t var_rs) {
   uint8_t var_op;
   uint8_t var_rt;
   uint8_t var_rd;
   uint8_t var_code;
   uint8_t var_specop;
   
   if (true) {
      var_op = 0U /* SPECIAL */;
      var_rt = 0U /* z0 */;
      var_rd = 0U /* z0 */;
      var_code = 0U;
      var_specop = 8U /* JR */;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding jalr_raw defined at ../../../targets/mips/encoding.def:449:4-453:6
 */
static void jalr_raw_e13e13(int line, uint8_t var_rd, uint8_t var_rs) {
   uint8_t var_op;
   uint8_t var_rt;
   uint8_t var_code;
   uint8_t var_specop;
   
   if (true) {
      var_op = 0U /* SPECIAL */;
      var_rt = 0U /* z0 */;
      var_code = 0U;
      var_specop = 9U /* JALR */;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding shift defined at ../../../targets/mips/encoding.def:471:4-475:6
 */
static void shift_e13e13u32(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rt, uint32_t var_bits) {
   uint8_t var_op;
   uint8_t var_rs;
   uint8_t var_code;
   
   if ((((var_specop == 0U /* SLL */)||(var_specop == 2U /* SRL */))||(var_specop == 3U /* SRA */))) {
      var_op = 0U /* SPECIAL */;
      var_rs = 0U /* z0 */;
      var_code =(uint8_t)var_bits;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding clo defined at ../../../targets/mips/encoding.def:797:4-54
 */
static void clo_e13e13(int line, uint8_t var_rd, uint8_t var_rs) {
   uint8_t var_code;
   uint8_t var_op;
   uint8_t var_spec2op;
   uint8_t var_rt;
   
   if (true) {
      var_code = 0U;
      var_op = 28U /* SPECIAL2 */;
      var_spec2op = 33U /* CLO */;
      var_rt = var_rd;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_spec2op & 63U)));
      }
      return;
   }
}

/*
 * Encoding clz defined at ../../../targets/mips/encoding.def:798:4-54
 */
static void clz_e13e13(int line, uint8_t var_rd, uint8_t var_rs) {
   uint8_t var_code;
   uint8_t var_op;
   uint8_t var_spec2op;
   uint8_t var_rt;
   
   if (true) {
      var_code = 0U;
      var_op = 28U /* SPECIAL2 */;
      var_spec2op = 32U /* CLZ */;
      var_rt = var_rd;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_spec2op & 63U)));
      }
      return;
   }
}

/*
 * Encoding madd defined at ../../../targets/mips/encoding.def:799:4-55
 */
static void madd_e13e13(int line, uint8_t var_rs, uint8_t var_rt) {
   uint8_t var_code;
   uint8_t var_op;
   uint8_t var_spec2op;
   uint8_t var_rd;
   
   if (true) {
      var_code = 0U;
      var_op = 28U /* SPECIAL2 */;
      var_spec2op = 0U /* MADD */;
      var_rd = 0U /* z0 */;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_spec2op & 63U)));
      }
      return;
   }
}

/*
 * Encoding maddu defined at ../../../targets/mips/encoding.def:800:4-56
 */
static void maddu_e13e13(int line, uint8_t var_rs, uint8_t var_rt) {
   uint8_t var_code;
   uint8_t var_op;
   uint8_t var_spec2op;
   uint8_t var_rd;
   
   if (true) {
      var_code = 0U;
      var_op = 28U /* SPECIAL2 */;
      var_spec2op = 1U /* MADDU */;
      var_rd = 0U /* z0 */;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_spec2op & 63U)));
      }
      return;
   }
}

/*
 * Encoding msub defined at ../../../targets/mips/encoding.def:801:4-55
 */
static void msub_e13e13(int line, uint8_t var_rs, uint8_t var_rt) {
   uint8_t var_code;
   uint8_t var_op;
   uint8_t var_spec2op;
   uint8_t var_rd;
   
   if (true) {
      var_code = 0U;
      var_op = 28U /* SPECIAL2 */;
      var_spec2op = 4U /* MSUB */;
      var_rd = 0U /* z0 */;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_spec2op & 63U)));
      }
      return;
   }
}

/*
 * Encoding msubu defined at ../../../targets/mips/encoding.def:802:4-56
 */
static void msubu_e13e13(int line, uint8_t var_rs, uint8_t var_rt) {
   uint8_t var_code;
   uint8_t var_op;
   uint8_t var_spec2op;
   uint8_t var_rd;
   
   if (true) {
      var_code = 0U;
      var_op = 28U /* SPECIAL2 */;
      var_spec2op = 5U /* MSUBU */;
      var_rd = 0U /* z0 */;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_spec2op & 63U)));
      }
      return;
   }
}

/*
 * Encoding mul defined at ../../../targets/mips/encoding.def:803:4-47
 */
static void mul_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   uint8_t var_code;
   uint8_t var_op;
   uint8_t var_spec2op;
   
   if (true) {
      var_code = 0U;
      var_op = 28U /* SPECIAL2 */;
      var_spec2op = 2U /* MUL */;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      reginfo_use_gp_reg(var_rd);
      {
         add32(line,(((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_spec2op & 63U)));
      }
      return;
   }
}

/*
 * Encoding break defined at ../../../targets/mips/encoding.def:853:4-34
 */
static void break_u10u10(int line, uint16_t var_code10a, uint16_t var_code10b) {
   uint8_t var_specop;
   uint8_t var_op;
   
   if (true) {
      var_specop = 13U /* BREAK */;
      var_op = 0U /* SPECIAL */;
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_code10a & 1023U)<< 16U))|((uint32_t)(var_code10b & 1023U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding syscall defined at ../../../targets/mips/encoding.def:871:4-873:6
 */
static void syscall_u32(int line, uint32_t var_code32) {
   uint8_t var_specop;
   uint8_t var_op;
   uint32_t var_code20;
   
   if (!(1048575U < var_code32)) {
      var_specop = 12U /* SYSCALL */;
      var_op = 0U /* SPECIAL */;
      var_code20 = var_code32;
      {
         add32(line,((((uint32_t)(var_op & 63U)<< 26U)|((var_code20 & 1048575U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding sdbbp defined at ../../../targets/mips/encoding.def:881:4-883:6
 */
static void sdbbp_u32(int line, uint32_t var_code32) {
   uint8_t var_spec2op;
   uint8_t var_op;
   uint32_t var_code20;
   
   if (!(1048575U < var_code32)) {
      var_spec2op = 63U /* SDBBP */;
      var_op = 28U /* SPECIAL2 */;
      var_code20 = var_code32;
      {
         add32(line,((((uint32_t)(var_op & 63U)<< 26U)|((var_code20 & 1048575U)<< 6U))|(uint32_t)(var_spec2op & 63U)));
      }
      return;
   }
}

/*
 * Encoding ctrap defined at ../../../targets/mips/encoding.def:892:4-894:6
 */
static void ctrap_e13e13u32(int line, uint8_t var_specop, uint8_t var_rs, uint8_t var_rt, uint32_t var_code32) {
   uint8_t var_op;
   uint16_t var_code10b;
   
   if ((!(1023U < var_code32)&&((var_specop == 54U)|| !((var_specop < 48U)||(52U < var_specop)))/* specops_ctrap */)) {
      var_op = 0U /* SPECIAL */;
      var_code10b =(uint16_t)var_code32;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_code10b & 1023U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding ctrapiraw defined at ../../../targets/mips/encoding.def:903:4-66
 */
static void ctrapiraw_e13i16(int line, uint8_t var_bcondop, uint8_t var_rs, int16_t var_imm) {
   uint8_t var_op;
   
   if (((var_bcondop == 14U)|| !((var_bcondop < 8U)||(12U < var_bcondop)))/* bcondops_ctrap */) {
      var_op = 1U /* BCOND */;
      reginfo_use_gp_reg(var_rs);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_bcondop & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding ctrapi defined at ../../../targets/mips/encoding.def:904:4-906:6
 */
static void ctrapi_e13xi16(int line, uint8_t var_bcondop, uint8_t var_rs, struct expr * var_immexpr) {
   uint8_t var_op;
   int16_t var_imm;
   
   if (((var_bcondop == 14U)|| !((var_bcondop < 8U)||(12U < var_bcondop)))/* bcondops_ctrap */) {
      var_op = 1U /* BCOND */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_bcondop & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding bcondraw defined at ../../../targets/mips/encoding.def:929:4-932:6
 */
static void bcondraw_e13xu32(int line, uint8_t var_bcondop, uint8_t var_rs, struct expr * var_branchtargetsym) {
   uint8_t var_op;
   struct expr * var_distance;
   int16_t var_branchtarget;
   
   if (true) {
      var_op = 1U /* BCOND */;
      var_distance = mkexpr_binary(mkexpr_binary(var_branchtargetsym, OP_SUB, mkexpr_label(label_declaredot(line))), OP_ADD, mkexpr_number(-4U));
      var_branchtarget = process_expr(line, mkexpr_modifier("branchoffset", var_distance), RELOC_FIELD_BRANCHTARGET, 0);
      reginfo_use_gp_reg(var_rs);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_bcondop & 31U)<< 16U))|(uint32_t)((uint16_t)var_branchtarget & 65535U)));
      }
      return;
   }
}

/*
 * Encoding j_raw defined at ../../../targets/mips/encoding.def:949:4-952:6
 */
static void j_raw_xu32(int line, struct expr * var_jumptargetsym) {
   uint32_t var_jumptarget;
   uint8_t var_op;
   
   if (true) {
      var_jumptarget = process_expr(line, var_jumptargetsym, RELOC_FIELD_JUMPTARGET, 0);
      var_op = 2U /* J */;
      {
         add32(line,(((uint32_t)(var_op & 63U)<< 26U)|(var_jumptarget & 67108863U)));
      }
      return;
   }
}

/*
 * Encoding jal_raw defined at ../../../targets/mips/encoding.def:953:4-956:6
 */
static void jal_raw_xu32(int line, struct expr * var_jumptargetsym) {
   uint32_t var_jumptarget;
   uint8_t var_op;
   
   if (true) {
      var_jumptarget = process_expr(line, var_jumptargetsym, RELOC_FIELD_JUMPTARGET, 0);
      var_op = 3U /* JAL */;
      {
         add32(line,(((uint32_t)(var_op & 63U)<< 26U)|(var_jumptarget & 67108863U)));
      }
      return;
   }
}

/*
 * Encoding branchraw defined at ../../../targets/mips/encoding.def:990:4-993:6
 */
static void branchraw_e13e13xu32(int line, uint8_t var_op, uint8_t var_rs, uint8_t var_rt, struct expr * var_branchtargetsym) {
   struct expr * var_distance;
   int16_t var_branchtarget;
   
   if (((((var_op == 4U /* BEQ */)||(var_op == 5U /* BNE */))||(var_op == 20U /* BEQL */))||(var_op == 21U /* BNEL */))) {
      var_distance = mkexpr_binary(mkexpr_binary(var_branchtargetsym, OP_SUB, mkexpr_label(label_declaredot(line))), OP_ADD, mkexpr_number(-4U));
      var_branchtarget = process_expr(line, mkexpr_modifier("branchoffset", var_distance), RELOC_FIELD_BRANCHTARGET, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)((uint16_t)var_branchtarget & 65535U)));
      }
      return;
   }
}

/*
 * Encoding branch0raw defined at ../../../targets/mips/encoding.def:1003:4-1007:6
 */
static void branch0raw_e13xu32(int line, uint8_t var_op, uint8_t var_rs, struct expr * var_branchtargetsym) {
   uint8_t var_rt;
   struct expr * var_distance;
   int16_t var_branchtarget;
   
   if (((((var_op == 6U /* BLEZ */)||(var_op == 7U /* BGTZ */))||(var_op == 22U /* BLEZL */))||(var_op == 23U /* BGTZL */))) {
      var_rt = 0U /* z0 */;
      var_distance = mkexpr_binary(mkexpr_binary(var_branchtargetsym, OP_SUB, mkexpr_label(label_declaredot(line))), OP_ADD, mkexpr_number(-4U));
      var_branchtarget = process_expr(line, mkexpr_modifier("branchoffset", var_distance), RELOC_FIELD_BRANCHTARGET, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)((uint16_t)var_branchtarget & 65535U)));
      }
      return;
   }
   if (((((var_op == 4U /* BEQ */)||(var_op == 5U /* BNE */))||(var_op == 20U /* BEQL */))||(var_op == 21U /* BNEL */))) {
      var_rt = 0U /* z0 */;
      var_distance = mkexpr_binary(mkexpr_binary(var_branchtargetsym, OP_SUB, mkexpr_label(label_declaredot(line))), OP_ADD, mkexpr_number(-4U));
      var_branchtarget = process_expr(line, mkexpr_modifier("branchoffset", var_distance), RELOC_FIELD_BRANCHTARGET, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)((uint16_t)var_branchtarget & 65535U)));
      }
      return;
   }
}

/*
 * Encoding bneplain defined at ../../../targets/mips/encoding.def:1044:4-1046:6
 */
static void bneplain_e13e13i16(int line, uint8_t var_rs, uint8_t var_rt, int16_t var_branchtarget) {
   uint8_t var_op;
   
   if (true) {
      var_op = 5U /* BNE */;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)((uint16_t)var_branchtarget & 65535U)));
      }
      return;
   }
}

/*
 * Encoding arithimm defined at ../../../targets/mips/encoding.def:1051:4-1053:6
 */
static void arithimm_e13e13xi16(int line, uint8_t var_op, uint8_t var_rt, uint8_t var_rs, struct expr * var_immexpr) {
   int16_t var_imm;
   
   if (((((var_op == 8U /* ADDI */)||(var_op == 9U /* ADDIU */))||(var_op == 10U /* SLTI */))||(var_op == 11U /* SLTIU */))) {
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding arithimmraw defined at ../../../targets/mips/encoding.def:1054:4-74
 */
static void arithimmraw_e13e13i16(int line, uint8_t var_op, uint8_t var_rt, uint8_t var_rs, int16_t var_imm) {
   
   if (((((var_op == 8U /* ADDI */)||(var_op == 9U /* ADDIU */))||(var_op == 10U /* SLTI */))||(var_op == 11U /* SLTIU */))) {
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding loadraw defined at ../../../targets/mips/encoding.def:1055:4-80
 */
static void loadraw_e13e13i16(int line, uint8_t var_op, uint8_t var_rt, uint8_t var_rs, int16_t var_imm) {
   
   if (((((((((var_op == 32U /* LB */)||(var_op == 33U /* LH */))||(var_op == 34U /* LWL */))||(var_op == 35U /* LW */))||(var_op == 36U /* LBU */))||(var_op == 37U /* LHU */))||(var_op == 38U /* LWR */))||(var_op == 48U /* LL */))) {
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding load defined at ../../../targets/mips/encoding.def:1056:4-1059:6
 */
static void load_e13mem(int line, uint8_t var_op, uint8_t var_rt, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   int16_t var_imm;
   
   if (((((((((var_op == 32U /* LB */)||(var_op == 33U /* LH */))||(var_op == 34U /* LWL */))||(var_op == 35U /* LW */))||(var_op == 36U /* LBU */))||(var_op == 37U /* LHU */))||(var_op == 38U /* LWR */))||(var_op == 48U /* LL */))) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding storeraw defined at ../../../targets/mips/encoding.def:1075:4-71
 */
static void storeraw_e13e13i16(int line, uint8_t var_op, uint8_t var_rt, uint8_t var_rs, int16_t var_imm) {
   
   if (((((((var_op == 40U /* SB */)||(var_op == 41U /* SH */))||(var_op == 42U /* SWL */))||(var_op == 43U /* SW */))||(var_op == 46U /* SWR */))||(var_op == 56U /* SC */))) {
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding store defined at ../../../targets/mips/encoding.def:1076:4-1079:6
 */
static void store_e13mem(int line, uint8_t var_op, uint8_t var_rt, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   int16_t var_imm;
   
   if (((((((var_op == 40U /* SB */)||(var_op == 41U /* SH */))||(var_op == 42U /* SWL */))||(var_op == 43U /* SW */))||(var_op == 46U /* SWR */))||(var_op == 56U /* SC */))) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding cache defined at ../../../targets/mips/encoding.def:1139:4-1144:6
 */
static void cache_u32mem(int line, uint32_t var_cacheop32, struct compound_mem * var_addr) {
   uint8_t var_op;
   uint8_t var_cacheop;
   struct expr * var_immexpr;
   uint8_t var_rs;
   int16_t var_imm;
   
   if (!(31U < var_cacheop32)) {
      var_op = 47U /* CACHE */;
      var_cacheop =(uint8_t)var_cacheop32;
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_cacheop & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding pref defined at ../../../targets/mips/encoding.def:1157:4-1162:6
 */
static void pref_u32mem(int line, uint32_t var_prefop32, struct compound_mem * var_addr) {
   uint8_t var_op;
   uint8_t var_prefop;
   struct expr * var_immexpr;
   uint8_t var_rs;
   int16_t var_imm;
   
   if (!(31U < var_prefop32)) {
      var_op = 51U /* LWC3 */;
      var_prefop =(uint8_t)var_prefop32;
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_prefop & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding bitimm defined at ../../../targets/mips/encoding.def:1175:4-1177:6
 */
static void bitimm_e13e13xu16(int line, uint8_t var_op, uint8_t var_rt, uint8_t var_rs, struct expr * var_uimmexpr) {
   uint16_t var_uimm;
   
   if ((((var_op == 12U /* ANDI */)||(var_op == 13U /* ORI */))||(var_op == 14U /* XORI */))) {
      var_uimm = process_expr(line, var_uimmexpr, RELOC_FIELD_UIMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)(var_uimm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding bitimmraw defined at ../../../targets/mips/encoding.def:1178:4-64
 */
static void bitimmraw_e13e13u16(int line, uint8_t var_op, uint8_t var_rt, uint8_t var_rs, uint16_t var_uimm) {
   
   if ((((var_op == 12U /* ANDI */)||(var_op == 13U /* ORI */))||(var_op == 14U /* XORI */))) {
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)(var_uimm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding luiraw defined at ../../../targets/mips/encoding.def:1179:4-1182:6
 */
static void luiraw_e13u16(int line, uint8_t var_rt, uint16_t var_uimm) {
   uint8_t var_op;
   uint8_t var_rs;
   
   if (true) {
      var_op = 15U /* LUI */;
      var_rs = 0U /* z0 */;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)(var_uimm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding lui defined at ../../../targets/mips/encoding.def:1183:4-1187:6
 */
static void lui_e13xu16(int line, uint8_t var_rt, struct expr * var_uimmexpr) {
   uint8_t var_op;
   uint8_t var_rs;
   uint16_t var_uimm;
   
   if (true) {
      var_op = 15U /* LUI */;
      var_rs = 0U /* z0 */;
      var_uimm = process_expr(line, var_uimmexpr, RELOC_FIELD_UIMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rt);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|(uint32_t)(var_uimm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding mfc0 defined at ../../../targets/mips/encoding.def:1200:4-1202:6
 */
static void mfc0_e13e8u3(int line, uint8_t var_rt, uint8_t var_rd_cop0, uint8_t var_sel) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var__Z25;
   uint8_t var__Z26;
   
   if (true) {
      var_co = 0U;
      var_op = 16U /* COP0 */;
      var_gencopop = 0U /* MF */;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop0_reg(var_rd_cop0);
      var__Z25 = 0U;
      var__Z26 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop0 & 31U)<< 11U))|((uint32_t)(var__Z25 & 31U)<< 6U))|((uint32_t)(var__Z26 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding mfc0 defined at ../../../targets/mips/encoding.def:1203:4-1205:6
 */
static void mfc0_e13e8(int line, uint8_t var_rt, uint8_t var_rd_cop0) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z25;
   uint8_t var__Z26;
   
   if (true) {
      var_co = 0U;
      var_op = 16U /* COP0 */;
      var_gencopop = 0U /* MF */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop0_reg(var_rd_cop0);
      var__Z25 = 0U;
      var__Z26 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop0 & 31U)<< 11U))|((uint32_t)(var__Z25 & 31U)<< 6U))|((uint32_t)(var__Z26 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding mtc0 defined at ../../../targets/mips/encoding.def:1206:4-1208:6
 */
static void mtc0_e13e8u3(int line, uint8_t var_rt, uint8_t var_rd_cop0, uint8_t var_sel) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var__Z25;
   uint8_t var__Z26;
   
   if (true) {
      var_co = 0U;
      var_op = 16U /* COP0 */;
      var_gencopop = 4U /* MT */;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop0_reg(var_rd_cop0);
      var__Z25 = 0U;
      var__Z26 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop0 & 31U)<< 11U))|((uint32_t)(var__Z25 & 31U)<< 6U))|((uint32_t)(var__Z26 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding mtc0 defined at ../../../targets/mips/encoding.def:1209:4-1211:6
 */
static void mtc0_e13e8(int line, uint8_t var_rt, uint8_t var_rd_cop0) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z25;
   uint8_t var__Z26;
   
   if (true) {
      var_co = 0U;
      var_op = 16U /* COP0 */;
      var_gencopop = 4U /* MT */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop0_reg(var_rd_cop0);
      var__Z25 = 0U;
      var__Z26 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop0 & 31U)<< 11U))|((uint32_t)(var__Z25 & 31U)<< 6U))|((uint32_t)(var__Z26 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding cop0 defined at ../../../targets/mips/encoding.def:1219:4-1221:6
 */
static void cop0_(int line, uint8_t var_cop0op) {
   uint8_t var_co;
   uint8_t var_op;
   uint32_t var_code19;
   
   if (true) {
      var_co = 1U;
      var_op = 16U /* COP0 */;
      var_code19 = 0U;
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((var_code19 & 524287U)<< 6U))|(uint32_t)(var_cop0op & 63U)));
      }
      return;
   }
}

/*
 * Encoding wait defined at ../../../targets/mips/encoding.def:1222:4-1225:6
 */
static void wait_u32(int line, uint32_t var_code32) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_cop0op;
   uint32_t var_code19;
   
   if (!(524287U < var_code32)) {
      var_co = 1U;
      var_op = 16U /* COP0 */;
      var_cop0op = 32U /* WAIT */;
      var_code19 = var_code32;
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((var_code19 & 524287U)<< 6U))|(uint32_t)(var_cop0op & 63U)));
      }
      return;
   }
}

/*
 * Encoding mfc2 defined at ../../../targets/mips/encoding.def:1233:4-1235:6
 */
static void mfc2_e13e9u3(int line, uint8_t var_rt, uint8_t var_rd_cop2, uint8_t var_sel) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var__Z29;
   uint8_t var__Z30;
   
   if (true) {
      var_co = 0U;
      var_op = 18U /* COP2 */;
      var_gencopop = 0U /* MF */;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop2_reg(var_rd_cop2);
      var__Z29 = 0U;
      var__Z30 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop2 & 31U)<< 11U))|((uint32_t)(var__Z29 & 31U)<< 6U))|((uint32_t)(var__Z30 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding mfc2 defined at ../../../targets/mips/encoding.def:1236:4-1238:6
 */
static void mfc2_e13e9(int line, uint8_t var_rt, uint8_t var_rd_cop2) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z29;
   uint8_t var__Z30;
   
   if (true) {
      var_co = 0U;
      var_op = 18U /* COP2 */;
      var_gencopop = 0U /* MF */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop2_reg(var_rd_cop2);
      var__Z29 = 0U;
      var__Z30 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop2 & 31U)<< 11U))|((uint32_t)(var__Z29 & 31U)<< 6U))|((uint32_t)(var__Z30 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding mtc2 defined at ../../../targets/mips/encoding.def:1239:4-1241:6
 */
static void mtc2_e13e9u3(int line, uint8_t var_rt, uint8_t var_rd_cop2, uint8_t var_sel) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var__Z29;
   uint8_t var__Z30;
   
   if (true) {
      var_co = 0U;
      var_op = 18U /* COP2 */;
      var_gencopop = 4U /* MT */;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop2_reg(var_rd_cop2);
      var__Z29 = 0U;
      var__Z30 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop2 & 31U)<< 11U))|((uint32_t)(var__Z29 & 31U)<< 6U))|((uint32_t)(var__Z30 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding mtc2 defined at ../../../targets/mips/encoding.def:1242:4-1244:6
 */
static void mtc2_e13e9(int line, uint8_t var_rt, uint8_t var_rd_cop2) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z29;
   uint8_t var__Z30;
   
   if (true) {
      var_co = 0U;
      var_op = 18U /* COP2 */;
      var_gencopop = 4U /* MT */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop2_reg(var_rd_cop2);
      var__Z29 = 0U;
      var__Z30 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop2 & 31U)<< 11U))|((uint32_t)(var__Z29 & 31U)<< 6U))|((uint32_t)(var__Z30 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding cfc2 defined at ../../../targets/mips/encoding.def:1245:4-1247:6
 */
static void cfc2_e13e9(int line, uint8_t var_rt, uint8_t var_rd_cop2) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z29;
   uint8_t var__Z30;
   
   if (true) {
      var_co = 0U;
      var_op = 18U /* COP2 */;
      var_gencopop = 2U /* CF */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop2_reg(var_rd_cop2);
      var__Z29 = 0U;
      var__Z30 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop2 & 31U)<< 11U))|((uint32_t)(var__Z29 & 31U)<< 6U))|((uint32_t)(var__Z30 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding ctc2 defined at ../../../targets/mips/encoding.def:1248:4-1250:6
 */
static void ctc2_e13e9(int line, uint8_t var_rt, uint8_t var_rd_cop2) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z29;
   uint8_t var__Z30;
   
   if (true) {
      var_co = 0U;
      var_op = 18U /* COP2 */;
      var_gencopop = 6U /* CT */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop2_reg(var_rd_cop2);
      var__Z29 = 0U;
      var__Z30 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop2 & 31U)<< 11U))|((uint32_t)(var__Z29 & 31U)<< 6U))|((uint32_t)(var__Z30 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding bc2rawraw defined at ../../../targets/mips/encoding.def:1257:4-1260:6
 */
static void bc2rawraw_e11xu32(int line, uint8_t var_nd, uint8_t var_tf, uint8_t var_cc, struct expr * var_branchtargetsym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   struct expr * var_distance;
   int16_t var_branchtarget;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 18U /* COP2 */;
      var_distance = mkexpr_binary(mkexpr_binary(var_branchtargetsym, OP_SUB, mkexpr_label(label_declaredot(line))), OP_ADD, mkexpr_number(-4U));
      var_branchtarget = process_expr(line, mkexpr_modifier("branchoffset", var_distance), RELOC_FIELD_BRANCHTARGET, 0);
      {
         add32(line,((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_cc & 7U)<< 18U))|((uint32_t)(var_nd & 1U)<< 17U))|((uint32_t)(var_tf & 1U)<< 16U))|(uint32_t)((uint16_t)var_branchtarget & 65535U)));
      }
      return;
   }
}

/*
 * Encoding lwc2 defined at ../../../targets/mips/encoding.def:1281:4-1285:6
 */
static void lwc2_e9mem(int line, uint8_t var_rt_cop2, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   uint8_t var_op;
   int16_t var_imm;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_op = 50U /* LWC2 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_cop2_reg(var_rt_cop2);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt_cop2 & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding ldc2 defined at ../../../targets/mips/encoding.def:1293:4-1297:6
 */
static void ldc2_e9mem(int line, uint8_t var_rt_cop2, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   uint8_t var_op;
   int16_t var_imm;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_op = 54U /* LDC2 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_cop2_reg(var_rt_cop2);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt_cop2 & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding swc2 defined at ../../../targets/mips/encoding.def:1305:4-1309:6
 */
static void swc2_e9mem(int line, uint8_t var_rt_cop2, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   uint8_t var_op;
   int16_t var_imm;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_op = 58U /* SWC2 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_cop2_reg(var_rt_cop2);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt_cop2 & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding sdc2 defined at ../../../targets/mips/encoding.def:1317:4-1321:6
 */
static void sdc2_e9mem(int line, uint8_t var_rt_cop2, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   uint8_t var_op;
   int16_t var_imm;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_op = 62U /* SDC2 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_cop2_reg(var_rt_cop2);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt_cop2 & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding cop2 defined at ../../../targets/mips/encoding.def:1334:4-1336:6
 */
static void cop2_u32(int line, uint32_t var_cofunraw) {
   uint8_t var_co;
   uint8_t var_op;
   uint32_t var_cofun;
   
   if (!(33554431U < var_cofunraw)) {
      var_co = 1U;
      var_op = 18U /* COP2 */;
      var_cofun = var_cofunraw;
      {
         add32(line,((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|(var_cofun & 33554431U)));
      }
      return;
   }
}

/*
 * Encoding mfc3 defined at ../../../targets/mips/encoding.def:1345:4-1347:6
 */
static void mfc3_e13e10u3(int line, uint8_t var_rt, uint8_t var_rd_cop3, uint8_t var_sel) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var__Z35;
   uint8_t var__Z36;
   
   if (true) {
      var_co = 0U;
      var_op = 19U /* COP3 */;
      var_gencopop = 0U /* MF */;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop3_reg(var_rd_cop3);
      var__Z35 = 0U;
      var__Z36 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop3 & 31U)<< 11U))|((uint32_t)(var__Z35 & 31U)<< 6U))|((uint32_t)(var__Z36 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding mfc3 defined at ../../../targets/mips/encoding.def:1348:4-1350:6
 */
static void mfc3_e13e10(int line, uint8_t var_rt, uint8_t var_rd_cop3) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z35;
   uint8_t var__Z36;
   
   if (true) {
      var_co = 0U;
      var_op = 19U /* COP3 */;
      var_gencopop = 0U /* MF */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop3_reg(var_rd_cop3);
      var__Z35 = 0U;
      var__Z36 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop3 & 31U)<< 11U))|((uint32_t)(var__Z35 & 31U)<< 6U))|((uint32_t)(var__Z36 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding mtc3 defined at ../../../targets/mips/encoding.def:1351:4-1353:6
 */
static void mtc3_e13e10u3(int line, uint8_t var_rt, uint8_t var_rd_cop3, uint8_t var_sel) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var__Z35;
   uint8_t var__Z36;
   
   if (true) {
      var_co = 0U;
      var_op = 19U /* COP3 */;
      var_gencopop = 4U /* MT */;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop3_reg(var_rd_cop3);
      var__Z35 = 0U;
      var__Z36 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop3 & 31U)<< 11U))|((uint32_t)(var__Z35 & 31U)<< 6U))|((uint32_t)(var__Z36 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding mtc3 defined at ../../../targets/mips/encoding.def:1354:4-1356:6
 */
static void mtc3_e13e10(int line, uint8_t var_rt, uint8_t var_rd_cop3) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z35;
   uint8_t var__Z36;
   
   if (true) {
      var_co = 0U;
      var_op = 19U /* COP3 */;
      var_gencopop = 4U /* MT */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop3_reg(var_rd_cop3);
      var__Z35 = 0U;
      var__Z36 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop3 & 31U)<< 11U))|((uint32_t)(var__Z35 & 31U)<< 6U))|((uint32_t)(var__Z36 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding cfc3 defined at ../../../targets/mips/encoding.def:1357:4-1359:6
 */
static void cfc3_e13e10(int line, uint8_t var_rt, uint8_t var_rd_cop3) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z35;
   uint8_t var__Z36;
   
   if (true) {
      var_co = 0U;
      var_op = 19U /* COP3 */;
      var_gencopop = 2U /* CF */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop3_reg(var_rd_cop3);
      var__Z35 = 0U;
      var__Z36 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop3 & 31U)<< 11U))|((uint32_t)(var__Z35 & 31U)<< 6U))|((uint32_t)(var__Z36 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding ctc3 defined at ../../../targets/mips/encoding.def:1360:4-1362:6
 */
static void ctc3_e13e10(int line, uint8_t var_rt, uint8_t var_rd_cop3) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z35;
   uint8_t var__Z36;
   
   if (true) {
      var_co = 0U;
      var_op = 19U /* COP3 */;
      var_gencopop = 6U /* CT */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_cop3_reg(var_rd_cop3);
      var__Z35 = 0U;
      var__Z36 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_rd_cop3 & 31U)<< 11U))|((uint32_t)(var__Z35 & 31U)<< 6U))|((uint32_t)(var__Z36 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding bc3rawraw defined at ../../../targets/mips/encoding.def:1369:4-1372:6
 */
static void bc3rawraw_e11xu32(int line, uint8_t var_nd, uint8_t var_tf, uint8_t var_cc, struct expr * var_branchtargetsym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   struct expr * var_distance;
   int16_t var_branchtarget;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 19U /* COP3 */;
      var_distance = mkexpr_binary(mkexpr_binary(var_branchtargetsym, OP_SUB, mkexpr_label(label_declaredot(line))), OP_ADD, mkexpr_number(-4U));
      var_branchtarget = process_expr(line, mkexpr_modifier("branchoffset", var_distance), RELOC_FIELD_BRANCHTARGET, 0);
      {
         add32(line,((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_cc & 7U)<< 18U))|((uint32_t)(var_nd & 1U)<< 17U))|((uint32_t)(var_tf & 1U)<< 16U))|(uint32_t)((uint16_t)var_branchtarget & 65535U)));
      }
      return;
   }
}

/*
 * Encoding lwc3 defined at ../../../targets/mips/encoding.def:1393:4-1397:6
 */
static void lwc3_e10mem(int line, uint8_t var_rt_cop3, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   uint8_t var_op;
   int16_t var_imm;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_op = 51U /* LWC3 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_cop3_reg(var_rt_cop3);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt_cop3 & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding ldc3 defined at ../../../targets/mips/encoding.def:1405:4-1409:6
 */
static void ldc3_e10mem(int line, uint8_t var_rt_cop3, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   uint8_t var_op;
   int16_t var_imm;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_op = 55U /* LDC3 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_cop3_reg(var_rt_cop3);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt_cop3 & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding swc3 defined at ../../../targets/mips/encoding.def:1417:4-1421:6
 */
static void swc3_e10mem(int line, uint8_t var_rt_cop3, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   uint8_t var_op;
   int16_t var_imm;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_op = 59U /* SWC3 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_cop3_reg(var_rt_cop3);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt_cop3 & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding sdc3 defined at ../../../targets/mips/encoding.def:1429:4-1433:6
 */
static void sdc3_e10mem(int line, uint8_t var_rt_cop3, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   uint8_t var_op;
   int16_t var_imm;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_op = 63U /* SDC3 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_cop3_reg(var_rt_cop3);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_rt_cop3 & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding cop3 defined at ../../../targets/mips/encoding.def:1445:4-1447:6
 */
static void cop3_u32(int line, uint32_t var_cofunraw) {
   uint8_t var_co;
   uint8_t var_op;
   uint32_t var_cofun;
   
   if (!(33554431U < var_cofunraw)) {
      var_co = 1U;
      var_op = 19U /* COP3 */;
      var_cofun = var_cofunraw;
      {
         add32(line,((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|(var_cofun & 33554431U)));
      }
      return;
   }
}

/*
 * Encoding mfc1 defined at ../../../targets/mips/encoding.def:1458:4-1460:6
 */
static void mfc1_e13e12(int line, uint8_t var_rt, uint8_t var_fs) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z41;
   uint8_t var__Z42;
   
   if (true) {
      var_co = 0U;
      var_op = 17U /* COP1 */;
      var_gencopop = 0U /* MF */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_fp_reg(var_fs);
      var__Z41 = 0U;
      var__Z42 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_fs & 31U)<< 11U))|((uint32_t)(var__Z41 & 31U)<< 6U))|((uint32_t)(var__Z42 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding mtc1 defined at ../../../targets/mips/encoding.def:1465:4-1467:6
 */
static void mtc1_e13e12(int line, uint8_t var_rt, uint8_t var_fs) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z41;
   uint8_t var__Z42;
   
   if (true) {
      var_co = 0U;
      var_op = 17U /* COP1 */;
      var_gencopop = 4U /* MT */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_fp_reg(var_fs);
      var__Z41 = 0U;
      var__Z42 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_fs & 31U)<< 11U))|((uint32_t)(var__Z41 & 31U)<< 6U))|((uint32_t)(var__Z42 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding cfc1 defined at ../../../targets/mips/encoding.def:1468:4-1470:6
 */
static void cfc1_e13e12(int line, uint8_t var_rt, uint8_t var_fs) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z41;
   uint8_t var__Z42;
   
   if (true) {
      var_co = 0U;
      var_op = 17U /* COP1 */;
      var_gencopop = 2U /* CF */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_fp_reg(var_fs);
      var__Z41 = 0U;
      var__Z42 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_fs & 31U)<< 11U))|((uint32_t)(var__Z41 & 31U)<< 6U))|((uint32_t)(var__Z42 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding ctc1 defined at ../../../targets/mips/encoding.def:1471:4-1473:6
 */
static void ctc1_e13e12(int line, uint8_t var_rt, uint8_t var_fs) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_gencopop;
   uint8_t var_sel;
   uint8_t var__Z41;
   uint8_t var__Z42;
   
   if (true) {
      var_co = 0U;
      var_op = 17U /* COP1 */;
      var_gencopop = 6U /* CT */;
      var_sel = 0U;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_fp_reg(var_fs);
      var__Z41 = 0U;
      var__Z42 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_fs & 31U)<< 11U))|((uint32_t)(var__Z41 & 31U)<< 6U))|((uint32_t)(var__Z42 & 7U)<< 3U))|(uint32_t)(var_sel & 7U)));
      }
      return;
   }
}

/*
 * Encoding bc1rawraw defined at ../../../targets/mips/encoding.def:1480:4-1483:6
 */
static void bc1rawraw_e11xu32(int line, uint8_t var_nd, uint8_t var_tf, uint8_t var_cc, struct expr * var_branchtargetsym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   struct expr * var_distance;
   int16_t var_branchtarget;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 17U /* COP1 */;
      var_distance = mkexpr_binary(mkexpr_binary(var_branchtargetsym, OP_SUB, mkexpr_label(label_declaredot(line))), OP_ADD, mkexpr_number(-4U));
      var_branchtarget = process_expr(line, mkexpr_modifier("branchoffset", var_distance), RELOC_FIELD_BRANCHTARGET, 0);
      {
         add32(line,((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_gencopop & 15U)<< 21U))|((uint32_t)(var_cc & 7U)<< 18U))|((uint32_t)(var_nd & 1U)<< 17U))|((uint32_t)(var_tf & 1U)<< 16U))|(uint32_t)((uint16_t)var_branchtarget & 65535U)));
      }
      return;
   }
}

/*
 * Encoding lwc1 defined at ../../../targets/mips/encoding.def:1504:4-1508:6
 */
static void lwc1_e12mem(int line, uint8_t var_ft, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   uint8_t var_op;
   int16_t var_imm;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_op = 49U /* LWC1 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_fp_reg(var_ft);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_ft & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding ldc1 defined at ../../../targets/mips/encoding.def:1516:4-1520:6
 */
static void ldc1_e12mem(int line, uint8_t var_ft, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   uint8_t var_op;
   int16_t var_imm;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_op = 53U /* LDC1 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_fp_reg(var_ft);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_ft & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding swc1 defined at ../../../targets/mips/encoding.def:1528:4-1532:6
 */
static void swc1_e12mem(int line, uint8_t var_ft, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   uint8_t var_op;
   int16_t var_imm;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_op = 57U /* SWC1 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_fp_reg(var_ft);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_ft & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding sdc1 defined at ../../../targets/mips/encoding.def:1540:4-1544:6
 */
static void sdc1_e12mem(int line, uint8_t var_ft, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   uint8_t var_op;
   int16_t var_imm;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      var_op = 61U /* SDC1 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM, 0);
      reginfo_use_gp_reg(var_rs);
      reginfo_use_fp_reg(var_ft);
      {
         add32(line,(((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_ft & 31U)<< 16U))|(uint32_t)((uint16_t)var_imm & 65535U)));
      }
      return;
   }
}

/*
 * Encoding fparith defined at ../../../targets/mips/encoding.def:1556:4-1557:39
 */
static void fparith_e12e12e12(int line, uint8_t var_cop1op, uint8_t var_fmt, uint8_t var_fd, uint8_t var_fs, uint8_t var_ft) {
   uint8_t var_co;
   uint8_t var_op;
   
   if (((((var_cop1op == 0U /* FADD */)||(var_cop1op == 1U /* FSUB */))||(var_cop1op == 2U /* FMUL */))||(var_cop1op == 3U /* FDIV */))) {
      var_co = 1U;
      var_op = 17U /* COP1 */;
      reginfo_use_fp_reg(var_ft);
      reginfo_use_fp_reg(var_fs);
      reginfo_use_fp_reg(var_fd);
      {
         add32(line,((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_fmt & 15U)<< 21U))|((uint32_t)(var_ft & 31U)<< 16U))|((uint32_t)(var_fs & 31U)<< 11U))|((uint32_t)(var_fd & 31U)<< 6U))|(uint32_t)(var_cop1op & 63U)));
      }
      return;
   }
}

/*
 * Encoding fparith defined at ../../../targets/mips/encoding.def:1558:4-1563:6
 */
static void fparith_e12e12(int line, uint8_t var_cop1op, uint8_t var_fmt, uint8_t var_fd, uint8_t var_fs) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_ft;
   
   if ((((((((((((var_cop1op == 4U /* FSQRT */)||(var_cop1op == 5U /* FABS */))||(var_cop1op == 6U /* FMOV */))||(var_cop1op == 7U /* FNEG */))||(var_cop1op == 12U /* ROUND_W */))||(var_cop1op == 13U /* TRUNC_W */))||(var_cop1op == 14U /* CEIL_W */))||(var_cop1op == 15U /* FLOOR_W */))||(var_cop1op == 32U /* CVT_S */))||(var_cop1op == 33U /* CVT_D */))||(var_cop1op == 36U /* CVT_W */))) {
      var_co = 1U;
      var_op = 17U /* COP1 */;
      var_ft = 0U /* f0 */;
      reginfo_use_fp_reg(var_ft);
      reginfo_use_fp_reg(var_fs);
      reginfo_use_fp_reg(var_fd);
      {
         add32(line,((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_fmt & 15U)<< 21U))|((uint32_t)(var_ft & 31U)<< 16U))|((uint32_t)(var_fs & 31U)<< 11U))|((uint32_t)(var_fd & 31U)<< 6U))|(uint32_t)(var_cop1op & 63U)));
      }
      return;
   }
}

/*
 * Encoding fmovnz defined at ../../../targets/mips/encoding.def:1572:4-69
 */
static void fmovnz_e12e12e13(int line, uint8_t var_cop1op, uint8_t var_fmt, uint8_t var_fd, uint8_t var_fs, uint8_t var_rt) {
   uint8_t var_co;
   uint8_t var_op;
   
   if (((var_cop1op == 18U /* FMOVZ */)||(var_cop1op == 19U /* FMOVN */))) {
      var_co = 1U;
      var_op = 17U /* COP1 */;
      reginfo_use_gp_reg(var_rt);
      reginfo_use_fp_reg(var_fs);
      reginfo_use_fp_reg(var_fd);
      {
         add32(line,((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_fmt & 15U)<< 21U))|((uint32_t)(var_rt & 31U)<< 16U))|((uint32_t)(var_fs & 31U)<< 11U))|((uint32_t)(var_fd & 31U)<< 6U))|(uint32_t)(var_cop1op & 63U)));
      }
      return;
   }
}

/*
 * Encoding fmovf defined at ../../../targets/mips/encoding.def:1578:4-45
 */
static void fmovf_e12e12e11(int line, uint8_t var_fmt, uint8_t var_fd, uint8_t var_fs, uint8_t var_cc) {
   uint8_t var_cop1op;
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_tf;
   uint8_t var__Z48;
   
   if (true) {
      var_cop1op = 17U /* MOVCF */;
      var_co = 1U;
      var_op = 17U /* COP1 */;
      var_tf = 0U;
      reginfo_use_fp_reg(var_fs);
      reginfo_use_fp_reg(var_fd);
      var__Z48 = 0U;
      {
         add32(line,((((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_fmt & 15U)<< 21U))|((uint32_t)(var_cc & 7U)<< 18U))|((uint32_t)(var__Z48 & 1U)<< 17U))|((uint32_t)(var_tf & 1U)<< 16U))|((uint32_t)(var_fs & 31U)<< 11U))|((uint32_t)(var_fd & 31U)<< 6U))|(uint32_t)(var_cop1op & 63U)));
      }
      return;
   }
}

/*
 * Encoding fmovt defined at ../../../targets/mips/encoding.def:1579:4-45
 */
static void fmovt_e12e12e11(int line, uint8_t var_fmt, uint8_t var_fd, uint8_t var_fs, uint8_t var_cc) {
   uint8_t var_cop1op;
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var_tf;
   uint8_t var__Z48;
   
   if (true) {
      var_cop1op = 17U /* MOVCF */;
      var_co = 1U;
      var_op = 17U /* COP1 */;
      var_tf = 1U;
      reginfo_use_fp_reg(var_fs);
      reginfo_use_fp_reg(var_fd);
      var__Z48 = 0U;
      {
         add32(line,((((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_fmt & 15U)<< 21U))|((uint32_t)(var_cc & 7U)<< 18U))|((uint32_t)(var__Z48 & 1U)<< 17U))|((uint32_t)(var_tf & 1U)<< 16U))|((uint32_t)(var_fs & 31U)<< 11U))|((uint32_t)(var_fd & 31U)<< 6U))|(uint32_t)(var_cop1op & 63U)));
      }
      return;
   }
}

/*
 * Encoding movf defined at ../../../targets/mips/encoding.def:1585:4-39
 */
static void movf_e13e13e11(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_cc) {
   uint8_t var_specop;
   uint8_t var_code;
   uint8_t var_op;
   uint8_t var_tf;
   uint8_t var__Z50;
   
   if (true) {
      var_specop = 1U /* MOVC */;
      var_code = 0U;
      var_op = 0U /* SPECIAL */;
      var_tf = 0U;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rd);
      var__Z50 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_cc & 7U)<< 18U))|((uint32_t)(var__Z50 & 1U)<< 17U))|((uint32_t)(var_tf & 1U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding movt defined at ../../../targets/mips/encoding.def:1588:4-39
 */
static void movt_e13e13e11(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_cc) {
   uint8_t var_specop;
   uint8_t var_code;
   uint8_t var_op;
   uint8_t var_tf;
   uint8_t var__Z50;
   
   if (true) {
      var_specop = 1U /* MOVC */;
      var_code = 0U;
      var_op = 0U /* SPECIAL */;
      var_tf = 1U;
      reginfo_use_gp_reg(var_rs);
      reginfo_use_gp_reg(var_rd);
      var__Z50 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_rs & 31U)<< 21U))|((uint32_t)(var_cc & 7U)<< 18U))|((uint32_t)(var__Z50 & 1U)<< 17U))|((uint32_t)(var_tf & 1U)<< 16U))|((uint32_t)(var_rd & 31U)<< 11U))|((uint32_t)(var_code & 31U)<< 6U))|(uint32_t)(var_specop & 63U)));
      }
      return;
   }
}

/*
 * Encoding c defined at ../../../targets/mips/encoding.def:1596:4-62
 */
static void c_e11e12e12(int line, uint8_t var_cop1op, uint8_t var_fmt, uint8_t var_cc_alt, uint8_t var_fs, uint8_t var_ft) {
   uint8_t var_co;
   uint8_t var_op;
   uint8_t var__Z52;
   
   if (!((var_cop1op < 48U)||(63U < var_cop1op))/* cop1op_c */) {
      var_co = 1U;
      var_op = 17U /* COP1 */;
      reginfo_use_fp_reg(var_ft);
      reginfo_use_fp_reg(var_fs);
      var__Z52 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 63U)<< 26U)|((uint32_t)(var_co & 1U)<< 25U))|((uint32_t)(var_fmt & 15U)<< 21U))|((uint32_t)(var_ft & 31U)<< 16U))|((uint32_t)(var_fs & 31U)<< 11U))|((uint32_t)(var_cc_alt & 7U)<< 8U))|((uint32_t)(var__Z52 & 3U)<< 6U))|(uint32_t)(var_cop1op & 63U)));
      }
      return;
   }
}

/*
 * Macro arith defined at ../../../targets/mips/encoding.def:238:4-240:6
 */
static void arith_e13e13(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rs) {
   uint8_t var_op;
   
   if ((!((var_specop < 42U)||(43U < var_specop))|| !((var_specop < 32U)||(39U < var_specop)))/* specarith3 */) {
      var_op = 0U /* SPECIAL */;
      arith_e13e13e13(line, var_specop, var_rd, var_rd, var_rs);
      return;
   }
   (void)var_op;
   (void)var_rd;
   (void)var_rs;
   (void)var_specop;
}

/*
 * Macro addiu defined at ../../../targets/mips/encoding.def:780:4-70
 */
static void addiu_e13e13i16(int line, uint8_t var_rt, uint8_t var_rs, int16_t var_imm) {
   
   if (true) {
      arithimmraw_e13e13i16(line, 9U /* ADDIU */, var_rt, var_rs, var_imm);
      return;
   }
   (void)var_imm;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro ori defined at ../../../targets/mips/encoding.def:790:4-66
 */
static void ori_e13e13u16(int line, uint8_t var_rt, uint8_t var_rs, uint16_t var_uimm) {
   
   if (true) {
      bitimmraw_e13e13u16(line, 13U /* ORI */, var_rt, var_rs, var_uimm);
      return;
   }
   (void)var_rs;
   (void)var_rt;
   (void)var_uimm;
}

/*
 * Macro li defined at ../../../targets/mips/encoding.def:808:4-811:6
 */
static void li_e13u32(int line, uint8_t var_rd, uint32_t var_val) {
   int16_t var_val16;
   uint16_t var_hi;
   uint32_t var_lo;
   uint16_t var_lo_u16;
   int16_t var_lo_s16;
   int32_t var_lo_s32;
   uint32_t var_lo_u32;
   
   if ((!(32767 <(int32_t)var_val)&& !((int32_t)var_val <(-32767 - 1)))) {
      var_val16 =(int16_t)(int32_t)var_val;
      addiu_e13e13i16(line, var_rd, 0U /* z0 */, var_val16);
      return;
   }
   if (!(65535U < var_val)) {
      var_val16 =(uint16_t)var_val;
      ori_e13e13u16(line, var_rd, 0U /* z0 */, var_val16);
      return;
   }
   if (((var_val & 65535U)== 0U)) {
      var_hi =(uint16_t)(var_val >> 16U);
      luiraw_e13u16(line, var_rd, var_hi);
      return;
   }
   if (true) {
      var_lo =(var_val & 65535U);
      var_lo_u16 =(uint16_t)var_lo;
      var_lo_s16 =(int16_t)var_lo_u16;
      var_lo_s32 =(int32_t)((uint32_t)(uint16_t)var_lo_s16 |(((1U << 15U)&(uint32_t)(uint16_t)var_lo_s16)?(4294967295U - 65535U): 0U));
      var_lo_u32 =(uint32_t)var_lo_s32;
      var_hi =(uint16_t)((var_val - var_lo_u32)>> 16U);
      luiraw_e13u16(line, var_rd, var_hi);
      addiu_e13e13i16(line, var_rd, var_rd, var_lo_s16);
      return;
   }
   (void)var_hi;
   (void)var_lo;
   (void)var_lo_s16;
   (void)var_lo_s32;
   (void)var_lo_u16;
   (void)var_lo_u32;
   (void)var_rd;
   (void)var_val;
   (void)var_val16;
}

/*
 * Macro arithval_plain defined at ../../../targets/mips/encoding.def:243:4-254:6
 */
static void arithval_plain_e13e13u32(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rt, uint32_t var_val) {
   uint8_t var_op;
   
   if ((!((var_specop < 42U)||(43U < var_specop))|| !((var_specop < 32U)||(39U < var_specop)))/* specarith3 */) {
      var_op = 0U /* SPECIAL */;
      if ((var_rd == var_rt)) {
         li_e13u32(line, 1U /* AT */, var_val);
         arith_e13e13e13(line, var_specop, var_rd, var_rt, 1U /* AT */);
      }
      else{
         li_e13u32(line, var_rd, var_val);
         arith_e13e13e13(line, var_specop, var_rd, var_rt, var_rd);
      }
      return;
   }
   (void)var_op;
   (void)var_rd;
   (void)var_rt;
   (void)var_specop;
   (void)var_val;
}

/*
 * Macro arithval_u defined at ../../../targets/mips/encoding.def:255:4-273:6
 */
static void arithval_u_e13e13u32(int line, uint8_t var_specop, uint8_t var_immop, uint8_t var_rd, uint8_t var_rt, uint32_t var_val) {
   uint8_t var_op;
   uint16_t var_val16;
   
   if ((!((var_specop < 42U)||(43U < var_specop))|| !((var_specop < 32U)||(39U < var_specop)))/* specarith3 */) {
      var_op = 0U /* SPECIAL */;
      if (!(65535U < var_val)) {
         var_val16 =(uint16_t)var_val;
         bitimmraw_e13e13u16(line, var_immop, var_rd, var_rt, var_val16);
      }
      else{
         if ((var_rd == var_rt)) {
            li_e13u32(line, 1U /* AT */, var_val);
            arith_e13e13e13(line, var_specop, var_rd, var_rt, 1U /* AT */);
         }
         else{
            li_e13u32(line, var_rd, var_val);
            arith_e13e13e13(line, var_specop, var_rd, var_rt, var_rd);
         }
      }
      return;
   }
   (void)var_immop;
   (void)var_op;
   (void)var_rd;
   (void)var_rt;
   (void)var_specop;
   (void)var_val;
   (void)var_val16;
}

/*
 * Macro arithval_s defined at ../../../targets/mips/encoding.def:274:4-292:6
 */
static void arithval_s_e13e13u32(int line, uint8_t var_specop, uint8_t var_immop, uint8_t var_rd, uint8_t var_rt, uint32_t var_val) {
   uint8_t var_op;
   int16_t var_val16;
   
   if ((!((var_specop < 42U)||(43U < var_specop))|| !((var_specop < 32U)||(39U < var_specop)))/* specarith3 */) {
      var_op = 0U /* SPECIAL */;
      if ((!(32767 <(int32_t)var_val)&& !((int32_t)var_val <(-32767 - 1)))) {
         var_val16 =(int16_t)(int32_t)var_val;
         arithimmraw_e13e13i16(line, var_immop, var_rd, var_rt, var_val16);
      }
      else{
         if ((var_rd == var_rt)) {
            li_e13u32(line, 1U /* AT */, var_val);
            arith_e13e13e13(line, var_specop, var_rd, var_rt, 1U /* AT */);
         }
         else{
            li_e13u32(line, var_rd, var_val);
            arith_e13e13e13(line, var_specop, var_rd, var_rt, var_rd);
         }
      }
      return;
   }
   (void)var_immop;
   (void)var_op;
   (void)var_rd;
   (void)var_rt;
   (void)var_specop;
   (void)var_val;
   (void)var_val16;
}

/*
 * Macro arithval_sub defined at ../../../targets/mips/encoding.def:294:4-312:6
 */
static void arithval_sub_e13e13u32(int line, uint8_t var_specop, uint8_t var_addop, uint8_t var_rd, uint8_t var_rt, uint32_t var_val) {
   uint8_t var_op;
   int16_t var_val16;
   
   if (((var_specop == 34U /* SUB */)||(var_specop == 35U /* SUBU */))) {
      var_op = 0U /* SPECIAL */;
      if ((!(32767 < -(int32_t)var_val)&& !(-(int32_t)var_val <(-32767 - 1)))) {
         var_val16 =(int16_t)-(int32_t)var_val;
         arithimmraw_e13e13i16(line, var_addop, var_rd, var_rt, var_val16);
      }
      else{
         if ((var_rd == var_rt)) {
            li_e13u32(line, 1U /* AT */, var_val);
            arith_e13e13e13(line, var_specop, var_rd, var_rt, 1U /* AT */);
         }
         else{
            li_e13u32(line, var_rd, var_val);
            arith_e13e13e13(line, var_specop, var_rd, var_rt, var_rd);
         }
      }
      return;
   }
   (void)var_addop;
   (void)var_op;
   (void)var_rd;
   (void)var_rt;
   (void)var_specop;
   (void)var_val;
   (void)var_val16;
}

/*
 * Macro addiu defined at ../../../targets/mips/opmatch.def:51:1-42
 */
static void addiu_e13e13xi16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      arithimm_e13e13xi16(line, 9U /* ADDIU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro arithval_subi defined at ../../../targets/mips/encoding.def:314:4-326:6
 */
static void arithval_subi_e13e13xi16(int line, uint8_t var_specop, uint8_t var_rd, uint8_t var_rt, struct expr * var_expr) {
   uint8_t var_op;
   
   if (((var_specop == 34U /* SUB */)||(var_specop == 35U /* SUBU */))) {
      var_op = 0U /* SPECIAL */;
      if ((var_rd == var_rt)) {
         addiu_e13e13xi16(line, 1U /* AT */, 0U /* z0 */, var_expr);
         arith_e13e13e13(line, var_specop, var_rd, var_rt, 1U /* AT */);
      }
      else{
         addiu_e13e13xi16(line, var_rd, 0U /* z0 */, var_expr);
         arith_e13e13e13(line, var_specop, var_rd, var_rt, var_rd);
      }
      return;
   }
   (void)var_expr;
   (void)var_op;
   (void)var_rd;
   (void)var_rt;
   (void)var_specop;
}

/*
 * Macro nop defined at ../../../targets/mips/encoding.def:481:4-483:6
 */
static void nop_(int line) {
   
   if (true) {
      shift_e13e13u32(line, 0U /* SLL */, 0U /* z0 */, 0U /* z0 */, 0U);
      return;
   }
}

/*
 * Macro mflo defined at ../../../targets/mips/opmatch.def:174:1-26
 */
static void mflo_e13(int line, uint8_t var__op0) {
   
   if (true) {
      mfhilo_e13(line, 18U /* MFLO */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro div defined at ../../../targets/mips/encoding.def:354:4-384:6
 */
static void div_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   uint8_t var_op;
   int16_t var_br_2;
   int16_t var_br_5;
   uint16_t var_brk_overflow;
   uint16_t var_brk_divzero;
   uint32_t var_negone;
   uint16_t var_intminupper;
   
   if (true) {
      var_op = 0U /* SPECIAL */;
      if ((var_rd == 0U /* z0 */)) {
         muldivraw_e13e13(line, 26U /* DIV */, var_rs, var_rt);
      }
      else{
         var_br_2 = 2;
         var_br_5 = 5;
         var_brk_overflow = 6U;
         var_brk_divzero = 7U;
         var_negone =(uint32_t)-1;
         var_intminupper = 32768U;
         bneplain_e13e13i16(line, var_rt, 0U /* z0 */, var_br_2);
         muldivraw_e13e13(line, 26U /* DIV */, var_rs, var_rt);
         break_u10u10(line, var_brk_divzero, 0U);
         li_e13u32(line, 1U /* AT */, var_negone);
         bneplain_e13e13i16(line, var_rt, 1U /* AT */, var_br_5);
         nop_(line);
         luiraw_e13u16(line, 1U /* AT */, var_intminupper);
         bneplain_e13e13i16(line, var_rs, 1U /* AT */, var_br_2);
         nop_(line);
         break_u10u10(line, var_brk_overflow, 0U);
         mflo_e13(line, var_rd);
      }
      return;
   }
   (void)var_br_2;
   (void)var_br_5;
   (void)var_brk_divzero;
   (void)var_brk_overflow;
   (void)var_intminupper;
   (void)var_negone;
   (void)var_op;
   (void)var_rd;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro div defined at ../../../targets/mips/encoding.def:385:4-387:6
 */
static void div_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   uint8_t var_op;
   
   if (true) {
      var_op = 0U /* SPECIAL */;
      div_e13e13e13(line, var_rd, var_rd, var_rt);
      return;
   }
   (void)var_op;
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro divu defined at ../../../targets/mips/encoding.def:388:4-407:6
 */
static void divu_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   uint8_t var_op;
   int16_t var_br_2;
   uint16_t var_brk_divzero;
   
   if (true) {
      var_op = 0U /* SPECIAL */;
      if ((var_rd == 0U /* z0 */)) {
         muldivraw_e13e13(line, 27U /* DIVU */, var_rs, var_rt);
      }
      else{
         var_br_2 = 2;
         var_brk_divzero = 7U;
         bneplain_e13e13i16(line, var_rt, 0U /* z0 */, var_br_2);
         muldivraw_e13e13(line, 27U /* DIVU */, var_rs, var_rt);
         break_u10u10(line, var_brk_divzero, 0U);
         mflo_e13(line, var_rd);
      }
      return;
   }
   (void)var_br_2;
   (void)var_brk_divzero;
   (void)var_op;
   (void)var_rd;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro divu defined at ../../../targets/mips/encoding.def:408:4-410:6
 */
static void divu_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   uint8_t var_op;
   
   if (true) {
      var_op = 0U /* SPECIAL */;
      divu_e13e13e13(line, var_rd, var_rd, var_rt);
      return;
   }
   (void)var_op;
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro sync defined at ../../../targets/mips/encoding.def:438:4-440:6
 */
static void sync_(int line) {
   uint8_t var_op;
   
   if (true) {
      var_op = 0U /* SPECIAL */;
      sync_u5(line, 0U);
      return;
   }
   (void)var_op;
}

/*
 * Macro jr defined at ../../../targets/mips/encoding.def:454:4-459:6
 */
static void jr_e13(int line, uint8_t var_rs) {
   uint8_t var_op;
   
   if (true) {
      var_op = 0U /* SPECIAL */;
      jr_raw_e13(line, var_rs);
      if (modeison("reorder")) {
         nop_(line);
      }
      return;
   }
   (void)var_op;
   (void)var_rs;
}

/*
 * Macro jalr defined at ../../../targets/mips/encoding.def:460:4-465:6
 */
static void jalr_e13e13(int line, uint8_t var_rd, uint8_t var_rs) {
   uint8_t var_op;
   
   if (true) {
      var_op = 0U /* SPECIAL */;
      jalr_raw_e13e13(line, var_rd, var_rs);
      if (modeison("reorder")) {
         nop_(line);
      }
      return;
   }
   (void)var_op;
   (void)var_rd;
   (void)var_rs;
}

/*
 * Macro jalr defined at ../../../targets/mips/encoding.def:466:4-468:6
 */
static void jalr_e13(int line, uint8_t var_rs) {
   uint8_t var_op;
   
   if (true) {
      var_op = 0U /* SPECIAL */;
      jalr_e13e13(line, 31U /* ra */, var_rs);
      return;
   }
   (void)var_op;
   (void)var_rs;
}

/*
 * Macro ssnop defined at ../../../targets/mips/encoding.def:484:4-486:6
 */
static void ssnop_(int line) {
   
   if (true) {
      shift_e13e13u32(line, 0U /* SLL */, 0U /* z0 */, 0U /* z0 */, 1U);
      return;
   }
}

/*
 * Macro move defined at ../../../targets/mips/encoding.def:489:4-491:6
 */
static void move_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   
   if (true) {
      arith_e13e13e13(line, 33U /* ADDU */, var_rd, var_rt, 0U /* z0 */);
      return;
   }
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro sub defined at ../../../targets/mips/opmatch.def:279:1-32
 */
static void sub_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e13e13e13(line, 34U /* SUB */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro neg defined at ../../../targets/mips/encoding.def:494:4-496:6
 */
static void neg_e13e13(int line, uint8_t var_rd, uint8_t var_rs) {
   
   if (true) {
      sub_e13e13e13(line, var_rd, 0U /* z0 */, var_rs);
      return;
   }
   (void)var_rd;
   (void)var_rs;
}

/*
 * Macro neg defined at ../../../targets/mips/encoding.def:497:4-499:6
 */
static void neg_e13(int line, uint8_t var_rd) {
   
   if (true) {
      neg_e13e13(line, var_rd, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro subu defined at ../../../targets/mips/opmatch.def:283:1-34
 */
static void subu_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e13e13e13(line, 35U /* SUBU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro negu defined at ../../../targets/mips/encoding.def:500:4-502:6
 */
static void negu_e13e13(int line, uint8_t var_rd, uint8_t var_rs) {
   
   if (true) {
      subu_e13e13e13(line, var_rd, 0U /* z0 */, var_rs);
      return;
   }
   (void)var_rd;
   (void)var_rs;
}

/*
 * Macro negu defined at ../../../targets/mips/encoding.def:503:4-505:6
 */
static void negu_e13(int line, uint8_t var_rd) {
   
   if (true) {
      negu_e13e13(line, var_rd, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro nor defined at ../../../targets/mips/opmatch.def:198:1-32
 */
static void nor_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e13e13e13(line, 39U /* NOR */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro not defined at ../../../targets/mips/encoding.def:508:4-510:6
 */
static void not_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   
   if (true) {
      nor_e13e13e13(line, var_rd, var_rt, 0U /* z0 */);
      return;
   }
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro not defined at ../../../targets/mips/encoding.def:511:4-513:6
 */
static void not_e13(int line, uint8_t var_rd) {
   
   if (true) {
      not_e13e13(line, var_rd, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro sra defined at ../../../targets/mips/opmatch.def:271:1-34
 */
static void sra_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      shift_e13e13u32(line, 3U /* SRA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro xor defined at ../../../targets/mips/opmatch.def:336:1-32
 */
static void xor_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e13e13e13(line, 38U /* XOR */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro abs defined at ../../../targets/mips/encoding.def:516:4-535:6
 */
static void abs_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   uint32_t var_bits;
   
   if (true) {
      var_bits = 31U;
      sra_e13e13u32(line, 1U /* AT */, var_rt, var_bits);
      xor_e13e13e13(line, var_rd, var_rt, 1U /* AT */);
      sub_e13e13e13(line, var_rd, var_rd, 1U /* AT */);
      return;
   }
   (void)var_bits;
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro abs defined at ../../../targets/mips/encoding.def:536:4-538:6
 */
static void abs_e13(int line, uint8_t var_rd) {
   
   if (true) {
      abs_e13e13(line, var_rd, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro sltu defined at ../../../targets/mips/opmatch.def:265:1-48
 */
static void sltu_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      arithval_s_e13e13u32(line, 43U /* SLTU */, 11U /* SLTIU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro seq defined at ../../../targets/mips/encoding.def:541:4-546:6
 */
static void seq_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   
   if (true) {
      xor_e13e13e13(line, var_rd, var_rs, var_rt);
      sltu_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro seq defined at ../../../targets/mips/encoding.def:547:4-549:6
 */
static void seq_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   
   if (true) {
      seq_e13e13e13(line, var_rd, var_rd, var_rt);
      return;
   }
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro subu defined at ../../../targets/mips/opmatch.def:284:1-50
 */
static void subu_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      arithval_sub_e13e13u32(line, 35U /* SUBU */, 9U /* ADDIU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro xor defined at ../../../targets/mips/opmatch.def:337:1-45
 */
static void xor_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      arithval_u_e13e13u32(line, 38U /* XOR */, 14U /* XORI */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro seq defined at ../../../targets/mips/encoding.def:550:4-565:6
 */
static void seq_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val) {
   int32_t var_negval;
   
   if (true) {
      var_negval = -(int32_t)var_val;
      if ((!(32767 < var_negval)&& !(var_negval <(-32767 - 1)))) {
         subu_e13e13u32(line, var_rd, var_rs, var_val);
      }
      else{
         xor_e13e13u32(line, var_rd, var_rs, var_val);
      }
      sltu_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_negval;
   (void)var_rd;
   (void)var_rs;
   (void)var_val;
}

/*
 * Macro xori defined at ../../../targets/mips/opmatch.def:338:1-38
 */
static void xori_e13e13xu16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      bitimm_e13e13xu16(line, 14U /* XORI */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro seqi defined at ../../../targets/mips/encoding.def:566:4-570:6
 */
static void seqi_e13e13xu16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr) {
   
   if (true) {
      xori_e13e13xu16(line, var_rd, var_rs, var_expr);
      sltu_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_expr;
   (void)var_rd;
   (void)var_rs;
}

/*
 * Macro sltu defined at ../../../targets/mips/opmatch.def:264:1-34
 */
static void sltu_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e13e13e13(line, 43U /* SLTU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sne defined at ../../../targets/mips/encoding.def:571:4-576:6
 */
static void sne_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   
   if (true) {
      xor_e13e13e13(line, var_rd, var_rs, var_rt);
      sltu_e13e13e13(line, var_rd, 0U /* z0 */, var_rd);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro sne defined at ../../../targets/mips/encoding.def:577:4-579:6
 */
static void sne_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   
   if (true) {
      sne_e13e13e13(line, var_rd, var_rd, var_rt);
      return;
   }
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro sne defined at ../../../targets/mips/encoding.def:580:4-595:6
 */
static void sne_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val) {
   int32_t var_negval;
   
   if (true) {
      var_negval = -(int32_t)var_val;
      if ((!(32767 < var_negval)&& !(var_negval <(-32767 - 1)))) {
         subu_e13e13u32(line, var_rd, var_rs, var_val);
      }
      else{
         xor_e13e13u32(line, var_rd, var_rs, var_val);
      }
      sltu_e13e13e13(line, var_rd, 0U /* z0 */, var_rd);
      return;
   }
   (void)var_negval;
   (void)var_rd;
   (void)var_rs;
   (void)var_val;
}

/*
 * Macro snei defined at ../../../targets/mips/encoding.def:596:4-600:6
 */
static void snei_e13e13xu16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr) {
   
   if (true) {
      xori_e13e13xu16(line, var_rd, var_rs, var_expr);
      sltu_e13e13e13(line, var_rd, 0U /* z0 */, var_rd);
      return;
   }
   (void)var_expr;
   (void)var_rd;
   (void)var_rs;
}

/*
 * Macro slt defined at ../../../targets/mips/opmatch.def:260:1-32
 */
static void slt_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e13e13e13(line, 42U /* SLT */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sgt defined at ../../../targets/mips/encoding.def:602:4-605:6
 */
static void sgt_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   
   if (true) {
      slt_e13e13e13(line, var_rd, var_rt, var_rs);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro sgt defined at ../../../targets/mips/encoding.def:606:4-608:6
 */
static void sgt_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   
   if (true) {
      sgt_e13e13e13(line, var_rd, var_rd, var_rt);
      return;
   }
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro sgt defined at ../../../targets/mips/encoding.def:609:4-620:6
 */
static void sgt_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val) {
   
   if (true) {
      if ((var_rd == var_rs)) {
         li_e13u32(line, 1U /* AT */, var_val);
         slt_e13e13e13(line, var_rd, 1U /* AT */, var_rs);
      }
      else{
         li_e13u32(line, var_rd, var_val);
         slt_e13e13e13(line, var_rd, var_rd, var_rs);
      }
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_val;
}

/*
 * Macro sgti defined at ../../../targets/mips/encoding.def:621:4-632:6
 */
static void sgti_e13e13xi16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr) {
   
   if (true) {
      if ((var_rd == var_rs)) {
         addiu_e13e13xi16(line, 1U /* AT */, 0U /* z0 */, var_expr);
         slt_e13e13e13(line, var_rd, 1U /* AT */, var_rs);
      }
      else{
         addiu_e13e13xi16(line, var_rd, 0U /* z0 */, var_expr);
         slt_e13e13e13(line, var_rd, var_rd, var_rs);
      }
      return;
   }
   (void)var_expr;
   (void)var_rd;
   (void)var_rs;
}

/*
 * Macro sgtu defined at ../../../targets/mips/encoding.def:633:4-636:6
 */
static void sgtu_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   
   if (true) {
      sltu_e13e13e13(line, var_rd, var_rt, var_rs);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro sgtu defined at ../../../targets/mips/encoding.def:637:4-639:6
 */
static void sgtu_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   
   if (true) {
      sgtu_e13e13e13(line, var_rd, var_rd, var_rt);
      return;
   }
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro sgtu defined at ../../../targets/mips/encoding.def:640:4-651:6
 */
static void sgtu_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val) {
   
   if (true) {
      if ((var_rd == var_rs)) {
         li_e13u32(line, 1U /* AT */, var_val);
         sltu_e13e13e13(line, var_rd, var_rs, 1U /* AT */);
      }
      else{
         li_e13u32(line, var_rd, var_val);
         sltu_e13e13e13(line, var_rd, var_rs, var_rd);
      }
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_val;
}

/*
 * Macro sgtiu defined at ../../../targets/mips/encoding.def:652:4-663:6
 */
static void sgtiu_e13e13xi16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr) {
   
   if (true) {
      if ((var_rd == var_rs)) {
         addiu_e13e13xi16(line, 1U /* AT */, 0U /* z0 */, var_expr);
         sltu_e13e13e13(line, var_rd, 1U /* AT */, var_rs);
      }
      else{
         addiu_e13e13xi16(line, var_rd, 0U /* z0 */, var_expr);
         sltu_e13e13e13(line, var_rd, var_rd, var_rs);
      }
      return;
   }
   (void)var_expr;
   (void)var_rd;
   (void)var_rs;
}

/*
 * Macro sge defined at ../../../targets/mips/encoding.def:665:4-670:6
 */
static void sge_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   
   if (true) {
      slt_e13e13e13(line, var_rd, var_rs, var_rt);
      xor_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro sge defined at ../../../targets/mips/encoding.def:671:4-673:6
 */
static void sge_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   
   if (true) {
      sge_e13e13e13(line, var_rd, var_rd, var_rt);
      return;
   }
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro slt defined at ../../../targets/mips/opmatch.def:261:1-45
 */
static void slt_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      arithval_s_e13e13u32(line, 42U /* SLT */, 10U /* SLTI */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sge defined at ../../../targets/mips/encoding.def:674:4-679:6
 */
static void sge_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val) {
   
   if (true) {
      slt_e13e13u32(line, var_rd, var_rs, var_val);
      xor_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_val;
}

/*
 * Macro slti defined at ../../../targets/mips/opmatch.def:262:1-40
 */
static void slti_e13e13xi16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      arithimm_e13e13xi16(line, 10U /* SLTI */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sgei defined at ../../../targets/mips/encoding.def:680:4-685:6
 */
static void sgei_e13e13xi16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr) {
   
   if (true) {
      slti_e13e13xi16(line, var_rd, var_rs, var_expr);
      xor_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_expr;
   (void)var_rd;
   (void)var_rs;
}

/*
 * Macro sgeu defined at ../../../targets/mips/encoding.def:686:4-691:6
 */
static void sgeu_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   
   if (true) {
      sltu_e13e13e13(line, var_rd, var_rs, var_rt);
      xor_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro sgeu defined at ../../../targets/mips/encoding.def:692:4-694:6
 */
static void sgeu_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   
   if (true) {
      sgeu_e13e13e13(line, var_rd, var_rd, var_rt);
      return;
   }
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro sgeu defined at ../../../targets/mips/encoding.def:695:4-700:6
 */
static void sgeu_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val) {
   
   if (true) {
      sltu_e13e13u32(line, var_rd, var_rs, var_val);
      xor_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_val;
}

/*
 * Macro sltiu defined at ../../../targets/mips/opmatch.def:266:1-42
 */
static void sltiu_e13e13xi16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      arithimm_e13e13xi16(line, 11U /* SLTIU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sgeiu defined at ../../../targets/mips/encoding.def:701:4-706:6
 */
static void sgeiu_e13e13xi16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr) {
   
   if (true) {
      sltiu_e13e13xi16(line, var_rd, var_rs, var_expr);
      xor_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_expr;
   (void)var_rd;
   (void)var_rs;
}

/*
 * Macro sle defined at ../../../targets/mips/encoding.def:708:4-713:6
 */
static void sle_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   
   if (true) {
      slt_e13e13e13(line, var_rd, var_rt, var_rs);
      xor_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro sle defined at ../../../targets/mips/encoding.def:714:4-716:6
 */
static void sle_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   
   if (true) {
      sle_e13e13e13(line, var_rd, var_rd, var_rt);
      return;
   }
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro sle defined at ../../../targets/mips/encoding.def:717:4-721:6
 */
static void sle_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val) {
   
   if (true) {
      sgt_e13e13u32(line, var_rd, var_rs, var_val);
      xor_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_val;
}

/*
 * Macro slei defined at ../../../targets/mips/encoding.def:722:4-726:6
 */
static void slei_e13e13xi16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr) {
   
   if (true) {
      sgti_e13e13xi16(line, var_rd, var_rs, var_expr);
      xor_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_expr;
   (void)var_rd;
   (void)var_rs;
}

/*
 * Macro sleu defined at ../../../targets/mips/encoding.def:727:4-732:6
 */
static void sleu_e13e13e13(int line, uint8_t var_rd, uint8_t var_rs, uint8_t var_rt) {
   
   if (true) {
      sltu_e13e13e13(line, var_rd, var_rt, var_rs);
      xor_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro sleu defined at ../../../targets/mips/encoding.def:733:4-735:6
 */
static void sleu_e13e13(int line, uint8_t var_rd, uint8_t var_rt) {
   
   if (true) {
      sleu_e13e13e13(line, var_rd, var_rd, var_rt);
      return;
   }
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro sleu defined at ../../../targets/mips/encoding.def:736:4-740:6
 */
static void sleu_e13e13u32(int line, uint8_t var_rd, uint8_t var_rs, uint32_t var_val) {
   
   if (true) {
      sgtu_e13e13u32(line, var_rd, var_rs, var_val);
      xor_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_val;
}

/*
 * Macro sleiu defined at ../../../targets/mips/encoding.def:741:4-745:6
 */
static void sleiu_e13e13xi16(int line, uint8_t var_rd, uint8_t var_rs, struct expr * var_expr) {
   
   if (true) {
      sgtiu_e13e13xi16(line, var_rd, var_rs, var_expr);
      xor_e13e13u32(line, var_rd, var_rd, 1U);
      return;
   }
   (void)var_expr;
   (void)var_rd;
   (void)var_rs;
}

/*
 * Macro srl defined at ../../../targets/mips/opmatch.def:274:1-34
 */
static void srl_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      shift_e13e13u32(line, 2U /* SRL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sll defined at ../../../targets/mips/opmatch.def:256:1-34
 */
static void sll_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      shift_e13e13u32(line, 0U /* SLL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro or defined at ../../../targets/mips/opmatch.def:204:1-30
 */
static void or_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e13e13e13(line, 37U /* OR */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro ror defined at ../../../targets/mips/encoding.def:748:4-755:6
 */
static void ror_e13e13u32(int line, uint8_t var_rd, uint8_t var_rt, uint32_t var_bits) {
   uint32_t var_nbits;
   
   if (true) {
      var_nbits =(-var_bits & 31U);
      srl_e13e13u32(line, 1U /* AT */, var_rt, var_bits);
      sll_e13e13u32(line, var_rd, var_rt, var_nbits);
      or_e13e13e13(line, var_rd, var_rd, 1U /* AT */);
      return;
   }
   (void)var_bits;
   (void)var_nbits;
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro rol defined at ../../../targets/mips/encoding.def:756:4-763:6
 */
static void rol_e13e13u32(int line, uint8_t var_rd, uint8_t var_rt, uint32_t var_bits) {
   uint32_t var_nbits;
   
   if (true) {
      var_nbits =(-var_bits & 31U);
      sll_e13e13u32(line, 1U /* AT */, var_rt, var_bits);
      srl_e13e13u32(line, var_rd, var_rt, var_nbits);
      or_e13e13e13(line, var_rd, var_rd, 1U /* AT */);
      return;
   }
   (void)var_bits;
   (void)var_nbits;
   (void)var_rd;
   (void)var_rt;
}

/*
 * Macro sll defined at ../../../targets/mips/opmatch.def:257:1-34
 */
static void sll_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shiftv_e13e13e13(line, 4U /* SLLV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro srl defined at ../../../targets/mips/opmatch.def:275:1-34
 */
static void srl_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shiftv_e13e13e13(line, 6U /* SRLV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro ror defined at ../../../targets/mips/encoding.def:764:4-770:6
 */
static void ror_e13e13e13(int line, uint8_t var_rd, uint8_t var_rt, uint8_t var_rs) {
   
   if (true) {
      negu_e13e13(line, 1U /* AT */, var_rs);
      sll_e13e13e13(line, 1U /* AT */, var_rt, 1U /* AT */);
      srl_e13e13e13(line, var_rd, var_rt, var_rs);
      or_e13e13e13(line, var_rd, var_rd, 1U /* AT */);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro rol defined at ../../../targets/mips/encoding.def:771:4-777:6
 */
static void rol_e13e13e13(int line, uint8_t var_rd, uint8_t var_rt, uint8_t var_rs) {
   
   if (true) {
      negu_e13e13(line, 1U /* AT */, var_rs);
      srl_e13e13e13(line, 1U /* AT */, var_rt, 1U /* AT */);
      sll_e13e13e13(line, var_rd, var_rt, var_rs);
      or_e13e13e13(line, var_rd, var_rd, 1U /* AT */);
      return;
   }
   (void)var_rd;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro la defined at ../../../targets/mips/encoding.def:842:4-847:6
 */
static void la_e13xu32(int line, uint8_t var_rd, struct expr * var_sym) {
   struct expr * var_hival;
   struct expr * var_loval;
   
   if (true) {
      var_hival = mkexpr_modifier("hi", var_sym);
      var_loval = mkexpr_modifier("lo", var_sym);
      lui_e13xu16(line, var_rd, var_hival);
      addiu_e13e13xi16(line, var_rd, var_rd, var_loval);
      return;
   }
   (void)var_hival;
   (void)var_loval;
   (void)var_rd;
   (void)var_sym;
}

/*
 * Macro break defined at ../../../targets/mips/encoding.def:854:4-859:6
 */
static void break_u32u32(int line, uint32_t var_a, uint32_t var_b) {
   uint8_t var_specop;
   uint8_t var_op;
   uint16_t var_code10a;
   uint16_t var_code10b;
   
   if ((!(1023U < var_a)&& !(1023U < var_b))) {
      var_specop = 13U /* BREAK */;
      var_op = 0U /* SPECIAL */;
      var_code10a =(uint16_t)var_a;
      var_code10b =(uint16_t)var_b;
      break_u10u10(line, var_code10a, var_code10b);
      return;
   }
   (void)var_a;
   (void)var_b;
   (void)var_code10a;
   (void)var_code10b;
   (void)var_op;
   (void)var_specop;
}

/*
 * Macro break defined at ../../../targets/mips/encoding.def:860:4-862:6
 */
static void break_u32(int line, uint32_t var_a) {
   uint8_t var_specop;
   uint8_t var_op;
   
   if (true) {
      var_specop = 13U /* BREAK */;
      var_op = 0U /* SPECIAL */;
      break_u32u32(line, var_a, 0U);
      return;
   }
   (void)var_a;
   (void)var_op;
   (void)var_specop;
}

/*
 * Macro break defined at ../../../targets/mips/encoding.def:863:4-865:6
 */
static void break_(int line) {
   uint8_t var_specop;
   uint8_t var_op;
   
   if (true) {
      var_specop = 13U /* BREAK */;
      var_op = 0U /* SPECIAL */;
      break_u32u32(line, 0U, 0U);
      return;
   }
   (void)var_op;
   (void)var_specop;
}

/*
 * Macro syscall defined at ../../../targets/mips/encoding.def:874:4-876:6
 */
static void syscall_(int line) {
   uint8_t var_specop;
   uint8_t var_op;
   
   if (true) {
      var_specop = 12U /* SYSCALL */;
      var_op = 0U /* SPECIAL */;
      syscall_u32(line, 0U);
      return;
   }
   (void)var_op;
   (void)var_specop;
}

/*
 * Macro sdbbp defined at ../../../targets/mips/encoding.def:884:4-886:6
 */
static void sdbbp_(int line) {
   uint8_t var_spec2op;
   uint8_t var_op;
   
   if (true) {
      var_spec2op = 63U /* SDBBP */;
      var_op = 28U /* SPECIAL2 */;
      sdbbp_u32(line, 0U);
      return;
   }
   (void)var_op;
   (void)var_spec2op;
}

/*
 * Macro ctrap defined at ../../../targets/mips/encoding.def:895:4-897:6
 */
static void ctrap_e13e13(int line, uint8_t var_specop, uint8_t var_rs, uint8_t var_rt) {
   uint8_t var_op;
   
   if (true) {
      var_op = 0U /* SPECIAL */;
      ctrap_e13e13u32(line, var_specop, var_rs, var_rt, 0U);
      return;
   }
   (void)var_op;
   (void)var_rs;
   (void)var_rt;
   (void)var_specop;
}

/*
 * Macro ctrapval defined at ../../../targets/mips/encoding.def:911:4-923:6
 */
static void ctrapval_e13u32(int line, uint8_t var_specop, uint8_t var_bcondop, uint8_t var_rs, uint32_t var_val) {
   int32_t var_sval;
   int16_t var_sval16;
   
   if (true) {
      var_sval =(int32_t)var_val;
      if ((!(32767 < var_sval)&& !(var_sval <(-32767 - 1)))) {
         var_sval16 =(int16_t)var_sval;
         ctrapiraw_e13i16(line, var_bcondop, var_rs, var_sval16);
      }
      else{
         li_e13u32(line, 1U /* AT */, var_val);
         ctrap_e13e13(line, var_specop, var_rs, 1U /* AT */);
      }
      return;
   }
   (void)var_bcondop;
   (void)var_rs;
   (void)var_specop;
   (void)var_sval;
   (void)var_sval16;
   (void)var_val;
}

/*
 * Macro bcond defined at ../../../targets/mips/encoding.def:933:4-941:6
 */
static void bcond_e13xu32(int line, uint8_t var_bcondop, uint8_t var_rs, struct expr * var_branchtargetsym) {
   uint8_t var_op;
   
   if (true) {
      var_op = 1U /* BCOND */;
      if ((!((var_bcondop < 18U)||(19U < var_bcondop))|| !((var_bcondop < 2U)||(3U < var_bcondop)))) {
         file_warn(line, "Branch-likely instruction");
      }
      bcondraw_e13xu32(line, var_bcondop, var_rs, var_branchtargetsym);
      if (modeison("reorder")) {
         nop_(line);
      }
      return;
   }
   (void)var_bcondop;
   (void)var_branchtargetsym;
   (void)var_op;
   (void)var_rs;
}

/*
 * Macro bal defined at ../../../targets/mips/encoding.def:942:4-944:6
 */
static void bal_xu32(int line, struct expr * var_sym) {
   uint8_t var_op;
   
   if (true) {
      var_op = 1U /* BCOND */;
      bcond_e13xu32(line, 17U /* BGEZAL */, 0U /* z0 */, var_sym);
      return;
   }
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro j defined at ../../../targets/mips/encoding.def:957:4-962:6
 */
static void j_xu32(int line, struct expr * var_sym) {
   
   if (true) {
      j_raw_xu32(line, var_sym);
      if (modeison("reorder")) {
         nop_(line);
      }
      return;
   }
   (void)var_sym;
}

/*
 * Macro jal defined at ../../../targets/mips/encoding.def:963:4-968:6
 */
static void jal_xu32(int line, struct expr * var_sym) {
   
   if (true) {
      jal_raw_xu32(line, var_sym);
      if (modeison("reorder")) {
         nop_(line);
      }
      return;
   }
   (void)var_sym;
}

/*
 * Macro jal defined at ../../../targets/mips/encoding.def:970:4-982:6
 */
static void jal_e13xu32(int line, uint8_t var_rd, struct expr * var_jumptargetsym) {
   
   if (true) {
      if ((var_rd == 0U /* z0 */)) {
         la_e13xu32(line, 1U /* AT */, var_jumptargetsym);
         jalr_e13e13(line, var_rd, 1U /* AT */);
      }
      else{
         la_e13xu32(line, var_rd, var_jumptargetsym);
         jalr_e13e13(line, var_rd, var_rd);
      }
      return;
   }
   (void)var_jumptargetsym;
   (void)var_rd;
}

/*
 * Macro branch defined at ../../../targets/mips/encoding.def:994:4-1002:6
 */
static void branch_e13e13xu32(int line, uint8_t var_op, uint8_t var_rs, uint8_t var_rt, struct expr * var_branchtargetsym) {
   
   if (((((var_op == 4U /* BEQ */)||(var_op == 5U /* BNE */))||(var_op == 20U /* BEQL */))||(var_op == 21U /* BNEL */))) {
      if (!((var_op < 20U)||(23U < var_op))) {
         file_warn(line, "Branch-likely instruction");
      }
      branchraw_e13e13xu32(line, var_op, var_rs, var_rt, var_branchtargetsym);
      if (modeison("reorder")) {
         nop_(line);
      }
      return;
   }
   (void)var_branchtargetsym;
   (void)var_op;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro branch0 defined at ../../../targets/mips/encoding.def:1008:4-1016:6
 */
static void branch0_e13xu32(int line, uint8_t var_op, uint8_t var_rs, struct expr * var_branchtargetsym) {
   
   if (((((var_op == 6U /* BLEZ */)||(var_op == 7U /* BGTZ */))||(var_op == 22U /* BLEZL */))||(var_op == 23U /* BGTZL */))) {
      if (!((var_op < 20U)||(23U < var_op))) {
         file_warn(line, "Branch-likely instruction");
      }
      branch0raw_e13xu32(line, var_op, var_rs, var_branchtargetsym);
      if (modeison("reorder")) {
         nop_(line);
      }
      return;
   }
   if (((((var_op == 4U /* BEQ */)||(var_op == 5U /* BNE */))||(var_op == 20U /* BEQL */))||(var_op == 21U /* BNEL */))) {
      if (!((var_op < 20U)||(23U < var_op))) {
         file_warn(line, "Branch-likely instruction");
      }
      branch0raw_e13xu32(line, var_op, var_rs, var_branchtargetsym);
      if (modeison("reorder")) {
         nop_(line);
      }
      return;
   }
   (void)var_branchtargetsym;
   (void)var_op;
   (void)var_rs;
}

/*
 * Macro branchN defined at ../../../targets/mips/encoding.def:1031:4-1039:6
 */
static void branchN_e13u32xu32(int line, uint8_t var_op, uint8_t var_rs, uint32_t var_val, struct expr * var_branchtargetsym) {
   
   if (((((var_op == 4U /* BEQ */)||(var_op == 5U /* BNE */))||(var_op == 20U /* BEQL */))||(var_op == 21U /* BNEL */))) {
      if (!((var_op < 20U)||(23U < var_op))) {
         file_warn(line, "Branch-likely instruction");
      }
      li_e13u32(line, 1U /* AT */, var_val);
      branch_e13e13xu32(line, var_op, var_rs, 1U /* AT */, var_branchtargetsym);
      return;
   }
   (void)var_branchtargetsym;
   (void)var_op;
   (void)var_rs;
   (void)var_val;
}

/*
 * Macro b defined at ../../../targets/mips/encoding.def:1040:4-1042:6
 */
static void b_xu32(int line, struct expr * var_sym) {
   
   if (true) {
      branch_e13e13xu32(line, 4U /* BEQ */, 0U /* z0 */, 0U /* z0 */, var_sym);
      return;
   }
   (void)var_sym;
}

/*
 * Macro load defined at ../../../targets/mips/encoding.def:1060:4-1074:6
 */
static void load_e13xu32(int line, uint8_t var_op, uint8_t var_rt, struct expr * var_sym) {
   struct compound_mem pack_1;
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (((((((((var_op == 32U /* LB */)||(var_op == 33U /* LH */))||(var_op == 34U /* LWL */))||(var_op == 35U /* LW */))||(var_op == 36U /* LBU */))||(var_op == 37U /* LHU */))||(var_op == 38U /* LWR */))||(var_op == 48U /* LL */))) {
      if (((var_op == 34U /* LWL */)||(var_op == 38U /* LWR */))) {
         lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
         {
            pack_1.m0 = mkexpr_modifier("lo", var_sym);
            pack_1.m1 = 1U /* AT */;
            var_addr = &pack_1;
         }
         load_e13mem(line, var_op, var_rt, var_addr);
      }
      else{
         lui_e13xu16(line, var_rt, mkexpr_modifier("hi", var_sym));
         {
            pack_0.m0 = mkexpr_modifier("lo", var_sym);
            pack_0.m1 = var_rt;
            var_addr = &pack_0;
         }
         load_e13mem(line, var_op, var_rt, var_addr);
      }
      return;
   }
   (void)var_addr;
   (void)var_op;
   (void)var_rt;
   (void)var_sym;
}

/*
 * Macro store defined at ../../../targets/mips/encoding.def:1080:4-1087:6
 */
static void store_e13xu32(int line, uint8_t var_op, uint8_t var_rt, struct expr * var_sym) {
   struct expr * var_hi;
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (((((((var_op == 40U /* SB */)||(var_op == 41U /* SH */))||(var_op == 42U /* SWL */))||(var_op == 43U /* SW */))||(var_op == 46U /* SWR */))||(var_op == 56U /* SC */))) {
      var_hi = mkexpr_modifier("hi", var_sym);
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, var_hi);
      store_e13mem(line, var_op, var_rt, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_hi;
   (void)var_op;
   (void)var_rt;
   (void)var_sym;
}

/*
 * Macro ulw defined at ../../../targets/mips/encoding.def:1088:4-1109:6
 */
static void ulw_e13mem(int line, uint8_t var_rt, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      addiu_e13e13xi16(line, 1U /* AT */, var_rs, var_immexpr);
      loadraw_e13e13i16(line, 34U /* LWL */, var_rt, 1U /* AT */, 0);
      loadraw_e13e13i16(line, 38U /* LWR */, var_rt, 1U /* AT */, 3);
      return;
   }
   (void)var_addr;
   (void)var_immexpr;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro usw defined at ../../../targets/mips/encoding.def:1110:4-1120:6
 */
static void usw_e13mem(int line, uint8_t var_rt, struct compound_mem * var_addr) {
   struct expr * var_immexpr;
   uint8_t var_rs;
   
   if (true) {
      {
         var_immexpr =(var_addr -> m0);
         var_rs =(var_addr -> m1);
      }
      addiu_e13e13xi16(line, 1U /* AT */, var_rs, var_immexpr);
      storeraw_e13e13i16(line, 42U /* SWL */, var_rt, 1U /* AT */, 0);
      storeraw_e13e13i16(line, 46U /* SWR */, var_rt, 1U /* AT */, 3);
      return;
   }
   (void)var_addr;
   (void)var_immexpr;
   (void)var_rs;
   (void)var_rt;
}

/*
 * Macro ulw defined at ../../../targets/mips/encoding.def:1121:4-1127:6
 */
static void ulw_e13xu32(int line, uint8_t var_rt, struct expr * var_sym) {
   
   if (true) {
      la_e13xu32(line, 1U /* AT */, var_sym);
      loadraw_e13e13i16(line, 34U /* LWL */, var_rt, 1U /* AT */, 0);
      loadraw_e13e13i16(line, 38U /* LWR */, var_rt, 1U /* AT */, 3);
      return;
   }
   (void)var_rt;
   (void)var_sym;
}

/*
 * Macro usw defined at ../../../targets/mips/encoding.def:1128:4-1134:6
 */
static void usw_e13xu32(int line, uint8_t var_rt, struct expr * var_sym) {
   
   if (true) {
      la_e13xu32(line, 1U /* AT */, var_sym);
      storeraw_e13e13i16(line, 42U /* SWL */, var_rt, 1U /* AT */, 0);
      storeraw_e13e13i16(line, 46U /* SWR */, var_rt, 1U /* AT */, 3);
      return;
   }
   (void)var_rt;
   (void)var_sym;
}

/*
 * Macro cache defined at ../../../targets/mips/encoding.def:1145:4-1152:6
 */
static void cache_u32xu32(int line, uint32_t var_cacheop32, struct expr * var_sym) {
   struct expr * var_hi;
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      var_hi = mkexpr_modifier("hi", var_sym);
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, var_hi);
      cache_u32mem(line, var_cacheop32, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_cacheop32;
   (void)var_hi;
   (void)var_sym;
}

/*
 * Macro pref defined at ../../../targets/mips/encoding.def:1163:4-1170:6
 */
static void pref_u32xu32(int line, uint32_t var_prefop32, struct expr * var_sym) {
   struct expr * var_hi;
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      var_hi = mkexpr_modifier("hi", var_sym);
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, var_hi);
      pref_u32mem(line, var_prefop32, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_hi;
   (void)var_prefop32;
   (void)var_sym;
}

/*
 * Macro ori defined at ../../../targets/mips/opmatch.def:206:1-36
 */
static void ori_e13e13xu16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      bitimm_e13e13xu16(line, 13U /* ORI */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro nori defined at ../../../targets/mips/encoding.def:1188:4-1193:6
 */
static void nori_e13e13xu16(int line, uint8_t var_rt, uint8_t var_rs, struct expr * var_uimmexpr) {
   
   if (true) {
      ori_e13e13xu16(line, 1U /* AT */, 0U /* z0 */, var_uimmexpr);
      nor_e13e13e13(line, var_rt, var_rs, 1U /* AT */);
      return;
   }
   (void)var_rs;
   (void)var_rt;
   (void)var_uimmexpr;
}

/*
 * Macro bc2raw defined at ../../../targets/mips/encoding.def:1261:4-1269:6
 */
static void bc2raw_e11xu32(int line, uint8_t var_nd, uint8_t var_tf, uint8_t var_cc, struct expr * var_branchtargetsym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 18U /* COP2 */;
      if ((var_nd == 1U)) {
         file_warn(line, "Branch-likely instruction");
      }
      bc2rawraw_e11xu32(line, var_nd, var_tf, var_cc, var_branchtargetsym);
      if (modeison("reorder")) {
         nop_(line);
      }
      return;
   }
   (void)var_branchtargetsym;
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_nd;
   (void)var_op;
   (void)var_tf;
}

/*
 * Macro bc2f defined at ../../../targets/mips/encoding.def:1271:4-56
 */
static void bc2f_e11xu32(int line, uint8_t var_cc, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 18U /* COP2 */;
      bc2raw_e11xu32(line, 0U, 0U, var_cc, var_sym);
      return;
   }
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc2fl defined at ../../../targets/mips/encoding.def:1272:4-56
 */
static void bc2fl_e11xu32(int line, uint8_t var_cc, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 18U /* COP2 */;
      bc2raw_e11xu32(line, 1U, 0U, var_cc, var_sym);
      return;
   }
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc2t defined at ../../../targets/mips/encoding.def:1273:4-56
 */
static void bc2t_e11xu32(int line, uint8_t var_cc, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 18U /* COP2 */;
      bc2raw_e11xu32(line, 0U, 1U, var_cc, var_sym);
      return;
   }
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc2tl defined at ../../../targets/mips/encoding.def:1274:4-56
 */
static void bc2tl_e11xu32(int line, uint8_t var_cc, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 18U /* COP2 */;
      bc2raw_e11xu32(line, 1U, 1U, var_cc, var_sym);
      return;
   }
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc2f defined at ../../../targets/mips/encoding.def:1275:4-46
 */
static void bc2f_xu32(int line, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 18U /* COP2 */;
      bc2f_e11xu32(line, 0U /* cc0 */, var_sym);
      return;
   }
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc2fl defined at ../../../targets/mips/encoding.def:1276:4-46
 */
static void bc2fl_xu32(int line, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 18U /* COP2 */;
      bc2fl_e11xu32(line, 0U /* cc0 */, var_sym);
      return;
   }
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc2t defined at ../../../targets/mips/encoding.def:1277:4-46
 */
static void bc2t_xu32(int line, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 18U /* COP2 */;
      bc2t_e11xu32(line, 0U /* cc0 */, var_sym);
      return;
   }
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc2tl defined at ../../../targets/mips/encoding.def:1278:4-46
 */
static void bc2tl_xu32(int line, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 18U /* COP2 */;
      bc2tl_e11xu32(line, 0U /* cc0 */, var_sym);
      return;
   }
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro lwc2 defined at ../../../targets/mips/encoding.def:1286:4-1292:6
 */
static void lwc2_e9xu32(int line, uint8_t var_rt_cop2, struct expr * var_sym) {
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
      lwc2_e9mem(line, var_rt_cop2, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_rt_cop2;
   (void)var_sym;
}

/*
 * Macro ldc2 defined at ../../../targets/mips/encoding.def:1298:4-1304:6
 */
static void ldc2_e9xu32(int line, uint8_t var_rt_cop2, struct expr * var_sym) {
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
      ldc2_e9mem(line, var_rt_cop2, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_rt_cop2;
   (void)var_sym;
}

/*
 * Macro swc2 defined at ../../../targets/mips/encoding.def:1310:4-1316:6
 */
static void swc2_e9xu32(int line, uint8_t var_rt_cop2, struct expr * var_sym) {
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
      swc2_e9mem(line, var_rt_cop2, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_rt_cop2;
   (void)var_sym;
}

/*
 * Macro sdc2 defined at ../../../targets/mips/encoding.def:1322:4-1328:6
 */
static void sdc2_e9xu32(int line, uint8_t var_rt_cop2, struct expr * var_sym) {
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
      sdc2_e9mem(line, var_rt_cop2, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_rt_cop2;
   (void)var_sym;
}

/*
 * Macro bc3raw defined at ../../../targets/mips/encoding.def:1373:4-1381:6
 */
static void bc3raw_e11xu32(int line, uint8_t var_nd, uint8_t var_tf, uint8_t var_cc, struct expr * var_branchtargetsym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 19U /* COP3 */;
      if ((var_nd == 1U)) {
         file_warn(line, "Branch-likely instruction");
      }
      bc3rawraw_e11xu32(line, var_nd, var_tf, var_cc, var_branchtargetsym);
      if (modeison("reorder")) {
         nop_(line);
      }
      return;
   }
   (void)var_branchtargetsym;
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_nd;
   (void)var_op;
   (void)var_tf;
}

/*
 * Macro bc3f defined at ../../../targets/mips/encoding.def:1383:4-56
 */
static void bc3f_e11xu32(int line, uint8_t var_cc, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 19U /* COP3 */;
      bc3raw_e11xu32(line, 0U, 0U, var_cc, var_sym);
      return;
   }
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc3fl defined at ../../../targets/mips/encoding.def:1384:4-56
 */
static void bc3fl_e11xu32(int line, uint8_t var_cc, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 19U /* COP3 */;
      bc3raw_e11xu32(line, 1U, 0U, var_cc, var_sym);
      return;
   }
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc3t defined at ../../../targets/mips/encoding.def:1385:4-56
 */
static void bc3t_e11xu32(int line, uint8_t var_cc, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 19U /* COP3 */;
      bc3raw_e11xu32(line, 0U, 1U, var_cc, var_sym);
      return;
   }
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc3tl defined at ../../../targets/mips/encoding.def:1386:4-56
 */
static void bc3tl_e11xu32(int line, uint8_t var_cc, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 19U /* COP3 */;
      bc3raw_e11xu32(line, 1U, 1U, var_cc, var_sym);
      return;
   }
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc3f defined at ../../../targets/mips/encoding.def:1387:4-46
 */
static void bc3f_xu32(int line, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 19U /* COP3 */;
      bc3f_e11xu32(line, 0U /* cc0 */, var_sym);
      return;
   }
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc3fl defined at ../../../targets/mips/encoding.def:1388:4-46
 */
static void bc3fl_xu32(int line, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 19U /* COP3 */;
      bc3fl_e11xu32(line, 0U /* cc0 */, var_sym);
      return;
   }
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc3t defined at ../../../targets/mips/encoding.def:1389:4-46
 */
static void bc3t_xu32(int line, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 19U /* COP3 */;
      bc3t_e11xu32(line, 0U /* cc0 */, var_sym);
      return;
   }
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc3tl defined at ../../../targets/mips/encoding.def:1390:4-46
 */
static void bc3tl_xu32(int line, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 19U /* COP3 */;
      bc3tl_e11xu32(line, 0U /* cc0 */, var_sym);
      return;
   }
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro lwc3 defined at ../../../targets/mips/encoding.def:1398:4-1404:6
 */
static void lwc3_e10xu32(int line, uint8_t var_rt_cop3, struct expr * var_sym) {
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
      lwc3_e10mem(line, var_rt_cop3, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_rt_cop3;
   (void)var_sym;
}

/*
 * Macro ldc3 defined at ../../../targets/mips/encoding.def:1410:4-1416:6
 */
static void ldc3_e10xu32(int line, uint8_t var_rt_cop3, struct expr * var_sym) {
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
      ldc3_e10mem(line, var_rt_cop3, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_rt_cop3;
   (void)var_sym;
}

/*
 * Macro swc3 defined at ../../../targets/mips/encoding.def:1422:4-1428:6
 */
static void swc3_e10xu32(int line, uint8_t var_rt_cop3, struct expr * var_sym) {
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
      swc3_e10mem(line, var_rt_cop3, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_rt_cop3;
   (void)var_sym;
}

/*
 * Macro sdc3 defined at ../../../targets/mips/encoding.def:1434:4-1440:6
 */
static void sdc3_e10xu32(int line, uint8_t var_rt_cop3, struct expr * var_sym) {
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
      sdc3_e10mem(line, var_rt_cop3, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_rt_cop3;
   (void)var_sym;
}

/*
 * Macro bc1raw defined at ../../../targets/mips/encoding.def:1484:4-1492:6
 */
static void bc1raw_e11xu32(int line, uint8_t var_nd, uint8_t var_tf, uint8_t var_cc, struct expr * var_branchtargetsym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 17U /* COP1 */;
      if ((var_nd == 1U)) {
         file_warn(line, "Branch-likely instruction");
      }
      bc1rawraw_e11xu32(line, var_nd, var_tf, var_cc, var_branchtargetsym);
      if (modeison("reorder")) {
         nop_(line);
      }
      return;
   }
   (void)var_branchtargetsym;
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_nd;
   (void)var_op;
   (void)var_tf;
}

/*
 * Macro bc1f defined at ../../../targets/mips/encoding.def:1494:4-56
 */
static void bc1f_e11xu32(int line, uint8_t var_cc, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 17U /* COP1 */;
      bc1raw_e11xu32(line, 0U, 0U, var_cc, var_sym);
      return;
   }
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc1fl defined at ../../../targets/mips/encoding.def:1495:4-56
 */
static void bc1fl_e11xu32(int line, uint8_t var_cc, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 17U /* COP1 */;
      bc1raw_e11xu32(line, 1U, 0U, var_cc, var_sym);
      return;
   }
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc1t defined at ../../../targets/mips/encoding.def:1496:4-56
 */
static void bc1t_e11xu32(int line, uint8_t var_cc, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 17U /* COP1 */;
      bc1raw_e11xu32(line, 0U, 1U, var_cc, var_sym);
      return;
   }
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc1tl defined at ../../../targets/mips/encoding.def:1497:4-56
 */
static void bc1tl_e11xu32(int line, uint8_t var_cc, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 17U /* COP1 */;
      bc1raw_e11xu32(line, 1U, 1U, var_cc, var_sym);
      return;
   }
   (void)var_cc;
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc1f defined at ../../../targets/mips/encoding.def:1498:4-46
 */
static void bc1f_xu32(int line, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 17U /* COP1 */;
      bc1f_e11xu32(line, 0U /* cc0 */, var_sym);
      return;
   }
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc1fl defined at ../../../targets/mips/encoding.def:1499:4-46
 */
static void bc1fl_xu32(int line, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 17U /* COP1 */;
      bc1fl_e11xu32(line, 0U /* cc0 */, var_sym);
      return;
   }
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc1t defined at ../../../targets/mips/encoding.def:1500:4-46
 */
static void bc1t_xu32(int line, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 17U /* COP1 */;
      bc1t_e11xu32(line, 0U /* cc0 */, var_sym);
      return;
   }
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro bc1tl defined at ../../../targets/mips/encoding.def:1501:4-46
 */
static void bc1tl_xu32(int line, struct expr * var_sym) {
   uint8_t var_gencopop;
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_gencopop = 8U /* BC */;
      var_co = 0U;
      var_op = 17U /* COP1 */;
      bc1tl_e11xu32(line, 0U /* cc0 */, var_sym);
      return;
   }
   (void)var_co;
   (void)var_gencopop;
   (void)var_op;
   (void)var_sym;
}

/*
 * Macro lwc1 defined at ../../../targets/mips/encoding.def:1509:4-1515:6
 */
static void lwc1_e12xu32(int line, uint8_t var_ft, struct expr * var_sym) {
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
      lwc1_e12mem(line, var_ft, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_ft;
   (void)var_sym;
}

/*
 * Macro ldc1 defined at ../../../targets/mips/encoding.def:1521:4-1527:6
 */
static void ldc1_e12xu32(int line, uint8_t var_ft, struct expr * var_sym) {
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
      ldc1_e12mem(line, var_ft, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_ft;
   (void)var_sym;
}

/*
 * Macro swc1 defined at ../../../targets/mips/encoding.def:1533:4-1539:6
 */
static void swc1_e12xu32(int line, uint8_t var_ft, struct expr * var_sym) {
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
      swc1_e12mem(line, var_ft, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_ft;
   (void)var_sym;
}

/*
 * Macro sdc1 defined at ../../../targets/mips/encoding.def:1545:4-1551:6
 */
static void sdc1_e12xu32(int line, uint8_t var_ft, struct expr * var_sym) {
   struct compound_mem * var_addr;
   struct compound_mem pack_0;
   
   if (true) {
      {
         pack_0.m0 = mkexpr_modifier("lo", var_sym);
         pack_0.m1 = 1U /* AT */;
         var_addr = &pack_0;
      }
      lui_e13xu16(line, 1U /* AT */, mkexpr_modifier("hi", var_sym));
      sdc1_e12mem(line, var_ft, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_ft;
   (void)var_sym;
}

/*
 * Macro fparith2 defined at ../../../targets/mips/encoding.def:1564:4-1567:6
 */
static void fparith2_e12e12(int line, uint8_t var_cop1op, uint8_t var_fmt, uint8_t var_fd, uint8_t var_ft) {
   uint8_t var_co;
   uint8_t var_op;
   
   if (((((var_cop1op == 0U /* FADD */)||(var_cop1op == 1U /* FSUB */))||(var_cop1op == 2U /* FMUL */))||(var_cop1op == 3U /* FDIV */))) {
      var_co = 1U;
      var_op = 17U /* COP1 */;
      fparith_e12e12e12(line, var_cop1op, var_fmt, var_fd, var_fd, var_ft);
      return;
   }
   (void)var_co;
   (void)var_cop1op;
   (void)var_fd;
   (void)var_fmt;
   (void)var_ft;
   (void)var_op;
}

/*
 * Macro c defined at ../../../targets/mips/encoding.def:1597:4-1599:6
 */
static void c_e12e12(int line, uint8_t var_cop1op, uint8_t var_fmt, uint8_t var_fs, uint8_t var_ft) {
   uint8_t var_co;
   uint8_t var_op;
   
   if (true) {
      var_co = 1U;
      var_op = 17U /* COP1 */;
      c_e11e12e12(line, var_cop1op, var_fmt, 0U /* cc0 */, var_fs, var_ft);
      return;
   }
   (void)var_co;
   (void)var_cop1op;
   (void)var_fmt;
   (void)var_fs;
   (void)var_ft;
   (void)var_op;
}

/*
 * Macro add defined at ../../../targets/mips/opmatch.def:44:1-27
 */
static void add_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      arith_e13e13(line, 32U /* ADD */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro add defined at ../../../targets/mips/opmatch.def:45:1-32
 */
static void add_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e13e13e13(line, 32U /* ADD */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro add defined at ../../../targets/mips/opmatch.def:46:1-45
 */
static void add_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      arithval_s_e13e13u32(line, 32U /* ADD */, 8U /* ADDI */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro addi defined at ../../../targets/mips/opmatch.def:47:1-40
 */
static void addi_e13e13xi16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      arithimm_e13e13xi16(line, 8U /* ADDI */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro addu defined at ../../../targets/mips/opmatch.def:48:1-29
 */
static void addu_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      arith_e13e13(line, 33U /* ADDU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro addu defined at ../../../targets/mips/opmatch.def:49:1-34
 */
static void addu_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e13e13e13(line, 33U /* ADDU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro addu defined at ../../../targets/mips/opmatch.def:50:1-48
 */
static void addu_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      arithval_s_e13e13u32(line, 33U /* ADDU */, 9U /* ADDIU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro and defined at ../../../targets/mips/opmatch.def:52:1-27
 */
static void and_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      arith_e13e13(line, 36U /* AND */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro and defined at ../../../targets/mips/opmatch.def:53:1-32
 */
static void and_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e13e13e13(line, 36U /* AND */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro and defined at ../../../targets/mips/opmatch.def:54:1-45
 */
static void and_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      arithval_u_e13e13u32(line, 36U /* AND */, 12U /* ANDI */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro andi defined at ../../../targets/mips/opmatch.def:55:1-38
 */
static void andi_e13e13xu16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      bitimm_e13e13xu16(line, 12U /* ANDI */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro beq defined at ../../../targets/mips/opmatch.def:82:1-35
 */
static void beq_e13e13xu32(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      branch_e13e13xu32(line, 4U /* BEQ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro beq defined at ../../../targets/mips/opmatch.def:83:1-39
 */
static void beq_e13u32xu32(int line, uint8_t var__op0, uint32_t var__op1, struct expr * var__op2) {
   
   if (true) {
      branchN_e13u32xu32(line, 4U /* BEQ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro beql defined at ../../../targets/mips/opmatch.def:84:1-37
 */
static void beql_e13e13xu32(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      branch_e13e13xu32(line, 20U /* BEQL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro beql defined at ../../../targets/mips/opmatch.def:85:1-41
 */
static void beql_e13u32xu32(int line, uint8_t var__op0, uint32_t var__op1, struct expr * var__op2) {
   
   if (true) {
      branchN_e13u32xu32(line, 20U /* BEQL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro beqz defined at ../../../targets/mips/opmatch.def:86:1-36
 */
static void beqz_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      branch0_e13xu32(line, 4U /* BEQ */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro beqzl defined at ../../../targets/mips/opmatch.def:87:1-37
 */
static void beqzl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      branch0_e13xu32(line, 20U /* BEQL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgez defined at ../../../targets/mips/opmatch.def:88:1-32
 */
static void bgez_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bcond_e13xu32(line, 1U /* BGEZ */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgezl defined at ../../../targets/mips/opmatch.def:89:1-34
 */
static void bgezl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bcond_e13xu32(line, 3U /* BGEZL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgezal defined at ../../../targets/mips/opmatch.def:90:1-36
 */
static void bgezal_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bcond_e13xu32(line, 17U /* BGEZAL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgezall defined at ../../../targets/mips/opmatch.def:91:1-38
 */
static void bgezall_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bcond_e13xu32(line, 19U /* BGEZALL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgtz defined at ../../../targets/mips/opmatch.def:92:1-34
 */
static void bgtz_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      branch0_e13xu32(line, 7U /* BGTZ */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgtzl defined at ../../../targets/mips/opmatch.def:93:1-36
 */
static void bgtzl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      branch0_e13xu32(line, 23U /* BGTZL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro blez defined at ../../../targets/mips/opmatch.def:94:1-34
 */
static void blez_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      branch0_e13xu32(line, 6U /* BLEZ */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro blezl defined at ../../../targets/mips/opmatch.def:95:1-36
 */
static void blezl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      branch0_e13xu32(line, 22U /* BLEZL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bltz defined at ../../../targets/mips/opmatch.def:96:1-32
 */
static void bltz_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bcond_e13xu32(line, 0U /* BLTZ */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bltzl defined at ../../../targets/mips/opmatch.def:97:1-34
 */
static void bltzl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bcond_e13xu32(line, 2U /* BLTZL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bltzal defined at ../../../targets/mips/opmatch.def:98:1-36
 */
static void bltzal_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bcond_e13xu32(line, 16U /* BLTZAL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bltzall defined at ../../../targets/mips/opmatch.def:99:1-38
 */
static void bltzall_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bcond_e13xu32(line, 18U /* BLTZALL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bne defined at ../../../targets/mips/opmatch.def:100:1-35
 */
static void bne_e13e13xu32(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      branch_e13e13xu32(line, 5U /* BNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro bne defined at ../../../targets/mips/opmatch.def:101:1-39
 */
static void bne_e13u32xu32(int line, uint8_t var__op0, uint32_t var__op1, struct expr * var__op2) {
   
   if (true) {
      branchN_e13u32xu32(line, 5U /* BNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro bnel defined at ../../../targets/mips/opmatch.def:102:1-37
 */
static void bnel_e13e13xu32(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      branch_e13e13xu32(line, 21U /* BNEL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro bnel defined at ../../../targets/mips/opmatch.def:103:1-41
 */
static void bnel_e13u32xu32(int line, uint8_t var__op0, uint32_t var__op1, struct expr * var__op2) {
   
   if (true) {
      branchN_e13u32xu32(line, 21U /* BNEL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro bnez defined at ../../../targets/mips/opmatch.def:104:1-33
 */
static void bnez_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      branch0_e13xu32(line, 5U /* BNE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bnezl defined at ../../../targets/mips/opmatch.def:105:1-35
 */
static void bnezl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      branch0_e13xu32(line, 21U /* BNEL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro deret defined at ../../../targets/mips/opmatch.def:121:1-23
 */
static void deret_(int line) {
   
   if (true) {
      cop0_(line, 31U /* DERET */);
      return;
   }
}

/*
 * Macro eret defined at ../../../targets/mips/opmatch.def:126:1-21
 */
static void eret_(int line) {
   
   if (true) {
      cop0_(line, 24U /* ERET */);
      return;
   }
}

/*
 * Macro j defined at ../../../targets/mips/opmatch.def:128:1-13
 */
static void j_e13(int line, uint8_t var__op0) {
   
   if (true) {
      jr_e13(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro jal defined at ../../../targets/mips/opmatch.def:131:1-17
 */
static void jal_e13(int line, uint8_t var__op0) {
   
   if (true) {
      jalr_e13(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro lb defined at ../../../targets/mips/opmatch.def:135:1-27
 */
static void lb_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      load_e13xu32(line, 32U /* LB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lb defined at ../../../targets/mips/opmatch.def:136:1-24
 */
static void lb_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      load_e13mem(line, 32U /* LB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lbu defined at ../../../targets/mips/opmatch.def:137:1-29
 */
static void lbu_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      load_e13xu32(line, 36U /* LBU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lbu defined at ../../../targets/mips/opmatch.def:138:1-26
 */
static void lbu_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      load_e13mem(line, 36U /* LBU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lh defined at ../../../targets/mips/opmatch.def:145:1-27
 */
static void lh_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      load_e13xu32(line, 33U /* LH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lh defined at ../../../targets/mips/opmatch.def:146:1-24
 */
static void lh_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      load_e13mem(line, 33U /* LH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lhu defined at ../../../targets/mips/opmatch.def:147:1-29
 */
static void lhu_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      load_e13xu32(line, 37U /* LHU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lhu defined at ../../../targets/mips/opmatch.def:148:1-26
 */
static void lhu_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      load_e13mem(line, 37U /* LHU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ll defined at ../../../targets/mips/opmatch.def:149:1-27
 */
static void ll_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      load_e13xu32(line, 48U /* LL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ll defined at ../../../targets/mips/opmatch.def:150:1-24
 */
static void ll_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      load_e13mem(line, 48U /* LL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lw defined at ../../../targets/mips/opmatch.def:152:1-27
 */
static void lw_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      load_e13xu32(line, 35U /* LW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lw defined at ../../../targets/mips/opmatch.def:153:1-24
 */
static void lw_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      load_e13mem(line, 35U /* LW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lwl defined at ../../../targets/mips/opmatch.def:160:1-29
 */
static void lwl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      load_e13xu32(line, 34U /* LWL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lwl defined at ../../../targets/mips/opmatch.def:161:1-26
 */
static void lwl_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      load_e13mem(line, 34U /* LWL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lwr defined at ../../../targets/mips/opmatch.def:162:1-29
 */
static void lwr_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      load_e13xu32(line, 38U /* LWR */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lwr defined at ../../../targets/mips/opmatch.def:163:1-26
 */
static void lwr_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      load_e13mem(line, 38U /* LWR */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro mfhi defined at ../../../targets/mips/opmatch.def:173:1-26
 */
static void mfhi_e13(int line, uint8_t var__op0) {
   
   if (true) {
      mfhilo_e13(line, 16U /* MFHI */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro movn defined at ../../../targets/mips/opmatch.def:176:1-34
 */
static void movn_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movnz_e13e13e13(line, 11U /* MOVN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movz defined at ../../../targets/mips/opmatch.def:177:1-34
 */
static void movz_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movnz_e13e13e13(line, 10U /* MOVZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro mthi defined at ../../../targets/mips/opmatch.def:187:1-26
 */
static void mthi_e13(int line, uint8_t var__op0) {
   
   if (true) {
      mthilo_e13(line, 17U /* MTHI */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro mtlo defined at ../../../targets/mips/opmatch.def:188:1-26
 */
static void mtlo_e13(int line, uint8_t var__op0) {
   
   if (true) {
      mthilo_e13(line, 19U /* MTLO */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro mult defined at ../../../targets/mips/opmatch.def:190:1-33
 */
static void mult_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      muldivraw_e13e13(line, 24U /* MULT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro multu defined at ../../../targets/mips/opmatch.def:191:1-35
 */
static void multu_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      muldivraw_e13e13(line, 25U /* MULTU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro nor defined at ../../../targets/mips/opmatch.def:197:1-27
 */
static void nor_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      arith_e13e13(line, 39U /* NOR */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro nor defined at ../../../targets/mips/opmatch.def:199:1-43
 */
static void nor_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      arithval_plain_e13e13u32(line, 39U /* NOR */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro or defined at ../../../targets/mips/opmatch.def:203:1-25
 */
static void or_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      arith_e13e13(line, 37U /* OR */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro or defined at ../../../targets/mips/opmatch.def:205:1-42
 */
static void or_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      arithval_u_e13e13u32(line, 37U /* OR */, 13U /* ORI */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro rfe defined at ../../../targets/mips/opmatch.def:209:1-19
 */
static void rfe_(int line) {
   
   if (true) {
      cop0_(line, 16U /* RFE */);
      return;
   }
}

/*
 * Macro sb defined at ../../../targets/mips/opmatch.def:214:1-28
 */
static void sb_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      store_e13xu32(line, 40U /* SB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sb defined at ../../../targets/mips/opmatch.def:215:1-25
 */
static void sb_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      store_e13mem(line, 40U /* SB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sc defined at ../../../targets/mips/opmatch.def:216:1-28
 */
static void sc_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      store_e13xu32(line, 56U /* SC */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sc defined at ../../../targets/mips/opmatch.def:217:1-25
 */
static void sc_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      store_e13mem(line, 56U /* SC */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sh defined at ../../../targets/mips/opmatch.def:246:1-28
 */
static void sh_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      store_e13xu32(line, 41U /* SH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sh defined at ../../../targets/mips/opmatch.def:247:1-25
 */
static void sh_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      store_e13mem(line, 41U /* SH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sllv defined at ../../../targets/mips/opmatch.def:258:1-35
 */
static void sllv_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shiftv_e13e13e13(line, 4U /* SLLV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro slt defined at ../../../targets/mips/opmatch.def:259:1-27
 */
static void slt_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      arith_e13e13(line, 42U /* SLT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sltu defined at ../../../targets/mips/opmatch.def:263:1-29
 */
static void sltu_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      arith_e13e13(line, 43U /* SLTU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sra defined at ../../../targets/mips/opmatch.def:272:1-34
 */
static void sra_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shiftv_e13e13e13(line, 7U /* SRAV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro srav defined at ../../../targets/mips/opmatch.def:273:1-35
 */
static void srav_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shiftv_e13e13e13(line, 7U /* SRAV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro srlv defined at ../../../targets/mips/opmatch.def:276:1-35
 */
static void srlv_e13e13e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shiftv_e13e13e13(line, 6U /* SRLV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sub defined at ../../../targets/mips/opmatch.def:278:1-27
 */
static void sub_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      arith_e13e13(line, 34U /* SUB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sub defined at ../../../targets/mips/opmatch.def:280:1-47
 */
static void sub_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      arithval_sub_e13e13u32(line, 34U /* SUB */, 8U /* ADDI */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro subi defined at ../../../targets/mips/opmatch.def:281:1-44
 */
static void subi_e13e13xi16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      arithval_subi_e13e13xi16(line, 34U /* SUB */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro subu defined at ../../../targets/mips/opmatch.def:282:1-29
 */
static void subu_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      arith_e13e13(line, 35U /* SUBU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro subiu defined at ../../../targets/mips/opmatch.def:285:1-46
 */
static void subiu_e13e13xi16(int line, uint8_t var__op0, uint8_t var__op1, struct expr * var__op2) {
   
   if (true) {
      arithval_subi_e13e13xi16(line, 35U /* SUBU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sw defined at ../../../targets/mips/opmatch.def:286:1-28
 */
static void sw_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      store_e13xu32(line, 43U /* SW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sw defined at ../../../targets/mips/opmatch.def:287:1-25
 */
static void sw_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      store_e13mem(line, 43U /* SW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro swl defined at ../../../targets/mips/opmatch.def:294:1-30
 */
static void swl_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      store_e13xu32(line, 42U /* SWL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro swl defined at ../../../targets/mips/opmatch.def:295:1-27
 */
static void swl_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      store_e13mem(line, 42U /* SWL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro swr defined at ../../../targets/mips/opmatch.def:296:1-30
 */
static void swr_e13xu32(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      store_e13xu32(line, 46U /* SWR */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro swr defined at ../../../targets/mips/opmatch.def:297:1-27
 */
static void swr_e13mem(int line, uint8_t var__op0, struct compound_mem * var__op1) {
   
   if (true) {
      store_e13mem(line, 46U /* SWR */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro teq defined at ../../../targets/mips/opmatch.def:301:1-27
 */
static void teq_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      ctrap_e13e13(line, 52U /* TEQ */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro teq defined at ../../../targets/mips/opmatch.def:302:1-34
 */
static void teq_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      ctrap_e13e13u32(line, 52U /* TEQ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro teq defined at ../../../targets/mips/opmatch.def:303:1-39
 */
static void teq_e13u32(int line, uint8_t var__op0, uint32_t var__op1) {
   
   if (true) {
      ctrapval_e13u32(line, 52U /* TEQ */, 12U /* TEQI */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro teqi defined at ../../../targets/mips/opmatch.def:304:1-34
 */
static void teqi_e13xi16(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      ctrapi_e13xi16(line, 12U /* TEQI */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tge defined at ../../../targets/mips/opmatch.def:305:1-27
 */
static void tge_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      ctrap_e13e13(line, 48U /* TGE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tge defined at ../../../targets/mips/opmatch.def:306:1-34
 */
static void tge_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      ctrap_e13e13u32(line, 48U /* TGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro tge defined at ../../../targets/mips/opmatch.def:307:1-39
 */
static void tge_e13u32(int line, uint8_t var__op0, uint32_t var__op1) {
   
   if (true) {
      ctrapval_e13u32(line, 48U /* TGE */, 8U /* TGEI */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tgei defined at ../../../targets/mips/opmatch.def:308:1-34
 */
static void tgei_e13xi16(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      ctrapi_e13xi16(line, 8U /* TGEI */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tgeu defined at ../../../targets/mips/opmatch.def:309:1-29
 */
static void tgeu_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      ctrap_e13e13(line, 49U /* TGEU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tgeu defined at ../../../targets/mips/opmatch.def:310:1-36
 */
static void tgeu_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      ctrap_e13e13u32(line, 49U /* TGEU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro tgeu defined at ../../../targets/mips/opmatch.def:311:1-42
 */
static void tgeu_e13u32(int line, uint8_t var__op0, uint32_t var__op1) {
   
   if (true) {
      ctrapval_e13u32(line, 49U /* TGEU */, 9U /* TGEIU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tgeiu defined at ../../../targets/mips/opmatch.def:312:1-36
 */
static void tgeiu_e13xi16(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      ctrapi_e13xi16(line, 9U /* TGEIU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tlbp defined at ../../../targets/mips/opmatch.def:313:1-21
 */
static void tlbp_(int line) {
   
   if (true) {
      cop0_(line, 8U /* TLBP */);
      return;
   }
}

/*
 * Macro tlbr defined at ../../../targets/mips/opmatch.def:314:1-21
 */
static void tlbr_(int line) {
   
   if (true) {
      cop0_(line, 1U /* TLBR */);
      return;
   }
}

/*
 * Macro tlbwi defined at ../../../targets/mips/opmatch.def:315:1-23
 */
static void tlbwi_(int line) {
   
   if (true) {
      cop0_(line, 2U /* TLBWI */);
      return;
   }
}

/*
 * Macro tlbwr defined at ../../../targets/mips/opmatch.def:316:1-23
 */
static void tlbwr_(int line) {
   
   if (true) {
      cop0_(line, 6U /* TLBWR */);
      return;
   }
}

/*
 * Macro tlt defined at ../../../targets/mips/opmatch.def:317:1-27
 */
static void tlt_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      ctrap_e13e13(line, 50U /* TLT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tlt defined at ../../../targets/mips/opmatch.def:318:1-34
 */
static void tlt_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      ctrap_e13e13u32(line, 50U /* TLT */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro tlt defined at ../../../targets/mips/opmatch.def:319:1-39
 */
static void tlt_e13u32(int line, uint8_t var__op0, uint32_t var__op1) {
   
   if (true) {
      ctrapval_e13u32(line, 50U /* TLT */, 10U /* TLTI */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tlti defined at ../../../targets/mips/opmatch.def:320:1-34
 */
static void tlti_e13xi16(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      ctrapi_e13xi16(line, 10U /* TLTI */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tltu defined at ../../../targets/mips/opmatch.def:321:1-29
 */
static void tltu_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      ctrap_e13e13(line, 51U /* TLTU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tltu defined at ../../../targets/mips/opmatch.def:322:1-36
 */
static void tltu_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      ctrap_e13e13u32(line, 51U /* TLTU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro tltu defined at ../../../targets/mips/opmatch.def:323:1-42
 */
static void tltu_e13u32(int line, uint8_t var__op0, uint32_t var__op1) {
   
   if (true) {
      ctrapval_e13u32(line, 51U /* TLTU */, 11U /* TLTIU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tltiu defined at ../../../targets/mips/opmatch.def:324:1-36
 */
static void tltiu_e13xi16(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      ctrapi_e13xi16(line, 11U /* TLTIU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tne defined at ../../../targets/mips/opmatch.def:325:1-27
 */
static void tne_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      ctrap_e13e13(line, 54U /* TNE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tne defined at ../../../targets/mips/opmatch.def:326:1-34
 */
static void tne_e13e13u32(int line, uint8_t var__op0, uint8_t var__op1, uint32_t var__op2) {
   
   if (true) {
      ctrap_e13e13u32(line, 54U /* TNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro tne defined at ../../../targets/mips/opmatch.def:327:1-39
 */
static void tne_e13u32(int line, uint8_t var__op0, uint32_t var__op1) {
   
   if (true) {
      ctrapval_e13u32(line, 54U /* TNE */, 14U /* TNEI */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tnei defined at ../../../targets/mips/opmatch.def:328:1-34
 */
static void tnei_e13xi16(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      ctrapi_e13xi16(line, 14U /* TNEI */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro wait defined at ../../../targets/mips/opmatch.def:333:1-21
 */
static void wait_(int line) {
   
   if (true) {
      cop0_(line, 32U /* WAIT */);
      return;
   }
}

/*
 * Macro xor defined at ../../../targets/mips/opmatch.def:335:1-27
 */
static void xor_e13e13(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      arith_e13e13(line, 38U /* XOR */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro abs.s defined at ../../../targets/mips/opmatch.def:343:1-37
 */
static void abs_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 5U /* FABS */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro abs.d defined at ../../../targets/mips/opmatch.def:344:1-37
 */
static void abs_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 5U /* FABS */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro add.s defined at ../../../targets/mips/opmatch.def:345:1-38
 */
static void add_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith2_e12e12(line, 0U /* FADD */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro add.d defined at ../../../targets/mips/opmatch.def:346:1-38
 */
static void add_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith2_e12e12(line, 0U /* FADD */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro add.s defined at ../../../targets/mips/opmatch.def:347:1-42
 */
static void add_s_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fparith_e12e12e12(line, 0U /* FADD */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro add.d defined at ../../../targets/mips/opmatch.def:348:1-42
 */
static void add_d_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fparith_e12e12e12(line, 0U /* FADD */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro ceil.w.s defined at ../../../targets/mips/opmatch.def:349:1-42
 */
static void ceil_w_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 14U /* CEIL_W */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ceil.w.d defined at ../../../targets/mips/opmatch.def:350:1-42
 */
static void ceil_w_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 14U /* CEIL_W */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro cvt.d.s defined at ../../../targets/mips/opmatch.def:351:1-40
 */
static void cvt_d_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 33U /* CVT_D */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro cvt.d.w defined at ../../../targets/mips/opmatch.def:352:1-40
 */
static void cvt_d_w_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 33U /* CVT_D */, 4U /* W */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro cvt.d.l defined at ../../../targets/mips/opmatch.def:353:1-40
 */
static void cvt_d_l_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 33U /* CVT_D */, 5U /* L */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro cvt.s.d defined at ../../../targets/mips/opmatch.def:354:1-40
 */
static void cvt_s_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 32U /* CVT_S */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro cvt.s.w defined at ../../../targets/mips/opmatch.def:355:1-40
 */
static void cvt_s_w_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 32U /* CVT_S */, 4U /* W */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro cvt.s.l defined at ../../../targets/mips/opmatch.def:356:1-40
 */
static void cvt_s_l_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 32U /* CVT_S */, 5U /* L */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro cvt.w.s defined at ../../../targets/mips/opmatch.def:357:1-40
 */
static void cvt_w_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 36U /* CVT_W */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro cvt.w.d defined at ../../../targets/mips/opmatch.def:358:1-40
 */
static void cvt_w_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 36U /* CVT_W */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro div.s defined at ../../../targets/mips/opmatch.def:359:1-38
 */
static void div_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith2_e12e12(line, 3U /* FDIV */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro div.d defined at ../../../targets/mips/opmatch.def:360:1-38
 */
static void div_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith2_e12e12(line, 3U /* FDIV */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro div.s defined at ../../../targets/mips/opmatch.def:361:1-42
 */
static void div_s_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fparith_e12e12e12(line, 3U /* FDIV */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro div.d defined at ../../../targets/mips/opmatch.def:362:1-42
 */
static void div_d_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fparith_e12e12e12(line, 3U /* FDIV */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro floor.w.s defined at ../../../targets/mips/opmatch.def:363:1-44
 */
static void floor_w_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 15U /* FLOOR_W */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro floor.w.d defined at ../../../targets/mips/opmatch.def:364:1-44
 */
static void floor_w_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 15U /* FLOOR_W */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro mov.s defined at ../../../targets/mips/opmatch.def:365:1-37
 */
static void mov_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 6U /* FMOV */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro mov.d defined at ../../../targets/mips/opmatch.def:366:1-37
 */
static void mov_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 6U /* FMOV */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro movf.s defined at ../../../targets/mips/opmatch.def:368:1-34
 */
static void movf_s_e12e12e11(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmovf_e12e12e11(line, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movf.d defined at ../../../targets/mips/opmatch.def:369:1-34
 */
static void movf_d_e12e12e11(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmovf_e12e12e11(line, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movt.s defined at ../../../targets/mips/opmatch.def:371:1-34
 */
static void movt_s_e12e12e11(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmovt_e12e12e11(line, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movt.d defined at ../../../targets/mips/opmatch.def:372:1-34
 */
static void movt_d_e12e12e11(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmovt_e12e12e11(line, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movn.s defined at ../../../targets/mips/opmatch.def:373:1-43
 */
static void movn_s_e12e12e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmovnz_e12e12e13(line, 19U /* FMOVN */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movn.d defined at ../../../targets/mips/opmatch.def:374:1-43
 */
static void movn_d_e12e12e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmovnz_e12e12e13(line, 19U /* FMOVN */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movz.s defined at ../../../targets/mips/opmatch.def:375:1-43
 */
static void movz_s_e12e12e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmovnz_e12e12e13(line, 18U /* FMOVZ */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movz.d defined at ../../../targets/mips/opmatch.def:376:1-43
 */
static void movz_d_e12e12e13(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmovnz_e12e12e13(line, 18U /* FMOVZ */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro mul.s defined at ../../../targets/mips/opmatch.def:377:1-38
 */
static void mul_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith2_e12e12(line, 2U /* FMUL */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro mul.d defined at ../../../targets/mips/opmatch.def:378:1-38
 */
static void mul_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith2_e12e12(line, 2U /* FMUL */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro mul.s defined at ../../../targets/mips/opmatch.def:379:1-42
 */
static void mul_s_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fparith_e12e12e12(line, 2U /* FMUL */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro mul.d defined at ../../../targets/mips/opmatch.def:380:1-42
 */
static void mul_d_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fparith_e12e12e12(line, 2U /* FMUL */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro neg.s defined at ../../../targets/mips/opmatch.def:381:1-37
 */
static void neg_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 7U /* FNEG */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro neg.d defined at ../../../targets/mips/opmatch.def:382:1-37
 */
static void neg_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 7U /* FNEG */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro round.w.s defined at ../../../targets/mips/opmatch.def:383:1-44
 */
static void round_w_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 12U /* ROUND_W */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro round.w.d defined at ../../../targets/mips/opmatch.def:384:1-44
 */
static void round_w_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 12U /* ROUND_W */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sqrt.s defined at ../../../targets/mips/opmatch.def:385:1-39
 */
static void sqrt_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 4U /* FSQRT */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sqrt.d defined at ../../../targets/mips/opmatch.def:386:1-39
 */
static void sqrt_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 4U /* FSQRT */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sub.s defined at ../../../targets/mips/opmatch.def:387:1-38
 */
static void sub_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith2_e12e12(line, 1U /* FSUB */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sub.d defined at ../../../targets/mips/opmatch.def:388:1-38
 */
static void sub_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith2_e12e12(line, 1U /* FSUB */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sub.s defined at ../../../targets/mips/opmatch.def:389:1-42
 */
static void sub_s_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fparith_e12e12e12(line, 1U /* FSUB */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sub.d defined at ../../../targets/mips/opmatch.def:390:1-42
 */
static void sub_d_e12e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fparith_e12e12e12(line, 1U /* FSUB */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro trunc.w.s defined at ../../../targets/mips/opmatch.def:391:1-44
 */
static void trunc_w_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 13U /* TRUNC_W */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro trunc.w.d defined at ../../../targets/mips/opmatch.def:392:1-44
 */
static void trunc_w_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fparith_e12e12(line, 13U /* TRUNC_W */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.f.s defined at ../../../targets/mips/opmatch.def:395:1-30
 */
static void c_f_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 48U /* C_F */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.un.s defined at ../../../targets/mips/opmatch.def:396:1-32
 */
static void c_un_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 49U /* C_UN */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.eq.s defined at ../../../targets/mips/opmatch.def:397:1-32
 */
static void c_eq_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 50U /* C_EQ */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ueq.s defined at ../../../targets/mips/opmatch.def:398:1-34
 */
static void c_ueq_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 51U /* C_UEQ */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.olt.s defined at ../../../targets/mips/opmatch.def:399:1-34
 */
static void c_olt_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 52U /* C_OLT */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ult.s defined at ../../../targets/mips/opmatch.def:400:1-34
 */
static void c_ult_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 53U /* C_ULT */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ole.s defined at ../../../targets/mips/opmatch.def:401:1-34
 */
static void c_ole_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 54U /* C_OLE */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ule.s defined at ../../../targets/mips/opmatch.def:402:1-34
 */
static void c_ule_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 55U /* C_ULE */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.sf.s defined at ../../../targets/mips/opmatch.def:403:1-32
 */
static void c_sf_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 56U /* C_SF */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ngle.s defined at ../../../targets/mips/opmatch.def:404:1-36
 */
static void c_ngle_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 57U /* C_NGLE */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.seq.s defined at ../../../targets/mips/opmatch.def:405:1-34
 */
static void c_seq_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 58U /* C_SEQ */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ngl.s defined at ../../../targets/mips/opmatch.def:406:1-34
 */
static void c_ngl_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 59U /* C_NGL */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.lt.s defined at ../../../targets/mips/opmatch.def:407:1-32
 */
static void c_lt_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 60U /* C_LT */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.nge.s defined at ../../../targets/mips/opmatch.def:408:1-34
 */
static void c_nge_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 61U /* C_NGE */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.le.s defined at ../../../targets/mips/opmatch.def:409:1-32
 */
static void c_le_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 62U /* C_LE */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ngt.s defined at ../../../targets/mips/opmatch.def:410:1-34
 */
static void c_ngt_s_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 63U /* C_NGT */, 0U /* S */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.f.d defined at ../../../targets/mips/opmatch.def:411:1-30
 */
static void c_f_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 48U /* C_F */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.un.d defined at ../../../targets/mips/opmatch.def:412:1-32
 */
static void c_un_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 49U /* C_UN */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.eq.d defined at ../../../targets/mips/opmatch.def:413:1-32
 */
static void c_eq_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 50U /* C_EQ */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ueq.d defined at ../../../targets/mips/opmatch.def:414:1-34
 */
static void c_ueq_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 51U /* C_UEQ */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.olt.d defined at ../../../targets/mips/opmatch.def:415:1-34
 */
static void c_olt_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 52U /* C_OLT */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ult.d defined at ../../../targets/mips/opmatch.def:416:1-34
 */
static void c_ult_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 53U /* C_ULT */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ole.d defined at ../../../targets/mips/opmatch.def:417:1-34
 */
static void c_ole_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 54U /* C_OLE */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ule.d defined at ../../../targets/mips/opmatch.def:418:1-34
 */
static void c_ule_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 55U /* C_ULE */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.sf.d defined at ../../../targets/mips/opmatch.def:419:1-32
 */
static void c_sf_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 56U /* C_SF */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ngle.d defined at ../../../targets/mips/opmatch.def:420:1-36
 */
static void c_ngle_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 57U /* C_NGLE */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.seq.d defined at ../../../targets/mips/opmatch.def:421:1-34
 */
static void c_seq_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 58U /* C_SEQ */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ngl.d defined at ../../../targets/mips/opmatch.def:422:1-34
 */
static void c_ngl_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 59U /* C_NGL */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.lt.d defined at ../../../targets/mips/opmatch.def:423:1-32
 */
static void c_lt_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 60U /* C_LT */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.nge.d defined at ../../../targets/mips/opmatch.def:424:1-34
 */
static void c_nge_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 61U /* C_NGE */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.le.d defined at ../../../targets/mips/opmatch.def:425:1-32
 */
static void c_le_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 62U /* C_LE */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.ngt.d defined at ../../../targets/mips/opmatch.def:426:1-34
 */
static void c_ngt_d_e12e12(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      c_e12e12(line, 63U /* C_NGT */, 1U /* D */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro c.f.s defined at ../../../targets/mips/opmatch.def:427:1-34
 */
static void c_f_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 48U /* C_F */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.un.s defined at ../../../targets/mips/opmatch.def:428:1-36
 */
static void c_un_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 49U /* C_UN */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.eq.s defined at ../../../targets/mips/opmatch.def:429:1-36
 */
static void c_eq_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 50U /* C_EQ */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ueq.s defined at ../../../targets/mips/opmatch.def:430:1-38
 */
static void c_ueq_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 51U /* C_UEQ */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.olt.s defined at ../../../targets/mips/opmatch.def:431:1-38
 */
static void c_olt_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 52U /* C_OLT */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ult.s defined at ../../../targets/mips/opmatch.def:432:1-38
 */
static void c_ult_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 53U /* C_ULT */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ole.s defined at ../../../targets/mips/opmatch.def:433:1-38
 */
static void c_ole_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 54U /* C_OLE */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ule.s defined at ../../../targets/mips/opmatch.def:434:1-38
 */
static void c_ule_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 55U /* C_ULE */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.sf.s defined at ../../../targets/mips/opmatch.def:435:1-36
 */
static void c_sf_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 56U /* C_SF */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ngle.s defined at ../../../targets/mips/opmatch.def:436:1-40
 */
static void c_ngle_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 57U /* C_NGLE */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.seq.s defined at ../../../targets/mips/opmatch.def:437:1-38
 */
static void c_seq_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 58U /* C_SEQ */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ngl.s defined at ../../../targets/mips/opmatch.def:438:1-38
 */
static void c_ngl_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 59U /* C_NGL */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.lt.s defined at ../../../targets/mips/opmatch.def:439:1-36
 */
static void c_lt_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 60U /* C_LT */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.nge.s defined at ../../../targets/mips/opmatch.def:440:1-38
 */
static void c_nge_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 61U /* C_NGE */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.le.s defined at ../../../targets/mips/opmatch.def:441:1-36
 */
static void c_le_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 62U /* C_LE */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ngt.s defined at ../../../targets/mips/opmatch.def:442:1-38
 */
static void c_ngt_s_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 63U /* C_NGT */, 0U /* S */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.f.d defined at ../../../targets/mips/opmatch.def:443:1-34
 */
static void c_f_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 48U /* C_F */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.un.d defined at ../../../targets/mips/opmatch.def:444:1-36
 */
static void c_un_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 49U /* C_UN */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.eq.d defined at ../../../targets/mips/opmatch.def:445:1-36
 */
static void c_eq_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 50U /* C_EQ */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ueq.d defined at ../../../targets/mips/opmatch.def:446:1-38
 */
static void c_ueq_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 51U /* C_UEQ */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.olt.d defined at ../../../targets/mips/opmatch.def:447:1-38
 */
static void c_olt_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 52U /* C_OLT */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ult.d defined at ../../../targets/mips/opmatch.def:448:1-38
 */
static void c_ult_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 53U /* C_ULT */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ole.d defined at ../../../targets/mips/opmatch.def:449:1-38
 */
static void c_ole_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 54U /* C_OLE */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ule.d defined at ../../../targets/mips/opmatch.def:450:1-38
 */
static void c_ule_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 55U /* C_ULE */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.sf.d defined at ../../../targets/mips/opmatch.def:451:1-36
 */
static void c_sf_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 56U /* C_SF */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ngle.d defined at ../../../targets/mips/opmatch.def:452:1-40
 */
static void c_ngle_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 57U /* C_NGLE */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.seq.d defined at ../../../targets/mips/opmatch.def:453:1-38
 */
static void c_seq_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 58U /* C_SEQ */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ngl.d defined at ../../../targets/mips/opmatch.def:454:1-38
 */
static void c_ngl_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 59U /* C_NGL */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.lt.d defined at ../../../targets/mips/opmatch.def:455:1-36
 */
static void c_lt_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 60U /* C_LT */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.nge.d defined at ../../../targets/mips/opmatch.def:456:1-38
 */
static void c_nge_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 61U /* C_NGE */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.le.d defined at ../../../targets/mips/opmatch.def:457:1-36
 */
static void c_le_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 62U /* C_LE */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro c.ngt.d defined at ../../../targets/mips/opmatch.def:458:1-38
 */
static void c_ngt_d_e11e12e12(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      c_e11e12e12(line, 63U /* C_NGT */, 1U /* D */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Insn abs defined at ../../../targets/mips/opmatch.def:42:1-8
 */
void insn_abs_reg(int line, uint8_t op_0) {
   abs_e13(line, op_0);
}

/*
 * Insn abs defined at ../../../targets/mips/opmatch.def:43:1-13
 */
void insn_abs_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   abs_e13e13(line, op_0, op_1);
}

/*
 * Insn add defined at ../../../targets/mips/opmatch.def:44:1-27
 */
void insn_add_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   add_e13e13(line, op_0, op_1);
}

/*
 * Insn add defined at ../../../targets/mips/opmatch.def:45:1-32
 */
void insn_add_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   add_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn add defined at ../../../targets/mips/opmatch.def:46:1-45
 */
void insn_add_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   add_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn addi defined at ../../../targets/mips/opmatch.def:47:1-40
 */
void insn_addi_reg_reg_s16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   addi_e13e13xi16(line, op_0, op_1, op_2);
}

/*
 * Insn addu defined at ../../../targets/mips/opmatch.def:48:1-29
 */
void insn_addu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   addu_e13e13(line, op_0, op_1);
}

/*
 * Insn addu defined at ../../../targets/mips/opmatch.def:49:1-34
 */
void insn_addu_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   addu_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn addu defined at ../../../targets/mips/opmatch.def:50:1-48
 */
void insn_addu_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   addu_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn addiu defined at ../../../targets/mips/opmatch.def:51:1-42
 */
void insn_addiu_reg_reg_s16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   addiu_e13e13xi16(line, op_0, op_1, op_2);
}

/*
 * Insn and defined at ../../../targets/mips/opmatch.def:52:1-27
 */
void insn_and_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   and_e13e13(line, op_0, op_1);
}

/*
 * Insn and defined at ../../../targets/mips/opmatch.def:53:1-32
 */
void insn_and_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   and_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn and defined at ../../../targets/mips/opmatch.def:54:1-45
 */
void insn_and_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   and_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn andi defined at ../../../targets/mips/opmatch.def:55:1-38
 */
void insn_andi_reg_reg_u16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   andi_e13e13xu16(line, op_0, op_1, op_2);
}

/*
 * Insn b defined at ../../../targets/mips/opmatch.def:56:1-9
 */
void insn_b_symbol(int line, struct expr * op_0) {
   b_xu32(line, op_0);
}

/*
 * Insn bal defined at ../../../targets/mips/opmatch.def:57:1-11
 */
void insn_bal_symbol(int line, struct expr * op_0) {
   bal_xu32(line, op_0);
}

/*
 * Insn bc1f defined at ../../../targets/mips/opmatch.def:58:1-12
 */
void insn_bc1f_symbol(int line, struct expr * op_0) {
   bc1f_xu32(line, op_0);
}

/*
 * Insn bc1f defined at ../../../targets/mips/opmatch.def:59:1-16
 */
void insn_bc1f_cc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bc1f_e11xu32(line, op_0, op_1);
}

/*
 * Insn bc1fl defined at ../../../targets/mips/opmatch.def:60:1-13
 */
void insn_bc1fl_symbol(int line, struct expr * op_0) {
   bc1fl_xu32(line, op_0);
}

/*
 * Insn bc1fl defined at ../../../targets/mips/opmatch.def:61:1-17
 */
void insn_bc1fl_cc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bc1fl_e11xu32(line, op_0, op_1);
}

/*
 * Insn bc1t defined at ../../../targets/mips/opmatch.def:62:1-12
 */
void insn_bc1t_symbol(int line, struct expr * op_0) {
   bc1t_xu32(line, op_0);
}

/*
 * Insn bc1t defined at ../../../targets/mips/opmatch.def:63:1-16
 */
void insn_bc1t_cc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bc1t_e11xu32(line, op_0, op_1);
}

/*
 * Insn bc1tl defined at ../../../targets/mips/opmatch.def:64:1-13
 */
void insn_bc1tl_symbol(int line, struct expr * op_0) {
   bc1tl_xu32(line, op_0);
}

/*
 * Insn bc1tl defined at ../../../targets/mips/opmatch.def:65:1-17
 */
void insn_bc1tl_cc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bc1tl_e11xu32(line, op_0, op_1);
}

/*
 * Insn bc2f defined at ../../../targets/mips/opmatch.def:66:1-12
 */
void insn_bc2f_symbol(int line, struct expr * op_0) {
   bc2f_xu32(line, op_0);
}

/*
 * Insn bc2f defined at ../../../targets/mips/opmatch.def:67:1-16
 */
void insn_bc2f_cc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bc2f_e11xu32(line, op_0, op_1);
}

/*
 * Insn bc2fl defined at ../../../targets/mips/opmatch.def:68:1-13
 */
void insn_bc2fl_symbol(int line, struct expr * op_0) {
   bc2fl_xu32(line, op_0);
}

/*
 * Insn bc2fl defined at ../../../targets/mips/opmatch.def:69:1-17
 */
void insn_bc2fl_cc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bc2fl_e11xu32(line, op_0, op_1);
}

/*
 * Insn bc2t defined at ../../../targets/mips/opmatch.def:70:1-12
 */
void insn_bc2t_symbol(int line, struct expr * op_0) {
   bc2t_xu32(line, op_0);
}

/*
 * Insn bc2t defined at ../../../targets/mips/opmatch.def:71:1-16
 */
void insn_bc2t_cc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bc2t_e11xu32(line, op_0, op_1);
}

/*
 * Insn bc2tl defined at ../../../targets/mips/opmatch.def:72:1-13
 */
void insn_bc2tl_symbol(int line, struct expr * op_0) {
   bc2tl_xu32(line, op_0);
}

/*
 * Insn bc2tl defined at ../../../targets/mips/opmatch.def:73:1-17
 */
void insn_bc2tl_cc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bc2tl_e11xu32(line, op_0, op_1);
}

/*
 * Insn bc3f defined at ../../../targets/mips/opmatch.def:74:1-12
 */
void insn_bc3f_symbol(int line, struct expr * op_0) {
   bc3f_xu32(line, op_0);
}

/*
 * Insn bc3f defined at ../../../targets/mips/opmatch.def:75:1-16
 */
void insn_bc3f_cc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bc3f_e11xu32(line, op_0, op_1);
}

/*
 * Insn bc3fl defined at ../../../targets/mips/opmatch.def:76:1-13
 */
void insn_bc3fl_symbol(int line, struct expr * op_0) {
   bc3fl_xu32(line, op_0);
}

/*
 * Insn bc3fl defined at ../../../targets/mips/opmatch.def:77:1-17
 */
void insn_bc3fl_cc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bc3fl_e11xu32(line, op_0, op_1);
}

/*
 * Insn bc3t defined at ../../../targets/mips/opmatch.def:78:1-12
 */
void insn_bc3t_symbol(int line, struct expr * op_0) {
   bc3t_xu32(line, op_0);
}

/*
 * Insn bc3t defined at ../../../targets/mips/opmatch.def:79:1-16
 */
void insn_bc3t_cc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bc3t_e11xu32(line, op_0, op_1);
}

/*
 * Insn bc3tl defined at ../../../targets/mips/opmatch.def:80:1-13
 */
void insn_bc3tl_symbol(int line, struct expr * op_0) {
   bc3tl_xu32(line, op_0);
}

/*
 * Insn bc3tl defined at ../../../targets/mips/opmatch.def:81:1-17
 */
void insn_bc3tl_cc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bc3tl_e11xu32(line, op_0, op_1);
}

/*
 * Insn beq defined at ../../../targets/mips/opmatch.def:82:1-35
 */
void insn_beq_reg_reg_symbol(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   beq_e13e13xu32(line, op_0, op_1, op_2);
}

/*
 * Insn beq defined at ../../../targets/mips/opmatch.def:83:1-39
 */
void insn_beq_reg_number_symbol(int line, uint8_t op_0, uint32_t op_1, struct expr * op_2) {
   beq_e13u32xu32(line, op_0, op_1, op_2);
}

/*
 * Insn beql defined at ../../../targets/mips/opmatch.def:84:1-37
 */
void insn_beql_reg_reg_symbol(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   beql_e13e13xu32(line, op_0, op_1, op_2);
}

/*
 * Insn beql defined at ../../../targets/mips/opmatch.def:85:1-41
 */
void insn_beql_reg_number_symbol(int line, uint8_t op_0, uint32_t op_1, struct expr * op_2) {
   beql_e13u32xu32(line, op_0, op_1, op_2);
}

/*
 * Insn beqz defined at ../../../targets/mips/opmatch.def:86:1-36
 */
void insn_beqz_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   beqz_e13xu32(line, op_0, op_1);
}

/*
 * Insn beqzl defined at ../../../targets/mips/opmatch.def:87:1-37
 */
void insn_beqzl_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   beqzl_e13xu32(line, op_0, op_1);
}

/*
 * Insn bgez defined at ../../../targets/mips/opmatch.def:88:1-32
 */
void insn_bgez_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgez_e13xu32(line, op_0, op_1);
}

/*
 * Insn bgezl defined at ../../../targets/mips/opmatch.def:89:1-34
 */
void insn_bgezl_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgezl_e13xu32(line, op_0, op_1);
}

/*
 * Insn bgezal defined at ../../../targets/mips/opmatch.def:90:1-36
 */
void insn_bgezal_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgezal_e13xu32(line, op_0, op_1);
}

/*
 * Insn bgezall defined at ../../../targets/mips/opmatch.def:91:1-38
 */
void insn_bgezall_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgezall_e13xu32(line, op_0, op_1);
}

/*
 * Insn bgtz defined at ../../../targets/mips/opmatch.def:92:1-34
 */
void insn_bgtz_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgtz_e13xu32(line, op_0, op_1);
}

/*
 * Insn bgtzl defined at ../../../targets/mips/opmatch.def:93:1-36
 */
void insn_bgtzl_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgtzl_e13xu32(line, op_0, op_1);
}

/*
 * Insn blez defined at ../../../targets/mips/opmatch.def:94:1-34
 */
void insn_blez_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   blez_e13xu32(line, op_0, op_1);
}

/*
 * Insn blezl defined at ../../../targets/mips/opmatch.def:95:1-36
 */
void insn_blezl_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   blezl_e13xu32(line, op_0, op_1);
}

/*
 * Insn bltz defined at ../../../targets/mips/opmatch.def:96:1-32
 */
void insn_bltz_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bltz_e13xu32(line, op_0, op_1);
}

/*
 * Insn bltzl defined at ../../../targets/mips/opmatch.def:97:1-34
 */
void insn_bltzl_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bltzl_e13xu32(line, op_0, op_1);
}

/*
 * Insn bltzal defined at ../../../targets/mips/opmatch.def:98:1-36
 */
void insn_bltzal_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bltzal_e13xu32(line, op_0, op_1);
}

/*
 * Insn bltzall defined at ../../../targets/mips/opmatch.def:99:1-38
 */
void insn_bltzall_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bltzall_e13xu32(line, op_0, op_1);
}

/*
 * Insn bne defined at ../../../targets/mips/opmatch.def:100:1-35
 */
void insn_bne_reg_reg_symbol(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   bne_e13e13xu32(line, op_0, op_1, op_2);
}

/*
 * Insn bne defined at ../../../targets/mips/opmatch.def:101:1-39
 */
void insn_bne_reg_number_symbol(int line, uint8_t op_0, uint32_t op_1, struct expr * op_2) {
   bne_e13u32xu32(line, op_0, op_1, op_2);
}

/*
 * Insn bnel defined at ../../../targets/mips/opmatch.def:102:1-37
 */
void insn_bnel_reg_reg_symbol(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   bnel_e13e13xu32(line, op_0, op_1, op_2);
}

/*
 * Insn bnel defined at ../../../targets/mips/opmatch.def:103:1-41
 */
void insn_bnel_reg_number_symbol(int line, uint8_t op_0, uint32_t op_1, struct expr * op_2) {
   bnel_e13u32xu32(line, op_0, op_1, op_2);
}

/*
 * Insn bnez defined at ../../../targets/mips/opmatch.def:104:1-33
 */
void insn_bnez_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bnez_e13xu32(line, op_0, op_1);
}

/*
 * Insn bnezl defined at ../../../targets/mips/opmatch.def:105:1-35
 */
void insn_bnezl_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bnezl_e13xu32(line, op_0, op_1);
}

/*
 * Insn break defined at ../../../targets/mips/opmatch.def:106:1-6
 */
void insn_break_(int line) {
   break_(line);
}

/*
 * Insn break defined at ../../../targets/mips/opmatch.def:107:1-13
 */
void insn_break_number(int line, uint32_t op_0) {
   break_u32(line, op_0);
}

/*
 * Insn break defined at ../../../targets/mips/opmatch.def:108:1-21
 */
void insn_break_number_number(int line, uint32_t op_0, uint32_t op_1) {
   break_u32u32(line, op_0, op_1);
}

/*
 * Insn cache defined at ../../../targets/mips/opmatch.def:109:1-21
 */
void insn_cache_number_symbol(int line, uint32_t op_0, struct expr * op_1) {
   cache_u32xu32(line, op_0, op_1);
}

/*
 * Insn cache defined at ../../../targets/mips/opmatch.def:110:1-18
 */
void insn_cache_number_mem(int line, uint32_t op_0, struct compound_mem * op_1) {
   cache_u32mem(line, op_0, op_1);
}

/*
 * Insn cfc1 defined at ../../../targets/mips/opmatch.def:111:1-15
 */
void insn_cfc1_reg_freg(int line, uint8_t op_0, uint8_t op_1) {
   cfc1_e13e12(line, op_0, op_1);
}

/*
 * Insn cfc2 defined at ../../../targets/mips/opmatch.def:112:1-16
 */
void insn_cfc2_reg_c2reg(int line, uint8_t op_0, uint8_t op_1) {
   cfc2_e13e9(line, op_0, op_1);
}

/*
 * Insn cfc3 defined at ../../../targets/mips/opmatch.def:113:1-16
 */
void insn_cfc3_reg_c3reg(int line, uint8_t op_0, uint8_t op_1) {
   cfc3_e13e10(line, op_0, op_1);
}

/*
 * Insn clo defined at ../../../targets/mips/opmatch.def:114:1-13
 */
void insn_clo_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   clo_e13e13(line, op_0, op_1);
}

/*
 * Insn clz defined at ../../../targets/mips/opmatch.def:115:1-13
 */
void insn_clz_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   clz_e13e13(line, op_0, op_1);
}

/*
 * Insn cop2 defined at ../../../targets/mips/opmatch.def:116:1-12
 */
void insn_cop2_number(int line, uint32_t op_0) {
   cop2_u32(line, op_0);
}

/*
 * Insn cop3 defined at ../../../targets/mips/opmatch.def:117:1-12
 */
void insn_cop3_number(int line, uint32_t op_0) {
   cop3_u32(line, op_0);
}

/*
 * Insn ctc1 defined at ../../../targets/mips/opmatch.def:118:1-15
 */
void insn_ctc1_reg_freg(int line, uint8_t op_0, uint8_t op_1) {
   ctc1_e13e12(line, op_0, op_1);
}

/*
 * Insn ctc2 defined at ../../../targets/mips/opmatch.def:119:1-16
 */
void insn_ctc2_reg_c2reg(int line, uint8_t op_0, uint8_t op_1) {
   ctc2_e13e9(line, op_0, op_1);
}

/*
 * Insn ctc3 defined at ../../../targets/mips/opmatch.def:120:1-16
 */
void insn_ctc3_reg_c3reg(int line, uint8_t op_0, uint8_t op_1) {
   ctc3_e13e10(line, op_0, op_1);
}

/*
 * Insn deret defined at ../../../targets/mips/opmatch.def:121:1-23
 */
void insn_deret_(int line) {
   deret_(line);
}

/*
 * Insn div defined at ../../../targets/mips/opmatch.def:122:1-13
 */
void insn_div_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   div_e13e13(line, op_0, op_1);
}

/*
 * Insn div defined at ../../../targets/mips/opmatch.def:123:1-18
 */
void insn_div_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   div_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn divu defined at ../../../targets/mips/opmatch.def:124:1-14
 */
void insn_divu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   divu_e13e13(line, op_0, op_1);
}

/*
 * Insn divu defined at ../../../targets/mips/opmatch.def:125:1-19
 */
void insn_divu_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   divu_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn eret defined at ../../../targets/mips/opmatch.def:126:1-21
 */
void insn_eret_(int line) {
   eret_(line);
}

/*
 * Insn j defined at ../../../targets/mips/opmatch.def:127:1-9
 */
void insn_j_symbol(int line, struct expr * op_0) {
   j_xu32(line, op_0);
}

/*
 * Insn j defined at ../../../targets/mips/opmatch.def:128:1-13
 */
void insn_j_reg(int line, uint8_t op_0) {
   j_e13(line, op_0);
}

/*
 * Insn jr defined at ../../../targets/mips/opmatch.def:129:1-7
 */
void insn_jr_reg(int line, uint8_t op_0) {
   jr_e13(line, op_0);
}

/*
 * Insn jal defined at ../../../targets/mips/opmatch.def:130:1-11
 */
void insn_jal_symbol(int line, struct expr * op_0) {
   jal_xu32(line, op_0);
}

/*
 * Insn jal defined at ../../../targets/mips/opmatch.def:131:1-17
 */
void insn_jal_reg(int line, uint8_t op_0) {
   jal_e13(line, op_0);
}

/*
 * Insn jal defined at ../../../targets/mips/opmatch.def:132:1-16
 */
void insn_jal_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   jal_e13xu32(line, op_0, op_1);
}

/*
 * Insn jalr defined at ../../../targets/mips/opmatch.def:133:1-9
 */
void insn_jalr_reg(int line, uint8_t op_0) {
   jalr_e13(line, op_0);
}

/*
 * Insn jalr defined at ../../../targets/mips/opmatch.def:134:1-14
 */
void insn_jalr_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   jalr_e13e13(line, op_0, op_1);
}

/*
 * Insn lb defined at ../../../targets/mips/opmatch.def:135:1-27
 */
void insn_lb_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   lb_e13xu32(line, op_0, op_1);
}

/*
 * Insn lb defined at ../../../targets/mips/opmatch.def:136:1-24
 */
void insn_lb_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   lb_e13mem(line, op_0, op_1);
}

/*
 * Insn lbu defined at ../../../targets/mips/opmatch.def:137:1-29
 */
void insn_lbu_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   lbu_e13xu32(line, op_0, op_1);
}

/*
 * Insn lbu defined at ../../../targets/mips/opmatch.def:138:1-26
 */
void insn_lbu_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   lbu_e13mem(line, op_0, op_1);
}

/*
 * Insn ldc1 defined at ../../../targets/mips/opmatch.def:139:1-18
 */
void insn_ldc1_freg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ldc1_e12xu32(line, op_0, op_1);
}

/*
 * Insn ldc1 defined at ../../../targets/mips/opmatch.def:140:1-15
 */
void insn_ldc1_freg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   ldc1_e12mem(line, op_0, op_1);
}

/*
 * Insn ldc2 defined at ../../../targets/mips/opmatch.def:141:1-19
 */
void insn_ldc2_c2reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ldc2_e9xu32(line, op_0, op_1);
}

/*
 * Insn ldc2 defined at ../../../targets/mips/opmatch.def:142:1-16
 */
void insn_ldc2_c2reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   ldc2_e9mem(line, op_0, op_1);
}

/*
 * Insn ldc3 defined at ../../../targets/mips/opmatch.def:143:1-19
 */
void insn_ldc3_c3reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ldc3_e10xu32(line, op_0, op_1);
}

/*
 * Insn ldc3 defined at ../../../targets/mips/opmatch.def:144:1-16
 */
void insn_ldc3_c3reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   ldc3_e10mem(line, op_0, op_1);
}

/*
 * Insn lh defined at ../../../targets/mips/opmatch.def:145:1-27
 */
void insn_lh_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   lh_e13xu32(line, op_0, op_1);
}

/*
 * Insn lh defined at ../../../targets/mips/opmatch.def:146:1-24
 */
void insn_lh_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   lh_e13mem(line, op_0, op_1);
}

/*
 * Insn lhu defined at ../../../targets/mips/opmatch.def:147:1-29
 */
void insn_lhu_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   lhu_e13xu32(line, op_0, op_1);
}

/*
 * Insn lhu defined at ../../../targets/mips/opmatch.def:148:1-26
 */
void insn_lhu_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   lhu_e13mem(line, op_0, op_1);
}

/*
 * Insn ll defined at ../../../targets/mips/opmatch.def:149:1-27
 */
void insn_ll_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ll_e13xu32(line, op_0, op_1);
}

/*
 * Insn ll defined at ../../../targets/mips/opmatch.def:150:1-24
 */
void insn_ll_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   ll_e13mem(line, op_0, op_1);
}

/*
 * Insn lui defined at ../../../targets/mips/opmatch.def:151:1-17
 */
void insn_lui_reg_u16expr(int line, uint8_t op_0, struct expr * op_1) {
   lui_e13xu16(line, op_0, op_1);
}

/*
 * Insn lw defined at ../../../targets/mips/opmatch.def:152:1-27
 */
void insn_lw_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   lw_e13xu32(line, op_0, op_1);
}

/*
 * Insn lw defined at ../../../targets/mips/opmatch.def:153:1-24
 */
void insn_lw_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   lw_e13mem(line, op_0, op_1);
}

/*
 * Insn lwc1 defined at ../../../targets/mips/opmatch.def:154:1-18
 */
void insn_lwc1_freg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   lwc1_e12xu32(line, op_0, op_1);
}

/*
 * Insn lwc1 defined at ../../../targets/mips/opmatch.def:155:1-15
 */
void insn_lwc1_freg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   lwc1_e12mem(line, op_0, op_1);
}

/*
 * Insn lwc2 defined at ../../../targets/mips/opmatch.def:156:1-19
 */
void insn_lwc2_c2reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   lwc2_e9xu32(line, op_0, op_1);
}

/*
 * Insn lwc2 defined at ../../../targets/mips/opmatch.def:157:1-16
 */
void insn_lwc2_c2reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   lwc2_e9mem(line, op_0, op_1);
}

/*
 * Insn lwc3 defined at ../../../targets/mips/opmatch.def:158:1-19
 */
void insn_lwc3_c3reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   lwc3_e10xu32(line, op_0, op_1);
}

/*
 * Insn lwc3 defined at ../../../targets/mips/opmatch.def:159:1-16
 */
void insn_lwc3_c3reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   lwc3_e10mem(line, op_0, op_1);
}

/*
 * Insn lwl defined at ../../../targets/mips/opmatch.def:160:1-29
 */
void insn_lwl_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   lwl_e13xu32(line, op_0, op_1);
}

/*
 * Insn lwl defined at ../../../targets/mips/opmatch.def:161:1-26
 */
void insn_lwl_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   lwl_e13mem(line, op_0, op_1);
}

/*
 * Insn lwr defined at ../../../targets/mips/opmatch.def:162:1-29
 */
void insn_lwr_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   lwr_e13xu32(line, op_0, op_1);
}

/*
 * Insn lwr defined at ../../../targets/mips/opmatch.def:163:1-26
 */
void insn_lwr_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   lwr_e13mem(line, op_0, op_1);
}

/*
 * Insn madd defined at ../../../targets/mips/opmatch.def:164:1-14
 */
void insn_madd_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   madd_e13e13(line, op_0, op_1);
}

/*
 * Insn maddu defined at ../../../targets/mips/opmatch.def:165:1-15
 */
void insn_maddu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   maddu_e13e13(line, op_0, op_1);
}

/*
 * Insn mfc0 defined at ../../../targets/mips/opmatch.def:166:1-16
 */
void insn_mfc0_reg_c0reg(int line, uint8_t op_0, uint8_t op_1) {
   mfc0_e13e8(line, op_0, op_1);
}

/*
 * Insn mfc0 defined at ../../../targets/mips/opmatch.def:167:1-21
 */
void insn_mfc0_reg_c0reg_sel(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mfc0_e13e8u3(line, op_0, op_1, op_2);
}

/*
 * Insn mfc1 defined at ../../../targets/mips/opmatch.def:168:1-15
 */
void insn_mfc1_reg_freg(int line, uint8_t op_0, uint8_t op_1) {
   mfc1_e13e12(line, op_0, op_1);
}

/*
 * Insn mfc2 defined at ../../../targets/mips/opmatch.def:169:1-16
 */
void insn_mfc2_reg_c2reg(int line, uint8_t op_0, uint8_t op_1) {
   mfc2_e13e9(line, op_0, op_1);
}

/*
 * Insn mfc2 defined at ../../../targets/mips/opmatch.def:170:1-21
 */
void insn_mfc2_reg_c2reg_sel(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mfc2_e13e9u3(line, op_0, op_1, op_2);
}

/*
 * Insn mfc3 defined at ../../../targets/mips/opmatch.def:171:1-19
 */
void insn_mfc3_reg_c3reg(int line, uint8_t op_0, uint8_t op_1) {
   mfc3_e13e10(line, op_0, op_1);
}

/*
 * Insn mfc3 defined at ../../../targets/mips/opmatch.def:172:1-24
 */
void insn_mfc3_reg_c3reg_sel(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mfc3_e13e10u3(line, op_0, op_1, op_2);
}

/*
 * Insn mfhi defined at ../../../targets/mips/opmatch.def:173:1-26
 */
void insn_mfhi_reg(int line, uint8_t op_0) {
   mfhi_e13(line, op_0);
}

/*
 * Insn mflo defined at ../../../targets/mips/opmatch.def:174:1-26
 */
void insn_mflo_reg(int line, uint8_t op_0) {
   mflo_e13(line, op_0);
}

/*
 * Insn move defined at ../../../targets/mips/opmatch.def:175:1-14
 */
void insn_move_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   move_e13e13(line, op_0, op_1);
}

/*
 * Insn movn defined at ../../../targets/mips/opmatch.def:176:1-34
 */
void insn_movn_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movn_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn movz defined at ../../../targets/mips/opmatch.def:177:1-34
 */
void insn_movz_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movz_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn msub defined at ../../../targets/mips/opmatch.def:178:1-14
 */
void insn_msub_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   msub_e13e13(line, op_0, op_1);
}

/*
 * Insn msubu defined at ../../../targets/mips/opmatch.def:179:1-15
 */
void insn_msubu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   msubu_e13e13(line, op_0, op_1);
}

/*
 * Insn mtc0 defined at ../../../targets/mips/opmatch.def:180:1-16
 */
void insn_mtc0_reg_c0reg(int line, uint8_t op_0, uint8_t op_1) {
   mtc0_e13e8(line, op_0, op_1);
}

/*
 * Insn mtc0 defined at ../../../targets/mips/opmatch.def:181:1-21
 */
void insn_mtc0_reg_c0reg_sel(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mtc0_e13e8u3(line, op_0, op_1, op_2);
}

/*
 * Insn mtc1 defined at ../../../targets/mips/opmatch.def:182:1-15
 */
void insn_mtc1_reg_freg(int line, uint8_t op_0, uint8_t op_1) {
   mtc1_e13e12(line, op_0, op_1);
}

/*
 * Insn mtc2 defined at ../../../targets/mips/opmatch.def:183:1-16
 */
void insn_mtc2_reg_c2reg(int line, uint8_t op_0, uint8_t op_1) {
   mtc2_e13e9(line, op_0, op_1);
}

/*
 * Insn mtc2 defined at ../../../targets/mips/opmatch.def:184:1-21
 */
void insn_mtc2_reg_c2reg_sel(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mtc2_e13e9u3(line, op_0, op_1, op_2);
}

/*
 * Insn mtc3 defined at ../../../targets/mips/opmatch.def:185:1-16
 */
void insn_mtc3_reg_c3reg(int line, uint8_t op_0, uint8_t op_1) {
   mtc3_e13e10(line, op_0, op_1);
}

/*
 * Insn mtc3 defined at ../../../targets/mips/opmatch.def:186:1-21
 */
void insn_mtc3_reg_c3reg_sel(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mtc3_e13e10u3(line, op_0, op_1, op_2);
}

/*
 * Insn mthi defined at ../../../targets/mips/opmatch.def:187:1-26
 */
void insn_mthi_reg(int line, uint8_t op_0) {
   mthi_e13(line, op_0);
}

/*
 * Insn mtlo defined at ../../../targets/mips/opmatch.def:188:1-26
 */
void insn_mtlo_reg(int line, uint8_t op_0) {
   mtlo_e13(line, op_0);
}

/*
 * Insn mul defined at ../../../targets/mips/opmatch.def:189:1-18
 */
void insn_mul_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mul_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn mult defined at ../../../targets/mips/opmatch.def:190:1-33
 */
void insn_mult_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   mult_e13e13(line, op_0, op_1);
}

/*
 * Insn multu defined at ../../../targets/mips/opmatch.def:191:1-35
 */
void insn_multu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   multu_e13e13(line, op_0, op_1);
}

/*
 * Insn neg defined at ../../../targets/mips/opmatch.def:192:1-8
 */
void insn_neg_reg(int line, uint8_t op_0) {
   neg_e13(line, op_0);
}

/*
 * Insn neg defined at ../../../targets/mips/opmatch.def:193:1-13
 */
void insn_neg_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   neg_e13e13(line, op_0, op_1);
}

/*
 * Insn negu defined at ../../../targets/mips/opmatch.def:194:1-9
 */
void insn_negu_reg(int line, uint8_t op_0) {
   negu_e13(line, op_0);
}

/*
 * Insn negu defined at ../../../targets/mips/opmatch.def:195:1-14
 */
void insn_negu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   negu_e13e13(line, op_0, op_1);
}

/*
 * Insn nop defined at ../../../targets/mips/opmatch.def:196:1-4
 */
void insn_nop_(int line) {
   nop_(line);
}

/*
 * Insn nor defined at ../../../targets/mips/opmatch.def:197:1-27
 */
void insn_nor_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   nor_e13e13(line, op_0, op_1);
}

/*
 * Insn nor defined at ../../../targets/mips/opmatch.def:198:1-32
 */
void insn_nor_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   nor_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn nor defined at ../../../targets/mips/opmatch.def:199:1-43
 */
void insn_nor_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   nor_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn nori defined at ../../../targets/mips/opmatch.def:200:1-23
 */
void insn_nori_reg_reg_u16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   nori_e13e13xu16(line, op_0, op_1, op_2);
}

/*
 * Insn not defined at ../../../targets/mips/opmatch.def:201:1-8
 */
void insn_not_reg(int line, uint8_t op_0) {
   not_e13(line, op_0);
}

/*
 * Insn not defined at ../../../targets/mips/opmatch.def:202:1-13
 */
void insn_not_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   not_e13e13(line, op_0, op_1);
}

/*
 * Insn or defined at ../../../targets/mips/opmatch.def:203:1-25
 */
void insn_or_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   or_e13e13(line, op_0, op_1);
}

/*
 * Insn or defined at ../../../targets/mips/opmatch.def:204:1-30
 */
void insn_or_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   or_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn or defined at ../../../targets/mips/opmatch.def:205:1-42
 */
void insn_or_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   or_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn ori defined at ../../../targets/mips/opmatch.def:206:1-36
 */
void insn_ori_reg_reg_u16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   ori_e13e13xu16(line, op_0, op_1, op_2);
}

/*
 * Insn pref defined at ../../../targets/mips/opmatch.def:207:1-20
 */
void insn_pref_number_symbol(int line, uint32_t op_0, struct expr * op_1) {
   pref_u32xu32(line, op_0, op_1);
}

/*
 * Insn pref defined at ../../../targets/mips/opmatch.def:208:1-17
 */
void insn_pref_number_mem(int line, uint32_t op_0, struct compound_mem * op_1) {
   pref_u32mem(line, op_0, op_1);
}

/*
 * Insn rfe defined at ../../../targets/mips/opmatch.def:209:1-19
 */
void insn_rfe_(int line) {
   rfe_(line);
}

/*
 * Insn rol defined at ../../../targets/mips/opmatch.def:210:1-18
 */
void insn_rol_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   rol_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn rol defined at ../../../targets/mips/opmatch.def:211:1-21
 */
void insn_rol_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   rol_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn ror defined at ../../../targets/mips/opmatch.def:212:1-18
 */
void insn_ror_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   ror_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn ror defined at ../../../targets/mips/opmatch.def:213:1-21
 */
void insn_ror_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   ror_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn sb defined at ../../../targets/mips/opmatch.def:214:1-28
 */
void insn_sb_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   sb_e13xu32(line, op_0, op_1);
}

/*
 * Insn sb defined at ../../../targets/mips/opmatch.def:215:1-25
 */
void insn_sb_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   sb_e13mem(line, op_0, op_1);
}

/*
 * Insn sc defined at ../../../targets/mips/opmatch.def:216:1-28
 */
void insn_sc_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   sc_e13xu32(line, op_0, op_1);
}

/*
 * Insn sc defined at ../../../targets/mips/opmatch.def:217:1-25
 */
void insn_sc_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   sc_e13mem(line, op_0, op_1);
}

/*
 * Insn sdbbp defined at ../../../targets/mips/opmatch.def:218:1-6
 */
void insn_sdbbp_(int line) {
   sdbbp_(line);
}

/*
 * Insn sdbbp defined at ../../../targets/mips/opmatch.def:219:1-13
 */
void insn_sdbbp_number(int line, uint32_t op_0) {
   sdbbp_u32(line, op_0);
}

/*
 * Insn sdc1 defined at ../../../targets/mips/opmatch.def:220:1-18
 */
void insn_sdc1_freg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   sdc1_e12xu32(line, op_0, op_1);
}

/*
 * Insn sdc1 defined at ../../../targets/mips/opmatch.def:221:1-15
 */
void insn_sdc1_freg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   sdc1_e12mem(line, op_0, op_1);
}

/*
 * Insn sdc2 defined at ../../../targets/mips/opmatch.def:222:1-19
 */
void insn_sdc2_c2reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   sdc2_e9xu32(line, op_0, op_1);
}

/*
 * Insn sdc2 defined at ../../../targets/mips/opmatch.def:223:1-16
 */
void insn_sdc2_c2reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   sdc2_e9mem(line, op_0, op_1);
}

/*
 * Insn sdc3 defined at ../../../targets/mips/opmatch.def:224:1-19
 */
void insn_sdc3_c3reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   sdc3_e10xu32(line, op_0, op_1);
}

/*
 * Insn sdc3 defined at ../../../targets/mips/opmatch.def:225:1-16
 */
void insn_sdc3_c3reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   sdc3_e10mem(line, op_0, op_1);
}

/*
 * Insn seq defined at ../../../targets/mips/opmatch.def:226:1-13
 */
void insn_seq_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   seq_e13e13(line, op_0, op_1);
}

/*
 * Insn seq defined at ../../../targets/mips/opmatch.def:227:1-18
 */
void insn_seq_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   seq_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn seq defined at ../../../targets/mips/opmatch.def:228:1-21
 */
void insn_seq_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   seq_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn seqi defined at ../../../targets/mips/opmatch.def:229:1-25
 */
void insn_seqi_reg_reg_u16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   seqi_e13e13xu16(line, op_0, op_1, op_2);
}

/*
 * Insn sge defined at ../../../targets/mips/opmatch.def:230:1-13
 */
void insn_sge_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   sge_e13e13(line, op_0, op_1);
}

/*
 * Insn sge defined at ../../../targets/mips/opmatch.def:231:1-18
 */
void insn_sge_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sge_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn sge defined at ../../../targets/mips/opmatch.def:232:1-21
 */
void insn_sge_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   sge_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn sgeu defined at ../../../targets/mips/opmatch.def:233:1-14
 */
void insn_sgeu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   sgeu_e13e13(line, op_0, op_1);
}

/*
 * Insn sgeu defined at ../../../targets/mips/opmatch.def:234:1-19
 */
void insn_sgeu_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sgeu_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn sgeu defined at ../../../targets/mips/opmatch.def:235:1-22
 */
void insn_sgeu_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   sgeu_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn sgei defined at ../../../targets/mips/opmatch.def:236:1-23
 */
void insn_sgei_reg_reg_s16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   sgei_e13e13xi16(line, op_0, op_1, op_2);
}

/*
 * Insn sgeiu defined at ../../../targets/mips/opmatch.def:237:1-24
 */
void insn_sgeiu_reg_reg_s16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   sgeiu_e13e13xi16(line, op_0, op_1, op_2);
}

/*
 * Insn sgt defined at ../../../targets/mips/opmatch.def:238:1-13
 */
void insn_sgt_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   sgt_e13e13(line, op_0, op_1);
}

/*
 * Insn sgt defined at ../../../targets/mips/opmatch.def:239:1-18
 */
void insn_sgt_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sgt_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn sgt defined at ../../../targets/mips/opmatch.def:240:1-21
 */
void insn_sgt_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   sgt_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn sgtu defined at ../../../targets/mips/opmatch.def:241:1-14
 */
void insn_sgtu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   sgtu_e13e13(line, op_0, op_1);
}

/*
 * Insn sgtu defined at ../../../targets/mips/opmatch.def:242:1-19
 */
void insn_sgtu_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sgtu_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn sgtu defined at ../../../targets/mips/opmatch.def:243:1-22
 */
void insn_sgtu_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   sgtu_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn sgti defined at ../../../targets/mips/opmatch.def:244:1-23
 */
void insn_sgti_reg_reg_s16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   sgti_e13e13xi16(line, op_0, op_1, op_2);
}

/*
 * Insn sgtiu defined at ../../../targets/mips/opmatch.def:245:1-24
 */
void insn_sgtiu_reg_reg_s16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   sgtiu_e13e13xi16(line, op_0, op_1, op_2);
}

/*
 * Insn sh defined at ../../../targets/mips/opmatch.def:246:1-28
 */
void insn_sh_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   sh_e13xu32(line, op_0, op_1);
}

/*
 * Insn sh defined at ../../../targets/mips/opmatch.def:247:1-25
 */
void insn_sh_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   sh_e13mem(line, op_0, op_1);
}

/*
 * Insn sle defined at ../../../targets/mips/opmatch.def:248:1-13
 */
void insn_sle_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   sle_e13e13(line, op_0, op_1);
}

/*
 * Insn sle defined at ../../../targets/mips/opmatch.def:249:1-18
 */
void insn_sle_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sle_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn sle defined at ../../../targets/mips/opmatch.def:250:1-21
 */
void insn_sle_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   sle_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn sleu defined at ../../../targets/mips/opmatch.def:251:1-14
 */
void insn_sleu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   sleu_e13e13(line, op_0, op_1);
}

/*
 * Insn sleu defined at ../../../targets/mips/opmatch.def:252:1-19
 */
void insn_sleu_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sleu_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn sleu defined at ../../../targets/mips/opmatch.def:253:1-22
 */
void insn_sleu_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   sleu_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn slei defined at ../../../targets/mips/opmatch.def:254:1-23
 */
void insn_slei_reg_reg_s16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   slei_e13e13xi16(line, op_0, op_1, op_2);
}

/*
 * Insn sleiu defined at ../../../targets/mips/opmatch.def:255:1-24
 */
void insn_sleiu_reg_reg_s16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   sleiu_e13e13xi16(line, op_0, op_1, op_2);
}

/*
 * Insn sll defined at ../../../targets/mips/opmatch.def:256:1-34
 */
void insn_sll_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   sll_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn sll defined at ../../../targets/mips/opmatch.def:257:1-34
 */
void insn_sll_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sll_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn sllv defined at ../../../targets/mips/opmatch.def:258:1-35
 */
void insn_sllv_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sllv_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn slt defined at ../../../targets/mips/opmatch.def:259:1-27
 */
void insn_slt_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   slt_e13e13(line, op_0, op_1);
}

/*
 * Insn slt defined at ../../../targets/mips/opmatch.def:260:1-32
 */
void insn_slt_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   slt_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn slt defined at ../../../targets/mips/opmatch.def:261:1-45
 */
void insn_slt_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   slt_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn slti defined at ../../../targets/mips/opmatch.def:262:1-40
 */
void insn_slti_reg_reg_s16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   slti_e13e13xi16(line, op_0, op_1, op_2);
}

/*
 * Insn sltu defined at ../../../targets/mips/opmatch.def:263:1-29
 */
void insn_sltu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   sltu_e13e13(line, op_0, op_1);
}

/*
 * Insn sltu defined at ../../../targets/mips/opmatch.def:264:1-34
 */
void insn_sltu_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sltu_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn sltu defined at ../../../targets/mips/opmatch.def:265:1-48
 */
void insn_sltu_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   sltu_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn sltiu defined at ../../../targets/mips/opmatch.def:266:1-42
 */
void insn_sltiu_reg_reg_s16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   sltiu_e13e13xi16(line, op_0, op_1, op_2);
}

/*
 * Insn sne defined at ../../../targets/mips/opmatch.def:267:1-13
 */
void insn_sne_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   sne_e13e13(line, op_0, op_1);
}

/*
 * Insn sne defined at ../../../targets/mips/opmatch.def:268:1-18
 */
void insn_sne_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sne_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn sne defined at ../../../targets/mips/opmatch.def:269:1-21
 */
void insn_sne_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   sne_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn snei defined at ../../../targets/mips/opmatch.def:270:1-25
 */
void insn_snei_reg_reg_u16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   snei_e13e13xu16(line, op_0, op_1, op_2);
}

/*
 * Insn sra defined at ../../../targets/mips/opmatch.def:271:1-34
 */
void insn_sra_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   sra_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn sra defined at ../../../targets/mips/opmatch.def:272:1-34
 */
void insn_sra_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sra_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn srav defined at ../../../targets/mips/opmatch.def:273:1-35
 */
void insn_srav_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   srav_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn srl defined at ../../../targets/mips/opmatch.def:274:1-34
 */
void insn_srl_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   srl_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn srl defined at ../../../targets/mips/opmatch.def:275:1-34
 */
void insn_srl_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   srl_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn srlv defined at ../../../targets/mips/opmatch.def:276:1-35
 */
void insn_srlv_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   srlv_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn ssnop defined at ../../../targets/mips/opmatch.def:277:1-6
 */
void insn_ssnop_(int line) {
   ssnop_(line);
}

/*
 * Insn sub defined at ../../../targets/mips/opmatch.def:278:1-27
 */
void insn_sub_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   sub_e13e13(line, op_0, op_1);
}

/*
 * Insn sub defined at ../../../targets/mips/opmatch.def:279:1-32
 */
void insn_sub_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sub_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn sub defined at ../../../targets/mips/opmatch.def:280:1-47
 */
void insn_sub_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   sub_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn subi defined at ../../../targets/mips/opmatch.def:281:1-44
 */
void insn_subi_reg_reg_s16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   subi_e13e13xi16(line, op_0, op_1, op_2);
}

/*
 * Insn subu defined at ../../../targets/mips/opmatch.def:282:1-29
 */
void insn_subu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   subu_e13e13(line, op_0, op_1);
}

/*
 * Insn subu defined at ../../../targets/mips/opmatch.def:283:1-34
 */
void insn_subu_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   subu_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn subu defined at ../../../targets/mips/opmatch.def:284:1-50
 */
void insn_subu_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   subu_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn subiu defined at ../../../targets/mips/opmatch.def:285:1-46
 */
void insn_subiu_reg_reg_s16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   subiu_e13e13xi16(line, op_0, op_1, op_2);
}

/*
 * Insn sw defined at ../../../targets/mips/opmatch.def:286:1-28
 */
void insn_sw_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   sw_e13xu32(line, op_0, op_1);
}

/*
 * Insn sw defined at ../../../targets/mips/opmatch.def:287:1-25
 */
void insn_sw_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   sw_e13mem(line, op_0, op_1);
}

/*
 * Insn swc1 defined at ../../../targets/mips/opmatch.def:288:1-18
 */
void insn_swc1_freg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   swc1_e12xu32(line, op_0, op_1);
}

/*
 * Insn swc1 defined at ../../../targets/mips/opmatch.def:289:1-15
 */
void insn_swc1_freg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   swc1_e12mem(line, op_0, op_1);
}

/*
 * Insn swc2 defined at ../../../targets/mips/opmatch.def:290:1-19
 */
void insn_swc2_c2reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   swc2_e9xu32(line, op_0, op_1);
}

/*
 * Insn swc2 defined at ../../../targets/mips/opmatch.def:291:1-16
 */
void insn_swc2_c2reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   swc2_e9mem(line, op_0, op_1);
}

/*
 * Insn swc3 defined at ../../../targets/mips/opmatch.def:292:1-19
 */
void insn_swc3_c3reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   swc3_e10xu32(line, op_0, op_1);
}

/*
 * Insn swc3 defined at ../../../targets/mips/opmatch.def:293:1-16
 */
void insn_swc3_c3reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   swc3_e10mem(line, op_0, op_1);
}

/*
 * Insn swl defined at ../../../targets/mips/opmatch.def:294:1-30
 */
void insn_swl_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   swl_e13xu32(line, op_0, op_1);
}

/*
 * Insn swl defined at ../../../targets/mips/opmatch.def:295:1-27
 */
void insn_swl_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   swl_e13mem(line, op_0, op_1);
}

/*
 * Insn swr defined at ../../../targets/mips/opmatch.def:296:1-30
 */
void insn_swr_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   swr_e13xu32(line, op_0, op_1);
}

/*
 * Insn swr defined at ../../../targets/mips/opmatch.def:297:1-27
 */
void insn_swr_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   swr_e13mem(line, op_0, op_1);
}

/*
 * Insn sync defined at ../../../targets/mips/opmatch.def:298:1-5
 */
void insn_sync_(int line) {
   sync_(line);
}

/*
 * Insn syscall defined at ../../../targets/mips/opmatch.def:299:1-8
 */
void insn_syscall_(int line) {
   syscall_(line);
}

/*
 * Insn syscall defined at ../../../targets/mips/opmatch.def:300:1-15
 */
void insn_syscall_number(int line, uint32_t op_0) {
   syscall_u32(line, op_0);
}

/*
 * Insn teq defined at ../../../targets/mips/opmatch.def:301:1-27
 */
void insn_teq_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   teq_e13e13(line, op_0, op_1);
}

/*
 * Insn teq defined at ../../../targets/mips/opmatch.def:302:1-34
 */
void insn_teq_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   teq_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn teq defined at ../../../targets/mips/opmatch.def:303:1-39
 */
void insn_teq_reg_number(int line, uint8_t op_0, uint32_t op_1) {
   teq_e13u32(line, op_0, op_1);
}

/*
 * Insn teqi defined at ../../../targets/mips/opmatch.def:304:1-34
 */
void insn_teqi_reg_s16expr(int line, uint8_t op_0, struct expr * op_1) {
   teqi_e13xi16(line, op_0, op_1);
}

/*
 * Insn tge defined at ../../../targets/mips/opmatch.def:305:1-27
 */
void insn_tge_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   tge_e13e13(line, op_0, op_1);
}

/*
 * Insn tge defined at ../../../targets/mips/opmatch.def:306:1-34
 */
void insn_tge_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   tge_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn tge defined at ../../../targets/mips/opmatch.def:307:1-39
 */
void insn_tge_reg_number(int line, uint8_t op_0, uint32_t op_1) {
   tge_e13u32(line, op_0, op_1);
}

/*
 * Insn tgei defined at ../../../targets/mips/opmatch.def:308:1-34
 */
void insn_tgei_reg_s16expr(int line, uint8_t op_0, struct expr * op_1) {
   tgei_e13xi16(line, op_0, op_1);
}

/*
 * Insn tgeu defined at ../../../targets/mips/opmatch.def:309:1-29
 */
void insn_tgeu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   tgeu_e13e13(line, op_0, op_1);
}

/*
 * Insn tgeu defined at ../../../targets/mips/opmatch.def:310:1-36
 */
void insn_tgeu_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   tgeu_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn tgeu defined at ../../../targets/mips/opmatch.def:311:1-42
 */
void insn_tgeu_reg_number(int line, uint8_t op_0, uint32_t op_1) {
   tgeu_e13u32(line, op_0, op_1);
}

/*
 * Insn tgeiu defined at ../../../targets/mips/opmatch.def:312:1-36
 */
void insn_tgeiu_reg_s16expr(int line, uint8_t op_0, struct expr * op_1) {
   tgeiu_e13xi16(line, op_0, op_1);
}

/*
 * Insn tlbp defined at ../../../targets/mips/opmatch.def:313:1-21
 */
void insn_tlbp_(int line) {
   tlbp_(line);
}

/*
 * Insn tlbr defined at ../../../targets/mips/opmatch.def:314:1-21
 */
void insn_tlbr_(int line) {
   tlbr_(line);
}

/*
 * Insn tlbwi defined at ../../../targets/mips/opmatch.def:315:1-23
 */
void insn_tlbwi_(int line) {
   tlbwi_(line);
}

/*
 * Insn tlbwr defined at ../../../targets/mips/opmatch.def:316:1-23
 */
void insn_tlbwr_(int line) {
   tlbwr_(line);
}

/*
 * Insn tlt defined at ../../../targets/mips/opmatch.def:317:1-27
 */
void insn_tlt_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   tlt_e13e13(line, op_0, op_1);
}

/*
 * Insn tlt defined at ../../../targets/mips/opmatch.def:318:1-34
 */
void insn_tlt_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   tlt_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn tlt defined at ../../../targets/mips/opmatch.def:319:1-39
 */
void insn_tlt_reg_number(int line, uint8_t op_0, uint32_t op_1) {
   tlt_e13u32(line, op_0, op_1);
}

/*
 * Insn tlti defined at ../../../targets/mips/opmatch.def:320:1-34
 */
void insn_tlti_reg_s16expr(int line, uint8_t op_0, struct expr * op_1) {
   tlti_e13xi16(line, op_0, op_1);
}

/*
 * Insn tltu defined at ../../../targets/mips/opmatch.def:321:1-29
 */
void insn_tltu_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   tltu_e13e13(line, op_0, op_1);
}

/*
 * Insn tltu defined at ../../../targets/mips/opmatch.def:322:1-36
 */
void insn_tltu_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   tltu_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn tltu defined at ../../../targets/mips/opmatch.def:323:1-42
 */
void insn_tltu_reg_number(int line, uint8_t op_0, uint32_t op_1) {
   tltu_e13u32(line, op_0, op_1);
}

/*
 * Insn tltiu defined at ../../../targets/mips/opmatch.def:324:1-36
 */
void insn_tltiu_reg_s16expr(int line, uint8_t op_0, struct expr * op_1) {
   tltiu_e13xi16(line, op_0, op_1);
}

/*
 * Insn tne defined at ../../../targets/mips/opmatch.def:325:1-27
 */
void insn_tne_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   tne_e13e13(line, op_0, op_1);
}

/*
 * Insn tne defined at ../../../targets/mips/opmatch.def:326:1-34
 */
void insn_tne_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   tne_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn tne defined at ../../../targets/mips/opmatch.def:327:1-39
 */
void insn_tne_reg_number(int line, uint8_t op_0, uint32_t op_1) {
   tne_e13u32(line, op_0, op_1);
}

/*
 * Insn tnei defined at ../../../targets/mips/opmatch.def:328:1-34
 */
void insn_tnei_reg_s16expr(int line, uint8_t op_0, struct expr * op_1) {
   tnei_e13xi16(line, op_0, op_1);
}

/*
 * Insn ulw defined at ../../../targets/mips/opmatch.def:329:1-16
 */
void insn_ulw_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ulw_e13xu32(line, op_0, op_1);
}

/*
 * Insn ulw defined at ../../../targets/mips/opmatch.def:330:1-13
 */
void insn_ulw_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   ulw_e13mem(line, op_0, op_1);
}

/*
 * Insn usw defined at ../../../targets/mips/opmatch.def:331:1-16
 */
void insn_usw_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   usw_e13xu32(line, op_0, op_1);
}

/*
 * Insn usw defined at ../../../targets/mips/opmatch.def:332:1-13
 */
void insn_usw_reg_mem(int line, uint8_t op_0, struct compound_mem * op_1) {
   usw_e13mem(line, op_0, op_1);
}

/*
 * Insn wait defined at ../../../targets/mips/opmatch.def:333:1-21
 */
void insn_wait_(int line) {
   wait_(line);
}

/*
 * Insn wait defined at ../../../targets/mips/opmatch.def:334:1-12
 */
void insn_wait_number(int line, uint32_t op_0) {
   wait_u32(line, op_0);
}

/*
 * Insn xor defined at ../../../targets/mips/opmatch.def:335:1-27
 */
void insn_xor_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   xor_e13e13(line, op_0, op_1);
}

/*
 * Insn xor defined at ../../../targets/mips/opmatch.def:336:1-32
 */
void insn_xor_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   xor_e13e13e13(line, op_0, op_1, op_2);
}

/*
 * Insn xor defined at ../../../targets/mips/opmatch.def:337:1-45
 */
void insn_xor_reg_reg_number(int line, uint8_t op_0, uint8_t op_1, uint32_t op_2) {
   xor_e13e13u32(line, op_0, op_1, op_2);
}

/*
 * Insn xori defined at ../../../targets/mips/opmatch.def:338:1-38
 */
void insn_xori_reg_reg_u16expr(int line, uint8_t op_0, uint8_t op_1, struct expr * op_2) {
   xori_e13e13xu16(line, op_0, op_1, op_2);
}

/*
 * Insn la defined at ../../../targets/mips/opmatch.def:340:1-15
 */
void insn_la_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   la_e13xu32(line, op_0, op_1);
}

/*
 * Insn li defined at ../../../targets/mips/opmatch.def:341:1-15
 */
void insn_li_reg_number(int line, uint8_t op_0, uint32_t op_1) {
   li_e13u32(line, op_0, op_1);
}

/*
 * Insn abs.s defined at ../../../targets/mips/opmatch.def:343:1-37
 */
void insn_abs_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   abs_s_e12e12(line, op_0, op_1);
}

/*
 * Insn abs.d defined at ../../../targets/mips/opmatch.def:344:1-37
 */
void insn_abs_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   abs_d_e12e12(line, op_0, op_1);
}

/*
 * Insn add.s defined at ../../../targets/mips/opmatch.def:345:1-38
 */
void insn_add_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   add_s_e12e12(line, op_0, op_1);
}

/*
 * Insn add.d defined at ../../../targets/mips/opmatch.def:346:1-38
 */
void insn_add_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   add_d_e12e12(line, op_0, op_1);
}

/*
 * Insn add.s defined at ../../../targets/mips/opmatch.def:347:1-42
 */
void insn_add_s_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   add_s_e12e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn add.d defined at ../../../targets/mips/opmatch.def:348:1-42
 */
void insn_add_d_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   add_d_e12e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn ceil.w.s defined at ../../../targets/mips/opmatch.def:349:1-42
 */
void insn_ceil_w_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   ceil_w_s_e12e12(line, op_0, op_1);
}

/*
 * Insn ceil.w.d defined at ../../../targets/mips/opmatch.def:350:1-42
 */
void insn_ceil_w_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   ceil_w_d_e12e12(line, op_0, op_1);
}

/*
 * Insn cvt.d.s defined at ../../../targets/mips/opmatch.def:351:1-40
 */
void insn_cvt_d_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   cvt_d_s_e12e12(line, op_0, op_1);
}

/*
 * Insn cvt.d.w defined at ../../../targets/mips/opmatch.def:352:1-40
 */
void insn_cvt_d_w_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   cvt_d_w_e12e12(line, op_0, op_1);
}

/*
 * Insn cvt.d.l defined at ../../../targets/mips/opmatch.def:353:1-40
 */
void insn_cvt_d_l_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   cvt_d_l_e12e12(line, op_0, op_1);
}

/*
 * Insn cvt.s.d defined at ../../../targets/mips/opmatch.def:354:1-40
 */
void insn_cvt_s_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   cvt_s_d_e12e12(line, op_0, op_1);
}

/*
 * Insn cvt.s.w defined at ../../../targets/mips/opmatch.def:355:1-40
 */
void insn_cvt_s_w_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   cvt_s_w_e12e12(line, op_0, op_1);
}

/*
 * Insn cvt.s.l defined at ../../../targets/mips/opmatch.def:356:1-40
 */
void insn_cvt_s_l_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   cvt_s_l_e12e12(line, op_0, op_1);
}

/*
 * Insn cvt.w.s defined at ../../../targets/mips/opmatch.def:357:1-40
 */
void insn_cvt_w_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   cvt_w_s_e12e12(line, op_0, op_1);
}

/*
 * Insn cvt.w.d defined at ../../../targets/mips/opmatch.def:358:1-40
 */
void insn_cvt_w_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   cvt_w_d_e12e12(line, op_0, op_1);
}

/*
 * Insn div.s defined at ../../../targets/mips/opmatch.def:359:1-38
 */
void insn_div_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   div_s_e12e12(line, op_0, op_1);
}

/*
 * Insn div.d defined at ../../../targets/mips/opmatch.def:360:1-38
 */
void insn_div_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   div_d_e12e12(line, op_0, op_1);
}

/*
 * Insn div.s defined at ../../../targets/mips/opmatch.def:361:1-42
 */
void insn_div_s_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   div_s_e12e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn div.d defined at ../../../targets/mips/opmatch.def:362:1-42
 */
void insn_div_d_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   div_d_e12e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn floor.w.s defined at ../../../targets/mips/opmatch.def:363:1-44
 */
void insn_floor_w_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   floor_w_s_e12e12(line, op_0, op_1);
}

/*
 * Insn floor.w.d defined at ../../../targets/mips/opmatch.def:364:1-44
 */
void insn_floor_w_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   floor_w_d_e12e12(line, op_0, op_1);
}

/*
 * Insn mov.s defined at ../../../targets/mips/opmatch.def:365:1-37
 */
void insn_mov_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   mov_s_e12e12(line, op_0, op_1);
}

/*
 * Insn mov.d defined at ../../../targets/mips/opmatch.def:366:1-37
 */
void insn_mov_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   mov_d_e12e12(line, op_0, op_1);
}

/*
 * Insn movf defined at ../../../targets/mips/opmatch.def:367:1-18
 */
void insn_movf_reg_reg_cc(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movf_e13e13e11(line, op_0, op_1, op_2);
}

/*
 * Insn movf.s defined at ../../../targets/mips/opmatch.def:368:1-34
 */
void insn_movf_s_freg_freg_cc(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movf_s_e12e12e11(line, op_0, op_1, op_2);
}

/*
 * Insn movf.d defined at ../../../targets/mips/opmatch.def:369:1-34
 */
void insn_movf_d_freg_freg_cc(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movf_d_e12e12e11(line, op_0, op_1, op_2);
}

/*
 * Insn movt defined at ../../../targets/mips/opmatch.def:370:1-18
 */
void insn_movt_reg_reg_cc(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movt_e13e13e11(line, op_0, op_1, op_2);
}

/*
 * Insn movt.s defined at ../../../targets/mips/opmatch.def:371:1-34
 */
void insn_movt_s_freg_freg_cc(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movt_s_e12e12e11(line, op_0, op_1, op_2);
}

/*
 * Insn movt.d defined at ../../../targets/mips/opmatch.def:372:1-34
 */
void insn_movt_d_freg_freg_cc(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movt_d_e12e12e11(line, op_0, op_1, op_2);
}

/*
 * Insn movn.s defined at ../../../targets/mips/opmatch.def:373:1-43
 */
void insn_movn_s_freg_freg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movn_s_e12e12e13(line, op_0, op_1, op_2);
}

/*
 * Insn movn.d defined at ../../../targets/mips/opmatch.def:374:1-43
 */
void insn_movn_d_freg_freg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movn_d_e12e12e13(line, op_0, op_1, op_2);
}

/*
 * Insn movz.s defined at ../../../targets/mips/opmatch.def:375:1-43
 */
void insn_movz_s_freg_freg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movz_s_e12e12e13(line, op_0, op_1, op_2);
}

/*
 * Insn movz.d defined at ../../../targets/mips/opmatch.def:376:1-43
 */
void insn_movz_d_freg_freg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movz_d_e12e12e13(line, op_0, op_1, op_2);
}

/*
 * Insn mul.s defined at ../../../targets/mips/opmatch.def:377:1-38
 */
void insn_mul_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   mul_s_e12e12(line, op_0, op_1);
}

/*
 * Insn mul.d defined at ../../../targets/mips/opmatch.def:378:1-38
 */
void insn_mul_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   mul_d_e12e12(line, op_0, op_1);
}

/*
 * Insn mul.s defined at ../../../targets/mips/opmatch.def:379:1-42
 */
void insn_mul_s_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mul_s_e12e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn mul.d defined at ../../../targets/mips/opmatch.def:380:1-42
 */
void insn_mul_d_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mul_d_e12e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn neg.s defined at ../../../targets/mips/opmatch.def:381:1-37
 */
void insn_neg_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   neg_s_e12e12(line, op_0, op_1);
}

/*
 * Insn neg.d defined at ../../../targets/mips/opmatch.def:382:1-37
 */
void insn_neg_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   neg_d_e12e12(line, op_0, op_1);
}

/*
 * Insn round.w.s defined at ../../../targets/mips/opmatch.def:383:1-44
 */
void insn_round_w_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   round_w_s_e12e12(line, op_0, op_1);
}

/*
 * Insn round.w.d defined at ../../../targets/mips/opmatch.def:384:1-44
 */
void insn_round_w_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   round_w_d_e12e12(line, op_0, op_1);
}

/*
 * Insn sqrt.s defined at ../../../targets/mips/opmatch.def:385:1-39
 */
void insn_sqrt_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   sqrt_s_e12e12(line, op_0, op_1);
}

/*
 * Insn sqrt.d defined at ../../../targets/mips/opmatch.def:386:1-39
 */
void insn_sqrt_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   sqrt_d_e12e12(line, op_0, op_1);
}

/*
 * Insn sub.s defined at ../../../targets/mips/opmatch.def:387:1-38
 */
void insn_sub_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   sub_s_e12e12(line, op_0, op_1);
}

/*
 * Insn sub.d defined at ../../../targets/mips/opmatch.def:388:1-38
 */
void insn_sub_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   sub_d_e12e12(line, op_0, op_1);
}

/*
 * Insn sub.s defined at ../../../targets/mips/opmatch.def:389:1-42
 */
void insn_sub_s_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sub_s_e12e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn sub.d defined at ../../../targets/mips/opmatch.def:390:1-42
 */
void insn_sub_d_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sub_d_e12e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn trunc.w.s defined at ../../../targets/mips/opmatch.def:391:1-44
 */
void insn_trunc_w_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   trunc_w_s_e12e12(line, op_0, op_1);
}

/*
 * Insn trunc.w.d defined at ../../../targets/mips/opmatch.def:392:1-44
 */
void insn_trunc_w_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   trunc_w_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.f.s defined at ../../../targets/mips/opmatch.def:395:1-30
 */
void insn_c_f_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_f_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.un.s defined at ../../../targets/mips/opmatch.def:396:1-32
 */
void insn_c_un_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_un_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.eq.s defined at ../../../targets/mips/opmatch.def:397:1-32
 */
void insn_c_eq_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_eq_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ueq.s defined at ../../../targets/mips/opmatch.def:398:1-34
 */
void insn_c_ueq_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ueq_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.olt.s defined at ../../../targets/mips/opmatch.def:399:1-34
 */
void insn_c_olt_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_olt_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ult.s defined at ../../../targets/mips/opmatch.def:400:1-34
 */
void insn_c_ult_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ult_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ole.s defined at ../../../targets/mips/opmatch.def:401:1-34
 */
void insn_c_ole_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ole_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ule.s defined at ../../../targets/mips/opmatch.def:402:1-34
 */
void insn_c_ule_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ule_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.sf.s defined at ../../../targets/mips/opmatch.def:403:1-32
 */
void insn_c_sf_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_sf_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ngle.s defined at ../../../targets/mips/opmatch.def:404:1-36
 */
void insn_c_ngle_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ngle_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.seq.s defined at ../../../targets/mips/opmatch.def:405:1-34
 */
void insn_c_seq_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_seq_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ngl.s defined at ../../../targets/mips/opmatch.def:406:1-34
 */
void insn_c_ngl_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ngl_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.lt.s defined at ../../../targets/mips/opmatch.def:407:1-32
 */
void insn_c_lt_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_lt_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.nge.s defined at ../../../targets/mips/opmatch.def:408:1-34
 */
void insn_c_nge_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_nge_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.le.s defined at ../../../targets/mips/opmatch.def:409:1-32
 */
void insn_c_le_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_le_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ngt.s defined at ../../../targets/mips/opmatch.def:410:1-34
 */
void insn_c_ngt_s_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ngt_s_e12e12(line, op_0, op_1);
}

/*
 * Insn c.f.d defined at ../../../targets/mips/opmatch.def:411:1-30
 */
void insn_c_f_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_f_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.un.d defined at ../../../targets/mips/opmatch.def:412:1-32
 */
void insn_c_un_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_un_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.eq.d defined at ../../../targets/mips/opmatch.def:413:1-32
 */
void insn_c_eq_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_eq_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ueq.d defined at ../../../targets/mips/opmatch.def:414:1-34
 */
void insn_c_ueq_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ueq_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.olt.d defined at ../../../targets/mips/opmatch.def:415:1-34
 */
void insn_c_olt_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_olt_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ult.d defined at ../../../targets/mips/opmatch.def:416:1-34
 */
void insn_c_ult_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ult_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ole.d defined at ../../../targets/mips/opmatch.def:417:1-34
 */
void insn_c_ole_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ole_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ule.d defined at ../../../targets/mips/opmatch.def:418:1-34
 */
void insn_c_ule_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ule_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.sf.d defined at ../../../targets/mips/opmatch.def:419:1-32
 */
void insn_c_sf_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_sf_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ngle.d defined at ../../../targets/mips/opmatch.def:420:1-36
 */
void insn_c_ngle_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ngle_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.seq.d defined at ../../../targets/mips/opmatch.def:421:1-34
 */
void insn_c_seq_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_seq_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ngl.d defined at ../../../targets/mips/opmatch.def:422:1-34
 */
void insn_c_ngl_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ngl_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.lt.d defined at ../../../targets/mips/opmatch.def:423:1-32
 */
void insn_c_lt_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_lt_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.nge.d defined at ../../../targets/mips/opmatch.def:424:1-34
 */
void insn_c_nge_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_nge_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.le.d defined at ../../../targets/mips/opmatch.def:425:1-32
 */
void insn_c_le_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_le_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.ngt.d defined at ../../../targets/mips/opmatch.def:426:1-34
 */
void insn_c_ngt_d_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   c_ngt_d_e12e12(line, op_0, op_1);
}

/*
 * Insn c.f.s defined at ../../../targets/mips/opmatch.def:427:1-34
 */
void insn_c_f_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_f_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.un.s defined at ../../../targets/mips/opmatch.def:428:1-36
 */
void insn_c_un_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_un_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.eq.s defined at ../../../targets/mips/opmatch.def:429:1-36
 */
void insn_c_eq_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_eq_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ueq.s defined at ../../../targets/mips/opmatch.def:430:1-38
 */
void insn_c_ueq_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ueq_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.olt.s defined at ../../../targets/mips/opmatch.def:431:1-38
 */
void insn_c_olt_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_olt_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ult.s defined at ../../../targets/mips/opmatch.def:432:1-38
 */
void insn_c_ult_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ult_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ole.s defined at ../../../targets/mips/opmatch.def:433:1-38
 */
void insn_c_ole_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ole_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ule.s defined at ../../../targets/mips/opmatch.def:434:1-38
 */
void insn_c_ule_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ule_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.sf.s defined at ../../../targets/mips/opmatch.def:435:1-36
 */
void insn_c_sf_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_sf_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ngle.s defined at ../../../targets/mips/opmatch.def:436:1-40
 */
void insn_c_ngle_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ngle_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.seq.s defined at ../../../targets/mips/opmatch.def:437:1-38
 */
void insn_c_seq_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_seq_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ngl.s defined at ../../../targets/mips/opmatch.def:438:1-38
 */
void insn_c_ngl_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ngl_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.lt.s defined at ../../../targets/mips/opmatch.def:439:1-36
 */
void insn_c_lt_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_lt_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.nge.s defined at ../../../targets/mips/opmatch.def:440:1-38
 */
void insn_c_nge_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_nge_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.le.s defined at ../../../targets/mips/opmatch.def:441:1-36
 */
void insn_c_le_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_le_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ngt.s defined at ../../../targets/mips/opmatch.def:442:1-38
 */
void insn_c_ngt_s_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ngt_s_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.f.d defined at ../../../targets/mips/opmatch.def:443:1-34
 */
void insn_c_f_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_f_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.un.d defined at ../../../targets/mips/opmatch.def:444:1-36
 */
void insn_c_un_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_un_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.eq.d defined at ../../../targets/mips/opmatch.def:445:1-36
 */
void insn_c_eq_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_eq_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ueq.d defined at ../../../targets/mips/opmatch.def:446:1-38
 */
void insn_c_ueq_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ueq_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.olt.d defined at ../../../targets/mips/opmatch.def:447:1-38
 */
void insn_c_olt_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_olt_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ult.d defined at ../../../targets/mips/opmatch.def:448:1-38
 */
void insn_c_ult_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ult_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ole.d defined at ../../../targets/mips/opmatch.def:449:1-38
 */
void insn_c_ole_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ole_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ule.d defined at ../../../targets/mips/opmatch.def:450:1-38
 */
void insn_c_ule_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ule_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.sf.d defined at ../../../targets/mips/opmatch.def:451:1-36
 */
void insn_c_sf_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_sf_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ngle.d defined at ../../../targets/mips/opmatch.def:452:1-40
 */
void insn_c_ngle_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ngle_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.seq.d defined at ../../../targets/mips/opmatch.def:453:1-38
 */
void insn_c_seq_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_seq_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ngl.d defined at ../../../targets/mips/opmatch.def:454:1-38
 */
void insn_c_ngl_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ngl_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.lt.d defined at ../../../targets/mips/opmatch.def:455:1-36
 */
void insn_c_lt_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_lt_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.nge.d defined at ../../../targets/mips/opmatch.def:456:1-38
 */
void insn_c_nge_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_nge_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.le.d defined at ../../../targets/mips/opmatch.def:457:1-36
 */
void insn_c_le_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_le_d_e11e12e12(line, op_0, op_1, op_2);
}

/*
 * Insn c.ngt.d defined at ../../../targets/mips/opmatch.def:458:1-38
 */
void insn_c_ngt_d_cc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   c_ngt_d_e11e12e12(line, op_0, op_1, op_2);
}

