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

#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "array.h"
#include "arlib.h"
#include "genfile.h"
#include "binfile.h"

#include "section.h"
#include "symtab.h"
#include "outputsym.h"
#include "outputrel.h"
#include "loadfile.h"

/* this should probably live somewhere central */
DECLARRAY_FULL(u_machwordarray, u_machword, static inline);
DEFARRAY_FULL(u_machwordarray, u_machword, static inline);

/* this too */
DECLARRAY(binfile, static inline);
DEFARRAY(binfile, static inline);

/*
 * These are here because they parallel (slightly) part of link_bin().
 */
void symbol_commandline_undef(const char *sym) {
   struct gensym *gsm;
   unsigned id;

   gsm = gensym_create(sym);
   gsm->gsm_value = 0;
   gsm->gsm_size = 0;
   gsm->gsm_section = GSX_UNDEF;
   gsm->gsm_type = GSMT_UNKNOWN;
   gsm->gsm_flags = GSMF_GLOBL;

   id = outputsym_add(gsm);
   symtab_add("<command-line>", gsm, id);
}

void symbol_ld_provided(const char *sym, u_machword addr) {
   struct gensym *gsm;
   unsigned id;

   if (!symtab_resolves(sym)) {
      return;
   }

   gsm = gensym_create(sym);
   gsm->gsm_value = addr;
   gsm->gsm_size = 0;
   gsm->gsm_section = GSX_ABS;
   gsm->gsm_type = GSMT_DATA;
   gsm->gsm_flags = GSMF_GLOBL;

   id = outputsym_add(gsm);
   symtab_add("<ld-provided>", gsm, id);
}

static void link_bin(struct binfile *ef, const char *filename, int Rflag) {
   bool isshlib;
   unsigned i, nsx, sect, sym;
   u_machword off;
   struct u_machwordarray section_offsets;
   struct uintarray section_numbers;

   isshlib = binfile_gettype(ef) == BFT_LIB;

   file_setname(filename);

   /*
    * first, get the linkable sections. load the data for each section
    * and pass it off to section.cc. this gives us an offset to add to
    * the locations of symbols within the section.
    */

   nsx = binfile_numsections(ef);
   u_machwordarray_init(&section_offsets);
   u_machwordarray_setsize(&section_offsets, nsx);
   uintarray_init(&section_numbers);
   uintarray_setsize(&section_numbers, nsx);

   for (i=0; i<nsx; i++) {
      struct gensect *gsx;

      u_machwordarray_set(&section_offsets, i, 0);
      uintarray_set(&section_numbers, i, GSX_INVALID);

      gsx = binfile_getsection(ef, i, 1);
      if (gsx == NULL) {
	 /* binfmt-internal section of some kind */
	 continue;
      }

      if (isshlib) {
	 /* don't actually link chunks from shared libs */
	 gensect_destroy(gsx);
	 continue;
      }

      if (Rflag) {
	 /*
	  * Don't actually link chunks from Rflag objs either; 
	  * arrange to convert the symbols to absolute.
	  */
	 u_machwordarray_set(&section_offsets, i, gsx->gsx_vaddr);
	 uintarray_set(&section_numbers, i, GSX_ABS);
	 gensect_destroy(gsx);
	 continue;
      }

      sect = section_add(binfile_getname(ef), gsx, &off);
      u_machwordarray_set(&section_offsets, i, off);
      uintarray_set(&section_numbers, i, sect);
   }

   /*
    * second, get the symbols.
    *
    * all symbols are copied to outputsym.cc.
    * outputsym hands back a symbol id number that we remember for
    * translating relocations.
    *
    * linkable (those that aren't local) symbols are sent to symtab.cc.
    * symtab will tell outputsym which symbols resolve undefs.
    */

   unsigned nsm = binfile_numsymbols(ef);
   struct uintarray symbol_numbers;
   uintarray_init(&symbol_numbers);
   uintarray_setsize(&symbol_numbers, nsm);

   assert(nsm > 0);
   for (i=0; i<nsm; i++) {
      struct gensym *gsm;
      
      gsm = binfile_getsymbol(ef, i);
      if (gsm == NULL) {
	 /* shouldn't ordinarily happen */
	 uintarray_set(&symbol_numbers, i, GSM_INVALID);
	 continue;
      }

      if (gensect_isspecialnum(gsm->gsm_section) == false) {
	 gsm->gsm_value += u_machwordarray_get(&section_offsets, gsm->gsm_section);
	 gsm->gsm_section = uintarray_get(&section_numbers, gsm->gsm_section);
      }

      sym = outputsym_add(gsm);
      uintarray_set(&symbol_numbers, i, sym);

      if (gsm->gsm_name && (gsm->gsm_flags & GSMF_GLOBL)) {
	 symtab_add(binfile_getname(ef), gsm, sym);
      }
   }

   if (isshlib || Rflag) {
      /* don't need relocations from this file */
      goto done;
   }

   /*
    * third, get the relocations.
    *
    * translate the symbol ids from the file to the ones managed by
    * outputsym. send these to outputrel.cc. 
    */
   unsigned nr = binfile_numrelocs(ef);
   for (i=0; i<nr; i++) {
      struct genreloc *gr;

      gr = binfile_getreloc(ef, i);
      if (gr==NULL) {
	 continue;
      }

      /* binfile_getreloc should trap anything failing this check */
      assert(gensect_isspecialnum(gr->gr_section) == false);

      gr->gr_offset += u_machwordarray_get(&section_offsets, gr->gr_section);
      gr->gr_section = uintarray_get(&section_numbers, gr->gr_section);
      gr->gr_symbol = uintarray_get(&symbol_numbers, gr->gr_symbol);

      outputreloc_add(gr);
   }

 done:
   u_machwordarray_setsize(&section_offsets, 0);
   u_machwordarray_cleanup(&section_offsets);
   uintarray_setsize(&section_numbers, 0);
   uintarray_cleanup(&section_numbers);
   uintarray_setsize(&symbol_numbers, 0);
   uintarray_cleanup(&symbol_numbers);

   file_clearname();
}

