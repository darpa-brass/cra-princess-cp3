/* Automatically generated; do not edit */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "common.h"

#include "expr.h"
#include "eparse.h"
#include "token.h"
#include "targetoper.h"

static bool tagrulematch_0(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_GENERALREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_reg = true;
   oper->val_reg = x;
   return true;
}
static bool tagrulematch_1(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_COP0REG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_c0reg = true;
   oper->val_c0reg = x;
   return true;
}
static bool tagrulematch_2(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_COP2REG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_c2reg = true;
   oper->val_c2reg = x;
   return true;
}
static bool tagrulematch_3(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_COP3REG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_c3reg = true;
   oper->val_c3reg = x;
   return true;
}
static bool tagrulematch_4(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_FPREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_freg = true;
   oper->val_freg = x;
   return true;
}
static bool tagrulematch_5(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_FPCC)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_cc = true;
   oper->val_cc = x;
   return true;
}
static bool tagrulematch_6(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint64_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_sel = true;
   oper->val_sel =(uint8_t)x;
   return true;
}
static bool tagrulematch_7(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint64_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_number = true;
   oper->val_number =(uint32_t)x;
   return true;
}
static bool tagrulematch_8(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   const char * s;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_STRING))return false;
   s = dostrdup((l__t -> t_value));
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_qstring = true;
   oper->val_qstring = s;
   return true;
}
static bool tagrulematch_9(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   struct expr * x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__x = parserange(lineno, toks, 0U,(l__num - 0U), true);
   if ((l__x == NULL))return false;
   l__x = fold_constant_arithmetic(l__x, true);
   x = l__x;
   if (!is_constant(x))return false;
   oper->is_number = true;
   u_machlarge tmp;
   assert(((x -> x_type)== EXPR_NUM));
   tmp =((x -> x_u). u_num);
   (x -> x_u).u_num = 0;
   expr_destroy(x);
   oper->val_number = tmp;
   return true;
}
static bool tagrulematch_10(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   struct expr * x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__x = parserange(lineno, toks, 0U,(l__num - 0U), true);
   if ((l__x == NULL))return false;
   l__x = fold_constant_arithmetic(l__x, true);
   x = l__x;
   if (!true)return false;
   oper->is_expr = true;
   oper->val_expr = x;
   return true;
}
static bool tagrulematch_11(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   struct expr * x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_IDENT))return false;
   l__x = parserange(lineno, toks, 0U, 1U, true);
   if ((l__x == NULL))return false;
   l__x = fold_constant_arithmetic(l__x, true);
   x = l__x;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_symbol = true;
   oper->val_symbol = x;
   return true;
}
static bool tagrulematch_12(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   struct expr * x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__x = parserange(lineno, toks, 0U,(l__num - 0U), true);
   if ((l__x == NULL))return false;
   l__x = fold_constant_arithmetic(l__x, true);
   x = l__x;
   if (!true)return false;
   oper->is_s16expr = true;
   oper->val_s16expr = x;
   return true;
}
static bool tagrulematch_13(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   struct expr * x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__x = parserange(lineno, toks, 0U,(l__num - 0U), true);
   if ((l__x == NULL))return false;
   l__x = fold_constant_arithmetic(l__x, true);
   x = l__x;
   if (!true)return false;
   oper->is_u16expr = true;
   oper->val_u16expr = x;
   return true;
}
static bool tagrulematch_14(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   struct expr * x;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 4U))return false;
   l__x = parserange(lineno, toks, 0U,(l__num - 3U), true);
   if ((l__x == NULL))return false;
   l__x = fold_constant_arithmetic(l__x, true);
   x = l__x;
   l__t = tokenarray_get(toks,((l__num - 3U)+ 0U));
   if (!((l__t -> t_type)== TOK_LPAREN))return false;
   l__t = tokenarray_get(toks,((l__num - 3U)+ 1U));
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_GENERALREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks,((l__num - 3U)+ 2U));
   if (!((l__t -> t_type)== TOK_RPAREN))return false;
   if (!true)return false;
   oper->is_mem = true;
   (oper -> val_mem).m0 = x;
   (oper -> val_mem).m1 = r;
   return true;
}
static bool tagrulematch_15(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   const char * s;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 2U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_AT))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_IDENT))return false;
   s = dostrdup((l__t -> t_value));
   if (!(l__num == 2U))return false;
   if (!true)return false;
   oper->is_symboltype = true;
   oper->val_symboltype = s;
   return true;
}
static bool tagrulematch_16(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   const char * s;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 2U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_AT))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_IDENT))return false;
   s = dostrdup((l__t -> t_value));
   if (!(l__num == 2U))return false;
   if (!true)return false;
   oper->is_sectiontype = true;
   oper->val_sectiontype = s;
   return true;
}
static bool tagrulematch_17(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 9U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_AT))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_AT))return false;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_AT))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!((l__t -> t_type)== TOK_AT))return false;
   l__t = tokenarray_get(toks, 4U);
   if (!((l__t -> t_type)== TOK_AT))return false;
   l__t = tokenarray_get(toks, 5U);
   if (!((l__t -> t_type)== TOK_HASH))return false;
   l__t = tokenarray_get(toks, 6U);
   if (!((l__t -> t_type)== TOK_HASH))return false;
   l__t = tokenarray_get(toks, 7U);
   if (!((l__t -> t_type)== TOK_HASH))return false;
   l__t = tokenarray_get(toks, 8U);
   if (!((l__t -> t_type)== TOK_HASH))return false;
   if (!(l__num == 9U))return false;
   if (!true)return false;
   oper->is_rtag = true;
   oper->val_rtag = 0U /* z0 */;
   return true;
}
static void opermatch_c0reg(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_1(lineno, oper, toks))return;
}

