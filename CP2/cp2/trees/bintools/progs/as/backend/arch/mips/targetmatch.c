/* Automatically generated; do not edit */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "common.h"

#include "expr.h"
#include "backend.h"
#include "targetoper.h"
#include "match.h"
#include "targetmatch.h"


static UNUSED bool check_reg(struct operand *oper) {
   return oper->is_reg;
}
static UNUSED bool check_c0reg(struct operand *oper) {
   return oper->is_c0reg;
}
static UNUSED bool check_freg(struct operand *oper) {
   return oper->is_freg;
}
static UNUSED bool check_c2reg(struct operand *oper) {
   return oper->is_c2reg;
}
static UNUSED bool check_c3reg(struct operand *oper) {
   return oper->is_c3reg;
}
static UNUSED bool check_cc(struct operand *oper) {
   return oper->is_cc;
}
static UNUSED bool check_sel(struct operand *oper) {
   return oper->is_sel;
}
static UNUSED bool check_rtag(struct operand *oper) {
   return oper->is_rtag;
}
static UNUSED bool check_expr(struct operand *oper) {
   return oper->is_expr;
}
static UNUSED bool check_number(struct operand *oper) {
   return oper->is_number;
}
static UNUSED bool check_symbol(struct operand *oper) {
   return oper->is_symbol;
}
static UNUSED bool check_s16expr(struct operand *oper) {
   return oper->is_s16expr;
}
static UNUSED bool check_u16expr(struct operand *oper) {
   return oper->is_u16expr;
}
static UNUSED bool check_mem(struct operand *oper) {
   return oper->is_mem;
}
static UNUSED bool check_qstring(struct operand *oper) {
   return oper->is_qstring;
}
static UNUSED bool check_symboltype(struct operand *oper) {
   return oper->is_symboltype;
}
static UNUSED bool check_sectiontype(struct operand *oper) {
   return oper->is_sectiontype;
}
static UNUSED bool check_magiczero(struct operand *oper) {
   return oper->is_magiczero;
}

