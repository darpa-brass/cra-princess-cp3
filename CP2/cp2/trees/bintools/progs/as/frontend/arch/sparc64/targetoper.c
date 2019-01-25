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
static bool tagrulematch_1(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!((l__t -> t_type)== TOK_HASH))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_IDENT))return false;
   s = dostrdup((l__t -> t_value));
   if (!(l__num == 2U))return false;
   if (!true)return false;
   oper->is_symboltype = true;
   oper->val_symboltype = s;
   return true;
}
static bool tagrulematch_2(int lineno, struct operand * oper, struct tokenarray * toks) {
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
static bool tagrulematch_3(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 2U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_HASH))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_IDENT))return false;
   if (!!strcmp((l__t -> t_value), "scratch"))return false;
   if (!(l__num == 2U))return false;
   if (!true)return false;
   oper->is_registertag = true;
   oper->val_registertag = 0U /* RTAG_SCRATCH */;
   return true;
}
static bool tagrulematch_4(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 2U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_HASH))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_IDENT))return false;
   if (!!strcmp((l__t -> t_value), "ignore"))return false;
   if (!(l__num == 2U))return false;
   if (!true)return false;
   oper->is_registertag = true;
   oper->val_registertag = 1U /* RTAG_IGNORE */;
   return true;
}
static bool tagrulematch_5(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!!(511ULL < x))return false;
   oper->is_i10num = true;
   oper->val_i10num =(int16_t)(int64_t)x;
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
   if ((l__num < 2U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 2U))return false;
   if (!((x == 0ULL)|| !(511ULL <(x - 1ULL))))return false;
   oper->is_i10num = true;
   oper->val_i10num =(int16_t)(int64_t)-x;
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
   if (!!(1023ULL < x))return false;
   oper->is_i11num = true;
   oper->val_i11num =(int16_t)(int64_t)x;
   return true;
}
static bool tagrulematch_8(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 2U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 2U))return false;
   if (!((x == 0ULL)|| !(1023ULL <(x - 1ULL))))return false;
   oper->is_i11num = true;
   oper->val_i11num =(int16_t)(int64_t)-x;
   return true;
}
static bool tagrulematch_9(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!!(4095ULL < x))return false;
   oper->is_i13num = true;
   oper->val_i13num =(int16_t)(int64_t)x;
   return true;
}
static bool tagrulematch_10(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 2U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 2U))return false;
   if (!((x == 0ULL)|| !(4095ULL <(x - 1ULL))))return false;
   oper->is_i13num = true;
   oper->val_i13num =(int16_t)(int64_t)-x;
   return true;
}
static bool tagrulematch_11(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!!(2147483647ULL < x))return false;
   oper->is_i32num = true;
   oper->val_i32num =(int32_t)(int64_t)x;
   return true;
}
static bool tagrulematch_12(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 2U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 2U))return false;
   if (!((x == 0ULL)|| !(2147483647ULL <(x - 1ULL))))return false;
   oper->is_i32num = true;
   oper->val_i32num =(int32_t)(int64_t)-x;
   return true;
}
static bool tagrulematch_13(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   oper->is_i64num = true;
   oper->val_i64num =(int64_t)x;
   return true;
}
static bool tagrulematch_14(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 2U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 2U))return false;
   if (!true)return false;
   oper->is_i64num = true;
   oper->val_i64num =(int64_t)-x;
   return true;
}
static bool tagrulematch_15(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!!(31ULL < x))return false;
   oper->is_u5num = true;
   oper->val_u5num =(uint8_t)x;
   return true;
}
static bool tagrulematch_16(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!!(63ULL < x))return false;
   oper->is_u6num = true;
   oper->val_u6num =(uint8_t)x;
   return true;
}
static bool tagrulematch_17(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!!(524287ULL < x))return false;
   oper->is_u19num = true;
   oper->val_u19num =(uint32_t)x;
   return true;
}
static bool tagrulematch_18(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!!(4194303ULL < x))return false;
   oper->is_u22num = true;
   oper->val_u22num =(uint32_t)x;
   return true;
}
static bool tagrulematch_19(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!!(4294967295ULL < x))return false;
   oper->is_u32num = true;
   oper->val_u32num =(uint32_t)x;
   return true;
}
static bool tagrulematch_20(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!!(4294967295ULL < x))return false;
   oper->is_number = true;
   oper->val_number =(uint32_t)x;
   return true;
}
static bool tagrulematch_21(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!!(127ULL < x))return false;
   oper->is_membarmask = true;
   oper->val_membarmask =(uint8_t)x;
   return true;
}
static bool tagrulematch_22(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_reg = true;
   oper->val_reg = r;
   return true;
}
static bool tagrulematch_23(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t cc;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_ICC)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   cc = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_icc = true;
   oper->val_icc = cc;
   return true;
}
static bool tagrulematch_24(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t f;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_FREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   f = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_freg = true;
   oper->val_freg = f;
   return true;
}
static bool tagrulematch_25(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t cc;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_FCC)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   cc = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_fcc = true;
   oper->val_fcc = cc;
   return true;
}
static bool tagrulematch_26(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t n;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_FSR)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   n = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_fsr = true;
   oper->val_fsr = n;
   return true;
}
static bool tagrulematch_27(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_ASR)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_asr = true;
   oper->val_asr = r;
   return true;
}
static bool tagrulematch_28(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_PR)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_pr = true;
   oper->val_pr = r;
   return true;
}
static bool tagrulematch_29(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_addr_rr = true;
   (oper -> val_addr_rr).m0 = r;
   (oper -> val_addr_rr).m1 = 0U /* r0 */;
   return true;
}
static bool tagrulematch_30(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t ra;
   uint8_t rb;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   ra = l__ul;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks, 2U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   rb = l__ul;
   if (!(l__num == 3U))return false;
   if (!true)return false;
   oper->is_addr_rr = true;
   (oper -> val_addr_rr).m0 = ra;
   (oper -> val_addr_rr).m1 = rb;
   return true;
}
static bool tagrulematch_31(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   uint64_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 3U))return false;
   if (!!(4095ULL < x))return false;
   oper->is_addr_ri = true;
   (oper -> val_addr_ri).m0 = r;
   (oper -> val_addr_ri).m1 =(int16_t)(int64_t)x;
   return true;
}
static bool tagrulematch_32(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint64_t x;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks, 2U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   if (!(l__num == 3U))return false;
   if (!!(4095ULL < x))return false;
   oper->is_addr_ri = true;
   (oper -> val_addr_ri).m0 = r;
   (oper -> val_addr_ri).m1 =(int16_t)(int64_t)x;
   return true;
}
static bool tagrulematch_33(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   uint64_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 3U))return false;
   if (!((x == 0ULL)|| !(4095ULL <(x - 1ULL))))return false;
   oper->is_addr_ri = true;
   (oper -> val_addr_ri).m0 = r;
   (oper -> val_addr_ri).m1 =(int16_t)(int64_t)-x;
   return true;
}
static bool tagrulematch_34(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!!(4095ULL < x))return false;
   oper->is_addr_ri = true;
   (oper -> val_addr_ri).m0 = 0U /* r0 */;
   (oper -> val_addr_ri).m1 =(int16_t)(int64_t)x;
   return true;
}
static bool tagrulematch_35(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 2U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 2U))return false;
   if (!((x == 0ULL)|| !(4095ULL <(x - 1ULL))))return false;
   oper->is_addr_ri = true;
   (oper -> val_addr_ri).m0 = 0U /* r0 */;
   (oper -> val_addr_ri).m1 =(int16_t)(int64_t)-x;
   return true;
}
static bool tagrulematch_36(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   struct expr * x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__x = parserange(lineno, toks, 2U,(l__num - 0U), true);
   if ((l__x == NULL))return false;
   l__x = fold_constant_arithmetic(l__x, true);
   x = l__x;
   if (!true)return false;
   oper->is_addr_rx = true;
   (oper -> val_addr_rx).m0 = r;
   (oper -> val_addr_rx).m1 = x;
   return true;
}
static bool tagrulematch_37(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 3U))return false;
   l__x = parserange(lineno, toks, 0U,(l__num - 2U), true);
   if ((l__x == NULL))return false;
   l__x = fold_constant_arithmetic(l__x, true);
   x = l__x;
   l__t = tokenarray_get(toks,((l__num - 2U)+ 0U));
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks,((l__num - 2U)+ 1U));
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   if (!true)return false;
   oper->is_addr_rx = true;
   (oper -> val_addr_rx).m0 = r;
   (oper -> val_addr_rx).m1 = x;
   return true;
}
static bool tagrulematch_38(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   oper->is_addr_rx = true;
   (oper -> val_addr_rx).m0 = 0U /* r0 */;
   (oper -> val_addr_rx).m1 = x;
   return true;
}
static bool tagrulematch_39(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   if (!(l__num == 3U))return false;
   if (!true)return false;
   oper->is_braddr_rr = true;
   (oper -> val_braddr_rr).m0 = r;
   (oper -> val_braddr_rr).m1 = 0U /* r0 */;
   return true;
}
static bool tagrulematch_40(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t ra;
   uint8_t rb;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 5U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   ra = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   rb = l__ul;
   l__t = tokenarray_get(toks, 4U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   if (!(l__num == 5U))return false;
   if (!true)return false;
   oper->is_braddr_rr = true;
   (oper -> val_braddr_rr).m0 = ra;
   (oper -> val_braddr_rr).m1 = rb;
   return true;
}
static bool tagrulematch_41(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   uint64_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 5U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   l__t = tokenarray_get(toks, 4U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   if (!(l__num == 5U))return false;
   if (!!(4095ULL < x))return false;
   oper->is_braddr_ri = true;
   (oper -> val_braddr_ri).m0 = r;
   (oper -> val_braddr_ri).m1 =(int16_t)(int64_t)x;
   return true;
}
static bool tagrulematch_42(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint64_t x;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 5U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 4U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   if (!(l__num == 5U))return false;
   if (!!(4095ULL < x))return false;
   oper->is_braddr_ri = true;
   (oper -> val_braddr_ri).m0 = r;
   (oper -> val_braddr_ri).m1 =(int16_t)(int64_t)x;
   return true;
}
static bool tagrulematch_43(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   uint64_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 5U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   l__t = tokenarray_get(toks, 4U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   if (!(l__num == 5U))return false;
   if (!((x == 0ULL)|| !(4095ULL <(x - 1ULL))))return false;
   oper->is_braddr_ri = true;
   (oper -> val_braddr_ri).m0 = r;
   (oper -> val_braddr_ri).m1 =(int16_t)(int64_t)-x;
   return true;
}
static bool tagrulematch_44(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   if (!(l__num == 3U))return false;
   if (!!(4095ULL < x))return false;
   oper->is_braddr_ri = true;
   (oper -> val_braddr_ri).m0 = 0U /* r0 */;
   (oper -> val_braddr_ri).m1 =(int16_t)(int64_t)x;
   return true;
}
static bool tagrulematch_45(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 4U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   l__t = tokenarray_get(toks, 3U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   if (!(l__num == 4U))return false;
   if (!((x == 0ULL)|| !(4095ULL <(x - 1ULL))))return false;
   oper->is_braddr_ri = true;
   (oper -> val_braddr_ri).m0 = 0U /* r0 */;
   (oper -> val_braddr_ri).m1 =(int16_t)(int64_t)-x;
   return true;
}
static bool tagrulematch_46(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   struct expr * x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 5U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__x = parserange(lineno, toks, 3U,(l__num - 1U), true);
   if ((l__x == NULL))return false;
   l__x = fold_constant_arithmetic(l__x, true);
   x = l__x;
   l__t = tokenarray_get(toks,((l__num - 1U)+ 0U));
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   if (!true)return false;
   oper->is_braddr_rx = true;
   (oper -> val_braddr_rx).m0 = r;
   (oper -> val_braddr_rx).m1 = x;
   return true;
}
static bool tagrulematch_47(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 5U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__x = parserange(lineno, toks, 1U,(l__num - 3U), true);
   if ((l__x == NULL))return false;
   l__x = fold_constant_arithmetic(l__x, true);
   x = l__x;
   l__t = tokenarray_get(toks,((l__num - 3U)+ 0U));
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks,((l__num - 3U)+ 1U));
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks,((l__num - 3U)+ 2U));
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   if (!true)return false;
   oper->is_braddr_rx = true;
   (oper -> val_braddr_rx).m0 = r;
   (oper -> val_braddr_rx).m1 = x;
   return true;
}
static bool tagrulematch_48(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__x = parserange(lineno, toks, 1U,(l__num - 1U), true);
   if ((l__x == NULL))return false;
   l__x = fold_constant_arithmetic(l__x, true);
   x = l__x;
   l__t = tokenarray_get(toks,((l__num - 1U)+ 0U));
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   if (!true)return false;
   oper->is_braddr_rx = true;
   (oper -> val_braddr_rx).m0 = 0U /* r0 */;
   (oper -> val_braddr_rx).m1 = x;
   return true;
}
static bool tagrulematch_49(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   uint64_t asi;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 4U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   asi = l__ul;
   if (!(l__num == 4U))return false;
   if (!!(255ULL < asi))return false;
   oper->is_braddr_rr_immasi = true;
   (oper -> val_braddr_rr_immasi).m0 = r;
   (oper -> val_braddr_rr_immasi).m1 = 0U /* r0 */;
   (oper -> val_braddr_rr_immasi).m2 =(uint8_t)asi;
   return true;
}
static bool tagrulematch_50(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t ra;
   uint8_t rb;
   uint64_t asi;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 6U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   ra = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   rb = l__ul;
   l__t = tokenarray_get(toks, 4U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   l__t = tokenarray_get(toks, 5U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   asi = l__ul;
   if (!(l__num == 6U))return false;
   if (!true)return false;
   oper->is_braddr_rr_immasi = true;
   (oper -> val_braddr_rr_immasi).m0 = ra;
   (oper -> val_braddr_rr_immasi).m1 = rb;
   (oper -> val_braddr_rr_immasi).m2 =(uint8_t)asi;
   return true;
}
static bool tagrulematch_51(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   uint64_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 6U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   l__t = tokenarray_get(toks, 4U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   l__t = tokenarray_get(toks, 5U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_ASIREG)))return false;
   if (!(l__num == 6U))return false;
   if (!!(4095ULL < x))return false;
   oper->is_braddr_ri_asi = true;
   (oper -> val_braddr_ri_asi).m0 = r;
   (oper -> val_braddr_ri_asi).m1 =(int16_t)(int64_t)x;
   return true;
}
static bool tagrulematch_52(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint64_t x;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 6U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 4U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   l__t = tokenarray_get(toks, 5U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_ASIREG)))return false;
   if (!(l__num == 6U))return false;
   if (!!(4095ULL < x))return false;
   oper->is_braddr_ri_asi = true;
   (oper -> val_braddr_ri_asi).m0 = r;
   (oper -> val_braddr_ri_asi).m1 =(int16_t)(int64_t)x;
   return true;
}
static bool tagrulematch_53(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   uint64_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 6U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   l__t = tokenarray_get(toks, 4U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   l__t = tokenarray_get(toks, 5U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_ASIREG)))return false;
   if (!(l__num == 6U))return false;
   if (!((x == 0ULL)|| !(4095ULL <(x - 1ULL))))return false;
   oper->is_braddr_ri_asi = true;
   (oper -> val_braddr_ri_asi).m0 = r;
   (oper -> val_braddr_ri_asi).m1 =(int16_t)(int64_t)-x;
   return true;
}
static bool tagrulematch_54(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 4U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_ASIREG)))return false;
   if (!(l__num == 4U))return false;
   if (!!(4095ULL < x))return false;
   oper->is_braddr_ri_asi = true;
   (oper -> val_braddr_ri_asi).m0 = 0U /* r0 */;
   (oper -> val_braddr_ri_asi).m1 =(int16_t)(int64_t)x;
   return true;
}
static bool tagrulematch_55(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 5U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   l__t = tokenarray_get(toks, 3U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   l__t = tokenarray_get(toks, 4U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_ASIREG)))return false;
   if (!(l__num == 5U))return false;
   if (!((x == 0ULL)|| !(4095ULL <(x - 1ULL))))return false;
   oper->is_braddr_ri_asi = true;
   (oper -> val_braddr_ri_asi).m0 = 0U /* r0 */;
   (oper -> val_braddr_ri_asi).m1 =(int16_t)(int64_t)-x;
   return true;
}
static bool tagrulematch_56(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   uint64_t asi;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 4U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   asi = l__ul;
   if (!(l__num == 4U))return false;
   if (!!(255ULL < asi))return false;
   oper->is_braddr_r_immasi = true;
   (oper -> val_braddr_r_immasi).m0 = r;
   (oper -> val_braddr_r_immasi).m1 =(uint8_t)asi;
   return true;
}
static bool tagrulematch_57(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 4U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   l__t = tokenarray_get(toks, 3U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_ASIREG)))return false;
   if (!(l__num == 4U))return false;
   if (!true)return false;
   oper->is_braddr_r_asi = true;
   (oper -> val_braddr_r_asi).m0 = r;
   return true;
}
static bool tagrulematch_58(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_LBRACK))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_RBRACK))return false;
   if (!(l__num == 3U))return false;
   if (!true)return false;
   oper->is_braddr_r = true;
   oper->val_braddr_r = r;
   return true;
}
static bool tagrulematch_59(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 1U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   if (!(l__num == 1U))return false;
   if (!true)return false;
   oper->is_trapnum_rr = true;
   (oper -> val_trapnum_rr).m0 = r;
   (oper -> val_trapnum_rr).m1 = 0U /* r0 */;
   return true;
}
static bool tagrulematch_60(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t ra;
   uint8_t rb;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   ra = l__ul;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks, 2U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   rb = l__ul;
   if (!(l__num == 3U))return false;
   if (!true)return false;
   oper->is_trapnum_rr = true;
   (oper -> val_trapnum_rr).m0 = ra;
   (oper -> val_trapnum_rr).m1 = rb;
   return true;
}
static bool tagrulematch_61(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   uint64_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 3U))return false;
   if (!!(63ULL < x))return false;
   oper->is_trapnum_ri = true;
   (oper -> val_trapnum_ri).m0 = r;
   (oper -> val_trapnum_ri).m1 =(int8_t)(int64_t)x;
   return true;
}
static bool tagrulematch_62(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint64_t x;
   uint8_t r;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_PLUS))return false;
   l__t = tokenarray_get(toks, 2U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   if (!(l__num == 3U))return false;
   if (!!(63ULL < x))return false;
   oper->is_trapnum_ri = true;
   (oper -> val_trapnum_ri).m0 = r;
   (oper -> val_trapnum_ri).m1 =(int8_t)(int64_t)x;
   return true;
}
static bool tagrulematch_63(int lineno, struct operand * oper, struct tokenarray * toks) {
   unsigned int l__num;
   struct token * l__t;
   struct expr * l__x;
   unsigned long l__ul;
   char * l__end;
   uint8_t r;
   uint64_t x;
   
   (void)lineno;
   (void)l__t;
   (void)l__x;
   (void)l__ul;
   (void)l__end;
   l__num = tokenarray_num(toks);
   if ((l__num < 3U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!(((l__t -> t_type)== TOK_TARGET)&&((l__t -> t_ttype)== TTOK_REGCLASS_RREG)))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   r = l__ul;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 2U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 3U))return false;
   if (!((x == 0ULL)|| !(63ULL <(x - 1ULL))))return false;
   oper->is_trapnum_ri = true;
   (oper -> val_trapnum_ri).m0 = r;
   (oper -> val_trapnum_ri).m1 =(int8_t)(int64_t)-x;
   return true;
}
static bool tagrulematch_64(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if (!!(63ULL < x))return false;
   oper->is_trapnum_ri = true;
   (oper -> val_trapnum_ri).m0 = 0U /* r0 */;
   (oper -> val_trapnum_ri).m1 =(int8_t)(int64_t)x;
   return true;
}
static bool tagrulematch_65(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   if ((l__num < 2U))return false;
   l__t = tokenarray_get(toks, 0U);
   if (!((l__t -> t_type)== TOK_MINUS))return false;
   l__t = tokenarray_get(toks, 1U);
   if (!((l__t -> t_type)== TOK_NUMBER))return false;
   errno = 0;
   l__ul = strtoul((l__t -> t_value), &l__end, 0);
   if ((!(errno == 0)|| !(strlen(l__end)== 0)))return false;
   x = l__ul;
   if (!(l__num == 2U))return false;
   if (!((x == 0ULL)|| !(63ULL <(x - 1ULL))))return false;
   oper->is_trapnum_ri = true;
   (oper -> val_trapnum_ri).m0 = 0U /* r0 */;
   (oper -> val_trapnum_ri).m1 =(int8_t)(int64_t)-x;
   return true;
}
static bool tagrulematch_66(int lineno, struct operand * oper, struct tokenarray * toks) {
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
   oper->val_number =(uint32_t)tmp;
   return true;
}
static bool tagrulematch_67(int lineno, struct operand * oper, struct tokenarray * toks) {
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
static bool tagrulematch_68(int lineno, struct operand * oper, struct tokenarray * toks) {
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
static void opermatch_addr_ri(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_31(lineno, oper, toks))return;
   if (tagrulematch_32(lineno, oper, toks))return;
   if (tagrulematch_33(lineno, oper, toks))return;
   if (tagrulematch_34(lineno, oper, toks))return;
   if (tagrulematch_35(lineno, oper, toks))return;
}

static void opermatch_addr_rr(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_29(lineno, oper, toks))return;
   if (tagrulematch_30(lineno, oper, toks))return;
}

