/* Automatically generated; do not edit */

#ifndef TARGETOPER_H
#define TARGETOPER_H


struct tokenarray;

struct compound_am2imm{
   uint8_t m0;
   uint8_t m1;
   uint8_t m2;
   uint8_t m3;
   uint16_t m4;
};
struct compound_am2reg{
   uint8_t m0;
   uint8_t m1;
   uint8_t m2;
   uint8_t m3;
   uint8_t m4;
   uint8_t m5;
   uint8_t m6;
};
struct compound_am3imm{
   uint8_t m0;
   uint8_t m1;
   uint8_t m2;
   uint8_t m3;
   uint8_t m4;
};
struct compound_am3reg{
   uint8_t m0;
   uint8_t m1;
   uint8_t m2;
   uint8_t m3;
   uint8_t m4;
};
struct compound_bangreg{
   uint8_t m0;
   uint8_t m1;
};
struct compound_ishiftop{
   uint8_t m0;
   uint8_t m1;
};
struct compound_reglist{
   uint8_t m0;
   uint16_t m1;
};
struct compound_rshiftop{
   uint8_t m0;
   uint8_t m1;
};
struct compound_signedimm12{
   uint8_t m0;
   uint16_t m1;
};
struct compound_signedimm8{
   uint8_t m0;
   uint8_t m1;
};
struct compound_signedreg{
   uint8_t m0;
   uint8_t m1;
};

struct operand{
   bool is_am2imm;
   struct compound_am2imm val_am2imm;
   bool is_am2reg;
   struct compound_am2reg val_am2reg;
   bool is_am3imm;
   struct compound_am3imm val_am3imm;
   bool is_am3reg;
   struct compound_am3reg val_am3reg;
   bool is_bangreg;
   struct compound_bangreg val_bangreg;
   bool is_bracketreg;
   uint8_t val_bracketreg;
   bool is_expr;
   struct expr * val_expr;
   bool is_imm;
   uint32_t val_imm;
   bool is_ishift;
   struct compound_ishiftop val_ishift;
   bool is_magiczero;
   uint32_t val_magiczero;
   bool is_number;
   uint32_t val_number;
   bool is_qstring;
   const char * val_qstring;
   bool is_reg;
   uint8_t val_reg;
   bool is_reglist;
   struct compound_reglist val_reglist;
   bool is_rshift;
   struct compound_rshiftop val_rshift;
   bool is_rtag;
   uint8_t val_rtag;
   bool is_sectiontype;
   const char * val_sectiontype;
   bool is_signedimm12;
   struct compound_signedimm12 val_signedimm12;
   bool is_signedimm8;
   struct compound_signedimm8 val_signedimm8;
   bool is_signedreg;
   struct compound_signedreg val_signedreg;
   bool is_symbol;
   struct expr * val_symbol;
   bool is_symboltype;
   const char * val_symboltype;
};
void operand_init(struct operand * oper);
void operand_cleanup(struct operand * oper);
void operand_match(int lineno, struct operand * oper, struct tokenarray * toks);


#endif /* TARGETOPER_H */