static void opermatch_c2reg(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_2(lineno, oper, toks))return;
}

static void opermatch_c3reg(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_3(lineno, oper, toks))return;
}

static void opermatch_cc(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_5(lineno, oper, toks))return;
}

static void opermatch_expr(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_10(lineno, oper, toks))return;
}

static void opermatch_freg(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_4(lineno, oper, toks))return;
}

static void opermatch_magiczero(int lineno, struct operand * oper, struct tokenarray * toks) {
   (void)lineno;
   (void)oper;
   (void)toks;
}

static void opermatch_mem(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_14(lineno, oper, toks))return;
}

static void opermatch_number(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_7(lineno, oper, toks))return;
   if (tagrulematch_9(lineno, oper, toks))return;
}

static void opermatch_qstring(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_8(lineno, oper, toks))return;
}

static void opermatch_reg(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_0(lineno, oper, toks))return;
}

static void opermatch_rtag(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_17(lineno, oper, toks))return;
}

static void opermatch_s16expr(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_12(lineno, oper, toks))return;
}

static void opermatch_sectiontype(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_16(lineno, oper, toks))return;
}

static void opermatch_sel(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_6(lineno, oper, toks))return;
}

static void opermatch_symbol(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_11(lineno, oper, toks))return;
}

static void opermatch_symboltype(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_15(lineno, oper, toks))return;
}

static void opermatch_u16expr(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_13(lineno, oper, toks))return;
}

void operand_init(struct operand * oper) {
   oper->is_c0reg = false;
   oper->val_c0reg = 0U;
   oper->is_c2reg = false;
   oper->val_c2reg = 0U;
   oper->is_c3reg = false;
   oper->val_c3reg = 0U;
   oper->is_cc = false;
   oper->val_cc = 0U;
   oper->is_expr = false;
   oper->val_expr = NULL;
   oper->is_freg = false;
   oper->val_freg = 0U;
   oper->is_magiczero = false;
   oper->val_magiczero = 0U;
   oper->is_mem = false;
   (oper -> val_mem).m0 = NULL;
   (oper -> val_mem).m1 = 0U;
   oper->is_number = false;
   oper->val_number = 0U;
   oper->is_qstring = false;
   oper->val_qstring = NULL;
   oper->is_reg = false;
   oper->val_reg = 0U;
   oper->is_rtag = false;
   oper->val_rtag = 0U;
   oper->is_s16expr = false;
   oper->val_s16expr = NULL;
   oper->is_sectiontype = false;
   oper->val_sectiontype = NULL;
   oper->is_sel = false;
   oper->val_sel = 0U;
   oper->is_symbol = false;
   oper->val_symbol = NULL;
   oper->is_symboltype = false;
   oper->val_symboltype = NULL;
   oper->is_u16expr = false;
   oper->val_u16expr = NULL;
}
void operand_cleanup(struct operand * oper) {
   (void)oper;
   expr_destroy((oper -> val_expr));
   expr_destroy(((oper -> val_mem). m0));
   expr_destroy((oper -> val_s16expr));
   expr_destroy((oper -> val_symbol));
   expr_destroy((oper -> val_u16expr));
}
void operand_match(int lineno, struct operand * oper, struct tokenarray * toks) {
   opermatch_c0reg(lineno, oper, toks);
   opermatch_c2reg(lineno, oper, toks);
   opermatch_c3reg(lineno, oper, toks);
   opermatch_cc(lineno, oper, toks);
   opermatch_expr(lineno, oper, toks);
   opermatch_freg(lineno, oper, toks);
   opermatch_magiczero(lineno, oper, toks);
   opermatch_mem(lineno, oper, toks);
   opermatch_number(lineno, oper, toks);
   opermatch_qstring(lineno, oper, toks);
   opermatch_reg(lineno, oper, toks);
   opermatch_rtag(lineno, oper, toks);
   opermatch_s16expr(lineno, oper, toks);
   opermatch_sectiontype(lineno, oper, toks);
   opermatch_sel(lineno, oper, toks);
   opermatch_symbol(lineno, oper, toks);
   opermatch_symboltype(lineno, oper, toks);
   opermatch_u16expr(lineno, oper, toks);
}
