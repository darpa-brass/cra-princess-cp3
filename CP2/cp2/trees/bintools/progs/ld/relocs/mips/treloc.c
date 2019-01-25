/* Automatically generated; do not edit */

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "common.h"

#include "elfreloc.h"

#include "section.h"
#include "outputrel.h"

static UNUSED u_machword reloc_input_imm(int linenum, unsigned int snum, u_machword offset) {
   u_machword input;
   uint32_t imm;
   uint32_t signbits;
   u_machword location;
   
   (void)linenum;
   (void)signbits;
   location = offset;
   (void)location;
   imm = section_fetch32(snum, offset);
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
   uimm = section_fetch32(snum, offset);
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
   branchtarget = section_fetch32(snum, offset);
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
   jumptarget = section_fetch32(snum, offset);
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
   data32 = section_fetch32(snum, offset);
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
   data16 = section_fetch16(snum, offset);
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
   prev = section_fetch32(snum, offset);
   imm =(imm << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   imm =(prev | imm);
   section_store32(snum, offset, imm);
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
   prev = section_fetch32(snum, offset);
   uimm =(uimm << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   uimm =(prev | uimm);
   section_store32(snum, offset, uimm);
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
   prev = section_fetch32(snum, offset);
   branchtarget =(branchtarget << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   branchtarget =(prev | branchtarget);
   section_store32(snum, offset, branchtarget);
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
   prev = section_fetch32(snum, offset);
   jumptarget =(jumptarget << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   jumptarget =(prev | jumptarget);
   section_store32(snum, offset, jumptarget);
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
static uint32_t reloc_compute_univ_absolute(int linenum, uint32_t symbol, uint32_t addend, uint32_t offset, uint32_t location) {
   uint32_t univ_absolute;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   univ_absolute =(symbol + addend);
   return univ_absolute;
}
static uint32_t reloc_compute_univ_relative(int linenum, uint32_t symbol, uint32_t addend, uint32_t offset, uint32_t location) {
   uint32_t univ_relative;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   univ_relative =((symbol + addend)- location);
   return univ_relative;
}
static uint32_t reloc_compute_absolute16(int linenum, uint32_t symbol, uint32_t addend, uint32_t offset, uint32_t location) {
   uint32_t absolute16;
   uint32_t addr;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   addr =(symbol + addend);
   if ((!(!(32767 <(int32_t)symbol)&& !((int32_t)symbol <(-32767 - 1)))&& !(!(32767 <(int32_t)addr)&& !((int32_t)addr <(-32767 - 1))))) {
      {
         file_warn(linenum, "32-bit value truncated into 16-bit field");
      }
   }
   else{
      {
      }
   }
   absolute16 = addr;
   return absolute16;
}
static uint32_t reloc_compute_hi16(int linenum, uint32_t symbol, uint32_t addend, uint32_t offset, uint32_t location) {
   uint16_t hi16;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   hi16 = modifier_hi(linenum,(symbol + addend));
   return hi16;
}
static uint32_t reloc_compute_lo16(int linenum, uint32_t symbol, uint32_t addend, uint32_t offset, uint32_t location) {
   int16_t lo16;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   lo16 = modifier_lo(linenum,(symbol + addend));
   return lo16;
}
static uint32_t reloc_compute_hi16rel(int linenum, uint32_t symbol, uint32_t addend, uint32_t offset, uint32_t location) {
   uint16_t hi16rel;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   hi16rel = modifier_hi(linenum,((symbol + addend)- location));
   return hi16rel;
}
static uint32_t reloc_compute_lo16rel(int linenum, uint32_t symbol, uint32_t addend, uint32_t offset, uint32_t location) {
   int16_t lo16rel;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   lo16rel = modifier_lo(linenum,((symbol + addend)- location));
   return lo16rel;
}
static uint32_t reloc_compute_got16(int linenum, uint32_t symbol, uint32_t addend, uint32_t offset, uint32_t location) {
   int16_t got16;
   uint32_t index;
   int32_t sindex;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   if ((addend == 0U)) {
   }
   else{
      file_warn(linenum, "Requirement not met: ==(addend :: uint(32)), (0 :: uint(32)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/mips/relocs.def:148:3-25");
   }
   index = modifier_got(linenum, symbol);
   sindex =(int32_t)index;
   if ((!(32767 < sindex)&& !(sindex <(-32767 - 1)))) {
   }
   else{
      file_warn(linenum, "Requirement not met: (sindex :: int(32) fits int(16)) :: bool");
      file_err(linenum, "Requirement at: ../../../targets/mips/relocs.def:151:3-33");
   }
   got16 =(int16_t)sindex;
   return got16;
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
      case R_MIPS_NONE:{
         /*
          * nop
          */
         return;
      }
      case R_MIPS_16:{
         addend =(addend + reloc_input_data16(linenum, section, offset));
         break;
      }
      case R_MIPS_32:{
         addend =(addend + reloc_input_data32(linenum, section, offset));
         break;
      }
      case R_MIPS_26:{
         addend =(addend + reloc_input_jumptarget(linenum, section, offset));
         break;
      }
      case R_MIPS_HI16:{
         addend =(addend + reloc_input_uimm(linenum, section, offset));
         break;
      }
      case R_MIPS_LO16:{
         addend =(addend + reloc_input_imm(linenum, section, offset));
         break;
      }
      case R_MIPS_HI16_GPDISP:{
         addend =(addend + reloc_input_uimm(linenum, section, offset));
         break;
      }
      case R_MIPS_LO16_GPDISP:{
         addend =(addend + reloc_input_imm(linenum, section, offset));
         break;
      }
      case R_MIPS_GOT16:{
         addend =(addend + reloc_input_imm(linenum, section, offset));
         break;
      }
      case R_MIPS_PC16:{
         addend =(addend + reloc_input_imm(linenum, section, offset));
         break;
      }
      case R_MIPS_CALL16:{
         addend =(addend + reloc_input_imm(linenum, section, offset));
         break;
      }
      case R_MIPS_64:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 16");
         break;
      }
      case R_MIPS_SHIFT5:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 17");
         break;
      }
      case R_MIPS_SHIFT6:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 18");
         break;
      }
      case R_MIPS_GOT_DISP:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 19");
         break;
      }
      case R_MIPS_GOT_PAGE:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 20");
         break;
      }
      case R_MIPS_GOT_OFST:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 21");
         break;
      }
      case R_MIPS_SUB:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 24");
         break;
      }
      case R_MIPS_INSERT_A:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 25");
         break;
      }
      case R_MIPS_INSERT_B:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 26");
         break;
      }
      case R_MIPS_DELETE:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 27");
         break;
      }
      case R_MIPS_HIGHER:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 28");
         break;
      }
      case R_MIPS_HIGHEST:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 29");
         break;
      }
      case R_MIPS_SCN_DISP:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 32");
         break;
      }
      case R_MIPS_REL16:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 33");
         break;
      }
      case R_MIPS_ADD_IMMEDIATE:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 34");
         break;
      }
      case R_MIPS_PJUMP:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 35");
         break;
      }
      case R_MIPS_ADD_RELGOT:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 36");
         break;
      }
      case R_MIPS_JALR:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 37");
         break;
      }
      case R_MIPS_DTPMOD32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 38");
         break;
      }
      case R_MIPS_DTPREL32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 39");
         break;
      }
      case R_MIPS_DTPMOD64:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 40");
         break;
      }
      case R_MIPS_DTPREL64:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 41");
         break;
      }
      case R_MIPS_GD:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 42");
         break;
      }
      case R_MIPS_LDM:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 43");
         break;
      }
      case R_MIPS_DTPREL_HI16:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 44");
         break;
      }
      case R_MIPS_DTPREL_LO16:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 45");
         break;
      }
      case R_MIPS_GOTTPREL:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 46");
         break;
      }
      case R_MIPS_TPREL32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 47");
         break;
      }
      case R_MIPS_GPREL64:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 48");
         break;
      }
      case R_MIPS_TPREL_HI16:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 49");
         break;
      }
      case R_MIPS_TPREL_LO16:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 50");
         break;
      }
      case R_MIPS16_26:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 100");
         break;
      }
      case R_MIPS16_GPREL:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 101");
         break;
      }
      case R_MIPS16_GOT16:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 102");
         break;
      }
      case R_MIPS16_CALL16:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 103");
         break;
      }
      case R_MIPS16_HI16:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 104");
         break;
      }
      case R_MIPS16_LO16:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 105");
         break;
      }
      case R_MIPS16_COPY:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 126");
         break;
      }
      case R_MIPS16_JUMP_SLOT:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 127");
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
   case R_MIPS_NONE:{
      /*
       * nop
       */
      return;
   }
   case R_MIPS_16:{
      value = reloc_compute_absolute16(linenum, symval, addend, offset, location);
      break;
   }
   case R_MIPS_32:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_MIPS_26:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_MIPS_HI16:{
      value = reloc_compute_hi16(linenum, symval, addend, offset, location);
      break;
   }
   case R_MIPS_LO16:{
      value = reloc_compute_lo16(linenum, symval, addend, offset, location);
      break;
   }
   case R_MIPS_HI16_GPDISP:{
      value = reloc_compute_hi16rel(linenum, symval, addend, offset, location);
      break;
   }
   case R_MIPS_LO16_GPDISP:{
      value = reloc_compute_lo16rel(linenum, symval, addend, offset, location);
      break;
   }
   case R_MIPS_GOT16:{
      value = reloc_compute_got16(linenum, symval, addend, offset, location);
      break;
   }
   case R_MIPS_PC16:{
      value = reloc_compute_univ_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_MIPS_CALL16:{
      value = reloc_compute_got16(linenum, symval, addend, offset, location);
      break;
   }
   case R_MIPS_64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 16");
      break;
   }
   case R_MIPS_SHIFT5:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 17");
      break;
   }
   case R_MIPS_SHIFT6:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 18");
      break;
   }
   case R_MIPS_GOT_DISP:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 19");
      break;
   }
   case R_MIPS_GOT_PAGE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 20");
      break;
   }
   case R_MIPS_GOT_OFST:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 21");
      break;
   }
   case R_MIPS_SUB:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 24");
      break;
   }
   case R_MIPS_INSERT_A:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 25");
      break;
   }
   case R_MIPS_INSERT_B:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 26");
      break;
   }
   case R_MIPS_DELETE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 27");
      break;
   }
   case R_MIPS_HIGHER:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 28");
      break;
   }
   case R_MIPS_HIGHEST:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 29");
      break;
   }
   case R_MIPS_SCN_DISP:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 32");
      break;
   }
   case R_MIPS_REL16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 33");
      break;
   }
   case R_MIPS_ADD_IMMEDIATE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 34");
      break;
   }
   case R_MIPS_PJUMP:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 35");
      break;
   }
   case R_MIPS_ADD_RELGOT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 36");
      break;
   }
   case R_MIPS_JALR:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 37");
      break;
   }
   case R_MIPS_DTPMOD32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 38");
      break;
   }
   case R_MIPS_DTPREL32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 39");
      break;
   }
   case R_MIPS_DTPMOD64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 40");
      break;
   }
   case R_MIPS_DTPREL64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 41");
      break;
   }
   case R_MIPS_GD:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 42");
      break;
   }
   case R_MIPS_LDM:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 43");
      break;
   }
   case R_MIPS_DTPREL_HI16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 44");
      break;
   }
   case R_MIPS_DTPREL_LO16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 45");
      break;
   }
   case R_MIPS_GOTTPREL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 46");
      break;
   }
   case R_MIPS_TPREL32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 47");
      break;
   }
   case R_MIPS_GPREL64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 48");
      break;
   }
   case R_MIPS_TPREL_HI16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 49");
      break;
   }
   case R_MIPS_TPREL_LO16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 50");
      break;
   }
   case R_MIPS16_26:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 100");
      break;
   }
   case R_MIPS16_GPREL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 101");
      break;
   }
   case R_MIPS16_GOT16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 102");
      break;
   }
   case R_MIPS16_CALL16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 103");
      break;
   }
   case R_MIPS16_HI16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 104");
      break;
   }
   case R_MIPS16_LO16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 105");
      break;
   }
   case R_MIPS16_COPY:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 126");
      break;
   }
   case R_MIPS16_JUMP_SLOT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 127");
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
   case R_MIPS_NONE:{
      /*
       * nop
       */
      return;
   }
   case R_MIPS_16:{
      reloc_output_data16(linenum, section, offset, value);
      break;
   }
   case R_MIPS_32:{
      reloc_output_data32(linenum, section, offset, value);
      break;
   }
   case R_MIPS_26:{
      reloc_output_jumptarget(linenum, section, offset, value);
      break;
   }
   case R_MIPS_HI16:{
      reloc_output_uimm(linenum, section, offset, value);
      break;
   }
   case R_MIPS_LO16:{
      reloc_output_imm(linenum, section, offset, value);
      break;
   }
   case R_MIPS_HI16_GPDISP:{
      reloc_output_uimm(linenum, section, offset, value);
      break;
   }
   case R_MIPS_LO16_GPDISP:{
      reloc_output_imm(linenum, section, offset, value);
      break;
   }
   case R_MIPS_GOT16:{
      reloc_output_imm(linenum, section, offset, value);
      break;
   }
   case R_MIPS_PC16:{
      reloc_output_imm(linenum, section, offset, value);
      break;
   }
   case R_MIPS_CALL16:{
      reloc_output_imm(linenum, section, offset, value);
      break;
   }
   case R_MIPS_64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 16");
      break;
   }
   case R_MIPS_SHIFT5:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 17");
      break;
   }
   case R_MIPS_SHIFT6:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 18");
      break;
   }
   case R_MIPS_GOT_DISP:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 19");
      break;
   }
   case R_MIPS_GOT_PAGE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 20");
      break;
   }
   case R_MIPS_GOT_OFST:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 21");
      break;
   }
   case R_MIPS_SUB:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 24");
      break;
   }
   case R_MIPS_INSERT_A:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 25");
      break;
   }
   case R_MIPS_INSERT_B:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 26");
      break;
   }
   case R_MIPS_DELETE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 27");
      break;
   }
   case R_MIPS_HIGHER:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 28");
      break;
   }
   case R_MIPS_HIGHEST:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 29");
      break;
   }
   case R_MIPS_SCN_DISP:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 32");
      break;
   }
   case R_MIPS_REL16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 33");
      break;
   }
   case R_MIPS_ADD_IMMEDIATE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 34");
      break;
   }
   case R_MIPS_PJUMP:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 35");
      break;
   }
   case R_MIPS_ADD_RELGOT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 36");
      break;
   }
   case R_MIPS_JALR:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 37");
      break;
   }
   case R_MIPS_DTPMOD32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 38");
      break;
   }
   case R_MIPS_DTPREL32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 39");
      break;
   }
   case R_MIPS_DTPMOD64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 40");
      break;
   }
   case R_MIPS_DTPREL64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 41");
      break;
   }
   case R_MIPS_GD:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 42");
      break;
   }
   case R_MIPS_LDM:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 43");
      break;
   }
   case R_MIPS_DTPREL_HI16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 44");
      break;
   }
   case R_MIPS_DTPREL_LO16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 45");
      break;
   }
   case R_MIPS_GOTTPREL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 46");
      break;
   }
   case R_MIPS_TPREL32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 47");
      break;
   }
   case R_MIPS_GPREL64:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 48");
      break;
   }
   case R_MIPS_TPREL_HI16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 49");
      break;
   }
   case R_MIPS_TPREL_LO16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 50");
      break;
   }
   case R_MIPS16_26:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 100");
      break;
   }
   case R_MIPS16_GPREL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 101");
      break;
   }
   case R_MIPS16_GOT16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 102");
      break;
   }
   case R_MIPS16_CALL16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 103");
      break;
   }
   case R_MIPS16_HI16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 104");
      break;
   }
   case R_MIPS16_LO16:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 105");
      break;
   }
   case R_MIPS16_COPY:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 126");
      break;
   }
   case R_MIPS16_JUMP_SLOT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 127");
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
