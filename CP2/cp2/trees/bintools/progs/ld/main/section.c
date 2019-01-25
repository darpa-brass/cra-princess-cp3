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
#include "array.h"
#include "genfmt.h"
#include "binfile.h"
#include "loadfile.h"

#include "section.h"

DECLARRAY(gensect, static inline);
DEFARRAY(gensect, static inline);

struct mysection {
   char *firstfile;
   struct gensectarray constituents;
   u_machword align;
   u_machword curoffset;
   u_machword vaddr;
};

DECLARRAY(mysection, static inline);
DEFARRAY(mysection, static inline);


static struct mysectionarray allsections;
static struct uintarray outputorder;

static struct mysection *mysection_create(const char *fromfile) {
   struct mysection *ms;

   ms = domalloc(sizeof(*ms));
   ms->firstfile = dostrdup(fromfile);
   gensectarray_init(&ms->constituents);
   ms->align = 0;
   ms->curoffset = 0;
   ms->vaddr = 0;
   return ms;
}

/* XXX enable this */
#if 0
static void mysection_destroy(struct mysection *ms) {
   /* XXX: destroyall? */
   gensectarray_setsize(&ms->constituents, 0);
   gensectarray_cleanup(&ms->constituents);
   dostrfree(ms->firstfile);
   dofree(ms, sizeof(*ms));
}
#endif

static unsigned findsection(const char *name) {
   unsigned i, num;
   struct mysection *ms;
   struct gensect *gsx;

   num = mysectionarray_num(&allsections);
   for (i=0; i<num; i++) {
      ms = mysectionarray_get(&allsections, i);
      assert(gensectarray_num(&ms->constituents) > 0);
      gsx = gensectarray_get(&ms->constituents, 0);
      if (!strcmp(gsx->gsx_name, name)) {
	 return i;
      }
   }
   return (unsigned)-1;
}

static void mysection_add(const char *fromfile,
			  struct mysection *ms, struct gensect *newgsx) {
   struct gensect *oldgsx;

   if (gensectarray_num(&ms->constituents) > 0) {
      oldgsx = gensectarray_get(&ms->constituents, 0);
      if (oldgsx->gsx_flags != newgsx->gsx_flags) {
	 assert(fromfile != NULL);
	 prog_err("Attributes of section %s in %s differ from in %s",
		  newgsx->gsx_name, fromfile, ms->firstfile);
      }
   }

   gensectarray_add(&ms->constituents, newgsx);
   ms->curoffset += newgsx->gsx_size;
}

static void mysection_align(struct mysection *ms, u_machword alignment) {
   u_machword mask, count;
   struct gensect *model, *gsx;

   mask = (1<<alignment) - 1;
   count = 0;
   while ((ms->curoffset + count) & mask) {
      count++;
   }

   if (count > 0) {
      assert(gensectarray_num(&ms->constituents) > 0);
      model = gensectarray_get(&ms->constituents, 0);

      gsx = gensect_create(model->gsx_name);
      gsx->gsx_vaddr = 0;
      gsx->gsx_size = count;
      gsx->gsx_align = 0;
      gsx->gsx_flags = model->gsx_flags;
      gsx->gsx_data = domalloc(count);
      memset(gsx->gsx_data, 0, count);

      mysection_add(NULL, ms, gsx);
   }

   if (alignment > ms->align) {
      ms->align = alignment;
   }
}

/*
 * Add the section provided to the current store of sections.
 * If a section of the same name already exists, merge it; otherwise
 * add a new section.
 *
 * Return the index number.
 * Also hand back the offset from the beginning of our section
 * where the provided section starts.
 */

unsigned section_add(const char *fromfile, struct gensect *gsx,
		     u_machword *offset) {
   unsigned ix;
   struct mysection *ms;

   ix = findsection(gsx->gsx_name);
   if (ix == (unsigned)-1) {
      ms = mysection_create(fromfile);
      mysectionarray_addx(&allsections, ms, &ix);
   }

   ms = mysectionarray_get(&allsections,ix);
   mysection_align(ms, gsx->gsx_align);

   *offset = ms->curoffset;
   mysection_add(fromfile, ms, gsx);

   return ix;
}

/*
 * Emit one section to a binfile.
 */
