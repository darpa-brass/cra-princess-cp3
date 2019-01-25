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

#ifndef BINFILE_ELF_H
#define BINFILE_ELF_H

struct genfile; /* from genfile.h */
struct elfstrtab; /* from elfstrtab.h */

#include "array.h"
#include "elf.h"


#ifndef BINFILE_INLINE
#define BINFILE_INLINE INLINE
#endif

/* arrays of ELF structures; give them sensibile names */
DECLARRAY_FULL(shdrarray, Elf_Shdr, BINFILE_INLINE);
DECLARRAY_FULL(phdrarray, Elf_Phdr, BINFILE_INLINE);
DECLARRAY_FULL(symarray, Elf_Sym, BINFILE_INLINE);
DECLARRAY_FULL(relarray, Elf_Rela, BINFILE_INLINE);
DEFARRAY_FULL(shdrarray, Elf_Shdr, BINFILE_INLINE);
DEFARRAY_FULL(phdrarray, Elf_Phdr, BINFILE_INLINE);
DEFARRAY_FULL(symarray, Elf_Sym, BINFILE_INLINE);
DEFARRAY_FULL(relarray, Elf_Rela, BINFILE_INLINE);

/*
 * Binfile structure for ELF
 */
struct binfile {
   /* identity */
   char *name;
   struct genfile *gf;

   /* what we've loaded, if any */
   bool ehdr_loaded;
   bool sections_loaded;
   bool syms_loaded;
   bool rels_loaded;

   /* the main file header */
   Elf_Ehdr ehdr;

   /* section data */
   struct shdrarray sections;
   struct elfstrtab *shstrtab;

   /* symbol data */
   struct symarray syms;
   struct elfstrtab *symstrtab;

   /* reloc data */
   struct relarray rels;
   struct uintarray relsects;
   struct boolarray rels_are_rela;

   /* used only for output, to translate ld's index #s to our index #s */
   struct uintarray section_lookup;
   struct uintarray symbol_lookup;

   /* used only for output, to hold the actual section data */
   struct ptrarray sectiondata;
};

struct binfile *binfile_create(const char *name, struct genfile *gf);

void load_sections(struct binfile *bf);


#endif /* BINFILE_ELF_H */
