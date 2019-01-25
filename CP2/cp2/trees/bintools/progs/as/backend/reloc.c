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
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "array.h"
#include "genfmt.h"
#include "binfile.h"

#include "label.h"
#include "reloc.h"
#include "section.h"

DECLARRAY(reloc, static UNUSED inline);
DEFARRAY(reloc, static UNUSED inline);

/*
 * Table of all relocations generated.
 */
static struct relocarray allrelocs;

/*
 * Constructor
 *
 * (does not implicitly add to the master table)
 */
struct reloc *reloc_create(int ln, enum reloc_modifier mod,
			   struct label *s1, struct label *s2,
			   u_machword addend) {
   struct reloc *r;

   r = domalloc(sizeof(*r));
   r->r_linenum = ln;
   r->r_sectnum = 0;
   r->r_offset = 0;
   r->r_curpos = 0;
   r->r_sym1 = s1;
   r->r_sym2 = s2;
   r->r_addend = addend;
   r->r_modifier = mod;
   r->r_field = RELOC_FIELD_DEFAULT;
   return r;
}

/*
 * Destructor
 */
void reloc_destroy(struct reloc *r) {
   dofree(r, sizeof(*r));
}

/*
 * Add a relocation.
 */
void reloc_add(struct reloc *r, unsigned sect) {
   if (section_isbss(sect)) {
      file_err(r->r_linenum, "Relocation requested in %s", 
               section_name(sect));
   }
   r->r_curpos = section_getsize(sect);
   r->r_sectnum = sect;
   relocarray_add(&allrelocs, r);
}

////////////////////////////////////////////////////////////
// dump

/*
 * Dump out one relocation.
 */
static void dump_reloc(struct reloc *r) {
   assert(r->r_sym2 == NULL || label_isdot(r->r_sym2));
   printf("  @0x%lx: (%s) ", (unsigned long) r->r_offset,
	  target_reloc_field_name(r->r_field));

   switch (r->r_modifier) {
    case RELOC_MOD_NONE:
     break;
    default:
     printf("%s(", target_reloc_modifier_name(r->r_modifier));
     break;
   }

   printf("%s", label_getname(r->r_sym1));
   if (r->r_addend > 0) {
      printf(" + %ju", (uintmax_t)r->r_addend);
   }
   if (r->r_sym2 != NULL) {
      printf(" - .");
   }

   switch (r->r_modifier) {
    case RELOC_MOD_NONE:
     break;
    default:
     printf(")");
     break;
   }
   printf("\n");
}

/*
 * Dump out all relocations.
 */
void dump_relocs(void) {
   unsigned i, num;
   struct reloc *r;

   num = relocarray_num(&allrelocs);
   for (i=0; i<num; i++) {
      r = relocarray_get(&allrelocs, i);
      if (!r) {
	 continue;
      }
      dump_reloc(r);
   }
   printf("\n");
}

////////////////////////////////////////////////////////////
// process

/*
 * Handle a relocation that applies the difference of two symbols.
 */
static struct reloc *process_difference_reloc(struct reloc *r) {
   u_machword value;
   int linenum;
   unsigned snum;
   unsigned sect1, sect2;

   linenum = r->r_linenum;
   snum = r->r_sectnum;
   
   assert(r->r_sym1 != NULL && r->r_sym2 != NULL);
   if (label_isdot(r->r_sym1) && label_isdot(r->r_sym2)) {
      /* stupid case: . - . */
      value = 0;
   }
   else if (label_isdot(r->r_sym1)) {
      if (!label_isdefined(r->r_sym2) || label_isextern(r->r_sym2)) {
	 file_err(linenum, "Cannot take difference with an external symbol");
      }
      sect2 = label_getsection(r->r_sym2);
      if (sect2 != snum) {
	 file_err(linenum, "Cannot take difference of `.' (%s) and `%s' (%s)",
		  section_name(snum), label_getname(r->r_sym2),
		  section_name(sect2));
      }
      value = r->r_curpos - label_getoffset(r->r_sym2);
   }
   else if (label_isdot(r->r_sym2)) {
      if (!label_isdefined(r->r_sym1) || label_isextern(r->r_sym1)) {
	 return r;
	 /*
	 file_err(linenum, "Cannot take difference with an external symbol");
	 */
      }
      sect1 = label_getsection(r->r_sym1);
      if (sect1 != snum) {
	 return r;
	 /*
	 file_err(linenum, "Cannot take difference of `%s' (%s) and `.' (%s)",
		  label_getname(r->r_sym1), section_name(sect1),
		  section_name(snum));
	 */
      }
      value = label_getoffset(r->r_sym1) - r->r_curpos;
   }
   else {
      if (!label_isdefined(r->r_sym1) || label_isextern(r->r_sym1) ||
	  !label_isdefined(r->r_sym2) || label_isextern(r->r_sym2)) {
	 file_err(linenum, "Cannot take difference with an external symbol");
      }
      sect1 = label_getsection(r->r_sym1);
      sect2 = label_getsection(r->r_sym2);
      if (sect1 != sect2) {
	 file_err(linenum, "Cannot take difference of '%s' (%s) and `%s' (%s)",
		  label_getname(r->r_sym1), section_name(sect1), 
		  label_getname(r->r_sym2), section_name(sect2));
      }
      value = label_getoffset(r->r_sym1) - label_getoffset(r->r_sym2);
   }
   value += r->r_addend;

   target_reloc_apply(r, value);
   //reloc_destroy(r); // XXX
   return NULL;
}

/*
 * Handle a relocation that is just a single symbol. These get left
 * for the linker.
 */
static void process_straight_reloc(struct reloc *r) {
   if (label_isdot(r->r_sym1)) {
      file_err(r->r_linenum, "Illegal use of special symbol `.'");
   }
   assert(r->r_sym2==NULL);
}

/*
 * Handle one relocation of any form.
 */
static struct reloc *process_reloc(struct reloc *r) {
   if (r==NULL) {
      /* for convenience */
      return NULL;
   }

   if (r->r_sym2 == NULL) {
      process_straight_reloc(r);
   }
   else {
      r = process_difference_reloc(r);
   }
   if (r != NULL) {
      label_markused(r->r_sym1);
   }
   return r;
}

/*
 * Handle all relocations, in the sense of resolving things that we
 * can resolve after assembling the whole input file. Called from
 * main.
 */
void process_relocs(void) {
   unsigned i, num;
   struct reloc *r;

   num = relocarray_num(&allrelocs);
   for (i=0; i<num; i++) {
      r = relocarray_get(&allrelocs, i);
      r = process_reloc(r);
      relocarray_set(&allrelocs, i, r);
   }
}

////////////////////////////////////////////////////////////
// emit

/*
 * Issue all (remaining) relocations into the passed binfile.
 */
void emit_relocs(struct binfile *bf) {
   unsigned i, num;
   struct reloc *r;
   struct genreloc *gr;

   num = relocarray_num(&allrelocs);
   for (i=0; i<num; i++) {
      r = relocarray_get(&allrelocs, i);
      if (r == NULL) {
	 continue;
      }
      target_reloc_preoutput(r);

      gr = genreloc_create();
      gr->gr_addend = r->r_addend;
      gr->gr_offset = r->r_offset;
      gr->gr_section = r->r_sectnum;
      gr->gr_symbol = label_getnumber(r->r_sym1);
      assert(r->r_sym2 == NULL || label_isdot(r->r_sym2));
      gr->gr_code = target_reloc_code(r);
      binfile_addreloc(bf, gr);
   }
}

