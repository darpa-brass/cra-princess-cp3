/*
 * Copyright (c) 2002, 2016
 *	The President and Fellows of Harvard College.
 *
 * Written by David A. Holland.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

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

////////////////////////////////////////////////////////////
// format-independent

enum reloc_modifier target_reloc_getmodifier(const char *name) {
   if (!strcmp(name, "hi")) {
      return RELOC_MOD_HI;
   }
   else if (!strcmp(name, "lo")) {
      return RELOC_MOD_LO;
   }
   else if (!strcmp(name, "branchoffset")) {
      return RELOC_MOD_BRANCHOFFSET;
   }
   else {
      assert(0); /* ? */
      return RELOC_MOD_NONE;
   }
}

const char *target_reloc_modifier_name(enum reloc_modifier mod) {
   switch (mod) {
    case RELOC_MOD_NONE: return NULL;
    case RELOC_MOD_HI: return "%hi";
    case RELOC_MOD_LO: return "%lo";
    case RELOC_MOD_BRANCHOFFSET: return "%branchoffset";
   }
   assert(0);
   return NULL;
}

const char *target_reloc_field_name(enum reloc_field f) {
   switch (f) {
    case RELOC_FIELD_32: return "32";
    case RELOC_FIELD_U16: return "u16";
    case RELOC_FIELD_S16: return "s16";
    case RELOC_FIELD_ANY16: return "16";
    case RELOC_FIELD_BRANCH16: return "s16 branch";
    case RELOC_FIELD_JUMP26: return "u26 jump";
   }
   assert(0);
   return NULL;
}

static void target_reloc_apply_directly(struct reloc *r, u_machword value) {
   int linenum = r->r_linenum;
   unsigned snum = r->r_sectnum;
   u_machword orig;

   switch (r->r_field) {
    case RELOC_FIELD_32:
     assert(r->r_modifier == RELOC_MOD_NONE);
     orig = section_get32(snum, r->r_offset);
     assert(orig == 0);
     section_put32(snum, r->r_offset, value);
     break;
    case RELOC_FIELD_S16:
     if ((s_machword)value > 32767 || (s_machword)value < -32768) {
	file_err(linenum, "Value does not fit in 16-bit field");
     }
     orig = section_get16(snum, r->r_offset);
     assert(orig == 0);
     section_put16(snum, r->r_offset, value);
     break;
    case RELOC_FIELD_U16:
     if (value > 65535) {
	file_err(linenum, "Value does not fit in 16-bit field");
     }
     orig = section_get16(snum, r->r_offset);
     assert(orig == 0);
     section_put16(snum, r->r_offset, value);
     break;
    case RELOC_FIELD_ANY16:
     if (value > 65535) {
	file_err(linenum, "Value does not fit in 16-bit field");
     }
     if ((s_machword)value < -32768) {
	file_err(linenum, "Value does not fit in 16-bit field");
     }
     orig = section_get16(snum, r->r_offset);
     assert(orig == 0);
     section_put16(snum, r->r_offset, value);
     break;
    case RELOC_FIELD_BRANCH16:
     orig = section_get16(snum, r->r_offset);
     assert(orig == 0);
     if (!fits_s16((u_machlarge)(s_machlarge)(s_machword)value)) {
	file_err(linenum, "Branch out of range - offset %ld", 
	    (long) (s_machword) value);
     }
     section_put16(snum, r->r_offset, value & 0xffff);
     break;
    case RELOC_FIELD_JUMP26:
     assert(r->r_modifier == RELOC_MOD_NONE);
     orig = section_get32(snum, r->r_offset);
     assert((orig & 0x3ffffff) == 0);
     if (value & 3) {
	file_err(linenum, "Unaligned jump target %lu", (unsigned long) value);
     }
     if ((value & 0xf0000000) != ((r->r_offset + 4) & 0xf0000000)) {
	file_err(linenum, "Jump target %lu too far", (unsigned long) value);
     }
     value = (orig & 0xfc000000) | ((value >> 2) & 0x3ffffff);
     section_put32(snum, r->r_offset, value);
     break;
    default:
     assert(0);
     break;
   }
}