static void opermatch_addr_rx(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_36(lineno, oper, toks))return;
   if (tagrulematch_37(lineno, oper, toks))return;
   if (tagrulematch_38(lineno, oper, toks))return;
}

static void opermatch_asr(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_27(lineno, oper, toks))return;
}

static void opermatch_braddr_r(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_58(lineno, oper, toks))return;
}

static void opermatch_braddr_r_asi(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_57(lineno, oper, toks))return;
}

static void opermatch_braddr_r_immasi(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_56(lineno, oper, toks))return;
}

static void opermatch_braddr_ri(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_41(lineno, oper, toks))return;
   if (tagrulematch_42(lineno, oper, toks))return;
   if (tagrulematch_43(lineno, oper, toks))return;
   if (tagrulematch_44(lineno, oper, toks))return;
   if (tagrulematch_45(lineno, oper, toks))return;
}

static void opermatch_braddr_ri_asi(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_51(lineno, oper, toks))return;
   if (tagrulematch_52(lineno, oper, toks))return;
   if (tagrulematch_53(lineno, oper, toks))return;
   if (tagrulematch_54(lineno, oper, toks))return;
   if (tagrulematch_55(lineno, oper, toks))return;
}

static void opermatch_braddr_rr(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_39(lineno, oper, toks))return;
   if (tagrulematch_40(lineno, oper, toks))return;
}

