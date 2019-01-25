/* Automatically generated; do not edit */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "utils.h"
#include "section.h"
#include "reloc.h"
#include "elfreloc.h"
#include "targetreloc.h"
#include "targetelfdefs.h"
#include "as.h"

enum reloc_modifier target_reloc_getmodifier(const char * name) {
   if (!strcmp(name, "lo"))return RELOC_MOD_LO;
   else if (!strcmp(name, "hi"))return RELOC_MOD_HI;
   else if (!strcmp(name, "ulo"))return RELOC_MOD_ULO;
   else if (!strcmp(name, "uhi"))return RELOC_MOD_UHI;
   else if (!strcmp(name, "h44"))return RELOC_MOD_H44;
   else if (!strcmp(name, "m44"))return RELOC_MOD_M44;
   else if (!strcmp(name, "l44"))return RELOC_MOD_L44;
   else if (!strcmp(name, "got"))return RELOC_MOD_GOT;
   else if (!strcmp(name, "plt"))return RELOC_MOD_PLT;
   else{
      (void)name;
      /*
       * ?
       */
      assert(0);
      return RELOC_MOD_NONE;
   }
}
const char * target_reloc_modifier_name(enum reloc_modifier mod) {
   switch(mod) {
   case RELOC_MOD_NONE: return NULL;
   case RELOC_MOD_LO: return "%lo";
   case RELOC_MOD_HI: return "%hi";
   case RELOC_MOD_ULO: return "%ulo";
   case RELOC_MOD_UHI: return "%uhi";
   case RELOC_MOD_H44: return "%h44";
   case RELOC_MOD_M44: return "%m44";
   case RELOC_MOD_L44: return "%l44";
   case RELOC_MOD_GOT: return "%got";
   case RELOC_MOD_PLT: return "%plt";
   }
   assert(0);
   return NULL;
}
const char * target_reloc_field_name(enum reloc_field rf) {
   switch(rf) {
   case RELOC_FIELD_DISP30: return "disp30";
   case RELOC_FIELD_DISP22: return "disp22";
   case RELOC_FIELD_DISP19: return "disp19";
   case RELOC_FIELD_D16LO: return "d16lo";
   case RELOC_FIELD_IMM22: return "imm22";
   case RELOC_FIELD_SIMM13: return "simm13";
   case RELOC_FIELD_SIMM11: return "simm11";
   case RELOC_FIELD_SIMM10: return "simm10";
   case RELOC_FIELD_IMM7: return "imm7";
   case RELOC_FIELD_IMM6: return "imm6";
   case RELOC_FIELD_IMM5: return "imm5";
   case RELOC_FIELD_DATA64: return "data64";
   case RELOC_FIELD_DATA32: return "data32";
   case RELOC_FIELD_DATA16: return "data16";
   case RELOC_FIELD_DATA8: return "data8";
   }
   assert(0);
   return NULL;
}
static UNUSED u_machword reloc_input_disp30(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t disp30;
   uint32_t signbits;
   u_machword location;
   int64_t sval;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   disp30 = section_get32(snum, offset);
   disp30 =((disp30 >> 0U)& 1073741823U);
   signbits = 1U;
   if (!((disp30 &(signbits << 29))== 0U)) {
      signbits = 3U;
      disp30 =(disp30 |(signbits << 30));
   }
   sval =((int64_t)((uint64_t)(uint32_t)disp30 |(((1ULL << 29ULL)&(uint64_t)(uint32_t)disp30)?(18446744073709551615ULL - 1073741823ULL): 0ULL))<< 2U);
   input =(uint64_t)sval;
   return input;
}
static UNUSED u_machword reloc_input_disp22(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t disp22;
   uint32_t signbits;
   u_machword location;
   int64_t sval;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   disp22 = section_get32(snum, offset);
   disp22 =((disp22 >> 0U)& 4194303U);
   signbits = 1U;
   if (!((disp22 &(signbits << 21))== 0U)) {
      signbits = 1023U;
      disp22 =(disp22 |(signbits << 22));
   }
   sval =((int64_t)((uint64_t)(uint32_t)disp22 |(((1ULL << 21ULL)&(uint64_t)(uint32_t)disp22)?(18446744073709551615ULL - 4194303ULL): 0ULL))<< 2U);
   input =(uint64_t)sval;
   return input;
}
static UNUSED u_machword reloc_input_disp19(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t disp19;
   uint32_t signbits;
   u_machword location;
   int64_t sval;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   disp19 = section_get32(snum, offset);
   disp19 =((disp19 >> 0U)& 524287U);
   signbits = 1U;
   if (!((disp19 &(signbits << 18))== 0U)) {
      signbits = 8191U;
      disp19 =(disp19 |(signbits << 19));
   }
   sval =((int64_t)((uint64_t)(uint32_t)disp19 |(((1ULL << 18ULL)&(uint64_t)(uint32_t)disp19)?(18446744073709551615ULL - 524287ULL): 0ULL))<< 2U);
   input =(uint64_t)sval;
   return input;
}
static UNUSED u_machword reloc_input_d16lo(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t d16lo;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   d16lo = section_get32(snum, offset);
   d16lo =((d16lo >> 0U)& 16383U);
   input =(uint16_t)d16lo;
   return input;
}
static UNUSED u_machword reloc_input_imm22(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t imm22;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   imm22 = section_get32(snum, offset);
   imm22 =((imm22 >> 0U)& 4194303U);
   input =(uint32_t)imm22;
   return input;
}
static UNUSED u_machword reloc_input_simm13(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t simm13;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   simm13 = section_get32(snum, offset);
   simm13 =((simm13 >> 0U)& 8191U);
   signbits = 1U;
   if (!((simm13 &(signbits << 12))== 0U)) {
      signbits = 524287U;
      simm13 =(simm13 |(signbits << 13));
   }
   input =(int16_t)(int32_t)simm13;
   return input;
}
static UNUSED u_machword reloc_input_simm11(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t simm11;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   simm11 = section_get32(snum, offset);
   simm11 =((simm11 >> 0U)& 2047U);
   signbits = 1U;
   if (!((simm11 &(signbits << 10))== 0U)) {
      signbits = 2097151U;
      simm11 =(simm11 |(signbits << 11));
   }
   input =(int16_t)(int32_t)simm11;
   return input;
}
static UNUSED u_machword reloc_input_simm10(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t simm10;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   simm10 = section_get32(snum, offset);
   simm10 =((simm10 >> 0U)& 1023U);
   signbits = 1U;
   if (!((simm10 &(signbits << 9))== 0U)) {
      signbits = 4194303U;
      simm10 =(simm10 |(signbits << 10));
   }
   input =(int16_t)(int32_t)simm10;
   return input;
}
static UNUSED u_machword reloc_input_imm7(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t imm7;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   imm7 = section_get32(snum, offset);
   imm7 =((imm7 >> 0U)& 127U);
   signbits = 1U;
   if (!((imm7 &(signbits << 6))== 0U)) {
      signbits = 33554431U;
      imm7 =(imm7 |(signbits << 7));
   }
   input =(int8_t)(int32_t)imm7;
   return input;
}
static UNUSED u_machword reloc_input_imm6(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t imm6;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   imm6 = section_get32(snum, offset);
   imm6 =((imm6 >> 0U)& 63U);
   input =(uint8_t)imm6;
   return input;
}
static UNUSED u_machword reloc_input_imm5(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t imm5;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   imm5 = section_get32(snum, offset);
   imm5 =((imm5 >> 0U)& 31U);
   input =(uint8_t)imm5;
   return input;
}
static UNUSED u_machword reloc_input_data64(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint64_t data64;
   uint64_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   data64 = section_get64(snum, offset);
   input =(int64_t)data64;
   return input;
}
static UNUSED u_machword reloc_input_data32(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t data32;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   data32 = section_get32(snum, offset);
   input =(int32_t)data32;
   return input;
}
static UNUSED u_machword reloc_input_data16(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint16_t data16;
   uint16_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   data16 = section_get16(snum, offset);
   input =(int16_t)data16;
   return input;
}
static UNUSED u_machword reloc_input_data8(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint8_t data8;
   uint8_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   data8 = section_get8(snum, offset);
   input =(int8_t)data8;
   return input;
}
static UNUSED void reloc_output_disp30(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t disp30;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   int64_t tmp;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   if (((output & 3ULL)== 0ULL)) {
   }
   else{
      file_warn(linenum, "Requirement not met: ==(&(output :: uint(64)), (3 :: uint(64)) :: uint(64)), (0 :: uint(64)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/sparc64/relocs.def:30:10-40");
   }
   tmp =(int64_t)output;
   if ((!(536870911LL <(tmp >> 2U))&& !((tmp >> 2U)<(-536870911LL - 1)))) {
   }
   else{
      file_warn(linenum, "Requirement not met: (>>(tmp :: int(64)), (2 :: uint(8)) :: int(64) fits int(30)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/sparc64/relocs.def:32:10-44");
   }
   disp30 =(int32_t)(tmp >> 2U);
   if (!(!(536870911 <(int32_t)disp30)&& !((int32_t)disp30 <(-536870911 - 1)))) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %jd",(intmax_t)(int32_t)disp30);
      file_err(linenum, "Field is: disp30 :: int(30)");
   }
   ones = 1073741823U;
   disp30 =(disp30 & ones);
   prev = section_get32(snum, offset);
   disp30 =(disp30 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   disp30 =(prev | disp30);
   section_put32(snum, offset, disp30);
}
static UNUSED void reloc_output_disp22(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t disp22;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   int64_t tmp;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   if (((output & 3ULL)== 0ULL)) {
   }
   else{
      file_warn(linenum, "Requirement not met: ==(&(output :: uint(64)), (3 :: uint(64)) :: uint(64)), (0 :: uint(64)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/sparc64/relocs.def:42:10-40");
   }
   tmp =(int64_t)output;
   if ((!(2097151LL <(tmp >> 2U))&& !((tmp >> 2U)<(-2097151LL - 1)))) {
   }
   else{
      file_warn(linenum, "Requirement not met: (>>(tmp :: int(64)), (2 :: uint(8)) :: int(64) fits int(22)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/sparc64/relocs.def:44:10-44");
   }
   disp22 =(int32_t)(tmp >> 2U);
   if (!(!(2097151 <(int32_t)disp22)&& !((int32_t)disp22 <(-2097151 - 1)))) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %jd",(intmax_t)(int32_t)disp22);
      file_err(linenum, "Field is: disp22 :: int(22)");
   }
   ones = 4194303U;
   disp22 =(disp22 & ones);
   prev = section_get32(snum, offset);
   disp22 =(disp22 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   disp22 =(prev | disp22);
   section_put32(snum, offset, disp22);
}
static UNUSED void reloc_output_disp19(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t disp19;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   int64_t tmp;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   if (((output & 3ULL)== 0ULL)) {
   }
   else{
      file_warn(linenum, "Requirement not met: ==(&(output :: uint(64)), (3 :: uint(64)) :: uint(64)), (0 :: uint(64)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/sparc64/relocs.def:54:10-40");
   }
   tmp =(int64_t)output;
   if ((!(262143LL <(tmp >> 2U))&& !((tmp >> 2U)<(-262143LL - 1)))) {
   }
   else{
      file_warn(linenum, "Requirement not met: (>>(tmp :: int(64)), (2 :: uint(8)) :: int(64) fits int(19)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/sparc64/relocs.def:56:10-44");
   }
   disp19 =(int32_t)(tmp >> 2U);
   if (!(!(262143 <(int32_t)disp19)&& !((int32_t)disp19 <(-262143 - 1)))) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %jd",(intmax_t)(int32_t)disp19);
      file_err(linenum, "Field is: disp19 :: int(19)");
   }
   ones = 524287U;
   disp19 =(disp19 & ones);
   prev = section_get32(snum, offset);
   disp19 =(disp19 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   disp19 =(prev | disp19);
   section_put32(snum, offset, disp19);
}
static UNUSED void reloc_output_d16lo(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t d16lo;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   d16lo =(uint32_t)output;
   if (!!(16383U < d16lo)) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %ju",(uintmax_t)d16lo);
      file_err(linenum, "Field is: d16lo :: uint(14)");
   }
   ones = 16383U;
   d16lo =(d16lo & ones);
   prev = section_get32(snum, offset);
   d16lo =(d16lo << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   d16lo =(prev | d16lo);
   section_put32(snum, offset, d16lo);
}
static UNUSED void reloc_output_imm22(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t imm22;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   imm22 =(uint32_t)output;
   if (!!(4194303U < imm22)) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %ju",(uintmax_t)imm22);
      file_err(linenum, "Field is: imm22 :: uint(22)");
   }
   ones = 4194303U;
   imm22 =(imm22 & ones);
   prev = section_get32(snum, offset);
   imm22 =(imm22 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   imm22 =(prev | imm22);
   section_put32(snum, offset, imm22);
}
static UNUSED void reloc_output_simm13(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t simm13;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   simm13 =(uint32_t)(int32_t)output;
   if (!(!(4095 <(int32_t)simm13)&& !((int32_t)simm13 <(-4095 - 1)))) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %jd",(intmax_t)(int32_t)simm13);
      file_err(linenum, "Field is: simm13 :: int(13)");
   }
   ones = 8191U;
   simm13 =(simm13 & ones);
   prev = section_get32(snum, offset);
   simm13 =(simm13 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   simm13 =(prev | simm13);
   section_put32(snum, offset, simm13);
}
static UNUSED void reloc_output_simm11(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t simm11;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   simm11 =(uint32_t)(int32_t)output;
   if (!(!(1023 <(int32_t)simm11)&& !((int32_t)simm11 <(-1023 - 1)))) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %jd",(intmax_t)(int32_t)simm11);
      file_err(linenum, "Field is: simm11 :: int(11)");
   }
   ones = 2047U;
   simm11 =(simm11 & ones);
   prev = section_get32(snum, offset);
   simm11 =(simm11 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   simm11 =(prev | simm11);
   section_put32(snum, offset, simm11);
}
static UNUSED void reloc_output_simm10(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t simm10;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   simm10 =(uint32_t)(int32_t)output;
   if (!(!(511 <(int32_t)simm10)&& !((int32_t)simm10 <(-511 - 1)))) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %jd",(intmax_t)(int32_t)simm10);
      file_err(linenum, "Field is: simm10 :: int(10)");
   }
   ones = 1023U;
   simm10 =(simm10 & ones);
   prev = section_get32(snum, offset);
   simm10 =(simm10 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   simm10 =(prev | simm10);
   section_put32(snum, offset, simm10);
}
static UNUSED void reloc_output_imm7(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t imm7;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   imm7 =(uint32_t)(int32_t)output;
   if (!(!(63 <(int32_t)imm7)&& !((int32_t)imm7 <(-63 - 1)))) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %jd",(intmax_t)(int32_t)imm7);
      file_err(linenum, "Field is: imm7 :: int(7)");
   }
   ones = 127U;
   imm7 =(imm7 & ones);
   prev = section_get32(snum, offset);
   imm7 =(imm7 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   imm7 =(prev | imm7);
   section_put32(snum, offset, imm7);
}
static UNUSED void reloc_output_imm6(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t imm6;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   imm6 =(uint32_t)output;
   if (!!(63U < imm6)) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %ju",(uintmax_t)imm6);
      file_err(linenum, "Field is: imm6 :: uint(6)");
   }
   ones = 63U;
   imm6 =(imm6 & ones);
   prev = section_get32(snum, offset);
   imm6 =(imm6 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   imm6 =(prev | imm6);
   section_put32(snum, offset, imm6);
}
static UNUSED void reloc_output_imm5(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t imm5;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   imm5 =(uint32_t)output;
   if (!!(31U < imm5)) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %ju",(uintmax_t)imm5);
      file_err(linenum, "Field is: imm5 :: uint(5)");
   }
   ones = 31U;
   imm5 =(imm5 & ones);
   prev = section_get32(snum, offset);
   imm5 =(imm5 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   imm5 =(prev | imm5);
   section_put32(snum, offset, imm5);
}
static UNUSED void reloc_output_data64(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint64_t data64;
   uint64_t prev;
   uint64_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   data64 =(uint64_t)output;
   section_put64(snum, offset, data64);
}
static UNUSED void reloc_output_data32(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t data32;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   data32 =(uint32_t)output;
   section_put32(snum, offset, data32);
}
static UNUSED void reloc_output_data16(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint16_t data16;
   uint16_t prev;
   uint16_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   data16 =(uint16_t)output;
   section_put16(snum, offset, data16);
}
static UNUSED void reloc_output_data8(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint8_t data8;
   uint8_t prev;
   uint8_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   data8 =(uint8_t)output;
   section_put8(snum, offset, data8);
}
static UNUSED uint16_t modifier_lo(int linenum, uint64_t addr);
static UNUSED uint32_t modifier_hi(int linenum, uint64_t addr);
static UNUSED uint16_t modifier_ulo(int linenum, uint64_t addr);
static UNUSED uint32_t modifier_uhi(int linenum, uint64_t addr);
static UNUSED uint32_t modifier_h44(int linenum, uint64_t addr);
static UNUSED uint16_t modifier_m44(int linenum, uint64_t addr);
static UNUSED uint16_t modifier_l44(int linenum, uint64_t addr);
static UNUSED uint64_t modifier_got(int linenum, uint64_t addr);
static UNUSED uint64_t modifier_plt(int linenum, uint64_t addr);
static UNUSED uint16_t modifier_lo(int linenum, uint64_t addr) {
   uint16_t lo;
   
   (void)linenum;
   lo =(uint16_t)(addr & 1023ULL);
   return lo;
}
static UNUSED uint32_t modifier_hi(int linenum, uint64_t addr) {
   uint32_t hi;
   
   (void)linenum;
   hi =(uint32_t)((addr >> 10U)& 4194303ULL);
   return hi;
}
static UNUSED uint16_t modifier_ulo(int linenum, uint64_t addr) {
   uint16_t ulo;
   
   (void)linenum;
   ulo =(uint16_t)((addr >> 32U)& 1023ULL);
   return ulo;
}
static UNUSED uint32_t modifier_uhi(int linenum, uint64_t addr) {
   uint32_t uhi;
   
   (void)linenum;
   uhi =(uint32_t)((addr >> 42U)& 4194303ULL);
   return uhi;
}
static UNUSED uint32_t modifier_h44(int linenum, uint64_t addr) {
   uint32_t h44;
   
   (void)linenum;
   h44 =(uint32_t)((addr >> 22U)& 4398046511103ULL);
   return h44;
}
static UNUSED uint16_t modifier_m44(int linenum, uint64_t addr) {
   uint16_t m44;
   
   (void)linenum;
   m44 =(uint16_t)((addr >> 12U)& 1023ULL);
   return m44;
}
static UNUSED uint16_t modifier_l44(int linenum, uint64_t addr) {
   uint16_t l44;
   
   (void)linenum;
   l44 =(uint16_t)(addr & 4095ULL);
   return l44;
}
static UNUSED uint64_t modifier_got(int linenum, uint64_t addr) {
   uint64_t got;
   
   (void)linenum;
   got = addr;
   return got;
}
static UNUSED uint64_t modifier_plt(int linenum, uint64_t addr) {
   uint64_t plt;
   
   (void)linenum;
   plt = addr;
   return plt;
}
static void target_reloc_apply_directly(struct reloc * r, u_machword value) {
   int linenum;
   unsigned int snum;
   u_machword orig;
   linenum =(r -> r_linenum);
   snum =(r -> r_sectnum);
   switch((r -> r_field)) {
   case RELOC_FIELD_DISP30:{
      orig = reloc_input_disp30(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_disp30(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_DISP22:{
      orig = reloc_input_disp22(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_disp22(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_DISP19:{
      orig = reloc_input_disp19(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_disp19(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_D16LO:{
      orig = reloc_input_d16lo(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_d16lo(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_IMM22:{
      orig = reloc_input_imm22(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_imm22(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_SIMM13:{
      orig = reloc_input_simm13(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_simm13(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_SIMM11:{
      orig = reloc_input_simm11(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_simm11(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_SIMM10:{
      orig = reloc_input_simm10(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_simm10(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_IMM7:{
      orig = reloc_input_imm7(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_imm7(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_IMM6:{
      orig = reloc_input_imm6(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_imm6(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_IMM5:{
      orig = reloc_input_imm5(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_imm5(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_DATA64:{
      orig = reloc_input_data64(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_data64(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_DATA32:{
      orig = reloc_input_data32(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_data32(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_DATA16:{
      orig = reloc_input_data16(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_data16(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_DATA8:{
      orig = reloc_input_data8(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_data8(linenum, snum,(r -> r_offset), value);
      break;
   }
   default:{
      {
         assert(0);
         break;
      }
   }
   }
}
u_machword target_modifier_apply(int linenum, enum reloc_modifier m, u_machword value) {
   
   (void)linenum;
   switch(m) {
   case RELOC_MOD_NONE: break;
   case RELOC_MOD_LO:{
      value =(uint64_t)modifier_lo(linenum, value);
      break;
   }
   case RELOC_MOD_HI:{
      value =(uint64_t)modifier_hi(linenum, value);
      break;
   }
   case RELOC_MOD_ULO:{
      value =(uint64_t)modifier_ulo(linenum, value);
      break;
   }
   case RELOC_MOD_UHI:{
      value =(uint64_t)modifier_uhi(linenum, value);
      break;
   }
   case RELOC_MOD_H44:{
      value =(uint64_t)modifier_h44(linenum, value);
      break;
   }
   case RELOC_MOD_M44:{
      value =(uint64_t)modifier_m44(linenum, value);
      break;
   }
   case RELOC_MOD_L44:{
      value =(uint64_t)modifier_l44(linenum, value);
      break;
   }
   case RELOC_MOD_GOT:{
      value = modifier_got(linenum, value);
      break;
   }
   case RELOC_MOD_PLT:{
      value = modifier_plt(linenum, value);
      break;
   }
   }
   return value;
}
void target_reloc_apply(struct reloc * r, u_machword value) {
   int linenum;
   
   linenum =(r -> r_linenum);
   value = target_modifier_apply(linenum,(r -> r_modifier), value);
   target_reloc_apply_directly(r, value);
}
static int target_reloc_code_raw(struct reloc * r) {
   enum reloc_modifier mod;
   enum reloc_field rf;
   bool isrel;
   mod =(r -> r_modifier);
   rf =(r -> r_field);
   isrel = !((r -> r_sym2)== NULL);
   switch(mod) {
   case RELOC_MOD_NONE:{
      switch(rf) {
      case RELOC_FIELD_DISP30: if (isrel) {
         return R_SPARC_WDISP30;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP22: if (isrel) {
         return R_SPARC_WDISP22;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP19: if (isrel) {
         return R_SPARC_WDISP19;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_D16LO: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_SPARC_22;
      }
      case RELOC_FIELD_SIMM13: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_SPARC_13;
      }
      case RELOC_FIELD_SIMM11: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_SPARC_11;
      }
      case RELOC_FIELD_SIMM10: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_SPARC_10;
      }
      case RELOC_FIELD_IMM7: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_SPARC_7;
      }
      case RELOC_FIELD_IMM6: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_SPARC_6;
      }
      case RELOC_FIELD_IMM5: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_SPARC_5;
      }
      case RELOC_FIELD_DATA64: if (isrel) {
         return R_SPARC_DISP64;
      }
      else{
         return R_SPARC_64;
      }
      case RELOC_FIELD_DATA32: if (isrel) {
         return R_SPARC_DISP32;
      }
      else{
         return R_SPARC_32;
      }
      case RELOC_FIELD_DATA16: if (isrel) {
         return R_SPARC_DISP16;
      }
      else{
         return R_SPARC_16;
      }
      case RELOC_FIELD_DATA8: if (isrel) {
         return R_SPARC_DISP8;
      }
      else{
         return R_SPARC_8;
      }
      }
      break;
   }
   case RELOC_MOD_LO:{
      switch(rf) {
      case RELOC_FIELD_DISP30: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP19: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_D16LO: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM13: if (isrel) {
         return R_SPARC_PC10;
      }
      else{
         return R_SPARC_LO10;
      }
      case RELOC_FIELD_SIMM11: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM10: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM7: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM6: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM5: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA64: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA32: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA16: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA8: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      }
      break;
   }
   case RELOC_MOD_HI:{
      switch(rf) {
      case RELOC_FIELD_DISP30: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP19: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_D16LO: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM22: if (isrel) {
         return R_SPARC_PC22;
      }
      else{
         return R_SPARC_HI22;
      }
      case RELOC_FIELD_SIMM13: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM11: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM10: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM7: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM6: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM5: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA64: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA32: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA16: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA8: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      }
      break;
   }
   case RELOC_MOD_ULO:{
      switch(rf) {
      case RELOC_FIELD_DISP30: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP19: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_D16LO: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM13: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM11: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM10: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM7: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM6: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM5: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA64: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA32: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA16: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA8: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      }
      break;
   }
   case RELOC_MOD_UHI:{
      switch(rf) {
      case RELOC_FIELD_DISP30: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP19: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_D16LO: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM13: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM11: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM10: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM7: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM6: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM5: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA64: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA32: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA16: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA8: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      }
      break;
   }
   case RELOC_MOD_H44:{
      switch(rf) {
      case RELOC_FIELD_DISP30: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP19: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_D16LO: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_SPARC_H44;
      }
      case RELOC_FIELD_SIMM13: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM11: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM10: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM7: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM6: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM5: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA64: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA32: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA16: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA8: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      }
      break;
   }
   case RELOC_MOD_M44:{
      switch(rf) {
      case RELOC_FIELD_DISP30: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP19: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_D16LO: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM13: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_SPARC_M44;
      }
      case RELOC_FIELD_SIMM11: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_SPARC_M44;
      }
      case RELOC_FIELD_SIMM10: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_SPARC_M44;
      }
      case RELOC_FIELD_IMM7: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM6: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM5: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA64: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA32: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA16: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA8: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      }
      break;
   }
   case RELOC_MOD_L44:{
      switch(rf) {
      case RELOC_FIELD_DISP30: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP19: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_D16LO: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM13: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_SPARC_L44;
      }
      case RELOC_FIELD_SIMM11: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM10: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM7: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM6: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM5: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA64: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA32: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA16: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA8: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      }
      break;
   }
   case RELOC_MOD_GOT:{
      switch(rf) {
      case RELOC_FIELD_DISP30: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP19: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_D16LO: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM13: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM11: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM10: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM7: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM6: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM5: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA64: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA32: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA16: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA8: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      }
      break;
   }
   case RELOC_MOD_PLT:{
      switch(rf) {
      case RELOC_FIELD_DISP30: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DISP19: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_D16LO: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM22: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM13: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM11: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_SIMM10: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM7: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM6: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_IMM5: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA64: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA32: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA16: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_DATA8: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      }
      break;
   }
   }
   assert(0);
   return R_SPARC_NONE;
}
int target_reloc_code(struct reloc * r) {
   #ifdef TARGET_ELF_USE_REL
   return -target_reloc_code_raw(r);
   #else
   #ifdef TARGET_ELF_USE_RELA
   return target_reloc_code_raw(r);
   #else
   #error TARGET_ELF_USE_REL/RELA not set
   #endif
   #endif
}
void target_reloc_preoutput(struct reloc * r) {
   #ifdef TARGET_ELF_USE_REL
   target_reloc_apply_directly(r,(r -> r_addend));
   r->r_addend = 0;
   #else
   (void)r;
   #endif
}
