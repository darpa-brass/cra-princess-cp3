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
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "array.h"
#include "genfmt.h"
#include "binfile.h"

#include "label.h"
#include "section.h"

/* scratch label numbers are 0..99 */
#define MAXSCRATCHLABELS 100

/*
 * Structure for information about a label.
 */
struct label {
   char *l_name;
   int l_isdot;		/* is an instance of the "." label */
   int l_isscratch;	/* is a scratch (numbered) label */

   int l_quashname;	/* true: don't emit symbol name into .o file */
   int l_used;		/* approximate usage count of this symbol */
   
   int l_linenum;	/* line number of declaration or definition */
   bool l_defined;	/* true if physically defined in this file */
   bool l_common;	/* true if a common */
   bool l_extern;	/* true if explicitly declared extern */
   bool l_globl;	/* true if declared global */
   bool l_local;	/* true if explicitly declared local */
   unsigned l_type;	/* declared type if any (GSMT_*) */

   unsigned l_sectnum;	/* section number of definition */
   u_machword l_offset;	/* offset from section base */
   u_machword l_size;	/* size of symbol if known */
   u_machword l_align;	/* alignment of symbol (commons only) */
};
DECLARRAY(label, static UNUSED inline);
DEFARRAY(label, static UNUSED inline);

/* All labels */
static struct labelarray labels;
/* The name of the source file (like and unlike a label) */
static char *sourcefile = NULL;

/* Tables used for resolving numbered scratch labels */
static struct label *backwardscratchlabels[MAXSCRATCHLABELS];
static struct label *forwardscratchlabels[MAXSCRATCHLABELS];

/*
 * Set the source file.
 */
void set_sourcefile(const char *s) {
   // directive.c is supposed to enforce this (sourcefile set only once)
   assert(sourcefile==NULL);

   sourcefile = dostrdup(s);
}

/*
 * Constructor (implicitly adds to the master table)
 */
static struct label *label_create(int linenum, const char *name) {
   struct label *l;

   l = domalloc(sizeof(*l));
   l->l_name = dostrdup(name);
   l->l_isdot = 0;
   l->l_isscratch = 0;
   l->l_quashname = 0;
   l->l_used = 0;
   l->l_linenum = linenum;
   l->l_defined = 0;
   l->l_common = 0;
   l->l_extern = 0;
   l->l_globl = 0;
   l->l_local = 0;
   l->l_type = GSMT_UNKNOWN;
   l->l_sectnum = UNDEFINED_SECTION;
   l->l_offset = 0;
   l->l_size = 0;
   l->l_align = 0;
   labelarray_add(&labels, l);
   return l;
}

/*
 * Destructor (does not correspondingly remove from the master table)
 * XXX: tidy that
 */
static void label_destroy(struct label *l) {
   dostrfree(l->l_name);
   dofree(l, sizeof(*l));
}

/*
 * Constructor for numbered scratch labels.
 *
 * (Note that MAXSCRATCHLABELS is 100, not 1000, so the assert will
 * really never fail)
 */
static struct label *label_mkscratch(int linenum, unsigned scratchnum) {
   struct label *l;
   char tmp[4];

   assert(scratchnum<1000);	// fit in buffer

   snprintf(tmp, sizeof(tmp), "%u", scratchnum);

   l = label_create(linenum, tmp);
   l->l_isscratch = 1;
   l->l_quashname = 1;
   return l;
}

/*
 * Declare a numbered scratch label.
 *
 * The "how" argument tells us if it's a definition (which should
 * just be the number, as in "3:") or a reference, which includes
 * a direction 'f' or 'b', as in "jmp 3f".
 * XXX: this interface is messy.
 *
 * XXX: why don't we check errno after strtoul?
 *
 * Note that we don't define the offset or anything; the caller
 * uses label_define for that at the proper point.
 */
