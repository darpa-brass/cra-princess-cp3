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

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h> /* for SIZE_MAX (for buffer.h) */
#include <limits.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "array.h"
#include "buffer.h"
#include "genfmt.h"
#include "binfile.h"

#include "section.h"

/*
 * A section as the assembler needs to think about it: a generic
 * section header plus the data that goes in.
 */
struct section {
   struct gensect *s_gsx;
   struct buffer s_data;
};
DECLARRAY(section, static UNUSED inline);
DEFARRAY(section, static UNUSED inline);

/*
 * All the sections in the current output file.
 */
static struct sectionarray sections;

/*
 * Constructor (does not implicitly add to the master table)
 */
static struct section *section_create(const char *name, unsigned flags) {
   struct section *s;

   s = domalloc(sizeof(*s));
   s->s_gsx = gensect_create(name);
   s->s_gsx->gsx_vaddr = 0;
   s->s_gsx->gsx_size = 0;
   s->s_gsx->gsx_align = 0;
   s->s_gsx->gsx_flags = flags;
   s->s_gsx->gsx_data = NULL;
   buffer_init(&s->s_data);
   return s;
}

/*
 * Destructor
 */
static void section_destroy(struct section *s) {
   gensect_destroy(s->s_gsx);
   buffer_cleanup(&s->s_data);
   dofree(s, sizeof(*s));
}

/*
 * Look up a section by name and return its index number.
 *
 * Use UNDEFINED_SECTION if it's not there.
 * UNDEFINED_SECTION is ours, but it has the same value as
 * GSX_UNDEF from genfmt.h.
 */
static unsigned findsection(const char *name) {
   unsigned i, num;
   struct section *s;

   num = sectionarray_num(&sections);
   for (i=0; i<num; i++) {
      s = sectionarray_get(&sections, i);
      if (!strcmp(s->s_gsx->gsx_name, name)) {
	 return i;
      }
   }
   return UNDEFINED_SECTION;
}

/*
 * Look up a section by name, external version: creates the
 * section if it doesn't exist.
 *
 * The flags options
 *    i: contains instructions
 *    ro: readonly
 *    b: is BSS
 * specify the section type. If HAVEFLAGS is set, these contain explicit
 * values; if not, they are defaults. If the section already exists,
 * explicit values must match what's already there.
 *
 * Returns the section index number, which is always valid. (If we
 * can't create the section, we'll bail out.)
 */
unsigned getsection(const char *name, bool haveflags, bool i, bool ro, bool b){
   struct section *ns;
   struct section *s;
   unsigned snum;
   unsigned flags;

   snum = findsection(name);

   flags = GSXF_READPERM|GSXF_LOADABLE;
   if (i) {
      flags |= GSXF_EXECPERM;
   }
   if (!ro) {
      flags |= GSXF_WRITEPERM;
   }
   if (b) {
      flags |= GSXF_ISBSS;
   }

   if (snum != UNDEFINED_SECTION) {
      s = sectionarray_get(&sections, snum);
      if (haveflags && s->s_gsx->gsx_flags != flags) {
	 prog_err("Section %s requested with wrong flags", name);
      }
      return snum;
   }

#if 0 /* gcc 4.8 output triggers this */
   if (!haveflags) {
      prog_warn("Section %s requested without flags", name);
   }
#endif

   ns = section_create(name, flags);
   sectionarray_addx(&sections, ns, &snum);
   return snum;
}

/*
 * Return the name of a section by its index number.
 */
const char *section_name(unsigned snum) {
   struct section *s;

   if (snum == UNDEFINED_SECTION) {
      return "[undef]";
   }
   s = sectionarray_get(&sections, snum);
   return s->s_gsx->gsx_name;
}

/* 
 * Assign a required alignment to the section. Does not affect the
 * section contents directly.
 */
void require_section_alignment(unsigned snum, u_machword alignment) {
   struct section *s;

   s = sectionarray_get(&sections, snum);

   if (s->s_gsx->gsx_align < alignment) {
      s->s_gsx->gsx_align = alignment;
   }
}

/*
 * Align the section, padding with zeros.
 */
void align_section(unsigned snum, u_machword alignment) {
   u_machword mask;
   struct section *s;

   mask = (1 << alignment) - 1;
   s = sectionarray_get(&sections, snum);

   if (s->s_gsx->gsx_align < alignment) {
      s->s_gsx->gsx_align = alignment;
   }

   while (s->s_gsx->gsx_size & mask) {
      section_addbyte(snum, -1, 0);
   }
}

/*
 * Print out sections; used by main when -v is in effect.
 */

