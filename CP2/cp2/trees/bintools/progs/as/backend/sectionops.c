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

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "utils.h"
#include "expr.h"
#include "reloc.h"
#include "label.h"
#include "section.h"
#include "sectionops.h"
#include "targetmatch.h"

/*
 * Section-related directives and their state.
 */

static unsigned cur_sectnum = UNDEFINED_SECTION;
static unsigned prev_sectnum = UNDEFINED_SECTION;

static void have_section(int linenum) {
   (void)linenum;

   if (cur_sectnum == UNDEFINED_SECTION) {
      /* gcc output triggers this (XXX 2016: does it still?) */
      /*dowarn(linenum, "No section defined - assuming .text");*/
      cur_sectnum = getsection(".text", true, true, true, false);
   }
}

unsigned getcursection(int linenum) {
   have_section(linenum);
   return cur_sectnum;
}

void setcursection(unsigned sectnum) {
   assert(sectnum != UNDEFINED_SECTION);
   prev_sectnum = cur_sectnum;
   cur_sectnum = sectnum;
}

static void setprevsection(int linenum) {
   unsigned t;

   have_section(linenum);
   if (prev_sectnum == UNDEFINED_SECTION) {
      /* gcc 4.8.3 output triggers this */
      /*file_err(linenum, "No previous section");*/
   }
   t = prev_sectnum;
   prev_sectnum = cur_sectnum;
   cur_sectnum = t;
}

static const char *default_flags(const char *sectname) {
   if (!strcmp(sectname, ".text")) {
      /* allocate, hasinsns */
      return "ax";
   }
   if (!strcmp(sectname, ".rdata") || !strcmp(sectname, ".rodata")) {
      /* allocate */
      return "a";
   }
   if (!strcmp(sectname, ".data") || !strcmp(sectname, ".bss")) {
      /* allocate, writeable */
      return "aw";
   }
   /* XXX there are more, target-dependent, standard section names to know */
   return NULL;
}

static const char *default_type(const char *sectname) {
   if (!strcmp(sectname, ".text") ||
       !strcmp(sectname, ".rdata") || !strcmp(sectname, ".rodata") ||
       !strcmp(sectname, ".data")) {
      return "progbits";
   }
   if (!strcmp(sectname, ".bss")) {
      /* allocate */
      return "nobits";
   }
   /* XXX there are more, target-dependent, standard section names to know */
   return NULL;
}

void directive_text_(int linenum) {
   unsigned sect;

   (void)linenum;

   sect = getsection(".text", true, true, true, false);
   require_section_alignment(sect, TARGET_TEXT_ALIGNMENT);
   setcursection(sect);
}

void directive_rdata_(int linenum) {
   unsigned sect;

   (void)linenum;

   sect = getsection(".rdata", true, false, true, false);
   require_section_alignment(sect, TARGET_RDATA_ALIGNMENT);
   setcursection(sect);
}

void directive_data_(int linenum) {
   unsigned sect;

   (void)linenum;

   sect = getsection(".data", true, false, false, false);
   require_section_alignment(sect, TARGET_DATA_ALIGNMENT);
   setcursection(sect);
}

void directive_bss_(int linenum) {
   unsigned sect;

   (void)linenum;

   sect = getsection(".bss", true, false, false, true);
   require_section_alignment(sect, TARGET_BSS_ALIGNMENT);
   setcursection(sect);
}

