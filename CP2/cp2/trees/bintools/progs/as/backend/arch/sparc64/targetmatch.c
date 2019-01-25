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


static UNUSED bool check_registertag(struct operand *oper) {
   return oper->is_registertag;
}
static UNUSED bool check_reg(struct operand *oper) {
   return oper->is_reg;
}
static UNUSED bool check_icc(struct operand *oper) {
   return oper->is_icc;
}
static UNUSED bool check_freg(struct operand *oper) {
   return oper->is_freg;
}
static UNUSED bool check_fcc(struct operand *oper) {
   return oper->is_fcc;
}
static UNUSED bool check_fsr(struct operand *oper) {
   return oper->is_fsr;
}
static UNUSED bool check_asr(struct operand *oper) {
   return oper->is_asr;
}
static UNUSED bool check_pr(struct operand *oper) {
   return oper->is_pr;
}
static UNUSED bool check_expr(struct operand *oper) {
   return oper->is_expr;
}
static UNUSED bool check_symbol(struct operand *oper) {
   return oper->is_symbol;
}
static UNUSED bool check_number(struct operand *oper) {
   return oper->is_number;
}
static UNUSED bool check_i10num(struct operand *oper) {
   return oper->is_i10num;
}
static UNUSED bool check_i11num(struct operand *oper) {
   return oper->is_i11num;
}
static UNUSED bool check_i13num(struct operand *oper) {
   return oper->is_i13num;
}
static UNUSED bool check_i32num(struct operand *oper) {
   return oper->is_i32num;
}
static UNUSED bool check_i64num(struct operand *oper) {
   return oper->is_i64num;
}
static UNUSED bool check_u5num(struct operand *oper) {
   return oper->is_u5num;
}
static UNUSED bool check_u6num(struct operand *oper) {
   return oper->is_u6num;
}
static UNUSED bool check_u19num(struct operand *oper) {
   return oper->is_u19num;
}
static UNUSED bool check_u22num(struct operand *oper) {
   return oper->is_u22num;
}
static UNUSED bool check_u32num(struct operand *oper) {
   return oper->is_u32num;
}
static UNUSED bool check_membarmask(struct operand *oper) {
   return oper->is_membarmask;
}
static UNUSED bool check_addr_rr(struct operand *oper) {
   return oper->is_addr_rr;
}
static UNUSED bool check_addr_ri(struct operand *oper) {
   return oper->is_addr_ri;
}
static UNUSED bool check_addr_rx(struct operand *oper) {
   return oper->is_addr_rx;
}
static UNUSED bool check_braddr_rr(struct operand *oper) {
   return oper->is_braddr_rr;
}
static UNUSED bool check_braddr_ri(struct operand *oper) {
   return oper->is_braddr_ri;
}
static UNUSED bool check_braddr_rx(struct operand *oper) {
   return oper->is_braddr_rx;
}
static UNUSED bool check_braddr_rr_immasi(struct operand *oper) {
   return oper->is_braddr_rr_immasi;
}
static UNUSED bool check_braddr_ri_asi(struct operand *oper) {
   return oper->is_braddr_ri_asi;
}
static UNUSED bool check_braddr_r_immasi(struct operand *oper) {
   return oper->is_braddr_r_immasi;
}
static UNUSED bool check_braddr_r_asi(struct operand *oper) {
   return oper->is_braddr_r_asi;
}
static UNUSED bool check_braddr_r(struct operand *oper) {
   return oper->is_braddr_r;
}
static UNUSED bool check_trapnum_rr(struct operand *oper) {
   return oper->is_trapnum_rr;
}
static UNUSED bool check_trapnum_ri(struct operand *oper) {
   return oper->is_trapnum_ri;
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
   insn_sethi_u32num_reg(line, operandarray_get(ops, 0)->val_u32num, operandarray_get(ops, 1)->val_reg);
}

static void call_1(int line, struct operandarray *ops) {
   insn_sethi_expr_reg(line, operandarray_get(ops, 0)->val_expr, operandarray_get(ops, 1)->val_reg);
}