static void dump_section(struct section *s) {
   int neednl;
   u_machword i;

   if (s->s_gsx->gsx_size==0) {
      return;
   }

   printf("Section %s", s->s_gsx->gsx_name);
   if (s->s_gsx->gsx_align > 0) {
      printf(" [align 2^%lu]", (unsigned long) s->s_gsx->gsx_align);
   }
   printf("\n");

   neednl = 0;
   for (i=0; i<s->s_gsx->gsx_size; i++) {
      if (i%16==0) {
	 printf("   ");
      }
      printf("%02x ", (unsigned char) buffer_getbyte(&s->s_data, i));
      if (i%16==15) { 
	 neednl=0;
	 printf("\n");
      }
      else {
	 neednl=1;
      }
   }
   if (neednl) {
      printf("\n");
   }
}

void dump_sections(void) {
   unsigned i, num;

   num = sectionarray_num(&sections);
   for (i=0; i<num; i++) {
      dump_section(sectionarray_get(&sections, i));
   }
}

/*
 * Issue all section data into the argument binfile.
 */
void emit_sections(struct binfile *bf) {
   unsigned i, num;
   struct section *s;
   u_machword len;

   num = sectionarray_num(&sections);
   for (i=0; i<num; i++) {
      s = sectionarray_get(&sections, i);
      len = s->s_gsx->gsx_size;
      assert(len == (u_machword) buffer_getsize(&s->s_data));
      
      s->s_gsx->gsx_data = domalloc(len);
      memcpy(s->s_gsx->gsx_data, buffer_mapat(&s->s_data, 0, len), len);

      binfile_addsect(bf, s->s_gsx, i);
   }
}

////////////////////////////////////////////////////////////

/*
 * Add data to a section.
 */
void section_addbyte(unsigned snum, int linenum, u_machbyte a) {
   struct section *s;

   s = sectionarray_get(&sections, snum);
   if ((s->s_gsx->gsx_flags & GSXF_ISBSS) && a!=0) {
      file_err(linenum, "Nonzero value in %s", s->s_gsx->gsx_name);
   }
   buffer_addbyte(&s->s_data, a);
   s->s_gsx->gsx_size++;
}

/*
 * Check if a section is currently aligned.
 * XXX: should return bool
 */
int section_isaligned(unsigned snum, u_machword alignment) {
   u_machword mask;
   struct section *s;

   mask = (1<<alignment)-1;
   s = sectionarray_get(&sections, snum);
   return (s->s_gsx->gsx_size & mask) == 0;
}

/*
 * Check if a section is tagged as BSS.
 */
bool section_isbss(unsigned snum) {
   struct section *s;

   s = sectionarray_get(&sections, snum);
   return s->s_gsx->gsx_flags & GSXF_ISBSS;
}

/*
 * Check if a section is tagged as code/having instructions/executable.
 */
bool section_iscode(unsigned snum) {
   struct section *s;

   s = sectionarray_get(&sections, snum);
   return s->s_gsx->gsx_flags & GSXF_EXECPERM;
}

/*
 * Fetch section size.
 */
u_machword section_getsize(unsigned snum) {
   struct section *s;

   s = sectionarray_get(&sections, snum);
   return s->s_gsx->gsx_size;
}

////////////////////////////////////////////////////////////

/* XXX XXX endianness!! */

/*
 * Get and update data within a section (as opposed to adding
 * new data at the end, which uses section_addbyte)
 *
 * XXX: need a systematic approach to words, word sizes, and endianness
 */

u_machword section_get64(unsigned snum, u_machword offset) {
   struct section *s;
   u_machbyte a;
   u_machword ret;
   unsigned i;

   /* this will not work if u_machword is 32 bits; but that's probably ok */

   s = sectionarray_get(&sections, snum);

   ret = 0;
#if TARGET_ENDIANNESS == MY_LITTLE_ENDIAN
   for (i=8; i-- > 0; ) {
      a = buffer_getbyte(&s->s_data, offset+i);
      ret = (ret << 8) | a;
   }
#elif TARGET_ENDIANNESS == MY_BIG_ENDIAN
   for (i=0; i<8; i++) {
      a = buffer_getbyte(&s->s_data, offset+i);
      ret = (ret << 8) | a;
   }
#else
#error "Endianness messed up"
#endif
   return ret;
}

u_machword section_get32(unsigned snum, u_machword offset) {
   struct section *s;
   u_machbyte a;
   u_machword ret;
   unsigned i;

   s = sectionarray_get(&sections, snum);

   ret = 0;
#if TARGET_ENDIANNESS == MY_LITTLE_ENDIAN
   for (i=4; i-- > 0; ) {
      a = buffer_getbyte(&s->s_data, offset+i);
      ret = (ret << 8) | a;
   }
#elif TARGET_ENDIANNESS == MY_BIG_ENDIAN
   for (i=0; i<4; i++) {
      a = buffer_getbyte(&s->s_data, offset+i);
      ret = (ret << 8) | a;
   }
#else
#error "Endianness messed up"
#endif
   /* XXX is this supposed to sign-extend like get16 does? */
   return ret;
}

