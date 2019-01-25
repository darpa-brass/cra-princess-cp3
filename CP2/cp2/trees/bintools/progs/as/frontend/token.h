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

#ifndef TOKEN_H
#define TOKEN_H

#include "array.h"
#include "targettoken.h"


/*
 * Possible input tokens
 *
 * This should match the list in langtree.ml in the gentarget code.
 */
enum toktypes {
   /* Invalid token type */
   TOK_NIL,

   /* Primitive token types (MI) */
   TOK_WS,
   TOK_IDENT,
   TOK_NUMBER,
   TOK_STRING,
   TOK_MODIFIER,
   TOK_LPAREN,
   TOK_RPAREN,
   TOK_LBRACK,
   TOK_RBRACK,
   TOK_LBRACE,
   TOK_RBRACE,
   TOK_BANG,
   TOK_HASH,
   TOK_DOL,
   TOK_PCT,
   TOK_AMP,
   TOK_STAR,
   TOK_PLUS,
   TOK_COMMA,
   TOK_MINUS,
   TOK_SLASH,
   TOK_COLON,
   TOK_SEMIC,
   TOK_LT,
   TOK_LTLT,
   TOK_EQ,
   TOK_GT,
   TOK_GTGT,
   TOK_QUES,
   TOK_AT,
   TOK_CARET,
   TOK_BAR,
   TOK_TILDE,

   /* Additional MD token types defined by target; use t_targettype */
   TOK_TARGET,
};

/*
 * Token structure
 */
struct token {
   enum toktypes t_type;
   enum targettoktypes t_ttype;	/* if t_type is TOK_TARGET */
   char *t_value;
};

/*
 * Array of tokens
 */
#ifndef TOKENINLINE
#define TOKENINLINE INLINE
#endif
DECLARRAY(token, TOKENINLINE);
DEFARRAY(token, TOKENINLINE);

/*
 * MI functions in token.c
 */
struct token *token_create(enum toktypes t, const char *s);
void token_destroy(struct token *t);

/*
 * MD functions in target/ttoken.c
 */
void target_scantokens(int line, struct tokenarray *);
bool ttok_is_baseexpr(enum targettoktypes tok);


#endif /* TOKEN_H */
