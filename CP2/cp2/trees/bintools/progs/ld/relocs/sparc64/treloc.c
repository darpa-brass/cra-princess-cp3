/* Automatically generated; do not edit */

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "common.h"

#include "elfreloc.h"

#include "section.h"
#include "outputrel.h"

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
   disp30 = section_fetch32(snum, offset);
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
   disp22 = section_fetch32(snum, offset);
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
   disp19 = section_fetch32(snum, offset);
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
   d16lo = section_fetch32(snum, offset);
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
   imm22 = section_fetch32(snum, offset);
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
   simm13 = section_fetch32(snum, offset);
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
   simm11 = section_fetch32(snum, offset);
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
   simm10 = section_fetch32(snum, offset);
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
   imm7 = section_fetch32(snum, offset);
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
   imm6 = section_fetch32(snum, offset);
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
   imm5 = section_fetch32(snum, offset);
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
   data64 = section_fetch64(snum, offset);
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
   data32 = section_fetch32(snum, offset);
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
   data16 = section_fetch16(snum, offset);
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
   data8 = section_fetch8(snum, offset);
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
   prev = section_fetch32(snum, offset);
   disp30 =(disp30 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   disp30 =(prev | disp30);
   section_store32(snum, offset, disp30);
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
   prev = section_fetch32(snum, offset);
   disp22 =(disp22 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   disp22 =(prev | disp22);
   section_store32(snum, offset, disp22);
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
   prev = section_fetch32(snum, offset);
   disp19 =(disp19 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   disp19 =(prev | disp19);
   section_store32(snum, offset, disp19);
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
   prev = section_fetch32(snum, offset);
   d16lo =(d16lo << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   d16lo =(prev | d16lo);
   section_store32(snum, offset, d16lo);
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
   prev = section_fetch32(snum, offset);
   imm22 =(imm22 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   imm22 =(prev | imm22);
   section_store32(snum, offset, imm22);
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
   prev = section_fetch32(snum, offset);
   simm13 =(simm13 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   simm13 =(prev | simm13);
   section_store32(snum, offset, simm13);
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
   prev = section_fetch32(snum, offset);
   simm11 =(simm11 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   simm11 =(prev | simm11);
   section_store32(snum, offset, simm11);
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
   prev = section_fetch32(snum, offset);
   simm10 =(simm10 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   simm10 =(prev | simm10);
   section_store32(snum, offset, simm10);
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
   prev = section_fetch32(snum, offset);
   imm7 =(imm7 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   imm7 =(prev | imm7);
   section_store32(snum, offset, imm7);
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
   prev = section_fetch32(snum, offset);
   imm6 =(imm6 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   imm6 =(prev | imm6);
   section_store32(snum, offset, imm6);
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
   prev = section_fetch32(snum, offset);
   imm5 =(imm5 << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   imm5 =(prev | imm5);
   section_store32(snum, offset, imm5);
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
   section_store64(snum, offset, data64);
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
   section_store32(snum, offset, data32);
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
   section_store16(snum, offset, data16);
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
   section_store8(snum, offset, data8);
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
static uint64_t reloc_compute_univ_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t univ_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   univ_absolute =(symbol + addend);
   return univ_absolute;
}
static uint64_t reloc_compute_univ_relative(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t univ_relative;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   univ_relative =((symbol + addend)- location);
   return univ_relative;
}
static uint64_t reloc_compute_hi20_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t hi20_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   hi20_absolute =((symbol + addend)>> 12U);
   return hi20_absolute;
}
static uint64_t reloc_compute_hi22_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint32_t hi22_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   hi22_absolute = modifier_hi(linenum,(symbol + addend));
   return hi22_absolute;
}
static uint64_t reloc_compute_hi22_relative(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint32_t hi22_relative;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   hi22_relative = modifier_hi(linenum,((symbol + addend)- location));
   return hi22_relative;
}
static uint64_t reloc_compute_lo10t_relative(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint16_t lo10t_relative;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   lo10t_relative = modifier_lo(linenum,((symbol + addend)- location));
   return lo10t_relative;
}
static uint64_t reloc_compute_lo10t_absolute2(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint16_t lo10t_absolute2;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   lo10t_absolute2 =(modifier_lo(linenum, symbol)+(uint16_t)addend);
   return lo10t_absolute2;
}
static uint64_t reloc_compute_h44_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint32_t h44_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   h44_absolute = modifier_h44(linenum,(symbol + addend));
   return h44_absolute;
}
static uint64_t reloc_compute_m44_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint16_t m44_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   m44_absolute = modifier_m44(linenum,(symbol + addend));
   return m44_absolute;
}
static uint64_t reloc_compute_l44_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint16_t l44_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   l44_absolute = modifier_l44(linenum,(symbol + addend));
   return l44_absolute;
}
static uint64_t reloc_compute_hihi22_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t hihi22_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   hihi22_absolute =((symbol + addend)>> 42U);
   return hihi22_absolute;
}
static uint64_t reloc_compute_hilo10_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t hilo10_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   hilo10_absolute =(((symbol + addend)>> 32U)& 1023ULL);
   return hilo10_absolute;
}
static uint64_t reloc_compute_lohi22_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t lohi22_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   lohi22_absolute =(((symbol + addend)>> 10U)& 4194303ULL);
   return lohi22_absolute;
}
static uint64_t reloc_compute_hihi22_relative(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t hihi22_relative;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   hihi22_relative =(((symbol + addend)- location)>> 42U);
   return hihi22_relative;
}
static uint64_t reloc_compute_hilo10_relative(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t hilo10_relative;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   hilo10_relative =((((symbol + addend)- location)>> 32U)& 1023ULL);
   return hilo10_relative;
}
static uint64_t reloc_compute_lohi22_relative(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t lohi22_relative;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   lohi22_relative =((((symbol + addend)- location)>> 10U)& 4194303ULL);
   return lohi22_relative;
}
static uint64_t reloc_compute_got10(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t got10;
   uint64_t index;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   if ((addend == 0ULL)) {
   }
   else{
      file_warn(linenum, "Requirement not met: ==(addend :: uint(64)), (0 :: uint(64)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/sparc64/relocs.def:125:7-29");
   }
   index = modifier_got(linenum, symbol);
   got10 =(index & 1023ULL);
   return got10;
}
static uint64_t reloc_compute_got13(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t got13;
   uint64_t index;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   if ((addend == 0ULL)) {
   }
   else{
      file_warn(linenum, "Requirement not met: ==(addend :: uint(64)), (0 :: uint(64)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/sparc64/relocs.def:130:7-29");
   }
   index = modifier_got(linenum, symbol);
   got13 = index;
   return got13;
}
static uint64_t reloc_compute_got22(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t got22;
   uint64_t index;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   if ((addend == 0ULL)) {
   }
   else{
      file_warn(linenum, "Requirement not met: ==(addend :: uint(64)), (0 :: uint(64)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/sparc64/relocs.def:135:7-29");
   }
   index = modifier_got(linenum, symbol);
   got22 =((index >> 10U)& 4194303ULL);
   return got22;
}
static uint64_t reloc_compute_plt64_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t index;
   uint64_t plt64_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   index = modifier_plt(linenum, symbol);
   plt64_absolute =(index + addend);
   return plt64_absolute;
}
static uint64_t reloc_compute_plt32_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t index;
   uint64_t plt32_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   index = modifier_plt(linenum, symbol);
   plt32_absolute =(index + addend);
   return plt32_absolute;
}
static uint64_t reloc_compute_plthi22_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t index;
   uint64_t plthi22_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   index = modifier_plt(linenum, symbol);
   plthi22_absolute =((index + addend)>> 10U);
   return plthi22_absolute;
}
static uint64_t reloc_compute_pltlo10_absolute(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t index;
   uint64_t pltlo10_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   index = modifier_plt(linenum, symbol);
   pltlo10_absolute =((index + addend)& 1023ULL);
   return pltlo10_absolute;
}
static uint64_t reloc_compute_plt32_relative(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t index;
   uint64_t plt32_relative;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   index = modifier_plt(linenum, symbol);
   plt32_relative =((index + addend)- location);
   return plt32_relative;
}
static uint64_t reloc_compute_plthi22_relative(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t index;
   uint64_t plthi22_relative;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   index = modifier_plt(linenum, symbol);
   plthi22_relative =(((index + addend)- location)>> 10U);
   return plthi22_relative;
}
static uint64_t reloc_compute_pltlo10_relative(int linenum, uint64_t symbol, uint64_t addend, uint64_t offset, uint64_t location) {
   uint64_t index;
   uint64_t pltlo10_relative;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   index = modifier_plt(linenum, symbol);
   pltlo10_relative =(((index + addend)- location)& 1023ULL);
   return pltlo10_relative;
}
void machdep_do_reloc(int code, unsigned int section, u_machword offset, u_machword symval, u_machword addend) {
   u_machword location;
   u_machword value;
   int linenum;
   location =(section_getbase(section)+ offset);
   linenum = 0;
   if ((code < 0)) {
      code = -code;
      switch(code) {
      case R_SPARC_NONE:{
         /*
          * nop
          */
         return;
      }
      case R_SPARC_8:{
         addend =(addend + reloc_input_data8(linenum, section, offset));
         break;
      }
      case R_SPARC_16:{
         addend =(addend + reloc_input_data16(linenum, section, offset));
         break;
      }
      case R_SPARC_32:{
         addend =(addend + reloc_input_data32(linenum, section, offset));
         break;
      }
      case R_SPARC_DISP8:{
         addend =(addend + reloc_input_data8(linenum, section, offset));
         break;
      }
      case R_SPARC_DISP16:{
         addend =(addend + reloc_input_data16(linenum, section, offset));
         break;
      }
      case R_SPARC_DISP32:{
         addend =(addend + reloc_input_data32(linenum, section, offset));
         break;
      }
      case R_SPARC_WDISP30:{
         addend =(addend + reloc_input_disp30(linenum, section, offset));
         break;
      }
      case R_SPARC_WDISP22:{
         addend =(addend + reloc_input_disp22(linenum, section, offset));
         break;
      }
      case R_SPARC_HI22:{
         addend =(addend + reloc_input_imm22(linenum, section, offset));
         break;
      }
      case R_SPARC_22:{
         addend =(addend + reloc_input_imm22(linenum, section, offset));
         break;
      }
      case R_SPARC_13:{
         addend =(addend + reloc_input_simm13(linenum, section, offset));
         break;
      }
      case R_SPARC_LO10:{
         addend =(addend + reloc_input_simm13(linenum, section, offset));
         break;
      }
      case R_SPARC_GOT10:{
         addend =(addend + reloc_input_simm13(linenum, section, offset));
         break;
      }
      case R_SPARC_GOT13:{
         addend =(addend + reloc_input_simm13(linenum, section, offset));
         break;
      }
      case R_SPARC_GOT22:{
         addend =(addend + reloc_input_imm22(linenum, section, offset));
         break;
      }
      case R_SPARC_PC10:{
         addend =(addend + reloc_input_simm13(linenum, section, offset));
         break;
      }
      case R_SPARC_PC22:{
         addend =(addend + reloc_input_imm22(linenum, section, offset));
         break;
      }
      case R_SPARC_WPLT30:{
         addend =(addend + reloc_input_disp30(linenum, section, offset));
         break;
      }
      case R_SPARC_COPY:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 19");
         break;
      }
      case R_SPARC_GLOB_DAT:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 20");
         break;
      }
      case R_SPARC_JMP_SLOT:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 21");
         break;
      }
      case R_SPARC_RELATIVE:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 22");
         break;
      }
      case R_SPARC_PLT32:{
         addend =(addend + reloc_input_data32(linenum, section, offset));
         break;
      }
      case R_SPARC_HIPLT22:{
         addend =(addend + reloc_input_imm22(linenum, section, offset));
         break;
      }
      case R_SPARC_LOPLT10:{
         addend =(addend + reloc_input_simm13(linenum, section, offset));
         break;
      }
      case R_SPARC_PCPLT32:{
         addend =(addend + reloc_input_data32(linenum, section, offset));
         break;
      }
      case R_SPARC_PCPLT22:{
         addend =(addend + reloc_input_imm22(linenum, section, offset));
         break;
      }
      case R_SPARC_PCPLT10:{
         addend =(addend + reloc_input_simm13(linenum, section, offset));
         break;
      }
      case R_SPARC_10:{
         addend =(addend + reloc_input_simm10(linenum, section, offset));
         break;
      }
      case R_SPARC_11:{
         addend =(addend + reloc_input_simm11(linenum, section, offset));
         break;
      }
      case R_SPARC_64:{
         addend =(addend + reloc_input_data64(linenum, section, offset));
         break;
      }
      case R_SPARC_OLO10:{
         addend =(addend + reloc_input_simm13(linenum, section, offset));
         break;
      }
      case R_SPARC_HH22:{
         addend =(addend + reloc_input_imm22(linenum, section, offset));
         break;
      }
      case R_SPARC_HM10:{
         addend =(addend + reloc_input_simm13(linenum, section, offset));
         break;
      }
      case R_SPARC_LM22:{
         addend =(addend + reloc_input_imm22(linenum, section, offset));
         break;
      }
      case R_SPARC_PC_HH22:{
         addend =(addend + reloc_input_imm22(linenum, section, offset));
         break;
      }
      case R_SPARC_PC_HM10:{
         addend =(addend + reloc_input_simm13(linenum, section, offset));
         break;
      }
      case R_SPARC_PC_LM22:{
         addend =(addend + reloc_input_imm22(linenum, section, offset));
         break;
      }
      case R_SPARC_WDISP16:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 40");
         break;
      }
      case R_SPARC_WDISP19:{
         addend =(addend + reloc_input_disp19(linenum, section, offset));
         break;
      }
      case R_SPARC_GLOB_JMP:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 42");
         break;
      }
      case R_SPARC_7:{
         addend =(addend + reloc_input_imm7(linenum, section, offset));
         break;
      }
      case R_SPARC_5:{
         addend =(addend + reloc_input_imm5(linenum, section, offset));
         break;
      }
      case R_SPARC_6:{
         addend =(addend + reloc_input_imm6(linenum, section, offset));
         break;
      }
      case R_SPARC_DISP64:{
         addend =(addend + reloc_input_data64(linenum, section, offset));
         break;
      }
      case R_SPARC_PLT64:{
         addend =(addend + reloc_input_data64(linenum, section, offset));
         break;
      }
      case R_SPARC_HIX22:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 48");
         break;
      }
      case R_SPARC_LOX10:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 49");
         break;
      }
      case R_SPARC_H44:{
         addend =(addend + reloc_input_imm22(linenum, section, offset));
         break;
      }
      case R_SPARC_M44:{
         addend =(addend + reloc_input_simm10(linenum, section, offset));
         break;
      }
      case R_SPARC_L44:{
         addend =(addend + reloc_input_simm13(linenum, section, offset));
         break;
      }
      case R_SPARC_REGISTER:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 53");
         break;
      }
      case R_SPARC_TLS_GD_HI22:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 56");
         break;
      }
      case R_SPARC_TLS_GD_LO10:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 57");
         break;
      }
      case R_SPARC_TLS_GD_ADD:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 58");
         break;
      }
      case R_SPARC_TLS_GD_CALL:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 59");
         break;
      }
      case R_SPARC_TLS_LDM_HI22:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 60");
         break;
      }
      case R_SPARC_TLS_LDM_LO10:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 61");
         break;
      }
      case R_SPARC_TLS_LDM_ADD:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 62");
         break;
      }
      case R_SPARC_TLS_LDM_CALL:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 63");
         break;
      }
      case R_SPARC_TLS_LDO_HIX22:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 64");
         break;
      }
      case R_SPARC_TLS_LDO_LOX10:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 65");
         break;
      }
      case R_SPARC_TLS_LDO_ADD:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 66");
         break;
      }
      case R_SPARC_TLS_IE_HI22:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 67");
         break;
      }
      case R_SPARC_TLS_IE_LO10:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 68");
         break;
      }
      case R_SPARC_TLS_IE_LD:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 69");
         break;
      }
      case R_SPARC_TLS_IE_LDX:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 70");
         break;
      }
      case R_SPARC_TLS_IE_ADD:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 71");
         break;
      }
      case R_SPARC_TLS_LE_HIX22:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 72");
         break;
      }
      case R_SPARC_TLS_LE_LOX10:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 73");
         break;
      }
      case R_SPARC_TLS_DTPMOD32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 74");
         break;
      }
      case R_SPARC_TLS_DTPMOD64:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 75");
         break;
      }
      case R_SPARC_TLS_DTPOFF32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 76");
         break;
      }
      case R_SPARC_TLS_DTPOFF64:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 77");
         break;
      }
      case R_SPARC_TLS_TPOFF32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 78");
         break;
      }
      case R_SPARC_TLS_TPOFF64:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 79");
         break;
      }
      case R_SPARC_GOTDATA_HIX22:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 80");
         break;
      }
      case R_SPARC_GOTDATA_LOX10:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 81");
         break;
      }
      case R_SPARC_GOTDATA_OP_HIX22:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 82");
         break;
      }
      case R_SPARC_GOTDATA_OP_LOX10:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 83");
         break;
      }
      case R_SPARC_GOTDATA_OP:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 84");
         break;
      }
      case R_SPARC_H34:{
         addend =(addend + reloc_input_imm22(linenum, section, offset));
         break;
      }
      case R_SPARC_SIZE32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 86");
         break;
      }
      case R_SPARC_SIZE64:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 87");
         break;
      }
      case R_SPARC_JMP_IREL:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 248");
         break;
      }
      case R_SPARC_IRELATIVE:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 249");
         break;
      }
      default:{
         {
            file_warn(linenum, "Unknown relocation code %d", code);
            file_err(linenum, "Fatal error, sorry");
         }
      }
      }
   }
   switch(code) {
   case R_SPARC_NONE:{
      /*
       * nop
       */
      return;
   }
   case R_SPARC_8:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_16:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_32:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_DISP8:{
      value = reloc_compute_univ_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_DISP16:{
      value = reloc_compute_univ_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_DISP32:{
      value = reloc_compute_univ_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_WDISP30:{
      value = reloc_compute_univ_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_WDISP22:{
      value = reloc_compute_univ_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_HI22:{
      value = reloc_compute_hi22_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_22:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_13:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_LO10:{
      value = reloc_compute_lo10t_absolute2(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_GOT10:{
      value = reloc_compute_got10(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_GOT13:{
      value = reloc_compute_got13(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_GOT22:{
      value = reloc_compute_got22(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_PC10:{
      value = reloc_compute_lo10t_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_PC22:{
      value = reloc_compute_hi22_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_WPLT30:{
      value = reloc_compute_plt64_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_COPY:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 19");
      break;
   }
   case R_SPARC_GLOB_DAT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 20");
      break;
   }
   case R_SPARC_JMP_SLOT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 21");
      break;
   }
   case R_SPARC_RELATIVE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 22");
      break;
   }
   case R_SPARC_PLT32:{
      value = reloc_compute_plt32_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_HIPLT22:{
      value = reloc_compute_plthi22_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_LOPLT10:{
      value = reloc_compute_pltlo10_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_PCPLT32:{
      value = reloc_compute_plt32_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_PCPLT22:{
      value = reloc_compute_plthi22_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_PCPLT10:{
      value = reloc_compute_pltlo10_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_10:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_11:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_64:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_OLO10:{
      value = reloc_compute_lo10t_absolute2(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_HH22:{
      value = reloc_compute_hihi22_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_HM10:{
      value = reloc_compute_hilo10_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_LM22:{
      value = reloc_compute_lohi22_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_PC_HH22:{
      value = reloc_compute_hihi22_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_PC_HM10:{
      value = reloc_compute_hilo10_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_PC_LM22:{
      value = reloc_compute_lohi22_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_WDISP16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 40");
      break;
   }
   case R_SPARC_WDISP19:{
      value = reloc_compute_univ_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_GLOB_JMP:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 42");
      break;
   }
   case R_SPARC_7:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_5:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_6:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_DISP64:{
      value = reloc_compute_univ_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_PLT64:{
      value = reloc_compute_plt64_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_HIX22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 48");
      break;
   }
   case R_SPARC_LOX10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 49");
      break;
   }
   case R_SPARC_H44:{
      value = reloc_compute_h44_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_M44:{
      value = reloc_compute_m44_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_L44:{
      value = reloc_compute_l44_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_REGISTER:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 53");
      break;
   }
   case R_SPARC_TLS_GD_HI22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 56");
      break;
   }
   case R_SPARC_TLS_GD_LO10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 57");
      break;
   }
   case R_SPARC_TLS_GD_ADD:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 58");
      break;
   }
   case R_SPARC_TLS_GD_CALL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 59");
      break;
   }
   case R_SPARC_TLS_LDM_HI22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 60");
      break;
   }
   case R_SPARC_TLS_LDM_LO10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 61");
      break;
   }
   case R_SPARC_TLS_LDM_ADD:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 62");
      break;
   }
   case R_SPARC_TLS_LDM_CALL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 63");
      break;
   }
   case R_SPARC_TLS_LDO_HIX22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 64");
      break;
   }
   case R_SPARC_TLS_LDO_LOX10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 65");
      break;
   }
   case R_SPARC_TLS_LDO_ADD:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 66");
      break;
   }
   case R_SPARC_TLS_IE_HI22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 67");
      break;
   }
   case R_SPARC_TLS_IE_LO10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 68");
      break;
   }
   case R_SPARC_TLS_IE_LD:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 69");
      break;
   }
   case R_SPARC_TLS_IE_LDX:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 70");
      break;
   }
   case R_SPARC_TLS_IE_ADD:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 71");
      break;
   }
   case R_SPARC_TLS_LE_HIX22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 72");
      break;
   }
   case R_SPARC_TLS_LE_LOX10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 73");
      break;
   }
   case R_SPARC_TLS_DTPMOD32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 74");
      break;
   }
   case R_SPARC_TLS_DTPMOD64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 75");
      break;
   }
   case R_SPARC_TLS_DTPOFF32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 76");
      break;
   }
   case R_SPARC_TLS_DTPOFF64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 77");
      break;
   }
   case R_SPARC_TLS_TPOFF32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 78");
      break;
   }
   case R_SPARC_TLS_TPOFF64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 79");
      break;
   }
   case R_SPARC_GOTDATA_HIX22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 80");
      break;
   }
   case R_SPARC_GOTDATA_LOX10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 81");
      break;
   }
   case R_SPARC_GOTDATA_OP_HIX22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 82");
      break;
   }
   case R_SPARC_GOTDATA_OP_LOX10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 83");
      break;
   }
   case R_SPARC_GOTDATA_OP:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 84");
      break;
   }
   case R_SPARC_H34:{
      value = reloc_compute_hi20_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_SPARC_SIZE32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 86");
      break;
   }
   case R_SPARC_SIZE64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 87");
      break;
   }
   case R_SPARC_JMP_IREL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 248");
      break;
   }
   case R_SPARC_IRELATIVE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 249");
      break;
   }
   default:{
      {
         file_warn(linenum, "Unknown relocation code %d", code);
         file_err(linenum, "Fatal error, sorry");
      }
   }
   }
   switch(code) {
   case R_SPARC_NONE:{
      /*
       * nop
       */
      return;
   }
   case R_SPARC_8:{
      reloc_output_data8(linenum, section, offset, value);
      break;
   }
   case R_SPARC_16:{
      reloc_output_data16(linenum, section, offset, value);
      break;
   }
   case R_SPARC_32:{
      reloc_output_data32(linenum, section, offset, value);
      break;
   }
   case R_SPARC_DISP8:{
      reloc_output_data8(linenum, section, offset, value);
      break;
   }
   case R_SPARC_DISP16:{
      reloc_output_data16(linenum, section, offset, value);
      break;
   }
   case R_SPARC_DISP32:{
      reloc_output_data32(linenum, section, offset, value);
      break;
   }
   case R_SPARC_WDISP30:{
      reloc_output_disp30(linenum, section, offset, value);
      break;
   }
   case R_SPARC_WDISP22:{
      reloc_output_disp22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_HI22:{
      reloc_output_imm22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_22:{
      reloc_output_imm22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_13:{
      reloc_output_simm13(linenum, section, offset, value);
      break;
   }
   case R_SPARC_LO10:{
      reloc_output_simm13(linenum, section, offset, value);
      break;
   }
   case R_SPARC_GOT10:{
      reloc_output_simm13(linenum, section, offset, value);
      break;
   }
   case R_SPARC_GOT13:{
      reloc_output_simm13(linenum, section, offset, value);
      break;
   }
   case R_SPARC_GOT22:{
      reloc_output_imm22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_PC10:{
      reloc_output_simm13(linenum, section, offset, value);
      break;
   }
   case R_SPARC_PC22:{
      reloc_output_imm22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_WPLT30:{
      reloc_output_disp30(linenum, section, offset, value);
      break;
   }
   case R_SPARC_COPY:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 19");
      break;
   }
   case R_SPARC_GLOB_DAT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 20");
      break;
   }
   case R_SPARC_JMP_SLOT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 21");
      break;
   }
   case R_SPARC_RELATIVE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 22");
      break;
   }
   case R_SPARC_PLT32:{
      reloc_output_data32(linenum, section, offset, value);
      break;
   }
   case R_SPARC_HIPLT22:{
      reloc_output_imm22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_LOPLT10:{
      reloc_output_simm13(linenum, section, offset, value);
      break;
   }
   case R_SPARC_PCPLT32:{
      reloc_output_data32(linenum, section, offset, value);
      break;
   }
   case R_SPARC_PCPLT22:{
      reloc_output_imm22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_PCPLT10:{
      reloc_output_simm13(linenum, section, offset, value);
      break;
   }
   case R_SPARC_10:{
      reloc_output_simm10(linenum, section, offset, value);
      break;
   }
   case R_SPARC_11:{
      reloc_output_simm11(linenum, section, offset, value);
      break;
   }
   case R_SPARC_64:{
      reloc_output_data64(linenum, section, offset, value);
      break;
   }
   case R_SPARC_OLO10:{
      reloc_output_simm13(linenum, section, offset, value);
      break;
   }
   case R_SPARC_HH22:{
      reloc_output_imm22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_HM10:{
      reloc_output_simm13(linenum, section, offset, value);
      break;
   }
   case R_SPARC_LM22:{
      reloc_output_imm22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_PC_HH22:{
      reloc_output_imm22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_PC_HM10:{
      reloc_output_simm13(linenum, section, offset, value);
      break;
   }
   case R_SPARC_PC_LM22:{
      reloc_output_imm22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_WDISP16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 40");
      break;
   }
   case R_SPARC_WDISP19:{
      reloc_output_disp19(linenum, section, offset, value);
      break;
   }
   case R_SPARC_GLOB_JMP:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 42");
      break;
   }
   case R_SPARC_7:{
      reloc_output_imm7(linenum, section, offset, value);
      break;
   }
   case R_SPARC_5:{
      reloc_output_imm5(linenum, section, offset, value);
      break;
   }
   case R_SPARC_6:{
      reloc_output_imm6(linenum, section, offset, value);
      break;
   }
   case R_SPARC_DISP64:{
      reloc_output_data64(linenum, section, offset, value);
      break;
   }
   case R_SPARC_PLT64:{
      reloc_output_data64(linenum, section, offset, value);
      break;
   }
   case R_SPARC_HIX22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 48");
      break;
   }
   case R_SPARC_LOX10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 49");
      break;
   }
   case R_SPARC_H44:{
      reloc_output_imm22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_M44:{
      reloc_output_simm10(linenum, section, offset, value);
      break;
   }
   case R_SPARC_L44:{
      reloc_output_simm13(linenum, section, offset, value);
      break;
   }
   case R_SPARC_REGISTER:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 53");
      break;
   }
   case R_SPARC_TLS_GD_HI22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 56");
      break;
   }
   case R_SPARC_TLS_GD_LO10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 57");
      break;
   }
   case R_SPARC_TLS_GD_ADD:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 58");
      break;
   }
   case R_SPARC_TLS_GD_CALL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 59");
      break;
   }
   case R_SPARC_TLS_LDM_HI22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 60");
      break;
   }
   case R_SPARC_TLS_LDM_LO10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 61");
      break;
   }
   case R_SPARC_TLS_LDM_ADD:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 62");
      break;
   }
   case R_SPARC_TLS_LDM_CALL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 63");
      break;
   }
   case R_SPARC_TLS_LDO_HIX22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 64");
      break;
   }
   case R_SPARC_TLS_LDO_LOX10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 65");
      break;
   }
   case R_SPARC_TLS_LDO_ADD:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 66");
      break;
   }
   case R_SPARC_TLS_IE_HI22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 67");
      break;
   }
   case R_SPARC_TLS_IE_LO10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 68");
      break;
   }
   case R_SPARC_TLS_IE_LD:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 69");
      break;
   }
   case R_SPARC_TLS_IE_LDX:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 70");
      break;
   }
   case R_SPARC_TLS_IE_ADD:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 71");
      break;
   }
   case R_SPARC_TLS_LE_HIX22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 72");
      break;
   }
   case R_SPARC_TLS_LE_LOX10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 73");
      break;
   }
   case R_SPARC_TLS_DTPMOD32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 74");
      break;
   }
   case R_SPARC_TLS_DTPMOD64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 75");
      break;
   }
   case R_SPARC_TLS_DTPOFF32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 76");
      break;
   }
   case R_SPARC_TLS_DTPOFF64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 77");
      break;
   }
   case R_SPARC_TLS_TPOFF32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 78");
      break;
   }
   case R_SPARC_TLS_TPOFF64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 79");
      break;
   }
   case R_SPARC_GOTDATA_HIX22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 80");
      break;
   }
   case R_SPARC_GOTDATA_LOX10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 81");
      break;
   }
   case R_SPARC_GOTDATA_OP_HIX22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 82");
      break;
   }
   case R_SPARC_GOTDATA_OP_LOX10:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 83");
      break;
   }
   case R_SPARC_GOTDATA_OP:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 84");
      break;
   }
   case R_SPARC_H34:{
      reloc_output_imm22(linenum, section, offset, value);
      break;
   }
   case R_SPARC_SIZE32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 86");
      break;
   }
   case R_SPARC_SIZE64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 87");
      break;
   }
   case R_SPARC_JMP_IREL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 248");
      break;
   }
   case R_SPARC_IRELATIVE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 249");
      break;
   }
   default:{
      {
         file_warn(linenum, "Unknown relocation code %d", code);
         file_err(linenum, "Fatal error, sorry");
      }
   }
   }
}
