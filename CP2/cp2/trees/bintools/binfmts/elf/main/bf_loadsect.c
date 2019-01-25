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

#include "intops.h"
#include "genfile.h"
#include "binfile.h"
#include "elf.h"
#include "elfbits.h"
#include "elfstrtab.h"
#include "binfile_elf.h"

static void elf_check_shdr(const char *filename, 
			   const struct shdrarray *sections, unsigned which,
			   struct elfstrtab *shstrtab, const Elf_Ehdr *eh)
{
   const char *name;
   unsigned minentsize;
   Elf_Shdr *sh, *sh2;

   sh = shdrarray_getptr(sections, which);

   if (sh->sh_type == SHT_NULL) {
      if (sh->sh_name || sh->sh_flags || sh->sh_addr ||
	  sh->sh_size || sh->sh_link || sh->sh_info || sh->sh_addralign ||
	  sh->sh_entsize) {
	 /* allow sh->sh_offset to be nonzero */
	 prog_err("%s: Corrupt ELF file: Invalid SHT_NULL section (%u)",
		  filename, which);
      }
      return;
   }

   /* Every section (besides SHT_NULL ones) must have a nonempty name */
   name = elfstrtab_get(shstrtab, sh->sh_name);
   if (name==NULL) {
      prog_err("%s: Corrupt ELF file: section %u name index out of range",
	       filename, which);
   }
   if (*name==0) {
      prog_err("%s: Corrupt ELF file: section %u has empty name",
	       filename, which);
   }

   /* elf section flags we don't support but can ignore for now (XXX) */
   /* XXX: ignoring SHF_LINK_ORDER is probably really not safe */
#define IGNFLAGS  (SHF_MERGE|SHF_GROUP|SHF_LINK_ORDER)
   sh->sh_flags = ~((~sh->sh_flags)|IGNFLAGS);

   /* elf section flags we support */
#define OKFLAGS   (SHF_WRITE|SHF_ALLOC|SHF_EXECINSTR|SHF_STRINGS|SHF_INFO_LINK)

   if (~((~sh->sh_flags)|OKFLAGS)) {
     prog_err("%s: Corrupt ELF file (section %s: unknown flags 0x%jx)", 
	      filename, name, (uintmax_t) ~((~sh->sh_flags)|OKFLAGS|IGNFLAGS));
   }

   switch (sh->sh_type) {
    case SHT_PROGBITS:
    case SHT_SYMTAB:
    case SHT_STRTAB:
    case SHT_RELA:
    case SHT_HASH:
    case SHT_DYNAMIC:
    case SHT_NOTE:
    case SHT_NOBITS:
    case SHT_REL:
    case SHT_SHLIB:
    case SHT_DYNSYM:
    case SHT_INIT_ARRAY:
    case SHT_FINI_ARRAY:
    case SHT_PREINIT_ARRAY:
    case SHT_GROUP:
    case SHT_GNU_ATTRIBUTES:
    case SHT_ARM_EXIDX:
    case SHT_ARM_ATTRIBUTES:
    case SHT_MIPS_REGINFO:
     break;
    default:
     prog_err("%s: Corrupt ELF file (section %s: invalid type %u)", filename,
	      name, (unsigned) sh->sh_type);
     break;
   }

   switch (sh->sh_type) {
    case SHT_PROGBITS: break;
    default:
     if (sh->sh_flags & SHF_EXECINSTR) {
	prog_err("%s: Corrupt ELF file (section %s: code in non-code section)",
		 filename, name);
     }
     break;
   }