static void call_0(int line, struct operandarray *ops) {
   insn_abs_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_1(int line, struct operandarray *ops) {
   insn_abs_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_2(int line, struct operandarray *ops) {
   insn_add_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_3(int line, struct operandarray *ops) {
   insn_add_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_4(int line, struct operandarray *ops) {
   insn_add_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_5(int line, struct operandarray *ops) {
   insn_addi_reg_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_s16expr);
}

static void call_6(int line, struct operandarray *ops) {
   insn_addu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_7(int line, struct operandarray *ops) {
   insn_addu_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_8(int line, struct operandarray *ops) {
   insn_addu_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_9(int line, struct operandarray *ops) {
   insn_addiu_reg_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_s16expr);
}

static void call_10(int line, struct operandarray *ops) {
   insn_and_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_11(int line, struct operandarray *ops) {
   insn_and_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_12(int line, struct operandarray *ops) {
   insn_and_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_13(int line, struct operandarray *ops) {
   insn_andi_reg_reg_u16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_u16expr);
}

static void call_14(int line, struct operandarray *ops) {
   insn_b_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_15(int line, struct operandarray *ops) {
   insn_bal_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_16(int line, struct operandarray *ops) {
   insn_bc1f_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_17(int line, struct operandarray *ops) {
   insn_bc1f_cc_symbol(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_symbol);
}

static void call_18(int line, struct operandarray *ops) {
   insn_bc1fl_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_19(int line, struct operandarray *ops) {
   insn_bc1fl_cc_symbol(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_symbol);
}

static void call_20(int line, struct operandarray *ops) {
   insn_bc1t_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_21(int line, struct operandarray *ops) {
   insn_bc1t_cc_symbol(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_symbol);
}

static void call_22(int line, struct operandarray *ops) {
   insn_bc1tl_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_23(int line, struct operandarray *ops) {
   insn_bc1tl_cc_symbol(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_symbol);
}

static void call_24(int line, struct operandarray *ops) {
   insn_bc2f_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_25(int line, struct operandarray *ops) {
   insn_bc2f_cc_symbol(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_symbol);
}

static void call_26(int line, struct operandarray *ops) {
   insn_bc2fl_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_27(int line, struct operandarray *ops) {
   insn_bc2fl_cc_symbol(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_symbol);
}

static void call_28(int line, struct operandarray *ops) {
   insn_bc2t_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_29(int line, struct operandarray *ops) {
   insn_bc2t_cc_symbol(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_symbol);
}

static void call_30(int line, struct operandarray *ops) {
   insn_bc2tl_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_31(int line, struct operandarray *ops) {
   insn_bc2tl_cc_symbol(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_symbol);
}

static void call_32(int line, struct operandarray *ops) {
   insn_bc3f_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_33(int line, struct operandarray *ops) {
   insn_bc3f_cc_symbol(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_symbol);
}

static void call_34(int line, struct operandarray *ops) {
   insn_bc3fl_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_35(int line, struct operandarray *ops) {
   insn_bc3fl_cc_symbol(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_symbol);
}

static void call_36(int line, struct operandarray *ops) {
   insn_bc3t_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_37(int line, struct operandarray *ops) {
   insn_bc3t_cc_symbol(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_symbol);
}

static void call_38(int line, struct operandarray *ops) {
   insn_bc3tl_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_39(int line, struct operandarray *ops) {
   insn_bc3tl_cc_symbol(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_symbol);
}

static void call_40(int line, struct operandarray *ops) {
   insn_beq_reg_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_symbol);
}

static void call_41(int line, struct operandarray *ops) {
   insn_beq_reg_number_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_symbol);
}

static void call_42(int line, struct operandarray *ops) {
   insn_beql_reg_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_symbol);
}

static void call_43(int line, struct operandarray *ops) {
   insn_beql_reg_number_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_symbol);
}

static void call_44(int line, struct operandarray *ops) {
   insn_beqz_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_45(int line, struct operandarray *ops) {
   insn_beqzl_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_46(int line, struct operandarray *ops) {
   insn_bgez_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_47(int line, struct operandarray *ops) {
   insn_bgezl_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_48(int line, struct operandarray *ops) {
   insn_bgezal_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_49(int line, struct operandarray *ops) {
   insn_bgezall_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_50(int line, struct operandarray *ops) {
   insn_bgtz_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_51(int line, struct operandarray *ops) {
   insn_bgtzl_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_52(int line, struct operandarray *ops) {
   insn_blez_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_53(int line, struct operandarray *ops) {
   insn_blezl_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_54(int line, struct operandarray *ops) {
   insn_bltz_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_55(int line, struct operandarray *ops) {
   insn_bltzl_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_56(int line, struct operandarray *ops) {
   insn_bltzal_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_57(int line, struct operandarray *ops) {
   insn_bltzall_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_58(int line, struct operandarray *ops) {
   insn_bne_reg_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_symbol);
}

static void call_59(int line, struct operandarray *ops) {
   insn_bne_reg_number_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_symbol);
}

static void call_60(int line, struct operandarray *ops) {
   insn_bnel_reg_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_symbol);
}

static void call_61(int line, struct operandarray *ops) {
   insn_bnel_reg_number_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_symbol);
}

static void call_62(int line, struct operandarray *ops) {
   insn_bnez_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_63(int line, struct operandarray *ops) {
   insn_bnezl_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_64(int line, struct operandarray *ops) {
   (void)ops;
   insn_break_(line);
}

static void call_65(int line, struct operandarray *ops) {
   insn_break_number(line, operandarray_get(ops, 0)->val_number);
}

static void call_66(int line, struct operandarray *ops) {
   insn_break_number_number(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_67(int line, struct operandarray *ops) {
   insn_cache_number_symbol(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_symbol);
}

static void call_68(int line, struct operandarray *ops) {
   insn_cache_number_mem(line, operandarray_get(ops, 0)->val_number, &operandarray_get(ops, 1)->val_mem);
}

static void call_69(int line, struct operandarray *ops) {
   insn_cfc1_reg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg);
}

static void call_70(int line, struct operandarray *ops) {
   insn_cfc2_reg_c2reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c2reg);
}

static void call_71(int line, struct operandarray *ops) {
   insn_cfc3_reg_c3reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c3reg);
}

static void call_72(int line, struct operandarray *ops) {
   insn_clo_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_73(int line, struct operandarray *ops) {
   insn_clz_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_74(int line, struct operandarray *ops) {
   insn_cop2_number(line, operandarray_get(ops, 0)->val_number);
}

static void call_75(int line, struct operandarray *ops) {
   insn_cop3_number(line, operandarray_get(ops, 0)->val_number);
}

static void call_76(int line, struct operandarray *ops) {
   insn_ctc1_reg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg);
}

static void call_77(int line, struct operandarray *ops) {
   insn_ctc2_reg_c2reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c2reg);
}

static void call_78(int line, struct operandarray *ops) {
   insn_ctc3_reg_c3reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c3reg);
}

static void call_79(int line, struct operandarray *ops) {
   (void)ops;
   insn_deret_(line);
}

static void call_80(int line, struct operandarray *ops) {
   insn_div_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_81(int line, struct operandarray *ops) {
   insn_div_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_82(int line, struct operandarray *ops) {
   insn_divu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_83(int line, struct operandarray *ops) {
   insn_divu_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_84(int line, struct operandarray *ops) {
   (void)ops;
   insn_eret_(line);
}

static void call_85(int line, struct operandarray *ops) {
   insn_j_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_86(int line, struct operandarray *ops) {
   insn_j_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_87(int line, struct operandarray *ops) {
   insn_jr_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_88(int line, struct operandarray *ops) {
   insn_jal_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_89(int line, struct operandarray *ops) {
   insn_jal_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_90(int line, struct operandarray *ops) {
   insn_jal_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_91(int line, struct operandarray *ops) {
   insn_jalr_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_92(int line, struct operandarray *ops) {
   insn_jalr_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_93(int line, struct operandarray *ops) {
   insn_lb_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_94(int line, struct operandarray *ops) {
   insn_lb_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_95(int line, struct operandarray *ops) {
   insn_lbu_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_96(int line, struct operandarray *ops) {
   insn_lbu_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_97(int line, struct operandarray *ops) {
   insn_ldc1_freg_symbol(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_symbol);
}

static void call_98(int line, struct operandarray *ops) {
   insn_ldc1_freg_mem(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_mem);
}

static void call_99(int line, struct operandarray *ops) {
   insn_ldc2_c2reg_symbol(line, operandarray_get(ops, 0)->val_c2reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_100(int line, struct operandarray *ops) {
   insn_ldc2_c2reg_mem(line, operandarray_get(ops, 0)->val_c2reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_101(int line, struct operandarray *ops) {
   insn_ldc3_c3reg_symbol(line, operandarray_get(ops, 0)->val_c3reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_102(int line, struct operandarray *ops) {
   insn_ldc3_c3reg_mem(line, operandarray_get(ops, 0)->val_c3reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_103(int line, struct operandarray *ops) {
   insn_lh_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_104(int line, struct operandarray *ops) {
   insn_lh_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_105(int line, struct operandarray *ops) {
   insn_lhu_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_106(int line, struct operandarray *ops) {
   insn_lhu_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_107(int line, struct operandarray *ops) {
   insn_ll_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_108(int line, struct operandarray *ops) {
   insn_ll_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_109(int line, struct operandarray *ops) {
   insn_lui_reg_u16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_u16expr);
}

static void call_110(int line, struct operandarray *ops) {
   insn_lw_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_111(int line, struct operandarray *ops) {
   insn_lw_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_112(int line, struct operandarray *ops) {
   insn_lwc1_freg_symbol(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_symbol);
}

static void call_113(int line, struct operandarray *ops) {
   insn_lwc1_freg_mem(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_mem);
}

static void call_114(int line, struct operandarray *ops) {
   insn_lwc2_c2reg_symbol(line, operandarray_get(ops, 0)->val_c2reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_115(int line, struct operandarray *ops) {
   insn_lwc2_c2reg_mem(line, operandarray_get(ops, 0)->val_c2reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_116(int line, struct operandarray *ops) {
   insn_lwc3_c3reg_symbol(line, operandarray_get(ops, 0)->val_c3reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_117(int line, struct operandarray *ops) {
   insn_lwc3_c3reg_mem(line, operandarray_get(ops, 0)->val_c3reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_118(int line, struct operandarray *ops) {
   insn_lwl_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_119(int line, struct operandarray *ops) {
   insn_lwl_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_120(int line, struct operandarray *ops) {
   insn_lwr_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_121(int line, struct operandarray *ops) {
   insn_lwr_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_122(int line, struct operandarray *ops) {
   insn_madd_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_123(int line, struct operandarray *ops) {
   insn_maddu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_124(int line, struct operandarray *ops) {
   insn_mfc0_reg_c0reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c0reg);
}

static void call_125(int line, struct operandarray *ops) {
   insn_mfc0_reg_c0reg_sel(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c0reg, operandarray_get(ops, 2)->val_sel);
}

static void call_126(int line, struct operandarray *ops) {
   insn_mfc1_reg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg);
}

static void call_127(int line, struct operandarray *ops) {
   insn_mfc2_reg_c2reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c2reg);
}

static void call_128(int line, struct operandarray *ops) {
   insn_mfc2_reg_c2reg_sel(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c2reg, operandarray_get(ops, 2)->val_sel);
}

static void call_129(int line, struct operandarray *ops) {
   insn_mfc3_reg_c3reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c3reg);
}

static void call_130(int line, struct operandarray *ops) {
   insn_mfc3_reg_c3reg_sel(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c3reg, operandarray_get(ops, 2)->val_sel);
}

static void call_131(int line, struct operandarray *ops) {
   insn_mfhi_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_132(int line, struct operandarray *ops) {
   insn_mflo_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_133(int line, struct operandarray *ops) {
   insn_move_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_134(int line, struct operandarray *ops) {
   insn_movn_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_135(int line, struct operandarray *ops) {
   insn_movz_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_136(int line, struct operandarray *ops) {
   insn_msub_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_137(int line, struct operandarray *ops) {
   insn_msubu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_138(int line, struct operandarray *ops) {
   insn_mtc0_reg_c0reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c0reg);
}

static void call_139(int line, struct operandarray *ops) {
   insn_mtc0_reg_c0reg_sel(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c0reg, operandarray_get(ops, 2)->val_sel);
}

static void call_140(int line, struct operandarray *ops) {
   insn_mtc1_reg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg);
}

static void call_141(int line, struct operandarray *ops) {
   insn_mtc2_reg_c2reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c2reg);
}

static void call_142(int line, struct operandarray *ops) {
   insn_mtc2_reg_c2reg_sel(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c2reg, operandarray_get(ops, 2)->val_sel);
}

static void call_143(int line, struct operandarray *ops) {
   insn_mtc3_reg_c3reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c3reg);
}

static void call_144(int line, struct operandarray *ops) {
   insn_mtc3_reg_c3reg_sel(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_c3reg, operandarray_get(ops, 2)->val_sel);
}

static void call_145(int line, struct operandarray *ops) {
   insn_mthi_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_146(int line, struct operandarray *ops) {
   insn_mtlo_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_147(int line, struct operandarray *ops) {
   insn_mul_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_148(int line, struct operandarray *ops) {
   insn_mult_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_149(int line, struct operandarray *ops) {
   insn_multu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_150(int line, struct operandarray *ops) {
   insn_neg_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_151(int line, struct operandarray *ops) {
   insn_neg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_152(int line, struct operandarray *ops) {
   insn_negu_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_153(int line, struct operandarray *ops) {
   insn_negu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_154(int line, struct operandarray *ops) {
   (void)ops;
   insn_nop_(line);
}

static void call_155(int line, struct operandarray *ops) {
   insn_nor_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_156(int line, struct operandarray *ops) {
   insn_nor_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_157(int line, struct operandarray *ops) {
   insn_nor_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_158(int line, struct operandarray *ops) {
   insn_nori_reg_reg_u16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_u16expr);
}

static void call_159(int line, struct operandarray *ops) {
   insn_not_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_160(int line, struct operandarray *ops) {
   insn_not_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_161(int line, struct operandarray *ops) {
   insn_or_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_162(int line, struct operandarray *ops) {
   insn_or_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_163(int line, struct operandarray *ops) {
   insn_or_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_164(int line, struct operandarray *ops) {
   insn_ori_reg_reg_u16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_u16expr);
}

static void call_165(int line, struct operandarray *ops) {
   insn_pref_number_symbol(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_symbol);
}

static void call_166(int line, struct operandarray *ops) {
   insn_pref_number_mem(line, operandarray_get(ops, 0)->val_number, &operandarray_get(ops, 1)->val_mem);
}

static void call_167(int line, struct operandarray *ops) {
   (void)ops;
   insn_rfe_(line);
}

static void call_168(int line, struct operandarray *ops) {
   insn_rol_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_169(int line, struct operandarray *ops) {
   insn_rol_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_170(int line, struct operandarray *ops) {
   insn_ror_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_171(int line, struct operandarray *ops) {
   insn_ror_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_172(int line, struct operandarray *ops) {
   insn_sb_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_173(int line, struct operandarray *ops) {
   insn_sb_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_174(int line, struct operandarray *ops) {
   insn_sc_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_175(int line, struct operandarray *ops) {
   insn_sc_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_176(int line, struct operandarray *ops) {
   (void)ops;
   insn_sdbbp_(line);
}

static void call_177(int line, struct operandarray *ops) {
   insn_sdbbp_number(line, operandarray_get(ops, 0)->val_number);
}

static void call_178(int line, struct operandarray *ops) {
   insn_sdc1_freg_symbol(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_symbol);
}

static void call_179(int line, struct operandarray *ops) {
   insn_sdc1_freg_mem(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_mem);
}

static void call_180(int line, struct operandarray *ops) {
   insn_sdc2_c2reg_symbol(line, operandarray_get(ops, 0)->val_c2reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_181(int line, struct operandarray *ops) {
   insn_sdc2_c2reg_mem(line, operandarray_get(ops, 0)->val_c2reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_182(int line, struct operandarray *ops) {
   insn_sdc3_c3reg_symbol(line, operandarray_get(ops, 0)->val_c3reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_183(int line, struct operandarray *ops) {
   insn_sdc3_c3reg_mem(line, operandarray_get(ops, 0)->val_c3reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_184(int line, struct operandarray *ops) {
   insn_seq_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_185(int line, struct operandarray *ops) {
   insn_seq_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_186(int line, struct operandarray *ops) {
   insn_seq_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_187(int line, struct operandarray *ops) {
   insn_seqi_reg_reg_u16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_u16expr);
}

static void call_188(int line, struct operandarray *ops) {
   insn_sge_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_189(int line, struct operandarray *ops) {
   insn_sge_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_190(int line, struct operandarray *ops) {
   insn_sge_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_191(int line, struct operandarray *ops) {
   insn_sgeu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_192(int line, struct operandarray *ops) {
   insn_sgeu_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_193(int line, struct operandarray *ops) {
   insn_sgeu_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_194(int line, struct operandarray *ops) {
   insn_sgei_reg_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_s16expr);
}

static void call_195(int line, struct operandarray *ops) {
   insn_sgeiu_reg_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_s16expr);
}

static void call_196(int line, struct operandarray *ops) {
   insn_sgt_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_197(int line, struct operandarray *ops) {
   insn_sgt_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_198(int line, struct operandarray *ops) {
   insn_sgt_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_199(int line, struct operandarray *ops) {
   insn_sgtu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_200(int line, struct operandarray *ops) {
   insn_sgtu_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_201(int line, struct operandarray *ops) {
   insn_sgtu_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_202(int line, struct operandarray *ops) {
   insn_sgti_reg_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_s16expr);
}

static void call_203(int line, struct operandarray *ops) {
   insn_sgtiu_reg_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_s16expr);
}

static void call_204(int line, struct operandarray *ops) {
   insn_sh_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_205(int line, struct operandarray *ops) {
   insn_sh_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_206(int line, struct operandarray *ops) {
   insn_sle_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_207(int line, struct operandarray *ops) {
   insn_sle_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_208(int line, struct operandarray *ops) {
   insn_sle_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_209(int line, struct operandarray *ops) {
   insn_sleu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_210(int line, struct operandarray *ops) {
   insn_sleu_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_211(int line, struct operandarray *ops) {
   insn_sleu_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_212(int line, struct operandarray *ops) {
   insn_slei_reg_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_s16expr);
}

static void call_213(int line, struct operandarray *ops) {
   insn_sleiu_reg_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_s16expr);
}

static void call_214(int line, struct operandarray *ops) {
   insn_sll_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_215(int line, struct operandarray *ops) {
   insn_sll_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_216(int line, struct operandarray *ops) {
   insn_sllv_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_217(int line, struct operandarray *ops) {
   insn_slt_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_218(int line, struct operandarray *ops) {
   insn_slt_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_219(int line, struct operandarray *ops) {
   insn_slt_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_220(int line, struct operandarray *ops) {
   insn_slti_reg_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_s16expr);
}

static void call_221(int line, struct operandarray *ops) {
   insn_sltu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_222(int line, struct operandarray *ops) {
   insn_sltu_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_223(int line, struct operandarray *ops) {
   insn_sltu_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_224(int line, struct operandarray *ops) {
   insn_sltiu_reg_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_s16expr);
}

static void call_225(int line, struct operandarray *ops) {
   insn_sne_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_226(int line, struct operandarray *ops) {
   insn_sne_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_227(int line, struct operandarray *ops) {
   insn_sne_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_228(int line, struct operandarray *ops) {
   insn_snei_reg_reg_u16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_u16expr);
}

static void call_229(int line, struct operandarray *ops) {
   insn_sra_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_230(int line, struct operandarray *ops) {
   insn_sra_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_231(int line, struct operandarray *ops) {
   insn_srav_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_232(int line, struct operandarray *ops) {
   insn_srl_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_233(int line, struct operandarray *ops) {
   insn_srl_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_234(int line, struct operandarray *ops) {
   insn_srlv_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_235(int line, struct operandarray *ops) {
   (void)ops;
   insn_ssnop_(line);
}

static void call_236(int line, struct operandarray *ops) {
   insn_sub_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_237(int line, struct operandarray *ops) {
   insn_sub_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_238(int line, struct operandarray *ops) {
   insn_sub_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_239(int line, struct operandarray *ops) {
   insn_subi_reg_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_s16expr);
}

static void call_240(int line, struct operandarray *ops) {
   insn_subu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_241(int line, struct operandarray *ops) {
   insn_subu_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_242(int line, struct operandarray *ops) {
   insn_subu_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_243(int line, struct operandarray *ops) {
   insn_subiu_reg_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_s16expr);
}

static void call_244(int line, struct operandarray *ops) {
   insn_sw_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_245(int line, struct operandarray *ops) {
   insn_sw_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_246(int line, struct operandarray *ops) {
   insn_swc1_freg_symbol(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_symbol);
}

static void call_247(int line, struct operandarray *ops) {
   insn_swc1_freg_mem(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_mem);
}

static void call_248(int line, struct operandarray *ops) {
   insn_swc2_c2reg_symbol(line, operandarray_get(ops, 0)->val_c2reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_249(int line, struct operandarray *ops) {
   insn_swc2_c2reg_mem(line, operandarray_get(ops, 0)->val_c2reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_250(int line, struct operandarray *ops) {
   insn_swc3_c3reg_symbol(line, operandarray_get(ops, 0)->val_c3reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_251(int line, struct operandarray *ops) {
   insn_swc3_c3reg_mem(line, operandarray_get(ops, 0)->val_c3reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_252(int line, struct operandarray *ops) {
   insn_swl_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_253(int line, struct operandarray *ops) {
   insn_swl_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_254(int line, struct operandarray *ops) {
   insn_swr_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_255(int line, struct operandarray *ops) {
   insn_swr_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_256(int line, struct operandarray *ops) {
   (void)ops;
   insn_sync_(line);
}

static void call_257(int line, struct operandarray *ops) {
   (void)ops;
   insn_syscall_(line);
}

static void call_258(int line, struct operandarray *ops) {
   insn_syscall_number(line, operandarray_get(ops, 0)->val_number);
}

static void call_259(int line, struct operandarray *ops) {
   insn_teq_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_260(int line, struct operandarray *ops) {
   insn_teq_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_261(int line, struct operandarray *ops) {
   insn_teq_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number);
}

static void call_262(int line, struct operandarray *ops) {
   insn_teqi_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_s16expr);
}

static void call_263(int line, struct operandarray *ops) {
   insn_tge_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_264(int line, struct operandarray *ops) {
   insn_tge_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_265(int line, struct operandarray *ops) {
   insn_tge_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number);
}

static void call_266(int line, struct operandarray *ops) {
   insn_tgei_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_s16expr);
}

static void call_267(int line, struct operandarray *ops) {
   insn_tgeu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_268(int line, struct operandarray *ops) {
   insn_tgeu_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_269(int line, struct operandarray *ops) {
   insn_tgeu_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number);
}

static void call_270(int line, struct operandarray *ops) {
   insn_tgeiu_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_s16expr);
}

static void call_271(int line, struct operandarray *ops) {
   (void)ops;
   insn_tlbp_(line);
}

static void call_272(int line, struct operandarray *ops) {
   (void)ops;
   insn_tlbr_(line);
}

static void call_273(int line, struct operandarray *ops) {
   (void)ops;
   insn_tlbwi_(line);
}

static void call_274(int line, struct operandarray *ops) {
   (void)ops;
   insn_tlbwr_(line);
}

static void call_275(int line, struct operandarray *ops) {
   insn_tlt_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_276(int line, struct operandarray *ops) {
   insn_tlt_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_277(int line, struct operandarray *ops) {
   insn_tlt_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number);
}

static void call_278(int line, struct operandarray *ops) {
   insn_tlti_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_s16expr);
}

static void call_279(int line, struct operandarray *ops) {
   insn_tltu_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_280(int line, struct operandarray *ops) {
   insn_tltu_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_281(int line, struct operandarray *ops) {
   insn_tltu_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number);
}

static void call_282(int line, struct operandarray *ops) {
   insn_tltiu_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_s16expr);
}

static void call_283(int line, struct operandarray *ops) {
   insn_tne_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_284(int line, struct operandarray *ops) {
   insn_tne_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_285(int line, struct operandarray *ops) {
   insn_tne_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number);
}

static void call_286(int line, struct operandarray *ops) {
   insn_tnei_reg_s16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_s16expr);
}

static void call_287(int line, struct operandarray *ops) {
   insn_ulw_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_288(int line, struct operandarray *ops) {
   insn_ulw_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_289(int line, struct operandarray *ops) {
   insn_usw_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_290(int line, struct operandarray *ops) {
   insn_usw_reg_mem(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_mem);
}

static void call_291(int line, struct operandarray *ops) {
   (void)ops;
   insn_wait_(line);
}

static void call_292(int line, struct operandarray *ops) {
   insn_wait_number(line, operandarray_get(ops, 0)->val_number);
}

static void call_293(int line, struct operandarray *ops) {
   insn_xor_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_294(int line, struct operandarray *ops) {
   insn_xor_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_295(int line, struct operandarray *ops) {
   insn_xor_reg_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_number);
}

static void call_296(int line, struct operandarray *ops) {
   insn_xori_reg_reg_u16expr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_u16expr);
}

static void call_297(int line, struct operandarray *ops) {
   insn_la_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_298(int line, struct operandarray *ops) {
   insn_li_reg_number(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number);
}

static void call_299(int line, struct operandarray *ops) {
   insn_abs_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_300(int line, struct operandarray *ops) {
   insn_abs_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_301(int line, struct operandarray *ops) {
   insn_add_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_302(int line, struct operandarray *ops) {
   insn_add_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_303(int line, struct operandarray *ops) {
   insn_add_s_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_304(int line, struct operandarray *ops) {
   insn_add_d_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_305(int line, struct operandarray *ops) {
   insn_ceil_w_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_306(int line, struct operandarray *ops) {
   insn_ceil_w_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_307(int line, struct operandarray *ops) {
   insn_cvt_d_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_308(int line, struct operandarray *ops) {
   insn_cvt_d_w_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_309(int line, struct operandarray *ops) {
   insn_cvt_d_l_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_310(int line, struct operandarray *ops) {
   insn_cvt_s_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_311(int line, struct operandarray *ops) {
   insn_cvt_s_w_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_312(int line, struct operandarray *ops) {
   insn_cvt_s_l_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_313(int line, struct operandarray *ops) {
   insn_cvt_w_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_314(int line, struct operandarray *ops) {
   insn_cvt_w_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_315(int line, struct operandarray *ops) {
   insn_div_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_316(int line, struct operandarray *ops) {
   insn_div_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_317(int line, struct operandarray *ops) {
   insn_div_s_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_318(int line, struct operandarray *ops) {
   insn_div_d_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_319(int line, struct operandarray *ops) {
   insn_floor_w_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_320(int line, struct operandarray *ops) {
   insn_floor_w_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_321(int line, struct operandarray *ops) {
   insn_mov_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_322(int line, struct operandarray *ops) {
   insn_mov_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_323(int line, struct operandarray *ops) {
   insn_movf_reg_reg_cc(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_cc);
}

static void call_324(int line, struct operandarray *ops) {
   insn_movf_s_freg_freg_cc(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_cc);
}

static void call_325(int line, struct operandarray *ops) {
   insn_movf_d_freg_freg_cc(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_cc);
}

static void call_326(int line, struct operandarray *ops) {
   insn_movt_reg_reg_cc(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_cc);
}

static void call_327(int line, struct operandarray *ops) {
   insn_movt_s_freg_freg_cc(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_cc);
}

static void call_328(int line, struct operandarray *ops) {
   insn_movt_d_freg_freg_cc(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_cc);
}

static void call_329(int line, struct operandarray *ops) {
   insn_movn_s_freg_freg_reg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_reg);
}

static void call_330(int line, struct operandarray *ops) {
   insn_movn_d_freg_freg_reg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_reg);
}

static void call_331(int line, struct operandarray *ops) {
   insn_movz_s_freg_freg_reg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_reg);
}

static void call_332(int line, struct operandarray *ops) {
   insn_movz_d_freg_freg_reg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_reg);
}

static void call_333(int line, struct operandarray *ops) {
   insn_mul_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_334(int line, struct operandarray *ops) {
   insn_mul_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_335(int line, struct operandarray *ops) {
   insn_mul_s_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_336(int line, struct operandarray *ops) {
   insn_mul_d_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_337(int line, struct operandarray *ops) {
   insn_neg_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_338(int line, struct operandarray *ops) {
   insn_neg_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_339(int line, struct operandarray *ops) {
   insn_round_w_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_340(int line, struct operandarray *ops) {
   insn_round_w_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_341(int line, struct operandarray *ops) {
   insn_sqrt_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_342(int line, struct operandarray *ops) {
   insn_sqrt_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_343(int line, struct operandarray *ops) {
   insn_sub_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_344(int line, struct operandarray *ops) {
   insn_sub_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_345(int line, struct operandarray *ops) {
   insn_sub_s_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_346(int line, struct operandarray *ops) {
   insn_sub_d_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_347(int line, struct operandarray *ops) {
   insn_trunc_w_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_348(int line, struct operandarray *ops) {
   insn_trunc_w_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_349(int line, struct operandarray *ops) {
   insn_c_f_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_350(int line, struct operandarray *ops) {
   insn_c_un_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_351(int line, struct operandarray *ops) {
   insn_c_eq_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_352(int line, struct operandarray *ops) {
   insn_c_ueq_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_353(int line, struct operandarray *ops) {
   insn_c_olt_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_354(int line, struct operandarray *ops) {
   insn_c_ult_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_355(int line, struct operandarray *ops) {
   insn_c_ole_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_356(int line, struct operandarray *ops) {
   insn_c_ule_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_357(int line, struct operandarray *ops) {
   insn_c_sf_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_358(int line, struct operandarray *ops) {
   insn_c_ngle_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_359(int line, struct operandarray *ops) {
   insn_c_seq_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_360(int line, struct operandarray *ops) {
   insn_c_ngl_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_361(int line, struct operandarray *ops) {
   insn_c_lt_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_362(int line, struct operandarray *ops) {
   insn_c_nge_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_363(int line, struct operandarray *ops) {
   insn_c_le_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_364(int line, struct operandarray *ops) {
   insn_c_ngt_s_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_365(int line, struct operandarray *ops) {
   insn_c_f_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_366(int line, struct operandarray *ops) {
   insn_c_un_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_367(int line, struct operandarray *ops) {
   insn_c_eq_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_368(int line, struct operandarray *ops) {
   insn_c_ueq_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_369(int line, struct operandarray *ops) {
   insn_c_olt_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_370(int line, struct operandarray *ops) {
   insn_c_ult_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_371(int line, struct operandarray *ops) {
   insn_c_ole_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_372(int line, struct operandarray *ops) {
   insn_c_ule_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_373(int line, struct operandarray *ops) {
   insn_c_sf_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_374(int line, struct operandarray *ops) {
   insn_c_ngle_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_375(int line, struct operandarray *ops) {
   insn_c_seq_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_376(int line, struct operandarray *ops) {
   insn_c_ngl_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_377(int line, struct operandarray *ops) {
   insn_c_lt_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_378(int line, struct operandarray *ops) {
   insn_c_nge_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_379(int line, struct operandarray *ops) {
   insn_c_le_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_380(int line, struct operandarray *ops) {
   insn_c_ngt_d_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_381(int line, struct operandarray *ops) {
   insn_c_f_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_382(int line, struct operandarray *ops) {
   insn_c_un_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_383(int line, struct operandarray *ops) {
   insn_c_eq_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_384(int line, struct operandarray *ops) {
   insn_c_ueq_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_385(int line, struct operandarray *ops) {
   insn_c_olt_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_386(int line, struct operandarray *ops) {
   insn_c_ult_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_387(int line, struct operandarray *ops) {
   insn_c_ole_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_388(int line, struct operandarray *ops) {
   insn_c_ule_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_389(int line, struct operandarray *ops) {
   insn_c_sf_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_390(int line, struct operandarray *ops) {
   insn_c_ngle_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_391(int line, struct operandarray *ops) {
   insn_c_seq_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_392(int line, struct operandarray *ops) {
   insn_c_ngl_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_393(int line, struct operandarray *ops) {
   insn_c_lt_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_394(int line, struct operandarray *ops) {
   insn_c_nge_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_395(int line, struct operandarray *ops) {
   insn_c_le_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_396(int line, struct operandarray *ops) {
   insn_c_ngt_s_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_397(int line, struct operandarray *ops) {
   insn_c_f_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_398(int line, struct operandarray *ops) {
   insn_c_un_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_399(int line, struct operandarray *ops) {
   insn_c_eq_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_400(int line, struct operandarray *ops) {
   insn_c_ueq_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_401(int line, struct operandarray *ops) {
   insn_c_olt_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_402(int line, struct operandarray *ops) {
   insn_c_ult_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_403(int line, struct operandarray *ops) {
   insn_c_ole_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_404(int line, struct operandarray *ops) {
   insn_c_ule_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_405(int line, struct operandarray *ops) {
   insn_c_sf_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_406(int line, struct operandarray *ops) {
   insn_c_ngle_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_407(int line, struct operandarray *ops) {
   insn_c_seq_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_408(int line, struct operandarray *ops) {
   insn_c_ngl_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_409(int line, struct operandarray *ops) {
   insn_c_lt_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_410(int line, struct operandarray *ops) {
   insn_c_nge_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_411(int line, struct operandarray *ops) {
   insn_c_le_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_412(int line, struct operandarray *ops) {
   insn_c_ngt_d_cc_freg_freg(line, operandarray_get(ops, 0)->val_cc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_413(int line, struct operandarray *ops) {
   directive_register_r_rtag(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_rtag);
}

static void call_414(int line, struct operandarray *ops) {
   directive_set_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_415(int line, struct operandarray *ops) {
   directive_unset_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_416(int line, struct operandarray *ops) {
   directive_set_s_x(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_expr);
}

static void call_417(int line, struct operandarray *ops) {
   directive_file_q(line, operandarray_get(ops, 0)->val_qstring);
}

static void call_418(int line, struct operandarray *ops) {
   directive_file_x(line, operandarray_get(ops, 0)->val_expr);
}

static void call_419(int line, struct operandarray *ops) {
   directive_ident_q(line, operandarray_get(ops, 0)->val_qstring);
}

static void call_420(int line, struct operandarray *ops) {
   directive_gnu_attribute_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_421(int line, struct operandarray *ops) {
   (void)ops;
   directive_text_(line);
}

static void call_422(int line, struct operandarray *ops) {
   (void)ops;
   directive_rdata_(line);
}

static void call_423(int line, struct operandarray *ops) {
   (void)ops;
   directive_data_(line);
}

static void call_424(int line, struct operandarray *ops) {
   (void)ops;
   directive_bss_(line);
}

static void call_425(int line, struct operandarray *ops) {
   directive_section_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_426(int line, struct operandarray *ops) {
   directive_section_s_q(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring);
}

static void call_427(int line, struct operandarray *ops) {
   directive_section_s_q_q(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_qstring);
}

static void call_428(int line, struct operandarray *ops) {
   directive_section_s_q_q_x(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_qstring, operandarray_get(ops, 3)->val_expr);
}

static void call_429(int line, struct operandarray *ops) {
   directive_section_s_q_q_x_x(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_qstring, operandarray_get(ops, 3)->val_expr, operandarray_get(ops, 4)->val_expr);
}

static void call_430(int line, struct operandarray *ops) {
   directive_section_s_q_secty(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_sectiontype);
}

static void call_431(int line, struct operandarray *ops) {
   directive_section_s_q_secty_x(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_sectiontype, operandarray_get(ops, 3)->val_expr);
}

static void call_432(int line, struct operandarray *ops) {
   directive_section_s_q_secty_x_x(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_sectiontype, operandarray_get(ops, 3)->val_expr, operandarray_get(ops, 4)->val_expr);
}

static void call_433(int line, struct operandarray *ops) {
   directive_section_q(line, operandarray_get(ops, 0)->val_qstring);
}

static void call_434(int line, struct operandarray *ops) {
   (void)ops;
   directive_previous_(line);
}

static void call_435(int line, struct operandarray *ops) {
   directive_align_mz(line, operandarray_get(ops, 0)->val_magiczero);
}

static void call_436(int line, struct operandarray *ops) {
   directive_align_n(line, operandarray_get(ops, 0)->val_number);
}

static void call_437(int line, struct operandarray *ops) {
   directive_space_n(line, operandarray_get(ops, 0)->val_number);
}

static void call_438(int line, struct operandarray *ops) {
   directive_lcomm_s_n(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number);
}

static void call_439(int line, struct operandarray *ops) {
   directive_lcomm_s_n_n(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_number);
}

static void call_440(int line, struct operandarray *ops) {
   directive_comm_s_n(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number);
}

static void call_441(int line, struct operandarray *ops) {
   directive_comm_s_n_n(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_number);
}

static void call_442(int line, struct operandarray *ops) {
   directive_local_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_443(int line, struct operandarray *ops) {
   directive_globl_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_444(int line, struct operandarray *ops) {
   directive_global_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_445(int line, struct operandarray *ops) {
   directive_extern_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_446(int line, struct operandarray *ops) {
   directive_type_s_symty(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_symboltype);
}

static void call_447(int line, struct operandarray *ops) {
   directive_ent_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_448(int line, struct operandarray *ops) {
   directive_end_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_449(int line, struct operandarray *ops) {
   directive_size_s_x(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_expr);
}

static void call_450(int line, struct operandarray *ops) {
   directive_frame_r_n_r(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_reg);
}

static void call_451(int line, struct operandarray *ops) {
   directive_mask_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_452(int line, struct operandarray *ops) {
   directive_fmask_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_453(int line, struct operandarray *ops) {
   directive_ascii_q(line, operandarray_get(ops, 0)->val_qstring);
}

static void call_454(int line, struct operandarray *ops) {
   directive_asciz_q(line, operandarray_get(ops, 0)->val_qstring);
}

static void call_455(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_8byte_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_456(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_word_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_457(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_4byte_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_458(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_hword_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_459(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_half_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_460(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_short_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_461(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_2byte_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_462(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_byte_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_463(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_int_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_464(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_long_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_465(int line, struct operandarray *ops) {
   (void)ops;
   directive_cfi_startproc_(line);
}

static void call_466(int line, struct operandarray *ops) {
   (void)ops;
   directive_cfi_endproc_(line);
}

static void call_467(int line, struct operandarray *ops) {
   (void)ops;
   directive_cfi_signal_frame_(line);
}

static void call_468(int line, struct operandarray *ops) {
   directive_cfi_def_cfa_r_n(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number);
}

static void call_469(int line, struct operandarray *ops) {
   directive_cfi_def_cfa_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_470(int line, struct operandarray *ops) {
   directive_cfi_offset_r_n(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number);
}

static void call_471(int line, struct operandarray *ops) {
   directive_cfi_offset_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_472(int line, struct operandarray *ops) {
   directive_cfi_return_column_r(line, operandarray_get(ops, 0)->val_reg);
}

static void call_473(int line, struct operandarray *ops) {
   (void)ops;
   directive_cfi_window_save_(line);
}

static void call_474(int line, struct operandarray *ops) {
   directive_cfi_register_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_475(int line, struct operandarray *ops) {
   directive_cfi_def_cfa_register_n(line, operandarray_get(ops, 0)->val_number);
}

static void call_476(int line, struct operandarray *ops) {
   directive_common_s_n_q(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_qstring);
}

static void call_477(int line, struct operandarray *ops) {
   directive_reserve_s_n_q(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_qstring);
}

static void call_478(int line, struct operandarray *ops) {
   directive_common_s_n_n(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_number);
}

static void call_479(int line, struct operandarray *ops) {
   directive_reserve_s_n_n(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_number);
}

static void call_480(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_nword_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_481(int line, struct operandarray *ops) {
   (void)ops;
   directive_proc_(line);
}

static void call_482(int line, struct operandarray *ops) {
   directive_proc_x(line, operandarray_get(ops, 0)->val_expr);
}

static void call_483(int line, struct operandarray *ops) {
   directive_seg_q(line, operandarray_get(ops, 0)->val_qstring);
}

static void call_484(int line, struct operandarray *ops) {
   directive_skip_n(line, operandarray_get(ops, 0)->val_number);
}

static void call_485(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_xword_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_486(int line, struct operandarray *ops) {
   directive_section_x_q_secty(line, operandarray_get(ops, 0)->val_expr, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_sectiontype);
}

static void call_487(int line, struct operandarray *ops) {
   directive_syntax_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_488(int line, struct operandarray *ops) {
   directive_arch_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_489(int line, struct operandarray *ops) {
   directive_arch_extension_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_490(int line, struct operandarray *ops) {
   directive_cpu_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_491(int line, struct operandarray *ops) {
   directive_cpu_x(line, operandarray_get(ops, 0)->val_expr);
}

static void call_492(int line, struct operandarray *ops) {
   directive_fpu_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_493(int line, struct operandarray *ops) {
   (void)ops;
   directive_arm_(line);
}

static void call_494(int line, struct operandarray *ops) {
   (void)ops;
   directive_thumb_(line);
}

static void call_495(int line, struct operandarray *ops) {
   directive_code_n(line, operandarray_get(ops, 0)->val_number);
}

static void call_496(int line, struct operandarray *ops) {
   (void)ops;
   directive_force_thumb_(line);
}

static void call_497(int line, struct operandarray *ops) {
   (void)ops;
   directive_thumb_func_(line);
}

static void call_498(int line, struct operandarray *ops) {
   (void)ops;
   directive_thumb_set_(line);
}

static void call_499(int line, struct operandarray *ops) {
   directive_eabi_attribute_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_500(int line, struct operandarray *ops) {
   directive_personality_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_501(int line, struct operandarray *ops) {
   directive_personalityindex_n(line, operandarray_get(ops, 0)->val_number);
}

static void call_502(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_inst_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_503(int line, struct operandarray *ops) {
   (void)ops;
   directive_even_(line);
}

static void call_504(int line, struct operandarray *ops) {
   (void)ops;
   directive_fnstart_(line);
}

static void call_505(int line, struct operandarray *ops) {
   (void)ops;
   directive_fnend_(line);
}

static const opmatchfn matches_c2reg_mem[2] = {
   check_c2reg,
   check_mem,
};

static const opmatchfn matches_c2reg_symbol[2] = {
   check_c2reg,
   check_symbol,
};

static const opmatchfn matches_c3reg_mem[2] = {
   check_c3reg,
   check_mem,
};

static const opmatchfn matches_c3reg_symbol[2] = {
   check_c3reg,
   check_symbol,
};

static const opmatchfn matches_cc_freg_freg[3] = {
   check_cc,
   check_freg,
   check_freg,
};

static const opmatchfn matches_cc_symbol[2] = {
   check_cc,
   check_symbol,
};

static const opmatchfn matches_freg_freg[2] = {
   check_freg,
   check_freg,
};

static const opmatchfn matches_freg_freg_cc[3] = {
   check_freg,
   check_freg,
   check_cc,
};

static const opmatchfn matches_freg_freg_freg[3] = {
   check_freg,
   check_freg,
   check_freg,
};

static const opmatchfn matches_freg_freg_reg[3] = {
   check_freg,
   check_freg,
   check_reg,
};

static const opmatchfn matches_freg_mem[2] = {
   check_freg,
   check_mem,
};

static const opmatchfn matches_freg_symbol[2] = {
   check_freg,
   check_symbol,
};

static const opmatchfn matches_mz[1] = {
   check_magiczero,
};

static const opmatchfn matches_n[1] = {
   check_number,
};

static const opmatchfn matches_n_n[2] = {
   check_number,
   check_number,
};

static const opmatchfn matches_number[1] = {
   check_number,
};

static const opmatchfn matches_number_mem[2] = {
   check_number,
   check_mem,
};

static const opmatchfn matches_number_number[2] = {
   check_number,
   check_number,
};

static const opmatchfn matches_number_symbol[2] = {
   check_number,
   check_symbol,
};

static const opmatchfn matches_q[1] = {
   check_qstring,
};

static const opmatchfn matches_r[1] = {
   check_reg,
};

static const opmatchfn matches_r_n[2] = {
   check_reg,
   check_number,
};

static const opmatchfn matches_r_n_r[3] = {
   check_reg,
   check_number,
   check_reg,
};

static const opmatchfn matches_r_rtag[2] = {
   check_reg,
   check_rtag,
};

static const opmatchfn matches_reg[1] = {
   check_reg,
};

static const opmatchfn matches_reg_c0reg[2] = {
   check_reg,
   check_c0reg,
};

static const opmatchfn matches_reg_c0reg_sel[3] = {
   check_reg,
   check_c0reg,
   check_sel,
};

static const opmatchfn matches_reg_c2reg[2] = {
   check_reg,
   check_c2reg,
};

static const opmatchfn matches_reg_c2reg_sel[3] = {
   check_reg,
   check_c2reg,
   check_sel,
};

static const opmatchfn matches_reg_c3reg[2] = {
   check_reg,
   check_c3reg,
};

static const opmatchfn matches_reg_c3reg_sel[3] = {
   check_reg,
   check_c3reg,
   check_sel,
};

static const opmatchfn matches_reg_freg[2] = {
   check_reg,
   check_freg,
};

static const opmatchfn matches_reg_mem[2] = {
   check_reg,
   check_mem,
};

static const opmatchfn matches_reg_number[2] = {
   check_reg,
   check_number,
};

static const opmatchfn matches_reg_number_symbol[3] = {
   check_reg,
   check_number,
   check_symbol,
};

static const opmatchfn matches_reg_reg[2] = {
   check_reg,
   check_reg,
};

static const opmatchfn matches_reg_reg_cc[3] = {
   check_reg,
   check_reg,
   check_cc,
};

static const opmatchfn matches_reg_reg_number[3] = {
   check_reg,
   check_reg,
   check_number,
};

static const opmatchfn matches_reg_reg_reg[3] = {
   check_reg,
   check_reg,
   check_reg,
};

static const opmatchfn matches_reg_reg_s16expr[3] = {
   check_reg,
   check_reg,
   check_s16expr,
};

static const opmatchfn matches_reg_reg_symbol[3] = {
   check_reg,
   check_reg,
   check_symbol,
};

static const opmatchfn matches_reg_reg_u16expr[3] = {
   check_reg,
   check_reg,
   check_u16expr,
};

static const opmatchfn matches_reg_s16expr[2] = {
   check_reg,
   check_s16expr,
};

static const opmatchfn matches_reg_symbol[2] = {
   check_reg,
   check_symbol,
};

static const opmatchfn matches_reg_u16expr[2] = {
   check_reg,
   check_u16expr,
};

static const opmatchfn matches_s[1] = {
   check_symbol,
};

static const opmatchfn matches_s_n[2] = {
   check_symbol,
   check_number,
};

static const opmatchfn matches_s_n_n[3] = {
   check_symbol,
   check_number,
   check_number,
};

static const opmatchfn matches_s_n_q[3] = {
   check_symbol,
   check_number,
   check_qstring,
};

static const opmatchfn matches_s_q[2] = {
   check_symbol,
   check_qstring,
};

static const opmatchfn matches_s_q_q[3] = {
   check_symbol,
   check_qstring,
   check_qstring,
};

static const opmatchfn matches_s_q_q_x[4] = {
   check_symbol,
   check_qstring,
   check_qstring,
   check_expr,
};

static const opmatchfn matches_s_q_q_x_x[5] = {
   check_symbol,
   check_qstring,
   check_qstring,
   check_expr,
   check_expr,
};

static const opmatchfn matches_s_q_secty[3] = {
   check_symbol,
   check_qstring,
   check_sectiontype,
};

static const opmatchfn matches_s_q_secty_x[4] = {
   check_symbol,
   check_qstring,
   check_sectiontype,
   check_expr,
};

static const opmatchfn matches_s_q_secty_x_x[5] = {
   check_symbol,
   check_qstring,
   check_sectiontype,
   check_expr,
   check_expr,
};

static const opmatchfn matches_s_symty[2] = {
   check_symbol,
   check_symboltype,
};

static const opmatchfn matches_s_x[2] = {
   check_symbol,
   check_expr,
};

static const opmatchfn matches_symbol[1] = {
   check_symbol,
};

static const opmatchfn matches_x[1] = {
   check_expr,
};

static const opmatchfn matches_x_q_secty[3] = {
   check_expr,
   check_qstring,
   check_sectiontype,
};

/* .2byte */
static const struct insnsig sigtbl0[1] = {
   { matches_x,      1, 1, call_461 } /* line 566 */,
};

/* .4byte */
static const struct insnsig sigtbl1[1] = {
   { matches_x,      1, 1, call_457 } /* line 562 */,
};

/* .8byte */
static const struct insnsig sigtbl2[1] = {
   { matches_x,      1, 1, call_455 } /* line 560 */,
};

/* .align */
static const struct insnsig sigtbl3[2] = {
   { matches_mz,     1, 0, call_435 } /* line 535 */,
   { matches_n,      1, 0, call_436 } /* line 537 */,
};

/* .arch */
static const struct insnsig sigtbl4[1] = {
   { matches_s,      1, 0, call_488 } /* line 604 */,
};

/* .arch_extension */
static const struct insnsig sigtbl5[1] = {
   { matches_s,      1, 0, call_489 } /* line 605 */,
};

/* .arm */
static const struct insnsig sigtbl6[1] = {
   { NULL,           0, 0, call_493 } /* line 609 */,
};

/* .ascii */
static const struct insnsig sigtbl7[1] = {
   { matches_q,      1, 0, call_453 } /* line 558 */,
};

/* .asciz */
static const struct insnsig sigtbl8[1] = {
   { matches_q,      1, 0, call_454 } /* line 559 */,
};

/* .bss */
static const struct insnsig sigtbl9[1] = {
   { NULL,           0, 0, call_424 } /* line 520 */,
};

/* .byte */
static const struct insnsig sigtbl10[1] = {
   { matches_x,      1, 1, call_462 } /* line 567 */,
};

/* .cfi_def_cfa */
static const struct insnsig sigtbl11[2] = {
   { matches_r_n,    2, 0, call_468 } /* line 575 */,
   { matches_n_n,    2, 0, call_469 } /* line 576 */,
};

/* .cfi_def_cfa_register */
static const struct insnsig sigtbl12[1] = {
   { matches_n,      1, 0, call_475 } /* line 582 */,
};

/* .cfi_endproc */
static const struct insnsig sigtbl13[1] = {
   { NULL,           0, 0, call_466 } /* line 573 */,
};

/* .cfi_offset */
static const struct insnsig sigtbl14[2] = {
   { matches_r_n,    2, 0, call_470 } /* line 577 */,
   { matches_n_n,    2, 0, call_471 } /* line 578 */,
};

/* .cfi_register */
static const struct insnsig sigtbl15[1] = {
   { matches_n_n,    2, 0, call_474 } /* line 581 */,
};

/* .cfi_return_column */
static const struct insnsig sigtbl16[1] = {
   { matches_r,      1, 0, call_472 } /* line 579 */,
};

/* .cfi_signal_frame */
static const struct insnsig sigtbl17[1] = {
   { NULL,           0, 0, call_467 } /* line 574 */,
};

/* .cfi_startproc */
static const struct insnsig sigtbl18[1] = {
   { NULL,           0, 0, call_465 } /* line 572 */,
};

/* .cfi_window_save */
static const struct insnsig sigtbl19[1] = {
   { NULL,           0, 0, call_473 } /* line 580 */,
};

/* .code */
static const struct insnsig sigtbl20[1] = {
   { matches_n,      1, 0, call_495 } /* line 611 */,
};

/* .comm */
static const struct insnsig sigtbl21[2] = {
   { matches_s_n,    2, 0, call_440 } /* line 542 */,
   { matches_s_n_n,  3, 0, call_441 } /* line 543 */,
};

/* .common */
static const struct insnsig sigtbl22[2] = {
   { matches_s_n_q,  3, 0, call_476 } /* line 587 */,
   { matches_s_n_n,  3, 0, call_478 } /* line 590 */,
};

/* .cpu */
static const struct insnsig sigtbl23[2] = {
   { matches_s,      1, 0, call_490 } /* line 606 */,
   { matches_x,      1, 0, call_491 } /* line 607 */,
};

/* .data */
static const struct insnsig sigtbl24[1] = {
   { NULL,           0, 0, call_423 } /* line 519 */,
};

/* .eabi_attribute */
static const struct insnsig sigtbl25[1] = {
   { matches_n_n,    2, 0, call_499 } /* line 615 */,
};

/* .end */
static const struct insnsig sigtbl26[1] = {
   { matches_s,      1, 0, call_448 } /* line 551 */,
};

/* .ent */
static const struct insnsig sigtbl27[1] = {
   { matches_s,      1, 0, call_447 } /* line 550 */,
};

/* .even */
static const struct insnsig sigtbl28[1] = {
   { NULL,           0, 0, call_503 } /* line 622 */,
};

/* .extern */
static const struct insnsig sigtbl29[1] = {
   { matches_s,      1, 0, call_445 } /* line 548 */,
};

/* .file */
static const struct insnsig sigtbl30[2] = {
   { matches_q,      1, 0, call_417 } /* line 512 */,
   { matches_x,      1, 0, call_418 } /* line 513 */,
};

/* .fmask */
static const struct insnsig sigtbl31[1] = {
   { matches_n_n,    2, 0, call_452 } /* line 556 */,
};

/* .fnend */
static const struct insnsig sigtbl32[1] = {
   { NULL,           0, 0, call_505 } /* line 624 */,
};

/* .fnstart */
static const struct insnsig sigtbl33[1] = {
   { NULL,           0, 0, call_504 } /* line 623 */,
};

/* .force_thumb */
static const struct insnsig sigtbl34[1] = {
   { NULL,           0, 0, call_496 } /* line 612 */,
};

/* .fpu */
static const struct insnsig sigtbl35[1] = {
   { matches_s,      1, 0, call_492 } /* line 608 */,
};

/* .frame */
static const struct insnsig sigtbl36[1] = {
   { matches_r_n_r,  3, 0, call_450 } /* line 554 */,
};

/* .global */
static const struct insnsig sigtbl37[1] = {
   { matches_s,      1, 0, call_444 } /* line 547 */,
};

/* .globl */
static const struct insnsig sigtbl38[1] = {
   { matches_s,      1, 0, call_443 } /* line 546 */,
};

/* .gnu_attribute */
static const struct insnsig sigtbl39[1] = {
   { matches_n_n,    2, 0, call_420 } /* line 515 */,
};

/* .half */
static const struct insnsig sigtbl40[1] = {
   { matches_x,      1, 1, call_459 } /* line 564 */,
};

/* .hword */
static const struct insnsig sigtbl41[1] = {
   { matches_x,      1, 1, call_458 } /* line 563 */,
};

/* .ident */
static const struct insnsig sigtbl42[1] = {
   { matches_q,      1, 0, call_419 } /* line 514 */,
};

/* .inst */
static const struct insnsig sigtbl43[1] = {
   { matches_x,      1, 1, call_502 } /* line 621 */,
};

/* .int */
static const struct insnsig sigtbl44[1] = {
   { matches_x,      1, 1, call_463 } /* line 569 */,
};

/* .lcomm */
static const struct insnsig sigtbl45[2] = {
   { matches_s_n,    2, 0, call_438 } /* line 540 */,
   { matches_s_n_n,  3, 0, call_439 } /* line 541 */,
};

/* .local */
static const struct insnsig sigtbl46[1] = {
   { matches_s,      1, 0, call_442 } /* line 545 */,
};

/* .long */
static const struct insnsig sigtbl47[1] = {
   { matches_x,      1, 1, call_464 } /* line 570 */,
};

/* .mask */
static const struct insnsig sigtbl48[1] = {
   { matches_n_n,    2, 0, call_451 } /* line 555 */,
};

/* .nword */
static const struct insnsig sigtbl49[1] = {
   { matches_x,      1, 1, call_480 } /* line 592 */,
};

/* .personality */
static const struct insnsig sigtbl50[1] = {
   { matches_s,      1, 0, call_500 } /* line 616 */,
};

/* .personalityindex */
static const struct insnsig sigtbl51[1] = {
   { matches_n,      1, 0, call_501 } /* line 617 */,
};

/* .previous */
static const struct insnsig sigtbl52[1] = {
   { NULL,           0, 0, call_434 } /* line 530 */,
};

/* .proc */
static const struct insnsig sigtbl53[2] = {
   { NULL,           0, 0, call_481 } /* line 593 */,
   { matches_x,      1, 0, call_482 } /* line 594 */,
};

/* .rdata */
static const struct insnsig sigtbl54[1] = {
   { NULL,           0, 0, call_422 } /* line 518 */,
};

/* .register */
static const struct insnsig sigtbl55[1] = {
   { matches_r_rtag,  2, 0, call_413 } /* line 464 */,
};

/* .reserve */
static const struct insnsig sigtbl56[2] = {
   { matches_s_n_q,  3, 0, call_477 } /* line 588 */,
   { matches_s_n_n,  3, 0, call_479 } /* line 591 */,
};

/* .section */
static const struct insnsig sigtbl57[10] = {
   { matches_s,      1, 0, call_425 } /* line 521 */,
   { matches_s_q,    2, 0, call_426 } /* line 522 */,
   { matches_s_q_q,  3, 0, call_427 } /* line 523 */,
   { matches_s_q_q_x,  4, 0, call_428 } /* line 524 */,
   { matches_s_q_q_x_x,  5, 0, call_429 } /* line 525 */,
   { matches_s_q_secty,  3, 0, call_430 } /* line 526 */,
   { matches_s_q_secty_x,  4, 0, call_431 } /* line 527 */,
   { matches_s_q_secty_x_x,  5, 0, call_432 } /* line 528 */,
   { matches_q,      1, 0, call_433 } /* line 529 */,
   { matches_x_q_secty,  3, 0, call_486 } /* line 599 */,
};

/* .seg */
static const struct insnsig sigtbl58[1] = {
   { matches_q,      1, 0, call_483 } /* line 595 */,
};

/* .set */
static const struct insnsig sigtbl59[2] = {
   { matches_s,      1, 0, call_414 } /* line 506 */,
   { matches_s_x,    2, 0, call_416 } /* line 510 */,
};

/* .short */
static const struct insnsig sigtbl60[1] = {
   { matches_x,      1, 1, call_460 } /* line 565 */,
};

/* .size */
static const struct insnsig sigtbl61[1] = {
   { matches_s_x,    2, 0, call_449 } /* line 552 */,
};

/* .skip */
static const struct insnsig sigtbl62[1] = {
   { matches_n,      1, 0, call_484 } /* line 596 */,
};

/* .space */
static const struct insnsig sigtbl63[1] = {
   { matches_n,      1, 0, call_437 } /* line 538 */,
};

/* .syntax */
static const struct insnsig sigtbl64[1] = {
   { matches_s,      1, 0, call_487 } /* line 603 */,
};

/* .text */
static const struct insnsig sigtbl65[1] = {
   { NULL,           0, 0, call_421 } /* line 517 */,
};

/* .thumb */
static const struct insnsig sigtbl66[1] = {
   { NULL,           0, 0, call_494 } /* line 610 */,
};

/* .thumb_func */
static const struct insnsig sigtbl67[1] = {
   { NULL,           0, 0, call_497 } /* line 613 */,
};

/* .thumb_set */
static const struct insnsig sigtbl68[1] = {
   { NULL,           0, 0, call_498 } /* line 614 */,
};

/* .type */
static const struct insnsig sigtbl69[1] = {
   { matches_s_symty,  2, 0, call_446 } /* line 549 */,
};

/* .unset */
static const struct insnsig sigtbl70[1] = {
   { matches_s,      1, 0, call_415 } /* line 507 */,
};

/* .word */
static const struct insnsig sigtbl71[1] = {
   { matches_x,      1, 1, call_456 } /* line 561 */,
};

/* .xword */
static const struct insnsig sigtbl72[1] = {
   { matches_x,      1, 1, call_485 } /* line 597 */,
};

/* abs */
static const struct insnsig sigtbl73[2] = {
   { matches_reg,    1, 0, call_0 } /* line  42 */,
   { matches_reg_reg,  2, 0, call_1 } /* line  43 */,
};

/* abs.d */
static const struct insnsig sigtbl74[1] = {
   { matches_freg_freg,  2, 0, call_300 } /* line 344 */,
};

/* abs.s */
static const struct insnsig sigtbl75[1] = {
   { matches_freg_freg,  2, 0, call_299 } /* line 343 */,
};

/* add */
static const struct insnsig sigtbl76[3] = {
   { matches_reg_reg,  2, 0, call_2 } /* line  44 */,
   { matches_reg_reg_reg,  3, 0, call_3 } /* line  45 */,
   { matches_reg_reg_number,  3, 0, call_4 } /* line  46 */,
};

/* add.d */
static const struct insnsig sigtbl77[2] = {
   { matches_freg_freg,  2, 0, call_302 } /* line 346 */,
   { matches_freg_freg_freg,  3, 0, call_304 } /* line 348 */,
};

/* add.s */
static const struct insnsig sigtbl78[2] = {
   { matches_freg_freg,  2, 0, call_301 } /* line 345 */,
   { matches_freg_freg_freg,  3, 0, call_303 } /* line 347 */,
};

/* addi */
static const struct insnsig sigtbl79[1] = {
   { matches_reg_reg_s16expr,  3, 0, call_5 } /* line  47 */,
};

/* addiu */
static const struct insnsig sigtbl80[1] = {
   { matches_reg_reg_s16expr,  3, 0, call_9 } /* line  51 */,
};

/* addu */
static const struct insnsig sigtbl81[3] = {
   { matches_reg_reg,  2, 0, call_6 } /* line  48 */,
   { matches_reg_reg_reg,  3, 0, call_7 } /* line  49 */,
   { matches_reg_reg_number,  3, 0, call_8 } /* line  50 */,
};

/* and */
static const struct insnsig sigtbl82[3] = {
   { matches_reg_reg,  2, 0, call_10 } /* line  52 */,
   { matches_reg_reg_reg,  3, 0, call_11 } /* line  53 */,
   { matches_reg_reg_number,  3, 0, call_12 } /* line  54 */,
};

/* andi */
static const struct insnsig sigtbl83[1] = {
   { matches_reg_reg_u16expr,  3, 0, call_13 } /* line  55 */,
};

/* b */
static const struct insnsig sigtbl84[1] = {
   { matches_symbol,  1, 0, call_14 } /* line  56 */,
};

/* bal */
static const struct insnsig sigtbl85[1] = {
   { matches_symbol,  1, 0, call_15 } /* line  57 */,
};

/* bc1f */
static const struct insnsig sigtbl86[2] = {
   { matches_symbol,  1, 0, call_16 } /* line  58 */,
   { matches_cc_symbol,  2, 0, call_17 } /* line  59 */,
};

/* bc1fl */
static const struct insnsig sigtbl87[2] = {
   { matches_symbol,  1, 0, call_18 } /* line  60 */,
   { matches_cc_symbol,  2, 0, call_19 } /* line  61 */,
};

/* bc1t */
static const struct insnsig sigtbl88[2] = {
   { matches_symbol,  1, 0, call_20 } /* line  62 */,
   { matches_cc_symbol,  2, 0, call_21 } /* line  63 */,
};

/* bc1tl */
static const struct insnsig sigtbl89[2] = {
   { matches_symbol,  1, 0, call_22 } /* line  64 */,
   { matches_cc_symbol,  2, 0, call_23 } /* line  65 */,
};

/* bc2f */
static const struct insnsig sigtbl90[2] = {
   { matches_symbol,  1, 0, call_24 } /* line  66 */,
   { matches_cc_symbol,  2, 0, call_25 } /* line  67 */,
};

/* bc2fl */
static const struct insnsig sigtbl91[2] = {
   { matches_symbol,  1, 0, call_26 } /* line  68 */,
   { matches_cc_symbol,  2, 0, call_27 } /* line  69 */,
};

/* bc2t */
static const struct insnsig sigtbl92[2] = {
   { matches_symbol,  1, 0, call_28 } /* line  70 */,
   { matches_cc_symbol,  2, 0, call_29 } /* line  71 */,
};

/* bc2tl */
static const struct insnsig sigtbl93[2] = {
   { matches_symbol,  1, 0, call_30 } /* line  72 */,
   { matches_cc_symbol,  2, 0, call_31 } /* line  73 */,
};

/* bc3f */
static const struct insnsig sigtbl94[2] = {
   { matches_symbol,  1, 0, call_32 } /* line  74 */,
   { matches_cc_symbol,  2, 0, call_33 } /* line  75 */,
};

/* bc3fl */
static const struct insnsig sigtbl95[2] = {
   { matches_symbol,  1, 0, call_34 } /* line  76 */,
   { matches_cc_symbol,  2, 0, call_35 } /* line  77 */,
};

/* bc3t */
static const struct insnsig sigtbl96[2] = {
   { matches_symbol,  1, 0, call_36 } /* line  78 */,
   { matches_cc_symbol,  2, 0, call_37 } /* line  79 */,
};

/* bc3tl */
static const struct insnsig sigtbl97[2] = {
   { matches_symbol,  1, 0, call_38 } /* line  80 */,
   { matches_cc_symbol,  2, 0, call_39 } /* line  81 */,
};

/* beq */
static const struct insnsig sigtbl98[2] = {
   { matches_reg_reg_symbol,  3, 0, call_40 } /* line  82 */,
   { matches_reg_number_symbol,  3, 0, call_41 } /* line  83 */,
};

/* beql */
static const struct insnsig sigtbl99[2] = {
   { matches_reg_reg_symbol,  3, 0, call_42 } /* line  84 */,
   { matches_reg_number_symbol,  3, 0, call_43 } /* line  85 */,
};

/* beqz */
static const struct insnsig sigtbl100[1] = {
   { matches_reg_symbol,  2, 0, call_44 } /* line  86 */,
};

/* beqzl */
static const struct insnsig sigtbl101[1] = {
   { matches_reg_symbol,  2, 0, call_45 } /* line  87 */,
};

/* bgez */
static const struct insnsig sigtbl102[1] = {
   { matches_reg_symbol,  2, 0, call_46 } /* line  88 */,
};

/* bgezal */
static const struct insnsig sigtbl103[1] = {
   { matches_reg_symbol,  2, 0, call_48 } /* line  90 */,
};

/* bgezall */
static const struct insnsig sigtbl104[1] = {
   { matches_reg_symbol,  2, 0, call_49 } /* line  91 */,
};

/* bgezl */
static const struct insnsig sigtbl105[1] = {
   { matches_reg_symbol,  2, 0, call_47 } /* line  89 */,
};

/* bgtz */
static const struct insnsig sigtbl106[1] = {
   { matches_reg_symbol,  2, 0, call_50 } /* line  92 */,
};

/* bgtzl */
static const struct insnsig sigtbl107[1] = {
   { matches_reg_symbol,  2, 0, call_51 } /* line  93 */,
};

/* blez */
static const struct insnsig sigtbl108[1] = {
   { matches_reg_symbol,  2, 0, call_52 } /* line  94 */,
};

/* blezl */
static const struct insnsig sigtbl109[1] = {
   { matches_reg_symbol,  2, 0, call_53 } /* line  95 */,
};

/* bltz */
static const struct insnsig sigtbl110[1] = {
   { matches_reg_symbol,  2, 0, call_54 } /* line  96 */,
};

/* bltzal */
static const struct insnsig sigtbl111[1] = {
   { matches_reg_symbol,  2, 0, call_56 } /* line  98 */,
};

/* bltzall */
static const struct insnsig sigtbl112[1] = {
   { matches_reg_symbol,  2, 0, call_57 } /* line  99 */,
};

/* bltzl */
static const struct insnsig sigtbl113[1] = {
   { matches_reg_symbol,  2, 0, call_55 } /* line  97 */,
};

/* bne */
static const struct insnsig sigtbl114[2] = {
   { matches_reg_reg_symbol,  3, 0, call_58 } /* line 100 */,
   { matches_reg_number_symbol,  3, 0, call_59 } /* line 101 */,
};

/* bnel */
static const struct insnsig sigtbl115[2] = {
   { matches_reg_reg_symbol,  3, 0, call_60 } /* line 102 */,
   { matches_reg_number_symbol,  3, 0, call_61 } /* line 103 */,
};

/* bnez */
static const struct insnsig sigtbl116[1] = {
   { matches_reg_symbol,  2, 0, call_62 } /* line 104 */,
};

/* bnezl */
static const struct insnsig sigtbl117[1] = {
   { matches_reg_symbol,  2, 0, call_63 } /* line 105 */,
};

/* break */
static const struct insnsig sigtbl118[3] = {
   { NULL,           0, 0, call_64 } /* line 106 */,
   { matches_number,  1, 0, call_65 } /* line 107 */,
   { matches_number_number,  2, 0, call_66 } /* line 108 */,
};

/* c.eq.d */
static const struct insnsig sigtbl119[2] = {
   { matches_freg_freg,  2, 0, call_367 } /* line 413 */,
   { matches_cc_freg_freg,  3, 0, call_399 } /* line 445 */,
};

/* c.eq.s */
static const struct insnsig sigtbl120[2] = {
   { matches_freg_freg,  2, 0, call_351 } /* line 397 */,
   { matches_cc_freg_freg,  3, 0, call_383 } /* line 429 */,
};

/* c.f.d */
static const struct insnsig sigtbl121[2] = {
   { matches_freg_freg,  2, 0, call_365 } /* line 411 */,
   { matches_cc_freg_freg,  3, 0, call_397 } /* line 443 */,
};

/* c.f.s */
static const struct insnsig sigtbl122[2] = {
   { matches_freg_freg,  2, 0, call_349 } /* line 395 */,
   { matches_cc_freg_freg,  3, 0, call_381 } /* line 427 */,
};

/* c.le.d */
static const struct insnsig sigtbl123[2] = {
   { matches_freg_freg,  2, 0, call_379 } /* line 425 */,
   { matches_cc_freg_freg,  3, 0, call_411 } /* line 457 */,
};

/* c.le.s */
static const struct insnsig sigtbl124[2] = {
   { matches_freg_freg,  2, 0, call_363 } /* line 409 */,
   { matches_cc_freg_freg,  3, 0, call_395 } /* line 441 */,
};

/* c.lt.d */
static const struct insnsig sigtbl125[2] = {
   { matches_freg_freg,  2, 0, call_377 } /* line 423 */,
   { matches_cc_freg_freg,  3, 0, call_409 } /* line 455 */,
};

/* c.lt.s */
static const struct insnsig sigtbl126[2] = {
   { matches_freg_freg,  2, 0, call_361 } /* line 407 */,
   { matches_cc_freg_freg,  3, 0, call_393 } /* line 439 */,
};

/* c.nge.d */
static const struct insnsig sigtbl127[2] = {
   { matches_freg_freg,  2, 0, call_378 } /* line 424 */,
   { matches_cc_freg_freg,  3, 0, call_410 } /* line 456 */,
};

/* c.nge.s */
static const struct insnsig sigtbl128[2] = {
   { matches_freg_freg,  2, 0, call_362 } /* line 408 */,
   { matches_cc_freg_freg,  3, 0, call_394 } /* line 440 */,
};

/* c.ngl.d */
static const struct insnsig sigtbl129[2] = {
   { matches_freg_freg,  2, 0, call_376 } /* line 422 */,
   { matches_cc_freg_freg,  3, 0, call_408 } /* line 454 */,
};

/* c.ngl.s */
static const struct insnsig sigtbl130[2] = {
   { matches_freg_freg,  2, 0, call_360 } /* line 406 */,
   { matches_cc_freg_freg,  3, 0, call_392 } /* line 438 */,
};

/* c.ngle.d */
static const struct insnsig sigtbl131[2] = {
   { matches_freg_freg,  2, 0, call_374 } /* line 420 */,
   { matches_cc_freg_freg,  3, 0, call_406 } /* line 452 */,
};

/* c.ngle.s */
static const struct insnsig sigtbl132[2] = {
   { matches_freg_freg,  2, 0, call_358 } /* line 404 */,
   { matches_cc_freg_freg,  3, 0, call_390 } /* line 436 */,
};

/* c.ngt.d */
static const struct insnsig sigtbl133[2] = {
   { matches_freg_freg,  2, 0, call_380 } /* line 426 */,
   { matches_cc_freg_freg,  3, 0, call_412 } /* line 458 */,
};

/* c.ngt.s */
static const struct insnsig sigtbl134[2] = {
   { matches_freg_freg,  2, 0, call_364 } /* line 410 */,
   { matches_cc_freg_freg,  3, 0, call_396 } /* line 442 */,
};

/* c.ole.d */
static const struct insnsig sigtbl135[2] = {
   { matches_freg_freg,  2, 0, call_371 } /* line 417 */,
   { matches_cc_freg_freg,  3, 0, call_403 } /* line 449 */,
};

/* c.ole.s */
static const struct insnsig sigtbl136[2] = {
   { matches_freg_freg,  2, 0, call_355 } /* line 401 */,
   { matches_cc_freg_freg,  3, 0, call_387 } /* line 433 */,
};

/* c.olt.d */
static const struct insnsig sigtbl137[2] = {
   { matches_freg_freg,  2, 0, call_369 } /* line 415 */,
   { matches_cc_freg_freg,  3, 0, call_401 } /* line 447 */,
};

/* c.olt.s */
static const struct insnsig sigtbl138[2] = {
   { matches_freg_freg,  2, 0, call_353 } /* line 399 */,
   { matches_cc_freg_freg,  3, 0, call_385 } /* line 431 */,
};

/* c.seq.d */
static const struct insnsig sigtbl139[2] = {
   { matches_freg_freg,  2, 0, call_375 } /* line 421 */,
   { matches_cc_freg_freg,  3, 0, call_407 } /* line 453 */,
};

/* c.seq.s */
static const struct insnsig sigtbl140[2] = {
   { matches_freg_freg,  2, 0, call_359 } /* line 405 */,
   { matches_cc_freg_freg,  3, 0, call_391 } /* line 437 */,
};

/* c.sf.d */
static const struct insnsig sigtbl141[2] = {
   { matches_freg_freg,  2, 0, call_373 } /* line 419 */,
   { matches_cc_freg_freg,  3, 0, call_405 } /* line 451 */,
};

/* c.sf.s */
static const struct insnsig sigtbl142[2] = {
   { matches_freg_freg,  2, 0, call_357 } /* line 403 */,
   { matches_cc_freg_freg,  3, 0, call_389 } /* line 435 */,
};

/* c.ueq.d */
static const struct insnsig sigtbl143[2] = {
   { matches_freg_freg,  2, 0, call_368 } /* line 414 */,
   { matches_cc_freg_freg,  3, 0, call_400 } /* line 446 */,
};

/* c.ueq.s */
static const struct insnsig sigtbl144[2] = {
   { matches_freg_freg,  2, 0, call_352 } /* line 398 */,
   { matches_cc_freg_freg,  3, 0, call_384 } /* line 430 */,
};

/* c.ule.d */
static const struct insnsig sigtbl145[2] = {
   { matches_freg_freg,  2, 0, call_372 } /* line 418 */,
   { matches_cc_freg_freg,  3, 0, call_404 } /* line 450 */,
};

/* c.ule.s */
static const struct insnsig sigtbl146[2] = {
   { matches_freg_freg,  2, 0, call_356 } /* line 402 */,
   { matches_cc_freg_freg,  3, 0, call_388 } /* line 434 */,
};

/* c.ult.d */
static const struct insnsig sigtbl147[2] = {
   { matches_freg_freg,  2, 0, call_370 } /* line 416 */,
   { matches_cc_freg_freg,  3, 0, call_402 } /* line 448 */,
};

/* c.ult.s */
static const struct insnsig sigtbl148[2] = {
   { matches_freg_freg,  2, 0, call_354 } /* line 400 */,
   { matches_cc_freg_freg,  3, 0, call_386 } /* line 432 */,
};

/* c.un.d */
static const struct insnsig sigtbl149[2] = {
   { matches_freg_freg,  2, 0, call_366 } /* line 412 */,
   { matches_cc_freg_freg,  3, 0, call_398 } /* line 444 */,
};

/* c.un.s */
static const struct insnsig sigtbl150[2] = {
   { matches_freg_freg,  2, 0, call_350 } /* line 396 */,
   { matches_cc_freg_freg,  3, 0, call_382 } /* line 428 */,
};

/* cache */
static const struct insnsig sigtbl151[2] = {
   { matches_number_symbol,  2, 0, call_67 } /* line 109 */,
   { matches_number_mem,  2, 0, call_68 } /* line 110 */,
};

/* ceil.w.d */
static const struct insnsig sigtbl152[1] = {
   { matches_freg_freg,  2, 0, call_306 } /* line 350 */,
};

/* ceil.w.s */
static const struct insnsig sigtbl153[1] = {
   { matches_freg_freg,  2, 0, call_305 } /* line 349 */,
};

/* cfc1 */
static const struct insnsig sigtbl154[1] = {
   { matches_reg_freg,  2, 0, call_69 } /* line 111 */,
};

/* cfc2 */
static const struct insnsig sigtbl155[1] = {
   { matches_reg_c2reg,  2, 0, call_70 } /* line 112 */,
};

/* cfc3 */
static const struct insnsig sigtbl156[1] = {
   { matches_reg_c3reg,  2, 0, call_71 } /* line 113 */,
};

/* clo */
static const struct insnsig sigtbl157[1] = {
   { matches_reg_reg,  2, 0, call_72 } /* line 114 */,
};

/* clz */
static const struct insnsig sigtbl158[1] = {
   { matches_reg_reg,  2, 0, call_73 } /* line 115 */,
};

/* cop2 */
static const struct insnsig sigtbl159[1] = {
   { matches_number,  1, 0, call_74 } /* line 116 */,
};

/* cop3 */
static const struct insnsig sigtbl160[1] = {
   { matches_number,  1, 0, call_75 } /* line 117 */,
};

/* ctc1 */
static const struct insnsig sigtbl161[1] = {
   { matches_reg_freg,  2, 0, call_76 } /* line 118 */,
};

/* ctc2 */
static const struct insnsig sigtbl162[1] = {
   { matches_reg_c2reg,  2, 0, call_77 } /* line 119 */,
};

/* ctc3 */
static const struct insnsig sigtbl163[1] = {
   { matches_reg_c3reg,  2, 0, call_78 } /* line 120 */,
};

/* cvt.d.l */
static const struct insnsig sigtbl164[1] = {
   { matches_freg_freg,  2, 0, call_309 } /* line 353 */,
};

/* cvt.d.s */
static const struct insnsig sigtbl165[1] = {
   { matches_freg_freg,  2, 0, call_307 } /* line 351 */,
};

/* cvt.d.w */
static const struct insnsig sigtbl166[1] = {
   { matches_freg_freg,  2, 0, call_308 } /* line 352 */,
};

/* cvt.s.d */
static const struct insnsig sigtbl167[1] = {
   { matches_freg_freg,  2, 0, call_310 } /* line 354 */,
};

/* cvt.s.l */
static const struct insnsig sigtbl168[1] = {
   { matches_freg_freg,  2, 0, call_312 } /* line 356 */,
};

/* cvt.s.w */
static const struct insnsig sigtbl169[1] = {
   { matches_freg_freg,  2, 0, call_311 } /* line 355 */,
};

/* cvt.w.d */
static const struct insnsig sigtbl170[1] = {
   { matches_freg_freg,  2, 0, call_314 } /* line 358 */,
};

/* cvt.w.s */
static const struct insnsig sigtbl171[1] = {
   { matches_freg_freg,  2, 0, call_313 } /* line 357 */,
};

/* deret */
static const struct insnsig sigtbl172[1] = {
   { NULL,           0, 0, call_79 } /* line 121 */,
};

/* div */
static const struct insnsig sigtbl173[2] = {
   { matches_reg_reg,  2, 0, call_80 } /* line 122 */,
   { matches_reg_reg_reg,  3, 0, call_81 } /* line 123 */,
};

/* div.d */
static const struct insnsig sigtbl174[2] = {
   { matches_freg_freg,  2, 0, call_316 } /* line 360 */,
   { matches_freg_freg_freg,  3, 0, call_318 } /* line 362 */,
};

/* div.s */
static const struct insnsig sigtbl175[2] = {
   { matches_freg_freg,  2, 0, call_315 } /* line 359 */,
   { matches_freg_freg_freg,  3, 0, call_317 } /* line 361 */,
};

/* divu */
static const struct insnsig sigtbl176[2] = {
   { matches_reg_reg,  2, 0, call_82 } /* line 124 */,
   { matches_reg_reg_reg,  3, 0, call_83 } /* line 125 */,
};

/* eret */
static const struct insnsig sigtbl177[1] = {
   { NULL,           0, 0, call_84 } /* line 126 */,
};

/* floor.w.d */
static const struct insnsig sigtbl178[1] = {
   { matches_freg_freg,  2, 0, call_320 } /* line 364 */,
};

/* floor.w.s */
static const struct insnsig sigtbl179[1] = {
   { matches_freg_freg,  2, 0, call_319 } /* line 363 */,
};

/* j */
static const struct insnsig sigtbl180[2] = {
   { matches_symbol,  1, 0, call_85 } /* line 127 */,
   { matches_reg,    1, 0, call_86 } /* line 128 */,
};

/* jal */
static const struct insnsig sigtbl181[3] = {
   { matches_symbol,  1, 0, call_88 } /* line 130 */,
   { matches_reg,    1, 0, call_89 } /* line 131 */,
   { matches_reg_symbol,  2, 0, call_90 } /* line 132 */,
};

/* jalr */
static const struct insnsig sigtbl182[2] = {
   { matches_reg,    1, 0, call_91 } /* line 133 */,
   { matches_reg_reg,  2, 0, call_92 } /* line 134 */,
};

/* jr */
static const struct insnsig sigtbl183[1] = {
   { matches_reg,    1, 0, call_87 } /* line 129 */,
};

/* la */
static const struct insnsig sigtbl184[1] = {
   { matches_reg_symbol,  2, 0, call_297 } /* line 340 */,
};

/* lb */
static const struct insnsig sigtbl185[2] = {
   { matches_reg_symbol,  2, 0, call_93 } /* line 135 */,
   { matches_reg_mem,  2, 0, call_94 } /* line 136 */,
};

/* lbu */
static const struct insnsig sigtbl186[2] = {
   { matches_reg_symbol,  2, 0, call_95 } /* line 137 */,
   { matches_reg_mem,  2, 0, call_96 } /* line 138 */,
};

/* ldc1 */
static const struct insnsig sigtbl187[2] = {
   { matches_freg_symbol,  2, 0, call_97 } /* line 139 */,
   { matches_freg_mem,  2, 0, call_98 } /* line 140 */,
};

/* ldc2 */
static const struct insnsig sigtbl188[2] = {
   { matches_c2reg_symbol,  2, 0, call_99 } /* line 141 */,
   { matches_c2reg_mem,  2, 0, call_100 } /* line 142 */,
};

/* ldc3 */
static const struct insnsig sigtbl189[2] = {
   { matches_c3reg_symbol,  2, 0, call_101 } /* line 143 */,
   { matches_c3reg_mem,  2, 0, call_102 } /* line 144 */,
};

/* lh */
static const struct insnsig sigtbl190[2] = {
   { matches_reg_symbol,  2, 0, call_103 } /* line 145 */,
   { matches_reg_mem,  2, 0, call_104 } /* line 146 */,
};

/* lhu */
static const struct insnsig sigtbl191[2] = {
   { matches_reg_symbol,  2, 0, call_105 } /* line 147 */,
   { matches_reg_mem,  2, 0, call_106 } /* line 148 */,
};

/* li */
static const struct insnsig sigtbl192[1] = {
   { matches_reg_number,  2, 0, call_298 } /* line 341 */,
};

/* ll */
static const struct insnsig sigtbl193[2] = {
   { matches_reg_symbol,  2, 0, call_107 } /* line 149 */,
   { matches_reg_mem,  2, 0, call_108 } /* line 150 */,
};

/* lui */
static const struct insnsig sigtbl194[1] = {
   { matches_reg_u16expr,  2, 0, call_109 } /* line 151 */,
};

/* lw */
static const struct insnsig sigtbl195[2] = {
   { matches_reg_symbol,  2, 0, call_110 } /* line 152 */,
   { matches_reg_mem,  2, 0, call_111 } /* line 153 */,
};

/* lwc1 */
static const struct insnsig sigtbl196[2] = {
   { matches_freg_symbol,  2, 0, call_112 } /* line 154 */,
   { matches_freg_mem,  2, 0, call_113 } /* line 155 */,
};

/* lwc2 */
static const struct insnsig sigtbl197[2] = {
   { matches_c2reg_symbol,  2, 0, call_114 } /* line 156 */,
   { matches_c2reg_mem,  2, 0, call_115 } /* line 157 */,
};

/* lwc3 */
static const struct insnsig sigtbl198[2] = {
   { matches_c3reg_symbol,  2, 0, call_116 } /* line 158 */,
   { matches_c3reg_mem,  2, 0, call_117 } /* line 159 */,
};

/* lwl */
static const struct insnsig sigtbl199[2] = {
   { matches_reg_symbol,  2, 0, call_118 } /* line 160 */,
   { matches_reg_mem,  2, 0, call_119 } /* line 161 */,
};

/* lwr */
static const struct insnsig sigtbl200[2] = {
   { matches_reg_symbol,  2, 0, call_120 } /* line 162 */,
   { matches_reg_mem,  2, 0, call_121 } /* line 163 */,
};

/* madd */
static const struct insnsig sigtbl201[1] = {
   { matches_reg_reg,  2, 0, call_122 } /* line 164 */,
};

/* maddu */
static const struct insnsig sigtbl202[1] = {
   { matches_reg_reg,  2, 0, call_123 } /* line 165 */,
};

/* mfc0 */
static const struct insnsig sigtbl203[2] = {
   { matches_reg_c0reg,  2, 0, call_124 } /* line 166 */,
   { matches_reg_c0reg_sel,  3, 0, call_125 } /* line 167 */,
};

/* mfc1 */
static const struct insnsig sigtbl204[1] = {
   { matches_reg_freg,  2, 0, call_126 } /* line 168 */,
};

/* mfc2 */
static const struct insnsig sigtbl205[2] = {
   { matches_reg_c2reg,  2, 0, call_127 } /* line 169 */,
   { matches_reg_c2reg_sel,  3, 0, call_128 } /* line 170 */,
};

/* mfc3 */
static const struct insnsig sigtbl206[2] = {
   { matches_reg_c3reg,  2, 0, call_129 } /* line 171 */,
   { matches_reg_c3reg_sel,  3, 0, call_130 } /* line 172 */,
};

/* mfhi */
static const struct insnsig sigtbl207[1] = {
   { matches_reg,    1, 0, call_131 } /* line 173 */,
};

/* mflo */
static const struct insnsig sigtbl208[1] = {
   { matches_reg,    1, 0, call_132 } /* line 174 */,
};

/* mov.d */
static const struct insnsig sigtbl209[1] = {
   { matches_freg_freg,  2, 0, call_322 } /* line 366 */,
};

/* mov.s */
static const struct insnsig sigtbl210[1] = {
   { matches_freg_freg,  2, 0, call_321 } /* line 365 */,
};

/* move */
static const struct insnsig sigtbl211[1] = {
   { matches_reg_reg,  2, 0, call_133 } /* line 175 */,
};

/* movf */
static const struct insnsig sigtbl212[1] = {
   { matches_reg_reg_cc,  3, 0, call_323 } /* line 367 */,
};

/* movf.d */
static const struct insnsig sigtbl213[1] = {
   { matches_freg_freg_cc,  3, 0, call_325 } /* line 369 */,
};

/* movf.s */
static const struct insnsig sigtbl214[1] = {
   { matches_freg_freg_cc,  3, 0, call_324 } /* line 368 */,
};

/* movn */
static const struct insnsig sigtbl215[1] = {
   { matches_reg_reg_reg,  3, 0, call_134 } /* line 176 */,
};

/* movn.d */
static const struct insnsig sigtbl216[1] = {
   { matches_freg_freg_reg,  3, 0, call_330 } /* line 374 */,
};

/* movn.s */
static const struct insnsig sigtbl217[1] = {
   { matches_freg_freg_reg,  3, 0, call_329 } /* line 373 */,
};

/* movt */
static const struct insnsig sigtbl218[1] = {
   { matches_reg_reg_cc,  3, 0, call_326 } /* line 370 */,
};

/* movt.d */
static const struct insnsig sigtbl219[1] = {
   { matches_freg_freg_cc,  3, 0, call_328 } /* line 372 */,
};

/* movt.s */
static const struct insnsig sigtbl220[1] = {
   { matches_freg_freg_cc,  3, 0, call_327 } /* line 371 */,
};

/* movz */
static const struct insnsig sigtbl221[1] = {
   { matches_reg_reg_reg,  3, 0, call_135 } /* line 177 */,
};

/* movz.d */
static const struct insnsig sigtbl222[1] = {
   { matches_freg_freg_reg,  3, 0, call_332 } /* line 376 */,
};

/* movz.s */
static const struct insnsig sigtbl223[1] = {
   { matches_freg_freg_reg,  3, 0, call_331 } /* line 375 */,
};

/* msub */
static const struct insnsig sigtbl224[1] = {
   { matches_reg_reg,  2, 0, call_136 } /* line 178 */,
};

/* msubu */
static const struct insnsig sigtbl225[1] = {
   { matches_reg_reg,  2, 0, call_137 } /* line 179 */,
};

/* mtc0 */
static const struct insnsig sigtbl226[2] = {
   { matches_reg_c0reg,  2, 0, call_138 } /* line 180 */,
   { matches_reg_c0reg_sel,  3, 0, call_139 } /* line 181 */,
};

/* mtc1 */
static const struct insnsig sigtbl227[1] = {
   { matches_reg_freg,  2, 0, call_140 } /* line 182 */,
};

/* mtc2 */
static const struct insnsig sigtbl228[2] = {
   { matches_reg_c2reg,  2, 0, call_141 } /* line 183 */,
   { matches_reg_c2reg_sel,  3, 0, call_142 } /* line 184 */,
};

/* mtc3 */
static const struct insnsig sigtbl229[2] = {
   { matches_reg_c3reg,  2, 0, call_143 } /* line 185 */,
   { matches_reg_c3reg_sel,  3, 0, call_144 } /* line 186 */,
};

/* mthi */
static const struct insnsig sigtbl230[1] = {
   { matches_reg,    1, 0, call_145 } /* line 187 */,
};

/* mtlo */
static const struct insnsig sigtbl231[1] = {
   { matches_reg,    1, 0, call_146 } /* line 188 */,
};

/* mul */
static const struct insnsig sigtbl232[1] = {
   { matches_reg_reg_reg,  3, 0, call_147 } /* line 189 */,
};

/* mul.d */
static const struct insnsig sigtbl233[2] = {
   { matches_freg_freg,  2, 0, call_334 } /* line 378 */,
   { matches_freg_freg_freg,  3, 0, call_336 } /* line 380 */,
};

/* mul.s */
static const struct insnsig sigtbl234[2] = {
   { matches_freg_freg,  2, 0, call_333 } /* line 377 */,
   { matches_freg_freg_freg,  3, 0, call_335 } /* line 379 */,
};

/* mult */
static const struct insnsig sigtbl235[1] = {
   { matches_reg_reg,  2, 0, call_148 } /* line 190 */,
};

/* multu */
static const struct insnsig sigtbl236[1] = {
   { matches_reg_reg,  2, 0, call_149 } /* line 191 */,
};

/* neg */
static const struct insnsig sigtbl237[2] = {
   { matches_reg,    1, 0, call_150 } /* line 192 */,
   { matches_reg_reg,  2, 0, call_151 } /* line 193 */,
};

/* neg.d */
static const struct insnsig sigtbl238[1] = {
   { matches_freg_freg,  2, 0, call_338 } /* line 382 */,
};

/* neg.s */
static const struct insnsig sigtbl239[1] = {
   { matches_freg_freg,  2, 0, call_337 } /* line 381 */,
};

/* negu */
static const struct insnsig sigtbl240[2] = {
   { matches_reg,    1, 0, call_152 } /* line 194 */,
   { matches_reg_reg,  2, 0, call_153 } /* line 195 */,
};

/* nop */
static const struct insnsig sigtbl241[1] = {
   { NULL,           0, 0, call_154 } /* line 196 */,
};

/* nor */
static const struct insnsig sigtbl242[3] = {
   { matches_reg_reg,  2, 0, call_155 } /* line 197 */,
   { matches_reg_reg_reg,  3, 0, call_156 } /* line 198 */,
   { matches_reg_reg_number,  3, 0, call_157 } /* line 199 */,
};

/* nori */
static const struct insnsig sigtbl243[1] = {
   { matches_reg_reg_u16expr,  3, 0, call_158 } /* line 200 */,
};

/* not */
static const struct insnsig sigtbl244[2] = {
   { matches_reg,    1, 0, call_159 } /* line 201 */,
   { matches_reg_reg,  2, 0, call_160 } /* line 202 */,
};

/* or */
static const struct insnsig sigtbl245[3] = {
   { matches_reg_reg,  2, 0, call_161 } /* line 203 */,
   { matches_reg_reg_reg,  3, 0, call_162 } /* line 204 */,
   { matches_reg_reg_number,  3, 0, call_163 } /* line 205 */,
};

/* ori */
static const struct insnsig sigtbl246[1] = {
   { matches_reg_reg_u16expr,  3, 0, call_164 } /* line 206 */,
};

/* pref */
static const struct insnsig sigtbl247[2] = {
   { matches_number_symbol,  2, 0, call_165 } /* line 207 */,
   { matches_number_mem,  2, 0, call_166 } /* line 208 */,
};

/* rfe */
static const struct insnsig sigtbl248[1] = {
   { NULL,           0, 0, call_167 } /* line 209 */,
};

/* rol */
static const struct insnsig sigtbl249[2] = {
   { matches_reg_reg_reg,  3, 0, call_168 } /* line 210 */,
   { matches_reg_reg_number,  3, 0, call_169 } /* line 211 */,
};

/* ror */
static const struct insnsig sigtbl250[2] = {
   { matches_reg_reg_reg,  3, 0, call_170 } /* line 212 */,
   { matches_reg_reg_number,  3, 0, call_171 } /* line 213 */,
};

/* round.w.d */
static const struct insnsig sigtbl251[1] = {
   { matches_freg_freg,  2, 0, call_340 } /* line 384 */,
};

/* round.w.s */
static const struct insnsig sigtbl252[1] = {
   { matches_freg_freg,  2, 0, call_339 } /* line 383 */,
};

/* sb */
static const struct insnsig sigtbl253[2] = {
   { matches_reg_symbol,  2, 0, call_172 } /* line 214 */,
   { matches_reg_mem,  2, 0, call_173 } /* line 215 */,
};

/* sc */
static const struct insnsig sigtbl254[2] = {
   { matches_reg_symbol,  2, 0, call_174 } /* line 216 */,
   { matches_reg_mem,  2, 0, call_175 } /* line 217 */,
};

/* sdbbp */
static const struct insnsig sigtbl255[2] = {
   { NULL,           0, 0, call_176 } /* line 218 */,
   { matches_number,  1, 0, call_177 } /* line 219 */,
};

/* sdc1 */
static const struct insnsig sigtbl256[2] = {
   { matches_freg_symbol,  2, 0, call_178 } /* line 220 */,
   { matches_freg_mem,  2, 0, call_179 } /* line 221 */,
};

/* sdc2 */
static const struct insnsig sigtbl257[2] = {
   { matches_c2reg_symbol,  2, 0, call_180 } /* line 222 */,
   { matches_c2reg_mem,  2, 0, call_181 } /* line 223 */,
};

/* sdc3 */
static const struct insnsig sigtbl258[2] = {
   { matches_c3reg_symbol,  2, 0, call_182 } /* line 224 */,
   { matches_c3reg_mem,  2, 0, call_183 } /* line 225 */,
};

/* seq */
static const struct insnsig sigtbl259[3] = {
   { matches_reg_reg,  2, 0, call_184 } /* line 226 */,
   { matches_reg_reg_reg,  3, 0, call_185 } /* line 227 */,
   { matches_reg_reg_number,  3, 0, call_186 } /* line 228 */,
};

/* seqi */
static const struct insnsig sigtbl260[1] = {
   { matches_reg_reg_u16expr,  3, 0, call_187 } /* line 229 */,
};

/* sge */
static const struct insnsig sigtbl261[3] = {
   { matches_reg_reg,  2, 0, call_188 } /* line 230 */,
   { matches_reg_reg_reg,  3, 0, call_189 } /* line 231 */,
   { matches_reg_reg_number,  3, 0, call_190 } /* line 232 */,
};

/* sgei */
static const struct insnsig sigtbl262[1] = {
   { matches_reg_reg_s16expr,  3, 0, call_194 } /* line 236 */,
};

/* sgeiu */
static const struct insnsig sigtbl263[1] = {
   { matches_reg_reg_s16expr,  3, 0, call_195 } /* line 237 */,
};

/* sgeu */
static const struct insnsig sigtbl264[3] = {
   { matches_reg_reg,  2, 0, call_191 } /* line 233 */,
   { matches_reg_reg_reg,  3, 0, call_192 } /* line 234 */,
   { matches_reg_reg_number,  3, 0, call_193 } /* line 235 */,
};

/* sgt */
static const struct insnsig sigtbl265[3] = {
   { matches_reg_reg,  2, 0, call_196 } /* line 238 */,
   { matches_reg_reg_reg,  3, 0, call_197 } /* line 239 */,
   { matches_reg_reg_number,  3, 0, call_198 } /* line 240 */,
};

/* sgti */
static const struct insnsig sigtbl266[1] = {
   { matches_reg_reg_s16expr,  3, 0, call_202 } /* line 244 */,
};

/* sgtiu */
static const struct insnsig sigtbl267[1] = {
   { matches_reg_reg_s16expr,  3, 0, call_203 } /* line 245 */,
};

/* sgtu */
static const struct insnsig sigtbl268[3] = {
   { matches_reg_reg,  2, 0, call_199 } /* line 241 */,
   { matches_reg_reg_reg,  3, 0, call_200 } /* line 242 */,
   { matches_reg_reg_number,  3, 0, call_201 } /* line 243 */,
};

/* sh */
static const struct insnsig sigtbl269[2] = {
   { matches_reg_symbol,  2, 0, call_204 } /* line 246 */,
   { matches_reg_mem,  2, 0, call_205 } /* line 247 */,
};

/* sle */
static const struct insnsig sigtbl270[3] = {
   { matches_reg_reg,  2, 0, call_206 } /* line 248 */,
   { matches_reg_reg_reg,  3, 0, call_207 } /* line 249 */,
   { matches_reg_reg_number,  3, 0, call_208 } /* line 250 */,
};

/* slei */
static const struct insnsig sigtbl271[1] = {
   { matches_reg_reg_s16expr,  3, 0, call_212 } /* line 254 */,
};

/* sleiu */
static const struct insnsig sigtbl272[1] = {
   { matches_reg_reg_s16expr,  3, 0, call_213 } /* line 255 */,
};

/* sleu */
static const struct insnsig sigtbl273[3] = {
   { matches_reg_reg,  2, 0, call_209 } /* line 251 */,
   { matches_reg_reg_reg,  3, 0, call_210 } /* line 252 */,
   { matches_reg_reg_number,  3, 0, call_211 } /* line 253 */,
};

/* sll */
static const struct insnsig sigtbl274[2] = {
   { matches_reg_reg_number,  3, 0, call_214 } /* line 256 */,
   { matches_reg_reg_reg,  3, 0, call_215 } /* line 257 */,
};

/* sllv */
static const struct insnsig sigtbl275[1] = {
   { matches_reg_reg_reg,  3, 0, call_216 } /* line 258 */,
};

/* slt */
static const struct insnsig sigtbl276[3] = {
   { matches_reg_reg,  2, 0, call_217 } /* line 259 */,
   { matches_reg_reg_reg,  3, 0, call_218 } /* line 260 */,
   { matches_reg_reg_number,  3, 0, call_219 } /* line 261 */,
};

/* slti */
static const struct insnsig sigtbl277[1] = {
   { matches_reg_reg_s16expr,  3, 0, call_220 } /* line 262 */,
};

/* sltiu */
static const struct insnsig sigtbl278[1] = {
   { matches_reg_reg_s16expr,  3, 0, call_224 } /* line 266 */,
};

/* sltu */
static const struct insnsig sigtbl279[3] = {
   { matches_reg_reg,  2, 0, call_221 } /* line 263 */,
   { matches_reg_reg_reg,  3, 0, call_222 } /* line 264 */,
   { matches_reg_reg_number,  3, 0, call_223 } /* line 265 */,
};

/* sne */
static const struct insnsig sigtbl280[3] = {
   { matches_reg_reg,  2, 0, call_225 } /* line 267 */,
   { matches_reg_reg_reg,  3, 0, call_226 } /* line 268 */,
   { matches_reg_reg_number,  3, 0, call_227 } /* line 269 */,
};

/* snei */
static const struct insnsig sigtbl281[1] = {
   { matches_reg_reg_u16expr,  3, 0, call_228 } /* line 270 */,
};

/* sqrt.d */
static const struct insnsig sigtbl282[1] = {
   { matches_freg_freg,  2, 0, call_342 } /* line 386 */,
};

/* sqrt.s */
static const struct insnsig sigtbl283[1] = {
   { matches_freg_freg,  2, 0, call_341 } /* line 385 */,
};

/* sra */
static const struct insnsig sigtbl284[2] = {
   { matches_reg_reg_number,  3, 0, call_229 } /* line 271 */,
   { matches_reg_reg_reg,  3, 0, call_230 } /* line 272 */,
};

/* srav */
static const struct insnsig sigtbl285[1] = {
   { matches_reg_reg_reg,  3, 0, call_231 } /* line 273 */,
};

/* srl */
static const struct insnsig sigtbl286[2] = {
   { matches_reg_reg_number,  3, 0, call_232 } /* line 274 */,
   { matches_reg_reg_reg,  3, 0, call_233 } /* line 275 */,
};

/* srlv */
static const struct insnsig sigtbl287[1] = {
   { matches_reg_reg_reg,  3, 0, call_234 } /* line 276 */,
};

/* ssnop */
static const struct insnsig sigtbl288[1] = {
   { NULL,           0, 0, call_235 } /* line 277 */,
};

/* sub */
static const struct insnsig sigtbl289[3] = {
   { matches_reg_reg,  2, 0, call_236 } /* line 278 */,
   { matches_reg_reg_reg,  3, 0, call_237 } /* line 279 */,
   { matches_reg_reg_number,  3, 0, call_238 } /* line 280 */,
};

/* sub.d */
static const struct insnsig sigtbl290[2] = {
   { matches_freg_freg,  2, 0, call_344 } /* line 388 */,
   { matches_freg_freg_freg,  3, 0, call_346 } /* line 390 */,
};

/* sub.s */
static const struct insnsig sigtbl291[2] = {
   { matches_freg_freg,  2, 0, call_343 } /* line 387 */,
   { matches_freg_freg_freg,  3, 0, call_345 } /* line 389 */,
};

/* subi */
static const struct insnsig sigtbl292[1] = {
   { matches_reg_reg_s16expr,  3, 0, call_239 } /* line 281 */,
};

/* subiu */
static const struct insnsig sigtbl293[1] = {
   { matches_reg_reg_s16expr,  3, 0, call_243 } /* line 285 */,
};

/* subu */
static const struct insnsig sigtbl294[3] = {
   { matches_reg_reg,  2, 0, call_240 } /* line 282 */,
   { matches_reg_reg_reg,  3, 0, call_241 } /* line 283 */,
   { matches_reg_reg_number,  3, 0, call_242 } /* line 284 */,
};

/* sw */
static const struct insnsig sigtbl295[2] = {
   { matches_reg_symbol,  2, 0, call_244 } /* line 286 */,
   { matches_reg_mem,  2, 0, call_245 } /* line 287 */,
};

/* swc1 */
static const struct insnsig sigtbl296[2] = {
   { matches_freg_symbol,  2, 0, call_246 } /* line 288 */,
   { matches_freg_mem,  2, 0, call_247 } /* line 289 */,
};

/* swc2 */
static const struct insnsig sigtbl297[2] = {
   { matches_c2reg_symbol,  2, 0, call_248 } /* line 290 */,
   { matches_c2reg_mem,  2, 0, call_249 } /* line 291 */,
};

/* swc3 */
static const struct insnsig sigtbl298[2] = {
   { matches_c3reg_symbol,  2, 0, call_250 } /* line 292 */,
   { matches_c3reg_mem,  2, 0, call_251 } /* line 293 */,
};

/* swl */
static const struct insnsig sigtbl299[2] = {
   { matches_reg_symbol,  2, 0, call_252 } /* line 294 */,
   { matches_reg_mem,  2, 0, call_253 } /* line 295 */,
};

/* swr */
static const struct insnsig sigtbl300[2] = {
   { matches_reg_symbol,  2, 0, call_254 } /* line 296 */,
   { matches_reg_mem,  2, 0, call_255 } /* line 297 */,
};

/* sync */
static const struct insnsig sigtbl301[1] = {
   { NULL,           0, 0, call_256 } /* line 298 */,
};

/* syscall */
static const struct insnsig sigtbl302[2] = {
   { NULL,           0, 0, call_257 } /* line 299 */,
   { matches_number,  1, 0, call_258 } /* line 300 */,
};

/* teq */
static const struct insnsig sigtbl303[3] = {
   { matches_reg_reg,  2, 0, call_259 } /* line 301 */,
   { matches_reg_reg_number,  3, 0, call_260 } /* line 302 */,
   { matches_reg_number,  2, 0, call_261 } /* line 303 */,
};

/* teqi */
static const struct insnsig sigtbl304[1] = {
   { matches_reg_s16expr,  2, 0, call_262 } /* line 304 */,
};

/* tge */
static const struct insnsig sigtbl305[3] = {
   { matches_reg_reg,  2, 0, call_263 } /* line 305 */,
   { matches_reg_reg_number,  3, 0, call_264 } /* line 306 */,
   { matches_reg_number,  2, 0, call_265 } /* line 307 */,
};

/* tgei */
static const struct insnsig sigtbl306[1] = {
   { matches_reg_s16expr,  2, 0, call_266 } /* line 308 */,
};

/* tgeiu */
static const struct insnsig sigtbl307[1] = {
   { matches_reg_s16expr,  2, 0, call_270 } /* line 312 */,
};

/* tgeu */
static const struct insnsig sigtbl308[3] = {
   { matches_reg_reg,  2, 0, call_267 } /* line 309 */,
   { matches_reg_reg_number,  3, 0, call_268 } /* line 310 */,
   { matches_reg_number,  2, 0, call_269 } /* line 311 */,
};

/* tlbp */
static const struct insnsig sigtbl309[1] = {
   { NULL,           0, 0, call_271 } /* line 313 */,
};

/* tlbr */
static const struct insnsig sigtbl310[1] = {
   { NULL,           0, 0, call_272 } /* line 314 */,
};

/* tlbwi */
static const struct insnsig sigtbl311[1] = {
   { NULL,           0, 0, call_273 } /* line 315 */,
};

/* tlbwr */
static const struct insnsig sigtbl312[1] = {
   { NULL,           0, 0, call_274 } /* line 316 */,
};

/* tlt */
static const struct insnsig sigtbl313[3] = {
   { matches_reg_reg,  2, 0, call_275 } /* line 317 */,
   { matches_reg_reg_number,  3, 0, call_276 } /* line 318 */,
   { matches_reg_number,  2, 0, call_277 } /* line 319 */,
};

/* tlti */
static const struct insnsig sigtbl314[1] = {
   { matches_reg_s16expr,  2, 0, call_278 } /* line 320 */,
};

/* tltiu */
static const struct insnsig sigtbl315[1] = {
   { matches_reg_s16expr,  2, 0, call_282 } /* line 324 */,
};

/* tltu */
static const struct insnsig sigtbl316[3] = {
   { matches_reg_reg,  2, 0, call_279 } /* line 321 */,
   { matches_reg_reg_number,  3, 0, call_280 } /* line 322 */,
   { matches_reg_number,  2, 0, call_281 } /* line 323 */,
};

/* tne */
static const struct insnsig sigtbl317[3] = {
   { matches_reg_reg,  2, 0, call_283 } /* line 325 */,
   { matches_reg_reg_number,  3, 0, call_284 } /* line 326 */,
   { matches_reg_number,  2, 0, call_285 } /* line 327 */,
};

/* tnei */
static const struct insnsig sigtbl318[1] = {
   { matches_reg_s16expr,  2, 0, call_286 } /* line 328 */,
};

/* trunc.w.d */
static const struct insnsig sigtbl319[1] = {
   { matches_freg_freg,  2, 0, call_348 } /* line 392 */,
};

/* trunc.w.s */
static const struct insnsig sigtbl320[1] = {
   { matches_freg_freg,  2, 0, call_347 } /* line 391 */,
};

/* ulw */
static const struct insnsig sigtbl321[2] = {
   { matches_reg_symbol,  2, 0, call_287 } /* line 329 */,
   { matches_reg_mem,  2, 0, call_288 } /* line 330 */,
};

/* usw */
static const struct insnsig sigtbl322[2] = {
   { matches_reg_symbol,  2, 0, call_289 } /* line 331 */,
   { matches_reg_mem,  2, 0, call_290 } /* line 332 */,
};

/* wait */
static const struct insnsig sigtbl323[2] = {
   { NULL,           0, 0, call_291 } /* line 333 */,
   { matches_number,  1, 0, call_292 } /* line 334 */,
};

/* xor */
static const struct insnsig sigtbl324[3] = {
   { matches_reg_reg,  2, 0, call_293 } /* line 335 */,
   { matches_reg_reg_reg,  3, 0, call_294 } /* line 336 */,
   { matches_reg_reg_number,  3, 0, call_295 } /* line 337 */,
};

/* xori */
static const struct insnsig sigtbl325[1] = {
   { matches_reg_reg_u16expr,  3, 0, call_296 } /* line 338 */,
};

const struct insnmatch opcodes[] = {
   { ".2byte",        sigtbl0, 1 },
   { ".4byte",        sigtbl1, 1 },
   { ".8byte",        sigtbl2, 1 },
   { ".align",        sigtbl3, 2 },
   { ".arch",         sigtbl4, 1 },
   { ".arch_extension", sigtbl5, 1 },
   { ".arm",          sigtbl6, 1 },
   { ".ascii",        sigtbl7, 1 },
   { ".asciz",        sigtbl8, 1 },
   { ".bss",          sigtbl9, 1 },
   { ".byte",         sigtbl10, 1 },
   { ".cfi_def_cfa",  sigtbl11, 2 },
   { ".cfi_def_cfa_register", sigtbl12, 1 },
   { ".cfi_endproc",  sigtbl13, 1 },
   { ".cfi_offset",   sigtbl14, 2 },
   { ".cfi_register", sigtbl15, 1 },
   { ".cfi_return_column", sigtbl16, 1 },
   { ".cfi_signal_frame", sigtbl17, 1 },
   { ".cfi_startproc", sigtbl18, 1 },
   { ".cfi_window_save", sigtbl19, 1 },
   { ".code",         sigtbl20, 1 },
   { ".comm",         sigtbl21, 2 },
   { ".common",       sigtbl22, 2 },
   { ".cpu",          sigtbl23, 2 },
   { ".data",         sigtbl24, 1 },
   { ".eabi_attribute", sigtbl25, 1 },
   { ".end",          sigtbl26, 1 },
   { ".ent",          sigtbl27, 1 },
   { ".even",         sigtbl28, 1 },
   { ".extern",       sigtbl29, 1 },
   { ".file",         sigtbl30, 2 },
   { ".fmask",        sigtbl31, 1 },
   { ".fnend",        sigtbl32, 1 },
   { ".fnstart",      sigtbl33, 1 },
   { ".force_thumb",  sigtbl34, 1 },
   { ".fpu",          sigtbl35, 1 },
   { ".frame",        sigtbl36, 1 },
   { ".global",       sigtbl37, 1 },
   { ".globl",        sigtbl38, 1 },
   { ".gnu_attribute", sigtbl39, 1 },
   { ".half",         sigtbl40, 1 },
   { ".hword",        sigtbl41, 1 },
   { ".ident",        sigtbl42, 1 },
   { ".inst",         sigtbl43, 1 },
   { ".int",          sigtbl44, 1 },
   { ".lcomm",        sigtbl45, 2 },
   { ".local",        sigtbl46, 1 },
   { ".long",         sigtbl47, 1 },
   { ".mask",         sigtbl48, 1 },
   { ".nword",        sigtbl49, 1 },
   { ".personality",  sigtbl50, 1 },
   { ".personalityindex", sigtbl51, 1 },
   { ".previous",     sigtbl52, 1 },
   { ".proc",         sigtbl53, 2 },
   { ".rdata",        sigtbl54, 1 },
   { ".register",     sigtbl55, 1 },
   { ".reserve",      sigtbl56, 2 },
   { ".section",      sigtbl57, 10 },
   { ".seg",          sigtbl58, 1 },
   { ".set",          sigtbl59, 2 },
   { ".short",        sigtbl60, 1 },
   { ".size",         sigtbl61, 1 },
   { ".skip",         sigtbl62, 1 },
   { ".space",        sigtbl63, 1 },
   { ".syntax",       sigtbl64, 1 },
   { ".text",         sigtbl65, 1 },
   { ".thumb",        sigtbl66, 1 },
   { ".thumb_func",   sigtbl67, 1 },
   { ".thumb_set",    sigtbl68, 1 },
   { ".type",         sigtbl69, 1 },
   { ".unset",        sigtbl70, 1 },
   { ".word",         sigtbl71, 1 },
   { ".xword",        sigtbl72, 1 },
   { "abs",           sigtbl73, 2 },
   { "abs.d",         sigtbl74, 1 },
   { "abs.s",         sigtbl75, 1 },
   { "add",           sigtbl76, 3 },
   { "add.d",         sigtbl77, 2 },
   { "add.s",         sigtbl78, 2 },
   { "addi",          sigtbl79, 1 },
   { "addiu",         sigtbl80, 1 },
   { "addu",          sigtbl81, 3 },
   { "and",           sigtbl82, 3 },
   { "andi",          sigtbl83, 1 },
   { "b",             sigtbl84, 1 },
   { "bal",           sigtbl85, 1 },
   { "bc1f",          sigtbl86, 2 },
   { "bc1fl",         sigtbl87, 2 },
   { "bc1t",          sigtbl88, 2 },
   { "bc1tl",         sigtbl89, 2 },
   { "bc2f",          sigtbl90, 2 },
   { "bc2fl",         sigtbl91, 2 },
   { "bc2t",          sigtbl92, 2 },
   { "bc2tl",         sigtbl93, 2 },
   { "bc3f",          sigtbl94, 2 },
   { "bc3fl",         sigtbl95, 2 },
   { "bc3t",          sigtbl96, 2 },
   { "bc3tl",         sigtbl97, 2 },
   { "beq",           sigtbl98, 2 },
   { "beql",          sigtbl99, 2 },
   { "beqz",          sigtbl100, 1 },
   { "beqzl",         sigtbl101, 1 },
   { "bgez",          sigtbl102, 1 },
   { "bgezal",        sigtbl103, 1 },
   { "bgezall",       sigtbl104, 1 },
   { "bgezl",         sigtbl105, 1 },
   { "bgtz",          sigtbl106, 1 },
   { "bgtzl",         sigtbl107, 1 },
   { "blez",          sigtbl108, 1 },
   { "blezl",         sigtbl109, 1 },
   { "bltz",          sigtbl110, 1 },
   { "bltzal",        sigtbl111, 1 },
   { "bltzall",       sigtbl112, 1 },
   { "bltzl",         sigtbl113, 1 },
   { "bne",           sigtbl114, 2 },
   { "bnel",          sigtbl115, 2 },
   { "bnez",          sigtbl116, 1 },
   { "bnezl",         sigtbl117, 1 },
   { "break",         sigtbl118, 3 },
   { "c.eq.d",        sigtbl119, 2 },
   { "c.eq.s",        sigtbl120, 2 },
   { "c.f.d",         sigtbl121, 2 },
   { "c.f.s",         sigtbl122, 2 },
   { "c.le.d",        sigtbl123, 2 },
   { "c.le.s",        sigtbl124, 2 },
   { "c.lt.d",        sigtbl125, 2 },
   { "c.lt.s",        sigtbl126, 2 },
   { "c.nge.d",       sigtbl127, 2 },
   { "c.nge.s",       sigtbl128, 2 },
   { "c.ngl.d",       sigtbl129, 2 },
   { "c.ngl.s",       sigtbl130, 2 },
   { "c.ngle.d",      sigtbl131, 2 },
   { "c.ngle.s",      sigtbl132, 2 },
   { "c.ngt.d",       sigtbl133, 2 },
   { "c.ngt.s",       sigtbl134, 2 },
   { "c.ole.d",       sigtbl135, 2 },
   { "c.ole.s",       sigtbl136, 2 },
   { "c.olt.d",       sigtbl137, 2 },
   { "c.olt.s",       sigtbl138, 2 },
   { "c.seq.d",       sigtbl139, 2 },
   { "c.seq.s",       sigtbl140, 2 },
   { "c.sf.d",        sigtbl141, 2 },
   { "c.sf.s",        sigtbl142, 2 },
   { "c.ueq.d",       sigtbl143, 2 },
   { "c.ueq.s",       sigtbl144, 2 },
   { "c.ule.d",       sigtbl145, 2 },
   { "c.ule.s",       sigtbl146, 2 },
   { "c.ult.d",       sigtbl147, 2 },
   { "c.ult.s",       sigtbl148, 2 },
   { "c.un.d",        sigtbl149, 2 },
   { "c.un.s",        sigtbl150, 2 },
   { "cache",         sigtbl151, 2 },
   { "ceil.w.d",      sigtbl152, 1 },
   { "ceil.w.s",      sigtbl153, 1 },
   { "cfc1",          sigtbl154, 1 },
   { "cfc2",          sigtbl155, 1 },
   { "cfc3",          sigtbl156, 1 },
   { "clo",           sigtbl157, 1 },
   { "clz",           sigtbl158, 1 },
   { "cop2",          sigtbl159, 1 },
   { "cop3",          sigtbl160, 1 },
   { "ctc1",          sigtbl161, 1 },
   { "ctc2",          sigtbl162, 1 },
   { "ctc3",          sigtbl163, 1 },
   { "cvt.d.l",       sigtbl164, 1 },
   { "cvt.d.s",       sigtbl165, 1 },
   { "cvt.d.w",       sigtbl166, 1 },
   { "cvt.s.d",       sigtbl167, 1 },
   { "cvt.s.l",       sigtbl168, 1 },
   { "cvt.s.w",       sigtbl169, 1 },
   { "cvt.w.d",       sigtbl170, 1 },
   { "cvt.w.s",       sigtbl171, 1 },
   { "deret",         sigtbl172, 1 },
   { "div",           sigtbl173, 2 },
   { "div.d",         sigtbl174, 2 },
   { "div.s",         sigtbl175, 2 },
   { "divu",          sigtbl176, 2 },
   { "eret",          sigtbl177, 1 },
   { "floor.w.d",     sigtbl178, 1 },
   { "floor.w.s",     sigtbl179, 1 },
   { "j",             sigtbl180, 2 },
   { "jal",           sigtbl181, 3 },
   { "jalr",          sigtbl182, 2 },
   { "jr",            sigtbl183, 1 },
   { "la",            sigtbl184, 1 },
   { "lb",            sigtbl185, 2 },
   { "lbu",           sigtbl186, 2 },
   { "ldc1",          sigtbl187, 2 },
   { "ldc2",          sigtbl188, 2 },
   { "ldc3",          sigtbl189, 2 },
   { "lh",            sigtbl190, 2 },
   { "lhu",           sigtbl191, 2 },
   { "li",            sigtbl192, 1 },
   { "ll",            sigtbl193, 2 },
   { "lui",           sigtbl194, 1 },
   { "lw",            sigtbl195, 2 },
   { "lwc1",          sigtbl196, 2 },
   { "lwc2",          sigtbl197, 2 },
   { "lwc3",          sigtbl198, 2 },
   { "lwl",           sigtbl199, 2 },
   { "lwr",           sigtbl200, 2 },
   { "madd",          sigtbl201, 1 },
   { "maddu",         sigtbl202, 1 },
   { "mfc0",          sigtbl203, 2 },
   { "mfc1",          sigtbl204, 1 },
   { "mfc2",          sigtbl205, 2 },
   { "mfc3",          sigtbl206, 2 },
   { "mfhi",          sigtbl207, 1 },
   { "mflo",          sigtbl208, 1 },
   { "mov.d",         sigtbl209, 1 },
   { "mov.s",         sigtbl210, 1 },
   { "move",          sigtbl211, 1 },
   { "movf",          sigtbl212, 1 },
   { "movf.d",        sigtbl213, 1 },
   { "movf.s",        sigtbl214, 1 },
   { "movn",          sigtbl215, 1 },
   { "movn.d",        sigtbl216, 1 },
   { "movn.s",        sigtbl217, 1 },
   { "movt",          sigtbl218, 1 },
   { "movt.d",        sigtbl219, 1 },
   { "movt.s",        sigtbl220, 1 },
   { "movz",          sigtbl221, 1 },
   { "movz.d",        sigtbl222, 1 },
   { "movz.s",        sigtbl223, 1 },
   { "msub",          sigtbl224, 1 },
   { "msubu",         sigtbl225, 1 },
   { "mtc0",          sigtbl226, 2 },
   { "mtc1",          sigtbl227, 1 },
   { "mtc2",          sigtbl228, 2 },
   { "mtc3",          sigtbl229, 2 },
   { "mthi",          sigtbl230, 1 },
   { "mtlo",          sigtbl231, 1 },
   { "mul",           sigtbl232, 1 },
   { "mul.d",         sigtbl233, 2 },
   { "mul.s",         sigtbl234, 2 },
   { "mult",          sigtbl235, 1 },
   { "multu",         sigtbl236, 1 },
   { "neg",           sigtbl237, 2 },
   { "neg.d",         sigtbl238, 1 },
   { "neg.s",         sigtbl239, 1 },
   { "negu",          sigtbl240, 2 },
   { "nop",           sigtbl241, 1 },
   { "nor",           sigtbl242, 3 },
   { "nori",          sigtbl243, 1 },
   { "not",           sigtbl244, 2 },
   { "or",            sigtbl245, 3 },
   { "ori",           sigtbl246, 1 },
   { "pref",          sigtbl247, 2 },
   { "rfe",           sigtbl248, 1 },
   { "rol",           sigtbl249, 2 },
   { "ror",           sigtbl250, 2 },
   { "round.w.d",     sigtbl251, 1 },
   { "round.w.s",     sigtbl252, 1 },
   { "sb",            sigtbl253, 2 },
   { "sc",            sigtbl254, 2 },
   { "sdbbp",         sigtbl255, 2 },
   { "sdc1",          sigtbl256, 2 },
   { "sdc2",          sigtbl257, 2 },
   { "sdc3",          sigtbl258, 2 },
   { "seq",           sigtbl259, 3 },
   { "seqi",          sigtbl260, 1 },
   { "sge",           sigtbl261, 3 },
   { "sgei",          sigtbl262, 1 },
   { "sgeiu",         sigtbl263, 1 },
   { "sgeu",          sigtbl264, 3 },
   { "sgt",           sigtbl265, 3 },
   { "sgti",          sigtbl266, 1 },
   { "sgtiu",         sigtbl267, 1 },
   { "sgtu",          sigtbl268, 3 },
   { "sh",            sigtbl269, 2 },
   { "sle",           sigtbl270, 3 },
   { "slei",          sigtbl271, 1 },
   { "sleiu",         sigtbl272, 1 },
   { "sleu",          sigtbl273, 3 },
   { "sll",           sigtbl274, 2 },
   { "sllv",          sigtbl275, 1 },
   { "slt",           sigtbl276, 3 },
   { "slti",          sigtbl277, 1 },
   { "sltiu",         sigtbl278, 1 },
   { "sltu",          sigtbl279, 3 },
   { "sne",           sigtbl280, 3 },
   { "snei",          sigtbl281, 1 },
   { "sqrt.d",        sigtbl282, 1 },
   { "sqrt.s",        sigtbl283, 1 },
   { "sra",           sigtbl284, 2 },
   { "srav",          sigtbl285, 1 },
   { "srl",           sigtbl286, 2 },
   { "srlv",          sigtbl287, 1 },
   { "ssnop",         sigtbl288, 1 },
   { "sub",           sigtbl289, 3 },
   { "sub.d",         sigtbl290, 2 },
   { "sub.s",         sigtbl291, 2 },
   { "subi",          sigtbl292, 1 },
   { "subiu",         sigtbl293, 1 },
   { "subu",          sigtbl294, 3 },
   { "sw",            sigtbl295, 2 },
   { "swc1",          sigtbl296, 2 },
   { "swc2",          sigtbl297, 2 },
   { "swc3",          sigtbl298, 2 },
   { "swl",           sigtbl299, 2 },
   { "swr",           sigtbl300, 2 },
   { "sync",          sigtbl301, 1 },
   { "syscall",       sigtbl302, 2 },
   { "teq",           sigtbl303, 3 },
   { "teqi",          sigtbl304, 1 },
   { "tge",           sigtbl305, 3 },
   { "tgei",          sigtbl306, 1 },
   { "tgeiu",         sigtbl307, 1 },
   { "tgeu",          sigtbl308, 3 },
   { "tlbp",          sigtbl309, 1 },
   { "tlbr",          sigtbl310, 1 },
   { "tlbwi",         sigtbl311, 1 },
   { "tlbwr",         sigtbl312, 1 },
   { "tlt",           sigtbl313, 3 },
   { "tlti",          sigtbl314, 1 },
   { "tltiu",         sigtbl315, 1 },
   { "tltu",          sigtbl316, 3 },
   { "tne",           sigtbl317, 3 },
   { "tnei",          sigtbl318, 1 },
   { "trunc.w.d",     sigtbl319, 1 },
   { "trunc.w.s",     sigtbl320, 1 },
   { "ulw",           sigtbl321, 2 },
   { "usw",           sigtbl322, 2 },
   { "wait",          sigtbl323, 2 },
   { "xor",           sigtbl324, 3 },
   { "xori",          sigtbl325, 1 },
};

const unsigned numopcodes = sizeof(opcodes)/sizeof(opcodes[0]);