static void directive_section(int linenum, const char *sectname,
			      const char *flags, const char *type,
			      struct expr *arg1, struct expr *arg2) {
   bool hasinsns = false;
   bool readonly = true;
   bool isbss = false;

   bool mergeable = false;
   bool group = false;

   unsigned i, sect;

   if (flags != NULL) {
      for (i=0; flags[i]; i++) {
	 switch (flags[i]) {
	  case 'a':
	   /* allocatable */
	   // XXX
	   break;
	  case 'e':
	   /* exclude from final link */
	   // XXX
	   break;
	  case 'w':
	   readonly = false;
	   break;
	  case 'x':
	   hasinsns = true;
	   break;
	  case 'T':
	   /* thread-local storage section */
	   // XXX
	   break;
	  case 'M':
	   /* merge duplicate values */
	   mergeable = true;
	   // XXX
	   break;
	  case 'S':
	   /* mergeable values are 0-terminated strings */
	   // XXX
	   break;
	  case 'G':
	   /* member of a section group */
	   group = true;
	   // XXX
	   break;
	  case '?':
	   /* member of same section group as previous section */
	   // XXX
	   break;
	  default:
	   file_err(linenum, "Illegal section flag %c", flags[i]);
	   break;
	 }
      }
   }

   if (type == NULL) {
      /* nothing */
   }
   else if (!strcmp(type, "progbits")) {
      // XXX how is this different from allocatable?
   }
   else if (!strcmp(type, "nobits")) {
      isbss = true;
   }
   else if (!strcmp(type, "note")) {
      /* note section */
      // XXX
   }
   else if (!strcmp(type, "init_array")) {
      /* constructors */
      // XXX
   }
   else if (!strcmp(type, "fini_array")) {
      /* destructors */
      // XXX
   }
   else if (!strcmp(type, "preinit_array")) {
      /* pre-constructor constructors (I think) */
      // XXX
   }
   else {
      file_err(linenum, "Invalid section type %s", type);
   }

   if (mergeable) {
      if (arg1 == NULL) {
	 file_err(linenum, "Mergeable section must declare entry size");
      }
      if (arg2 != NULL) {
	 file_err(linenum, "Extra argument to .section");
      }
      if (arg1->x_type != EXPR_NUM) {
	 file_err(linenum, "Mergeable section entry size must be a number");
      }
      // XXX
      (void)arg1->x_u.u_num;
   }
   else if (group) {
      if (arg1 == NULL) {
	 file_err(linenum, "Missing section group name");
      }
      if (arg1->x_type != EXPR_IDENT) {
	 file_err(linenum, "Invalid section group name");
      }
      // XXX
      (void)arg1->x_u.u_ident.sym;

      if (arg2 != NULL) {
	 if (arg2->x_type != EXPR_IDENT) {
	    file_err(linenum, "Invalid section group linkage type");
	 }
	 // XXX
	 /*
	  * The only valid values here are apparently "comdat" and
	  * ".gnu.linkonce", which mean the same thing.
	  */
	 (void)arg2->x_u.u_ident.sym;
      }
   }
   else if (arg1 != NULL || arg2 != NULL) {
      file_err(linenum, "Extra argument to .section");
   }

   sect = getsection(sectname, flags != NULL, hasinsns, readonly, isbss);
   setcursection(sect);
}

void directive_section_s_q_q_x_x(int linenum, struct expr *sectnamex,
				 const char *flags, const char *type,
				 struct expr *arg1, struct expr *arg2) {
   const char *sectname;

   assert(sectnamex->x_type == EXPR_IDENT);
   sectname = label_getname(sectnamex->x_u.u_ident.sym);
   directive_section(linenum, sectname, flags, type, arg1, arg2);
}

/*
 * XXX it would be nice to be able to arrange to not need these.
 */
void directive_section_s_q_q_x(int linenum, struct expr *sect, const char *flags,
		       const char *type, struct expr *arg1) {
   directive_section_s_q_q_x_x(linenum, sect, flags, type, arg1, NULL);
}
void directive_section_s_q_q(int linenum, struct expr *sect, const char *flags,
		       const char *type) {
   directive_section_s_q_q_x_x(linenum, sect, flags, type, NULL, NULL);
}
void directive_section_s_q(int linenum, struct expr *sect, const char *flags) {
   const char *sectname, *type;

   assert(sect->x_type == EXPR_IDENT);
   sectname = label_getname(sect->x_u.u_ident.sym);
   type = default_type(sectname);
   directive_section(linenum, sectname, flags, type, NULL, NULL);
}
void directive_section_s(int linenum, struct expr *sect) {
   const char *sectname, *flags, *type;

   assert(sect->x_type == EXPR_IDENT);
   sectname = label_getname(sect->x_u.u_ident.sym);
   flags = default_flags(sectname);
   type = default_type(sectname);
   directive_section(linenum, sectname, flags, type, NULL, NULL);
}

