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
#include <stdio.h> /* for snprintf, XXX */
#include <stdarg.h>
#include <assert.h>
#include <setjmp.h> /* hopefully temporary */
#include "common.h"

#include "targetdefs.h"
#include "utils.h"
#include "token.h"
#define EXPRINLINE
#include "expr.h"
#include "eparse.h"
#include "label.h"

/*
 * The expression grammar is:
 *
 *     expression ::=
 *        juxtapose-expression
 *
 *     juxtapose-expression ::=
 *        bitor-expression
 *        juxtapose-expression bitor-expression
 *
 *     bitor-expression ::=
 *        bitxor-expression
 *        bitor-expression | bitxor-expression
 *     
 *     bitxor-expression ::=
 *        bitand-expression
 *        bitxor-expression ^ bitand-expression
 *     
 *     bitand-expression ::=
 *        shift-expression
 *        bitand-expression & shift-expression
 *     
 *     shift-expression ::=
 *        add-expression
 *        shift-expression << add-expression
 *        shift-expression >> add-expression
 *
 *     add-expression ::=
 *        prefix-expression
 *        add-expression + prefix-expression
 *        add-expression - prefix-expression
 *
 *     prefix-expression ::=
 *        primary-expression
 *        + prefix-expression
 *        - prefix-expression
 *        ~ prefix-expression
 *        operator(expression)
 *
 *     primary-expression ::=
 *        number
 *        symbol
 *        register
 *        string
 *        (expression)
 */

/*
 * The parser reads from this pile of tokens.
 */
static struct tokenarray *ptoks;
static unsigned curtok;
static int linenum;

////////////////////////////////////////////////////////////

/*
 * Get a token out of the input array.
 */
static struct token *gettok(void) {
   if (curtok >= tokenarray_num(ptoks)) {
      return NULL;
   }
   return tokenarray_get(ptoks, curtok++);
}

/*
 * Look at the next input token without popping it off.
 */
static struct token *peektok(void) {
   if (curtok >= tokenarray_num(ptoks)) {
      return NULL;
   }
   return tokenarray_get(ptoks, curtok);
}

////////////////////////////////////////////////////////////

/*
 * XXX: this was expedient; it should be removed in favor of updating
 * the parser to fail properly. By the time doing that is likely an
 * option, it will likely also be time to rearrange the parser to not
 * have juxtapose expressions and other related simplifications.
 */
static bool jump_on_error;
static jmp_buf jb;

static void noparse(const char *fmt, ...) {
   va_list ap;
   char buf[4096];

   if (jump_on_error) {
      longjmp(jb, 1);
   }
   /* XXX: should use file_errv, but we don't have one */
   va_start(ap, fmt);
   vsnprintf(buf, sizeof(buf), fmt, ap);
   va_end(ap);
   file_err(linenum, "%s", buf);
}

////////////////////////////////////////////////////////////
// support code

static u_machlarge parsenumber(const char *val) {
   u_machlarge num = 0, tmp2;
   int base = 10, digit;

   if (*val=='0') {
      val++;
      if (*val=='x' || *val=='X') {
	 base=16;
	 val++;
      }
      else {
	 base = 8;
      }
   }

   while (*val) {
      if (*val>='0' && *val<='9') {
	 digit = *val - '0';
      }
      else if (*val>='a' && *val<='f') {
	 digit = *val + 10 - 'a';
      }
      else if (*val>='A' && *val<='F') {
	 digit = *val + 10 - 'A';
      }
      else {
	 digit = -1;
      }
      if (digit < 0 || digit >= base) {
	 noparse("Invalid digit in number %s (apparently base %d)", 
		  val, base);
      }

      tmp2 = num*base + digit;
      if (tmp2 < num) {		/* XXX this is wrong */
	 /* overflow */
	 noparse("Number too large: %s", val);
      }
      num = tmp2;
      val++;
   }

   return num;
}

static enum operators token_to_binary_operator(enum toktypes t) {
   switch (t) {
    case TOK_PLUS: return OP_ADD;
    case TOK_MINUS: return OP_SUB;
    case TOK_LTLT: return OP_LSHIFT;
    case TOK_GTGT: return OP_RSHIFT;
    case TOK_AMP: return OP_BITAND;
    case TOK_CARET: return OP_BITXOR;
    case TOK_BAR: return OP_BITOR;
    default: assert(0); return OP_ADD;
   }
}

////////////////////////////////////////////////////////////

/*
 * common code for binary operators
 */
static struct expr *parse_binary_operator(enum toktypes tt1, enum toktypes tt2,
					  struct expr *(*subfunc)(void)) {
   struct expr *x, *x2;
   struct token *pt;

   x = subfunc();
   assert(x!=NULL);

   while ((pt = peektok())!=NULL) {
      assert(pt->t_type != TOK_NIL);
      if (pt->t_type != tt1 && pt->t_type != tt2) {
	 break;
      }
      gettok();		/* consume the operator */
      x2 = subfunc();
      assert(x2 != NULL);
      x = mkexpr_binary(x, token_to_binary_operator(pt->t_type), x2);
   }
   return x;
}


static struct expr *parse_real_expression(void);

/*
 * Expect parentheses.
 */
static struct expr *parse_parens(void) {
   struct token *pt, *pt2;
   struct expr *x;

   pt = gettok();
   if (pt==NULL || pt->t_type != TOK_LPAREN) {
      noparse("Expected open parenthesis in expression");
   }
   pt2 = peektok();
   if (pt2==NULL) {
      noparse("Missing close parenthesis in expression");
   }
   if (pt2->t_type == TOK_RPAREN) {
      noparse("Empty parentheses");
   }
   x = parse_real_expression();
   pt = gettok();
   if (pt->t_type != TOK_RPAREN) {
      noparse("Missing close parenthesis in expression");
   }
   return mkexpr_unary(OP_PARENS, x);
}

