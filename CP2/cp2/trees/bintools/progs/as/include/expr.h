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

#ifndef EXPR_H
#define EXPR_H

#include "targetdefs.h"
#include "array.h"
#include "targettoken.h"
struct label; /* from label.h */


/*
 * Expression tree
 */

enum operators {
   OP_PARENS,		/* enclose in parentheses */
   OP_NEG,
   OP_ADD,
   OP_SUB,
   OP_BITNOT,
   OP_BITXOR,
   OP_BITOR,
   OP_BITAND,
   OP_LSHIFT,
   OP_RSHIFT,
};

enum exprtypes {
   EXPR_TARGET,		/* target-defined base expression */
   EXPR_STR,		/* string constant */
   EXPR_NUM,		/* number */
   EXPR_IDENT,		/* identifier */
   EXPR_OPERATOR,	/* unary or binary operator */
   EXPR_MODIFIER,	/* relocation modifier */
   EXPR_JUXTAPOSE,	/* juxtaposition of two expressions */
};

struct expr {
   enum exprtypes x_type;
   union {
      struct {
	 enum targettoktypes ttok;
	 char *val;
      } u_target;
      char *u_str;
      u_machlarge u_num;
      struct {
	 const char *ident;
	 struct label *sym;
      } u_ident;
      struct {
	 enum operators op;
	 struct expr *arg1;
	 struct expr *arg2;	/* null for unary operators */
      } u_operator;
      struct {
	 char *op;
	 struct expr *arg;
      } u_modifier;
      struct {
	 struct expr *arg1;
	 struct expr *arg2;
      } u_juxtapose;
   } x_u;
};

/*
 * Array of expressions
 */
#ifndef EXPRINLINE
#define EXPRINLINE INLINE
#endif
DECLARRAY(expr, EXPRINLINE);
DEFARRAY(expr, EXPRINLINE);

/*
 * Functions in expr.c
 */
struct expr *mkexpr_target(enum targettoktypes ttok, const char *val);
struct expr *mkexpr_targetnum(enum targettoktypes ttok, u_machlarge val);
struct expr *mkexpr_string(const char *val);
struct expr *mkexpr_number(u_machlarge val);
struct expr *mkexpr_label(struct label *sym);
struct expr *mkexpr_binary(struct expr *, enum operators, struct expr *);
struct expr *mkexpr_unary(enum operators, struct expr *);
struct expr *mkexpr_modifier(const char *, struct expr *);
struct expr *mkexpr_juxtapose(struct expr *, struct expr *);
struct expr *expr_clone(const struct expr *e);
void expr_destroy(struct expr *e);

bool is_unary(struct expr *x);
bool is_binary(struct expr *x);
bool is_specific_unary(struct expr *x, enum operators op);
bool is_specific_binary(struct expr *x, enum operators op);
bool is_constant(struct expr *x);
bool has_defined_symbols(struct expr *x);

/*
 * Functions in expropt.c
 */
struct expr *fold_constant_arithmetic(struct expr *x, bool aggressive);


#endif /* EXPR_H */
