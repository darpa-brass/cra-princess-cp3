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
#include <stdlib.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "array.h"
#include "binfile.h"

#include "dumptbl.h"

////////////////////////////////////////////////////////////

/*
 * Prepare/keep list of symbols in numeric order, so we can find
 * the previous symbol when disassembling.
 */

DECLARRAY(gensym, static inline);
DEFARRAY(gensym, static inline);

static struct gensymarray syms_by_addr;

/*
 * Prepare/keep list of relocs in numeric order, so we can try to
 * identify the targets when disassembling external calls and
 * whatnot.
 */

DECLARRAY(genreloc, static inline);
DEFARRAY(genreloc, static inline);

static struct genrelocarray relocs_by_addr;

/*
 * Also remember the file handle.
 */

static struct binfile *curfile;

////////////////////////////////////////

static int symsortfunc(const void *aa, const void *bb) {
   struct gensym *a = *(struct gensym *const *)aa;
   struct gensym *b = *(struct gensym *const *)bb;

   if (a->gsm_value > b->gsm_value) {
      return 1;
   }
   if (a->gsm_value < b->gsm_value) {
      return -1;
   }
   return 0;
}

static int relsortfunc(const void *aa, const void *bb) {
   struct genreloc *a = *(struct genreloc *const *)aa;
   struct genreloc *b = *(struct genreloc *const *)bb;

   if (a->gr_offset > b->gr_offset) {
      return 1;
   }
   if (a->gr_offset < b->gr_offset) {
      return -1;
   }
   return 0;
}

static void sort_tables(void) {
   qsort(gensymarray_getdata(&syms_by_addr),
	 gensymarray_num(&syms_by_addr), 
	 sizeof(struct gensym *), symsortfunc);
   qsort(genrelocarray_getdata(&relocs_by_addr),
	 genrelocarray_num(&relocs_by_addr),
	 sizeof(struct genreloc *), relsortfunc);
}

// for bsearch() -- not used
//static int symsearchfunc(const void *kk, const void *vv) {
//   u_machword addr = *(const u_machword *)kk;
//   struct gensym *sym = *(struct gensym *const *)vv;
//
//   if (addr > sym->gsm_value) {
//      return 1;
//   }
//   else if (addr < sym->gsm_value) {
//      return -1;
//   }
//   return 0;
//}

/* Find the nearest symbol with address <= addr. */
static int symsearch(u_machword addr) {
   unsigned num;
   int lo, hi, mid;
   struct gensym *gsm;

   num = gensymarray_num(&syms_by_addr);

   if (num == 0) {
      /* just in case */
      return -1;
   }

   lo = 0;
   hi = num - 1;

   if (gensymarray_get(&syms_by_addr, lo)->gsm_value > addr) {
      return -1;
   }

   if (gensymarray_get(&syms_by_addr, hi)->gsm_value <= addr) {
      return hi;
   }

   while (hi-lo > 1) {
      mid = (hi+lo)/2;
      gsm = gensymarray_get(&syms_by_addr, mid);
      if (gsm->gsm_value == addr) {
	 lo = mid;
	 break;
      }
      else if (gsm->gsm_value > addr) {
	 hi = mid;
      }
      else {
	 lo = mid;
      }
   }

   assert(gensymarray_get(&syms_by_addr, lo)->gsm_value <= addr);
   assert(gensymarray_get(&syms_by_addr, hi)->gsm_value > addr);

   while (lo > 0 && gensymarray_get(&syms_by_addr, lo)->gsm_name == NULL) {
      lo--;
   }

   return lo;
}

static int relsearchfunc(const void *kk, const void *vv) {
   u_machword addr = *(const u_machword *)kk;
   struct genreloc *rel = *(struct genreloc *const *)vv;

   if (addr > rel->gr_offset) {
      return 1;
   }
   else if (addr < rel->gr_offset) {
      return -1;
   }
   return 0;
}

static unsigned relsearch(u_machword addr) {
   void *base, *x;
   unsigned num;
   unsigned index;

   base = genrelocarray_getdata(&relocs_by_addr);
   num = genrelocarray_num(&relocs_by_addr);

   x = bsearch(&addr, base, num, sizeof(struct genreloc *), relsearchfunc);
   if (x==NULL) {
      return num;
   }

   index = (struct genreloc **)x - (struct genreloc **)base;
   assert(index < num);

   while (index > 0 &&
	  genrelocarray_get(&relocs_by_addr, index-1)->gr_offset == addr) {
      index--;
   }
   assert(genrelocarray_get(&relocs_by_addr, index)->gr_offset == addr);
   return index;
}

////////////////////////////////////////////////////////////

struct genreloc *try_find_reloc(u_machword addr, unsigned section) {
   unsigned num, ix;
   struct genreloc *gr;

   num = genrelocarray_num(&relocs_by_addr);

   ix = relsearch(addr);
   if (ix >= num) {
      return NULL;
   }
   while (ix < num) {
      gr = genrelocarray_get(&relocs_by_addr, ix);
      if (gr->gr_offset != addr) {
	 break;
      }
      if (gr->gr_section == section) {
	 return gr;
      }
      ix++;
   }
   return NULL;
}

struct gensym *get_nearest_sym_byaddr(u_machword addr) {
   int ix;

   ix = symsearch(addr);
   if (ix<0) {
      return NULL;
   }
   return gensymarray_get(&syms_by_addr, ix);
}

struct gensym *get_sym_byaddr(u_machword vaddr) {
   struct gensym *gsm;

   gsm = get_nearest_sym_byaddr(vaddr);
   if (gsm->gsm_value != vaddr) {
      return NULL;
   }
   return gsm;
}

struct gensym *sym_of_reloc(struct genreloc *gr) {
   return binfile_getsymbol(curfile, gr->gr_symbol);
}

void dumptable_init(struct binfile *bf) {
   unsigned nsym, nreloc, i;
   struct gensym *gsm;
   struct genreloc *gr;

   gensymarray_init(&syms_by_addr);
   genrelocarray_init(&relocs_by_addr);

   nsym = binfile_numsymbols(bf);
   for (i=0; i<nsym; i++) {
      gsm = binfile_getsymbol(bf, i);
      if (gsm==NULL) {
	 continue;
      }
      gensymarray_add(&syms_by_addr, gsm);
   }

   nreloc = binfile_numrelocs(bf);
   for (i=0; i<nreloc; i++) {
      gr = binfile_getreloc(bf, i);
      assert(gr != NULL);
      genrelocarray_add(&relocs_by_addr, gr);
   }

   sort_tables();
   curfile = bf;
}

void dumptable_cleanup(void) {
   gensymarray_setsize(&syms_by_addr, 0);
   genrelocarray_setsize(&relocs_by_addr, 0);
   gensymarray_cleanup(&syms_by_addr);
   genrelocarray_cleanup(&relocs_by_addr);
   curfile = NULL;
}