static void emit_one_section(struct binfile *bf, struct mysection *ms,
			     unsigned id) {
   struct gensect *gs;

   gs = gensect_create(gensectarray_get(&ms->constituents, 0)->gsx_name);
   gs->gsx_vaddr = ms->vaddr;
   gs->gsx_size = ms->curoffset;
   gs->gsx_align = ms->align;
   gs->gsx_flags = gensectarray_get(&ms->constituents, 0)->gsx_flags;
   if (gs->gsx_flags & GSXF_ISBSS) {
      gs->gsx_data = NULL;
   }
   else {
      unsigned j, num;
      struct gensect *from;
      u_machword pos = 0;
      char *data;

      data = domalloc(gs->gsx_size);

      /* any/all alignment padding has already been stuck in constituents[] */

      num = gensectarray_num(&ms->constituents);
      for (j=0; j<num; j++) {
	 from = gensectarray_get(&ms->constituents, j);
	 memcpy(data + pos, from->gsx_data, from->gsx_size);
	 pos += from->gsx_size;
      }
      gs->gsx_data = data;
   }

   binfile_addsect(bf, gs, id);
}

/*
 * Emit all the sections to a binfile.
 */
void section_emit(struct binfile *bf) {
   unsigned i, s, num;

   num = uintarray_num(&outputorder);
   for (i=0; i<num; i++) {
      s = uintarray_get(&outputorder, i);
      emit_one_section(bf, mysectionarray_get(&allsections, s), s);
   }
}

////////////////////////////////////////////////////////////

/*
 * Get size of beginning-of-file header.
 * We need to hand in all the sections and their flags, to support
 * formats where the section headers must come at the beginning.
 */
static u_machword get_headersize(bool impure) {
   unsigned i, s, num;
   struct mysection *ms;
   struct gensect *gsx0;
   unsigned flags;

   headersize_clear();

   num = uintarray_num(&outputorder);
   for (i=0; i<num; i++) {
      s = uintarray_get(&outputorder, i);
      ms = mysectionarray_get(&allsections, s);
      gsx0 = gensectarray_get(&ms->constituents, 0);

      flags = gsx0->gsx_flags;
#ifdef TARGET_DISREGARD_EXEC_PERMS
      flags &= ~(GSXF_EXECPERM);
#endif
      if (impure) {
	 flags |= GSXF_WRITEPERM;
      }
      headersize_addsection(gsx0->gsx_name, flags);
   }
   return headersize_get();
}

/*
 * Group sections with the same characteristics together.
 */
static void section_permute(void) {
   struct uintarray orderings;
   unsigned i, j, num;
   struct mysection *ms;
   struct gensect *gsx0;
   unsigned flags, ordering;

   uintarray_init(&orderings);
   num = mysectionarray_num(&allsections);
   uintarray_setsize(&orderings, num);
   for (i=0; i<num; i++) {
      ms = mysectionarray_get(&allsections, i);
      gsx0 = gensectarray_get(&ms->constituents, 0);
      flags = gsx0->gsx_flags;

      ordering = 0;

      if ((flags & GSXF_LOADABLE)==0) ordering |= 32;
      if ((flags & GSXF_ISNOTE)!=0) ordering |= 16;
      if ((flags & GSXF_ISBSS)!=0) ordering |= 8;
      if ((flags & GSXF_WRITEPERM)!=0) ordering |= 4;
      if ((flags & GSXF_READPERM)==0) ordering |= 2;
      if ((flags & GSXF_EXECPERM)==0) ordering |= 1;

      uintarray_set(&orderings, i, ordering);
   }

   for (j=0; j<63; j++) {
       for (i=0; i<num; i++) {
	  if (uintarray_get(&orderings, i) == j) {
	     uintarray_add(&outputorder, i);
	  }
       }
    }

    assert(uintarray_num(&outputorder) == mysectionarray_num(&allsections));

    uintarray_setsize(&orderings, 0);
    uintarray_cleanup(&orderings);
}

