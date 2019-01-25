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
#include "as.h"
#include "modeinfo.h"
#include "targetmatch.h"
#include "backend.h"

/*
 * label-related directives
 *
 * .align is in here as well because it and label alignment share logic.
 */

/*
 * XXX 20170710 a lot of integer arguments got changed from
 * u_machlarge (which is portable though broader than necessary) to
 * sized integer types, whose sizes may be target-dependent. This
 * needs to be sorted out later.
 */

/* arbitrarily chosen at 64k (XXX?) */
#define MAXIMUM_ALLOWED_ALIGNMENT	16

static u_machlarge check_alignment_value(int linenum, u_machlarge val) {
   u_machword sval = val;
   u_machlarge i = 1;

   if (sval == 0) {
      file_err(linenum, "Invalid alignment %llu", (unsigned long long) sval);
   }
   if ((sval & (sval-1))!=0) {
      file_err(linenum, ".align must use a power of 2");
   }
   if (sval > (u_machlarge)1 << MAXIMUM_ALLOWED_ALIGNMENT) {
      file_err(linenum, "Invalid alignment %llu", (unsigned long long) sval);
   }
   /* we handle alignments as logs internally */
   /* XXX we have an ilog2, use it */
   val = 0;
   for (; (i&sval)==0; val++, i<<=1) {
      assert(i!=0);
   }
   return val;
}

#if defined(AS_ALIGNS_BY_LOGVALUE)
static u_machlarge check_alignment_logvalue(int linenum, u_machlarge val) {
   if (val > MAXIMUM_ALLOWED_ALIGNMENT) {
      file_err(linenum, "Invalid alignment 2^%llu", (unsigned long long) val);
   }
   return val;
}
#endif

static u_machlarge check_alignment_align(int linenum, u_machlarge val) {
#if defined(AS_ALIGNS_BY_VALUE)
   return check_alignment_value(linenum, val);
#elif defined(AS_ALIGNS_BY_LOGVALUE)
   return check_alignment_logvalue(linenum, val);
#else
#error "AS_ALIGNS_BY_* not set"
#endif
}

static u_machlarge check_alignment_comm(int linenum, u_machlarge val) {
#if defined(AS_COMM_ALIGNS_BY_VALUE)
   return check_alignment_value(linenum, val);
#elif defined(AS_COMM_ALIGNS_BY_LOGVALUE)
   return check_alignment_logvalue(linenum, val);
#else
#error "AS_COMM_ALIGNS_BY_* not set"
#endif
}

void directive_align_n(int linenum, uint32_t val) {
   unsigned sect;

   val = check_alignment_align(linenum, val);
   sect = getcursection(linenum);
   align_section(sect, val);
}

static void directive_lcomm(int linenum, struct expr *symx, u_machlarge size,
			    bool doalign, u_machlarge align) {
   struct label *sym;
   unsigned oldsect, bss;

   assert(symx->x_type == EXPR_IDENT);
   sym = symx->x_u.u_ident.sym;

   oldsect = getcursection(linenum);
   bss = getsection(".bss", true, false, false, true);

   if (doalign) {
      align = check_alignment_comm(linenum, align);
      align_section(bss, align);
   }
   label_define(sym, linenum, bss, section_getsize(bss));
   label_setsize(sym, size);
   label_setdata(sym);

   setcursection(bss);
   directive_space_n(linenum, size);
   setcursection(oldsect);
}

static void directive_comm(int linenum, struct expr *symx, uint32_t size,
			   bool doalign, uint32_t align) {
   struct label *sym;

   assert(symx->x_type == EXPR_IDENT);
   sym = symx->x_u.u_ident.sym;

   /*
    * In gas apparently you can do .local foo; .comm foo, 1234
    * in place of .lcomm foo, 1234. Why why why.......?
    */
   if (label_isexplicitlylocal(sym)) {
      directive_lcomm(linenum, symx, size, doalign, align);
      return;
   }

   if (doalign) {
      align = check_alignment_comm(linenum, align);
   }
   else {
      /* XXX gas does powers of two at least as large as size up to this */
      align = TARGET_BSS_ALIGNMENT;
   }

   label_definecommon(sym, linenum, size, align);
   label_setdata(sym);
}

