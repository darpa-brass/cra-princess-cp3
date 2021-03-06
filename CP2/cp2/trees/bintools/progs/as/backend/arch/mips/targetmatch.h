/* Automatically generated; do not edit */
#include "targetdefs.h"
struct label; /* from label.h */
struct compound_mem;
void insn_abs_reg(int line, uint8_t val1);
void insn_abs_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_add_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_add_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_add_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_addi_reg_reg_s16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_addu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_addu_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_addu_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_addiu_reg_reg_s16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_and_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_and_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_and_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_andi_reg_reg_u16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_b_symbol(int line, struct expr * val1);
void insn_bal_symbol(int line, struct expr * val1);
void insn_bc1f_symbol(int line, struct expr * val1);
void insn_bc1f_cc_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bc1fl_symbol(int line, struct expr * val1);
void insn_bc1fl_cc_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bc1t_symbol(int line, struct expr * val1);
void insn_bc1t_cc_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bc1tl_symbol(int line, struct expr * val1);
void insn_bc1tl_cc_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bc2f_symbol(int line, struct expr * val1);
void insn_bc2f_cc_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bc2fl_symbol(int line, struct expr * val1);
void insn_bc2fl_cc_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bc2t_symbol(int line, struct expr * val1);
void insn_bc2t_cc_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bc2tl_symbol(int line, struct expr * val1);
void insn_bc2tl_cc_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bc3f_symbol(int line, struct expr * val1);
void insn_bc3f_cc_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bc3fl_symbol(int line, struct expr * val1);
void insn_bc3fl_cc_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bc3t_symbol(int line, struct expr * val1);
void insn_bc3t_cc_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bc3tl_symbol(int line, struct expr * val1);
void insn_bc3tl_cc_symbol(int line, uint8_t val1, struct expr * val2);
void insn_beq_reg_reg_symbol(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_beq_reg_number_symbol(int line, uint8_t val1, uint32_t val2, struct expr * val3);
void insn_beql_reg_reg_symbol(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_beql_reg_number_symbol(int line, uint8_t val1, uint32_t val2, struct expr * val3);
void insn_beqz_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_beqzl_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bgez_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bgezl_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bgezal_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bgezall_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bgtz_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bgtzl_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_blez_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_blezl_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bltz_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bltzl_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bltzal_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bltzall_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bne_reg_reg_symbol(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_bne_reg_number_symbol(int line, uint8_t val1, uint32_t val2, struct expr * val3);
void insn_bnel_reg_reg_symbol(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_bnel_reg_number_symbol(int line, uint8_t val1, uint32_t val2, struct expr * val3);
void insn_bnez_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_bnezl_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_break_(int line);
void insn_break_number(int line, uint32_t val1);
void insn_break_number_number(int line, uint32_t val1, uint32_t val2);
void insn_cache_number_symbol(int line, uint32_t val1, struct expr * val2);
void insn_cache_number_mem(int line, uint32_t val1, struct compound_mem * val2);
void insn_cfc1_reg_freg(int line, uint8_t val1, uint8_t val2);
void insn_cfc2_reg_c2reg(int line, uint8_t val1, uint8_t val2);
void insn_cfc3_reg_c3reg(int line, uint8_t val1, uint8_t val2);
void insn_clo_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_clz_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_cop2_number(int line, uint32_t val1);
void insn_cop3_number(int line, uint32_t val1);
void insn_ctc1_reg_freg(int line, uint8_t val1, uint8_t val2);
void insn_ctc2_reg_c2reg(int line, uint8_t val1, uint8_t val2);
void insn_ctc3_reg_c3reg(int line, uint8_t val1, uint8_t val2);
void insn_deret_(int line);
void insn_div_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_div_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_divu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_divu_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_eret_(int line);
void insn_j_symbol(int line, struct expr * val1);
void insn_j_reg(int line, uint8_t val1);
void insn_jr_reg(int line, uint8_t val1);
void insn_jal_symbol(int line, struct expr * val1);
void insn_jal_reg(int line, uint8_t val1);
void insn_jal_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_jalr_reg(int line, uint8_t val1);
void insn_jalr_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_lb_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_lb_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_lbu_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_lbu_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_ldc1_freg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_ldc1_freg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_ldc2_c2reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_ldc2_c2reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_ldc3_c3reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_ldc3_c3reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_lh_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_lh_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_lhu_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_lhu_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_ll_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_ll_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_lui_reg_u16expr(int line, uint8_t val1, struct expr * val2);
void insn_lw_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_lw_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_lwc1_freg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_lwc1_freg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_lwc2_c2reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_lwc2_c2reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_lwc3_c3reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_lwc3_c3reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_lwl_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_lwl_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_lwr_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_lwr_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_madd_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_maddu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_mfc0_reg_c0reg(int line, uint8_t val1, uint8_t val2);
void insn_mfc0_reg_c0reg_sel(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_mfc1_reg_freg(int line, uint8_t val1, uint8_t val2);
void insn_mfc2_reg_c2reg(int line, uint8_t val1, uint8_t val2);
void insn_mfc2_reg_c2reg_sel(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_mfc3_reg_c3reg(int line, uint8_t val1, uint8_t val2);
void insn_mfc3_reg_c3reg_sel(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_mfhi_reg(int line, uint8_t val1);
void insn_mflo_reg(int line, uint8_t val1);
void insn_move_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_movn_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_movz_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_msub_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_msubu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_mtc0_reg_c0reg(int line, uint8_t val1, uint8_t val2);
void insn_mtc0_reg_c0reg_sel(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_mtc1_reg_freg(int line, uint8_t val1, uint8_t val2);
void insn_mtc2_reg_c2reg(int line, uint8_t val1, uint8_t val2);
void insn_mtc2_reg_c2reg_sel(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_mtc3_reg_c3reg(int line, uint8_t val1, uint8_t val2);
void insn_mtc3_reg_c3reg_sel(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_mthi_reg(int line, uint8_t val1);
void insn_mtlo_reg(int line, uint8_t val1);
void insn_mul_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_mult_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_multu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_neg_reg(int line, uint8_t val1);
void insn_neg_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_negu_reg(int line, uint8_t val1);
void insn_negu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_nop_(int line);
void insn_nor_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_nor_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_nor_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_nori_reg_reg_u16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_not_reg(int line, uint8_t val1);
void insn_not_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_or_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_or_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_or_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_ori_reg_reg_u16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_pref_number_symbol(int line, uint32_t val1, struct expr * val2);
void insn_pref_number_mem(int line, uint32_t val1, struct compound_mem * val2);
void insn_rfe_(int line);
void insn_rol_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_rol_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_ror_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_ror_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_sb_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_sb_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_sc_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_sc_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_sdbbp_(int line);
void insn_sdbbp_number(int line, uint32_t val1);
void insn_sdc1_freg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_sdc1_freg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_sdc2_c2reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_sdc2_c2reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_sdc3_c3reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_sdc3_c3reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_seq_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_seq_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_seq_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_seqi_reg_reg_u16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_sge_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_sge_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_sge_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_sgeu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_sgeu_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_sgeu_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_sgei_reg_reg_s16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_sgeiu_reg_reg_s16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_sgt_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_sgt_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_sgt_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_sgtu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_sgtu_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_sgtu_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_sgti_reg_reg_s16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_sgtiu_reg_reg_s16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_sh_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_sh_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_sle_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_sle_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_sle_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_sleu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_sleu_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_sleu_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_slei_reg_reg_s16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_sleiu_reg_reg_s16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_sll_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_sll_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_sllv_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_slt_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_slt_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_slt_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_slti_reg_reg_s16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_sltu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_sltu_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_sltu_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_sltiu_reg_reg_s16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_sne_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_sne_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_sne_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_snei_reg_reg_u16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_sra_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_sra_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_srav_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_srl_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_srl_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_srlv_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_ssnop_(int line);
void insn_sub_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_sub_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_sub_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_subi_reg_reg_s16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_subu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_subu_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_subu_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_subiu_reg_reg_s16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_sw_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_sw_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_swc1_freg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_swc1_freg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_swc2_c2reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_swc2_c2reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_swc3_c3reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_swc3_c3reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_swl_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_swl_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_swr_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_swr_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_sync_(int line);
void insn_syscall_(int line);
void insn_syscall_number(int line, uint32_t val1);
void insn_teq_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_teq_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_teq_reg_number(int line, uint8_t val1, uint32_t val2);
void insn_teqi_reg_s16expr(int line, uint8_t val1, struct expr * val2);
void insn_tge_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_tge_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_tge_reg_number(int line, uint8_t val1, uint32_t val2);
void insn_tgei_reg_s16expr(int line, uint8_t val1, struct expr * val2);
void insn_tgeu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_tgeu_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_tgeu_reg_number(int line, uint8_t val1, uint32_t val2);
void insn_tgeiu_reg_s16expr(int line, uint8_t val1, struct expr * val2);
void insn_tlbp_(int line);
void insn_tlbr_(int line);
void insn_tlbwi_(int line);
void insn_tlbwr_(int line);
void insn_tlt_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_tlt_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_tlt_reg_number(int line, uint8_t val1, uint32_t val2);
void insn_tlti_reg_s16expr(int line, uint8_t val1, struct expr * val2);
void insn_tltu_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_tltu_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_tltu_reg_number(int line, uint8_t val1, uint32_t val2);
void insn_tltiu_reg_s16expr(int line, uint8_t val1, struct expr * val2);
void insn_tne_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_tne_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_tne_reg_number(int line, uint8_t val1, uint32_t val2);
void insn_tnei_reg_s16expr(int line, uint8_t val1, struct expr * val2);
void insn_ulw_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_ulw_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_usw_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_usw_reg_mem(int line, uint8_t val1, struct compound_mem * val2);
void insn_wait_(int line);
void insn_wait_number(int line, uint32_t val1);
void insn_xor_reg_reg(int line, uint8_t val1, uint8_t val2);
void insn_xor_reg_reg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_xor_reg_reg_number(int line, uint8_t val1, uint8_t val2, uint32_t val3);
void insn_xori_reg_reg_u16expr(int line, uint8_t val1, uint8_t val2, struct expr * val3);
void insn_la_reg_symbol(int line, uint8_t val1, struct expr * val2);
void insn_li_reg_number(int line, uint8_t val1, uint32_t val2);
void insn_abs_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_abs_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_add_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_add_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_add_s_freg_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_add_d_freg_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_ceil_w_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_ceil_w_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_cvt_d_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_cvt_d_w_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_cvt_d_l_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_cvt_s_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_cvt_s_w_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_cvt_s_l_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_cvt_w_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_cvt_w_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_div_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_div_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_div_s_freg_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_div_d_freg_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_floor_w_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_floor_w_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_mov_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_mov_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_movf_reg_reg_cc(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_movf_s_freg_freg_cc(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_movf_d_freg_freg_cc(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_movt_reg_reg_cc(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_movt_s_freg_freg_cc(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_movt_d_freg_freg_cc(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_movn_s_freg_freg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_movn_d_freg_freg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_movz_s_freg_freg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_movz_d_freg_freg_reg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_mul_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_mul_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_mul_s_freg_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_mul_d_freg_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_neg_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_neg_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_round_w_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_round_w_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_sqrt_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_sqrt_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_sub_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_sub_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_sub_s_freg_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_sub_d_freg_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_trunc_w_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_trunc_w_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_f_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_un_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_eq_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ueq_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_olt_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ult_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ole_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ule_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_sf_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ngle_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_seq_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ngl_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_lt_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_nge_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_le_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ngt_s_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_f_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_un_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_eq_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ueq_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_olt_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ult_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ole_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ule_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_sf_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ngle_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_seq_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ngl_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_lt_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_nge_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_le_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_ngt_d_freg_freg(int line, uint8_t val1, uint8_t val2);
void insn_c_f_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_un_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_eq_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ueq_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_olt_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ult_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ole_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ule_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_sf_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ngle_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_seq_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ngl_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_lt_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_nge_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_le_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ngt_s_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_f_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_un_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_eq_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ueq_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_olt_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ult_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ole_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ule_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_sf_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ngle_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_seq_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ngl_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_lt_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_nge_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_le_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void insn_c_ngt_d_cc_freg_freg(int line, uint8_t val1, uint8_t val2, uint8_t val3);
void directive_register_r_rtag(int line, uint8_t val1, uint8_t val2);
void directive_set_s(int line, struct expr * val1);
void directive_unset_s(int line, struct expr * val1);
void directive_set_s_x(int line, struct expr * val1, struct expr * val2);
void directive_file_q(int line, const char * val1);
void directive_file_x(int line, struct expr * val1);
void directive_ident_q(int line, const char * val1);
void directive_gnu_attribute_n_n(int line, uint32_t val1, uint32_t val2);
void directive_text_(int line);
void directive_rdata_(int line);
void directive_data_(int line);
void directive_bss_(int line);
void directive_section_s(int line, struct expr * val1);
void directive_section_s_q(int line, struct expr * val1, const char * val2);
void directive_section_s_q_q(int line, struct expr * val1, const char * val2, const char * val3);
void directive_section_s_q_q_x(int line, struct expr * val1, const char * val2, const char * val3, struct expr * val4);
void directive_section_s_q_q_x_x(int line, struct expr * val1, const char * val2, const char * val3, struct expr * val4, struct expr * val5);
void directive_section_s_q_secty(int line, struct expr * val1, const char * val2, const char * val3);
void directive_section_s_q_secty_x(int line, struct expr * val1, const char * val2, const char * val3, struct expr * val4);
void directive_section_s_q_secty_x_x(int line, struct expr * val1, const char * val2, const char * val3, struct expr * val4, struct expr * val5);
void directive_section_q(int line, const char * val1);
void directive_previous_(int line);
void directive_align_mz(int line, uint32_t val1);
void directive_align_n(int line, uint32_t val1);
void directive_space_n(int line, uint32_t val1);
void directive_lcomm_s_n(int line, struct expr * val1, uint32_t val2);
void directive_lcomm_s_n_n(int line, struct expr * val1, uint32_t val2, uint32_t val3);
void directive_comm_s_n(int line, struct expr * val1, uint32_t val2);
void directive_comm_s_n_n(int line, struct expr * val1, uint32_t val2, uint32_t val3);
void directive_local_s(int line, struct expr * val1);
void directive_globl_s(int line, struct expr * val1);
void directive_global_s(int line, struct expr * val1);
void directive_extern_s(int line, struct expr * val1);
void directive_type_s_symty(int line, struct expr * val1, const char * val2);
void directive_ent_s(int line, struct expr * val1);
void directive_end_s(int line, struct expr * val1);
void directive_size_s_x(int line, struct expr * val1, struct expr * val2);
void directive_frame_r_n_r(int line, uint8_t val1, uint32_t val2, uint8_t val3);
void directive_mask_n_n(int line, uint32_t val1, uint32_t val2);
void directive_fmask_n_n(int line, uint32_t val1, uint32_t val2);
void directive_ascii_q(int line, const char * val1);
void directive_asciz_q(int line, const char * val1);
void directive_8byte_x(int line, struct expr * val1);
void directive_word_x(int line, struct expr * val1);
void directive_4byte_x(int line, struct expr * val1);
void directive_hword_x(int line, struct expr * val1);
void directive_half_x(int line, struct expr * val1);
void directive_short_x(int line, struct expr * val1);
void directive_2byte_x(int line, struct expr * val1);
void directive_byte_x(int line, struct expr * val1);
void directive_int_x(int line, struct expr * val1);
void directive_long_x(int line, struct expr * val1);
void directive_cfi_startproc_(int line);
void directive_cfi_endproc_(int line);
void directive_cfi_signal_frame_(int line);
void directive_cfi_def_cfa_r_n(int line, uint8_t val1, uint32_t val2);
void directive_cfi_def_cfa_n_n(int line, uint32_t val1, uint32_t val2);
void directive_cfi_offset_r_n(int line, uint8_t val1, uint32_t val2);
void directive_cfi_offset_n_n(int line, uint32_t val1, uint32_t val2);
void directive_cfi_return_column_r(int line, uint8_t val1);
void directive_cfi_window_save_(int line);
void directive_cfi_register_n_n(int line, uint32_t val1, uint32_t val2);
void directive_cfi_def_cfa_register_n(int line, uint32_t val1);
void directive_common_s_n_q(int line, struct expr * val1, uint32_t val2, const char * val3);
void directive_reserve_s_n_q(int line, struct expr * val1, uint32_t val2, const char * val3);
void directive_common_s_n_n(int line, struct expr * val1, uint32_t val2, uint32_t val3);
void directive_reserve_s_n_n(int line, struct expr * val1, uint32_t val2, uint32_t val3);
void directive_nword_x(int line, struct expr * val1);
void directive_proc_(int line);
void directive_proc_x(int line, struct expr * val1);
void directive_seg_q(int line, const char * val1);
void directive_skip_n(int line, uint32_t val1);
void directive_xword_x(int line, struct expr * val1);
void directive_section_x_q_secty(int line, struct expr * val1, const char * val2, const char * val3);
void directive_syntax_s(int line, struct expr * val1);
void directive_arch_s(int line, struct expr * val1);
void directive_arch_extension_s(int line, struct expr * val1);
void directive_cpu_s(int line, struct expr * val1);
void directive_cpu_x(int line, struct expr * val1);
void directive_fpu_s(int line, struct expr * val1);
void directive_arm_(int line);
void directive_thumb_(int line);
void directive_code_n(int line, uint32_t val1);
void directive_force_thumb_(int line);
void directive_thumb_func_(int line);
void directive_thumb_set_(int line);
void directive_eabi_attribute_n_n(int line, uint32_t val1, uint32_t val2);
void directive_personality_s(int line, struct expr * val1);
void directive_personalityindex_n(int line, uint32_t val1);
void directive_inst_x(int line, struct expr * val1);
void directive_even_(int line);
void directive_fnstart_(int line);
void directive_fnend_(int line);