void section_layout(u_machword textorg, u_machword dataorg, u_machword bssorg,
		    bool impure) {
   u_machword pos, oldpos, headersize;
   u_machword etext=0, edata=0;
   unsigned flags = 0, oldflags;
   int first=1;
   int firstdata=1, firstbss=1;
   unsigned i, s, num;
   struct mysection *ms;

   section_permute();

   headersize = get_headersize(impure);
   headersize %= TARGET_PAGESIZE;

   oldpos = 0;
   pos = textorg + headersize;

   //prog_warn("textorg                  0x%x", textorg);
   //prog_warn("dataorg                  0x%x", dataorg);
   //prog_warn("bssorg                   0x%x", bssorg);
   //prog_warn("header size              0x%x", headersize);
   //prog_warn("initial pos              0x%x", pos);

   num = uintarray_num(&outputorder);
   for (i=0; i<num; i++) {
      s = uintarray_get(&outputorder, i);
      ms = mysectionarray_get(&allsections, s);
      assert(ms != NULL);

      assert(oldpos<=pos);

      oldflags = flags;
      oldpos = pos;

      flags = gensectarray_get(&ms->constituents, 0)->gsx_flags;

      if ((flags & GSXF_LOADABLE) == 0) {
	 ms->vaddr = 0;
	 continue;
      }

      if ((flags & GSXF_EXECPERM) != (oldflags & GSXF_EXECPERM)) {
	 if (etext == 0) {
	    etext = pos;
	 }
      }
      if ((flags & GSXF_ISBSS) != (oldflags & GSXF_ISBSS)) {
	 if (edata == 0) {
	    edata = pos;
	 }
      }

#ifdef TARGET_DISREGARD_EXEC_PERMS
      flags &= ~(GSXF_EXECPERM);
#endif
      if (impure) {
	 flags |= GSXF_WRITEPERM;
      }

      if (flags != oldflags) {
	 if (flags == (GSXF_LOADABLE|GSXF_WRITEPERM|GSXF_READPERM)) {
	    if (firstdata && dataorg != 0) {
	       firstdata = 0;
	       pos = dataorg;
	    }
	 }
	 if (flags == (GSXF_LOADABLE|GSXF_ISBSS|GSXF_WRITEPERM|GSXF_READPERM)){
	    if (firstbss) {
	       firstbss=0;
	       if (bssorg != 0) {
		  pos = bssorg;
	       }
	       else {
		  bssorg = pos;
	       }
	    }
	 }
      }

      while (pos & ((1 << ms->align)-1)) {
	 pos++;
      }

      /* BSS is not different from data from a layout perspective */
      flags &= ~(GSXF_ISBSS);

      if (flags != oldflags && 
	  pos/TARGET_PAGESIZE == oldpos/TARGET_PAGESIZE &&
	  (pos & (TARGET_PAGESIZE-1))!=0) {
	 if (first) {
	    first = 0;
	 }
	 else {
	    pos += TARGET_PAGESIZE;
	 }
      }

      //prog_warn("Section %-11svaddr 0x%x",ms->constituents[0]->gsx_name,pos);

      ms->vaddr = pos;

      pos += ms->curoffset;
   }

   if (etext==0) {
      etext = pos;
   }
   if (edata==0) {
      edata = pos;
   }
   symbol_ld_provided("_etext", etext);
   symbol_ld_provided("_edata", edata);
   symbol_ld_provided("__bss_start", bssorg);
   symbol_ld_provided("_end", pos);
}

u_machword section_getbase(unsigned sectnum) {
   assert(sectnum != GSX_INVALID);
   assert(sectnum != GSX_UNDEF);
   assert(sectnum != GSX_COMMON);

   if (sectnum == GSX_ABS) {
      return 0;
   }
   return mysectionarray_get(&allsections, sectnum)->vaddr;
}

////////////////////////////////////////////////////////////

static uint8_t *getptr(unsigned sectnum, u_machword offset) {
   struct mysection *ms;
   unsigned i, num;
   struct gensect *gsx;

   ms = mysectionarray_get(&allsections, sectnum);
   assert(ms != NULL);

   num = gensectarray_num(&ms->constituents);
   for (i=0; i<num; i++) {
      gsx = gensectarray_get(&ms->constituents, i);
      if (offset < gsx->gsx_size) {
	 uint8_t *data = (uint8_t *) gsx->gsx_data;
	 assert(data != NULL);
	 return data + offset;
      }
      else {
	 offset -= gsx->gsx_size;
      }
   }

   assert(0);
   return NULL;
}

u_machword section_fetch8(unsigned sectnum, u_machword offset) {
   uint8_t *ptr = getptr(sectnum, offset);

   return ptr[0];
}

