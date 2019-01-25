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
   case 36: return 1;
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
   case 36: return 1;
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
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
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_12 =(t -> t_value);
   (void)gen_12;
   
   ok = !strcmp(gen_12, "r12");
   return ok;
}
static bool match_13(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_13;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_13 =(t -> t_value);
   (void)gen_13;
   
   ok = !strcmp(gen_13, "r13");
   return ok;
}
static bool match_14(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_14;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_14 =(t -> t_value);
   (void)gen_14;
   
   ok = !strcmp(gen_14, "r14");
   return ok;
}
static bool match_15(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_15;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_15 =(t -> t_value);
   (void)gen_15;
   
   ok = !strcmp(gen_15, "r15");
   return ok;
}
static bool match_16(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_16;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_16 =(t -> t_value);
   (void)gen_16;
   
   ok = !strcmp(gen_16, "r16");
   return ok;
}
static bool match_17(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_17;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_17 =(t -> t_value);
   (void)gen_17;
   
   ok = !strcmp(gen_17, "r17");
   return ok;
}
static bool match_18(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_18;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_18 =(t -> t_value);
   (void)gen_18;
   
   ok = !strcmp(gen_18, "r18");
   return ok;
}
static bool match_19(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_19;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_19 =(t -> t_value);
   (void)gen_19;
   
   ok = !strcmp(gen_19, "r19");
   return ok;
}
static bool match_20(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_20;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_20 =(t -> t_value);
   (void)gen_20;
   
   ok = !strcmp(gen_20, "r20");
   return ok;
}
static bool match_21(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_21;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_21 =(t -> t_value);
   (void)gen_21;
   
   ok = !strcmp(gen_21, "r21");
   return ok;
}
static bool match_22(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_22;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_22 =(t -> t_value);
   (void)gen_22;
   
   ok = !strcmp(gen_22, "r22");
   return ok;
}
static bool match_23(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_23;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_23 =(t -> t_value);
   (void)gen_23;
   
   ok = !strcmp(gen_23, "r23");
   return ok;
}
static bool match_24(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_24;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_24 =(t -> t_value);
   (void)gen_24;
   
   ok = !strcmp(gen_24, "r24");
   return ok;
}
static bool match_25(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_25;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_25 =(t -> t_value);
   (void)gen_25;
   
   ok = !strcmp(gen_25, "r25");
   return ok;
}
static bool match_26(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_26;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_26 =(t -> t_value);
   (void)gen_26;
   
   ok = !strcmp(gen_26, "r26");
   return ok;
}
static bool match_27(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_27;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_27 =(t -> t_value);
   (void)gen_27;
   
   ok = !strcmp(gen_27, "r27");
   return ok;
}
static bool match_28(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_28;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_28 =(t -> t_value);
   (void)gen_28;
   
   ok = !strcmp(gen_28, "r28");
   return ok;
}
static bool match_29(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_29;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_29 =(t -> t_value);
   (void)gen_29;
   
   ok = !strcmp(gen_29, "r29");
   return ok;
}
static bool match_30(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_30;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_30 =(t -> t_value);
   (void)gen_30;
   
   ok = !strcmp(gen_30, "r30");
   return ok;
}
static bool match_31(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_31;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_31 =(t -> t_value);
   (void)gen_31;
   
   ok = !strcmp(gen_31, "r31");
   return ok;
}
static bool match_32(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_32;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_32 =(t -> t_value);
   (void)gen_32;
   
   ok = !strcmp(gen_32, "g0");
   return ok;
}
static bool match_33(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_33;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_33 =(t -> t_value);
   (void)gen_33;
   
   ok = !strcmp(gen_33, "g1");
   return ok;
}
static bool match_34(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_34;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_34 =(t -> t_value);
   (void)gen_34;
   
   ok = !strcmp(gen_34, "g2");
   return ok;
}
static bool match_35(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_35;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_35 =(t -> t_value);
   (void)gen_35;
   
   ok = !strcmp(gen_35, "g3");
   return ok;
}
static bool match_36(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_36;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_36 =(t -> t_value);
   (void)gen_36;
   
   ok = !strcmp(gen_36, "g4");
   return ok;
}
static bool match_37(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_37;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_37 =(t -> t_value);
   (void)gen_37;
   
   ok = !strcmp(gen_37, "g5");
   return ok;
}
static bool match_38(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_38;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_38 =(t -> t_value);
   (void)gen_38;
   
   ok = !strcmp(gen_38, "g6");
   return ok;
}
static bool match_39(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_39;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_39 =(t -> t_value);
   (void)gen_39;
   
   ok = !strcmp(gen_39, "g7");
   return ok;
}
static bool match_40(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_40;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_40 =(t -> t_value);
   (void)gen_40;
   
   ok = !strcmp(gen_40, "o0");
   return ok;
}
static bool match_41(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_41;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_41 =(t -> t_value);
   (void)gen_41;
   
   ok = !strcmp(gen_41, "o1");
   return ok;
}
static bool match_42(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_42;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_42 =(t -> t_value);
   (void)gen_42;
   
   ok = !strcmp(gen_42, "o2");
   return ok;
}
static bool match_43(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_43;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_43 =(t -> t_value);
   (void)gen_43;
   
   ok = !strcmp(gen_43, "o3");
   return ok;
}
static bool match_44(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_44;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_44 =(t -> t_value);
   (void)gen_44;
   
   ok = !strcmp(gen_44, "o4");
   return ok;
}
static bool match_45(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_45;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_45 =(t -> t_value);
   (void)gen_45;
   
   ok = !strcmp(gen_45, "o5");
   return ok;
}
static bool match_46(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_46;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_46 =(t -> t_value);
   (void)gen_46;
   
   ok = !strcmp(gen_46, "o6");
   return ok;
}
static bool match_47(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_47;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_47 =(t -> t_value);
   (void)gen_47;
   
   ok = !strcmp(gen_47, "o7");
   return ok;
}
static bool match_48(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_48;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_48 =(t -> t_value);
   (void)gen_48;
   
   ok = !strcmp(gen_48, "l0");
   return ok;
}
static bool match_49(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_49;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_49 =(t -> t_value);
   (void)gen_49;
   
   ok = !strcmp(gen_49, "l1");
   return ok;
}
static bool match_50(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_50;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_50 =(t -> t_value);
   (void)gen_50;
   
   ok = !strcmp(gen_50, "l2");
   return ok;
}
static bool match_51(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_51;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_51 =(t -> t_value);
   (void)gen_51;
   
   ok = !strcmp(gen_51, "l3");
   return ok;
}
static bool match_52(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_52;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_52 =(t -> t_value);
   (void)gen_52;
   
   ok = !strcmp(gen_52, "l4");
   return ok;
}
static bool match_53(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_53;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_53 =(t -> t_value);
   (void)gen_53;
   
   ok = !strcmp(gen_53, "l5");
   return ok;
}
static bool match_54(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_54;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_54 =(t -> t_value);
   (void)gen_54;
   
   ok = !strcmp(gen_54, "l6");
   return ok;
}
static bool match_55(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_55;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_55 =(t -> t_value);
   (void)gen_55;
   
   ok = !strcmp(gen_55, "l7");
   return ok;
}
static bool match_56(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_56;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_56 =(t -> t_value);
   (void)gen_56;
   
   ok = !strcmp(gen_56, "i0");
   return ok;
}
static bool match_57(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_57;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_57 =(t -> t_value);
   (void)gen_57;
   
   ok = !strcmp(gen_57, "i1");
   return ok;
}
static bool match_58(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_58;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_58 =(t -> t_value);
   (void)gen_58;
   
   ok = !strcmp(gen_58, "i2");
   return ok;
}
static bool match_59(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_59;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_59 =(t -> t_value);
   (void)gen_59;
   
   ok = !strcmp(gen_59, "i3");
   return ok;
}
static bool match_60(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_60;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_60 =(t -> t_value);
   (void)gen_60;
   
   ok = !strcmp(gen_60, "i4");
   return ok;
}
static bool match_61(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_61;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_61 =(t -> t_value);
   (void)gen_61;
   
   ok = !strcmp(gen_61, "i5");
   return ok;
}
static bool match_62(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_62;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_62 =(t -> t_value);
   (void)gen_62;
   
   ok = !strcmp(gen_62, "i6");
   return ok;
}
static bool match_63(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_63;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_63 =(t -> t_value);
   (void)gen_63;
   
   ok = !strcmp(gen_63, "i7");
   return ok;
}
static bool match_64(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_64;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_64 =(t -> t_value);
   (void)gen_64;
   
   ok = !strcmp(gen_64, "fp");
   return ok;
}
static bool match_65(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_65;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_65 =(t -> t_value);
   (void)gen_65;
   
   ok = !strcmp(gen_65, "sp");
   return ok;
}
static bool match_66(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_66;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_66 =(t -> t_value);
   (void)gen_66;
   
   ok = !strcmp(gen_66, "icc");
   return ok;
}
static bool match_67(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_67;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_67 =(t -> t_value);
   (void)gen_67;
   
   ok = !strcmp(gen_67, "xcc");
   return ok;
}
static bool match_68(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_68;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_68 =(t -> t_value);
   (void)gen_68;
   
   ok = !strcmp(gen_68, "ncc");
   return ok;
}
static bool match_69(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_69;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_69 =(t -> t_value);
   (void)gen_69;
   
   ok = !strcmp(gen_69, "f0");
   return ok;
}
static bool match_70(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_70;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_70 =(t -> t_value);
   (void)gen_70;
   
   ok = !strcmp(gen_70, "f1");
   return ok;
}
static bool match_71(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_71;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_71 =(t -> t_value);
   (void)gen_71;
   
   ok = !strcmp(gen_71, "f2");
   return ok;
}
static bool match_72(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_72;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_72 =(t -> t_value);
   (void)gen_72;
   
   ok = !strcmp(gen_72, "f3");
   return ok;
}
static bool match_73(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_73;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_73 =(t -> t_value);
   (void)gen_73;
   
   ok = !strcmp(gen_73, "f4");
   return ok;
}
static bool match_74(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_74;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_74 =(t -> t_value);
   (void)gen_74;
   
   ok = !strcmp(gen_74, "f5");
   return ok;
}
static bool match_75(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_75;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_75 =(t -> t_value);
   (void)gen_75;
   
   ok = !strcmp(gen_75, "f6");
   return ok;
}
static bool match_76(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_76;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_76 =(t -> t_value);
   (void)gen_76;
   
   ok = !strcmp(gen_76, "f7");
   return ok;
}
static bool match_77(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_77;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_77 =(t -> t_value);
   (void)gen_77;
   
   ok = !strcmp(gen_77, "f8");
   return ok;
}
static bool match_78(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_78;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_78 =(t -> t_value);
   (void)gen_78;
   
   ok = !strcmp(gen_78, "f9");
   return ok;
}
static bool match_79(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_79;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_79 =(t -> t_value);
   (void)gen_79;
   
   ok = !strcmp(gen_79, "f10");
   return ok;
}
static bool match_80(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_80;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_80 =(t -> t_value);
   (void)gen_80;
   
   ok = !strcmp(gen_80, "f11");
   return ok;
}
static bool match_81(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_81;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_81 =(t -> t_value);
   (void)gen_81;
   
   ok = !strcmp(gen_81, "f12");
   return ok;
}
static bool match_82(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_82;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_82 =(t -> t_value);
   (void)gen_82;
   
   ok = !strcmp(gen_82, "f13");
   return ok;
}
static bool match_83(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_83;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_83 =(t -> t_value);
   (void)gen_83;
   
   ok = !strcmp(gen_83, "f14");
   return ok;
}
static bool match_84(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_84;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_84 =(t -> t_value);
   (void)gen_84;
   
   ok = !strcmp(gen_84, "f15");
   return ok;
}
static bool match_85(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_85;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_85 =(t -> t_value);
   (void)gen_85;
   
   ok = !strcmp(gen_85, "f16");
   return ok;
}
static bool match_86(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_86;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_86 =(t -> t_value);
   (void)gen_86;
   
   ok = !strcmp(gen_86, "f17");
   return ok;
}
static bool match_87(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_87;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_87 =(t -> t_value);
   (void)gen_87;
   
   ok = !strcmp(gen_87, "f18");
   return ok;
}
static bool match_88(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_88;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_88 =(t -> t_value);
   (void)gen_88;
   
   ok = !strcmp(gen_88, "f19");
   return ok;
}
static bool match_89(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_89;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_89 =(t -> t_value);
   (void)gen_89;
   
   ok = !strcmp(gen_89, "f20");
   return ok;
}
static bool match_90(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_90;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_90 =(t -> t_value);
   (void)gen_90;
   
   ok = !strcmp(gen_90, "f21");
   return ok;
}
static bool match_91(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_91;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_91 =(t -> t_value);
   (void)gen_91;
   
   ok = !strcmp(gen_91, "f22");
   return ok;
}
static bool match_92(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_92;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_92 =(t -> t_value);
   (void)gen_92;
   
   ok = !strcmp(gen_92, "f23");
   return ok;
}
static bool match_93(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_93;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_93 =(t -> t_value);
   (void)gen_93;
   
   ok = !strcmp(gen_93, "f24");
   return ok;
}
static bool match_94(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_94;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_94 =(t -> t_value);
   (void)gen_94;
   
   ok = !strcmp(gen_94, "f25");
   return ok;
}
static bool match_95(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_95;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_95 =(t -> t_value);
   (void)gen_95;
   
   ok = !strcmp(gen_95, "f26");
   return ok;
}
static bool match_96(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_96;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_96 =(t -> t_value);
   (void)gen_96;
   
   ok = !strcmp(gen_96, "f27");
   return ok;
}
static bool match_97(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_97;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_97 =(t -> t_value);
   (void)gen_97;
   
   ok = !strcmp(gen_97, "f28");
   return ok;
}
static bool match_98(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_98;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_98 =(t -> t_value);
   (void)gen_98;
   
   ok = !strcmp(gen_98, "f29");
   return ok;
}
static bool match_99(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_99;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_99 =(t -> t_value);
   (void)gen_99;
   
   ok = !strcmp(gen_99, "f30");
   return ok;
}
static bool match_100(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_100;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_100 =(t -> t_value);
   (void)gen_100;
   
   ok = !strcmp(gen_100, "f31");
   return ok;
}
static bool match_101(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_101;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_101 =(t -> t_value);
   (void)gen_101;
   
   ok = !strcmp(gen_101, "f32");
   return ok;
}
static bool match_102(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_102;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_102 =(t -> t_value);
   (void)gen_102;
   
   ok = !strcmp(gen_102, "f34");
   return ok;
}
static bool match_103(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_103;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_103 =(t -> t_value);
   (void)gen_103;
   
   ok = !strcmp(gen_103, "f36");
   return ok;
}
static bool match_104(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_104;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_104 =(t -> t_value);
   (void)gen_104;
   
   ok = !strcmp(gen_104, "f38");
   return ok;
}
static bool match_105(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_105;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_105 =(t -> t_value);
   (void)gen_105;
   
   ok = !strcmp(gen_105, "f40");
   return ok;
}
static bool match_106(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_106;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_106 =(t -> t_value);
   (void)gen_106;
   
   ok = !strcmp(gen_106, "f42");
   return ok;
}
static bool match_107(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_107;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_107 =(t -> t_value);
   (void)gen_107;
   
   ok = !strcmp(gen_107, "f44");
   return ok;
}
static bool match_108(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_108;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_108 =(t -> t_value);
   (void)gen_108;
   
   ok = !strcmp(gen_108, "f46");
   return ok;
}
static bool match_109(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_109;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_109 =(t -> t_value);
   (void)gen_109;
   
   ok = !strcmp(gen_109, "f48");
   return ok;
}
static bool match_110(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_110;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_110 =(t -> t_value);
   (void)gen_110;
   
   ok = !strcmp(gen_110, "f50");
   return ok;
}
static bool match_111(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_111;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_111 =(t -> t_value);
   (void)gen_111;
   
   ok = !strcmp(gen_111, "f52");
   return ok;
}
static bool match_112(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_112;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_112 =(t -> t_value);
   (void)gen_112;
   
   ok = !strcmp(gen_112, "f54");
   return ok;
}
static bool match_113(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_113;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_113 =(t -> t_value);
   (void)gen_113;
   
   ok = !strcmp(gen_113, "f56");
   return ok;
}
static bool match_114(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_114;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_114 =(t -> t_value);
   (void)gen_114;
   
   ok = !strcmp(gen_114, "f58");
   return ok;
}
static bool match_115(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_115;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_115 =(t -> t_value);
   (void)gen_115;
   
   ok = !strcmp(gen_115, "f60");
   return ok;
}
static bool match_116(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_116;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_116 =(t -> t_value);
   (void)gen_116;
   
   ok = !strcmp(gen_116, "f62");
   return ok;
}
static bool match_117(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_117;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_117 =(t -> t_value);
   (void)gen_117;
   
   ok = !strcmp(gen_117, "d0");
   return ok;
}
static bool match_118(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_118;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_118 =(t -> t_value);
   (void)gen_118;
   
   ok = !strcmp(gen_118, "d2");
   return ok;
}
static bool match_119(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_119;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_119 =(t -> t_value);
   (void)gen_119;
   
   ok = !strcmp(gen_119, "d4");
   return ok;
}
static bool match_120(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_120;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_120 =(t -> t_value);
   (void)gen_120;
   
   ok = !strcmp(gen_120, "d6");
   return ok;
}
static bool match_121(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_121;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_121 =(t -> t_value);
   (void)gen_121;
   
   ok = !strcmp(gen_121, "d8");
   return ok;
}
static bool match_122(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_122;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_122 =(t -> t_value);
   (void)gen_122;
   
   ok = !strcmp(gen_122, "d10");
   return ok;
}
static bool match_123(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_123;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_123 =(t -> t_value);
   (void)gen_123;
   
   ok = !strcmp(gen_123, "d12");
   return ok;
}
static bool match_124(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_124;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_124 =(t -> t_value);
   (void)gen_124;
   
   ok = !strcmp(gen_124, "d14");
   return ok;
}
static bool match_125(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_125;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_125 =(t -> t_value);
   (void)gen_125;
   
   ok = !strcmp(gen_125, "d16");
   return ok;
}
static bool match_126(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_126;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_126 =(t -> t_value);
   (void)gen_126;
   
   ok = !strcmp(gen_126, "d18");
   return ok;
}
static bool match_127(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_127;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_127 =(t -> t_value);
   (void)gen_127;
   
   ok = !strcmp(gen_127, "d20");
   return ok;
}
static bool match_128(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_128;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_128 =(t -> t_value);
   (void)gen_128;
   
   ok = !strcmp(gen_128, "d22");
   return ok;
}
static bool match_129(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_129;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_129 =(t -> t_value);
   (void)gen_129;
   
   ok = !strcmp(gen_129, "d24");
   return ok;
}
static bool match_130(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_130;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_130 =(t -> t_value);
   (void)gen_130;
   
   ok = !strcmp(gen_130, "d26");
   return ok;
}
static bool match_131(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_131;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_131 =(t -> t_value);
   (void)gen_131;
   
   ok = !strcmp(gen_131, "d28");
   return ok;
}
static bool match_132(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_132;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_132 =(t -> t_value);
   (void)gen_132;
   
   ok = !strcmp(gen_132, "d30");
   return ok;
}
static bool match_133(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_133;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_133 =(t -> t_value);
   (void)gen_133;
   
   ok = !strcmp(gen_133, "d32");
   return ok;
}
static bool match_134(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_134;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_134 =(t -> t_value);
   (void)gen_134;
   
   ok = !strcmp(gen_134, "d34");
   return ok;
}
static bool match_135(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_135;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_135 =(t -> t_value);
   (void)gen_135;
   
   ok = !strcmp(gen_135, "d36");
   return ok;
}
static bool match_136(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_136;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_136 =(t -> t_value);
   (void)gen_136;
   
   ok = !strcmp(gen_136, "d38");
   return ok;
}
static bool match_137(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_137;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_137 =(t -> t_value);
   (void)gen_137;
   
   ok = !strcmp(gen_137, "d40");
   return ok;
}
static bool match_138(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_138;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_138 =(t -> t_value);
   (void)gen_138;
   
   ok = !strcmp(gen_138, "d42");
   return ok;
}
static bool match_139(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_139;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_139 =(t -> t_value);
   (void)gen_139;
   
   ok = !strcmp(gen_139, "d44");
   return ok;
}
static bool match_140(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_140;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_140 =(t -> t_value);
   (void)gen_140;
   
   ok = !strcmp(gen_140, "d46");
   return ok;
}
static bool match_141(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_141;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_141 =(t -> t_value);
   (void)gen_141;
   
   ok = !strcmp(gen_141, "d48");
   return ok;
}
static bool match_142(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_142;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_142 =(t -> t_value);
   (void)gen_142;
   
   ok = !strcmp(gen_142, "d50");
   return ok;
}
static bool match_143(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_143;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_143 =(t -> t_value);
   (void)gen_143;
   
   ok = !strcmp(gen_143, "d52");
   return ok;
}
static bool match_144(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_144;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_144 =(t -> t_value);
   (void)gen_144;
   
   ok = !strcmp(gen_144, "d54");
   return ok;
}
static bool match_145(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_145;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_145 =(t -> t_value);
   (void)gen_145;
   
   ok = !strcmp(gen_145, "d56");
   return ok;
}
static bool match_146(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_146;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_146 =(t -> t_value);
   (void)gen_146;
   
   ok = !strcmp(gen_146, "d58");
   return ok;
}
static bool match_147(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_147;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_147 =(t -> t_value);
   (void)gen_147;
   
   ok = !strcmp(gen_147, "d60");
   return ok;
}
static bool match_148(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_148;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_148 =(t -> t_value);
   (void)gen_148;
   
   ok = !strcmp(gen_148, "d62");
   return ok;
}
static bool match_149(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_149;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_149 =(t -> t_value);
   (void)gen_149;
   
   ok = !strcmp(gen_149, "q0");
   return ok;
}
static bool match_150(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_150;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_150 =(t -> t_value);
   (void)gen_150;
   
   ok = !strcmp(gen_150, "q4");
   return ok;
}
static bool match_151(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_151;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_151 =(t -> t_value);
   (void)gen_151;
   
   ok = !strcmp(gen_151, "d8");
   return ok;
}
static bool match_152(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_152;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_152 =(t -> t_value);
   (void)gen_152;
   
   ok = !strcmp(gen_152, "q12");
   return ok;
}
static bool match_153(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_153;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_153 =(t -> t_value);
   (void)gen_153;
   
   ok = !strcmp(gen_153, "q16");
   return ok;
}
static bool match_154(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_154;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_154 =(t -> t_value);
   (void)gen_154;
   
   ok = !strcmp(gen_154, "q20");
   return ok;
}
static bool match_155(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_155;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_155 =(t -> t_value);
   (void)gen_155;
   
   ok = !strcmp(gen_155, "q24");
   return ok;
}
static bool match_156(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_156;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_156 =(t -> t_value);
   (void)gen_156;
   
   ok = !strcmp(gen_156, "q28");
   return ok;
}
static bool match_157(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_157;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_157 =(t -> t_value);
   (void)gen_157;
   
   ok = !strcmp(gen_157, "q32");
   return ok;
}
static bool match_158(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_158;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_158 =(t -> t_value);
   (void)gen_158;
   
   ok = !strcmp(gen_158, "q36");
   return ok;
}
static bool match_159(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_159;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_159 =(t -> t_value);
   (void)gen_159;
   
   ok = !strcmp(gen_159, "q40");
   return ok;
}
static bool match_160(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_160;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_160 =(t -> t_value);
   (void)gen_160;
   
   ok = !strcmp(gen_160, "q44");
   return ok;
}
static bool match_161(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_161;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_161 =(t -> t_value);
   (void)gen_161;
   
   ok = !strcmp(gen_161, "q48");
   return ok;
}
static bool match_162(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_162;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_162 =(t -> t_value);
   (void)gen_162;
   
   ok = !strcmp(gen_162, "q52");
   return ok;
}
static bool match_163(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_163;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_163 =(t -> t_value);
   (void)gen_163;
   
   ok = !strcmp(gen_163, "q56");
   return ok;
}
static bool match_164(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_164;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_164 =(t -> t_value);
   (void)gen_164;
   
   ok = !strcmp(gen_164, "q60");
   return ok;
}
static bool match_165(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_165;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_165 =(t -> t_value);
   (void)gen_165;
   
   ok = !strcmp(gen_165, "fcc0");
   return ok;
}
static bool match_166(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_166;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_166 =(t -> t_value);
   (void)gen_166;
   
   ok = !strcmp(gen_166, "fcc1");
   return ok;
}
static bool match_167(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_167;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_167 =(t -> t_value);
   (void)gen_167;
   
   ok = !strcmp(gen_167, "fcc2");
   return ok;
}
static bool match_168(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_168;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_168 =(t -> t_value);
   (void)gen_168;
   
   ok = !strcmp(gen_168, "fcc3");
   return ok;
}
static bool match_169(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_169;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_169 =(t -> t_value);
   (void)gen_169;
   
   ok = !strcmp(gen_169, "asr16");
   return ok;
}
static bool match_170(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_170;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_170 =(t -> t_value);
   (void)gen_170;
   
   ok = !strcmp(gen_170, "asr17");
   return ok;
}
static bool match_171(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_171;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_171 =(t -> t_value);
   (void)gen_171;
   
   ok = !strcmp(gen_171, "asr18");
   return ok;
}
static bool match_172(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_172;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_172 =(t -> t_value);
   (void)gen_172;
   
   ok = !strcmp(gen_172, "asr19");
   return ok;
}
static bool match_173(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_173;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_173 =(t -> t_value);
   (void)gen_173;
   
   ok = !strcmp(gen_173, "asr20");
   return ok;
}
static bool match_174(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_174;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_174 =(t -> t_value);
   (void)gen_174;
   
   ok = !strcmp(gen_174, "asr21");
   return ok;
}
static bool match_175(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_175;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_175 =(t -> t_value);
   (void)gen_175;
   
   ok = !strcmp(gen_175, "asr22");
   return ok;
}
static bool match_176(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_176;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_176 =(t -> t_value);
   (void)gen_176;
   
   ok = !strcmp(gen_176, "asr23");
   return ok;
}
static bool match_177(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_177;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_177 =(t -> t_value);
   (void)gen_177;
   
   ok = !strcmp(gen_177, "asr24");
   return ok;
}
static bool match_178(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_178;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_178 =(t -> t_value);
   (void)gen_178;
   
   ok = !strcmp(gen_178, "asr25");
   return ok;
}
static bool match_179(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_179;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_179 =(t -> t_value);
   (void)gen_179;
   
   ok = !strcmp(gen_179, "asr26");
   return ok;
}
static bool match_180(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_180;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_180 =(t -> t_value);
   (void)gen_180;
   
   ok = !strcmp(gen_180, "asr27");
   return ok;
}
static bool match_181(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_181;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_181 =(t -> t_value);
   (void)gen_181;
   
   ok = !strcmp(gen_181, "asr28");
   return ok;
}
static bool match_182(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_182;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_182 =(t -> t_value);
   (void)gen_182;
   
   ok = !strcmp(gen_182, "asr29");
   return ok;
}
static bool match_183(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_183;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_183 =(t -> t_value);
   (void)gen_183;
   
   ok = !strcmp(gen_183, "asr30");
   return ok;
}
static bool match_184(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_184;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_184 =(t -> t_value);
   (void)gen_184;
   
   ok = !strcmp(gen_184, "asr31");
   return ok;
}
static bool match_185(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_185;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_185 =(t -> t_value);
   (void)gen_185;
   
   ok = !strcmp(gen_185, "asi");
   return ok;
}
static bool match_186(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_186;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_186 =(t -> t_value);
   (void)gen_186;
   
   ok = !strcmp(gen_186, "canrestore");
   return ok;
}
static bool match_187(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_187;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_187 =(t -> t_value);
   (void)gen_187;
   
   ok = !strcmp(gen_187, "cansave");
   return ok;
}
static bool match_188(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_188;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_188 =(t -> t_value);
   (void)gen_188;
   
   ok = !strcmp(gen_188, "cleanwin");
   return ok;
}
static bool match_189(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_189;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_189 =(t -> t_value);
   (void)gen_189;
   
   ok = !strcmp(gen_189, "cwp");
   return ok;
}
static bool match_190(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_190;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_190 =(t -> t_value);
   (void)gen_190;
   
   ok = !strcmp(gen_190, "fq");
   return ok;
}
static bool match_191(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_191;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_191 =(t -> t_value);
   (void)gen_191;
   
   ok = !strcmp(gen_191, "otherwin");
   return ok;
}
static bool match_192(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_192;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_192 =(t -> t_value);
   (void)gen_192;
   
   ok = !strcmp(gen_192, "pc");
   return ok;
}
static bool match_193(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_193;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_193 =(t -> t_value);
   (void)gen_193;
   
   ok = !strcmp(gen_193, "pil");
   return ok;
}
static bool match_194(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_194;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_194 =(t -> t_value);
   (void)gen_194;
   
   ok = !strcmp(gen_194, "pstate");
   return ok;
}
static bool match_195(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_195;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_195 =(t -> t_value);
   (void)gen_195;
   
   ok = !strcmp(gen_195, "tba");
   return ok;
}
static bool match_196(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_196;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_196 =(t -> t_value);
   (void)gen_196;
   
   ok = !strcmp(gen_196, "tick");
   return ok;
}
static bool match_197(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_197;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_197 =(t -> t_value);
   (void)gen_197;
   
   ok = !strcmp(gen_197, "tl");
   return ok;
}
static bool match_198(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_198;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_198 =(t -> t_value);
   (void)gen_198;
   
   ok = !strcmp(gen_198, "tnpc");
   return ok;
}
static bool match_199(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_199;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_199 =(t -> t_value);
   (void)gen_199;
   
   ok = !strcmp(gen_199, "tpc");
   return ok;
}
static bool match_200(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_200;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_200 =(t -> t_value);
   (void)gen_200;
   
   ok = !strcmp(gen_200, "tstate");
   return ok;
}
static bool match_201(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_201;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_201 =(t -> t_value);
   (void)gen_201;
   
   ok = !strcmp(gen_201, "tt");
   return ok;
}
static bool match_202(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_202;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_202 =(t -> t_value);
   (void)gen_202;
   
   ok = !strcmp(gen_202, "ccr");
   return ok;
}
static bool match_203(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_203;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_203 =(t -> t_value);
   (void)gen_203;
   
   ok = !strcmp(gen_203, "fprs");
   return ok;
}
static bool match_204(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_204;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_204 =(t -> t_value);
   (void)gen_204;
   
   ok = !strcmp(gen_204, "ver");
   return ok;
}
static bool match_205(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_205;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_205 =(t -> t_value);
   (void)gen_205;
   
   ok = !strcmp(gen_205, "wstate");
   return ok;
}
static bool match_206(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_206;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_206 =(t -> t_value);
   (void)gen_206;
   
   ok = !strcmp(gen_206, "y");
   return ok;
}
static bool match_207(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_207;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_207 =(t -> t_value);
   (void)gen_207;
   
   ok = !strcmp(gen_207, "fsr");
   return ok;
}
static bool match_208(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_208;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_208 =(t -> t_value);
   (void)gen_208;
   
   ok = !strcmp(gen_208, "n_reads");
   return ok;
}
static bool match_209(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_209;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_209 =(t -> t_value);
   (void)gen_209;
   
   ok = !strcmp(gen_209, "one_read");
   return ok;
}
static bool match_210(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_210;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_210 =(t -> t_value);
   (void)gen_210;
   
   ok = !strcmp(gen_210, "n_writes");
   return ok;
}
static bool match_211(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_211;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_211 =(t -> t_value);
   (void)gen_211;
   
   ok = !strcmp(gen_211, "one_write");
   return ok;
}
static bool match_212(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_212;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_212 =(t -> t_value);
   (void)gen_212;
   
   ok = !strcmp(gen_212, "page");
   return ok;
}
static bool match_213(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_213;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_213 =(t -> t_value);
   (void)gen_213;
   
   ok = !strcmp(gen_213, "Sync");
   return ok;
}
static bool match_214(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_214;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_214 =(t -> t_value);
   (void)gen_214;
   
   ok = !strcmp(gen_214, "MemIssue");
   return ok;
}
static bool match_215(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_215;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_215 =(t -> t_value);
   (void)gen_215;
   
   ok = !strcmp(gen_215, "Lookaside");
   return ok;
}
static bool match_216(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_216;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_216 =(t -> t_value);
   (void)gen_216;
   
   ok = !strcmp(gen_216, "StoreStore");
   return ok;
}
static bool match_217(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_217;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_217 =(t -> t_value);
   (void)gen_217;
   
   ok = !strcmp(gen_217, "LoadStore");
   return ok;
}
static bool match_218(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_218;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_218 =(t -> t_value);
   (void)gen_218;
   
   ok = !strcmp(gen_218, "StoreLoad");
   return ok;
}
static bool match_219(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_219;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_219 =(t -> t_value);
   (void)gen_219;
   
   ok = !strcmp(gen_219, "LoadLoad");
   return ok;
}
static bool match_220(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_220;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_220 =(t -> t_value);
   (void)gen_220;
   
   ok = !strcmp(gen_220, "ASI_AIUP");
   return ok;
}
static bool match_221(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_221;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_221 =(t -> t_value);
   (void)gen_221;
   
   ok = !strcmp(gen_221, "ASI_AIUS");
   return ok;
}
static bool match_222(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_222;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_222 =(t -> t_value);
   (void)gen_222;
   
   ok = !strcmp(gen_222, "ASI_AIUP_L");
   return ok;
}
static bool match_223(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_223;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_223 =(t -> t_value);
   (void)gen_223;
   
   ok = !strcmp(gen_223, "ASI_AIUS_L");
   return ok;
}
static bool match_224(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_224;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_224 =(t -> t_value);
   (void)gen_224;
   
   ok = !strcmp(gen_224, "ASI_P");
   return ok;
}
static bool match_225(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_225;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_225 =(t -> t_value);
   (void)gen_225;
   
   ok = !strcmp(gen_225, "ASI_S");
   return ok;
}
static bool match_226(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_226;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_226 =(t -> t_value);
   (void)gen_226;
   
   ok = !strcmp(gen_226, "ASI_PNF");
   return ok;
}
static bool match_227(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_227;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_227 =(t -> t_value);
   (void)gen_227;
   
   ok = !strcmp(gen_227, "ASI_SNF");
   return ok;
}
static bool match_228(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_228;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_228 =(t -> t_value);
   (void)gen_228;
   
   ok = !strcmp(gen_228, "ASI_P_L");
   return ok;
}
static bool match_229(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_229;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_229 =(t -> t_value);
   (void)gen_229;
   
   ok = !strcmp(gen_229, "ASI_S_L");
   return ok;
}
static bool match_230(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_230;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_230 =(t -> t_value);
   (void)gen_230;
   
   ok = !strcmp(gen_230, "ASI_PNF_L");
   return ok;
}
static bool match_231(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_231;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_231 =(t -> t_value);
   (void)gen_231;
   
   ok = !strcmp(gen_231, "ASL_SNF_L");
   return ok;
}
static bool match_232(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_232;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_232 =(t -> t_value);
   (void)gen_232;
   
   ok = !strcmp(gen_232, "ASI_AS_IF_USER_PRIMARY");
   return ok;
}
static bool match_233(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_233;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_233 =(t -> t_value);
   (void)gen_233;
   
   ok = !strcmp(gen_233, "ASI_AS_IF_USER_SECONDARY");
   return ok;
}
static bool match_234(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_234;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_234 =(t -> t_value);
   (void)gen_234;
   
   ok = !strcmp(gen_234, "ASI_AS_IF_USER_PRIMARY_LITTLE");
   return ok;
}
static bool match_235(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_235;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_235 =(t -> t_value);
   (void)gen_235;
   
   ok = !strcmp(gen_235, "ASI_AS_IF_USER_SECONDARY_LITTLE");
   return ok;
}
static bool match_236(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_236;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_236 =(t -> t_value);
   (void)gen_236;
   
   ok = !strcmp(gen_236, "ASI_PRIMARY");
   return ok;
}
static bool match_237(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_237;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_237 =(t -> t_value);
   (void)gen_237;
   
   ok = !strcmp(gen_237, "ASI_SECONDARY");
   return ok;
}
static bool match_238(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_238;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_238 =(t -> t_value);
   (void)gen_238;
   
   ok = !strcmp(gen_238, "ASI_PRIMARY_NOFAULT");
   return ok;
}
static bool match_239(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_239;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_239 =(t -> t_value);
   (void)gen_239;
   
   ok = !strcmp(gen_239, "ASI_SECONDARY_NOFAULT");
   return ok;
}
static bool match_240(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_240;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_240 =(t -> t_value);
   (void)gen_240;
   
   ok = !strcmp(gen_240, "ASI_PRIMARY_LITTLE");
   return ok;
}
static bool match_241(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_241;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_241 =(t -> t_value);
   (void)gen_241;
   
   ok = !strcmp(gen_241, "ASI_SECONDARY_LITTLE");
   return ok;
}
static bool match_242(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_242;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_242 =(t -> t_value);
   (void)gen_242;
   
   ok = !strcmp(gen_242, "ASI_PRIMARY_NOFAULT_LITTLE");
   return ok;
}
static bool match_243(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_243;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_HASH))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_243 =(t -> t_value);
   (void)gen_243;
   
   ok = !strcmp(gen_243, "ASL_SECONDARY_NOFAULT_LITTLE");
   return ok;
}
static bool match_244(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_244;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_244 =(t -> t_value);
   (void)gen_244;
   
   ok = !strcmp(gen_244, "hi");
   return ok;
}
static bool match_245(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_245;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_245 =(t -> t_value);
   (void)gen_245;
   
   ok = !strcmp(gen_245, "lo");
   return ok;
}
static bool match_246(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_246;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_246 =(t -> t_value);
   (void)gen_246;
   
   ok = !strcmp(gen_246, "uhi");
   return ok;
}
static bool match_247(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_247;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_247 =(t -> t_value);
   (void)gen_247;
   
   ok = !strcmp(gen_247, "ulo");
   return ok;
}
static bool match_248(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_248;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_248 =(t -> t_value);
   (void)gen_248;
   
   ok = !strcmp(gen_248, "h44");
   return ok;
}
static bool match_249(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_249;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_249 =(t -> t_value);
   (void)gen_249;
   
   ok = !strcmp(gen_249, "m44");
   return ok;
}
static bool match_250(struct tokenarray * toks, unsigned int i) {
   unsigned int num;
   struct token * t;
   char * gen_250;
   bool ok;
   
   num = tokenarray_num(toks);
   if ((num <(i + 2)))return false;
   
   t = tokenarray_get(toks,(i + 0));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_PCT))return false;
   t = tokenarray_get(toks,(i + 1));
   assert(!(t == NULL));
   if (!((t -> t_type)== TOK_IDENT))return false;
   gen_250 =(t -> t_value);
   (void)gen_250;
   
   ok = !strcmp(gen_250, "l44");
   return ok;
}
static unsigned int subst_0(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_0;
   const char * val;
   
   gen_0 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_0;
   
   val = "0" /* r0 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_1(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_1;
   const char * val;
   
   gen_1 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_1;
   
   val = "1" /* r1 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_2(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_2;
   const char * val;
   
   gen_2 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_2;
   
   val = "2" /* r2 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_3(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_3;
   const char * val;
   
   gen_3 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_3;
   
   val = "3" /* r3 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_4(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_4;
   const char * val;
   
   gen_4 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_4;
   
   val = "4" /* r4 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_5(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_5;
   const char * val;
   
   gen_5 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_5;
   
   val = "5" /* r5 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_6(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_6;
   const char * val;
   
   gen_6 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_6;
   
   val = "6" /* r6 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_7(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_7;
   const char * val;
   
   gen_7 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_7;
   
   val = "7" /* r7 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_8(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_8;
   const char * val;
   
   gen_8 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_8;
   
   val = "8" /* r8 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_9(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_9;
   const char * val;
   
   gen_9 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_9;
   
   val = "9" /* r9 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_10(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_10;
   const char * val;
   
   gen_10 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_10;
   
   val = "10" /* r10 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_11(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_11;
   const char * val;
   
   gen_11 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_11;
   
   val = "11" /* r11 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_12(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_12;
   const char * val;
   
   gen_12 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_12;
   
   val = "12" /* r12 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_13(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_13;
   const char * val;
   
   gen_13 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_13;
   
   val = "13" /* r13 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_14(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_14;
   const char * val;
   
   gen_14 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_14;
   
   val = "14" /* r14 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_15(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_15;
   const char * val;
   
   gen_15 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_15;
   
   val = "15" /* r15 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_16(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_16;
   const char * val;
   
   gen_16 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_16;
   
   val = "16" /* r16 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_17(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_17;
   const char * val;
   
   gen_17 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_17;
   
   val = "17" /* r17 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_18(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_18;
   const char * val;
   
   gen_18 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_18;
   
   val = "18" /* r18 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_19(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_19;
   const char * val;
   
   gen_19 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_19;
   
   val = "19" /* r19 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_20(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_20;
   const char * val;
   
   gen_20 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_20;
   
   val = "20" /* r20 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_21(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_21;
   const char * val;
   
   gen_21 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_21;
   
   val = "21" /* r21 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_22(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_22;
   const char * val;
   
   gen_22 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_22;
   
   val = "22" /* r22 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_23(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_23;
   const char * val;
   
   gen_23 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_23;
   
   val = "23" /* r23 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_24(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_24;
   const char * val;
   
   gen_24 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_24;
   
   val = "24" /* r24 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_25(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_25;
   const char * val;
   
   gen_25 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_25;
   
   val = "25" /* r25 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_26(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_26;
   const char * val;
   
   gen_26 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_26;
   
   val = "26" /* r26 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_27(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_27;
   const char * val;
   
   gen_27 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_27;
   
   val = "27" /* r27 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_28(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_28;
   const char * val;
   
   gen_28 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_28;
   
   val = "28" /* r28 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_29(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_29;
   const char * val;
   
   gen_29 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_29;
   
   val = "29" /* r29 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_30(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_30;
   const char * val;
   
   gen_30 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_30;
   
   val = "30" /* r30 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_31(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_31;
   const char * val;
   
   gen_31 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_31;
   
   val = "31" /* r31 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_32(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_32;
   const char * val;
   
   gen_32 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_32;
   
   val = "0" /* r0 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_33(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_33;
   const char * val;
   
   gen_33 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_33;
   
   val = "1" /* r1 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_34(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_34;
   const char * val;
   
   gen_34 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_34;
   
   val = "2" /* r2 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_35(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_35;
   const char * val;
   
   gen_35 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_35;
   
   val = "3" /* r3 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_36(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_36;
   const char * val;
   
   gen_36 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_36;
   
   val = "4" /* r4 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_37(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_37;
   const char * val;
   
   gen_37 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_37;
   
   val = "5" /* r5 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_38(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_38;
   const char * val;
   
   gen_38 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_38;
   
   val = "6" /* r6 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_39(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_39;
   const char * val;
   
   gen_39 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_39;
   
   val = "7" /* r7 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_40(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_40;
   const char * val;
   
   gen_40 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_40;
   
   val = "8" /* r8 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_41(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_41;
   const char * val;
   
   gen_41 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_41;
   
   val = "9" /* r9 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_42(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_42;
   const char * val;
   
   gen_42 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_42;
   
   val = "10" /* r10 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_43(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_43;
   const char * val;
   
   gen_43 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_43;
   
   val = "11" /* r11 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_44(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_44;
   const char * val;
   
   gen_44 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_44;
   
   val = "12" /* r12 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_45(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_45;
   const char * val;
   
   gen_45 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_45;
   
   val = "13" /* r13 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_46(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_46;
   const char * val;
   
   gen_46 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_46;
   
   val = "14" /* r14 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_47(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_47;
   const char * val;
   
   gen_47 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_47;
   
   val = "15" /* r15 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_48(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_48;
   const char * val;
   
   gen_48 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_48;
   
   val = "16" /* r16 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_49(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_49;
   const char * val;
   
   gen_49 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_49;
   
   val = "17" /* r17 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_50(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_50;
   const char * val;
   
   gen_50 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_50;
   
   val = "18" /* r18 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_51(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_51;
   const char * val;
   
   gen_51 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_51;
   
   val = "19" /* r19 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_52(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_52;
   const char * val;
   
   gen_52 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_52;
   
   val = "20" /* r20 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_53(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_53;
   const char * val;
   
   gen_53 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_53;
   
   val = "21" /* r21 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_54(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_54;
   const char * val;
   
   gen_54 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_54;
   
   val = "22" /* r22 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_55(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_55;
   const char * val;
   
   gen_55 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_55;
   
   val = "23" /* r23 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_56(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_56;
   const char * val;
   
   gen_56 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_56;
   
   val = "24" /* r24 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_57(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_57;
   const char * val;
   
   gen_57 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_57;
   
   val = "25" /* r25 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_58(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_58;
   const char * val;
   
   gen_58 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_58;
   
   val = "26" /* r26 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_59(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_59;
   const char * val;
   
   gen_59 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_59;
   
   val = "27" /* r27 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_60(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_60;
   const char * val;
   
   gen_60 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_60;
   
   val = "28" /* r28 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_61(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_61;
   const char * val;
   
   gen_61 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_61;
   
   val = "29" /* r29 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_62(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_62;
   const char * val;
   
   gen_62 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_62;
   
   val = "30" /* r30 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_63(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_63;
   const char * val;
   
   gen_63 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_63;
   
   val = "31" /* r31 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_64(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_64;
   const char * val;
   
   gen_64 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_64;
   
   val = "30" /* r30 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_65(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_65;
   const char * val;
   
   gen_65 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_65;
   
   val = "14" /* r14 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_RREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_66(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_66;
   const char * val;
   
   gen_66 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_66;
   
   val = "0" /* ICC */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ICC;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_67(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_67;
   const char * val;
   
   gen_67 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_67;
   
   val = "2" /* XCC */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ICC;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_68(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_68;
   const char * val;
   
   gen_68 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_68;
   
   val = "2" /* XCC */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ICC;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_69(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_69;
   const char * val;
   
   gen_69 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_69;
   
   val = "0" /* f0 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_70(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_70;
   const char * val;
   
   gen_70 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_70;
   
   val = "1" /* f1 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_71(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_71;
   const char * val;
   
   gen_71 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_71;
   
   val = "2" /* f2 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_72(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_72;
   const char * val;
   
   gen_72 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_72;
   
   val = "3" /* f3 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_73(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_73;
   const char * val;
   
   gen_73 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_73;
   
   val = "4" /* f4 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_74(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_74;
   const char * val;
   
   gen_74 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_74;
   
   val = "5" /* f5 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_75(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_75;
   const char * val;
   
   gen_75 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_75;
   
   val = "6" /* f6 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_76(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_76;
   const char * val;
   
   gen_76 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_76;
   
   val = "7" /* f7 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_77(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_77;
   const char * val;
   
   gen_77 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_77;
   
   val = "8" /* f8 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_78(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_78;
   const char * val;
   
   gen_78 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_78;
   
   val = "9" /* f9 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_79(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_79;
   const char * val;
   
   gen_79 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_79;
   
   val = "10" /* f10 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_80(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_80;
   const char * val;
   
   gen_80 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_80;
   
   val = "11" /* f11 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_81(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_81;
   const char * val;
   
   gen_81 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_81;
   
   val = "12" /* f12 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_82(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_82;
   const char * val;
   
   gen_82 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_82;
   
   val = "13" /* f13 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_83(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_83;
   const char * val;
   
   gen_83 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_83;
   
   val = "14" /* f14 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_84(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_84;
   const char * val;
   
   gen_84 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_84;
   
   val = "15" /* f15 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_85(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_85;
   const char * val;
   
   gen_85 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_85;
   
   val = "16" /* f16 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_86(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_86;
   const char * val;
   
   gen_86 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_86;
   
   val = "17" /* f17 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_87(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_87;
   const char * val;
   
   gen_87 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_87;
   
   val = "18" /* f18 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_88(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_88;
   const char * val;
   
   gen_88 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_88;
   
   val = "19" /* f19 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_89(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_89;
   const char * val;
   
   gen_89 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_89;
   
   val = "20" /* f20 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_90(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_90;
   const char * val;
   
   gen_90 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_90;
   
   val = "21" /* f21 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_91(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_91;
   const char * val;
   
   gen_91 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_91;
   
   val = "22" /* f22 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_92(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_92;
   const char * val;
   
   gen_92 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_92;
   
   val = "23" /* f23 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_93(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_93;
   const char * val;
   
   gen_93 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_93;
   
   val = "24" /* f24 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_94(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_94;
   const char * val;
   
   gen_94 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_94;
   
   val = "25" /* f25 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_95(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_95;
   const char * val;
   
   gen_95 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_95;
   
   val = "26" /* f26 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_96(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_96;
   const char * val;
   
   gen_96 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_96;
   
   val = "27" /* f27 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_97(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_97;
   const char * val;
   
   gen_97 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_97;
   
   val = "28" /* f28 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_98(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_98;
   const char * val;
   
   gen_98 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_98;
   
   val = "29" /* f29 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_99(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_99;
   const char * val;
   
   gen_99 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_99;
   
   val = "30" /* f30 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_100(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_100;
   const char * val;
   
   gen_100 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_100;
   
   val = "31" /* f31 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_101(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_101;
   const char * val;
   
   gen_101 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_101;
   
   val = "1" /* f1 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_102(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_102;
   const char * val;
   
   gen_102 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_102;
   
   val = "3" /* f3 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_103(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_103;
   const char * val;
   
   gen_103 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_103;
   
   val = "5" /* f5 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_104(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_104;
   const char * val;
   
   gen_104 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_104;
   
   val = "7" /* f7 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_105(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_105;
   const char * val;
   
   gen_105 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_105;
   
   val = "9" /* f9 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_106(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_106;
   const char * val;
   
   gen_106 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_106;
   
   val = "11" /* f11 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_107(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_107;
   const char * val;
   
   gen_107 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_107;
   
   val = "13" /* f13 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_108(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_108;
   const char * val;
   
   gen_108 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_108;
   
   val = "15" /* f15 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_109(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_109;
   const char * val;
   
   gen_109 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_109;
   
   val = "17" /* f17 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_110(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_110;
   const char * val;
   
   gen_110 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_110;
   
   val = "19" /* f19 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_111(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_111;
   const char * val;
   
   gen_111 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_111;
   
   val = "21" /* f21 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_112(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_112;
   const char * val;
   
   gen_112 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_112;
   
   val = "23" /* f23 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_113(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_113;
   const char * val;
   
   gen_113 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_113;
   
   val = "25" /* f25 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_114(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_114;
   const char * val;
   
   gen_114 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_114;
   
   val = "27" /* f27 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_115(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_115;
   const char * val;
   
   gen_115 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_115;
   
   val = "29" /* f29 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_116(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_116;
   const char * val;
   
   gen_116 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_116;
   
   val = "31" /* f31 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_117(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_117;
   const char * val;
   
   gen_117 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_117;
   
   val = "0" /* f0 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_118(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_118;
   const char * val;
   
   gen_118 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_118;
   
   val = "2" /* f2 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_119(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_119;
   const char * val;
   
   gen_119 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_119;
   
   val = "4" /* f4 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_120(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_120;
   const char * val;
   
   gen_120 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_120;
   
   val = "6" /* f6 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_121(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_121;
   const char * val;
   
   gen_121 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_121;
   
   val = "8" /* f8 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_122(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_122;
   const char * val;
   
   gen_122 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_122;
   
   val = "10" /* f10 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_123(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_123;
   const char * val;
   
   gen_123 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_123;
   
   val = "12" /* f12 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_124(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_124;
   const char * val;
   
   gen_124 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_124;
   
   val = "14" /* f14 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_125(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_125;
   const char * val;
   
   gen_125 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_125;
   
   val = "16" /* f16 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_126(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_126;
   const char * val;
   
   gen_126 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_126;
   
   val = "18" /* f18 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_127(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_127;
   const char * val;
   
   gen_127 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_127;
   
   val = "20" /* f20 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_128(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_128;
   const char * val;
   
   gen_128 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_128;
   
   val = "22" /* f22 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_129(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_129;
   const char * val;
   
   gen_129 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_129;
   
   val = "24" /* f24 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_130(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_130;
   const char * val;
   
   gen_130 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_130;
   
   val = "26" /* f26 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_131(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_131;
   const char * val;
   
   gen_131 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_131;
   
   val = "28" /* f28 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_132(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_132;
   const char * val;
   
   gen_132 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_132;
   
   val = "30" /* f30 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_133(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_133;
   const char * val;
   
   gen_133 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_133;
   
   val = "1" /* f1 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_134(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_134;
   const char * val;
   
   gen_134 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_134;
   
   val = "3" /* f3 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_135(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_135;
   const char * val;
   
   gen_135 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_135;
   
   val = "5" /* f5 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_136(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_136;
   const char * val;
   
   gen_136 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_136;
   
   val = "7" /* f7 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_137(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_137;
   const char * val;
   
   gen_137 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_137;
   
   val = "9" /* f9 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_138(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_138;
   const char * val;
   
   gen_138 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_138;
   
   val = "11" /* f11 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_139(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_139;
   const char * val;
   
   gen_139 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_139;
   
   val = "13" /* f13 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_140(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_140;
   const char * val;
   
   gen_140 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_140;
   
   val = "15" /* f15 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_141(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_141;
   const char * val;
   
   gen_141 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_141;
   
   val = "17" /* f17 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_142(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_142;
   const char * val;
   
   gen_142 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_142;
   
   val = "19" /* f19 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_143(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_143;
   const char * val;
   
   gen_143 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_143;
   
   val = "21" /* f21 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_144(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_144;
   const char * val;
   
   gen_144 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_144;
   
   val = "23" /* f23 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_145(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_145;
   const char * val;
   
   gen_145 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_145;
   
   val = "25" /* f25 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_146(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_146;
   const char * val;
   
   gen_146 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_146;
   
   val = "27" /* f27 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_147(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_147;
   const char * val;
   
   gen_147 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_147;
   
   val = "29" /* f29 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_148(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_148;
   const char * val;
   
   gen_148 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_148;
   
   val = "31" /* f31 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_149(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_149;
   const char * val;
   
   gen_149 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_149;
   
   val = "0" /* f0 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_150(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_150;
   const char * val;
   
   gen_150 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_150;
   
   val = "4" /* f4 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_151(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_151;
   const char * val;
   
   gen_151 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_151;
   
   val = "8" /* f8 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_152(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_152;
   const char * val;
   
   gen_152 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_152;
   
   val = "12" /* f12 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_153(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_153;
   const char * val;
   
   gen_153 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_153;
   
   val = "16" /* f16 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_154(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_154;
   const char * val;
   
   gen_154 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_154;
   
   val = "20" /* f20 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_155(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_155;
   const char * val;
   
   gen_155 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_155;
   
   val = "24" /* f24 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_156(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_156;
   const char * val;
   
   gen_156 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_156;
   
   val = "28" /* f28 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_157(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_157;
   const char * val;
   
   gen_157 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_157;
   
   val = "1" /* f1 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_158(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_158;
   const char * val;
   
   gen_158 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_158;
   
   val = "5" /* f5 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_159(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_159;
   const char * val;
   
   gen_159 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_159;
   
   val = "9" /* f9 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_160(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_160;
   const char * val;
   
   gen_160 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_160;
   
   val = "13" /* f13 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_161(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_161;
   const char * val;
   
   gen_161 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_161;
   
   val = "17" /* f17 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_162(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_162;
   const char * val;
   
   gen_162 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_162;
   
   val = "21" /* f21 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_163(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_163;
   const char * val;
   
   gen_163 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_163;
   
   val = "25" /* f25 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_164(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_164;
   const char * val;
   
   gen_164 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_164;
   
   val = "29" /* f29 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_165(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_165;
   const char * val;
   
   gen_165 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_165;
   
   val = "0" /* fcc0 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FCC;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_166(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_166;
   const char * val;
   
   gen_166 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_166;
   
   val = "1" /* fcc1 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FCC;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_167(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_167;
   const char * val;
   
   gen_167 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_167;
   
   val = "2" /* fcc2 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FCC;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_168(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_168;
   const char * val;
   
   gen_168 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_168;
   
   val = "3" /* fcc3 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FCC;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_169(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_169;
   const char * val;
   
   gen_169 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_169;
   
   val = "16" /* ASR16 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_170(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_170;
   const char * val;
   
   gen_170 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_170;
   
   val = "17" /* ASR17 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_171(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_171;
   const char * val;
   
   gen_171 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_171;
   
   val = "18" /* ASR18 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_172(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_172;
   const char * val;
   
   gen_172 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_172;
   
   val = "19" /* ASR19 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_173(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_173;
   const char * val;
   
   gen_173 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_173;
   
   val = "20" /* ASR20 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_174(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_174;
   const char * val;
   
   gen_174 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_174;
   
   val = "21" /* ASR21 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_175(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_175;
   const char * val;
   
   gen_175 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_175;
   
   val = "22" /* ASR22 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_176(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_176;
   const char * val;
   
   gen_176 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_176;
   
   val = "23" /* ASR23 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_177(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_177;
   const char * val;
   
   gen_177 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_177;
   
   val = "24" /* ASR24 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_178(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_178;
   const char * val;
   
   gen_178 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_178;
   
   val = "25" /* ASR25 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_179(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_179;
   const char * val;
   
   gen_179 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_179;
   
   val = "26" /* ASR26 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_180(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_180;
   const char * val;
   
   gen_180 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_180;
   
   val = "27" /* ASR27 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_181(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_181;
   const char * val;
   
   gen_181 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_181;
   
   val = "28" /* ASR28 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_182(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_182;
   const char * val;
   
   gen_182 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_182;
   
   val = "29" /* ASR29 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_183(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_183;
   const char * val;
   
   gen_183 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_183;
   
   val = "30" /* ASR30 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_184(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_184;
   const char * val;
   
   gen_184 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_184;
   
   val = "31" /* ASR31 */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_185(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_185;
   const char * val;
   
   gen_185 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_185;
   
   val = "0";
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_ASIREG;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_186(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_186;
   const char * val;
   
   gen_186 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_186;
   
   val = "11" /* CANRESTORE */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_187(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_187;
   const char * val;
   
   gen_187 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_187;
   
   val = "10" /* CANSAVE */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_188(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_188;
   const char * val;
   
   gen_188 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_188;
   
   val = "12" /* CLEANWIN */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_189(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_189;
   const char * val;
   
   gen_189 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_189;
   
   val = "9" /* CWP */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_190(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_190;
   const char * val;
   
   gen_190 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_190;
   
   val = "15" /* FQ */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_191(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_191;
   const char * val;
   
   gen_191 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_191;
   
   val = "13" /* OTHERWIN */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_192(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_192;
   const char * val;
   
   gen_192 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_192;
   
   val = "5" /* PC */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_193(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_193;
   const char * val;
   
   gen_193 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_193;
   
   val = "8" /* PIL */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_194(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_194;
   const char * val;
   
   gen_194 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_194;
   
   val = "6" /* PSTATE */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_195(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_195;
   const char * val;
   
   gen_195 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_195;
   
   val = "5" /* TBA */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_196(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_196;
   const char * val;
   
   gen_196 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_196;
   
   val = "4" /* TICK */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_197(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_197;
   const char * val;
   
   gen_197 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_197;
   
   val = "7" /* TL */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_198(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_198;
   const char * val;
   
   gen_198 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_198;
   
   val = "1" /* TNPC */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_199(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_199;
   const char * val;
   
   gen_199 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_199;
   
   val = "0" /* TPC */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_200(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_200;
   const char * val;
   
   gen_200 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_200;
   
   val = "2" /* TSTATE */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_201(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_201;
   const char * val;
   
   gen_201 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_201;
   
   val = "3" /* TT */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_202(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_202;
   const char * val;
   
   gen_202 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_202;
   
   val = "2" /* CCR */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_203(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_203;
   const char * val;
   
   gen_203 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_203;
   
   val = "6" /* FPRS */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_204(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_204;
   const char * val;
   
   gen_204 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_204;
   
   val = "31" /* VER */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_205(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_205;
   const char * val;
   
   gen_205 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_205;
   
   val = "14" /* WSTATE */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_PR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_206(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_206;
   const char * val;
   
   gen_206 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_206;
   
   val = "0" /* Y */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_ASR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_207(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_207;
   const char * val;
   
   gen_207 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_207;
   
   val = "0" /* FSR */;
   nt = token_create(TOK_TARGET, val);
   nt->t_ttype = TTOK_REGCLASS_FSR;
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_208(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_208;
   const char * val;
   
   gen_208 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_208;
   
   val = "0";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_209(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_209;
   const char * val;
   
   gen_209 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_209;
   
   val = "1";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_210(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_210;
   const char * val;
   
   gen_210 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_210;
   
   val = "2";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_211(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_211;
   const char * val;
   
   gen_211 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_211;
   
   val = "3";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_212(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_212;
   const char * val;
   
   gen_212 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_212;
   
   val = "4";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_213(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_213;
   const char * val;
   
   gen_213 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_213;
   
   val = "64";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_214(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_214;
   const char * val;
   
   gen_214 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_214;
   
   val = "32";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_215(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_215;
   const char * val;
   
   gen_215 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_215;
   
   val = "16";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_216(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_216;
   const char * val;
   
   gen_216 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_216;
   
   val = "8";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_217(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_217;
   const char * val;
   
   gen_217 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_217;
   
   val = "4";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_218(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_218;
   const char * val;
   
   gen_218 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_218;
   
   val = "2";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_219(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_219;
   const char * val;
   
   gen_219 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_219;
   
   val = "1";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_220(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_220;
   const char * val;
   
   gen_220 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_220;
   
   val = "16";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_221(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_221;
   const char * val;
   
   gen_221 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_221;
   
   val = "17";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_222(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_222;
   const char * val;
   
   gen_222 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_222;
   
   val = "24";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_223(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_223;
   const char * val;
   
   gen_223 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_223;
   
   val = "25";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_224(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_224;
   const char * val;
   
   gen_224 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_224;
   
   val = "128";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_225(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_225;
   const char * val;
   
   gen_225 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_225;
   
   val = "129";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_226(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_226;
   const char * val;
   
   gen_226 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_226;
   
   val = "130";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_227(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_227;
   const char * val;
   
   gen_227 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_227;
   
   val = "131";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_228(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_228;
   const char * val;
   
   gen_228 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_228;
   
   val = "136";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_229(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_229;
   const char * val;
   
   gen_229 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_229;
   
   val = "137";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_230(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_230;
   const char * val;
   
   gen_230 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_230;
   
   val = "138";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_231(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_231;
   const char * val;
   
   gen_231 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_231;
   
   val = "139";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_232(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_232;
   const char * val;
   
   gen_232 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_232;
   
   val = "16";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_233(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_233;
   const char * val;
   
   gen_233 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_233;
   
   val = "17";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_234(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_234;
   const char * val;
   
   gen_234 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_234;
   
   val = "24";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_235(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_235;
   const char * val;
   
   gen_235 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_235;
   
   val = "25";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_236(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_236;
   const char * val;
   
   gen_236 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_236;
   
   val = "128";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_237(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_237;
   const char * val;
   
   gen_237 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_237;
   
   val = "129";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_238(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_238;
   const char * val;
   
   gen_238 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_238;
   
   val = "130";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_239(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_239;
   const char * val;
   
   gen_239 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_239;
   
   val = "131";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_240(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_240;
   const char * val;
   
   gen_240 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_240;
   
   val = "136";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_241(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_241;
   const char * val;
   
   gen_241 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_241;
   
   val = "137";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_242(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_242;
   const char * val;
   
   gen_242 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_242;
   
   val = "138";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_243(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_243;
   const char * val;
   
   gen_243 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_243;
   
   val = "139";
   nt = token_create(TOK_NUMBER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_244(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_244;
   const char * val;
   
   gen_244 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_244;
   
   val = "hi";
   nt = token_create(TOK_MODIFIER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_245(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_245;
   const char * val;
   
   gen_245 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_245;
   
   val = "lo";
   nt = token_create(TOK_MODIFIER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_246(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_246;
   const char * val;
   
   gen_246 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_246;
   
   val = "uhi";
   nt = token_create(TOK_MODIFIER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_247(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_247;
   const char * val;
   
   gen_247 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_247;
   
   val = "ulo";
   nt = token_create(TOK_MODIFIER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_248(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_248;
   const char * val;
   
   gen_248 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_248;
   
   val = "h44";
   nt = token_create(TOK_MODIFIER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_249(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_249;
   const char * val;
   
   gen_249 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_249;
   
   val = "m44";
   nt = token_create(TOK_MODIFIER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
}
static unsigned int subst_250(struct tokenarray * toks, unsigned int i) {
   unsigned int j;
   struct token * nt;
   struct token * ot;
   char * gen_250;
   const char * val;
   
   gen_250 =(tokenarray_get(toks,(i + 1))-> t_value);
   (void)gen_250;
   
   val = "l44";
   nt = token_create(TOK_MODIFIER, val);
   for(j = 0U;
   (j < 2); j =(j + 1U)) {
      ot = tokenarray_get(toks,(i + j));
      token_destroy(ot);
   }
   tokenarray_set(toks,(i + 0U), NULL);
   tokenarray_set(toks,(i + 1), nt);
   return 1;
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
      if (match_26(toks, i))i =(i + subst_26(toks, i));
      if (match_27(toks, i))i =(i + subst_27(toks, i));
      if (match_28(toks, i))i =(i + subst_28(toks, i));
      if (match_29(toks, i))i =(i + subst_29(toks, i));
      if (match_30(toks, i))i =(i + subst_30(toks, i));
      if (match_31(toks, i))i =(i + subst_31(toks, i));
      if (match_32(toks, i))i =(i + subst_32(toks, i));
      if (match_33(toks, i))i =(i + subst_33(toks, i));
      if (match_34(toks, i))i =(i + subst_34(toks, i));
      if (match_35(toks, i))i =(i + subst_35(toks, i));
      if (match_36(toks, i))i =(i + subst_36(toks, i));
      if (match_37(toks, i))i =(i + subst_37(toks, i));
      if (match_38(toks, i))i =(i + subst_38(toks, i));
      if (match_39(toks, i))i =(i + subst_39(toks, i));
      if (match_40(toks, i))i =(i + subst_40(toks, i));
      if (match_41(toks, i))i =(i + subst_41(toks, i));
      if (match_42(toks, i))i =(i + subst_42(toks, i));
      if (match_43(toks, i))i =(i + subst_43(toks, i));
      if (match_44(toks, i))i =(i + subst_44(toks, i));
      if (match_45(toks, i))i =(i + subst_45(toks, i));
      if (match_46(toks, i))i =(i + subst_46(toks, i));
      if (match_47(toks, i))i =(i + subst_47(toks, i));
      if (match_48(toks, i))i =(i + subst_48(toks, i));
      if (match_49(toks, i))i =(i + subst_49(toks, i));
      if (match_50(toks, i))i =(i + subst_50(toks, i));
      if (match_51(toks, i))i =(i + subst_51(toks, i));
      if (match_52(toks, i))i =(i + subst_52(toks, i));
      if (match_53(toks, i))i =(i + subst_53(toks, i));
      if (match_54(toks, i))i =(i + subst_54(toks, i));
      if (match_55(toks, i))i =(i + subst_55(toks, i));
      if (match_56(toks, i))i =(i + subst_56(toks, i));
      if (match_57(toks, i))i =(i + subst_57(toks, i));
      if (match_58(toks, i))i =(i + subst_58(toks, i));
      if (match_59(toks, i))i =(i + subst_59(toks, i));
      if (match_60(toks, i))i =(i + subst_60(toks, i));
      if (match_61(toks, i))i =(i + subst_61(toks, i));
      if (match_62(toks, i))i =(i + subst_62(toks, i));
      if (match_63(toks, i))i =(i + subst_63(toks, i));
      if (match_64(toks, i))i =(i + subst_64(toks, i));
      if (match_65(toks, i))i =(i + subst_65(toks, i));
      if (match_66(toks, i))i =(i + subst_66(toks, i));
      if (match_67(toks, i))i =(i + subst_67(toks, i));
      if (match_68(toks, i))i =(i + subst_68(toks, i));
      if (match_69(toks, i))i =(i + subst_69(toks, i));
      if (match_70(toks, i))i =(i + subst_70(toks, i));
      if (match_71(toks, i))i =(i + subst_71(toks, i));
      if (match_72(toks, i))i =(i + subst_72(toks, i));
      if (match_73(toks, i))i =(i + subst_73(toks, i));
      if (match_74(toks, i))i =(i + subst_74(toks, i));
      if (match_75(toks, i))i =(i + subst_75(toks, i));
      if (match_76(toks, i))i =(i + subst_76(toks, i));
      if (match_77(toks, i))i =(i + subst_77(toks, i));
      if (match_78(toks, i))i =(i + subst_78(toks, i));
      if (match_79(toks, i))i =(i + subst_79(toks, i));
      if (match_80(toks, i))i =(i + subst_80(toks, i));
      if (match_81(toks, i))i =(i + subst_81(toks, i));
      if (match_82(toks, i))i =(i + subst_82(toks, i));
      if (match_83(toks, i))i =(i + subst_83(toks, i));
      if (match_84(toks, i))i =(i + subst_84(toks, i));
      if (match_85(toks, i))i =(i + subst_85(toks, i));
      if (match_86(toks, i))i =(i + subst_86(toks, i));
      if (match_87(toks, i))i =(i + subst_87(toks, i));
      if (match_88(toks, i))i =(i + subst_88(toks, i));
      if (match_89(toks, i))i =(i + subst_89(toks, i));
      if (match_90(toks, i))i =(i + subst_90(toks, i));
      if (match_91(toks, i))i =(i + subst_91(toks, i));
      if (match_92(toks, i))i =(i + subst_92(toks, i));
      if (match_93(toks, i))i =(i + subst_93(toks, i));
      if (match_94(toks, i))i =(i + subst_94(toks, i));
      if (match_95(toks, i))i =(i + subst_95(toks, i));
      if (match_96(toks, i))i =(i + subst_96(toks, i));
      if (match_97(toks, i))i =(i + subst_97(toks, i));
      if (match_98(toks, i))i =(i + subst_98(toks, i));
      if (match_99(toks, i))i =(i + subst_99(toks, i));
      if (match_100(toks, i))i =(i + subst_100(toks, i));
      if (match_101(toks, i))i =(i + subst_101(toks, i));
      if (match_102(toks, i))i =(i + subst_102(toks, i));
      if (match_103(toks, i))i =(i + subst_103(toks, i));
      if (match_104(toks, i))i =(i + subst_104(toks, i));
      if (match_105(toks, i))i =(i + subst_105(toks, i));
      if (match_106(toks, i))i =(i + subst_106(toks, i));
      if (match_107(toks, i))i =(i + subst_107(toks, i));
      if (match_108(toks, i))i =(i + subst_108(toks, i));
      if (match_109(toks, i))i =(i + subst_109(toks, i));
      if (match_110(toks, i))i =(i + subst_110(toks, i));
      if (match_111(toks, i))i =(i + subst_111(toks, i));
      if (match_112(toks, i))i =(i + subst_112(toks, i));
      if (match_113(toks, i))i =(i + subst_113(toks, i));
      if (match_114(toks, i))i =(i + subst_114(toks, i));
      if (match_115(toks, i))i =(i + subst_115(toks, i));
      if (match_116(toks, i))i =(i + subst_116(toks, i));
      if (match_117(toks, i))i =(i + subst_117(toks, i));
      if (match_118(toks, i))i =(i + subst_118(toks, i));
      if (match_119(toks, i))i =(i + subst_119(toks, i));
      if (match_120(toks, i))i =(i + subst_120(toks, i));
      if (match_121(toks, i))i =(i + subst_121(toks, i));
      if (match_122(toks, i))i =(i + subst_122(toks, i));
      if (match_123(toks, i))i =(i + subst_123(toks, i));
      if (match_124(toks, i))i =(i + subst_124(toks, i));
      if (match_125(toks, i))i =(i + subst_125(toks, i));
      if (match_126(toks, i))i =(i + subst_126(toks, i));
      if (match_127(toks, i))i =(i + subst_127(toks, i));
      if (match_128(toks, i))i =(i + subst_128(toks, i));
      if (match_129(toks, i))i =(i + subst_129(toks, i));
      if (match_130(toks, i))i =(i + subst_130(toks, i));
      if (match_131(toks, i))i =(i + subst_131(toks, i));
      if (match_132(toks, i))i =(i + subst_132(toks, i));
      if (match_133(toks, i))i =(i + subst_133(toks, i));
      if (match_134(toks, i))i =(i + subst_134(toks, i));
      if (match_135(toks, i))i =(i + subst_135(toks, i));
      if (match_136(toks, i))i =(i + subst_136(toks, i));
      if (match_137(toks, i))i =(i + subst_137(toks, i));
      if (match_138(toks, i))i =(i + subst_138(toks, i));
      if (match_139(toks, i))i =(i + subst_139(toks, i));
      if (match_140(toks, i))i =(i + subst_140(toks, i));
      if (match_141(toks, i))i =(i + subst_141(toks, i));
      if (match_142(toks, i))i =(i + subst_142(toks, i));
      if (match_143(toks, i))i =(i + subst_143(toks, i));
      if (match_144(toks, i))i =(i + subst_144(toks, i));
      if (match_145(toks, i))i =(i + subst_145(toks, i));
      if (match_146(toks, i))i =(i + subst_146(toks, i));
      if (match_147(toks, i))i =(i + subst_147(toks, i));
      if (match_148(toks, i))i =(i + subst_148(toks, i));
      if (match_149(toks, i))i =(i + subst_149(toks, i));
      if (match_150(toks, i))i =(i + subst_150(toks, i));
      if (match_151(toks, i))i =(i + subst_151(toks, i));
      if (match_152(toks, i))i =(i + subst_152(toks, i));
      if (match_153(toks, i))i =(i + subst_153(toks, i));
      if (match_154(toks, i))i =(i + subst_154(toks, i));
      if (match_155(toks, i))i =(i + subst_155(toks, i));
      if (match_156(toks, i))i =(i + subst_156(toks, i));
      if (match_157(toks, i))i =(i + subst_157(toks, i));
      if (match_158(toks, i))i =(i + subst_158(toks, i));
      if (match_159(toks, i))i =(i + subst_159(toks, i));
      if (match_160(toks, i))i =(i + subst_160(toks, i));
      if (match_161(toks, i))i =(i + subst_161(toks, i));
      if (match_162(toks, i))i =(i + subst_162(toks, i));
      if (match_163(toks, i))i =(i + subst_163(toks, i));
      if (match_164(toks, i))i =(i + subst_164(toks, i));
      if (match_165(toks, i))i =(i + subst_165(toks, i));
      if (match_166(toks, i))i =(i + subst_166(toks, i));
      if (match_167(toks, i))i =(i + subst_167(toks, i));
      if (match_168(toks, i))i =(i + subst_168(toks, i));
      if (match_169(toks, i))i =(i + subst_169(toks, i));
      if (match_170(toks, i))i =(i + subst_170(toks, i));
      if (match_171(toks, i))i =(i + subst_171(toks, i));
      if (match_172(toks, i))i =(i + subst_172(toks, i));
      if (match_173(toks, i))i =(i + subst_173(toks, i));
      if (match_174(toks, i))i =(i + subst_174(toks, i));
      if (match_175(toks, i))i =(i + subst_175(toks, i));
      if (match_176(toks, i))i =(i + subst_176(toks, i));
      if (match_177(toks, i))i =(i + subst_177(toks, i));
      if (match_178(toks, i))i =(i + subst_178(toks, i));
      if (match_179(toks, i))i =(i + subst_179(toks, i));
      if (match_180(toks, i))i =(i + subst_180(toks, i));
      if (match_181(toks, i))i =(i + subst_181(toks, i));
      if (match_182(toks, i))i =(i + subst_182(toks, i));
      if (match_183(toks, i))i =(i + subst_183(toks, i));
      if (match_184(toks, i))i =(i + subst_184(toks, i));
      if (match_185(toks, i))i =(i + subst_185(toks, i));
      if (match_186(toks, i))i =(i + subst_186(toks, i));
      if (match_187(toks, i))i =(i + subst_187(toks, i));
      if (match_188(toks, i))i =(i + subst_188(toks, i));
      if (match_189(toks, i))i =(i + subst_189(toks, i));
      if (match_190(toks, i))i =(i + subst_190(toks, i));
      if (match_191(toks, i))i =(i + subst_191(toks, i));
      if (match_192(toks, i))i =(i + subst_192(toks, i));
      if (match_193(toks, i))i =(i + subst_193(toks, i));
      if (match_194(toks, i))i =(i + subst_194(toks, i));
      if (match_195(toks, i))i =(i + subst_195(toks, i));
      if (match_196(toks, i))i =(i + subst_196(toks, i));
      if (match_197(toks, i))i =(i + subst_197(toks, i));
      if (match_198(toks, i))i =(i + subst_198(toks, i));
      if (match_199(toks, i))i =(i + subst_199(toks, i));
      if (match_200(toks, i))i =(i + subst_200(toks, i));
      if (match_201(toks, i))i =(i + subst_201(toks, i));
      if (match_202(toks, i))i =(i + subst_202(toks, i));
      if (match_203(toks, i))i =(i + subst_203(toks, i));
      if (match_204(toks, i))i =(i + subst_204(toks, i));
      if (match_205(toks, i))i =(i + subst_205(toks, i));
      if (match_206(toks, i))i =(i + subst_206(toks, i));
      if (match_207(toks, i))i =(i + subst_207(toks, i));
      if (match_208(toks, i))i =(i + subst_208(toks, i));
      if (match_209(toks, i))i =(i + subst_209(toks, i));
      if (match_210(toks, i))i =(i + subst_210(toks, i));
      if (match_211(toks, i))i =(i + subst_211(toks, i));
      if (match_212(toks, i))i =(i + subst_212(toks, i));
      if (match_213(toks, i))i =(i + subst_213(toks, i));
      if (match_214(toks, i))i =(i + subst_214(toks, i));
      if (match_215(toks, i))i =(i + subst_215(toks, i));
      if (match_216(toks, i))i =(i + subst_216(toks, i));
      if (match_217(toks, i))i =(i + subst_217(toks, i));
      if (match_218(toks, i))i =(i + subst_218(toks, i));
      if (match_219(toks, i))i =(i + subst_219(toks, i));
      if (match_220(toks, i))i =(i + subst_220(toks, i));
      if (match_221(toks, i))i =(i + subst_221(toks, i));
      if (match_222(toks, i))i =(i + subst_222(toks, i));
      if (match_223(toks, i))i =(i + subst_223(toks, i));
      if (match_224(toks, i))i =(i + subst_224(toks, i));
      if (match_225(toks, i))i =(i + subst_225(toks, i));
      if (match_226(toks, i))i =(i + subst_226(toks, i));
      if (match_227(toks, i))i =(i + subst_227(toks, i));
      if (match_228(toks, i))i =(i + subst_228(toks, i));
      if (match_229(toks, i))i =(i + subst_229(toks, i));
      if (match_230(toks, i))i =(i + subst_230(toks, i));
      if (match_231(toks, i))i =(i + subst_231(toks, i));
      if (match_232(toks, i))i =(i + subst_232(toks, i));
      if (match_233(toks, i))i =(i + subst_233(toks, i));
      if (match_234(toks, i))i =(i + subst_234(toks, i));
      if (match_235(toks, i))i =(i + subst_235(toks, i));
      if (match_236(toks, i))i =(i + subst_236(toks, i));
      if (match_237(toks, i))i =(i + subst_237(toks, i));
      if (match_238(toks, i))i =(i + subst_238(toks, i));
      if (match_239(toks, i))i =(i + subst_239(toks, i));
      if (match_240(toks, i))i =(i + subst_240(toks, i));
      if (match_241(toks, i))i =(i + subst_241(toks, i));
      if (match_242(toks, i))i =(i + subst_242(toks, i));
      if (match_243(toks, i))i =(i + subst_243(toks, i));
      if (match_244(toks, i))i =(i + subst_244(toks, i));
      if (match_245(toks, i))i =(i + subst_245(toks, i));
      if (match_246(toks, i))i =(i + subst_246(toks, i));
      if (match_247(toks, i))i =(i + subst_247(toks, i));
      if (match_248(toks, i))i =(i + subst_248(toks, i));
      if (match_249(toks, i))i =(i + subst_249(toks, i));
      if (match_250(toks, i))i =(i + subst_250(toks, i));
   }
   
}
