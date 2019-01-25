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
#include "reloc.h" // XXX: this violates the organization of things

/*
 * Constant folding for unary operators.
 *
 * If "aggressive" is set remove parentheses. This is set downstream
 * of operand type matching, where parentheses in expressions no
 * longer have semantic meaning. Prior to that parentheses must be
 * retained, since many architectures use parentheses in addressing
 * modes to mean indirection.
 */
static struct expr *fold_unary(struct expr *x, bool aggressive) {
   struct expr *arg1 = x->x_u.u_operator.arg1;
   struct expr *arg2 = x->x_u.u_operator.arg2;

   assert(arg2 == NULL);

   if (aggressive && x->x_u.u_operator.op == OP_PARENS) {
      /*
       * As long as we're downstream from operand matching we can
       * strip parentheses.
       */
      x->x_u.u_operator.arg1 = NULL;
      expr_destroy(x);
      /* we already did constant folding on arg1, so just return it */
      return arg1;
   }

   if (arg1->x_type != EXPR_NUM) {
      return x;
   }

   switch (x->x_u.u_operator.op) {
    case OP_PARENS:
     /* number in parentheses is just a number */
     break;
    case OP_NEG:
     arg1->x_u.u_num = (u_machlarge) (- (s_machlarge)arg1->x_u.u_num);
     break;
    case OP_BITNOT:
     arg1->x_u.u_num = ~arg1->x_u.u_num;
     break;
    default:
     assert(0);
     return NULL;
   }

   x->x_u.u_operator.arg1 = NULL;
   expr_destroy(x);
   return arg1;
}

/*
 * Constant folding for binary operators.
 */
static struct expr *fold_binary(struct expr *x) {
   struct expr *arg1 = x->x_u.u_operator.arg1;
   struct expr *arg2 = x->x_u.u_operator.arg2;

   if (x->x_u.u_operator.op == OP_ADD &&
       arg1->x_type == EXPR_NUM && arg1->x_u.u_num == 0) {
      return arg2;
   }
   if (x->x_u.u_operator.op == OP_ADD &&
       arg2->x_type == EXPR_NUM && arg2->x_u.u_num == 0) {
      return arg1;
   }

   if (arg1->x_type != EXPR_NUM || arg2->x_type != EXPR_NUM) {
      return x;
   }

   switch (x->x_u.u_operator.op) {
    case OP_ADD:
     arg1->x_u.u_num += arg2->x_u.u_num;
     break;
    case OP_SUB:
     arg1->x_u.u_num -= arg2->x_u.u_num;
     break;
    case OP_BITXOR:
     arg1->x_u.u_num ^= arg2->x_u.u_num;
     break;
    case OP_BITOR:
     arg1->x_u.u_num |= arg2->x_u.u_num;
     break;
    case OP_BITAND:
     arg1->x_u.u_num &= arg2->x_u.u_num;
     break;
    case OP_LSHIFT:
     arg1->x_u.u_num <<= arg2->x_u.u_num;
     break;
    case OP_RSHIFT:
     arg1->x_u.u_num >>= arg2->x_u.u_num;
     break;
    default:
     assert(0);
     return NULL;
   }
   expr_destroy(arg2);
   x->x_u.u_operator.arg1 = NULL;
   x->x_u.u_operator.arg2 = NULL;
   expr_destroy(x);
   return arg1;
}

/*
 * "Constant folding" for modifiers. This removes the
 * parentheses used to delimit the argument. It also (now) applies
 * the modifier if the argument is a constant.
 */
static struct expr *fold_modifier(struct expr *x) {
   struct expr *arg = x->x_u.u_modifier.arg;
   struct expr *tmp;
   int linenum;
   enum reloc_modifier m;

   if (is_specific_unary(arg, OP_PARENS)) {
      /* special case: dump the parens from %foo(x) */
      tmp = arg->x_u.u_operator.arg1;
      arg->x_u.u_operator.arg1 = NULL;
      expr_destroy(arg);
      x->x_u.u_modifier.arg = arg = tmp;
   }

   if (arg->x_type != EXPR_NUM) {
      return x;
   }

   linenum = 0; /* XXX, but I believe it's unused below here */
   if (x->x_u.u_modifier.op != NULL) {
      m = target_reloc_getmodifier(x->x_u.u_modifier.op);
      arg->x_u.u_num = target_modifier_apply(linenum, m, arg->x_u.u_num);
   }
   x->x_u.u_modifier.arg = NULL;
   expr_destroy(x);

   return arg;
}

/*
 * Constant folding (and some related stuff).
 *
 * As noted above the AGGRESSIVE flag should be set only downstream
 * from operand matching; it allows changes that retain expression
 * semantics but alter the syntactic form.
 *
 * Allow the argument to be NULL to simplify call sites.
 */
struct expr *fold_constant_arithmetic(struct expr *x, bool aggressive) {
   if (x==NULL) {
      return NULL;
   }

   switch (x->x_type) {
    case EXPR_TARGET:
    case EXPR_STR:
    case EXPR_NUM:
    case EXPR_IDENT:
     return x;
    case EXPR_OPERATOR: {
       struct expr *arg1 = x->x_u.u_operator.arg1;
       struct expr *arg2 = x->x_u.u_operator.arg2;

       arg1 = fold_constant_arithmetic(arg1, aggressive);
       arg2 = arg2 ? fold_constant_arithmetic(arg2, aggressive) : NULL;

       x->x_u.u_operator.arg1 = arg1;
       x->x_u.u_operator.arg2 = arg2;

       if (arg2) {
	  return fold_binary(x);
       }
       else {
	  return fold_unary(x, aggressive);
       }
    }
    case EXPR_MODIFIER: {
       struct expr *arg = x->x_u.u_modifier.arg;

       arg = fold_constant_arithmetic(arg, aggressive);

       x->x_u.u_modifier.arg = arg;

       return fold_modifier(x);
    }
    case EXPR_JUXTAPOSE: {
       struct expr *arg1 = x->x_u.u_juxtapose.arg1;
       struct expr *arg2 = x->x_u.u_juxtapose.arg2;

       arg1 = fold_constant_arithmetic(arg1, aggressive);
       arg2 = fold_constant_arithmetic(arg2, aggressive);

       x->x_u.u_juxtapose.arg1 = arg1;
       x->x_u.u_juxtapose.arg2 = arg2;
       return x;
    }
    default:
     assert(0);
     return NULL;
   }
}