/* ...more cases */
void directive_section_s_q_secty_x_x(int linenum, struct expr *sect, const char *flags,
		       const char *type, struct expr *arg1, struct expr *arg2) {
   const char *ident;

   /*
    * XXX we need a MI way of getting these @foo symbols
    */
#if 0
   if (type->x_type != EXPR_IDENT) {
      file_err(linenum, "Invalid .section directive");
   }
   ident = type->x_u.u_ident.ident;
#else
   ident = type;
#endif
   directive_section_s_q_q_x_x(linenum, sect, flags, ident, arg1, arg2);
}
void directive_section_s_q_secty_x(int linenum, struct expr *sect, const char *flags,
		       const char *type, struct expr *arg1) {
   directive_section_s_q_secty_x_x(linenum, sect, flags, type, arg1, NULL);
}
void directive_section_s_q_secty(int linenum, struct expr *sect, const char *flags,
		       const char *type) {
   directive_section_s_q_secty_x_x(linenum, sect, flags, type, NULL, NULL);
}
/*
 * sigh... not sure if this is sparc64-specific, a gcc bug, or what, but
 * gcc is emitting section names with - in them.
 */
void directive_section_x_q_secty(int linenum, struct expr *sect, const char *flags,
		       const char *type) {
   if (sect->x_type == EXPR_OPERATOR && sect->x_u.u_operator.op == OP_SUB) {
      struct expr *a1, *a2;

      a1 = sect->x_u.u_operator.arg1;
      a2 = sect->x_u.u_operator.arg2;
      if (a1->x_type == EXPR_IDENT && a2 != NULL && a2->x_type == EXPR_IDENT) {
	 char *s;

	 s = dostrdup3(a1->x_u.u_ident.ident, "-", a2->x_u.u_ident.ident);
	 // XXX apparently can't do this?
	 //dostrfree(a1->x_u.u_ident.ident);
	 a1->x_u.u_ident.ident = s;
	 sect->x_u.u_operator.arg1 = NULL;
	 // this is wrong, don't do it.
	 //expr_destroy(sect);
	 sect = a1;
      }
   }

   if (sect->x_type == EXPR_IDENT) {
      directive_section_s_q_secty_x_x(linenum, sect, flags, type, NULL, NULL);
   }
   else {
      file_err(linenum, "Invalid section name");
   }
}

/*
 * apparently there's another kind of .section, of the form
 *     .section "name", [flag, ]*
 * where each flag is a symbolic constant. To handle this we'll
 * need to add token/expression types for symbolic constants (@foo
 * on mips, but e.g. #foo on sparc) so the match logic can
 * distinguish the forms. (Then the types in .type will be of this
 * form too.)
 *
 * Also we'll need to improve the match specifications to support
 * operand specs of the form "i(k*)" - currently we only allow
 * "ik+" and it means "(ik)+". This will also require some way to
 * pass those flags... the method used for (ik)+ won't do.
 *
 * For now just support the simple form without any flags.
 */

void directive_section_q(int linenum, const char *sectname) {
   const char *flags, *type;

   flags = default_flags(sectname);
   type = default_type(sectname);
   directive_section(linenum, sectname, flags, type, NULL, NULL);
}


void directive_previous_(int linenum) {
   setprevsection(linenum);
}

/*
 * XXX this is sparc64-specific and should be moved to code generation when
 * we figure that out.
 */
void directive_seg_q(int linenum, const char *seg) {
   if (!strcmp(seg, "text")) {
      directive_text_(linenum);
   }
   else if (!strcmp(seg, "data")) {
      directive_data_(linenum);
   }
   else if (!strcmp(seg, "data1")) {
      /* XXX: it's supposed to be the same as ".data 1" */
      file_err(linenum, ".seg \"data1\": not supported");
   }
   else {
      file_err(linenum, "Invalid .seg directive");
   }
}