/*
 * Expect a primary (base) expression.
 */
static struct expr *parse_primary_expression(void) {
   struct token *pt;
   struct label *l;

   pt = peektok();
   assert(pt != NULL);	/* already checked */

   if (pt->t_type == TOK_NUMBER) {
      gettok();
      return mkexpr_number(parsenumber(pt->t_value));
   }
   else if (pt->t_type == TOK_IDENT) {
      gettok();
      if (!strcmp(pt->t_value, ".")) {
	 l = label_declaredot(linenum);
      }
      else {
	 l = label_declare(linenum, pt->t_value, SCRATCHLABELS_REFER);
      }
      return mkexpr_label(l);
   }
   else if (pt->t_type == TOK_TARGET) {
      /*
       * TTOK_NIL must exist so the field can be initialized, but
       * shouldn't ever be seen.
       */
      assert(pt->t_ttype != TTOK_NIL);
      gettok();
      return mkexpr_target(pt->t_ttype, pt->t_value);
   }
   else if (pt->t_type == TOK_STRING) {
      gettok();
      return mkexpr_string(pt->t_value);
   }
   else if (pt->t_type!=TOK_LPAREN) {
      noparse("Syntax error in expression");
   }
   return parse_parens();
}

/*
 * Expect a prefix expression.
 */
static struct expr *parse_prefix_expression(void) {
   struct token *pt;

   pt = peektok();
   if (pt==NULL) {
      noparse("Expression expected following operator");
   }
   switch (pt->t_type) {
    case TOK_PLUS:
     /* unary plus - ignore */
     gettok();
     return parse_prefix_expression();
    case TOK_MINUS: 
     /* unary minus */
     gettok();
     return mkexpr_unary(OP_NEG, parse_prefix_expression()); 
    case TOK_TILDE: 
     /* unary bitwise not */
     gettok();
     return mkexpr_unary(OP_BITNOT, parse_prefix_expression()); 
    case TOK_MODIFIER:
     /*
      * parenthesized string unary modifiers like %hi(); these
      * do *not* become EXPR_TARGET.
      */
     gettok();
     return mkexpr_modifier(pt->t_value, parse_parens());
    default:
     return parse_primary_expression();
   }
}

/*
 * Binary operators in precedence order.
 */
static struct expr *parse_add_expression(void) {
   return parse_binary_operator(TOK_PLUS, TOK_MINUS, parse_prefix_expression);
}

static struct expr *parse_shift_expression(void) {
   return parse_binary_operator(TOK_LTLT, TOK_GTGT, parse_add_expression);
}

static struct expr *parse_bitand_expression(void) {
   return parse_binary_operator(TOK_AMP, TOK_NIL, parse_shift_expression);
}

static struct expr *parse_bitxor_expression(void) {
   return parse_binary_operator(TOK_CARET, TOK_NIL, parse_bitand_expression);
}

static struct expr *parse_bitor_expression(void) {
   return parse_binary_operator(TOK_BAR, TOK_NIL, parse_bitxor_expression);
}

static struct expr *parse_real_expression(void) {
   return parse_bitor_expression();
}

/*
 * A juxtapose expression is two expressions sitting next to each other
 * with nothing in between them.
 */
static struct expr *parse_juxtapose_expression(void) {
   struct expr *x;

   x = parse_bitor_expression();

   while (peektok()!=NULL) {
      struct expr *x2 = parse_bitor_expression();
      assert(x2 != NULL);

      x = mkexpr_juxtapose(x, x2);
   }

   return x;
}

/*
 * Top level.
 */
static struct expr *parse_complete_expression(void) {
   struct token *pt;
   struct expr *x;

   pt = peektok();
   if (pt==NULL) {
      noparse("Parse error: invalid null operand");
   }

   x = parse_juxtapose_expression();
   assert(x != NULL);

   pt = peektok();
   assert(pt == NULL);

   return x;
}

////////////////////////////////////////////////////////////

static struct expr *real_parserange(int ln, struct tokenarray *argtoks,
				    unsigned lo, unsigned hi) {
   struct tokenarray mytoks;
   struct token *t, *pt;
   struct expr *x;
   unsigned i;

   /*
    * why do we need to copy the array?
    * answer: we didn't while we were only parsing the whole array,
    * but now that's not true again.
    */

   /*num = tokenarray_num(argtoks);*/
   tokenarray_init(&mytoks);
   tokenarray_setsize(&mytoks, hi - lo);
   for (i=lo; i<hi; i++) {
      t = tokenarray_get(argtoks, i);
      assert(t != NULL);
      tokenarray_set(&mytoks, i - lo, t);
   }

   ptoks = &mytoks;
   curtok = 0;
   linenum = ln;

   x = parse_complete_expression();
   assert(x != NULL);

   pt = peektok();
   if (pt != NULL) {
      noparse("Parse error: missing/invalid operator or trailing garbage");
   }

   tokenarray_setsize(&mytoks, 0);
   tokenarray_cleanup(&mytoks);
   ptoks = NULL;

   return x;
}

/*
 * External entry points.
 */
struct expr *parserange(int ln, struct tokenarray *argtoks,
			unsigned lo, unsigned hi, bool failok) {
   jump_on_error = failok;
   if (jump_on_error) {
      if (setjmp(jb)) {
	 return NULL;
      }
   }
   return real_parserange(ln, argtoks, lo, hi);
}

struct expr *parse(int ln, struct tokenarray *argtoks, bool failok) {
   return parserange(ln, argtoks, 0, tokenarray_num(argtoks), failok);
}