static int consider_bin(struct binfile *ef) {
   const char *name;
   unsigned i, num;

   num = binfile_numsymbols(ef);
   assert(num>0);

   for (i=0; i<num; i++) {
      name = binfile_getprovidedsymbol(ef, i);
      if (!name) {
	 continue;
      }
      if (symtab_resolves(name)) {
	 return 1;
      }
   }
   return 0;
}

static void load_ar(struct arfile *arf, int Rflag) {
   struct boolarray used;
   struct binfilearray eftable;
   bool done;
   unsigned i, num;
   const char *subname;
   char *reportname;
   struct genfile *gf;
   struct binfile *bf;
   
   num = ar_getnumfiles(arf);
   boolarray_init(&used);
   boolarray_setsize(&used, num);
   binfilearray_init(&eftable);
   binfilearray_setsize(&eftable, num);

   for (i=0; i<num; i++) {
      subname = ar_getname(arf, i);
      reportname = ar_mkreportname(arf, subname);
      gf = ar_opensubfile(arf, subname);
      assert(gf != NULL);

      bf = binfile_bind(reportname, gf);
      if (bf == NULL) {
	 prog_warn("%s: Warning: Unrecognized file format (skipping)",
		   reportname);
	 boolarray_set(&used, i, true);
      }
      else if (binfile_numsymbols(bf) == 0) {
	 // XXX disable for now, arm libgcc is full of empty files
	 //prog_warn("%s: Warning: No symbols (skipping)", reportname);
	 boolarray_set(&used, i, true);
	 binfile_destroy(bf);
	 bf = NULL;
      }
      else {
	 boolarray_set(&used, i, false);
      }
      binfilearray_set(&eftable, i, bf);

      dostrfree(reportname);
   }

   done = false;
   while (!done) {
      done = true;
      for (i=0; i<num; i++) {
	 if (boolarray_get(&used, i) == false) {
	    bf = binfilearray_get(&eftable, i);
	    if (consider_bin(bf)) {
	       subname = ar_getname(arf, i);
	       reportname = ar_mkreportname(arf, subname);
	       link_bin(bf, reportname, Rflag);
	       dostrfree(reportname);
	       binfile_destroy(bf);
	       binfilearray_set(&eftable, i, NULL);
	       boolarray_set(&used, i, true);
	       done = false;
	    }
	 }
      }
   }

   for (i=0; i<num; i++) {
      bf = binfilearray_get(&eftable, i);
      if (boolarray_get(&used, i)) {
	 assert(bf == NULL);
      }
      else {
	 binfile_destroy(bf);
      }
   }
   binfilearray_setsize(&eftable, 0);
   binfilearray_cleanup(&eftable);
   boolarray_setsize(&used, 0);
   boolarray_cleanup(&used);
}

void loadfile(const char *filename, int Rflag) {
   struct arfile *arf;
   struct genfile *gf;
   struct binfile *ef;

   arf = ar_open(filename, "r", false);
   if (arf) {
      load_ar(arf, Rflag);
      ar_close(arf);
   }
   else {
      gf = genfile_open(filename, "r");
      if (!gf) {
	 prog_err("Cannot open %s", filename);
      }

      ef = binfile_bind(filename, gf);
      if (ef==NULL) {
	 prog_err("%s: Unrecognized file format", filename);
      }
      else if (binfile_numsymbols(ef) == 0) {
	 prog_err("%s: No symbols (file is unlinkable)", filename);
      }
      else {
	 link_bin(ef, filename, Rflag);
	 binfile_destroy(ef);
      }
   }
}
