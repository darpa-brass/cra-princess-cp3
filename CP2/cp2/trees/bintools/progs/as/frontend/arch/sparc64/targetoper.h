/* Automatically generated; do not edit */

#ifndef TARGETOPER_H
#define TARGETOPER_H


struct tokenarray;

struct compound_addr_ri{
   uint8_t m0;
   int16_t m1;
};
struct compound_addr_rr{
   uint8_t m0;
   uint8_t m1;
};
struct compound_addr_rx{
   uint8_t m0;
   struct expr * m1;
};
struct compound_braddr_r_asi{
   uint8_t m0;
};
struct compound_braddr_r_immasi{
   uint8_t m0;
   uint8_t m1;
};
struct compound_braddr_ri{
   uint8_t m0;
   int16_t m1;
};
struct compound_braddr_ri_asi{
   uint8_t m0;
   int16_t m1;
};
struct compound_braddr_rr{
   uint8_t m0;
   uint8_t m1;
};
struct compound_braddr_rr_immasi{
   uint8_t m0;
   uint8_t m1;
   uint8_t m2;
};
struct compound_braddr_rx{
   uint8_t m0;
   struct expr * m1;
};
struct compound_trapnum_ri{
   uint8_t m0;
   int8_t m1;
};
struct compound_trapnum_rr{
   uint8_t m0;
   uint8_t m1;
};

struct operand{
   bool is_addr_ri;
   struct compound_addr_ri val_addr_ri;
   bool is_addr_rr;
   struct compound_addr_rr val_addr_rr;
   bool is_addr_rx;
   struct compound_addr_rx val_addr_rx;
   bool is_asr;
   uint8_t val_asr;
   bool is_braddr_r;
   uint8_t val_braddr_r;
   bool is_braddr_r_asi;
   struct compound_braddr_r_asi val_braddr_r_asi;
   bool is_braddr_r_immasi;
   struct compound_braddr_r_immasi val_braddr_r_immasi;
   bool is_braddr_ri;
   struct compound_braddr_ri val_braddr_ri;
   bool is_braddr_ri_asi;
   struct compound_braddr_ri_asi val_braddr_ri_asi;
   bool is_braddr_rr;
   struct compound_braddr_rr val_braddr_rr;
   bool is_braddr_rr_immasi;
   struct compound_braddr_rr_immasi val_braddr_rr_immasi;
   bool is_braddr_rx;
   struct compound_braddr_rx val_braddr_rx;
   bool is_expr;
   struct expr * val_expr;
   bool is_fcc;
   uint8_t val_fcc;
   bool is_freg;
   uint8_t val_freg;
   bool is_fsr;
   uint8_t val_fsr;
   bool is_i10num;
   int16_t val_i10num;
   bool is_i11num;
   int16_t val_i11num;
   bool is_i13num;
   int16_t val_i13num;
   bool is_i32num;
   int32_t val_i32num;
   bool is_i64num;
   int64_t val_i64num;
   bool is_icc;
   uint8_t val_icc;
   bool is_magiczero;
   uint32_t val_magiczero;
   bool is_membarmask;
   uint8_t val_membarmask;
   bool is_number;
   uint32_t val_number;
   bool is_pr;
   uint8_t val_pr;
   bool is_qstring;
   const char * val_qstring;
   bool is_reg;
   uint8_t val_reg;
   bool is_registertag;
   uint8_t val_registertag;
   bool is_sectiontype;
   const char * val_sectiontype;
   bool is_symbol;
   struct expr * val_symbol;
   bool is_symboltype;
   const char * val_symboltype;
   bool is_trapnum_ri;
   struct compound_trapnum_ri val_trapnum_ri;
   bool is_trapnum_rr;
   struct compound_trapnum_rr val_trapnum_rr;
   bool is_u19num;
   uint32_t val_u19num;
   bool is_u22num;
   uint32_t val_u22num;
   bool is_u32num;
   uint32_t val_u32num;
   bool is_u5num;
   uint8_t val_u5num;
   bool is_u6num;
   uint8_t val_u6num;
};
void operand_init(struct operand * oper);
void operand_cleanup(struct operand * oper);
void operand_match(int lineno, struct operand * oper, struct tokenarray * toks);


#endif /* TARGETOPER_H */