static struct label *declare_scratch(int linenum, const char *sym,
				     enum scratchlabelhow s) {
   bool isforward;
   const char *endptr;
   unsigned long scratchnum;
   struct label *rv;

   isforward = false;
   scratchnum = strtoul(sym, (char **)&endptr, 10);

   if (s==SCRATCHLABELS_DEFINE && strlen(endptr) > 0) {
      file_err(linenum, "Ill-formed scratch label");
   }
   else if (s==SCRATCHLABELS_REFER) {
      if (!strcmp(endptr, "f")) {
	 isforward = true;
      }
      else if (!strcmp(endptr, "b")) {
	 isforward = false;
      }
      else {
	 file_err(linenum, "Ill-formed scratch label");
      }
   }

   if (scratchnum >= MAXSCRATCHLABELS) {
      file_err(linenum, "Out-of-range scratch label number");
   }

   if (s==SCRATCHLABELS_DEFINE) {
      /* A definition */
      if (forwardscratchlabels[scratchnum] != NULL) {
	 /* Something already points here; resolve it */
	 rv = forwardscratchlabels[scratchnum];
	 forwardscratchlabels[scratchnum] = NULL;
      }
      else {
	 /* Nothing already points here; make a new label */
	 rv = label_mkscratch(linenum, scratchnum);
      }
      /* Further backward references to this number get this label */
      backwardscratchlabels[scratchnum] = rv;
   }
   else {
      /* A use */
      if (isforward) {
	 if (forwardscratchlabels[scratchnum] == NULL) {
	    /* No such label yet */
	    rv = label_mkscratch(linenum, scratchnum);
	    forwardscratchlabels[scratchnum] = rv;
	 }
	 else {
	    /*
	     * This number already exists as a forward reference
	     * (this happens if there's more than one "jmp 1f"
	     * before the "1:")
	     *
	     * XXX: maybe assert that it hasn't been defined yet
	     */
	    rv = forwardscratchlabels[scratchnum];
	 }
      }
      else {
	 /* backwards references must already exist */
	 if (backwardscratchlabels[scratchnum] == NULL) {
	    file_err(linenum, "Scratch label %s not resolvable", sym);
	 }
	 rv = backwardscratchlabels[scratchnum];
      }
   }
   return rv;
}

/*
 * Declare a label. If it's a scratch label (as determined by
 * whether it begins with a digit) hand off to declare_scratch
 * above. If not, the "how" argument is irrelevant.
 *
 * This may not be used for the magic "." label; use label_declaredot
 * for that.
 *
 * XXX: should we have a second entry point for declaring scratch
 * labels and have the caller know which labels are scratch labels?
 * It might be tidier that way.
 */
struct label *label_declare(int linenum, const char *sym,
			    enum scratchlabelhow s) {
   unsigned i, num;
   struct label *l;
   bool isscratch;

   /* the "." symbol needs to be handled specially */
   assert(strcmp(sym, "."));
   /* symbols may not be empty */
   assert(sym[0]!=0);

   isscratch = (strchr("0123456789", sym[0]) != NULL);
   if (isscratch) {
      return declare_scratch(linenum, sym, s);
   }

   /* XXX: We should really use a table that lets us look up by name... */

   num = labelarray_num(&labels);
   for (i=0; i<num; i++) {
      l = labelarray_get(&labels, i);
      if (l->l_isdot || l->l_isscratch) {
	 continue;
      }

      if (!strcmp(l->l_name, sym)) {
	 return l;
      }
   }

   /* Doesn't exist yet; make a new one */
   return label_create(linenum, sym);
}

/*
 * Like label_declare, but for ".".
 *
 * Since "." magically refers to the current address, every instance
 * of "." is distinct; always create a new label. The caller will
 * still define the location with label_define.
 */
struct label *label_declaredot(int linenum) {
   struct label *l;

   /* all "." labels are distinct */

   l = label_create(linenum, ".");
   l->l_isdot = 1;
   l->l_quashname = 1;
   return l;
}

/*
 * Provide a definition of a label: section and offset.
 *
 * Also updates the input line number associated with the symbol, so
 * any subsequent errors point to the definition.
 */
void label_define(struct label *l,
		  int linenum, unsigned sectnum, u_machword offset) {

   assert(l->l_defined==0);
   assert(l->l_common==0);
   assert(l->l_extern==0);

   l->l_defined = 1;
   l->l_linenum = linenum;
   l->l_offset = offset;
   l->l_used++;
   l->l_sectnum = sectnum;
}

/*
 * Provide a definition of a label as a copy of another label.
 *
 * Also updates the input line number associated with the symbol, so
 * any subsequent errors point to the definition.
 */
void label_assign(struct label *l, int linenum, struct label *otherl) {

   assert(l->l_defined==0);
   assert(l->l_common==0);
   assert(l->l_extern==0);

   assert(otherl->l_defined);
   assert(otherl->l_isdot==0);

   l->l_used++;

   l->l_defined = 1;
   l->l_linenum = linenum;
   l->l_common = otherl->l_common; /* should this be allowed? */
   l->l_extern = otherl->l_extern;
   l->l_offset = otherl->l_offset;
   l->l_type = otherl->l_type;
   l->l_sectnum = otherl->l_sectnum;
   l->l_offset = otherl->l_offset;
   l->l_size = otherl->l_size;
   l->l_align = otherl->l_align;
}

/*
 * Like label_define but "define" the symbol as a common. This gives
 * it no particular address (that's left to the linker) but it does
 * have a size and it might have an alignment restriction.
 */
void label_definecommon(struct label *l, int linenum,
			u_machword size, u_machword align) {

   assert(l->l_defined==0);
   assert(l->l_common==0);
   assert(l->l_extern==0);

   l->l_defined = 1;
   l->l_common = 1;
   l->l_globl = 1;
   l->l_linenum = linenum;
   l->l_offset = 0;
   l->l_align = align;
   l->l_size = size;
   l->l_used++;
   l->l_sectnum = UNDEFINED_SECTION;
}

