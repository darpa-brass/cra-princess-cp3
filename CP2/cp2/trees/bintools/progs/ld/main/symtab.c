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
#include <string.h>
#include <assert.h>
#include "common.h"

#include "array.h"
#include "genfmt.h"

#include "main.h"
#include "section.h"
#include "symtab.h"
#include "outputsym.h"

struct externsym;

struct mysym {
   char *fromfile;
   struct gensym *gsm;
   unsigned id;
   struct externsym *ref;
};

struct externsym {
   const char *name;
   struct mysym *defn;
   struct mysym *firstuse;
};

DECLARRAY(mysym, static inline);
DEFARRAY(mysym, static inline);
DECLARRAY(externsym, static inline);
DEFARRAY(externsym, static inline);

static struct mysymarray mysyms;
static struct externsymarray externsyms;

static struct mysym *mysym_create(const char *fromfile, struct gensym *gsm,
				  unsigned outputsym_id) {
   struct mysym *ms;

   ms = domalloc(sizeof(*ms));
   ms->fromfile = dostrdup(fromfile);
   ms->gsm = gsm;
   ms->id = outputsym_id;
   ms->ref = NULL;
   return ms;
}

static void mysym_destroy(struct mysym *ms) {
   /* do NOT destroy ms->gsm; we don't own it */
   dostrfree(ms->fromfile);
   dofree(ms, sizeof(*ms));
}

static struct externsym *externsym_create(struct gensym *gsm,
					  struct mysym *ms) {
   struct externsym *es;

   es = domalloc(sizeof(*es));
   es->name = gsm->gsm_name;
   if (gsm->gsm_section == GSX_UNDEF) {
      es->defn = NULL;
      es->firstuse = ms;
   }
   else {
      es->defn = ms;
      es->firstuse = NULL;
   }
   externsymarray_add(&externsyms, es);
   return es;
}

int symtab_resolves(const char *name) {
   unsigned i, num;
   struct externsym *es;

   num = externsymarray_num(&externsyms);
   for (i=0; i<num; i++) {
      es = externsymarray_get(&externsyms, i);
      if (es->defn == NULL && !strcmp(name, es->name)) {
	 return 1;
      }
   }
   return 0;
}

void symtab_add(const char *fromfile, struct gensym *gsm,
		 unsigned outputsym_id) {
   unsigned i, num;
   struct externsym *es;
   struct mysym *ms;

   assert(gsm->gsm_flags & GSMF_GLOBL);

   ms = mysym_create(fromfile, gsm, outputsym_id);

   num = externsymarray_num(&externsyms);
   for (i=0; i<num; i++) {
      es = externsymarray_get(&externsyms, i);
      if (!strcmp(gsm->gsm_name, es->name)) {
	 ms->ref = es;
	 break;
      }
   }

   if (ms->ref == NULL) {
      /*
       * Symbol not already known
       */
      ms->ref = externsym_create(gsm, ms);
      mysymarray_add(&mysyms, ms);
      return;
   }

   /*
    * Symbol was already known
    */

   if (gsm->gsm_section == GSX_UNDEF) {
      /*
       * We're an undefined reference to it
       */
      if (ms->ref->firstuse == NULL) {
	 ms->ref->firstuse = ms;
      }
      mysymarray_add(&mysyms, ms);
      return;
   }

   /*
    * At this point, we're a definition of a known symbol
    */

   if (ms->ref->defn == NULL) {
      /*
       * No previous definition
       */
      ms->ref->defn = ms;
      mysymarray_add(&mysyms, ms);
      return;
   }

   if (gsm->gsm_flags & GSMF_WEAK) {
      /*
       * Previous definition, but we're a weak symbol - ignore
       */
      mysym_destroy(ms);
      return;
   }

   if (ms->ref->defn->gsm->gsm_flags & GSMF_WEAK) {
      /*
       * Previous definition is weak, but we aren't - override
       */
      ms->ref->defn = ms;
      mysymarray_add(&mysyms, ms);
      return;
   }

   /*
    * At this point, we're a repeat definition. Check for commons.
    */
   if (gsm->gsm_section == GSX_COMMON) {
      if (ms->ref->defn->gsm->gsm_section != GSX_COMMON) {
	 prog_warn("%s: Warning: linking common symbol %s to "
		   "non-common definition in %s",
		   fromfile, gsm->gsm_name, ms->ref->defn->fromfile);
      }
      else {
	 /* both common, don't warn */
	 /* XXX what about warn-commons? */
      }
      mysymarray_add(&mysyms, ms);
      return;
   }

   /*
    * We're not common. Is the current definition common?
    */
   if (ms->ref->defn->gsm->gsm_section == GSX_COMMON) {
      prog_warn("%s: Warning: linking common symbol %s to "
		"non-common definition in %s",
		ms->ref->defn->fromfile, gsm->gsm_name, fromfile);
      /*
       * Make us the current definition, so multiple non-common definitions
       * will bomb out properly.
       */
      ms->ref->defn = ms;
      mysymarray_add(&mysyms, ms);
      return;
   }

   /*
    * Nothing is common or weak - multiple definition.
    */

   prog_warn("%s: Multiply defined symbol %s (previous definition in %s)",
	    fromfile, gsm->gsm_name, ms->ref->defn->fromfile);
   main_failed();

   mysym_destroy(ms);
}