void target_reloc_apply(struct reloc *r, u_machword value) {
   u_machword lo;

   switch (r->r_modifier) {
    case RELOC_MOD_NONE:
     break;
    case RELOC_MOD_LO:
     value = value & 0xffff;
     break;
    case RELOC_MOD_HI:
     /*
      * x = (%hi(x) << 16) + sign-extend(%lo(x))
      *
      * So if %lo(x) has its sign bit set, %hi(x) is 1 greater than x >> 16.
      */
     lo = (u_machword)(s_machword)(int16_t)(uint16_t)(value & 0xffff);
     value = (value - lo) >> 16;
     break;
    case RELOC_MOD_BRANCHOFFSET:
     /*
      * This should just be value >> 2, but it would need to be a
      * signed right shift. Growl.
      */
     /*
      * XXX: switch this back to an assertion when the encoding stuff
      * learns to enforce alignment of instructions. test with:
      *   foo: nop; .asciz "abcde"; nop; bar: nop
      */
     if (value & 3) {
	file_err(r->r_linenum, "Branch to unaligned instruction");
     }
     assert((value & 3) == 0);
     value = (u_machword)((s_machword)value / 4);

     break;
   }

   target_reloc_apply_directly(r, value);
}

////////////////////////////////////////////////////////////
// elf

static int target_reloc_code_raw(struct reloc *r) {
   enum reloc_modifier mod = r->r_modifier;
   enum reloc_field f = r->r_field;

   /*
    * XXX: figure out how to expose elf stuff less
    */
   switch (mod) {
    case RELOC_MOD_NONE:
     switch (f) {
      case RELOC_FIELD_32: return R_MIPS_32;
      case RELOC_FIELD_U16: return R_MIPS_16;
      case RELOC_FIELD_S16: return R_MIPS_16;
      case RELOC_FIELD_ANY16: return R_MIPS_16;
      case RELOC_FIELD_BRANCH16:
       file_err(r->r_linenum, "Cannot resolve branch");
       break;
      case RELOC_FIELD_JUMP26: return R_MIPS_26;
     }
     break;
    case RELOC_MOD_LO:
     /*
      * XXX. We need to use this with u16 fields like in andi/ori/xori,
      * but what happens to the addend overflow semantics then?
      */
     assert(f == RELOC_FIELD_S16 || f == RELOC_FIELD_U16);
     return R_MIPS_LO16;
    case RELOC_MOD_HI:
     assert(f == RELOC_FIELD_U16);
     return R_MIPS_HI16;
    case RELOC_MOD_BRANCHOFFSET:
     file_err(r->r_linenum, "Cannot encode branch offset in output file");
     break;
   }
   assert(0);
   return R_MIPS_NONE;
}

int target_reloc_code(struct reloc *r) {
   /*
    * Negative relocation codes mean Elf_Rel rather than Elf_Rela.
    */
#if defined(TARGET_ELF_USE_REL)
   return -target_reloc_code_raw(r);
#elif defined(TARGET_ELF_USE_RELA)
   return target_reloc_code_raw(r);
#else
#error "TARGET_ELF_USE_REL/RELA not set"
#endif
}

/*
 * Pre-output hook for relocation to allow any final adjustments.
 */
void target_reloc_preoutput(struct reloc *r) {
#if defined(TARGET_ELF_USE_REL)
   /*
    * If we're using Elf_Rel rather than Elf_Rela (for now we are),
    * apply the addend into the section data.
    *
    * To do this we can just use target_reloc_apply_directly.
    */
   target_reloc_apply_directly(r, r->r_addend);
   r->r_addend = 0;
#else
   (void)r;
#endif
}
