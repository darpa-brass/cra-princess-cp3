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
#include <stdio.h> /* XXX remove along with mkexpr_targetnum */
#include <string.h>
#include <assert.h>
#include "common.h"

#include "mem.h"
#include "label.h"
#include "expr.h"

////////////////////////////////////////////////////////////
// expression constructors

static struct expr *expr_create(enum exprtypes type) {
   struct expr *nx;

   nx = domalloc(sizeof(*nx));
   nx->x_type = type;
   return nx;
}

struct expr *mkexpr_target(enum targettoktypes ttok, const char *val) {
   struct expr *nx = expr_create(EXPR_TARGET);
   nx->x_u.u_target.ttok = ttok;
   nx->x_u.u_target.val = dostrdup(val);
   return nx;
}

/*
 * XXX this shouldn't need to exist; make it go away again
 */
struct expr *mkexpr_targetnum(enum targettoktypes ttok, u_machlarge val) {
   char tmp[16];

   snprintf(tmp, sizeof(tmp), "%lu", val);
   return mkexpr_target(ttok, tmp);
}

struct expr *mkexpr_string(const char *val) {
   struct expr *nx = expr_create(EXPR_STR);
   nx->x_u.u_str = dostrdup(val);
   return nx;
}

struct expr *mkexpr_number(u_machlarge val) {
   struct expr *nx = expr_create(EXPR_NUM);
   nx->x_u.u_num = val;
   return nx;
}

struct expr *mkexpr_label(struct label *sym) {
   struct expr *e;

   e = expr_create(EXPR_IDENT);
   e->x_u.u_ident.sym = sym;
   e->x_u.u_ident.ident = dostrdup(label_getname(sym));
   return e;
}

/*
 * We provide both mkexpr_binary and mkexpr_unary, but the
 * representation only distinguishes them based on whether arg2 is
 * null.
 *
 * These should probably assert that the operator named is suitable.
 */

struct expr *mkexpr_binary(struct expr *x1, enum operators what,
			   struct expr *x2) {
  struct expr *nx = expr_create(EXPR_OPERATOR);
   nx->x_u.u_operator.op = what;
   nx->x_u.u_operator.arg1 = x1;
   nx->x_u.u_operator.arg2 = x2;
   return nx;
}

struct expr *mkexpr_unary(enum operators what, struct expr *x1) {
   struct expr *nx = expr_create(EXPR_OPERATOR);
   nx->x_u.u_operator.op = what;
   nx->x_u.u_operator.arg1 = x1;
   nx->x_u.u_operator.arg2 = NULL;
   return nx;
}

struct expr *mkexpr_modifier(const char *op, struct expr *x1) {
   struct expr *nx = expr_create(EXPR_MODIFIER);
   nx->x_u.u_modifier.op = dostrdup(op);
   nx->x_u.u_modifier.arg = x1;
   return nx;
}

struct expr *mkexpr_juxtapose(struct expr *x1, struct expr *x2) {
   struct expr *nx = expr_create(EXPR_JUXTAPOSE);
   nx->x_u.u_juxtapose.arg1 = x1;
   nx->x_u.u_juxtapose.arg2 = x2;
   return nx;
}

static char *dostrdup_nullok(const char *s) {
   return s ? dostrdup(s) : NULL;
}

/*
 * Copy an expression tree.
 */
struct expr *expr_clone(const struct expr *x) {
   struct expr *nx;

   if (x == NULL) {
      return NULL;
   }

