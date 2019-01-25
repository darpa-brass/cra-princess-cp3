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

#include "binfile.h"
#include "elfbits.h"
#include "binfile_elf.h"

static void load_rels(struct binfile *bf) {
   unsigned numsections, i;

   if (!bf->sections_loaded) {
      load_sections(bf);
   }

   assert(!bf->rels_loaded);
   assert(relarray_num(&bf->rels) == 0);
   assert(uintarray_num(&bf->relsects) == 0);
   assert(boolarray_num(&bf->rels_are_rela) == 0);

   bf->rels_loaded = true;

   numsections = shdrarray_num(&bf->sections);
   for (i=0; i<numsections; i++) {
      bool isrela;
      unsigned symtabnum, targetsectionnum, numrels;
      Elf_Rela era;
      Elf_Rel er;
      off_t base;
      Elf_Shdr *sh, *symtab; // *targetsection;
      unsigned j;

      sh = shdrarray_getptr(&bf->sections, i);
      if (sh->sh_type == SHT_REL) {
	 isrela = false;
      }
      else if (sh->sh_type == SHT_RELA) {
	 isrela = true;
      }
      else {
	 continue;
      }

      symtabnum = sh->sh_link;
      targetsectionnum = sh->sh_info;
      symtab = shdrarray_getptr(&bf->sections, symtabnum);
      //targetsection = shdrarray_getptr(&bf->sections, targetsectionnum);

      if (symtab->sh_type != SHT_SYMTAB) {
	 /*
	  * bf_loadsect has already checked to make sure it's SYMTAB or
	  * DYNSYM, but we don't use DYNSYM here.
	  */
	 continue;
      }

      assert(sh->sh_entsize > 0);
      numrels = sh->sh_size / sh->sh_entsize;
      if (numrels == 0) {
	 continue;
      }

      base = sh->sh_offset;

      for (j=0; j<numrels; j++) {
	 if (isrela) {
	    elf_read_rela(bf->gf, base + j*sh->sh_entsize, &era);
	 }
	 else {
	    elf_read_rel(bf->gf, base + j*sh->sh_entsize, &er);
	    era.r_offset = er.r_offset;
	    era.r_info = er.r_info;
	    era.r_addend = 0;
	 }
	 relarray_add(&bf->rels, era);
	 uintarray_add(&bf->relsects, targetsectionnum);
	 boolarray_add(&bf->rels_are_rela, isrela);
      }
   }	    
}

unsigned binfile_numrelocs(struct binfile *bf) {
   if (!bf->rels_loaded) {
      load_rels(bf);
   }

   assert(relarray_num(&bf->rels) == uintarray_num(&bf->relsects));
   assert(relarray_num(&bf->rels) == boolarray_num(&bf->rels_are_rela));

   return relarray_num(&bf->rels);
}

struct genreloc *binfile_getreloc(struct binfile *bf, unsigned which) {
   Elf_Rela *er;
   struct genreloc *gr;

   if (!bf->rels_loaded) {
      load_rels(bf);
   }

   assert(relarray_num(&bf->rels) == uintarray_num(&bf->relsects));
   assert(relarray_num(&bf->rels) == boolarray_num(&bf->rels_are_rela));

   er = relarray_getptr(&bf->rels, which);

   gr = genreloc_create();
   gr->gr_addend = er->r_addend;
   gr->gr_offset = er->r_offset;
   gr->gr_section = uintarray_get(&bf->relsects, which);
   gr->gr_symbol = ELF_R_SYM(er->r_info);
#if defined(TARGET_ELF_USE_R_EXT)
   /*
    * XXX in the future someone might use the "data" for something
    * other than more addend, in which case this will not be
    * sufficient and we'll have to store the extra data and pass it
    * through the whole pipeline. But for now the only known uses
    * are as extra addend.
    *
    * Note that for this to work properly it's critical that the
    * gr_addend field be reliably set to 0 for .rel relocations, so
    * that the downstream pipeline can add the value it fetches out of
    * the section data to the existing value of gr_addend.
    *
    * Of course, since for platforms that are defined to use this thing,
    * theoretically the assembler is free to leave trash in the data
    * field for relocation types that don't use it, so just in case it
    * would be better to do the work to pass it through anyway, and
    * maybe confirm it's 0 for other relocation codes.
    */
   gr->gr_code = ELF_R_EXT_TYPE(er->r_info);
   gr->gr_addend += ELF_R_EXT_DATA(er->r_info);
#else
   gr->gr_code = ELF_R_TYPE(er->r_info);
#endif
   if (!boolarray_get(&bf->rels_are_rela, which)) {
      gr->gr_code = -gr->gr_code;
   }

   return gr;
}