   switch (sh->sh_type) {
    case SHT_PROGBITS: break;
    case SHT_NOBITS: break;
    case SHT_NOTE: break;
    case SHT_INIT_ARRAY: break;
    case SHT_FINI_ARRAY: break;
    case SHT_PREINIT_ARRAY: break;
    case SHT_GROUP:
    case SHT_GNU_ATTRIBUTES:
    case SHT_ARM_EXIDX:
    case SHT_ARM_ATTRIBUTES:
    case SHT_MIPS_REGINFO: break;
    default:
     if (sh->sh_flags & SHF_WRITE) {
	prog_err("%s: Corrupt ELF file (section %s: data in non-data section)",
		 filename, name);
     }
     if (sh->sh_flags & SHF_ALLOC) {
	prog_err("%s: Corrupt ELF file (section %s: loadable section of "
		 "invalid type", filename, name);
     }
     break;
   }

   
   switch (sh->sh_type) {
    case SHT_ARM_EXIDX:
     if (sh->sh_link == SHN_BEFORE || sh->sh_link == SHN_AFTER) {
	break;
     }
     /* FALLTHROUGH */
    case SHT_HASH:
    case SHT_DYNAMIC:
    case SHT_REL:
    case SHT_RELA:
    case SHT_SYMTAB: 
    case SHT_DYNSYM:
    case SHT_GROUP:
     if (sh->sh_link >= eh->e_shnum) {
	prog_err("%s: Corrupt ELF file (section %s linked to nowhere)",
		 filename, name);
     }
     break;
    default:
     if (sh->sh_link != SHN_UNDEF) {
	prog_err("%s: Corrupt ELF file (section %s should not have link)",
		 filename, name);
     }
     break;
   }

   switch (sh->sh_type) {
    case SHT_RELA:
    case SHT_REL:
     if (sh->sh_info >= eh->e_shnum) {
	prog_err("%s: Corrupt ELF file (relocations %s applied to nowhere)",
		 filename, name);
     }
     break;
    case SHT_SYMTAB: 
    case SHT_DYNSYM:
    case SHT_GROUP:
     break;
    default:
     if (sh->sh_info != 0) {
	prog_err("%s: Corrupt ELF file (section %s should not have info)",
		 filename, name);
     }
     break;
   }

   switch (sh->sh_type) {
    case SHT_HASH:
     sh2 = shdrarray_getptr(sections, sh->sh_link);
     if (sh2->sh_type != SHT_SYMTAB && sh2->sh_type != SHT_DYNSYM) {
	prog_err("%s: Corrupt ELF file (section %s hashes invalid section %s)",
		 filename, name, 
		 elfstrtab_get(shstrtab, sh2->sh_name));
     }
     break;
    case SHT_DYNAMIC:
     sh2 = shdrarray_getptr(sections, sh->sh_link);
     if (sh2->sh_type != SHT_SYMTAB && sh2->sh_type != SHT_DYNSYM) {
	prog_err("%s: Corrupt ELF file (section %s uses invalid section %s)",
		 filename, name,
		 elfstrtab_get(shstrtab, sh2->sh_name));
     }
     break;
    case SHT_REL:
    case SHT_RELA:
     sh2 = shdrarray_getptr(sections, sh->sh_link);
     if (sh2->sh_type != SHT_SYMTAB && sh2->sh_type != SHT_DYNSYM) {
	prog_err("%s: Corrupt ELF file (section %s uses invalid section %s)",
		 filename, name,
		 elfstrtab_get(shstrtab, sh2->sh_name));
     }
     sh2 = shdrarray_getptr(sections, sh->sh_info);
     if (sh2->sh_type != SHT_PROGBITS &&
	 sh2->sh_type != SHT_INIT_ARRAY && sh2->sh_type != SHT_FINI_ARRAY &&
	 sh2->sh_type != SHT_PREINIT_ARRAY &&
	 sh2->sh_type != SHT_ARM_EXIDX) {
	prog_err("%s: Corrupt ELF file (section %s relocates "
		 "invalid section %s)",
		 filename, name,
		 elfstrtab_get(shstrtab, sh2->sh_name));
     }
     break;
    case SHT_SYMTAB:
    case SHT_DYNSYM:
     sh2 = shdrarray_getptr(sections, sh->sh_link);
     if (sh2->sh_type != SHT_STRTAB) {
	prog_err("%s: Corrupt ELF file (section %s uses invalid section %s)",
		 filename, name,
		 elfstrtab_get(shstrtab, sh2->sh_name));
     }
     break;
    default:
     break;
   }