void directive_lcomm_s_n(int linenum, struct expr *symx, uint32_t size) {
   directive_lcomm(linenum, symx, size, false, 0);
}

void directive_lcomm_s_n_n(int linenum, struct expr *symx, uint32_t size,
			   uint32_t align) {
   directive_lcomm(linenum, symx, size, true, align);
}

void directive_comm_s_n(int linenum, struct expr *symx, uint32_t size) {
   directive_comm(linenum, symx, size, false, 0);
}

void directive_comm_s_n_n(int linenum, struct expr *symx, uint32_t size,
			  uint32_t align) {
   directive_comm(linenum, symx, size, true, align);
}

void directive_local_s(int linenum, struct expr *symx) {
   struct label *sym;

   assert(symx->x_type == EXPR_IDENT);
   sym = symx->x_u.u_ident.sym;

   if (label_isdot(sym)) {
      file_err(linenum, ".globl `.' not permitted");
   }
   if (label_isscratch(sym)) {
      file_err(linenum, ".globl not permitted with scratch labels");
   }
   label_setlocal(sym);
}

void directive_globl_s(int linenum, struct expr *symx) {
   struct label *sym;

   assert(symx->x_type == EXPR_IDENT);
   sym = symx->x_u.u_ident.sym;

   if (label_isdot(sym)) {
      file_err(linenum, ".globl `.' not permitted");
   }
   if (label_isscratch(sym)) {
      file_err(linenum, ".globl not permitted with scratch labels");
   }
   label_setglobl(sym);
}
void directive_global_s(int linenum, struct expr *symx) {
   directive_globl_s(linenum, symx);
}

void directive_extern_s(int linenum, struct expr *symx) {
   struct label *sym;

   assert(symx->x_type == EXPR_IDENT);
   sym = symx->x_u.u_ident.sym;

   if (label_isdot(sym)) {
      file_err(linenum, ".extern `.' not permitted");
   }
   if (label_isscratch(sym)) {
      file_err(linenum, ".extern not permitted with scratch labels");
   }
   if (label_isdefined(sym)) {
      file_err(linenum, ".extern used on locally defined symbol `%s'", 
	       label_getname(sym));
   }
   label_setextern(sym);
}

void directive_type_s_symty(int linenum, struct expr *symx, const char *ty) {
   struct label *sym;

   assert(symx->x_type == EXPR_IDENT);
   sym = symx->x_u.u_ident.sym;

   if (!strcmp(ty, "object")) {
      label_setdata(sym);
   }
   else if (!strcmp(ty, "function")) {
      label_setcode(sym);
   }
   else {
      file_err(linenum, "Invalid symbol type %s", ty);
   }
}

void directive_ent_s(int linenum, struct expr *sym) {
   // XXX for now ignore this
   (void)linenum;
   (void)sym;
}

void directive_end_s(int linenum, struct expr *sym) {
   // XXX for now ignore this
   (void)linenum;
   (void)sym;
}

void directive_size_s_x(int linenum, struct expr *sym, struct expr *e) {
   // XXX for now ignore this
   // (we can emit symbol sizes now, but the expression can be
   // sym1 - sym2 and we can't handle that yet)
   (void)linenum;
   (void)sym;
   (void)e;
}

/*
 * XXX: these are sparc64-specific and should be moved to code generation
 * when we figure out how to do that.
 */
