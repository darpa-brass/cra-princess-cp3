/* Automatically generated; do not edit */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "utils.h"
#include "token.h"

int is_letter(int ch) {
   switch(ch) {
   case 97: return 1;
   case 98: return 1;
   case 99: return 1;
   case 100: return 1;
   case 101: return 1;
   case 102: return 1;
   case 103: return 1;
   case 104: return 1;
   case 105: return 1;
   case 106: return 1;
   case 107: return 1;
   case 108: return 1;
   case 109: return 1;
   case 110: return 1;
   case 111: return 1;
   case 112: return 1;
   case 113: return 1;
   case 114: return 1;
   case 115: return 1;
   case 116: return 1;
   case 117: return 1;
   case 118: return 1;
   case 119: return 1;
   case 120: return 1;
   case 121: return 1;
   case 122: return 1;
   case 65: return 1;
   case 66: return 1;
   case 67: return 1;
   case 68: return 1;
   case 69: return 1;
   case 70: return 1;
   case 71: return 1;
   case 72: return 1;
   case 73: return 1;
   case 74: return 1;
   case 75: return 1;
   case 76: return 1;
   case 77: return 1;
   case 78: return 1;
   case 79: return 1;
   case 80: return 1;
   case 81: return 1;
   case 82: return 1;
   case 83: return 1;
   case 84: return 1;
   case 85: return 1;
   case 86: return 1;
   case 87: return 1;
   case 88: return 1;
   case 89: return 1;
   case 90: return 1;
   case 95: return 1;
   case 46: return 1;
   default:{
      break;
   }
   }
   return 0;
}
int is_subletter(int ch) {
   switch(ch) {
   case 97: return 1;
   case 98: return 1;
   case 99: return 1;
   case 100: return 1;
   case 101: return 1;
   case 102: return 1;
   case 103: return 1;
   case 104: return 1;
   case 105: return 1;
   case 106: return 1;
   case 107: return 1;
   case 108: return 1;
   case 109: return 1;
   case 110: return 1;
   case 111: return 1;
   case 112: return 1;
   case 113: return 1;
   case 114: return 1;
   case 115: return 1;
   case 116: return 1;
   case 117: return 1;
   case 118: return 1;
   case 119: return 1;
   case 120: return 1;
   case 121: return 1;
   case 122: return 1;
   case 65: return 1;
   case 66: return 1;
   case 67: return 1;
   case 68: return 1;
   case 69: return 1;
   case 70: return 1;
   case 71: return 1;
   case 72: return 1;
   case 73: return 1;
   case 74: return 1;
   case 75: return 1;
   case 76: return 1;
   case 77: return 1;
   case 78: return 1;
   case 79: return 1;
   case 80: return 1;
   case 81: return 1;
   case 82: return 1;
   case 83: return 1;
   case 84: return 1;
   case 85: return 1;
   case 86: return 1;
   case 87: return 1;
   case 88: return 1;
   case 89: return 1;
   case 90: return 1;
   case 95: return 1;
   case 46: return 1;
   default:{
      break;
   }
   }
   return 0;
}
static bool match_0(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_0;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_0 =(t -> t_value);
   (void)gen_0;
   
   ok = !strcmp(gen_0, "r0");
   return ok;
}
static bool match_1(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_1;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_1 =(t -> t_value);
   (void)gen_1;
   
   ok = !strcmp(gen_1, "r1");
   return ok;
}
static bool match_2(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_2;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_2 =(t -> t_value);
   (void)gen_2;
   
   ok = !strcmp(gen_2, "r2");
   return ok;
}
static bool match_3(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_3;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_3 =(t -> t_value);
   (void)gen_3;
   
   ok = !strcmp(gen_3, "r3");
   return ok;
}
static bool match_4(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_4;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_4 =(t -> t_value);
   (void)gen_4;
   
   ok = !strcmp(gen_4, "r4");
   return ok;
}
static bool match_5(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_5;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_5 =(t -> t_value);
   (void)gen_5;
   
   ok = !strcmp(gen_5, "r5");
   return ok;
}
static bool match_6(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_6;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_6 =(t -> t_value);
   (void)gen_6;
   
   ok = !strcmp(gen_6, "r6");
   return ok;
}
static bool match_7(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_7;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_7 =(t -> t_value);
   (void)gen_7;
   
   ok = !strcmp(gen_7, "r7");
   return ok;
}
static bool match_8(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_8;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_8 =(t -> t_value);
   (void)gen_8;
   
   ok = !strcmp(gen_8, "r8");
   return ok;
}
static bool match_9(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_9;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_9 =(t -> t_value);
   (void)gen_9;
   
   ok = !strcmp(gen_9, "r9");
   return ok;
}
static bool match_10(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_10;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_10 =(t -> t_value);
   (void)gen_10;
   
   ok = !strcmp(gen_10, "r10");
   return ok;
}
static bool match_11(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_11;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_11 =(t -> t_value);
   (void)gen_11;
   
   ok = !strcmp(gen_11, "r11");
   return ok;
}
static bool match_12(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_12;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_12 =(t -> t_value);
   (void)gen_12;
   
   ok = !strcmp(gen_12, "fp");
   return ok;
}
static bool match_13(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_13;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_13 =(t -> t_value);
   (void)gen_13;
   
   ok = !strcmp(gen_13, "r12");
   return ok;
}
static bool match_14(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_14;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_14 =(t -> t_value);
   (void)gen_14;
   
   ok = !strcmp(gen_14, "ip");
   return ok;
}
static bool match_15(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_15;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_15 =(t -> t_value);
   (void)gen_15;
   
   ok = !strcmp(gen_15, "r13");
   return ok;
}
static bool match_16(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_16;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_16 =(t -> t_value);
   (void)gen_16;
   
   ok = !strcmp(gen_16, "sp");
   return ok;
}
static bool match_17(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_17;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_17 =(t -> t_value);
   (void)gen_17;
   
   ok = !strcmp(gen_17, "r14");
   return ok;
}
static bool match_18(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_18;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_18 =(t -> t_value);
   (void)gen_18;
   
   ok = !strcmp(gen_18, "lr");
   return ok;
}
static bool match_19(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_19;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_19 =(t -> t_value);
   (void)gen_19;
   
   ok = !strcmp(gen_19, "r15");
   return ok;
}
static bool match_20(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_20;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_20 =(t -> t_value);
   (void)gen_20;
   
   ok = !strcmp(gen_20, "pc");
   return ok;
}
static bool match_21(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_21;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_21 =(t -> t_value);
   (void)gen_21;
   
   ok = !strcmp(gen_21, "lsl");
   return ok;
}
static bool match_22(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_22;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_22 =(t -> t_value);
   (void)gen_22;
   
   ok = !strcmp(gen_22, "lsr");
   return ok;
}
static bool match_23(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_23;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_23 =(t -> t_value);
   (void)gen_23;
   
   ok = !strcmp(gen_23, "asr");
   return ok;
}
static bool match_24(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_24;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 1)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_24 =(t -> t_value);
   (void)gen_24;
   
   ok = !strcmp(gen_24, "ror");
   return ok;
}
static bool match_25(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * user_s;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 3)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_COLON))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   user_s =(t -> t_value);
   (void)user_s;
   t = tokenarray_get(toks,(i + 2));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_COLON))return false;
   
   ok = true;
   return ok;
}
static unsigned int subst_0(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_0;
   const char * val;
   
   gen_0 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_0;
   
   val = "0" /* r0 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_1(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_1;
   const char * val;
   
   gen_1 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_1;
   
   val = "1" /* r1 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_2(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_2;
   const char * val;
   
   gen_2 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_2;
   
   val = "2" /* r2 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_3(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_3;
   const char * val;
   
   gen_3 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_3;
   
   val = "3" /* r3 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_4(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_4;
   const char * val;
   
   gen_4 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_4;
   
   val = "4" /* r4 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_5(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_5;
   const char * val;
   
   gen_5 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_5;
   
   val = "5" /* r5 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_6(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_6;
   const char * val;
   
   gen_6 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_6;
   
   val = "6" /* r6 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_7(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_7;
   const char * val;
   
   gen_7 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_7;
   
   val = "7" /* r7 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_8(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_8;
   const char * val;
   
   gen_8 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_8;
   
   val = "8" /* r8 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_9(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_9;
   const char * val;
   
   gen_9 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_9;
   
   val = "9" /* r9 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_10(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_10;
   const char * val;
   
   gen_10 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_10;
   
   val = "10" /* r10 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_11(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_11;
   const char * val;
   
   gen_11 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_11;
   
   val = "11" /* fp */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_12(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_12;
   const char * val;
   
   gen_12 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_12;
   
   val = "11" /* fp */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_13(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_13;
   const char * val;
   
   gen_13 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_13;
   
   val = "12" /* ip */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_14(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_14;
   const char * val;
   
   gen_14 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_14;
   
   val = "12" /* ip */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_15(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_15;
   const char * val;
   
   gen_15 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_15;
   
   val = "13" /* sp */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_16(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_16;
   const char * val;
   
   gen_16 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_16;
   
   val = "13" /* sp */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_17(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_17;
   const char * val;
   
   gen_17 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_17;
   
   val = "14" /* lr */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_18(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_18;
   const char * val;
   
   gen_18 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_18;
   
   val = "14" /* lr */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_19(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_19;
   const char * val;
   
   gen_19 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_19;
   
   val = "15" /* pc */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_20(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_20;
   const char * val;
   
   gen_20 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_20;
   
   val = "15" /* pc */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REG;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_21(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_21;
   const char * val;
   
   gen_21 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_21;
   
   val = "0" /* LSL */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_SHIFTCODE;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_22(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_22;
   const char * val;
   
   gen_22 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_22;
   
   val = "1" /* LSR */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_SHIFTCODE;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_23(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_23;
   const char * val;
   
   gen_23 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_23;
   
   val = "2" /* ASR */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_SHIFTCODE;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_24(struct tokenarray * toks, unsigned int i) {
   struct token * nt;
   struct token * ot;
   char * gen_24;
   const char * val;
   
   gen_24 =(tokenarray_get(toks,(i + 0))-> t_value);
   (void)gen_24;
   
   val = "3" /* ROR */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_SHIFTCODE;
   ot = tokenarray_get(toks, i);
   token_destroy(ot);
   tokenarray_set(toks,(i + 0), nt);
   return 0;
}
static unsigned int subst_25(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * user_s;
   const char * val;
   
   user_s =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)user_s;
   
   val = user_s;
   nt = token_create(TOK_MODIFIER, val);
   for(j = 0U;
   (j < 3); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      tokenarray_set(toks,(i + j), NULL);
   }
   tokenarray_set(toks,(i + 2), nt);
   return 2;
}
void target_scantokens(int line, struct tokenarray * toks) {
   unsigned int i;
   unsigned int num;
   
   (void)line;
   num = tokenarray_num(toks);
   for(i = 0U;
   (i < num); i =(i + 1U)) {
      if (match_0(toks, i))i =(i + subst_0(toks, i));
      if (match_1(toks, i))i =(i + subst_1(toks, i));
      if (match_2(toks, i))i =(i + subst_2(toks, i));
      if (match_3(toks, i))i =(i + subst_3(toks, i));
      if (match_4(toks, i))i =(i + subst_4(toks, i));
      if (match_5(toks, i))i =(i + subst_5(toks, i));
      if (match_6(toks, i))i =(i + subst_6(toks, i));
      if (match_7(toks, i))i =(i + subst_7(toks, i));
      if (match_8(toks, i))i =(i + subst_8(toks, i));
      if (match_9(toks, i))i =(i + subst_9(toks, i));
      if (match_10(toks, i))i =(i + subst_10(toks, i));
      if (match_11(toks, i))i =(i + subst_11(toks, i));
      if (match_12(toks, i))i =(i + subst_12(toks, i));
      if (match_13(toks, i))i =(i + subst_13(toks, i));
      if (match_14(toks, i))i =(i + subst_14(toks, i));
      if (match_15(toks, i))i =(i + subst_15(toks, i));
      if (match_16(toks, i))i =(i + subst_16(toks, i));
      if (match_17(toks, i))i =(i + subst_17(toks, i));
      if (match_18(toks, i))i =(i + subst_18(toks, i));
      if (match_19(toks, i))i =(i + subst_19(toks, i));
      if (match_20(toks, i))i =(i + subst_20(toks, i));
      if (match_21(toks, i))i =(i + subst_21(toks, i));
      if (match_22(toks, i))i =(i + subst_22(toks, i));
      if (match_23(toks, i))i =(i + subst_23(toks, i));
      if (match_24(toks, i))i =(i + subst_24(toks, i));
      if (match_25(toks, i))i =(i + subst_25(toks, i));
   }
   
}
