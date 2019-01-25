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
   {
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
   }
   assert(0);
   return NULL;
}
const char * target_reloc_field_name(enum reloc_field rf) {
   switch(rf) {
   case RELOC_FIELD_BRANCHOFFSET: return "branchoffset";
   case RELOC_FIELD_LS_IMMEDIATE: return "ls_immediate";
   case RELOC_FIELD_DATA32: return "data32";
   case RELOC_FIELD_DATA16: return "data16";
   case RELOC_FIELD_DATA8: return "data8";
   case RELOC_FIELD_DP_ROTIMMHACK: return "dp_rotimmhack";
   }
   assert(0);
   return NULL;
}
static UNUSED u_machword reloc_input_branchoffset(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t branchoffset;
   uint32_t signbits;
   u_machword location;
   int32_t sval;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   branchoffset = section_get32(snum, offset);
   branchoffset =((branchoffset >> 0U)& 16777215U);
   signbits = 1U;
   if (!((branchoffset &(signbits << 23))== 0U)) {
      signbits = 255U;
      branchoffset =(branchoffset |(signbits << 24));
   }
   sval =((int32_t)((uint32_t)(uint32_t)branchoffset |(((1U << 23U)&(uint32_t)(uint32_t)branchoffset)?(4294967295U - 16777215U): 0U))<< 2U);
   input =(uint32_t)sval;
   return input;
}
static UNUSED u_machword reloc_input_ls_immediate(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t ls_immediate;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   ls_immediate = section_get32(snum, offset);
   ls_immediate =((ls_immediate >> 0U)& 4095U);
   input =(uint16_t)ls_immediate;
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
static UNUSED u_machword reloc_input_dp_rotimmhack(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t dp_rotimmhack;
   uint32_t signbits;
   u_machword location;
   uint8_t r;
   uint32_t vall;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   dp_rotimmhack = section_get32(snum, offset);
   dp_rotimmhack =((dp_rotimmhack >> 0U)& 4095U);
   r =(uint8_t)(dp_rotimmhack >> 8U);
   vall =(uint32_t)(dp_rotimmhack & 255U);
   input =(((vall >>(r % 2U))& 4294967295U)|((vall <<(32U -(r % 2U)))& 4294967295U));
   return input;
}
static UNUSED void reloc_output_branchoffset(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t branchoffset;
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
      file_err(linenum, "Requirement at: ../../../targets/arm/relocs.def:8:10-40");
   }
   tmp =(int32_t)output;
   if ((!(8388607 <(tmp >> 2U))&& !((tmp >> 2U)<(-8388607 - 1)))) {
   }
   else{
      file_warn(linenum, "Requirement not met: (>>(tmp :: int(32)), (2 :: uint(8)) :: int(32) fits int(24)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/arm/relocs.def:10:10-44");
   }
   branchoffset =(int32_t)(tmp >> 2U);
   if (!(!(8388607 <(int32_t)branchoffset)&& !((int32_t)branchoffset <(-8388607 - 1)))) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %jd",(intmax_t)(int32_t)branchoffset);
      file_err(linenum, "Field is: branchoffset :: int(24)");
   }
   ones = 16777215U;
   branchoffset =(branchoffset & ones);
   prev = section_get32(snum, offset);
   branchoffset =(branchoffset << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   branchoffset =(prev | branchoffset);
   section_put32(snum, offset, branchoffset);
}
static UNUSED void reloc_output_ls_immediate(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t ls_immediate;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   ls_immediate =(uint32_t)output;
   if (!!(4095U < ls_immediate)) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %ju",(uintmax_t)ls_immediate);
      file_err(linenum, "Field is: ls_immediate :: uint(12)");
   }
   ones = 4095U;
   ls_immediate =(ls_immediate & ones);
   prev = section_get32(snum, offset);
   ls_immediate =(ls_immediate << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   ls_immediate =(prev | ls_immediate);
   section_put32(snum, offset, ls_immediate);
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
static UNUSED void reloc_output_dp_rotimmhack(int linenum, unsigned int snum, u_machword offset, u_machword output) {
   uint32_t dp_rotimmhack;
   uint32_t prev;
   uint32_t ones;
   u_machword location;
   uint8_t r;
   uint8_t val;
   uint16_t wr;
   uint16_t wval;
   
   (void)linenum;
   (void)prev;
   (void)ones;
   location = offset;
   (void)location;
   r = 0U;
   val = 0U;
   r = modimm_hack_a(linenum, output);
   val = modimm_hack_b(linenum, output);
   wr =(uint16_t)r;
   wval =(uint16_t)val;
   dp_rotimmhack =((wr << 8U)| wval);
   if (!!(4095U < dp_rotimmhack)) {
      file_warn(linenum, "Value does not fit relocation field");
      file_warn(linenum, "Value is: %ju",(uintmax_t)dp_rotimmhack);
      file_err(linenum, "Field is: dp_rotimmhack :: uint(12)");
   }
   ones = 4095U;
   dp_rotimmhack =(dp_rotimmhack & ones);
   prev = section_get32(snum, offset);
   dp_rotimmhack =(dp_rotimmhack << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   dp_rotimmhack =(prev | dp_rotimmhack);
   section_put32(snum, offset, dp_rotimmhack);
}
static void target_reloc_apply_directly(struct reloc * r, u_machword value) {
   int linenum;
   unsigned int snum;
   u_machword orig;
   linenum =(r -> r_linenum);
   snum =(r -> r_sectnum);
   switch((r -> r_field)) {
   case RELOC_FIELD_BRANCHOFFSET:{
      orig = reloc_input_branchoffset(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_branchoffset(linenum, snum,(r -> r_offset), value);
      break;
   }
   case RELOC_FIELD_LS_IMMEDIATE:{
      orig = reloc_input_ls_immediate(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_ls_immediate(linenum, snum,(r -> r_offset), value);
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
   case RELOC_FIELD_DP_ROTIMMHACK:{
      orig = reloc_input_dp_rotimmhack(linenum, snum,(r -> r_offset));
      assert((orig == 0));
      reloc_output_dp_rotimmhack(linenum, snum,(r -> r_offset), value);
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
      case RELOC_FIELD_BRANCHOFFSET: if (isrel) {
         return R_ARM_JUMP24;
      }
      else{
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      case RELOC_FIELD_LS_IMMEDIATE: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_ARM_ABS12;
      }
      case RELOC_FIELD_DATA32: if (isrel) {
         return R_ARM_REL32;
      }
      else{
         return R_ARM_ABS32;
      }
      case RELOC_FIELD_DATA16: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_ARM_ABS16;
      }
      case RELOC_FIELD_DATA8: if (isrel) {
         file_err((r -> r_linenum), "Cannot encode relocation in output");
         break;
      }
      else{
         return R_ARM_ABS8;
      }
      case RELOC_FIELD_DP_ROTIMMHACK: if (isrel) {
         return R_ARM_PRIVATE_ROTIMMHACK;
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
   return R_ARM_PRIVATE_ROTIMMHACK;
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
