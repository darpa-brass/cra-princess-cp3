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

#include "utils.h"
#include "expr.h"
#include "reloc.h"

static struct expr *extract_modifier(int linenum, struct expr *x,
				     enum reloc_modifier *m_ret) {
   const char *mod;

   if (x->x_type == EXPR_MODIFIER) {
      mod = x->x_u.u_modifier.op;
      *m_ret = target_reloc_getmodifier(mod);
      if (*m_ret == RELOC_MOD_NONE) {
	 file_err(linenum, "Invalid relocation modifier %s()", mod);
      }
      x = x->x_u.u_modifier.arg;
   }
   return x;
}

static struct expr *extract_addend(struct expr *x, u_machword *addend) {
   /*
    * if either side of an add is a constant, move it to the addend.
    */
   if (is_specific_binary(x, OP_ADD)) {
      struct expr *arg1 = x->x_u.u_operator.arg1;
      struct expr *arg2 = x->x_u.u_operator.arg2;

      if (arg1->x_type == EXPR_NUM) {
	 *addend += arg1->x_u.u_num;
	 x = extract_addend(arg2, addend);
      }
      else if (arg2->x_type == EXPR_NUM) {
	 *addend += arg2->x_u.u_num;
	 x = extract_addend(arg1, addend);
      }
   }

   /*
    * If we have something minus a constant, turn it into plus and shift
    * it into the addend.
    */
   if (is_specific_binary(x, OP_SUB)) {
      struct expr *arg1 = x->x_u.u_operator.arg1;
      struct expr *arg2 = x->x_u.u_operator.arg2;

      if (arg2->x_type == EXPR_NUM) {
	 *addend = -arg2->x_u.u_num;
	 x = extract_addend(arg1, addend);
      }
   }

   return x;
}

/*
 * Compile an expression that isn't just a constant.
 *
 * XXX should explicitly check to make sure the addend fits
 */
static struct reloc *compile_expr_really(int linenum, struct expr *x) {
   u_machword addend = 0;
   struct reloc *result = NULL;

   enum reloc_modifier modtype = RELOC_MOD_NONE;

   /* first do any constant folding */
   x = fold_constant_arithmetic(x, true);

   /* If we have a modifier, pull it off. */
   x = extract_modifier(linenum, x, &modtype);

   /*
    * If we have something plus a constant, shift the constant into
    * the addend.
    */
   x = extract_addend(x, &addend);

   /* If we now have a modifier, pull it off now. */
   /*
    * XXX this is not right. We really need to distinguish between
    * %mod(sym + addend) and %mod(sym) + addend, because both exist
    * as relocations on various platforms and they are not the same.
    *
    * However, for now doing it this way is expedient, and I think it
    * won't blow up: the definition of the relocation will control
    * when the linker adds the addend in (before or after whatever
    * the modifier does) so as long as the input usage matches the
    * relocation nothing bad will happen.
    *
    * However, this way we can't detect wrong uses, and if a platform
    * has relocations for both cases we'll mess up.
    *
    * Don't even try if we already got a modifier though.
    */
   if (modtype == RELOC_MOD_NONE) {
      x = extract_modifier(linenum, x, &modtype);
   }

   /*
    * If there's another addend inside a subtraction, haul it out.
    */
   if (is_specific_binary(x, OP_SUB)) {
      u_machword tmp;

      x->x_u.u_operator.arg1 = extract_addend(x->x_u.u_operator.arg1, &addend);

      /* need to flip the sign on this one */
      tmp = 0;
      x->x_u.u_operator.arg2 = extract_addend(x->x_u.u_operator.arg2, &tmp);
      addend -= tmp;
   }

   /*
    * sym1 - sym2
    */
   if (is_specific_binary(x, OP_SUB)) {
      struct expr *arg1 = x->x_u.u_operator.arg1;
      struct expr *arg2 = x->x_u.u_operator.arg2;

      if (arg1->x_type==EXPR_IDENT && arg2->x_type==EXPR_IDENT) {
	 result = reloc_create(linenum, modtype,
			       arg1->x_u.u_ident.sym,
			       arg2->x_u.u_ident.sym, addend);
	 return result;
      }
   }

   /*
    * just sym1
    */
   if (x->x_type==EXPR_IDENT) {
      result = reloc_create(linenum, modtype, x->x_u.u_ident.sym, NULL, addend);
      return result;
   }

   file_err(linenum, "Cannot represent expression in output file");

   /* NOTREACHED */
   return NULL;
}

/*
 * Compile an expression into a (MI) relocation and a constant addend.
 */
struct reloc *compile_expr(int linenum, struct expr *x, u_machlarge *val) {
   if (x->x_type == EXPR_NUM) {
      *val = x->x_u.u_num;
      return NULL;
   }
   *val = 0;
   return compile_expr_really(linenum, x);
}