u_machword section_fetch16(unsigned sectnum, u_machword offset) {
   u_machword result = 0;
   uint8_t *ptr = getptr(sectnum, offset);
   int i;

#if TARGET_ENDIANNESS == MY_BIG_ENDIAN
   for (i=0; i<2; i++) {
      result = (result << 8) | ptr[i];
   }
#elif TARGET_ENDIANNESS == MY_LITTLE_ENDIAN
   for (i=1; i>=0; i--) {
      result = (result << 8) | ptr[i];
   }
#else
#error "Endianness messed up"
#endif

   return result;
}

u_machword section_fetch32(unsigned sectnum, u_machword offset) {
   u_machword result = 0;
   uint8_t *ptr = getptr(sectnum, offset);
   int i;

#if TARGET_ENDIANNESS == MY_BIG_ENDIAN
   for (i=0; i<4; i++) {
      result = (result << 8) | ptr[i];
   }
#elif TARGET_ENDIANNESS == MY_LITTLE_ENDIAN
   for (i=3; i>=0; i--) {
      result = (result << 8) | ptr[i];
   }
#else
#error "Endianness messed up"
#endif

   return result;
}

u_machword section_fetch64(unsigned sectnum, u_machword offset) {
   u_machword result = 0;
   uint8_t *ptr = getptr(sectnum, offset);
   int i;

   /* this won't work if u_machword is 32 bits, but that's pretty much ok */

#if TARGET_ENDIANNESS == MY_BIG_ENDIAN
   for (i=0; i<8; i++) {
      result = (result << 8) | ptr[i];
   }
#elif TARGET_ENDIANNESS == MY_LITTLE_ENDIAN
   for (i=7; i>=0; i--) {
      result = (result << 8) | ptr[i];
   }
#else
#error "Endianness messed up"
#endif

   return result;
}

void section_store8(unsigned sectnum, u_machword offset, u_machword val) {
   uint8_t *ptr = getptr(sectnum, offset);

   ptr[0] = val & 0xff;
}

void section_store16(unsigned sectnum, u_machword offset, u_machword val) {
   uint8_t *ptr = getptr(sectnum, offset);
   int i;

#if TARGET_ENDIANNESS == MY_LITTLE_ENDIAN
   for (i=0; i<2; i++) {
      ptr[i] = val & 0xff;
      val = val >> 8;
   }
#elif TARGET_ENDIANNESS == MY_BIG_ENDIAN
   for (i=1; i>=0; i--) {
      ptr[i] = val & 0xff;
      val = val >> 8;
   }
#else
#error "Endianness messed up"
#endif
}

void section_store32(unsigned sectnum, u_machword offset, u_machword val) {
   uint8_t *ptr = getptr(sectnum, offset);
   int i;

#if TARGET_ENDIANNESS == MY_LITTLE_ENDIAN
   for (i=0; i<4; i++) {
      ptr[i] = val & 0xff;
      val = val >> 8;
   }
#elif TARGET_ENDIANNESS == MY_BIG_ENDIAN
   for (i=3; i>=0; i--) {
      ptr[i] = val & 0xff;
      val = val >> 8;
   }
#else
#error "Endianness messed up"
#endif
}

void section_store64(unsigned sectnum, u_machword offset, u_machword val) {
   uint8_t *ptr = getptr(sectnum, offset);
   int i;

#if TARGET_ENDIANNESS == MY_LITTLE_ENDIAN
   for (i=0; i<8; i++) {
      ptr[i] = val & 0xff;
      val = val >> 8;
   }
#elif TARGET_ENDIANNESS == MY_BIG_ENDIAN
   for (i=7; i>=0; i--) {
      ptr[i] = val & 0xff;
      val = val >> 8;
   }
#else
#error "Endianness messed up"
#endif
}

////////////////////////////////////////////////////////////
// global init

void section_setup(void) {
   mysectionarray_init(&allsections);
   uintarray_init(&outputorder);
}

void section_shutdown(void) {
   /* XXX: destroyall? */
   mysectionarray_setsize(&allsections, 0);
   uintarray_setsize(&outputorder, 0);
   
   mysectionarray_cleanup(&allsections);
   uintarray_cleanup(&outputorder);
}
