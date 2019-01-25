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

#include "targetdefs.h"
#include "utils.h"
#include "match.h"
#include "reloc.h"
#include "label.h"
#include "section.h"
#include "sectionops.h"
#include "as.h"

void addbyte(int linenum, u_machbyte a) {
   unsigned sect;

   sect = getcursection(linenum);
   section_addbyte(sect, linenum, a);
}

void add8(int linenum, uint8_t x) {
   addbyte(linenum, x);
}

void add16(int linenum, uint16_t x) {
#if TARGET_ENDIANNESS == MY_BIG_ENDIAN
   addbyte(linenum, (x >> 8) & 0xff);
   addbyte(linenum, x & 0xff);
#else
   addbyte(linenum, x & 0xff);
   addbyte(linenum, (x >> 8) & 0xff);
#endif
}

void add32(int linenum, uint32_t x) {
#if TARGET_ENDIANNESS == MY_BIG_ENDIAN
   addbyte(linenum, x >> 24);
   addbyte(linenum, (x >> 16) & 0xff);
   addbyte(linenum, (x >> 8) & 0xff);
   addbyte(linenum, x & 0xff);
#else
   addbyte(linenum, x & 0xff);
   addbyte(linenum, (x >> 8) & 0xff);
   addbyte(linenum, (x >> 16) & 0xff);
   addbyte(linenum, x >> 24);
#endif
}

void add64(int linenum, uint64_t x) {
#if TARGET_ENDIANNESS == MY_BIG_ENDIAN
   addbyte(linenum, x >> 56);
   addbyte(linenum, (x >> 48) & 0xff);
   addbyte(linenum, (x >> 40) & 0xff);
   addbyte(linenum, (x >> 32) & 0xff);
   addbyte(linenum, (x >> 24) & 0xff);
   addbyte(linenum, (x >> 16) & 0xff);
   addbyte(linenum, (x >> 8) & 0xff);
   addbyte(linenum, x & 0xff);
#else
   addbyte(linenum, x & 0xff);
   addbyte(linenum, (x >> 8) & 0xff);
   addbyte(linenum, (x >> 16) & 0xff);
   addbyte(linenum, (x >> 24) & 0xff);
   addbyte(linenum, (x >> 32) & 0xff);
   addbyte(linenum, (x >> 40) & 0xff);
   addbyte(linenum, (x >> 48) & 0xff);
   addbyte(linenum, x >> 56);
#endif
}

/*
 * Hacks
 */
static void modimm_hack_joint(int lineno, unsigned val,
			      unsigned *a, unsigned *b) {
   unsigned i, val2;

   if (val == (val & 0xff)) {
      *a = 0;
      *b = val;
      return;
   }
   for (i=1; i<16; i++) {
      val2 = ((val << (i*2)) & 0xffffffff) |
	     ((val >> (32 - i*2)) & 0xffffffff);
      if (val2 == (val2 & 0xff)) {
	 *a = i;
	 *b = val2;
	 return;
      }
   }
   file_err(lineno, "Cannot encode constant 0x%x (%u)", val, val);
}
unsigned modimm_hack_a(int lineno, unsigned val) {
   unsigned a, b;
   
   modimm_hack_joint(lineno, val, &a, &b);
   return a;
}
unsigned modimm_hack_b(int lineno, unsigned val) {
   unsigned a, b;
   
   modimm_hack_joint(lineno, val, &a, &b);
   return b;
}