   nx = expr_create(x->x_type);
   switch (x->x_type) {
    case EXPR_TARGET:
     nx->x_u.u_target.ttok = x->x_u.u_target.ttok;
     nx->x_u.u_target.val = dostrdup_nullok(x->x_u.u_target.val);
     break;
    case EXPR_STR:
     nx->x_u.u_str = dostrdup_nullok(x->x_u.u_str);
     break;
    case EXPR_NUM:
     nx->x_u.u_num = x->x_u.u_num;
     break;
    case EXPR_IDENT:
     nx->x_u.u_ident.ident = x->x_u.u_ident.ident;
     nx->x_u.u_ident.sym = x->x_u.u_ident.sym;
     break;
    case EXPR_OPERATOR:
     nx->x_u.u_operator.op = x->x_u.u_operator.op;
     nx->x_u.u_operator.arg1 = expr_clone(x->x_u.u_operator.arg1);
     nx->x_u.u_operator.arg2 = expr_clone(x->x_u.u_operator.arg2);
     break;
    case EXPR_MODIFIER:
     nx->x_u.u_modifier.op = dostrdup_nullok(x->x_u.u_modifier.op);
     nx->x_u.u_modifier.arg = expr_clone(x->x_u.u_modifier.arg);
     break;
    case EXPR_JUXTAPOSE:
     nx->x_u.u_juxtapose.arg1 = expr_clone(x->x_u.u_juxtapose.arg1);
     nx->x_u.u_juxtapose.arg2 = expr_clone(x->x_u.u_juxtapose.arg2);
     break;
   }
   return nx;
}

////////////////////////////////////////////////////////////
// expression destructor

void expr_destroy(struct expr *x) {
   if (x == NULL) {
      return;
   }
#if 0 /* XXX enabling this causes SIGSEGV */
   switch (x->x_type) {
    case EXPR_TARGET:
     dostrfree(x->x_u.u_target.val);
     break;
    case EXPR_STR:
     dostrfree(x->x_u.u_str);
     break;
    case EXPR_NUM:
     break;
    case EXPR_IDENT:
     break;
    case EXPR_OPERATOR:
     expr_destroy(x->x_u.u_operator.arg1);
     expr_destroy(x->x_u.u_operator.arg2);
     break;
    case EXPR_MODIFIER:
     dostrfree(x->x_u.u_modifier.op);
     expr_destroy(x->x_u.u_modifier.arg);
     break;
    case EXPR_JUXTAPOSE:
     expr_destroy(x->x_u.u_juxtapose.arg1);
     expr_destroy(x->x_u.u_juxtapose.arg2);
     break;
   }
#endif
   dofree(x, sizeof(*x));
}

////////////////////////////////////////////////////////////
// expression predicates

bool is_unary(struct expr *x) {
   return x->x_type == EXPR_OPERATOR && x->x_u.u_operator.arg2 == NULL;
}

bool is_binary(struct expr *x) {
   return x->x_type == EXPR_OPERATOR && x->x_u.u_operator.arg2 != NULL;
}

bool is_specific_unary(struct expr *x, enum operators op) {
   return is_unary(x) && x->x_u.u_operator.op==op;
}

bool is_specific_binary(struct expr *x, enum operators op) {
   return is_binary(x) && x->x_u.u_operator.op==op;
}

/*
 * Only allow numeric expressions. There's no compelling argument
 * for allowing string expressions, and it creates problems because we
 * have no way of distinguishing them at runtime in the generated code.
 *
 * To be general we might need to do that and maybe also handle
 * expressions of machine-dependent types too, but let's wait until we
 * have a clear use case as it requires adding a bunch of runtime
 * infrastructure.
 */
bool is_constant(struct expr *x) {
   return x->x_type == EXPR_NUM;
}

/*
 * This is the backend manifestation of definedp() in the description
 * expressions, which is more or less a hack and ought to be removed.
 */
bool has_defined_symbols(struct expr *x) {
   if (x == NULL) {
      return true;
   }
   switch (x->x_type) {
    case EXPR_TARGET:
    case EXPR_STR:
    case EXPR_NUM:
     return true;
    case EXPR_IDENT:
     return label_isdefined(x->x_u.u_ident.sym);
    case EXPR_OPERATOR:
     return has_defined_symbols(x->x_u.u_operator.arg1) &&
	has_defined_symbols(x->x_u.u_operator.arg2);
    case EXPR_MODIFIER:
     return has_defined_symbols(x->x_u.u_modifier.arg);
    case EXPR_JUXTAPOSE:
     return has_defined_symbols(x->x_u.u_juxtapose.arg1) &&
	has_defined_symbols(x->x_u.u_juxtapose.arg2);
   }
   assert(0);
   return false;
}