static void opermatch_braddr_rr_immasi(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_49(lineno, oper, toks))return;
   if (tagrulematch_50(lineno, oper, toks))return;
}

static void opermatch_braddr_rx(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_46(lineno, oper, toks))return;
   if (tagrulematch_47(lineno, oper, toks))return;
   if (tagrulematch_48(lineno, oper, toks))return;
}

static void opermatch_expr(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_67(lineno, oper, toks))return;
}

static void opermatch_fcc(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_25(lineno, oper, toks))return;
}

static void opermatch_freg(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_24(lineno, oper, toks))return;
}

static void opermatch_fsr(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_26(lineno, oper, toks))return;
}

static void opermatch_i10num(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_5(lineno, oper, toks))return;
   if (tagrulematch_6(lineno, oper, toks))return;
}

static void opermatch_i11num(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_7(lineno, oper, toks))return;
   if (tagrulematch_8(lineno, oper, toks))return;
}

static void opermatch_i13num(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_9(lineno, oper, toks))return;
   if (tagrulematch_10(lineno, oper, toks))return;
}

static void opermatch_i32num(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_11(lineno, oper, toks))return;
   if (tagrulematch_12(lineno, oper, toks))return;
}

static void opermatch_i64num(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_13(lineno, oper, toks))return;
   if (tagrulematch_14(lineno, oper, toks))return;
}

