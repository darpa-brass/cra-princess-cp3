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
#include "elfstrtab.h"
#include "binfile_elf.h"

static unsigned findsection(struct binfile *bf, const char *sect) {
   unsigned i, num;
   Elf_Shdr *sh;
   const char *name;

   assert(bf->sections_loaded);

   num = shdrarray_num(&bf->sections);
   for (i=0; i < num; i++) {
      sh = shdrarray_getptr(&bf->sections, i);
      name = elfstrtab_get(bf->shstrtab, sh->sh_name);

      /* checked in load_sections() */
      assert(name != NULL);
      if (i == 0) {
	 assert(*name == 0);
      }
      else {
	 assert(*name != 0);
      }

      if (!strcmp(name, sect)) {
	 return i;
      }
   }
   /* out-of-range value for "not found" */
   return bf->ehdr.e_shnum;
}

static void load_syms(struct binfile *bf) {
   unsigned numsyms, i;
   unsigned strtabnum, symtabnum;
   Elf_Shdr *symtab, *strtab;
   unsigned entsize;
   const char *strtabname;
   off_t base;

   if (!bf->sections_loaded) {
      load_sections(bf);
   }

   assert(!bf->syms_loaded);
   assert(symarray_num(&bf->syms) == 0);
   assert(bf->symstrtab == NULL);

   bf->syms_loaded = true;

   symtabnum = findsection(bf, ".symtab");
   if (symtabnum >= bf->ehdr.e_shnum) {
      /* no symbols */
      return;
   }

   symtab = shdrarray_getptr(&bf->sections, symtabnum);
   if (symtab->sh_type != SHT_SYMTAB) {
      prog_err("%s: Corrupt ELF file: symbol table has wrong section type",
	       bf->name);
   }
   entsize = symtab->sh_entsize;
   if (entsize < sizeof(Elf_Sym)) {
      prog_err("%s: Corrupt ELF file: symbol table entry size too small",
	       bf->name);
   }

   numsyms = symtab->sh_size / entsize;
   if (numsyms==0) {
      return;
   }

   strtabnum = symtab->sh_link;
   if (strtabnum >= shdrarray_num(&bf->sections)) {
      prog_err("%s: Corrupt ELF file: symbol string table index out of range",
	       bf->name);
   }

   strtab = shdrarray_getptr(&bf->sections, strtabnum);
   strtabname = elfstrtab_get(bf->shstrtab, strtab->sh_name);
   assert(strtabname != NULL);
   assert(*strtabname != 0);
   if (strcmp(strtabname, ".strtab")) {
      prog_err("%s: Corrupt ELF file: symbol string table has wrong name %s",
	       bf->name, strtabname);
   }

   if (strtab->sh_type != SHT_STRTAB) {
      prog_err("%s: Corrupt ELF file: symbol string table has wrong type %u",
	       bf->name, strtab->sh_type);
   }

   bf->symstrtab = elfstrtab_load(bf->gf, strtab->sh_offset, strtab->sh_size);

   symarray_setsize(&bf->syms, numsyms);
   base = symtab->sh_offset;
   for (i=0; i<numsyms; i++) {
      elf_read_sym(bf->gf, base + i*entsize, symarray_getptr(&bf->syms, i));
   }
}


unsigned binfile_numsymbols(struct binfile *bf) {
   if (!bf->syms_loaded) {
      load_syms(bf);
   }
   return symarray_num(&bf->syms);
}

struct gensym *binfile_getsymbol(struct binfile *bf, unsigned which) {
   Elf_Sym *es;
   struct gensym *gsm;
   const char *name;
   Elf_Shdr *shdr;

   if (!bf->syms_loaded) {
      load_syms(bf);
   }

   es = symarray_getptr(&bf->syms, which);

   if (which == 0 && es->st_name == 0 && es->st_shndx == 0) {
      /* invalid/meaningless first symbol */
      return NULL;
   }

   name = elfstrtab_get(bf->symstrtab, es->st_name);
   if (name == NULL) {
      prog_err("%s: Corrupt ELF file (invalid symbol name)", bf->name);
   }
   if (*name == 0) {
      /* anonymous private symbol for relocation only */
      name = NULL;
   }

   gsm = gensym_create(name);
   gsm->gsm_value = es->st_value;
   gsm->gsm_size = es->st_size;

   switch (ELF_ST_BIND(es->st_info)) {
    case STB_LOCAL:
     gsm->gsm_flags = 0;
     break;
    case STB_GLOBAL:
     gsm->gsm_flags = GSMF_GLOBL;
     break;
    case STB_WEAK:
     gsm->gsm_flags = GSMF_GLOBL|GSMF_WEAK;
     break;
    default:
     prog_err("%s: Corrupt ELF file (invalid symbol binding)", bf->name);
     break;
   }

   switch (ELF_ST_TYPE(es->st_info)) {
    case STT_NOTYPE:
     gsm->gsm_type = GSMT_UNKNOWN;
     break;
    case STT_OBJECT:
     gsm->gsm_type = GSMT_DATA;
     break;
    case STT_FUNC:
     gsm->gsm_type = GSMT_CODE;
     break;
    case STT_FILE:
     gsm->gsm_type = GSMT_FILENAME;
     break;
    case STT_SECTION:
     /* XXX */
     gsm->gsm_type = GSMT_UNKNOWN;
     break;
    case STT_SPARC_REGISTER:
     /* XXX */
     gsm->gsm_type = GSMT_UNKNOWN;
     break;
    default:
     prog_err("%s: Corrupt ELF file (invalid symbol type %u)", bf->name,
	      ELF_ST_TYPE(es->st_info));
     break;
   }

   switch (es->st_shndx) {
    case SHN_UNDEF:
     gsm->gsm_section = GSX_UNDEF;
     gsm->gsm_flags |= GSMF_GLOBL;
     break;
    case SHN_ABS:
     gsm->gsm_section = GSX_ABS;
     break;
    case SHN_COMMON:
     gsm->gsm_section = GSX_COMMON;
     break;
    default:
     if (es->st_shndx >= bf->ehdr.e_shnum) {
	prog_err("%s: Corrupt ELF file (invalid section %u for "
		 "symbol %u%s%s)", 
		 bf->name, es->st_shndx, which,
		 name ? ", " : "", name ? name : "");
     }
     gsm->gsm_section = es->st_shndx;
     shdr = shdrarray_getptr(&bf->sections, es->st_shndx);

     /* generic symbols are always section-relative */
     gsm->gsm_value -= shdr->sh_addr;

     break;
   }

   return gsm;
}


const char *binfile_getprovidedsymbol(struct binfile *bf, unsigned which) {
   Elf_Sym *es;
   const char *name;

   if (!bf->syms_loaded) {
      load_syms(bf);
   }

   es = symarray_getptr(&bf->syms, which);

   /* if the symbol is undefined, we obviously don't provide it */
   if (es->st_shndx == SHN_UNDEF) {
      return NULL;
   }

   /* symbols without global binding aren't provided */
   if (ELF_ST_BIND(es->st_info) != STB_GLOBAL && 
       ELF_ST_BIND(es->st_info) != STB_WEAK) {
      return NULL;
   }

   /* and, it must have a name. */
   name = elfstrtab_get(bf->symstrtab, es->st_name);
   if (name==NULL || *name==0) {
      /* anonymous private symbol for relocation only */
      return NULL;
   }

   return name;
}