static void call_2(int line, struct operandarray *ops) {
   insn_add_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_3(int line, struct operandarray *ops) {
   insn_add_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_4(int line, struct operandarray *ops) {
   insn_addcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_5(int line, struct operandarray *ops) {
   insn_addcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_6(int line, struct operandarray *ops) {
   insn_addc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_7(int line, struct operandarray *ops) {
   insn_addc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_8(int line, struct operandarray *ops) {
   insn_addccc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_9(int line, struct operandarray *ops) {
   insn_addccc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_10(int line, struct operandarray *ops) {
   insn_sub_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_11(int line, struct operandarray *ops) {
   insn_sub_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_12(int line, struct operandarray *ops) {
   insn_subcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_13(int line, struct operandarray *ops) {
   insn_subcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_14(int line, struct operandarray *ops) {
   insn_subc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_15(int line, struct operandarray *ops) {
   insn_subc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_16(int line, struct operandarray *ops) {
   insn_subccc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_17(int line, struct operandarray *ops) {
   insn_subccc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_18(int line, struct operandarray *ops) {
   insn_and_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_19(int line, struct operandarray *ops) {
   insn_and_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_20(int line, struct operandarray *ops) {
   insn_andcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_21(int line, struct operandarray *ops) {
   insn_andcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_22(int line, struct operandarray *ops) {
   insn_andn_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_23(int line, struct operandarray *ops) {
   insn_andn_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_24(int line, struct operandarray *ops) {
   insn_andncc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_25(int line, struct operandarray *ops) {
   insn_andncc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_26(int line, struct operandarray *ops) {
   insn_or_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_27(int line, struct operandarray *ops) {
   insn_or_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_28(int line, struct operandarray *ops) {
   insn_or_reg_expr_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_expr, operandarray_get(ops, 2)->val_reg);
}

static void call_29(int line, struct operandarray *ops) {
   insn_orcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_30(int line, struct operandarray *ops) {
   insn_orcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_31(int line, struct operandarray *ops) {
   insn_orn_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_32(int line, struct operandarray *ops) {
   insn_orn_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_33(int line, struct operandarray *ops) {
   insn_orncc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_34(int line, struct operandarray *ops) {
   insn_orncc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_35(int line, struct operandarray *ops) {
   insn_xor_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_36(int line, struct operandarray *ops) {
   insn_xor_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_37(int line, struct operandarray *ops) {
   insn_xorcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_38(int line, struct operandarray *ops) {
   insn_xorcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_39(int line, struct operandarray *ops) {
   insn_xnor_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_40(int line, struct operandarray *ops) {
   insn_xnor_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_41(int line, struct operandarray *ops) {
   insn_xnorcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_42(int line, struct operandarray *ops) {
   insn_xnorcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_43(int line, struct operandarray *ops) {
   insn_popc_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_44(int line, struct operandarray *ops) {
   insn_popc_i13num_reg(line, operandarray_get(ops, 0)->val_i13num, operandarray_get(ops, 1)->val_reg);
}

static void call_45(int line, struct operandarray *ops) {
   insn_save_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_46(int line, struct operandarray *ops) {
   insn_save_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_47(int line, struct operandarray *ops) {
   insn_restore_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_48(int line, struct operandarray *ops) {
   insn_restore_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_49(int line, struct operandarray *ops) {
   insn_taddcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_50(int line, struct operandarray *ops) {
   insn_taddcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_51(int line, struct operandarray *ops) {
   insn_taddcctv_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_52(int line, struct operandarray *ops) {
   insn_taddcctv_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_53(int line, struct operandarray *ops) {
   insn_tsubcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_54(int line, struct operandarray *ops) {
   insn_tsubcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_55(int line, struct operandarray *ops) {
   insn_tsubcctv_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_56(int line, struct operandarray *ops) {
   insn_tsubcctv_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_57(int line, struct operandarray *ops) {
   insn_addx_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_58(int line, struct operandarray *ops) {
   insn_addx_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_59(int line, struct operandarray *ops) {
   insn_addxcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_60(int line, struct operandarray *ops) {
   insn_addxcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_61(int line, struct operandarray *ops) {
   insn_subx_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_62(int line, struct operandarray *ops) {
   insn_subx_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_63(int line, struct operandarray *ops) {
   insn_subxcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_64(int line, struct operandarray *ops) {
   insn_subxcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_65(int line, struct operandarray *ops) {
   insn_sll_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_66(int line, struct operandarray *ops) {
   insn_sll_reg_u5num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_u5num, operandarray_get(ops, 2)->val_reg);
}

static void call_67(int line, struct operandarray *ops) {
   insn_srl_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_68(int line, struct operandarray *ops) {
   insn_srl_reg_u5num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_u5num, operandarray_get(ops, 2)->val_reg);
}

static void call_69(int line, struct operandarray *ops) {
   insn_sra_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_70(int line, struct operandarray *ops) {
   insn_sra_reg_u5num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_u5num, operandarray_get(ops, 2)->val_reg);
}

static void call_71(int line, struct operandarray *ops) {
   insn_sllx_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_72(int line, struct operandarray *ops) {
   insn_sllx_reg_u6num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_u6num, operandarray_get(ops, 2)->val_reg);
}

static void call_73(int line, struct operandarray *ops) {
   insn_srlx_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_74(int line, struct operandarray *ops) {
   insn_srlx_reg_u6num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_u6num, operandarray_get(ops, 2)->val_reg);
}

static void call_75(int line, struct operandarray *ops) {
   insn_srax_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_76(int line, struct operandarray *ops) {
   insn_srax_reg_u6num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_u6num, operandarray_get(ops, 2)->val_reg);
}

static void call_77(int line, struct operandarray *ops) {
   insn_umul_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_78(int line, struct operandarray *ops) {
   insn_umul_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_79(int line, struct operandarray *ops) {
   insn_smul_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_80(int line, struct operandarray *ops) {
   insn_smul_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_81(int line, struct operandarray *ops) {
   insn_umulcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_82(int line, struct operandarray *ops) {
   insn_umulcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_83(int line, struct operandarray *ops) {
   insn_smulcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_84(int line, struct operandarray *ops) {
   insn_smulcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_85(int line, struct operandarray *ops) {
   insn_mulscc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_86(int line, struct operandarray *ops) {
   insn_mulscc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_87(int line, struct operandarray *ops) {
   insn_sdiv_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_88(int line, struct operandarray *ops) {
   insn_sdiv_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_89(int line, struct operandarray *ops) {
   insn_udiv_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_90(int line, struct operandarray *ops) {
   insn_udiv_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_91(int line, struct operandarray *ops) {
   insn_sdivcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_92(int line, struct operandarray *ops) {
   insn_sdivcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_93(int line, struct operandarray *ops) {
   insn_udivcc_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_94(int line, struct operandarray *ops) {
   insn_udivcc_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_95(int line, struct operandarray *ops) {
   insn_mulx_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_96(int line, struct operandarray *ops) {
   insn_mulx_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_97(int line, struct operandarray *ops) {
   insn_sdivx_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_98(int line, struct operandarray *ops) {
   insn_sdivx_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_99(int line, struct operandarray *ops) {
   insn_udivx_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_100(int line, struct operandarray *ops) {
   insn_udivx_reg_i13num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_reg);
}

static void call_101(int line, struct operandarray *ops) {
   insn_fadds_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_102(int line, struct operandarray *ops) {
   insn_faddd_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_103(int line, struct operandarray *ops) {
   insn_faddq_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_104(int line, struct operandarray *ops) {
   insn_fsubs_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_105(int line, struct operandarray *ops) {
   insn_fsubd_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_106(int line, struct operandarray *ops) {
   insn_fsubq_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_107(int line, struct operandarray *ops) {
   insn_fcmps_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_108(int line, struct operandarray *ops) {
   insn_fcmpd_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_109(int line, struct operandarray *ops) {
   insn_fcmpq_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_110(int line, struct operandarray *ops) {
   insn_fcmpes_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_111(int line, struct operandarray *ops) {
   insn_fcmped_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_112(int line, struct operandarray *ops) {
   insn_fcmpeq_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_113(int line, struct operandarray *ops) {
   insn_fstox_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_114(int line, struct operandarray *ops) {
   insn_fdtox_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_115(int line, struct operandarray *ops) {
   insn_fqtox_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_116(int line, struct operandarray *ops) {
   insn_fstoi_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_117(int line, struct operandarray *ops) {
   insn_fdtoi_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_118(int line, struct operandarray *ops) {
   insn_fqtoi_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_119(int line, struct operandarray *ops) {
   insn_fxtos_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_120(int line, struct operandarray *ops) {
   insn_fxtod_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_121(int line, struct operandarray *ops) {
   insn_fxtoq_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_122(int line, struct operandarray *ops) {
   insn_fitos_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_123(int line, struct operandarray *ops) {
   insn_fitod_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_124(int line, struct operandarray *ops) {
   insn_fitoq_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_125(int line, struct operandarray *ops) {
   insn_fstod_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_126(int line, struct operandarray *ops) {
   insn_fstoq_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_127(int line, struct operandarray *ops) {
   insn_fdtos_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_128(int line, struct operandarray *ops) {
   insn_fdtoq_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_129(int line, struct operandarray *ops) {
   insn_fqtos_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_130(int line, struct operandarray *ops) {
   insn_fqtod_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_131(int line, struct operandarray *ops) {
   insn_fmovs_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_132(int line, struct operandarray *ops) {
   insn_fmovd_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_133(int line, struct operandarray *ops) {
   insn_fmovq_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_134(int line, struct operandarray *ops) {
   insn_fnegs_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_135(int line, struct operandarray *ops) {
   insn_fnegd_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_136(int line, struct operandarray *ops) {
   insn_fnegq_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_137(int line, struct operandarray *ops) {
   insn_fabss_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_138(int line, struct operandarray *ops) {
   insn_fabsd_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_139(int line, struct operandarray *ops) {
   insn_fabsq_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_140(int line, struct operandarray *ops) {
   insn_fsqrts_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_141(int line, struct operandarray *ops) {
   insn_fsqrtd_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_142(int line, struct operandarray *ops) {
   insn_fsqrtq_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg);
}

static void call_143(int line, struct operandarray *ops) {
   insn_fmuls_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_144(int line, struct operandarray *ops) {
   insn_fmuld_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_145(int line, struct operandarray *ops) {
   insn_fmulq_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_146(int line, struct operandarray *ops) {
   insn_fsmuld_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_147(int line, struct operandarray *ops) {
   insn_fdmulq_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_148(int line, struct operandarray *ops) {
   insn_fdivs_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_149(int line, struct operandarray *ops) {
   insn_fdivd_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_150(int line, struct operandarray *ops) {
   insn_fdivq_freg_freg_freg(line, operandarray_get(ops, 0)->val_freg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_151(int line, struct operandarray *ops) {
   insn_brz_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_152(int line, struct operandarray *ops) {
   insn_brz_pt_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_153(int line, struct operandarray *ops) {
   insn_brz_pn_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_154(int line, struct operandarray *ops) {
   insn_brz_a_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_155(int line, struct operandarray *ops) {
   insn_brz_a_pt_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_156(int line, struct operandarray *ops) {
   insn_brz_a_pn_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_157(int line, struct operandarray *ops) {
   insn_brlez_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_158(int line, struct operandarray *ops) {
   insn_brlez_pt_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_159(int line, struct operandarray *ops) {
   insn_brlez_pn_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_160(int line, struct operandarray *ops) {
   insn_brlez_a_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_161(int line, struct operandarray *ops) {
   insn_brlez_a_pt_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_162(int line, struct operandarray *ops) {
   insn_brlez_a_pn_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_163(int line, struct operandarray *ops) {
   insn_brlz_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_164(int line, struct operandarray *ops) {
   insn_brlz_pt_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_165(int line, struct operandarray *ops) {
   insn_brlz_pn_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_166(int line, struct operandarray *ops) {
   insn_brlz_a_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_167(int line, struct operandarray *ops) {
   insn_brlz_a_pt_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_168(int line, struct operandarray *ops) {
   insn_brlz_a_pn_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_169(int line, struct operandarray *ops) {
   insn_brnz_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_170(int line, struct operandarray *ops) {
   insn_brnz_pt_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_171(int line, struct operandarray *ops) {
   insn_brnz_pn_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_172(int line, struct operandarray *ops) {
   insn_brnz_a_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_173(int line, struct operandarray *ops) {
   insn_brnz_a_pt_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_174(int line, struct operandarray *ops) {
   insn_brnz_a_pn_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_175(int line, struct operandarray *ops) {
   insn_brgz_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_176(int line, struct operandarray *ops) {
   insn_brgz_pt_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_177(int line, struct operandarray *ops) {
   insn_brgz_pn_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_178(int line, struct operandarray *ops) {
   insn_brgz_a_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_179(int line, struct operandarray *ops) {
   insn_brgz_a_pt_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_180(int line, struct operandarray *ops) {
   insn_brgz_a_pn_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_181(int line, struct operandarray *ops) {
   insn_brgez_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_182(int line, struct operandarray *ops) {
   insn_brgez_pt_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_183(int line, struct operandarray *ops) {
   insn_brgez_pn_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_184(int line, struct operandarray *ops) {
   insn_brgez_a_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_185(int line, struct operandarray *ops) {
   insn_brgez_a_pt_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_186(int line, struct operandarray *ops) {
   insn_brgez_a_pn_reg_symbol(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_symbol);
}

static void call_187(int line, struct operandarray *ops) {
   insn_fba_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_188(int line, struct operandarray *ops) {
   insn_fba_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_189(int line, struct operandarray *ops) {
   insn_fbn_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_190(int line, struct operandarray *ops) {
   insn_fbn_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_191(int line, struct operandarray *ops) {
   insn_fbu_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_192(int line, struct operandarray *ops) {
   insn_fbu_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_193(int line, struct operandarray *ops) {
   insn_fbg_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_194(int line, struct operandarray *ops) {
   insn_fbg_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_195(int line, struct operandarray *ops) {
   insn_fbug_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_196(int line, struct operandarray *ops) {
   insn_fbug_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_197(int line, struct operandarray *ops) {
   insn_fbl_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_198(int line, struct operandarray *ops) {
   insn_fbl_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_199(int line, struct operandarray *ops) {
   insn_fbul_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_200(int line, struct operandarray *ops) {
   insn_fbul_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_201(int line, struct operandarray *ops) {
   insn_fblg_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_202(int line, struct operandarray *ops) {
   insn_fblg_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_203(int line, struct operandarray *ops) {
   insn_fbne_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_204(int line, struct operandarray *ops) {
   insn_fbne_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_205(int line, struct operandarray *ops) {
   insn_fbe_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_206(int line, struct operandarray *ops) {
   insn_fbe_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_207(int line, struct operandarray *ops) {
   insn_fbue_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_208(int line, struct operandarray *ops) {
   insn_fbue_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_209(int line, struct operandarray *ops) {
   insn_fbge_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_210(int line, struct operandarray *ops) {
   insn_fbge_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_211(int line, struct operandarray *ops) {
   insn_fbuge_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_212(int line, struct operandarray *ops) {
   insn_fbuge_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_213(int line, struct operandarray *ops) {
   insn_fble_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_214(int line, struct operandarray *ops) {
   insn_fble_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_215(int line, struct operandarray *ops) {
   insn_fbule_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_216(int line, struct operandarray *ops) {
   insn_fbule_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_217(int line, struct operandarray *ops) {
   insn_fbo_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_218(int line, struct operandarray *ops) {
   insn_fbo_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_219(int line, struct operandarray *ops) {
   insn_fbnz_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_220(int line, struct operandarray *ops) {
   insn_fbnz_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_221(int line, struct operandarray *ops) {
   insn_fbz_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_222(int line, struct operandarray *ops) {
   insn_fbz_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_223(int line, struct operandarray *ops) {
   insn_fba_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_224(int line, struct operandarray *ops) {
   insn_fba_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_225(int line, struct operandarray *ops) {
   insn_fba_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_226(int line, struct operandarray *ops) {
   insn_fba_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_227(int line, struct operandarray *ops) {
   insn_fba_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_228(int line, struct operandarray *ops) {
   insn_fba_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_229(int line, struct operandarray *ops) {
   insn_fbn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_230(int line, struct operandarray *ops) {
   insn_fbn_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_231(int line, struct operandarray *ops) {
   insn_fbn_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_232(int line, struct operandarray *ops) {
   insn_fbn_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_233(int line, struct operandarray *ops) {
   insn_fbn_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_234(int line, struct operandarray *ops) {
   insn_fbn_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_235(int line, struct operandarray *ops) {
   insn_fbu_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_236(int line, struct operandarray *ops) {
   insn_fbu_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_237(int line, struct operandarray *ops) {
   insn_fbu_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_238(int line, struct operandarray *ops) {
   insn_fbu_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_239(int line, struct operandarray *ops) {
   insn_fbu_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_240(int line, struct operandarray *ops) {
   insn_fbu_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_241(int line, struct operandarray *ops) {
   insn_fbg_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_242(int line, struct operandarray *ops) {
   insn_fbg_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_243(int line, struct operandarray *ops) {
   insn_fbg_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_244(int line, struct operandarray *ops) {
   insn_fbg_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_245(int line, struct operandarray *ops) {
   insn_fbg_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_246(int line, struct operandarray *ops) {
   insn_fbg_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_247(int line, struct operandarray *ops) {
   insn_fbug_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_248(int line, struct operandarray *ops) {
   insn_fbug_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_249(int line, struct operandarray *ops) {
   insn_fbug_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_250(int line, struct operandarray *ops) {
   insn_fbug_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_251(int line, struct operandarray *ops) {
   insn_fbug_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_252(int line, struct operandarray *ops) {
   insn_fbug_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_253(int line, struct operandarray *ops) {
   insn_fbl_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_254(int line, struct operandarray *ops) {
   insn_fbl_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_255(int line, struct operandarray *ops) {
   insn_fbl_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_256(int line, struct operandarray *ops) {
   insn_fbl_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_257(int line, struct operandarray *ops) {
   insn_fbl_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_258(int line, struct operandarray *ops) {
   insn_fbl_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_259(int line, struct operandarray *ops) {
   insn_fbul_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_260(int line, struct operandarray *ops) {
   insn_fbul_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_261(int line, struct operandarray *ops) {
   insn_fbul_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_262(int line, struct operandarray *ops) {
   insn_fbul_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_263(int line, struct operandarray *ops) {
   insn_fbul_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_264(int line, struct operandarray *ops) {
   insn_fbul_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_265(int line, struct operandarray *ops) {
   insn_fblg_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_266(int line, struct operandarray *ops) {
   insn_fblg_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_267(int line, struct operandarray *ops) {
   insn_fblg_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_268(int line, struct operandarray *ops) {
   insn_fblg_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_269(int line, struct operandarray *ops) {
   insn_fblg_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_270(int line, struct operandarray *ops) {
   insn_fblg_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_271(int line, struct operandarray *ops) {
   insn_fbne_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_272(int line, struct operandarray *ops) {
   insn_fbne_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_273(int line, struct operandarray *ops) {
   insn_fbne_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_274(int line, struct operandarray *ops) {
   insn_fbne_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_275(int line, struct operandarray *ops) {
   insn_fbne_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_276(int line, struct operandarray *ops) {
   insn_fbne_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_277(int line, struct operandarray *ops) {
   insn_fbe_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_278(int line, struct operandarray *ops) {
   insn_fbe_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_279(int line, struct operandarray *ops) {
   insn_fbe_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_280(int line, struct operandarray *ops) {
   insn_fbe_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_281(int line, struct operandarray *ops) {
   insn_fbe_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_282(int line, struct operandarray *ops) {
   insn_fbe_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_283(int line, struct operandarray *ops) {
   insn_fbue_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_284(int line, struct operandarray *ops) {
   insn_fbue_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_285(int line, struct operandarray *ops) {
   insn_fbue_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_286(int line, struct operandarray *ops) {
   insn_fbue_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_287(int line, struct operandarray *ops) {
   insn_fbue_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_288(int line, struct operandarray *ops) {
   insn_fbue_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_289(int line, struct operandarray *ops) {
   insn_fbge_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_290(int line, struct operandarray *ops) {
   insn_fbge_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_291(int line, struct operandarray *ops) {
   insn_fbge_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_292(int line, struct operandarray *ops) {
   insn_fbge_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_293(int line, struct operandarray *ops) {
   insn_fbge_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_294(int line, struct operandarray *ops) {
   insn_fbge_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_295(int line, struct operandarray *ops) {
   insn_fbuge_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_296(int line, struct operandarray *ops) {
   insn_fbuge_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_297(int line, struct operandarray *ops) {
   insn_fbuge_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_298(int line, struct operandarray *ops) {
   insn_fbuge_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_299(int line, struct operandarray *ops) {
   insn_fbuge_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_300(int line, struct operandarray *ops) {
   insn_fbuge_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_301(int line, struct operandarray *ops) {
   insn_fble_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_302(int line, struct operandarray *ops) {
   insn_fble_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_303(int line, struct operandarray *ops) {
   insn_fble_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_304(int line, struct operandarray *ops) {
   insn_fble_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_305(int line, struct operandarray *ops) {
   insn_fble_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_306(int line, struct operandarray *ops) {
   insn_fble_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_307(int line, struct operandarray *ops) {
   insn_fbule_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_308(int line, struct operandarray *ops) {
   insn_fbule_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_309(int line, struct operandarray *ops) {
   insn_fbule_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_310(int line, struct operandarray *ops) {
   insn_fbule_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_311(int line, struct operandarray *ops) {
   insn_fbule_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_312(int line, struct operandarray *ops) {
   insn_fbule_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_313(int line, struct operandarray *ops) {
   insn_fbo_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_314(int line, struct operandarray *ops) {
   insn_fbo_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_315(int line, struct operandarray *ops) {
   insn_fbo_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_316(int line, struct operandarray *ops) {
   insn_fbo_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_317(int line, struct operandarray *ops) {
   insn_fbo_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_318(int line, struct operandarray *ops) {
   insn_fbo_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_319(int line, struct operandarray *ops) {
   insn_fbnz_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_320(int line, struct operandarray *ops) {
   insn_fbnz_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_321(int line, struct operandarray *ops) {
   insn_fbnz_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_322(int line, struct operandarray *ops) {
   insn_fbnz_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_323(int line, struct operandarray *ops) {
   insn_fbnz_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_324(int line, struct operandarray *ops) {
   insn_fbnz_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_325(int line, struct operandarray *ops) {
   insn_fbz_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_326(int line, struct operandarray *ops) {
   insn_fbz_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_327(int line, struct operandarray *ops) {
   insn_fbz_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_328(int line, struct operandarray *ops) {
   insn_fbz_a_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_329(int line, struct operandarray *ops) {
   insn_fbz_a_pt_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_330(int line, struct operandarray *ops) {
   insn_fbz_a_pn_fcc_symbol(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_symbol);
}

static void call_331(int line, struct operandarray *ops) {
   insn_ba_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_332(int line, struct operandarray *ops) {
   insn_ba_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_333(int line, struct operandarray *ops) {
   insn_bn_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_334(int line, struct operandarray *ops) {
   insn_bn_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_335(int line, struct operandarray *ops) {
   insn_bne_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_336(int line, struct operandarray *ops) {
   insn_bne_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_337(int line, struct operandarray *ops) {
   insn_be_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_338(int line, struct operandarray *ops) {
   insn_be_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_339(int line, struct operandarray *ops) {
   insn_bg_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_340(int line, struct operandarray *ops) {
   insn_bg_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_341(int line, struct operandarray *ops) {
   insn_ble_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_342(int line, struct operandarray *ops) {
   insn_ble_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_343(int line, struct operandarray *ops) {
   insn_bge_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_344(int line, struct operandarray *ops) {
   insn_bge_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_345(int line, struct operandarray *ops) {
   insn_bl_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_346(int line, struct operandarray *ops) {
   insn_bl_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_347(int line, struct operandarray *ops) {
   insn_bgu_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_348(int line, struct operandarray *ops) {
   insn_bgu_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_349(int line, struct operandarray *ops) {
   insn_bleu_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_350(int line, struct operandarray *ops) {
   insn_bleu_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_351(int line, struct operandarray *ops) {
   insn_bcc_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_352(int line, struct operandarray *ops) {
   insn_bcc_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_353(int line, struct operandarray *ops) {
   insn_bcs_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_354(int line, struct operandarray *ops) {
   insn_bcs_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_355(int line, struct operandarray *ops) {
   insn_bpos_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_356(int line, struct operandarray *ops) {
   insn_bpos_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_357(int line, struct operandarray *ops) {
   insn_bneg_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_358(int line, struct operandarray *ops) {
   insn_bneg_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_359(int line, struct operandarray *ops) {
   insn_bvc_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_360(int line, struct operandarray *ops) {
   insn_bvc_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_361(int line, struct operandarray *ops) {
   insn_bvs_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_362(int line, struct operandarray *ops) {
   insn_bvs_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_363(int line, struct operandarray *ops) {
   insn_bnz_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_364(int line, struct operandarray *ops) {
   insn_bnz_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_365(int line, struct operandarray *ops) {
   insn_bz_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_366(int line, struct operandarray *ops) {
   insn_bz_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_367(int line, struct operandarray *ops) {
   insn_bgeu_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_368(int line, struct operandarray *ops) {
   insn_bgeu_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_369(int line, struct operandarray *ops) {
   insn_blu_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_370(int line, struct operandarray *ops) {
   insn_blu_a_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_371(int line, struct operandarray *ops) {
   insn_ba_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_372(int line, struct operandarray *ops) {
   insn_ba_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_373(int line, struct operandarray *ops) {
   insn_ba_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_374(int line, struct operandarray *ops) {
   insn_ba_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_375(int line, struct operandarray *ops) {
   insn_ba_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_376(int line, struct operandarray *ops) {
   insn_ba_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_377(int line, struct operandarray *ops) {
   insn_bn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_378(int line, struct operandarray *ops) {
   insn_bn_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_379(int line, struct operandarray *ops) {
   insn_bn_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_380(int line, struct operandarray *ops) {
   insn_bn_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_381(int line, struct operandarray *ops) {
   insn_bn_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_382(int line, struct operandarray *ops) {
   insn_bn_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_383(int line, struct operandarray *ops) {
   insn_bne_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_384(int line, struct operandarray *ops) {
   insn_bne_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_385(int line, struct operandarray *ops) {
   insn_bne_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_386(int line, struct operandarray *ops) {
   insn_bne_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_387(int line, struct operandarray *ops) {
   insn_bne_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_388(int line, struct operandarray *ops) {
   insn_bne_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_389(int line, struct operandarray *ops) {
   insn_be_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_390(int line, struct operandarray *ops) {
   insn_be_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_391(int line, struct operandarray *ops) {
   insn_be_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_392(int line, struct operandarray *ops) {
   insn_be_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_393(int line, struct operandarray *ops) {
   insn_be_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_394(int line, struct operandarray *ops) {
   insn_be_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_395(int line, struct operandarray *ops) {
   insn_bg_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_396(int line, struct operandarray *ops) {
   insn_bg_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_397(int line, struct operandarray *ops) {
   insn_bg_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_398(int line, struct operandarray *ops) {
   insn_bg_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_399(int line, struct operandarray *ops) {
   insn_bg_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_400(int line, struct operandarray *ops) {
   insn_bg_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_401(int line, struct operandarray *ops) {
   insn_ble_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_402(int line, struct operandarray *ops) {
   insn_ble_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_403(int line, struct operandarray *ops) {
   insn_ble_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_404(int line, struct operandarray *ops) {
   insn_ble_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_405(int line, struct operandarray *ops) {
   insn_ble_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_406(int line, struct operandarray *ops) {
   insn_ble_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_407(int line, struct operandarray *ops) {
   insn_bge_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_408(int line, struct operandarray *ops) {
   insn_bge_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_409(int line, struct operandarray *ops) {
   insn_bge_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_410(int line, struct operandarray *ops) {
   insn_bge_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_411(int line, struct operandarray *ops) {
   insn_bge_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_412(int line, struct operandarray *ops) {
   insn_bge_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_413(int line, struct operandarray *ops) {
   insn_bl_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_414(int line, struct operandarray *ops) {
   insn_bl_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_415(int line, struct operandarray *ops) {
   insn_bl_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_416(int line, struct operandarray *ops) {
   insn_bl_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_417(int line, struct operandarray *ops) {
   insn_bl_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_418(int line, struct operandarray *ops) {
   insn_bl_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_419(int line, struct operandarray *ops) {
   insn_bgu_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_420(int line, struct operandarray *ops) {
   insn_bgu_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_421(int line, struct operandarray *ops) {
   insn_bgu_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_422(int line, struct operandarray *ops) {
   insn_bgu_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_423(int line, struct operandarray *ops) {
   insn_bgu_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_424(int line, struct operandarray *ops) {
   insn_bgu_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_425(int line, struct operandarray *ops) {
   insn_bleu_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_426(int line, struct operandarray *ops) {
   insn_bleu_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_427(int line, struct operandarray *ops) {
   insn_bleu_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_428(int line, struct operandarray *ops) {
   insn_bleu_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_429(int line, struct operandarray *ops) {
   insn_bleu_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_430(int line, struct operandarray *ops) {
   insn_bleu_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_431(int line, struct operandarray *ops) {
   insn_bcc_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_432(int line, struct operandarray *ops) {
   insn_bcc_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_433(int line, struct operandarray *ops) {
   insn_bcc_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_434(int line, struct operandarray *ops) {
   insn_bcc_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_435(int line, struct operandarray *ops) {
   insn_bcc_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_436(int line, struct operandarray *ops) {
   insn_bcc_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_437(int line, struct operandarray *ops) {
   insn_bcs_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_438(int line, struct operandarray *ops) {
   insn_bcs_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_439(int line, struct operandarray *ops) {
   insn_bcs_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_440(int line, struct operandarray *ops) {
   insn_bcs_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_441(int line, struct operandarray *ops) {
   insn_bcs_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_442(int line, struct operandarray *ops) {
   insn_bcs_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_443(int line, struct operandarray *ops) {
   insn_bpos_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_444(int line, struct operandarray *ops) {
   insn_bpos_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_445(int line, struct operandarray *ops) {
   insn_bpos_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_446(int line, struct operandarray *ops) {
   insn_bpos_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_447(int line, struct operandarray *ops) {
   insn_bpos_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_448(int line, struct operandarray *ops) {
   insn_bpos_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_449(int line, struct operandarray *ops) {
   insn_bneg_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_450(int line, struct operandarray *ops) {
   insn_bneg_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_451(int line, struct operandarray *ops) {
   insn_bneg_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_452(int line, struct operandarray *ops) {
   insn_bneg_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_453(int line, struct operandarray *ops) {
   insn_bneg_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_454(int line, struct operandarray *ops) {
   insn_bneg_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_455(int line, struct operandarray *ops) {
   insn_bvc_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_456(int line, struct operandarray *ops) {
   insn_bvc_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_457(int line, struct operandarray *ops) {
   insn_bvc_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_458(int line, struct operandarray *ops) {
   insn_bvc_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_459(int line, struct operandarray *ops) {
   insn_bvc_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_460(int line, struct operandarray *ops) {
   insn_bvc_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_461(int line, struct operandarray *ops) {
   insn_bvs_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_462(int line, struct operandarray *ops) {
   insn_bvs_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_463(int line, struct operandarray *ops) {
   insn_bvs_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_464(int line, struct operandarray *ops) {
   insn_bvs_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_465(int line, struct operandarray *ops) {
   insn_bvs_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_466(int line, struct operandarray *ops) {
   insn_bvs_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_467(int line, struct operandarray *ops) {
   insn_bnz_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_468(int line, struct operandarray *ops) {
   insn_bnz_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_469(int line, struct operandarray *ops) {
   insn_bnz_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_470(int line, struct operandarray *ops) {
   insn_bnz_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_471(int line, struct operandarray *ops) {
   insn_bnz_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_472(int line, struct operandarray *ops) {
   insn_bnz_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_473(int line, struct operandarray *ops) {
   insn_bz_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_474(int line, struct operandarray *ops) {
   insn_bz_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_475(int line, struct operandarray *ops) {
   insn_bz_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_476(int line, struct operandarray *ops) {
   insn_bz_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_477(int line, struct operandarray *ops) {
   insn_bz_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_478(int line, struct operandarray *ops) {
   insn_bz_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_479(int line, struct operandarray *ops) {
   insn_bgeu_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_480(int line, struct operandarray *ops) {
   insn_bgeu_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_481(int line, struct operandarray *ops) {
   insn_bgeu_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_482(int line, struct operandarray *ops) {
   insn_bgeu_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_483(int line, struct operandarray *ops) {
   insn_bgeu_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_484(int line, struct operandarray *ops) {
   insn_bgeu_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_485(int line, struct operandarray *ops) {
   insn_blu_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_486(int line, struct operandarray *ops) {
   insn_blu_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_487(int line, struct operandarray *ops) {
   insn_blu_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_488(int line, struct operandarray *ops) {
   insn_blu_a_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_489(int line, struct operandarray *ops) {
   insn_blu_a_pt_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_490(int line, struct operandarray *ops) {
   insn_blu_a_pn_icc_symbol(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_symbol);
}

static void call_491(int line, struct operandarray *ops) {
   insn_fmovsa_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_492(int line, struct operandarray *ops) {
   insn_fmovda_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_493(int line, struct operandarray *ops) {
   insn_fmovqa_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_494(int line, struct operandarray *ops) {
   insn_fmovsn_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_495(int line, struct operandarray *ops) {
   insn_fmovdn_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_496(int line, struct operandarray *ops) {
   insn_fmovqn_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_497(int line, struct operandarray *ops) {
   insn_fmovsne_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_498(int line, struct operandarray *ops) {
   insn_fmovdne_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_499(int line, struct operandarray *ops) {
   insn_fmovqne_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_500(int line, struct operandarray *ops) {
   insn_fmovse_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_501(int line, struct operandarray *ops) {
   insn_fmovde_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_502(int line, struct operandarray *ops) {
   insn_fmovqe_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_503(int line, struct operandarray *ops) {
   insn_fmovsg_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_504(int line, struct operandarray *ops) {
   insn_fmovdg_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_505(int line, struct operandarray *ops) {
   insn_fmovqg_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_506(int line, struct operandarray *ops) {
   insn_fmovsle_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_507(int line, struct operandarray *ops) {
   insn_fmovdle_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_508(int line, struct operandarray *ops) {
   insn_fmovqle_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_509(int line, struct operandarray *ops) {
   insn_fmovsge_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_510(int line, struct operandarray *ops) {
   insn_fmovdge_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_511(int line, struct operandarray *ops) {
   insn_fmovqge_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_512(int line, struct operandarray *ops) {
   insn_fmovsl_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_513(int line, struct operandarray *ops) {
   insn_fmovdl_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_514(int line, struct operandarray *ops) {
   insn_fmovql_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_515(int line, struct operandarray *ops) {
   insn_fmovsgu_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_516(int line, struct operandarray *ops) {
   insn_fmovdgu_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_517(int line, struct operandarray *ops) {
   insn_fmovqgu_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_518(int line, struct operandarray *ops) {
   insn_fmovsleu_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_519(int line, struct operandarray *ops) {
   insn_fmovdleu_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_520(int line, struct operandarray *ops) {
   insn_fmovqleu_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_521(int line, struct operandarray *ops) {
   insn_fmovscc_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_522(int line, struct operandarray *ops) {
   insn_fmovdcc_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_523(int line, struct operandarray *ops) {
   insn_fmovqcc_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_524(int line, struct operandarray *ops) {
   insn_fmovscs_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_525(int line, struct operandarray *ops) {
   insn_fmovdcs_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_526(int line, struct operandarray *ops) {
   insn_fmovqcs_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_527(int line, struct operandarray *ops) {
   insn_fmovspos_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_528(int line, struct operandarray *ops) {
   insn_fmovdpos_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_529(int line, struct operandarray *ops) {
   insn_fmovqpos_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_530(int line, struct operandarray *ops) {
   insn_fmovsneg_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_531(int line, struct operandarray *ops) {
   insn_fmovdneg_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_532(int line, struct operandarray *ops) {
   insn_fmovqneg_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_533(int line, struct operandarray *ops) {
   insn_fmovsvc_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_534(int line, struct operandarray *ops) {
   insn_fmovdvc_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_535(int line, struct operandarray *ops) {
   insn_fmovqvc_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_536(int line, struct operandarray *ops) {
   insn_fmovsvs_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_537(int line, struct operandarray *ops) {
   insn_fmovdvs_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_538(int line, struct operandarray *ops) {
   insn_fmovqvs_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_539(int line, struct operandarray *ops) {
   insn_fmovsnz_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_540(int line, struct operandarray *ops) {
   insn_fmovdnz_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_541(int line, struct operandarray *ops) {
   insn_fmovqnz_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_542(int line, struct operandarray *ops) {
   insn_fmovsz_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_543(int line, struct operandarray *ops) {
   insn_fmovdz_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_544(int line, struct operandarray *ops) {
   insn_fmovqz_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_545(int line, struct operandarray *ops) {
   insn_fmovsgeu_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_546(int line, struct operandarray *ops) {
   insn_fmovdgeu_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_547(int line, struct operandarray *ops) {
   insn_fmovqgeu_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_548(int line, struct operandarray *ops) {
   insn_fmovslu_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_549(int line, struct operandarray *ops) {
   insn_fmovdlu_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_550(int line, struct operandarray *ops) {
   insn_fmovqlu_icc_freg_freg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_551(int line, struct operandarray *ops) {
   insn_fmovsa_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_552(int line, struct operandarray *ops) {
   insn_fmovda_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_553(int line, struct operandarray *ops) {
   insn_fmovqa_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_554(int line, struct operandarray *ops) {
   insn_fmovsn_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_555(int line, struct operandarray *ops) {
   insn_fmovdn_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_556(int line, struct operandarray *ops) {
   insn_fmovqn_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_557(int line, struct operandarray *ops) {
   insn_fmovsu_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_558(int line, struct operandarray *ops) {
   insn_fmovdu_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_559(int line, struct operandarray *ops) {
   insn_fmovqu_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_560(int line, struct operandarray *ops) {
   insn_fmovsg_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_561(int line, struct operandarray *ops) {
   insn_fmovdg_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_562(int line, struct operandarray *ops) {
   insn_fmovqg_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_563(int line, struct operandarray *ops) {
   insn_fmovsug_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_564(int line, struct operandarray *ops) {
   insn_fmovdug_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_565(int line, struct operandarray *ops) {
   insn_fmovqug_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_566(int line, struct operandarray *ops) {
   insn_fmovsl_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_567(int line, struct operandarray *ops) {
   insn_fmovdl_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_568(int line, struct operandarray *ops) {
   insn_fmovql_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_569(int line, struct operandarray *ops) {
   insn_fmovsul_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_570(int line, struct operandarray *ops) {
   insn_fmovdul_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_571(int line, struct operandarray *ops) {
   insn_fmovqul_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_572(int line, struct operandarray *ops) {
   insn_fmovslg_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_573(int line, struct operandarray *ops) {
   insn_fmovdlg_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_574(int line, struct operandarray *ops) {
   insn_fmovqlg_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_575(int line, struct operandarray *ops) {
   insn_fmovsne_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_576(int line, struct operandarray *ops) {
   insn_fmovdne_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_577(int line, struct operandarray *ops) {
   insn_fmovqne_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_578(int line, struct operandarray *ops) {
   insn_fmovse_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_579(int line, struct operandarray *ops) {
   insn_fmovde_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_580(int line, struct operandarray *ops) {
   insn_fmovqe_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_581(int line, struct operandarray *ops) {
   insn_fmovsue_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_582(int line, struct operandarray *ops) {
   insn_fmovdue_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_583(int line, struct operandarray *ops) {
   insn_fmovque_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_584(int line, struct operandarray *ops) {
   insn_fmovsge_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_585(int line, struct operandarray *ops) {
   insn_fmovdge_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_586(int line, struct operandarray *ops) {
   insn_fmovqge_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_587(int line, struct operandarray *ops) {
   insn_fmovsuge_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_588(int line, struct operandarray *ops) {
   insn_fmovduge_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_589(int line, struct operandarray *ops) {
   insn_fmovquge_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_590(int line, struct operandarray *ops) {
   insn_fmovsle_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_591(int line, struct operandarray *ops) {
   insn_fmovdle_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_592(int line, struct operandarray *ops) {
   insn_fmovqle_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_593(int line, struct operandarray *ops) {
   insn_fmovsule_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_594(int line, struct operandarray *ops) {
   insn_fmovdule_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_595(int line, struct operandarray *ops) {
   insn_fmovqule_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_596(int line, struct operandarray *ops) {
   insn_fmovso_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_597(int line, struct operandarray *ops) {
   insn_fmovdo_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_598(int line, struct operandarray *ops) {
   insn_fmovqo_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_599(int line, struct operandarray *ops) {
   insn_fmovsnz_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_600(int line, struct operandarray *ops) {
   insn_fmovdnz_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_601(int line, struct operandarray *ops) {
   insn_fmovqnz_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_602(int line, struct operandarray *ops) {
   insn_fmovsz_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_603(int line, struct operandarray *ops) {
   insn_fmovdz_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_604(int line, struct operandarray *ops) {
   insn_fmovqz_fcc_freg_freg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_605(int line, struct operandarray *ops) {
   insn_fmovrsz_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_606(int line, struct operandarray *ops) {
   insn_fmovrdz_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_607(int line, struct operandarray *ops) {
   insn_fmovrqz_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_608(int line, struct operandarray *ops) {
   insn_fmovrslez_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_609(int line, struct operandarray *ops) {
   insn_fmovrdlez_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_610(int line, struct operandarray *ops) {
   insn_fmovrqlez_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_611(int line, struct operandarray *ops) {
   insn_fmovrslz_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_612(int line, struct operandarray *ops) {
   insn_fmovrdlz_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_613(int line, struct operandarray *ops) {
   insn_fmovrqlz_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_614(int line, struct operandarray *ops) {
   insn_fmovrsnz_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_615(int line, struct operandarray *ops) {
   insn_fmovrdnz_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_616(int line, struct operandarray *ops) {
   insn_fmovrqnz_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_617(int line, struct operandarray *ops) {
   insn_fmovrsg_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_618(int line, struct operandarray *ops) {
   insn_fmovrdg_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_619(int line, struct operandarray *ops) {
   insn_fmovrqg_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_620(int line, struct operandarray *ops) {
   insn_fmovrsgez_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_621(int line, struct operandarray *ops) {
   insn_fmovrdgez_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_622(int line, struct operandarray *ops) {
   insn_fmovrqgez_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_623(int line, struct operandarray *ops) {
   insn_fmovrse_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_624(int line, struct operandarray *ops) {
   insn_fmovrde_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_625(int line, struct operandarray *ops) {
   insn_fmovrqe_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_626(int line, struct operandarray *ops) {
   insn_fmovrsne_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_627(int line, struct operandarray *ops) {
   insn_fmovrdne_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_628(int line, struct operandarray *ops) {
   insn_fmovrqne_reg_freg_freg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_freg, operandarray_get(ops, 2)->val_freg);
}

static void call_629(int line, struct operandarray *ops) {
   insn_mova_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_630(int line, struct operandarray *ops) {
   insn_mova_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_631(int line, struct operandarray *ops) {
   insn_movn_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_632(int line, struct operandarray *ops) {
   insn_movn_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_633(int line, struct operandarray *ops) {
   insn_movne_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_634(int line, struct operandarray *ops) {
   insn_movne_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_635(int line, struct operandarray *ops) {
   insn_move_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_636(int line, struct operandarray *ops) {
   insn_move_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_637(int line, struct operandarray *ops) {
   insn_movg_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_638(int line, struct operandarray *ops) {
   insn_movg_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_639(int line, struct operandarray *ops) {
   insn_movle_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_640(int line, struct operandarray *ops) {
   insn_movle_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_641(int line, struct operandarray *ops) {
   insn_movge_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_642(int line, struct operandarray *ops) {
   insn_movge_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_643(int line, struct operandarray *ops) {
   insn_movl_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_644(int line, struct operandarray *ops) {
   insn_movl_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_645(int line, struct operandarray *ops) {
   insn_movgu_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_646(int line, struct operandarray *ops) {
   insn_movgu_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_647(int line, struct operandarray *ops) {
   insn_movleu_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_648(int line, struct operandarray *ops) {
   insn_movleu_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_649(int line, struct operandarray *ops) {
   insn_movcc_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_650(int line, struct operandarray *ops) {
   insn_movcc_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_651(int line, struct operandarray *ops) {
   insn_movcs_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_652(int line, struct operandarray *ops) {
   insn_movcs_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_653(int line, struct operandarray *ops) {
   insn_movpos_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_654(int line, struct operandarray *ops) {
   insn_movpos_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_655(int line, struct operandarray *ops) {
   insn_movneg_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_656(int line, struct operandarray *ops) {
   insn_movneg_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_657(int line, struct operandarray *ops) {
   insn_movvc_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_658(int line, struct operandarray *ops) {
   insn_movvc_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_659(int line, struct operandarray *ops) {
   insn_movvs_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_660(int line, struct operandarray *ops) {
   insn_movvs_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_661(int line, struct operandarray *ops) {
   insn_movnz_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_662(int line, struct operandarray *ops) {
   insn_movnz_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_663(int line, struct operandarray *ops) {
   insn_movz_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_664(int line, struct operandarray *ops) {
   insn_movz_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_665(int line, struct operandarray *ops) {
   insn_movgeu_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_666(int line, struct operandarray *ops) {
   insn_movgeu_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_667(int line, struct operandarray *ops) {
   insn_movlu_icc_reg_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_668(int line, struct operandarray *ops) {
   insn_movlu_icc_i11num_reg(line, operandarray_get(ops, 0)->val_icc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_669(int line, struct operandarray *ops) {
   insn_mova_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_670(int line, struct operandarray *ops) {
   insn_mova_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_671(int line, struct operandarray *ops) {
   insn_movn_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_672(int line, struct operandarray *ops) {
   insn_movn_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_673(int line, struct operandarray *ops) {
   insn_movu_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_674(int line, struct operandarray *ops) {
   insn_movu_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_675(int line, struct operandarray *ops) {
   insn_movg_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_676(int line, struct operandarray *ops) {
   insn_movg_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_677(int line, struct operandarray *ops) {
   insn_movug_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_678(int line, struct operandarray *ops) {
   insn_movug_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_679(int line, struct operandarray *ops) {
   insn_movl_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_680(int line, struct operandarray *ops) {
   insn_movl_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_681(int line, struct operandarray *ops) {
   insn_movul_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_682(int line, struct operandarray *ops) {
   insn_movul_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_683(int line, struct operandarray *ops) {
   insn_movlg_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_684(int line, struct operandarray *ops) {
   insn_movlg_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_685(int line, struct operandarray *ops) {
   insn_movne_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_686(int line, struct operandarray *ops) {
   insn_movne_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_687(int line, struct operandarray *ops) {
   insn_move_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_688(int line, struct operandarray *ops) {
   insn_move_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_689(int line, struct operandarray *ops) {
   insn_movue_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_690(int line, struct operandarray *ops) {
   insn_movue_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_691(int line, struct operandarray *ops) {
   insn_movge_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_692(int line, struct operandarray *ops) {
   insn_movge_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_693(int line, struct operandarray *ops) {
   insn_movuge_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_694(int line, struct operandarray *ops) {
   insn_movuge_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_695(int line, struct operandarray *ops) {
   insn_movle_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_696(int line, struct operandarray *ops) {
   insn_movle_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_697(int line, struct operandarray *ops) {
   insn_movule_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_698(int line, struct operandarray *ops) {
   insn_movule_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_699(int line, struct operandarray *ops) {
   insn_movo_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_700(int line, struct operandarray *ops) {
   insn_movo_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_701(int line, struct operandarray *ops) {
   insn_movnz_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_702(int line, struct operandarray *ops) {
   insn_movnz_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_703(int line, struct operandarray *ops) {
   insn_movz_fcc_reg_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_704(int line, struct operandarray *ops) {
   insn_movz_fcc_i11num_reg(line, operandarray_get(ops, 0)->val_fcc, operandarray_get(ops, 1)->val_i11num, operandarray_get(ops, 2)->val_reg);
}

static void call_705(int line, struct operandarray *ops) {
   insn_movrz_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_706(int line, struct operandarray *ops) {
   insn_movrz_reg_i10num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i10num, operandarray_get(ops, 2)->val_reg);
}

static void call_707(int line, struct operandarray *ops) {
   insn_movrlez_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_708(int line, struct operandarray *ops) {
   insn_movrlez_reg_i10num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i10num, operandarray_get(ops, 2)->val_reg);
}

static void call_709(int line, struct operandarray *ops) {
   insn_movrlz_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_710(int line, struct operandarray *ops) {
   insn_movrlz_reg_i10num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i10num, operandarray_get(ops, 2)->val_reg);
}

static void call_711(int line, struct operandarray *ops) {
   insn_movrnz_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_712(int line, struct operandarray *ops) {
   insn_movrnz_reg_i10num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i10num, operandarray_get(ops, 2)->val_reg);
}

static void call_713(int line, struct operandarray *ops) {
   insn_movrgz_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_714(int line, struct operandarray *ops) {
   insn_movrgz_reg_i10num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i10num, operandarray_get(ops, 2)->val_reg);
}

static void call_715(int line, struct operandarray *ops) {
   insn_movrgez_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_716(int line, struct operandarray *ops) {
   insn_movrgez_reg_i10num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i10num, operandarray_get(ops, 2)->val_reg);
}

static void call_717(int line, struct operandarray *ops) {
   insn_movre_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_718(int line, struct operandarray *ops) {
   insn_movre_reg_i10num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i10num, operandarray_get(ops, 2)->val_reg);
}

static void call_719(int line, struct operandarray *ops) {
   insn_movrne_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_720(int line, struct operandarray *ops) {
   insn_movrne_reg_i10num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i10num, operandarray_get(ops, 2)->val_reg);
}

static void call_721(int line, struct operandarray *ops) {
   insn_membar_membarmask(line, operandarray_get(ops, 0)->val_membarmask);
}

static void call_722(int line, struct operandarray *ops) {
   (void)ops;
   insn_stbar_(line);
}

static void call_723(int line, struct operandarray *ops) {
   insn_flush_addr_rr(line, &operandarray_get(ops, 0)->val_addr_rr);
}

static void call_724(int line, struct operandarray *ops) {
   insn_flush_addr_ri(line, &operandarray_get(ops, 0)->val_addr_ri);
}

static void call_725(int line, struct operandarray *ops) {
   insn_prefetch_braddr_rr_u5num(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_u5num);
}

static void call_726(int line, struct operandarray *ops) {
   insn_prefetch_braddr_ri_u5num(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_u5num);
}

static void call_727(int line, struct operandarray *ops) {
   insn_prefetcha_braddr_rr_immasi_u5num(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_u5num);
}

static void call_728(int line, struct operandarray *ops) {
   insn_prefetcha_braddr_ri_asi_u5num(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_u5num);
}

static void call_729(int line, struct operandarray *ops) {
   insn_casa_braddr_r_immasi_reg_reg(line, &operandarray_get(ops, 0)->val_braddr_r_immasi, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_730(int line, struct operandarray *ops) {
   insn_casa_braddr_r_asi_reg_reg(line, &operandarray_get(ops, 0)->val_braddr_r_asi, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_731(int line, struct operandarray *ops) {
   insn_casxa_braddr_r_immasi_reg_reg(line, &operandarray_get(ops, 0)->val_braddr_r_immasi, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_732(int line, struct operandarray *ops) {
   insn_casxa_braddr_r_asi_reg_reg(line, &operandarray_get(ops, 0)->val_braddr_r_asi, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_733(int line, struct operandarray *ops) {
   insn_ldstub_braddr_rr_reg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_734(int line, struct operandarray *ops) {
   insn_ldstub_braddr_ri_reg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_735(int line, struct operandarray *ops) {
   insn_ldstub_braddr_rx_reg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_reg);
}

static void call_736(int line, struct operandarray *ops) {
   insn_ldstuba_braddr_rr_immasi_reg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_reg);
}

static void call_737(int line, struct operandarray *ops) {
   insn_ldstuba_braddr_ri_asi_reg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_reg);
}

static void call_738(int line, struct operandarray *ops) {
   insn_swap_braddr_rr_reg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_739(int line, struct operandarray *ops) {
   insn_swap_braddr_ri_reg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_740(int line, struct operandarray *ops) {
   insn_swapa_braddr_rr_immasi_reg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_reg);
}

static void call_741(int line, struct operandarray *ops) {
   insn_swapa_braddr_ri_asi_reg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_reg);
}

static void call_742(int line, struct operandarray *ops) {
   insn_ld_braddr_rr_freg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_freg);
}

static void call_743(int line, struct operandarray *ops) {
   insn_ld_braddr_ri_freg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_freg);
}

static void call_744(int line, struct operandarray *ops) {
   insn_ld_braddr_rx_freg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_freg);
}

static void call_745(int line, struct operandarray *ops) {
   insn_ldd_braddr_rr_freg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_freg);
}

static void call_746(int line, struct operandarray *ops) {
   insn_ldd_braddr_ri_freg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_freg);
}

static void call_747(int line, struct operandarray *ops) {
   insn_ldd_braddr_rx_freg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_freg);
}

static void call_748(int line, struct operandarray *ops) {
   insn_ldq_braddr_rr_freg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_freg);
}

static void call_749(int line, struct operandarray *ops) {
   insn_ldq_braddr_ri_freg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_freg);
}

static void call_750(int line, struct operandarray *ops) {
   insn_ldq_braddr_rx_freg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_freg);
}

static void call_751(int line, struct operandarray *ops) {
   insn_ld_braddr_rr_fsr(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_fsr);
}

static void call_752(int line, struct operandarray *ops) {
   insn_ld_braddr_ri_fsr(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_fsr);
}

static void call_753(int line, struct operandarray *ops) {
   insn_ld_braddr_rx_fsr(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_fsr);
}

static void call_754(int line, struct operandarray *ops) {
   insn_ldx_braddr_rr_fsr(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_fsr);
}

static void call_755(int line, struct operandarray *ops) {
   insn_ldx_braddr_ri_fsr(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_fsr);
}

static void call_756(int line, struct operandarray *ops) {
   insn_ldx_braddr_rx_fsr(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_fsr);
}

static void call_757(int line, struct operandarray *ops) {
   insn_lda_braddr_rr_immasi_freg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_freg);
}

static void call_758(int line, struct operandarray *ops) {
   insn_lda_braddr_ri_asi_freg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_freg);
}

static void call_759(int line, struct operandarray *ops) {
   insn_ldda_braddr_rr_immasi_freg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_freg);
}

static void call_760(int line, struct operandarray *ops) {
   insn_ldda_braddr_ri_asi_freg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_freg);
}

static void call_761(int line, struct operandarray *ops) {
   insn_ldqa_braddr_rr_immasi_freg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_freg);
}

static void call_762(int line, struct operandarray *ops) {
   insn_ldqa_braddr_ri_asi_freg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_freg);
}

static void call_763(int line, struct operandarray *ops) {
   insn_ldsb_braddr_rr_reg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_764(int line, struct operandarray *ops) {
   insn_ldsb_braddr_ri_reg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_765(int line, struct operandarray *ops) {
   insn_ldsb_braddr_rx_reg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_reg);
}

static void call_766(int line, struct operandarray *ops) {
   insn_ldsh_braddr_rr_reg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_767(int line, struct operandarray *ops) {
   insn_ldsh_braddr_ri_reg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_768(int line, struct operandarray *ops) {
   insn_ldsh_braddr_rx_reg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_reg);
}

static void call_769(int line, struct operandarray *ops) {
   insn_ldsw_braddr_rr_reg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_770(int line, struct operandarray *ops) {
   insn_ldsw_braddr_ri_reg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_771(int line, struct operandarray *ops) {
   insn_ldsw_braddr_rx_reg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_reg);
}

static void call_772(int line, struct operandarray *ops) {
   insn_ldub_braddr_rr_reg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_773(int line, struct operandarray *ops) {
   insn_ldub_braddr_ri_reg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_774(int line, struct operandarray *ops) {
   insn_ldub_braddr_rx_reg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_reg);
}

static void call_775(int line, struct operandarray *ops) {
   insn_lduh_braddr_rr_reg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_776(int line, struct operandarray *ops) {
   insn_lduh_braddr_ri_reg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_777(int line, struct operandarray *ops) {
   insn_lduh_braddr_rx_reg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_reg);
}

static void call_778(int line, struct operandarray *ops) {
   insn_lduw_braddr_rr_reg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_779(int line, struct operandarray *ops) {
   insn_lduw_braddr_ri_reg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_780(int line, struct operandarray *ops) {
   insn_lduw_braddr_rx_reg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_reg);
}

static void call_781(int line, struct operandarray *ops) {
   insn_ldx_braddr_rr_reg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_782(int line, struct operandarray *ops) {
   insn_ldx_braddr_ri_reg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_783(int line, struct operandarray *ops) {
   insn_ldx_braddr_rx_reg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_reg);
}

static void call_784(int line, struct operandarray *ops) {
   insn_ldd_braddr_rr_reg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_785(int line, struct operandarray *ops) {
   insn_ldd_braddr_ri_reg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_786(int line, struct operandarray *ops) {
   insn_ldd_braddr_rx_reg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_reg);
}

static void call_787(int line, struct operandarray *ops) {
   insn_ld_braddr_rr_reg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_788(int line, struct operandarray *ops) {
   insn_ld_braddr_ri_reg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_789(int line, struct operandarray *ops) {
   insn_ld_braddr_rx_reg(line, &operandarray_get(ops, 0)->val_braddr_rx, operandarray_get(ops, 1)->val_reg);
}

static void call_790(int line, struct operandarray *ops) {
   insn_ldsba_braddr_rr_immasi_reg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_reg);
}

static void call_791(int line, struct operandarray *ops) {
   insn_ldsba_braddr_ri_asi_reg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_reg);
}

static void call_792(int line, struct operandarray *ops) {
   insn_ldsha_braddr_rr_immasi_reg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_reg);
}

static void call_793(int line, struct operandarray *ops) {
   insn_ldsha_braddr_ri_asi_reg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_reg);
}

static void call_794(int line, struct operandarray *ops) {
   insn_ldswa_braddr_rr_immasi_reg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_reg);
}

static void call_795(int line, struct operandarray *ops) {
   insn_ldswa_braddr_ri_asi_reg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_reg);
}

static void call_796(int line, struct operandarray *ops) {
   insn_lduba_braddr_rr_immasi_reg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_reg);
}

static void call_797(int line, struct operandarray *ops) {
   insn_lduba_braddr_ri_asi_reg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_reg);
}

static void call_798(int line, struct operandarray *ops) {
   insn_lduha_braddr_rr_immasi_reg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_reg);
}

static void call_799(int line, struct operandarray *ops) {
   insn_lduha_braddr_ri_asi_reg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_reg);
}

static void call_800(int line, struct operandarray *ops) {
   insn_lduwa_braddr_rr_immasi_reg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_reg);
}

static void call_801(int line, struct operandarray *ops) {
   insn_lduwa_braddr_ri_asi_reg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_reg);
}

static void call_802(int line, struct operandarray *ops) {
   insn_ldxa_braddr_rr_immasi_reg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_reg);
}

static void call_803(int line, struct operandarray *ops) {
   insn_ldxa_braddr_ri_asi_reg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_reg);
}

static void call_804(int line, struct operandarray *ops) {
   insn_ldda_braddr_rr_immasi_reg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_reg);
}

static void call_805(int line, struct operandarray *ops) {
   insn_ldda_braddr_ri_asi_reg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_reg);
}

static void call_806(int line, struct operandarray *ops) {
   insn_lda_braddr_rr_immasi_reg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_reg);
}

static void call_807(int line, struct operandarray *ops) {
   insn_lda_braddr_ri_asi_reg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_reg);
}

static void call_808(int line, struct operandarray *ops) {
   insn_st_freg_braddr_rr(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_809(int line, struct operandarray *ops) {
   insn_st_freg_braddr_ri(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_810(int line, struct operandarray *ops) {
   insn_st_freg_braddr_rx(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_811(int line, struct operandarray *ops) {
   insn_std_freg_braddr_rr(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_812(int line, struct operandarray *ops) {
   insn_std_freg_braddr_ri(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_813(int line, struct operandarray *ops) {
   insn_std_freg_braddr_rx(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_814(int line, struct operandarray *ops) {
   insn_stq_freg_braddr_rr(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_815(int line, struct operandarray *ops) {
   insn_stq_freg_braddr_ri(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_816(int line, struct operandarray *ops) {
   insn_stq_freg_braddr_rx(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_817(int line, struct operandarray *ops) {
   insn_st_fsr_braddr_rr(line, operandarray_get(ops, 0)->val_fsr, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_818(int line, struct operandarray *ops) {
   insn_st_fsr_braddr_ri(line, operandarray_get(ops, 0)->val_fsr, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_819(int line, struct operandarray *ops) {
   insn_st_fsr_braddr_rx(line, operandarray_get(ops, 0)->val_fsr, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_820(int line, struct operandarray *ops) {
   insn_stx_fsr_braddr_rr(line, operandarray_get(ops, 0)->val_fsr, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_821(int line, struct operandarray *ops) {
   insn_stx_fsr_braddr_ri(line, operandarray_get(ops, 0)->val_fsr, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_822(int line, struct operandarray *ops) {
   insn_stx_fsr_braddr_rx(line, operandarray_get(ops, 0)->val_fsr, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_823(int line, struct operandarray *ops) {
   insn_sta_freg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_824(int line, struct operandarray *ops) {
   insn_sta_freg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_825(int line, struct operandarray *ops) {
   insn_stda_freg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_826(int line, struct operandarray *ops) {
   insn_stda_freg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_827(int line, struct operandarray *ops) {
   insn_stqa_freg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_828(int line, struct operandarray *ops) {
   insn_stqa_freg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_freg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_829(int line, struct operandarray *ops) {
   insn_stb_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_830(int line, struct operandarray *ops) {
   insn_stb_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_831(int line, struct operandarray *ops) {
   insn_stb_reg_braddr_rx(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_832(int line, struct operandarray *ops) {
   insn_sth_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_833(int line, struct operandarray *ops) {
   insn_sth_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_834(int line, struct operandarray *ops) {
   insn_sth_reg_braddr_rx(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_835(int line, struct operandarray *ops) {
   insn_stw_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_836(int line, struct operandarray *ops) {
   insn_stw_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_837(int line, struct operandarray *ops) {
   insn_stw_reg_braddr_rx(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_838(int line, struct operandarray *ops) {
   insn_stx_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_839(int line, struct operandarray *ops) {
   insn_stx_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_840(int line, struct operandarray *ops) {
   insn_stx_reg_braddr_rx(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_841(int line, struct operandarray *ops) {
   insn_std_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_842(int line, struct operandarray *ops) {
   insn_std_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_843(int line, struct operandarray *ops) {
   insn_std_reg_braddr_rx(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_844(int line, struct operandarray *ops) {
   insn_stsb_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_845(int line, struct operandarray *ops) {
   insn_stsb_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_846(int line, struct operandarray *ops) {
   insn_stsb_reg_braddr_rx(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_847(int line, struct operandarray *ops) {
   insn_stub_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_848(int line, struct operandarray *ops) {
   insn_stub_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_849(int line, struct operandarray *ops) {
   insn_stub_reg_braddr_rx(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_850(int line, struct operandarray *ops) {
   insn_stsh_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_851(int line, struct operandarray *ops) {
   insn_stsh_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_852(int line, struct operandarray *ops) {
   insn_stsh_reg_braddr_rx(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_853(int line, struct operandarray *ops) {
   insn_stuh_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_854(int line, struct operandarray *ops) {
   insn_stuh_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_855(int line, struct operandarray *ops) {
   insn_stuh_reg_braddr_rx(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_856(int line, struct operandarray *ops) {
   insn_st_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_857(int line, struct operandarray *ops) {
   insn_st_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_858(int line, struct operandarray *ops) {
   insn_st_reg_braddr_rx(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_859(int line, struct operandarray *ops) {
   insn_stsw_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_860(int line, struct operandarray *ops) {
   insn_stsw_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_861(int line, struct operandarray *ops) {
   insn_stsw_reg_braddr_rx(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_862(int line, struct operandarray *ops) {
   insn_stuw_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_863(int line, struct operandarray *ops) {
   insn_stuw_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_864(int line, struct operandarray *ops) {
   insn_stuw_reg_braddr_rx(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rx);
}

static void call_865(int line, struct operandarray *ops) {
   insn_stba_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_866(int line, struct operandarray *ops) {
   insn_stba_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_867(int line, struct operandarray *ops) {
   insn_stha_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_868(int line, struct operandarray *ops) {
   insn_stha_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_869(int line, struct operandarray *ops) {
   insn_stwa_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_870(int line, struct operandarray *ops) {
   insn_stwa_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_871(int line, struct operandarray *ops) {
   insn_stxa_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_872(int line, struct operandarray *ops) {
   insn_stxa_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_873(int line, struct operandarray *ops) {
   insn_stda_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_874(int line, struct operandarray *ops) {
   insn_stda_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_875(int line, struct operandarray *ops) {
   insn_stsba_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_876(int line, struct operandarray *ops) {
   insn_stsba_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_877(int line, struct operandarray *ops) {
   insn_stuba_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_878(int line, struct operandarray *ops) {
   insn_stuba_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_879(int line, struct operandarray *ops) {
   insn_stsha_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_880(int line, struct operandarray *ops) {
   insn_stsha_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_881(int line, struct operandarray *ops) {
   insn_stuha_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_882(int line, struct operandarray *ops) {
   insn_stuha_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_883(int line, struct operandarray *ops) {
   insn_stswa_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_884(int line, struct operandarray *ops) {
   insn_stswa_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_885(int line, struct operandarray *ops) {
   insn_stuwa_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_886(int line, struct operandarray *ops) {
   insn_stuwa_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_887(int line, struct operandarray *ops) {
   insn_sta_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_888(int line, struct operandarray *ops) {
   insn_sta_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_889(int line, struct operandarray *ops) {
   insn_call_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_890(int line, struct operandarray *ops) {
   insn_call_symbol_number(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number);
}

static void call_891(int line, struct operandarray *ops) {
   insn_jmpl_addr_rr_reg(line, &operandarray_get(ops, 0)->val_addr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_892(int line, struct operandarray *ops) {
   insn_jmpl_addr_ri_reg(line, &operandarray_get(ops, 0)->val_addr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_893(int line, struct operandarray *ops) {
   insn_return_addr_rr(line, &operandarray_get(ops, 0)->val_addr_rr);
}

static void call_894(int line, struct operandarray *ops) {
   insn_return_addr_ri(line, &operandarray_get(ops, 0)->val_addr_ri);
}

static void call_895(int line, struct operandarray *ops) {
   insn_illtrap_u22num(line, operandarray_get(ops, 0)->val_u22num);
}

static void call_896(int line, struct operandarray *ops) {
   insn_sir_i13num(line, operandarray_get(ops, 0)->val_i13num);
}

static void call_897(int line, struct operandarray *ops) {
   insn_ta_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_898(int line, struct operandarray *ops) {
   insn_ta_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_899(int line, struct operandarray *ops) {
   insn_tn_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_900(int line, struct operandarray *ops) {
   insn_tn_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_901(int line, struct operandarray *ops) {
   insn_tne_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_902(int line, struct operandarray *ops) {
   insn_tne_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_903(int line, struct operandarray *ops) {
   insn_te_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_904(int line, struct operandarray *ops) {
   insn_te_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_905(int line, struct operandarray *ops) {
   insn_tg_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_906(int line, struct operandarray *ops) {
   insn_tg_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_907(int line, struct operandarray *ops) {
   insn_tle_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_908(int line, struct operandarray *ops) {
   insn_tle_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_909(int line, struct operandarray *ops) {
   insn_tge_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_910(int line, struct operandarray *ops) {
   insn_tge_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_911(int line, struct operandarray *ops) {
   insn_tl_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_912(int line, struct operandarray *ops) {
   insn_tl_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_913(int line, struct operandarray *ops) {
   insn_tgu_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_914(int line, struct operandarray *ops) {
   insn_tgu_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_915(int line, struct operandarray *ops) {
   insn_tleu_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_916(int line, struct operandarray *ops) {
   insn_tleu_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_917(int line, struct operandarray *ops) {
   insn_tcc_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_918(int line, struct operandarray *ops) {
   insn_tcc_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_919(int line, struct operandarray *ops) {
   insn_tcs_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_920(int line, struct operandarray *ops) {
   insn_tcs_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_921(int line, struct operandarray *ops) {
   insn_tpos_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_922(int line, struct operandarray *ops) {
   insn_tpos_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_923(int line, struct operandarray *ops) {
   insn_tneg_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_924(int line, struct operandarray *ops) {
   insn_tneg_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_925(int line, struct operandarray *ops) {
   insn_tvc_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_926(int line, struct operandarray *ops) {
   insn_tvc_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_927(int line, struct operandarray *ops) {
   insn_tvs_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_928(int line, struct operandarray *ops) {
   insn_tvs_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_929(int line, struct operandarray *ops) {
   insn_tnz_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_930(int line, struct operandarray *ops) {
   insn_tnz_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_931(int line, struct operandarray *ops) {
   insn_tz_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_932(int line, struct operandarray *ops) {
   insn_tz_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_933(int line, struct operandarray *ops) {
   insn_tgeu_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_934(int line, struct operandarray *ops) {
   insn_tgeu_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_935(int line, struct operandarray *ops) {
   insn_tlu_icc_trapnum_rr(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_rr);
}

static void call_936(int line, struct operandarray *ops) {
   insn_tlu_icc_trapnum_ri(line, operandarray_get(ops, 0)->val_icc, &operandarray_get(ops, 1)->val_trapnum_ri);
}

static void call_937(int line, struct operandarray *ops) {
   (void)ops;
   insn_nop_(line);
}

static void call_938(int line, struct operandarray *ops) {
   insn_rd_asr_reg(line, operandarray_get(ops, 0)->val_asr, operandarray_get(ops, 1)->val_reg);
}

static void call_939(int line, struct operandarray *ops) {
   insn_wr_reg_reg_asr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_asr);
}

static void call_940(int line, struct operandarray *ops) {
   insn_wr_reg_i13num_asr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_asr);
}

static void call_941(int line, struct operandarray *ops) {
   insn_impl1_u5num_u19num(line, operandarray_get(ops, 0)->val_u5num, operandarray_get(ops, 1)->val_u19num);
}

static void call_942(int line, struct operandarray *ops) {
   insn_impl2_u5num_u19num(line, operandarray_get(ops, 0)->val_u5num, operandarray_get(ops, 1)->val_u19num);
}

static void call_943(int line, struct operandarray *ops) {
   insn_rdpr_pr_reg(line, operandarray_get(ops, 0)->val_pr, operandarray_get(ops, 1)->val_reg);
}

static void call_944(int line, struct operandarray *ops) {
   insn_wrpr_reg_reg_pr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_pr);
}

static void call_945(int line, struct operandarray *ops) {
   insn_wrpr_reg_i13num_pr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num, operandarray_get(ops, 2)->val_pr);
}

static void call_946(int line, struct operandarray *ops) {
   (void)ops;
   insn_done_(line);
}

static void call_947(int line, struct operandarray *ops) {
   (void)ops;
   insn_retry_(line);
}

static void call_948(int line, struct operandarray *ops) {
   (void)ops;
   insn_flushw_(line);
}

static void call_949(int line, struct operandarray *ops) {
   (void)ops;
   insn_saved_(line);
}

static void call_950(int line, struct operandarray *ops) {
   (void)ops;
   insn_restored_(line);
}

static void call_951(int line, struct operandarray *ops) {
   insn_cmp_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_952(int line, struct operandarray *ops) {
   insn_cmp_reg_i13num(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_i13num);
}

static void call_953(int line, struct operandarray *ops) {
   insn_jmp_addr_rr(line, &operandarray_get(ops, 0)->val_addr_rr);
}

static void call_954(int line, struct operandarray *ops) {
   insn_jmp_addr_ri(line, &operandarray_get(ops, 0)->val_addr_ri);
}

static void call_955(int line, struct operandarray *ops) {
   insn_call_addr_rr(line, &operandarray_get(ops, 0)->val_addr_rr);
}

static void call_956(int line, struct operandarray *ops) {
   insn_call_addr_ri(line, &operandarray_get(ops, 0)->val_addr_ri);
}

static void call_957(int line, struct operandarray *ops) {
   insn_call_addr_rr_number(line, &operandarray_get(ops, 0)->val_addr_rr, operandarray_get(ops, 1)->val_number);
}

static void call_958(int line, struct operandarray *ops) {
   insn_call_addr_ri_number(line, &operandarray_get(ops, 0)->val_addr_ri, operandarray_get(ops, 1)->val_number);
}

static void call_959(int line, struct operandarray *ops) {
   (void)ops;
   insn_ret_(line);
}

static void call_960(int line, struct operandarray *ops) {
   (void)ops;
   insn_retl_(line);
}

static void call_961(int line, struct operandarray *ops) {
   (void)ops;
   insn_save_(line);
}

static void call_962(int line, struct operandarray *ops) {
   (void)ops;
   insn_restore_(line);
}

static void call_963(int line, struct operandarray *ops) {
   insn_iprefetch_symbol(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_964(int line, struct operandarray *ops) {
   insn_tst_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_965(int line, struct operandarray *ops) {
   insn_setuw_u32num_reg(line, operandarray_get(ops, 0)->val_u32num, operandarray_get(ops, 1)->val_reg);
}

static void call_966(int line, struct operandarray *ops) {
   insn_set_u32num_reg(line, operandarray_get(ops, 0)->val_u32num, operandarray_get(ops, 1)->val_reg);
}

static void call_967(int line, struct operandarray *ops) {
   insn_setsw_i32num_reg(line, operandarray_get(ops, 0)->val_i32num, operandarray_get(ops, 1)->val_reg);
}

static void call_968(int line, struct operandarray *ops) {
   insn_setx_i64num_reg_reg(line, operandarray_get(ops, 0)->val_i64num, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_969(int line, struct operandarray *ops) {
   insn_signx_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_970(int line, struct operandarray *ops) {
   insn_signx_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_971(int line, struct operandarray *ops) {
   insn_not_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_972(int line, struct operandarray *ops) {
   insn_not_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_973(int line, struct operandarray *ops) {
   insn_neg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_974(int line, struct operandarray *ops) {
   insn_neg_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_975(int line, struct operandarray *ops) {
   insn_cas_braddr_r_reg_reg(line, operandarray_get(ops, 0)->val_braddr_r, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_976(int line, struct operandarray *ops) {
   insn_casl_braddr_r_reg_reg(line, operandarray_get(ops, 0)->val_braddr_r, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_977(int line, struct operandarray *ops) {
   insn_casx_braddr_r_reg_reg(line, operandarray_get(ops, 0)->val_braddr_r, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_978(int line, struct operandarray *ops) {
   insn_casxl_braddr_r_reg_reg(line, operandarray_get(ops, 0)->val_braddr_r, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_979(int line, struct operandarray *ops) {
   insn_inc_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_980(int line, struct operandarray *ops) {
   insn_inc_i13num_reg(line, operandarray_get(ops, 0)->val_i13num, operandarray_get(ops, 1)->val_reg);
}

static void call_981(int line, struct operandarray *ops) {
   insn_inccc_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_982(int line, struct operandarray *ops) {
   insn_inccc_i13num_reg(line, operandarray_get(ops, 0)->val_i13num, operandarray_get(ops, 1)->val_reg);
}

static void call_983(int line, struct operandarray *ops) {
   insn_dec_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_984(int line, struct operandarray *ops) {
   insn_dec_i13num_reg(line, operandarray_get(ops, 0)->val_i13num, operandarray_get(ops, 1)->val_reg);
}

static void call_985(int line, struct operandarray *ops) {
   insn_deccc_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_986(int line, struct operandarray *ops) {
   insn_deccc_i13num_reg(line, operandarray_get(ops, 0)->val_i13num, operandarray_get(ops, 1)->val_reg);
}

static void call_987(int line, struct operandarray *ops) {
   insn_btst_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_988(int line, struct operandarray *ops) {
   insn_btst_i13num_reg(line, operandarray_get(ops, 0)->val_i13num, operandarray_get(ops, 1)->val_reg);
}

static void call_989(int line, struct operandarray *ops) {
   insn_bset_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_990(int line, struct operandarray *ops) {
   insn_bset_i13num_reg(line, operandarray_get(ops, 0)->val_i13num, operandarray_get(ops, 1)->val_reg);
}

static void call_991(int line, struct operandarray *ops) {
   insn_bclr_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_992(int line, struct operandarray *ops) {
   insn_bclr_i13num_reg(line, operandarray_get(ops, 0)->val_i13num, operandarray_get(ops, 1)->val_reg);
}

static void call_993(int line, struct operandarray *ops) {
   insn_btog_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_994(int line, struct operandarray *ops) {
   insn_btog_i13num_reg(line, operandarray_get(ops, 0)->val_i13num, operandarray_get(ops, 1)->val_reg);
}

static void call_995(int line, struct operandarray *ops) {
   insn_clr_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_996(int line, struct operandarray *ops) {
   insn_clrb_braddr_rr(line, &operandarray_get(ops, 0)->val_braddr_rr);
}

static void call_997(int line, struct operandarray *ops) {
   insn_clrb_braddr_ri(line, &operandarray_get(ops, 0)->val_braddr_ri);
}

static void call_998(int line, struct operandarray *ops) {
   insn_clrh_braddr_rr(line, &operandarray_get(ops, 0)->val_braddr_rr);
}

static void call_999(int line, struct operandarray *ops) {
   insn_clrh_braddr_ri(line, &operandarray_get(ops, 0)->val_braddr_ri);
}

static void call_1000(int line, struct operandarray *ops) {
   insn_clr_braddr_rr(line, &operandarray_get(ops, 0)->val_braddr_rr);
}

static void call_1001(int line, struct operandarray *ops) {
   insn_clr_braddr_ri(line, &operandarray_get(ops, 0)->val_braddr_ri);
}

static void call_1002(int line, struct operandarray *ops) {
   insn_clrx_braddr_rr(line, &operandarray_get(ops, 0)->val_braddr_rr);
}

static void call_1003(int line, struct operandarray *ops) {
   insn_clrx_braddr_ri(line, &operandarray_get(ops, 0)->val_braddr_ri);
}

static void call_1004(int line, struct operandarray *ops) {
   insn_clruw_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_1005(int line, struct operandarray *ops) {
   insn_clruw_reg(line, operandarray_get(ops, 0)->val_reg);
}

static void call_1006(int line, struct operandarray *ops) {
   insn_mov_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg);
}

static void call_1007(int line, struct operandarray *ops) {
   insn_mov_i13num_reg(line, operandarray_get(ops, 0)->val_i13num, operandarray_get(ops, 1)->val_reg);
}

static void call_1008(int line, struct operandarray *ops) {
   insn_mov_asr_reg(line, operandarray_get(ops, 0)->val_asr, operandarray_get(ops, 1)->val_reg);
}

static void call_1009(int line, struct operandarray *ops) {
   insn_mov_reg_asr(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_asr);
}

static void call_1010(int line, struct operandarray *ops) {
   insn_ldn_braddr_rr_reg(line, &operandarray_get(ops, 0)->val_braddr_rr, operandarray_get(ops, 1)->val_reg);
}

static void call_1011(int line, struct operandarray *ops) {
   insn_ldn_braddr_ri_reg(line, &operandarray_get(ops, 0)->val_braddr_ri, operandarray_get(ops, 1)->val_reg);
}

static void call_1012(int line, struct operandarray *ops) {
   insn_ldna_braddr_rr_immasi_reg(line, &operandarray_get(ops, 0)->val_braddr_rr_immasi, operandarray_get(ops, 1)->val_reg);
}

static void call_1013(int line, struct operandarray *ops) {
   insn_ldna_braddr_ri_asi_reg(line, &operandarray_get(ops, 0)->val_braddr_ri_asi, operandarray_get(ops, 1)->val_reg);
}

static void call_1014(int line, struct operandarray *ops) {
   insn_stn_reg_braddr_rr(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr);
}

static void call_1015(int line, struct operandarray *ops) {
   insn_stn_reg_braddr_ri(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri);
}

static void call_1016(int line, struct operandarray *ops) {
   insn_stna_reg_braddr_rr_immasi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_rr_immasi);
}

static void call_1017(int line, struct operandarray *ops) {
   insn_stna_reg_braddr_ri_asi(line, operandarray_get(ops, 0)->val_reg, &operandarray_get(ops, 1)->val_braddr_ri_asi);
}

static void call_1018(int line, struct operandarray *ops) {
   insn_slln_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_1019(int line, struct operandarray *ops) {
   insn_slln_reg_u6num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_u6num, operandarray_get(ops, 2)->val_reg);
}

static void call_1020(int line, struct operandarray *ops) {
   insn_srln_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_1021(int line, struct operandarray *ops) {
   insn_srln_reg_u6num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_u6num, operandarray_get(ops, 2)->val_reg);
}

static void call_1022(int line, struct operandarray *ops) {
   insn_sran_reg_reg_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_1023(int line, struct operandarray *ops) {
   insn_sran_reg_u6num_reg(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_u6num, operandarray_get(ops, 2)->val_reg);
}

static void call_1024(int line, struct operandarray *ops) {
   insn_casn_braddr_r_reg_reg(line, operandarray_get(ops, 0)->val_braddr_r, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_1025(int line, struct operandarray *ops) {
   insn_casna_braddr_r_immasi_reg_reg(line, &operandarray_get(ops, 0)->val_braddr_r_immasi, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_1026(int line, struct operandarray *ops) {
   insn_casna_braddr_r_asi_reg_reg(line, &operandarray_get(ops, 0)->val_braddr_r_asi, operandarray_get(ops, 1)->val_reg, operandarray_get(ops, 2)->val_reg);
}

static void call_1027(int line, struct operandarray *ops) {
   insn_clrn_braddr_rr(line, &operandarray_get(ops, 0)->val_braddr_rr);
}

static void call_1028(int line, struct operandarray *ops) {
   insn_clrn_braddr_ri(line, &operandarray_get(ops, 0)->val_braddr_ri);
}

static void call_1029(int line, struct operandarray *ops) {
   directive_register_r_rtag(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_registertag);
}

static void call_1030(int line, struct operandarray *ops) {
   directive_set_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1031(int line, struct operandarray *ops) {
   directive_unset_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1032(int line, struct operandarray *ops) {
   directive_set_s_x(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_expr);
}

static void call_1033(int line, struct operandarray *ops) {
   directive_file_q(line, operandarray_get(ops, 0)->val_qstring);
}

static void call_1034(int line, struct operandarray *ops) {
   directive_file_x(line, operandarray_get(ops, 0)->val_expr);
}

static void call_1035(int line, struct operandarray *ops) {
   directive_ident_q(line, operandarray_get(ops, 0)->val_qstring);
}

static void call_1036(int line, struct operandarray *ops) {
   directive_gnu_attribute_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_1037(int line, struct operandarray *ops) {
   (void)ops;
   directive_text_(line);
}

static void call_1038(int line, struct operandarray *ops) {
   (void)ops;
   directive_rdata_(line);
}

static void call_1039(int line, struct operandarray *ops) {
   (void)ops;
   directive_data_(line);
}

static void call_1040(int line, struct operandarray *ops) {
   (void)ops;
   directive_bss_(line);
}

static void call_1041(int line, struct operandarray *ops) {
   directive_section_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1042(int line, struct operandarray *ops) {
   directive_section_s_q(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring);
}

static void call_1043(int line, struct operandarray *ops) {
   directive_section_s_q_q(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_qstring);
}

static void call_1044(int line, struct operandarray *ops) {
   directive_section_s_q_q_x(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_qstring, operandarray_get(ops, 3)->val_expr);
}

static void call_1045(int line, struct operandarray *ops) {
   directive_section_s_q_q_x_x(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_qstring, operandarray_get(ops, 3)->val_expr, operandarray_get(ops, 4)->val_expr);
}

static void call_1046(int line, struct operandarray *ops) {
   directive_section_s_q_secty(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_sectiontype);
}

static void call_1047(int line, struct operandarray *ops) {
   directive_section_s_q_secty_x(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_sectiontype, operandarray_get(ops, 3)->val_expr);
}

static void call_1048(int line, struct operandarray *ops) {
   directive_section_s_q_secty_x_x(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_sectiontype, operandarray_get(ops, 3)->val_expr, operandarray_get(ops, 4)->val_expr);
}

static void call_1049(int line, struct operandarray *ops) {
   directive_section_q(line, operandarray_get(ops, 0)->val_qstring);
}

static void call_1050(int line, struct operandarray *ops) {
   (void)ops;
   directive_previous_(line);
}

static void call_1051(int line, struct operandarray *ops) {
   directive_align_mz(line, operandarray_get(ops, 0)->val_magiczero);
}

static void call_1052(int line, struct operandarray *ops) {
   directive_align_n(line, operandarray_get(ops, 0)->val_number);
}

static void call_1053(int line, struct operandarray *ops) {
   directive_space_n(line, operandarray_get(ops, 0)->val_number);
}

static void call_1054(int line, struct operandarray *ops) {
   directive_lcomm_s_n(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number);
}

static void call_1055(int line, struct operandarray *ops) {
   directive_lcomm_s_n_n(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_number);
}

static void call_1056(int line, struct operandarray *ops) {
   directive_comm_s_n(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number);
}

static void call_1057(int line, struct operandarray *ops) {
   directive_comm_s_n_n(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_number);
}

static void call_1058(int line, struct operandarray *ops) {
   directive_local_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1059(int line, struct operandarray *ops) {
   directive_globl_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1060(int line, struct operandarray *ops) {
   directive_global_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1061(int line, struct operandarray *ops) {
   directive_extern_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1062(int line, struct operandarray *ops) {
   directive_type_s_symty(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_symboltype);
}

static void call_1063(int line, struct operandarray *ops) {
   directive_ent_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1064(int line, struct operandarray *ops) {
   directive_end_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1065(int line, struct operandarray *ops) {
   directive_size_s_x(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_expr);
}

static void call_1066(int line, struct operandarray *ops) {
   directive_frame_r_n_r(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_reg);
}

static void call_1067(int line, struct operandarray *ops) {
   directive_mask_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_1068(int line, struct operandarray *ops) {
   directive_fmask_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_1069(int line, struct operandarray *ops) {
   directive_ascii_q(line, operandarray_get(ops, 0)->val_qstring);
}

static void call_1070(int line, struct operandarray *ops) {
   directive_asciz_q(line, operandarray_get(ops, 0)->val_qstring);
}

static void call_1071(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_8byte_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1072(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_word_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1073(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_4byte_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1074(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_hword_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1075(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_half_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1076(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_short_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1077(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_2byte_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1078(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_byte_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1079(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_int_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1080(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_long_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1081(int line, struct operandarray *ops) {
   (void)ops;
   directive_cfi_startproc_(line);
}

static void call_1082(int line, struct operandarray *ops) {
   (void)ops;
   directive_cfi_endproc_(line);
}

static void call_1083(int line, struct operandarray *ops) {
   (void)ops;
   directive_cfi_signal_frame_(line);
}

static void call_1084(int line, struct operandarray *ops) {
   directive_cfi_def_cfa_r_n(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number);
}

static void call_1085(int line, struct operandarray *ops) {
   directive_cfi_def_cfa_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_1086(int line, struct operandarray *ops) {
   directive_cfi_offset_r_n(line, operandarray_get(ops, 0)->val_reg, operandarray_get(ops, 1)->val_number);
}

static void call_1087(int line, struct operandarray *ops) {
   directive_cfi_offset_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_1088(int line, struct operandarray *ops) {
   directive_cfi_return_column_r(line, operandarray_get(ops, 0)->val_reg);
}

static void call_1089(int line, struct operandarray *ops) {
   (void)ops;
   directive_cfi_window_save_(line);
}

static void call_1090(int line, struct operandarray *ops) {
   directive_cfi_register_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_1091(int line, struct operandarray *ops) {
   directive_cfi_def_cfa_register_n(line, operandarray_get(ops, 0)->val_number);
}

static void call_1092(int line, struct operandarray *ops) {
   directive_common_s_n_q(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_qstring);
}

static void call_1093(int line, struct operandarray *ops) {
   directive_reserve_s_n_q(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_qstring);
}

static void call_1094(int line, struct operandarray *ops) {
   directive_common_s_n_n(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_number);
}

static void call_1095(int line, struct operandarray *ops) {
   directive_reserve_s_n_n(line, operandarray_get(ops, 0)->val_symbol, operandarray_get(ops, 1)->val_number, operandarray_get(ops, 2)->val_number);
}

static void call_1096(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_nword_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1097(int line, struct operandarray *ops) {
   (void)ops;
   directive_proc_(line);
}

static void call_1098(int line, struct operandarray *ops) {
   directive_proc_x(line, operandarray_get(ops, 0)->val_expr);
}

static void call_1099(int line, struct operandarray *ops) {
   directive_seg_q(line, operandarray_get(ops, 0)->val_qstring);
}

static void call_1100(int line, struct operandarray *ops) {
   directive_skip_n(line, operandarray_get(ops, 0)->val_number);
}

static void call_1101(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_xword_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1102(int line, struct operandarray *ops) {
   directive_section_x_q_secty(line, operandarray_get(ops, 0)->val_expr, operandarray_get(ops, 1)->val_qstring, operandarray_get(ops, 2)->val_sectiontype);
}

static void call_1103(int line, struct operandarray *ops) {
   directive_syntax_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1104(int line, struct operandarray *ops) {
   directive_arch_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1105(int line, struct operandarray *ops) {
   directive_arch_extension_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1106(int line, struct operandarray *ops) {
   directive_cpu_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1107(int line, struct operandarray *ops) {
   directive_cpu_x(line, operandarray_get(ops, 0)->val_expr);
}

static void call_1108(int line, struct operandarray *ops) {
   directive_fpu_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1109(int line, struct operandarray *ops) {
   (void)ops;
   directive_arm_(line);
}

static void call_1110(int line, struct operandarray *ops) {
   (void)ops;
   directive_thumb_(line);
}

static void call_1111(int line, struct operandarray *ops) {
   directive_code_n(line, operandarray_get(ops, 0)->val_number);
}

static void call_1112(int line, struct operandarray *ops) {
   (void)ops;
   directive_force_thumb_(line);
}

static void call_1113(int line, struct operandarray *ops) {
   (void)ops;
   directive_thumb_func_(line);
}

static void call_1114(int line, struct operandarray *ops) {
   (void)ops;
   directive_thumb_set_(line);
}

static void call_1115(int line, struct operandarray *ops) {
   directive_eabi_attribute_n_n(line, operandarray_get(ops, 0)->val_number, operandarray_get(ops, 1)->val_number);
}

static void call_1116(int line, struct operandarray *ops) {
   directive_personality_s(line, operandarray_get(ops, 0)->val_symbol);
}

static void call_1117(int line, struct operandarray *ops) {
   directive_personalityindex_n(line, operandarray_get(ops, 0)->val_number);
}

static void call_1118(int line, struct operandarray *ops) {
   const unsigned n=1;
   unsigned i, num;
   num = operandarray_num(ops);
   for (i=0; i<num/n; i+=n) {
      directive_inst_x(line, operandarray_get(ops, i+0)->val_expr);
   }
}

static void call_1119(int line, struct operandarray *ops) {
   (void)ops;
   directive_even_(line);
}

static void call_1120(int line, struct operandarray *ops) {
   (void)ops;
   directive_fnstart_(line);
}

static void call_1121(int line, struct operandarray *ops) {
   (void)ops;
   directive_fnend_(line);
}

static const opmatchfn matches_addr_ri[1] = {
   check_addr_ri,
};

static const opmatchfn matches_addr_ri_number[2] = {
   check_addr_ri,
   check_number,
};

static const opmatchfn matches_addr_ri_reg[2] = {
   check_addr_ri,
   check_reg,
};

static const opmatchfn matches_addr_rr[1] = {
   check_addr_rr,
};

static const opmatchfn matches_addr_rr_number[2] = {
   check_addr_rr,
   check_number,
};

static const opmatchfn matches_addr_rr_reg[2] = {
   check_addr_rr,
   check_reg,
};

static const opmatchfn matches_asr_reg[2] = {
   check_asr,
   check_reg,
};

static const opmatchfn matches_braddr_r_asi_reg_reg[3] = {
   check_braddr_r_asi,
   check_reg,
   check_reg,
};

static const opmatchfn matches_braddr_r_immasi_reg_reg[3] = {
   check_braddr_r_immasi,
   check_reg,
   check_reg,
};

static const opmatchfn matches_braddr_r_reg_reg[3] = {
   check_braddr_r,
   check_reg,
   check_reg,
};

static const opmatchfn matches_braddr_ri[1] = {
   check_braddr_ri,
};

static const opmatchfn matches_braddr_ri_asi_freg[2] = {
   check_braddr_ri_asi,
   check_freg,
};

static const opmatchfn matches_braddr_ri_asi_reg[2] = {
   check_braddr_ri_asi,
   check_reg,
};

static const opmatchfn matches_braddr_ri_asi_u5num[2] = {
   check_braddr_ri_asi,
   check_u5num,
};

static const opmatchfn matches_braddr_ri_freg[2] = {
   check_braddr_ri,
   check_freg,
};

static const opmatchfn matches_braddr_ri_fsr[2] = {
   check_braddr_ri,
   check_fsr,
};

static const opmatchfn matches_braddr_ri_reg[2] = {
   check_braddr_ri,
   check_reg,
};

static const opmatchfn matches_braddr_ri_u5num[2] = {
   check_braddr_ri,
   check_u5num,
};

static const opmatchfn matches_braddr_rr[1] = {
   check_braddr_rr,
};

static const opmatchfn matches_braddr_rr_freg[2] = {
   check_braddr_rr,
   check_freg,
};

static const opmatchfn matches_braddr_rr_fsr[2] = {
   check_braddr_rr,
   check_fsr,
};

static const opmatchfn matches_braddr_rr_immasi_freg[2] = {
   check_braddr_rr_immasi,
   check_freg,
};

static const opmatchfn matches_braddr_rr_immasi_reg[2] = {
   check_braddr_rr_immasi,
   check_reg,
};

static const opmatchfn matches_braddr_rr_immasi_u5num[2] = {
   check_braddr_rr_immasi,
   check_u5num,
};

static const opmatchfn matches_braddr_rr_reg[2] = {
   check_braddr_rr,
   check_reg,
};

static const opmatchfn matches_braddr_rr_u5num[2] = {
   check_braddr_rr,
   check_u5num,
};

static const opmatchfn matches_braddr_rx_freg[2] = {
   check_braddr_rx,
   check_freg,
};

static const opmatchfn matches_braddr_rx_fsr[2] = {
   check_braddr_rx,
   check_fsr,
};

static const opmatchfn matches_braddr_rx_reg[2] = {
   check_braddr_rx,
   check_reg,
};

static const opmatchfn matches_expr_reg[2] = {
   check_expr,
   check_reg,
};

static const opmatchfn matches_fcc_freg_freg[3] = {
   check_fcc,
   check_freg,
   check_freg,
};

static const opmatchfn matches_fcc_i11num_reg[3] = {
   check_fcc,
   check_i11num,
   check_reg,
};

static const opmatchfn matches_fcc_reg_reg[3] = {
   check_fcc,
   check_reg,
   check_reg,
};

static const opmatchfn matches_fcc_symbol[2] = {
   check_fcc,
   check_symbol,
};

static const opmatchfn matches_freg_braddr_ri[2] = {
   check_freg,
   check_braddr_ri,
};

static const opmatchfn matches_freg_braddr_ri_asi[2] = {
   check_freg,
   check_braddr_ri_asi,
};

static const opmatchfn matches_freg_braddr_rr[2] = {
   check_freg,
   check_braddr_rr,
};

static const opmatchfn matches_freg_braddr_rr_immasi[2] = {
   check_freg,
   check_braddr_rr_immasi,
};

static const opmatchfn matches_freg_braddr_rx[2] = {
   check_freg,
   check_braddr_rx,
};

static const opmatchfn matches_freg_freg[2] = {
   check_freg,
   check_freg,
};

static const opmatchfn matches_freg_freg_freg[3] = {
   check_freg,
   check_freg,
   check_freg,
};

static const opmatchfn matches_fsr_braddr_ri[2] = {
   check_fsr,
   check_braddr_ri,
};

static const opmatchfn matches_fsr_braddr_rr[2] = {
   check_fsr,
   check_braddr_rr,
};

static const opmatchfn matches_fsr_braddr_rx[2] = {
   check_fsr,
   check_braddr_rx,
};

static const opmatchfn matches_i13num[1] = {
   check_i13num,
};

static const opmatchfn matches_i13num_reg[2] = {
   check_i13num,
   check_reg,
};

static const opmatchfn matches_i32num_reg[2] = {
   check_i32num,
   check_reg,
};

static const opmatchfn matches_i64num_reg_reg[3] = {
   check_i64num,
   check_reg,
   check_reg,
};

static const opmatchfn matches_icc_freg_freg[3] = {
   check_icc,
   check_freg,
   check_freg,
};

static const opmatchfn matches_icc_i11num_reg[3] = {
   check_icc,
   check_i11num,
   check_reg,
};

static const opmatchfn matches_icc_reg_reg[3] = {
   check_icc,
   check_reg,
   check_reg,
};

static const opmatchfn matches_icc_symbol[2] = {
   check_icc,
   check_symbol,
};

static const opmatchfn matches_icc_trapnum_ri[2] = {
   check_icc,
   check_trapnum_ri,
};

static const opmatchfn matches_icc_trapnum_rr[2] = {
   check_icc,
   check_trapnum_rr,
};

static const opmatchfn matches_membarmask[1] = {
   check_membarmask,
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

static const opmatchfn matches_pr_reg[2] = {
   check_pr,
   check_reg,
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
   check_registertag,
};

static const opmatchfn matches_reg[1] = {
   check_reg,
};

static const opmatchfn matches_reg_asr[2] = {
   check_reg,
   check_asr,
};

static const opmatchfn matches_reg_braddr_ri[2] = {
   check_reg,
   check_braddr_ri,
};

static const opmatchfn matches_reg_braddr_ri_asi[2] = {
   check_reg,
   check_braddr_ri_asi,
};

static const opmatchfn matches_reg_braddr_rr[2] = {
   check_reg,
   check_braddr_rr,
};

static const opmatchfn matches_reg_braddr_rr_immasi[2] = {
   check_reg,
   check_braddr_rr_immasi,
};

static const opmatchfn matches_reg_braddr_rx[2] = {
   check_reg,
   check_braddr_rx,
};

static const opmatchfn matches_reg_expr_reg[3] = {
   check_reg,
   check_expr,
   check_reg,
};

static const opmatchfn matches_reg_freg_freg[3] = {
   check_reg,
   check_freg,
   check_freg,
};

static const opmatchfn matches_reg_i10num_reg[3] = {
   check_reg,
   check_i10num,
   check_reg,
};

static const opmatchfn matches_reg_i13num[2] = {
   check_reg,
   check_i13num,
};

static const opmatchfn matches_reg_i13num_asr[3] = {
   check_reg,
   check_i13num,
   check_asr,
};

static const opmatchfn matches_reg_i13num_pr[3] = {
   check_reg,
   check_i13num,
   check_pr,
};

static const opmatchfn matches_reg_i13num_reg[3] = {
   check_reg,
   check_i13num,
   check_reg,
};

static const opmatchfn matches_reg_reg[2] = {
   check_reg,
   check_reg,
};

static const opmatchfn matches_reg_reg_asr[3] = {
   check_reg,
   check_reg,
   check_asr,
};

static const opmatchfn matches_reg_reg_pr[3] = {
   check_reg,
   check_reg,
   check_pr,
};

static const opmatchfn matches_reg_reg_reg[3] = {
   check_reg,
   check_reg,
   check_reg,
};

static const opmatchfn matches_reg_symbol[2] = {
   check_reg,
   check_symbol,
};

static const opmatchfn matches_reg_u5num_reg[3] = {
   check_reg,
   check_u5num,
   check_reg,
};

static const opmatchfn matches_reg_u6num_reg[3] = {
   check_reg,
   check_u6num,
   check_reg,
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

static const opmatchfn matches_symbol_number[2] = {
   check_symbol,
   check_number,
};

static const opmatchfn matches_u22num[1] = {
   check_u22num,
};

static const opmatchfn matches_u32num_reg[2] = {
   check_u32num,
   check_reg,
};

static const opmatchfn matches_u5num_u19num[2] = {
   check_u5num,
   check_u19num,
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
   { matches_x,      1, 1, call_1077 } /* line 1216 */,
};

/* .4byte */
static const struct insnsig sigtbl1[1] = {
   { matches_x,      1, 1, call_1073 } /* line 1212 */,
};

/* .8byte */
static const struct insnsig sigtbl2[1] = {
   { matches_x,      1, 1, call_1071 } /* line 1210 */,
};

/* .align */
static const struct insnsig sigtbl3[2] = {
   { matches_mz,     1, 0, call_1051 } /* line 1185 */,
   { matches_n,      1, 0, call_1052 } /* line 1187 */,
};

/* .arch */
static const struct insnsig sigtbl4[1] = {
   { matches_s,      1, 0, call_1104 } /* line 1254 */,
};

/* .arch_extension */
static const struct insnsig sigtbl5[1] = {
   { matches_s,      1, 0, call_1105 } /* line 1255 */,
};

/* .arm */
static const struct insnsig sigtbl6[1] = {
   { NULL,           0, 0, call_1109 } /* line 1259 */,
};

/* .ascii */
static const struct insnsig sigtbl7[1] = {
   { matches_q,      1, 0, call_1069 } /* line 1208 */,
};

/* .asciz */
static const struct insnsig sigtbl8[1] = {
   { matches_q,      1, 0, call_1070 } /* line 1209 */,
};

/* .bss */
static const struct insnsig sigtbl9[1] = {
   { NULL,           0, 0, call_1040 } /* line 1170 */,
};

/* .byte */
static const struct insnsig sigtbl10[1] = {
   { matches_x,      1, 1, call_1078 } /* line 1217 */,
};

/* .cfi_def_cfa */
static const struct insnsig sigtbl11[2] = {
   { matches_r_n,    2, 0, call_1084 } /* line 1225 */,
   { matches_n_n,    2, 0, call_1085 } /* line 1226 */,
};

/* .cfi_def_cfa_register */
static const struct insnsig sigtbl12[1] = {
   { matches_n,      1, 0, call_1091 } /* line 1232 */,
};

/* .cfi_endproc */
static const struct insnsig sigtbl13[1] = {
   { NULL,           0, 0, call_1082 } /* line 1223 */,
};

/* .cfi_offset */
static const struct insnsig sigtbl14[2] = {
   { matches_r_n,    2, 0, call_1086 } /* line 1227 */,
   { matches_n_n,    2, 0, call_1087 } /* line 1228 */,
};

/* .cfi_register */
static const struct insnsig sigtbl15[1] = {
   { matches_n_n,    2, 0, call_1090 } /* line 1231 */,
};

/* .cfi_return_column */
static const struct insnsig sigtbl16[1] = {
   { matches_r,      1, 0, call_1088 } /* line 1229 */,
};

/* .cfi_signal_frame */
static const struct insnsig sigtbl17[1] = {
   { NULL,           0, 0, call_1083 } /* line 1224 */,
};

/* .cfi_startproc */
static const struct insnsig sigtbl18[1] = {
   { NULL,           0, 0, call_1081 } /* line 1222 */,
};

/* .cfi_window_save */
static const struct insnsig sigtbl19[1] = {
   { NULL,           0, 0, call_1089 } /* line 1230 */,
};

/* .code */
static const struct insnsig sigtbl20[1] = {
   { matches_n,      1, 0, call_1111 } /* line 1261 */,
};

/* .comm */
static const struct insnsig sigtbl21[2] = {
   { matches_s_n,    2, 0, call_1056 } /* line 1192 */,
   { matches_s_n_n,  3, 0, call_1057 } /* line 1193 */,
};

/* .common */
static const struct insnsig sigtbl22[2] = {
   { matches_s_n_q,  3, 0, call_1092 } /* line 1237 */,
   { matches_s_n_n,  3, 0, call_1094 } /* line 1240 */,
};

/* .cpu */
static const struct insnsig sigtbl23[2] = {
   { matches_s,      1, 0, call_1106 } /* line 1256 */,
   { matches_x,      1, 0, call_1107 } /* line 1257 */,
};

/* .data */
static const struct insnsig sigtbl24[1] = {
   { NULL,           0, 0, call_1039 } /* line 1169 */,
};

/* .eabi_attribute */
static const struct insnsig sigtbl25[1] = {
   { matches_n_n,    2, 0, call_1115 } /* line 1265 */,
};

/* .end */
static const struct insnsig sigtbl26[1] = {
   { matches_s,      1, 0, call_1064 } /* line 1201 */,
};

/* .ent */
static const struct insnsig sigtbl27[1] = {
   { matches_s,      1, 0, call_1063 } /* line 1200 */,
};

/* .even */
static const struct insnsig sigtbl28[1] = {
   { NULL,           0, 0, call_1119 } /* line 1272 */,
};

/* .extern */
static const struct insnsig sigtbl29[1] = {
   { matches_s,      1, 0, call_1061 } /* line 1198 */,
};

/* .file */
static const struct insnsig sigtbl30[2] = {
   { matches_q,      1, 0, call_1033 } /* line 1162 */,
   { matches_x,      1, 0, call_1034 } /* line 1163 */,
};

/* .fmask */
static const struct insnsig sigtbl31[1] = {
   { matches_n_n,    2, 0, call_1068 } /* line 1206 */,
};

/* .fnend */
static const struct insnsig sigtbl32[1] = {
   { NULL,           0, 0, call_1121 } /* line 1274 */,
};

/* .fnstart */
static const struct insnsig sigtbl33[1] = {
   { NULL,           0, 0, call_1120 } /* line 1273 */,
};

/* .force_thumb */
static const struct insnsig sigtbl34[1] = {
   { NULL,           0, 0, call_1112 } /* line 1262 */,
};

/* .fpu */
static const struct insnsig sigtbl35[1] = {
   { matches_s,      1, 0, call_1108 } /* line 1258 */,
};

/* .frame */
static const struct insnsig sigtbl36[1] = {
   { matches_r_n_r,  3, 0, call_1066 } /* line 1204 */,
};

/* .global */
static const struct insnsig sigtbl37[1] = {
   { matches_s,      1, 0, call_1060 } /* line 1197 */,
};

/* .globl */
static const struct insnsig sigtbl38[1] = {
   { matches_s,      1, 0, call_1059 } /* line 1196 */,
};

/* .gnu_attribute */
static const struct insnsig sigtbl39[1] = {
   { matches_n_n,    2, 0, call_1036 } /* line 1165 */,
};

/* .half */
static const struct insnsig sigtbl40[1] = {
   { matches_x,      1, 1, call_1075 } /* line 1214 */,
};

/* .hword */
static const struct insnsig sigtbl41[1] = {
   { matches_x,      1, 1, call_1074 } /* line 1213 */,
};

/* .ident */
static const struct insnsig sigtbl42[1] = {
   { matches_q,      1, 0, call_1035 } /* line 1164 */,
};

/* .inst */
static const struct insnsig sigtbl43[1] = {
   { matches_x,      1, 1, call_1118 } /* line 1271 */,
};

/* .int */
static const struct insnsig sigtbl44[1] = {
   { matches_x,      1, 1, call_1079 } /* line 1219 */,
};

/* .lcomm */
static const struct insnsig sigtbl45[2] = {
   { matches_s_n,    2, 0, call_1054 } /* line 1190 */,
   { matches_s_n_n,  3, 0, call_1055 } /* line 1191 */,
};

/* .local */
static const struct insnsig sigtbl46[1] = {
   { matches_s,      1, 0, call_1058 } /* line 1195 */,
};

/* .long */
static const struct insnsig sigtbl47[1] = {
   { matches_x,      1, 1, call_1080 } /* line 1220 */,
};

/* .mask */
static const struct insnsig sigtbl48[1] = {
   { matches_n_n,    2, 0, call_1067 } /* line 1205 */,
};

/* .nword */
static const struct insnsig sigtbl49[1] = {
   { matches_x,      1, 1, call_1096 } /* line 1242 */,
};

/* .personality */
static const struct insnsig sigtbl50[1] = {
   { matches_s,      1, 0, call_1116 } /* line 1266 */,
};

/* .personalityindex */
static const struct insnsig sigtbl51[1] = {
   { matches_n,      1, 0, call_1117 } /* line 1267 */,
};

/* .previous */
static const struct insnsig sigtbl52[1] = {
   { NULL,           0, 0, call_1050 } /* line 1180 */,
};

/* .proc */
static const struct insnsig sigtbl53[2] = {
   { NULL,           0, 0, call_1097 } /* line 1243 */,
   { matches_x,      1, 0, call_1098 } /* line 1244 */,
};

/* .rdata */
static const struct insnsig sigtbl54[1] = {
   { NULL,           0, 0, call_1038 } /* line 1168 */,
};

/* .register */
static const struct insnsig sigtbl55[1] = {
   { matches_r_rtag,  2, 0, call_1029 } /* line 1114 */,
};

/* .reserve */
static const struct insnsig sigtbl56[2] = {
   { matches_s_n_q,  3, 0, call_1093 } /* line 1238 */,
   { matches_s_n_n,  3, 0, call_1095 } /* line 1241 */,
};

/* .section */
static const struct insnsig sigtbl57[10] = {
   { matches_s,      1, 0, call_1041 } /* line 1171 */,
   { matches_s_q,    2, 0, call_1042 } /* line 1172 */,
   { matches_s_q_q,  3, 0, call_1043 } /* line 1173 */,
   { matches_s_q_q_x,  4, 0, call_1044 } /* line 1174 */,
   { matches_s_q_q_x_x,  5, 0, call_1045 } /* line 1175 */,
   { matches_s_q_secty,  3, 0, call_1046 } /* line 1176 */,
   { matches_s_q_secty_x,  4, 0, call_1047 } /* line 1177 */,
   { matches_s_q_secty_x_x,  5, 0, call_1048 } /* line 1178 */,
   { matches_q,      1, 0, call_1049 } /* line 1179 */,
   { matches_x_q_secty,  3, 0, call_1102 } /* line 1249 */,
};

/* .seg */
static const struct insnsig sigtbl58[1] = {
   { matches_q,      1, 0, call_1099 } /* line 1245 */,
};

/* .set */
static const struct insnsig sigtbl59[2] = {
   { matches_s,      1, 0, call_1030 } /* line 1156 */,
   { matches_s_x,    2, 0, call_1032 } /* line 1160 */,
};

/* .short */
static const struct insnsig sigtbl60[1] = {
   { matches_x,      1, 1, call_1076 } /* line 1215 */,
};

/* .size */
static const struct insnsig sigtbl61[1] = {
   { matches_s_x,    2, 0, call_1065 } /* line 1202 */,
};

/* .skip */
static const struct insnsig sigtbl62[1] = {
   { matches_n,      1, 0, call_1100 } /* line 1246 */,
};

/* .space */
static const struct insnsig sigtbl63[1] = {
   { matches_n,      1, 0, call_1053 } /* line 1188 */,
};

/* .syntax */
static const struct insnsig sigtbl64[1] = {
   { matches_s,      1, 0, call_1103 } /* line 1253 */,
};

/* .text */
static const struct insnsig sigtbl65[1] = {
   { NULL,           0, 0, call_1037 } /* line 1167 */,
};

/* .thumb */
static const struct insnsig sigtbl66[1] = {
   { NULL,           0, 0, call_1110 } /* line 1260 */,
};

/* .thumb_func */
static const struct insnsig sigtbl67[1] = {
   { NULL,           0, 0, call_1113 } /* line 1263 */,
};

/* .thumb_set */
static const struct insnsig sigtbl68[1] = {
   { NULL,           0, 0, call_1114 } /* line 1264 */,
};

/* .type */
static const struct insnsig sigtbl69[1] = {
   { matches_s_symty,  2, 0, call_1062 } /* line 1199 */,
};

/* .unset */
static const struct insnsig sigtbl70[1] = {
   { matches_s,      1, 0, call_1031 } /* line 1157 */,
};

/* .word */
static const struct insnsig sigtbl71[1] = {
   { matches_x,      1, 1, call_1072 } /* line 1211 */,
};

/* .xword */
static const struct insnsig sigtbl72[1] = {
   { matches_x,      1, 1, call_1101 } /* line 1247 */,
};

/* add */
static const struct insnsig sigtbl73[2] = {
   { matches_reg_reg_reg,  3, 0, call_2 } /* line   4 */,
   { matches_reg_i13num_reg,  3, 0, call_3 } /* line   5 */,
};

/* addc */
static const struct insnsig sigtbl74[2] = {
   { matches_reg_reg_reg,  3, 0, call_6 } /* line   8 */,
   { matches_reg_i13num_reg,  3, 0, call_7 } /* line   9 */,
};

/* addcc */
static const struct insnsig sigtbl75[2] = {
   { matches_reg_reg_reg,  3, 0, call_4 } /* line   6 */,
   { matches_reg_i13num_reg,  3, 0, call_5 } /* line   7 */,
};

/* addccc */
static const struct insnsig sigtbl76[2] = {
   { matches_reg_reg_reg,  3, 0, call_8 } /* line  10 */,
   { matches_reg_i13num_reg,  3, 0, call_9 } /* line  11 */,
};

/* addx */
static const struct insnsig sigtbl77[2] = {
   { matches_reg_reg_reg,  3, 0, call_57 } /* line  61 */,
   { matches_reg_i13num_reg,  3, 0, call_58 } /* line  62 */,
};

/* addxcc */
static const struct insnsig sigtbl78[2] = {
   { matches_reg_reg_reg,  3, 0, call_59 } /* line  63 */,
   { matches_reg_i13num_reg,  3, 0, call_60 } /* line  64 */,
};

/* and */
static const struct insnsig sigtbl79[2] = {
   { matches_reg_reg_reg,  3, 0, call_18 } /* line  20 */,
   { matches_reg_i13num_reg,  3, 0, call_19 } /* line  21 */,
};

/* andcc */
static const struct insnsig sigtbl80[2] = {
   { matches_reg_reg_reg,  3, 0, call_20 } /* line  22 */,
   { matches_reg_i13num_reg,  3, 0, call_21 } /* line  23 */,
};

/* andn */
static const struct insnsig sigtbl81[2] = {
   { matches_reg_reg_reg,  3, 0, call_22 } /* line  24 */,
   { matches_reg_i13num_reg,  3, 0, call_23 } /* line  25 */,
};

/* andncc */
static const struct insnsig sigtbl82[2] = {
   { matches_reg_reg_reg,  3, 0, call_24 } /* line  26 */,
   { matches_reg_i13num_reg,  3, 0, call_25 } /* line  27 */,
};

/* ba */
static const struct insnsig sigtbl83[2] = {
   { matches_symbol,  1, 0, call_331 } /* line 354 */,
   { matches_icc_symbol,  2, 0, call_371 } /* line 397 */,
};

/* ba,a */
static const struct insnsig sigtbl84[2] = {
   { matches_symbol,  1, 0, call_332 } /* line 355 */,
   { matches_icc_symbol,  2, 0, call_374 } /* line 400 */,
};

/* ba,a,pn */
static const struct insnsig sigtbl85[1] = {
   { matches_icc_symbol,  2, 0, call_376 } /* line 402 */,
};

/* ba,a,pt */
static const struct insnsig sigtbl86[1] = {
   { matches_icc_symbol,  2, 0, call_375 } /* line 401 */,
};

/* ba,pn */
static const struct insnsig sigtbl87[1] = {
   { matches_icc_symbol,  2, 0, call_373 } /* line 399 */,
};

/* ba,pt */
static const struct insnsig sigtbl88[1] = {
   { matches_icc_symbol,  2, 0, call_372 } /* line 398 */,
};

/* bcc */
static const struct insnsig sigtbl89[2] = {
   { matches_symbol,  1, 0, call_351 } /* line 374 */,
   { matches_icc_symbol,  2, 0, call_431 } /* line 457 */,
};

/* bcc,a */
static const struct insnsig sigtbl90[2] = {
   { matches_symbol,  1, 0, call_352 } /* line 375 */,
   { matches_icc_symbol,  2, 0, call_434 } /* line 460 */,
};

/* bcc,a,pn */
static const struct insnsig sigtbl91[1] = {
   { matches_icc_symbol,  2, 0, call_436 } /* line 462 */,
};

/* bcc,a,pt */
static const struct insnsig sigtbl92[1] = {
   { matches_icc_symbol,  2, 0, call_435 } /* line 461 */,
};

/* bcc,pn */
static const struct insnsig sigtbl93[1] = {
   { matches_icc_symbol,  2, 0, call_433 } /* line 459 */,
};

/* bcc,pt */
static const struct insnsig sigtbl94[1] = {
   { matches_icc_symbol,  2, 0, call_432 } /* line 458 */,
};

/* bclr */
static const struct insnsig sigtbl95[2] = {
   { matches_reg_reg,  2, 0, call_991 } /* line 1068 */,
   { matches_i13num_reg,  2, 0, call_992 } /* line 1069 */,
};

/* bcs */
static const struct insnsig sigtbl96[2] = {
   { matches_symbol,  1, 0, call_353 } /* line 376 */,
   { matches_icc_symbol,  2, 0, call_437 } /* line 463 */,
};

/* bcs,a */
static const struct insnsig sigtbl97[2] = {
   { matches_symbol,  1, 0, call_354 } /* line 377 */,
   { matches_icc_symbol,  2, 0, call_440 } /* line 466 */,
};

/* bcs,a,pn */
static const struct insnsig sigtbl98[1] = {
   { matches_icc_symbol,  2, 0, call_442 } /* line 468 */,
};

/* bcs,a,pt */
static const struct insnsig sigtbl99[1] = {
   { matches_icc_symbol,  2, 0, call_441 } /* line 467 */,
};

/* bcs,pn */
static const struct insnsig sigtbl100[1] = {
   { matches_icc_symbol,  2, 0, call_439 } /* line 465 */,
};

/* bcs,pt */
static const struct insnsig sigtbl101[1] = {
   { matches_icc_symbol,  2, 0, call_438 } /* line 464 */,
};

/* be */
static const struct insnsig sigtbl102[2] = {
   { matches_symbol,  1, 0, call_337 } /* line 360 */,
   { matches_icc_symbol,  2, 0, call_389 } /* line 415 */,
};

/* be,a */
static const struct insnsig sigtbl103[2] = {
   { matches_symbol,  1, 0, call_338 } /* line 361 */,
   { matches_icc_symbol,  2, 0, call_392 } /* line 418 */,
};

/* be,a,pn */
static const struct insnsig sigtbl104[1] = {
   { matches_icc_symbol,  2, 0, call_394 } /* line 420 */,
};

/* be,a,pt */
static const struct insnsig sigtbl105[1] = {
   { matches_icc_symbol,  2, 0, call_393 } /* line 419 */,
};

/* be,pn */
static const struct insnsig sigtbl106[1] = {
   { matches_icc_symbol,  2, 0, call_391 } /* line 417 */,
};

/* be,pt */
static const struct insnsig sigtbl107[1] = {
   { matches_icc_symbol,  2, 0, call_390 } /* line 416 */,
};

/* bg */
static const struct insnsig sigtbl108[2] = {
   { matches_symbol,  1, 0, call_339 } /* line 362 */,
   { matches_icc_symbol,  2, 0, call_395 } /* line 421 */,
};

/* bg,a */
static const struct insnsig sigtbl109[2] = {
   { matches_symbol,  1, 0, call_340 } /* line 363 */,
   { matches_icc_symbol,  2, 0, call_398 } /* line 424 */,
};

/* bg,a,pn */
static const struct insnsig sigtbl110[1] = {
   { matches_icc_symbol,  2, 0, call_400 } /* line 426 */,
};

/* bg,a,pt */
static const struct insnsig sigtbl111[1] = {
   { matches_icc_symbol,  2, 0, call_399 } /* line 425 */,
};

/* bg,pn */
static const struct insnsig sigtbl112[1] = {
   { matches_icc_symbol,  2, 0, call_397 } /* line 423 */,
};

/* bg,pt */
static const struct insnsig sigtbl113[1] = {
   { matches_icc_symbol,  2, 0, call_396 } /* line 422 */,
};

/* bge */
static const struct insnsig sigtbl114[2] = {
   { matches_symbol,  1, 0, call_343 } /* line 366 */,
   { matches_icc_symbol,  2, 0, call_407 } /* line 433 */,
};

/* bge,a */
static const struct insnsig sigtbl115[2] = {
   { matches_symbol,  1, 0, call_344 } /* line 367 */,
   { matches_icc_symbol,  2, 0, call_410 } /* line 436 */,
};

/* bge,a,pn */
static const struct insnsig sigtbl116[1] = {
   { matches_icc_symbol,  2, 0, call_412 } /* line 438 */,
};

/* bge,a,pt */
static const struct insnsig sigtbl117[1] = {
   { matches_icc_symbol,  2, 0, call_411 } /* line 437 */,
};

/* bge,pn */
static const struct insnsig sigtbl118[1] = {
   { matches_icc_symbol,  2, 0, call_409 } /* line 435 */,
};

/* bge,pt */
static const struct insnsig sigtbl119[1] = {
   { matches_icc_symbol,  2, 0, call_408 } /* line 434 */,
};

/* bgeu */
static const struct insnsig sigtbl120[2] = {
   { matches_symbol,  1, 0, call_367 } /* line 391 */,
   { matches_icc_symbol,  2, 0, call_479 } /* line 506 */,
};

/* bgeu,a */
static const struct insnsig sigtbl121[2] = {
   { matches_symbol,  1, 0, call_368 } /* line 392 */,
   { matches_icc_symbol,  2, 0, call_482 } /* line 509 */,
};

/* bgeu,a,pn */
static const struct insnsig sigtbl122[1] = {
   { matches_icc_symbol,  2, 0, call_484 } /* line 511 */,
};

/* bgeu,a,pt */
static const struct insnsig sigtbl123[1] = {
   { matches_icc_symbol,  2, 0, call_483 } /* line 510 */,
};

/* bgeu,pn */
static const struct insnsig sigtbl124[1] = {
   { matches_icc_symbol,  2, 0, call_481 } /* line 508 */,
};

/* bgeu,pt */
static const struct insnsig sigtbl125[1] = {
   { matches_icc_symbol,  2, 0, call_480 } /* line 507 */,
};

/* bgu */
static const struct insnsig sigtbl126[2] = {
   { matches_symbol,  1, 0, call_347 } /* line 370 */,
   { matches_icc_symbol,  2, 0, call_419 } /* line 445 */,
};

/* bgu,a */
static const struct insnsig sigtbl127[2] = {
   { matches_symbol,  1, 0, call_348 } /* line 371 */,
   { matches_icc_symbol,  2, 0, call_422 } /* line 448 */,
};

/* bgu,a,pn */
static const struct insnsig sigtbl128[1] = {
   { matches_icc_symbol,  2, 0, call_424 } /* line 450 */,
};

/* bgu,a,pt */
static const struct insnsig sigtbl129[1] = {
   { matches_icc_symbol,  2, 0, call_423 } /* line 449 */,
};

/* bgu,pn */
static const struct insnsig sigtbl130[1] = {
   { matches_icc_symbol,  2, 0, call_421 } /* line 447 */,
};

/* bgu,pt */
static const struct insnsig sigtbl131[1] = {
   { matches_icc_symbol,  2, 0, call_420 } /* line 446 */,
};

/* bl */
static const struct insnsig sigtbl132[2] = {
   { matches_symbol,  1, 0, call_345 } /* line 368 */,
   { matches_icc_symbol,  2, 0, call_413 } /* line 439 */,
};

/* bl,a */
static const struct insnsig sigtbl133[2] = {
   { matches_symbol,  1, 0, call_346 } /* line 369 */,
   { matches_icc_symbol,  2, 0, call_416 } /* line 442 */,
};

/* bl,a,pn */
static const struct insnsig sigtbl134[1] = {
   { matches_icc_symbol,  2, 0, call_418 } /* line 444 */,
};

/* bl,a,pt */
static const struct insnsig sigtbl135[1] = {
   { matches_icc_symbol,  2, 0, call_417 } /* line 443 */,
};

/* bl,pn */
static const struct insnsig sigtbl136[1] = {
   { matches_icc_symbol,  2, 0, call_415 } /* line 441 */,
};

/* bl,pt */
static const struct insnsig sigtbl137[1] = {
   { matches_icc_symbol,  2, 0, call_414 } /* line 440 */,
};

/* ble */
static const struct insnsig sigtbl138[2] = {
   { matches_symbol,  1, 0, call_341 } /* line 364 */,
   { matches_icc_symbol,  2, 0, call_401 } /* line 427 */,
};

/* ble,a */
static const struct insnsig sigtbl139[2] = {
   { matches_symbol,  1, 0, call_342 } /* line 365 */,
   { matches_icc_symbol,  2, 0, call_404 } /* line 430 */,
};

/* ble,a,pn */
static const struct insnsig sigtbl140[1] = {
   { matches_icc_symbol,  2, 0, call_406 } /* line 432 */,
};

/* ble,a,pt */
static const struct insnsig sigtbl141[1] = {
   { matches_icc_symbol,  2, 0, call_405 } /* line 431 */,
};

/* ble,pn */
static const struct insnsig sigtbl142[1] = {
   { matches_icc_symbol,  2, 0, call_403 } /* line 429 */,
};

/* ble,pt */
static const struct insnsig sigtbl143[1] = {
   { matches_icc_symbol,  2, 0, call_402 } /* line 428 */,
};

/* bleu */
static const struct insnsig sigtbl144[2] = {
   { matches_symbol,  1, 0, call_349 } /* line 372 */,
   { matches_icc_symbol,  2, 0, call_425 } /* line 451 */,
};

/* bleu,a */
static const struct insnsig sigtbl145[2] = {
   { matches_symbol,  1, 0, call_350 } /* line 373 */,
   { matches_icc_symbol,  2, 0, call_428 } /* line 454 */,
};

/* bleu,a,pn */
static const struct insnsig sigtbl146[1] = {
   { matches_icc_symbol,  2, 0, call_430 } /* line 456 */,
};

/* bleu,a,pt */
static const struct insnsig sigtbl147[1] = {
   { matches_icc_symbol,  2, 0, call_429 } /* line 455 */,
};

/* bleu,pn */
static const struct insnsig sigtbl148[1] = {
   { matches_icc_symbol,  2, 0, call_427 } /* line 453 */,
};

/* bleu,pt */
static const struct insnsig sigtbl149[1] = {
   { matches_icc_symbol,  2, 0, call_426 } /* line 452 */,
};

/* blu */
static const struct insnsig sigtbl150[2] = {
   { matches_symbol,  1, 0, call_369 } /* line 393 */,
   { matches_icc_symbol,  2, 0, call_485 } /* line 512 */,
};

/* blu,a */
static const struct insnsig sigtbl151[2] = {
   { matches_symbol,  1, 0, call_370 } /* line 394 */,
   { matches_icc_symbol,  2, 0, call_488 } /* line 515 */,
};

/* blu,a,pn */
static const struct insnsig sigtbl152[1] = {
   { matches_icc_symbol,  2, 0, call_490 } /* line 517 */,
};

/* blu,a,pt */
static const struct insnsig sigtbl153[1] = {
   { matches_icc_symbol,  2, 0, call_489 } /* line 516 */,
};

/* blu,pn */
static const struct insnsig sigtbl154[1] = {
   { matches_icc_symbol,  2, 0, call_487 } /* line 514 */,
};

/* blu,pt */
static const struct insnsig sigtbl155[1] = {
   { matches_icc_symbol,  2, 0, call_486 } /* line 513 */,
};

/* bn */
static const struct insnsig sigtbl156[2] = {
   { matches_symbol,  1, 0, call_333 } /* line 356 */,
   { matches_icc_symbol,  2, 0, call_377 } /* line 403 */,
};

/* bn,a */
static const struct insnsig sigtbl157[2] = {
   { matches_symbol,  1, 0, call_334 } /* line 357 */,
   { matches_icc_symbol,  2, 0, call_380 } /* line 406 */,
};

/* bn,a,pn */
static const struct insnsig sigtbl158[1] = {
   { matches_icc_symbol,  2, 0, call_382 } /* line 408 */,
};

/* bn,a,pt */
static const struct insnsig sigtbl159[1] = {
   { matches_icc_symbol,  2, 0, call_381 } /* line 407 */,
};

/* bn,pn */
static const struct insnsig sigtbl160[1] = {
   { matches_icc_symbol,  2, 0, call_379 } /* line 405 */,
};

/* bn,pt */
static const struct insnsig sigtbl161[1] = {
   { matches_icc_symbol,  2, 0, call_378 } /* line 404 */,
};

/* bne */
static const struct insnsig sigtbl162[2] = {
   { matches_symbol,  1, 0, call_335 } /* line 358 */,
   { matches_icc_symbol,  2, 0, call_383 } /* line 409 */,
};

/* bne,a */
static const struct insnsig sigtbl163[2] = {
   { matches_symbol,  1, 0, call_336 } /* line 359 */,
   { matches_icc_symbol,  2, 0, call_386 } /* line 412 */,
};

/* bne,a,pn */
static const struct insnsig sigtbl164[1] = {
   { matches_icc_symbol,  2, 0, call_388 } /* line 414 */,
};

/* bne,a,pt */
static const struct insnsig sigtbl165[1] = {
   { matches_icc_symbol,  2, 0, call_387 } /* line 413 */,
};

/* bne,pn */
static const struct insnsig sigtbl166[1] = {
   { matches_icc_symbol,  2, 0, call_385 } /* line 411 */,
};

/* bne,pt */
static const struct insnsig sigtbl167[1] = {
   { matches_icc_symbol,  2, 0, call_384 } /* line 410 */,
};

/* bneg */
static const struct insnsig sigtbl168[2] = {
   { matches_symbol,  1, 0, call_357 } /* line 380 */,
   { matches_icc_symbol,  2, 0, call_449 } /* line 475 */,
};

/* bneg,a */
static const struct insnsig sigtbl169[2] = {
   { matches_symbol,  1, 0, call_358 } /* line 381 */,
   { matches_icc_symbol,  2, 0, call_452 } /* line 478 */,
};

/* bneg,a,pn */
static const struct insnsig sigtbl170[1] = {
   { matches_icc_symbol,  2, 0, call_454 } /* line 480 */,
};

/* bneg,a,pt */
static const struct insnsig sigtbl171[1] = {
   { matches_icc_symbol,  2, 0, call_453 } /* line 479 */,
};

/* bneg,pn */
static const struct insnsig sigtbl172[1] = {
   { matches_icc_symbol,  2, 0, call_451 } /* line 477 */,
};

/* bneg,pt */
static const struct insnsig sigtbl173[1] = {
   { matches_icc_symbol,  2, 0, call_450 } /* line 476 */,
};

/* bnz */
static const struct insnsig sigtbl174[2] = {
   { matches_symbol,  1, 0, call_363 } /* line 387 */,
   { matches_icc_symbol,  2, 0, call_467 } /* line 494 */,
};

/* bnz,a */
static const struct insnsig sigtbl175[2] = {
   { matches_symbol,  1, 0, call_364 } /* line 388 */,
   { matches_icc_symbol,  2, 0, call_470 } /* line 497 */,
};

/* bnz,a,pn */
static const struct insnsig sigtbl176[1] = {
   { matches_icc_symbol,  2, 0, call_472 } /* line 499 */,
};

/* bnz,a,pt */
static const struct insnsig sigtbl177[1] = {
   { matches_icc_symbol,  2, 0, call_471 } /* line 498 */,
};

/* bnz,pn */
static const struct insnsig sigtbl178[1] = {
   { matches_icc_symbol,  2, 0, call_469 } /* line 496 */,
};

/* bnz,pt */
static const struct insnsig sigtbl179[1] = {
   { matches_icc_symbol,  2, 0, call_468 } /* line 495 */,
};

/* bpos */
static const struct insnsig sigtbl180[2] = {
   { matches_symbol,  1, 0, call_355 } /* line 378 */,
   { matches_icc_symbol,  2, 0, call_443 } /* line 469 */,
};

/* bpos,a */
static const struct insnsig sigtbl181[2] = {
   { matches_symbol,  1, 0, call_356 } /* line 379 */,
   { matches_icc_symbol,  2, 0, call_446 } /* line 472 */,
};

/* bpos,a,pn */
static const struct insnsig sigtbl182[1] = {
   { matches_icc_symbol,  2, 0, call_448 } /* line 474 */,
};

/* bpos,a,pt */
static const struct insnsig sigtbl183[1] = {
   { matches_icc_symbol,  2, 0, call_447 } /* line 473 */,
};

/* bpos,pn */
static const struct insnsig sigtbl184[1] = {
   { matches_icc_symbol,  2, 0, call_445 } /* line 471 */,
};

/* bpos,pt */
static const struct insnsig sigtbl185[1] = {
   { matches_icc_symbol,  2, 0, call_444 } /* line 470 */,
};

/* brgez */
static const struct insnsig sigtbl186[1] = {
   { matches_reg_symbol,  2, 0, call_181 } /* line 196 */,
};

/* brgez,a */
static const struct insnsig sigtbl187[1] = {
   { matches_reg_symbol,  2, 0, call_184 } /* line 199 */,
};

/* brgez,a,pn */
static const struct insnsig sigtbl188[1] = {
   { matches_reg_symbol,  2, 0, call_186 } /* line 201 */,
};

/* brgez,a,pt */
static const struct insnsig sigtbl189[1] = {
   { matches_reg_symbol,  2, 0, call_185 } /* line 200 */,
};

/* brgez,pn */
static const struct insnsig sigtbl190[1] = {
   { matches_reg_symbol,  2, 0, call_183 } /* line 198 */,
};

/* brgez,pt */
static const struct insnsig sigtbl191[1] = {
   { matches_reg_symbol,  2, 0, call_182 } /* line 197 */,
};

/* brgz */
static const struct insnsig sigtbl192[1] = {
   { matches_reg_symbol,  2, 0, call_175 } /* line 190 */,
};

/* brgz,a */
static const struct insnsig sigtbl193[1] = {
   { matches_reg_symbol,  2, 0, call_178 } /* line 193 */,
};

/* brgz,a,pn */
static const struct insnsig sigtbl194[1] = {
   { matches_reg_symbol,  2, 0, call_180 } /* line 195 */,
};

/* brgz,a,pt */
static const struct insnsig sigtbl195[1] = {
   { matches_reg_symbol,  2, 0, call_179 } /* line 194 */,
};

/* brgz,pn */
static const struct insnsig sigtbl196[1] = {
   { matches_reg_symbol,  2, 0, call_177 } /* line 192 */,
};

/* brgz,pt */
static const struct insnsig sigtbl197[1] = {
   { matches_reg_symbol,  2, 0, call_176 } /* line 191 */,
};

/* brlez */
static const struct insnsig sigtbl198[1] = {
   { matches_reg_symbol,  2, 0, call_157 } /* line 172 */,
};

/* brlez,a */
static const struct insnsig sigtbl199[1] = {
   { matches_reg_symbol,  2, 0, call_160 } /* line 175 */,
};

/* brlez,a,pn */
static const struct insnsig sigtbl200[1] = {
   { matches_reg_symbol,  2, 0, call_162 } /* line 177 */,
};

/* brlez,a,pt */
static const struct insnsig sigtbl201[1] = {
   { matches_reg_symbol,  2, 0, call_161 } /* line 176 */,
};

/* brlez,pn */
static const struct insnsig sigtbl202[1] = {
   { matches_reg_symbol,  2, 0, call_159 } /* line 174 */,
};

/* brlez,pt */
static const struct insnsig sigtbl203[1] = {
   { matches_reg_symbol,  2, 0, call_158 } /* line 173 */,
};

/* brlz */
static const struct insnsig sigtbl204[1] = {
   { matches_reg_symbol,  2, 0, call_163 } /* line 178 */,
};

/* brlz,a */
static const struct insnsig sigtbl205[1] = {
   { matches_reg_symbol,  2, 0, call_166 } /* line 181 */,
};

/* brlz,a,pn */
static const struct insnsig sigtbl206[1] = {
   { matches_reg_symbol,  2, 0, call_168 } /* line 183 */,
};

/* brlz,a,pt */
static const struct insnsig sigtbl207[1] = {
   { matches_reg_symbol,  2, 0, call_167 } /* line 182 */,
};

/* brlz,pn */
static const struct insnsig sigtbl208[1] = {
   { matches_reg_symbol,  2, 0, call_165 } /* line 180 */,
};

/* brlz,pt */
static const struct insnsig sigtbl209[1] = {
   { matches_reg_symbol,  2, 0, call_164 } /* line 179 */,
};

/* brnz */
static const struct insnsig sigtbl210[1] = {
   { matches_reg_symbol,  2, 0, call_169 } /* line 184 */,
};

/* brnz,a */
static const struct insnsig sigtbl211[1] = {
   { matches_reg_symbol,  2, 0, call_172 } /* line 187 */,
};

/* brnz,a,pn */
static const struct insnsig sigtbl212[1] = {
   { matches_reg_symbol,  2, 0, call_174 } /* line 189 */,
};

/* brnz,a,pt */
static const struct insnsig sigtbl213[1] = {
   { matches_reg_symbol,  2, 0, call_173 } /* line 188 */,
};

/* brnz,pn */
static const struct insnsig sigtbl214[1] = {
   { matches_reg_symbol,  2, 0, call_171 } /* line 186 */,
};

/* brnz,pt */
static const struct insnsig sigtbl215[1] = {
   { matches_reg_symbol,  2, 0, call_170 } /* line 185 */,
};

/* brz */
static const struct insnsig sigtbl216[1] = {
   { matches_reg_symbol,  2, 0, call_151 } /* line 166 */,
};

/* brz,a */
static const struct insnsig sigtbl217[1] = {
   { matches_reg_symbol,  2, 0, call_154 } /* line 169 */,
};

/* brz,a,pn */
static const struct insnsig sigtbl218[1] = {
   { matches_reg_symbol,  2, 0, call_156 } /* line 171 */,
};

/* brz,a,pt */
static const struct insnsig sigtbl219[1] = {
   { matches_reg_symbol,  2, 0, call_155 } /* line 170 */,
};

/* brz,pn */
static const struct insnsig sigtbl220[1] = {
   { matches_reg_symbol,  2, 0, call_153 } /* line 168 */,
};

/* brz,pt */
static const struct insnsig sigtbl221[1] = {
   { matches_reg_symbol,  2, 0, call_152 } /* line 167 */,
};

/* bset */
static const struct insnsig sigtbl222[2] = {
   { matches_reg_reg,  2, 0, call_989 } /* line 1066 */,
   { matches_i13num_reg,  2, 0, call_990 } /* line 1067 */,
};

/* btog */
static const struct insnsig sigtbl223[2] = {
   { matches_reg_reg,  2, 0, call_993 } /* line 1070 */,
   { matches_i13num_reg,  2, 0, call_994 } /* line 1071 */,
};

/* btst */
static const struct insnsig sigtbl224[2] = {
   { matches_reg_reg,  2, 0, call_987 } /* line 1064 */,
   { matches_i13num_reg,  2, 0, call_988 } /* line 1065 */,
};

/* bvc */
static const struct insnsig sigtbl225[2] = {
   { matches_symbol,  1, 0, call_359 } /* line 382 */,
   { matches_icc_symbol,  2, 0, call_455 } /* line 481 */,
};

/* bvc,a */
static const struct insnsig sigtbl226[2] = {
   { matches_symbol,  1, 0, call_360 } /* line 383 */,
   { matches_icc_symbol,  2, 0, call_458 } /* line 484 */,
};

/* bvc,a,pn */
static const struct insnsig sigtbl227[1] = {
   { matches_icc_symbol,  2, 0, call_460 } /* line 486 */,
};

/* bvc,a,pt */
static const struct insnsig sigtbl228[1] = {
   { matches_icc_symbol,  2, 0, call_459 } /* line 485 */,
};

/* bvc,pn */
static const struct insnsig sigtbl229[1] = {
   { matches_icc_symbol,  2, 0, call_457 } /* line 483 */,
};

/* bvc,pt */
static const struct insnsig sigtbl230[1] = {
   { matches_icc_symbol,  2, 0, call_456 } /* line 482 */,
};

/* bvs */
static const struct insnsig sigtbl231[2] = {
   { matches_symbol,  1, 0, call_361 } /* line 384 */,
   { matches_icc_symbol,  2, 0, call_461 } /* line 487 */,
};

/* bvs,a */
static const struct insnsig sigtbl232[2] = {
   { matches_symbol,  1, 0, call_362 } /* line 385 */,
   { matches_icc_symbol,  2, 0, call_464 } /* line 490 */,
};

/* bvs,a,pn */
static const struct insnsig sigtbl233[1] = {
   { matches_icc_symbol,  2, 0, call_466 } /* line 492 */,
};

/* bvs,a,pt */
static const struct insnsig sigtbl234[1] = {
   { matches_icc_symbol,  2, 0, call_465 } /* line 491 */,
};

/* bvs,pn */
static const struct insnsig sigtbl235[1] = {
   { matches_icc_symbol,  2, 0, call_463 } /* line 489 */,
};

/* bvs,pt */
static const struct insnsig sigtbl236[1] = {
   { matches_icc_symbol,  2, 0, call_462 } /* line 488 */,
};

/* bz */
static const struct insnsig sigtbl237[2] = {
   { matches_symbol,  1, 0, call_365 } /* line 389 */,
   { matches_icc_symbol,  2, 0, call_473 } /* line 500 */,
};

/* bz,a */
static const struct insnsig sigtbl238[2] = {
   { matches_symbol,  1, 0, call_366 } /* line 390 */,
   { matches_icc_symbol,  2, 0, call_476 } /* line 503 */,
};

/* bz,a,pn */
static const struct insnsig sigtbl239[1] = {
   { matches_icc_symbol,  2, 0, call_478 } /* line 505 */,
};

/* bz,a,pt */
static const struct insnsig sigtbl240[1] = {
   { matches_icc_symbol,  2, 0, call_477 } /* line 504 */,
};

/* bz,pn */
static const struct insnsig sigtbl241[1] = {
   { matches_icc_symbol,  2, 0, call_475 } /* line 502 */,
};

/* bz,pt */
static const struct insnsig sigtbl242[1] = {
   { matches_icc_symbol,  2, 0, call_474 } /* line 501 */,
};

/* call */
static const struct insnsig sigtbl243[6] = {
   { matches_symbol,  1, 0, call_889 } /* line 949 */,
   { matches_symbol_number,  2, 0, call_890 } /* line 950 */,
   { matches_addr_rr,  1, 0, call_955 } /* line 1029 */,
   { matches_addr_ri,  1, 0, call_956 } /* line 1030 */,
   { matches_addr_rr_number,  2, 0, call_957 } /* line 1031 */,
   { matches_addr_ri_number,  2, 0, call_958 } /* line 1032 */,
};

/* cas */
static const struct insnsig sigtbl244[1] = {
   { matches_braddr_r_reg_reg,  3, 0, call_975 } /* line 1050 */,
};

/* casa */
static const struct insnsig sigtbl245[2] = {
   { matches_braddr_r_immasi_reg_reg,  3, 0, call_729 } /* line 772 */,
   { matches_braddr_r_asi_reg_reg,  3, 0, call_730 } /* line 773 */,
};

/* casl */
static const struct insnsig sigtbl246[1] = {
   { matches_braddr_r_reg_reg,  3, 0, call_976 } /* line 1051 */,
};

/* casn */
static const struct insnsig sigtbl247[1] = {
   { matches_braddr_r_reg_reg,  3, 0, call_1024 } /* line 1107 */,
};

/* casna */
static const struct insnsig sigtbl248[2] = {
   { matches_braddr_r_immasi_reg_reg,  3, 0, call_1025 } /* line 1108 */,
   { matches_braddr_r_asi_reg_reg,  3, 0, call_1026 } /* line 1109 */,
};

/* casx */
static const struct insnsig sigtbl249[1] = {
   { matches_braddr_r_reg_reg,  3, 0, call_977 } /* line 1052 */,
};

/* casxa */
static const struct insnsig sigtbl250[2] = {
   { matches_braddr_r_immasi_reg_reg,  3, 0, call_731 } /* line 774 */,
   { matches_braddr_r_asi_reg_reg,  3, 0, call_732 } /* line 775 */,
};

/* casxl */
static const struct insnsig sigtbl251[1] = {
   { matches_braddr_r_reg_reg,  3, 0, call_978 } /* line 1053 */,
};

/* clr */
static const struct insnsig sigtbl252[3] = {
   { matches_reg,    1, 0, call_995 } /* line 1073 */,
   { matches_braddr_rr,  1, 0, call_1000 } /* line 1078 */,
   { matches_braddr_ri,  1, 0, call_1001 } /* line 1079 */,
};

/* clrb */
static const struct insnsig sigtbl253[2] = {
   { matches_braddr_rr,  1, 0, call_996 } /* line 1074 */,
   { matches_braddr_ri,  1, 0, call_997 } /* line 1075 */,
};

/* clrh */
static const struct insnsig sigtbl254[2] = {
   { matches_braddr_rr,  1, 0, call_998 } /* line 1076 */,
   { matches_braddr_ri,  1, 0, call_999 } /* line 1077 */,
};

/* clrn */
static const struct insnsig sigtbl255[2] = {
   { matches_braddr_rr,  1, 0, call_1027 } /* line 1110 */,
   { matches_braddr_ri,  1, 0, call_1028 } /* line 1111 */,
};

/* clruw */
static const struct insnsig sigtbl256[2] = {
   { matches_reg_reg,  2, 0, call_1004 } /* line 1083 */,
   { matches_reg,    1, 0, call_1005 } /* line 1084 */,
};

/* clrx */
static const struct insnsig sigtbl257[2] = {
   { matches_braddr_rr,  1, 0, call_1002 } /* line 1080 */,
   { matches_braddr_ri,  1, 0, call_1003 } /* line 1081 */,
};

/* cmp */
static const struct insnsig sigtbl258[2] = {
   { matches_reg_reg,  2, 0, call_951 } /* line 1025 */,
   { matches_reg_i13num,  2, 0, call_952 } /* line 1026 */,
};

/* dec */
static const struct insnsig sigtbl259[2] = {
   { matches_reg,    1, 0, call_983 } /* line 1059 */,
   { matches_i13num_reg,  2, 0, call_984 } /* line 1060 */,
};

/* deccc */
static const struct insnsig sigtbl260[2] = {
   { matches_reg,    1, 0, call_985 } /* line 1061 */,
   { matches_i13num_reg,  2, 0, call_986 } /* line 1062 */,
};

/* done */
static const struct insnsig sigtbl261[1] = {
   { NULL,           0, 0, call_946 } /* line 1016 */,
};

/* fabsd */
static const struct insnsig sigtbl262[1] = {
   { matches_freg_freg,  2, 0, call_138 } /* line 151 */,
};

/* fabsq */
static const struct insnsig sigtbl263[1] = {
   { matches_freg_freg,  2, 0, call_139 } /* line 152 */,
};

/* fabss */
static const struct insnsig sigtbl264[1] = {
   { matches_freg_freg,  2, 0, call_137 } /* line 150 */,
};

/* faddd */
static const struct insnsig sigtbl265[1] = {
   { matches_freg_freg_freg,  3, 0, call_102 } /* line 112 */,
};

/* faddq */
static const struct insnsig sigtbl266[1] = {
   { matches_freg_freg_freg,  3, 0, call_103 } /* line 113 */,
};

/* fadds */
static const struct insnsig sigtbl267[1] = {
   { matches_freg_freg_freg,  3, 0, call_101 } /* line 111 */,
};

/* fba */
static const struct insnsig sigtbl268[2] = {
   { matches_symbol,  1, 0, call_187 } /* line 204 */,
   { matches_fcc_symbol,  2, 0, call_223 } /* line 243 */,
};

/* fba,a */
static const struct insnsig sigtbl269[2] = {
   { matches_symbol,  1, 0, call_188 } /* line 205 */,
   { matches_fcc_symbol,  2, 0, call_226 } /* line 246 */,
};

/* fba,a,pn */
static const struct insnsig sigtbl270[1] = {
   { matches_fcc_symbol,  2, 0, call_228 } /* line 248 */,
};

/* fba,a,pt */
static const struct insnsig sigtbl271[1] = {
   { matches_fcc_symbol,  2, 0, call_227 } /* line 247 */,
};

/* fba,pn */
static const struct insnsig sigtbl272[1] = {
   { matches_fcc_symbol,  2, 0, call_225 } /* line 245 */,
};

/* fba,pt */
static const struct insnsig sigtbl273[1] = {
   { matches_fcc_symbol,  2, 0, call_224 } /* line 244 */,
};

/* fbe */
static const struct insnsig sigtbl274[2] = {
   { matches_symbol,  1, 0, call_205 } /* line 222 */,
   { matches_fcc_symbol,  2, 0, call_277 } /* line 297 */,
};

/* fbe,a */
static const struct insnsig sigtbl275[2] = {
   { matches_symbol,  1, 0, call_206 } /* line 223 */,
   { matches_fcc_symbol,  2, 0, call_280 } /* line 300 */,
};

/* fbe,a,pn */
static const struct insnsig sigtbl276[1] = {
   { matches_fcc_symbol,  2, 0, call_282 } /* line 302 */,
};

/* fbe,a,pt */
static const struct insnsig sigtbl277[1] = {
   { matches_fcc_symbol,  2, 0, call_281 } /* line 301 */,
};

/* fbe,pn */
static const struct insnsig sigtbl278[1] = {
   { matches_fcc_symbol,  2, 0, call_279 } /* line 299 */,
};

/* fbe,pt */
static const struct insnsig sigtbl279[1] = {
   { matches_fcc_symbol,  2, 0, call_278 } /* line 298 */,
};

/* fbg */
static const struct insnsig sigtbl280[2] = {
   { matches_symbol,  1, 0, call_193 } /* line 210 */,
   { matches_fcc_symbol,  2, 0, call_241 } /* line 261 */,
};

/* fbg,a */
static const struct insnsig sigtbl281[2] = {
   { matches_symbol,  1, 0, call_194 } /* line 211 */,
   { matches_fcc_symbol,  2, 0, call_244 } /* line 264 */,
};

/* fbg,a,pn */
static const struct insnsig sigtbl282[1] = {
   { matches_fcc_symbol,  2, 0, call_246 } /* line 266 */,
};

/* fbg,a,pt */
static const struct insnsig sigtbl283[1] = {
   { matches_fcc_symbol,  2, 0, call_245 } /* line 265 */,
};

/* fbg,pn */
static const struct insnsig sigtbl284[1] = {
   { matches_fcc_symbol,  2, 0, call_243 } /* line 263 */,
};

/* fbg,pt */
static const struct insnsig sigtbl285[1] = {
   { matches_fcc_symbol,  2, 0, call_242 } /* line 262 */,
};

/* fbge */
static const struct insnsig sigtbl286[2] = {
   { matches_symbol,  1, 0, call_209 } /* line 226 */,
   { matches_fcc_symbol,  2, 0, call_289 } /* line 309 */,
};

/* fbge,a */
static const struct insnsig sigtbl287[2] = {
   { matches_symbol,  1, 0, call_210 } /* line 227 */,
   { matches_fcc_symbol,  2, 0, call_292 } /* line 312 */,
};

/* fbge,a,pn */
static const struct insnsig sigtbl288[1] = {
   { matches_fcc_symbol,  2, 0, call_294 } /* line 314 */,
};

/* fbge,a,pt */
static const struct insnsig sigtbl289[1] = {
   { matches_fcc_symbol,  2, 0, call_293 } /* line 313 */,
};

/* fbge,pn */
static const struct insnsig sigtbl290[1] = {
   { matches_fcc_symbol,  2, 0, call_291 } /* line 311 */,
};

/* fbge,pt */
static const struct insnsig sigtbl291[1] = {
   { matches_fcc_symbol,  2, 0, call_290 } /* line 310 */,
};

/* fbl */
static const struct insnsig sigtbl292[2] = {
   { matches_symbol,  1, 0, call_197 } /* line 214 */,
   { matches_fcc_symbol,  2, 0, call_253 } /* line 273 */,
};

/* fbl,a */
static const struct insnsig sigtbl293[2] = {
   { matches_symbol,  1, 0, call_198 } /* line 215 */,
   { matches_fcc_symbol,  2, 0, call_256 } /* line 276 */,
};

/* fbl,a,pn */
static const struct insnsig sigtbl294[1] = {
   { matches_fcc_symbol,  2, 0, call_258 } /* line 278 */,
};

/* fbl,a,pt */
static const struct insnsig sigtbl295[1] = {
   { matches_fcc_symbol,  2, 0, call_257 } /* line 277 */,
};

/* fbl,pn */
static const struct insnsig sigtbl296[1] = {
   { matches_fcc_symbol,  2, 0, call_255 } /* line 275 */,
};

/* fbl,pt */
static const struct insnsig sigtbl297[1] = {
   { matches_fcc_symbol,  2, 0, call_254 } /* line 274 */,
};

/* fble */
static const struct insnsig sigtbl298[2] = {
   { matches_symbol,  1, 0, call_213 } /* line 230 */,
   { matches_fcc_symbol,  2, 0, call_301 } /* line 321 */,
};

/* fble,a */
static const struct insnsig sigtbl299[2] = {
   { matches_symbol,  1, 0, call_214 } /* line 231 */,
   { matches_fcc_symbol,  2, 0, call_304 } /* line 324 */,
};

/* fble,a,pn */
static const struct insnsig sigtbl300[1] = {
   { matches_fcc_symbol,  2, 0, call_306 } /* line 326 */,
};

/* fble,a,pt */
static const struct insnsig sigtbl301[1] = {
   { matches_fcc_symbol,  2, 0, call_305 } /* line 325 */,
};

/* fble,pn */
static const struct insnsig sigtbl302[1] = {
   { matches_fcc_symbol,  2, 0, call_303 } /* line 323 */,
};

/* fble,pt */
static const struct insnsig sigtbl303[1] = {
   { matches_fcc_symbol,  2, 0, call_302 } /* line 322 */,
};

/* fblg */
static const struct insnsig sigtbl304[2] = {
   { matches_symbol,  1, 0, call_201 } /* line 218 */,
   { matches_fcc_symbol,  2, 0, call_265 } /* line 285 */,
};

/* fblg,a */
static const struct insnsig sigtbl305[2] = {
   { matches_symbol,  1, 0, call_202 } /* line 219 */,
   { matches_fcc_symbol,  2, 0, call_268 } /* line 288 */,
};

/* fblg,a,pn */
static const struct insnsig sigtbl306[1] = {
   { matches_fcc_symbol,  2, 0, call_270 } /* line 290 */,
};

/* fblg,a,pt */
static const struct insnsig sigtbl307[1] = {
   { matches_fcc_symbol,  2, 0, call_269 } /* line 289 */,
};

/* fblg,pn */
static const struct insnsig sigtbl308[1] = {
   { matches_fcc_symbol,  2, 0, call_267 } /* line 287 */,
};

/* fblg,pt */
static const struct insnsig sigtbl309[1] = {
   { matches_fcc_symbol,  2, 0, call_266 } /* line 286 */,
};

/* fbn */
static const struct insnsig sigtbl310[2] = {
   { matches_symbol,  1, 0, call_189 } /* line 206 */,
   { matches_fcc_symbol,  2, 0, call_229 } /* line 249 */,
};

/* fbn,a */
static const struct insnsig sigtbl311[2] = {
   { matches_symbol,  1, 0, call_190 } /* line 207 */,
   { matches_fcc_symbol,  2, 0, call_232 } /* line 252 */,
};

/* fbn,a,pn */
static const struct insnsig sigtbl312[1] = {
   { matches_fcc_symbol,  2, 0, call_234 } /* line 254 */,
};

/* fbn,a,pt */
static const struct insnsig sigtbl313[1] = {
   { matches_fcc_symbol,  2, 0, call_233 } /* line 253 */,
};

/* fbn,pn */
static const struct insnsig sigtbl314[1] = {
   { matches_fcc_symbol,  2, 0, call_231 } /* line 251 */,
};

/* fbn,pt */
static const struct insnsig sigtbl315[1] = {
   { matches_fcc_symbol,  2, 0, call_230 } /* line 250 */,
};

/* fbne */
static const struct insnsig sigtbl316[2] = {
   { matches_symbol,  1, 0, call_203 } /* line 220 */,
   { matches_fcc_symbol,  2, 0, call_271 } /* line 291 */,
};

/* fbne,a */
static const struct insnsig sigtbl317[2] = {
   { matches_symbol,  1, 0, call_204 } /* line 221 */,
   { matches_fcc_symbol,  2, 0, call_274 } /* line 294 */,
};

/* fbne,a,pn */
static const struct insnsig sigtbl318[1] = {
   { matches_fcc_symbol,  2, 0, call_276 } /* line 296 */,
};

/* fbne,a,pt */
static const struct insnsig sigtbl319[1] = {
   { matches_fcc_symbol,  2, 0, call_275 } /* line 295 */,
};

/* fbne,pn */
static const struct insnsig sigtbl320[1] = {
   { matches_fcc_symbol,  2, 0, call_273 } /* line 293 */,
};

/* fbne,pt */
static const struct insnsig sigtbl321[1] = {
   { matches_fcc_symbol,  2, 0, call_272 } /* line 292 */,
};

/* fbnz */
static const struct insnsig sigtbl322[2] = {
   { matches_symbol,  1, 0, call_219 } /* line 237 */,
   { matches_fcc_symbol,  2, 0, call_319 } /* line 340 */,
};

/* fbnz,a */
static const struct insnsig sigtbl323[2] = {
   { matches_symbol,  1, 0, call_220 } /* line 238 */,
   { matches_fcc_symbol,  2, 0, call_322 } /* line 343 */,
};

/* fbnz,a,pn */
static const struct insnsig sigtbl324[1] = {
   { matches_fcc_symbol,  2, 0, call_324 } /* line 345 */,
};

/* fbnz,a,pt */
static const struct insnsig sigtbl325[1] = {
   { matches_fcc_symbol,  2, 0, call_323 } /* line 344 */,
};

/* fbnz,pn */
static const struct insnsig sigtbl326[1] = {
   { matches_fcc_symbol,  2, 0, call_321 } /* line 342 */,
};

/* fbnz,pt */
static const struct insnsig sigtbl327[1] = {
   { matches_fcc_symbol,  2, 0, call_320 } /* line 341 */,
};

/* fbo */
static const struct insnsig sigtbl328[2] = {
   { matches_symbol,  1, 0, call_217 } /* line 234 */,
   { matches_fcc_symbol,  2, 0, call_313 } /* line 333 */,
};

/* fbo,a */
static const struct insnsig sigtbl329[2] = {
   { matches_symbol,  1, 0, call_218 } /* line 235 */,
   { matches_fcc_symbol,  2, 0, call_316 } /* line 336 */,
};

/* fbo,a,pn */
static const struct insnsig sigtbl330[1] = {
   { matches_fcc_symbol,  2, 0, call_318 } /* line 338 */,
};

/* fbo,a,pt */
static const struct insnsig sigtbl331[1] = {
   { matches_fcc_symbol,  2, 0, call_317 } /* line 337 */,
};

/* fbo,pn */
static const struct insnsig sigtbl332[1] = {
   { matches_fcc_symbol,  2, 0, call_315 } /* line 335 */,
};

/* fbo,pt */
static const struct insnsig sigtbl333[1] = {
   { matches_fcc_symbol,  2, 0, call_314 } /* line 334 */,
};

/* fbu */
static const struct insnsig sigtbl334[2] = {
   { matches_symbol,  1, 0, call_191 } /* line 208 */,
   { matches_fcc_symbol,  2, 0, call_235 } /* line 255 */,
};

/* fbu,a */
static const struct insnsig sigtbl335[2] = {
   { matches_symbol,  1, 0, call_192 } /* line 209 */,
   { matches_fcc_symbol,  2, 0, call_238 } /* line 258 */,
};

/* fbu,a,pn */
static const struct insnsig sigtbl336[1] = {
   { matches_fcc_symbol,  2, 0, call_240 } /* line 260 */,
};

/* fbu,a,pt */
static const struct insnsig sigtbl337[1] = {
   { matches_fcc_symbol,  2, 0, call_239 } /* line 259 */,
};

/* fbu,pn */
static const struct insnsig sigtbl338[1] = {
   { matches_fcc_symbol,  2, 0, call_237 } /* line 257 */,
};

/* fbu,pt */
static const struct insnsig sigtbl339[1] = {
   { matches_fcc_symbol,  2, 0, call_236 } /* line 256 */,
};

/* fbue */
static const struct insnsig sigtbl340[2] = {
   { matches_symbol,  1, 0, call_207 } /* line 224 */,
   { matches_fcc_symbol,  2, 0, call_283 } /* line 303 */,
};

/* fbue,a */
static const struct insnsig sigtbl341[2] = {
   { matches_symbol,  1, 0, call_208 } /* line 225 */,
   { matches_fcc_symbol,  2, 0, call_286 } /* line 306 */,
};

/* fbue,a,pn */
static const struct insnsig sigtbl342[1] = {
   { matches_fcc_symbol,  2, 0, call_288 } /* line 308 */,
};

/* fbue,a,pt */
static const struct insnsig sigtbl343[1] = {
   { matches_fcc_symbol,  2, 0, call_287 } /* line 307 */,
};

/* fbue,pn */
static const struct insnsig sigtbl344[1] = {
   { matches_fcc_symbol,  2, 0, call_285 } /* line 305 */,
};

/* fbue,pt */
static const struct insnsig sigtbl345[1] = {
   { matches_fcc_symbol,  2, 0, call_284 } /* line 304 */,
};

/* fbug */
static const struct insnsig sigtbl346[2] = {
   { matches_symbol,  1, 0, call_195 } /* line 212 */,
   { matches_fcc_symbol,  2, 0, call_247 } /* line 267 */,
};

/* fbug,a */
static const struct insnsig sigtbl347[2] = {
   { matches_symbol,  1, 0, call_196 } /* line 213 */,
   { matches_fcc_symbol,  2, 0, call_250 } /* line 270 */,
};

/* fbug,a,pn */
static const struct insnsig sigtbl348[1] = {
   { matches_fcc_symbol,  2, 0, call_252 } /* line 272 */,
};

/* fbug,a,pt */
static const struct insnsig sigtbl349[1] = {
   { matches_fcc_symbol,  2, 0, call_251 } /* line 271 */,
};

/* fbug,pn */
static const struct insnsig sigtbl350[1] = {
   { matches_fcc_symbol,  2, 0, call_249 } /* line 269 */,
};

/* fbug,pt */
static const struct insnsig sigtbl351[1] = {
   { matches_fcc_symbol,  2, 0, call_248 } /* line 268 */,
};

/* fbuge */
static const struct insnsig sigtbl352[2] = {
   { matches_symbol,  1, 0, call_211 } /* line 228 */,
   { matches_fcc_symbol,  2, 0, call_295 } /* line 315 */,
};

/* fbuge,a */
static const struct insnsig sigtbl353[2] = {
   { matches_symbol,  1, 0, call_212 } /* line 229 */,
   { matches_fcc_symbol,  2, 0, call_298 } /* line 318 */,
};

/* fbuge,a,pn */
static const struct insnsig sigtbl354[1] = {
   { matches_fcc_symbol,  2, 0, call_300 } /* line 320 */,
};

/* fbuge,a,pt */
static const struct insnsig sigtbl355[1] = {
   { matches_fcc_symbol,  2, 0, call_299 } /* line 319 */,
};

/* fbuge,pn */
static const struct insnsig sigtbl356[1] = {
   { matches_fcc_symbol,  2, 0, call_297 } /* line 317 */,
};

/* fbuge,pt */
static const struct insnsig sigtbl357[1] = {
   { matches_fcc_symbol,  2, 0, call_296 } /* line 316 */,
};

/* fbul */
static const struct insnsig sigtbl358[2] = {
   { matches_symbol,  1, 0, call_199 } /* line 216 */,
   { matches_fcc_symbol,  2, 0, call_259 } /* line 279 */,
};

/* fbul,a */
static const struct insnsig sigtbl359[2] = {
   { matches_symbol,  1, 0, call_200 } /* line 217 */,
   { matches_fcc_symbol,  2, 0, call_262 } /* line 282 */,
};

/* fbul,a,pn */
static const struct insnsig sigtbl360[1] = {
   { matches_fcc_symbol,  2, 0, call_264 } /* line 284 */,
};

/* fbul,a,pt */
static const struct insnsig sigtbl361[1] = {
   { matches_fcc_symbol,  2, 0, call_263 } /* line 283 */,
};

/* fbul,pn */
static const struct insnsig sigtbl362[1] = {
   { matches_fcc_symbol,  2, 0, call_261 } /* line 281 */,
};

/* fbul,pt */
static const struct insnsig sigtbl363[1] = {
   { matches_fcc_symbol,  2, 0, call_260 } /* line 280 */,
};

/* fbule */
static const struct insnsig sigtbl364[2] = {
   { matches_symbol,  1, 0, call_215 } /* line 232 */,
   { matches_fcc_symbol,  2, 0, call_307 } /* line 327 */,
};

/* fbule,a */
static const struct insnsig sigtbl365[2] = {
   { matches_symbol,  1, 0, call_216 } /* line 233 */,
   { matches_fcc_symbol,  2, 0, call_310 } /* line 330 */,
};

/* fbule,a,pn */
static const struct insnsig sigtbl366[1] = {
   { matches_fcc_symbol,  2, 0, call_312 } /* line 332 */,
};

/* fbule,a,pt */
static const struct insnsig sigtbl367[1] = {
   { matches_fcc_symbol,  2, 0, call_311 } /* line 331 */,
};

/* fbule,pn */
static const struct insnsig sigtbl368[1] = {
   { matches_fcc_symbol,  2, 0, call_309 } /* line 329 */,
};

/* fbule,pt */
static const struct insnsig sigtbl369[1] = {
   { matches_fcc_symbol,  2, 0, call_308 } /* line 328 */,
};

/* fbz */
static const struct insnsig sigtbl370[2] = {
   { matches_symbol,  1, 0, call_221 } /* line 239 */,
   { matches_fcc_symbol,  2, 0, call_325 } /* line 346 */,
};

/* fbz,a */
static const struct insnsig sigtbl371[2] = {
   { matches_symbol,  1, 0, call_222 } /* line 240 */,
   { matches_fcc_symbol,  2, 0, call_328 } /* line 349 */,
};

/* fbz,a,pn */
static const struct insnsig sigtbl372[1] = {
   { matches_fcc_symbol,  2, 0, call_330 } /* line 351 */,
};

/* fbz,a,pt */
static const struct insnsig sigtbl373[1] = {
   { matches_fcc_symbol,  2, 0, call_329 } /* line 350 */,
};

/* fbz,pn */
static const struct insnsig sigtbl374[1] = {
   { matches_fcc_symbol,  2, 0, call_327 } /* line 348 */,
};

/* fbz,pt */
static const struct insnsig sigtbl375[1] = {
   { matches_fcc_symbol,  2, 0, call_326 } /* line 347 */,
};

/* fcmpd */
static const struct insnsig sigtbl376[1] = {
   { matches_fcc_freg_freg,  3, 0, call_108 } /* line 119 */,
};

/* fcmped */
static const struct insnsig sigtbl377[1] = {
   { matches_fcc_freg_freg,  3, 0, call_111 } /* line 122 */,
};

/* fcmpeq */
static const struct insnsig sigtbl378[1] = {
   { matches_fcc_freg_freg,  3, 0, call_112 } /* line 123 */,
};

/* fcmpes */
static const struct insnsig sigtbl379[1] = {
   { matches_fcc_freg_freg,  3, 0, call_110 } /* line 121 */,
};

/* fcmpq */
static const struct insnsig sigtbl380[1] = {
   { matches_fcc_freg_freg,  3, 0, call_109 } /* line 120 */,
};

/* fcmps */
static const struct insnsig sigtbl381[1] = {
   { matches_fcc_freg_freg,  3, 0, call_107 } /* line 118 */,
};

/* fdivd */
static const struct insnsig sigtbl382[1] = {
   { matches_freg_freg_freg,  3, 0, call_149 } /* line 163 */,
};

/* fdivq */
static const struct insnsig sigtbl383[1] = {
   { matches_freg_freg_freg,  3, 0, call_150 } /* line 164 */,
};

/* fdivs */
static const struct insnsig sigtbl384[1] = {
   { matches_freg_freg_freg,  3, 0, call_148 } /* line 162 */,
};

/* fdmulq */
static const struct insnsig sigtbl385[1] = {
   { matches_freg_freg_freg,  3, 0, call_147 } /* line 161 */,
};

/* fdtoi */
static const struct insnsig sigtbl386[1] = {
   { matches_freg_freg,  2, 0, call_117 } /* line 129 */,
};

/* fdtoq */
static const struct insnsig sigtbl387[1] = {
   { matches_freg_freg,  2, 0, call_128 } /* line 140 */,
};

/* fdtos */
static const struct insnsig sigtbl388[1] = {
   { matches_freg_freg,  2, 0, call_127 } /* line 139 */,
};

/* fdtox */
static const struct insnsig sigtbl389[1] = {
   { matches_freg_freg,  2, 0, call_114 } /* line 126 */,
};

/* fitod */
static const struct insnsig sigtbl390[1] = {
   { matches_freg_freg,  2, 0, call_123 } /* line 135 */,
};

/* fitoq */
static const struct insnsig sigtbl391[1] = {
   { matches_freg_freg,  2, 0, call_124 } /* line 136 */,
};

/* fitos */
static const struct insnsig sigtbl392[1] = {
   { matches_freg_freg,  2, 0, call_122 } /* line 134 */,
};

/* flush */
static const struct insnsig sigtbl393[2] = {
   { matches_addr_rr,  1, 0, call_723 } /* line 764 */,
   { matches_addr_ri,  1, 0, call_724 } /* line 765 */,
};

/* flushw */
static const struct insnsig sigtbl394[1] = {
   { NULL,           0, 0, call_948 } /* line 1018 */,
};

/* fmovd */
static const struct insnsig sigtbl395[1] = {
   { matches_freg_freg,  2, 0, call_132 } /* line 145 */,
};

/* fmovda */
static const struct insnsig sigtbl396[2] = {
   { matches_icc_freg_freg,  3, 0, call_492 } /* line 520 */,
   { matches_fcc_freg_freg,  3, 0, call_552 } /* line 582 */,
};

/* fmovdcc */
static const struct insnsig sigtbl397[1] = {
   { matches_icc_freg_freg,  3, 0, call_522 } /* line 550 */,
};

/* fmovdcs */
static const struct insnsig sigtbl398[1] = {
   { matches_icc_freg_freg,  3, 0, call_525 } /* line 553 */,
};

/* fmovde */
static const struct insnsig sigtbl399[2] = {
   { matches_icc_freg_freg,  3, 0, call_501 } /* line 529 */,
   { matches_fcc_freg_freg,  3, 0, call_579 } /* line 609 */,
};

/* fmovdg */
static const struct insnsig sigtbl400[2] = {
   { matches_icc_freg_freg,  3, 0, call_504 } /* line 532 */,
   { matches_fcc_freg_freg,  3, 0, call_561 } /* line 591 */,
};

/* fmovdge */
static const struct insnsig sigtbl401[2] = {
   { matches_icc_freg_freg,  3, 0, call_510 } /* line 538 */,
   { matches_fcc_freg_freg,  3, 0, call_585 } /* line 615 */,
};

/* fmovdgeu */
static const struct insnsig sigtbl402[1] = {
   { matches_icc_freg_freg,  3, 0, call_546 } /* line 575 */,
};

/* fmovdgu */
static const struct insnsig sigtbl403[1] = {
   { matches_icc_freg_freg,  3, 0, call_516 } /* line 544 */,
};

/* fmovdl */
static const struct insnsig sigtbl404[2] = {
   { matches_icc_freg_freg,  3, 0, call_513 } /* line 541 */,
   { matches_fcc_freg_freg,  3, 0, call_567 } /* line 597 */,
};

/* fmovdle */
static const struct insnsig sigtbl405[2] = {
   { matches_icc_freg_freg,  3, 0, call_507 } /* line 535 */,
   { matches_fcc_freg_freg,  3, 0, call_591 } /* line 621 */,
};

/* fmovdleu */
static const struct insnsig sigtbl406[1] = {
   { matches_icc_freg_freg,  3, 0, call_519 } /* line 547 */,
};

/* fmovdlg */
static const struct insnsig sigtbl407[1] = {
   { matches_fcc_freg_freg,  3, 0, call_573 } /* line 603 */,
};

/* fmovdlu */
static const struct insnsig sigtbl408[1] = {
   { matches_icc_freg_freg,  3, 0, call_549 } /* line 578 */,
};

/* fmovdn */
static const struct insnsig sigtbl409[2] = {
   { matches_icc_freg_freg,  3, 0, call_495 } /* line 523 */,
   { matches_fcc_freg_freg,  3, 0, call_555 } /* line 585 */,
};

/* fmovdne */
static const struct insnsig sigtbl410[2] = {
   { matches_icc_freg_freg,  3, 0, call_498 } /* line 526 */,
   { matches_fcc_freg_freg,  3, 0, call_576 } /* line 606 */,
};

/* fmovdneg */
static const struct insnsig sigtbl411[1] = {
   { matches_icc_freg_freg,  3, 0, call_531 } /* line 559 */,
};

/* fmovdnz */
static const struct insnsig sigtbl412[2] = {
   { matches_icc_freg_freg,  3, 0, call_540 } /* line 569 */,
   { matches_fcc_freg_freg,  3, 0, call_600 } /* line 631 */,
};

/* fmovdo */
static const struct insnsig sigtbl413[1] = {
   { matches_fcc_freg_freg,  3, 0, call_597 } /* line 627 */,
};

/* fmovdpos */
static const struct insnsig sigtbl414[1] = {
   { matches_icc_freg_freg,  3, 0, call_528 } /* line 556 */,
};

/* fmovdu */
static const struct insnsig sigtbl415[1] = {
   { matches_fcc_freg_freg,  3, 0, call_558 } /* line 588 */,
};

/* fmovdue */
static const struct insnsig sigtbl416[1] = {
   { matches_fcc_freg_freg,  3, 0, call_582 } /* line 612 */,
};

/* fmovdug */
static const struct insnsig sigtbl417[1] = {
   { matches_fcc_freg_freg,  3, 0, call_564 } /* line 594 */,
};

/* fmovduge */
static const struct insnsig sigtbl418[1] = {
   { matches_fcc_freg_freg,  3, 0, call_588 } /* line 618 */,
};

/* fmovdul */
static const struct insnsig sigtbl419[1] = {
   { matches_fcc_freg_freg,  3, 0, call_570 } /* line 600 */,
};

/* fmovdule */
static const struct insnsig sigtbl420[1] = {
   { matches_fcc_freg_freg,  3, 0, call_594 } /* line 624 */,
};

/* fmovdvc */
static const struct insnsig sigtbl421[1] = {
   { matches_icc_freg_freg,  3, 0, call_534 } /* line 562 */,
};

/* fmovdvs */
static const struct insnsig sigtbl422[1] = {
   { matches_icc_freg_freg,  3, 0, call_537 } /* line 565 */,
};

/* fmovdz */
static const struct insnsig sigtbl423[2] = {
   { matches_icc_freg_freg,  3, 0, call_543 } /* line 572 */,
   { matches_fcc_freg_freg,  3, 0, call_603 } /* line 634 */,
};

/* fmovq */
static const struct insnsig sigtbl424[1] = {
   { matches_freg_freg,  2, 0, call_133 } /* line 146 */,
};

/* fmovqa */
static const struct insnsig sigtbl425[2] = {
   { matches_icc_freg_freg,  3, 0, call_493 } /* line 521 */,
   { matches_fcc_freg_freg,  3, 0, call_553 } /* line 583 */,
};

/* fmovqcc */
static const struct insnsig sigtbl426[1] = {
   { matches_icc_freg_freg,  3, 0, call_523 } /* line 551 */,
};

/* fmovqcs */
static const struct insnsig sigtbl427[1] = {
   { matches_icc_freg_freg,  3, 0, call_526 } /* line 554 */,
};

/* fmovqe */
static const struct insnsig sigtbl428[2] = {
   { matches_icc_freg_freg,  3, 0, call_502 } /* line 530 */,
   { matches_fcc_freg_freg,  3, 0, call_580 } /* line 610 */,
};

/* fmovqg */
static const struct insnsig sigtbl429[2] = {
   { matches_icc_freg_freg,  3, 0, call_505 } /* line 533 */,
   { matches_fcc_freg_freg,  3, 0, call_562 } /* line 592 */,
};

/* fmovqge */
static const struct insnsig sigtbl430[2] = {
   { matches_icc_freg_freg,  3, 0, call_511 } /* line 539 */,
   { matches_fcc_freg_freg,  3, 0, call_586 } /* line 616 */,
};

/* fmovqgeu */
static const struct insnsig sigtbl431[1] = {
   { matches_icc_freg_freg,  3, 0, call_547 } /* line 576 */,
};

/* fmovqgu */
static const struct insnsig sigtbl432[1] = {
   { matches_icc_freg_freg,  3, 0, call_517 } /* line 545 */,
};

/* fmovql */
static const struct insnsig sigtbl433[2] = {
   { matches_icc_freg_freg,  3, 0, call_514 } /* line 542 */,
   { matches_fcc_freg_freg,  3, 0, call_568 } /* line 598 */,
};

/* fmovqle */
static const struct insnsig sigtbl434[2] = {
   { matches_icc_freg_freg,  3, 0, call_508 } /* line 536 */,
   { matches_fcc_freg_freg,  3, 0, call_592 } /* line 622 */,
};

/* fmovqleu */
static const struct insnsig sigtbl435[1] = {
   { matches_icc_freg_freg,  3, 0, call_520 } /* line 548 */,
};

/* fmovqlg */
static const struct insnsig sigtbl436[1] = {
   { matches_fcc_freg_freg,  3, 0, call_574 } /* line 604 */,
};

/* fmovqlu */
static const struct insnsig sigtbl437[1] = {
   { matches_icc_freg_freg,  3, 0, call_550 } /* line 579 */,
};

/* fmovqn */
static const struct insnsig sigtbl438[2] = {
   { matches_icc_freg_freg,  3, 0, call_496 } /* line 524 */,
   { matches_fcc_freg_freg,  3, 0, call_556 } /* line 586 */,
};

/* fmovqne */
static const struct insnsig sigtbl439[2] = {
   { matches_icc_freg_freg,  3, 0, call_499 } /* line 527 */,
   { matches_fcc_freg_freg,  3, 0, call_577 } /* line 607 */,
};

/* fmovqneg */
static const struct insnsig sigtbl440[1] = {
   { matches_icc_freg_freg,  3, 0, call_532 } /* line 560 */,
};

/* fmovqnz */
static const struct insnsig sigtbl441[2] = {
   { matches_icc_freg_freg,  3, 0, call_541 } /* line 570 */,
   { matches_fcc_freg_freg,  3, 0, call_601 } /* line 632 */,
};

/* fmovqo */
static const struct insnsig sigtbl442[1] = {
   { matches_fcc_freg_freg,  3, 0, call_598 } /* line 628 */,
};

/* fmovqpos */
static const struct insnsig sigtbl443[1] = {
   { matches_icc_freg_freg,  3, 0, call_529 } /* line 557 */,
};

/* fmovqu */
static const struct insnsig sigtbl444[1] = {
   { matches_fcc_freg_freg,  3, 0, call_559 } /* line 589 */,
};

/* fmovque */
static const struct insnsig sigtbl445[1] = {
   { matches_fcc_freg_freg,  3, 0, call_583 } /* line 613 */,
};

/* fmovqug */
static const struct insnsig sigtbl446[1] = {
   { matches_fcc_freg_freg,  3, 0, call_565 } /* line 595 */,
};

/* fmovquge */
static const struct insnsig sigtbl447[1] = {
   { matches_fcc_freg_freg,  3, 0, call_589 } /* line 619 */,
};

/* fmovqul */
static const struct insnsig sigtbl448[1] = {
   { matches_fcc_freg_freg,  3, 0, call_571 } /* line 601 */,
};

/* fmovqule */
static const struct insnsig sigtbl449[1] = {
   { matches_fcc_freg_freg,  3, 0, call_595 } /* line 625 */,
};

/* fmovqvc */
static const struct insnsig sigtbl450[1] = {
   { matches_icc_freg_freg,  3, 0, call_535 } /* line 563 */,
};

/* fmovqvs */
static const struct insnsig sigtbl451[1] = {
   { matches_icc_freg_freg,  3, 0, call_538 } /* line 566 */,
};

/* fmovqz */
static const struct insnsig sigtbl452[2] = {
   { matches_icc_freg_freg,  3, 0, call_544 } /* line 573 */,
   { matches_fcc_freg_freg,  3, 0, call_604 } /* line 635 */,
};

/* fmovrde */
static const struct insnsig sigtbl453[1] = {
   { matches_reg_freg_freg,  3, 0, call_624 } /* line 657 */,
};

/* fmovrdg */
static const struct insnsig sigtbl454[1] = {
   { matches_reg_freg_freg,  3, 0, call_618 } /* line 650 */,
};

/* fmovrdgez */
static const struct insnsig sigtbl455[1] = {
   { matches_reg_freg_freg,  3, 0, call_621 } /* line 653 */,
};

/* fmovrdlez */
static const struct insnsig sigtbl456[1] = {
   { matches_reg_freg_freg,  3, 0, call_609 } /* line 641 */,
};

/* fmovrdlz */
static const struct insnsig sigtbl457[1] = {
   { matches_reg_freg_freg,  3, 0, call_612 } /* line 644 */,
};

/* fmovrdne */
static const struct insnsig sigtbl458[1] = {
   { matches_reg_freg_freg,  3, 0, call_627 } /* line 660 */,
};

/* fmovrdnz */
static const struct insnsig sigtbl459[1] = {
   { matches_reg_freg_freg,  3, 0, call_615 } /* line 647 */,
};

/* fmovrdz */
static const struct insnsig sigtbl460[1] = {
   { matches_reg_freg_freg,  3, 0, call_606 } /* line 638 */,
};

/* fmovrqe */
static const struct insnsig sigtbl461[1] = {
   { matches_reg_freg_freg,  3, 0, call_625 } /* line 658 */,
};

/* fmovrqg */
static const struct insnsig sigtbl462[1] = {
   { matches_reg_freg_freg,  3, 0, call_619 } /* line 651 */,
};

/* fmovrqgez */
static const struct insnsig sigtbl463[1] = {
   { matches_reg_freg_freg,  3, 0, call_622 } /* line 654 */,
};

/* fmovrqlez */
static const struct insnsig sigtbl464[1] = {
   { matches_reg_freg_freg,  3, 0, call_610 } /* line 642 */,
};

/* fmovrqlz */
static const struct insnsig sigtbl465[1] = {
   { matches_reg_freg_freg,  3, 0, call_613 } /* line 645 */,
};

/* fmovrqne */
static const struct insnsig sigtbl466[1] = {
   { matches_reg_freg_freg,  3, 0, call_628 } /* line 661 */,
};

/* fmovrqnz */
static const struct insnsig sigtbl467[1] = {
   { matches_reg_freg_freg,  3, 0, call_616 } /* line 648 */,
};

/* fmovrqz */
static const struct insnsig sigtbl468[1] = {
   { matches_reg_freg_freg,  3, 0, call_607 } /* line 639 */,
};

/* fmovrse */
static const struct insnsig sigtbl469[1] = {
   { matches_reg_freg_freg,  3, 0, call_623 } /* line 656 */,
};

/* fmovrsg */
static const struct insnsig sigtbl470[1] = {
   { matches_reg_freg_freg,  3, 0, call_617 } /* line 649 */,
};

/* fmovrsgez */
static const struct insnsig sigtbl471[1] = {
   { matches_reg_freg_freg,  3, 0, call_620 } /* line 652 */,
};

/* fmovrslez */
static const struct insnsig sigtbl472[1] = {
   { matches_reg_freg_freg,  3, 0, call_608 } /* line 640 */,
};

/* fmovrslz */
static const struct insnsig sigtbl473[1] = {
   { matches_reg_freg_freg,  3, 0, call_611 } /* line 643 */,
};

/* fmovrsne */
static const struct insnsig sigtbl474[1] = {
   { matches_reg_freg_freg,  3, 0, call_626 } /* line 659 */,
};

/* fmovrsnz */
static const struct insnsig sigtbl475[1] = {
   { matches_reg_freg_freg,  3, 0, call_614 } /* line 646 */,
};

/* fmovrsz */
static const struct insnsig sigtbl476[1] = {
   { matches_reg_freg_freg,  3, 0, call_605 } /* line 637 */,
};

/* fmovs */
static const struct insnsig sigtbl477[1] = {
   { matches_freg_freg,  2, 0, call_131 } /* line 144 */,
};

/* fmovsa */
static const struct insnsig sigtbl478[2] = {
   { matches_icc_freg_freg,  3, 0, call_491 } /* line 519 */,
   { matches_fcc_freg_freg,  3, 0, call_551 } /* line 581 */,
};

/* fmovscc */
static const struct insnsig sigtbl479[1] = {
   { matches_icc_freg_freg,  3, 0, call_521 } /* line 549 */,
};

/* fmovscs */
static const struct insnsig sigtbl480[1] = {
   { matches_icc_freg_freg,  3, 0, call_524 } /* line 552 */,
};

/* fmovse */
static const struct insnsig sigtbl481[2] = {
   { matches_icc_freg_freg,  3, 0, call_500 } /* line 528 */,
   { matches_fcc_freg_freg,  3, 0, call_578 } /* line 608 */,
};

/* fmovsg */
static const struct insnsig sigtbl482[2] = {
   { matches_icc_freg_freg,  3, 0, call_503 } /* line 531 */,
   { matches_fcc_freg_freg,  3, 0, call_560 } /* line 590 */,
};

/* fmovsge */
static const struct insnsig sigtbl483[2] = {
   { matches_icc_freg_freg,  3, 0, call_509 } /* line 537 */,
   { matches_fcc_freg_freg,  3, 0, call_584 } /* line 614 */,
};

/* fmovsgeu */
static const struct insnsig sigtbl484[1] = {
   { matches_icc_freg_freg,  3, 0, call_545 } /* line 574 */,
};

/* fmovsgu */
static const struct insnsig sigtbl485[1] = {
   { matches_icc_freg_freg,  3, 0, call_515 } /* line 543 */,
};

/* fmovsl */
static const struct insnsig sigtbl486[2] = {
   { matches_icc_freg_freg,  3, 0, call_512 } /* line 540 */,
   { matches_fcc_freg_freg,  3, 0, call_566 } /* line 596 */,
};

/* fmovsle */
static const struct insnsig sigtbl487[2] = {
   { matches_icc_freg_freg,  3, 0, call_506 } /* line 534 */,
   { matches_fcc_freg_freg,  3, 0, call_590 } /* line 620 */,
};

/* fmovsleu */
static const struct insnsig sigtbl488[1] = {
   { matches_icc_freg_freg,  3, 0, call_518 } /* line 546 */,
};

/* fmovslg */
static const struct insnsig sigtbl489[1] = {
   { matches_fcc_freg_freg,  3, 0, call_572 } /* line 602 */,
};

/* fmovslu */
static const struct insnsig sigtbl490[1] = {
   { matches_icc_freg_freg,  3, 0, call_548 } /* line 577 */,
};

/* fmovsn */
static const struct insnsig sigtbl491[2] = {
   { matches_icc_freg_freg,  3, 0, call_494 } /* line 522 */,
   { matches_fcc_freg_freg,  3, 0, call_554 } /* line 584 */,
};

/* fmovsne */
static const struct insnsig sigtbl492[2] = {
   { matches_icc_freg_freg,  3, 0, call_497 } /* line 525 */,
   { matches_fcc_freg_freg,  3, 0, call_575 } /* line 605 */,
};

/* fmovsneg */
static const struct insnsig sigtbl493[1] = {
   { matches_icc_freg_freg,  3, 0, call_530 } /* line 558 */,
};

/* fmovsnz */
static const struct insnsig sigtbl494[2] = {
   { matches_icc_freg_freg,  3, 0, call_539 } /* line 568 */,
   { matches_fcc_freg_freg,  3, 0, call_599 } /* line 630 */,
};

/* fmovso */
static const struct insnsig sigtbl495[1] = {
   { matches_fcc_freg_freg,  3, 0, call_596 } /* line 626 */,
};

/* fmovspos */
static const struct insnsig sigtbl496[1] = {
   { matches_icc_freg_freg,  3, 0, call_527 } /* line 555 */,
};

/* fmovsu */
static const struct insnsig sigtbl497[1] = {
   { matches_fcc_freg_freg,  3, 0, call_557 } /* line 587 */,
};

/* fmovsue */
static const struct insnsig sigtbl498[1] = {
   { matches_fcc_freg_freg,  3, 0, call_581 } /* line 611 */,
};

/* fmovsug */
static const struct insnsig sigtbl499[1] = {
   { matches_fcc_freg_freg,  3, 0, call_563 } /* line 593 */,
};

/* fmovsuge */
static const struct insnsig sigtbl500[1] = {
   { matches_fcc_freg_freg,  3, 0, call_587 } /* line 617 */,
};

/* fmovsul */
static const struct insnsig sigtbl501[1] = {
   { matches_fcc_freg_freg,  3, 0, call_569 } /* line 599 */,
};

/* fmovsule */
static const struct insnsig sigtbl502[1] = {
   { matches_fcc_freg_freg,  3, 0, call_593 } /* line 623 */,
};

/* fmovsvc */
static const struct insnsig sigtbl503[1] = {
   { matches_icc_freg_freg,  3, 0, call_533 } /* line 561 */,
};

/* fmovsvs */
static const struct insnsig sigtbl504[1] = {
   { matches_icc_freg_freg,  3, 0, call_536 } /* line 564 */,
};

/* fmovsz */
static const struct insnsig sigtbl505[2] = {
   { matches_icc_freg_freg,  3, 0, call_542 } /* line 571 */,
   { matches_fcc_freg_freg,  3, 0, call_602 } /* line 633 */,
};

/* fmuld */
static const struct insnsig sigtbl506[1] = {
   { matches_freg_freg_freg,  3, 0, call_144 } /* line 158 */,
};

/* fmulq */
static const struct insnsig sigtbl507[1] = {
   { matches_freg_freg_freg,  3, 0, call_145 } /* line 159 */,
};

/* fmuls */
static const struct insnsig sigtbl508[1] = {
   { matches_freg_freg_freg,  3, 0, call_143 } /* line 157 */,
};

/* fnegd */
static const struct insnsig sigtbl509[1] = {
   { matches_freg_freg,  2, 0, call_135 } /* line 148 */,
};

/* fnegq */
static const struct insnsig sigtbl510[1] = {
   { matches_freg_freg,  2, 0, call_136 } /* line 149 */,
};

/* fnegs */
static const struct insnsig sigtbl511[1] = {
   { matches_freg_freg,  2, 0, call_134 } /* line 147 */,
};

/* fqtod */
static const struct insnsig sigtbl512[1] = {
   { matches_freg_freg,  2, 0, call_130 } /* line 142 */,
};

/* fqtoi */
static const struct insnsig sigtbl513[1] = {
   { matches_freg_freg,  2, 0, call_118 } /* line 130 */,
};

/* fqtos */
static const struct insnsig sigtbl514[1] = {
   { matches_freg_freg,  2, 0, call_129 } /* line 141 */,
};

/* fqtox */
static const struct insnsig sigtbl515[1] = {
   { matches_freg_freg,  2, 0, call_115 } /* line 127 */,
};

/* fsmuld */
static const struct insnsig sigtbl516[1] = {
   { matches_freg_freg_freg,  3, 0, call_146 } /* line 160 */,
};

/* fsqrtd */
static const struct insnsig sigtbl517[1] = {
   { matches_freg_freg,  2, 0, call_141 } /* line 154 */,
};

/* fsqrtq */
static const struct insnsig sigtbl518[1] = {
   { matches_freg_freg,  2, 0, call_142 } /* line 155 */,
};

/* fsqrts */
static const struct insnsig sigtbl519[1] = {
   { matches_freg_freg,  2, 0, call_140 } /* line 153 */,
};

/* fstod */
static const struct insnsig sigtbl520[1] = {
   { matches_freg_freg,  2, 0, call_125 } /* line 137 */,
};

/* fstoi */
static const struct insnsig sigtbl521[1] = {
   { matches_freg_freg,  2, 0, call_116 } /* line 128 */,
};

/* fstoq */
static const struct insnsig sigtbl522[1] = {
   { matches_freg_freg,  2, 0, call_126 } /* line 138 */,
};

/* fstox */
static const struct insnsig sigtbl523[1] = {
   { matches_freg_freg,  2, 0, call_113 } /* line 125 */,
};

/* fsubd */
static const struct insnsig sigtbl524[1] = {
   { matches_freg_freg_freg,  3, 0, call_105 } /* line 115 */,
};

/* fsubq */
static const struct insnsig sigtbl525[1] = {
   { matches_freg_freg_freg,  3, 0, call_106 } /* line 116 */,
};

/* fsubs */
static const struct insnsig sigtbl526[1] = {
   { matches_freg_freg_freg,  3, 0, call_104 } /* line 114 */,
};

/* fxtod */
static const struct insnsig sigtbl527[1] = {
   { matches_freg_freg,  2, 0, call_120 } /* line 132 */,
};

/* fxtoq */
static const struct insnsig sigtbl528[1] = {
   { matches_freg_freg,  2, 0, call_121 } /* line 133 */,
};

/* fxtos */
static const struct insnsig sigtbl529[1] = {
   { matches_freg_freg,  2, 0, call_119 } /* line 131 */,
};

/* illtrap */
static const struct insnsig sigtbl530[1] = {
   { matches_u22num,  1, 0, call_895 } /* line 957 */,
};

/* impl1 */
static const struct insnsig sigtbl531[1] = {
   { matches_u5num_u19num,  2, 0, call_941 } /* line 1010 */,
};

/* impl2 */
static const struct insnsig sigtbl532[1] = {
   { matches_u5num_u19num,  2, 0, call_942 } /* line 1011 */,
};

/* inc */
static const struct insnsig sigtbl533[2] = {
   { matches_reg,    1, 0, call_979 } /* line 1055 */,
   { matches_i13num_reg,  2, 0, call_980 } /* line 1056 */,
};

/* inccc */
static const struct insnsig sigtbl534[2] = {
   { matches_reg,    1, 0, call_981 } /* line 1057 */,
   { matches_i13num_reg,  2, 0, call_982 } /* line 1058 */,
};

/* iprefetch */
static const struct insnsig sigtbl535[1] = {
   { matches_symbol,  1, 0, call_963 } /* line 1037 */,
};

/* jmp */
static const struct insnsig sigtbl536[2] = {
   { matches_addr_rr,  1, 0, call_953 } /* line 1027 */,
   { matches_addr_ri,  1, 0, call_954 } /* line 1028 */,
};

/* jmpl */
static const struct insnsig sigtbl537[2] = {
   { matches_addr_rr_reg,  2, 0, call_891 } /* line 951 */,
   { matches_addr_ri_reg,  2, 0, call_892 } /* line 952 */,
};

/* ld */
static const struct insnsig sigtbl538[9] = {
   { matches_braddr_rr_freg,  2, 0, call_742 } /* line 786 */,
   { matches_braddr_ri_freg,  2, 0, call_743 } /* line 787 */,
   { matches_braddr_rx_freg,  2, 0, call_744 } /* line 788 */,
   { matches_braddr_rr_fsr,  2, 0, call_751 } /* line 795 */,
   { matches_braddr_ri_fsr,  2, 0, call_752 } /* line 796 */,
   { matches_braddr_rx_fsr,  2, 0, call_753 } /* line 797 */,
   { matches_braddr_rr_reg,  2, 0, call_787 } /* line 835 */,
   { matches_braddr_ri_reg,  2, 0, call_788 } /* line 836 */,
   { matches_braddr_rx_reg,  2, 0, call_789 } /* line 837 */,
};

/* lda */
static const struct insnsig sigtbl539[4] = {
   { matches_braddr_rr_immasi_freg,  2, 0, call_757 } /* line 802 */,
   { matches_braddr_ri_asi_freg,  2, 0, call_758 } /* line 803 */,
   { matches_braddr_rr_immasi_reg,  2, 0, call_806 } /* line 857 */,
   { matches_braddr_ri_asi_reg,  2, 0, call_807 } /* line 858 */,
};

/* ldd */
static const struct insnsig sigtbl540[6] = {
   { matches_braddr_rr_freg,  2, 0, call_745 } /* line 789 */,
   { matches_braddr_ri_freg,  2, 0, call_746 } /* line 790 */,
   { matches_braddr_rx_freg,  2, 0, call_747 } /* line 791 */,
   { matches_braddr_rr_reg,  2, 0, call_784 } /* line 831 */,
   { matches_braddr_ri_reg,  2, 0, call_785 } /* line 832 */,
   { matches_braddr_rx_reg,  2, 0, call_786 } /* line 833 */,
};

/* ldda */
static const struct insnsig sigtbl541[4] = {
   { matches_braddr_rr_immasi_freg,  2, 0, call_759 } /* line 804 */,
   { matches_braddr_ri_asi_freg,  2, 0, call_760 } /* line 805 */,
   { matches_braddr_rr_immasi_reg,  2, 0, call_804 } /* line 854 */,
   { matches_braddr_ri_asi_reg,  2, 0, call_805 } /* line 855 */,
};

/* ldn */
static const struct insnsig sigtbl542[2] = {
   { matches_braddr_rr_reg,  2, 0, call_1010 } /* line 1093 */,
   { matches_braddr_ri_reg,  2, 0, call_1011 } /* line 1094 */,
};

/* ldna */
static const struct insnsig sigtbl543[2] = {
   { matches_braddr_rr_immasi_reg,  2, 0, call_1012 } /* line 1095 */,
   { matches_braddr_ri_asi_reg,  2, 0, call_1013 } /* line 1096 */,
};

/* ldq */
static const struct insnsig sigtbl544[3] = {
   { matches_braddr_rr_freg,  2, 0, call_748 } /* line 792 */,
   { matches_braddr_ri_freg,  2, 0, call_749 } /* line 793 */,
   { matches_braddr_rx_freg,  2, 0, call_750 } /* line 794 */,
};

/* ldqa */
static const struct insnsig sigtbl545[2] = {
   { matches_braddr_rr_immasi_freg,  2, 0, call_761 } /* line 806 */,
   { matches_braddr_ri_asi_freg,  2, 0, call_762 } /* line 807 */,
};

/* ldsb */
static const struct insnsig sigtbl546[3] = {
   { matches_braddr_rr_reg,  2, 0, call_763 } /* line 809 */,
   { matches_braddr_ri_reg,  2, 0, call_764 } /* line 810 */,
   { matches_braddr_rx_reg,  2, 0, call_765 } /* line 811 */,
};

/* ldsba */
static const struct insnsig sigtbl547[2] = {
   { matches_braddr_rr_immasi_reg,  2, 0, call_790 } /* line 839 */,
   { matches_braddr_ri_asi_reg,  2, 0, call_791 } /* line 840 */,
};

/* ldsh */
static const struct insnsig sigtbl548[3] = {
   { matches_braddr_rr_reg,  2, 0, call_766 } /* line 812 */,
   { matches_braddr_ri_reg,  2, 0, call_767 } /* line 813 */,
   { matches_braddr_rx_reg,  2, 0, call_768 } /* line 814 */,
};

/* ldsha */
static const struct insnsig sigtbl549[2] = {
   { matches_braddr_rr_immasi_reg,  2, 0, call_792 } /* line 841 */,
   { matches_braddr_ri_asi_reg,  2, 0, call_793 } /* line 842 */,
};

/* ldstub */
static const struct insnsig sigtbl550[3] = {
   { matches_braddr_rr_reg,  2, 0, call_733 } /* line 776 */,
   { matches_braddr_ri_reg,  2, 0, call_734 } /* line 777 */,
   { matches_braddr_rx_reg,  2, 0, call_735 } /* line 778 */,
};

/* ldstuba */
static const struct insnsig sigtbl551[2] = {
   { matches_braddr_rr_immasi_reg,  2, 0, call_736 } /* line 779 */,
   { matches_braddr_ri_asi_reg,  2, 0, call_737 } /* line 780 */,
};

/* ldsw */
static const struct insnsig sigtbl552[3] = {
   { matches_braddr_rr_reg,  2, 0, call_769 } /* line 815 */,
   { matches_braddr_ri_reg,  2, 0, call_770 } /* line 816 */,
   { matches_braddr_rx_reg,  2, 0, call_771 } /* line 817 */,
};

/* ldswa */
static const struct insnsig sigtbl553[2] = {
   { matches_braddr_rr_immasi_reg,  2, 0, call_794 } /* line 843 */,
   { matches_braddr_ri_asi_reg,  2, 0, call_795 } /* line 844 */,
};

/* ldub */
static const struct insnsig sigtbl554[3] = {
   { matches_braddr_rr_reg,  2, 0, call_772 } /* line 818 */,
   { matches_braddr_ri_reg,  2, 0, call_773 } /* line 819 */,
   { matches_braddr_rx_reg,  2, 0, call_774 } /* line 820 */,
};

/* lduba */
static const struct insnsig sigtbl555[2] = {
   { matches_braddr_rr_immasi_reg,  2, 0, call_796 } /* line 845 */,
   { matches_braddr_ri_asi_reg,  2, 0, call_797 } /* line 846 */,
};

/* lduh */
static const struct insnsig sigtbl556[3] = {
   { matches_braddr_rr_reg,  2, 0, call_775 } /* line 821 */,
   { matches_braddr_ri_reg,  2, 0, call_776 } /* line 822 */,
   { matches_braddr_rx_reg,  2, 0, call_777 } /* line 823 */,
};

/* lduha */
static const struct insnsig sigtbl557[2] = {
   { matches_braddr_rr_immasi_reg,  2, 0, call_798 } /* line 847 */,
   { matches_braddr_ri_asi_reg,  2, 0, call_799 } /* line 848 */,
};

/* lduw */
static const struct insnsig sigtbl558[3] = {
   { matches_braddr_rr_reg,  2, 0, call_778 } /* line 824 */,
   { matches_braddr_ri_reg,  2, 0, call_779 } /* line 825 */,
   { matches_braddr_rx_reg,  2, 0, call_780 } /* line 826 */,
};

/* lduwa */
static const struct insnsig sigtbl559[2] = {
   { matches_braddr_rr_immasi_reg,  2, 0, call_800 } /* line 849 */,
   { matches_braddr_ri_asi_reg,  2, 0, call_801 } /* line 850 */,
};

/* ldx */
static const struct insnsig sigtbl560[6] = {
   { matches_braddr_rr_fsr,  2, 0, call_754 } /* line 798 */,
   { matches_braddr_ri_fsr,  2, 0, call_755 } /* line 799 */,
   { matches_braddr_rx_fsr,  2, 0, call_756 } /* line 800 */,
   { matches_braddr_rr_reg,  2, 0, call_781 } /* line 827 */,
   { matches_braddr_ri_reg,  2, 0, call_782 } /* line 828 */,
   { matches_braddr_rx_reg,  2, 0, call_783 } /* line 829 */,
};

/* ldxa */
static const struct insnsig sigtbl561[2] = {
   { matches_braddr_rr_immasi_reg,  2, 0, call_802 } /* line 851 */,
   { matches_braddr_ri_asi_reg,  2, 0, call_803 } /* line 852 */,
};

/* membar */
static const struct insnsig sigtbl562[1] = {
   { matches_membarmask,  1, 0, call_721 } /* line 761 */,
};

/* mov */
static const struct insnsig sigtbl563[4] = {
   { matches_reg_reg,  2, 0, call_1006 } /* line 1086 */,
   { matches_i13num_reg,  2, 0, call_1007 } /* line 1087 */,
   { matches_asr_reg,  2, 0, call_1008 } /* line 1088 */,
   { matches_reg_asr,  2, 0, call_1009 } /* line 1089 */,
};

/* mova */
static const struct insnsig sigtbl564[4] = {
   { matches_icc_reg_reg,  3, 0, call_629 } /* line 663 */,
   { matches_icc_i11num_reg,  3, 0, call_630 } /* line 664 */,
   { matches_fcc_reg_reg,  3, 0, call_669 } /* line 705 */,
   { matches_fcc_i11num_reg,  3, 0, call_670 } /* line 706 */,
};

/* movcc */
static const struct insnsig sigtbl565[2] = {
   { matches_icc_reg_reg,  3, 0, call_649 } /* line 683 */,
   { matches_icc_i11num_reg,  3, 0, call_650 } /* line 684 */,
};

/* movcs */
static const struct insnsig sigtbl566[2] = {
   { matches_icc_reg_reg,  3, 0, call_651 } /* line 685 */,
   { matches_icc_i11num_reg,  3, 0, call_652 } /* line 686 */,
};

/* move */
static const struct insnsig sigtbl567[4] = {
   { matches_icc_reg_reg,  3, 0, call_635 } /* line 669 */,
   { matches_icc_i11num_reg,  3, 0, call_636 } /* line 670 */,
   { matches_fcc_reg_reg,  3, 0, call_687 } /* line 723 */,
   { matches_fcc_i11num_reg,  3, 0, call_688 } /* line 724 */,
};

/* movg */
static const struct insnsig sigtbl568[4] = {
   { matches_icc_reg_reg,  3, 0, call_637 } /* line 671 */,
   { matches_icc_i11num_reg,  3, 0, call_638 } /* line 672 */,
   { matches_fcc_reg_reg,  3, 0, call_675 } /* line 711 */,
   { matches_fcc_i11num_reg,  3, 0, call_676 } /* line 712 */,
};

/* movge */
static const struct insnsig sigtbl569[4] = {
   { matches_icc_reg_reg,  3, 0, call_641 } /* line 675 */,
   { matches_icc_i11num_reg,  3, 0, call_642 } /* line 676 */,
   { matches_fcc_reg_reg,  3, 0, call_691 } /* line 727 */,
   { matches_fcc_i11num_reg,  3, 0, call_692 } /* line 728 */,
};

/* movgeu */
static const struct insnsig sigtbl570[2] = {
   { matches_icc_reg_reg,  3, 0, call_665 } /* line 700 */,
   { matches_icc_i11num_reg,  3, 0, call_666 } /* line 701 */,
};

/* movgu */
static const struct insnsig sigtbl571[2] = {
   { matches_icc_reg_reg,  3, 0, call_645 } /* line 679 */,
   { matches_icc_i11num_reg,  3, 0, call_646 } /* line 680 */,
};

/* movl */
static const struct insnsig sigtbl572[4] = {
   { matches_icc_reg_reg,  3, 0, call_643 } /* line 677 */,
   { matches_icc_i11num_reg,  3, 0, call_644 } /* line 678 */,
   { matches_fcc_reg_reg,  3, 0, call_679 } /* line 715 */,
   { matches_fcc_i11num_reg,  3, 0, call_680 } /* line 716 */,
};

/* movle */
static const struct insnsig sigtbl573[4] = {
   { matches_icc_reg_reg,  3, 0, call_639 } /* line 673 */,
   { matches_icc_i11num_reg,  3, 0, call_640 } /* line 674 */,
   { matches_fcc_reg_reg,  3, 0, call_695 } /* line 731 */,
   { matches_fcc_i11num_reg,  3, 0, call_696 } /* line 732 */,
};

/* movleu */
static const struct insnsig sigtbl574[2] = {
   { matches_icc_reg_reg,  3, 0, call_647 } /* line 681 */,
   { matches_icc_i11num_reg,  3, 0, call_648 } /* line 682 */,
};

/* movlg */
static const struct insnsig sigtbl575[2] = {
   { matches_fcc_reg_reg,  3, 0, call_683 } /* line 719 */,
   { matches_fcc_i11num_reg,  3, 0, call_684 } /* line 720 */,
};

/* movlu */
static const struct insnsig sigtbl576[2] = {
   { matches_icc_reg_reg,  3, 0, call_667 } /* line 702 */,
   { matches_icc_i11num_reg,  3, 0, call_668 } /* line 703 */,
};

/* movn */
static const struct insnsig sigtbl577[4] = {
   { matches_icc_reg_reg,  3, 0, call_631 } /* line 665 */,
   { matches_icc_i11num_reg,  3, 0, call_632 } /* line 666 */,
   { matches_fcc_reg_reg,  3, 0, call_671 } /* line 707 */,
   { matches_fcc_i11num_reg,  3, 0, call_672 } /* line 708 */,
};

/* movne */
static const struct insnsig sigtbl578[4] = {
   { matches_icc_reg_reg,  3, 0, call_633 } /* line 667 */,
   { matches_icc_i11num_reg,  3, 0, call_634 } /* line 668 */,
   { matches_fcc_reg_reg,  3, 0, call_685 } /* line 721 */,
   { matches_fcc_i11num_reg,  3, 0, call_686 } /* line 722 */,
};

/* movneg */
static const struct insnsig sigtbl579[2] = {
   { matches_icc_reg_reg,  3, 0, call_655 } /* line 689 */,
   { matches_icc_i11num_reg,  3, 0, call_656 } /* line 690 */,
};

/* movnz */
static const struct insnsig sigtbl580[4] = {
   { matches_icc_reg_reg,  3, 0, call_661 } /* line 696 */,
   { matches_icc_i11num_reg,  3, 0, call_662 } /* line 697 */,
   { matches_fcc_reg_reg,  3, 0, call_701 } /* line 738 */,
   { matches_fcc_i11num_reg,  3, 0, call_702 } /* line 739 */,
};

/* movo */
static const struct insnsig sigtbl581[2] = {
   { matches_fcc_reg_reg,  3, 0, call_699 } /* line 735 */,
   { matches_fcc_i11num_reg,  3, 0, call_700 } /* line 736 */,
};

/* movpos */
static const struct insnsig sigtbl582[2] = {
   { matches_icc_reg_reg,  3, 0, call_653 } /* line 687 */,
   { matches_icc_i11num_reg,  3, 0, call_654 } /* line 688 */,
};

/* movre */
static const struct insnsig sigtbl583[2] = {
   { matches_reg_reg_reg,  3, 0, call_717 } /* line 756 */,
   { matches_reg_i10num_reg,  3, 0, call_718 } /* line 757 */,
};

/* movrgez */
static const struct insnsig sigtbl584[2] = {
   { matches_reg_reg_reg,  3, 0, call_715 } /* line 753 */,
   { matches_reg_i10num_reg,  3, 0, call_716 } /* line 754 */,
};

/* movrgz */
static const struct insnsig sigtbl585[2] = {
   { matches_reg_reg_reg,  3, 0, call_713 } /* line 751 */,
   { matches_reg_i10num_reg,  3, 0, call_714 } /* line 752 */,
};

/* movrlez */
static const struct insnsig sigtbl586[2] = {
   { matches_reg_reg_reg,  3, 0, call_707 } /* line 745 */,
   { matches_reg_i10num_reg,  3, 0, call_708 } /* line 746 */,
};

/* movrlz */
static const struct insnsig sigtbl587[2] = {
   { matches_reg_reg_reg,  3, 0, call_709 } /* line 747 */,
   { matches_reg_i10num_reg,  3, 0, call_710 } /* line 748 */,
};

/* movrne */
static const struct insnsig sigtbl588[2] = {
   { matches_reg_reg_reg,  3, 0, call_719 } /* line 758 */,
   { matches_reg_i10num_reg,  3, 0, call_720 } /* line 759 */,
};

/* movrnz */
static const struct insnsig sigtbl589[2] = {
   { matches_reg_reg_reg,  3, 0, call_711 } /* line 749 */,
   { matches_reg_i10num_reg,  3, 0, call_712 } /* line 750 */,
};

/* movrz */
static const struct insnsig sigtbl590[2] = {
   { matches_reg_reg_reg,  3, 0, call_705 } /* line 743 */,
   { matches_reg_i10num_reg,  3, 0, call_706 } /* line 744 */,
};

/* movu */
static const struct insnsig sigtbl591[2] = {
   { matches_fcc_reg_reg,  3, 0, call_673 } /* line 709 */,
   { matches_fcc_i11num_reg,  3, 0, call_674 } /* line 710 */,
};

/* movue */
static const struct insnsig sigtbl592[2] = {
   { matches_fcc_reg_reg,  3, 0, call_689 } /* line 725 */,
   { matches_fcc_i11num_reg,  3, 0, call_690 } /* line 726 */,
};

/* movug */
static const struct insnsig sigtbl593[2] = {
   { matches_fcc_reg_reg,  3, 0, call_677 } /* line 713 */,
   { matches_fcc_i11num_reg,  3, 0, call_678 } /* line 714 */,
};

/* movuge */
static const struct insnsig sigtbl594[2] = {
   { matches_fcc_reg_reg,  3, 0, call_693 } /* line 729 */,
   { matches_fcc_i11num_reg,  3, 0, call_694 } /* line 730 */,
};

/* movul */
static const struct insnsig sigtbl595[2] = {
   { matches_fcc_reg_reg,  3, 0, call_681 } /* line 717 */,
   { matches_fcc_i11num_reg,  3, 0, call_682 } /* line 718 */,
};

/* movule */
static const struct insnsig sigtbl596[2] = {
   { matches_fcc_reg_reg,  3, 0, call_697 } /* line 733 */,
   { matches_fcc_i11num_reg,  3, 0, call_698 } /* line 734 */,
};

/* movvc */
static const struct insnsig sigtbl597[2] = {
   { matches_icc_reg_reg,  3, 0, call_657 } /* line 691 */,
   { matches_icc_i11num_reg,  3, 0, call_658 } /* line 692 */,
};

/* movvs */
static const struct insnsig sigtbl598[2] = {
   { matches_icc_reg_reg,  3, 0, call_659 } /* line 693 */,
   { matches_icc_i11num_reg,  3, 0, call_660 } /* line 694 */,
};

/* movz */
static const struct insnsig sigtbl599[4] = {
   { matches_icc_reg_reg,  3, 0, call_663 } /* line 698 */,
   { matches_icc_i11num_reg,  3, 0, call_664 } /* line 699 */,
   { matches_fcc_reg_reg,  3, 0, call_703 } /* line 740 */,
   { matches_fcc_i11num_reg,  3, 0, call_704 } /* line 741 */,
};

/* mulscc */
static const struct insnsig sigtbl600[2] = {
   { matches_reg_reg_reg,  3, 0, call_85 } /* line  92 */,
   { matches_reg_i13num_reg,  3, 0, call_86 } /* line  93 */,
};

/* mulx */
static const struct insnsig sigtbl601[2] = {
   { matches_reg_reg_reg,  3, 0, call_95 } /* line 104 */,
   { matches_reg_i13num_reg,  3, 0, call_96 } /* line 105 */,
};

/* neg */
static const struct insnsig sigtbl602[2] = {
   { matches_reg_reg,  2, 0, call_973 } /* line 1047 */,
   { matches_reg,    1, 0, call_974 } /* line 1048 */,
};

/* nop */
static const struct insnsig sigtbl603[1] = {
   { NULL,           0, 0, call_937 } /* line 1002 */,
};

/* not */
static const struct insnsig sigtbl604[2] = {
   { matches_reg_reg,  2, 0, call_971 } /* line 1045 */,
   { matches_reg,    1, 0, call_972 } /* line 1046 */,
};

/* or */
static const struct insnsig sigtbl605[3] = {
   { matches_reg_reg_reg,  3, 0, call_26 } /* line  28 */,
   { matches_reg_i13num_reg,  3, 0, call_27 } /* line  29 */,
   { matches_reg_expr_reg,  3, 0, call_28 } /* line  30 */,
};

/* orcc */
static const struct insnsig sigtbl606[2] = {
   { matches_reg_reg_reg,  3, 0, call_29 } /* line  31 */,
   { matches_reg_i13num_reg,  3, 0, call_30 } /* line  32 */,
};

/* orn */
static const struct insnsig sigtbl607[2] = {
   { matches_reg_reg_reg,  3, 0, call_31 } /* line  33 */,
   { matches_reg_i13num_reg,  3, 0, call_32 } /* line  34 */,
};

/* orncc */
static const struct insnsig sigtbl608[2] = {
   { matches_reg_reg_reg,  3, 0, call_33 } /* line  35 */,
   { matches_reg_i13num_reg,  3, 0, call_34 } /* line  36 */,
};

/* popc */
static const struct insnsig sigtbl609[2] = {
   { matches_reg_reg,  2, 0, call_43 } /* line  45 */,
   { matches_i13num_reg,  2, 0, call_44 } /* line  46 */,
};

/* prefetch */
static const struct insnsig sigtbl610[2] = {
   { matches_braddr_rr_u5num,  2, 0, call_725 } /* line 767 */,
   { matches_braddr_ri_u5num,  2, 0, call_726 } /* line 768 */,
};

/* prefetcha */
static const struct insnsig sigtbl611[2] = {
   { matches_braddr_rr_immasi_u5num,  2, 0, call_727 } /* line 769 */,
   { matches_braddr_ri_asi_u5num,  2, 0, call_728 } /* line 770 */,
};

/* rd */
static const struct insnsig sigtbl612[1] = {
   { matches_asr_reg,  2, 0, call_938 } /* line 1004 */,
};

/* rdpr */
static const struct insnsig sigtbl613[1] = {
   { matches_pr_reg,  2, 0, call_943 } /* line 1013 */,
};

/* restore */
static const struct insnsig sigtbl614[3] = {
   { matches_reg_reg_reg,  3, 0, call_47 } /* line  49 */,
   { matches_reg_i13num_reg,  3, 0, call_48 } /* line  50 */,
   { NULL,           0, 0, call_962 } /* line 1036 */,
};

/* restored */
static const struct insnsig sigtbl615[1] = {
   { NULL,           0, 0, call_950 } /* line 1020 */,
};

/* ret */
static const struct insnsig sigtbl616[1] = {
   { NULL,           0, 0, call_959 } /* line 1033 */,
};

/* retl */
static const struct insnsig sigtbl617[1] = {
   { NULL,           0, 0, call_960 } /* line 1034 */,
};

/* retry */
static const struct insnsig sigtbl618[1] = {
   { NULL,           0, 0, call_947 } /* line 1017 */,
};

/* return */
static const struct insnsig sigtbl619[2] = {
   { matches_addr_rr,  1, 0, call_893 } /* line 953 */,
   { matches_addr_ri,  1, 0, call_894 } /* line 954 */,
};

/* save */
static const struct insnsig sigtbl620[3] = {
   { matches_reg_reg_reg,  3, 0, call_45 } /* line  47 */,
   { matches_reg_i13num_reg,  3, 0, call_46 } /* line  48 */,
   { NULL,           0, 0, call_961 } /* line 1035 */,
};

/* saved */
static const struct insnsig sigtbl621[1] = {
   { NULL,           0, 0, call_949 } /* line 1019 */,
};

/* sdiv */
static const struct insnsig sigtbl622[2] = {
   { matches_reg_reg_reg,  3, 0, call_87 } /* line  94 */,
   { matches_reg_i13num_reg,  3, 0, call_88 } /* line  95 */,
};

/* sdivcc */
static const struct insnsig sigtbl623[2] = {
   { matches_reg_reg_reg,  3, 0, call_91 } /* line  98 */,
   { matches_reg_i13num_reg,  3, 0, call_92 } /* line  99 */,
};

/* sdivx */
static const struct insnsig sigtbl624[2] = {
   { matches_reg_reg_reg,  3, 0, call_97 } /* line 106 */,
   { matches_reg_i13num_reg,  3, 0, call_98 } /* line 107 */,
};

/* set */
static const struct insnsig sigtbl625[1] = {
   { matches_u32num_reg,  2, 0, call_966 } /* line 1040 */,
};

/* sethi */
static const struct insnsig sigtbl626[2] = {
   { matches_u32num_reg,  2, 0, call_0 } /* line   1 */,
   { matches_expr_reg,  2, 0, call_1 } /* line   2 */,
};

/* setsw */
static const struct insnsig sigtbl627[1] = {
   { matches_i32num_reg,  2, 0, call_967 } /* line 1041 */,
};

/* setuw */
static const struct insnsig sigtbl628[1] = {
   { matches_u32num_reg,  2, 0, call_965 } /* line 1039 */,
};

/* setx */
static const struct insnsig sigtbl629[1] = {
   { matches_i64num_reg_reg,  3, 0, call_968 } /* line 1042 */,
};

/* signx */
static const struct insnsig sigtbl630[2] = {
   { matches_reg_reg,  2, 0, call_969 } /* line 1043 */,
   { matches_reg,    1, 0, call_970 } /* line 1044 */,
};

/* sir */
static const struct insnsig sigtbl631[1] = {
   { matches_i13num,  1, 0, call_896 } /* line 958 */,
};

/* sll */
static const struct insnsig sigtbl632[2] = {
   { matches_reg_reg_reg,  3, 0, call_65 } /* line  70 */,
   { matches_reg_u5num_reg,  3, 0, call_66 } /* line  71 */,
};

/* slln */
static const struct insnsig sigtbl633[2] = {
   { matches_reg_reg_reg,  3, 0, call_1018 } /* line 1101 */,
   { matches_reg_u6num_reg,  3, 0, call_1019 } /* line 1102 */,
};

/* sllx */
static const struct insnsig sigtbl634[2] = {
   { matches_reg_reg_reg,  3, 0, call_71 } /* line  76 */,
   { matches_reg_u6num_reg,  3, 0, call_72 } /* line  77 */,
};

/* smul */
static const struct insnsig sigtbl635[2] = {
   { matches_reg_reg_reg,  3, 0, call_79 } /* line  86 */,
   { matches_reg_i13num_reg,  3, 0, call_80 } /* line  87 */,
};

/* smulcc */
static const struct insnsig sigtbl636[2] = {
   { matches_reg_reg_reg,  3, 0, call_83 } /* line  90 */,
   { matches_reg_i13num_reg,  3, 0, call_84 } /* line  91 */,
};

/* sra */
static const struct insnsig sigtbl637[2] = {
   { matches_reg_reg_reg,  3, 0, call_69 } /* line  74 */,
   { matches_reg_u5num_reg,  3, 0, call_70 } /* line  75 */,
};

/* sran */
static const struct insnsig sigtbl638[2] = {
   { matches_reg_reg_reg,  3, 0, call_1022 } /* line 1105 */,
   { matches_reg_u6num_reg,  3, 0, call_1023 } /* line 1106 */,
};

/* srax */
static const struct insnsig sigtbl639[2] = {
   { matches_reg_reg_reg,  3, 0, call_75 } /* line  80 */,
   { matches_reg_u6num_reg,  3, 0, call_76 } /* line  81 */,
};

/* srl */
static const struct insnsig sigtbl640[2] = {
   { matches_reg_reg_reg,  3, 0, call_67 } /* line  72 */,
   { matches_reg_u5num_reg,  3, 0, call_68 } /* line  73 */,
};

/* srln */
static const struct insnsig sigtbl641[2] = {
   { matches_reg_reg_reg,  3, 0, call_1020 } /* line 1103 */,
   { matches_reg_u6num_reg,  3, 0, call_1021 } /* line 1104 */,
};

/* srlx */
static const struct insnsig sigtbl642[2] = {
   { matches_reg_reg_reg,  3, 0, call_73 } /* line  78 */,
   { matches_reg_u6num_reg,  3, 0, call_74 } /* line  79 */,
};

/* st */
static const struct insnsig sigtbl643[9] = {
   { matches_freg_braddr_rr,  2, 0, call_808 } /* line 860 */,
   { matches_freg_braddr_ri,  2, 0, call_809 } /* line 861 */,
   { matches_freg_braddr_rx,  2, 0, call_810 } /* line 862 */,
   { matches_fsr_braddr_rr,  2, 0, call_817 } /* line 869 */,
   { matches_fsr_braddr_ri,  2, 0, call_818 } /* line 870 */,
   { matches_fsr_braddr_rx,  2, 0, call_819 } /* line 871 */,
   { matches_reg_braddr_rr,  2, 0, call_856 } /* line 912 */,
   { matches_reg_braddr_ri,  2, 0, call_857 } /* line 913 */,
   { matches_reg_braddr_rx,  2, 0, call_858 } /* line 914 */,
};

/* sta */
static const struct insnsig sigtbl644[4] = {
   { matches_freg_braddr_rr_immasi,  2, 0, call_823 } /* line 876 */,
   { matches_freg_braddr_ri_asi,  2, 0, call_824 } /* line 877 */,
   { matches_reg_braddr_rr_immasi,  2, 0, call_887 } /* line 946 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_888 } /* line 947 */,
};

/* stb */
static const struct insnsig sigtbl645[3] = {
   { matches_reg_braddr_rr,  2, 0, call_829 } /* line 883 */,
   { matches_reg_braddr_ri,  2, 0, call_830 } /* line 884 */,
   { matches_reg_braddr_rx,  2, 0, call_831 } /* line 885 */,
};

/* stba */
static const struct insnsig sigtbl646[2] = {
   { matches_reg_braddr_rr_immasi,  2, 0, call_865 } /* line 922 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_866 } /* line 923 */,
};

/* stbar */
static const struct insnsig sigtbl647[1] = {
   { NULL,           0, 0, call_722 } /* line 762 */,
};

/* std */
static const struct insnsig sigtbl648[6] = {
   { matches_freg_braddr_rr,  2, 0, call_811 } /* line 863 */,
   { matches_freg_braddr_ri,  2, 0, call_812 } /* line 864 */,
   { matches_freg_braddr_rx,  2, 0, call_813 } /* line 865 */,
   { matches_reg_braddr_rr,  2, 0, call_841 } /* line 896 */,
   { matches_reg_braddr_ri,  2, 0, call_842 } /* line 897 */,
   { matches_reg_braddr_rx,  2, 0, call_843 } /* line 898 */,
};

/* stda */
static const struct insnsig sigtbl649[4] = {
   { matches_freg_braddr_rr_immasi,  2, 0, call_825 } /* line 878 */,
   { matches_freg_braddr_ri_asi,  2, 0, call_826 } /* line 879 */,
   { matches_reg_braddr_rr_immasi,  2, 0, call_873 } /* line 931 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_874 } /* line 932 */,
};

/* sth */
static const struct insnsig sigtbl650[3] = {
   { matches_reg_braddr_rr,  2, 0, call_832 } /* line 886 */,
   { matches_reg_braddr_ri,  2, 0, call_833 } /* line 887 */,
   { matches_reg_braddr_rx,  2, 0, call_834 } /* line 888 */,
};

/* stha */
static const struct insnsig sigtbl651[2] = {
   { matches_reg_braddr_rr_immasi,  2, 0, call_867 } /* line 924 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_868 } /* line 925 */,
};

/* stn */
static const struct insnsig sigtbl652[2] = {
   { matches_reg_braddr_rr,  2, 0, call_1014 } /* line 1097 */,
   { matches_reg_braddr_ri,  2, 0, call_1015 } /* line 1098 */,
};

/* stna */
static const struct insnsig sigtbl653[2] = {
   { matches_reg_braddr_rr_immasi,  2, 0, call_1016 } /* line 1099 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_1017 } /* line 1100 */,
};

/* stq */
static const struct insnsig sigtbl654[3] = {
   { matches_freg_braddr_rr,  2, 0, call_814 } /* line 866 */,
   { matches_freg_braddr_ri,  2, 0, call_815 } /* line 867 */,
   { matches_freg_braddr_rx,  2, 0, call_816 } /* line 868 */,
};

/* stqa */
static const struct insnsig sigtbl655[2] = {
   { matches_freg_braddr_rr_immasi,  2, 0, call_827 } /* line 880 */,
   { matches_freg_braddr_ri_asi,  2, 0, call_828 } /* line 881 */,
};

/* stsb */
static const struct insnsig sigtbl656[3] = {
   { matches_reg_braddr_rr,  2, 0, call_844 } /* line 900 */,
   { matches_reg_braddr_ri,  2, 0, call_845 } /* line 901 */,
   { matches_reg_braddr_rx,  2, 0, call_846 } /* line 902 */,
};

/* stsba */
static const struct insnsig sigtbl657[2] = {
   { matches_reg_braddr_rr_immasi,  2, 0, call_875 } /* line 934 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_876 } /* line 935 */,
};

/* stsh */
static const struct insnsig sigtbl658[3] = {
   { matches_reg_braddr_rr,  2, 0, call_850 } /* line 906 */,
   { matches_reg_braddr_ri,  2, 0, call_851 } /* line 907 */,
   { matches_reg_braddr_rx,  2, 0, call_852 } /* line 908 */,
};

/* stsha */
static const struct insnsig sigtbl659[2] = {
   { matches_reg_braddr_rr_immasi,  2, 0, call_879 } /* line 938 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_880 } /* line 939 */,
};

/* stsw */
static const struct insnsig sigtbl660[3] = {
   { matches_reg_braddr_rr,  2, 0, call_859 } /* line 915 */,
   { matches_reg_braddr_ri,  2, 0, call_860 } /* line 916 */,
   { matches_reg_braddr_rx,  2, 0, call_861 } /* line 917 */,
};

/* stswa */
static const struct insnsig sigtbl661[2] = {
   { matches_reg_braddr_rr_immasi,  2, 0, call_883 } /* line 942 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_884 } /* line 943 */,
};

/* stub */
static const struct insnsig sigtbl662[3] = {
   { matches_reg_braddr_rr,  2, 0, call_847 } /* line 903 */,
   { matches_reg_braddr_ri,  2, 0, call_848 } /* line 904 */,
   { matches_reg_braddr_rx,  2, 0, call_849 } /* line 905 */,
};

/* stuba */
static const struct insnsig sigtbl663[2] = {
   { matches_reg_braddr_rr_immasi,  2, 0, call_877 } /* line 936 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_878 } /* line 937 */,
};

/* stuh */
static const struct insnsig sigtbl664[3] = {
   { matches_reg_braddr_rr,  2, 0, call_853 } /* line 909 */,
   { matches_reg_braddr_ri,  2, 0, call_854 } /* line 910 */,
   { matches_reg_braddr_rx,  2, 0, call_855 } /* line 911 */,
};

/* stuha */
static const struct insnsig sigtbl665[2] = {
   { matches_reg_braddr_rr_immasi,  2, 0, call_881 } /* line 940 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_882 } /* line 941 */,
};

/* stuw */
static const struct insnsig sigtbl666[3] = {
   { matches_reg_braddr_rr,  2, 0, call_862 } /* line 918 */,
   { matches_reg_braddr_ri,  2, 0, call_863 } /* line 919 */,
   { matches_reg_braddr_rx,  2, 0, call_864 } /* line 920 */,
};

/* stuwa */
static const struct insnsig sigtbl667[2] = {
   { matches_reg_braddr_rr_immasi,  2, 0, call_885 } /* line 944 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_886 } /* line 945 */,
};

/* stw */
static const struct insnsig sigtbl668[3] = {
   { matches_reg_braddr_rr,  2, 0, call_835 } /* line 889 */,
   { matches_reg_braddr_ri,  2, 0, call_836 } /* line 890 */,
   { matches_reg_braddr_rx,  2, 0, call_837 } /* line 891 */,
};

/* stwa */
static const struct insnsig sigtbl669[2] = {
   { matches_reg_braddr_rr_immasi,  2, 0, call_869 } /* line 926 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_870 } /* line 927 */,
};

/* stx */
static const struct insnsig sigtbl670[6] = {
   { matches_fsr_braddr_rr,  2, 0, call_820 } /* line 872 */,
   { matches_fsr_braddr_ri,  2, 0, call_821 } /* line 873 */,
   { matches_fsr_braddr_rx,  2, 0, call_822 } /* line 874 */,
   { matches_reg_braddr_rr,  2, 0, call_838 } /* line 892 */,
   { matches_reg_braddr_ri,  2, 0, call_839 } /* line 893 */,
   { matches_reg_braddr_rx,  2, 0, call_840 } /* line 894 */,
};

/* stxa */
static const struct insnsig sigtbl671[2] = {
   { matches_reg_braddr_rr_immasi,  2, 0, call_871 } /* line 928 */,
   { matches_reg_braddr_ri_asi,  2, 0, call_872 } /* line 929 */,
};

/* sub */
static const struct insnsig sigtbl672[2] = {
   { matches_reg_reg_reg,  3, 0, call_10 } /* line  12 */,
   { matches_reg_i13num_reg,  3, 0, call_11 } /* line  13 */,
};

/* subc */
static const struct insnsig sigtbl673[2] = {
   { matches_reg_reg_reg,  3, 0, call_14 } /* line  16 */,
   { matches_reg_i13num_reg,  3, 0, call_15 } /* line  17 */,
};

/* subcc */
static const struct insnsig sigtbl674[2] = {
   { matches_reg_reg_reg,  3, 0, call_12 } /* line  14 */,
   { matches_reg_i13num_reg,  3, 0, call_13 } /* line  15 */,
};

/* subccc */
static const struct insnsig sigtbl675[2] = {
   { matches_reg_reg_reg,  3, 0, call_16 } /* line  18 */,
   { matches_reg_i13num_reg,  3, 0, call_17 } /* line  19 */,
};

/* subx */
static const struct insnsig sigtbl676[2] = {
   { matches_reg_reg_reg,  3, 0, call_61 } /* line  65 */,
   { matches_reg_i13num_reg,  3, 0, call_62 } /* line  66 */,
};

/* subxcc */
static const struct insnsig sigtbl677[2] = {
   { matches_reg_reg_reg,  3, 0, call_63 } /* line  67 */,
   { matches_reg_i13num_reg,  3, 0, call_64 } /* line  68 */,
};

/* swap */
static const struct insnsig sigtbl678[2] = {
   { matches_braddr_rr_reg,  2, 0, call_738 } /* line 781 */,
   { matches_braddr_ri_reg,  2, 0, call_739 } /* line 782 */,
};

/* swapa */
static const struct insnsig sigtbl679[2] = {
   { matches_braddr_rr_immasi_reg,  2, 0, call_740 } /* line 783 */,
   { matches_braddr_ri_asi_reg,  2, 0, call_741 } /* line 784 */,
};

/* ta */
static const struct insnsig sigtbl680[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_897 } /* line 960 */,
   { matches_icc_trapnum_ri,  2, 0, call_898 } /* line 961 */,
};

/* taddcc */
static const struct insnsig sigtbl681[2] = {
   { matches_reg_reg_reg,  3, 0, call_49 } /* line  51 */,
   { matches_reg_i13num_reg,  3, 0, call_50 } /* line  52 */,
};

/* taddcctv */
static const struct insnsig sigtbl682[2] = {
   { matches_reg_reg_reg,  3, 0, call_51 } /* line  53 */,
   { matches_reg_i13num_reg,  3, 0, call_52 } /* line  54 */,
};

/* tcc */
static const struct insnsig sigtbl683[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_917 } /* line 980 */,
   { matches_icc_trapnum_ri,  2, 0, call_918 } /* line 981 */,
};

/* tcs */
static const struct insnsig sigtbl684[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_919 } /* line 982 */,
   { matches_icc_trapnum_ri,  2, 0, call_920 } /* line 983 */,
};

/* te */
static const struct insnsig sigtbl685[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_903 } /* line 966 */,
   { matches_icc_trapnum_ri,  2, 0, call_904 } /* line 967 */,
};

/* tg */
static const struct insnsig sigtbl686[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_905 } /* line 968 */,
   { matches_icc_trapnum_ri,  2, 0, call_906 } /* line 969 */,
};

/* tge */
static const struct insnsig sigtbl687[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_909 } /* line 972 */,
   { matches_icc_trapnum_ri,  2, 0, call_910 } /* line 973 */,
};

/* tgeu */
static const struct insnsig sigtbl688[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_933 } /* line 997 */,
   { matches_icc_trapnum_ri,  2, 0, call_934 } /* line 998 */,
};

/* tgu */
static const struct insnsig sigtbl689[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_913 } /* line 976 */,
   { matches_icc_trapnum_ri,  2, 0, call_914 } /* line 977 */,
};

/* tl */
static const struct insnsig sigtbl690[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_911 } /* line 974 */,
   { matches_icc_trapnum_ri,  2, 0, call_912 } /* line 975 */,
};

/* tle */
static const struct insnsig sigtbl691[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_907 } /* line 970 */,
   { matches_icc_trapnum_ri,  2, 0, call_908 } /* line 971 */,
};

/* tleu */
static const struct insnsig sigtbl692[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_915 } /* line 978 */,
   { matches_icc_trapnum_ri,  2, 0, call_916 } /* line 979 */,
};

/* tlu */
static const struct insnsig sigtbl693[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_935 } /* line 999 */,
   { matches_icc_trapnum_ri,  2, 0, call_936 } /* line 1000 */,
};

/* tn */
static const struct insnsig sigtbl694[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_899 } /* line 962 */,
   { matches_icc_trapnum_ri,  2, 0, call_900 } /* line 963 */,
};

/* tne */
static const struct insnsig sigtbl695[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_901 } /* line 964 */,
   { matches_icc_trapnum_ri,  2, 0, call_902 } /* line 965 */,
};

/* tneg */
static const struct insnsig sigtbl696[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_923 } /* line 986 */,
   { matches_icc_trapnum_ri,  2, 0, call_924 } /* line 987 */,
};

/* tnz */
static const struct insnsig sigtbl697[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_929 } /* line 993 */,
   { matches_icc_trapnum_ri,  2, 0, call_930 } /* line 994 */,
};

/* tpos */
static const struct insnsig sigtbl698[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_921 } /* line 984 */,
   { matches_icc_trapnum_ri,  2, 0, call_922 } /* line 985 */,
};

/* tst */
static const struct insnsig sigtbl699[1] = {
   { matches_reg,    1, 0, call_964 } /* line 1038 */,
};

/* tsubcc */
static const struct insnsig sigtbl700[2] = {
   { matches_reg_reg_reg,  3, 0, call_53 } /* line  55 */,
   { matches_reg_i13num_reg,  3, 0, call_54 } /* line  56 */,
};

/* tsubcctv */
static const struct insnsig sigtbl701[2] = {
   { matches_reg_reg_reg,  3, 0, call_55 } /* line  57 */,
   { matches_reg_i13num_reg,  3, 0, call_56 } /* line  58 */,
};

/* tvc */
static const struct insnsig sigtbl702[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_925 } /* line 988 */,
   { matches_icc_trapnum_ri,  2, 0, call_926 } /* line 989 */,
};

/* tvs */
static const struct insnsig sigtbl703[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_927 } /* line 990 */,
   { matches_icc_trapnum_ri,  2, 0, call_928 } /* line 991 */,
};

/* tz */
static const struct insnsig sigtbl704[2] = {
   { matches_icc_trapnum_rr,  2, 0, call_931 } /* line 995 */,
   { matches_icc_trapnum_ri,  2, 0, call_932 } /* line 996 */,
};

/* udiv */
static const struct insnsig sigtbl705[2] = {
   { matches_reg_reg_reg,  3, 0, call_89 } /* line  96 */,
   { matches_reg_i13num_reg,  3, 0, call_90 } /* line  97 */,
};

/* udivcc */
static const struct insnsig sigtbl706[2] = {
   { matches_reg_reg_reg,  3, 0, call_93 } /* line 100 */,
   { matches_reg_i13num_reg,  3, 0, call_94 } /* line 101 */,
};

/* udivx */
static const struct insnsig sigtbl707[2] = {
   { matches_reg_reg_reg,  3, 0, call_99 } /* line 108 */,
   { matches_reg_i13num_reg,  3, 0, call_100 } /* line 109 */,
};

/* umul */
static const struct insnsig sigtbl708[2] = {
   { matches_reg_reg_reg,  3, 0, call_77 } /* line  84 */,
   { matches_reg_i13num_reg,  3, 0, call_78 } /* line  85 */,
};

/* umulcc */
static const struct insnsig sigtbl709[2] = {
   { matches_reg_reg_reg,  3, 0, call_81 } /* line  88 */,
   { matches_reg_i13num_reg,  3, 0, call_82 } /* line  89 */,
};

/* wr */
static const struct insnsig sigtbl710[2] = {
   { matches_reg_reg_asr,  3, 0, call_939 } /* line 1005 */,
   { matches_reg_i13num_asr,  3, 0, call_940 } /* line 1006 */,
};

/* wrpr */
static const struct insnsig sigtbl711[2] = {
   { matches_reg_reg_pr,  3, 0, call_944 } /* line 1014 */,
   { matches_reg_i13num_pr,  3, 0, call_945 } /* line 1015 */,
};

/* xnor */
static const struct insnsig sigtbl712[2] = {
   { matches_reg_reg_reg,  3, 0, call_39 } /* line  41 */,
   { matches_reg_i13num_reg,  3, 0, call_40 } /* line  42 */,
};

/* xnorcc */
static const struct insnsig sigtbl713[2] = {
   { matches_reg_reg_reg,  3, 0, call_41 } /* line  43 */,
   { matches_reg_i13num_reg,  3, 0, call_42 } /* line  44 */,
};

/* xor */
static const struct insnsig sigtbl714[2] = {
   { matches_reg_reg_reg,  3, 0, call_35 } /* line  37 */,
   { matches_reg_i13num_reg,  3, 0, call_36 } /* line  38 */,
};

/* xorcc */
static const struct insnsig sigtbl715[2] = {
   { matches_reg_reg_reg,  3, 0, call_37 } /* line  39 */,
   { matches_reg_i13num_reg,  3, 0, call_38 } /* line  40 */,
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
   { "add",           sigtbl73, 2 },
   { "addc",          sigtbl74, 2 },
   { "addcc",         sigtbl75, 2 },
   { "addccc",        sigtbl76, 2 },
   { "addx",          sigtbl77, 2 },
   { "addxcc",        sigtbl78, 2 },
   { "and",           sigtbl79, 2 },
   { "andcc",         sigtbl80, 2 },
   { "andn",          sigtbl81, 2 },
   { "andncc",        sigtbl82, 2 },
   { "ba",            sigtbl83, 2 },
   { "ba,a",          sigtbl84, 2 },
   { "ba,a,pn",       sigtbl85, 1 },
   { "ba,a,pt",       sigtbl86, 1 },
   { "ba,pn",         sigtbl87, 1 },
   { "ba,pt",         sigtbl88, 1 },
   { "bcc",           sigtbl89, 2 },
   { "bcc,a",         sigtbl90, 2 },
   { "bcc,a,pn",      sigtbl91, 1 },
   { "bcc,a,pt",      sigtbl92, 1 },
   { "bcc,pn",        sigtbl93, 1 },
   { "bcc,pt",        sigtbl94, 1 },
   { "bclr",          sigtbl95, 2 },
   { "bcs",           sigtbl96, 2 },
   { "bcs,a",         sigtbl97, 2 },
   { "bcs,a,pn",      sigtbl98, 1 },
   { "bcs,a,pt",      sigtbl99, 1 },
   { "bcs,pn",        sigtbl100, 1 },
   { "bcs,pt",        sigtbl101, 1 },
   { "be",            sigtbl102, 2 },
   { "be,a",          sigtbl103, 2 },
   { "be,a,pn",       sigtbl104, 1 },
   { "be,a,pt",       sigtbl105, 1 },
   { "be,pn",         sigtbl106, 1 },
   { "be,pt",         sigtbl107, 1 },
   { "bg",            sigtbl108, 2 },
   { "bg,a",          sigtbl109, 2 },
   { "bg,a,pn",       sigtbl110, 1 },
   { "bg,a,pt",       sigtbl111, 1 },
   { "bg,pn",         sigtbl112, 1 },
   { "bg,pt",         sigtbl113, 1 },
   { "bge",           sigtbl114, 2 },
   { "bge,a",         sigtbl115, 2 },
   { "bge,a,pn",      sigtbl116, 1 },
   { "bge,a,pt",      sigtbl117, 1 },
   { "bge,pn",        sigtbl118, 1 },
   { "bge,pt",        sigtbl119, 1 },
   { "bgeu",          sigtbl120, 2 },
   { "bgeu,a",        sigtbl121, 2 },
   { "bgeu,a,pn",     sigtbl122, 1 },
   { "bgeu,a,pt",     sigtbl123, 1 },
   { "bgeu,pn",       sigtbl124, 1 },
   { "bgeu,pt",       sigtbl125, 1 },
   { "bgu",           sigtbl126, 2 },
   { "bgu,a",         sigtbl127, 2 },
   { "bgu,a,pn",      sigtbl128, 1 },
   { "bgu,a,pt",      sigtbl129, 1 },
   { "bgu,pn",        sigtbl130, 1 },
   { "bgu,pt",        sigtbl131, 1 },
   { "bl",            sigtbl132, 2 },
   { "bl,a",          sigtbl133, 2 },
   { "bl,a,pn",       sigtbl134, 1 },
   { "bl,a,pt",       sigtbl135, 1 },
   { "bl,pn",         sigtbl136, 1 },
   { "bl,pt",         sigtbl137, 1 },
   { "ble",           sigtbl138, 2 },
   { "ble,a",         sigtbl139, 2 },
   { "ble,a,pn",      sigtbl140, 1 },
   { "ble,a,pt",      sigtbl141, 1 },
   { "ble,pn",        sigtbl142, 1 },
   { "ble,pt",        sigtbl143, 1 },
   { "bleu",          sigtbl144, 2 },
   { "bleu,a",        sigtbl145, 2 },
   { "bleu,a,pn",     sigtbl146, 1 },
   { "bleu,a,pt",     sigtbl147, 1 },
   { "bleu,pn",       sigtbl148, 1 },
   { "bleu,pt",       sigtbl149, 1 },
   { "blu",           sigtbl150, 2 },
   { "blu,a",         sigtbl151, 2 },
   { "blu,a,pn",      sigtbl152, 1 },
   { "blu,a,pt",      sigtbl153, 1 },
   { "blu,pn",        sigtbl154, 1 },
   { "blu,pt",        sigtbl155, 1 },
   { "bn",            sigtbl156, 2 },
   { "bn,a",          sigtbl157, 2 },
   { "bn,a,pn",       sigtbl158, 1 },
   { "bn,a,pt",       sigtbl159, 1 },
   { "bn,pn",         sigtbl160, 1 },
   { "bn,pt",         sigtbl161, 1 },
   { "bne",           sigtbl162, 2 },
   { "bne,a",         sigtbl163, 2 },
   { "bne,a,pn",      sigtbl164, 1 },
   { "bne,a,pt",      sigtbl165, 1 },
   { "bne,pn",        sigtbl166, 1 },
   { "bne,pt",        sigtbl167, 1 },
   { "bneg",          sigtbl168, 2 },
   { "bneg,a",        sigtbl169, 2 },
   { "bneg,a,pn",     sigtbl170, 1 },
   { "bneg,a,pt",     sigtbl171, 1 },
   { "bneg,pn",       sigtbl172, 1 },
   { "bneg,pt",       sigtbl173, 1 },
   { "bnz",           sigtbl174, 2 },
   { "bnz,a",         sigtbl175, 2 },
   { "bnz,a,pn",      sigtbl176, 1 },
   { "bnz,a,pt",      sigtbl177, 1 },
   { "bnz,pn",        sigtbl178, 1 },
   { "bnz,pt",        sigtbl179, 1 },
   { "bpos",          sigtbl180, 2 },
   { "bpos,a",        sigtbl181, 2 },
   { "bpos,a,pn",     sigtbl182, 1 },
   { "bpos,a,pt",     sigtbl183, 1 },
   { "bpos,pn",       sigtbl184, 1 },
   { "bpos,pt",       sigtbl185, 1 },
   { "brgez",         sigtbl186, 1 },
   { "brgez,a",       sigtbl187, 1 },
   { "brgez,a,pn",    sigtbl188, 1 },
   { "brgez,a,pt",    sigtbl189, 1 },
   { "brgez,pn",      sigtbl190, 1 },
   { "brgez,pt",      sigtbl191, 1 },
   { "brgz",          sigtbl192, 1 },
   { "brgz,a",        sigtbl193, 1 },
   { "brgz,a,pn",     sigtbl194, 1 },
   { "brgz,a,pt",     sigtbl195, 1 },
   { "brgz,pn",       sigtbl196, 1 },
   { "brgz,pt",       sigtbl197, 1 },
   { "brlez",         sigtbl198, 1 },
   { "brlez,a",       sigtbl199, 1 },
   { "brlez,a,pn",    sigtbl200, 1 },
   { "brlez,a,pt",    sigtbl201, 1 },
   { "brlez,pn",      sigtbl202, 1 },
   { "brlez,pt",      sigtbl203, 1 },
   { "brlz",          sigtbl204, 1 },
   { "brlz,a",        sigtbl205, 1 },
   { "brlz,a,pn",     sigtbl206, 1 },
   { "brlz,a,pt",     sigtbl207, 1 },
   { "brlz,pn",       sigtbl208, 1 },
   { "brlz,pt",       sigtbl209, 1 },
   { "brnz",          sigtbl210, 1 },
   { "brnz,a",        sigtbl211, 1 },
   { "brnz,a,pn",     sigtbl212, 1 },
   { "brnz,a,pt",     sigtbl213, 1 },
   { "brnz,pn",       sigtbl214, 1 },
   { "brnz,pt",       sigtbl215, 1 },
   { "brz",           sigtbl216, 1 },
   { "brz,a",         sigtbl217, 1 },
   { "brz,a,pn",      sigtbl218, 1 },
   { "brz,a,pt",      sigtbl219, 1 },
   { "brz,pn",        sigtbl220, 1 },
   { "brz,pt",        sigtbl221, 1 },
   { "bset",          sigtbl222, 2 },
   { "btog",          sigtbl223, 2 },
   { "btst",          sigtbl224, 2 },
   { "bvc",           sigtbl225, 2 },
   { "bvc,a",         sigtbl226, 2 },
   { "bvc,a,pn",      sigtbl227, 1 },
   { "bvc,a,pt",      sigtbl228, 1 },
   { "bvc,pn",        sigtbl229, 1 },
   { "bvc,pt",        sigtbl230, 1 },
   { "bvs",           sigtbl231, 2 },
   { "bvs,a",         sigtbl232, 2 },
   { "bvs,a,pn",      sigtbl233, 1 },
   { "bvs,a,pt",      sigtbl234, 1 },
   { "bvs,pn",        sigtbl235, 1 },
   { "bvs,pt",        sigtbl236, 1 },
   { "bz",            sigtbl237, 2 },
   { "bz,a",          sigtbl238, 2 },
   { "bz,a,pn",       sigtbl239, 1 },
   { "bz,a,pt",       sigtbl240, 1 },
   { "bz,pn",         sigtbl241, 1 },
   { "bz,pt",         sigtbl242, 1 },
   { "call",          sigtbl243, 6 },
   { "cas",           sigtbl244, 1 },
   { "casa",          sigtbl245, 2 },
   { "casl",          sigtbl246, 1 },
   { "casn",          sigtbl247, 1 },
   { "casna",         sigtbl248, 2 },
   { "casx",          sigtbl249, 1 },
   { "casxa",         sigtbl250, 2 },
   { "casxl",         sigtbl251, 1 },
   { "clr",           sigtbl252, 3 },
   { "clrb",          sigtbl253, 2 },
   { "clrh",          sigtbl254, 2 },
   { "clrn",          sigtbl255, 2 },
   { "clruw",         sigtbl256, 2 },
   { "clrx",          sigtbl257, 2 },
   { "cmp",           sigtbl258, 2 },
   { "dec",           sigtbl259, 2 },
   { "deccc",         sigtbl260, 2 },
   { "done",          sigtbl261, 1 },
   { "fabsd",         sigtbl262, 1 },
   { "fabsq",         sigtbl263, 1 },
   { "fabss",         sigtbl264, 1 },
   { "faddd",         sigtbl265, 1 },
   { "faddq",         sigtbl266, 1 },
   { "fadds",         sigtbl267, 1 },
   { "fba",           sigtbl268, 2 },
   { "fba,a",         sigtbl269, 2 },
   { "fba,a,pn",      sigtbl270, 1 },
   { "fba,a,pt",      sigtbl271, 1 },
   { "fba,pn",        sigtbl272, 1 },
   { "fba,pt",        sigtbl273, 1 },
   { "fbe",           sigtbl274, 2 },
   { "fbe,a",         sigtbl275, 2 },
   { "fbe,a,pn",      sigtbl276, 1 },
   { "fbe,a,pt",      sigtbl277, 1 },
   { "fbe,pn",        sigtbl278, 1 },
   { "fbe,pt",        sigtbl279, 1 },
   { "fbg",           sigtbl280, 2 },
   { "fbg,a",         sigtbl281, 2 },
   { "fbg,a,pn",      sigtbl282, 1 },
   { "fbg,a,pt",      sigtbl283, 1 },
   { "fbg,pn",        sigtbl284, 1 },
   { "fbg,pt",        sigtbl285, 1 },
   { "fbge",          sigtbl286, 2 },
   { "fbge,a",        sigtbl287, 2 },
   { "fbge,a,pn",     sigtbl288, 1 },
   { "fbge,a,pt",     sigtbl289, 1 },
   { "fbge,pn",       sigtbl290, 1 },
   { "fbge,pt",       sigtbl291, 1 },
   { "fbl",           sigtbl292, 2 },
   { "fbl,a",         sigtbl293, 2 },
   { "fbl,a,pn",      sigtbl294, 1 },
   { "fbl,a,pt",      sigtbl295, 1 },
   { "fbl,pn",        sigtbl296, 1 },
   { "fbl,pt",        sigtbl297, 1 },
   { "fble",          sigtbl298, 2 },
   { "fble,a",        sigtbl299, 2 },
   { "fble,a,pn",     sigtbl300, 1 },
   { "fble,a,pt",     sigtbl301, 1 },
   { "fble,pn",       sigtbl302, 1 },
   { "fble,pt",       sigtbl303, 1 },
   { "fblg",          sigtbl304, 2 },
   { "fblg,a",        sigtbl305, 2 },
   { "fblg,a,pn",     sigtbl306, 1 },
   { "fblg,a,pt",     sigtbl307, 1 },
   { "fblg,pn",       sigtbl308, 1 },
   { "fblg,pt",       sigtbl309, 1 },
   { "fbn",           sigtbl310, 2 },
   { "fbn,a",         sigtbl311, 2 },
   { "fbn,a,pn",      sigtbl312, 1 },
   { "fbn,a,pt",      sigtbl313, 1 },
   { "fbn,pn",        sigtbl314, 1 },
   { "fbn,pt",        sigtbl315, 1 },
   { "fbne",          sigtbl316, 2 },
   { "fbne,a",        sigtbl317, 2 },
   { "fbne,a,pn",     sigtbl318, 1 },
   { "fbne,a,pt",     sigtbl319, 1 },
   { "fbne,pn",       sigtbl320, 1 },
   { "fbne,pt",       sigtbl321, 1 },
   { "fbnz",          sigtbl322, 2 },
   { "fbnz,a",        sigtbl323, 2 },
   { "fbnz,a,pn",     sigtbl324, 1 },
   { "fbnz,a,pt",     sigtbl325, 1 },
   { "fbnz,pn",       sigtbl326, 1 },
   { "fbnz,pt",       sigtbl327, 1 },
   { "fbo",           sigtbl328, 2 },
   { "fbo,a",         sigtbl329, 2 },
   { "fbo,a,pn",      sigtbl330, 1 },
   { "fbo,a,pt",      sigtbl331, 1 },
   { "fbo,pn",        sigtbl332, 1 },
   { "fbo,pt",        sigtbl333, 1 },
   { "fbu",           sigtbl334, 2 },
   { "fbu,a",         sigtbl335, 2 },
   { "fbu,a,pn",      sigtbl336, 1 },
   { "fbu,a,pt",      sigtbl337, 1 },
   { "fbu,pn",        sigtbl338, 1 },
   { "fbu,pt",        sigtbl339, 1 },
   { "fbue",          sigtbl340, 2 },
   { "fbue,a",        sigtbl341, 2 },
   { "fbue,a,pn",     sigtbl342, 1 },
   { "fbue,a,pt",     sigtbl343, 1 },
   { "fbue,pn",       sigtbl344, 1 },
   { "fbue,pt",       sigtbl345, 1 },
   { "fbug",          sigtbl346, 2 },
   { "fbug,a",        sigtbl347, 2 },
   { "fbug,a,pn",     sigtbl348, 1 },
   { "fbug,a,pt",     sigtbl349, 1 },
   { "fbug,pn",       sigtbl350, 1 },
   { "fbug,pt",       sigtbl351, 1 },
   { "fbuge",         sigtbl352, 2 },
   { "fbuge,a",       sigtbl353, 2 },
   { "fbuge,a,pn",    sigtbl354, 1 },
   { "fbuge,a,pt",    sigtbl355, 1 },
   { "fbuge,pn",      sigtbl356, 1 },
   { "fbuge,pt",      sigtbl357, 1 },
   { "fbul",          sigtbl358, 2 },
   { "fbul,a",        sigtbl359, 2 },
   { "fbul,a,pn",     sigtbl360, 1 },
   { "fbul,a,pt",     sigtbl361, 1 },
   { "fbul,pn",       sigtbl362, 1 },
   { "fbul,pt",       sigtbl363, 1 },
   { "fbule",         sigtbl364, 2 },
   { "fbule,a",       sigtbl365, 2 },
   { "fbule,a,pn",    sigtbl366, 1 },
   { "fbule,a,pt",    sigtbl367, 1 },
   { "fbule,pn",      sigtbl368, 1 },
   { "fbule,pt",      sigtbl369, 1 },
   { "fbz",           sigtbl370, 2 },
   { "fbz,a",         sigtbl371, 2 },
   { "fbz,a,pn",      sigtbl372, 1 },
   { "fbz,a,pt",      sigtbl373, 1 },
   { "fbz,pn",        sigtbl374, 1 },
   { "fbz,pt",        sigtbl375, 1 },
   { "fcmpd",         sigtbl376, 1 },
   { "fcmped",        sigtbl377, 1 },
   { "fcmpeq",        sigtbl378, 1 },
   { "fcmpes",        sigtbl379, 1 },
   { "fcmpq",         sigtbl380, 1 },
   { "fcmps",         sigtbl381, 1 },
   { "fdivd",         sigtbl382, 1 },
   { "fdivq",         sigtbl383, 1 },
   { "fdivs",         sigtbl384, 1 },
   { "fdmulq",        sigtbl385, 1 },
   { "fdtoi",         sigtbl386, 1 },
   { "fdtoq",         sigtbl387, 1 },
   { "fdtos",         sigtbl388, 1 },
   { "fdtox",         sigtbl389, 1 },
   { "fitod",         sigtbl390, 1 },
   { "fitoq",         sigtbl391, 1 },
   { "fitos",         sigtbl392, 1 },
   { "flush",         sigtbl393, 2 },
   { "flushw",        sigtbl394, 1 },
   { "fmovd",         sigtbl395, 1 },
   { "fmovda",        sigtbl396, 2 },
   { "fmovdcc",       sigtbl397, 1 },
   { "fmovdcs",       sigtbl398, 1 },
   { "fmovde",        sigtbl399, 2 },
   { "fmovdg",        sigtbl400, 2 },
   { "fmovdge",       sigtbl401, 2 },
   { "fmovdgeu",      sigtbl402, 1 },
   { "fmovdgu",       sigtbl403, 1 },
   { "fmovdl",        sigtbl404, 2 },
   { "fmovdle",       sigtbl405, 2 },
   { "fmovdleu",      sigtbl406, 1 },
   { "fmovdlg",       sigtbl407, 1 },
   { "fmovdlu",       sigtbl408, 1 },
   { "fmovdn",        sigtbl409, 2 },
   { "fmovdne",       sigtbl410, 2 },
   { "fmovdneg",      sigtbl411, 1 },
   { "fmovdnz",       sigtbl412, 2 },
   { "fmovdo",        sigtbl413, 1 },
   { "fmovdpos",      sigtbl414, 1 },
   { "fmovdu",        sigtbl415, 1 },
   { "fmovdue",       sigtbl416, 1 },
   { "fmovdug",       sigtbl417, 1 },
   { "fmovduge",      sigtbl418, 1 },
   { "fmovdul",       sigtbl419, 1 },
   { "fmovdule",      sigtbl420, 1 },
   { "fmovdvc",       sigtbl421, 1 },
   { "fmovdvs",       sigtbl422, 1 },
   { "fmovdz",        sigtbl423, 2 },
   { "fmovq",         sigtbl424, 1 },
   { "fmovqa",        sigtbl425, 2 },
   { "fmovqcc",       sigtbl426, 1 },
   { "fmovqcs",       sigtbl427, 1 },
   { "fmovqe",        sigtbl428, 2 },
   { "fmovqg",        sigtbl429, 2 },
   { "fmovqge",       sigtbl430, 2 },
   { "fmovqgeu",      sigtbl431, 1 },
   { "fmovqgu",       sigtbl432, 1 },
   { "fmovql",        sigtbl433, 2 },
   { "fmovqle",       sigtbl434, 2 },
   { "fmovqleu",      sigtbl435, 1 },
   { "fmovqlg",       sigtbl436, 1 },
   { "fmovqlu",       sigtbl437, 1 },
   { "fmovqn",        sigtbl438, 2 },
   { "fmovqne",       sigtbl439, 2 },
   { "fmovqneg",      sigtbl440, 1 },
   { "fmovqnz",       sigtbl441, 2 },
   { "fmovqo",        sigtbl442, 1 },
   { "fmovqpos",      sigtbl443, 1 },
   { "fmovqu",        sigtbl444, 1 },
   { "fmovque",       sigtbl445, 1 },
   { "fmovqug",       sigtbl446, 1 },
   { "fmovquge",      sigtbl447, 1 },
   { "fmovqul",       sigtbl448, 1 },
   { "fmovqule",      sigtbl449, 1 },
   { "fmovqvc",       sigtbl450, 1 },
   { "fmovqvs",       sigtbl451, 1 },
   { "fmovqz",        sigtbl452, 2 },
   { "fmovrde",       sigtbl453, 1 },
   { "fmovrdg",       sigtbl454, 1 },
   { "fmovrdgez",     sigtbl455, 1 },
   { "fmovrdlez",     sigtbl456, 1 },
   { "fmovrdlz",      sigtbl457, 1 },
   { "fmovrdne",      sigtbl458, 1 },
   { "fmovrdnz",      sigtbl459, 1 },
   { "fmovrdz",       sigtbl460, 1 },
   { "fmovrqe",       sigtbl461, 1 },
   { "fmovrqg",       sigtbl462, 1 },
   { "fmovrqgez",     sigtbl463, 1 },
   { "fmovrqlez",     sigtbl464, 1 },
   { "fmovrqlz",      sigtbl465, 1 },
   { "fmovrqne",      sigtbl466, 1 },
   { "fmovrqnz",      sigtbl467, 1 },
   { "fmovrqz",       sigtbl468, 1 },
   { "fmovrse",       sigtbl469, 1 },
   { "fmovrsg",       sigtbl470, 1 },
   { "fmovrsgez",     sigtbl471, 1 },
   { "fmovrslez",     sigtbl472, 1 },
   { "fmovrslz",      sigtbl473, 1 },
   { "fmovrsne",      sigtbl474, 1 },
   { "fmovrsnz",      sigtbl475, 1 },
   { "fmovrsz",       sigtbl476, 1 },
   { "fmovs",         sigtbl477, 1 },
   { "fmovsa",        sigtbl478, 2 },
   { "fmovscc",       sigtbl479, 1 },
   { "fmovscs",       sigtbl480, 1 },
   { "fmovse",        sigtbl481, 2 },
   { "fmovsg",        sigtbl482, 2 },
   { "fmovsge",       sigtbl483, 2 },
   { "fmovsgeu",      sigtbl484, 1 },
   { "fmovsgu",       sigtbl485, 1 },
   { "fmovsl",        sigtbl486, 2 },
   { "fmovsle",       sigtbl487, 2 },
   { "fmovsleu",      sigtbl488, 1 },
   { "fmovslg",       sigtbl489, 1 },
   { "fmovslu",       sigtbl490, 1 },
   { "fmovsn",        sigtbl491, 2 },
   { "fmovsne",       sigtbl492, 2 },
   { "fmovsneg",      sigtbl493, 1 },
   { "fmovsnz",       sigtbl494, 2 },
   { "fmovso",        sigtbl495, 1 },
   { "fmovspos",      sigtbl496, 1 },
   { "fmovsu",        sigtbl497, 1 },
   { "fmovsue",       sigtbl498, 1 },
   { "fmovsug",       sigtbl499, 1 },
   { "fmovsuge",      sigtbl500, 1 },
   { "fmovsul",       sigtbl501, 1 },
   { "fmovsule",      sigtbl502, 1 },
   { "fmovsvc",       sigtbl503, 1 },
   { "fmovsvs",       sigtbl504, 1 },
   { "fmovsz",        sigtbl505, 2 },
   { "fmuld",         sigtbl506, 1 },
   { "fmulq",         sigtbl507, 1 },
   { "fmuls",         sigtbl508, 1 },
   { "fnegd",         sigtbl509, 1 },
   { "fnegq",         sigtbl510, 1 },
   { "fnegs",         sigtbl511, 1 },
   { "fqtod",         sigtbl512, 1 },
   { "fqtoi",         sigtbl513, 1 },
   { "fqtos",         sigtbl514, 1 },
   { "fqtox",         sigtbl515, 1 },
   { "fsmuld",        sigtbl516, 1 },
   { "fsqrtd",        sigtbl517, 1 },
   { "fsqrtq",        sigtbl518, 1 },
   { "fsqrts",        sigtbl519, 1 },
   { "fstod",         sigtbl520, 1 },
   { "fstoi",         sigtbl521, 1 },
   { "fstoq",         sigtbl522, 1 },
   { "fstox",         sigtbl523, 1 },
   { "fsubd",         sigtbl524, 1 },
   { "fsubq",         sigtbl525, 1 },
   { "fsubs",         sigtbl526, 1 },
   { "fxtod",         sigtbl527, 1 },
   { "fxtoq",         sigtbl528, 1 },
   { "fxtos",         sigtbl529, 1 },
   { "illtrap",       sigtbl530, 1 },
   { "impl1",         sigtbl531, 1 },
   { "impl2",         sigtbl532, 1 },
   { "inc",           sigtbl533, 2 },
   { "inccc",         sigtbl534, 2 },
   { "iprefetch",     sigtbl535, 1 },
   { "jmp",           sigtbl536, 2 },
   { "jmpl",          sigtbl537, 2 },
   { "ld",            sigtbl538, 9 },
   { "lda",           sigtbl539, 4 },
   { "ldd",           sigtbl540, 6 },
   { "ldda",          sigtbl541, 4 },
   { "ldn",           sigtbl542, 2 },
   { "ldna",          sigtbl543, 2 },
   { "ldq",           sigtbl544, 3 },
   { "ldqa",          sigtbl545, 2 },
   { "ldsb",          sigtbl546, 3 },
   { "ldsba",         sigtbl547, 2 },
   { "ldsh",          sigtbl548, 3 },
   { "ldsha",         sigtbl549, 2 },
   { "ldstub",        sigtbl550, 3 },
   { "ldstuba",       sigtbl551, 2 },
   { "ldsw",          sigtbl552, 3 },
   { "ldswa",         sigtbl553, 2 },
   { "ldub",          sigtbl554, 3 },
   { "lduba",         sigtbl555, 2 },
   { "lduh",          sigtbl556, 3 },
   { "lduha",         sigtbl557, 2 },
   { "lduw",          sigtbl558, 3 },
   { "lduwa",         sigtbl559, 2 },
   { "ldx",           sigtbl560, 6 },
   { "ldxa",          sigtbl561, 2 },
   { "membar",        sigtbl562, 1 },
   { "mov",           sigtbl563, 4 },
   { "mova",          sigtbl564, 4 },
   { "movcc",         sigtbl565, 2 },
   { "movcs",         sigtbl566, 2 },
   { "move",          sigtbl567, 4 },
   { "movg",          sigtbl568, 4 },
   { "movge",         sigtbl569, 4 },
   { "movgeu",        sigtbl570, 2 },
   { "movgu",         sigtbl571, 2 },
   { "movl",          sigtbl572, 4 },
   { "movle",         sigtbl573, 4 },
   { "movleu",        sigtbl574, 2 },
   { "movlg",         sigtbl575, 2 },
   { "movlu",         sigtbl576, 2 },
   { "movn",          sigtbl577, 4 },
   { "movne",         sigtbl578, 4 },
   { "movneg",        sigtbl579, 2 },
   { "movnz",         sigtbl580, 4 },
   { "movo",          sigtbl581, 2 },
   { "movpos",        sigtbl582, 2 },
   { "movre",         sigtbl583, 2 },
   { "movrgez",       sigtbl584, 2 },
   { "movrgz",        sigtbl585, 2 },
   { "movrlez",       sigtbl586, 2 },
   { "movrlz",        sigtbl587, 2 },
   { "movrne",        sigtbl588, 2 },
   { "movrnz",        sigtbl589, 2 },
   { "movrz",         sigtbl590, 2 },
   { "movu",          sigtbl591, 2 },
   { "movue",         sigtbl592, 2 },
   { "movug",         sigtbl593, 2 },
   { "movuge",        sigtbl594, 2 },
   { "movul",         sigtbl595, 2 },
   { "movule",        sigtbl596, 2 },
   { "movvc",         sigtbl597, 2 },
   { "movvs",         sigtbl598, 2 },
   { "movz",          sigtbl599, 4 },
   { "mulscc",        sigtbl600, 2 },
   { "mulx",          sigtbl601, 2 },
   { "neg",           sigtbl602, 2 },
   { "nop",           sigtbl603, 1 },
   { "not",           sigtbl604, 2 },
   { "or",            sigtbl605, 3 },
   { "orcc",          sigtbl606, 2 },
   { "orn",           sigtbl607, 2 },
   { "orncc",         sigtbl608, 2 },
   { "popc",          sigtbl609, 2 },
   { "prefetch",      sigtbl610, 2 },
   { "prefetcha",     sigtbl611, 2 },
   { "rd",            sigtbl612, 1 },
   { "rdpr",          sigtbl613, 1 },
   { "restore",       sigtbl614, 3 },
   { "restored",      sigtbl615, 1 },
   { "ret",           sigtbl616, 1 },
   { "retl",          sigtbl617, 1 },
   { "retry",         sigtbl618, 1 },
   { "return",        sigtbl619, 2 },
   { "save",          sigtbl620, 3 },
   { "saved",         sigtbl621, 1 },
   { "sdiv",          sigtbl622, 2 },
   { "sdivcc",        sigtbl623, 2 },
   { "sdivx",         sigtbl624, 2 },
   { "set",           sigtbl625, 1 },
   { "sethi",         sigtbl626, 2 },
   { "setsw",         sigtbl627, 1 },
   { "setuw",         sigtbl628, 1 },
   { "setx",          sigtbl629, 1 },
   { "signx",         sigtbl630, 2 },
   { "sir",           sigtbl631, 1 },
   { "sll",           sigtbl632, 2 },
   { "slln",          sigtbl633, 2 },
   { "sllx",          sigtbl634, 2 },
   { "smul",          sigtbl635, 2 },
   { "smulcc",        sigtbl636, 2 },
   { "sra",           sigtbl637, 2 },
   { "sran",          sigtbl638, 2 },
   { "srax",          sigtbl639, 2 },
   { "srl",           sigtbl640, 2 },
   { "srln",          sigtbl641, 2 },
   { "srlx",          sigtbl642, 2 },
   { "st",            sigtbl643, 9 },
   { "sta",           sigtbl644, 4 },
   { "stb",           sigtbl645, 3 },
   { "stba",          sigtbl646, 2 },
   { "stbar",         sigtbl647, 1 },
   { "std",           sigtbl648, 6 },
   { "stda",          sigtbl649, 4 },
   { "sth",           sigtbl650, 3 },
   { "stha",          sigtbl651, 2 },
   { "stn",           sigtbl652, 2 },
   { "stna",          sigtbl653, 2 },
   { "stq",           sigtbl654, 3 },
   { "stqa",          sigtbl655, 2 },
   { "stsb",          sigtbl656, 3 },
   { "stsba",         sigtbl657, 2 },
   { "stsh",          sigtbl658, 3 },
   { "stsha",         sigtbl659, 2 },
   { "stsw",          sigtbl660, 3 },
   { "stswa",         sigtbl661, 2 },
   { "stub",          sigtbl662, 3 },
   { "stuba",         sigtbl663, 2 },
   { "stuh",          sigtbl664, 3 },
   { "stuha",         sigtbl665, 2 },
   { "stuw",          sigtbl666, 3 },
   { "stuwa",         sigtbl667, 2 },
   { "stw",           sigtbl668, 3 },
   { "stwa",          sigtbl669, 2 },
   { "stx",           sigtbl670, 6 },
   { "stxa",          sigtbl671, 2 },
   { "sub",           sigtbl672, 2 },
   { "subc",          sigtbl673, 2 },
   { "subcc",         sigtbl674, 2 },
   { "subccc",        sigtbl675, 2 },
   { "subx",          sigtbl676, 2 },
   { "subxcc",        sigtbl677, 2 },
   { "swap",          sigtbl678, 2 },
   { "swapa",         sigtbl679, 2 },
   { "ta",            sigtbl680, 2 },
   { "taddcc",        sigtbl681, 2 },
   { "taddcctv",      sigtbl682, 2 },
   { "tcc",           sigtbl683, 2 },
   { "tcs",           sigtbl684, 2 },
   { "te",            sigtbl685, 2 },
   { "tg",            sigtbl686, 2 },
   { "tge",           sigtbl687, 2 },
   { "tgeu",          sigtbl688, 2 },
   { "tgu",           sigtbl689, 2 },
   { "tl",            sigtbl690, 2 },
   { "tle",           sigtbl691, 2 },
   { "tleu",          sigtbl692, 2 },
   { "tlu",           sigtbl693, 2 },
   { "tn",            sigtbl694, 2 },
   { "tne",           sigtbl695, 2 },
   { "tneg",          sigtbl696, 2 },
   { "tnz",           sigtbl697, 2 },
   { "tpos",          sigtbl698, 2 },
   { "tst",           sigtbl699, 1 },
   { "tsubcc",        sigtbl700, 2 },
   { "tsubcctv",      sigtbl701, 2 },
   { "tvc",           sigtbl702, 2 },
   { "tvs",           sigtbl703, 2 },
   { "tz",            sigtbl704, 2 },
   { "udiv",          sigtbl705, 2 },
   { "udivcc",        sigtbl706, 2 },
   { "udivx",         sigtbl707, 2 },
   { "umul",          sigtbl708, 2 },
   { "umulcc",        sigtbl709, 2 },
   { "wr",            sigtbl710, 2 },
   { "wrpr",          sigtbl711, 2 },
   { "xnor",          sigtbl712, 2 },
   { "xnorcc",        sigtbl713, 2 },
   { "xor",           sigtbl714, 2 },
   { "xorcc",         sigtbl715, 2 },
};

const unsigned numopcodes = sizeof(opcodes)/sizeof(opcodes[0]);