void directive_common_s_n_q(int linenum, struct expr *symx, uint32_t size,
			    const char *section) {
   if (strcmp(section, "bss") != 0) {
      file_err(linenum, "Invalid .common directive");
   }
   directive_comm(linenum, symx, size, false, 0);
}
void directive_reserve_s_n_q(int linenum, struct expr *symx, uint32_t size,
			    const char *section) {
   if (strcmp(section, "bss") != 0) {
      file_err(linenum, "Invalid .common directive");
   }
   directive_lcomm(linenum, symx, size, false, 0);
}
void directive_common_s_n_n(int linenum, struct expr *symx, uint32_t size,
			    uint32_t align) {
   directive_comm(linenum, symx, size, true, align);
}
void directive_reserve_s_n_n(int linenum, struct expr *symx, uint32_t size,
			     uint32_t align) {
   directive_lcomm(linenum, symx, size, true, align);
}

/*
 * XXX this is arm-specific and should be made to go away
 */
void directive_align_mz(int linenum, uint32_t mz) {
   assert(mz == 0);
   directive_align_n(linenum, 2);
}
void directive_even_(int linenum) {
   directive_align_n(linenum, 1);
}

////////////////////////////////////////////////////////////
// label definitions coming from the frontend

static void backend_add_label_with_offset(int linenum, const char *sym,
					  u_machword offset) {
   struct label *l;
   unsigned sect;

   sect = getcursection(linenum);
   if (!strcmp(sym, ".")) {
      file_err(linenum, "`.' is a reserved label");
   }
   l = label_declare(linenum, sym, SCRATCHLABELS_DEFINE);
   if (label_isdefined(l) || label_isextern(l)) {
      int oldline = label_getline(l);
      file_warn(oldline, "Label `%s' previously defined here", sym);
      file_err(linenum, "is defined again here");
   }

   label_define(l, linenum, sect, section_getsize(sect) + offset);
}

void backend_add_label(int linenum, const char *sym) {
   backend_add_label_with_offset(linenum, sym, 0);
}

void backend_assign_label(int linenum, const char *sym, const char *othersym) {
   struct label *l, *otherl;

   if (!strcmp(sym, ".")) {
      file_err(linenum, "`.' is a reserved label");
   }
   if (!strcmp(othersym, ".")) {
      file_err(linenum, "`.' is a reserved label");
   }

   l = label_declare(linenum, sym, SCRATCHLABELS_DEFINE);
   if (label_isdefined(l) || label_isextern(l)) {
      int oldline = label_getline(l);
      file_warn(oldline, "Label `%s' previously defined here", sym);
      file_err(linenum, "is defined again here");
   }

   otherl = label_declare(linenum, othersym, SCRATCHLABELS_REFER);
   if (!(label_isdefined(otherl) || label_isextern(otherl))) {
      file_err(linenum, "Label `%s' not defined", othersym);
   }

   label_assign(l, linenum, otherl);
}

/* same op as backend_assign_label */
void directive_set_s_x(int linenum, struct expr *symexpr, struct expr *val) {
   const char *sym, *othersym;

   assert(symexpr->x_type == EXPR_IDENT);
   sym = symexpr->x_u.u_ident.ident;

   val = fold_constant_arithmetic(val, true);
   if (val->x_type == EXPR_IDENT) {
      /*
       * XXX it would probably be simpler if backend_add_label were
       * folded into backend_assign_label.
       */
      othersym = val->x_u.u_ident.ident;
      if (!strcmp(othersym, ".")) {
	 backend_add_label(linenum, sym);
      }
      else {
	 backend_assign_label(linenum, sym, othersym);
      }
   }
   else if (val->x_type == EXPR_OPERATOR &&
	    val->x_u.u_operator.op == OP_ADD &&
	    val->x_u.u_operator.arg1->x_type == EXPR_IDENT &&
	    val->x_u.u_operator.arg2->x_type == EXPR_NUM) {
      u_machword offset;

      othersym = val->x_u.u_operator.arg1->x_u.u_ident.ident;
      offset = val->x_u.u_operator.arg2->x_u.u_num;
      if (!strcmp(othersym, ".")) {
	 backend_add_label_with_offset(linenum, sym, offset);
      }
      else {
	 goto nope;
      }
   }
   else {
 nope:
      file_err(linenum, "Unsupported label address expression in .set");
   }
}