/*
 * These symbols are providable by ld itself - but they can't be provided
 * until after layout, which happens after symtab_noundefs is called. (sigh)
 */
static const char *providable_syms[] = {
   "_etext",
   "_edata",
   "__bss_start",
   "_end",
   NULL
};

static int providable(const char *sym) {
   unsigned i;

   for (i=0; providable_syms[i]; i++) {
      if (!strcmp(sym, providable_syms[i])) {
	 return 1;
      }
   }
   return 0;
}

void symtab_noundefs(int allow_providable) {
   unsigned i, num;
   struct externsym *es;

   num = externsymarray_num(&externsyms);
   for (i=0; i<num; i++) {
      es = externsymarray_get(&externsyms, i);
      if (es->defn != NULL) {
	 continue;
      }
      if (allow_providable && providable(es->name)) {
	 continue;
      }
      assert(es->firstuse != NULL);
      prog_warn("Undefined symbol %s (first used in %s)",
		es->name, es->firstuse->fromfile);
      main_failed();
   }
}

void symtab_alloc_commons(void) {
   const u_machword alignment = TARGET_MAXALIGN;
   const u_machword alignmask = (1 << alignment)-1;

   struct externsym *es;
   struct mysymarray results;	/* symbols created */
   unsigned i, num;
   struct gensym *gsm;		/* gensym of symbol being created */
   struct mysym *ms;		/* symbol currently being created */
   struct gensect *gsx;		/* section created */
   unsigned sectnum;		/* section id from section.cc */
   u_machword offset;		/* section offset from section.cc */
   u_machword pos = 0;		/* current position for adding to section */

   mysymarray_init(&results);

   /*
    * Really, we should align by the minimum of TARGET_MAXALIGN and
    * the (log of the) size of the object. It would also be nice to
    * sort the commons by decreasing size to minimize space wastage.
    * FUTURE.
    */

   num = externsymarray_num(&externsyms);
   for (i=0; i<num; i++) {
      es = externsymarray_get(&externsyms, i);
      if (es->defn == NULL) {
	 continue;
      }
      if (es->defn->gsm->gsm_section != GSX_COMMON) {
	 continue;
      }

      /* align the position within the commons section */
      while (pos & alignmask) {
	 pos++;
      }

      /*
       * Make a new symbol to resolve the common.
       */

      gsm = gensym_create(es->name);
      gsm->gsm_value = pos;
      gsm->gsm_size = es->defn->gsm->gsm_size;
      gsm->gsm_section = GSX_INVALID;
      gsm->gsm_type = GSMT_DATA;
      gsm->gsm_flags = GSMF_GLOBL;

      ms = mysym_create("<commons>", gsm, GSM_INVALID);
      ms->ref = es;

      /*
       * Make this the definition.
       */
      ms->ref->defn = ms;

      /* update the position */
      pos += ms->gsm->gsm_size;

      /* remember all the new symbols */
      mysymarray_add(&results, ms);
   }

   if (mysymarray_num(&results) == 0) {
      /* wasn't anything to do */
      mysymarray_cleanup(&results);
      return;
   }

   /*
    * Now, make ourselves a .bss section.
    */

   gsx = gensect_create(".bss");
   gsx->gsx_vaddr = 0;
   gsx->gsx_size = pos;
   gsx->gsx_align = alignment; 
   gsx->gsx_flags = GSXF_ISBSS|GSXF_LOADABLE|GSXF_READPERM|GSXF_WRITEPERM;
   gsx->gsx_data = NULL;

   sectnum = section_add("<commons>", gsx, &offset);

   num = mysymarray_num(&results);
   for (i=0; i<num; i++) {
      ms = mysymarray_get(&results, i);
      ms->gsm->gsm_value += offset;
      ms->gsm->gsm_section = sectnum;
      ms->id = outputsym_add(ms->gsm);
   }

   /*
    * XXX: Did we really mean to drop all the new mysyms on the floor?
    * Should probably keep them in mysyms[]...
    */

   mysymarray_setsize(&results, 0);
   mysymarray_cleanup(&results);
}

void symtab_push_definitions(void) {
   unsigned i, num;
   struct mysym *ms;

   num = mysymarray_num(&mysyms);
   for (i=0; i<num; i++) {
      ms = mysymarray_get(&mysyms, i);
      assert(ms->ref);
      if (ms->ref->defn) {
	 outputsym_setdefn(ms->id, ms->ref->defn->id);
      }
   }
}

unsigned symtab_find(const char *sym) {
   unsigned i, num;
   struct externsym *es;

   num = externsymarray_num(&externsyms);
   for (i=0; i<num; i++) {
      es = externsymarray_get(&externsyms, i);
      if (!strcmp(es->name, sym)) {
	 if (es->defn != NULL) {
	    return es->defn->id;
	 }
      }
   }
   return GSM_INVALID;
}

////////////////////////////////////////////////////////////
// global init

void symtab_setup(void) {
   mysymarray_init(&mysyms);
   externsymarray_init(&externsyms);
}

void symtab_shutdown(void) {
   /* XXX: destroyall? */
   mysymarray_setsize(&mysyms, 0);
   externsymarray_setsize(&externsyms, 0);
   
   mysymarray_cleanup(&mysyms);
   externsymarray_cleanup(&externsyms);
}