   minentsize = 0;
   switch (sh->sh_type) {
    case SHT_SYMTAB: 
    case SHT_DYNSYM:
     minentsize = sizeof(Elf_Sym);
     break;
    case SHT_RELA:
     minentsize = sizeof(Elf_Rela);
     break;
    case SHT_REL:
     minentsize = sizeof(Elf_Rel);
     break;
    case SHT_PROGBITS:
    case SHT_STRTAB:
    case SHT_HASH:
    case SHT_DYNAMIC:
    case SHT_INIT_ARRAY:
    case SHT_FINI_ARRAY:
    case SHT_PREINIT_ARRAY:
    case SHT_NOTE:
    case SHT_NOBITS:
    case SHT_SHLIB:
     break;
    case SHT_MIPS_REGINFO:
     minentsize = 24;
     break;
   }

   if (minentsize > 0) {
      if (sh->sh_entsize < minentsize) {
	 prog_err("%s: Corrupt ELF file: section %s entry size %u (%u min)",
		  filename, name, (unsigned) sh->sh_entsize, minentsize);
      }
   }
   else {
#if 0 /* it seems some other sections have entry sizes */
      /* XXX figure out which ones, why, and what, and check them... */
      if (sh->sh_entsize != 0) {
	 prog_err("%s: Corrupt ELF file: section %s has entry size (%u)",
		  filename, name, (unsigned) sh->sh_entsize);
      }
#endif
   }

   switch (sh->sh_type) {
    case SHT_SYMTAB:
     if (strcmp(name, ".symtab")) {
	prog_err("%s: Corrupt ELF file: symbol table called %s",
		 filename, name);
     }
     break;
    case SHT_DYNSYM:
     if (strcmp(name, ".dynsym")) {
	prog_err("%s: Corrupt ELF file: dynsym table called %s",
		 filename, name);
     }
     break;
    default:
     break;
   }
}

static struct elfstrtab *elf_load_sections(struct genfile *gf, 
					   const Elf_Ehdr *eh,
					   struct shdrarray *sections)
{
   unsigned i;
   off_t pos;
   bool seen_symtab, seen_dynsym;
   struct elfstrtab *shstrtab;
   Elf_Shdr *shstrtab_shdr, *shdr;

   shdrarray_setsize(sections, eh->e_shnum);
   for (i=0; i<eh->e_shnum; i++) {
      pos = eh->e_shoff + i*eh->e_shentsize;
      elf_read_shdr(gf, pos, shdrarray_getptr(sections, i));
   }

   /* this was already checked by elf_check_ehdr */
   assert(eh->e_shstrndx < eh->e_shnum);

   /* get the section name table */
   shstrtab_shdr = shdrarray_getptr(sections, eh->e_shstrndx);
   if (shstrtab_shdr->sh_type != SHT_STRTAB) {
      prog_err("%s: Corrupt ELF file: section name table not a string table",
	       genfile_getname(gf));
   }
   if (shstrtab_shdr->sh_flags & (SHF_WRITE|SHF_ALLOC|SHF_EXECINSTR)) {
      prog_err("%s: Corrupt ELF file: section name table has flags 0x%lx",
	       genfile_getname(gf),
	       (unsigned long) shstrtab_shdr->sh_flags);
   }

   shstrtab = elfstrtab_load(gf, shstrtab_shdr->sh_offset,
			     shstrtab_shdr->sh_size);
   assert(shstrtab != NULL);

   for (i=0; i<eh->e_shnum; i++) {
      elf_check_shdr(genfile_getname(gf), sections, i, shstrtab, eh);
   }

   /* make sure shstrtab has the right name */
   if (strcmp(elfstrtab_get(shstrtab, shstrtab_shdr->sh_name),
	      ".shstrtab")) {
      prog_err("%s: Corrupt ELF file: section name table has wrong name %s",
	       genfile_getname(gf),
	       elfstrtab_get(shstrtab, shstrtab_shdr->sh_name));
   }

