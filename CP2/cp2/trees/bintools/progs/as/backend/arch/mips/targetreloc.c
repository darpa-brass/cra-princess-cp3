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
   if (!strcmp(name, "hi"))return RELOC_MOD_HI;
   else if (!strcmp(name, "lo"))return RELOC_MOD_LO;
   else if (!strcmp(name, "branchoffset"))return RELOC_MOD_BRANCHOFFSET;
   else if (!strcmp(name, "got"))return RELOC_MOD_GOT;
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
   case RELOC_MOD_HI: return "%hi";
   case RELOC_MOD_LO: return "%lo";
   case RELOC_MOD_BRANCHOFFSET: return "%branchoffset";
   case RELOC_MOD_GOT: return "%got";
   }
   assert(0);
   return NULL;
}
const char * target_reloc_field_name(enum reloc_field rf) {
   switch(rf) {
   case RELOC_FIELD_IMM: return "imm";
   case RELOC_FIELD_UIMM: return "uimm";
   case RELOC_FIELD_BRANCHTARGET: return "branchtarget";
   case RELOC_FIELD_JUMPTARGET: return "jumptarget";
   case RELOC_FIELD_DATA32: return "data32";
   case RELOC_FIELD_DATA16: return "data16";
   }
   assert(0);
   return NULL;
}
static UNUSED u_machword reloc_input_imm(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t imm;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   imm = section_get32(snum, offset);
   imm =((imm >> 0U)& 65535U);
   signbits = 1U;
   if (!((imm &(signbits << 15))== 0U)) {
      signbits = 65535U;
      imm =(imm |(signbits << 16));
   }
   input =(int16_t)(int32_t)imm;
   return input;
}
static UNUSED u_machword reloc_input_uimm(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t uimm;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   uimm = section_get32(snum, offset);
   uimm =((uimm >> 0U)& 65535U);
   input =(uint16_t)uimm;
   return input;
}
static UNUSED u_machword reloc_input_branchtarget(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t branchtarget;
   uint32_t signbits;
   u_machword location;
   int32_t val;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   branchtarget = section_get32(snum, offset);
   branchtarget =((branchtarget >> 0U)& 65535U);
   signbits = 1U;
   if (!((branchtarget &(signbits << 15))== 0U)) {
      signbits = 65535U;
      branchtarget =(branchtarget |(signbits << 16));
   }
   val =((int32_t)((uint32_t)(uint16_t)branchtarget |(((1U << 15U)&(uint32_t)(uint16_t)branchtarget)?(4294967295U - 65535U): 0U))<< 2U);
   input =(uint32_t)val;
   return input;
}
static UNUSED u_machword reloc_input_jumptarget(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t jumptarget;
   uint32_t signbits;
   u_machword location;
   uint32_t tmp;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   jumptarget = section_get32(snum, offset);
   jumptarget =((jumptarget >> 0U)& 67108863U);
   tmp =((uint32_t)jumptarget << 2U);
   input =((location & 4026531840U)| tmp);
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
   input = data32;
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
static UNUSED void reloc_output_imm(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t imm;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   imm =(uint32_t)(int32_t)output;
   if (!(!(32767 <(int32_t)imm)&& !((int32_t)imm <(-32767 - 1)))) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %jd",(intmax_t)(int32_t)imm);
      file_err(linenum, "Field is: imm :: int(16)");
   }
   ones = 65535U;
   imm =(imm & ones);
   prev = section_get32(snum, offset);
   imm =(imm << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   imm =(prev | imm);
   section_put32(snum, offset, imm);
}
static UNUSED void reloc_output_uimm(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t uimm;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   uimm =(uint32_t)output;
   if (!!(65535U < uimm)) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %ju",(uintmax_t)uimm);
      file_err(linenum, "Field is: uimm :: uint(16)");
   }
   ones = 65535U;
   uimm =(uimm & ones);
   prev = section_get32(snum, offset);
   uimm =(uimm << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   uimm =(prev | uimm);
   section_put32(snum, offset, uimm);
}
static UNUSED void reloc_output_branchtarget(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t branchtarget;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   int32_t tmp;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   if (((output & 3U)== 0U)) {
   }
   else{
      file_warn(linenum, "Requirement not met: ==(&(output :: uint(32)), (3 :: uint(32)) :: uint(32)), (0 :: uint(32)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/mips/relocs.def:78:3-33");
   }
   tmp =(int32_t)output;
   if ((!(32767 <(tmp >> 2U))&& !((tmp >> 2U)<(-32767 - 1)))) {
   }
   else{
      file_warn(linenum, "Requirement not met: (>>(tmp :: int(32)), (2 :: uint(8)) :: int(32) fits int(16)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/mips/relocs.def:80:3-37");
   }
   branchtarget =(int16_t)(tmp >> 2U);
   if (!(!(32767 <(int32_t)branchtarget)&& !((int32_t)branchtarget <(-32767 - 1)))) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %jd",(intmax_t)(int32_t)branchtarget);
      file_err(linenum, "Field is: branchtarget :: int(16)");
   }
   ones = 65535U;
   branchtarget =(branchtarget & ones);
   prev = section_get32(snum, offset);
   branchtarget =(branchtarget << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   branchtarget =(prev | branchtarget);
   section_put32(snum, offset, branchtarget);
}
static UNUSED void reloc_output_jumptarget(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t jumptarget;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   uint32_t tmp;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   if (((output & 4026531840U)==(location & 4026531840U))) {
   }
   else{
      file_warn(linenum, "Requirement not met: ==(&(output :: uint(32)), (4026531840 :: uint(32)) :: uint(32)), (&(location :: uint(32)), (4026531840 :: uint(32)) :: uint(32)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/mips/relocs.def:90:3-91:36");
   }
   if (((output & 3U)== 0U)) {
   }
   else{
      file_warn(linenum, "Requirement not met: ==(&(output :: uint(32)), (3 :: uint(32)) :: uint(32)), (0 :: uint(32)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/mips/relocs.def:92:3-32");
   }
   tmp =((output & 268435452U)>> 2U);
   jumptarget =(uint32_t)tmp;
   if (!!(67108863U < jumptarget)) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %ju",(uintmax_t)jumptarget);
      file_err(linenum, "Field is: jumptarget :: uint(26)");
   }
   ones = 67108863U;
   jumptarget =(jumptarget & ones);
   prev = section_get32(snum, offset);
   jumptarget =(jumptarget << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   jumptarget =(prev | jumptarget);
   section_put32(snum, offset, jumptarget);
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
   data32 = output;
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
static UNUSED uint16_t modifier_hi(int linenum, uint32_t addr);
static UNUSED int16_t modifier_lo(int linenum, uint32_t addr);
static UNUSED int16_t modifier_branchoffset(int linenum, uint32_t offset);
static UNUSED uint32_t modifier_got(int linenum, uint32_t addr);
static UNUSED uint16_t modifier_hi(int linenum, uint32_t addr) {
   uint16_t hi;
   
   (void)linenum;
   hi =((addr -(uint32_t)(int32_t)((uint32_t)(uint16_t)modifier_lo(linenum, addr)|(((1U << 15U)&(uint32_t)(uint16_t)modifier_lo(linenum, addr))?(4294967295U - 65535U): 0U)))>> 16U);
   return hi;
}
static UNUSED int16_t modifier_lo(int linenum, uint32_t addr) {
   int16_t lo;
   
   (void)linenum;
   lo =(int16_t)(uint16_t)addr;
   return lo;
}
static UNUSED int16_t modifier_branchoffset(int linenum, uint32_t offset) {
   int16_t branchoffset;
   int32_t offset32;
   
   (void)linenum;
   if (((offset & 3U)== 0U)) {
   }
   else{
      file_warn(linenum, "Requirement not met: ==(&(offset :: uint(32)), (3 :: uint(32)) :: uint(32)), (0 :: uint(32)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/mips/relocs.def:110:12-40");
   }
   offset32 =((int32_t)offset >> 2U);
   if ((!(32767 < offset32)&& !(offset32 <(-32767 - 1)))) {
   }
   else{
      file_warn(linenum, "Requirement not met: (offset32 :: int(32) fits int(16)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/mips/relocs.def:112:12-44");
   }
   branchoffset = offset;
   return branchoffset;
}
static UNUSED uint32_t modifier_got(int linenum, uint32_t addr) {
   uint32_t got;
   
   (void)linenum;
   got = addr;
   return got;
}
static void target_reloc_apply_directly(struct reloc * r, u_machword value) {
   int linenum;
   unsigned int snum;
   u_machword orig;
   linenum =(r -> r_linenum);
   snum =(r -> r_sectnum);
   switch((r -> r_field)) {
   case RELOC_FIELD_IMM:{
      orig = reloc_input_imm(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_imm(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_UIMM:{
      orig = reloc_input_uimm(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_uimm(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_BRANCHTARGET:{
      orig = reloc_input_branchtarget(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_branchtarget(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_JUMPTARGET:{
      orig = reloc_input_jumptarget(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_jumptarget(linenum, snum,(r -> r_offset), value);
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
   case RELOC_MOD_HI:{
      value =(uint32_t)modifier_hi(linenum, value);
      break;
   }
   case RELOC_MOD_LO:{
      value =(uint32_t)(int32_t)modifier_lo(linenum, value);
      break;
   }
   case RELOC_MOD_BRANCHOFFSET:{
      value =(uint32_t)(int32_t)modifier_branchoffset(linenum, value);
      break;
   }
   case RELOC_MOD_GOT:{
      value = modifier_got(linenum, value);
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
      case RELOC_FIELD_IMM: if (isrel) {
         return R_MIPS_PC16;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_UIMM: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_BRANCHTARGET: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_JUMPTARGET: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_MIPS_26;
      }
      case RELOC_FIELD_DATA32: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_MIPS_32;
      }
      case RELOC_FIELD_DATA16: if (isrel) {
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
      case RELOC_FIELD_IMM: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_UIMM: if (isrel) {
         return R_MIPS_HI16_GPDISP;
      }
      else{
         return R_MIPS_HI16;
      }
      case RELOC_FIELD_BRANCHTARGET: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_JUMPTARGET: if (isrel) {
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
      }
      break;
   }
   case RELOC_MOD_LO:{
      switch(rf) {
      case RELOC_FIELD_IMM: if (isrel) {
         return R_MIPS_LO16_GPDISP;
      }
      else{
         return R_MIPS_LO16;
      }
      case RELOC_FIELD_UIMM: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_BRANCHTARGET: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_JUMPTARGET: if (isrel) {
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
      }
      break;
   }
   case RELOC_MOD_BRANCHOFFSET:{
      switch(rf) {
      case RELOC_FIELD_IMM: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_UIMM: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_BRANCHTARGET: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_JUMPTARGET: if (isrel) {
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
      }
      break;
   }
   case RELOC_MOD_GOT:{
      switch(rf) {
      case RELOC_FIELD_IMM: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_UIMM: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_BRANCHTARGET: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_JUMPTARGET: if (isrel) {
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
      }
      break;
   }
   }
   assert(0);
   return R_MIPS_NONE;
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