static void opermatch_icc(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_23(lineno, oper, toks))return;
}

static void opermatch_magiczero(int lineno, struct operand * oper, struct tokenarray * toks) {
   (void)lineno;
   (void)oper;
   (void)toks;
}

static void opermatch_membarmask(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_21(lineno, oper, toks))return;
}

static void opermatch_number(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_20(lineno, oper, toks))return;
   if (tagrulematch_66(lineno, oper, toks))return;
}

static void opermatch_pr(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_28(lineno, oper, toks))return;
}

static void opermatch_qstring(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_0(lineno, oper, toks))return;
}

static void opermatch_reg(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_22(lineno, oper, toks))return;
}

static void opermatch_registertag(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_3(lineno, oper, toks))return;
   if (tagrulematch_4(lineno, oper, toks))return;
}

static void opermatch_sectiontype(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_2(lineno, oper, toks))return;
}

static void opermatch_symbol(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_68(lineno, oper, toks))return;
}

static void opermatch_symboltype(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_1(lineno, oper, toks))return;
}

static void opermatch_trapnum_ri(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_61(lineno, oper, toks))return;
   if (tagrulematch_62(lineno, oper, toks))return;
   if (tagrulematch_63(lineno, oper, toks))return;
   if (tagrulematch_64(lineno, oper, toks))return;
   if (tagrulematch_65(lineno, oper, toks))return;
}

