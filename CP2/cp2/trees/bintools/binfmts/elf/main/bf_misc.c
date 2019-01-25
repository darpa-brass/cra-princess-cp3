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

#include "mem.h"
#include "genfile.h"
#include "binfile.h"
#include "elfbits.h"
#include "elfstrtab.h"
#define BINFILE_INLINE
#include "binfile_elf.h"

struct binfile *binfile_create(const char *name, struct genfile *gf) {
   struct binfile *bf;

   bf = domalloc(sizeof(*bf));

   bf->name = dostrdup(name);
   bf->gf = gf;

   bf->ehdr_loaded = false;
   bf->sections_loaded = false;
   bf->syms_loaded = false;
   bf->rels_loaded = false;

   memset(&bf->ehdr, 0, sizeof(bf->ehdr));

   shdrarray_init(&bf->sections);
   bf->shstrtab = NULL;

   symarray_init(&bf->syms);
   bf->symstrtab = NULL;

   relarray_init(&bf->rels);
   uintarray_init(&bf->relsects);
   boolarray_init(&bf->rels_are_rela);

   uintarray_init(&bf->section_lookup);
   uintarray_init(&bf->symbol_lookup);

   ptrarray_init(&bf->sectiondata);

   return bf;
}

void binfile_destroy(struct binfile *bf) {
   if (bf->gf) {
      genfile_close(bf->gf);
   }

   shdrarray_setsize(&bf->sections, 0);
   shdrarray_cleanup(&bf->sections);
   if (bf->shstrtab) {
      elfstrtab_destroy(bf->shstrtab);
      bf->shstrtab = NULL;
   }

   symarray_setsize(&bf->syms, 0);
   symarray_cleanup(&bf->syms);
   if (bf->symstrtab) {
      elfstrtab_destroy(bf->symstrtab);
      bf->symstrtab = NULL;
   }

   relarray_setsize(&bf->rels, 0);
   uintarray_setsize(&bf->relsects, 0);
   boolarray_setsize(&bf->rels_are_rela, 0);
   relarray_cleanup(&bf->rels);
   uintarray_cleanup(&bf->relsects);
   boolarray_cleanup(&bf->rels_are_rela);

   uintarray_setsize(&bf->section_lookup, 0);
   uintarray_setsize(&bf->symbol_lookup, 0);
   uintarray_cleanup(&bf->section_lookup);
   uintarray_cleanup(&bf->symbol_lookup);

   ptrarray_setsize(&bf->sectiondata, 0);
   ptrarray_cleanup(&bf->sectiondata);

   dostrfree(bf->name);
   dofree(bf, sizeof(*bf));
}

static int load_ehdr(struct binfile *bf) {
   assert(!bf->ehdr_loaded);
   elf_read_ehdr(bf->gf, 0, &bf->ehdr);
   if (elf_check_ehdr(bf->name, &bf->ehdr)) {
      return -1;
   }
   bf->ehdr_loaded = true;
   return 0;
}

struct binfile *binfile_bind(const char *name, struct genfile *gf) {
   struct binfile *bf;

   bf = binfile_create(name, gf);

   if (load_ehdr(bf)) {
      /* don't destroy gf; we should have no net effect when failing */
      bf->gf = NULL;
      binfile_destroy(bf);
      return NULL;
   }

   return bf;
}

////////////////////////////////////////////////////////////

const char *binfile_getname(struct binfile *bf) {
   return bf->name;
}

enum bftypes binfile_gettype(struct binfile *bf) {
   if (!bf->ehdr_loaded) {
      load_ehdr(bf);
   }
   switch (bf->ehdr.e_type) {
    case ET_REL: return BFT_OBJ;
    case ET_EXEC: return BFT_PROG;
    case ET_DYN: return BFT_LIB;
    case ET_CORE:
     prog_err("%s: is a core file", bf->name);
     break;
    default:
     break;
   }
   assert(0);
   return BFT_OBJ;
}