u_machword section_get16(unsigned snum, u_machword offset) {
   struct section *s;
   u_machbyte a;
   u_machword ret;
   unsigned i;

   s = sectionarray_get(&sections, snum);

   ret = 0;
#if TARGET_ENDIANNESS == MY_LITTLE_ENDIAN
   for (i=2; i-- > 0; ) {
      a = buffer_getbyte(&s->s_data, offset+i);
      ret = (ret << 8) | a;
   }
#elif TARGET_ENDIANNESS == MY_BIG_ENDIAN
   for (i=0; i<2; i++) {
      a = buffer_getbyte(&s->s_data, offset+i);
      ret = (ret << 8) | a;
   }
#else
#error "Endianness messed up"
#endif
   if (ret & 0x8000) {
      /* sign-extend */
      ret |= ~(u_machword)0xffff;
   }
   return ret;
}

u_machword section_get8(unsigned snum, u_machword offset) {
   struct section *s;
   u_machword ret;

   s = sectionarray_get(&sections, snum);

   ret = buffer_getbyte(&s->s_data, offset);
   if (ret & 0x80) {
      /* sign-extend */
      ret |= ~(u_machword)0xff;
   }
   return ret;
}

void section_put64(unsigned snum, u_machword offset, u_machword val) {
   struct section *s;
   int i;

   s = sectionarray_get(&sections, snum);
#if TARGET_ENDIANNESS == MY_LITTLE_ENDIAN
   for (i=0; i<8; i++) {
      buffer_setbyte(&s->s_data, offset + i, val & 0xff);
      val = val >> 8;
   }
#elif TARGET_ENDIANNESS == MY_BIG_ENDIAN
   for (i=7; i>=0; i--) {
      buffer_setbyte(&s->s_data, offset + i, val & 0xff);
      val = val >> 8;
   }
#else
#error "Endianness messed up"
#endif
}

void section_put32(unsigned snum, u_machword offset, u_machword val) {
   struct section *s;

   s = sectionarray_get(&sections, snum);
#if TARGET_ENDIANNESS == MY_LITTLE_ENDIAN
   buffer_setbyte(&s->s_data, offset,   val & 0xff);
   buffer_setbyte(&s->s_data, offset+1, (val >> 8) & 0xff);
   buffer_setbyte(&s->s_data, offset+2, (val >> 16) & 0xff);
   buffer_setbyte(&s->s_data, offset+3, (val >> 24) & 0xff);
#elif TARGET_ENDIANNESS == MY_BIG_ENDIAN
   buffer_setbyte(&s->s_data, offset,   (val >> 24) & 0xff);
   buffer_setbyte(&s->s_data, offset+1, (val >> 16) & 0xff);
   buffer_setbyte(&s->s_data, offset+2, (val >> 8) & 0xff);
   buffer_setbyte(&s->s_data, offset+3, val & 0xff);
#else
#error "Endianness messed up"
#endif
}

void section_put16(unsigned snum, u_machword offset, u_machword val) {
   struct section *s;

   s = sectionarray_get(&sections, snum);
#if TARGET_ENDIANNESS == MY_LITTLE_ENDIAN
   buffer_setbyte(&s->s_data, offset, val & 0xff);
   buffer_setbyte(&s->s_data, offset+1, (val >> 8) & 0xff);
#elif TARGET_ENDIANNESS == MY_BIG_ENDIAN
   buffer_setbyte(&s->s_data, offset, (val >> 8) & 0xff);
   buffer_setbyte(&s->s_data, offset+1, val & 0xff);
#else
#error "Endianness messed up"
#endif
}

void section_put8(unsigned snum, u_machword offset, u_machword val) {
   struct section *s;

   s = sectionarray_get(&sections, snum);
   buffer_setbyte(&s->s_data, offset, val & 0xff);
}

////////////////////////////////////////////////////////////
// global init

/*
 * Initialize static data; called from main
 */
void section_setup(void) {
   sectionarray_init(&sections);
}

/*
 * Clean up static data; called from main
 */
void section_shutdown(void) {
   unsigned i, num;
   struct section *s;

   num = sectionarray_num(&sections);
   for (i=0; i<num; i++) {
      s = sectionarray_get(&sections, i);
      section_destroy(s);
   }
   sectionarray_setsize(&sections, 0);
   sectionarray_cleanup(&sections);
}