   /* make sure section 0 is what it's supposed to be */
   if (shdrarray_getptr(sections, 0)->sh_type != SHT_NULL) {
      prog_err("%s: Corrupt ELF file: section 0 not SHT_NULL",
	       genfile_getname(gf));
   }

   /* only allowed to be one each SHT_SYMTAB and SHT_DYNSYM */
   seen_symtab = false;
   seen_dynsym = false;
   for (i=0; i<eh->e_shnum; i++) {
      shdr = shdrarray_getptr(sections, i);
      if (shdr->sh_type == SHT_SYMTAB) {
	 if (seen_symtab) {
	    prog_err("%s: Corrupt ELF file (multiple symbol tables)",
		     genfile_getname(gf));
	 }
	 seen_symtab = true;
      }
      if (shdr->sh_type == SHT_DYNSYM) {
	 if (seen_dynsym) {
	    prog_err("%s: Corrupt ELF file (multiple dynsym tables)",
		     genfile_getname(gf));
	 }
	 seen_dynsym = true;
      }
   }

   return shstrtab;
}

void load_sections(struct binfile *bf) {
   assert(bf->ehdr_loaded);
   assert(!bf->sections_loaded);

   bf->shstrtab = elf_load_sections(bf->gf, &bf->ehdr, &bf->sections);

   bf->sections_loaded = true;
}

unsigned binfile_numsections(struct binfile *bf) {
   if (!bf->sections_loaded) {
      load_sections(bf);
   }

   return shdrarray_num(&bf->sections);
}

struct gensect *binfile_getsection(struct binfile *bf, unsigned which,
				   bool loaddata) {
   Elf_Shdr *sh;
   struct gensect *gsx;
   const char *name;
   unsigned flags;

   if (!bf->sections_loaded) {
      load_sections(bf);
   }

   sh = shdrarray_getptr(&bf->sections, which);
   name = elfstrtab_get(bf->shstrtab, sh->sh_name);

   flags = 0;
   switch (sh->sh_type) {
    case SHT_NULL:
    case SHT_SYMTAB:
    case SHT_STRTAB:
    case SHT_RELA:
    case SHT_HASH:
    case SHT_DYNAMIC:
    case SHT_REL:
    case SHT_SHLIB:
    case SHT_DYNSYM:
    case SHT_GROUP:
    case SHT_GNU_ATTRIBUTES:
    case SHT_ARM_ATTRIBUTES:
     return NULL;
    case SHT_PROGBITS:
    case SHT_INIT_ARRAY:
    case SHT_FINI_ARRAY:
    case SHT_PREINIT_ARRAY:
    case SHT_ARM_EXIDX:
     break;
    case SHT_NOTE:
     flags |= GSXF_ISNOTE;
     break;
    case SHT_NOBITS:
     flags |= GSXF_ISBSS;
     break;
    case SHT_MIPS_REGINFO:
     break;
    default:
     prog_err("%s: Corrupt ELF file: Invalid section type %d",
	      bf->name, sh->sh_type);
     break;
   }

   flags |= GSXF_READPERM;
   if (sh->sh_flags & SHF_WRITE) {
      flags |= GSXF_WRITEPERM;
   }
   if (sh->sh_flags & SHF_EXECINSTR) {
      flags |= GSXF_EXECPERM;
   }
   if (sh->sh_flags & SHF_ALLOC) {
      flags |= GSXF_LOADABLE;
   }

   gsx = gensect_create(name);
   gsx->gsx_vaddr = sh->sh_addr;
   gsx->gsx_flags = flags;
   gsx->gsx_size = sh->sh_size;
   /* XXX shouldn't this check and object if it's not a power of 2? */
   /* XXX also it should check for ilog2 failing */
   gsx->gsx_align = ilog2(sh->sh_addralign);

   if (loaddata && (flags & GSXF_ISBSS) == 0) {
      gsx->gsx_data = domalloc(gsx->gsx_size);
      genfile_read(bf->gf, sh->sh_offset, gsx->gsx_data, gsx->gsx_size);
   }
   else {
      gsx->gsx_data = NULL;
   }

   return gsx;
}