/*
 * Set the size for a label.
 *
 * The notion of labels having sizes is a little odd (since labels are
 * addresses) but this is an upstream problem in assembly languages.
 * Basically the size of a label is the size of the object the label
 * points to.
 */
void label_setsize(struct label *l, u_machword size) {
   l->l_size = size;
}

/*
 * Explicitly mark a label as local.
 */
void label_setlocal(struct label *l) {
   assert(l->l_common == 0);
   assert(l->l_extern == 0);
   l->l_globl = 0;
   l->l_local = 1;
}

/*
 * Mark a label global, so the definition will be exposed to the
 * linker.
 */
void label_setglobl(struct label *l) {
   assert(l->l_common == 0);
   assert(l->l_extern == 0);
   l->l_globl = 1;
   l->l_local = 0;
}

/*
 * Mark a label external, so we expect the linker to provide the
 * definition.
 *
 * XXX: if you do .globl foo .extern foo (or vice versa) do we assert?
 */
void label_setextern(struct label *l) {
   assert(l->l_defined == 0);
   assert(l->l_common == 0);
   assert(l->l_globl == 0);
   assert(l->l_local == 0);
   l->l_extern = 1;
}

/*
 * Mark a label used.
 */
void label_markused(struct label *l) {
   l->l_used++;
}

/*
 * Set the type of a label to code.
 */
void label_setcode(struct label *l) {
   l->l_type = GSMT_CODE;
}

/*
 * Set the type of a label to data.
 */
void label_setdata(struct label *l) {
   l->l_type = GSMT_DATA;
}

/*
 * Get various properties of a label.
 */

const char *label_getname(struct label *l) {
   return l->l_name;
}

int label_getline(struct label *l) {
   return l->l_linenum;
}

int label_isdot(struct label *l) {
   return l->l_isdot;
}

int label_isscratch(struct label *l) {
   return l->l_isscratch;
}

int label_isdefined(struct label *l) {
   return l->l_defined;
}

int label_isextern(struct label *l) {
   return l->l_extern;
}

// not used
//int label_isglobl(struct label *l) {
//   return l->l_globl;
//}

int label_isexplicitlylocal(struct label *l) {
   return l->l_local;
}

unsigned label_getsection(struct label *l) {
   return l->l_sectnum;
}

u_machword label_getoffset(struct label *l) {
   return l->l_offset;
}

////////////////////////////////////////////////////////////

/*
 * Make sure all forward scratch references made have been
 * satisfied.
 */
void check_scratch_labels(void) {
   unsigned i;
   struct label *l;

   for (i=0; i<MAXSCRATCHLABELS; i++) {
      if (forwardscratchlabels[i]) {
	 l = forwardscratchlabels[i];
	 assert(!l->l_defined);
	 file_err(l->l_linenum, "Scratch label %s is not resolvable",
		  l->l_name);
      }
   }
}

/*
 * Discard temporary labels. Temporary labels are not the same as
 * scratch labels... they are a family of labels emitted by compilers
 * that have specific names but where the names aren't interesting.
 *
 * If the label has been used we just suppress its name; otherwise we
 * drop it entirely.
 */
void discard_temp_labels(void) {
   unsigned i, num;
   struct label *l;

   num = labelarray_num(&labels);
   for (i=0; i<num; i++) {
      l = labelarray_get(&labels, i);
      assert(l != NULL);
      if (l->l_name == NULL ||
	  !strncmp(l->l_name, TEMP_LABEL_PREFIX, strlen(TEMP_LABEL_PREFIX))) {
	 if (l->l_used > 0) {
	    l->l_quashname = 1;
	 }
	 else {
	    labelarray_set(&labels, i, NULL);
	    label_destroy(l);
	 }
      }
   }
}

/*
 * Get the sort category of a label.
 */
static int labelsortcat(struct label *l) {
   if (l->l_quashname) {
      /* temporary-local */
      return 4;
   }
   else if (!l->l_defined && l->l_used == 0) {
      /* phantom */
      return 5;
   }
   else if (!l->l_defined) {
      /* extern */
      return 1;
   }
   else if (l->l_globl) {
      /* global */
      return 2;
   }
   else {
      return 3;
   }
}

/*
 * Sort comparison for labels.
 */
