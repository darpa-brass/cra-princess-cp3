/* Automatically generated; do not edit */

#ifndef TARGETOPER_H
#define TARGETOPER_H


struct tokenarray;

struct compound_mem{
   struct expr * m0;
   uint8_t m1;
};

struct operand{
   bool is_c0reg;
   uint8_t val_c0reg;
   bool is_c2reg;
   uint8_t val_c2reg;
   bool is_c3reg;
   uint8_t val_c3reg;
   bool is_cc;
   uint8_t val_cc;
   bool is_expr;
   struct expr * val_expr;
   bool is_freg;
   uint8_t val_freg;
   bool is_magiczero;
   uint32_t val_magiczero;
   bool is_mem;
   struct compound_mem val_mem;
   bool is_number;
   uint32_t val_number;
   bool is_qstring;
   const char * val_qstring;
   bool is_reg;
   uint8_t val_reg;
   bool is_rtag;
   uint8_t val_rtag;
   bool is_s16expr;
   struct expr * val_s16expr;
   bool is_sectiontype;
   const char * val_sectiontype;
   bool is_sel;
   uint8_t val_sel;
   bool is_symbol;
   struct expr * val_symbol;
   bool is_symboltype;
   const char * val_symboltype;
   bool is_u16expr;
   struct expr * val_u16expr;
};
void operand_init(struct operand * oper);
void operand_cleanup(struct operand * oper);
void operand_match(int lineno, struct operand * oper, struct tokenarray * toks);


#endif /* TARGETOPER_H */
