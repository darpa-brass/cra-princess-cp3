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
#include <assert.h>
#include "common.h"

#include "elfreloc.h"

#include "section.h"
#include "outputrel.h"


void machdep_do_reloc(int code, unsigned section, u_machword offset,
		      u_machword val, u_machword addend) {
   uint32_t lo, insn;

   if (code < 0) {
      code = -code;
      switch (code) {
       case R_MIPS_NONE:
	break;
       case R_MIPS_32:
       case R_MIPS_REL32:
       case R_MIPS_GPREL32:
	addend = section_fetch32(section, offset);
	break;

       case R_MIPS_LO16:
       case R_MIPS_HI16:
	/* XXX for these one needs to find matching pairs to get the addend */
	
       case R_MIPS_16:
       case R_MIPS_GPREL16:
       case R_MIPS_GOT16:
       case R_MIPS_PC16:
       case R_MIPS_CALL16:
	addend = section_fetch16(section, offset);
	break;
       case R_MIPS_26:
	addend = section_fetch32(section, offset) & 0x03ffffff;
	break;
       case R_MIPS_LITERAL:
	assert(!"dunno how to handle this relocation"); // XXX
	break;
       default:
	/* XXX how do we error in here? */
	assert(!"unknown relocation code"); // XXX
	break;
      }
   }

   /*
    * XXX review all these 
    */
   switch (code) {
    case R_MIPS_NONE:
     return;
    case R_MIPS_16:
     section_store16(section, offset, val + addend);
     break;
    case R_MIPS_32:
     section_store32(section, offset, val + addend);
     break;
    case R_MIPS_REL32:
     section_store32(section, offset, val + addend - offset);
     break;
    case R_MIPS_26:
     insn = section_fetch32(section, offset) & 0xfc000000;
     insn |= ((val + addend) >> 2) & 0x3ffffff;
     section_store32(section, offset, insn);
     break;
    case R_MIPS_HI16:
     lo = (uint32_t)(int32_t)(int16_t)(uint16_t)((val + addend) & 0xffff);
     section_store16(section, offset, (val + addend - lo) >> 16);
     break;
    case R_MIPS_LO16:
     section_store16(section, offset, (val + addend) & 0xffff);
     break;
    case R_MIPS_GPREL16:
    case R_MIPS_LITERAL:
    case R_MIPS_GOT16:
     assert(!"dunno how to handle this relocation yet");
     break;
    case R_MIPS_PC16:
     section_store16(section, offset, (val + addend - offset) & 0xffff);
     break;
    case R_MIPS_CALL16:
    case R_MIPS_GPREL32:
     assert(!"dunno how to handle this relocation yet");
     break;
    default:
     assert(!"unknown relocation type");
     break;
   }
}