static int labelsort(const void *av, const void *bv) {
   struct label *a, *b;
   int ac, bc, r;

   a = *(struct label **)av;
   b = *(struct label **)bv;

   /* First, sort by category (extern, global, local, temporary-local) */
   ac = labelsortcat(a);
   bc = labelsortcat(b);

   if (ac < bc) {
      return -1;
   }
   if (ac > bc) {
      return 1;
   }

   /* In the same category, sort by section */
   if (a->l_sectnum < b->l_sectnum) {
      return -1;
   }
   if (a->l_sectnum > b->l_sectnum) {
      return 1;
   }

   /* In the same section, sort by address */
   if (a->l_offset < b->l_offset) {
      return -1;
   }
   if (a->l_offset > b->l_offset) {
      return 1;
   }

   /* when the address is the same (e.g. undefined symbols), sort by name */
   if (a->l_name != NULL && b->l_name != NULL) {
      r = strcmp(a->l_name, b->l_name);
      if (r) {
	 return r;
      }
   }
   if (a->l_name == NULL && b->l_name != NULL) {
      return -1;
   }
   if (a->l_name != NULL && b->l_name == NULL) {
      return 1;
   }

   return 0;
}

/*
 * Sort the label table.
 */
void sort_labels(void) {
   qsort(labelarray_getdata(&labels), labelarray_num(&labels),
	 sizeof(struct label *), labelsort);
}

/*
 * Get the index number of a(n existing) label.
 *
 * This is used to populate the symbol references in relocations.
 */
unsigned label_getnumber(struct label *l) {
   // XXX this is stupid; the index should be an element of struct label
   unsigned i, num;

   num = labelarray_num(&labels);
   for (i=0; i<num; i++) {
      if (l == labelarray_get(&labels, i)) {
	 return i;
      }
   }
   assert(0);
   return -1;
}

/*
 * Dump out the label (symbol) table.
 */
void dump_labels(void) {
   unsigned i, num;
   struct label *l;

   num = labelarray_num(&labels);

   printf("Symbols:\n");
   for (i=0; i < num; i++) {
      l = labelarray_get(&labels, i);
      if (!l) {
	 continue;
      }

      if (l->l_isdot) {
	 continue;
      }

      printf("    %-20s  %-8s 0x%08lx%s%s%s\n", 
	     l->l_quashname ? "[...]" : l->l_name,
	     l->l_common ? "[common]" : section_name(l->l_sectnum),
	     (unsigned long)l->l_offset,
	     l->l_globl ? " [globl]" : "", 
	     l->l_extern || !l->l_defined ? " [extern]" : "",
	     l->l_used==0 ? " [discardable]" : "");
   }
}

/*
 * Issue all labels into the passed binfile.
 */
void emit_labels(struct binfile *bf) {
   unsigned i, num;
   struct label *l;
   struct gensym *gsm;

   num = labelarray_num(&labels);
   for (i=0; i<num; i++) {
      l = labelarray_get(&labels, i);
      assert(l != NULL);

      /* skip unused labels */
      if (l->l_used == 0) {
	 continue;
      }

      if (l->l_defined && l->l_common) {
	 assert(l->l_sectnum == UNDEFINED_SECTION);
      }
      else if (l->l_defined) {
	 assert(l->l_sectnum != UNDEFINED_SECTION);
      }
      else {
	 assert(l->l_sectnum == UNDEFINED_SECTION);
      }

      gsm = gensym_create(l->l_quashname ? NULL : l->l_name);
      gsm->gsm_value = l->l_offset;
      gsm->gsm_size = l->l_size;
      gsm->gsm_align = l->l_align;
      /* section */
      if (l->l_common) {
	 gsm->gsm_section = GSX_COMMON;
      }
      else {
	 /*
	  * For now at least the section numbers at the binfile layer
	  * are the same as the section numbers we use in the assembler
	  * proper.
	  */
	 gsm->gsm_section = l->l_sectnum;
      }
      /* type */
      if (l->l_type != GSMT_UNKNOWN) {
	 gsm->gsm_type = l->l_type;
      }
      else if (l->l_sectnum != UNDEFINED_SECTION &&
	       section_iscode(l->l_sectnum)) {
	 /* In a code segment it's code by default */
	 gsm->gsm_type = GSMT_CODE;
      }
      else if (l->l_sectnum != UNDEFINED_SECTION) {
	 /* In a non-code segment it's data by default */
	 gsm->gsm_type = GSMT_DATA;
      }
      else {
	 gsm->gsm_type = GSMT_UNKNOWN;
      }
      gsm->gsm_flags = 0;

      /* undefined symbols are global */
      /* XXX doesn't l_extern need to be checked here? */
      if (!l->l_defined || l->l_globl) {
	 gsm->gsm_flags |= GSMF_GLOBL;
      }

      /* undefined symbols go in the undefined section */
      /* XXX shouldn't this be with the other section cases? */
      if (!l->l_defined) {
	 gsm->gsm_section = GSX_UNDEF;
      }

      binfile_addsym(bf, gsm, i);
   }

   if (sourcefile != NULL) {
      binfile_setsource(bf, sourcefile);
   }
}
