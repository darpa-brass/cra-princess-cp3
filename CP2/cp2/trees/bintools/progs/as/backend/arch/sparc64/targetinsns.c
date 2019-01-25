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

void target_generate_special_sections(void) {
}

u_machword process_expr_qword(int linenum, struct expr * x, unsigned int offset) {
   return process_expr(linenum, x, RELOC_FIELD_DATA64, offset);
}
u_machword process_expr_word(int linenum, struct expr * x, unsigned int offset) {
   return process_expr(linenum, x, RELOC_FIELD_DATA32, offset);
}
u_machword process_expr_hword(int linenum, struct expr * x, unsigned int offset) {
   return process_expr(linenum, x, RELOC_FIELD_DATA16, offset);
}


static void call_xu64(int line, struct expr * var_destsym);
static void illtrap_u22(int line, uint32_t var_imm22);
static void sethi_u22e16(int line, uint32_t var_imm22, uint8_t var_rd);
static void fbfcc_xu64(int line, uint8_t var_fcondA, uint8_t var_a, struct expr * var_destsym);
static void bicc_xu64(int line, uint8_t var_icondA, uint8_t var_a, struct expr * var_destsym);
static void fbpfcc_e13xu64(int line, uint8_t var_fcondA, uint8_t var_a, uint8_t var_p, uint8_t var_fccB, struct expr * var_destsym);
static void bpcc_e17xu64(int line, uint8_t var_icondA, uint8_t var_a, uint8_t var_p, uint8_t var_iccB, struct expr * var_destsym);
static void bpr_e16xu64(int line, uint8_t var_rcondA, uint8_t var_a, uint8_t var_p, uint8_t var_rs1, struct expr * var_destsym);
static void arith_e16e16e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd);
static void popc_e16e16(int line, uint8_t var_rs2, uint8_t var_rd);
static void mul_e16e16e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd);
static void div_e16e16e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd);
static void muldivx_e16e16e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd);
static void jmpl_addr_rre16(int line, struct compound_addr_rr * var_addr, uint8_t var_rd);
static void return_addr_rr(int line, struct compound_addr_rr * var_addr);
static void flush_addr_rr(int line, struct compound_addr_rr * var_addr);
static void flushw_(int line);
static void arith_e16i13e16(int line, uint8_t var_op3a, uint8_t var_rs1, int16_t var_simm13, uint8_t var_rd);
static void popc_i13e16(int line, int16_t var_simm13, uint8_t var_rd);
static void mul_e16i13e16(int line, uint8_t var_op3a, uint8_t var_rs1, int16_t var_simm13, uint8_t var_rd);
static void div_e16i13e16(int line, uint8_t var_op3a, uint8_t var_rs1, int16_t var_simm13, uint8_t var_rd);
static void muldivx_e16i13e16(int line, uint8_t var_op3a, uint8_t var_rs1, int16_t var_simm13, uint8_t var_rd);
static void jmpl_addr_rie16(int line, struct compound_addr_ri * var_addr, uint8_t var_rd);
static void return_addr_ri(int line, struct compound_addr_ri * var_addr);
static void flush_addr_ri(int line, struct compound_addr_ri * var_addr);
static void swap_braddr_rre16(int line, struct compound_braddr_rr * var_addr, uint8_t var_rd);
static void load_braddr_rre16(int line, uint8_t var_op3b, struct compound_braddr_rr * var_addr, uint8_t var_rd);
static void ldstub_braddr_rre16(int line, struct compound_braddr_rr * var_addr, uint8_t var_rd);
static void store_e16braddr_rr(int line, uint8_t var_op3b, uint8_t var_rd, struct compound_braddr_rr * var_addr);
static void stf_e14braddr_rr(int line, uint8_t var_op3b, uint8_t var_fd, struct compound_braddr_rr * var_addr);
static void ldf_braddr_rre14(int line, uint8_t var_op3b, struct compound_braddr_rr * var_addr, uint8_t var_fd);
static void ldfsr_braddr_rre15(int line, struct compound_braddr_rr * var_addr, uint8_t var__);
static void ldxfsr_braddr_rre15(int line, struct compound_braddr_rr * var_addr, uint8_t var__);
static void stfsr_e15braddr_rr(int line, uint8_t var__, struct compound_braddr_rr * var_addr);
static void stxfsr_e15braddr_rr(int line, uint8_t var__, struct compound_braddr_rr * var_addr);
static void swap_braddr_rie16(int line, struct compound_braddr_ri * var_addr, uint8_t var_rd);
static void swapa_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var_addr, uint8_t var_rd);
static void load_braddr_rie16(int line, uint8_t var_op3b, struct compound_braddr_ri * var_addr, uint8_t var_rd);
static void load_braddr_rxe16(int line, uint8_t var_op3b, struct compound_braddr_rx * var_addr, uint8_t var_rd);
static void load_braddr_ri_asie16(int line, uint8_t var_op3b, struct compound_braddr_ri_asi * var_addr, uint8_t var_rd);
static void ldstub_braddr_rie16(int line, struct compound_braddr_ri * var_addr, uint8_t var_rd);
static void ldstub_braddr_rxe16(int line, struct compound_braddr_rx * var_addr, uint8_t var_rd);
static void ldstuba_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var_addr, uint8_t var_rd);
static void store_e16braddr_ri(int line, uint8_t var_op3b, uint8_t var_rd, struct compound_braddr_ri * var_addr);
static void store_e16braddr_rx(int line, uint8_t var_op3b, uint8_t var_rd, struct compound_braddr_rx * var_addr);
static void store_e16braddr_ri_asi(int line, uint8_t var_op3b, uint8_t var_rd, struct compound_braddr_ri_asi * var_addr);
static void ldf_braddr_rie14(int line, uint8_t var_op3b, struct compound_braddr_ri * var_addr, uint8_t var_fd);
static void ldf_braddr_rxe14(int line, uint8_t var_op3b, struct compound_braddr_rx * var_addr, uint8_t var_fd);
static void ldf_braddr_ri_asie14(int line, uint8_t var_op3b, struct compound_braddr_ri_asi * var_addr, uint8_t var_fd);
static void ldfsr_braddr_rie15(int line, struct compound_braddr_ri * var_addr, uint8_t var__);
static void ldfsr_braddr_rxe15(int line, struct compound_braddr_rx * var_addr, uint8_t var__);
static void ldxfsr_braddr_rie15(int line, struct compound_braddr_ri * var_addr, uint8_t var__);
static void ldxfsr_braddr_rxe15(int line, struct compound_braddr_rx * var_addr, uint8_t var__);
static void stf_e14braddr_ri(int line, uint8_t var_op3b, uint8_t var_fd, struct compound_braddr_ri * var_addr);
static void stf_e14braddr_rx(int line, uint8_t var_op3b, uint8_t var_fd, struct compound_braddr_rx * var_addr);
static void stf_e14braddr_ri_asi(int line, uint8_t var_op3b, uint8_t var_fd, struct compound_braddr_ri_asi * var_addr);
static void stfsr_e15braddr_ri(int line, uint8_t var__, struct compound_braddr_ri * var_addr);
static void stfsr_e15braddr_rx(int line, uint8_t var__, struct compound_braddr_rx * var_addr);
static void stxfsr_e15braddr_ri(int line, uint8_t var__, struct compound_braddr_ri * var_addr);
static void stxfsr_e15braddr_rx(int line, uint8_t var__, struct compound_braddr_rx * var_addr);
static void prefetch_braddr_rru5(int line, struct compound_braddr_rr * var_addr, uint8_t var_prefetchfcn);
static void prefetcha_braddr_rr_immasiu5(int line, struct compound_braddr_rr_immasi * var_addr, uint8_t var_prefetchfcn);
static void prefetch_braddr_riu5(int line, struct compound_braddr_ri * var_addr, uint8_t var_prefetchfcn);
static void prefetcha_braddr_ri_asiu5(int line, struct compound_braddr_ri_asi * var_addr, uint8_t var_prefetchfcn);
static void movr_e16e16e16(int line, uint8_t var_rcondB, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd);
static void movr_e16i10e16(int line, uint8_t var_rcondB, uint8_t var_rs1, int16_t var_simm10, uint8_t var_rd);
static void membar_u7(int line, uint8_t var_cmmask);
static void stbar_(int line);
static void rdasr_e11e16(int line, uint8_t var_asr_rs1, uint8_t var_rd);
static void wrasr_e16e16e11(int line, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_asr_rd);
static void wrasr_e16i13e11(int line, uint8_t var_rs1, int16_t var_simm13, uint8_t var_asr_rd);
static void sir_i13(int line, int16_t var_simm13);
static void casa__braddr_r_immasie16e16(int line, uint8_t var_op3b, struct compound_braddr_r_immasi * var_addr, uint8_t var_rs2, uint8_t var_rd);
static void swapa_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var_addr, uint8_t var_rd);
static void ldstuba_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var_addr, uint8_t var_rd);
static void load_braddr_rr_immasie16(int line, uint8_t var_op3b, struct compound_braddr_rr_immasi * var_addr, uint8_t var_rd);
static void store_e16braddr_rr_immasi(int line, uint8_t var_op3b, uint8_t var_rd, struct compound_braddr_rr_immasi * var_addr);
static void ldf_braddr_rr_immasie14(int line, uint8_t var_op3b, struct compound_braddr_rr_immasi * var_addr, uint8_t var_fd);
static void stf_e14braddr_rr_immasi(int line, uint8_t var_op3b, uint8_t var_fd, struct compound_braddr_rr_immasi * var_addr);
static void casa__braddr_r_asie16e16(int line, uint8_t var_op3b, struct compound_braddr_r_asi * var_addr, uint8_t var_rs2, uint8_t var_rd);
static void impl_u5u19(int line, uint8_t var_op3a, uint8_t var_impl1, uint32_t var_impl2);
static void shift_e16e16e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd);
static void shiftx_e16e16e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd);
static void shift_e16u5e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_shcnt32, uint8_t var_rd);
static void shiftx_e16u6e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_shcnt64, uint8_t var_rd);
static void fadd_e14e14e14(int line, uint16_t var_opf, uint8_t var_fs1, uint8_t var_fs2, uint8_t var_fd);
static void fto_e14e14(int line, uint16_t var_opf, uint8_t var_fs2, uint8_t var_fd);
static void fmov_e14e14(int line, uint16_t var_opf, uint8_t var_fs2, uint8_t var_fd);
static void fmul_e14e14e14(int line, uint16_t var_opf, uint8_t var_fs1, uint8_t var_fs2, uint8_t var_fd);
static void fcmp_e13e14e14(int line, uint16_t var_opf, uint8_t var_fccC, uint8_t var_fs1, uint8_t var_fs2);
static void rdpr_e19e16(int line, uint8_t var_priv_rs1, uint8_t var_rd);
static void wrpr_e16e16e19(int line, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_priv_rd);
static void wrpr_e16i13e19(int line, uint8_t var_rs1, int16_t var_simm13, uint8_t var_priv_rd);
static void done_(int line);
static void retry_(int line);
static void saved_(int line);
static void restored_(int line);
static void movcc__e17e16e16(int line, uint8_t var_icond, uint8_t var_iccA, uint8_t var_rs2, uint8_t var_rd);
static void movcc__e13e16e16(int line, uint8_t var_fcond, uint8_t var_fccA, uint8_t var_rs2, uint8_t var_rd);
static void movcc__e17i11e16(int line, uint8_t var_icond, uint8_t var_iccA, int16_t var_simm11, uint8_t var_rd);
static void movcc__e13i11e16(int line, uint8_t var_fcond, uint8_t var_fccA, int16_t var_simm11, uint8_t var_rd);
static void tcc__e17trapnum_rr(int line, uint8_t var_icondA, uint8_t var_iccA, struct compound_trapnum_rr * var_tn);
static void tcc__e17trapnum_ri(int line, uint8_t var_icondA, uint8_t var_iccA, struct compound_trapnum_ri * var_tn);
static void fmov_e16e14e14(int line, uint8_t var_opf_lowA, uint8_t var_rcondB, uint8_t var_rs1, uint8_t var_fs2, uint8_t var_fd);
static void fmov_e17e14e14(int line, uint8_t var_opf_lowB, uint8_t var_icondB, uint8_t var_iccA, uint8_t var_fs2, uint8_t var_fd);
static void fmov_e13e14e14(int line, uint8_t var_opf_lowB, uint8_t var_fcondB, uint8_t var_fccA, uint8_t var_fs2, uint8_t var_fd);
static void call_xu64u32(int line, struct expr * var_destsym, uint32_t var__);
static void sethi__u32e16(int line, uint32_t var_imm, uint8_t var_rd);
static void sethi__xu64e16(int line, struct expr * var_immexpr, uint8_t var_rd);
static void nop__(int line);
static void arith_e16xu64e16(int line, uint8_t var_op3a, uint8_t var_rs1, struct expr * var_immexpr, uint8_t var_rd);
static void subcc__e16e16e16(int line, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_dest);
static void subcc__e16i13e16(int line, uint8_t var_rs1, int16_t var_simm13, uint8_t var_dest);
static void cmp__e16e16(int line, uint8_t var_rs1, uint8_t var_rs2);
static void cmp__e16i13(int line, uint8_t var_rs1, int16_t var_imm);
static void jmp__addr_rr(int line, struct compound_addr_rr * var_addr);
static void jmp__addr_ri(int line, struct compound_addr_ri * var_addr);
static void call__addr_rr(int line, struct compound_addr_rr * var_addr);
static void call__addr_ri(int line, struct compound_addr_ri * var_addr);
static void call__addr_rru32(int line, struct compound_addr_rr * var_addr, uint32_t var__);
static void call__addr_riu32(int line, struct compound_addr_ri * var_addr, uint32_t var__);
static void ret__(int line);
static void retl__(int line);
static void save_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void save__(int line);
static void restore_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void restore__(int line);
static void iprefetch__xu64(int line, struct expr * var_sym);
static void orcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void tst__e16(int line, uint8_t var_rs2);
static void or_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void setuw__u32e16(int line, uint32_t var_num, uint8_t var_rd);
static void set__u32e16(int line, uint32_t var_val, uint8_t var_rd);
static void sra_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void setsw__i32e16(int line, int32_t var_num, uint8_t var_rd);
static void setuw_u32e16(int line, uint32_t var__op0, uint8_t var__op1);
static void sllx_e16u6e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sub_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void or_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void setx__i64e16e16(int line, int64_t var_val, uint8_t var_tmp, uint8_t var_rd);
static void signx__e16e16(int line, uint8_t var_rs1, uint8_t var_rd);
static void signx__e16(int line, uint8_t var_rd);
static void xnor_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void not__e16e16(int line, uint8_t var_rs1, uint8_t var_rd);
static void not__e16(int line, uint8_t var_rd);
static void sub_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void neg__e16e16(int line, uint8_t var_rs1, uint8_t var_rd);
static void neg__e16(int line, uint8_t var_rd);
static void casa_braddr_r_immasie16e16(int line, struct compound_braddr_r_immasi * var__op0, uint8_t var__op1, uint8_t var__op2);
static void cas__e16e16e16(int line, uint8_t var_addr, uint8_t var_rs2, uint8_t var_rd);
static void casl__e16e16e16(int line, uint8_t var_addr, uint8_t var_rs2, uint8_t var_rd);
static void casxa_braddr_r_immasie16e16(int line, struct compound_braddr_r_immasi * var__op0, uint8_t var__op1, uint8_t var__op2);
static void casx__e16e16e16(int line, uint8_t var_addr, uint8_t var_rs2, uint8_t var_rd);
static void casxl__e16e16e16(int line, uint8_t var_addr, uint8_t var_rs2, uint8_t var_rd);
static void add_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void inc__e16(int line, uint8_t var_rd);
static void inc__i13e16(int line, int16_t var_n, uint8_t var_rd);
static void addcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void inccc__e16(int line, uint8_t var_rd);
static void inccc__i13e16(int line, int16_t var_n, uint8_t var_rd);
static void dec__e16(int line, uint8_t var_rd);
static void dec__i13e16(int line, int16_t var_n, uint8_t var_rd);
static void deccc__e16(int line, uint8_t var_rd);
static void deccc__i13e16(int line, int16_t var_n, uint8_t var_rd);
static void andcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void btst__e16e16(int line, uint8_t var_rs2, uint8_t var_rs1);
static void andcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void btst__i13e16(int line, int16_t var_imm, uint8_t var_rs1);
static void bset__e16e16(int line, uint8_t var_rs2, uint8_t var_rd);
static void bset__i13e16(int line, int16_t var_imm, uint8_t var_rd);
static void andn_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void bclr__e16e16(int line, uint8_t var_rs2, uint8_t var_rd);
static void andn_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void bclr__i13e16(int line, int16_t var_imm, uint8_t var_rd);
static void xor_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void btog__e16e16(int line, uint8_t var_rs2, uint8_t var_rd);
static void xor_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void btog__i13e16(int line, int16_t var_imm, uint8_t var_rd);
static void clr___e16(int line, uint8_t var_rd);
static void clr__braddr_rr(int line, uint8_t var_op3b, struct compound_braddr_rr * var_addr);
static void clr__braddr_ri(int line, uint8_t var_op3b, struct compound_braddr_ri * var_addr);
static void srl_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void clruw__e16e16(int line, uint8_t var_rs1, uint8_t var_rd);
static void clruw__e16(int line, uint8_t var_rd);
static void mov__e16e16(int line, uint8_t var_rs2, uint8_t var_rd);
static void mov__i13e16(int line, int16_t var_imm, uint8_t var_rd);
static void rd_e11e16(int line, uint8_t var__op0, uint8_t var__op1);
static void mov__e11e16(int line, uint8_t var_asr, uint8_t var_rd);
static void mov__e16e11(int line, uint8_t var_rs1, uint8_t var_asr);
static void sethi_u32e16(int line, uint32_t var__op0, uint8_t var__op1);
static void sethi_xu64e16(int line, struct expr * var__op0, uint8_t var__op1);
static void add_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void addcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void addc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void addc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void addccc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void addccc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void subcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void subcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void subc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void subc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void subccc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void subccc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void and_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void and_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void andncc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void andncc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void or_e16xu64e16(int line, uint8_t var__op0, struct expr * var__op1, uint8_t var__op2);
static void orcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void orn_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void orn_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void orncc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void orncc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void xorcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void xorcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void xnor_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void xnorcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void xnorcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void save_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void restore_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void taddcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void taddcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void taddcctv_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void taddcctv_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void tsubcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void tsubcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void tsubcctv_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void tsubcctv_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void addx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void addx_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void addxcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void addxcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void subx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void subx_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void subxcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void subxcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void sll_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sll_e16u5e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void srl_e16u5e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sra_e16u5e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sllx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void srlx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void srlx_e16u6e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void srax_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void srax_e16u6e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void umul_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void umul_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void smul_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void smul_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void umulcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void umulcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void smulcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void smulcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void mulscc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void mulscc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void sdiv_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sdiv_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void udiv_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void udiv_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void sdivcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sdivcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void udivcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void udivcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void mulx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void mulx_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void sdivx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sdivx_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void udivx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void udivx_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void fadds_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void faddd_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void faddq_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fsubs_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fsubd_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fsubq_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fcmps_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fcmpd_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fcmpq_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fcmpes_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fcmped_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fcmpeq_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fstox_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fdtox_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fqtox_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fstoi_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fdtoi_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fqtoi_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fxtos_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fxtod_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fxtoq_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fitos_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fitod_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fitoq_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fstod_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fstoq_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fdtos_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fdtoq_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fqtos_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fqtod_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fmovs_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fmovd_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fmovq_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fnegs_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fnegd_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fnegq_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fabss_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fabsd_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fabsq_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fsqrts_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fsqrtd_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fsqrtq_e14e14(int line, uint8_t var__op0, uint8_t var__op1);
static void fmuls_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmuld_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmulq_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fsmuld_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fdmulq_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fdivs_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fdivd_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fdivq_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void brz_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brz_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brz_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brz_a_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brz_a_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brz_a_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brlez_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brlez_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brlez_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brlez_a_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brlez_a_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brlez_a_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brlz_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brlz_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brlz_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brlz_a_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brlz_a_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brlz_a_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brnz_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brnz_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brnz_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brnz_a_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brnz_a_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brnz_a_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brgz_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brgz_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brgz_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brgz_a_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brgz_a_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brgz_a_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brgez_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brgez_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brgez_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brgez_a_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brgez_a_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void brgez_a_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fba_xu64(int line, struct expr * var__op0);
static void fba_a_xu64(int line, struct expr * var__op0);
static void fbn_xu64(int line, struct expr * var__op0);
static void fbn_a_xu64(int line, struct expr * var__op0);
static void fbu_xu64(int line, struct expr * var__op0);
static void fbu_a_xu64(int line, struct expr * var__op0);
static void fbg_xu64(int line, struct expr * var__op0);
static void fbg_a_xu64(int line, struct expr * var__op0);
static void fbug_xu64(int line, struct expr * var__op0);
static void fbug_a_xu64(int line, struct expr * var__op0);
static void fbl_xu64(int line, struct expr * var__op0);
static void fbl_a_xu64(int line, struct expr * var__op0);
static void fbul_xu64(int line, struct expr * var__op0);
static void fbul_a_xu64(int line, struct expr * var__op0);
static void fblg_xu64(int line, struct expr * var__op0);
static void fblg_a_xu64(int line, struct expr * var__op0);
static void fbne_xu64(int line, struct expr * var__op0);
static void fbne_a_xu64(int line, struct expr * var__op0);
static void fbe_xu64(int line, struct expr * var__op0);
static void fbe_a_xu64(int line, struct expr * var__op0);
static void fbue_xu64(int line, struct expr * var__op0);
static void fbue_a_xu64(int line, struct expr * var__op0);
static void fbge_xu64(int line, struct expr * var__op0);
static void fbge_a_xu64(int line, struct expr * var__op0);
static void fbuge_xu64(int line, struct expr * var__op0);
static void fbuge_a_xu64(int line, struct expr * var__op0);
static void fble_xu64(int line, struct expr * var__op0);
static void fble_a_xu64(int line, struct expr * var__op0);
static void fbule_xu64(int line, struct expr * var__op0);
static void fbule_a_xu64(int line, struct expr * var__op0);
static void fbo_xu64(int line, struct expr * var__op0);
static void fbo_a_xu64(int line, struct expr * var__op0);
static void fbnz_xu64(int line, struct expr * var__op0);
static void fbnz_a_xu64(int line, struct expr * var__op0);
static void fbz_xu64(int line, struct expr * var__op0);
static void fbz_a_xu64(int line, struct expr * var__op0);
static void fba_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fba_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fba_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fba_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fba_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fba_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbn_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbn_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbn_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbn_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbn_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbu_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbu_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbu_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbu_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbu_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbu_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbg_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbg_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbg_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbg_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbg_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbg_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbug_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbug_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbug_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbug_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbug_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbug_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbl_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbl_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbl_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbl_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbl_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbl_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbul_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbul_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbul_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbul_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbul_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbul_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fblg_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fblg_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fblg_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fblg_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fblg_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fblg_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbne_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbne_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbne_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbne_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbne_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbne_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbe_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbe_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbe_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbe_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbe_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbe_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbue_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbue_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbue_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbue_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbue_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbue_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbge_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbge_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbge_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbge_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbge_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbge_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbuge_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbuge_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbuge_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbuge_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbuge_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbuge_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fble_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fble_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fble_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fble_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fble_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fble_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbule_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbule_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbule_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbule_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbule_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbule_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbo_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbo_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbo_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbo_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbo_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbo_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbnz_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbnz_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbnz_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbnz_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbnz_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbnz_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbz_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbz_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbz_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbz_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbz_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fbz_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void ba_xu64(int line, struct expr * var__op0);
static void ba_a_xu64(int line, struct expr * var__op0);
static void bn_xu64(int line, struct expr * var__op0);
static void bn_a_xu64(int line, struct expr * var__op0);
static void bne_xu64(int line, struct expr * var__op0);
static void bne_a_xu64(int line, struct expr * var__op0);
static void be_xu64(int line, struct expr * var__op0);
static void be_a_xu64(int line, struct expr * var__op0);
static void bg_xu64(int line, struct expr * var__op0);
static void bg_a_xu64(int line, struct expr * var__op0);
static void ble_xu64(int line, struct expr * var__op0);
static void ble_a_xu64(int line, struct expr * var__op0);
static void bge_xu64(int line, struct expr * var__op0);
static void bge_a_xu64(int line, struct expr * var__op0);
static void bl_xu64(int line, struct expr * var__op0);
static void bl_a_xu64(int line, struct expr * var__op0);
static void bgu_xu64(int line, struct expr * var__op0);
static void bgu_a_xu64(int line, struct expr * var__op0);
static void bleu_xu64(int line, struct expr * var__op0);
static void bleu_a_xu64(int line, struct expr * var__op0);
static void bcc_xu64(int line, struct expr * var__op0);
static void bcc_a_xu64(int line, struct expr * var__op0);
static void bcs_xu64(int line, struct expr * var__op0);
static void bcs_a_xu64(int line, struct expr * var__op0);
static void bpos_xu64(int line, struct expr * var__op0);
static void bpos_a_xu64(int line, struct expr * var__op0);
static void bneg_xu64(int line, struct expr * var__op0);
static void bneg_a_xu64(int line, struct expr * var__op0);
static void bvc_xu64(int line, struct expr * var__op0);
static void bvc_a_xu64(int line, struct expr * var__op0);
static void bvs_xu64(int line, struct expr * var__op0);
static void bvs_a_xu64(int line, struct expr * var__op0);
static void bnz_xu64(int line, struct expr * var__op0);
static void bnz_a_xu64(int line, struct expr * var__op0);
static void bz_xu64(int line, struct expr * var__op0);
static void bz_a_xu64(int line, struct expr * var__op0);
static void bgeu_xu64(int line, struct expr * var__op0);
static void bgeu_a_xu64(int line, struct expr * var__op0);
static void blu_xu64(int line, struct expr * var__op0);
static void blu_a_xu64(int line, struct expr * var__op0);
static void ba_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void ba_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void ba_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void ba_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void ba_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void ba_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bn_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bn_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bn_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bn_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bn_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bne_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bne_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bne_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bne_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bne_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bne_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void be_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void be_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void be_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void be_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void be_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void be_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bg_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bg_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bg_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bg_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bg_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bg_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void ble_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void ble_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void ble_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void ble_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void ble_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void ble_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bge_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bge_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bge_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bge_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bge_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bge_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bl_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bl_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bl_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bl_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bl_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bl_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bgu_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bgu_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bgu_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bgu_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bgu_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bgu_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bleu_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bleu_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bleu_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bleu_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bleu_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bleu_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bcc_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bcc_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bcc_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bcc_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bcc_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bcc_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bcs_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bcs_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bcs_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bcs_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bcs_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bcs_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bpos_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bpos_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bpos_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bpos_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bpos_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bpos_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bneg_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bneg_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bneg_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bneg_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bneg_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bneg_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bvc_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bvc_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bvc_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bvc_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bvc_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bvc_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bvs_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bvs_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bvs_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bvs_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bvs_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bvs_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bnz_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bnz_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bnz_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bnz_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bnz_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bnz_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bz_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bz_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bz_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bz_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bz_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bz_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bgeu_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bgeu_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bgeu_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bgeu_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bgeu_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void bgeu_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void blu_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void blu_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void blu_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void blu_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void blu_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void blu_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1);
static void fmovsa_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovda_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqa_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsn_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdn_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqn_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsne_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdne_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqne_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovse_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovde_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqe_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsg_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdg_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqg_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsle_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdle_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqle_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsge_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdge_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqge_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsl_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdl_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovql_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsgu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdgu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqgu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsleu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdleu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqleu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovscc_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdcc_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqcc_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovscs_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdcs_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqcs_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovspos_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdpos_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqpos_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsneg_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdneg_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqneg_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsvc_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdvc_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqvc_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsvs_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdvs_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqvs_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsnz_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdnz_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqnz_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsz_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdz_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqz_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsgeu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdgeu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqgeu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovslu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdlu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqlu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsa_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovda_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqa_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsn_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdn_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqn_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsu_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdu_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqu_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsg_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdg_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqg_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsug_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdug_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqug_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsl_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdl_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovql_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsul_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdul_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqul_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovslg_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdlg_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqlg_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsne_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdne_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqne_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovse_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovde_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqe_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsue_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdue_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovque_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsge_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdge_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqge_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsuge_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovduge_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovquge_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsle_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdle_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqle_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsule_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdule_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqule_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovso_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdo_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqo_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsnz_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdnz_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqnz_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovsz_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovdz_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovqz_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrsz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrdz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrqz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrslez_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrdlez_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrqlez_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrslz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrdlz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrqlz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrsnz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrdnz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrqnz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrsg_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrdg_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrqg_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrsgez_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrdgez_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrqgez_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrse_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrde_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrqe_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrsne_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrdne_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void fmovrqne_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void mova_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void mova_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movn_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movn_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movne_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movne_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void move_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void move_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movg_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movg_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movle_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movle_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movge_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movge_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movl_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movl_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movgu_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movgu_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movleu_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movleu_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movcc_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movcc_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movcs_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movcs_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movpos_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movpos_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movneg_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movneg_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movvc_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movvc_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movvs_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movvs_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movnz_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movnz_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movz_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movz_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movgeu_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movgeu_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movlu_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movlu_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void mova_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void mova_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movn_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movn_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movu_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movu_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movg_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movg_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movug_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movug_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movl_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movl_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movul_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movul_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movlg_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movlg_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movne_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movne_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void move_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void move_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movue_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movue_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movge_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movge_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movuge_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movuge_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movle_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movle_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movule_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movule_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movo_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movo_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movnz_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movnz_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movz_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movz_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movrz_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movrz_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movrlez_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movrlez_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movrlz_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movrlz_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movrnz_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movrnz_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movrgz_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movrgz_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movrgez_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movrgez_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movre_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movre_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void movrne_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void movrne_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void casa_braddr_r_asie16e16(int line, struct compound_braddr_r_asi * var__op0, uint8_t var__op1, uint8_t var__op2);
static void casxa_braddr_r_asie16e16(int line, struct compound_braddr_r_asi * var__op0, uint8_t var__op1, uint8_t var__op2);
static void ld_braddr_rre14(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ld_braddr_rie14(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ld_braddr_rxe14(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void ldd_braddr_rre14(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ldd_braddr_rie14(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ldd_braddr_rxe14(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void ldq_braddr_rre14(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ldq_braddr_rie14(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ldq_braddr_rxe14(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void ld_braddr_rre15(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ld_braddr_rie15(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ld_braddr_rxe15(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void ldx_braddr_rre15(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ldx_braddr_rie15(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ldx_braddr_rxe15(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void lda_braddr_rr_immasie14(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void lda_braddr_ri_asie14(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void ldda_braddr_rr_immasie14(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void ldda_braddr_ri_asie14(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void ldqa_braddr_rr_immasie14(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void ldqa_braddr_ri_asie14(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void ldsb_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ldsb_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ldsb_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void ldsh_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ldsh_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ldsh_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void ldsw_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ldsw_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ldsw_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void ldub_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ldub_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ldub_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void lduh_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void lduh_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void lduh_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void lduw_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void lduw_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void lduw_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void ldx_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ldx_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ldx_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void ldd_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ldd_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ldd_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void ld_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ld_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ld_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1);
static void ldsba_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void ldsba_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void ldsha_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void ldsha_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void ldswa_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void ldswa_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void lduba_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void lduba_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void lduha_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void lduha_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void lduwa_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void lduwa_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void ldxa_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void ldxa_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void ldda_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void ldda_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void lda_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void lda_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void st_e14braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void st_e14braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void st_e14braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void std_e14braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void std_e14braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void std_e14braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void stq_e14braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void stq_e14braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void stq_e14braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void st_e15braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void st_e15braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void st_e15braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void stx_e15braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void stx_e15braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void stx_e15braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void sta_e14braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void sta_e14braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stda_e14braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stda_e14braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stqa_e14braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stqa_e14braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stb_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void stb_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void stb_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void sth_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void sth_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void sth_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void stw_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void stw_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void stw_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void stx_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void stx_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void stx_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void std_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void std_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void std_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void stsb_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void stsb_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void stsb_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void stub_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void stub_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void stub_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void stsh_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void stsh_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void stsh_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void stuh_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void stuh_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void stuh_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void st_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void st_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void st_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void stsw_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void stsw_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void stsw_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void stuw_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void stuw_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void stuw_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1);
static void stba_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stba_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stha_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stha_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stwa_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stwa_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stxa_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stxa_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stda_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stda_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stsba_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stsba_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stuba_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stuba_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stsha_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stsha_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stuha_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stuha_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stswa_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stswa_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void stuwa_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stuwa_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void sta_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void sta_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void ta_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void ta_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tn_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tn_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tne_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tne_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void te_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void te_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tg_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tg_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tle_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tle_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tge_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tge_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tl_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tl_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tgu_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tgu_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tleu_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tleu_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tcc_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tcc_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tcs_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tcs_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tpos_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tpos_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tneg_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tneg_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tvc_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tvc_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tvs_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tvs_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tnz_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tnz_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tz_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tz_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tgeu_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tgeu_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void tlu_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1);
static void tlu_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1);
static void nop_(int line);
static void wr_e16e16e11(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void wr_e16i13e11(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2);
static void impl1_u5u19(int line, uint8_t var__op0, uint32_t var__op1);
static void impl2_u5u19(int line, uint8_t var__op0, uint32_t var__op1);
static void cmp_e16e16(int line, uint8_t var__op0, uint8_t var__op1);
static void cmp_e16i13(int line, uint8_t var__op0, int16_t var__op1);
static void jmp_addr_rr(int line, struct compound_addr_rr * var__op0);
static void jmp_addr_ri(int line, struct compound_addr_ri * var__op0);
static void call_addr_rr(int line, struct compound_addr_rr * var__op0);
static void call_addr_ri(int line, struct compound_addr_ri * var__op0);
static void call_addr_rru32(int line, struct compound_addr_rr * var__op0, uint32_t var__op1);
static void call_addr_riu32(int line, struct compound_addr_ri * var__op0, uint32_t var__op1);
static void ret_(int line);
static void retl_(int line);
static void save_(int line);
static void restore_(int line);
static void iprefetch_xu64(int line, struct expr * var__op0);
static void tst_e16(int line, uint8_t var__op0);
static void set_u32e16(int line, uint32_t var__op0, uint8_t var__op1);
static void setsw_i32e16(int line, int32_t var__op0, uint8_t var__op1);
static void setx_i64e16e16(int line, int64_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void signx_e16e16(int line, uint8_t var__op0, uint8_t var__op1);
static void signx_e16(int line, uint8_t var__op0);
static void not_e16e16(int line, uint8_t var__op0, uint8_t var__op1);
static void not_e16(int line, uint8_t var__op0);
static void neg_e16e16(int line, uint8_t var__op0, uint8_t var__op1);
static void neg_e16(int line, uint8_t var__op0);
static void cas_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void casl_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void casx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void casxl_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void inc_e16(int line, uint8_t var__op0);
static void inc_i13e16(int line, int16_t var__op0, uint8_t var__op1);
static void inccc_e16(int line, uint8_t var__op0);
static void inccc_i13e16(int line, int16_t var__op0, uint8_t var__op1);
static void dec_e16(int line, uint8_t var__op0);
static void dec_i13e16(int line, int16_t var__op0, uint8_t var__op1);
static void deccc_e16(int line, uint8_t var__op0);
static void deccc_i13e16(int line, int16_t var__op0, uint8_t var__op1);
static void btst_e16e16(int line, uint8_t var__op0, uint8_t var__op1);
static void btst_i13e16(int line, int16_t var__op0, uint8_t var__op1);
static void bset_e16e16(int line, uint8_t var__op0, uint8_t var__op1);
static void bset_i13e16(int line, int16_t var__op0, uint8_t var__op1);
static void bclr_e16e16(int line, uint8_t var__op0, uint8_t var__op1);
static void bclr_i13e16(int line, int16_t var__op0, uint8_t var__op1);
static void btog_e16e16(int line, uint8_t var__op0, uint8_t var__op1);
static void btog_i13e16(int line, int16_t var__op0, uint8_t var__op1);
static void clr_e16(int line, uint8_t var__op0);
static void clrb_braddr_rr(int line, struct compound_braddr_rr * var__op0);
static void clrb_braddr_ri(int line, struct compound_braddr_ri * var__op0);
static void clrh_braddr_rr(int line, struct compound_braddr_rr * var__op0);
static void clrh_braddr_ri(int line, struct compound_braddr_ri * var__op0);
static void clr_braddr_rr(int line, struct compound_braddr_rr * var__op0);
static void clr_braddr_ri(int line, struct compound_braddr_ri * var__op0);
static void clrx_braddr_rr(int line, struct compound_braddr_rr * var__op0);
static void clrx_braddr_ri(int line, struct compound_braddr_ri * var__op0);
static void clruw_e16e16(int line, uint8_t var__op0, uint8_t var__op1);
static void clruw_e16(int line, uint8_t var__op0);
static void mov_e16e16(int line, uint8_t var__op0, uint8_t var__op1);
static void mov_i13e16(int line, int16_t var__op0, uint8_t var__op1);
static void mov_e11e16(int line, uint8_t var__op0, uint8_t var__op1);
static void mov_e16e11(int line, uint8_t var__op0, uint8_t var__op1);
static void ldn_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1);
static void ldn_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1);
static void ldna_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1);
static void ldna_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1);
static void stn_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1);
static void stn_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1);
static void stna_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1);
static void stna_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1);
static void slln_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void slln_e16u6e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void srln_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void srln_e16u6e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sran_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void sran_e16u6e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void casn_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2);
static void casna_braddr_r_immasie16e16(int line, struct compound_braddr_r_immasi * var__op0, uint8_t var__op1, uint8_t var__op2);
static void casna_braddr_r_asie16e16(int line, struct compound_braddr_r_asi * var__op0, uint8_t var__op1, uint8_t var__op2);
static void clrn_braddr_rr(int line, struct compound_braddr_rr * var__op0);
static void clrn_braddr_ri(int line, struct compound_braddr_ri * var__op0);
/*
 * Encoding call defined at ../../../targets/sparc64/encoding.def:396:4-402:6
 */
static void call_xu64(int line, struct expr * var_destsym) {
   uint8_t var_op;
   struct expr * var_distance;
   uint64_t var_disp;
   int32_t var_disp30;
   
   if (true) {
      var_op = 1U /* CALL */;
      var_distance = mkexpr_binary(var_destsym, OP_SUB, mkexpr_label(label_declaredot(line)));
      var_disp = process_expr(line, var_distance, RELOC_FIELD_DISP30, 0);
      var_disp30 =(int32_t)(int64_t)(var_disp >> 2U);
      {
         add32(line,(((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)var_disp30 & 1073741823U)));
      }
      return;
   }
}

/*
 * Encoding illtrap defined at ../../../targets/sparc64/encoding.def:416:4-419:6
 */
static void illtrap_u22(int line, uint32_t var_imm22) {
   uint8_t var_op;
   uint8_t var_rd;
   uint8_t var_op2;
   
   if (true) {
      var_op = 0U /* OP2 */;
      var_rd = 0U /* r0 */;
      var_op2 = 0U /* ILLTRAP */;
      {
         add32(line,(((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op2 & 7U)<< 22U))|(var_imm22 & 4194303U)));
      }
      return;
   }
}

/*
 * Encoding sethi defined at ../../../targets/sparc64/encoding.def:420:4-422:6
 */
static void sethi_u22e16(int line, uint32_t var_imm22, uint8_t var_rd) {
   uint8_t var_op;
   uint8_t var_op2;
   
   if (true) {
      var_op = 0U /* OP2 */;
      var_op2 = 4U /* SETHI */;
      {
         add32(line,(((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op2 & 7U)<< 22U))|(var_imm22 & 4194303U)));
      }
      return;
   }
}

/*
 * Encoding fbfcc defined at ../../../targets/sparc64/encoding.def:440:4-447:6
 */
static void fbfcc_xu64(int line, uint8_t var_fcondA, uint8_t var_a, struct expr * var_destsym) {
   uint8_t var_op;
   uint8_t var_op2;
   struct expr * var_distance;
   uint64_t var_disp;
   int32_t var_disp22;
   
   if (true) {
      var_op = 0U /* OP2 */;
      var_op2 = 6U /* FBFCC */;
      var_distance = mkexpr_binary(var_destsym, OP_SUB, mkexpr_label(label_declaredot(line)));
      var_disp = process_expr(line, var_distance, RELOC_FIELD_DISP22, 0);
      var_disp22 =(int32_t)(int64_t)(var_disp >> 2U);
      {
         add32(line,((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_a & 1U)<< 29U))|((uint32_t)(var_fcondA & 15U)<< 25U))|((uint32_t)(var_op2 & 7U)<< 22U))|((uint32_t)var_disp22 & 4194303U)));
      }
      return;
   }
}

/*
 * Encoding bicc defined at ../../../targets/sparc64/encoding.def:453:4-460:6
 */
static void bicc_xu64(int line, uint8_t var_icondA, uint8_t var_a, struct expr * var_destsym) {
   uint8_t var_op;
   uint8_t var_op2;
   struct expr * var_distance;
   uint64_t var_disp;
   int32_t var_disp22;
   
   if (true) {
      var_op = 0U /* OP2 */;
      var_op2 = 2U /* BICC */;
      var_distance = mkexpr_binary(var_destsym, OP_SUB, mkexpr_label(label_declaredot(line)));
      var_disp = process_expr(line, var_distance, RELOC_FIELD_DISP22, 0);
      var_disp22 =(int32_t)(int64_t)(var_disp >> 2U);
      {
         add32(line,((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_a & 1U)<< 29U))|((uint32_t)(var_icondA & 15U)<< 25U))|((uint32_t)(var_op2 & 7U)<< 22U))|((uint32_t)var_disp22 & 4194303U)));
      }
      return;
   }
}

/*
 * Encoding fbpfcc defined at ../../../targets/sparc64/encoding.def:466:4-473:6
 */
static void fbpfcc_e13xu64(int line, uint8_t var_fcondA, uint8_t var_a, uint8_t var_p, uint8_t var_fccB, struct expr * var_destsym) {
   uint8_t var_op;
   uint8_t var_op2;
   struct expr * var_distance;
   uint64_t var_disp;
   int32_t var_disp19;
   
   if (true) {
      var_op = 0U /* OP2 */;
      var_op2 = 5U /* FBPFCC */;
      var_distance = mkexpr_binary(var_destsym, OP_SUB, mkexpr_label(label_declaredot(line)));
      var_disp = process_expr(line, var_distance, RELOC_FIELD_DISP19, 0);
      var_disp19 =(int32_t)(int64_t)(var_disp >> 2U);
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_a & 1U)<< 29U))|((uint32_t)(var_fcondA & 15U)<< 25U))|((uint32_t)(var_op2 & 7U)<< 22U))|((uint32_t)(var_fccB & 3U)<< 20U))|((uint32_t)(var_p & 1U)<< 19U))|((uint32_t)var_disp19 & 524287U)));
      }
      return;
   }
}

/*
 * Encoding bpcc defined at ../../../targets/sparc64/encoding.def:479:4-486:6
 */
static void bpcc_e17xu64(int line, uint8_t var_icondA, uint8_t var_a, uint8_t var_p, uint8_t var_iccB, struct expr * var_destsym) {
   uint8_t var_op;
   uint8_t var_op2;
   struct expr * var_distance;
   uint64_t var_disp;
   int32_t var_disp19;
   
   if (true) {
      var_op = 0U /* OP2 */;
      var_op2 = 1U /* BPCC */;
      var_distance = mkexpr_binary(var_destsym, OP_SUB, mkexpr_label(label_declaredot(line)));
      var_disp = process_expr(line, var_distance, RELOC_FIELD_DISP19, 0);
      var_disp19 =(int32_t)(int64_t)(var_disp >> 2U);
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_a & 1U)<< 29U))|((uint32_t)(var_icondA & 15U)<< 25U))|((uint32_t)(var_op2 & 7U)<< 22U))|((uint32_t)(var_iccB & 3U)<< 20U))|((uint32_t)(var_p & 1U)<< 19U))|((uint32_t)var_disp19 & 524287U)));
      }
      return;
   }
}

/*
 * Encoding bpr defined at ../../../targets/sparc64/encoding.def:492:4-509:6
 */
static void bpr_e16xu64(int line, uint8_t var_rcondA, uint8_t var_a, uint8_t var_p, uint8_t var_rs1, struct expr * var_destsym) {
   uint8_t var_op;
   uint8_t var_op2;
   struct expr * var_distance;
   uint64_t var_disp;
   uint16_t var_d16;
   int8_t var_d16hi;
   uint16_t var_d16lo;
   uint8_t var__Z17;
   
   if (true) {
      var_op = 0U /* OP2 */;
      var_op2 = 3U /* BPR */;
      var_distance = mkexpr_binary(var_destsym, OP_SUB, mkexpr_label(label_declaredot(line)));
      var_disp = process_expr(line, var_distance, RELOC_FIELD_D16LO, 0);
      var_d16 =(uint16_t)(int16_t)(int64_t)(var_disp >> 2U);
      var_d16hi = 0;
      var_d16lo =(var_d16 & 16383U);
      var__Z17 = 0U;
      {
         add32(line,((((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_a & 1U)<< 29U))|((uint32_t)(var__Z17 & 1U)<< 28U))|((uint32_t)(var_rcondA & 7U)<< 25U))|((uint32_t)(var_op2 & 7U)<< 22U))|((uint32_t)((uint8_t)var_d16hi & 3U)<< 20U))|((uint32_t)(var_p & 1U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|(uint32_t)(var_d16lo & 16383U)));
      }
      return;
   }
}

/*
 * Encoding arith defined at ../../../targets/sparc64/encoding.def:521:4-525:72
 */
static void arith_e16e16e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var__Z19;
   
   if (((((((((((((((((((((((((((var_op3a == 0U /* ADD */)||(var_op3a == 1U /* AND */))||(var_op3a == 2U /* OR */))||(var_op3a == 3U /* XOR */))||(var_op3a == 4U /* SUB */))||(var_op3a == 5U /* ANDN */))||(var_op3a == 6U /* ORN */))||(var_op3a == 7U /* XNOR */))||(var_op3a == 8U /* ADDC */))||(var_op3a == 12U /* SUBC */))||(var_op3a == 16U /* ADDcc */))||(var_op3a == 17U /* ANDcc */))||(var_op3a == 18U /* ORcc */))||(var_op3a == 19U /* XORcc */))||(var_op3a == 20U /* SUBcc */))||(var_op3a == 21U /* ANDNcc */))||(var_op3a == 22U /* ORNcc */))||(var_op3a == 23U /* XNORcc */))||(var_op3a == 24U /* ADDCcc */))||(var_op3a == 28U /* SUBCcc */))||(var_op3a == 32U /* TADDcc */))||(var_op3a == 33U /* TSUBcc */))||(var_op3a == 34U /* TADDccTV */))||(var_op3a == 35U /* TSUBccTV */))||(var_op3a == 60U /* SAVE */))||(var_op3a == 61U /* RESTORE */))) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var__Z19 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z19 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding popc defined at ../../../targets/sparc64/encoding.def:526:4-529:6
 */
static void popc_e16e16(int line, uint8_t var_rs2, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rs1;
   uint8_t var__Z19;
   
   if (true) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var_op3a = 46U /* POPC */;
      var_rs1 = 0U /* r0 */;
      var__Z19 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z19 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding mul defined at ../../../targets/sparc64/encoding.def:530:4-81
 */
static void mul_e16e16e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var__Z19;
   
   if ((((((var_op3a == 10U /* UMUL */)||(var_op3a == 11U /* SMUL */))||(var_op3a == 26U /* UMULcc */))||(var_op3a == 27U /* SMULcc */))||(var_op3a == 36U /* MULScc */))) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var__Z19 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z19 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding div defined at ../../../targets/sparc64/encoding.def:531:4-532:79
 */
static void div_e16e16e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var__Z19;
   
   if (((((var_op3a == 14U /* UDIV */)||(var_op3a == 15U /* SDIV */))||(var_op3a == 30U /* UDIVcc */))||(var_op3a == 31U /* SDIVcc */))) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var__Z19 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z19 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding muldivx defined at ../../../targets/sparc64/encoding.def:533:4-69
 */
static void muldivx_e16e16e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var__Z19;
   
   if ((((var_op3a == 9U /* MULX */)||(var_op3a == 13U /* UDIVX */))||(var_op3a == 45U /* SDIVX */))) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var__Z19 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z19 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding jmpl defined at ../../../targets/sparc64/encoding.def:534:4-537:6
 */
static void jmpl_addr_rre16(int line, struct compound_addr_rr * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z19;
   
   if (true) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var_op3a = 56U /* JMPL */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z19 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z19 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding return defined at ../../../targets/sparc64/encoding.def:538:4-542:6
 */
static void return_addr_rr(int line, struct compound_addr_rr * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rd;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z19;
   
   if (true) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var_op3a = 57U /* RETURN */;
      var_rd = 0U /* r0 */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z19 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z19 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding flush defined at ../../../targets/sparc64/encoding.def:543:4-547:6
 */
static void flush_addr_rr(int line, struct compound_addr_rr * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rd;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z19;
   
   if (true) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var_op3a = 59U /* FLUSH */;
      var_rd = 0U /* r0 */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z19 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z19 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding flushw defined at ../../../targets/sparc64/encoding.def:548:4-553:6
 */
static void flushw_(int line) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rd;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z19;
   
   if (true) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var_op3a = 43U /* FLUSHW */;
      var_rd = 0U /* r0 */;
      var_rs1 = 0U /* r0 */;
      var_rs2 = 0U /* r0 */;
      var__Z19 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z19 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding arith defined at ../../../targets/sparc64/encoding.def:561:4-565:72
 */
static void arith_e16i13e16(int line, uint8_t var_op3a, uint8_t var_rs1, int16_t var_simm13, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   
   if (((((((((((((((((((((((((((var_op3a == 0U /* ADD */)||(var_op3a == 1U /* AND */))||(var_op3a == 2U /* OR */))||(var_op3a == 3U /* XOR */))||(var_op3a == 4U /* SUB */))||(var_op3a == 5U /* ANDN */))||(var_op3a == 6U /* ORN */))||(var_op3a == 7U /* XNOR */))||(var_op3a == 8U /* ADDC */))||(var_op3a == 12U /* SUBC */))||(var_op3a == 16U /* ADDcc */))||(var_op3a == 17U /* ANDcc */))||(var_op3a == 18U /* ORcc */))||(var_op3a == 19U /* XORcc */))||(var_op3a == 20U /* SUBcc */))||(var_op3a == 21U /* ANDNcc */))||(var_op3a == 22U /* ORNcc */))||(var_op3a == 23U /* XNORcc */))||(var_op3a == 24U /* ADDCcc */))||(var_op3a == 28U /* SUBCcc */))||(var_op3a == 32U /* TADDcc */))||(var_op3a == 33U /* TSUBcc */))||(var_op3a == 34U /* TADDccTV */))||(var_op3a == 35U /* TSUBccTV */))||(var_op3a == 60U /* SAVE */))||(var_op3a == 61U /* RESTORE */))) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding popc defined at ../../../targets/sparc64/encoding.def:575:4-578:6
 */
static void popc_i13e16(int line, int16_t var_simm13, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rs1;
   
   if (true) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      var_op3a = 46U /* POPC */;
      var_rs1 = 0U /* r0 */;
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding mul defined at ../../../targets/sparc64/encoding.def:579:4-580:57
 */
static void mul_e16i13e16(int line, uint8_t var_op3a, uint8_t var_rs1, int16_t var_simm13, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   
   if ((((((var_op3a == 10U /* UMUL */)||(var_op3a == 11U /* SMUL */))||(var_op3a == 26U /* UMULcc */))||(var_op3a == 27U /* SMULcc */))||(var_op3a == 36U /* MULScc */))) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding div defined at ../../../targets/sparc64/encoding.def:581:4-582:79
 */
static void div_e16i13e16(int line, uint8_t var_op3a, uint8_t var_rs1, int16_t var_simm13, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   
   if (((((var_op3a == 14U /* UDIV */)||(var_op3a == 15U /* SDIV */))||(var_op3a == 30U /* UDIVcc */))||(var_op3a == 31U /* SDIVcc */))) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding muldivx defined at ../../../targets/sparc64/encoding.def:583:4-72
 */
static void muldivx_e16i13e16(int line, uint8_t var_op3a, uint8_t var_rs1, int16_t var_simm13, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   
   if ((((var_op3a == 9U /* MULX */)||(var_op3a == 13U /* UDIVX */))||(var_op3a == 45U /* SDIVX */))) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding jmpl defined at ../../../targets/sparc64/encoding.def:584:4-587:6
 */
static void jmpl_addr_rie16(int line, struct compound_addr_ri * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if (true) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      var_op3a = 56U /* JMPL */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding return defined at ../../../targets/sparc64/encoding.def:588:4-592:6
 */
static void return_addr_ri(int line, struct compound_addr_ri * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rd;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if (true) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      var_op3a = 57U /* RETURN */;
      var_rd = 0U /* r0 */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding flush defined at ../../../targets/sparc64/encoding.def:593:4-597:6
 */
static void flush_addr_ri(int line, struct compound_addr_ri * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rd;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if (true) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      var_op3a = 59U /* FLUSH */;
      var_rd = 0U /* r0 */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding swap defined at ../../../targets/sparc64/encoding.def:604:4-607:6
 */
static void swap_braddr_rre16(int line, struct compound_braddr_rr * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z22;
   
   if (true) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      var_op3b = 15U /* SWAP */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z22 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z22 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding load defined at ../../../targets/sparc64/encoding.def:609:4-612:6
 */
static void load_braddr_rre16(int line, uint8_t var_op3b, struct compound_braddr_rr * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z22;
   
   if (((((((((var_op3b == 0U /* LDUW */)||(var_op3b == 1U /* LDUB */))||(var_op3b == 2U /* LDUH */))||(var_op3b == 3U /* LDD */))||(var_op3b == 8U /* LDSW */))||(var_op3b == 9U /* LDSB */))||(var_op3b == 10U /* LDSH */))||(var_op3b == 11U /* LDX */))) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z22 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z22 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding ldstub defined at ../../../targets/sparc64/encoding.def:613:4-616:6
 */
static void ldstub_braddr_rre16(int line, struct compound_braddr_rr * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z22;
   
   if (true) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      var_op3b = 13U /* LDSTUB */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z22 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z22 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding store defined at ../../../targets/sparc64/encoding.def:618:4-621:6
 */
static void store_e16braddr_rr(int line, uint8_t var_op3b, uint8_t var_rd, struct compound_braddr_rr * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z22;
   
   if ((((((var_op3b == 4U /* STW */)||(var_op3b == 5U /* STB */))||(var_op3b == 6U /* STH */))||(var_op3b == 7U /* STD */))||(var_op3b == 14U /* STX */))) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z22 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z22 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding stf defined at ../../../targets/sparc64/encoding.def:627:4-630:6
 */
static void stf_e14braddr_rr(int line, uint8_t var_op3b, uint8_t var_fd, struct compound_braddr_rr * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z24;
   
   if ((((var_op3b == 36U /* STF */)||(var_op3b == 39U /* STDF */))||(var_op3b == 38U /* STQF */))) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z24 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z24 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding ldf defined at ../../../targets/sparc64/encoding.def:631:4-634:6
 */
static void ldf_braddr_rre14(int line, uint8_t var_op3b, struct compound_braddr_rr * var_addr, uint8_t var_fd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z24;
   
   if ((((var_op3b == 32U /* LDF */)||(var_op3b == 35U /* LDDF */))||(var_op3b == 34U /* LDQF */))) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z24 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z24 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding ldfsr defined at ../../../targets/sparc64/encoding.def:636:4-640:6
 */
static void ldfsr_braddr_rre15(int line, struct compound_braddr_rr * var_addr, uint8_t var__) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_fd;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z24;
   
   (void)var__;
   if (true) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      var_op3b = 33U /* LDFSR */;
      var_fd = 0U /* f0 */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z24 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z24 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding ldxfsr defined at ../../../targets/sparc64/encoding.def:641:4-645:6
 */
static void ldxfsr_braddr_rre15(int line, struct compound_braddr_rr * var_addr, uint8_t var__) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_fd;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z24;
   
   (void)var__;
   if (true) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      var_op3b = 33U /* LDFSR */;
      var_fd = 1U /* f1 */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z24 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z24 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding stfsr defined at ../../../targets/sparc64/encoding.def:646:4-650:6
 */
static void stfsr_e15braddr_rr(int line, uint8_t var__, struct compound_braddr_rr * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_fd;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z24;
   
   (void)var__;
   if (true) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      var_op3b = 37U /* STFSR */;
      var_fd = 0U /* f0 */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z24 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z24 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding stxfsr defined at ../../../targets/sparc64/encoding.def:651:4-655:6
 */
static void stxfsr_e15braddr_rr(int line, uint8_t var__, struct compound_braddr_rr * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_fd;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z24;
   
   (void)var__;
   if (true) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      var_op3b = 37U /* STFSR */;
      var_fd = 1U /* f1 */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var__Z24 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z24 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding swap defined at ../../../targets/sparc64/encoding.def:661:4-664:6
 */
static void swap_braddr_rie16(int line, struct compound_braddr_ri * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 15U /* SWAP */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding swapa defined at ../../../targets/sparc64/encoding.def:665:4-668:6
 */
static void swapa_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 31U /* SWAPA */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding load defined at ../../../targets/sparc64/encoding.def:670:4-673:6
 */
static void load_braddr_rie16(int line, uint8_t var_op3b, struct compound_braddr_ri * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if (((((((((var_op3b == 0U /* LDUW */)||(var_op3b == 1U /* LDUB */))||(var_op3b == 2U /* LDUH */))||(var_op3b == 3U /* LDD */))||(var_op3b == 8U /* LDSW */))||(var_op3b == 9U /* LDSB */))||(var_op3b == 10U /* LDSH */))||(var_op3b == 11U /* LDX */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding load defined at ../../../targets/sparc64/encoding.def:674:4-678:6
 */
static void load_braddr_rxe16(int line, uint8_t var_op3b, struct compound_braddr_rx * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   struct expr * var_simm13x;
   int16_t var_simm13;
   
   if (((((((((var_op3b == 0U /* LDUW */)||(var_op3b == 1U /* LDUB */))||(var_op3b == 2U /* LDUH */))||(var_op3b == 3U /* LDD */))||(var_op3b == 8U /* LDSW */))||(var_op3b == 9U /* LDSB */))||(var_op3b == 10U /* LDSH */))||(var_op3b == 11U /* LDX */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13x =(var_addr -> m1);
      }
      var_simm13 =(int16_t)(int64_t)process_expr(line, var_simm13x, RELOC_FIELD_SIMM13, 0);
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding load defined at ../../../targets/sparc64/encoding.def:679:4-682:6
 */
static void load_braddr_ri_asie16(int line, uint8_t var_op3b, struct compound_braddr_ri_asi * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if (((((((((var_op3b == 16U /* LDUWA */)||(var_op3b == 17U /* LDUBA */))||(var_op3b == 18U /* LDUHA */))||(var_op3b == 19U /* LDDA */))||(var_op3b == 24U /* LDSWA */))||(var_op3b == 25U /* LDSBA */))||(var_op3b == 26U /* LDSHA */))||(var_op3b == 27U /* LDXA */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding ldstub defined at ../../../targets/sparc64/encoding.def:683:4-686:6
 */
static void ldstub_braddr_rie16(int line, struct compound_braddr_ri * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 13U /* LDSTUB */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding ldstub defined at ../../../targets/sparc64/encoding.def:687:4-691:6
 */
static void ldstub_braddr_rxe16(int line, struct compound_braddr_rx * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   struct expr * var_simm13x;
   int16_t var_simm13;
   
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 13U /* LDSTUB */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13x =(var_addr -> m1);
      }
      var_simm13 =(int16_t)(int64_t)process_expr(line, var_simm13x, RELOC_FIELD_SIMM13, 0);
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding ldstuba defined at ../../../targets/sparc64/encoding.def:692:4-695:6
 */
static void ldstuba_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 29U /* LDSTUBA */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding store defined at ../../../targets/sparc64/encoding.def:697:4-700:6
 */
static void store_e16braddr_ri(int line, uint8_t var_op3b, uint8_t var_rd, struct compound_braddr_ri * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if ((((((var_op3b == 4U /* STW */)||(var_op3b == 5U /* STB */))||(var_op3b == 6U /* STH */))||(var_op3b == 7U /* STD */))||(var_op3b == 14U /* STX */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding store defined at ../../../targets/sparc64/encoding.def:701:4-705:6
 */
static void store_e16braddr_rx(int line, uint8_t var_op3b, uint8_t var_rd, struct compound_braddr_rx * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   struct expr * var_simm13x;
   int16_t var_simm13;
   
   if ((((((var_op3b == 4U /* STW */)||(var_op3b == 5U /* STB */))||(var_op3b == 6U /* STH */))||(var_op3b == 7U /* STD */))||(var_op3b == 14U /* STX */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13x =(var_addr -> m1);
      }
      var_simm13 =(int16_t)(int64_t)process_expr(line, var_simm13x, RELOC_FIELD_SIMM13, 0);
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding store defined at ../../../targets/sparc64/encoding.def:706:4-709:6
 */
static void store_e16braddr_ri_asi(int line, uint8_t var_op3b, uint8_t var_rd, struct compound_braddr_ri_asi * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if ((((((var_op3b == 20U /* STWA */)||(var_op3b == 21U /* STBA */))||(var_op3b == 22U /* STHA */))||(var_op3b == 23U /* STDA */))||(var_op3b == 30U /* STXA */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding ldf defined at ../../../targets/sparc64/encoding.def:715:4-718:6
 */
static void ldf_braddr_rie14(int line, uint8_t var_op3b, struct compound_braddr_ri * var_addr, uint8_t var_fd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if ((((var_op3b == 32U /* LDF */)||(var_op3b == 35U /* LDDF */))||(var_op3b == 34U /* LDQF */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding ldf defined at ../../../targets/sparc64/encoding.def:719:4-723:6
 */
static void ldf_braddr_rxe14(int line, uint8_t var_op3b, struct compound_braddr_rx * var_addr, uint8_t var_fd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   struct expr * var_simm13x;
   int16_t var_simm13;
   
   if ((((var_op3b == 32U /* LDF */)||(var_op3b == 35U /* LDDF */))||(var_op3b == 34U /* LDQF */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13x =(var_addr -> m1);
      }
      var_simm13 =(int16_t)(int64_t)process_expr(line, var_simm13x, RELOC_FIELD_SIMM13, 0);
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding ldf defined at ../../../targets/sparc64/encoding.def:724:4-727:6
 */
static void ldf_braddr_ri_asie14(int line, uint8_t var_op3b, struct compound_braddr_ri_asi * var_addr, uint8_t var_fd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if ((((var_op3b == 48U /* LDFA */)||(var_op3b == 51U /* LDDFA */))||(var_op3b == 50U /* LDQFA */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding ldfsr defined at ../../../targets/sparc64/encoding.def:728:4-732:6
 */
static void ldfsr_braddr_rie15(int line, struct compound_braddr_ri * var_addr, uint8_t var__) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_fd;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   (void)var__;
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 33U /* LDFSR */;
      var_fd = 0U /* f0 */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding ldfsr defined at ../../../targets/sparc64/encoding.def:733:4-738:6
 */
static void ldfsr_braddr_rxe15(int line, struct compound_braddr_rx * var_addr, uint8_t var__) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_fd;
   uint8_t var_rs1;
   struct expr * var_simm13x;
   int16_t var_simm13;
   
   (void)var__;
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 33U /* LDFSR */;
      var_fd = 0U /* f0 */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13x =(var_addr -> m1);
      }
      var_simm13 =(int16_t)(int64_t)process_expr(line, var_simm13x, RELOC_FIELD_SIMM13, 0);
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding ldxfsr defined at ../../../targets/sparc64/encoding.def:739:4-743:6
 */
static void ldxfsr_braddr_rie15(int line, struct compound_braddr_ri * var_addr, uint8_t var__) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_fd;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   (void)var__;
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 33U /* LDFSR */;
      var_fd = 1U /* f1 */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding ldxfsr defined at ../../../targets/sparc64/encoding.def:744:4-749:6
 */
static void ldxfsr_braddr_rxe15(int line, struct compound_braddr_rx * var_addr, uint8_t var__) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_fd;
   uint8_t var_rs1;
   struct expr * var_simm13x;
   int16_t var_simm13;
   
   (void)var__;
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 33U /* LDFSR */;
      var_fd = 1U /* f1 */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13x =(var_addr -> m1);
      }
      var_simm13 =(int16_t)(int64_t)process_expr(line, var_simm13x, RELOC_FIELD_SIMM13, 0);
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding stf defined at ../../../targets/sparc64/encoding.def:750:4-753:6
 */
static void stf_e14braddr_ri(int line, uint8_t var_op3b, uint8_t var_fd, struct compound_braddr_ri * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if ((((var_op3b == 36U /* STF */)||(var_op3b == 39U /* STDF */))||(var_op3b == 38U /* STQF */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding stf defined at ../../../targets/sparc64/encoding.def:754:4-758:6
 */
static void stf_e14braddr_rx(int line, uint8_t var_op3b, uint8_t var_fd, struct compound_braddr_rx * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   struct expr * var_simm13x;
   int16_t var_simm13;
   
   if ((((var_op3b == 36U /* STF */)||(var_op3b == 39U /* STDF */))||(var_op3b == 38U /* STQF */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13x =(var_addr -> m1);
      }
      var_simm13 =(int16_t)(int64_t)process_expr(line, var_simm13x, RELOC_FIELD_SIMM13, 0);
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding stf defined at ../../../targets/sparc64/encoding.def:759:4-762:6
 */
static void stf_e14braddr_ri_asi(int line, uint8_t var_op3b, uint8_t var_fd, struct compound_braddr_ri_asi * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if ((((var_op3b == 52U /* STFA */)||(var_op3b == 55U /* STDFA */))||(var_op3b == 54U /* STQFA */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding stfsr defined at ../../../targets/sparc64/encoding.def:763:4-767:6
 */
static void stfsr_e15braddr_ri(int line, uint8_t var__, struct compound_braddr_ri * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_fd;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   (void)var__;
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 37U /* STFSR */;
      var_fd = 0U /* f0 */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding stfsr defined at ../../../targets/sparc64/encoding.def:768:4-773:6
 */
static void stfsr_e15braddr_rx(int line, uint8_t var__, struct compound_braddr_rx * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_fd;
   uint8_t var_rs1;
   struct expr * var_simm13x;
   int16_t var_simm13;
   
   (void)var__;
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 37U /* STFSR */;
      var_fd = 0U /* f0 */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13x =(var_addr -> m1);
      }
      var_simm13 =(int16_t)(int64_t)process_expr(line, var_simm13x, RELOC_FIELD_SIMM13, 0);
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding stxfsr defined at ../../../targets/sparc64/encoding.def:774:4-778:6
 */
static void stxfsr_e15braddr_ri(int line, uint8_t var__, struct compound_braddr_ri * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_fd;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   (void)var__;
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 37U /* STFSR */;
      var_fd = 1U /* f1 */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding stxfsr defined at ../../../targets/sparc64/encoding.def:779:4-784:6
 */
static void stxfsr_e15braddr_rx(int line, uint8_t var__, struct compound_braddr_rx * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_fd;
   uint8_t var_rs1;
   struct expr * var_simm13x;
   int16_t var_simm13;
   
   (void)var__;
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 37U /* STFSR */;
      var_fd = 1U /* f1 */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13x =(var_addr -> m1);
      }
      var_simm13 =(int16_t)(int64_t)process_expr(line, var_simm13x, RELOC_FIELD_SIMM13, 0);
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding prefetch defined at ../../../targets/sparc64/encoding.def:790:4-794:6
 */
static void prefetch_braddr_rru5(int line, struct compound_braddr_rr * var_addr, uint8_t var_prefetchfcn) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var_imm_asi;
   
   if (true) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      var_op3b = 45U /* PREFETCH */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
      }
      var_imm_asi = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_prefetchfcn & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_imm_asi & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding prefetcha defined at ../../../targets/sparc64/encoding.def:795:4-798:6
 */
static void prefetcha_braddr_rr_immasiu5(int line, struct compound_braddr_rr_immasi * var_addr, uint8_t var_prefetchfcn) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var_imm_asi;
   
   if (true) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      var_op3b = 61U /* PREFETCHA */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
         var_imm_asi =(var_addr -> m2);
      }
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_prefetchfcn & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_imm_asi & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding prefetch defined at ../../../targets/sparc64/encoding.def:803:4-806:6
 */
static void prefetch_braddr_riu5(int line, struct compound_braddr_ri * var_addr, uint8_t var_prefetchfcn) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 45U /* PREFETCH */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_prefetchfcn & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding prefetcha defined at ../../../targets/sparc64/encoding.def:807:4-810:6
 */
static void prefetcha_braddr_ri_asiu5(int line, struct compound_braddr_ri_asi * var_addr, uint8_t var_prefetchfcn) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   int16_t var_simm13;
   
   if (true) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      var_op3b = 61U /* PREFETCHA */;
      {
         var_rs1 =(var_addr -> m0);
         var_simm13 =(var_addr -> m1);
      }
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_prefetchfcn & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding movr defined at ../../../targets/sparc64/encoding.def:817:4-819:6
 */
static void movr_e16e16e16(int line, uint8_t var_rcondB, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var__Z30;
   
   if (true) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var_op3a = 47U /* MOVR */;
      var__Z30 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_rcondB & 7U)<< 10U))|((uint32_t)(var__Z30 & 31U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding movr defined at ../../../targets/sparc64/encoding.def:826:4-828:6
 */
static void movr_e16i10e16(int line, uint8_t var_rcondB, uint8_t var_rs1, int16_t var_simm10, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   
   if (true) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      var_op3a = 47U /* MOVR */;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_rcondB & 7U)<< 10U))|(uint32_t)((uint16_t)var_simm10 & 1023U)));
      }
      return;
   }
}

/*
 * Encoding membar defined at ../../../targets/sparc64/encoding.def:835:4-841:6
 */
static void membar_u7(int line, uint8_t var_cmmask) {
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rd;
   uint8_t var_asr_rs1;
   uint8_t var_i;
   uint8_t var__Z33;
   
   if (true) {
      var_op = 2U /* OP3A */;
      var_op3a = 40U /* RDASR */;
      var_rd = 0U /* r0 */;
      var_asr_rs1 = 15U /* MEMBAR */;
      var_i = 1U;
      var__Z33 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_asr_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z33 & 63U)<< 7U))|(uint32_t)(var_cmmask & 127U)));
      }
      return;
   }
}

/*
 * Encoding stbar defined at ../../../targets/sparc64/encoding.def:843:4-850:6
 */
static void stbar_(int line) {
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rd;
   uint8_t var_asr_rs1;
   uint8_t var_cmmask;
   uint8_t var_i;
   uint8_t var__Z33;
   
   if (true) {
      var_op = 2U /* OP3A */;
      var_op3a = 40U /* RDASR */;
      var_rd = 0U /* r0 */;
      var_asr_rs1 = 15U /* MEMBAR */;
      var_cmmask = 0U;
      var_i = 0U;
      var__Z33 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_asr_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z33 & 63U)<< 7U))|(uint32_t)(var_cmmask & 127U)));
      }
      return;
   }
}

/*
 * Encoding rdasr defined at ../../../targets/sparc64/encoding.def:852:4-857:6
 */
static void rdasr_e11e16(int line, uint8_t var_asr_rs1, uint8_t var_rd) {
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_cmmask;
   uint8_t var_i;
   uint8_t var__Z33;
   
   if (true) {
      var_op = 2U /* OP3A */;
      var_op3a = 40U /* RDASR */;
      var_cmmask = 0U;
      var_i = 0U;
      var__Z33 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_asr_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z33 & 63U)<< 7U))|(uint32_t)(var_cmmask & 127U)));
      }
      return;
   }
}

/*
 * Encoding wrasr defined at ../../../targets/sparc64/encoding.def:863:4-34
 */
static void wrasr_e16e16e11(int line, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_asr_rd) {
   uint8_t var_i;
   uint8_t var_op3a;
   uint8_t var_op;
   uint8_t var__Z35;
   
   if (true) {
      var_i = 0U;
      var_op3a = 48U /* WRASR */;
      var_op = 2U /* OP3A */;
      var__Z35 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_asr_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z35 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding wrasr defined at ../../../targets/sparc64/encoding.def:869:4-37
 */
static void wrasr_e16i13e11(int line, uint8_t var_rs1, int16_t var_simm13, uint8_t var_asr_rd) {
   uint8_t var_i;
   uint8_t var_op3a;
   uint8_t var_op;
   
   if (true) {
      var_i = 1U;
      var_op3a = 48U /* WRASR */;
      var_op = 2U /* OP3A */;
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_asr_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding sir defined at ../../../targets/sparc64/encoding.def:870:4-873:6
 */
static void sir_i13(int line, int16_t var_simm13) {
   uint8_t var_i;
   uint8_t var_op3a;
   uint8_t var_op;
   uint8_t var_asr_rd;
   uint8_t var_rs1;
   
   if (true) {
      var_i = 1U;
      var_op3a = 48U /* WRASR */;
      var_op = 2U /* OP3A */;
      var_asr_rd = 15U /* MEMBAR */;
      var_rs1 = 0U /* r0 */;
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_asr_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding casa_ defined at ../../../targets/sparc64/encoding.def:880:4-882:6
 */
static void casa__braddr_r_immasie16e16(int line, uint8_t var_op3b, struct compound_braddr_r_immasi * var_addr, uint8_t var_rs2, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   uint8_t var_imm_asi;
   
   if (((var_op3b == 60U /* CASA */)||(var_op3b == 62U /* CASXA */))) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_imm_asi =(var_addr -> m1);
      }
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_imm_asi & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding swapa defined at ../../../targets/sparc64/encoding.def:883:4-886:6
 */
static void swapa_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var_imm_asi;
   
   if (true) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      var_op3b = 31U /* SWAPA */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
         var_imm_asi =(var_addr -> m2);
      }
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_imm_asi & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding ldstuba defined at ../../../targets/sparc64/encoding.def:887:4-890:6
 */
static void ldstuba_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3b;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var_imm_asi;
   
   if (true) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      var_op3b = 29U /* LDSTUBA */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
         var_imm_asi =(var_addr -> m2);
      }
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_imm_asi & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding load defined at ../../../targets/sparc64/encoding.def:892:4-895:6
 */
static void load_braddr_rr_immasie16(int line, uint8_t var_op3b, struct compound_braddr_rr_immasi * var_addr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var_imm_asi;
   
   if (((((((((var_op3b == 16U /* LDUWA */)||(var_op3b == 17U /* LDUBA */))||(var_op3b == 18U /* LDUHA */))||(var_op3b == 19U /* LDDA */))||(var_op3b == 24U /* LDSWA */))||(var_op3b == 25U /* LDSBA */))||(var_op3b == 26U /* LDSHA */))||(var_op3b == 27U /* LDXA */))) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
         var_imm_asi =(var_addr -> m2);
      }
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_imm_asi & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding store defined at ../../../targets/sparc64/encoding.def:896:4-899:6
 */
static void store_e16braddr_rr_immasi(int line, uint8_t var_op3b, uint8_t var_rd, struct compound_braddr_rr_immasi * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var_imm_asi;
   
   if ((((((var_op3b == 20U /* STWA */)||(var_op3b == 21U /* STBA */))||(var_op3b == 22U /* STHA */))||(var_op3b == 23U /* STDA */))||(var_op3b == 30U /* STXA */))) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
         var_imm_asi =(var_addr -> m2);
      }
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_imm_asi & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding ldf defined at ../../../targets/sparc64/encoding.def:905:4-908:6
 */
static void ldf_braddr_rr_immasie14(int line, uint8_t var_op3b, struct compound_braddr_rr_immasi * var_addr, uint8_t var_fd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var_imm_asi;
   
   if ((((var_op3b == 48U /* LDFA */)||(var_op3b == 51U /* LDDFA */))||(var_op3b == 50U /* LDQFA */))) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
         var_imm_asi =(var_addr -> m2);
      }
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_imm_asi & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding stf defined at ../../../targets/sparc64/encoding.def:909:4-912:6
 */
static void stf_e14braddr_rr_immasi(int line, uint8_t var_op3b, uint8_t var_fd, struct compound_braddr_rr_immasi * var_addr) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var_imm_asi;
   
   if ((((var_op3b == 52U /* STFA */)||(var_op3b == 55U /* STDFA */))||(var_op3b == 54U /* STQFA */))) {
      var_i = 0U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
         var_rs2 =(var_addr -> m1);
         var_imm_asi =(var_addr -> m2);
      }
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_imm_asi & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding casa_ defined at ../../../targets/sparc64/encoding.def:919:4-922:6
 */
static void casa__braddr_r_asie16e16(int line, uint8_t var_op3b, struct compound_braddr_r_asi * var_addr, uint8_t var_rs2, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_rs1;
   uint8_t var__Z40;
   
   if (((var_op3b == 60U /* CASA */)||(var_op3b == 62U /* CASXA */))) {
      var_i = 1U;
      var_op = 3U /* OP3B */;
      {
         var_rs1 =(var_addr -> m0);
      }
      var__Z40 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3b & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z40 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding impl defined at ../../../targets/sparc64/encoding.def:928:4-72
 */
static void impl_u5u19(int line, uint8_t var_op3a, uint8_t var_impl1, uint32_t var_impl2) {
   uint8_t var_op;
   
   if (((var_op3a == 54U /* IMPDEP1 */)||(var_op3a == 55U /* IMPDEP2 */))) {
      var_op = 2U /* OP3A */;
      {
         add32(line,(((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_impl1 & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|(var_impl2 & 524287U)));
      }
      return;
   }
}

/*
 * Encoding shift defined at ../../../targets/sparc64/encoding.def:934:4-936:6
 */
static void shift_e16e16e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_x;
   uint8_t var__Z43;
   
   if ((((var_op3a == 37U /* SLL */)||(var_op3a == 38U /* SRL */))||(var_op3a == 39U /* SRA */))) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var_x = 0U;
      var__Z43 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_x & 1U)<< 12U))|((uint32_t)(var__Z43 & 127U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding shiftx defined at ../../../targets/sparc64/encoding.def:937:4-939:6
 */
static void shiftx_e16e16e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_x;
   uint8_t var__Z43;
   
   if ((((var_op3a == 37U /* SLL */)||(var_op3a == 38U /* SRL */))||(var_op3a == 39U /* SRA */))) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var_x = 1U;
      var__Z43 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_x & 1U)<< 12U))|((uint32_t)(var__Z43 & 127U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding shift defined at ../../../targets/sparc64/encoding.def:946:4-66
 */
static void shift_e16u5e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_shcnt32, uint8_t var_rd) {
   uint8_t var_x;
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var__Z45;
   
   if ((((var_op3a == 37U /* SLL */)||(var_op3a == 38U /* SRL */))||(var_op3a == 39U /* SRA */))) {
      var_x = 0U;
      var_i = 1U;
      var_op = 2U /* OP3A */;
      var__Z45 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_x & 1U)<< 12U))|((uint32_t)(var__Z45 & 127U)<< 5U))|(uint32_t)(var_shcnt32 & 31U)));
      }
      return;
   }
}

/*
 * Encoding shiftx defined at ../../../targets/sparc64/encoding.def:953:4-67
 */
static void shiftx_e16u6e16(int line, uint8_t var_op3a, uint8_t var_rs1, uint8_t var_shcnt64, uint8_t var_rd) {
   uint8_t var_x;
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var__Z47;
   
   if ((((var_op3a == 37U /* SLL */)||(var_op3a == 38U /* SRL */))||(var_op3a == 39U /* SRA */))) {
      var_x = 1U;
      var_i = 1U;
      var_op = 2U /* OP3A */;
      var__Z47 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_x & 1U)<< 12U))|((uint32_t)(var__Z47 & 63U)<< 6U))|(uint32_t)(var_shcnt64 & 63U)));
      }
      return;
   }
}

/*
 * Encoding fadd defined at ../../../targets/sparc64/encoding.def:960:4-965:6
 */
static void fadd_e14e14e14(int line, uint16_t var_opf, uint8_t var_fs1, uint8_t var_fs2, uint8_t var_fd) {
   uint8_t var_op;
   uint8_t var_op3a;
   
   if (((((((var_opf == 65U /* FADDs */)||(var_opf == 66U /* FADDd */))||(var_opf == 67U /* FADDq */))||(var_opf == 69U /* FSUBs */))||(var_opf == 70U /* FSUBd */))||(var_opf == 71U /* FSUBq */))) {
      var_op = 2U /* OP3A */;
      var_op3a = 52U /* FADD */;
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_fs1 & 31U)<< 14U))|((uint32_t)(var_opf & 511U)<< 5U))|(uint32_t)(var_fs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding fto defined at ../../../targets/sparc64/encoding.def:966:4-976:6
 */
static void fto_e14e14(int line, uint16_t var_opf, uint8_t var_fs2, uint8_t var_fd) {
   uint8_t var_fs1;
   uint8_t var_op;
   uint8_t var_op3a;
   
   if (((((((((((((((((((var_opf == 129U /* FsTOx */)||(var_opf == 130U /* FdTOx */))||(var_opf == 131U /* FqTOx */))||(var_opf == 209U /* FsTOi */))||(var_opf == 210U /* FdTOi */))||(var_opf == 211U /* FqTOi */))||(var_opf == 201U /* FsTOd */))||(var_opf == 205U /* FsTOq */))||(var_opf == 198U /* FdTOs */))||(var_opf == 206U /* FdTOq */))||(var_opf == 199U /* FqTOs */))||(var_opf == 203U /* FqTOd */))||(var_opf == 132U /* FxTOs */))||(var_opf == 136U /* FxTOd */))||(var_opf == 140U /* FxTOq */))||(var_opf == 196U /* FiTOs */))||(var_opf == 200U /* FiTOd */))||(var_opf == 204U /* FiTOq */))) {
      var_fs1 = 0U /* f0 */;
      var_op = 2U /* OP3A */;
      var_op3a = 52U /* FADD */;
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_fs1 & 31U)<< 14U))|((uint32_t)(var_opf & 511U)<< 5U))|(uint32_t)(var_fs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding fmov defined at ../../../targets/sparc64/encoding.def:977:4-985:6
 */
static void fmov_e14e14(int line, uint16_t var_opf, uint8_t var_fs2, uint8_t var_fd) {
   uint8_t var_fs1;
   uint8_t var_op;
   uint8_t var_op3a;
   
   if (((((((((((((var_opf == 1U /* FMOVs */)||(var_opf == 2U /* FMOVd */))||(var_opf == 3U /* FMOVq */))||(var_opf == 5U /* FNEGs */))||(var_opf == 6U /* FNEGd */))||(var_opf == 7U /* FNEGq */))||(var_opf == 9U /* FABSs */))||(var_opf == 10U /* FABSd */))||(var_opf == 11U /* FABSq */))||(var_opf == 41U /* FSQRTs */))||(var_opf == 42U /* FSQRTd */))||(var_opf == 43U /* FSQRTq */))) {
      var_fs1 = 0U /* f0 */;
      var_op = 2U /* OP3A */;
      var_op3a = 52U /* FADD */;
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_fs1 & 31U)<< 14U))|((uint32_t)(var_opf & 511U)<< 5U))|(uint32_t)(var_fs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding fmul defined at ../../../targets/sparc64/encoding.def:986:4-992:6
 */
static void fmul_e14e14e14(int line, uint16_t var_opf, uint8_t var_fs1, uint8_t var_fs2, uint8_t var_fd) {
   uint8_t var_op;
   uint8_t var_op3a;
   
   if (((((((((var_opf == 73U /* FMULs */)||(var_opf == 74U /* FMULd */))||(var_opf == 75U /* FMULq */))||(var_opf == 105U /* FsMULd */))||(var_opf == 110U /* FdMULq */))||(var_opf == 77U /* FDIVs */))||(var_opf == 78U /* FDIVd */))||(var_opf == 79U /* FDIVq */))) {
      var_op = 2U /* OP3A */;
      var_op3a = 52U /* FADD */;
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_fs1 & 31U)<< 14U))|((uint32_t)(var_opf & 511U)<< 5U))|(uint32_t)(var_fs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding fcmp defined at ../../../targets/sparc64/encoding.def:996:4-999:6
 */
static void fcmp_e13e14e14(int line, uint16_t var_opf, uint8_t var_fccC, uint8_t var_fs1, uint8_t var_fs2) {
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var__Z50;
   
   if (true) {
      var_op = 2U /* OP3A */;
      var_op3a = 53U /* FCMP */;
      var__Z50 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var__Z50 & 7U)<< 27U))|((uint32_t)(var_fccC & 3U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_fs1 & 31U)<< 14U))|((uint32_t)(var_opf & 511U)<< 5U))|(uint32_t)(var_fs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding rdpr defined at ../../../targets/sparc64/encoding.def:1005:4-29
 */
static void rdpr_e19e16(int line, uint8_t var_priv_rs1, uint8_t var_rd) {
   uint8_t var_op3a;
   uint8_t var_op;
   uint16_t var__Z52;
   
   if (true) {
      var_op3a = 42U /* RDPR */;
      var_op = 2U /* OP3A */;
      var__Z52 = 0U;
      {
         add32(line,((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_priv_rs1 & 31U)<< 14U))|(uint32_t)(var__Z52 & 16383U)));
      }
      return;
   }
}

/*
 * Encoding wrpr defined at ../../../targets/sparc64/encoding.def:1012:4-34
 */
static void wrpr_e16e16e19(int line, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_priv_rd) {
   uint8_t var_i;
   uint8_t var_op3a;
   uint8_t var_op;
   uint8_t var__Z54;
   
   if (true) {
      var_i = 0U;
      var_op3a = 50U /* WRPR */;
      var_op = 2U /* OP3A */;
      var__Z54 = 0U;
      {
         add32(line,((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_priv_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var__Z54 & 255U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding wrpr defined at ../../../targets/sparc64/encoding.def:1018:4-37
 */
static void wrpr_e16i13e19(int line, uint8_t var_rs1, int16_t var_simm13, uint8_t var_priv_rd) {
   uint8_t var_i;
   uint8_t var_op3a;
   uint8_t var_op;
   
   if (true) {
      var_i = 0U;
      var_op3a = 50U /* WRPR */;
      var_op = 2U /* OP3A */;
      {
         add32(line,(((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_priv_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|(uint32_t)((uint16_t)var_simm13 & 8191U)));
      }
      return;
   }
}

/*
 * Encoding done defined at ../../../targets/sparc64/encoding.def:1024:4-1027:6
 */
static void done_(int line) {
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_fcn;
   uint32_t var__Z57;
   
   if (true) {
      var_op = 2U /* OP3A */;
      var_op3a = 62U /* DONERETRY */;
      var_fcn = 0U /* DONE */;
      var__Z57 = 0U;
      {
         add32(line,(((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fcn & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|(var__Z57 & 524287U)));
      }
      return;
   }
}

/*
 * Encoding retry defined at ../../../targets/sparc64/encoding.def:1028:4-1031:6
 */
static void retry_(int line) {
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_fcn;
   uint32_t var__Z57;
   
   if (true) {
      var_op = 2U /* OP3A */;
      var_op3a = 62U /* DONERETRY */;
      var_fcn = 1U /* RETRY */;
      var__Z57 = 0U;
      {
         add32(line,(((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fcn & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|(var__Z57 & 524287U)));
      }
      return;
   }
}

/*
 * Encoding saved defined at ../../../targets/sparc64/encoding.def:1037:4-38
 */
static void saved_(int line) {
   uint8_t var_op3a;
   uint8_t var_op;
   uint8_t var_srfcn;
   uint32_t var__Z59;
   
   if (true) {
      var_op3a = 49U /* SAVEDRESTORED */;
      var_op = 2U /* OP3A */;
      var_srfcn = 0U /* SAVED */;
      var__Z59 = 0U;
      {
         add32(line,(((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_srfcn & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|(var__Z59 & 524287U)));
      }
      return;
   }
}

/*
 * Encoding restored defined at ../../../targets/sparc64/encoding.def:1038:4-44
 */
static void restored_(int line) {
   uint8_t var_op3a;
   uint8_t var_op;
   uint8_t var_srfcn;
   uint32_t var__Z59;
   
   if (true) {
      var_op3a = 49U /* SAVEDRESTORED */;
      var_op = 2U /* OP3A */;
      var_srfcn = 1U /* RESTORED */;
      var__Z59 = 0U;
      {
         add32(line,(((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_srfcn & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|(var__Z59 & 524287U)));
      }
      return;
   }
}

/*
 * Encoding movcc_ defined at ../../../targets/sparc64/encoding.def:1062:4-1065:6
 */
static void movcc__e17e16e16(int line, uint8_t var_icond, uint8_t var_iccA, uint8_t var_rs2, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_cc2A;
   uint8_t var__Z61;
   
   if (true) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var_op3a = 44U /* MOVcc */;
      var_cc2A = 1U;
      var__Z61 = 0U;
      {
         add32(line,((((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_cc2A & 1U)<< 18U))|((uint32_t)(var_icond & 15U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_iccA & 3U)<< 11U))|((uint32_t)(var__Z61 & 63U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding movcc_ defined at ../../../targets/sparc64/encoding.def:1071:4-1074:6
 */
static void movcc__e13e16e16(int line, uint8_t var_fcond, uint8_t var_fccA, uint8_t var_rs2, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_cc2A;
   uint8_t var__Z63;
   
   if (true) {
      var_i = 0U;
      var_op = 2U /* OP3A */;
      var_op3a = 44U /* MOVcc */;
      var_cc2A = 0U;
      var__Z63 = 0U;
      {
         add32(line,((((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_cc2A & 1U)<< 18U))|((uint32_t)(var_fcond & 15U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_fccA & 3U)<< 11U))|((uint32_t)(var__Z63 & 63U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding movcc_ defined at ../../../targets/sparc64/encoding.def:1081:4-1084:6
 */
static void movcc__e17i11e16(int line, uint8_t var_icond, uint8_t var_iccA, int16_t var_simm11, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_cc2A;
   
   if (true) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      var_op3a = 44U /* MOVcc */;
      var_cc2A = 1U;
      {
         add32(line,(((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_cc2A & 1U)<< 18U))|((uint32_t)(var_icond & 15U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_iccA & 3U)<< 11U))|(uint32_t)((uint16_t)var_simm11 & 2047U)));
      }
      return;
   }
}

/*
 * Encoding movcc_ defined at ../../../targets/sparc64/encoding.def:1091:4-1094:6
 */
static void movcc__e13i11e16(int line, uint8_t var_fcond, uint8_t var_fccA, int16_t var_simm11, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_cc2A;
   
   if (true) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      var_op3a = 44U /* MOVcc */;
      var_cc2A = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_rd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_cc2A & 1U)<< 18U))|((uint32_t)(var_fcond & 15U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_fccA & 3U)<< 11U))|(uint32_t)((uint16_t)var_simm11 & 2047U)));
      }
      return;
   }
}

/*
 * Encoding tcc_ defined at ../../../targets/sparc64/encoding.def:1101:4-1104:6
 */
static void tcc__e17trapnum_rr(int line, uint8_t var_icondA, uint8_t var_iccA, struct compound_trapnum_rr * var_tn) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rs1;
   uint8_t var_rs2;
   uint8_t var__Z67;
   uint8_t var__Z68;
   
   if (true) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      var_op3a = 58U /* TCC */;
      {
         var_rs1 =(var_tn -> m0);
         var_rs2 =(var_tn -> m1);
      }
      var__Z67 = 0U;
      var__Z68 = 0U;
      {
         add32(line,((((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var__Z67 & 1U)<< 29U))|((uint32_t)(var_icondA & 15U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_iccA & 3U)<< 11U))|((uint32_t)(var__Z68 & 63U)<< 5U))|(uint32_t)(var_rs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding tcc_ defined at ../../../targets/sparc64/encoding.def:1109:4-1112:6
 */
static void tcc__e17trapnum_ri(int line, uint8_t var_icondA, uint8_t var_iccA, struct compound_trapnum_ri * var_tn) {
   uint8_t var_i;
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var_rs1;
   int8_t var_swtrapnum;
   uint8_t var__Z70;
   uint8_t var__Z71;
   
   if (true) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      var_op3a = 58U /* TCC */;
      {
         var_rs1 =(var_tn -> m0);
         var_swtrapnum =(var_tn -> m1);
      }
      var__Z70 = 0U;
      var__Z71 = 0U;
      {
         add32(line,((((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var__Z70 & 1U)<< 29U))|((uint32_t)(var_icondA & 15U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_iccA & 3U)<< 11U))|((uint32_t)(var__Z71 & 15U)<< 7U))|(uint32_t)((uint8_t)var_swtrapnum & 127U)));
      }
      return;
   }
}

/*
 * Encoding fmov defined at ../../../targets/sparc64/encoding.def:1118:4-1120:6
 */
static void fmov_e16e14e14(int line, uint8_t var_opf_lowA, uint8_t var_rcondB, uint8_t var_rs1, uint8_t var_fs2, uint8_t var_fd) {
   uint8_t var_op;
   uint8_t var_op3a;
   uint8_t var__Z73;
   
   if (true) {
      var_op = 2U /* OP3A */;
      var_op3a = 53U /* FCMP */;
      var__Z73 = 0U;
      {
         add32(line,(((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var_rs1 & 31U)<< 14U))|((uint32_t)(var__Z73 & 1U)<< 13U))|((uint32_t)(var_rcondB & 7U)<< 10U))|((uint32_t)(var_opf_lowA & 31U)<< 5U))|(uint32_t)(var_fs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding fmov defined at ../../../targets/sparc64/encoding.def:1132:4-48
 */
static void fmov_e17e14e14(int line, uint8_t var_opf_lowB, uint8_t var_icondB, uint8_t var_iccA, uint8_t var_fs2, uint8_t var_fd) {
   uint8_t var_i;
   uint8_t var_op3a;
   uint8_t var_op;
   uint8_t var__Z75;
   
   if (true) {
      var_i = 1U;
      var_op3a = 53U /* FCMP */;
      var_op = 2U /* OP3A */;
      var__Z75 = 0U;
      {
         add32(line,((((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var__Z75 & 1U)<< 18U))|((uint32_t)(var_icondB & 15U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_iccA & 3U)<< 11U))|((uint32_t)(var_opf_lowB & 63U)<< 5U))|(uint32_t)(var_fs2 & 31U)));
      }
      return;
   }
}

/*
 * Encoding fmov defined at ../../../targets/sparc64/encoding.def:1139:4-48
 */
static void fmov_e13e14e14(int line, uint8_t var_opf_lowB, uint8_t var_fcondB, uint8_t var_fccA, uint8_t var_fs2, uint8_t var_fd) {
   uint8_t var_i;
   uint8_t var_op3a;
   uint8_t var_op;
   uint8_t var__Z77;
   
   if (true) {
      var_i = 0U;
      var_op3a = 53U /* FCMP */;
      var_op = 2U /* OP3A */;
      var__Z77 = 0U;
      {
         add32(line,((((((((((uint32_t)(var_op & 3U)<< 30U)|((uint32_t)(var_fd & 31U)<< 25U))|((uint32_t)(var_op3a & 63U)<< 19U))|((uint32_t)(var__Z77 & 1U)<< 18U))|((uint32_t)(var_fcondB & 15U)<< 14U))|((uint32_t)(var_i & 1U)<< 13U))|((uint32_t)(var_fccA & 3U)<< 11U))|((uint32_t)(var_opf_lowB & 63U)<< 5U))|(uint32_t)(var_fs2 & 31U)));
      }
      return;
   }
}

/*
 * Macro call defined at ../../../targets/sparc64/encoding.def:406:4-80
 */
static void call_xu64u32(int line, struct expr * var_destsym, uint32_t var__) {
   uint8_t var_op;
   
   (void)var__;
   if (true) {
      var_op = 1U /* CALL */;
      call_xu64(line, var_destsym);
      return;
   }
   (void)var__;
   (void)var_destsym;
   (void)var_op;
}

/*
 * Macro sethi_ defined at ../../../targets/sparc64/encoding.def:423:4-427:6
 */
static void sethi__u32e16(int line, uint32_t var_imm, uint8_t var_rd) {
   uint8_t var_op;
   uint32_t var_imm22;
   
   if (true) {
      var_op = 0U /* OP2 */;
      var_imm22 = var_imm;
      sethi_u22e16(line, var_imm22, var_rd);
      return;
   }
   (void)var_imm;
   (void)var_imm22;
   (void)var_op;
   (void)var_rd;
}

/*
 * Macro sethi_ defined at ../../../targets/sparc64/encoding.def:428:4-433:6
 */
static void sethi__xu64e16(int line, struct expr * var_immexpr, uint8_t var_rd) {
   uint8_t var_op;
   uint64_t var_imm;
   uint32_t var_imm22;
   
   if (true) {
      var_op = 0U /* OP2 */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_IMM22, 0);
      var_imm22 =(uint32_t)var_imm;
      sethi_u22e16(line, var_imm22, var_rd);
      return;
   }
   (void)var_imm;
   (void)var_imm22;
   (void)var_immexpr;
   (void)var_op;
   (void)var_rd;
}

/*
 * Macro nop_ defined at ../../../targets/sparc64/encoding.def:434:4-50
 */
static void nop__(int line) {
   uint8_t var_op;
   
   if (true) {
      var_op = 0U /* OP2 */;
      sethi_u22e16(line, 0U, 0U /* r0 */);
      return;
   }
   (void)var_op;
}

/*
 * Macro arith defined at ../../../targets/sparc64/encoding.def:566:4-574:6
 */
static void arith_e16xu64e16(int line, uint8_t var_op3a, uint8_t var_rs1, struct expr * var_immexpr, uint8_t var_rd) {
   uint8_t var_i;
   uint8_t var_op;
   uint64_t var_imm;
   int16_t var_imm13;
   
   if (((((((((((((((((((((((((((var_op3a == 0U /* ADD */)||(var_op3a == 1U /* AND */))||(var_op3a == 2U /* OR */))||(var_op3a == 3U /* XOR */))||(var_op3a == 4U /* SUB */))||(var_op3a == 5U /* ANDN */))||(var_op3a == 6U /* ORN */))||(var_op3a == 7U /* XNOR */))||(var_op3a == 8U /* ADDC */))||(var_op3a == 12U /* SUBC */))||(var_op3a == 16U /* ADDcc */))||(var_op3a == 17U /* ANDcc */))||(var_op3a == 18U /* ORcc */))||(var_op3a == 19U /* XORcc */))||(var_op3a == 20U /* SUBcc */))||(var_op3a == 21U /* ANDNcc */))||(var_op3a == 22U /* ORNcc */))||(var_op3a == 23U /* XNORcc */))||(var_op3a == 24U /* ADDCcc */))||(var_op3a == 28U /* SUBCcc */))||(var_op3a == 32U /* TADDcc */))||(var_op3a == 33U /* TSUBcc */))||(var_op3a == 34U /* TADDccTV */))||(var_op3a == 35U /* TSUBccTV */))||(var_op3a == 60U /* SAVE */))||(var_op3a == 61U /* RESTORE */))) {
      var_i = 1U;
      var_op = 2U /* OP3A */;
      var_imm = process_expr(line, var_immexpr, RELOC_FIELD_SIMM13, 0);
      var_imm13 =(int16_t)(int64_t)var_imm;
      arith_e16i13e16(line, var_op3a, var_rs1, var_imm13, var_rd);
      return;
   }
   (void)var_i;
   (void)var_imm;
   (void)var_imm13;
   (void)var_immexpr;
   (void)var_op;
   (void)var_op3a;
   (void)var_rd;
   (void)var_rs1;
}

/*
 * Macro subcc_ defined at ../../../targets/sparc64/encoding.def:1149:4-85
 */
static void subcc__e16e16e16(int line, uint8_t var_rs1, uint8_t var_rs2, uint8_t var_dest) {
   
   if (true) {
      arith_e16e16e16(line, 20U /* SUBcc */, var_rs1, var_rs2, var_dest);
      return;
   }
   (void)var_dest;
   (void)var_rs1;
   (void)var_rs2;
}

/*
 * Macro subcc_ defined at ../../../targets/sparc64/encoding.def:1150:4-102
 */
static void subcc__e16i13e16(int line, uint8_t var_rs1, int16_t var_simm13, uint8_t var_dest) {
   
   if (true) {
      arith_e16i13e16(line, 20U /* SUBcc */, var_rs1, var_simm13, var_dest);
      return;
   }
   (void)var_dest;
   (void)var_rs1;
   (void)var_simm13;
}

/*
 * Macro cmp_ defined at ../../../targets/sparc64/encoding.def:1152:4-55
 */
static void cmp__e16e16(int line, uint8_t var_rs1, uint8_t var_rs2) {
   
   if (true) {
      subcc__e16e16e16(line, var_rs1, var_rs2, 0U /* r0 */);
      return;
   }
   (void)var_rs1;
   (void)var_rs2;
}

/*
 * Macro cmp_ defined at ../../../targets/sparc64/encoding.def:1153:4-66
 */
static void cmp__e16i13(int line, uint8_t var_rs1, int16_t var_imm) {
   
   if (true) {
      subcc__e16i13e16(line, var_rs1, var_imm, 0U /* r0 */);
      return;
   }
   (void)var_imm;
   (void)var_rs1;
}

/*
 * Macro jmp_ defined at ../../../targets/sparc64/encoding.def:1156:4-56
 */
static void jmp__addr_rr(int line, struct compound_addr_rr * var_addr) {
   
   if (true) {
      jmpl_addr_rre16(line, var_addr, 0U /* r0 */);
      return;
   }
   (void)var_addr;
}

/*
 * Macro jmp_ defined at ../../../targets/sparc64/encoding.def:1157:4-56
 */
static void jmp__addr_ri(int line, struct compound_addr_ri * var_addr) {
   
   if (true) {
      jmpl_addr_rie16(line, var_addr, 0U /* r0 */);
      return;
   }
   (void)var_addr;
}

/*
 * Macro call_ defined at ../../../targets/sparc64/encoding.def:1161:4-58
 */
static void call__addr_rr(int line, struct compound_addr_rr * var_addr) {
   
   if (true) {
      jmpl_addr_rre16(line, var_addr, 15U /* r15 */);
      return;
   }
   (void)var_addr;
}

/*
 * Macro call_ defined at ../../../targets/sparc64/encoding.def:1162:4-58
 */
static void call__addr_ri(int line, struct compound_addr_ri * var_addr) {
   
   if (true) {
      jmpl_addr_rie16(line, var_addr, 15U /* r15 */);
      return;
   }
   (void)var_addr;
}

/*
 * Macro call_ defined at ../../../targets/sparc64/encoding.def:1164:4-61
 */
static void call__addr_rru32(int line, struct compound_addr_rr * var_addr, uint32_t var__) {
   
   (void)var__;
   if (true) {
      jmpl_addr_rre16(line, var_addr, 15U /* r15 */);
      return;
   }
   (void)var__;
   (void)var_addr;
}

/*
 * Macro call_ defined at ../../../targets/sparc64/encoding.def:1165:4-61
 */
static void call__addr_riu32(int line, struct compound_addr_ri * var_addr, uint32_t var__) {
   
   (void)var__;
   if (true) {
      jmpl_addr_rie16(line, var_addr, 15U /* r15 */);
      return;
   }
   (void)var__;
   (void)var_addr;
}

/*
 * Macro ret_ defined at ../../../targets/sparc64/encoding.def:1169:4-51
 */
static void ret__(int line) {
   struct compound_addr_ri pack_0;
   
   if (true) {
      {
         pack_0.m0 = 31U /* r31 */;
         pack_0.m1 = 8;
         jmpl_addr_rie16(line, &pack_0, 0U /* r0 */);
      }
      return;
   }
}

/*
 * Macro retl_ defined at ../../../targets/sparc64/encoding.def:1170:4-52
 */
static void retl__(int line) {
   struct compound_addr_ri pack_0;
   
   if (true) {
      {
         pack_0.m0 = 15U /* r15 */;
         pack_0.m1 = 8;
         jmpl_addr_rie16(line, &pack_0, 0U /* r0 */);
      }
      return;
   }
}

/*
 * Macro save defined at ../../../targets/sparc64/opmatch.def:47:1-34
 */
static void save_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 60U /* SAVE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro save_ defined at ../../../targets/sparc64/encoding.def:1172:4-43
 */
static void save__(int line) {
   
   if (true) {
      save_e16e16e16(line, 0U /* r0 */, 0U /* r0 */, 0U /* r0 */);
      return;
   }
}

/*
 * Macro restore defined at ../../../targets/sparc64/opmatch.def:49:1-40
 */
static void restore_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 61U /* RESTORE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro restore_ defined at ../../../targets/sparc64/encoding.def:1173:4-49
 */
static void restore__(int line) {
   
   if (true) {
      restore_e16e16e16(line, 0U /* r0 */, 0U /* r0 */, 0U /* r0 */);
      return;
   }
}

/*
 * Macro iprefetch_ defined at ../../../targets/sparc64/encoding.def:1176:4-65
 */
static void iprefetch__xu64(int line, struct expr * var_sym) {
   
   if (true) {
      bpcc_e17xu64(line, 0U /* BN */, 1U /* ANNUL */, 1U /* PT */, 2U /* XCC */, var_sym);
      return;
   }
   (void)var_sym;
}

/*
 * Macro orcc defined at ../../../targets/sparc64/opmatch.def:31:1-34
 */
static void orcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 18U /* ORcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro tst_ defined at ../../../targets/sparc64/encoding.def:1178:4-47
 */
static void tst__e16(int line, uint8_t var_rs2) {
   
   if (true) {
      orcc_e16e16e16(line, 0U /* r0 */, var_rs2, 0U /* r0 */);
      return;
   }
   (void)var_rs2;
}

/*
 * Macro or defined at ../../../targets/sparc64/opmatch.def:29:1-33
 */
static void or_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 2U /* OR */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro setuw_ defined at ../../../targets/sparc64/encoding.def:1180:4-1196:6
 */
static void setuw__u32e16(int line, uint32_t var_num, uint8_t var_rd) {
   uint32_t var_hival;
   int16_t var_loval;
   
   if (true) {
      if (((var_num & 1023U)== 0U)) {
         var_hival =(var_num >> 10U);
         sethi_u22e16(line, var_hival, var_rd);
      }
      else{
         if ((var_num < 4096U)) {
            var_loval =(int16_t)(uint16_t)(var_num & 4095U);
            or_e16i13e16(line, 0U /* r0 */, var_loval, var_rd);
         }
         else{
            var_hival =(var_num >> 10U);
            var_loval =(int16_t)(uint16_t)(var_num & 1023U);
            sethi_u22e16(line, var_hival, var_rd);
            or_e16i13e16(line, var_rd, var_loval, var_rd);
         }
      }
      return;
   }
   (void)var_hival;
   (void)var_loval;
   (void)var_num;
   (void)var_rd;
}

/*
 * Macro set_ defined at ../../../targets/sparc64/encoding.def:1197:4-49
 */
static void set__u32e16(int line, uint32_t var_val, uint8_t var_rd) {
   
   if (true) {
      setuw__u32e16(line, var_val, var_rd);
      return;
   }
   (void)var_rd;
   (void)var_val;
}

/*
 * Macro sra defined at ../../../targets/sparc64/opmatch.def:74:1-32
 */
static void sra_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shift_e16e16e16(line, 39U /* SRA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro setsw_ defined at ../../../targets/sparc64/encoding.def:1198:4-1226:6
 */
static void setsw__i32e16(int line, int32_t var_num, uint8_t var_rd) {
   uint32_t var_hival;
   int16_t var_loval;
   
   if (true) {
      if ((!(var_num < 0)&&((var_num & 1023)== 0))) {
         var_hival =(uint32_t)(var_num >> 10U);
         sethi_u22e16(line, var_hival, var_rd);
      }
      else{
         if ((!(var_num < -4096)&&(var_num < 4096))) {
            var_loval =(int16_t)(var_num & 8191);
            or_e16i13e16(line, 0U /* r0 */, var_loval, var_rd);
         }
         else{
            if (((var_num < 0)&&((var_num & 1023)== 0))) {
               var_hival =(uint32_t)(var_num >> 10U);
               sethi_u22e16(line, var_hival, var_rd);
               sra_e16e16e16(line, var_rd, 0U /* r0 */, var_rd);
            }
            else{
               if (!(var_num < 0)) {
                  var_hival =(uint32_t)(var_num >> 10U);
                  var_loval =(int16_t)(var_num & 1023);
                  sethi_u22e16(line, var_hival, var_rd);
                  or_e16i13e16(line, var_rd, var_loval, var_rd);
               }
               else{
                  var_hival =(uint32_t)(var_num >> 10U);
                  var_loval =(int16_t)(var_num & 1023);
                  sethi_u22e16(line, var_hival, var_rd);
                  or_e16i13e16(line, var_rd, var_loval, var_rd);
                  sra_e16e16e16(line, var_rd, 0U /* r0 */, var_rd);
               }
            }
         }
      }
      return;
   }
   (void)var_hival;
   (void)var_loval;
   (void)var_num;
   (void)var_rd;
}

/*
 * Macro setuw defined at ../../../targets/sparc64/opmatch.def:1039:1-28
 */
static void setuw_u32e16(int line, uint32_t var__op0, uint8_t var__op1) {
   
   if (true) {
      setuw__u32e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sllx defined at ../../../targets/sparc64/opmatch.def:77:1-36
 */
static void sllx_e16u6e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shiftx_e16u6e16(line, 37U /* SLL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sub defined at ../../../targets/sparc64/opmatch.def:13:1-35
 */
static void sub_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 4U /* SUB */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro or defined at ../../../targets/sparc64/opmatch.def:28:1-30
 */
static void or_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 2U /* OR */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro setx_ defined at ../../../targets/sparc64/encoding.def:1227:4-1269:6
 */
static void setx__i64e16e16(int line, int64_t var_val, uint8_t var_tmp, uint8_t var_rd) {
   uint32_t var_val32;
   int32_t var_sval32;
   uint64_t var_uval;
   uint32_t var_upper;
   uint32_t var_lower;
   uint32_t var_upper1;
   uint32_t var_uhival;
   int16_t var_uloval;
   uint32_t var_lhival;
   int16_t var_lloval;
   
   if (true) {
      if (!(4294967295UL <(uint64_t)var_val)) {
         var_val32 =(uint32_t)(uint64_t)var_val;
         setuw_u32e16(line, var_val32, var_rd);
      }
      else{
         if ((!(2147483647L < var_val)&& !(var_val <(-2147483647L - 1L)))) {
            var_sval32 =(int32_t)var_val;
            setsw__i32e16(line, var_sval32, var_rd);
         }
         else{
            var_uval =(uint64_t)var_val;
            var_upper =(uint32_t)(var_uval >> 32U);
            var_lower =(uint32_t)(var_uval & 4294967295ULL);
            if ((var_lower == 0U)) {
               setuw_u32e16(line, var_upper, var_rd);
               sllx_e16u6e16(line, var_rd, 32U, var_rd);
            }
            else{
               if ((var_lower == 4294967295U)) {
                  var_upper1 =(var_upper + 1U);
                  setuw_u32e16(line, var_upper1, var_rd);
                  sub_e16i13e16(line, var_rd, 1, var_rd);
               }
               else{
                  var_uhival =(var_upper >> 10U);
                  var_uloval =(int16_t)(uint16_t)(var_upper & 1023U);
                  var_lhival =(var_lower >> 10U);
                  var_lloval =(int16_t)(uint16_t)(var_lower & 1023U);
                  sethi_u22e16(line, var_uhival, var_tmp);
                  sethi_u22e16(line, var_lhival, var_rd);
                  if (!(var_uloval == 0)) {
                     or_e16i13e16(line, var_tmp, var_uloval, var_tmp);
                  }
                  if (!(var_lloval == 0)) {
                     or_e16i13e16(line, var_rd, var_lloval, var_rd);
                  }
                  or_e16e16e16(line, var_rd, var_tmp, var_rd);
               }
            }
         }
      }
      return;
   }
   (void)var_lhival;
   (void)var_lloval;
   (void)var_lower;
   (void)var_rd;
   (void)var_sval32;
   (void)var_tmp;
   (void)var_uhival;
   (void)var_uloval;
   (void)var_upper;
   (void)var_upper1;
   (void)var_uval;
   (void)var_val;
   (void)var_val32;
}

/*
 * Macro signx_ defined at ../../../targets/sparc64/encoding.def:1271:4-52
 */
static void signx__e16e16(int line, uint8_t var_rs1, uint8_t var_rd) {
   
   if (true) {
      sra_e16e16e16(line, var_rs1, 0U /* r0 */, var_rd);
      return;
   }
   (void)var_rd;
   (void)var_rs1;
}

/*
 * Macro signx_ defined at ../../../targets/sparc64/encoding.def:1272:4-46
 */
static void signx__e16(int line, uint8_t var_rd) {
   
   if (true) {
      sra_e16e16e16(line, var_rd, 0U /* r0 */, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro xnor defined at ../../../targets/sparc64/opmatch.def:41:1-34
 */
static void xnor_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 7U /* XNOR */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro not_ defined at ../../../targets/sparc64/encoding.def:1273:4-51
 */
static void not__e16e16(int line, uint8_t var_rs1, uint8_t var_rd) {
   
   if (true) {
      xnor_e16e16e16(line, var_rs1, 0U /* r0 */, var_rd);
      return;
   }
   (void)var_rd;
   (void)var_rs1;
}

/*
 * Macro not_ defined at ../../../targets/sparc64/encoding.def:1274:4-45
 */
static void not__e16(int line, uint8_t var_rd) {
   
   if (true) {
      xnor_e16e16e16(line, var_rd, 0U /* r0 */, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro sub defined at ../../../targets/sparc64/opmatch.def:12:1-32
 */
static void sub_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 4U /* SUB */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro neg_ defined at ../../../targets/sparc64/encoding.def:1275:4-50
 */
static void neg__e16e16(int line, uint8_t var_rs1, uint8_t var_rd) {
   
   if (true) {
      sub_e16e16e16(line, 0U /* r0 */, var_rs1, var_rd);
      return;
   }
   (void)var_rd;
   (void)var_rs1;
}

/*
 * Macro neg_ defined at ../../../targets/sparc64/encoding.def:1276:4-45
 */
static void neg__e16(int line, uint8_t var_rd) {
   
   if (true) {
      xnor_e16e16e16(line, 0U /* r0 */, var_rd, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro casa defined at ../../../targets/sparc64/opmatch.def:772:1-45
 */
static void casa_braddr_r_immasie16e16(int line, struct compound_braddr_r_immasi * var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      casa__braddr_r_immasie16e16(line, 60U /* CASA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro cas_ defined at ../../../targets/sparc64/encoding.def:1278:4-1281:6
 */
static void cas__e16e16e16(int line, uint8_t var_addr, uint8_t var_rs2, uint8_t var_rd) {
   struct compound_braddr_r_immasi * var_addr2;
   struct compound_braddr_r_immasi pack_0;
   
   if (true) {
      {
         pack_0.m0 = var_addr;
         pack_0.m1 = 128U;
         var_addr2 = &pack_0;
      }
      casa_braddr_r_immasie16e16(line, var_addr2, var_rs2, var_rd);
      return;
   }
   (void)var_addr;
   (void)var_addr2;
   (void)var_rd;
   (void)var_rs2;
}

/*
 * Macro casl_ defined at ../../../targets/sparc64/encoding.def:1282:4-1285:6
 */
static void casl__e16e16e16(int line, uint8_t var_addr, uint8_t var_rs2, uint8_t var_rd) {
   struct compound_braddr_r_immasi * var_addr2;
   struct compound_braddr_r_immasi pack_0;
   
   if (true) {
      {
         pack_0.m0 = var_addr;
         pack_0.m1 = 136U;
         var_addr2 = &pack_0;
      }
      casa_braddr_r_immasie16e16(line, var_addr2, var_rs2, var_rd);
      return;
   }
   (void)var_addr;
   (void)var_addr2;
   (void)var_rd;
   (void)var_rs2;
}

/*
 * Macro casxa defined at ../../../targets/sparc64/opmatch.def:774:1-47
 */
static void casxa_braddr_r_immasie16e16(int line, struct compound_braddr_r_immasi * var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      casa__braddr_r_immasie16e16(line, 62U /* CASXA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro casx_ defined at ../../../targets/sparc64/encoding.def:1286:4-1289:6
 */
static void casx__e16e16e16(int line, uint8_t var_addr, uint8_t var_rs2, uint8_t var_rd) {
   struct compound_braddr_r_immasi * var_addr2;
   struct compound_braddr_r_immasi pack_0;
   
   if (true) {
      {
         pack_0.m0 = var_addr;
         pack_0.m1 = 128U;
         var_addr2 = &pack_0;
      }
      casxa_braddr_r_immasie16e16(line, var_addr2, var_rs2, var_rd);
      return;
   }
   (void)var_addr;
   (void)var_addr2;
   (void)var_rd;
   (void)var_rs2;
}

/*
 * Macro casxl_ defined at ../../../targets/sparc64/encoding.def:1290:4-1293:6
 */
static void casxl__e16e16e16(int line, uint8_t var_addr, uint8_t var_rs2, uint8_t var_rd) {
   struct compound_braddr_r_immasi * var_addr2;
   struct compound_braddr_r_immasi pack_0;
   
   if (true) {
      {
         pack_0.m0 = var_addr;
         pack_0.m1 = 136U;
         var_addr2 = &pack_0;
      }
      casxa_braddr_r_immasie16e16(line, var_addr2, var_rs2, var_rd);
      return;
   }
   (void)var_addr;
   (void)var_addr2;
   (void)var_rd;
   (void)var_rs2;
}

/*
 * Macro add defined at ../../../targets/sparc64/opmatch.def:5:1-35
 */
static void add_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 0U /* ADD */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro inc_ defined at ../../../targets/sparc64/encoding.def:1295:4-54
 */
static void inc__e16(int line, uint8_t var_rd) {
   
   if (true) {
      add_e16i13e16(line, var_rd, 1, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro inc_ defined at ../../../targets/sparc64/encoding.def:1296:4-57
 */
static void inc__i13e16(int line, int16_t var_n, uint8_t var_rd) {
   
   if (true) {
      add_e16i13e16(line, var_rd, var_n, var_rd);
      return;
   }
   (void)var_n;
   (void)var_rd;
}

/*
 * Macro addcc defined at ../../../targets/sparc64/opmatch.def:7:1-39
 */
static void addcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 16U /* ADDcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro inccc_ defined at ../../../targets/sparc64/encoding.def:1297:4-58
 */
static void inccc__e16(int line, uint8_t var_rd) {
   
   if (true) {
      addcc_e16i13e16(line, var_rd, 1, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro inccc_ defined at ../../../targets/sparc64/encoding.def:1298:4-61
 */
static void inccc__i13e16(int line, int16_t var_n, uint8_t var_rd) {
   
   if (true) {
      addcc_e16i13e16(line, var_rd, var_n, var_rd);
      return;
   }
   (void)var_n;
   (void)var_rd;
}

/*
 * Macro dec_ defined at ../../../targets/sparc64/encoding.def:1299:4-54
 */
static void dec__e16(int line, uint8_t var_rd) {
   
   if (true) {
      sub_e16i13e16(line, var_rd, 1, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro dec_ defined at ../../../targets/sparc64/encoding.def:1300:4-57
 */
static void dec__i13e16(int line, int16_t var_n, uint8_t var_rd) {
   
   if (true) {
      sub_e16i13e16(line, var_rd, var_n, var_rd);
      return;
   }
   (void)var_n;
   (void)var_rd;
}

/*
 * Macro deccc_ defined at ../../../targets/sparc64/encoding.def:1301:4-59
 */
static void deccc__e16(int line, uint8_t var_rd) {
   
   if (true) {
      subcc__e16i13e16(line, var_rd, 1, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro deccc_ defined at ../../../targets/sparc64/encoding.def:1302:4-62
 */
static void deccc__i13e16(int line, int16_t var_n, uint8_t var_rd) {
   
   if (true) {
      subcc__e16i13e16(line, var_rd, var_n, var_rd);
      return;
   }
   (void)var_n;
   (void)var_rd;
}

/*
 * Macro andcc defined at ../../../targets/sparc64/opmatch.def:22:1-36
 */
static void andcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 17U /* ANDcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro btst_ defined at ../../../targets/sparc64/encoding.def:1304:4-55
 */
static void btst__e16e16(int line, uint8_t var_rs2, uint8_t var_rs1) {
   
   if (true) {
      andcc_e16e16e16(line, var_rs1, var_rs2, 0U /* r0 */);
      return;
   }
   (void)var_rs1;
   (void)var_rs2;
}

/*
 * Macro andcc defined at ../../../targets/sparc64/opmatch.def:23:1-39
 */
static void andcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 17U /* ANDcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro btst_ defined at ../../../targets/sparc64/encoding.def:1305:4-66
 */
static void btst__i13e16(int line, int16_t var_imm, uint8_t var_rs1) {
   
   if (true) {
      andcc_e16i13e16(line, var_rs1, var_imm, 0U /* r0 */);
      return;
   }
   (void)var_imm;
   (void)var_rs1;
}

/*
 * Macro bset_ defined at ../../../targets/sparc64/encoding.def:1306:4-50
 */
static void bset__e16e16(int line, uint8_t var_rs2, uint8_t var_rd) {
   
   if (true) {
      or_e16e16e16(line, var_rd, var_rs2, var_rd);
      return;
   }
   (void)var_rd;
   (void)var_rs2;
}

/*
 * Macro bset_ defined at ../../../targets/sparc64/encoding.def:1307:4-61
 */
static void bset__i13e16(int line, int16_t var_imm, uint8_t var_rd) {
   
   if (true) {
      or_e16i13e16(line, var_rd, var_imm, var_rd);
      return;
   }
   (void)var_imm;
   (void)var_rd;
}

/*
 * Macro andn defined at ../../../targets/sparc64/opmatch.def:24:1-34
 */
static void andn_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 5U /* ANDN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro bclr_ defined at ../../../targets/sparc64/encoding.def:1308:4-52
 */
static void bclr__e16e16(int line, uint8_t var_rs2, uint8_t var_rd) {
   
   if (true) {
      andn_e16e16e16(line, var_rd, var_rs2, var_rd);
      return;
   }
   (void)var_rd;
   (void)var_rs2;
}

/*
 * Macro andn defined at ../../../targets/sparc64/opmatch.def:25:1-37
 */
static void andn_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 5U /* ANDN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro bclr_ defined at ../../../targets/sparc64/encoding.def:1309:4-63
 */
static void bclr__i13e16(int line, int16_t var_imm, uint8_t var_rd) {
   
   if (true) {
      andn_e16i13e16(line, var_rd, var_imm, var_rd);
      return;
   }
   (void)var_imm;
   (void)var_rd;
}

/*
 * Macro xor defined at ../../../targets/sparc64/opmatch.def:37:1-32
 */
static void xor_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 3U /* XOR */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro btog_ defined at ../../../targets/sparc64/encoding.def:1310:4-51
 */
static void btog__e16e16(int line, uint8_t var_rs2, uint8_t var_rd) {
   
   if (true) {
      xor_e16e16e16(line, var_rd, var_rs2, var_rd);
      return;
   }
   (void)var_rd;
   (void)var_rs2;
}

/*
 * Macro xor defined at ../../../targets/sparc64/opmatch.def:38:1-35
 */
static void xor_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 3U /* XOR */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro btog_ defined at ../../../targets/sparc64/encoding.def:1311:4-62
 */
static void btog__i13e16(int line, int16_t var_imm, uint8_t var_rd) {
   
   if (true) {
      xor_e16i13e16(line, var_rd, var_imm, var_rd);
      return;
   }
   (void)var_imm;
   (void)var_rd;
}

/*
 * Macro clr__ defined at ../../../targets/sparc64/encoding.def:1313:4-44
 */
static void clr___e16(int line, uint8_t var_rd) {
   
   if (true) {
      or_e16e16e16(line, 0U /* r0 */, 0U /* r0 */, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro clr_ defined at ../../../targets/sparc64/encoding.def:1318:4-71
 */
static void clr__braddr_rr(int line, uint8_t var_op3b, struct compound_braddr_rr * var_addr) {
   
   if (true) {
      store_e16braddr_rr(line, var_op3b, 0U /* r0 */, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_op3b;
}

/*
 * Macro clr_ defined at ../../../targets/sparc64/encoding.def:1319:4-71
 */
static void clr__braddr_ri(int line, uint8_t var_op3b, struct compound_braddr_ri * var_addr) {
   
   if (true) {
      store_e16braddr_ri(line, var_op3b, 0U /* r0 */, var_addr);
      return;
   }
   (void)var_addr;
   (void)var_op3b;
}

/*
 * Macro srl defined at ../../../targets/sparc64/opmatch.def:72:1-32
 */
static void srl_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shift_e16e16e16(line, 38U /* SRL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro clruw_ defined at ../../../targets/sparc64/encoding.def:1321:4-52
 */
static void clruw__e16e16(int line, uint8_t var_rs1, uint8_t var_rd) {
   
   if (true) {
      srl_e16e16e16(line, var_rs1, 0U /* r0 */, var_rd);
      return;
   }
   (void)var_rd;
   (void)var_rs1;
}

/*
 * Macro clruw_ defined at ../../../targets/sparc64/encoding.def:1322:4-46
 */
static void clruw__e16(int line, uint8_t var_rd) {
   
   if (true) {
      srl_e16e16e16(line, var_rd, 0U /* r0 */, var_rd);
      return;
   }
   (void)var_rd;
}

/*
 * Macro mov_ defined at ../../../targets/sparc64/encoding.def:1324:4-49
 */
static void mov__e16e16(int line, uint8_t var_rs2, uint8_t var_rd) {
   
   if (true) {
      or_e16e16e16(line, 0U /* r0 */, var_rs2, var_rd);
      return;
   }
   (void)var_rd;
   (void)var_rs2;
}

/*
 * Macro mov_ defined at ../../../targets/sparc64/encoding.def:1325:4-60
 */
static void mov__i13e16(int line, int16_t var_imm, uint8_t var_rd) {
   
   if (true) {
      or_e16i13e16(line, 0U /* r0 */, var_imm, var_rd);
      return;
   }
   (void)var_imm;
   (void)var_rd;
}

/*
 * Macro rd defined at ../../../targets/sparc64/opmatch.def:1004:1-22
 */
static void rd_e11e16(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      rdasr_e11e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro mov_ defined at ../../../targets/sparc64/encoding.def:1326:4-52
 */
static void mov__e11e16(int line, uint8_t var_asr, uint8_t var_rd) {
   
   if (true) {
      rd_e11e16(line, var_asr, var_rd);
      return;
   }
   (void)var_asr;
   (void)var_rd;
}

/*
 * Macro mov_ defined at ../../../targets/sparc64/encoding.def:1327:4-61
 */
static void mov__e16e11(int line, uint8_t var_rs1, uint8_t var_asr) {
   
   if (true) {
      wrasr_e16e16e11(line, var_rs1, 0U /* r0 */, var_asr);
      return;
   }
   (void)var_asr;
   (void)var_rs1;
}

/*
 * Macro sethi defined at ../../../targets/sparc64/opmatch.def:1:1-28
 */
static void sethi_u32e16(int line, uint32_t var__op0, uint8_t var__op1) {
   
   if (true) {
      sethi__u32e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sethi defined at ../../../targets/sparc64/opmatch.def:2:1-27
 */
static void sethi_xu64e16(int line, struct expr * var__op0, uint8_t var__op1) {
   
   if (true) {
      sethi__xu64e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro add defined at ../../../targets/sparc64/opmatch.def:4:1-32
 */
static void add_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 0U /* ADD */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro addcc defined at ../../../targets/sparc64/opmatch.def:6:1-36
 */
static void addcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 16U /* ADDcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro addc defined at ../../../targets/sparc64/opmatch.def:8:1-34
 */
static void addc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 8U /* ADDC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro addc defined at ../../../targets/sparc64/opmatch.def:9:1-37
 */
static void addc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 8U /* ADDC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro addccc defined at ../../../targets/sparc64/opmatch.def:10:1-38
 */
static void addccc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 24U /* ADDCcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro addccc defined at ../../../targets/sparc64/opmatch.def:11:1-41
 */
static void addccc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 24U /* ADDCcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro subcc defined at ../../../targets/sparc64/opmatch.def:14:1-36
 */
static void subcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 20U /* SUBcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro subcc defined at ../../../targets/sparc64/opmatch.def:15:1-39
 */
static void subcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 20U /* SUBcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro subc defined at ../../../targets/sparc64/opmatch.def:16:1-34
 */
static void subc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 12U /* SUBC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro subc defined at ../../../targets/sparc64/opmatch.def:17:1-37
 */
static void subc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 12U /* SUBC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro subccc defined at ../../../targets/sparc64/opmatch.def:18:1-38
 */
static void subccc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 28U /* SUBCcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro subccc defined at ../../../targets/sparc64/opmatch.def:19:1-41
 */
static void subccc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 28U /* SUBCcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro and defined at ../../../targets/sparc64/opmatch.def:20:1-32
 */
static void and_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 1U /* AND */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro and defined at ../../../targets/sparc64/opmatch.def:21:1-35
 */
static void and_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 1U /* AND */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro andncc defined at ../../../targets/sparc64/opmatch.def:26:1-38
 */
static void andncc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 21U /* ANDNcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro andncc defined at ../../../targets/sparc64/opmatch.def:27:1-41
 */
static void andncc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 21U /* ANDNcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro or defined at ../../../targets/sparc64/opmatch.def:30:1-31
 */
static void or_e16xu64e16(int line, uint8_t var__op0, struct expr * var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16xu64e16(line, 2U /* OR */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro orcc defined at ../../../targets/sparc64/opmatch.def:32:1-37
 */
static void orcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 18U /* ORcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro orn defined at ../../../targets/sparc64/opmatch.def:33:1-32
 */
static void orn_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 6U /* ORN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro orn defined at ../../../targets/sparc64/opmatch.def:34:1-35
 */
static void orn_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 6U /* ORN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro orncc defined at ../../../targets/sparc64/opmatch.def:35:1-36
 */
static void orncc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 22U /* ORNcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro orncc defined at ../../../targets/sparc64/opmatch.def:36:1-39
 */
static void orncc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 22U /* ORNcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro xorcc defined at ../../../targets/sparc64/opmatch.def:39:1-36
 */
static void xorcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 19U /* XORcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro xorcc defined at ../../../targets/sparc64/opmatch.def:40:1-39
 */
static void xorcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 19U /* XORcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro xnor defined at ../../../targets/sparc64/opmatch.def:42:1-37
 */
static void xnor_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 7U /* XNOR */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro xnorcc defined at ../../../targets/sparc64/opmatch.def:43:1-38
 */
static void xnorcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 23U /* XNORcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro xnorcc defined at ../../../targets/sparc64/opmatch.def:44:1-41
 */
static void xnorcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 23U /* XNORcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro save defined at ../../../targets/sparc64/opmatch.def:48:1-37
 */
static void save_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 60U /* SAVE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro restore defined at ../../../targets/sparc64/opmatch.def:50:1-42
 */
static void restore_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 61U /* RESTORE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro taddcc defined at ../../../targets/sparc64/opmatch.def:51:1-38
 */
static void taddcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 32U /* TADDcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro taddcc defined at ../../../targets/sparc64/opmatch.def:52:1-41
 */
static void taddcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 32U /* TADDcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro taddcctv defined at ../../../targets/sparc64/opmatch.def:53:1-42
 */
static void taddcctv_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 34U /* TADDccTV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro taddcctv defined at ../../../targets/sparc64/opmatch.def:54:1-44
 */
static void taddcctv_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 34U /* TADDccTV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro tsubcc defined at ../../../targets/sparc64/opmatch.def:55:1-38
 */
static void tsubcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 33U /* TSUBcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro tsubcc defined at ../../../targets/sparc64/opmatch.def:56:1-41
 */
static void tsubcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 33U /* TSUBcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro tsubcctv defined at ../../../targets/sparc64/opmatch.def:57:1-42
 */
static void tsubcctv_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 35U /* TSUBccTV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro tsubcctv defined at ../../../targets/sparc64/opmatch.def:58:1-44
 */
static void tsubcctv_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 35U /* TSUBccTV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro addx defined at ../../../targets/sparc64/opmatch.def:61:1-34
 */
static void addx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 8U /* ADDC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro addx defined at ../../../targets/sparc64/opmatch.def:62:1-37
 */
static void addx_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 8U /* ADDC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro addxcc defined at ../../../targets/sparc64/opmatch.def:63:1-38
 */
static void addxcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 24U /* ADDCcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro addxcc defined at ../../../targets/sparc64/opmatch.def:64:1-41
 */
static void addxcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 24U /* ADDCcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro subx defined at ../../../targets/sparc64/opmatch.def:65:1-34
 */
static void subx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 12U /* SUBC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro subx defined at ../../../targets/sparc64/opmatch.def:66:1-37
 */
static void subx_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 12U /* SUBC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro subxcc defined at ../../../targets/sparc64/opmatch.def:67:1-38
 */
static void subxcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16e16e16(line, 28U /* SUBCcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro subxcc defined at ../../../targets/sparc64/opmatch.def:68:1-41
 */
static void subxcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      arith_e16i13e16(line, 28U /* SUBCcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sll defined at ../../../targets/sparc64/opmatch.def:70:1-32
 */
static void sll_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shift_e16e16e16(line, 37U /* SLL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sll defined at ../../../targets/sparc64/opmatch.def:71:1-34
 */
static void sll_e16u5e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shift_e16u5e16(line, 37U /* SLL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro srl defined at ../../../targets/sparc64/opmatch.def:73:1-34
 */
static void srl_e16u5e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shift_e16u5e16(line, 38U /* SRL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sra defined at ../../../targets/sparc64/opmatch.def:75:1-34
 */
static void sra_e16u5e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shift_e16u5e16(line, 39U /* SRA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sllx defined at ../../../targets/sparc64/opmatch.def:76:1-34
 */
static void sllx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shiftx_e16e16e16(line, 37U /* SLL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro srlx defined at ../../../targets/sparc64/opmatch.def:78:1-34
 */
static void srlx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shiftx_e16e16e16(line, 38U /* SRL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro srlx defined at ../../../targets/sparc64/opmatch.def:79:1-36
 */
static void srlx_e16u6e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shiftx_e16u6e16(line, 38U /* SRL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro srax defined at ../../../targets/sparc64/opmatch.def:80:1-34
 */
static void srax_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shiftx_e16e16e16(line, 39U /* SRA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro srax defined at ../../../targets/sparc64/opmatch.def:81:1-36
 */
static void srax_e16u6e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      shiftx_e16u6e16(line, 39U /* SRA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro umul defined at ../../../targets/sparc64/opmatch.def:84:1-32
 */
static void umul_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      mul_e16e16e16(line, 10U /* UMUL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro umul defined at ../../../targets/sparc64/opmatch.def:85:1-35
 */
static void umul_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      mul_e16i13e16(line, 10U /* UMUL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro smul defined at ../../../targets/sparc64/opmatch.def:86:1-32
 */
static void smul_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      mul_e16e16e16(line, 11U /* SMUL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro smul defined at ../../../targets/sparc64/opmatch.def:87:1-35
 */
static void smul_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      mul_e16i13e16(line, 11U /* SMUL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro umulcc defined at ../../../targets/sparc64/opmatch.def:88:1-36
 */
static void umulcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      mul_e16e16e16(line, 26U /* UMULcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro umulcc defined at ../../../targets/sparc64/opmatch.def:89:1-39
 */
static void umulcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      mul_e16i13e16(line, 26U /* UMULcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro smulcc defined at ../../../targets/sparc64/opmatch.def:90:1-36
 */
static void smulcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      mul_e16e16e16(line, 27U /* SMULcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro smulcc defined at ../../../targets/sparc64/opmatch.def:91:1-39
 */
static void smulcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      mul_e16i13e16(line, 27U /* SMULcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro mulscc defined at ../../../targets/sparc64/opmatch.def:92:1-36
 */
static void mulscc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      mul_e16e16e16(line, 36U /* MULScc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro mulscc defined at ../../../targets/sparc64/opmatch.def:93:1-39
 */
static void mulscc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      mul_e16i13e16(line, 36U /* MULScc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sdiv defined at ../../../targets/sparc64/opmatch.def:94:1-32
 */
static void sdiv_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      div_e16e16e16(line, 15U /* SDIV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sdiv defined at ../../../targets/sparc64/opmatch.def:95:1-35
 */
static void sdiv_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      div_e16i13e16(line, 15U /* SDIV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro udiv defined at ../../../targets/sparc64/opmatch.def:96:1-32
 */
static void udiv_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      div_e16e16e16(line, 14U /* UDIV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro udiv defined at ../../../targets/sparc64/opmatch.def:97:1-35
 */
static void udiv_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      div_e16i13e16(line, 14U /* UDIV */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sdivcc defined at ../../../targets/sparc64/opmatch.def:98:1-36
 */
static void sdivcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      div_e16e16e16(line, 31U /* SDIVcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sdivcc defined at ../../../targets/sparc64/opmatch.def:99:1-39
 */
static void sdivcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      div_e16i13e16(line, 31U /* SDIVcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro udivcc defined at ../../../targets/sparc64/opmatch.def:100:1-36
 */
static void udivcc_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      div_e16e16e16(line, 30U /* UDIVcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro udivcc defined at ../../../targets/sparc64/opmatch.def:101:1-39
 */
static void udivcc_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      div_e16i13e16(line, 30U /* UDIVcc */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro mulx defined at ../../../targets/sparc64/opmatch.def:104:1-36
 */
static void mulx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      muldivx_e16e16e16(line, 9U /* MULX */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro mulx defined at ../../../targets/sparc64/opmatch.def:105:1-39
 */
static void mulx_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      muldivx_e16i13e16(line, 9U /* MULX */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sdivx defined at ../../../targets/sparc64/opmatch.def:106:1-38
 */
static void sdivx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      muldivx_e16e16e16(line, 45U /* SDIVX */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sdivx defined at ../../../targets/sparc64/opmatch.def:107:1-41
 */
static void sdivx_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      muldivx_e16i13e16(line, 45U /* SDIVX */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro udivx defined at ../../../targets/sparc64/opmatch.def:108:1-38
 */
static void udivx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      muldivx_e16e16e16(line, 13U /* UDIVX */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro udivx defined at ../../../targets/sparc64/opmatch.def:109:1-41
 */
static void udivx_e16i13e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      muldivx_e16i13e16(line, 13U /* UDIVX */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fadds defined at ../../../targets/sparc64/opmatch.def:111:1-38
 */
static void fadds_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fadd_e14e14e14(line, 65U /* FADDs */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro faddd defined at ../../../targets/sparc64/opmatch.def:112:1-38
 */
static void faddd_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fadd_e14e14e14(line, 66U /* FADDd */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro faddq defined at ../../../targets/sparc64/opmatch.def:113:1-38
 */
static void faddq_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fadd_e14e14e14(line, 67U /* FADDq */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fsubs defined at ../../../targets/sparc64/opmatch.def:114:1-38
 */
static void fsubs_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fadd_e14e14e14(line, 69U /* FSUBs */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fsubd defined at ../../../targets/sparc64/opmatch.def:115:1-38
 */
static void fsubd_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fadd_e14e14e14(line, 70U /* FSUBd */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fsubq defined at ../../../targets/sparc64/opmatch.def:116:1-38
 */
static void fsubq_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fadd_e14e14e14(line, 71U /* FSUBq */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fcmps defined at ../../../targets/sparc64/opmatch.def:118:1-37
 */
static void fcmps_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fcmp_e13e14e14(line, 81U /* FCMPs */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fcmpd defined at ../../../targets/sparc64/opmatch.def:119:1-37
 */
static void fcmpd_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fcmp_e13e14e14(line, 82U /* FCMPd */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fcmpq defined at ../../../targets/sparc64/opmatch.def:120:1-37
 */
static void fcmpq_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fcmp_e13e14e14(line, 83U /* FCMPq */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fcmpes defined at ../../../targets/sparc64/opmatch.def:121:1-39
 */
static void fcmpes_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fcmp_e13e14e14(line, 85U /* FCMPEs */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fcmped defined at ../../../targets/sparc64/opmatch.def:122:1-39
 */
static void fcmped_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fcmp_e13e14e14(line, 86U /* FCMPEd */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fcmpeq defined at ../../../targets/sparc64/opmatch.def:123:1-39
 */
static void fcmpeq_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fcmp_e13e14e14(line, 87U /* FCMPEq */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fstox defined at ../../../targets/sparc64/opmatch.def:125:1-31
 */
static void fstox_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 129U /* FsTOx */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fdtox defined at ../../../targets/sparc64/opmatch.def:126:1-31
 */
static void fdtox_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 130U /* FdTOx */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fqtox defined at ../../../targets/sparc64/opmatch.def:127:1-31
 */
static void fqtox_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 131U /* FqTOx */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fstoi defined at ../../../targets/sparc64/opmatch.def:128:1-31
 */
static void fstoi_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 209U /* FsTOi */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fdtoi defined at ../../../targets/sparc64/opmatch.def:129:1-31
 */
static void fdtoi_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 210U /* FdTOi */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fqtoi defined at ../../../targets/sparc64/opmatch.def:130:1-31
 */
static void fqtoi_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 211U /* FqTOi */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fxtos defined at ../../../targets/sparc64/opmatch.def:131:1-31
 */
static void fxtos_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 132U /* FxTOs */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fxtod defined at ../../../targets/sparc64/opmatch.def:132:1-31
 */
static void fxtod_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 136U /* FxTOd */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fxtoq defined at ../../../targets/sparc64/opmatch.def:133:1-31
 */
static void fxtoq_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 140U /* FxTOq */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fitos defined at ../../../targets/sparc64/opmatch.def:134:1-31
 */
static void fitos_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 196U /* FiTOs */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fitod defined at ../../../targets/sparc64/opmatch.def:135:1-31
 */
static void fitod_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 200U /* FiTOd */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fitoq defined at ../../../targets/sparc64/opmatch.def:136:1-31
 */
static void fitoq_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 204U /* FiTOq */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fstod defined at ../../../targets/sparc64/opmatch.def:137:1-31
 */
static void fstod_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 201U /* FsTOd */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fstoq defined at ../../../targets/sparc64/opmatch.def:138:1-31
 */
static void fstoq_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 205U /* FsTOq */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fdtos defined at ../../../targets/sparc64/opmatch.def:139:1-31
 */
static void fdtos_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 198U /* FdTOs */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fdtoq defined at ../../../targets/sparc64/opmatch.def:140:1-31
 */
static void fdtoq_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 206U /* FdTOq */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fqtos defined at ../../../targets/sparc64/opmatch.def:141:1-31
 */
static void fqtos_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 199U /* FqTOs */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fqtod defined at ../../../targets/sparc64/opmatch.def:142:1-31
 */
static void fqtod_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fto_e14e14(line, 203U /* FqTOd */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fmovs defined at ../../../targets/sparc64/opmatch.def:144:1-32
 */
static void fmovs_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fmov_e14e14(line, 1U /* FMOVs */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fmovd defined at ../../../targets/sparc64/opmatch.def:145:1-32
 */
static void fmovd_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fmov_e14e14(line, 2U /* FMOVd */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fmovq defined at ../../../targets/sparc64/opmatch.def:146:1-32
 */
static void fmovq_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fmov_e14e14(line, 3U /* FMOVq */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fnegs defined at ../../../targets/sparc64/opmatch.def:147:1-32
 */
static void fnegs_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fmov_e14e14(line, 5U /* FNEGs */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fnegd defined at ../../../targets/sparc64/opmatch.def:148:1-32
 */
static void fnegd_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fmov_e14e14(line, 6U /* FNEGd */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fnegq defined at ../../../targets/sparc64/opmatch.def:149:1-32
 */
static void fnegq_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fmov_e14e14(line, 7U /* FNEGq */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fabss defined at ../../../targets/sparc64/opmatch.def:150:1-32
 */
static void fabss_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fmov_e14e14(line, 9U /* FABSs */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fabsd defined at ../../../targets/sparc64/opmatch.def:151:1-32
 */
static void fabsd_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fmov_e14e14(line, 10U /* FABSd */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fabsq defined at ../../../targets/sparc64/opmatch.def:152:1-32
 */
static void fabsq_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fmov_e14e14(line, 11U /* FABSq */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fsqrts defined at ../../../targets/sparc64/opmatch.def:153:1-34
 */
static void fsqrts_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fmov_e14e14(line, 41U /* FSQRTs */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fsqrtd defined at ../../../targets/sparc64/opmatch.def:154:1-34
 */
static void fsqrtd_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fmov_e14e14(line, 42U /* FSQRTd */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fsqrtq defined at ../../../targets/sparc64/opmatch.def:155:1-34
 */
static void fsqrtq_e14e14(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      fmov_e14e14(line, 43U /* FSQRTq */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fmuls defined at ../../../targets/sparc64/opmatch.def:157:1-38
 */
static void fmuls_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmul_e14e14e14(line, 73U /* FMULs */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmuld defined at ../../../targets/sparc64/opmatch.def:158:1-38
 */
static void fmuld_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmul_e14e14e14(line, 74U /* FMULd */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmulq defined at ../../../targets/sparc64/opmatch.def:159:1-38
 */
static void fmulq_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmul_e14e14e14(line, 75U /* FMULq */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fsmuld defined at ../../../targets/sparc64/opmatch.def:160:1-40
 */
static void fsmuld_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmul_e14e14e14(line, 105U /* FsMULd */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fdmulq defined at ../../../targets/sparc64/opmatch.def:161:1-40
 */
static void fdmulq_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmul_e14e14e14(line, 110U /* FdMULq */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fdivs defined at ../../../targets/sparc64/opmatch.def:162:1-38
 */
static void fdivs_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmul_e14e14e14(line, 77U /* FDIVs */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fdivd defined at ../../../targets/sparc64/opmatch.def:163:1-38
 */
static void fdivd_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmul_e14e14e14(line, 78U /* FDIVd */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fdivq defined at ../../../targets/sparc64/opmatch.def:164:1-38
 */
static void fdivq_e14e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmul_e14e14e14(line, 79U /* FDIVq */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro brz defined at ../../../targets/sparc64/opmatch.def:166:1-42
 */
static void brz_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 1U /* BRZ */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brz,pt defined at ../../../targets/sparc64/opmatch.def:167:1-44
 */
static void brz_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 1U /* BRZ */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brz,pn defined at ../../../targets/sparc64/opmatch.def:168:1-44
 */
static void brz_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 1U /* BRZ */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brz,a defined at ../../../targets/sparc64/opmatch.def:169:1-41
 */
static void brz_a_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 1U /* BRZ */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brz,a,pt defined at ../../../targets/sparc64/opmatch.def:170:1-44
 */
static void brz_a_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 1U /* BRZ */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brz,a,pn defined at ../../../targets/sparc64/opmatch.def:171:1-44
 */
static void brz_a_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 1U /* BRZ */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brlez defined at ../../../targets/sparc64/opmatch.def:172:1-45
 */
static void brlez_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 2U /* BRLEZ */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brlez,pt defined at ../../../targets/sparc64/opmatch.def:173:1-48
 */
static void brlez_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 2U /* BRLEZ */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brlez,pn defined at ../../../targets/sparc64/opmatch.def:174:1-48
 */
static void brlez_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 2U /* BRLEZ */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brlez,a defined at ../../../targets/sparc64/opmatch.def:175:1-45
 */
static void brlez_a_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 2U /* BRLEZ */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brlez,a,pt defined at ../../../targets/sparc64/opmatch.def:176:1-48
 */
static void brlez_a_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 2U /* BRLEZ */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brlez,a,pn defined at ../../../targets/sparc64/opmatch.def:177:1-48
 */
static void brlez_a_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 2U /* BRLEZ */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brlz defined at ../../../targets/sparc64/opmatch.def:178:1-43
 */
static void brlz_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 3U /* BRLZ */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brlz,pt defined at ../../../targets/sparc64/opmatch.def:179:1-46
 */
static void brlz_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 3U /* BRLZ */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brlz,pn defined at ../../../targets/sparc64/opmatch.def:180:1-46
 */
static void brlz_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 3U /* BRLZ */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brlz,a defined at ../../../targets/sparc64/opmatch.def:181:1-43
 */
static void brlz_a_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 3U /* BRLZ */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brlz,a,pt defined at ../../../targets/sparc64/opmatch.def:182:1-46
 */
static void brlz_a_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 3U /* BRLZ */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brlz,a,pn defined at ../../../targets/sparc64/opmatch.def:183:1-46
 */
static void brlz_a_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 3U /* BRLZ */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brnz defined at ../../../targets/sparc64/opmatch.def:184:1-43
 */
static void brnz_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 5U /* BRNZ */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brnz,pt defined at ../../../targets/sparc64/opmatch.def:185:1-46
 */
static void brnz_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 5U /* BRNZ */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brnz,pn defined at ../../../targets/sparc64/opmatch.def:186:1-46
 */
static void brnz_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 5U /* BRNZ */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brnz,a defined at ../../../targets/sparc64/opmatch.def:187:1-43
 */
static void brnz_a_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 5U /* BRNZ */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brnz,a,pt defined at ../../../targets/sparc64/opmatch.def:188:1-46
 */
static void brnz_a_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 5U /* BRNZ */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brnz,a,pn defined at ../../../targets/sparc64/opmatch.def:189:1-46
 */
static void brnz_a_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 5U /* BRNZ */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brgz defined at ../../../targets/sparc64/opmatch.def:190:1-43
 */
static void brgz_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 6U /* BRGZ */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brgz,pt defined at ../../../targets/sparc64/opmatch.def:191:1-46
 */
static void brgz_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 6U /* BRGZ */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brgz,pn defined at ../../../targets/sparc64/opmatch.def:192:1-46
 */
static void brgz_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 6U /* BRGZ */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brgz,a defined at ../../../targets/sparc64/opmatch.def:193:1-43
 */
static void brgz_a_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 6U /* BRGZ */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brgz,a,pt defined at ../../../targets/sparc64/opmatch.def:194:1-46
 */
static void brgz_a_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 6U /* BRGZ */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brgz,a,pn defined at ../../../targets/sparc64/opmatch.def:195:1-46
 */
static void brgz_a_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 6U /* BRGZ */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brgez defined at ../../../targets/sparc64/opmatch.def:196:1-45
 */
static void brgez_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 7U /* BRGEZ */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brgez,pt defined at ../../../targets/sparc64/opmatch.def:197:1-48
 */
static void brgez_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 7U /* BRGEZ */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brgez,pn defined at ../../../targets/sparc64/opmatch.def:198:1-48
 */
static void brgez_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 7U /* BRGEZ */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brgez,a defined at ../../../targets/sparc64/opmatch.def:199:1-45
 */
static void brgez_a_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 7U /* BRGEZ */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brgez,a,pt defined at ../../../targets/sparc64/opmatch.def:200:1-48
 */
static void brgez_a_pt_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 7U /* BRGEZ */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro brgez,a,pn defined at ../../../targets/sparc64/opmatch.def:201:1-48
 */
static void brgez_a_pn_e16xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpr_e16xu64(line, 7U /* BRGEZ */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fba defined at ../../../targets/sparc64/opmatch.def:204:1-35
 */
static void fba_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 8U /* FBA */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fba,a defined at ../../../targets/sparc64/opmatch.def:205:1-35
 */
static void fba_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 8U /* FBA */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbn defined at ../../../targets/sparc64/opmatch.def:206:1-35
 */
static void fbn_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 0U /* FBN */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbn,a defined at ../../../targets/sparc64/opmatch.def:207:1-35
 */
static void fbn_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 0U /* FBN */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbu defined at ../../../targets/sparc64/opmatch.def:208:1-35
 */
static void fbu_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 7U /* FBU */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbu,a defined at ../../../targets/sparc64/opmatch.def:209:1-35
 */
static void fbu_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 7U /* FBU */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbg defined at ../../../targets/sparc64/opmatch.def:210:1-35
 */
static void fbg_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 6U /* FBG */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbg,a defined at ../../../targets/sparc64/opmatch.def:211:1-35
 */
static void fbg_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 6U /* FBG */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbug defined at ../../../targets/sparc64/opmatch.def:212:1-37
 */
static void fbug_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 5U /* FBUG */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbug,a defined at ../../../targets/sparc64/opmatch.def:213:1-37
 */
static void fbug_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 5U /* FBUG */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbl defined at ../../../targets/sparc64/opmatch.def:214:1-35
 */
static void fbl_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 4U /* FBL */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbl,a defined at ../../../targets/sparc64/opmatch.def:215:1-35
 */
static void fbl_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 4U /* FBL */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbul defined at ../../../targets/sparc64/opmatch.def:216:1-37
 */
static void fbul_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 3U /* FBUL */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbul,a defined at ../../../targets/sparc64/opmatch.def:217:1-37
 */
static void fbul_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 3U /* FBUL */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fblg defined at ../../../targets/sparc64/opmatch.def:218:1-37
 */
static void fblg_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 2U /* FBLG */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fblg,a defined at ../../../targets/sparc64/opmatch.def:219:1-37
 */
static void fblg_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 2U /* FBLG */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbne defined at ../../../targets/sparc64/opmatch.def:220:1-37
 */
static void fbne_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 1U /* FBNE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbne,a defined at ../../../targets/sparc64/opmatch.def:221:1-37
 */
static void fbne_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 1U /* FBNE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbe defined at ../../../targets/sparc64/opmatch.def:222:1-35
 */
static void fbe_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 9U /* FBE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbe,a defined at ../../../targets/sparc64/opmatch.def:223:1-35
 */
static void fbe_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 9U /* FBE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbue defined at ../../../targets/sparc64/opmatch.def:224:1-37
 */
static void fbue_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 10U /* FBUE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbue,a defined at ../../../targets/sparc64/opmatch.def:225:1-37
 */
static void fbue_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 10U /* FBUE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbge defined at ../../../targets/sparc64/opmatch.def:226:1-37
 */
static void fbge_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 11U /* FBGE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbge,a defined at ../../../targets/sparc64/opmatch.def:227:1-37
 */
static void fbge_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 11U /* FBGE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbuge defined at ../../../targets/sparc64/opmatch.def:228:1-39
 */
static void fbuge_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 12U /* FBUGE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbuge,a defined at ../../../targets/sparc64/opmatch.def:229:1-39
 */
static void fbuge_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 12U /* FBUGE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fble defined at ../../../targets/sparc64/opmatch.def:230:1-37
 */
static void fble_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 13U /* FBLE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fble,a defined at ../../../targets/sparc64/opmatch.def:231:1-37
 */
static void fble_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 13U /* FBLE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbule defined at ../../../targets/sparc64/opmatch.def:232:1-39
 */
static void fbule_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 14U /* FBULE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbule,a defined at ../../../targets/sparc64/opmatch.def:233:1-39
 */
static void fbule_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 14U /* FBULE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbo defined at ../../../targets/sparc64/opmatch.def:234:1-35
 */
static void fbo_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 15U /* FBO */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbo,a defined at ../../../targets/sparc64/opmatch.def:235:1-35
 */
static void fbo_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 15U /* FBO */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbnz defined at ../../../targets/sparc64/opmatch.def:237:1-37
 */
static void fbnz_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 1U /* FBNE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbnz,a defined at ../../../targets/sparc64/opmatch.def:238:1-37
 */
static void fbnz_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 1U /* FBNE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbz defined at ../../../targets/sparc64/opmatch.def:239:1-35
 */
static void fbz_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 9U /* FBE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fbz,a defined at ../../../targets/sparc64/opmatch.def:240:1-35
 */
static void fbz_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      fbfcc_xu64(line, 9U /* FBE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro fba defined at ../../../targets/sparc64/opmatch.def:243:1-45
 */
static void fba_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 8U /* FBA */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fba,pt defined at ../../../targets/sparc64/opmatch.def:244:1-47
 */
static void fba_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 8U /* FBA */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fba,pn defined at ../../../targets/sparc64/opmatch.def:245:1-47
 */
static void fba_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 8U /* FBA */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fba,a defined at ../../../targets/sparc64/opmatch.def:246:1-44
 */
static void fba_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 8U /* FBA */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fba,a,pt defined at ../../../targets/sparc64/opmatch.def:247:1-47
 */
static void fba_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 8U /* FBA */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fba,a,pn defined at ../../../targets/sparc64/opmatch.def:248:1-47
 */
static void fba_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 8U /* FBA */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbn defined at ../../../targets/sparc64/opmatch.def:249:1-45
 */
static void fbn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 0U /* FBN */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbn,pt defined at ../../../targets/sparc64/opmatch.def:250:1-47
 */
static void fbn_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 0U /* FBN */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbn,pn defined at ../../../targets/sparc64/opmatch.def:251:1-47
 */
static void fbn_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 0U /* FBN */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbn,a defined at ../../../targets/sparc64/opmatch.def:252:1-44
 */
static void fbn_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 0U /* FBN */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbn,a,pt defined at ../../../targets/sparc64/opmatch.def:253:1-47
 */
static void fbn_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 0U /* FBN */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbn,a,pn defined at ../../../targets/sparc64/opmatch.def:254:1-47
 */
static void fbn_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 0U /* FBN */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbu defined at ../../../targets/sparc64/opmatch.def:255:1-45
 */
static void fbu_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 7U /* FBU */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbu,pt defined at ../../../targets/sparc64/opmatch.def:256:1-47
 */
static void fbu_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 7U /* FBU */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbu,pn defined at ../../../targets/sparc64/opmatch.def:257:1-47
 */
static void fbu_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 7U /* FBU */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbu,a defined at ../../../targets/sparc64/opmatch.def:258:1-44
 */
static void fbu_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 7U /* FBU */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbu,a,pt defined at ../../../targets/sparc64/opmatch.def:259:1-47
 */
static void fbu_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 7U /* FBU */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbu,a,pn defined at ../../../targets/sparc64/opmatch.def:260:1-47
 */
static void fbu_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 7U /* FBU */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbg defined at ../../../targets/sparc64/opmatch.def:261:1-45
 */
static void fbg_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 6U /* FBG */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbg,pt defined at ../../../targets/sparc64/opmatch.def:262:1-47
 */
static void fbg_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 6U /* FBG */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbg,pn defined at ../../../targets/sparc64/opmatch.def:263:1-47
 */
static void fbg_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 6U /* FBG */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbg,a defined at ../../../targets/sparc64/opmatch.def:264:1-44
 */
static void fbg_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 6U /* FBG */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbg,a,pt defined at ../../../targets/sparc64/opmatch.def:265:1-47
 */
static void fbg_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 6U /* FBG */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbg,a,pn defined at ../../../targets/sparc64/opmatch.def:266:1-47
 */
static void fbg_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 6U /* FBG */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbug defined at ../../../targets/sparc64/opmatch.def:267:1-46
 */
static void fbug_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 5U /* FBUG */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbug,pt defined at ../../../targets/sparc64/opmatch.def:268:1-49
 */
static void fbug_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 5U /* FBUG */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbug,pn defined at ../../../targets/sparc64/opmatch.def:269:1-49
 */
static void fbug_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 5U /* FBUG */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbug,a defined at ../../../targets/sparc64/opmatch.def:270:1-46
 */
static void fbug_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 5U /* FBUG */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbug,a,pt defined at ../../../targets/sparc64/opmatch.def:271:1-49
 */
static void fbug_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 5U /* FBUG */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbug,a,pn defined at ../../../targets/sparc64/opmatch.def:272:1-49
 */
static void fbug_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 5U /* FBUG */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbl defined at ../../../targets/sparc64/opmatch.def:273:1-45
 */
static void fbl_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 4U /* FBL */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbl,pt defined at ../../../targets/sparc64/opmatch.def:274:1-47
 */
static void fbl_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 4U /* FBL */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbl,pn defined at ../../../targets/sparc64/opmatch.def:275:1-47
 */
static void fbl_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 4U /* FBL */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbl,a defined at ../../../targets/sparc64/opmatch.def:276:1-44
 */
static void fbl_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 4U /* FBL */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbl,a,pt defined at ../../../targets/sparc64/opmatch.def:277:1-47
 */
static void fbl_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 4U /* FBL */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbl,a,pn defined at ../../../targets/sparc64/opmatch.def:278:1-47
 */
static void fbl_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 4U /* FBL */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbul defined at ../../../targets/sparc64/opmatch.def:279:1-46
 */
static void fbul_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 3U /* FBUL */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbul,pt defined at ../../../targets/sparc64/opmatch.def:280:1-49
 */
static void fbul_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 3U /* FBUL */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbul,pn defined at ../../../targets/sparc64/opmatch.def:281:1-49
 */
static void fbul_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 3U /* FBUL */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbul,a defined at ../../../targets/sparc64/opmatch.def:282:1-46
 */
static void fbul_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 3U /* FBUL */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbul,a,pt defined at ../../../targets/sparc64/opmatch.def:283:1-49
 */
static void fbul_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 3U /* FBUL */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbul,a,pn defined at ../../../targets/sparc64/opmatch.def:284:1-49
 */
static void fbul_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 3U /* FBUL */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fblg defined at ../../../targets/sparc64/opmatch.def:285:1-46
 */
static void fblg_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 2U /* FBLG */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fblg,pt defined at ../../../targets/sparc64/opmatch.def:286:1-49
 */
static void fblg_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 2U /* FBLG */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fblg,pn defined at ../../../targets/sparc64/opmatch.def:287:1-49
 */
static void fblg_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 2U /* FBLG */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fblg,a defined at ../../../targets/sparc64/opmatch.def:288:1-46
 */
static void fblg_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 2U /* FBLG */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fblg,a,pt defined at ../../../targets/sparc64/opmatch.def:289:1-49
 */
static void fblg_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 2U /* FBLG */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fblg,a,pn defined at ../../../targets/sparc64/opmatch.def:290:1-49
 */
static void fblg_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 2U /* FBLG */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbne defined at ../../../targets/sparc64/opmatch.def:291:1-46
 */
static void fbne_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 1U /* FBNE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbne,pt defined at ../../../targets/sparc64/opmatch.def:292:1-49
 */
static void fbne_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 1U /* FBNE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbne,pn defined at ../../../targets/sparc64/opmatch.def:293:1-49
 */
static void fbne_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 1U /* FBNE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbne,a defined at ../../../targets/sparc64/opmatch.def:294:1-46
 */
static void fbne_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 1U /* FBNE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbne,a,pt defined at ../../../targets/sparc64/opmatch.def:295:1-49
 */
static void fbne_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 1U /* FBNE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbne,a,pn defined at ../../../targets/sparc64/opmatch.def:296:1-49
 */
static void fbne_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 1U /* FBNE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbe defined at ../../../targets/sparc64/opmatch.def:297:1-45
 */
static void fbe_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 9U /* FBE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbe,pt defined at ../../../targets/sparc64/opmatch.def:298:1-47
 */
static void fbe_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 9U /* FBE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbe,pn defined at ../../../targets/sparc64/opmatch.def:299:1-47
 */
static void fbe_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 9U /* FBE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbe,a defined at ../../../targets/sparc64/opmatch.def:300:1-44
 */
static void fbe_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 9U /* FBE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbe,a,pt defined at ../../../targets/sparc64/opmatch.def:301:1-47
 */
static void fbe_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 9U /* FBE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbe,a,pn defined at ../../../targets/sparc64/opmatch.def:302:1-47
 */
static void fbe_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 9U /* FBE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbue defined at ../../../targets/sparc64/opmatch.def:303:1-46
 */
static void fbue_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 10U /* FBUE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbue,pt defined at ../../../targets/sparc64/opmatch.def:304:1-49
 */
static void fbue_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 10U /* FBUE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbue,pn defined at ../../../targets/sparc64/opmatch.def:305:1-49
 */
static void fbue_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 10U /* FBUE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbue,a defined at ../../../targets/sparc64/opmatch.def:306:1-46
 */
static void fbue_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 10U /* FBUE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbue,a,pt defined at ../../../targets/sparc64/opmatch.def:307:1-49
 */
static void fbue_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 10U /* FBUE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbue,a,pn defined at ../../../targets/sparc64/opmatch.def:308:1-49
 */
static void fbue_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 10U /* FBUE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbge defined at ../../../targets/sparc64/opmatch.def:309:1-46
 */
static void fbge_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 11U /* FBGE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbge,pt defined at ../../../targets/sparc64/opmatch.def:310:1-49
 */
static void fbge_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 11U /* FBGE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbge,pn defined at ../../../targets/sparc64/opmatch.def:311:1-49
 */
static void fbge_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 11U /* FBGE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbge,a defined at ../../../targets/sparc64/opmatch.def:312:1-46
 */
static void fbge_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 11U /* FBGE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbge,a,pt defined at ../../../targets/sparc64/opmatch.def:313:1-49
 */
static void fbge_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 11U /* FBGE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbge,a,pn defined at ../../../targets/sparc64/opmatch.def:314:1-49
 */
static void fbge_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 11U /* FBGE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbuge defined at ../../../targets/sparc64/opmatch.def:315:1-48
 */
static void fbuge_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 12U /* FBUGE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbuge,pt defined at ../../../targets/sparc64/opmatch.def:316:1-51
 */
static void fbuge_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 12U /* FBUGE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbuge,pn defined at ../../../targets/sparc64/opmatch.def:317:1-51
 */
static void fbuge_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 12U /* FBUGE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbuge,a defined at ../../../targets/sparc64/opmatch.def:318:1-48
 */
static void fbuge_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 12U /* FBUGE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbuge,a,pt defined at ../../../targets/sparc64/opmatch.def:319:1-51
 */
static void fbuge_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 12U /* FBUGE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbuge,a,pn defined at ../../../targets/sparc64/opmatch.def:320:1-51
 */
static void fbuge_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 12U /* FBUGE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fble defined at ../../../targets/sparc64/opmatch.def:321:1-46
 */
static void fble_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 13U /* FBLE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fble,pt defined at ../../../targets/sparc64/opmatch.def:322:1-49
 */
static void fble_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 13U /* FBLE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fble,pn defined at ../../../targets/sparc64/opmatch.def:323:1-49
 */
static void fble_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 13U /* FBLE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fble,a defined at ../../../targets/sparc64/opmatch.def:324:1-46
 */
static void fble_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 13U /* FBLE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fble,a,pt defined at ../../../targets/sparc64/opmatch.def:325:1-49
 */
static void fble_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 13U /* FBLE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fble,a,pn defined at ../../../targets/sparc64/opmatch.def:326:1-49
 */
static void fble_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 13U /* FBLE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbule defined at ../../../targets/sparc64/opmatch.def:327:1-48
 */
static void fbule_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 14U /* FBULE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbule,pt defined at ../../../targets/sparc64/opmatch.def:328:1-51
 */
static void fbule_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 14U /* FBULE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbule,pn defined at ../../../targets/sparc64/opmatch.def:329:1-51
 */
static void fbule_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 14U /* FBULE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbule,a defined at ../../../targets/sparc64/opmatch.def:330:1-48
 */
static void fbule_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 14U /* FBULE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbule,a,pt defined at ../../../targets/sparc64/opmatch.def:331:1-51
 */
static void fbule_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 14U /* FBULE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbule,a,pn defined at ../../../targets/sparc64/opmatch.def:332:1-51
 */
static void fbule_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 14U /* FBULE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbo defined at ../../../targets/sparc64/opmatch.def:333:1-45
 */
static void fbo_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 15U /* FBO */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbo,pt defined at ../../../targets/sparc64/opmatch.def:334:1-47
 */
static void fbo_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 15U /* FBO */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbo,pn defined at ../../../targets/sparc64/opmatch.def:335:1-47
 */
static void fbo_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 15U /* FBO */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbo,a defined at ../../../targets/sparc64/opmatch.def:336:1-44
 */
static void fbo_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 15U /* FBO */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbo,a,pt defined at ../../../targets/sparc64/opmatch.def:337:1-47
 */
static void fbo_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 15U /* FBO */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbo,a,pn defined at ../../../targets/sparc64/opmatch.def:338:1-47
 */
static void fbo_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 15U /* FBO */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbnz defined at ../../../targets/sparc64/opmatch.def:340:1-46
 */
static void fbnz_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 1U /* FBNE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbnz,pt defined at ../../../targets/sparc64/opmatch.def:341:1-49
 */
static void fbnz_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 1U /* FBNE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbnz,pn defined at ../../../targets/sparc64/opmatch.def:342:1-49
 */
static void fbnz_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 1U /* FBNE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbnz,a defined at ../../../targets/sparc64/opmatch.def:343:1-46
 */
static void fbnz_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 1U /* FBNE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbnz,a,pt defined at ../../../targets/sparc64/opmatch.def:344:1-49
 */
static void fbnz_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 1U /* FBNE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbnz,a,pn defined at ../../../targets/sparc64/opmatch.def:345:1-49
 */
static void fbnz_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 1U /* FBNE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbz defined at ../../../targets/sparc64/opmatch.def:346:1-45
 */
static void fbz_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 9U /* FBE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbz,pt defined at ../../../targets/sparc64/opmatch.def:347:1-47
 */
static void fbz_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 9U /* FBE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbz,pn defined at ../../../targets/sparc64/opmatch.def:348:1-47
 */
static void fbz_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 9U /* FBE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbz,a defined at ../../../targets/sparc64/opmatch.def:349:1-44
 */
static void fbz_a_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 9U /* FBE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbz,a,pt defined at ../../../targets/sparc64/opmatch.def:350:1-47
 */
static void fbz_a_pt_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 9U /* FBE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fbz,a,pn defined at ../../../targets/sparc64/opmatch.def:351:1-47
 */
static void fbz_a_pn_e13xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      fbpfcc_e13xu64(line, 9U /* FBE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ba defined at ../../../targets/sparc64/opmatch.def:354:1-32
 */
static void ba_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 8U /* BA */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro ba,a defined at ../../../targets/sparc64/opmatch.def:355:1-32
 */
static void ba_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 8U /* BA */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bn defined at ../../../targets/sparc64/opmatch.def:356:1-32
 */
static void bn_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 0U /* BN */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bn,a defined at ../../../targets/sparc64/opmatch.def:357:1-32
 */
static void bn_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 0U /* BN */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bne defined at ../../../targets/sparc64/opmatch.def:358:1-34
 */
static void bne_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 9U /* BNE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bne,a defined at ../../../targets/sparc64/opmatch.def:359:1-34
 */
static void bne_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 9U /* BNE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro be defined at ../../../targets/sparc64/opmatch.def:360:1-32
 */
static void be_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 1U /* BE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro be,a defined at ../../../targets/sparc64/opmatch.def:361:1-32
 */
static void be_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 1U /* BE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bg defined at ../../../targets/sparc64/opmatch.def:362:1-32
 */
static void bg_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 10U /* BG */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bg,a defined at ../../../targets/sparc64/opmatch.def:363:1-32
 */
static void bg_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 10U /* BG */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro ble defined at ../../../targets/sparc64/opmatch.def:364:1-34
 */
static void ble_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 2U /* BLE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro ble,a defined at ../../../targets/sparc64/opmatch.def:365:1-34
 */
static void ble_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 2U /* BLE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bge defined at ../../../targets/sparc64/opmatch.def:366:1-34
 */
static void bge_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 11U /* BGE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bge,a defined at ../../../targets/sparc64/opmatch.def:367:1-34
 */
static void bge_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 11U /* BGE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bl defined at ../../../targets/sparc64/opmatch.def:368:1-32
 */
static void bl_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 3U /* BL */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bl,a defined at ../../../targets/sparc64/opmatch.def:369:1-32
 */
static void bl_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 3U /* BL */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bgu defined at ../../../targets/sparc64/opmatch.def:370:1-34
 */
static void bgu_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 12U /* BGU */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bgu,a defined at ../../../targets/sparc64/opmatch.def:371:1-34
 */
static void bgu_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 12U /* BGU */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bleu defined at ../../../targets/sparc64/opmatch.def:372:1-36
 */
static void bleu_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 4U /* BLEU */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bleu,a defined at ../../../targets/sparc64/opmatch.def:373:1-36
 */
static void bleu_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 4U /* BLEU */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bcc defined at ../../../targets/sparc64/opmatch.def:374:1-34
 */
static void bcc_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 13U /* BCC */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bcc,a defined at ../../../targets/sparc64/opmatch.def:375:1-34
 */
static void bcc_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 13U /* BCC */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bcs defined at ../../../targets/sparc64/opmatch.def:376:1-34
 */
static void bcs_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 5U /* BCS */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bcs,a defined at ../../../targets/sparc64/opmatch.def:377:1-34
 */
static void bcs_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 5U /* BCS */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bpos defined at ../../../targets/sparc64/opmatch.def:378:1-36
 */
static void bpos_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 14U /* BPOS */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bpos,a defined at ../../../targets/sparc64/opmatch.def:379:1-36
 */
static void bpos_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 14U /* BPOS */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bneg defined at ../../../targets/sparc64/opmatch.def:380:1-36
 */
static void bneg_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 6U /* BNEG */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bneg,a defined at ../../../targets/sparc64/opmatch.def:381:1-36
 */
static void bneg_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 6U /* BNEG */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bvc defined at ../../../targets/sparc64/opmatch.def:382:1-34
 */
static void bvc_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 15U /* BVC */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bvc,a defined at ../../../targets/sparc64/opmatch.def:383:1-34
 */
static void bvc_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 15U /* BVC */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bvs defined at ../../../targets/sparc64/opmatch.def:384:1-34
 */
static void bvs_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 7U /* BVS */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bvs,a defined at ../../../targets/sparc64/opmatch.def:385:1-34
 */
static void bvs_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 7U /* BVS */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bnz defined at ../../../targets/sparc64/opmatch.def:387:1-34
 */
static void bnz_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 9U /* BNE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bnz,a defined at ../../../targets/sparc64/opmatch.def:388:1-34
 */
static void bnz_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 9U /* BNE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bz defined at ../../../targets/sparc64/opmatch.def:389:1-32
 */
static void bz_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 1U /* BE */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bz,a defined at ../../../targets/sparc64/opmatch.def:390:1-32
 */
static void bz_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 1U /* BE */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bgeu defined at ../../../targets/sparc64/opmatch.def:391:1-35
 */
static void bgeu_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 13U /* BCC */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro bgeu,a defined at ../../../targets/sparc64/opmatch.def:392:1-35
 */
static void bgeu_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 13U /* BCC */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro blu defined at ../../../targets/sparc64/opmatch.def:393:1-34
 */
static void blu_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 5U /* BCS */, 0U /* NOANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro blu,a defined at ../../../targets/sparc64/opmatch.def:394:1-34
 */
static void blu_a_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      bicc_xu64(line, 5U /* BCS */, 1U /* ANNUL */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro ba defined at ../../../targets/sparc64/opmatch.def:397:1-41
 */
static void ba_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 8U /* BA */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ba,pt defined at ../../../targets/sparc64/opmatch.def:398:1-43
 */
static void ba_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 8U /* BA */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ba,pn defined at ../../../targets/sparc64/opmatch.def:399:1-43
 */
static void ba_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 8U /* BA */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ba,a defined at ../../../targets/sparc64/opmatch.def:400:1-40
 */
static void ba_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 8U /* BA */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ba,a,pt defined at ../../../targets/sparc64/opmatch.def:401:1-43
 */
static void ba_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 8U /* BA */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ba,a,pn defined at ../../../targets/sparc64/opmatch.def:402:1-43
 */
static void ba_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 8U /* BA */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bn defined at ../../../targets/sparc64/opmatch.def:403:1-41
 */
static void bn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 0U /* BN */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bn,pt defined at ../../../targets/sparc64/opmatch.def:404:1-43
 */
static void bn_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 0U /* BN */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bn,pn defined at ../../../targets/sparc64/opmatch.def:405:1-43
 */
static void bn_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 0U /* BN */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bn,a defined at ../../../targets/sparc64/opmatch.def:406:1-40
 */
static void bn_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 0U /* BN */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bn,a,pt defined at ../../../targets/sparc64/opmatch.def:407:1-43
 */
static void bn_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 0U /* BN */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bn,a,pn defined at ../../../targets/sparc64/opmatch.def:408:1-43
 */
static void bn_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 0U /* BN */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bne defined at ../../../targets/sparc64/opmatch.def:409:1-43
 */
static void bne_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 9U /* BNE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bne,pt defined at ../../../targets/sparc64/opmatch.def:410:1-45
 */
static void bne_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 9U /* BNE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bne,pn defined at ../../../targets/sparc64/opmatch.def:411:1-45
 */
static void bne_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 9U /* BNE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bne,a defined at ../../../targets/sparc64/opmatch.def:412:1-42
 */
static void bne_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 9U /* BNE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bne,a,pt defined at ../../../targets/sparc64/opmatch.def:413:1-45
 */
static void bne_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 9U /* BNE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bne,a,pn defined at ../../../targets/sparc64/opmatch.def:414:1-45
 */
static void bne_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 9U /* BNE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro be defined at ../../../targets/sparc64/opmatch.def:415:1-41
 */
static void be_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 1U /* BE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro be,pt defined at ../../../targets/sparc64/opmatch.def:416:1-43
 */
static void be_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 1U /* BE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro be,pn defined at ../../../targets/sparc64/opmatch.def:417:1-43
 */
static void be_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 1U /* BE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro be,a defined at ../../../targets/sparc64/opmatch.def:418:1-40
 */
static void be_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 1U /* BE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro be,a,pt defined at ../../../targets/sparc64/opmatch.def:419:1-43
 */
static void be_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 1U /* BE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro be,a,pn defined at ../../../targets/sparc64/opmatch.def:420:1-43
 */
static void be_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 1U /* BE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bg defined at ../../../targets/sparc64/opmatch.def:421:1-41
 */
static void bg_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 10U /* BG */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bg,pt defined at ../../../targets/sparc64/opmatch.def:422:1-43
 */
static void bg_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 10U /* BG */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bg,pn defined at ../../../targets/sparc64/opmatch.def:423:1-43
 */
static void bg_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 10U /* BG */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bg,a defined at ../../../targets/sparc64/opmatch.def:424:1-40
 */
static void bg_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 10U /* BG */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bg,a,pt defined at ../../../targets/sparc64/opmatch.def:425:1-43
 */
static void bg_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 10U /* BG */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bg,a,pn defined at ../../../targets/sparc64/opmatch.def:426:1-43
 */
static void bg_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 10U /* BG */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ble defined at ../../../targets/sparc64/opmatch.def:427:1-43
 */
static void ble_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 2U /* BLE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ble,pt defined at ../../../targets/sparc64/opmatch.def:428:1-45
 */
static void ble_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 2U /* BLE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ble,pn defined at ../../../targets/sparc64/opmatch.def:429:1-45
 */
static void ble_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 2U /* BLE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ble,a defined at ../../../targets/sparc64/opmatch.def:430:1-42
 */
static void ble_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 2U /* BLE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ble,a,pt defined at ../../../targets/sparc64/opmatch.def:431:1-45
 */
static void ble_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 2U /* BLE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ble,a,pn defined at ../../../targets/sparc64/opmatch.def:432:1-45
 */
static void ble_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 2U /* BLE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bge defined at ../../../targets/sparc64/opmatch.def:433:1-43
 */
static void bge_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 11U /* BGE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bge,pt defined at ../../../targets/sparc64/opmatch.def:434:1-45
 */
static void bge_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 11U /* BGE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bge,pn defined at ../../../targets/sparc64/opmatch.def:435:1-45
 */
static void bge_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 11U /* BGE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bge,a defined at ../../../targets/sparc64/opmatch.def:436:1-42
 */
static void bge_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 11U /* BGE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bge,a,pt defined at ../../../targets/sparc64/opmatch.def:437:1-45
 */
static void bge_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 11U /* BGE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bge,a,pn defined at ../../../targets/sparc64/opmatch.def:438:1-45
 */
static void bge_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 11U /* BGE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bl defined at ../../../targets/sparc64/opmatch.def:439:1-41
 */
static void bl_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 3U /* BL */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bl,pt defined at ../../../targets/sparc64/opmatch.def:440:1-43
 */
static void bl_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 3U /* BL */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bl,pn defined at ../../../targets/sparc64/opmatch.def:441:1-43
 */
static void bl_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 3U /* BL */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bl,a defined at ../../../targets/sparc64/opmatch.def:442:1-40
 */
static void bl_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 3U /* BL */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bl,a,pt defined at ../../../targets/sparc64/opmatch.def:443:1-43
 */
static void bl_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 3U /* BL */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bl,a,pn defined at ../../../targets/sparc64/opmatch.def:444:1-43
 */
static void bl_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 3U /* BL */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgu defined at ../../../targets/sparc64/opmatch.def:445:1-43
 */
static void bgu_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 12U /* BGU */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgu,pt defined at ../../../targets/sparc64/opmatch.def:446:1-45
 */
static void bgu_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 12U /* BGU */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgu,pn defined at ../../../targets/sparc64/opmatch.def:447:1-45
 */
static void bgu_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 12U /* BGU */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgu,a defined at ../../../targets/sparc64/opmatch.def:448:1-42
 */
static void bgu_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 12U /* BGU */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgu,a,pt defined at ../../../targets/sparc64/opmatch.def:449:1-45
 */
static void bgu_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 12U /* BGU */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgu,a,pn defined at ../../../targets/sparc64/opmatch.def:450:1-45
 */
static void bgu_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 12U /* BGU */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bleu defined at ../../../targets/sparc64/opmatch.def:451:1-44
 */
static void bleu_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 4U /* BLEU */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bleu,pt defined at ../../../targets/sparc64/opmatch.def:452:1-47
 */
static void bleu_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 4U /* BLEU */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bleu,pn defined at ../../../targets/sparc64/opmatch.def:453:1-47
 */
static void bleu_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 4U /* BLEU */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bleu,a defined at ../../../targets/sparc64/opmatch.def:454:1-44
 */
static void bleu_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 4U /* BLEU */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bleu,a,pt defined at ../../../targets/sparc64/opmatch.def:455:1-47
 */
static void bleu_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 4U /* BLEU */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bleu,a,pn defined at ../../../targets/sparc64/opmatch.def:456:1-47
 */
static void bleu_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 4U /* BLEU */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bcc defined at ../../../targets/sparc64/opmatch.def:457:1-43
 */
static void bcc_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 13U /* BCC */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bcc,pt defined at ../../../targets/sparc64/opmatch.def:458:1-45
 */
static void bcc_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 13U /* BCC */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bcc,pn defined at ../../../targets/sparc64/opmatch.def:459:1-45
 */
static void bcc_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 13U /* BCC */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bcc,a defined at ../../../targets/sparc64/opmatch.def:460:1-42
 */
static void bcc_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 13U /* BCC */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bcc,a,pt defined at ../../../targets/sparc64/opmatch.def:461:1-45
 */
static void bcc_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 13U /* BCC */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bcc,a,pn defined at ../../../targets/sparc64/opmatch.def:462:1-45
 */
static void bcc_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 13U /* BCC */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bcs defined at ../../../targets/sparc64/opmatch.def:463:1-43
 */
static void bcs_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 5U /* BCS */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bcs,pt defined at ../../../targets/sparc64/opmatch.def:464:1-45
 */
static void bcs_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 5U /* BCS */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bcs,pn defined at ../../../targets/sparc64/opmatch.def:465:1-45
 */
static void bcs_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 5U /* BCS */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bcs,a defined at ../../../targets/sparc64/opmatch.def:466:1-42
 */
static void bcs_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 5U /* BCS */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bcs,a,pt defined at ../../../targets/sparc64/opmatch.def:467:1-45
 */
static void bcs_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 5U /* BCS */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bcs,a,pn defined at ../../../targets/sparc64/opmatch.def:468:1-45
 */
static void bcs_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 5U /* BCS */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bpos defined at ../../../targets/sparc64/opmatch.def:469:1-44
 */
static void bpos_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 14U /* BPOS */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bpos,pt defined at ../../../targets/sparc64/opmatch.def:470:1-47
 */
static void bpos_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 14U /* BPOS */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bpos,pn defined at ../../../targets/sparc64/opmatch.def:471:1-47
 */
static void bpos_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 14U /* BPOS */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bpos,a defined at ../../../targets/sparc64/opmatch.def:472:1-44
 */
static void bpos_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 14U /* BPOS */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bpos,a,pt defined at ../../../targets/sparc64/opmatch.def:473:1-47
 */
static void bpos_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 14U /* BPOS */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bpos,a,pn defined at ../../../targets/sparc64/opmatch.def:474:1-47
 */
static void bpos_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 14U /* BPOS */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bneg defined at ../../../targets/sparc64/opmatch.def:475:1-44
 */
static void bneg_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 6U /* BNEG */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bneg,pt defined at ../../../targets/sparc64/opmatch.def:476:1-47
 */
static void bneg_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 6U /* BNEG */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bneg,pn defined at ../../../targets/sparc64/opmatch.def:477:1-47
 */
static void bneg_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 6U /* BNEG */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bneg,a defined at ../../../targets/sparc64/opmatch.def:478:1-44
 */
static void bneg_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 6U /* BNEG */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bneg,a,pt defined at ../../../targets/sparc64/opmatch.def:479:1-47
 */
static void bneg_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 6U /* BNEG */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bneg,a,pn defined at ../../../targets/sparc64/opmatch.def:480:1-47
 */
static void bneg_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 6U /* BNEG */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bvc defined at ../../../targets/sparc64/opmatch.def:481:1-43
 */
static void bvc_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 15U /* BVC */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bvc,pt defined at ../../../targets/sparc64/opmatch.def:482:1-45
 */
static void bvc_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 15U /* BVC */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bvc,pn defined at ../../../targets/sparc64/opmatch.def:483:1-45
 */
static void bvc_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 15U /* BVC */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bvc,a defined at ../../../targets/sparc64/opmatch.def:484:1-42
 */
static void bvc_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 15U /* BVC */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bvc,a,pt defined at ../../../targets/sparc64/opmatch.def:485:1-45
 */
static void bvc_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 15U /* BVC */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bvc,a,pn defined at ../../../targets/sparc64/opmatch.def:486:1-45
 */
static void bvc_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 15U /* BVC */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bvs defined at ../../../targets/sparc64/opmatch.def:487:1-43
 */
static void bvs_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 7U /* BVS */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bvs,pt defined at ../../../targets/sparc64/opmatch.def:488:1-45
 */
static void bvs_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 7U /* BVS */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bvs,pn defined at ../../../targets/sparc64/opmatch.def:489:1-45
 */
static void bvs_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 7U /* BVS */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bvs,a defined at ../../../targets/sparc64/opmatch.def:490:1-42
 */
static void bvs_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 7U /* BVS */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bvs,a,pt defined at ../../../targets/sparc64/opmatch.def:491:1-45
 */
static void bvs_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 7U /* BVS */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bvs,a,pn defined at ../../../targets/sparc64/opmatch.def:492:1-45
 */
static void bvs_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 7U /* BVS */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bnz defined at ../../../targets/sparc64/opmatch.def:494:1-43
 */
static void bnz_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 9U /* BNE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bnz,pt defined at ../../../targets/sparc64/opmatch.def:495:1-45
 */
static void bnz_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 9U /* BNE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bnz,pn defined at ../../../targets/sparc64/opmatch.def:496:1-45
 */
static void bnz_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 9U /* BNE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bnz,a defined at ../../../targets/sparc64/opmatch.def:497:1-42
 */
static void bnz_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 9U /* BNE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bnz,a,pt defined at ../../../targets/sparc64/opmatch.def:498:1-45
 */
static void bnz_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 9U /* BNE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bnz,a,pn defined at ../../../targets/sparc64/opmatch.def:499:1-45
 */
static void bnz_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 9U /* BNE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bz defined at ../../../targets/sparc64/opmatch.def:500:1-41
 */
static void bz_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 1U /* BE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bz,pt defined at ../../../targets/sparc64/opmatch.def:501:1-43
 */
static void bz_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 1U /* BE */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bz,pn defined at ../../../targets/sparc64/opmatch.def:502:1-43
 */
static void bz_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 1U /* BE */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bz,a defined at ../../../targets/sparc64/opmatch.def:503:1-40
 */
static void bz_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 1U /* BE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bz,a,pt defined at ../../../targets/sparc64/opmatch.def:504:1-43
 */
static void bz_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 1U /* BE */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bz,a,pn defined at ../../../targets/sparc64/opmatch.def:505:1-43
 */
static void bz_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 1U /* BE */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgeu defined at ../../../targets/sparc64/opmatch.def:506:1-43
 */
static void bgeu_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 13U /* BCC */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgeu,pt defined at ../../../targets/sparc64/opmatch.def:507:1-46
 */
static void bgeu_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 13U /* BCC */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgeu,pn defined at ../../../targets/sparc64/opmatch.def:508:1-46
 */
static void bgeu_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 13U /* BCC */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgeu,a defined at ../../../targets/sparc64/opmatch.def:509:1-43
 */
static void bgeu_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 13U /* BCC */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgeu,a,pt defined at ../../../targets/sparc64/opmatch.def:510:1-46
 */
static void bgeu_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 13U /* BCC */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bgeu,a,pn defined at ../../../targets/sparc64/opmatch.def:511:1-46
 */
static void bgeu_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 13U /* BCC */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro blu defined at ../../../targets/sparc64/opmatch.def:512:1-43
 */
static void blu_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 5U /* BCS */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro blu,pt defined at ../../../targets/sparc64/opmatch.def:513:1-45
 */
static void blu_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 5U /* BCS */, 0U /* NOANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro blu,pn defined at ../../../targets/sparc64/opmatch.def:514:1-45
 */
static void blu_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 5U /* BCS */, 0U /* NOANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro blu,a defined at ../../../targets/sparc64/opmatch.def:515:1-42
 */
static void blu_a_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 5U /* BCS */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro blu,a,pt defined at ../../../targets/sparc64/opmatch.def:516:1-45
 */
static void blu_a_pt_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 5U /* BCS */, 1U /* ANNUL */, 1U /* PT */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro blu,a,pn defined at ../../../targets/sparc64/opmatch.def:517:1-45
 */
static void blu_a_pn_e17xu64(int line, uint8_t var__op0, struct expr * var__op1) {
   
   if (true) {
      bpcc_e17xu64(line, 5U /* BCS */, 1U /* ANNUL */, 0U /* PN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro fmovsa defined at ../../../targets/sparc64/opmatch.def:519:1-44
 */
static void fmovsa_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 8U /* BA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovda defined at ../../../targets/sparc64/opmatch.def:520:1-44
 */
static void fmovda_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 8U /* BA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqa defined at ../../../targets/sparc64/opmatch.def:521:1-44
 */
static void fmovqa_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 8U /* BA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsn defined at ../../../targets/sparc64/opmatch.def:522:1-44
 */
static void fmovsn_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 0U /* BN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdn defined at ../../../targets/sparc64/opmatch.def:523:1-44
 */
static void fmovdn_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 0U /* BN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqn defined at ../../../targets/sparc64/opmatch.def:524:1-44
 */
static void fmovqn_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 0U /* BN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsne defined at ../../../targets/sparc64/opmatch.def:525:1-46
 */
static void fmovsne_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 9U /* BNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdne defined at ../../../targets/sparc64/opmatch.def:526:1-46
 */
static void fmovdne_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 9U /* BNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqne defined at ../../../targets/sparc64/opmatch.def:527:1-46
 */
static void fmovqne_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 9U /* BNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovse defined at ../../../targets/sparc64/opmatch.def:528:1-44
 */
static void fmovse_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 1U /* BE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovde defined at ../../../targets/sparc64/opmatch.def:529:1-44
 */
static void fmovde_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 1U /* BE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqe defined at ../../../targets/sparc64/opmatch.def:530:1-44
 */
static void fmovqe_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 1U /* BE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsg defined at ../../../targets/sparc64/opmatch.def:531:1-44
 */
static void fmovsg_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 10U /* BG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdg defined at ../../../targets/sparc64/opmatch.def:532:1-44
 */
static void fmovdg_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 10U /* BG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqg defined at ../../../targets/sparc64/opmatch.def:533:1-44
 */
static void fmovqg_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 10U /* BG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsle defined at ../../../targets/sparc64/opmatch.def:534:1-46
 */
static void fmovsle_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 2U /* BLE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdle defined at ../../../targets/sparc64/opmatch.def:535:1-46
 */
static void fmovdle_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 2U /* BLE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqle defined at ../../../targets/sparc64/opmatch.def:536:1-46
 */
static void fmovqle_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 2U /* BLE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsge defined at ../../../targets/sparc64/opmatch.def:537:1-46
 */
static void fmovsge_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 11U /* BGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdge defined at ../../../targets/sparc64/opmatch.def:538:1-46
 */
static void fmovdge_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 11U /* BGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqge defined at ../../../targets/sparc64/opmatch.def:539:1-46
 */
static void fmovqge_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 11U /* BGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsl defined at ../../../targets/sparc64/opmatch.def:540:1-44
 */
static void fmovsl_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 3U /* BL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdl defined at ../../../targets/sparc64/opmatch.def:541:1-44
 */
static void fmovdl_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 3U /* BL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovql defined at ../../../targets/sparc64/opmatch.def:542:1-44
 */
static void fmovql_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 3U /* BL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsgu defined at ../../../targets/sparc64/opmatch.def:543:1-46
 */
static void fmovsgu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 12U /* BGU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdgu defined at ../../../targets/sparc64/opmatch.def:544:1-46
 */
static void fmovdgu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 12U /* BGU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqgu defined at ../../../targets/sparc64/opmatch.def:545:1-46
 */
static void fmovqgu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 12U /* BGU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsleu defined at ../../../targets/sparc64/opmatch.def:546:1-47
 */
static void fmovsleu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 4U /* BLEU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdleu defined at ../../../targets/sparc64/opmatch.def:547:1-47
 */
static void fmovdleu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 4U /* BLEU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqleu defined at ../../../targets/sparc64/opmatch.def:548:1-47
 */
static void fmovqleu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 4U /* BLEU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovscc defined at ../../../targets/sparc64/opmatch.def:549:1-46
 */
static void fmovscc_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 13U /* BCC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdcc defined at ../../../targets/sparc64/opmatch.def:550:1-46
 */
static void fmovdcc_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 13U /* BCC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqcc defined at ../../../targets/sparc64/opmatch.def:551:1-46
 */
static void fmovqcc_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 13U /* BCC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovscs defined at ../../../targets/sparc64/opmatch.def:552:1-46
 */
static void fmovscs_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 5U /* BCS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdcs defined at ../../../targets/sparc64/opmatch.def:553:1-46
 */
static void fmovdcs_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 5U /* BCS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqcs defined at ../../../targets/sparc64/opmatch.def:554:1-46
 */
static void fmovqcs_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 5U /* BCS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovspos defined at ../../../targets/sparc64/opmatch.def:555:1-47
 */
static void fmovspos_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 14U /* BPOS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdpos defined at ../../../targets/sparc64/opmatch.def:556:1-47
 */
static void fmovdpos_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 14U /* BPOS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqpos defined at ../../../targets/sparc64/opmatch.def:557:1-47
 */
static void fmovqpos_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 14U /* BPOS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsneg defined at ../../../targets/sparc64/opmatch.def:558:1-47
 */
static void fmovsneg_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 6U /* BNEG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdneg defined at ../../../targets/sparc64/opmatch.def:559:1-47
 */
static void fmovdneg_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 6U /* BNEG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqneg defined at ../../../targets/sparc64/opmatch.def:560:1-47
 */
static void fmovqneg_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 6U /* BNEG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsvc defined at ../../../targets/sparc64/opmatch.def:561:1-46
 */
static void fmovsvc_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 15U /* BVC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdvc defined at ../../../targets/sparc64/opmatch.def:562:1-46
 */
static void fmovdvc_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 15U /* BVC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqvc defined at ../../../targets/sparc64/opmatch.def:563:1-46
 */
static void fmovqvc_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 15U /* BVC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsvs defined at ../../../targets/sparc64/opmatch.def:564:1-46
 */
static void fmovsvs_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 7U /* BVS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdvs defined at ../../../targets/sparc64/opmatch.def:565:1-46
 */
static void fmovdvs_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 7U /* BVS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqvs defined at ../../../targets/sparc64/opmatch.def:566:1-46
 */
static void fmovqvs_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 7U /* BVS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsnz defined at ../../../targets/sparc64/opmatch.def:568:1-46
 */
static void fmovsnz_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 9U /* BNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdnz defined at ../../../targets/sparc64/opmatch.def:569:1-46
 */
static void fmovdnz_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 9U /* BNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqnz defined at ../../../targets/sparc64/opmatch.def:570:1-46
 */
static void fmovqnz_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 9U /* BNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsz defined at ../../../targets/sparc64/opmatch.def:571:1-44
 */
static void fmovsz_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 1U /* BE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdz defined at ../../../targets/sparc64/opmatch.def:572:1-44
 */
static void fmovdz_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 1U /* BE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqz defined at ../../../targets/sparc64/opmatch.def:573:1-44
 */
static void fmovqz_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 1U /* BE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsgeu defined at ../../../targets/sparc64/opmatch.def:574:1-46
 */
static void fmovsgeu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 13U /* BCC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdgeu defined at ../../../targets/sparc64/opmatch.def:575:1-46
 */
static void fmovdgeu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 13U /* BCC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqgeu defined at ../../../targets/sparc64/opmatch.def:576:1-46
 */
static void fmovqgeu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 13U /* BCC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovslu defined at ../../../targets/sparc64/opmatch.def:577:1-46
 */
static void fmovslu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 1U /* FMOVScc */, 5U /* BCS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdlu defined at ../../../targets/sparc64/opmatch.def:578:1-46
 */
static void fmovdlu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 2U /* FMOVDcc */, 5U /* BCS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqlu defined at ../../../targets/sparc64/opmatch.def:579:1-46
 */
static void fmovqlu_e17e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e17e14e14(line, 3U /* FMOVQcc */, 5U /* BCS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsa defined at ../../../targets/sparc64/opmatch.def:581:1-45
 */
static void fmovsa_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 8U /* FBA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovda defined at ../../../targets/sparc64/opmatch.def:582:1-45
 */
static void fmovda_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 8U /* FBA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqa defined at ../../../targets/sparc64/opmatch.def:583:1-45
 */
static void fmovqa_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 8U /* FBA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsn defined at ../../../targets/sparc64/opmatch.def:584:1-45
 */
static void fmovsn_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 0U /* FBN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdn defined at ../../../targets/sparc64/opmatch.def:585:1-45
 */
static void fmovdn_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 0U /* FBN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqn defined at ../../../targets/sparc64/opmatch.def:586:1-45
 */
static void fmovqn_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 0U /* FBN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsu defined at ../../../targets/sparc64/opmatch.def:587:1-45
 */
static void fmovsu_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 7U /* FBU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdu defined at ../../../targets/sparc64/opmatch.def:588:1-45
 */
static void fmovdu_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 7U /* FBU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqu defined at ../../../targets/sparc64/opmatch.def:589:1-45
 */
static void fmovqu_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 7U /* FBU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsg defined at ../../../targets/sparc64/opmatch.def:590:1-45
 */
static void fmovsg_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 6U /* FBG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdg defined at ../../../targets/sparc64/opmatch.def:591:1-45
 */
static void fmovdg_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 6U /* FBG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqg defined at ../../../targets/sparc64/opmatch.def:592:1-45
 */
static void fmovqg_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 6U /* FBG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsug defined at ../../../targets/sparc64/opmatch.def:593:1-47
 */
static void fmovsug_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 5U /* FBUG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdug defined at ../../../targets/sparc64/opmatch.def:594:1-47
 */
static void fmovdug_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 5U /* FBUG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqug defined at ../../../targets/sparc64/opmatch.def:595:1-47
 */
static void fmovqug_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 5U /* FBUG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsl defined at ../../../targets/sparc64/opmatch.def:596:1-45
 */
static void fmovsl_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 4U /* FBL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdl defined at ../../../targets/sparc64/opmatch.def:597:1-45
 */
static void fmovdl_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 4U /* FBL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovql defined at ../../../targets/sparc64/opmatch.def:598:1-45
 */
static void fmovql_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 4U /* FBL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsul defined at ../../../targets/sparc64/opmatch.def:599:1-47
 */
static void fmovsul_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 3U /* FBUL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdul defined at ../../../targets/sparc64/opmatch.def:600:1-47
 */
static void fmovdul_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 3U /* FBUL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqul defined at ../../../targets/sparc64/opmatch.def:601:1-47
 */
static void fmovqul_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 3U /* FBUL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovslg defined at ../../../targets/sparc64/opmatch.def:602:1-47
 */
static void fmovslg_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 2U /* FBLG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdlg defined at ../../../targets/sparc64/opmatch.def:603:1-47
 */
static void fmovdlg_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 2U /* FBLG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqlg defined at ../../../targets/sparc64/opmatch.def:604:1-47
 */
static void fmovqlg_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 2U /* FBLG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsne defined at ../../../targets/sparc64/opmatch.def:605:1-47
 */
static void fmovsne_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 1U /* FBNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdne defined at ../../../targets/sparc64/opmatch.def:606:1-47
 */
static void fmovdne_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 1U /* FBNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqne defined at ../../../targets/sparc64/opmatch.def:607:1-47
 */
static void fmovqne_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 1U /* FBNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovse defined at ../../../targets/sparc64/opmatch.def:608:1-45
 */
static void fmovse_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 9U /* FBE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovde defined at ../../../targets/sparc64/opmatch.def:609:1-45
 */
static void fmovde_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 9U /* FBE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqe defined at ../../../targets/sparc64/opmatch.def:610:1-45
 */
static void fmovqe_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 9U /* FBE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsue defined at ../../../targets/sparc64/opmatch.def:611:1-47
 */
static void fmovsue_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 10U /* FBUE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdue defined at ../../../targets/sparc64/opmatch.def:612:1-47
 */
static void fmovdue_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 10U /* FBUE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovque defined at ../../../targets/sparc64/opmatch.def:613:1-47
 */
static void fmovque_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 10U /* FBUE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsge defined at ../../../targets/sparc64/opmatch.def:614:1-47
 */
static void fmovsge_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 11U /* FBGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdge defined at ../../../targets/sparc64/opmatch.def:615:1-47
 */
static void fmovdge_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 11U /* FBGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqge defined at ../../../targets/sparc64/opmatch.def:616:1-47
 */
static void fmovqge_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 11U /* FBGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsuge defined at ../../../targets/sparc64/opmatch.def:617:1-48
 */
static void fmovsuge_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 12U /* FBUGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovduge defined at ../../../targets/sparc64/opmatch.def:618:1-48
 */
static void fmovduge_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 12U /* FBUGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovquge defined at ../../../targets/sparc64/opmatch.def:619:1-48
 */
static void fmovquge_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 12U /* FBUGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsle defined at ../../../targets/sparc64/opmatch.def:620:1-47
 */
static void fmovsle_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 13U /* FBLE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdle defined at ../../../targets/sparc64/opmatch.def:621:1-47
 */
static void fmovdle_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 13U /* FBLE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqle defined at ../../../targets/sparc64/opmatch.def:622:1-47
 */
static void fmovqle_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 13U /* FBLE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsule defined at ../../../targets/sparc64/opmatch.def:623:1-48
 */
static void fmovsule_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 14U /* FBULE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdule defined at ../../../targets/sparc64/opmatch.def:624:1-48
 */
static void fmovdule_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 14U /* FBULE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqule defined at ../../../targets/sparc64/opmatch.def:625:1-48
 */
static void fmovqule_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 14U /* FBULE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovso defined at ../../../targets/sparc64/opmatch.def:626:1-45
 */
static void fmovso_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 15U /* FBO */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdo defined at ../../../targets/sparc64/opmatch.def:627:1-45
 */
static void fmovdo_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 15U /* FBO */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqo defined at ../../../targets/sparc64/opmatch.def:628:1-45
 */
static void fmovqo_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 15U /* FBO */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsnz defined at ../../../targets/sparc64/opmatch.def:630:1-47
 */
static void fmovsnz_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 1U /* FBNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdnz defined at ../../../targets/sparc64/opmatch.def:631:1-47
 */
static void fmovdnz_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 1U /* FBNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqnz defined at ../../../targets/sparc64/opmatch.def:632:1-47
 */
static void fmovqnz_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 1U /* FBNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovsz defined at ../../../targets/sparc64/opmatch.def:633:1-45
 */
static void fmovsz_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 1U /* FMOVScc */, 9U /* FBE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovdz defined at ../../../targets/sparc64/opmatch.def:634:1-45
 */
static void fmovdz_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 2U /* FMOVDcc */, 9U /* FBE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovqz defined at ../../../targets/sparc64/opmatch.def:635:1-45
 */
static void fmovqz_e13e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e13e14e14(line, 3U /* FMOVQcc */, 9U /* FBE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrsz defined at ../../../targets/sparc64/opmatch.def:637:1-46
 */
static void fmovrsz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 5U /* FMOVSrc */, 1U /* BRZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrdz defined at ../../../targets/sparc64/opmatch.def:638:1-46
 */
static void fmovrdz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 6U /* FMOVDrc */, 1U /* BRZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrqz defined at ../../../targets/sparc64/opmatch.def:639:1-46
 */
static void fmovrqz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 7U /* FMOVQrc */, 1U /* BRZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrslez defined at ../../../targets/sparc64/opmatch.def:640:1-49
 */
static void fmovrslez_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 5U /* FMOVSrc */, 2U /* BRLEZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrdlez defined at ../../../targets/sparc64/opmatch.def:641:1-49
 */
static void fmovrdlez_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 6U /* FMOVDrc */, 2U /* BRLEZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrqlez defined at ../../../targets/sparc64/opmatch.def:642:1-49
 */
static void fmovrqlez_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 7U /* FMOVQrc */, 2U /* BRLEZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrslz defined at ../../../targets/sparc64/opmatch.def:643:1-47
 */
static void fmovrslz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 5U /* FMOVSrc */, 3U /* BRLZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrdlz defined at ../../../targets/sparc64/opmatch.def:644:1-47
 */
static void fmovrdlz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 6U /* FMOVDrc */, 3U /* BRLZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrqlz defined at ../../../targets/sparc64/opmatch.def:645:1-47
 */
static void fmovrqlz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 7U /* FMOVQrc */, 3U /* BRLZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrsnz defined at ../../../targets/sparc64/opmatch.def:646:1-47
 */
static void fmovrsnz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 5U /* FMOVSrc */, 5U /* BRNZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrdnz defined at ../../../targets/sparc64/opmatch.def:647:1-47
 */
static void fmovrdnz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 6U /* FMOVDrc */, 5U /* BRNZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrqnz defined at ../../../targets/sparc64/opmatch.def:648:1-47
 */
static void fmovrqnz_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 7U /* FMOVQrc */, 5U /* BRNZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrsg defined at ../../../targets/sparc64/opmatch.def:649:1-47
 */
static void fmovrsg_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 5U /* FMOVSrc */, 6U /* BRGZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrdg defined at ../../../targets/sparc64/opmatch.def:650:1-47
 */
static void fmovrdg_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 6U /* FMOVDrc */, 6U /* BRGZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrqg defined at ../../../targets/sparc64/opmatch.def:651:1-47
 */
static void fmovrqg_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 7U /* FMOVQrc */, 6U /* BRGZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrsgez defined at ../../../targets/sparc64/opmatch.def:652:1-49
 */
static void fmovrsgez_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 5U /* FMOVSrc */, 7U /* BRGEZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrdgez defined at ../../../targets/sparc64/opmatch.def:653:1-49
 */
static void fmovrdgez_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 6U /* FMOVDrc */, 7U /* BRGEZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrqgez defined at ../../../targets/sparc64/opmatch.def:654:1-49
 */
static void fmovrqgez_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 7U /* FMOVQrc */, 7U /* BRGEZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrse defined at ../../../targets/sparc64/opmatch.def:656:1-46
 */
static void fmovrse_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 5U /* FMOVSrc */, 1U /* BRZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrde defined at ../../../targets/sparc64/opmatch.def:657:1-46
 */
static void fmovrde_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 6U /* FMOVDrc */, 1U /* BRZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrqe defined at ../../../targets/sparc64/opmatch.def:658:1-46
 */
static void fmovrqe_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 7U /* FMOVQrc */, 1U /* BRZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrsne defined at ../../../targets/sparc64/opmatch.def:659:1-47
 */
static void fmovrsne_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 5U /* FMOVSrc */, 5U /* BRNZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrdne defined at ../../../targets/sparc64/opmatch.def:660:1-47
 */
static void fmovrdne_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 6U /* FMOVDrc */, 5U /* BRNZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro fmovrqne defined at ../../../targets/sparc64/opmatch.def:661:1-47
 */
static void fmovrqne_e16e14e14(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      fmov_e16e14e14(line, 7U /* FMOVQrc */, 5U /* BRNZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro mova defined at ../../../targets/sparc64/opmatch.def:663:1-33
 */
static void mova_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 8U /* BA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro mova defined at ../../../targets/sparc64/opmatch.def:664:1-36
 */
static void mova_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 8U /* BA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movn defined at ../../../targets/sparc64/opmatch.def:665:1-33
 */
static void movn_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 0U /* BN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movn defined at ../../../targets/sparc64/opmatch.def:666:1-36
 */
static void movn_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 0U /* BN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movne defined at ../../../targets/sparc64/opmatch.def:667:1-35
 */
static void movne_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 9U /* BNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movne defined at ../../../targets/sparc64/opmatch.def:668:1-38
 */
static void movne_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 9U /* BNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro move defined at ../../../targets/sparc64/opmatch.def:669:1-33
 */
static void move_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 1U /* BE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro move defined at ../../../targets/sparc64/opmatch.def:670:1-36
 */
static void move_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 1U /* BE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movg defined at ../../../targets/sparc64/opmatch.def:671:1-33
 */
static void movg_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 10U /* BG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movg defined at ../../../targets/sparc64/opmatch.def:672:1-36
 */
static void movg_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 10U /* BG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movle defined at ../../../targets/sparc64/opmatch.def:673:1-35
 */
static void movle_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 2U /* BLE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movle defined at ../../../targets/sparc64/opmatch.def:674:1-38
 */
static void movle_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 2U /* BLE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movge defined at ../../../targets/sparc64/opmatch.def:675:1-35
 */
static void movge_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 11U /* BGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movge defined at ../../../targets/sparc64/opmatch.def:676:1-38
 */
static void movge_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 11U /* BGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movl defined at ../../../targets/sparc64/opmatch.def:677:1-33
 */
static void movl_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 3U /* BL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movl defined at ../../../targets/sparc64/opmatch.def:678:1-36
 */
static void movl_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 3U /* BL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movgu defined at ../../../targets/sparc64/opmatch.def:679:1-35
 */
static void movgu_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 12U /* BGU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movgu defined at ../../../targets/sparc64/opmatch.def:680:1-38
 */
static void movgu_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 12U /* BGU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movleu defined at ../../../targets/sparc64/opmatch.def:681:1-37
 */
static void movleu_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 4U /* BLEU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movleu defined at ../../../targets/sparc64/opmatch.def:682:1-40
 */
static void movleu_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 4U /* BLEU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movcc defined at ../../../targets/sparc64/opmatch.def:683:1-35
 */
static void movcc_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 13U /* BCC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movcc defined at ../../../targets/sparc64/opmatch.def:684:1-38
 */
static void movcc_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 13U /* BCC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movcs defined at ../../../targets/sparc64/opmatch.def:685:1-35
 */
static void movcs_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 5U /* BCS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movcs defined at ../../../targets/sparc64/opmatch.def:686:1-38
 */
static void movcs_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 5U /* BCS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movpos defined at ../../../targets/sparc64/opmatch.def:687:1-37
 */
static void movpos_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 14U /* BPOS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movpos defined at ../../../targets/sparc64/opmatch.def:688:1-40
 */
static void movpos_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 14U /* BPOS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movneg defined at ../../../targets/sparc64/opmatch.def:689:1-37
 */
static void movneg_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 6U /* BNEG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movneg defined at ../../../targets/sparc64/opmatch.def:690:1-40
 */
static void movneg_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 6U /* BNEG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movvc defined at ../../../targets/sparc64/opmatch.def:691:1-35
 */
static void movvc_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 15U /* BVC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movvc defined at ../../../targets/sparc64/opmatch.def:692:1-38
 */
static void movvc_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 15U /* BVC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movvs defined at ../../../targets/sparc64/opmatch.def:693:1-35
 */
static void movvs_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 7U /* BVS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movvs defined at ../../../targets/sparc64/opmatch.def:694:1-38
 */
static void movvs_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 7U /* BVS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movnz defined at ../../../targets/sparc64/opmatch.def:696:1-35
 */
static void movnz_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 9U /* BNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movnz defined at ../../../targets/sparc64/opmatch.def:697:1-38
 */
static void movnz_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 9U /* BNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movz defined at ../../../targets/sparc64/opmatch.def:698:1-33
 */
static void movz_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 1U /* BE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movz defined at ../../../targets/sparc64/opmatch.def:699:1-36
 */
static void movz_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 1U /* BE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movgeu defined at ../../../targets/sparc64/opmatch.def:700:1-36
 */
static void movgeu_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 13U /* BCC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movgeu defined at ../../../targets/sparc64/opmatch.def:701:1-39
 */
static void movgeu_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 13U /* BCC */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movlu defined at ../../../targets/sparc64/opmatch.def:702:1-35
 */
static void movlu_e17e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17e16e16(line, 5U /* BCS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movlu defined at ../../../targets/sparc64/opmatch.def:703:1-38
 */
static void movlu_e17i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e17i11e16(line, 5U /* BCS */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro mova defined at ../../../targets/sparc64/opmatch.def:705:1-34
 */
static void mova_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 8U /* FBA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro mova defined at ../../../targets/sparc64/opmatch.def:706:1-37
 */
static void mova_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 8U /* FBA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movn defined at ../../../targets/sparc64/opmatch.def:707:1-34
 */
static void movn_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 0U /* FBN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movn defined at ../../../targets/sparc64/opmatch.def:708:1-37
 */
static void movn_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 0U /* FBN */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movu defined at ../../../targets/sparc64/opmatch.def:709:1-34
 */
static void movu_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 7U /* FBU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movu defined at ../../../targets/sparc64/opmatch.def:710:1-37
 */
static void movu_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 7U /* FBU */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movg defined at ../../../targets/sparc64/opmatch.def:711:1-34
 */
static void movg_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 6U /* FBG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movg defined at ../../../targets/sparc64/opmatch.def:712:1-37
 */
static void movg_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 6U /* FBG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movug defined at ../../../targets/sparc64/opmatch.def:713:1-36
 */
static void movug_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 5U /* FBUG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movug defined at ../../../targets/sparc64/opmatch.def:714:1-39
 */
static void movug_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 5U /* FBUG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movl defined at ../../../targets/sparc64/opmatch.def:715:1-34
 */
static void movl_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 4U /* FBL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movl defined at ../../../targets/sparc64/opmatch.def:716:1-37
 */
static void movl_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 4U /* FBL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movul defined at ../../../targets/sparc64/opmatch.def:717:1-36
 */
static void movul_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 3U /* FBUL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movul defined at ../../../targets/sparc64/opmatch.def:718:1-39
 */
static void movul_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 3U /* FBUL */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movlg defined at ../../../targets/sparc64/opmatch.def:719:1-36
 */
static void movlg_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 2U /* FBLG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movlg defined at ../../../targets/sparc64/opmatch.def:720:1-39
 */
static void movlg_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 2U /* FBLG */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movne defined at ../../../targets/sparc64/opmatch.def:721:1-36
 */
static void movne_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 1U /* FBNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movne defined at ../../../targets/sparc64/opmatch.def:722:1-39
 */
static void movne_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 1U /* FBNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro move defined at ../../../targets/sparc64/opmatch.def:723:1-34
 */
static void move_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 9U /* FBE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro move defined at ../../../targets/sparc64/opmatch.def:724:1-37
 */
static void move_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 9U /* FBE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movue defined at ../../../targets/sparc64/opmatch.def:725:1-36
 */
static void movue_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 10U /* FBUE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movue defined at ../../../targets/sparc64/opmatch.def:726:1-39
 */
static void movue_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 10U /* FBUE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movge defined at ../../../targets/sparc64/opmatch.def:727:1-36
 */
static void movge_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 11U /* FBGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movge defined at ../../../targets/sparc64/opmatch.def:728:1-39
 */
static void movge_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 11U /* FBGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movuge defined at ../../../targets/sparc64/opmatch.def:729:1-38
 */
static void movuge_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 12U /* FBUGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movuge defined at ../../../targets/sparc64/opmatch.def:730:1-41
 */
static void movuge_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 12U /* FBUGE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movle defined at ../../../targets/sparc64/opmatch.def:731:1-36
 */
static void movle_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 13U /* FBLE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movle defined at ../../../targets/sparc64/opmatch.def:732:1-39
 */
static void movle_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 13U /* FBLE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movule defined at ../../../targets/sparc64/opmatch.def:733:1-38
 */
static void movule_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 14U /* FBULE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movule defined at ../../../targets/sparc64/opmatch.def:734:1-41
 */
static void movule_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 14U /* FBULE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movo defined at ../../../targets/sparc64/opmatch.def:735:1-34
 */
static void movo_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 15U /* FBO */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movo defined at ../../../targets/sparc64/opmatch.def:736:1-37
 */
static void movo_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 15U /* FBO */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movnz defined at ../../../targets/sparc64/opmatch.def:738:1-36
 */
static void movnz_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 1U /* FBNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movnz defined at ../../../targets/sparc64/opmatch.def:739:1-39
 */
static void movnz_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 1U /* FBNE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movz defined at ../../../targets/sparc64/opmatch.def:740:1-34
 */
static void movz_e13e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13e16e16(line, 9U /* FBE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movz defined at ../../../targets/sparc64/opmatch.def:741:1-37
 */
static void movz_e13i11e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movcc__e13i11e16(line, 9U /* FBE */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrz defined at ../../../targets/sparc64/opmatch.def:743:1-33
 */
static void movrz_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16e16e16(line, 1U /* BRZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrz defined at ../../../targets/sparc64/opmatch.def:744:1-36
 */
static void movrz_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16i10e16(line, 1U /* BRZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrlez defined at ../../../targets/sparc64/opmatch.def:745:1-37
 */
static void movrlez_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16e16e16(line, 2U /* BRLEZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrlez defined at ../../../targets/sparc64/opmatch.def:746:1-39
 */
static void movrlez_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16i10e16(line, 2U /* BRLEZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrlz defined at ../../../targets/sparc64/opmatch.def:747:1-35
 */
static void movrlz_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16e16e16(line, 3U /* BRLZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrlz defined at ../../../targets/sparc64/opmatch.def:748:1-38
 */
static void movrlz_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16i10e16(line, 3U /* BRLZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrnz defined at ../../../targets/sparc64/opmatch.def:749:1-35
 */
static void movrnz_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16e16e16(line, 5U /* BRNZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrnz defined at ../../../targets/sparc64/opmatch.def:750:1-38
 */
static void movrnz_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16i10e16(line, 5U /* BRNZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrgz defined at ../../../targets/sparc64/opmatch.def:751:1-35
 */
static void movrgz_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16e16e16(line, 6U /* BRGZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrgz defined at ../../../targets/sparc64/opmatch.def:752:1-38
 */
static void movrgz_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16i10e16(line, 6U /* BRGZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrgez defined at ../../../targets/sparc64/opmatch.def:753:1-37
 */
static void movrgez_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16e16e16(line, 7U /* BRGEZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrgez defined at ../../../targets/sparc64/opmatch.def:754:1-39
 */
static void movrgez_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16i10e16(line, 7U /* BRGEZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movre defined at ../../../targets/sparc64/opmatch.def:756:1-33
 */
static void movre_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16e16e16(line, 1U /* BRZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movre defined at ../../../targets/sparc64/opmatch.def:757:1-36
 */
static void movre_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16i10e16(line, 1U /* BRZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrne defined at ../../../targets/sparc64/opmatch.def:758:1-35
 */
static void movrne_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16e16e16(line, 5U /* BRNZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro movrne defined at ../../../targets/sparc64/opmatch.def:759:1-38
 */
static void movrne_e16i10e16(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      movr_e16i10e16(line, 5U /* BRNZ */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro casa defined at ../../../targets/sparc64/opmatch.def:773:1-42
 */
static void casa_braddr_r_asie16e16(int line, struct compound_braddr_r_asi * var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      casa__braddr_r_asie16e16(line, 60U /* CASA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro casxa defined at ../../../targets/sparc64/opmatch.def:775:1-44
 */
static void casxa_braddr_r_asie16e16(int line, struct compound_braddr_r_asi * var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      casa__braddr_r_asie16e16(line, 62U /* CASXA */, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro ld defined at ../../../targets/sparc64/opmatch.def:786:1-31
 */
static void ld_braddr_rre14(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_rre14(line, 32U /* LDF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ld defined at ../../../targets/sparc64/opmatch.def:787:1-31
 */
static void ld_braddr_rie14(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_rie14(line, 32U /* LDF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ld defined at ../../../targets/sparc64/opmatch.def:788:1-31
 */
static void ld_braddr_rxe14(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_rxe14(line, 32U /* LDF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldd defined at ../../../targets/sparc64/opmatch.def:789:1-33
 */
static void ldd_braddr_rre14(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_rre14(line, 35U /* LDDF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldd defined at ../../../targets/sparc64/opmatch.def:790:1-33
 */
static void ldd_braddr_rie14(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_rie14(line, 35U /* LDDF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldd defined at ../../../targets/sparc64/opmatch.def:791:1-33
 */
static void ldd_braddr_rxe14(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_rxe14(line, 35U /* LDDF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldq defined at ../../../targets/sparc64/opmatch.def:792:1-33
 */
static void ldq_braddr_rre14(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_rre14(line, 34U /* LDQF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldq defined at ../../../targets/sparc64/opmatch.def:793:1-33
 */
static void ldq_braddr_rie14(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_rie14(line, 34U /* LDQF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldq defined at ../../../targets/sparc64/opmatch.def:794:1-33
 */
static void ldq_braddr_rxe14(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_rxe14(line, 34U /* LDQF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ld defined at ../../../targets/sparc64/opmatch.def:795:1-27
 */
static void ld_braddr_rre15(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldfsr_braddr_rre15(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ld defined at ../../../targets/sparc64/opmatch.def:796:1-27
 */
static void ld_braddr_rie15(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldfsr_braddr_rie15(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ld defined at ../../../targets/sparc64/opmatch.def:797:1-27
 */
static void ld_braddr_rxe15(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldfsr_braddr_rxe15(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldx defined at ../../../targets/sparc64/opmatch.def:798:1-29
 */
static void ldx_braddr_rre15(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldxfsr_braddr_rre15(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldx defined at ../../../targets/sparc64/opmatch.def:799:1-29
 */
static void ldx_braddr_rie15(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldxfsr_braddr_rie15(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldx defined at ../../../targets/sparc64/opmatch.def:800:1-29
 */
static void ldx_braddr_rxe15(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldxfsr_braddr_rxe15(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lda defined at ../../../targets/sparc64/opmatch.def:802:1-39
 */
static void lda_braddr_rr_immasie14(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_rr_immasie14(line, 48U /* LDFA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lda defined at ../../../targets/sparc64/opmatch.def:803:1-37
 */
static void lda_braddr_ri_asie14(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_ri_asie14(line, 48U /* LDFA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldda defined at ../../../targets/sparc64/opmatch.def:804:1-41
 */
static void ldda_braddr_rr_immasie14(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_rr_immasie14(line, 51U /* LDDFA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldda defined at ../../../targets/sparc64/opmatch.def:805:1-38
 */
static void ldda_braddr_ri_asie14(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_ri_asie14(line, 51U /* LDDFA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldqa defined at ../../../targets/sparc64/opmatch.def:806:1-41
 */
static void ldqa_braddr_rr_immasie14(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_rr_immasie14(line, 50U /* LDQFA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldqa defined at ../../../targets/sparc64/opmatch.def:807:1-38
 */
static void ldqa_braddr_ri_asie14(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldf_braddr_ri_asie14(line, 50U /* LDQFA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsb defined at ../../../targets/sparc64/opmatch.def:809:1-34
 */
static void ldsb_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rre16(line, 9U /* LDSB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsb defined at ../../../targets/sparc64/opmatch.def:810:1-34
 */
static void ldsb_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rie16(line, 9U /* LDSB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsb defined at ../../../targets/sparc64/opmatch.def:811:1-34
 */
static void ldsb_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rxe16(line, 9U /* LDSB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsh defined at ../../../targets/sparc64/opmatch.def:812:1-34
 */
static void ldsh_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rre16(line, 10U /* LDSH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsh defined at ../../../targets/sparc64/opmatch.def:813:1-34
 */
static void ldsh_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rie16(line, 10U /* LDSH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsh defined at ../../../targets/sparc64/opmatch.def:814:1-34
 */
static void ldsh_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rxe16(line, 10U /* LDSH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsw defined at ../../../targets/sparc64/opmatch.def:815:1-34
 */
static void ldsw_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rre16(line, 8U /* LDSW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsw defined at ../../../targets/sparc64/opmatch.def:816:1-34
 */
static void ldsw_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rie16(line, 8U /* LDSW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsw defined at ../../../targets/sparc64/opmatch.def:817:1-34
 */
static void ldsw_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rxe16(line, 8U /* LDSW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldub defined at ../../../targets/sparc64/opmatch.def:818:1-34
 */
static void ldub_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rre16(line, 1U /* LDUB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldub defined at ../../../targets/sparc64/opmatch.def:819:1-34
 */
static void ldub_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rie16(line, 1U /* LDUB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldub defined at ../../../targets/sparc64/opmatch.def:820:1-34
 */
static void ldub_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rxe16(line, 1U /* LDUB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lduh defined at ../../../targets/sparc64/opmatch.def:821:1-34
 */
static void lduh_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rre16(line, 2U /* LDUH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lduh defined at ../../../targets/sparc64/opmatch.def:822:1-34
 */
static void lduh_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rie16(line, 2U /* LDUH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lduh defined at ../../../targets/sparc64/opmatch.def:823:1-34
 */
static void lduh_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rxe16(line, 2U /* LDUH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lduw defined at ../../../targets/sparc64/opmatch.def:824:1-34
 */
static void lduw_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rre16(line, 0U /* LDUW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lduw defined at ../../../targets/sparc64/opmatch.def:825:1-34
 */
static void lduw_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rie16(line, 0U /* LDUW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lduw defined at ../../../targets/sparc64/opmatch.def:826:1-34
 */
static void lduw_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rxe16(line, 0U /* LDUW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldx defined at ../../../targets/sparc64/opmatch.def:827:1-32
 */
static void ldx_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rre16(line, 11U /* LDX */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldx defined at ../../../targets/sparc64/opmatch.def:828:1-32
 */
static void ldx_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rie16(line, 11U /* LDX */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldx defined at ../../../targets/sparc64/opmatch.def:829:1-32
 */
static void ldx_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rxe16(line, 11U /* LDX */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldd defined at ../../../targets/sparc64/opmatch.def:831:1-32
 */
static void ldd_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rre16(line, 3U /* LDD */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldd defined at ../../../targets/sparc64/opmatch.def:832:1-32
 */
static void ldd_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rie16(line, 3U /* LDD */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldd defined at ../../../targets/sparc64/opmatch.def:833:1-32
 */
static void ldd_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rxe16(line, 3U /* LDD */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ld defined at ../../../targets/sparc64/opmatch.def:835:1-32
 */
static void ld_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rre16(line, 0U /* LDUW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ld defined at ../../../targets/sparc64/opmatch.def:836:1-32
 */
static void ld_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rie16(line, 0U /* LDUW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ld defined at ../../../targets/sparc64/opmatch.def:837:1-32
 */
static void ld_braddr_rxe16(int line, struct compound_braddr_rx * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rxe16(line, 0U /* LDUW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsba defined at ../../../targets/sparc64/opmatch.def:839:1-42
 */
static void ldsba_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rr_immasie16(line, 25U /* LDSBA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsba defined at ../../../targets/sparc64/opmatch.def:840:1-39
 */
static void ldsba_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_ri_asie16(line, 25U /* LDSBA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsha defined at ../../../targets/sparc64/opmatch.def:841:1-42
 */
static void ldsha_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rr_immasie16(line, 26U /* LDSHA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldsha defined at ../../../targets/sparc64/opmatch.def:842:1-39
 */
static void ldsha_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_ri_asie16(line, 26U /* LDSHA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldswa defined at ../../../targets/sparc64/opmatch.def:843:1-42
 */
static void ldswa_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rr_immasie16(line, 24U /* LDSWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldswa defined at ../../../targets/sparc64/opmatch.def:844:1-39
 */
static void ldswa_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_ri_asie16(line, 24U /* LDSWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lduba defined at ../../../targets/sparc64/opmatch.def:845:1-42
 */
static void lduba_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rr_immasie16(line, 17U /* LDUBA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lduba defined at ../../../targets/sparc64/opmatch.def:846:1-39
 */
static void lduba_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_ri_asie16(line, 17U /* LDUBA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lduha defined at ../../../targets/sparc64/opmatch.def:847:1-42
 */
static void lduha_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rr_immasie16(line, 18U /* LDUHA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lduha defined at ../../../targets/sparc64/opmatch.def:848:1-39
 */
static void lduha_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_ri_asie16(line, 18U /* LDUHA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lduwa defined at ../../../targets/sparc64/opmatch.def:849:1-42
 */
static void lduwa_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rr_immasie16(line, 16U /* LDUWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lduwa defined at ../../../targets/sparc64/opmatch.def:850:1-39
 */
static void lduwa_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_ri_asie16(line, 16U /* LDUWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldxa defined at ../../../targets/sparc64/opmatch.def:851:1-40
 */
static void ldxa_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rr_immasie16(line, 27U /* LDXA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldxa defined at ../../../targets/sparc64/opmatch.def:852:1-38
 */
static void ldxa_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_ri_asie16(line, 27U /* LDXA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldda defined at ../../../targets/sparc64/opmatch.def:854:1-40
 */
static void ldda_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rr_immasie16(line, 19U /* LDDA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldda defined at ../../../targets/sparc64/opmatch.def:855:1-38
 */
static void ldda_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_ri_asie16(line, 19U /* LDDA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lda defined at ../../../targets/sparc64/opmatch.def:857:1-40
 */
static void lda_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_rr_immasie16(line, 16U /* LDUWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro lda defined at ../../../targets/sparc64/opmatch.def:858:1-38
 */
static void lda_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      load_braddr_ri_asie16(line, 16U /* LDUWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro st defined at ../../../targets/sparc64/opmatch.def:860:1-31
 */
static void st_e14braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      stf_e14braddr_rr(line, 36U /* STF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro st defined at ../../../targets/sparc64/opmatch.def:861:1-31
 */
static void st_e14braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      stf_e14braddr_ri(line, 36U /* STF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro st defined at ../../../targets/sparc64/opmatch.def:862:1-31
 */
static void st_e14braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      stf_e14braddr_rx(line, 36U /* STF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro std defined at ../../../targets/sparc64/opmatch.def:863:1-33
 */
static void std_e14braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      stf_e14braddr_rr(line, 39U /* STDF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro std defined at ../../../targets/sparc64/opmatch.def:864:1-33
 */
static void std_e14braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      stf_e14braddr_ri(line, 39U /* STDF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro std defined at ../../../targets/sparc64/opmatch.def:865:1-33
 */
static void std_e14braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      stf_e14braddr_rx(line, 39U /* STDF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stq defined at ../../../targets/sparc64/opmatch.def:866:1-33
 */
static void stq_e14braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      stf_e14braddr_rr(line, 38U /* STQF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stq defined at ../../../targets/sparc64/opmatch.def:867:1-33
 */
static void stq_e14braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      stf_e14braddr_ri(line, 38U /* STQF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stq defined at ../../../targets/sparc64/opmatch.def:868:1-33
 */
static void stq_e14braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      stf_e14braddr_rx(line, 38U /* STQF */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro st defined at ../../../targets/sparc64/opmatch.def:869:1-27
 */
static void st_e15braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      stfsr_e15braddr_rr(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro st defined at ../../../targets/sparc64/opmatch.def:870:1-27
 */
static void st_e15braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      stfsr_e15braddr_ri(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro st defined at ../../../targets/sparc64/opmatch.def:871:1-27
 */
static void st_e15braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      stfsr_e15braddr_rx(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stx defined at ../../../targets/sparc64/opmatch.def:872:1-29
 */
static void stx_e15braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      stxfsr_e15braddr_rr(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stx defined at ../../../targets/sparc64/opmatch.def:873:1-29
 */
static void stx_e15braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      stxfsr_e15braddr_ri(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stx defined at ../../../targets/sparc64/opmatch.def:874:1-29
 */
static void stx_e15braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      stxfsr_e15braddr_rx(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sta defined at ../../../targets/sparc64/opmatch.def:876:1-39
 */
static void sta_e14braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      stf_e14braddr_rr_immasi(line, 52U /* STFA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sta defined at ../../../targets/sparc64/opmatch.def:877:1-37
 */
static void sta_e14braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      stf_e14braddr_ri_asi(line, 52U /* STFA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stda defined at ../../../targets/sparc64/opmatch.def:878:1-41
 */
static void stda_e14braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      stf_e14braddr_rr_immasi(line, 55U /* STDFA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stda defined at ../../../targets/sparc64/opmatch.def:879:1-38
 */
static void stda_e14braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      stf_e14braddr_ri_asi(line, 55U /* STDFA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stqa defined at ../../../targets/sparc64/opmatch.def:880:1-41
 */
static void stqa_e14braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      stf_e14braddr_rr_immasi(line, 54U /* STQFA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stqa defined at ../../../targets/sparc64/opmatch.def:881:1-38
 */
static void stqa_e14braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      stf_e14braddr_ri_asi(line, 54U /* STQFA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stb defined at ../../../targets/sparc64/opmatch.def:883:1-33
 */
static void stb_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      store_e16braddr_rr(line, 5U /* STB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stb defined at ../../../targets/sparc64/opmatch.def:884:1-33
 */
static void stb_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      store_e16braddr_ri(line, 5U /* STB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stb defined at ../../../targets/sparc64/opmatch.def:885:1-33
 */
static void stb_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      store_e16braddr_rx(line, 5U /* STB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sth defined at ../../../targets/sparc64/opmatch.def:886:1-33
 */
static void sth_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      store_e16braddr_rr(line, 6U /* STH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sth defined at ../../../targets/sparc64/opmatch.def:887:1-33
 */
static void sth_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      store_e16braddr_ri(line, 6U /* STH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sth defined at ../../../targets/sparc64/opmatch.def:888:1-33
 */
static void sth_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      store_e16braddr_rx(line, 6U /* STH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stw defined at ../../../targets/sparc64/opmatch.def:889:1-33
 */
static void stw_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      store_e16braddr_rr(line, 4U /* STW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stw defined at ../../../targets/sparc64/opmatch.def:890:1-33
 */
static void stw_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      store_e16braddr_ri(line, 4U /* STW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stw defined at ../../../targets/sparc64/opmatch.def:891:1-33
 */
static void stw_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      store_e16braddr_rx(line, 4U /* STW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stx defined at ../../../targets/sparc64/opmatch.def:892:1-33
 */
static void stx_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      store_e16braddr_rr(line, 14U /* STX */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stx defined at ../../../targets/sparc64/opmatch.def:893:1-33
 */
static void stx_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      store_e16braddr_ri(line, 14U /* STX */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stx defined at ../../../targets/sparc64/opmatch.def:894:1-33
 */
static void stx_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      store_e16braddr_rx(line, 14U /* STX */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro std defined at ../../../targets/sparc64/opmatch.def:896:1-33
 */
static void std_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      store_e16braddr_rr(line, 7U /* STD */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro std defined at ../../../targets/sparc64/opmatch.def:897:1-33
 */
static void std_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      store_e16braddr_ri(line, 7U /* STD */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro std defined at ../../../targets/sparc64/opmatch.def:898:1-33
 */
static void std_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      store_e16braddr_rx(line, 7U /* STD */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsb defined at ../../../targets/sparc64/opmatch.def:900:1-34
 */
static void stsb_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      store_e16braddr_rr(line, 5U /* STB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsb defined at ../../../targets/sparc64/opmatch.def:901:1-34
 */
static void stsb_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      store_e16braddr_ri(line, 5U /* STB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsb defined at ../../../targets/sparc64/opmatch.def:902:1-34
 */
static void stsb_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      store_e16braddr_rx(line, 5U /* STB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stub defined at ../../../targets/sparc64/opmatch.def:903:1-34
 */
static void stub_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      store_e16braddr_rr(line, 5U /* STB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stub defined at ../../../targets/sparc64/opmatch.def:904:1-34
 */
static void stub_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      store_e16braddr_ri(line, 5U /* STB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stub defined at ../../../targets/sparc64/opmatch.def:905:1-34
 */
static void stub_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      store_e16braddr_rx(line, 5U /* STB */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsh defined at ../../../targets/sparc64/opmatch.def:906:1-34
 */
static void stsh_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      store_e16braddr_rr(line, 6U /* STH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsh defined at ../../../targets/sparc64/opmatch.def:907:1-34
 */
static void stsh_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      store_e16braddr_ri(line, 6U /* STH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsh defined at ../../../targets/sparc64/opmatch.def:908:1-34
 */
static void stsh_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      store_e16braddr_rx(line, 6U /* STH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stuh defined at ../../../targets/sparc64/opmatch.def:909:1-34
 */
static void stuh_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      store_e16braddr_rr(line, 6U /* STH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stuh defined at ../../../targets/sparc64/opmatch.def:910:1-34
 */
static void stuh_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      store_e16braddr_ri(line, 6U /* STH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stuh defined at ../../../targets/sparc64/opmatch.def:911:1-34
 */
static void stuh_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      store_e16braddr_rx(line, 6U /* STH */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro st defined at ../../../targets/sparc64/opmatch.def:912:1-32
 */
static void st_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      store_e16braddr_rr(line, 4U /* STW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro st defined at ../../../targets/sparc64/opmatch.def:913:1-32
 */
static void st_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      store_e16braddr_ri(line, 4U /* STW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro st defined at ../../../targets/sparc64/opmatch.def:914:1-32
 */
static void st_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      store_e16braddr_rx(line, 4U /* STW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsw defined at ../../../targets/sparc64/opmatch.def:915:1-34
 */
static void stsw_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      store_e16braddr_rr(line, 4U /* STW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsw defined at ../../../targets/sparc64/opmatch.def:916:1-34
 */
static void stsw_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      store_e16braddr_ri(line, 4U /* STW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsw defined at ../../../targets/sparc64/opmatch.def:917:1-34
 */
static void stsw_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      store_e16braddr_rx(line, 4U /* STW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stuw defined at ../../../targets/sparc64/opmatch.def:918:1-34
 */
static void stuw_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      store_e16braddr_rr(line, 4U /* STW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stuw defined at ../../../targets/sparc64/opmatch.def:919:1-34
 */
static void stuw_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      store_e16braddr_ri(line, 4U /* STW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stuw defined at ../../../targets/sparc64/opmatch.def:920:1-34
 */
static void stuw_e16braddr_rx(int line, uint8_t var__op0, struct compound_braddr_rx * var__op1) {
   
   if (true) {
      store_e16braddr_rx(line, 4U /* STW */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stba defined at ../../../targets/sparc64/opmatch.def:922:1-41
 */
static void stba_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      store_e16braddr_rr_immasi(line, 21U /* STBA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stba defined at ../../../targets/sparc64/opmatch.def:923:1-39
 */
static void stba_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      store_e16braddr_ri_asi(line, 21U /* STBA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stha defined at ../../../targets/sparc64/opmatch.def:924:1-41
 */
static void stha_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      store_e16braddr_rr_immasi(line, 22U /* STHA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stha defined at ../../../targets/sparc64/opmatch.def:925:1-39
 */
static void stha_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      store_e16braddr_ri_asi(line, 22U /* STHA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stwa defined at ../../../targets/sparc64/opmatch.def:926:1-41
 */
static void stwa_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      store_e16braddr_rr_immasi(line, 20U /* STWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stwa defined at ../../../targets/sparc64/opmatch.def:927:1-39
 */
static void stwa_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      store_e16braddr_ri_asi(line, 20U /* STWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stxa defined at ../../../targets/sparc64/opmatch.def:928:1-41
 */
static void stxa_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      store_e16braddr_rr_immasi(line, 30U /* STXA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stxa defined at ../../../targets/sparc64/opmatch.def:929:1-39
 */
static void stxa_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      store_e16braddr_ri_asi(line, 30U /* STXA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stda defined at ../../../targets/sparc64/opmatch.def:931:1-41
 */
static void stda_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      store_e16braddr_rr_immasi(line, 23U /* STDA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stda defined at ../../../targets/sparc64/opmatch.def:932:1-39
 */
static void stda_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      store_e16braddr_ri_asi(line, 23U /* STDA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsba defined at ../../../targets/sparc64/opmatch.def:934:1-42
 */
static void stsba_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      store_e16braddr_rr_immasi(line, 21U /* STBA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsba defined at ../../../targets/sparc64/opmatch.def:935:1-39
 */
static void stsba_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      store_e16braddr_ri_asi(line, 21U /* STBA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stuba defined at ../../../targets/sparc64/opmatch.def:936:1-42
 */
static void stuba_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      store_e16braddr_rr_immasi(line, 21U /* STBA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stuba defined at ../../../targets/sparc64/opmatch.def:937:1-39
 */
static void stuba_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      store_e16braddr_ri_asi(line, 21U /* STBA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsha defined at ../../../targets/sparc64/opmatch.def:938:1-42
 */
static void stsha_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      store_e16braddr_rr_immasi(line, 22U /* STHA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stsha defined at ../../../targets/sparc64/opmatch.def:939:1-39
 */
static void stsha_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      store_e16braddr_ri_asi(line, 22U /* STHA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stuha defined at ../../../targets/sparc64/opmatch.def:940:1-42
 */
static void stuha_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      store_e16braddr_rr_immasi(line, 22U /* STHA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stuha defined at ../../../targets/sparc64/opmatch.def:941:1-39
 */
static void stuha_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      store_e16braddr_ri_asi(line, 22U /* STHA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stswa defined at ../../../targets/sparc64/opmatch.def:942:1-42
 */
static void stswa_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      store_e16braddr_rr_immasi(line, 20U /* STWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stswa defined at ../../../targets/sparc64/opmatch.def:943:1-39
 */
static void stswa_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      store_e16braddr_ri_asi(line, 20U /* STWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stuwa defined at ../../../targets/sparc64/opmatch.def:944:1-42
 */
static void stuwa_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      store_e16braddr_rr_immasi(line, 20U /* STWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stuwa defined at ../../../targets/sparc64/opmatch.def:945:1-39
 */
static void stuwa_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      store_e16braddr_ri_asi(line, 20U /* STWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sta defined at ../../../targets/sparc64/opmatch.def:946:1-40
 */
static void sta_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      store_e16braddr_rr_immasi(line, 20U /* STWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro sta defined at ../../../targets/sparc64/opmatch.def:947:1-38
 */
static void sta_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      store_e16braddr_ri_asi(line, 20U /* STWA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ta defined at ../../../targets/sparc64/opmatch.def:960:1-31
 */
static void ta_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 8U /* BA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ta defined at ../../../targets/sparc64/opmatch.def:961:1-31
 */
static void ta_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 8U /* BA */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tn defined at ../../../targets/sparc64/opmatch.def:962:1-31
 */
static void tn_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 0U /* BN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tn defined at ../../../targets/sparc64/opmatch.def:963:1-31
 */
static void tn_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 0U /* BN */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tne defined at ../../../targets/sparc64/opmatch.def:964:1-33
 */
static void tne_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 9U /* BNE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tne defined at ../../../targets/sparc64/opmatch.def:965:1-33
 */
static void tne_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 9U /* BNE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro te defined at ../../../targets/sparc64/opmatch.def:966:1-31
 */
static void te_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 1U /* BE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro te defined at ../../../targets/sparc64/opmatch.def:967:1-31
 */
static void te_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 1U /* BE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tg defined at ../../../targets/sparc64/opmatch.def:968:1-31
 */
static void tg_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 10U /* BG */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tg defined at ../../../targets/sparc64/opmatch.def:969:1-31
 */
static void tg_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 10U /* BG */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tle defined at ../../../targets/sparc64/opmatch.def:970:1-33
 */
static void tle_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 2U /* BLE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tle defined at ../../../targets/sparc64/opmatch.def:971:1-33
 */
static void tle_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 2U /* BLE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tge defined at ../../../targets/sparc64/opmatch.def:972:1-33
 */
static void tge_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 11U /* BGE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tge defined at ../../../targets/sparc64/opmatch.def:973:1-33
 */
static void tge_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 11U /* BGE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tl defined at ../../../targets/sparc64/opmatch.def:974:1-31
 */
static void tl_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 3U /* BL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tl defined at ../../../targets/sparc64/opmatch.def:975:1-31
 */
static void tl_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 3U /* BL */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tgu defined at ../../../targets/sparc64/opmatch.def:976:1-33
 */
static void tgu_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 12U /* BGU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tgu defined at ../../../targets/sparc64/opmatch.def:977:1-33
 */
static void tgu_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 12U /* BGU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tleu defined at ../../../targets/sparc64/opmatch.def:978:1-35
 */
static void tleu_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 4U /* BLEU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tleu defined at ../../../targets/sparc64/opmatch.def:979:1-35
 */
static void tleu_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 4U /* BLEU */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tcc defined at ../../../targets/sparc64/opmatch.def:980:1-33
 */
static void tcc_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 13U /* BCC */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tcc defined at ../../../targets/sparc64/opmatch.def:981:1-33
 */
static void tcc_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 13U /* BCC */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tcs defined at ../../../targets/sparc64/opmatch.def:982:1-33
 */
static void tcs_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 5U /* BCS */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tcs defined at ../../../targets/sparc64/opmatch.def:983:1-33
 */
static void tcs_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 5U /* BCS */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tpos defined at ../../../targets/sparc64/opmatch.def:984:1-35
 */
static void tpos_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 14U /* BPOS */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tpos defined at ../../../targets/sparc64/opmatch.def:985:1-35
 */
static void tpos_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 14U /* BPOS */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tneg defined at ../../../targets/sparc64/opmatch.def:986:1-35
 */
static void tneg_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 6U /* BNEG */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tneg defined at ../../../targets/sparc64/opmatch.def:987:1-35
 */
static void tneg_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 6U /* BNEG */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tvc defined at ../../../targets/sparc64/opmatch.def:988:1-33
 */
static void tvc_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 15U /* BVC */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tvc defined at ../../../targets/sparc64/opmatch.def:989:1-33
 */
static void tvc_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 15U /* BVC */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tvs defined at ../../../targets/sparc64/opmatch.def:990:1-33
 */
static void tvs_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 7U /* BVS */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tvs defined at ../../../targets/sparc64/opmatch.def:991:1-33
 */
static void tvs_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 7U /* BVS */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tnz defined at ../../../targets/sparc64/opmatch.def:993:1-33
 */
static void tnz_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 9U /* BNE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tnz defined at ../../../targets/sparc64/opmatch.def:994:1-33
 */
static void tnz_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 9U /* BNE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tz defined at ../../../targets/sparc64/opmatch.def:995:1-31
 */
static void tz_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 1U /* BE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tz defined at ../../../targets/sparc64/opmatch.def:996:1-31
 */
static void tz_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 1U /* BE */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tgeu defined at ../../../targets/sparc64/opmatch.def:997:1-34
 */
static void tgeu_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 13U /* BCC */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tgeu defined at ../../../targets/sparc64/opmatch.def:998:1-34
 */
static void tgeu_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 13U /* BCC */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tlu defined at ../../../targets/sparc64/opmatch.def:999:1-33
 */
static void tlu_e17trapnum_rr(int line, uint8_t var__op0, struct compound_trapnum_rr * var__op1) {
   
   if (true) {
      tcc__e17trapnum_rr(line, 5U /* BCS */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro tlu defined at ../../../targets/sparc64/opmatch.def:1000:1-33
 */
static void tlu_e17trapnum_ri(int line, uint8_t var__op0, struct compound_trapnum_ri * var__op1) {
   
   if (true) {
      tcc__e17trapnum_ri(line, 5U /* BCS */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro nop defined at ../../../targets/sparc64/opmatch.def:1002:1-14
 */
static void nop_(int line) {
   
   if (true) {
      nop__(line);
      return;
   }
}

/*
 * Macro wr defined at ../../../targets/sparc64/opmatch.def:1005:1-26
 */
static void wr_e16e16e11(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      wrasr_e16e16e11(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro wr defined at ../../../targets/sparc64/opmatch.def:1006:1-29
 */
static void wr_e16i13e11(int line, uint8_t var__op0, int16_t var__op1, uint8_t var__op2) {
   
   if (true) {
      wrasr_e16i13e11(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro impl1 defined at ../../../targets/sparc64/opmatch.def:1010:1-37
 */
static void impl1_u5u19(int line, uint8_t var__op0, uint32_t var__op1) {
   
   if (true) {
      impl_u5u19(line, 54U /* IMPDEP1 */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro impl2 defined at ../../../targets/sparc64/opmatch.def:1011:1-37
 */
static void impl2_u5u19(int line, uint8_t var__op0, uint32_t var__op1) {
   
   if (true) {
      impl_u5u19(line, 55U /* IMPDEP2 */, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro cmp defined at ../../../targets/sparc64/opmatch.def:1025:1-22
 */
static void cmp_e16e16(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      cmp__e16e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro cmp defined at ../../../targets/sparc64/opmatch.def:1026:1-25
 */
static void cmp_e16i13(int line, uint8_t var__op0, int16_t var__op1) {
   
   if (true) {
      cmp__e16i13(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro jmp defined at ../../../targets/sparc64/opmatch.def:1027:1-21
 */
static void jmp_addr_rr(int line, struct compound_addr_rr * var__op0) {
   
   if (true) {
      jmp__addr_rr(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro jmp defined at ../../../targets/sparc64/opmatch.def:1028:1-21
 */
static void jmp_addr_ri(int line, struct compound_addr_ri * var__op0) {
   
   if (true) {
      jmp__addr_ri(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro call defined at ../../../targets/sparc64/opmatch.def:1029:1-23
 */
static void call_addr_rr(int line, struct compound_addr_rr * var__op0) {
   
   if (true) {
      call__addr_rr(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro call defined at ../../../targets/sparc64/opmatch.def:1030:1-23
 */
static void call_addr_ri(int line, struct compound_addr_ri * var__op0) {
   
   if (true) {
      call__addr_ri(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro call defined at ../../../targets/sparc64/opmatch.def:1031:1-30
 */
static void call_addr_rru32(int line, struct compound_addr_rr * var__op0, uint32_t var__op1) {
   
   if (true) {
      call__addr_rru32(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro call defined at ../../../targets/sparc64/opmatch.def:1032:1-30
 */
static void call_addr_riu32(int line, struct compound_addr_ri * var__op0, uint32_t var__op1) {
   
   if (true) {
      call__addr_riu32(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ret defined at ../../../targets/sparc64/opmatch.def:1033:1-14
 */
static void ret_(int line) {
   
   if (true) {
      ret__(line);
      return;
   }
}

/*
 * Macro retl defined at ../../../targets/sparc64/opmatch.def:1034:1-16
 */
static void retl_(int line) {
   
   if (true) {
      retl__(line);
      return;
   }
}

/*
 * Macro save defined at ../../../targets/sparc64/opmatch.def:1035:1-16
 */
static void save_(int line) {
   
   if (true) {
      save__(line);
      return;
   }
}

/*
 * Macro restore defined at ../../../targets/sparc64/opmatch.def:1036:1-22
 */
static void restore_(int line) {
   
   if (true) {
      restore__(line);
      return;
   }
}

/*
 * Macro iprefetch defined at ../../../targets/sparc64/opmatch.def:1037:1-31
 */
static void iprefetch_xu64(int line, struct expr * var__op0) {
   
   if (true) {
      iprefetch__xu64(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro tst defined at ../../../targets/sparc64/opmatch.def:1038:1-18
 */
static void tst_e16(int line, uint8_t var__op0) {
   
   if (true) {
      tst__e16(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro set defined at ../../../targets/sparc64/opmatch.def:1040:1-25
 */
static void set_u32e16(int line, uint32_t var__op0, uint8_t var__op1) {
   
   if (true) {
      set__u32e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro setsw defined at ../../../targets/sparc64/opmatch.def:1041:1-28
 */
static void setsw_i32e16(int line, int32_t var__op0, uint8_t var__op1) {
   
   if (true) {
      setsw__i32e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro setx defined at ../../../targets/sparc64/opmatch.def:1042:1-31
 */
static void setx_i64e16e16(int line, int64_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      setx__i64e16e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro signx defined at ../../../targets/sparc64/opmatch.def:1043:1-26
 */
static void signx_e16e16(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      signx__e16e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro signx defined at ../../../targets/sparc64/opmatch.def:1044:1-21
 */
static void signx_e16(int line, uint8_t var__op0) {
   
   if (true) {
      signx__e16(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro not defined at ../../../targets/sparc64/opmatch.def:1045:1-22
 */
static void not_e16e16(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      not__e16e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro not defined at ../../../targets/sparc64/opmatch.def:1046:1-18
 */
static void not_e16(int line, uint8_t var__op0) {
   
   if (true) {
      not__e16(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro neg defined at ../../../targets/sparc64/opmatch.def:1047:1-22
 */
static void neg_e16e16(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      neg__e16e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro neg defined at ../../../targets/sparc64/opmatch.def:1048:1-18
 */
static void neg_e16(int line, uint8_t var__op0) {
   
   if (true) {
      neg__e16(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro cas defined at ../../../targets/sparc64/opmatch.def:1050:1-31
 */
static void cas_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      cas__e16e16e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro casl defined at ../../../targets/sparc64/opmatch.def:1051:1-33
 */
static void casl_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      casl__e16e16e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro casx defined at ../../../targets/sparc64/opmatch.def:1052:1-33
 */
static void casx_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      casx__e16e16e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro casxl defined at ../../../targets/sparc64/opmatch.def:1053:1-34
 */
static void casxl_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      casxl__e16e16e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro inc defined at ../../../targets/sparc64/opmatch.def:1055:1-18
 */
static void inc_e16(int line, uint8_t var__op0) {
   
   if (true) {
      inc__e16(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro inc defined at ../../../targets/sparc64/opmatch.def:1056:1-25
 */
static void inc_i13e16(int line, int16_t var__op0, uint8_t var__op1) {
   
   if (true) {
      inc__i13e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro inccc defined at ../../../targets/sparc64/opmatch.def:1057:1-21
 */
static void inccc_e16(int line, uint8_t var__op0) {
   
   if (true) {
      inccc__e16(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro inccc defined at ../../../targets/sparc64/opmatch.def:1058:1-28
 */
static void inccc_i13e16(int line, int16_t var__op0, uint8_t var__op1) {
   
   if (true) {
      inccc__i13e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro dec defined at ../../../targets/sparc64/opmatch.def:1059:1-18
 */
static void dec_e16(int line, uint8_t var__op0) {
   
   if (true) {
      dec__e16(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro dec defined at ../../../targets/sparc64/opmatch.def:1060:1-25
 */
static void dec_i13e16(int line, int16_t var__op0, uint8_t var__op1) {
   
   if (true) {
      dec__i13e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro deccc defined at ../../../targets/sparc64/opmatch.def:1061:1-21
 */
static void deccc_e16(int line, uint8_t var__op0) {
   
   if (true) {
      deccc__e16(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro deccc defined at ../../../targets/sparc64/opmatch.def:1062:1-28
 */
static void deccc_i13e16(int line, int16_t var__op0, uint8_t var__op1) {
   
   if (true) {
      deccc__i13e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro btst defined at ../../../targets/sparc64/opmatch.def:1064:1-24
 */
static void btst_e16e16(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      btst__e16e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro btst defined at ../../../targets/sparc64/opmatch.def:1065:1-26
 */
static void btst_i13e16(int line, int16_t var__op0, uint8_t var__op1) {
   
   if (true) {
      btst__i13e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bset defined at ../../../targets/sparc64/opmatch.def:1066:1-24
 */
static void bset_e16e16(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      bset__e16e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bset defined at ../../../targets/sparc64/opmatch.def:1067:1-26
 */
static void bset_i13e16(int line, int16_t var__op0, uint8_t var__op1) {
   
   if (true) {
      bset__i13e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bclr defined at ../../../targets/sparc64/opmatch.def:1068:1-24
 */
static void bclr_e16e16(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      bclr__e16e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro bclr defined at ../../../targets/sparc64/opmatch.def:1069:1-26
 */
static void bclr_i13e16(int line, int16_t var__op0, uint8_t var__op1) {
   
   if (true) {
      bclr__i13e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro btog defined at ../../../targets/sparc64/opmatch.def:1070:1-24
 */
static void btog_e16e16(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      btog__e16e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro btog defined at ../../../targets/sparc64/opmatch.def:1071:1-26
 */
static void btog_i13e16(int line, int16_t var__op0, uint8_t var__op1) {
   
   if (true) {
      btog__i13e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro clr defined at ../../../targets/sparc64/opmatch.def:1073:1-19
 */
static void clr_e16(int line, uint8_t var__op0) {
   
   if (true) {
      clr___e16(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro clrb defined at ../../../targets/sparc64/opmatch.def:1074:1-29
 */
static void clrb_braddr_rr(int line, struct compound_braddr_rr * var__op0) {
   
   if (true) {
      clr__braddr_rr(line, 5U /* STB */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro clrb defined at ../../../targets/sparc64/opmatch.def:1075:1-29
 */
static void clrb_braddr_ri(int line, struct compound_braddr_ri * var__op0) {
   
   if (true) {
      clr__braddr_ri(line, 5U /* STB */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro clrh defined at ../../../targets/sparc64/opmatch.def:1076:1-30
 */
static void clrh_braddr_rr(int line, struct compound_braddr_rr * var__op0) {
   
   if (true) {
      clr__braddr_rr(line, 6U /* STH */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro clrh defined at ../../../targets/sparc64/opmatch.def:1077:1-30
 */
static void clrh_braddr_ri(int line, struct compound_braddr_ri * var__op0) {
   
   if (true) {
      clr__braddr_ri(line, 6U /* STH */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro clr defined at ../../../targets/sparc64/opmatch.def:1078:1-28
 */
static void clr_braddr_rr(int line, struct compound_braddr_rr * var__op0) {
   
   if (true) {
      clr__braddr_rr(line, 4U /* STW */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro clr defined at ../../../targets/sparc64/opmatch.def:1079:1-28
 */
static void clr_braddr_ri(int line, struct compound_braddr_ri * var__op0) {
   
   if (true) {
      clr__braddr_ri(line, 4U /* STW */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro clrx defined at ../../../targets/sparc64/opmatch.def:1080:1-29
 */
static void clrx_braddr_rr(int line, struct compound_braddr_rr * var__op0) {
   
   if (true) {
      clr__braddr_rr(line, 14U /* STX */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro clrx defined at ../../../targets/sparc64/opmatch.def:1081:1-29
 */
static void clrx_braddr_ri(int line, struct compound_braddr_ri * var__op0) {
   
   if (true) {
      clr__braddr_ri(line, 14U /* STX */, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro clruw defined at ../../../targets/sparc64/opmatch.def:1083:1-26
 */
static void clruw_e16e16(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      clruw__e16e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro clruw defined at ../../../targets/sparc64/opmatch.def:1084:1-21
 */
static void clruw_e16(int line, uint8_t var__op0) {
   
   if (true) {
      clruw__e16(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro mov defined at ../../../targets/sparc64/opmatch.def:1086:1-22
 */
static void mov_e16e16(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      mov__e16e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro mov defined at ../../../targets/sparc64/opmatch.def:1087:1-25
 */
static void mov_i13e16(int line, int16_t var__op0, uint8_t var__op1) {
   
   if (true) {
      mov__i13e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro mov defined at ../../../targets/sparc64/opmatch.def:1088:1-22
 */
static void mov_e11e16(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      mov__e11e16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro mov defined at ../../../targets/sparc64/opmatch.def:1089:1-22
 */
static void mov_e16e11(int line, uint8_t var__op0, uint8_t var__op1) {
   
   if (true) {
      mov__e16e11(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldn defined at ../../../targets/sparc64/opmatch.def:1093:1-26
 */
static void ldn_braddr_rre16(int line, struct compound_braddr_rr * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldx_braddr_rre16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldn defined at ../../../targets/sparc64/opmatch.def:1094:1-26
 */
static void ldn_braddr_rie16(int line, struct compound_braddr_ri * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldx_braddr_rie16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldna defined at ../../../targets/sparc64/opmatch.def:1095:1-34
 */
static void ldna_braddr_rr_immasie16(int line, struct compound_braddr_rr_immasi * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldxa_braddr_rr_immasie16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro ldna defined at ../../../targets/sparc64/opmatch.def:1096:1-32
 */
static void ldna_braddr_ri_asie16(int line, struct compound_braddr_ri_asi * var__op0, uint8_t var__op1) {
   
   if (true) {
      ldxa_braddr_ri_asie16(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stn defined at ../../../targets/sparc64/opmatch.def:1097:1-26
 */
static void stn_e16braddr_rr(int line, uint8_t var__op0, struct compound_braddr_rr * var__op1) {
   
   if (true) {
      stx_e16braddr_rr(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stn defined at ../../../targets/sparc64/opmatch.def:1098:1-26
 */
static void stn_e16braddr_ri(int line, uint8_t var__op0, struct compound_braddr_ri * var__op1) {
   
   if (true) {
      stx_e16braddr_ri(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stna defined at ../../../targets/sparc64/opmatch.def:1099:1-34
 */
static void stna_e16braddr_rr_immasi(int line, uint8_t var__op0, struct compound_braddr_rr_immasi * var__op1) {
   
   if (true) {
      stxa_e16braddr_rr_immasi(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro stna defined at ../../../targets/sparc64/opmatch.def:1100:1-32
 */
static void stna_e16braddr_ri_asi(int line, uint8_t var__op0, struct compound_braddr_ri_asi * var__op1) {
   
   if (true) {
      stxa_e16braddr_ri_asi(line, var__op0, var__op1);
      return;
   }
   (void)var__op0;
   (void)var__op1;
}

/*
 * Macro slln defined at ../../../targets/sparc64/opmatch.def:1101:1-27
 */
static void slln_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      sllx_e16e16e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro slln defined at ../../../targets/sparc64/opmatch.def:1102:1-29
 */
static void slln_e16u6e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      sllx_e16u6e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro srln defined at ../../../targets/sparc64/opmatch.def:1103:1-27
 */
static void srln_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      srlx_e16e16e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro srln defined at ../../../targets/sparc64/opmatch.def:1104:1-29
 */
static void srln_e16u6e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      srlx_e16u6e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sran defined at ../../../targets/sparc64/opmatch.def:1105:1-27
 */
static void sran_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      srax_e16e16e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro sran defined at ../../../targets/sparc64/opmatch.def:1106:1-29
 */
static void sran_e16u6e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      srax_e16u6e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro casn defined at ../../../targets/sparc64/opmatch.def:1107:1-32
 */
static void casn_e16e16e16(int line, uint8_t var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      casx_e16e16e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro casna defined at ../../../targets/sparc64/opmatch.def:1108:1-40
 */
static void casna_braddr_r_immasie16e16(int line, struct compound_braddr_r_immasi * var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      casxa_braddr_r_immasie16e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro casna defined at ../../../targets/sparc64/opmatch.def:1109:1-37
 */
static void casna_braddr_r_asie16e16(int line, struct compound_braddr_r_asi * var__op0, uint8_t var__op1, uint8_t var__op2) {
   
   if (true) {
      casxa_braddr_r_asie16e16(line, var__op0, var__op1, var__op2);
      return;
   }
   (void)var__op0;
   (void)var__op1;
   (void)var__op2;
}

/*
 * Macro clrn defined at ../../../targets/sparc64/opmatch.def:1110:1-24
 */
static void clrn_braddr_rr(int line, struct compound_braddr_rr * var__op0) {
   
   if (true) {
      clrx_braddr_rr(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Macro clrn defined at ../../../targets/sparc64/opmatch.def:1111:1-24
 */
static void clrn_braddr_ri(int line, struct compound_braddr_ri * var__op0) {
   
   if (true) {
      clrx_braddr_ri(line, var__op0);
      return;
   }
   (void)var__op0;
}

/*
 * Insn sethi defined at ../../../targets/sparc64/opmatch.def:1:1-28
 */
void insn_sethi_u32num_reg(int line, uint32_t op_0, uint8_t op_1) {
   sethi_u32e16(line, op_0, op_1);
}

/*
 * Insn sethi defined at ../../../targets/sparc64/opmatch.def:2:1-27
 */
void insn_sethi_expr_reg(int line, struct expr * op_0, uint8_t op_1) {
   sethi_xu64e16(line, op_0, op_1);
}

/*
 * Insn add defined at ../../../targets/sparc64/opmatch.def:4:1-32
 */
void insn_add_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   add_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn add defined at ../../../targets/sparc64/opmatch.def:5:1-35
 */
void insn_add_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   add_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn addcc defined at ../../../targets/sparc64/opmatch.def:6:1-36
 */
void insn_addcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   addcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn addcc defined at ../../../targets/sparc64/opmatch.def:7:1-39
 */
void insn_addcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   addcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn addc defined at ../../../targets/sparc64/opmatch.def:8:1-34
 */
void insn_addc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   addc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn addc defined at ../../../targets/sparc64/opmatch.def:9:1-37
 */
void insn_addc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   addc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn addccc defined at ../../../targets/sparc64/opmatch.def:10:1-38
 */
void insn_addccc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   addccc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn addccc defined at ../../../targets/sparc64/opmatch.def:11:1-41
 */
void insn_addccc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   addccc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn sub defined at ../../../targets/sparc64/opmatch.def:12:1-32
 */
void insn_sub_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sub_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn sub defined at ../../../targets/sparc64/opmatch.def:13:1-35
 */
void insn_sub_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   sub_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn subcc defined at ../../../targets/sparc64/opmatch.def:14:1-36
 */
void insn_subcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   subcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn subcc defined at ../../../targets/sparc64/opmatch.def:15:1-39
 */
void insn_subcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   subcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn subc defined at ../../../targets/sparc64/opmatch.def:16:1-34
 */
void insn_subc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   subc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn subc defined at ../../../targets/sparc64/opmatch.def:17:1-37
 */
void insn_subc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   subc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn subccc defined at ../../../targets/sparc64/opmatch.def:18:1-38
 */
void insn_subccc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   subccc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn subccc defined at ../../../targets/sparc64/opmatch.def:19:1-41
 */
void insn_subccc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   subccc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn and defined at ../../../targets/sparc64/opmatch.def:20:1-32
 */
void insn_and_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   and_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn and defined at ../../../targets/sparc64/opmatch.def:21:1-35
 */
void insn_and_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   and_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn andcc defined at ../../../targets/sparc64/opmatch.def:22:1-36
 */
void insn_andcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   andcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn andcc defined at ../../../targets/sparc64/opmatch.def:23:1-39
 */
void insn_andcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   andcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn andn defined at ../../../targets/sparc64/opmatch.def:24:1-34
 */
void insn_andn_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   andn_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn andn defined at ../../../targets/sparc64/opmatch.def:25:1-37
 */
void insn_andn_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   andn_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn andncc defined at ../../../targets/sparc64/opmatch.def:26:1-38
 */
void insn_andncc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   andncc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn andncc defined at ../../../targets/sparc64/opmatch.def:27:1-41
 */
void insn_andncc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   andncc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn or defined at ../../../targets/sparc64/opmatch.def:28:1-30
 */
void insn_or_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   or_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn or defined at ../../../targets/sparc64/opmatch.def:29:1-33
 */
void insn_or_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   or_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn or defined at ../../../targets/sparc64/opmatch.def:30:1-31
 */
void insn_or_reg_expr_reg(int line, uint8_t op_0, struct expr * op_1, uint8_t op_2) {
   or_e16xu64e16(line, op_0, op_1, op_2);
}

/*
 * Insn orcc defined at ../../../targets/sparc64/opmatch.def:31:1-34
 */
void insn_orcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   orcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn orcc defined at ../../../targets/sparc64/opmatch.def:32:1-37
 */
void insn_orcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   orcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn orn defined at ../../../targets/sparc64/opmatch.def:33:1-32
 */
void insn_orn_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   orn_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn orn defined at ../../../targets/sparc64/opmatch.def:34:1-35
 */
void insn_orn_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   orn_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn orncc defined at ../../../targets/sparc64/opmatch.def:35:1-36
 */
void insn_orncc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   orncc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn orncc defined at ../../../targets/sparc64/opmatch.def:36:1-39
 */
void insn_orncc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   orncc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn xor defined at ../../../targets/sparc64/opmatch.def:37:1-32
 */
void insn_xor_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   xor_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn xor defined at ../../../targets/sparc64/opmatch.def:38:1-35
 */
void insn_xor_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   xor_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn xorcc defined at ../../../targets/sparc64/opmatch.def:39:1-36
 */
void insn_xorcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   xorcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn xorcc defined at ../../../targets/sparc64/opmatch.def:40:1-39
 */
void insn_xorcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   xorcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn xnor defined at ../../../targets/sparc64/opmatch.def:41:1-34
 */
void insn_xnor_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   xnor_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn xnor defined at ../../../targets/sparc64/opmatch.def:42:1-37
 */
void insn_xnor_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   xnor_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn xnorcc defined at ../../../targets/sparc64/opmatch.def:43:1-38
 */
void insn_xnorcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   xnorcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn xnorcc defined at ../../../targets/sparc64/opmatch.def:44:1-41
 */
void insn_xnorcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   xnorcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn popc defined at ../../../targets/sparc64/opmatch.def:45:1-14
 */
void insn_popc_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   popc_e16e16(line, op_0, op_1);
}

/*
 * Insn popc defined at ../../../targets/sparc64/opmatch.def:46:1-17
 */
void insn_popc_i13num_reg(int line, int16_t op_0, uint8_t op_1) {
   popc_i13e16(line, op_0, op_1);
}

/*
 * Insn save defined at ../../../targets/sparc64/opmatch.def:47:1-34
 */
void insn_save_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   save_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn save defined at ../../../targets/sparc64/opmatch.def:48:1-37
 */
void insn_save_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   save_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn restore defined at ../../../targets/sparc64/opmatch.def:49:1-40
 */
void insn_restore_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   restore_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn restore defined at ../../../targets/sparc64/opmatch.def:50:1-42
 */
void insn_restore_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   restore_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn taddcc defined at ../../../targets/sparc64/opmatch.def:51:1-38
 */
void insn_taddcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   taddcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn taddcc defined at ../../../targets/sparc64/opmatch.def:52:1-41
 */
void insn_taddcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   taddcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn taddcctv defined at ../../../targets/sparc64/opmatch.def:53:1-42
 */
void insn_taddcctv_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   taddcctv_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn taddcctv defined at ../../../targets/sparc64/opmatch.def:54:1-44
 */
void insn_taddcctv_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   taddcctv_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn tsubcc defined at ../../../targets/sparc64/opmatch.def:55:1-38
 */
void insn_tsubcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   tsubcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn tsubcc defined at ../../../targets/sparc64/opmatch.def:56:1-41
 */
void insn_tsubcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   tsubcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn tsubcctv defined at ../../../targets/sparc64/opmatch.def:57:1-42
 */
void insn_tsubcctv_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   tsubcctv_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn tsubcctv defined at ../../../targets/sparc64/opmatch.def:58:1-44
 */
void insn_tsubcctv_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   tsubcctv_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn addx defined at ../../../targets/sparc64/opmatch.def:61:1-34
 */
void insn_addx_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   addx_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn addx defined at ../../../targets/sparc64/opmatch.def:62:1-37
 */
void insn_addx_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   addx_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn addxcc defined at ../../../targets/sparc64/opmatch.def:63:1-38
 */
void insn_addxcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   addxcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn addxcc defined at ../../../targets/sparc64/opmatch.def:64:1-41
 */
void insn_addxcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   addxcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn subx defined at ../../../targets/sparc64/opmatch.def:65:1-34
 */
void insn_subx_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   subx_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn subx defined at ../../../targets/sparc64/opmatch.def:66:1-37
 */
void insn_subx_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   subx_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn subxcc defined at ../../../targets/sparc64/opmatch.def:67:1-38
 */
void insn_subxcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   subxcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn subxcc defined at ../../../targets/sparc64/opmatch.def:68:1-41
 */
void insn_subxcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   subxcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn sll defined at ../../../targets/sparc64/opmatch.def:70:1-32
 */
void insn_sll_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sll_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn sll defined at ../../../targets/sparc64/opmatch.def:71:1-34
 */
void insn_sll_reg_u5num_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sll_e16u5e16(line, op_0, op_1, op_2);
}

/*
 * Insn srl defined at ../../../targets/sparc64/opmatch.def:72:1-32
 */
void insn_srl_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   srl_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn srl defined at ../../../targets/sparc64/opmatch.def:73:1-34
 */
void insn_srl_reg_u5num_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   srl_e16u5e16(line, op_0, op_1, op_2);
}

/*
 * Insn sra defined at ../../../targets/sparc64/opmatch.def:74:1-32
 */
void insn_sra_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sra_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn sra defined at ../../../targets/sparc64/opmatch.def:75:1-34
 */
void insn_sra_reg_u5num_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sra_e16u5e16(line, op_0, op_1, op_2);
}

/*
 * Insn sllx defined at ../../../targets/sparc64/opmatch.def:76:1-34
 */
void insn_sllx_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sllx_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn sllx defined at ../../../targets/sparc64/opmatch.def:77:1-36
 */
void insn_sllx_reg_u6num_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sllx_e16u6e16(line, op_0, op_1, op_2);
}

/*
 * Insn srlx defined at ../../../targets/sparc64/opmatch.def:78:1-34
 */
void insn_srlx_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   srlx_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn srlx defined at ../../../targets/sparc64/opmatch.def:79:1-36
 */
void insn_srlx_reg_u6num_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   srlx_e16u6e16(line, op_0, op_1, op_2);
}

/*
 * Insn srax defined at ../../../targets/sparc64/opmatch.def:80:1-34
 */
void insn_srax_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   srax_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn srax defined at ../../../targets/sparc64/opmatch.def:81:1-36
 */
void insn_srax_reg_u6num_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   srax_e16u6e16(line, op_0, op_1, op_2);
}

/*
 * Insn umul defined at ../../../targets/sparc64/opmatch.def:84:1-32
 */
void insn_umul_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   umul_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn umul defined at ../../../targets/sparc64/opmatch.def:85:1-35
 */
void insn_umul_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   umul_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn smul defined at ../../../targets/sparc64/opmatch.def:86:1-32
 */
void insn_smul_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   smul_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn smul defined at ../../../targets/sparc64/opmatch.def:87:1-35
 */
void insn_smul_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   smul_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn umulcc defined at ../../../targets/sparc64/opmatch.def:88:1-36
 */
void insn_umulcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   umulcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn umulcc defined at ../../../targets/sparc64/opmatch.def:89:1-39
 */
void insn_umulcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   umulcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn smulcc defined at ../../../targets/sparc64/opmatch.def:90:1-36
 */
void insn_smulcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   smulcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn smulcc defined at ../../../targets/sparc64/opmatch.def:91:1-39
 */
void insn_smulcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   smulcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn mulscc defined at ../../../targets/sparc64/opmatch.def:92:1-36
 */
void insn_mulscc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mulscc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn mulscc defined at ../../../targets/sparc64/opmatch.def:93:1-39
 */
void insn_mulscc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   mulscc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn sdiv defined at ../../../targets/sparc64/opmatch.def:94:1-32
 */
void insn_sdiv_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sdiv_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn sdiv defined at ../../../targets/sparc64/opmatch.def:95:1-35
 */
void insn_sdiv_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   sdiv_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn udiv defined at ../../../targets/sparc64/opmatch.def:96:1-32
 */
void insn_udiv_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   udiv_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn udiv defined at ../../../targets/sparc64/opmatch.def:97:1-35
 */
void insn_udiv_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   udiv_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn sdivcc defined at ../../../targets/sparc64/opmatch.def:98:1-36
 */
void insn_sdivcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sdivcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn sdivcc defined at ../../../targets/sparc64/opmatch.def:99:1-39
 */
void insn_sdivcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   sdivcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn udivcc defined at ../../../targets/sparc64/opmatch.def:100:1-36
 */
void insn_udivcc_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   udivcc_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn udivcc defined at ../../../targets/sparc64/opmatch.def:101:1-39
 */
void insn_udivcc_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   udivcc_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn mulx defined at ../../../targets/sparc64/opmatch.def:104:1-36
 */
void insn_mulx_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mulx_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn mulx defined at ../../../targets/sparc64/opmatch.def:105:1-39
 */
void insn_mulx_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   mulx_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn sdivx defined at ../../../targets/sparc64/opmatch.def:106:1-38
 */
void insn_sdivx_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sdivx_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn sdivx defined at ../../../targets/sparc64/opmatch.def:107:1-41
 */
void insn_sdivx_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   sdivx_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn udivx defined at ../../../targets/sparc64/opmatch.def:108:1-38
 */
void insn_udivx_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   udivx_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn udivx defined at ../../../targets/sparc64/opmatch.def:109:1-41
 */
void insn_udivx_reg_i13num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   udivx_e16i13e16(line, op_0, op_1, op_2);
}

/*
 * Insn fadds defined at ../../../targets/sparc64/opmatch.def:111:1-38
 */
void insn_fadds_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fadds_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn faddd defined at ../../../targets/sparc64/opmatch.def:112:1-38
 */
void insn_faddd_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   faddd_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn faddq defined at ../../../targets/sparc64/opmatch.def:113:1-38
 */
void insn_faddq_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   faddq_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fsubs defined at ../../../targets/sparc64/opmatch.def:114:1-38
 */
void insn_fsubs_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fsubs_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fsubd defined at ../../../targets/sparc64/opmatch.def:115:1-38
 */
void insn_fsubd_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fsubd_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fsubq defined at ../../../targets/sparc64/opmatch.def:116:1-38
 */
void insn_fsubq_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fsubq_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fcmps defined at ../../../targets/sparc64/opmatch.def:118:1-37
 */
void insn_fcmps_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fcmps_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fcmpd defined at ../../../targets/sparc64/opmatch.def:119:1-37
 */
void insn_fcmpd_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fcmpd_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fcmpq defined at ../../../targets/sparc64/opmatch.def:120:1-37
 */
void insn_fcmpq_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fcmpq_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fcmpes defined at ../../../targets/sparc64/opmatch.def:121:1-39
 */
void insn_fcmpes_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fcmpes_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fcmped defined at ../../../targets/sparc64/opmatch.def:122:1-39
 */
void insn_fcmped_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fcmped_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fcmpeq defined at ../../../targets/sparc64/opmatch.def:123:1-39
 */
void insn_fcmpeq_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fcmpeq_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fstox defined at ../../../targets/sparc64/opmatch.def:125:1-31
 */
void insn_fstox_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fstox_e14e14(line, op_0, op_1);
}

/*
 * Insn fdtox defined at ../../../targets/sparc64/opmatch.def:126:1-31
 */
void insn_fdtox_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fdtox_e14e14(line, op_0, op_1);
}

/*
 * Insn fqtox defined at ../../../targets/sparc64/opmatch.def:127:1-31
 */
void insn_fqtox_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fqtox_e14e14(line, op_0, op_1);
}

/*
 * Insn fstoi defined at ../../../targets/sparc64/opmatch.def:128:1-31
 */
void insn_fstoi_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fstoi_e14e14(line, op_0, op_1);
}

/*
 * Insn fdtoi defined at ../../../targets/sparc64/opmatch.def:129:1-31
 */
void insn_fdtoi_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fdtoi_e14e14(line, op_0, op_1);
}

/*
 * Insn fqtoi defined at ../../../targets/sparc64/opmatch.def:130:1-31
 */
void insn_fqtoi_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fqtoi_e14e14(line, op_0, op_1);
}

/*
 * Insn fxtos defined at ../../../targets/sparc64/opmatch.def:131:1-31
 */
void insn_fxtos_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fxtos_e14e14(line, op_0, op_1);
}

/*
 * Insn fxtod defined at ../../../targets/sparc64/opmatch.def:132:1-31
 */
void insn_fxtod_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fxtod_e14e14(line, op_0, op_1);
}

/*
 * Insn fxtoq defined at ../../../targets/sparc64/opmatch.def:133:1-31
 */
void insn_fxtoq_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fxtoq_e14e14(line, op_0, op_1);
}

/*
 * Insn fitos defined at ../../../targets/sparc64/opmatch.def:134:1-31
 */
void insn_fitos_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fitos_e14e14(line, op_0, op_1);
}

/*
 * Insn fitod defined at ../../../targets/sparc64/opmatch.def:135:1-31
 */
void insn_fitod_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fitod_e14e14(line, op_0, op_1);
}

/*
 * Insn fitoq defined at ../../../targets/sparc64/opmatch.def:136:1-31
 */
void insn_fitoq_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fitoq_e14e14(line, op_0, op_1);
}

/*
 * Insn fstod defined at ../../../targets/sparc64/opmatch.def:137:1-31
 */
void insn_fstod_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fstod_e14e14(line, op_0, op_1);
}

/*
 * Insn fstoq defined at ../../../targets/sparc64/opmatch.def:138:1-31
 */
void insn_fstoq_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fstoq_e14e14(line, op_0, op_1);
}

/*
 * Insn fdtos defined at ../../../targets/sparc64/opmatch.def:139:1-31
 */
void insn_fdtos_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fdtos_e14e14(line, op_0, op_1);
}

/*
 * Insn fdtoq defined at ../../../targets/sparc64/opmatch.def:140:1-31
 */
void insn_fdtoq_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fdtoq_e14e14(line, op_0, op_1);
}

/*
 * Insn fqtos defined at ../../../targets/sparc64/opmatch.def:141:1-31
 */
void insn_fqtos_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fqtos_e14e14(line, op_0, op_1);
}

/*
 * Insn fqtod defined at ../../../targets/sparc64/opmatch.def:142:1-31
 */
void insn_fqtod_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fqtod_e14e14(line, op_0, op_1);
}

/*
 * Insn fmovs defined at ../../../targets/sparc64/opmatch.def:144:1-32
 */
void insn_fmovs_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fmovs_e14e14(line, op_0, op_1);
}

/*
 * Insn fmovd defined at ../../../targets/sparc64/opmatch.def:145:1-32
 */
void insn_fmovd_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fmovd_e14e14(line, op_0, op_1);
}

/*
 * Insn fmovq defined at ../../../targets/sparc64/opmatch.def:146:1-32
 */
void insn_fmovq_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fmovq_e14e14(line, op_0, op_1);
}

/*
 * Insn fnegs defined at ../../../targets/sparc64/opmatch.def:147:1-32
 */
void insn_fnegs_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fnegs_e14e14(line, op_0, op_1);
}

/*
 * Insn fnegd defined at ../../../targets/sparc64/opmatch.def:148:1-32
 */
void insn_fnegd_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fnegd_e14e14(line, op_0, op_1);
}

/*
 * Insn fnegq defined at ../../../targets/sparc64/opmatch.def:149:1-32
 */
void insn_fnegq_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fnegq_e14e14(line, op_0, op_1);
}

/*
 * Insn fabss defined at ../../../targets/sparc64/opmatch.def:150:1-32
 */
void insn_fabss_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fabss_e14e14(line, op_0, op_1);
}

/*
 * Insn fabsd defined at ../../../targets/sparc64/opmatch.def:151:1-32
 */
void insn_fabsd_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fabsd_e14e14(line, op_0, op_1);
}

/*
 * Insn fabsq defined at ../../../targets/sparc64/opmatch.def:152:1-32
 */
void insn_fabsq_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fabsq_e14e14(line, op_0, op_1);
}

/*
 * Insn fsqrts defined at ../../../targets/sparc64/opmatch.def:153:1-34
 */
void insn_fsqrts_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fsqrts_e14e14(line, op_0, op_1);
}

/*
 * Insn fsqrtd defined at ../../../targets/sparc64/opmatch.def:154:1-34
 */
void insn_fsqrtd_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fsqrtd_e14e14(line, op_0, op_1);
}

/*
 * Insn fsqrtq defined at ../../../targets/sparc64/opmatch.def:155:1-34
 */
void insn_fsqrtq_freg_freg(int line, uint8_t op_0, uint8_t op_1) {
   fsqrtq_e14e14(line, op_0, op_1);
}

/*
 * Insn fmuls defined at ../../../targets/sparc64/opmatch.def:157:1-38
 */
void insn_fmuls_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmuls_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmuld defined at ../../../targets/sparc64/opmatch.def:158:1-38
 */
void insn_fmuld_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmuld_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmulq defined at ../../../targets/sparc64/opmatch.def:159:1-38
 */
void insn_fmulq_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmulq_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fsmuld defined at ../../../targets/sparc64/opmatch.def:160:1-40
 */
void insn_fsmuld_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fsmuld_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fdmulq defined at ../../../targets/sparc64/opmatch.def:161:1-40
 */
void insn_fdmulq_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fdmulq_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fdivs defined at ../../../targets/sparc64/opmatch.def:162:1-38
 */
void insn_fdivs_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fdivs_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fdivd defined at ../../../targets/sparc64/opmatch.def:163:1-38
 */
void insn_fdivd_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fdivd_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fdivq defined at ../../../targets/sparc64/opmatch.def:164:1-38
 */
void insn_fdivq_freg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fdivq_e14e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn brz defined at ../../../targets/sparc64/opmatch.def:166:1-42
 */
void insn_brz_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brz_e16xu64(line, op_0, op_1);
}

/*
 * Insn brz,pt defined at ../../../targets/sparc64/opmatch.def:167:1-44
 */
void insn_brz_pt_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brz_pt_e16xu64(line, op_0, op_1);
}

/*
 * Insn brz,pn defined at ../../../targets/sparc64/opmatch.def:168:1-44
 */
void insn_brz_pn_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brz_pn_e16xu64(line, op_0, op_1);
}

/*
 * Insn brz,a defined at ../../../targets/sparc64/opmatch.def:169:1-41
 */
void insn_brz_a_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brz_a_e16xu64(line, op_0, op_1);
}

/*
 * Insn brz,a,pt defined at ../../../targets/sparc64/opmatch.def:170:1-44
 */
void insn_brz_a_pt_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brz_a_pt_e16xu64(line, op_0, op_1);
}

/*
 * Insn brz,a,pn defined at ../../../targets/sparc64/opmatch.def:171:1-44
 */
void insn_brz_a_pn_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brz_a_pn_e16xu64(line, op_0, op_1);
}

/*
 * Insn brlez defined at ../../../targets/sparc64/opmatch.def:172:1-45
 */
void insn_brlez_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brlez_e16xu64(line, op_0, op_1);
}

/*
 * Insn brlez,pt defined at ../../../targets/sparc64/opmatch.def:173:1-48
 */
void insn_brlez_pt_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brlez_pt_e16xu64(line, op_0, op_1);
}

/*
 * Insn brlez,pn defined at ../../../targets/sparc64/opmatch.def:174:1-48
 */
void insn_brlez_pn_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brlez_pn_e16xu64(line, op_0, op_1);
}

/*
 * Insn brlez,a defined at ../../../targets/sparc64/opmatch.def:175:1-45
 */
void insn_brlez_a_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brlez_a_e16xu64(line, op_0, op_1);
}

/*
 * Insn brlez,a,pt defined at ../../../targets/sparc64/opmatch.def:176:1-48
 */
void insn_brlez_a_pt_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brlez_a_pt_e16xu64(line, op_0, op_1);
}

/*
 * Insn brlez,a,pn defined at ../../../targets/sparc64/opmatch.def:177:1-48
 */
void insn_brlez_a_pn_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brlez_a_pn_e16xu64(line, op_0, op_1);
}

/*
 * Insn brlz defined at ../../../targets/sparc64/opmatch.def:178:1-43
 */
void insn_brlz_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brlz_e16xu64(line, op_0, op_1);
}

/*
 * Insn brlz,pt defined at ../../../targets/sparc64/opmatch.def:179:1-46
 */
void insn_brlz_pt_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brlz_pt_e16xu64(line, op_0, op_1);
}

/*
 * Insn brlz,pn defined at ../../../targets/sparc64/opmatch.def:180:1-46
 */
void insn_brlz_pn_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brlz_pn_e16xu64(line, op_0, op_1);
}

/*
 * Insn brlz,a defined at ../../../targets/sparc64/opmatch.def:181:1-43
 */
void insn_brlz_a_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brlz_a_e16xu64(line, op_0, op_1);
}

/*
 * Insn brlz,a,pt defined at ../../../targets/sparc64/opmatch.def:182:1-46
 */
void insn_brlz_a_pt_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brlz_a_pt_e16xu64(line, op_0, op_1);
}

/*
 * Insn brlz,a,pn defined at ../../../targets/sparc64/opmatch.def:183:1-46
 */
void insn_brlz_a_pn_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brlz_a_pn_e16xu64(line, op_0, op_1);
}

/*
 * Insn brnz defined at ../../../targets/sparc64/opmatch.def:184:1-43
 */
void insn_brnz_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brnz_e16xu64(line, op_0, op_1);
}

/*
 * Insn brnz,pt defined at ../../../targets/sparc64/opmatch.def:185:1-46
 */
void insn_brnz_pt_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brnz_pt_e16xu64(line, op_0, op_1);
}

/*
 * Insn brnz,pn defined at ../../../targets/sparc64/opmatch.def:186:1-46
 */
void insn_brnz_pn_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brnz_pn_e16xu64(line, op_0, op_1);
}

/*
 * Insn brnz,a defined at ../../../targets/sparc64/opmatch.def:187:1-43
 */
void insn_brnz_a_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brnz_a_e16xu64(line, op_0, op_1);
}

/*
 * Insn brnz,a,pt defined at ../../../targets/sparc64/opmatch.def:188:1-46
 */
void insn_brnz_a_pt_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brnz_a_pt_e16xu64(line, op_0, op_1);
}

/*
 * Insn brnz,a,pn defined at ../../../targets/sparc64/opmatch.def:189:1-46
 */
void insn_brnz_a_pn_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brnz_a_pn_e16xu64(line, op_0, op_1);
}

/*
 * Insn brgz defined at ../../../targets/sparc64/opmatch.def:190:1-43
 */
void insn_brgz_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brgz_e16xu64(line, op_0, op_1);
}

/*
 * Insn brgz,pt defined at ../../../targets/sparc64/opmatch.def:191:1-46
 */
void insn_brgz_pt_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brgz_pt_e16xu64(line, op_0, op_1);
}

/*
 * Insn brgz,pn defined at ../../../targets/sparc64/opmatch.def:192:1-46
 */
void insn_brgz_pn_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brgz_pn_e16xu64(line, op_0, op_1);
}

/*
 * Insn brgz,a defined at ../../../targets/sparc64/opmatch.def:193:1-43
 */
void insn_brgz_a_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brgz_a_e16xu64(line, op_0, op_1);
}

/*
 * Insn brgz,a,pt defined at ../../../targets/sparc64/opmatch.def:194:1-46
 */
void insn_brgz_a_pt_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brgz_a_pt_e16xu64(line, op_0, op_1);
}

/*
 * Insn brgz,a,pn defined at ../../../targets/sparc64/opmatch.def:195:1-46
 */
void insn_brgz_a_pn_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brgz_a_pn_e16xu64(line, op_0, op_1);
}

/*
 * Insn brgez defined at ../../../targets/sparc64/opmatch.def:196:1-45
 */
void insn_brgez_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brgez_e16xu64(line, op_0, op_1);
}

/*
 * Insn brgez,pt defined at ../../../targets/sparc64/opmatch.def:197:1-48
 */
void insn_brgez_pt_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brgez_pt_e16xu64(line, op_0, op_1);
}

/*
 * Insn brgez,pn defined at ../../../targets/sparc64/opmatch.def:198:1-48
 */
void insn_brgez_pn_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brgez_pn_e16xu64(line, op_0, op_1);
}

/*
 * Insn brgez,a defined at ../../../targets/sparc64/opmatch.def:199:1-45
 */
void insn_brgez_a_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brgez_a_e16xu64(line, op_0, op_1);
}

/*
 * Insn brgez,a,pt defined at ../../../targets/sparc64/opmatch.def:200:1-48
 */
void insn_brgez_a_pt_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brgez_a_pt_e16xu64(line, op_0, op_1);
}

/*
 * Insn brgez,a,pn defined at ../../../targets/sparc64/opmatch.def:201:1-48
 */
void insn_brgez_a_pn_reg_symbol(int line, uint8_t op_0, struct expr * op_1) {
   brgez_a_pn_e16xu64(line, op_0, op_1);
}

/*
 * Insn fba defined at ../../../targets/sparc64/opmatch.def:204:1-35
 */
void insn_fba_symbol(int line, struct expr * op_0) {
   fba_xu64(line, op_0);
}

/*
 * Insn fba,a defined at ../../../targets/sparc64/opmatch.def:205:1-35
 */
void insn_fba_a_symbol(int line, struct expr * op_0) {
   fba_a_xu64(line, op_0);
}

/*
 * Insn fbn defined at ../../../targets/sparc64/opmatch.def:206:1-35
 */
void insn_fbn_symbol(int line, struct expr * op_0) {
   fbn_xu64(line, op_0);
}

/*
 * Insn fbn,a defined at ../../../targets/sparc64/opmatch.def:207:1-35
 */
void insn_fbn_a_symbol(int line, struct expr * op_0) {
   fbn_a_xu64(line, op_0);
}

/*
 * Insn fbu defined at ../../../targets/sparc64/opmatch.def:208:1-35
 */
void insn_fbu_symbol(int line, struct expr * op_0) {
   fbu_xu64(line, op_0);
}

/*
 * Insn fbu,a defined at ../../../targets/sparc64/opmatch.def:209:1-35
 */
void insn_fbu_a_symbol(int line, struct expr * op_0) {
   fbu_a_xu64(line, op_0);
}

/*
 * Insn fbg defined at ../../../targets/sparc64/opmatch.def:210:1-35
 */
void insn_fbg_symbol(int line, struct expr * op_0) {
   fbg_xu64(line, op_0);
}

/*
 * Insn fbg,a defined at ../../../targets/sparc64/opmatch.def:211:1-35
 */
void insn_fbg_a_symbol(int line, struct expr * op_0) {
   fbg_a_xu64(line, op_0);
}

/*
 * Insn fbug defined at ../../../targets/sparc64/opmatch.def:212:1-37
 */
void insn_fbug_symbol(int line, struct expr * op_0) {
   fbug_xu64(line, op_0);
}

/*
 * Insn fbug,a defined at ../../../targets/sparc64/opmatch.def:213:1-37
 */
void insn_fbug_a_symbol(int line, struct expr * op_0) {
   fbug_a_xu64(line, op_0);
}

/*
 * Insn fbl defined at ../../../targets/sparc64/opmatch.def:214:1-35
 */
void insn_fbl_symbol(int line, struct expr * op_0) {
   fbl_xu64(line, op_0);
}

/*
 * Insn fbl,a defined at ../../../targets/sparc64/opmatch.def:215:1-35
 */
void insn_fbl_a_symbol(int line, struct expr * op_0) {
   fbl_a_xu64(line, op_0);
}

/*
 * Insn fbul defined at ../../../targets/sparc64/opmatch.def:216:1-37
 */
void insn_fbul_symbol(int line, struct expr * op_0) {
   fbul_xu64(line, op_0);
}

/*
 * Insn fbul,a defined at ../../../targets/sparc64/opmatch.def:217:1-37
 */
void insn_fbul_a_symbol(int line, struct expr * op_0) {
   fbul_a_xu64(line, op_0);
}

/*
 * Insn fblg defined at ../../../targets/sparc64/opmatch.def:218:1-37
 */
void insn_fblg_symbol(int line, struct expr * op_0) {
   fblg_xu64(line, op_0);
}

/*
 * Insn fblg,a defined at ../../../targets/sparc64/opmatch.def:219:1-37
 */
void insn_fblg_a_symbol(int line, struct expr * op_0) {
   fblg_a_xu64(line, op_0);
}

/*
 * Insn fbne defined at ../../../targets/sparc64/opmatch.def:220:1-37
 */
void insn_fbne_symbol(int line, struct expr * op_0) {
   fbne_xu64(line, op_0);
}

/*
 * Insn fbne,a defined at ../../../targets/sparc64/opmatch.def:221:1-37
 */
void insn_fbne_a_symbol(int line, struct expr * op_0) {
   fbne_a_xu64(line, op_0);
}

/*
 * Insn fbe defined at ../../../targets/sparc64/opmatch.def:222:1-35
 */
void insn_fbe_symbol(int line, struct expr * op_0) {
   fbe_xu64(line, op_0);
}

/*
 * Insn fbe,a defined at ../../../targets/sparc64/opmatch.def:223:1-35
 */
void insn_fbe_a_symbol(int line, struct expr * op_0) {
   fbe_a_xu64(line, op_0);
}

/*
 * Insn fbue defined at ../../../targets/sparc64/opmatch.def:224:1-37
 */
void insn_fbue_symbol(int line, struct expr * op_0) {
   fbue_xu64(line, op_0);
}

/*
 * Insn fbue,a defined at ../../../targets/sparc64/opmatch.def:225:1-37
 */
void insn_fbue_a_symbol(int line, struct expr * op_0) {
   fbue_a_xu64(line, op_0);
}

/*
 * Insn fbge defined at ../../../targets/sparc64/opmatch.def:226:1-37
 */
void insn_fbge_symbol(int line, struct expr * op_0) {
   fbge_xu64(line, op_0);
}

/*
 * Insn fbge,a defined at ../../../targets/sparc64/opmatch.def:227:1-37
 */
void insn_fbge_a_symbol(int line, struct expr * op_0) {
   fbge_a_xu64(line, op_0);
}

/*
 * Insn fbuge defined at ../../../targets/sparc64/opmatch.def:228:1-39
 */
void insn_fbuge_symbol(int line, struct expr * op_0) {
   fbuge_xu64(line, op_0);
}

/*
 * Insn fbuge,a defined at ../../../targets/sparc64/opmatch.def:229:1-39
 */
void insn_fbuge_a_symbol(int line, struct expr * op_0) {
   fbuge_a_xu64(line, op_0);
}

/*
 * Insn fble defined at ../../../targets/sparc64/opmatch.def:230:1-37
 */
void insn_fble_symbol(int line, struct expr * op_0) {
   fble_xu64(line, op_0);
}

/*
 * Insn fble,a defined at ../../../targets/sparc64/opmatch.def:231:1-37
 */
void insn_fble_a_symbol(int line, struct expr * op_0) {
   fble_a_xu64(line, op_0);
}

/*
 * Insn fbule defined at ../../../targets/sparc64/opmatch.def:232:1-39
 */
void insn_fbule_symbol(int line, struct expr * op_0) {
   fbule_xu64(line, op_0);
}

/*
 * Insn fbule,a defined at ../../../targets/sparc64/opmatch.def:233:1-39
 */
void insn_fbule_a_symbol(int line, struct expr * op_0) {
   fbule_a_xu64(line, op_0);
}

/*
 * Insn fbo defined at ../../../targets/sparc64/opmatch.def:234:1-35
 */
void insn_fbo_symbol(int line, struct expr * op_0) {
   fbo_xu64(line, op_0);
}

/*
 * Insn fbo,a defined at ../../../targets/sparc64/opmatch.def:235:1-35
 */
void insn_fbo_a_symbol(int line, struct expr * op_0) {
   fbo_a_xu64(line, op_0);
}

/*
 * Insn fbnz defined at ../../../targets/sparc64/opmatch.def:237:1-37
 */
void insn_fbnz_symbol(int line, struct expr * op_0) {
   fbnz_xu64(line, op_0);
}

/*
 * Insn fbnz,a defined at ../../../targets/sparc64/opmatch.def:238:1-37
 */
void insn_fbnz_a_symbol(int line, struct expr * op_0) {
   fbnz_a_xu64(line, op_0);
}

/*
 * Insn fbz defined at ../../../targets/sparc64/opmatch.def:239:1-35
 */
void insn_fbz_symbol(int line, struct expr * op_0) {
   fbz_xu64(line, op_0);
}

/*
 * Insn fbz,a defined at ../../../targets/sparc64/opmatch.def:240:1-35
 */
void insn_fbz_a_symbol(int line, struct expr * op_0) {
   fbz_a_xu64(line, op_0);
}

/*
 * Insn fba defined at ../../../targets/sparc64/opmatch.def:243:1-45
 */
void insn_fba_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fba_e13xu64(line, op_0, op_1);
}

/*
 * Insn fba,pt defined at ../../../targets/sparc64/opmatch.def:244:1-47
 */
void insn_fba_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fba_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fba,pn defined at ../../../targets/sparc64/opmatch.def:245:1-47
 */
void insn_fba_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fba_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fba,a defined at ../../../targets/sparc64/opmatch.def:246:1-44
 */
void insn_fba_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fba_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fba,a,pt defined at ../../../targets/sparc64/opmatch.def:247:1-47
 */
void insn_fba_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fba_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fba,a,pn defined at ../../../targets/sparc64/opmatch.def:248:1-47
 */
void insn_fba_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fba_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbn defined at ../../../targets/sparc64/opmatch.def:249:1-45
 */
void insn_fbn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbn,pt defined at ../../../targets/sparc64/opmatch.def:250:1-47
 */
void insn_fbn_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbn_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbn,pn defined at ../../../targets/sparc64/opmatch.def:251:1-47
 */
void insn_fbn_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbn_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbn,a defined at ../../../targets/sparc64/opmatch.def:252:1-44
 */
void insn_fbn_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbn_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbn,a,pt defined at ../../../targets/sparc64/opmatch.def:253:1-47
 */
void insn_fbn_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbn_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbn,a,pn defined at ../../../targets/sparc64/opmatch.def:254:1-47
 */
void insn_fbn_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbn_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbu defined at ../../../targets/sparc64/opmatch.def:255:1-45
 */
void insn_fbu_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbu_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbu,pt defined at ../../../targets/sparc64/opmatch.def:256:1-47
 */
void insn_fbu_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbu_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbu,pn defined at ../../../targets/sparc64/opmatch.def:257:1-47
 */
void insn_fbu_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbu_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbu,a defined at ../../../targets/sparc64/opmatch.def:258:1-44
 */
void insn_fbu_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbu_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbu,a,pt defined at ../../../targets/sparc64/opmatch.def:259:1-47
 */
void insn_fbu_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbu_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbu,a,pn defined at ../../../targets/sparc64/opmatch.def:260:1-47
 */
void insn_fbu_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbu_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbg defined at ../../../targets/sparc64/opmatch.def:261:1-45
 */
void insn_fbg_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbg_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbg,pt defined at ../../../targets/sparc64/opmatch.def:262:1-47
 */
void insn_fbg_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbg_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbg,pn defined at ../../../targets/sparc64/opmatch.def:263:1-47
 */
void insn_fbg_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbg_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbg,a defined at ../../../targets/sparc64/opmatch.def:264:1-44
 */
void insn_fbg_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbg_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbg,a,pt defined at ../../../targets/sparc64/opmatch.def:265:1-47
 */
void insn_fbg_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbg_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbg,a,pn defined at ../../../targets/sparc64/opmatch.def:266:1-47
 */
void insn_fbg_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbg_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbug defined at ../../../targets/sparc64/opmatch.def:267:1-46
 */
void insn_fbug_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbug_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbug,pt defined at ../../../targets/sparc64/opmatch.def:268:1-49
 */
void insn_fbug_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbug_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbug,pn defined at ../../../targets/sparc64/opmatch.def:269:1-49
 */
void insn_fbug_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbug_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbug,a defined at ../../../targets/sparc64/opmatch.def:270:1-46
 */
void insn_fbug_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbug_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbug,a,pt defined at ../../../targets/sparc64/opmatch.def:271:1-49
 */
void insn_fbug_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbug_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbug,a,pn defined at ../../../targets/sparc64/opmatch.def:272:1-49
 */
void insn_fbug_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbug_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbl defined at ../../../targets/sparc64/opmatch.def:273:1-45
 */
void insn_fbl_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbl_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbl,pt defined at ../../../targets/sparc64/opmatch.def:274:1-47
 */
void insn_fbl_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbl_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbl,pn defined at ../../../targets/sparc64/opmatch.def:275:1-47
 */
void insn_fbl_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbl_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbl,a defined at ../../../targets/sparc64/opmatch.def:276:1-44
 */
void insn_fbl_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbl_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbl,a,pt defined at ../../../targets/sparc64/opmatch.def:277:1-47
 */
void insn_fbl_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbl_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbl,a,pn defined at ../../../targets/sparc64/opmatch.def:278:1-47
 */
void insn_fbl_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbl_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbul defined at ../../../targets/sparc64/opmatch.def:279:1-46
 */
void insn_fbul_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbul_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbul,pt defined at ../../../targets/sparc64/opmatch.def:280:1-49
 */
void insn_fbul_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbul_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbul,pn defined at ../../../targets/sparc64/opmatch.def:281:1-49
 */
void insn_fbul_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbul_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbul,a defined at ../../../targets/sparc64/opmatch.def:282:1-46
 */
void insn_fbul_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbul_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbul,a,pt defined at ../../../targets/sparc64/opmatch.def:283:1-49
 */
void insn_fbul_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbul_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbul,a,pn defined at ../../../targets/sparc64/opmatch.def:284:1-49
 */
void insn_fbul_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbul_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fblg defined at ../../../targets/sparc64/opmatch.def:285:1-46
 */
void insn_fblg_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fblg_e13xu64(line, op_0, op_1);
}

/*
 * Insn fblg,pt defined at ../../../targets/sparc64/opmatch.def:286:1-49
 */
void insn_fblg_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fblg_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fblg,pn defined at ../../../targets/sparc64/opmatch.def:287:1-49
 */
void insn_fblg_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fblg_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fblg,a defined at ../../../targets/sparc64/opmatch.def:288:1-46
 */
void insn_fblg_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fblg_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fblg,a,pt defined at ../../../targets/sparc64/opmatch.def:289:1-49
 */
void insn_fblg_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fblg_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fblg,a,pn defined at ../../../targets/sparc64/opmatch.def:290:1-49
 */
void insn_fblg_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fblg_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbne defined at ../../../targets/sparc64/opmatch.def:291:1-46
 */
void insn_fbne_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbne_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbne,pt defined at ../../../targets/sparc64/opmatch.def:292:1-49
 */
void insn_fbne_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbne_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbne,pn defined at ../../../targets/sparc64/opmatch.def:293:1-49
 */
void insn_fbne_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbne_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbne,a defined at ../../../targets/sparc64/opmatch.def:294:1-46
 */
void insn_fbne_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbne_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbne,a,pt defined at ../../../targets/sparc64/opmatch.def:295:1-49
 */
void insn_fbne_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbne_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbne,a,pn defined at ../../../targets/sparc64/opmatch.def:296:1-49
 */
void insn_fbne_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbne_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbe defined at ../../../targets/sparc64/opmatch.def:297:1-45
 */
void insn_fbe_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbe_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbe,pt defined at ../../../targets/sparc64/opmatch.def:298:1-47
 */
void insn_fbe_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbe_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbe,pn defined at ../../../targets/sparc64/opmatch.def:299:1-47
 */
void insn_fbe_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbe_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbe,a defined at ../../../targets/sparc64/opmatch.def:300:1-44
 */
void insn_fbe_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbe_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbe,a,pt defined at ../../../targets/sparc64/opmatch.def:301:1-47
 */
void insn_fbe_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbe_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbe,a,pn defined at ../../../targets/sparc64/opmatch.def:302:1-47
 */
void insn_fbe_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbe_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbue defined at ../../../targets/sparc64/opmatch.def:303:1-46
 */
void insn_fbue_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbue_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbue,pt defined at ../../../targets/sparc64/opmatch.def:304:1-49
 */
void insn_fbue_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbue_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbue,pn defined at ../../../targets/sparc64/opmatch.def:305:1-49
 */
void insn_fbue_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbue_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbue,a defined at ../../../targets/sparc64/opmatch.def:306:1-46
 */
void insn_fbue_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbue_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbue,a,pt defined at ../../../targets/sparc64/opmatch.def:307:1-49
 */
void insn_fbue_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbue_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbue,a,pn defined at ../../../targets/sparc64/opmatch.def:308:1-49
 */
void insn_fbue_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbue_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbge defined at ../../../targets/sparc64/opmatch.def:309:1-46
 */
void insn_fbge_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbge_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbge,pt defined at ../../../targets/sparc64/opmatch.def:310:1-49
 */
void insn_fbge_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbge_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbge,pn defined at ../../../targets/sparc64/opmatch.def:311:1-49
 */
void insn_fbge_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbge_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbge,a defined at ../../../targets/sparc64/opmatch.def:312:1-46
 */
void insn_fbge_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbge_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbge,a,pt defined at ../../../targets/sparc64/opmatch.def:313:1-49
 */
void insn_fbge_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbge_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbge,a,pn defined at ../../../targets/sparc64/opmatch.def:314:1-49
 */
void insn_fbge_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbge_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbuge defined at ../../../targets/sparc64/opmatch.def:315:1-48
 */
void insn_fbuge_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbuge_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbuge,pt defined at ../../../targets/sparc64/opmatch.def:316:1-51
 */
void insn_fbuge_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbuge_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbuge,pn defined at ../../../targets/sparc64/opmatch.def:317:1-51
 */
void insn_fbuge_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbuge_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbuge,a defined at ../../../targets/sparc64/opmatch.def:318:1-48
 */
void insn_fbuge_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbuge_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbuge,a,pt defined at ../../../targets/sparc64/opmatch.def:319:1-51
 */
void insn_fbuge_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbuge_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbuge,a,pn defined at ../../../targets/sparc64/opmatch.def:320:1-51
 */
void insn_fbuge_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbuge_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fble defined at ../../../targets/sparc64/opmatch.def:321:1-46
 */
void insn_fble_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fble_e13xu64(line, op_0, op_1);
}

/*
 * Insn fble,pt defined at ../../../targets/sparc64/opmatch.def:322:1-49
 */
void insn_fble_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fble_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fble,pn defined at ../../../targets/sparc64/opmatch.def:323:1-49
 */
void insn_fble_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fble_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fble,a defined at ../../../targets/sparc64/opmatch.def:324:1-46
 */
void insn_fble_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fble_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fble,a,pt defined at ../../../targets/sparc64/opmatch.def:325:1-49
 */
void insn_fble_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fble_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fble,a,pn defined at ../../../targets/sparc64/opmatch.def:326:1-49
 */
void insn_fble_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fble_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbule defined at ../../../targets/sparc64/opmatch.def:327:1-48
 */
void insn_fbule_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbule_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbule,pt defined at ../../../targets/sparc64/opmatch.def:328:1-51
 */
void insn_fbule_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbule_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbule,pn defined at ../../../targets/sparc64/opmatch.def:329:1-51
 */
void insn_fbule_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbule_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbule,a defined at ../../../targets/sparc64/opmatch.def:330:1-48
 */
void insn_fbule_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbule_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbule,a,pt defined at ../../../targets/sparc64/opmatch.def:331:1-51
 */
void insn_fbule_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbule_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbule,a,pn defined at ../../../targets/sparc64/opmatch.def:332:1-51
 */
void insn_fbule_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbule_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbo defined at ../../../targets/sparc64/opmatch.def:333:1-45
 */
void insn_fbo_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbo_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbo,pt defined at ../../../targets/sparc64/opmatch.def:334:1-47
 */
void insn_fbo_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbo_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbo,pn defined at ../../../targets/sparc64/opmatch.def:335:1-47
 */
void insn_fbo_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbo_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbo,a defined at ../../../targets/sparc64/opmatch.def:336:1-44
 */
void insn_fbo_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbo_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbo,a,pt defined at ../../../targets/sparc64/opmatch.def:337:1-47
 */
void insn_fbo_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbo_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbo,a,pn defined at ../../../targets/sparc64/opmatch.def:338:1-47
 */
void insn_fbo_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbo_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbnz defined at ../../../targets/sparc64/opmatch.def:340:1-46
 */
void insn_fbnz_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbnz_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbnz,pt defined at ../../../targets/sparc64/opmatch.def:341:1-49
 */
void insn_fbnz_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbnz_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbnz,pn defined at ../../../targets/sparc64/opmatch.def:342:1-49
 */
void insn_fbnz_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbnz_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbnz,a defined at ../../../targets/sparc64/opmatch.def:343:1-46
 */
void insn_fbnz_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbnz_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbnz,a,pt defined at ../../../targets/sparc64/opmatch.def:344:1-49
 */
void insn_fbnz_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbnz_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbnz,a,pn defined at ../../../targets/sparc64/opmatch.def:345:1-49
 */
void insn_fbnz_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbnz_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbz defined at ../../../targets/sparc64/opmatch.def:346:1-45
 */
void insn_fbz_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbz_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbz,pt defined at ../../../targets/sparc64/opmatch.def:347:1-47
 */
void insn_fbz_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbz_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbz,pn defined at ../../../targets/sparc64/opmatch.def:348:1-47
 */
void insn_fbz_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbz_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbz,a defined at ../../../targets/sparc64/opmatch.def:349:1-44
 */
void insn_fbz_a_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbz_a_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbz,a,pt defined at ../../../targets/sparc64/opmatch.def:350:1-47
 */
void insn_fbz_a_pt_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbz_a_pt_e13xu64(line, op_0, op_1);
}

/*
 * Insn fbz,a,pn defined at ../../../targets/sparc64/opmatch.def:351:1-47
 */
void insn_fbz_a_pn_fcc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   fbz_a_pn_e13xu64(line, op_0, op_1);
}

/*
 * Insn ba defined at ../../../targets/sparc64/opmatch.def:354:1-32
 */
void insn_ba_symbol(int line, struct expr * op_0) {
   ba_xu64(line, op_0);
}

/*
 * Insn ba,a defined at ../../../targets/sparc64/opmatch.def:355:1-32
 */
void insn_ba_a_symbol(int line, struct expr * op_0) {
   ba_a_xu64(line, op_0);
}

/*
 * Insn bn defined at ../../../targets/sparc64/opmatch.def:356:1-32
 */
void insn_bn_symbol(int line, struct expr * op_0) {
   bn_xu64(line, op_0);
}

/*
 * Insn bn,a defined at ../../../targets/sparc64/opmatch.def:357:1-32
 */
void insn_bn_a_symbol(int line, struct expr * op_0) {
   bn_a_xu64(line, op_0);
}

/*
 * Insn bne defined at ../../../targets/sparc64/opmatch.def:358:1-34
 */
void insn_bne_symbol(int line, struct expr * op_0) {
   bne_xu64(line, op_0);
}

/*
 * Insn bne,a defined at ../../../targets/sparc64/opmatch.def:359:1-34
 */
void insn_bne_a_symbol(int line, struct expr * op_0) {
   bne_a_xu64(line, op_0);
}

/*
 * Insn be defined at ../../../targets/sparc64/opmatch.def:360:1-32
 */
void insn_be_symbol(int line, struct expr * op_0) {
   be_xu64(line, op_0);
}

/*
 * Insn be,a defined at ../../../targets/sparc64/opmatch.def:361:1-32
 */
void insn_be_a_symbol(int line, struct expr * op_0) {
   be_a_xu64(line, op_0);
}

/*
 * Insn bg defined at ../../../targets/sparc64/opmatch.def:362:1-32
 */
void insn_bg_symbol(int line, struct expr * op_0) {
   bg_xu64(line, op_0);
}

/*
 * Insn bg,a defined at ../../../targets/sparc64/opmatch.def:363:1-32
 */
void insn_bg_a_symbol(int line, struct expr * op_0) {
   bg_a_xu64(line, op_0);
}

/*
 * Insn ble defined at ../../../targets/sparc64/opmatch.def:364:1-34
 */
void insn_ble_symbol(int line, struct expr * op_0) {
   ble_xu64(line, op_0);
}

/*
 * Insn ble,a defined at ../../../targets/sparc64/opmatch.def:365:1-34
 */
void insn_ble_a_symbol(int line, struct expr * op_0) {
   ble_a_xu64(line, op_0);
}

/*
 * Insn bge defined at ../../../targets/sparc64/opmatch.def:366:1-34
 */
void insn_bge_symbol(int line, struct expr * op_0) {
   bge_xu64(line, op_0);
}

/*
 * Insn bge,a defined at ../../../targets/sparc64/opmatch.def:367:1-34
 */
void insn_bge_a_symbol(int line, struct expr * op_0) {
   bge_a_xu64(line, op_0);
}

/*
 * Insn bl defined at ../../../targets/sparc64/opmatch.def:368:1-32
 */
void insn_bl_symbol(int line, struct expr * op_0) {
   bl_xu64(line, op_0);
}

/*
 * Insn bl,a defined at ../../../targets/sparc64/opmatch.def:369:1-32
 */
void insn_bl_a_symbol(int line, struct expr * op_0) {
   bl_a_xu64(line, op_0);
}

/*
 * Insn bgu defined at ../../../targets/sparc64/opmatch.def:370:1-34
 */
void insn_bgu_symbol(int line, struct expr * op_0) {
   bgu_xu64(line, op_0);
}

/*
 * Insn bgu,a defined at ../../../targets/sparc64/opmatch.def:371:1-34
 */
void insn_bgu_a_symbol(int line, struct expr * op_0) {
   bgu_a_xu64(line, op_0);
}

/*
 * Insn bleu defined at ../../../targets/sparc64/opmatch.def:372:1-36
 */
void insn_bleu_symbol(int line, struct expr * op_0) {
   bleu_xu64(line, op_0);
}

/*
 * Insn bleu,a defined at ../../../targets/sparc64/opmatch.def:373:1-36
 */
void insn_bleu_a_symbol(int line, struct expr * op_0) {
   bleu_a_xu64(line, op_0);
}

/*
 * Insn bcc defined at ../../../targets/sparc64/opmatch.def:374:1-34
 */
void insn_bcc_symbol(int line, struct expr * op_0) {
   bcc_xu64(line, op_0);
}

/*
 * Insn bcc,a defined at ../../../targets/sparc64/opmatch.def:375:1-34
 */
void insn_bcc_a_symbol(int line, struct expr * op_0) {
   bcc_a_xu64(line, op_0);
}

/*
 * Insn bcs defined at ../../../targets/sparc64/opmatch.def:376:1-34
 */
void insn_bcs_symbol(int line, struct expr * op_0) {
   bcs_xu64(line, op_0);
}

/*
 * Insn bcs,a defined at ../../../targets/sparc64/opmatch.def:377:1-34
 */
void insn_bcs_a_symbol(int line, struct expr * op_0) {
   bcs_a_xu64(line, op_0);
}

/*
 * Insn bpos defined at ../../../targets/sparc64/opmatch.def:378:1-36
 */
void insn_bpos_symbol(int line, struct expr * op_0) {
   bpos_xu64(line, op_0);
}

/*
 * Insn bpos,a defined at ../../../targets/sparc64/opmatch.def:379:1-36
 */
void insn_bpos_a_symbol(int line, struct expr * op_0) {
   bpos_a_xu64(line, op_0);
}

/*
 * Insn bneg defined at ../../../targets/sparc64/opmatch.def:380:1-36
 */
void insn_bneg_symbol(int line, struct expr * op_0) {
   bneg_xu64(line, op_0);
}

/*
 * Insn bneg,a defined at ../../../targets/sparc64/opmatch.def:381:1-36
 */
void insn_bneg_a_symbol(int line, struct expr * op_0) {
   bneg_a_xu64(line, op_0);
}

/*
 * Insn bvc defined at ../../../targets/sparc64/opmatch.def:382:1-34
 */
void insn_bvc_symbol(int line, struct expr * op_0) {
   bvc_xu64(line, op_0);
}

/*
 * Insn bvc,a defined at ../../../targets/sparc64/opmatch.def:383:1-34
 */
void insn_bvc_a_symbol(int line, struct expr * op_0) {
   bvc_a_xu64(line, op_0);
}

/*
 * Insn bvs defined at ../../../targets/sparc64/opmatch.def:384:1-34
 */
void insn_bvs_symbol(int line, struct expr * op_0) {
   bvs_xu64(line, op_0);
}

/*
 * Insn bvs,a defined at ../../../targets/sparc64/opmatch.def:385:1-34
 */
void insn_bvs_a_symbol(int line, struct expr * op_0) {
   bvs_a_xu64(line, op_0);
}

/*
 * Insn bnz defined at ../../../targets/sparc64/opmatch.def:387:1-34
 */
void insn_bnz_symbol(int line, struct expr * op_0) {
   bnz_xu64(line, op_0);
}

/*
 * Insn bnz,a defined at ../../../targets/sparc64/opmatch.def:388:1-34
 */
void insn_bnz_a_symbol(int line, struct expr * op_0) {
   bnz_a_xu64(line, op_0);
}

/*
 * Insn bz defined at ../../../targets/sparc64/opmatch.def:389:1-32
 */
void insn_bz_symbol(int line, struct expr * op_0) {
   bz_xu64(line, op_0);
}

/*
 * Insn bz,a defined at ../../../targets/sparc64/opmatch.def:390:1-32
 */
void insn_bz_a_symbol(int line, struct expr * op_0) {
   bz_a_xu64(line, op_0);
}

/*
 * Insn bgeu defined at ../../../targets/sparc64/opmatch.def:391:1-35
 */
void insn_bgeu_symbol(int line, struct expr * op_0) {
   bgeu_xu64(line, op_0);
}

/*
 * Insn bgeu,a defined at ../../../targets/sparc64/opmatch.def:392:1-35
 */
void insn_bgeu_a_symbol(int line, struct expr * op_0) {
   bgeu_a_xu64(line, op_0);
}

/*
 * Insn blu defined at ../../../targets/sparc64/opmatch.def:393:1-34
 */
void insn_blu_symbol(int line, struct expr * op_0) {
   blu_xu64(line, op_0);
}

/*
 * Insn blu,a defined at ../../../targets/sparc64/opmatch.def:394:1-34
 */
void insn_blu_a_symbol(int line, struct expr * op_0) {
   blu_a_xu64(line, op_0);
}

/*
 * Insn ba defined at ../../../targets/sparc64/opmatch.def:397:1-41
 */
void insn_ba_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ba_e17xu64(line, op_0, op_1);
}

/*
 * Insn ba,pt defined at ../../../targets/sparc64/opmatch.def:398:1-43
 */
void insn_ba_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ba_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn ba,pn defined at ../../../targets/sparc64/opmatch.def:399:1-43
 */
void insn_ba_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ba_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn ba,a defined at ../../../targets/sparc64/opmatch.def:400:1-40
 */
void insn_ba_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ba_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn ba,a,pt defined at ../../../targets/sparc64/opmatch.def:401:1-43
 */
void insn_ba_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ba_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn ba,a,pn defined at ../../../targets/sparc64/opmatch.def:402:1-43
 */
void insn_ba_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ba_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bn defined at ../../../targets/sparc64/opmatch.def:403:1-41
 */
void insn_bn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bn,pt defined at ../../../targets/sparc64/opmatch.def:404:1-43
 */
void insn_bn_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bn_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bn,pn defined at ../../../targets/sparc64/opmatch.def:405:1-43
 */
void insn_bn_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bn_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bn,a defined at ../../../targets/sparc64/opmatch.def:406:1-40
 */
void insn_bn_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bn_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bn,a,pt defined at ../../../targets/sparc64/opmatch.def:407:1-43
 */
void insn_bn_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bn_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bn,a,pn defined at ../../../targets/sparc64/opmatch.def:408:1-43
 */
void insn_bn_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bn_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bne defined at ../../../targets/sparc64/opmatch.def:409:1-43
 */
void insn_bne_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bne_e17xu64(line, op_0, op_1);
}

/*
 * Insn bne,pt defined at ../../../targets/sparc64/opmatch.def:410:1-45
 */
void insn_bne_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bne_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bne,pn defined at ../../../targets/sparc64/opmatch.def:411:1-45
 */
void insn_bne_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bne_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bne,a defined at ../../../targets/sparc64/opmatch.def:412:1-42
 */
void insn_bne_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bne_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bne,a,pt defined at ../../../targets/sparc64/opmatch.def:413:1-45
 */
void insn_bne_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bne_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bne,a,pn defined at ../../../targets/sparc64/opmatch.def:414:1-45
 */
void insn_bne_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bne_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn be defined at ../../../targets/sparc64/opmatch.def:415:1-41
 */
void insn_be_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   be_e17xu64(line, op_0, op_1);
}

/*
 * Insn be,pt defined at ../../../targets/sparc64/opmatch.def:416:1-43
 */
void insn_be_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   be_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn be,pn defined at ../../../targets/sparc64/opmatch.def:417:1-43
 */
void insn_be_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   be_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn be,a defined at ../../../targets/sparc64/opmatch.def:418:1-40
 */
void insn_be_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   be_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn be,a,pt defined at ../../../targets/sparc64/opmatch.def:419:1-43
 */
void insn_be_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   be_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn be,a,pn defined at ../../../targets/sparc64/opmatch.def:420:1-43
 */
void insn_be_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   be_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bg defined at ../../../targets/sparc64/opmatch.def:421:1-41
 */
void insn_bg_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bg_e17xu64(line, op_0, op_1);
}

/*
 * Insn bg,pt defined at ../../../targets/sparc64/opmatch.def:422:1-43
 */
void insn_bg_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bg_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bg,pn defined at ../../../targets/sparc64/opmatch.def:423:1-43
 */
void insn_bg_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bg_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bg,a defined at ../../../targets/sparc64/opmatch.def:424:1-40
 */
void insn_bg_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bg_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bg,a,pt defined at ../../../targets/sparc64/opmatch.def:425:1-43
 */
void insn_bg_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bg_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bg,a,pn defined at ../../../targets/sparc64/opmatch.def:426:1-43
 */
void insn_bg_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bg_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn ble defined at ../../../targets/sparc64/opmatch.def:427:1-43
 */
void insn_ble_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ble_e17xu64(line, op_0, op_1);
}

/*
 * Insn ble,pt defined at ../../../targets/sparc64/opmatch.def:428:1-45
 */
void insn_ble_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ble_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn ble,pn defined at ../../../targets/sparc64/opmatch.def:429:1-45
 */
void insn_ble_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ble_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn ble,a defined at ../../../targets/sparc64/opmatch.def:430:1-42
 */
void insn_ble_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ble_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn ble,a,pt defined at ../../../targets/sparc64/opmatch.def:431:1-45
 */
void insn_ble_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ble_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn ble,a,pn defined at ../../../targets/sparc64/opmatch.def:432:1-45
 */
void insn_ble_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   ble_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bge defined at ../../../targets/sparc64/opmatch.def:433:1-43
 */
void insn_bge_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bge_e17xu64(line, op_0, op_1);
}

/*
 * Insn bge,pt defined at ../../../targets/sparc64/opmatch.def:434:1-45
 */
void insn_bge_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bge_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bge,pn defined at ../../../targets/sparc64/opmatch.def:435:1-45
 */
void insn_bge_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bge_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bge,a defined at ../../../targets/sparc64/opmatch.def:436:1-42
 */
void insn_bge_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bge_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bge,a,pt defined at ../../../targets/sparc64/opmatch.def:437:1-45
 */
void insn_bge_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bge_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bge,a,pn defined at ../../../targets/sparc64/opmatch.def:438:1-45
 */
void insn_bge_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bge_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bl defined at ../../../targets/sparc64/opmatch.def:439:1-41
 */
void insn_bl_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bl_e17xu64(line, op_0, op_1);
}

/*
 * Insn bl,pt defined at ../../../targets/sparc64/opmatch.def:440:1-43
 */
void insn_bl_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bl_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bl,pn defined at ../../../targets/sparc64/opmatch.def:441:1-43
 */
void insn_bl_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bl_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bl,a defined at ../../../targets/sparc64/opmatch.def:442:1-40
 */
void insn_bl_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bl_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bl,a,pt defined at ../../../targets/sparc64/opmatch.def:443:1-43
 */
void insn_bl_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bl_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bl,a,pn defined at ../../../targets/sparc64/opmatch.def:444:1-43
 */
void insn_bl_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bl_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bgu defined at ../../../targets/sparc64/opmatch.def:445:1-43
 */
void insn_bgu_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgu_e17xu64(line, op_0, op_1);
}

/*
 * Insn bgu,pt defined at ../../../targets/sparc64/opmatch.def:446:1-45
 */
void insn_bgu_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgu_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bgu,pn defined at ../../../targets/sparc64/opmatch.def:447:1-45
 */
void insn_bgu_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgu_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bgu,a defined at ../../../targets/sparc64/opmatch.def:448:1-42
 */
void insn_bgu_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgu_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bgu,a,pt defined at ../../../targets/sparc64/opmatch.def:449:1-45
 */
void insn_bgu_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgu_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bgu,a,pn defined at ../../../targets/sparc64/opmatch.def:450:1-45
 */
void insn_bgu_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgu_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bleu defined at ../../../targets/sparc64/opmatch.def:451:1-44
 */
void insn_bleu_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bleu_e17xu64(line, op_0, op_1);
}

/*
 * Insn bleu,pt defined at ../../../targets/sparc64/opmatch.def:452:1-47
 */
void insn_bleu_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bleu_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bleu,pn defined at ../../../targets/sparc64/opmatch.def:453:1-47
 */
void insn_bleu_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bleu_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bleu,a defined at ../../../targets/sparc64/opmatch.def:454:1-44
 */
void insn_bleu_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bleu_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bleu,a,pt defined at ../../../targets/sparc64/opmatch.def:455:1-47
 */
void insn_bleu_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bleu_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bleu,a,pn defined at ../../../targets/sparc64/opmatch.def:456:1-47
 */
void insn_bleu_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bleu_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bcc defined at ../../../targets/sparc64/opmatch.def:457:1-43
 */
void insn_bcc_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bcc_e17xu64(line, op_0, op_1);
}

/*
 * Insn bcc,pt defined at ../../../targets/sparc64/opmatch.def:458:1-45
 */
void insn_bcc_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bcc_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bcc,pn defined at ../../../targets/sparc64/opmatch.def:459:1-45
 */
void insn_bcc_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bcc_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bcc,a defined at ../../../targets/sparc64/opmatch.def:460:1-42
 */
void insn_bcc_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bcc_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bcc,a,pt defined at ../../../targets/sparc64/opmatch.def:461:1-45
 */
void insn_bcc_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bcc_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bcc,a,pn defined at ../../../targets/sparc64/opmatch.def:462:1-45
 */
void insn_bcc_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bcc_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bcs defined at ../../../targets/sparc64/opmatch.def:463:1-43
 */
void insn_bcs_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bcs_e17xu64(line, op_0, op_1);
}

/*
 * Insn bcs,pt defined at ../../../targets/sparc64/opmatch.def:464:1-45
 */
void insn_bcs_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bcs_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bcs,pn defined at ../../../targets/sparc64/opmatch.def:465:1-45
 */
void insn_bcs_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bcs_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bcs,a defined at ../../../targets/sparc64/opmatch.def:466:1-42
 */
void insn_bcs_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bcs_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bcs,a,pt defined at ../../../targets/sparc64/opmatch.def:467:1-45
 */
void insn_bcs_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bcs_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bcs,a,pn defined at ../../../targets/sparc64/opmatch.def:468:1-45
 */
void insn_bcs_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bcs_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bpos defined at ../../../targets/sparc64/opmatch.def:469:1-44
 */
void insn_bpos_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bpos_e17xu64(line, op_0, op_1);
}

/*
 * Insn bpos,pt defined at ../../../targets/sparc64/opmatch.def:470:1-47
 */
void insn_bpos_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bpos_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bpos,pn defined at ../../../targets/sparc64/opmatch.def:471:1-47
 */
void insn_bpos_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bpos_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bpos,a defined at ../../../targets/sparc64/opmatch.def:472:1-44
 */
void insn_bpos_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bpos_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bpos,a,pt defined at ../../../targets/sparc64/opmatch.def:473:1-47
 */
void insn_bpos_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bpos_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bpos,a,pn defined at ../../../targets/sparc64/opmatch.def:474:1-47
 */
void insn_bpos_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bpos_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bneg defined at ../../../targets/sparc64/opmatch.def:475:1-44
 */
void insn_bneg_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bneg_e17xu64(line, op_0, op_1);
}

/*
 * Insn bneg,pt defined at ../../../targets/sparc64/opmatch.def:476:1-47
 */
void insn_bneg_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bneg_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bneg,pn defined at ../../../targets/sparc64/opmatch.def:477:1-47
 */
void insn_bneg_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bneg_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bneg,a defined at ../../../targets/sparc64/opmatch.def:478:1-44
 */
void insn_bneg_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bneg_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bneg,a,pt defined at ../../../targets/sparc64/opmatch.def:479:1-47
 */
void insn_bneg_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bneg_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bneg,a,pn defined at ../../../targets/sparc64/opmatch.def:480:1-47
 */
void insn_bneg_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bneg_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bvc defined at ../../../targets/sparc64/opmatch.def:481:1-43
 */
void insn_bvc_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bvc_e17xu64(line, op_0, op_1);
}

/*
 * Insn bvc,pt defined at ../../../targets/sparc64/opmatch.def:482:1-45
 */
void insn_bvc_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bvc_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bvc,pn defined at ../../../targets/sparc64/opmatch.def:483:1-45
 */
void insn_bvc_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bvc_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bvc,a defined at ../../../targets/sparc64/opmatch.def:484:1-42
 */
void insn_bvc_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bvc_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bvc,a,pt defined at ../../../targets/sparc64/opmatch.def:485:1-45
 */
void insn_bvc_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bvc_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bvc,a,pn defined at ../../../targets/sparc64/opmatch.def:486:1-45
 */
void insn_bvc_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bvc_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bvs defined at ../../../targets/sparc64/opmatch.def:487:1-43
 */
void insn_bvs_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bvs_e17xu64(line, op_0, op_1);
}

/*
 * Insn bvs,pt defined at ../../../targets/sparc64/opmatch.def:488:1-45
 */
void insn_bvs_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bvs_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bvs,pn defined at ../../../targets/sparc64/opmatch.def:489:1-45
 */
void insn_bvs_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bvs_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bvs,a defined at ../../../targets/sparc64/opmatch.def:490:1-42
 */
void insn_bvs_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bvs_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bvs,a,pt defined at ../../../targets/sparc64/opmatch.def:491:1-45
 */
void insn_bvs_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bvs_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bvs,a,pn defined at ../../../targets/sparc64/opmatch.def:492:1-45
 */
void insn_bvs_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bvs_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bnz defined at ../../../targets/sparc64/opmatch.def:494:1-43
 */
void insn_bnz_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bnz_e17xu64(line, op_0, op_1);
}

/*
 * Insn bnz,pt defined at ../../../targets/sparc64/opmatch.def:495:1-45
 */
void insn_bnz_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bnz_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bnz,pn defined at ../../../targets/sparc64/opmatch.def:496:1-45
 */
void insn_bnz_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bnz_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bnz,a defined at ../../../targets/sparc64/opmatch.def:497:1-42
 */
void insn_bnz_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bnz_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bnz,a,pt defined at ../../../targets/sparc64/opmatch.def:498:1-45
 */
void insn_bnz_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bnz_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bnz,a,pn defined at ../../../targets/sparc64/opmatch.def:499:1-45
 */
void insn_bnz_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bnz_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bz defined at ../../../targets/sparc64/opmatch.def:500:1-41
 */
void insn_bz_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bz_e17xu64(line, op_0, op_1);
}

/*
 * Insn bz,pt defined at ../../../targets/sparc64/opmatch.def:501:1-43
 */
void insn_bz_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bz_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bz,pn defined at ../../../targets/sparc64/opmatch.def:502:1-43
 */
void insn_bz_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bz_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bz,a defined at ../../../targets/sparc64/opmatch.def:503:1-40
 */
void insn_bz_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bz_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bz,a,pt defined at ../../../targets/sparc64/opmatch.def:504:1-43
 */
void insn_bz_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bz_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bz,a,pn defined at ../../../targets/sparc64/opmatch.def:505:1-43
 */
void insn_bz_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bz_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bgeu defined at ../../../targets/sparc64/opmatch.def:506:1-43
 */
void insn_bgeu_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgeu_e17xu64(line, op_0, op_1);
}

/*
 * Insn bgeu,pt defined at ../../../targets/sparc64/opmatch.def:507:1-46
 */
void insn_bgeu_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgeu_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bgeu,pn defined at ../../../targets/sparc64/opmatch.def:508:1-46
 */
void insn_bgeu_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgeu_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn bgeu,a defined at ../../../targets/sparc64/opmatch.def:509:1-43
 */
void insn_bgeu_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgeu_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn bgeu,a,pt defined at ../../../targets/sparc64/opmatch.def:510:1-46
 */
void insn_bgeu_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgeu_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn bgeu,a,pn defined at ../../../targets/sparc64/opmatch.def:511:1-46
 */
void insn_bgeu_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   bgeu_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn blu defined at ../../../targets/sparc64/opmatch.def:512:1-43
 */
void insn_blu_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   blu_e17xu64(line, op_0, op_1);
}

/*
 * Insn blu,pt defined at ../../../targets/sparc64/opmatch.def:513:1-45
 */
void insn_blu_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   blu_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn blu,pn defined at ../../../targets/sparc64/opmatch.def:514:1-45
 */
void insn_blu_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   blu_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn blu,a defined at ../../../targets/sparc64/opmatch.def:515:1-42
 */
void insn_blu_a_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   blu_a_e17xu64(line, op_0, op_1);
}

/*
 * Insn blu,a,pt defined at ../../../targets/sparc64/opmatch.def:516:1-45
 */
void insn_blu_a_pt_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   blu_a_pt_e17xu64(line, op_0, op_1);
}

/*
 * Insn blu,a,pn defined at ../../../targets/sparc64/opmatch.def:517:1-45
 */
void insn_blu_a_pn_icc_symbol(int line, uint8_t op_0, struct expr * op_1) {
   blu_a_pn_e17xu64(line, op_0, op_1);
}

/*
 * Insn fmovsa defined at ../../../targets/sparc64/opmatch.def:519:1-44
 */
void insn_fmovsa_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsa_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovda defined at ../../../targets/sparc64/opmatch.def:520:1-44
 */
void insn_fmovda_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovda_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqa defined at ../../../targets/sparc64/opmatch.def:521:1-44
 */
void insn_fmovqa_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqa_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsn defined at ../../../targets/sparc64/opmatch.def:522:1-44
 */
void insn_fmovsn_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsn_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdn defined at ../../../targets/sparc64/opmatch.def:523:1-44
 */
void insn_fmovdn_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdn_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqn defined at ../../../targets/sparc64/opmatch.def:524:1-44
 */
void insn_fmovqn_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqn_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsne defined at ../../../targets/sparc64/opmatch.def:525:1-46
 */
void insn_fmovsne_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsne_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdne defined at ../../../targets/sparc64/opmatch.def:526:1-46
 */
void insn_fmovdne_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdne_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqne defined at ../../../targets/sparc64/opmatch.def:527:1-46
 */
void insn_fmovqne_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqne_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovse defined at ../../../targets/sparc64/opmatch.def:528:1-44
 */
void insn_fmovse_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovse_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovde defined at ../../../targets/sparc64/opmatch.def:529:1-44
 */
void insn_fmovde_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovde_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqe defined at ../../../targets/sparc64/opmatch.def:530:1-44
 */
void insn_fmovqe_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqe_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsg defined at ../../../targets/sparc64/opmatch.def:531:1-44
 */
void insn_fmovsg_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsg_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdg defined at ../../../targets/sparc64/opmatch.def:532:1-44
 */
void insn_fmovdg_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdg_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqg defined at ../../../targets/sparc64/opmatch.def:533:1-44
 */
void insn_fmovqg_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqg_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsle defined at ../../../targets/sparc64/opmatch.def:534:1-46
 */
void insn_fmovsle_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsle_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdle defined at ../../../targets/sparc64/opmatch.def:535:1-46
 */
void insn_fmovdle_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdle_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqle defined at ../../../targets/sparc64/opmatch.def:536:1-46
 */
void insn_fmovqle_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqle_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsge defined at ../../../targets/sparc64/opmatch.def:537:1-46
 */
void insn_fmovsge_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsge_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdge defined at ../../../targets/sparc64/opmatch.def:538:1-46
 */
void insn_fmovdge_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdge_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqge defined at ../../../targets/sparc64/opmatch.def:539:1-46
 */
void insn_fmovqge_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqge_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsl defined at ../../../targets/sparc64/opmatch.def:540:1-44
 */
void insn_fmovsl_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsl_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdl defined at ../../../targets/sparc64/opmatch.def:541:1-44
 */
void insn_fmovdl_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdl_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovql defined at ../../../targets/sparc64/opmatch.def:542:1-44
 */
void insn_fmovql_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovql_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsgu defined at ../../../targets/sparc64/opmatch.def:543:1-46
 */
void insn_fmovsgu_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsgu_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdgu defined at ../../../targets/sparc64/opmatch.def:544:1-46
 */
void insn_fmovdgu_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdgu_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqgu defined at ../../../targets/sparc64/opmatch.def:545:1-46
 */
void insn_fmovqgu_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqgu_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsleu defined at ../../../targets/sparc64/opmatch.def:546:1-47
 */
void insn_fmovsleu_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsleu_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdleu defined at ../../../targets/sparc64/opmatch.def:547:1-47
 */
void insn_fmovdleu_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdleu_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqleu defined at ../../../targets/sparc64/opmatch.def:548:1-47
 */
void insn_fmovqleu_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqleu_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovscc defined at ../../../targets/sparc64/opmatch.def:549:1-46
 */
void insn_fmovscc_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovscc_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdcc defined at ../../../targets/sparc64/opmatch.def:550:1-46
 */
void insn_fmovdcc_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdcc_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqcc defined at ../../../targets/sparc64/opmatch.def:551:1-46
 */
void insn_fmovqcc_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqcc_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovscs defined at ../../../targets/sparc64/opmatch.def:552:1-46
 */
void insn_fmovscs_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovscs_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdcs defined at ../../../targets/sparc64/opmatch.def:553:1-46
 */
void insn_fmovdcs_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdcs_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqcs defined at ../../../targets/sparc64/opmatch.def:554:1-46
 */
void insn_fmovqcs_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqcs_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovspos defined at ../../../targets/sparc64/opmatch.def:555:1-47
 */
void insn_fmovspos_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovspos_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdpos defined at ../../../targets/sparc64/opmatch.def:556:1-47
 */
void insn_fmovdpos_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdpos_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqpos defined at ../../../targets/sparc64/opmatch.def:557:1-47
 */
void insn_fmovqpos_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqpos_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsneg defined at ../../../targets/sparc64/opmatch.def:558:1-47
 */
void insn_fmovsneg_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsneg_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdneg defined at ../../../targets/sparc64/opmatch.def:559:1-47
 */
void insn_fmovdneg_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdneg_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqneg defined at ../../../targets/sparc64/opmatch.def:560:1-47
 */
void insn_fmovqneg_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqneg_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsvc defined at ../../../targets/sparc64/opmatch.def:561:1-46
 */
void insn_fmovsvc_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsvc_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdvc defined at ../../../targets/sparc64/opmatch.def:562:1-46
 */
void insn_fmovdvc_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdvc_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqvc defined at ../../../targets/sparc64/opmatch.def:563:1-46
 */
void insn_fmovqvc_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqvc_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsvs defined at ../../../targets/sparc64/opmatch.def:564:1-46
 */
void insn_fmovsvs_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsvs_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdvs defined at ../../../targets/sparc64/opmatch.def:565:1-46
 */
void insn_fmovdvs_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdvs_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqvs defined at ../../../targets/sparc64/opmatch.def:566:1-46
 */
void insn_fmovqvs_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqvs_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsnz defined at ../../../targets/sparc64/opmatch.def:568:1-46
 */
void insn_fmovsnz_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsnz_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdnz defined at ../../../targets/sparc64/opmatch.def:569:1-46
 */
void insn_fmovdnz_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdnz_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqnz defined at ../../../targets/sparc64/opmatch.def:570:1-46
 */
void insn_fmovqnz_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqnz_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsz defined at ../../../targets/sparc64/opmatch.def:571:1-44
 */
void insn_fmovsz_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsz_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdz defined at ../../../targets/sparc64/opmatch.def:572:1-44
 */
void insn_fmovdz_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdz_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqz defined at ../../../targets/sparc64/opmatch.def:573:1-44
 */
void insn_fmovqz_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqz_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsgeu defined at ../../../targets/sparc64/opmatch.def:574:1-46
 */
void insn_fmovsgeu_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsgeu_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdgeu defined at ../../../targets/sparc64/opmatch.def:575:1-46
 */
void insn_fmovdgeu_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdgeu_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqgeu defined at ../../../targets/sparc64/opmatch.def:576:1-46
 */
void insn_fmovqgeu_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqgeu_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovslu defined at ../../../targets/sparc64/opmatch.def:577:1-46
 */
void insn_fmovslu_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovslu_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdlu defined at ../../../targets/sparc64/opmatch.def:578:1-46
 */
void insn_fmovdlu_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdlu_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqlu defined at ../../../targets/sparc64/opmatch.def:579:1-46
 */
void insn_fmovqlu_icc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqlu_e17e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsa defined at ../../../targets/sparc64/opmatch.def:581:1-45
 */
void insn_fmovsa_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsa_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovda defined at ../../../targets/sparc64/opmatch.def:582:1-45
 */
void insn_fmovda_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovda_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqa defined at ../../../targets/sparc64/opmatch.def:583:1-45
 */
void insn_fmovqa_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqa_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsn defined at ../../../targets/sparc64/opmatch.def:584:1-45
 */
void insn_fmovsn_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsn_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdn defined at ../../../targets/sparc64/opmatch.def:585:1-45
 */
void insn_fmovdn_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdn_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqn defined at ../../../targets/sparc64/opmatch.def:586:1-45
 */
void insn_fmovqn_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqn_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsu defined at ../../../targets/sparc64/opmatch.def:587:1-45
 */
void insn_fmovsu_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsu_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdu defined at ../../../targets/sparc64/opmatch.def:588:1-45
 */
void insn_fmovdu_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdu_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqu defined at ../../../targets/sparc64/opmatch.def:589:1-45
 */
void insn_fmovqu_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqu_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsg defined at ../../../targets/sparc64/opmatch.def:590:1-45
 */
void insn_fmovsg_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsg_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdg defined at ../../../targets/sparc64/opmatch.def:591:1-45
 */
void insn_fmovdg_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdg_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqg defined at ../../../targets/sparc64/opmatch.def:592:1-45
 */
void insn_fmovqg_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqg_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsug defined at ../../../targets/sparc64/opmatch.def:593:1-47
 */
void insn_fmovsug_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsug_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdug defined at ../../../targets/sparc64/opmatch.def:594:1-47
 */
void insn_fmovdug_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdug_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqug defined at ../../../targets/sparc64/opmatch.def:595:1-47
 */
void insn_fmovqug_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqug_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsl defined at ../../../targets/sparc64/opmatch.def:596:1-45
 */
void insn_fmovsl_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsl_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdl defined at ../../../targets/sparc64/opmatch.def:597:1-45
 */
void insn_fmovdl_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdl_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovql defined at ../../../targets/sparc64/opmatch.def:598:1-45
 */
void insn_fmovql_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovql_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsul defined at ../../../targets/sparc64/opmatch.def:599:1-47
 */
void insn_fmovsul_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsul_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdul defined at ../../../targets/sparc64/opmatch.def:600:1-47
 */
void insn_fmovdul_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdul_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqul defined at ../../../targets/sparc64/opmatch.def:601:1-47
 */
void insn_fmovqul_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqul_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovslg defined at ../../../targets/sparc64/opmatch.def:602:1-47
 */
void insn_fmovslg_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovslg_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdlg defined at ../../../targets/sparc64/opmatch.def:603:1-47
 */
void insn_fmovdlg_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdlg_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqlg defined at ../../../targets/sparc64/opmatch.def:604:1-47
 */
void insn_fmovqlg_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqlg_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsne defined at ../../../targets/sparc64/opmatch.def:605:1-47
 */
void insn_fmovsne_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsne_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdne defined at ../../../targets/sparc64/opmatch.def:606:1-47
 */
void insn_fmovdne_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdne_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqne defined at ../../../targets/sparc64/opmatch.def:607:1-47
 */
void insn_fmovqne_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqne_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovse defined at ../../../targets/sparc64/opmatch.def:608:1-45
 */
void insn_fmovse_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovse_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovde defined at ../../../targets/sparc64/opmatch.def:609:1-45
 */
void insn_fmovde_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovde_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqe defined at ../../../targets/sparc64/opmatch.def:610:1-45
 */
void insn_fmovqe_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqe_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsue defined at ../../../targets/sparc64/opmatch.def:611:1-47
 */
void insn_fmovsue_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsue_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdue defined at ../../../targets/sparc64/opmatch.def:612:1-47
 */
void insn_fmovdue_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdue_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovque defined at ../../../targets/sparc64/opmatch.def:613:1-47
 */
void insn_fmovque_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovque_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsge defined at ../../../targets/sparc64/opmatch.def:614:1-47
 */
void insn_fmovsge_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsge_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdge defined at ../../../targets/sparc64/opmatch.def:615:1-47
 */
void insn_fmovdge_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdge_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqge defined at ../../../targets/sparc64/opmatch.def:616:1-47
 */
void insn_fmovqge_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqge_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsuge defined at ../../../targets/sparc64/opmatch.def:617:1-48
 */
void insn_fmovsuge_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsuge_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovduge defined at ../../../targets/sparc64/opmatch.def:618:1-48
 */
void insn_fmovduge_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovduge_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovquge defined at ../../../targets/sparc64/opmatch.def:619:1-48
 */
void insn_fmovquge_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovquge_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsle defined at ../../../targets/sparc64/opmatch.def:620:1-47
 */
void insn_fmovsle_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsle_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdle defined at ../../../targets/sparc64/opmatch.def:621:1-47
 */
void insn_fmovdle_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdle_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqle defined at ../../../targets/sparc64/opmatch.def:622:1-47
 */
void insn_fmovqle_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqle_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsule defined at ../../../targets/sparc64/opmatch.def:623:1-48
 */
void insn_fmovsule_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsule_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdule defined at ../../../targets/sparc64/opmatch.def:624:1-48
 */
void insn_fmovdule_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdule_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqule defined at ../../../targets/sparc64/opmatch.def:625:1-48
 */
void insn_fmovqule_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqule_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovso defined at ../../../targets/sparc64/opmatch.def:626:1-45
 */
void insn_fmovso_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovso_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdo defined at ../../../targets/sparc64/opmatch.def:627:1-45
 */
void insn_fmovdo_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdo_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqo defined at ../../../targets/sparc64/opmatch.def:628:1-45
 */
void insn_fmovqo_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqo_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsnz defined at ../../../targets/sparc64/opmatch.def:630:1-47
 */
void insn_fmovsnz_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsnz_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdnz defined at ../../../targets/sparc64/opmatch.def:631:1-47
 */
void insn_fmovdnz_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdnz_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqnz defined at ../../../targets/sparc64/opmatch.def:632:1-47
 */
void insn_fmovqnz_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqnz_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovsz defined at ../../../targets/sparc64/opmatch.def:633:1-45
 */
void insn_fmovsz_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovsz_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovdz defined at ../../../targets/sparc64/opmatch.def:634:1-45
 */
void insn_fmovdz_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovdz_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovqz defined at ../../../targets/sparc64/opmatch.def:635:1-45
 */
void insn_fmovqz_fcc_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovqz_e13e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrsz defined at ../../../targets/sparc64/opmatch.def:637:1-46
 */
void insn_fmovrsz_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrsz_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrdz defined at ../../../targets/sparc64/opmatch.def:638:1-46
 */
void insn_fmovrdz_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrdz_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrqz defined at ../../../targets/sparc64/opmatch.def:639:1-46
 */
void insn_fmovrqz_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrqz_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrslez defined at ../../../targets/sparc64/opmatch.def:640:1-49
 */
void insn_fmovrslez_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrslez_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrdlez defined at ../../../targets/sparc64/opmatch.def:641:1-49
 */
void insn_fmovrdlez_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrdlez_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrqlez defined at ../../../targets/sparc64/opmatch.def:642:1-49
 */
void insn_fmovrqlez_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrqlez_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrslz defined at ../../../targets/sparc64/opmatch.def:643:1-47
 */
void insn_fmovrslz_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrslz_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrdlz defined at ../../../targets/sparc64/opmatch.def:644:1-47
 */
void insn_fmovrdlz_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrdlz_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrqlz defined at ../../../targets/sparc64/opmatch.def:645:1-47
 */
void insn_fmovrqlz_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrqlz_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrsnz defined at ../../../targets/sparc64/opmatch.def:646:1-47
 */
void insn_fmovrsnz_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrsnz_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrdnz defined at ../../../targets/sparc64/opmatch.def:647:1-47
 */
void insn_fmovrdnz_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrdnz_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrqnz defined at ../../../targets/sparc64/opmatch.def:648:1-47
 */
void insn_fmovrqnz_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrqnz_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrsg defined at ../../../targets/sparc64/opmatch.def:649:1-47
 */
void insn_fmovrsg_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrsg_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrdg defined at ../../../targets/sparc64/opmatch.def:650:1-47
 */
void insn_fmovrdg_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrdg_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrqg defined at ../../../targets/sparc64/opmatch.def:651:1-47
 */
void insn_fmovrqg_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrqg_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrsgez defined at ../../../targets/sparc64/opmatch.def:652:1-49
 */
void insn_fmovrsgez_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrsgez_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrdgez defined at ../../../targets/sparc64/opmatch.def:653:1-49
 */
void insn_fmovrdgez_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrdgez_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrqgez defined at ../../../targets/sparc64/opmatch.def:654:1-49
 */
void insn_fmovrqgez_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrqgez_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrse defined at ../../../targets/sparc64/opmatch.def:656:1-46
 */
void insn_fmovrse_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrse_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrde defined at ../../../targets/sparc64/opmatch.def:657:1-46
 */
void insn_fmovrde_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrde_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrqe defined at ../../../targets/sparc64/opmatch.def:658:1-46
 */
void insn_fmovrqe_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrqe_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrsne defined at ../../../targets/sparc64/opmatch.def:659:1-47
 */
void insn_fmovrsne_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrsne_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrdne defined at ../../../targets/sparc64/opmatch.def:660:1-47
 */
void insn_fmovrdne_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrdne_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn fmovrqne defined at ../../../targets/sparc64/opmatch.def:661:1-47
 */
void insn_fmovrqne_reg_freg_freg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   fmovrqne_e16e14e14(line, op_0, op_1, op_2);
}

/*
 * Insn mova defined at ../../../targets/sparc64/opmatch.def:663:1-33
 */
void insn_mova_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mova_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn mova defined at ../../../targets/sparc64/opmatch.def:664:1-36
 */
void insn_mova_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   mova_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movn defined at ../../../targets/sparc64/opmatch.def:665:1-33
 */
void insn_movn_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movn_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movn defined at ../../../targets/sparc64/opmatch.def:666:1-36
 */
void insn_movn_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movn_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movne defined at ../../../targets/sparc64/opmatch.def:667:1-35
 */
void insn_movne_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movne_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movne defined at ../../../targets/sparc64/opmatch.def:668:1-38
 */
void insn_movne_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movne_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn move defined at ../../../targets/sparc64/opmatch.def:669:1-33
 */
void insn_move_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   move_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn move defined at ../../../targets/sparc64/opmatch.def:670:1-36
 */
void insn_move_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   move_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movg defined at ../../../targets/sparc64/opmatch.def:671:1-33
 */
void insn_movg_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movg_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movg defined at ../../../targets/sparc64/opmatch.def:672:1-36
 */
void insn_movg_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movg_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movle defined at ../../../targets/sparc64/opmatch.def:673:1-35
 */
void insn_movle_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movle_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movle defined at ../../../targets/sparc64/opmatch.def:674:1-38
 */
void insn_movle_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movle_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movge defined at ../../../targets/sparc64/opmatch.def:675:1-35
 */
void insn_movge_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movge_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movge defined at ../../../targets/sparc64/opmatch.def:676:1-38
 */
void insn_movge_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movge_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movl defined at ../../../targets/sparc64/opmatch.def:677:1-33
 */
void insn_movl_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movl_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movl defined at ../../../targets/sparc64/opmatch.def:678:1-36
 */
void insn_movl_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movl_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movgu defined at ../../../targets/sparc64/opmatch.def:679:1-35
 */
void insn_movgu_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movgu_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movgu defined at ../../../targets/sparc64/opmatch.def:680:1-38
 */
void insn_movgu_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movgu_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movleu defined at ../../../targets/sparc64/opmatch.def:681:1-37
 */
void insn_movleu_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movleu_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movleu defined at ../../../targets/sparc64/opmatch.def:682:1-40
 */
void insn_movleu_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movleu_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movcc defined at ../../../targets/sparc64/opmatch.def:683:1-35
 */
void insn_movcc_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movcc_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movcc defined at ../../../targets/sparc64/opmatch.def:684:1-38
 */
void insn_movcc_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movcc_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movcs defined at ../../../targets/sparc64/opmatch.def:685:1-35
 */
void insn_movcs_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movcs_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movcs defined at ../../../targets/sparc64/opmatch.def:686:1-38
 */
void insn_movcs_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movcs_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movpos defined at ../../../targets/sparc64/opmatch.def:687:1-37
 */
void insn_movpos_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movpos_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movpos defined at ../../../targets/sparc64/opmatch.def:688:1-40
 */
void insn_movpos_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movpos_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movneg defined at ../../../targets/sparc64/opmatch.def:689:1-37
 */
void insn_movneg_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movneg_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movneg defined at ../../../targets/sparc64/opmatch.def:690:1-40
 */
void insn_movneg_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movneg_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movvc defined at ../../../targets/sparc64/opmatch.def:691:1-35
 */
void insn_movvc_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movvc_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movvc defined at ../../../targets/sparc64/opmatch.def:692:1-38
 */
void insn_movvc_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movvc_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movvs defined at ../../../targets/sparc64/opmatch.def:693:1-35
 */
void insn_movvs_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movvs_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movvs defined at ../../../targets/sparc64/opmatch.def:694:1-38
 */
void insn_movvs_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movvs_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movnz defined at ../../../targets/sparc64/opmatch.def:696:1-35
 */
void insn_movnz_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movnz_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movnz defined at ../../../targets/sparc64/opmatch.def:697:1-38
 */
void insn_movnz_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movnz_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movz defined at ../../../targets/sparc64/opmatch.def:698:1-33
 */
void insn_movz_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movz_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movz defined at ../../../targets/sparc64/opmatch.def:699:1-36
 */
void insn_movz_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movz_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movgeu defined at ../../../targets/sparc64/opmatch.def:700:1-36
 */
void insn_movgeu_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movgeu_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movgeu defined at ../../../targets/sparc64/opmatch.def:701:1-39
 */
void insn_movgeu_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movgeu_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movlu defined at ../../../targets/sparc64/opmatch.def:702:1-35
 */
void insn_movlu_icc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movlu_e17e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movlu defined at ../../../targets/sparc64/opmatch.def:703:1-38
 */
void insn_movlu_icc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movlu_e17i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn mova defined at ../../../targets/sparc64/opmatch.def:705:1-34
 */
void insn_mova_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   mova_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn mova defined at ../../../targets/sparc64/opmatch.def:706:1-37
 */
void insn_mova_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   mova_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movn defined at ../../../targets/sparc64/opmatch.def:707:1-34
 */
void insn_movn_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movn_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movn defined at ../../../targets/sparc64/opmatch.def:708:1-37
 */
void insn_movn_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movn_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movu defined at ../../../targets/sparc64/opmatch.def:709:1-34
 */
void insn_movu_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movu_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movu defined at ../../../targets/sparc64/opmatch.def:710:1-37
 */
void insn_movu_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movu_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movg defined at ../../../targets/sparc64/opmatch.def:711:1-34
 */
void insn_movg_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movg_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movg defined at ../../../targets/sparc64/opmatch.def:712:1-37
 */
void insn_movg_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movg_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movug defined at ../../../targets/sparc64/opmatch.def:713:1-36
 */
void insn_movug_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movug_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movug defined at ../../../targets/sparc64/opmatch.def:714:1-39
 */
void insn_movug_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movug_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movl defined at ../../../targets/sparc64/opmatch.def:715:1-34
 */
void insn_movl_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movl_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movl defined at ../../../targets/sparc64/opmatch.def:716:1-37
 */
void insn_movl_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movl_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movul defined at ../../../targets/sparc64/opmatch.def:717:1-36
 */
void insn_movul_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movul_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movul defined at ../../../targets/sparc64/opmatch.def:718:1-39
 */
void insn_movul_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movul_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movlg defined at ../../../targets/sparc64/opmatch.def:719:1-36
 */
void insn_movlg_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movlg_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movlg defined at ../../../targets/sparc64/opmatch.def:720:1-39
 */
void insn_movlg_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movlg_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movne defined at ../../../targets/sparc64/opmatch.def:721:1-36
 */
void insn_movne_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movne_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movne defined at ../../../targets/sparc64/opmatch.def:722:1-39
 */
void insn_movne_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movne_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn move defined at ../../../targets/sparc64/opmatch.def:723:1-34
 */
void insn_move_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   move_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn move defined at ../../../targets/sparc64/opmatch.def:724:1-37
 */
void insn_move_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   move_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movue defined at ../../../targets/sparc64/opmatch.def:725:1-36
 */
void insn_movue_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movue_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movue defined at ../../../targets/sparc64/opmatch.def:726:1-39
 */
void insn_movue_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movue_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movge defined at ../../../targets/sparc64/opmatch.def:727:1-36
 */
void insn_movge_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movge_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movge defined at ../../../targets/sparc64/opmatch.def:728:1-39
 */
void insn_movge_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movge_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movuge defined at ../../../targets/sparc64/opmatch.def:729:1-38
 */
void insn_movuge_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movuge_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movuge defined at ../../../targets/sparc64/opmatch.def:730:1-41
 */
void insn_movuge_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movuge_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movle defined at ../../../targets/sparc64/opmatch.def:731:1-36
 */
void insn_movle_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movle_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movle defined at ../../../targets/sparc64/opmatch.def:732:1-39
 */
void insn_movle_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movle_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movule defined at ../../../targets/sparc64/opmatch.def:733:1-38
 */
void insn_movule_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movule_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movule defined at ../../../targets/sparc64/opmatch.def:734:1-41
 */
void insn_movule_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movule_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movo defined at ../../../targets/sparc64/opmatch.def:735:1-34
 */
void insn_movo_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movo_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movo defined at ../../../targets/sparc64/opmatch.def:736:1-37
 */
void insn_movo_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movo_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movnz defined at ../../../targets/sparc64/opmatch.def:738:1-36
 */
void insn_movnz_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movnz_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movnz defined at ../../../targets/sparc64/opmatch.def:739:1-39
 */
void insn_movnz_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movnz_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movz defined at ../../../targets/sparc64/opmatch.def:740:1-34
 */
void insn_movz_fcc_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movz_e13e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movz defined at ../../../targets/sparc64/opmatch.def:741:1-37
 */
void insn_movz_fcc_i11num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movz_e13i11e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrz defined at ../../../targets/sparc64/opmatch.def:743:1-33
 */
void insn_movrz_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movrz_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrz defined at ../../../targets/sparc64/opmatch.def:744:1-36
 */
void insn_movrz_reg_i10num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movrz_e16i10e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrlez defined at ../../../targets/sparc64/opmatch.def:745:1-37
 */
void insn_movrlez_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movrlez_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrlez defined at ../../../targets/sparc64/opmatch.def:746:1-39
 */
void insn_movrlez_reg_i10num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movrlez_e16i10e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrlz defined at ../../../targets/sparc64/opmatch.def:747:1-35
 */
void insn_movrlz_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movrlz_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrlz defined at ../../../targets/sparc64/opmatch.def:748:1-38
 */
void insn_movrlz_reg_i10num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movrlz_e16i10e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrnz defined at ../../../targets/sparc64/opmatch.def:749:1-35
 */
void insn_movrnz_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movrnz_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrnz defined at ../../../targets/sparc64/opmatch.def:750:1-38
 */
void insn_movrnz_reg_i10num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movrnz_e16i10e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrgz defined at ../../../targets/sparc64/opmatch.def:751:1-35
 */
void insn_movrgz_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movrgz_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrgz defined at ../../../targets/sparc64/opmatch.def:752:1-38
 */
void insn_movrgz_reg_i10num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movrgz_e16i10e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrgez defined at ../../../targets/sparc64/opmatch.def:753:1-37
 */
void insn_movrgez_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movrgez_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrgez defined at ../../../targets/sparc64/opmatch.def:754:1-39
 */
void insn_movrgez_reg_i10num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movrgez_e16i10e16(line, op_0, op_1, op_2);
}

/*
 * Insn movre defined at ../../../targets/sparc64/opmatch.def:756:1-33
 */
void insn_movre_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movre_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movre defined at ../../../targets/sparc64/opmatch.def:757:1-36
 */
void insn_movre_reg_i10num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movre_e16i10e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrne defined at ../../../targets/sparc64/opmatch.def:758:1-35
 */
void insn_movrne_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   movrne_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn movrne defined at ../../../targets/sparc64/opmatch.def:759:1-38
 */
void insn_movrne_reg_i10num_reg(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   movrne_e16i10e16(line, op_0, op_1, op_2);
}

/*
 * Insn membar defined at ../../../targets/sparc64/opmatch.def:761:1-18
 */
void insn_membar_membarmask(int line, uint8_t op_0) {
   membar_u7(line, op_0);
}

/*
 * Insn stbar defined at ../../../targets/sparc64/opmatch.def:762:1-6
 */
void insn_stbar_(int line) {
   stbar_(line);
}

/*
 * Insn flush defined at ../../../targets/sparc64/opmatch.def:764:1-14
 */
void insn_flush_addr_rr(int line, struct compound_addr_rr * op_0) {
   flush_addr_rr(line, op_0);
}

/*
 * Insn flush defined at ../../../targets/sparc64/opmatch.def:765:1-14
 */
void insn_flush_addr_ri(int line, struct compound_addr_ri * op_0) {
   flush_addr_ri(line, op_0);
}

/*
 * Insn prefetch defined at ../../../targets/sparc64/opmatch.def:767:1-26
 */
void insn_prefetch_braddr_rr_u5num(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   prefetch_braddr_rru5(line, op_0, op_1);
}

/*
 * Insn prefetch defined at ../../../targets/sparc64/opmatch.def:768:1-26
 */
void insn_prefetch_braddr_ri_u5num(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   prefetch_braddr_riu5(line, op_0, op_1);
}

/*
 * Insn prefetcha defined at ../../../targets/sparc64/opmatch.def:769:1-34
 */
void insn_prefetcha_braddr_rr_immasi_u5num(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   prefetcha_braddr_rr_immasiu5(line, op_0, op_1);
}

/*
 * Insn prefetcha defined at ../../../targets/sparc64/opmatch.def:770:1-31
 */
void insn_prefetcha_braddr_ri_asi_u5num(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   prefetcha_braddr_ri_asiu5(line, op_0, op_1);
}

/*
 * Insn casa defined at ../../../targets/sparc64/opmatch.def:772:1-45
 */
void insn_casa_braddr_r_immasi_reg_reg(int line, struct compound_braddr_r_immasi * op_0, uint8_t op_1, uint8_t op_2) {
   casa_braddr_r_immasie16e16(line, op_0, op_1, op_2);
}

/*
 * Insn casa defined at ../../../targets/sparc64/opmatch.def:773:1-42
 */
void insn_casa_braddr_r_asi_reg_reg(int line, struct compound_braddr_r_asi * op_0, uint8_t op_1, uint8_t op_2) {
   casa_braddr_r_asie16e16(line, op_0, op_1, op_2);
}

/*
 * Insn casxa defined at ../../../targets/sparc64/opmatch.def:774:1-47
 */
void insn_casxa_braddr_r_immasi_reg_reg(int line, struct compound_braddr_r_immasi * op_0, uint8_t op_1, uint8_t op_2) {
   casxa_braddr_r_immasie16e16(line, op_0, op_1, op_2);
}

/*
 * Insn casxa defined at ../../../targets/sparc64/opmatch.def:775:1-44
 */
void insn_casxa_braddr_r_asi_reg_reg(int line, struct compound_braddr_r_asi * op_0, uint8_t op_1, uint8_t op_2) {
   casxa_braddr_r_asie16e16(line, op_0, op_1, op_2);
}

/*
 * Insn ldstub defined at ../../../targets/sparc64/opmatch.def:776:1-22
 */
void insn_ldstub_braddr_rr_reg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ldstub_braddr_rre16(line, op_0, op_1);
}

/*
 * Insn ldstub defined at ../../../targets/sparc64/opmatch.def:777:1-22
 */
void insn_ldstub_braddr_ri_reg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ldstub_braddr_rie16(line, op_0, op_1);
}

/*
 * Insn ldstub defined at ../../../targets/sparc64/opmatch.def:778:1-22
 */
void insn_ldstub_braddr_rx_reg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ldstub_braddr_rxe16(line, op_0, op_1);
}

/*
 * Insn ldstuba defined at ../../../targets/sparc64/opmatch.def:779:1-30
 */
void insn_ldstuba_braddr_rr_immasi_reg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   ldstuba_braddr_rr_immasie16(line, op_0, op_1);
}

/*
 * Insn ldstuba defined at ../../../targets/sparc64/opmatch.def:780:1-27
 */
void insn_ldstuba_braddr_ri_asi_reg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   ldstuba_braddr_ri_asie16(line, op_0, op_1);
}

/*
 * Insn swap defined at ../../../targets/sparc64/opmatch.def:781:1-20
 */
void insn_swap_braddr_rr_reg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   swap_braddr_rre16(line, op_0, op_1);
}

/*
 * Insn swap defined at ../../../targets/sparc64/opmatch.def:782:1-20
 */
void insn_swap_braddr_ri_reg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   swap_braddr_rie16(line, op_0, op_1);
}

/*
 * Insn swapa defined at ../../../targets/sparc64/opmatch.def:783:1-28
 */
void insn_swapa_braddr_rr_immasi_reg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   swapa_braddr_rr_immasie16(line, op_0, op_1);
}

/*
 * Insn swapa defined at ../../../targets/sparc64/opmatch.def:784:1-25
 */
void insn_swapa_braddr_ri_asi_reg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   swapa_braddr_ri_asie16(line, op_0, op_1);
}

/*
 * Insn ld defined at ../../../targets/sparc64/opmatch.def:786:1-31
 */
void insn_ld_braddr_rr_freg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ld_braddr_rre14(line, op_0, op_1);
}

/*
 * Insn ld defined at ../../../targets/sparc64/opmatch.def:787:1-31
 */
void insn_ld_braddr_ri_freg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ld_braddr_rie14(line, op_0, op_1);
}

/*
 * Insn ld defined at ../../../targets/sparc64/opmatch.def:788:1-31
 */
void insn_ld_braddr_rx_freg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ld_braddr_rxe14(line, op_0, op_1);
}

/*
 * Insn ldd defined at ../../../targets/sparc64/opmatch.def:789:1-33
 */
void insn_ldd_braddr_rr_freg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ldd_braddr_rre14(line, op_0, op_1);
}

/*
 * Insn ldd defined at ../../../targets/sparc64/opmatch.def:790:1-33
 */
void insn_ldd_braddr_ri_freg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ldd_braddr_rie14(line, op_0, op_1);
}

/*
 * Insn ldd defined at ../../../targets/sparc64/opmatch.def:791:1-33
 */
void insn_ldd_braddr_rx_freg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ldd_braddr_rxe14(line, op_0, op_1);
}

/*
 * Insn ldq defined at ../../../targets/sparc64/opmatch.def:792:1-33
 */
void insn_ldq_braddr_rr_freg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ldq_braddr_rre14(line, op_0, op_1);
}

/*
 * Insn ldq defined at ../../../targets/sparc64/opmatch.def:793:1-33
 */
void insn_ldq_braddr_ri_freg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ldq_braddr_rie14(line, op_0, op_1);
}

/*
 * Insn ldq defined at ../../../targets/sparc64/opmatch.def:794:1-33
 */
void insn_ldq_braddr_rx_freg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ldq_braddr_rxe14(line, op_0, op_1);
}

/*
 * Insn ld defined at ../../../targets/sparc64/opmatch.def:795:1-27
 */
void insn_ld_braddr_rr_fsr(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ld_braddr_rre15(line, op_0, op_1);
}

/*
 * Insn ld defined at ../../../targets/sparc64/opmatch.def:796:1-27
 */
void insn_ld_braddr_ri_fsr(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ld_braddr_rie15(line, op_0, op_1);
}

/*
 * Insn ld defined at ../../../targets/sparc64/opmatch.def:797:1-27
 */
void insn_ld_braddr_rx_fsr(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ld_braddr_rxe15(line, op_0, op_1);
}

/*
 * Insn ldx defined at ../../../targets/sparc64/opmatch.def:798:1-29
 */
void insn_ldx_braddr_rr_fsr(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ldx_braddr_rre15(line, op_0, op_1);
}

/*
 * Insn ldx defined at ../../../targets/sparc64/opmatch.def:799:1-29
 */
void insn_ldx_braddr_ri_fsr(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ldx_braddr_rie15(line, op_0, op_1);
}

/*
 * Insn ldx defined at ../../../targets/sparc64/opmatch.def:800:1-29
 */
void insn_ldx_braddr_rx_fsr(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ldx_braddr_rxe15(line, op_0, op_1);
}

/*
 * Insn lda defined at ../../../targets/sparc64/opmatch.def:802:1-39
 */
void insn_lda_braddr_rr_immasi_freg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   lda_braddr_rr_immasie14(line, op_0, op_1);
}

/*
 * Insn lda defined at ../../../targets/sparc64/opmatch.def:803:1-37
 */
void insn_lda_braddr_ri_asi_freg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   lda_braddr_ri_asie14(line, op_0, op_1);
}

/*
 * Insn ldda defined at ../../../targets/sparc64/opmatch.def:804:1-41
 */
void insn_ldda_braddr_rr_immasi_freg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   ldda_braddr_rr_immasie14(line, op_0, op_1);
}

/*
 * Insn ldda defined at ../../../targets/sparc64/opmatch.def:805:1-38
 */
void insn_ldda_braddr_ri_asi_freg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   ldda_braddr_ri_asie14(line, op_0, op_1);
}

/*
 * Insn ldqa defined at ../../../targets/sparc64/opmatch.def:806:1-41
 */
void insn_ldqa_braddr_rr_immasi_freg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   ldqa_braddr_rr_immasie14(line, op_0, op_1);
}

/*
 * Insn ldqa defined at ../../../targets/sparc64/opmatch.def:807:1-38
 */
void insn_ldqa_braddr_ri_asi_freg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   ldqa_braddr_ri_asie14(line, op_0, op_1);
}

/*
 * Insn ldsb defined at ../../../targets/sparc64/opmatch.def:809:1-34
 */
void insn_ldsb_braddr_rr_reg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ldsb_braddr_rre16(line, op_0, op_1);
}

/*
 * Insn ldsb defined at ../../../targets/sparc64/opmatch.def:810:1-34
 */
void insn_ldsb_braddr_ri_reg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ldsb_braddr_rie16(line, op_0, op_1);
}

/*
 * Insn ldsb defined at ../../../targets/sparc64/opmatch.def:811:1-34
 */
void insn_ldsb_braddr_rx_reg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ldsb_braddr_rxe16(line, op_0, op_1);
}

/*
 * Insn ldsh defined at ../../../targets/sparc64/opmatch.def:812:1-34
 */
void insn_ldsh_braddr_rr_reg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ldsh_braddr_rre16(line, op_0, op_1);
}

/*
 * Insn ldsh defined at ../../../targets/sparc64/opmatch.def:813:1-34
 */
void insn_ldsh_braddr_ri_reg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ldsh_braddr_rie16(line, op_0, op_1);
}

/*
 * Insn ldsh defined at ../../../targets/sparc64/opmatch.def:814:1-34
 */
void insn_ldsh_braddr_rx_reg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ldsh_braddr_rxe16(line, op_0, op_1);
}

/*
 * Insn ldsw defined at ../../../targets/sparc64/opmatch.def:815:1-34
 */
void insn_ldsw_braddr_rr_reg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ldsw_braddr_rre16(line, op_0, op_1);
}

/*
 * Insn ldsw defined at ../../../targets/sparc64/opmatch.def:816:1-34
 */
void insn_ldsw_braddr_ri_reg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ldsw_braddr_rie16(line, op_0, op_1);
}

/*
 * Insn ldsw defined at ../../../targets/sparc64/opmatch.def:817:1-34
 */
void insn_ldsw_braddr_rx_reg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ldsw_braddr_rxe16(line, op_0, op_1);
}

/*
 * Insn ldub defined at ../../../targets/sparc64/opmatch.def:818:1-34
 */
void insn_ldub_braddr_rr_reg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ldub_braddr_rre16(line, op_0, op_1);
}

/*
 * Insn ldub defined at ../../../targets/sparc64/opmatch.def:819:1-34
 */
void insn_ldub_braddr_ri_reg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ldub_braddr_rie16(line, op_0, op_1);
}

/*
 * Insn ldub defined at ../../../targets/sparc64/opmatch.def:820:1-34
 */
void insn_ldub_braddr_rx_reg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ldub_braddr_rxe16(line, op_0, op_1);
}

/*
 * Insn lduh defined at ../../../targets/sparc64/opmatch.def:821:1-34
 */
void insn_lduh_braddr_rr_reg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   lduh_braddr_rre16(line, op_0, op_1);
}

/*
 * Insn lduh defined at ../../../targets/sparc64/opmatch.def:822:1-34
 */
void insn_lduh_braddr_ri_reg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   lduh_braddr_rie16(line, op_0, op_1);
}

/*
 * Insn lduh defined at ../../../targets/sparc64/opmatch.def:823:1-34
 */
void insn_lduh_braddr_rx_reg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   lduh_braddr_rxe16(line, op_0, op_1);
}

/*
 * Insn lduw defined at ../../../targets/sparc64/opmatch.def:824:1-34
 */
void insn_lduw_braddr_rr_reg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   lduw_braddr_rre16(line, op_0, op_1);
}

/*
 * Insn lduw defined at ../../../targets/sparc64/opmatch.def:825:1-34
 */
void insn_lduw_braddr_ri_reg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   lduw_braddr_rie16(line, op_0, op_1);
}

/*
 * Insn lduw defined at ../../../targets/sparc64/opmatch.def:826:1-34
 */
void insn_lduw_braddr_rx_reg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   lduw_braddr_rxe16(line, op_0, op_1);
}

/*
 * Insn ldx defined at ../../../targets/sparc64/opmatch.def:827:1-32
 */
void insn_ldx_braddr_rr_reg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ldx_braddr_rre16(line, op_0, op_1);
}

/*
 * Insn ldx defined at ../../../targets/sparc64/opmatch.def:828:1-32
 */
void insn_ldx_braddr_ri_reg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ldx_braddr_rie16(line, op_0, op_1);
}

/*
 * Insn ldx defined at ../../../targets/sparc64/opmatch.def:829:1-32
 */
void insn_ldx_braddr_rx_reg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ldx_braddr_rxe16(line, op_0, op_1);
}

/*
 * Insn ldd defined at ../../../targets/sparc64/opmatch.def:831:1-32
 */
void insn_ldd_braddr_rr_reg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ldd_braddr_rre16(line, op_0, op_1);
}

/*
 * Insn ldd defined at ../../../targets/sparc64/opmatch.def:832:1-32
 */
void insn_ldd_braddr_ri_reg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ldd_braddr_rie16(line, op_0, op_1);
}

/*
 * Insn ldd defined at ../../../targets/sparc64/opmatch.def:833:1-32
 */
void insn_ldd_braddr_rx_reg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ldd_braddr_rxe16(line, op_0, op_1);
}

/*
 * Insn ld defined at ../../../targets/sparc64/opmatch.def:835:1-32
 */
void insn_ld_braddr_rr_reg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ld_braddr_rre16(line, op_0, op_1);
}

/*
 * Insn ld defined at ../../../targets/sparc64/opmatch.def:836:1-32
 */
void insn_ld_braddr_ri_reg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ld_braddr_rie16(line, op_0, op_1);
}

/*
 * Insn ld defined at ../../../targets/sparc64/opmatch.def:837:1-32
 */
void insn_ld_braddr_rx_reg(int line, struct compound_braddr_rx * op_0, uint8_t op_1) {
   ld_braddr_rxe16(line, op_0, op_1);
}

/*
 * Insn ldsba defined at ../../../targets/sparc64/opmatch.def:839:1-42
 */
void insn_ldsba_braddr_rr_immasi_reg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   ldsba_braddr_rr_immasie16(line, op_0, op_1);
}

/*
 * Insn ldsba defined at ../../../targets/sparc64/opmatch.def:840:1-39
 */
void insn_ldsba_braddr_ri_asi_reg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   ldsba_braddr_ri_asie16(line, op_0, op_1);
}

/*
 * Insn ldsha defined at ../../../targets/sparc64/opmatch.def:841:1-42
 */
void insn_ldsha_braddr_rr_immasi_reg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   ldsha_braddr_rr_immasie16(line, op_0, op_1);
}

/*
 * Insn ldsha defined at ../../../targets/sparc64/opmatch.def:842:1-39
 */
void insn_ldsha_braddr_ri_asi_reg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   ldsha_braddr_ri_asie16(line, op_0, op_1);
}

/*
 * Insn ldswa defined at ../../../targets/sparc64/opmatch.def:843:1-42
 */
void insn_ldswa_braddr_rr_immasi_reg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   ldswa_braddr_rr_immasie16(line, op_0, op_1);
}

/*
 * Insn ldswa defined at ../../../targets/sparc64/opmatch.def:844:1-39
 */
void insn_ldswa_braddr_ri_asi_reg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   ldswa_braddr_ri_asie16(line, op_0, op_1);
}

/*
 * Insn lduba defined at ../../../targets/sparc64/opmatch.def:845:1-42
 */
void insn_lduba_braddr_rr_immasi_reg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   lduba_braddr_rr_immasie16(line, op_0, op_1);
}

/*
 * Insn lduba defined at ../../../targets/sparc64/opmatch.def:846:1-39
 */
void insn_lduba_braddr_ri_asi_reg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   lduba_braddr_ri_asie16(line, op_0, op_1);
}

/*
 * Insn lduha defined at ../../../targets/sparc64/opmatch.def:847:1-42
 */
void insn_lduha_braddr_rr_immasi_reg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   lduha_braddr_rr_immasie16(line, op_0, op_1);
}

/*
 * Insn lduha defined at ../../../targets/sparc64/opmatch.def:848:1-39
 */
void insn_lduha_braddr_ri_asi_reg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   lduha_braddr_ri_asie16(line, op_0, op_1);
}

/*
 * Insn lduwa defined at ../../../targets/sparc64/opmatch.def:849:1-42
 */
void insn_lduwa_braddr_rr_immasi_reg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   lduwa_braddr_rr_immasie16(line, op_0, op_1);
}

/*
 * Insn lduwa defined at ../../../targets/sparc64/opmatch.def:850:1-39
 */
void insn_lduwa_braddr_ri_asi_reg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   lduwa_braddr_ri_asie16(line, op_0, op_1);
}

/*
 * Insn ldxa defined at ../../../targets/sparc64/opmatch.def:851:1-40
 */
void insn_ldxa_braddr_rr_immasi_reg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   ldxa_braddr_rr_immasie16(line, op_0, op_1);
}

/*
 * Insn ldxa defined at ../../../targets/sparc64/opmatch.def:852:1-38
 */
void insn_ldxa_braddr_ri_asi_reg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   ldxa_braddr_ri_asie16(line, op_0, op_1);
}

/*
 * Insn ldda defined at ../../../targets/sparc64/opmatch.def:854:1-40
 */
void insn_ldda_braddr_rr_immasi_reg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   ldda_braddr_rr_immasie16(line, op_0, op_1);
}

/*
 * Insn ldda defined at ../../../targets/sparc64/opmatch.def:855:1-38
 */
void insn_ldda_braddr_ri_asi_reg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   ldda_braddr_ri_asie16(line, op_0, op_1);
}

/*
 * Insn lda defined at ../../../targets/sparc64/opmatch.def:857:1-40
 */
void insn_lda_braddr_rr_immasi_reg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   lda_braddr_rr_immasie16(line, op_0, op_1);
}

/*
 * Insn lda defined at ../../../targets/sparc64/opmatch.def:858:1-38
 */
void insn_lda_braddr_ri_asi_reg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   lda_braddr_ri_asie16(line, op_0, op_1);
}

/*
 * Insn st defined at ../../../targets/sparc64/opmatch.def:860:1-31
 */
void insn_st_freg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   st_e14braddr_rr(line, op_0, op_1);
}

/*
 * Insn st defined at ../../../targets/sparc64/opmatch.def:861:1-31
 */
void insn_st_freg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   st_e14braddr_ri(line, op_0, op_1);
}

/*
 * Insn st defined at ../../../targets/sparc64/opmatch.def:862:1-31
 */
void insn_st_freg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   st_e14braddr_rx(line, op_0, op_1);
}

/*
 * Insn std defined at ../../../targets/sparc64/opmatch.def:863:1-33
 */
void insn_std_freg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   std_e14braddr_rr(line, op_0, op_1);
}

/*
 * Insn std defined at ../../../targets/sparc64/opmatch.def:864:1-33
 */
void insn_std_freg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   std_e14braddr_ri(line, op_0, op_1);
}

/*
 * Insn std defined at ../../../targets/sparc64/opmatch.def:865:1-33
 */
void insn_std_freg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   std_e14braddr_rx(line, op_0, op_1);
}

/*
 * Insn stq defined at ../../../targets/sparc64/opmatch.def:866:1-33
 */
void insn_stq_freg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   stq_e14braddr_rr(line, op_0, op_1);
}

/*
 * Insn stq defined at ../../../targets/sparc64/opmatch.def:867:1-33
 */
void insn_stq_freg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   stq_e14braddr_ri(line, op_0, op_1);
}

/*
 * Insn stq defined at ../../../targets/sparc64/opmatch.def:868:1-33
 */
void insn_stq_freg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   stq_e14braddr_rx(line, op_0, op_1);
}

/*
 * Insn st defined at ../../../targets/sparc64/opmatch.def:869:1-27
 */
void insn_st_fsr_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   st_e15braddr_rr(line, op_0, op_1);
}

/*
 * Insn st defined at ../../../targets/sparc64/opmatch.def:870:1-27
 */
void insn_st_fsr_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   st_e15braddr_ri(line, op_0, op_1);
}

/*
 * Insn st defined at ../../../targets/sparc64/opmatch.def:871:1-27
 */
void insn_st_fsr_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   st_e15braddr_rx(line, op_0, op_1);
}

/*
 * Insn stx defined at ../../../targets/sparc64/opmatch.def:872:1-29
 */
void insn_stx_fsr_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   stx_e15braddr_rr(line, op_0, op_1);
}

/*
 * Insn stx defined at ../../../targets/sparc64/opmatch.def:873:1-29
 */
void insn_stx_fsr_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   stx_e15braddr_ri(line, op_0, op_1);
}

/*
 * Insn stx defined at ../../../targets/sparc64/opmatch.def:874:1-29
 */
void insn_stx_fsr_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   stx_e15braddr_rx(line, op_0, op_1);
}

/*
 * Insn sta defined at ../../../targets/sparc64/opmatch.def:876:1-39
 */
void insn_sta_freg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   sta_e14braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn sta defined at ../../../targets/sparc64/opmatch.def:877:1-37
 */
void insn_sta_freg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   sta_e14braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stda defined at ../../../targets/sparc64/opmatch.def:878:1-41
 */
void insn_stda_freg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stda_e14braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stda defined at ../../../targets/sparc64/opmatch.def:879:1-38
 */
void insn_stda_freg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stda_e14braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stqa defined at ../../../targets/sparc64/opmatch.def:880:1-41
 */
void insn_stqa_freg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stqa_e14braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stqa defined at ../../../targets/sparc64/opmatch.def:881:1-38
 */
void insn_stqa_freg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stqa_e14braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stb defined at ../../../targets/sparc64/opmatch.def:883:1-33
 */
void insn_stb_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   stb_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn stb defined at ../../../targets/sparc64/opmatch.def:884:1-33
 */
void insn_stb_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   stb_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn stb defined at ../../../targets/sparc64/opmatch.def:885:1-33
 */
void insn_stb_reg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   stb_e16braddr_rx(line, op_0, op_1);
}

/*
 * Insn sth defined at ../../../targets/sparc64/opmatch.def:886:1-33
 */
void insn_sth_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   sth_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn sth defined at ../../../targets/sparc64/opmatch.def:887:1-33
 */
void insn_sth_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   sth_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn sth defined at ../../../targets/sparc64/opmatch.def:888:1-33
 */
void insn_sth_reg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   sth_e16braddr_rx(line, op_0, op_1);
}

/*
 * Insn stw defined at ../../../targets/sparc64/opmatch.def:889:1-33
 */
void insn_stw_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   stw_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn stw defined at ../../../targets/sparc64/opmatch.def:890:1-33
 */
void insn_stw_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   stw_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn stw defined at ../../../targets/sparc64/opmatch.def:891:1-33
 */
void insn_stw_reg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   stw_e16braddr_rx(line, op_0, op_1);
}

/*
 * Insn stx defined at ../../../targets/sparc64/opmatch.def:892:1-33
 */
void insn_stx_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   stx_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn stx defined at ../../../targets/sparc64/opmatch.def:893:1-33
 */
void insn_stx_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   stx_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn stx defined at ../../../targets/sparc64/opmatch.def:894:1-33
 */
void insn_stx_reg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   stx_e16braddr_rx(line, op_0, op_1);
}

/*
 * Insn std defined at ../../../targets/sparc64/opmatch.def:896:1-33
 */
void insn_std_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   std_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn std defined at ../../../targets/sparc64/opmatch.def:897:1-33
 */
void insn_std_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   std_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn std defined at ../../../targets/sparc64/opmatch.def:898:1-33
 */
void insn_std_reg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   std_e16braddr_rx(line, op_0, op_1);
}

/*
 * Insn stsb defined at ../../../targets/sparc64/opmatch.def:900:1-34
 */
void insn_stsb_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   stsb_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn stsb defined at ../../../targets/sparc64/opmatch.def:901:1-34
 */
void insn_stsb_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   stsb_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn stsb defined at ../../../targets/sparc64/opmatch.def:902:1-34
 */
void insn_stsb_reg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   stsb_e16braddr_rx(line, op_0, op_1);
}

/*
 * Insn stub defined at ../../../targets/sparc64/opmatch.def:903:1-34
 */
void insn_stub_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   stub_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn stub defined at ../../../targets/sparc64/opmatch.def:904:1-34
 */
void insn_stub_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   stub_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn stub defined at ../../../targets/sparc64/opmatch.def:905:1-34
 */
void insn_stub_reg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   stub_e16braddr_rx(line, op_0, op_1);
}

/*
 * Insn stsh defined at ../../../targets/sparc64/opmatch.def:906:1-34
 */
void insn_stsh_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   stsh_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn stsh defined at ../../../targets/sparc64/opmatch.def:907:1-34
 */
void insn_stsh_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   stsh_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn stsh defined at ../../../targets/sparc64/opmatch.def:908:1-34
 */
void insn_stsh_reg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   stsh_e16braddr_rx(line, op_0, op_1);
}

/*
 * Insn stuh defined at ../../../targets/sparc64/opmatch.def:909:1-34
 */
void insn_stuh_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   stuh_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn stuh defined at ../../../targets/sparc64/opmatch.def:910:1-34
 */
void insn_stuh_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   stuh_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn stuh defined at ../../../targets/sparc64/opmatch.def:911:1-34
 */
void insn_stuh_reg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   stuh_e16braddr_rx(line, op_0, op_1);
}

/*
 * Insn st defined at ../../../targets/sparc64/opmatch.def:912:1-32
 */
void insn_st_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   st_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn st defined at ../../../targets/sparc64/opmatch.def:913:1-32
 */
void insn_st_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   st_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn st defined at ../../../targets/sparc64/opmatch.def:914:1-32
 */
void insn_st_reg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   st_e16braddr_rx(line, op_0, op_1);
}

/*
 * Insn stsw defined at ../../../targets/sparc64/opmatch.def:915:1-34
 */
void insn_stsw_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   stsw_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn stsw defined at ../../../targets/sparc64/opmatch.def:916:1-34
 */
void insn_stsw_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   stsw_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn stsw defined at ../../../targets/sparc64/opmatch.def:917:1-34
 */
void insn_stsw_reg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   stsw_e16braddr_rx(line, op_0, op_1);
}

/*
 * Insn stuw defined at ../../../targets/sparc64/opmatch.def:918:1-34
 */
void insn_stuw_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   stuw_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn stuw defined at ../../../targets/sparc64/opmatch.def:919:1-34
 */
void insn_stuw_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   stuw_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn stuw defined at ../../../targets/sparc64/opmatch.def:920:1-34
 */
void insn_stuw_reg_braddr_rx(int line, uint8_t op_0, struct compound_braddr_rx * op_1) {
   stuw_e16braddr_rx(line, op_0, op_1);
}

/*
 * Insn stba defined at ../../../targets/sparc64/opmatch.def:922:1-41
 */
void insn_stba_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stba_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stba defined at ../../../targets/sparc64/opmatch.def:923:1-39
 */
void insn_stba_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stba_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stha defined at ../../../targets/sparc64/opmatch.def:924:1-41
 */
void insn_stha_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stha_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stha defined at ../../../targets/sparc64/opmatch.def:925:1-39
 */
void insn_stha_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stha_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stwa defined at ../../../targets/sparc64/opmatch.def:926:1-41
 */
void insn_stwa_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stwa_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stwa defined at ../../../targets/sparc64/opmatch.def:927:1-39
 */
void insn_stwa_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stwa_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stxa defined at ../../../targets/sparc64/opmatch.def:928:1-41
 */
void insn_stxa_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stxa_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stxa defined at ../../../targets/sparc64/opmatch.def:929:1-39
 */
void insn_stxa_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stxa_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stda defined at ../../../targets/sparc64/opmatch.def:931:1-41
 */
void insn_stda_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stda_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stda defined at ../../../targets/sparc64/opmatch.def:932:1-39
 */
void insn_stda_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stda_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stsba defined at ../../../targets/sparc64/opmatch.def:934:1-42
 */
void insn_stsba_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stsba_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stsba defined at ../../../targets/sparc64/opmatch.def:935:1-39
 */
void insn_stsba_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stsba_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stuba defined at ../../../targets/sparc64/opmatch.def:936:1-42
 */
void insn_stuba_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stuba_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stuba defined at ../../../targets/sparc64/opmatch.def:937:1-39
 */
void insn_stuba_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stuba_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stsha defined at ../../../targets/sparc64/opmatch.def:938:1-42
 */
void insn_stsha_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stsha_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stsha defined at ../../../targets/sparc64/opmatch.def:939:1-39
 */
void insn_stsha_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stsha_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stuha defined at ../../../targets/sparc64/opmatch.def:940:1-42
 */
void insn_stuha_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stuha_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stuha defined at ../../../targets/sparc64/opmatch.def:941:1-39
 */
void insn_stuha_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stuha_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stswa defined at ../../../targets/sparc64/opmatch.def:942:1-42
 */
void insn_stswa_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stswa_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stswa defined at ../../../targets/sparc64/opmatch.def:943:1-39
 */
void insn_stswa_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stswa_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn stuwa defined at ../../../targets/sparc64/opmatch.def:944:1-42
 */
void insn_stuwa_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stuwa_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stuwa defined at ../../../targets/sparc64/opmatch.def:945:1-39
 */
void insn_stuwa_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stuwa_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn sta defined at ../../../targets/sparc64/opmatch.def:946:1-40
 */
void insn_sta_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   sta_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn sta defined at ../../../targets/sparc64/opmatch.def:947:1-38
 */
void insn_sta_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   sta_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn call defined at ../../../targets/sparc64/opmatch.def:949:1-12
 */
void insn_call_symbol(int line, struct expr * op_0) {
   call_xu64(line, op_0);
}

/*
 * Insn call defined at ../../../targets/sparc64/opmatch.def:950:1-20
 */
void insn_call_symbol_number(int line, struct expr * op_0, uint32_t op_1) {
   call_xu64u32(line, op_0, op_1);
}

/*
 * Insn jmpl defined at ../../../targets/sparc64/opmatch.def:951:1-18
 */
void insn_jmpl_addr_rr_reg(int line, struct compound_addr_rr * op_0, uint8_t op_1) {
   jmpl_addr_rre16(line, op_0, op_1);
}

/*
 * Insn jmpl defined at ../../../targets/sparc64/opmatch.def:952:1-18
 */
void insn_jmpl_addr_ri_reg(int line, struct compound_addr_ri * op_0, uint8_t op_1) {
   jmpl_addr_rie16(line, op_0, op_1);
}

/*
 * Insn return defined at ../../../targets/sparc64/opmatch.def:953:1-15
 */
void insn_return_addr_rr(int line, struct compound_addr_rr * op_0) {
   return_addr_rr(line, op_0);
}

/*
 * Insn return defined at ../../../targets/sparc64/opmatch.def:954:1-15
 */
void insn_return_addr_ri(int line, struct compound_addr_ri * op_0) {
   return_addr_ri(line, op_0);
}

/*
 * Insn illtrap defined at ../../../targets/sparc64/opmatch.def:957:1-15
 */
void insn_illtrap_u22num(int line, uint32_t op_0) {
   illtrap_u22(line, op_0);
}

/*
 * Insn sir defined at ../../../targets/sparc64/opmatch.def:958:1-11
 */
void insn_sir_i13num(int line, int16_t op_0) {
   sir_i13(line, op_0);
}

/*
 * Insn ta defined at ../../../targets/sparc64/opmatch.def:960:1-31
 */
void insn_ta_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   ta_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn ta defined at ../../../targets/sparc64/opmatch.def:961:1-31
 */
void insn_ta_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   ta_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tn defined at ../../../targets/sparc64/opmatch.def:962:1-31
 */
void insn_tn_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tn_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tn defined at ../../../targets/sparc64/opmatch.def:963:1-31
 */
void insn_tn_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tn_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tne defined at ../../../targets/sparc64/opmatch.def:964:1-33
 */
void insn_tne_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tne_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tne defined at ../../../targets/sparc64/opmatch.def:965:1-33
 */
void insn_tne_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tne_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn te defined at ../../../targets/sparc64/opmatch.def:966:1-31
 */
void insn_te_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   te_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn te defined at ../../../targets/sparc64/opmatch.def:967:1-31
 */
void insn_te_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   te_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tg defined at ../../../targets/sparc64/opmatch.def:968:1-31
 */
void insn_tg_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tg_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tg defined at ../../../targets/sparc64/opmatch.def:969:1-31
 */
void insn_tg_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tg_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tle defined at ../../../targets/sparc64/opmatch.def:970:1-33
 */
void insn_tle_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tle_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tle defined at ../../../targets/sparc64/opmatch.def:971:1-33
 */
void insn_tle_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tle_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tge defined at ../../../targets/sparc64/opmatch.def:972:1-33
 */
void insn_tge_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tge_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tge defined at ../../../targets/sparc64/opmatch.def:973:1-33
 */
void insn_tge_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tge_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tl defined at ../../../targets/sparc64/opmatch.def:974:1-31
 */
void insn_tl_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tl_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tl defined at ../../../targets/sparc64/opmatch.def:975:1-31
 */
void insn_tl_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tl_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tgu defined at ../../../targets/sparc64/opmatch.def:976:1-33
 */
void insn_tgu_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tgu_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tgu defined at ../../../targets/sparc64/opmatch.def:977:1-33
 */
void insn_tgu_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tgu_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tleu defined at ../../../targets/sparc64/opmatch.def:978:1-35
 */
void insn_tleu_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tleu_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tleu defined at ../../../targets/sparc64/opmatch.def:979:1-35
 */
void insn_tleu_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tleu_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tcc defined at ../../../targets/sparc64/opmatch.def:980:1-33
 */
void insn_tcc_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tcc_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tcc defined at ../../../targets/sparc64/opmatch.def:981:1-33
 */
void insn_tcc_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tcc_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tcs defined at ../../../targets/sparc64/opmatch.def:982:1-33
 */
void insn_tcs_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tcs_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tcs defined at ../../../targets/sparc64/opmatch.def:983:1-33
 */
void insn_tcs_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tcs_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tpos defined at ../../../targets/sparc64/opmatch.def:984:1-35
 */
void insn_tpos_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tpos_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tpos defined at ../../../targets/sparc64/opmatch.def:985:1-35
 */
void insn_tpos_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tpos_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tneg defined at ../../../targets/sparc64/opmatch.def:986:1-35
 */
void insn_tneg_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tneg_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tneg defined at ../../../targets/sparc64/opmatch.def:987:1-35
 */
void insn_tneg_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tneg_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tvc defined at ../../../targets/sparc64/opmatch.def:988:1-33
 */
void insn_tvc_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tvc_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tvc defined at ../../../targets/sparc64/opmatch.def:989:1-33
 */
void insn_tvc_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tvc_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tvs defined at ../../../targets/sparc64/opmatch.def:990:1-33
 */
void insn_tvs_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tvs_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tvs defined at ../../../targets/sparc64/opmatch.def:991:1-33
 */
void insn_tvs_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tvs_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tnz defined at ../../../targets/sparc64/opmatch.def:993:1-33
 */
void insn_tnz_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tnz_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tnz defined at ../../../targets/sparc64/opmatch.def:994:1-33
 */
void insn_tnz_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tnz_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tz defined at ../../../targets/sparc64/opmatch.def:995:1-31
 */
void insn_tz_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tz_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tz defined at ../../../targets/sparc64/opmatch.def:996:1-31
 */
void insn_tz_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tz_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tgeu defined at ../../../targets/sparc64/opmatch.def:997:1-34
 */
void insn_tgeu_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tgeu_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tgeu defined at ../../../targets/sparc64/opmatch.def:998:1-34
 */
void insn_tgeu_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tgeu_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn tlu defined at ../../../targets/sparc64/opmatch.def:999:1-33
 */
void insn_tlu_icc_trapnum_rr(int line, uint8_t op_0, struct compound_trapnum_rr * op_1) {
   tlu_e17trapnum_rr(line, op_0, op_1);
}

/*
 * Insn tlu defined at ../../../targets/sparc64/opmatch.def:1000:1-33
 */
void insn_tlu_icc_trapnum_ri(int line, uint8_t op_0, struct compound_trapnum_ri * op_1) {
   tlu_e17trapnum_ri(line, op_0, op_1);
}

/*
 * Insn nop defined at ../../../targets/sparc64/opmatch.def:1002:1-14
 */
void insn_nop_(int line) {
   nop_(line);
}

/*
 * Insn rd defined at ../../../targets/sparc64/opmatch.def:1004:1-22
 */
void insn_rd_asr_reg(int line, uint8_t op_0, uint8_t op_1) {
   rd_e11e16(line, op_0, op_1);
}

/*
 * Insn wr defined at ../../../targets/sparc64/opmatch.def:1005:1-26
 */
void insn_wr_reg_reg_asr(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   wr_e16e16e11(line, op_0, op_1, op_2);
}

/*
 * Insn wr defined at ../../../targets/sparc64/opmatch.def:1006:1-29
 */
void insn_wr_reg_i13num_asr(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   wr_e16i13e11(line, op_0, op_1, op_2);
}

/*
 * Insn impl1 defined at ../../../targets/sparc64/opmatch.def:1010:1-37
 */
void insn_impl1_u5num_u19num(int line, uint8_t op_0, uint32_t op_1) {
   impl1_u5u19(line, op_0, op_1);
}

/*
 * Insn impl2 defined at ../../../targets/sparc64/opmatch.def:1011:1-37
 */
void insn_impl2_u5num_u19num(int line, uint8_t op_0, uint32_t op_1) {
   impl2_u5u19(line, op_0, op_1);
}

/*
 * Insn rdpr defined at ../../../targets/sparc64/opmatch.def:1013:1-13
 */
void insn_rdpr_pr_reg(int line, uint8_t op_0, uint8_t op_1) {
   rdpr_e19e16(line, op_0, op_1);
}

/*
 * Insn wrpr defined at ../../../targets/sparc64/opmatch.def:1014:1-18
 */
void insn_wrpr_reg_reg_pr(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   wrpr_e16e16e19(line, op_0, op_1, op_2);
}

/*
 * Insn wrpr defined at ../../../targets/sparc64/opmatch.def:1015:1-21
 */
void insn_wrpr_reg_i13num_pr(int line, uint8_t op_0, int16_t op_1, uint8_t op_2) {
   wrpr_e16i13e19(line, op_0, op_1, op_2);
}

/*
 * Insn done defined at ../../../targets/sparc64/opmatch.def:1016:1-5
 */
void insn_done_(int line) {
   done_(line);
}

/*
 * Insn retry defined at ../../../targets/sparc64/opmatch.def:1017:1-6
 */
void insn_retry_(int line) {
   retry_(line);
}

/*
 * Insn flushw defined at ../../../targets/sparc64/opmatch.def:1018:1-7
 */
void insn_flushw_(int line) {
   flushw_(line);
}

/*
 * Insn saved defined at ../../../targets/sparc64/opmatch.def:1019:1-6
 */
void insn_saved_(int line) {
   saved_(line);
}

/*
 * Insn restored defined at ../../../targets/sparc64/opmatch.def:1020:1-9
 */
void insn_restored_(int line) {
   restored_(line);
}

/*
 * Insn cmp defined at ../../../targets/sparc64/opmatch.def:1025:1-22
 */
void insn_cmp_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   cmp_e16e16(line, op_0, op_1);
}

/*
 * Insn cmp defined at ../../../targets/sparc64/opmatch.def:1026:1-25
 */
void insn_cmp_reg_i13num(int line, uint8_t op_0, int16_t op_1) {
   cmp_e16i13(line, op_0, op_1);
}

/*
 * Insn jmp defined at ../../../targets/sparc64/opmatch.def:1027:1-21
 */
void insn_jmp_addr_rr(int line, struct compound_addr_rr * op_0) {
   jmp_addr_rr(line, op_0);
}

/*
 * Insn jmp defined at ../../../targets/sparc64/opmatch.def:1028:1-21
 */
void insn_jmp_addr_ri(int line, struct compound_addr_ri * op_0) {
   jmp_addr_ri(line, op_0);
}

/*
 * Insn call defined at ../../../targets/sparc64/opmatch.def:1029:1-23
 */
void insn_call_addr_rr(int line, struct compound_addr_rr * op_0) {
   call_addr_rr(line, op_0);
}

/*
 * Insn call defined at ../../../targets/sparc64/opmatch.def:1030:1-23
 */
void insn_call_addr_ri(int line, struct compound_addr_ri * op_0) {
   call_addr_ri(line, op_0);
}

/*
 * Insn call defined at ../../../targets/sparc64/opmatch.def:1031:1-30
 */
void insn_call_addr_rr_number(int line, struct compound_addr_rr * op_0, uint32_t op_1) {
   call_addr_rru32(line, op_0, op_1);
}

/*
 * Insn call defined at ../../../targets/sparc64/opmatch.def:1032:1-30
 */
void insn_call_addr_ri_number(int line, struct compound_addr_ri * op_0, uint32_t op_1) {
   call_addr_riu32(line, op_0, op_1);
}

/*
 * Insn ret defined at ../../../targets/sparc64/opmatch.def:1033:1-14
 */
void insn_ret_(int line) {
   ret_(line);
}

/*
 * Insn retl defined at ../../../targets/sparc64/opmatch.def:1034:1-16
 */
void insn_retl_(int line) {
   retl_(line);
}

/*
 * Insn save defined at ../../../targets/sparc64/opmatch.def:1035:1-16
 */
void insn_save_(int line) {
   save_(line);
}

/*
 * Insn restore defined at ../../../targets/sparc64/opmatch.def:1036:1-22
 */
void insn_restore_(int line) {
   restore_(line);
}

/*
 * Insn iprefetch defined at ../../../targets/sparc64/opmatch.def:1037:1-31
 */
void insn_iprefetch_symbol(int line, struct expr * op_0) {
   iprefetch_xu64(line, op_0);
}

/*
 * Insn tst defined at ../../../targets/sparc64/opmatch.def:1038:1-18
 */
void insn_tst_reg(int line, uint8_t op_0) {
   tst_e16(line, op_0);
}

/*
 * Insn setuw defined at ../../../targets/sparc64/opmatch.def:1039:1-28
 */
void insn_setuw_u32num_reg(int line, uint32_t op_0, uint8_t op_1) {
   setuw_u32e16(line, op_0, op_1);
}

/*
 * Insn set defined at ../../../targets/sparc64/opmatch.def:1040:1-25
 */
void insn_set_u32num_reg(int line, uint32_t op_0, uint8_t op_1) {
   set_u32e16(line, op_0, op_1);
}

/*
 * Insn setsw defined at ../../../targets/sparc64/opmatch.def:1041:1-28
 */
void insn_setsw_i32num_reg(int line, int32_t op_0, uint8_t op_1) {
   setsw_i32e16(line, op_0, op_1);
}

/*
 * Insn setx defined at ../../../targets/sparc64/opmatch.def:1042:1-31
 */
void insn_setx_i64num_reg_reg(int line, int64_t op_0, uint8_t op_1, uint8_t op_2) {
   setx_i64e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn signx defined at ../../../targets/sparc64/opmatch.def:1043:1-26
 */
void insn_signx_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   signx_e16e16(line, op_0, op_1);
}

/*
 * Insn signx defined at ../../../targets/sparc64/opmatch.def:1044:1-21
 */
void insn_signx_reg(int line, uint8_t op_0) {
   signx_e16(line, op_0);
}

/*
 * Insn not defined at ../../../targets/sparc64/opmatch.def:1045:1-22
 */
void insn_not_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   not_e16e16(line, op_0, op_1);
}

/*
 * Insn not defined at ../../../targets/sparc64/opmatch.def:1046:1-18
 */
void insn_not_reg(int line, uint8_t op_0) {
   not_e16(line, op_0);
}

/*
 * Insn neg defined at ../../../targets/sparc64/opmatch.def:1047:1-22
 */
void insn_neg_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   neg_e16e16(line, op_0, op_1);
}

/*
 * Insn neg defined at ../../../targets/sparc64/opmatch.def:1048:1-18
 */
void insn_neg_reg(int line, uint8_t op_0) {
   neg_e16(line, op_0);
}

/*
 * Insn cas defined at ../../../targets/sparc64/opmatch.def:1050:1-31
 */
void insn_cas_braddr_r_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   cas_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn casl defined at ../../../targets/sparc64/opmatch.def:1051:1-33
 */
void insn_casl_braddr_r_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   casl_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn casx defined at ../../../targets/sparc64/opmatch.def:1052:1-33
 */
void insn_casx_braddr_r_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   casx_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn casxl defined at ../../../targets/sparc64/opmatch.def:1053:1-34
 */
void insn_casxl_braddr_r_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   casxl_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn inc defined at ../../../targets/sparc64/opmatch.def:1055:1-18
 */
void insn_inc_reg(int line, uint8_t op_0) {
   inc_e16(line, op_0);
}

/*
 * Insn inc defined at ../../../targets/sparc64/opmatch.def:1056:1-25
 */
void insn_inc_i13num_reg(int line, int16_t op_0, uint8_t op_1) {
   inc_i13e16(line, op_0, op_1);
}

/*
 * Insn inccc defined at ../../../targets/sparc64/opmatch.def:1057:1-21
 */
void insn_inccc_reg(int line, uint8_t op_0) {
   inccc_e16(line, op_0);
}

/*
 * Insn inccc defined at ../../../targets/sparc64/opmatch.def:1058:1-28
 */
void insn_inccc_i13num_reg(int line, int16_t op_0, uint8_t op_1) {
   inccc_i13e16(line, op_0, op_1);
}

/*
 * Insn dec defined at ../../../targets/sparc64/opmatch.def:1059:1-18
 */
void insn_dec_reg(int line, uint8_t op_0) {
   dec_e16(line, op_0);
}

/*
 * Insn dec defined at ../../../targets/sparc64/opmatch.def:1060:1-25
 */
void insn_dec_i13num_reg(int line, int16_t op_0, uint8_t op_1) {
   dec_i13e16(line, op_0, op_1);
}

/*
 * Insn deccc defined at ../../../targets/sparc64/opmatch.def:1061:1-21
 */
void insn_deccc_reg(int line, uint8_t op_0) {
   deccc_e16(line, op_0);
}

/*
 * Insn deccc defined at ../../../targets/sparc64/opmatch.def:1062:1-28
 */
void insn_deccc_i13num_reg(int line, int16_t op_0, uint8_t op_1) {
   deccc_i13e16(line, op_0, op_1);
}

/*
 * Insn btst defined at ../../../targets/sparc64/opmatch.def:1064:1-24
 */
void insn_btst_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   btst_e16e16(line, op_0, op_1);
}

/*
 * Insn btst defined at ../../../targets/sparc64/opmatch.def:1065:1-26
 */
void insn_btst_i13num_reg(int line, int16_t op_0, uint8_t op_1) {
   btst_i13e16(line, op_0, op_1);
}

/*
 * Insn bset defined at ../../../targets/sparc64/opmatch.def:1066:1-24
 */
void insn_bset_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   bset_e16e16(line, op_0, op_1);
}

/*
 * Insn bset defined at ../../../targets/sparc64/opmatch.def:1067:1-26
 */
void insn_bset_i13num_reg(int line, int16_t op_0, uint8_t op_1) {
   bset_i13e16(line, op_0, op_1);
}

/*
 * Insn bclr defined at ../../../targets/sparc64/opmatch.def:1068:1-24
 */
void insn_bclr_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   bclr_e16e16(line, op_0, op_1);
}

/*
 * Insn bclr defined at ../../../targets/sparc64/opmatch.def:1069:1-26
 */
void insn_bclr_i13num_reg(int line, int16_t op_0, uint8_t op_1) {
   bclr_i13e16(line, op_0, op_1);
}

/*
 * Insn btog defined at ../../../targets/sparc64/opmatch.def:1070:1-24
 */
void insn_btog_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   btog_e16e16(line, op_0, op_1);
}

/*
 * Insn btog defined at ../../../targets/sparc64/opmatch.def:1071:1-26
 */
void insn_btog_i13num_reg(int line, int16_t op_0, uint8_t op_1) {
   btog_i13e16(line, op_0, op_1);
}

/*
 * Insn clr defined at ../../../targets/sparc64/opmatch.def:1073:1-19
 */
void insn_clr_reg(int line, uint8_t op_0) {
   clr_e16(line, op_0);
}

/*
 * Insn clrb defined at ../../../targets/sparc64/opmatch.def:1074:1-29
 */
void insn_clrb_braddr_rr(int line, struct compound_braddr_rr * op_0) {
   clrb_braddr_rr(line, op_0);
}

/*
 * Insn clrb defined at ../../../targets/sparc64/opmatch.def:1075:1-29
 */
void insn_clrb_braddr_ri(int line, struct compound_braddr_ri * op_0) {
   clrb_braddr_ri(line, op_0);
}

/*
 * Insn clrh defined at ../../../targets/sparc64/opmatch.def:1076:1-30
 */
void insn_clrh_braddr_rr(int line, struct compound_braddr_rr * op_0) {
   clrh_braddr_rr(line, op_0);
}

/*
 * Insn clrh defined at ../../../targets/sparc64/opmatch.def:1077:1-30
 */
void insn_clrh_braddr_ri(int line, struct compound_braddr_ri * op_0) {
   clrh_braddr_ri(line, op_0);
}

/*
 * Insn clr defined at ../../../targets/sparc64/opmatch.def:1078:1-28
 */
void insn_clr_braddr_rr(int line, struct compound_braddr_rr * op_0) {
   clr_braddr_rr(line, op_0);
}

/*
 * Insn clr defined at ../../../targets/sparc64/opmatch.def:1079:1-28
 */
void insn_clr_braddr_ri(int line, struct compound_braddr_ri * op_0) {
   clr_braddr_ri(line, op_0);
}

/*
 * Insn clrx defined at ../../../targets/sparc64/opmatch.def:1080:1-29
 */
void insn_clrx_braddr_rr(int line, struct compound_braddr_rr * op_0) {
   clrx_braddr_rr(line, op_0);
}

/*
 * Insn clrx defined at ../../../targets/sparc64/opmatch.def:1081:1-29
 */
void insn_clrx_braddr_ri(int line, struct compound_braddr_ri * op_0) {
   clrx_braddr_ri(line, op_0);
}

/*
 * Insn clruw defined at ../../../targets/sparc64/opmatch.def:1083:1-26
 */
void insn_clruw_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   clruw_e16e16(line, op_0, op_1);
}

/*
 * Insn clruw defined at ../../../targets/sparc64/opmatch.def:1084:1-21
 */
void insn_clruw_reg(int line, uint8_t op_0) {
   clruw_e16(line, op_0);
}

/*
 * Insn mov defined at ../../../targets/sparc64/opmatch.def:1086:1-22
 */
void insn_mov_reg_reg(int line, uint8_t op_0, uint8_t op_1) {
   mov_e16e16(line, op_0, op_1);
}

/*
 * Insn mov defined at ../../../targets/sparc64/opmatch.def:1087:1-25
 */
void insn_mov_i13num_reg(int line, int16_t op_0, uint8_t op_1) {
   mov_i13e16(line, op_0, op_1);
}

/*
 * Insn mov defined at ../../../targets/sparc64/opmatch.def:1088:1-22
 */
void insn_mov_asr_reg(int line, uint8_t op_0, uint8_t op_1) {
   mov_e11e16(line, op_0, op_1);
}

/*
 * Insn mov defined at ../../../targets/sparc64/opmatch.def:1089:1-22
 */
void insn_mov_reg_asr(int line, uint8_t op_0, uint8_t op_1) {
   mov_e16e11(line, op_0, op_1);
}

/*
 * Insn ldn defined at ../../../targets/sparc64/opmatch.def:1093:1-26
 */
void insn_ldn_braddr_rr_reg(int line, struct compound_braddr_rr * op_0, uint8_t op_1) {
   ldn_braddr_rre16(line, op_0, op_1);
}

/*
 * Insn ldn defined at ../../../targets/sparc64/opmatch.def:1094:1-26
 */
void insn_ldn_braddr_ri_reg(int line, struct compound_braddr_ri * op_0, uint8_t op_1) {
   ldn_braddr_rie16(line, op_0, op_1);
}

/*
 * Insn ldna defined at ../../../targets/sparc64/opmatch.def:1095:1-34
 */
void insn_ldna_braddr_rr_immasi_reg(int line, struct compound_braddr_rr_immasi * op_0, uint8_t op_1) {
   ldna_braddr_rr_immasie16(line, op_0, op_1);
}

/*
 * Insn ldna defined at ../../../targets/sparc64/opmatch.def:1096:1-32
 */
void insn_ldna_braddr_ri_asi_reg(int line, struct compound_braddr_ri_asi * op_0, uint8_t op_1) {
   ldna_braddr_ri_asie16(line, op_0, op_1);
}

/*
 * Insn stn defined at ../../../targets/sparc64/opmatch.def:1097:1-26
 */
void insn_stn_reg_braddr_rr(int line, uint8_t op_0, struct compound_braddr_rr * op_1) {
   stn_e16braddr_rr(line, op_0, op_1);
}

/*
 * Insn stn defined at ../../../targets/sparc64/opmatch.def:1098:1-26
 */
void insn_stn_reg_braddr_ri(int line, uint8_t op_0, struct compound_braddr_ri * op_1) {
   stn_e16braddr_ri(line, op_0, op_1);
}

/*
 * Insn stna defined at ../../../targets/sparc64/opmatch.def:1099:1-34
 */
void insn_stna_reg_braddr_rr_immasi(int line, uint8_t op_0, struct compound_braddr_rr_immasi * op_1) {
   stna_e16braddr_rr_immasi(line, op_0, op_1);
}

/*
 * Insn stna defined at ../../../targets/sparc64/opmatch.def:1100:1-32
 */
void insn_stna_reg_braddr_ri_asi(int line, uint8_t op_0, struct compound_braddr_ri_asi * op_1) {
   stna_e16braddr_ri_asi(line, op_0, op_1);
}

/*
 * Insn slln defined at ../../../targets/sparc64/opmatch.def:1101:1-27
 */
void insn_slln_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   slln_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn slln defined at ../../../targets/sparc64/opmatch.def:1102:1-29
 */
void insn_slln_reg_u6num_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   slln_e16u6e16(line, op_0, op_1, op_2);
}

/*
 * Insn srln defined at ../../../targets/sparc64/opmatch.def:1103:1-27
 */
void insn_srln_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   srln_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn srln defined at ../../../targets/sparc64/opmatch.def:1104:1-29
 */
void insn_srln_reg_u6num_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   srln_e16u6e16(line, op_0, op_1, op_2);
}

/*
 * Insn sran defined at ../../../targets/sparc64/opmatch.def:1105:1-27
 */
void insn_sran_reg_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sran_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn sran defined at ../../../targets/sparc64/opmatch.def:1106:1-29
 */
void insn_sran_reg_u6num_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   sran_e16u6e16(line, op_0, op_1, op_2);
}

/*
 * Insn casn defined at ../../../targets/sparc64/opmatch.def:1107:1-32
 */
void insn_casn_braddr_r_reg_reg(int line, uint8_t op_0, uint8_t op_1, uint8_t op_2) {
   casn_e16e16e16(line, op_0, op_1, op_2);
}

/*
 * Insn casna defined at ../../../targets/sparc64/opmatch.def:1108:1-40
 */
void insn_casna_braddr_r_immasi_reg_reg(int line, struct compound_braddr_r_immasi * op_0, uint8_t op_1, uint8_t op_2) {
   casna_braddr_r_immasie16e16(line, op_0, op_1, op_2);
}

/*
 * Insn casna defined at ../../../targets/sparc64/opmatch.def:1109:1-37
 */
void insn_casna_braddr_r_asi_reg_reg(int line, struct compound_braddr_r_asi * op_0, uint8_t op_1, uint8_t op_2) {
   casna_braddr_r_asie16e16(line, op_0, op_1, op_2);
}

/*
 * Insn clrn defined at ../../../targets/sparc64/opmatch.def:1110:1-24
 */
void insn_clrn_braddr_rr(int line, struct compound_braddr_rr * op_0) {
   clrn_braddr_rr(line, op_0);
}

/*
 * Insn clrn defined at ../../../targets/sparc64/opmatch.def:1111:1-24
 */
void insn_clrn_braddr_ri(int line, struct compound_braddr_ri * op_0) {
   clrn_braddr_ri(line, op_0);
}

