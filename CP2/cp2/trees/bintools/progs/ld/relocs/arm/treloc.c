/* Automatically generated; do not edit */

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "common.h"

#include "elfreloc.h"

#include "section.h"
#include "outputrel.h"

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
   branchoffset = section_fetch32(snum, offset);
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
   ls_immediate = section_fetch32(snum, offset);
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
   dp_rotimmhack = section_fetch32(snum, offset);
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
   prev = section_fetch32(snum, offset);
   branchoffset =(branchoffset << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   branchoffset =(prev | branchoffset);
   section_store32(snum, offset, branchoffset);
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
   prev = section_fetch32(snum, offset);
   ls_immediate =(ls_immediate << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   ls_immediate =(prev | ls_immediate);
   section_store32(snum, offset, ls_immediate);
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
   prev = section_fetch32(snum, offset);
   dp_rotimmhack =(dp_rotimmhack << 0U);
   ones =(ones << 0U);
   ones = ~ones;
   prev =(prev & ones);
   dp_rotimmhack =(prev | dp_rotimmhack);
   section_store32(snum, offset, dp_rotimmhack);
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
static uint32_t reloc_compute_rel31(int linenum, uint32_t symbol, uint32_t addend, uint32_t offset, uint32_t location) {
   int32_t rel31;
   
   (void)linenum;
   (void)addend;
   (void)offset;
   (void)location;
   rel31 =((int32_t)(((symbol + addend)- location)<< 1U)>> 1U);
   return rel31;
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
      case R_ARM_PRIVATE_ROTIMMHACK:{
         addend =(addend + reloc_input_dp_rotimmhack(linenum, section, offset));
         break;
      }
      case R_ARM_NONE:{
         /*
          * nop
          */
         return;
      }
      case R_ARM_PC24:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 1");
         break;
      }
      case R_ARM_ABS32:{
         addend =(addend + reloc_input_data32(linenum, section, offset));
         break;
      }
      case R_ARM_REL32:{
         addend =(addend + reloc_input_data32(linenum, section, offset));
         break;
      }
      case R_ARM_PC13:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 4");
         break;
      }
      case R_ARM_ABS16:{
         addend =(addend + reloc_input_data16(linenum, section, offset));
         break;
      }
      case R_ARM_ABS12:{
         addend =(addend + reloc_input_ls_immediate(linenum, section, offset));
         break;
      }
      case R_ARM_THM_ABS5:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 7");
         break;
      }
      case R_ARM_ABS8:{
         addend =(addend + reloc_input_data8(linenum, section, offset));
         break;
      }
      case R_ARM_SBREL32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 9");
         break;
      }
      case R_ARM_THM_PC22:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 10");
         break;
      }
      case R_ARM_THM_PC8:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 11");
         break;
      }
      case R_ARM_AMP_VCALL9:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 12");
         break;
      }
      case R_ARM_SWI24:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 13");
         break;
      }
      case R_ARM_THM_SWI8:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 14");
         break;
      }
      case R_ARM_XPC25:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 15");
         break;
      }
      case R_ARM_THM_XPC22:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 16");
         break;
      }
      case R_ARM_TLS_DTPMOD32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 17");
         break;
      }
      case R_ARM_TLS_DTPOFF32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 18");
         break;
      }
      case R_ARM_TLS_TPOFF32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 19");
         break;
      }
      case R_ARM_COPY:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 20");
         break;
      }
      case R_ARM_GLOB_DAT:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 21");
         break;
      }
      case R_ARM_JUMP_SLOT:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 22");
         break;
      }
      case R_ARM_RELATIVE:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 23");
         break;
      }
      case R_ARM_GOTOFF:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 24");
         break;
      }
      case R_ARM_GOTPC:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 25");
         break;
      }
      case R_ARM_GOT32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 26");
         break;
      }
      case R_ARM_PLT32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 27");
         break;
      }
      case R_ARM_CALL:{
         addend =(addend + reloc_input_branchoffset(linenum, section, offset));
         break;
      }
      case R_ARM_JUMP24:{
         addend =(addend + reloc_input_branchoffset(linenum, section, offset));
         break;
      }
      case R_ARM_THM_JUMP24:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 30");
         break;
      }
      case R_ARM_BASE_ABS:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 31");
         break;
      }
      case R_ARM_ALU_PCREL_7_0:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 32");
         break;
      }
      case R_ARM_ALU_PCREL_15_8:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 33");
         break;
      }
      case R_ARM_ALU_PCREL_23_15:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 34");
         break;
      }
      case R_ARM_ALU_SBREL_11_0:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 35");
         break;
      }
      case R_ARM_ALU_SBREL_19_12:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 36");
         break;
      }
      case R_ARM_ALU_SBREL_27_20:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 37");
         break;
      }
      case R_ARM_TARGET1:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 38");
         break;
      }
      case R_ARM_SBREL31:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 39");
         break;
      }
      case R_ARM_V4BX:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 40");
         break;
      }
      case R_ARM_TARGET2:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 41");
         break;
      }
      case R_ARM_PREL31:{
         addend =(addend + reloc_input_data32(linenum, section, offset));
         break;
      }
      case R_ARM_MOVW_ABS_NC:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 43");
         break;
      }
      case R_ARM_MOVT_ABS:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 44");
         break;
      }
      case R_ARM_MOVW_PREL_NC:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 45");
         break;
      }
      case R_ARM_MOVT_PREL:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 46");
         break;
      }
      case R_ARM_THM_MOVW_ABS_NC:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 47");
         break;
      }
      case R_ARM_THM_MOVT_ABS:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 48");
         break;
      }
      case R_ARM_THM_MOVW_PREL_NC:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 49");
         break;
      }
      case R_ARM_THM_MOVT_PREL:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 50");
         break;
      }
      case R_ARM_GNU_VTENTRY:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 100");
         break;
      }
      case R_ARM_GNU_VTINHERIT:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 101");
         break;
      }
      case R_ARM_THM_PC11:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 102");
         break;
      }
      case R_ARM_THM_PC9:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 103");
         break;
      }
      case R_ARM_ARM_TLS_GD32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 104");
         break;
      }
      case R_ARM_ARM_TLS_LDM32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 105");
         break;
      }
      case R_ARM_ARM_TLS_LDO32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 106");
         break;
      }
      case R_ARM_ARM_TLS_IE32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 107");
         break;
      }
      case R_ARM_ARM_TLS_LE32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 108");
         break;
      }
      case R_ARM_ARM_TLS_LDO12:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 109");
         break;
      }
      case R_ARM_ARM_TLS_LE12:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 110");
         break;
      }
      case R_ARM_ARM_TLS_IE12GP:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 111");
         break;
      }
      case R_ARM_IRELATIVE:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 160");
         break;
      }
      case R_ARM_RXPC25:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 249");
         break;
      }
      case R_ARM_RSBREL32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 250");
         break;
      }
      case R_ARM_THM_RPC22:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 251");
         break;
      }
      case R_ARM_RREL32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 252");
         break;
      }
      case R_ARM_RABS32:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 253");
         break;
      }
      case R_ARM_RPC24:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 254");
         break;
      }
      case R_ARM_RBASE:{
         /*
          * unsupported
          */
         assert(!"Unsupported relocation 255");
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
   case R_ARM_PRIVATE_ROTIMMHACK:{
      value = reloc_compute_univ_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_ARM_NONE:{
      /*
       * nop
       */
      return;
   }
   case R_ARM_PC24:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 1");
      break;
   }
   case R_ARM_ABS32:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_ARM_REL32:{
      value = reloc_compute_univ_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_ARM_PC13:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 4");
      break;
   }
   case R_ARM_ABS16:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_ARM_ABS12:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_ARM_THM_ABS5:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 7");
      break;
   }
   case R_ARM_ABS8:{
      value = reloc_compute_univ_absolute(linenum, symval, addend, offset, location);
      break;
   }
   case R_ARM_SBREL32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 9");
      break;
   }
   case R_ARM_THM_PC22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 10");
      break;
   }
   case R_ARM_THM_PC8:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 11");
      break;
   }
   case R_ARM_AMP_VCALL9:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 12");
      break;
   }
   case R_ARM_SWI24:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 13");
      break;
   }
   case R_ARM_THM_SWI8:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 14");
      break;
   }
   case R_ARM_XPC25:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 15");
      break;
   }
   case R_ARM_THM_XPC22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 16");
      break;
   }
   case R_ARM_TLS_DTPMOD32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 17");
      break;
   }
   case R_ARM_TLS_DTPOFF32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 18");
      break;
   }
   case R_ARM_TLS_TPOFF32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 19");
      break;
   }
   case R_ARM_COPY:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 20");
      break;
   }
   case R_ARM_GLOB_DAT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 21");
      break;
   }
   case R_ARM_JUMP_SLOT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 22");
      break;
   }
   case R_ARM_RELATIVE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 23");
      break;
   }
   case R_ARM_GOTOFF:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 24");
      break;
   }
   case R_ARM_GOTPC:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 25");
      break;
   }
   case R_ARM_GOT32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 26");
      break;
   }
   case R_ARM_PLT32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 27");
      break;
   }
   case R_ARM_CALL:{
      value = reloc_compute_univ_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_ARM_JUMP24:{
      value = reloc_compute_univ_relative(linenum, symval, addend, offset, location);
      break;
   }
   case R_ARM_THM_JUMP24:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 30");
      break;
   }
   case R_ARM_BASE_ABS:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 31");
      break;
   }
   case R_ARM_ALU_PCREL_7_0:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 32");
      break;
   }
   case R_ARM_ALU_PCREL_15_8:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 33");
      break;
   }
   case R_ARM_ALU_PCREL_23_15:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 34");
      break;
   }
   case R_ARM_ALU_SBREL_11_0:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 35");
      break;
   }
   case R_ARM_ALU_SBREL_19_12:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 36");
      break;
   }
   case R_ARM_ALU_SBREL_27_20:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 37");
      break;
   }
   case R_ARM_TARGET1:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 38");
      break;
   }
   case R_ARM_SBREL31:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 39");
      break;
   }
   case R_ARM_V4BX:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 40");
      break;
   }
   case R_ARM_TARGET2:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 41");
      break;
   }
   case R_ARM_PREL31:{
      value = reloc_compute_rel31(linenum, symval, addend, offset, location);
      break;
   }
   case R_ARM_MOVW_ABS_NC:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 43");
      break;
   }
   case R_ARM_MOVT_ABS:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 44");
      break;
   }
   case R_ARM_MOVW_PREL_NC:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 45");
      break;
   }
   case R_ARM_MOVT_PREL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 46");
      break;
   }
   case R_ARM_THM_MOVW_ABS_NC:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 47");
      break;
   }
   case R_ARM_THM_MOVT_ABS:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 48");
      break;
   }
   case R_ARM_THM_MOVW_PREL_NC:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 49");
      break;
   }
   case R_ARM_THM_MOVT_PREL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 50");
      break;
   }
   case R_ARM_GNU_VTENTRY:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 100");
      break;
   }
   case R_ARM_GNU_VTINHERIT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 101");
      break;
   }
   case R_ARM_THM_PC11:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 102");
      break;
   }
   case R_ARM_THM_PC9:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 103");
      break;
   }
   case R_ARM_ARM_TLS_GD32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 104");
      break;
   }
   case R_ARM_ARM_TLS_LDM32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 105");
      break;
   }
   case R_ARM_ARM_TLS_LDO32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 106");
      break;
   }
   case R_ARM_ARM_TLS_IE32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 107");
      break;
   }
   case R_ARM_ARM_TLS_LE32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 108");
      break;
   }
   case R_ARM_ARM_TLS_LDO12:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 109");
      break;
   }
   case R_ARM_ARM_TLS_LE12:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 110");
      break;
   }
   case R_ARM_ARM_TLS_IE12GP:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 111");
      break;
   }
   case R_ARM_IRELATIVE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 160");
      break;
   }
   case R_ARM_RXPC25:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 249");
      break;
   }
   case R_ARM_RSBREL32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 250");
      break;
   }
   case R_ARM_THM_RPC22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 251");
      break;
   }
   case R_ARM_RREL32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 252");
      break;
   }
   case R_ARM_RABS32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 253");
      break;
   }
   case R_ARM_RPC24:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 254");
      break;
   }
   case R_ARM_RBASE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 255");
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
   case R_ARM_PRIVATE_ROTIMMHACK:{
      reloc_output_dp_rotimmhack(linenum, section, offset, value);
      break;
   }
   case R_ARM_NONE:{
      /*
       * nop
       */
      return;
   }
   case R_ARM_PC24:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 1");
      break;
   }
   case R_ARM_ABS32:{
      reloc_output_data32(linenum, section, offset, value);
      break;
   }
   case R_ARM_REL32:{
      reloc_output_data32(linenum, section, offset, value);
      break;
   }
   case R_ARM_PC13:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 4");
      break;
   }
   case R_ARM_ABS16:{
      reloc_output_data16(linenum, section, offset, value);
      break;
   }
   case R_ARM_ABS12:{
      reloc_output_ls_immediate(linenum, section, offset, value);
      break;
   }
   case R_ARM_THM_ABS5:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 7");
      break;
   }
   case R_ARM_ABS8:{
      reloc_output_data8(linenum, section, offset, value);
      break;
   }
   case R_ARM_SBREL32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 9");
      break;
   }
   case R_ARM_THM_PC22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 10");
      break;
   }
   case R_ARM_THM_PC8:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 11");
      break;
   }
   case R_ARM_AMP_VCALL9:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 12");
      break;
   }
   case R_ARM_SWI24:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 13");
      break;
   }
   case R_ARM_THM_SWI8:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 14");
      break;
   }
   case R_ARM_XPC25:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 15");
      break;
   }
   case R_ARM_THM_XPC22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 16");
      break;
   }
   case R_ARM_TLS_DTPMOD32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 17");
      break;
   }
   case R_ARM_TLS_DTPOFF32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 18");
      break;
   }
   case R_ARM_TLS_TPOFF32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 19");
      break;
   }
   case R_ARM_COPY:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 20");
      break;
   }
   case R_ARM_GLOB_DAT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 21");
      break;
   }
   case R_ARM_JUMP_SLOT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 22");
      break;
   }
   case R_ARM_RELATIVE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 23");
      break;
   }
   case R_ARM_GOTOFF:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 24");
      break;
   }
   case R_ARM_GOTPC:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 25");
      break;
   }
   case R_ARM_GOT32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 26");
      break;
   }
   case R_ARM_PLT32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 27");
      break;
   }
   case R_ARM_CALL:{
      reloc_output_branchoffset(linenum, section, offset, value);
      break;
   }
   case R_ARM_JUMP24:{
      reloc_output_branchoffset(linenum, section, offset, value);
      break;
   }
   case R_ARM_THM_JUMP24:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 30");
      break;
   }
   case R_ARM_BASE_ABS:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 31");
      break;
   }
   case R_ARM_ALU_PCREL_7_0:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 32");
      break;
   }
   case R_ARM_ALU_PCREL_15_8:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 33");
      break;
   }
   case R_ARM_ALU_PCREL_23_15:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 34");
      break;
   }
   case R_ARM_ALU_SBREL_11_0:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 35");
      break;
   }
   case R_ARM_ALU_SBREL_19_12:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 36");
      break;
   }
   case R_ARM_ALU_SBREL_27_20:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 37");
      break;
   }
   case R_ARM_TARGET1:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 38");
      break;
   }
   case R_ARM_SBREL31:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 39");
      break;
   }
   case R_ARM_V4BX:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 40");
      break;
   }
   case R_ARM_TARGET2:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 41");
      break;
   }
   case R_ARM_PREL31:{
      reloc_output_data32(linenum, section, offset, value);
      break;
   }
   case R_ARM_MOVW_ABS_NC:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 43");
      break;
   }
   case R_ARM_MOVT_ABS:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 44");
      break;
   }
   case R_ARM_MOVW_PREL_NC:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 45");
      break;
   }
   case R_ARM_MOVT_PREL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 46");
      break;
   }
   case R_ARM_THM_MOVW_ABS_NC:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 47");
      break;
   }
   case R_ARM_THM_MOVT_ABS:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 48");
      break;
   }
   case R_ARM_THM_MOVW_PREL_NC:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 49");
      break;
   }
   case R_ARM_THM_MOVT_PREL:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 50");
      break;
   }
   case R_ARM_GNU_VTENTRY:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 100");
      break;
   }
   case R_ARM_GNU_VTINHERIT:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 101");
      break;
   }
   case R_ARM_THM_PC11:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 102");
      break;
   }
   case R_ARM_THM_PC9:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 103");
      break;
   }
   case R_ARM_ARM_TLS_GD32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 104");
      break;
   }
   case R_ARM_ARM_TLS_LDM32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 105");
      break;
   }
   case R_ARM_ARM_TLS_LDO32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 106");
      break;
   }
   case R_ARM_ARM_TLS_IE32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 107");
      break;
   }
   case R_ARM_ARM_TLS_LE32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 108");
      break;
   }
   case R_ARM_ARM_TLS_LDO12:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 109");
      break;
   }
   case R_ARM_ARM_TLS_LE12:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 110");
      break;
   }
   case R_ARM_ARM_TLS_IE12GP:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 111");
      break;
   }
   case R_ARM_IRELATIVE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 160");
      break;
   }
   case R_ARM_RXPC25:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 249");
      break;
   }
   case R_ARM_RSBREL32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 250");
      break;
   }
   case R_ARM_THM_RPC22:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 251");
      break;
   }
   case R_ARM_RREL32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 252");
      break;
   }
   case R_ARM_RABS32:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 253");
      break;
   }
   case R_ARM_RPC24:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 254");
      break;
   }
   case R_ARM_RBASE:{
      /*
       * unsupported
       */
      assert(!"Unsupported relocation 255");
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