static void opermatch_trapnum_rr(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_59(lineno, oper, toks))return;
   if (tagrulematch_60(lineno, oper, toks))return;
}

static void opermatch_u19num(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_17(lineno, oper, toks))return;
}

static void opermatch_u22num(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_18(lineno, oper, toks))return;
}

static void opermatch_u32num(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_19(lineno, oper, toks))return;
}

static void opermatch_u5num(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_15(lineno, oper, toks))return;
}

static void opermatch_u6num(int lineno, struct operand * oper, struct tokenarray * toks) {
   if (tagrulematch_16(lineno, oper, toks))return;
}

void operand_init(struct operand * oper) {
   oper->is_addr_ri = false;
   (oper -> val_addr_ri).m0 = 0U;
   (oper -> val_addr_ri).m1 = 0;
   oper->is_addr_rr = false;
   (oper -> val_addr_rr).m0 = 0U;
   (oper -> val_addr_rr).m1 = 0U;
   oper->is_addr_rx = false;
   (oper -> val_addr_rx).m0 = 0U;
   (oper -> val_addr_rx).m1 = NULL;
   oper->is_asr = false;
   oper->val_asr = 0U;
   oper->is_braddr_r = false;
   oper->val_braddr_r = 0U;
   oper->is_braddr_r_asi = false;
   (oper -> val_braddr_r_asi).m0 = 0U;
   oper->is_braddr_r_immasi = false;
   (oper -> val_braddr_r_immasi).m0 = 0U;
   (oper -> val_braddr_r_immasi).m1 = 0U;
   oper->is_braddr_ri = false;
   (oper -> val_braddr_ri).m0 = 0U;
   (oper -> val_braddr_ri).m1 = 0;
   oper->is_braddr_ri_asi = false;
   (oper -> val_braddr_ri_asi).m0 = 0U;
   (oper -> val_braddr_ri_asi).m1 = 0;
   oper->is_braddr_rr = false;
   (oper -> val_braddr_rr).m0 = 0U;
   (oper -> val_braddr_rr).m1 = 0U;
   oper->is_braddr_rr_immasi = false;
   (oper -> val_braddr_rr_immasi).m0 = 0U;
   (oper -> val_braddr_rr_immasi).m1 = 0U;
   (oper -> val_braddr_rr_immasi).m2 = 0U;
   oper->is_braddr_rx = false;
   (oper -> val_braddr_rx).m0 = 0U;
   (oper -> val_braddr_rx).m1 = NULL;
   oper->is_expr = false;
   oper->val_expr = NULL;
   oper->is_fcc = false;
   oper->val_fcc = 0U;
   oper->is_freg = false;
   oper->val_freg = 0U;
   oper->is_fsr = false;
   oper->val_fsr = 0U;
   oper->is_i10num = false;
   oper->val_i10num = 0;
   oper->is_i11num = false;
   oper->val_i11num = 0;
   oper->is_i13num = false;
   oper->val_i13num = 0;
   oper->is_i32num = false;
   oper->val_i32num = 0;
   oper->is_i64num = false;
   oper->val_i64num = 0;
   oper->is_icc = false;
   oper->val_icc = 0U;
   oper->is_magiczero = false;
   oper->val_magiczero = 0U;
   oper->is_membarmask = false;
   oper->val_membarmask = 0U;
   oper->is_number = false;
   oper->val_number = 0U;
   oper->is_pr = false;
   oper->val_pr = 0U;
   oper->is_qstring = false;
   oper->val_qstring = NULL;
   oper->is_reg = false;
   oper->val_reg = 0U;
   oper->is_registertag = false;
   oper->val_registertag = 0U;
   oper->is_sectiontype = false;
   oper->val_sectiontype = NULL;
   oper->is_symbol = false;
   oper->val_symbol = NULL;
   oper->is_symboltype = false;
   oper->val_symboltype = NULL;
   oper->is_trapnum_ri = false;
   (oper -> val_trapnum_ri).m0 = 0U;
   (oper -> val_trapnum_ri).m1 = 0;
   oper->is_trapnum_rr = false;
   (oper -> val_trapnum_rr).m0 = 0U;
   (oper -> val_trapnum_rr).m1 = 0U;
   oper->is_u19num = false;
   oper->val_u19num = 0U;
   oper->is_u22num = false;
   oper->val_u22num = 0U;
   oper->is_u32num = false;
   oper->val_u32num = 0U;
   oper->is_u5num = false;
   oper->val_u5num = 0U;
   oper->is_u6num = false;
   oper->val_u6num = 0U;
}
void operand_cleanup(struct operand * oper) {
   (void)oper;
   expr_destroy(((oper -> val_addr_rx). m1));
   expr_destroy(((oper -> val_braddr_rx). m1));
   expr_destroy((oper -> val_expr));
   expr_destroy((oper -> val_symbol));
}
void operand_match(int lineno, struct operand * oper, struct tokenarray * toks) {
   opermatch_addr_ri(lineno, oper, toks);
   opermatch_addr_rr(lineno, oper, toks);
   opermatch_addr_rx(lineno, oper, toks);
   opermatch_asr(lineno, oper, toks);
   opermatch_braddr_r(lineno, oper, toks);
   opermatch_braddr_r_asi(lineno, oper, toks);
   opermatch_braddr_r_immasi(lineno, oper, toks);
   opermatch_braddr_ri(lineno, oper, toks);
   opermatch_braddr_ri_asi(lineno, oper, toks);
   opermatch_braddr_rr(lineno, oper, toks);
   opermatch_braddr_rr_immasi(lineno, oper, toks);
   opermatch_braddr_rx(lineno, oper, toks);
   opermatch_expr(lineno, oper, toks);
   opermatch_fcc(lineno, oper, toks);
   opermatch_freg(lineno, oper, toks);
   opermatch_fsr(lineno, oper, toks);
   opermatch_i10num(lineno, oper, toks);
   opermatch_i11num(lineno, oper, toks);
   opermatch_i13num(lineno, oper, toks);
   opermatch_i32num(lineno, oper, toks);
   opermatch_i64num(lineno, oper, toks);
   opermatch_icc(lineno, oper, toks);
   opermatch_magiczero(lineno, oper, toks);
   opermatch_membarmask(lineno, oper, toks);
   opermatch_number(lineno, oper, toks);
   opermatch_pr(lineno, oper, toks);
   opermatch_qstring(lineno, oper, toks);
   opermatch_reg(lineno, oper, toks);
   opermatch_registertag(lineno, oper, toks);
   opermatch_sectiontype(lineno, oper, toks);
   opermatch_symbol(lineno, oper, toks);
   opermatch_symboltype(lineno, oper, toks);
   opermatch_trapnum_ri(lineno, oper, toks);
   opermatch_trapnum_rr(lineno, oper, toks);
   opermatch_u19num(lineno, oper, toks);
   opermatch_u22num(lineno, oper, toks);
   opermatch_u32num(lineno, oper, toks);
   opermatch_u5num(lineno, oper, toks);
   opermatch_u6num(lineno, oper, toks);
}
