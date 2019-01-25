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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "utils.h"
#include "langdefs.h"
#include "expr.h"
#include "eparse.h"
#include "fparse.h"
#include "backend.h"
#include "token.h"
#include "targetoper.h"

////////////////////////////////////////////////////////////
// MI ops on struct operand

static struct operand *operand_create(void) {
   struct operand *oper;

   oper = domalloc(sizeof(*oper));
   operand_init(oper);
   return oper;
}

static void operand_destroy(struct operand *oper) {
   operand_cleanup(oper);
   dofree(oper, sizeof(*oper));
}

////////////////////////////////////////////////////////////
// character classification

/*
 * Do not use <ctype.h> because its behavior is locale-dependent,
 * and assembly language is supposed to be the same everywhere.
 */

static int is_digit(int ch) {
   return ch >= '0' && ch <= '9';
}

static int is_identfirstchar(int ch) {
   if (is_digit(ch)) {
      return 1;
   }
   return is_letter(ch);
}

static int is_identsecondchar(int ch) {
   if (is_digit(ch)) {
      return 1;
   }
   return is_subletter(ch);
}

////////////////////////////////////////////////////////////
// tokenarray tools

/*
 * Drop nulls from a tokenarray.
 */
static void compact_tokens(struct tokenarray *ar) {
   unsigned i, j, num;
   struct token *t;

   num = tokenarray_num(ar);
   for (i=j=0; i<num; i++) {
      t = tokenarray_get(ar, i);
      if (t != NULL) {
	 if (i > j) {
	    tokenarray_set(ar, j, t);
	 }
	 j++;
      }
   }
   assert(i >= j);
   tokenarray_setsize(ar, j);
}

/*
 * Delete whitespace tokens from a tokenarray. (Then use
 * compact_tokens to remove the gaps.)
 */
static void nows_tokens(struct tokenarray *ar) {
   unsigned i, num;
   struct token *t;

   num = tokenarray_num(ar);
   for (i=0; i<num; i++) {
      t = tokenarray_get(ar, i);
      if (t != NULL && t->t_type == TOK_WS) {
	 tokenarray_set(ar, i, NULL);
	 token_destroy(t);
      }
   }
}

////////////////////////////////////////////////////////////
// parsing

/*
 * check for an assignment of labels
 */
static int find_labelassignment(int line, struct tokenarray *ar,
				unsigned start, unsigned end) {
   unsigned i;
   struct token *t1, *t2, *t3, *t4;

   assert(start < end);

   /* we've already skipped whitespace, and there should be no nulls here */

   i = start;

   t1 = tokenarray_get(ar, i);
   assert(t1 != NULL);
   if (t1->t_type != TOK_IDENT) {
      /* doesn't match */
      return false;
   }
   i++;

   if (i == end) {
      return false;
   }
   
   while (i < end && (t2 = tokenarray_get(ar, i))->t_type == TOK_WS) {
      i++;
   }
   if (i==end) {
      return false;
   }
   if (t2->t_type != TOK_EQ) {
      /* doesn't match */
      return false;
   }
   i++;

   while (i < end && (t3 = tokenarray_get(ar, i))->t_type == TOK_WS) {
      i++;
   }
   if (i==end) {
      return false;
   }
   if (t3->t_type != TOK_IDENT) {
      /* doesn't match */
      return false;
   }
   i++;

   while (i < end && (t4 = tokenarray_get(ar, i))->t_type == TOK_WS) {
      i++;
   }
   if (i!=end) {
      /* matched but was extra stuff after */
      return false;
   }

   if (!strcmp(t3->t_value, ".")) {
      /* label = .  -- define the label as here */
      backend_add_label(line, t1->t_value);
   }
   else {
      /* label = label  -- assign the label to the old one */
      backend_assign_label(line, t1->t_value, t3->t_value);
   }
   return true;
}

/*
 * helper for parsing labels
 */
static int find_labelmarker(struct tokenarray *ar,
		      unsigned start, unsigned end) {
   unsigned i;
   struct token *t;
   bool seensomething;

   /*
    * XXX: originally this logic was very broad in order to allow
    * target_scantokens to classify whatever it wanted as a label,
    * and allowed basically anything before a colon. This breaks on
    * arm where modifiers are marked with colons, so I tightened it
    * to reject if two identifiers appear, or an identifier and a
    * number.
    *
    * Since in the future probably target_scantokens will be run
    * before we get here, this is probably ok. But we should at
    * that point review this and figure out if it's general enough
    * (given what we expect assembly languages to look like) and
    * maybe parameterize it more.
    */

   seensomething = false;
   for (i=start; i<end; i++) {
      t = tokenarray_get(ar, i);
      if (t == NULL) {
	 continue;
      }

      if (t->t_type == TOK_COLON) {
	 return i;
      }

      if (t->t_type == TOK_IDENT || t->t_type == TOK_NUMBER) {
	 if (seensomething) {
	    return -1;
	 }
	 seensomething = true;
      }
   }
   return -1;
}

/*
 * Find the opcode. Stuff all the bits found into the first token,
 * and delete any other participating tokens.
 *
 * Return the next token index in the array.
 */
static unsigned collect_opcode(struct tokenarray *tokens,
			       unsigned start, unsigned end)
{
   struct token *t;
   unsigned pos, i;
   size_t moresize, len;
   char *newval;

   assert(start < end);

   /*
    * The first token should be (maybe the beginning of) the opcode
    * and thus an identifier.
    */
   t = tokenarray_get(tokens, start);
   if (t->t_type != TOK_IDENT) {
      return start;
   }
   pos = start + 1;

   /*
    * Because there are architectures that have commas in their opcode
    * names, stick any commas and further identifiers we find into the
    * opcode, until we see whitespace or some other punctuation.
    *
    * XXX: we should probably have a target-specific list of
    * "magic letters" or something to handle this way, since it's not
    * necessarily going to be just commas.
    */
   for (; pos < end; pos++) {
      t = tokenarray_get(tokens, pos);
      if (t == NULL) {
	 /* this shouldn't happen; but be safe */
	 continue;
      }
      if (t->t_type == TOK_IDENT || t->t_type == TOK_NUMBER) {
	 continue;
      }
      if (t->t_type == TOK_COMMA) {
	 continue;
      }
      if (t->t_type == TOK_WS) {
	 break;
      }
      break;
   }

   moresize = 0;
   for (i = start+1; i < pos; i++) {
      t = tokenarray_get(tokens, i);
      if (t == NULL) {
	 continue;
      }
      if (t->t_type == TOK_IDENT || t->t_type == TOK_NUMBER) {
	 moresize += strlen(t->t_value);
	 continue;
      }
      if (t->t_type == TOK_COMMA) {
	 moresize++;
	 continue;
      }
      assert(0);
   }

   if (moresize == 0) {
      /* nothing actually to do */
      return pos;
   }

   t = tokenarray_get(tokens, start);
   len = strlen(t->t_value);
   newval = domalloc(len + moresize + 1);
   memcpy(newval, t->t_value, len);
   dostrfree(t->t_value);
   t->t_value = newval;
   newval += len;

   for (i = start+1; i < pos; i++) {
      t = tokenarray_get(tokens, i);
      if (t == NULL) {
	 continue;
      }

      if (t->t_type == TOK_IDENT || t->t_type == TOK_NUMBER) {
	 len = strlen(t->t_value);
	 memcpy(newval, t->t_value, len);
	 newval += len;
      }
      else if (t->t_type == TOK_COMMA) {
	 *newval = ',';
	 newval++;
      }
      else {
	 assert(0);
      }

      tokenarray_set(tokens, i, NULL);
      token_destroy(t);
   }
   *newval = 0;

   return pos;
}

/*
 * Parse an operand.
 */
static struct operand *loadoperand(int line, struct tokenarray *tokens,
				   unsigned start, unsigned end)
{
   struct tokenarray optokens;
   struct token *t;
   struct operand *oper;
   unsigned num, i;
   size_t len;

   num = tokenarray_num(tokens);
   assert(start <= num);
   assert(end <= num);
   assert(start <= end);

   /* Transfer tokens to our own array so we can expand/shrink and whatnot */
   tokenarray_init(&optokens);
   for (i=start; i<end; i++) {
      t = tokenarray_get(tokens, i);
      assert(t != NULL);
      tokenarray_add(&optokens, t);
      tokenarray_set(tokens, i, NULL);
   }

   /*
    * "Decimal numbers" that end in f or b are scratch label
    * references and thus need to be marked as identifiers.
    */
   for (i=0; i<tokenarray_num(&optokens); i++) {
      t = tokenarray_get(&optokens, i);
      if (t->t_type==TOK_NUMBER) {
	 if (t->t_value[0] != '0' ||
	     (t->t_value[1] != 'x' && t->t_value[1] != 'X')) {
	    len = strlen(t->t_value);
	    assert(len > 0);
	    if (t->t_value[len-1] == 'f' ||
		t->t_value[len-1] == 'b') {
	       /* it's a scratch label */
	       t->t_type = TOK_IDENT;
	    }
	 }
      }
   }

   /* Let the target-specific code find registers, operators, etc. */
   target_scantokens(line, &optokens);

   /* drop whitespace */
   nows_tokens(&optokens);

   /* Compact the array if null token pointers were left in it. */
   compact_tokens(&optokens);

   /* Pass it to the expression parser. */
#if 0 /* for debugging */
   file_warn(line, "Calling parser: %d tokens", tokenarray_num(&optokens));
   num = tokenarray_num(&optokens);
   for (i=0; i<num; i++) {
      const char *val;
      int reg;

      t = tokenarray_get(&optokens, i);
      val = t->t_value;
      t->t_register;

      switch (t->t_type) {
       case TOK_NIL: file_warn(line, "   nil"); break;
       case TOK_IDENT: file_warn(line, "   ident: %s", val); break;
       case TOK_NUMBER: file_warn(line, "   number: %s", val); break;
       case TOK_STRING: file_warn(line, "   string: \"%s\"", val); break;
       case TOK_PLUS: file_warn(line, "   plus"); break;
       case TOK_MINUS: file_warn(line, "   minus"); break;
       case TOK_LPAREN: file_warn(line, "   lparen"); break;
       case TOK_RPAREN: file_warn(line, "   rparen"); break;
       case TOK_DOLLAR: file_warn(line, "   dollar"); break;
       case TOK_COLON: file_warn(line, "   colon"); break;
       case TOK_SEMICOLON: file_warn(line, "   semicolon"); break;
       case TOK_COMMA: file_warn(line, "   comma"); break;
       case TOK_AT: file_warn(line, "   at"); break;
       case TOK_EQ: file_warn(line, "   eq"); break;
       case TOK_PCT: file_warn(line, "   pct"); break;
       case TOK_TARGET:
	switch (t->t_ttype) {
	 case TTOK_NIL: file_warn(line, "   target nil (!?)"); break;
	 case TTOK_REGISTER: file_warn(line, "   register %d", reg); break;
	 case TTOK_OPERATOR: file_warn(line, "   operator %s", val); break;
	}
	break;

      }
   }
#endif

   oper = operand_create();
   operand_match(line, oper, &optokens);

   num = tokenarray_num(&optokens);
   for (i=0; i<num; i++) {
      t = tokenarray_get(&optokens, i);
      if (t != NULL) {
	 token_destroy(t);
      }
   }

   return oper;
}

/*
 * Parse a whole instruction.
 */
static void loadinstruction(int line, struct tokenarray *tokens, 
			    unsigned start, unsigned end)
{
   unsigned num, i, ix;
   struct token *t;
   struct operand *oper;
   const char *opcode;
   const struct insnsig *insnsigs;
   unsigned numsigs;
   struct operandarray operands;

   num = tokenarray_num(tokens);
   assert(start <= num);
   assert(end <= num);
   assert(start <= end);

   /*
    * Ignore leading and trailing whitespace.
    */
   while (start < end && tokenarray_get(tokens, start)->t_type == TOK_WS) {
      start++;
   }
   while (end > start && tokenarray_get(tokens, end - 1)->t_type == TOK_WS) {
      end--;
   }

   if (start==end) {
      /* empty line */
      return;
   }

   /*
    * Check for a line of the form IDENT = IDENT. The second IDENT can
    * be ".".
    */
   if (find_labelassignment(line, tokens, start, end)) {
      return;
   }

   /*
    * If there's a colon, the material up to the colon is a label. Use
    * target_scantokens to see if the target-specific code can
    * interpret the stuff before the colon as a symbol. If not, and
    * it's not a number (definition of a scratch label, which won't
    * have the f or b suffix that can be recognized to turn a number
    * into a scratch label reference symbol), reject it.
    */
   ix = find_labelmarker(tokens, start, end);
   if (ix < num) {
      struct tokenarray tmp;

      tokenarray_init(&tmp);
      tokenarray_setsize(&tmp, ix - start);
      for (i=start; i<ix; i++) {
	 tokenarray_set(&tmp, i-start, tokenarray_get(tokens, i));
	 tokenarray_set(tokens, i, NULL);
      }
      target_scantokens(line, &tmp);
      nows_tokens(&tmp);
      compact_tokens(&tmp);
      if (tokenarray_num(&tmp) > 1) {
	 file_err(line, "Invalid label");
      }
      t = tokenarray_get(&tmp, 0);
      if (t->t_type != TOK_NUMBER && t->t_type != TOK_IDENT) {
	 file_err(line, "Invalid label");
      }
      backend_add_label(line, t->t_value);
      token_destroy(t);
      tokenarray_setsize(&tmp, 0);
      tokenarray_cleanup(&tmp);
      start = ix + 1;
      while (start < end) {
	 t = tokenarray_get(tokens, start);
	 if (t == NULL || t->t_type == TOK_WS) {
	    start++;
	    continue;
	 }
	 break;
      }
   }

   if (start==end) {
      /* just a label */
      return;
   }

   /* Get the opcode, which comes next. */
   ix = collect_opcode(tokens, start, end);
   if (ix == start) {
      file_err(line, "Syntax error: Opcode or directive expected");
   }
   t = tokenarray_get(tokens, start);
   assert(t->t_type == TOK_IDENT);
   opcode = t->t_value;

   insnsigs = backend_find_opcode(opcode, &numsigs);
   if (insnsigs == NULL) {
      if (opcode[0] == '.') {
	 file_err(line, "No directive %s", opcode);
      }
      else {
	 file_err(line, "No opcode %s", opcode);
      }
   }

   start = ix;

   while (start < end) {
      t = tokenarray_get(tokens, start);
      if (t == NULL || t->t_type == TOK_WS) {
	 start++;
	 continue;
      }
      break;
   }

   /* What remains are operands, separated by commas. */
   operandarray_init(&operands);

   if (start < end) {
      unsigned parens, brackets, braces, sp;

      parens = 0;
      brackets = 0;
      braces = 0;
      sp = start;
      for (i=start; i<end; i++) {
	 t = tokenarray_get(tokens, i);
	 assert(t != NULL);

	 /* XXX this should enforce correct nesting of parens vs. brackets */
	 if (t->t_type == TOK_LPAREN) {
	    parens++;
	 }
	 else if (t->t_type == TOK_RPAREN) {
	    if (parens == 0) {
	       file_err(line, "Syntax error: mismatched parentheses");
	    }
	    else {
	       parens--;
	    }
	 }
	 else if (t->t_type == TOK_LBRACK) {
	    brackets++;
	 }
	 else if (t->t_type == TOK_RBRACK) {
	    if (brackets == 0) {
	       file_err(line, "Syntax error: mismatched brackets");
	    }
	    else {
	       brackets--;
	    }
	 }
	 else if (t->t_type == TOK_LBRACE) {
	    braces++;
	 }
	 else if (t->t_type == TOK_RBRACE) {
	    if (braces == 0) {
	       file_err(line, "Syntax error: mismatched braces");
	    }
	    else {
	       braces--;
	    }
	 }
	 else if (t->t_type==TOK_COMMA && parens==0 && brackets==0 && braces==0) {
	    operandarray_add(&operands, loadoperand(line, tokens, sp, i));
	    sp = i+1;
	 }
      }
      operandarray_add(&operands, loadoperand(line, tokens, sp, end));
      if (parens != 0) {
	 file_err(line, "Syntax error: mismatched parentheses");
      }
   }

   backend_dispatch_opcode(line, opcode, insnsigs, numsigs, &operands);

   num = operandarray_num(&operands);
   for (i=0; i<num; i++) {
      oper = operandarray_get(&operands, i);
      if (oper) {
	 operand_destroy(oper);
      }
   }

   operandarray_setsize(&operands, 0);
   operandarray_cleanup(&operands);
}

/*
 * Lexer state.
 */

static int inblockcomment = 0; /* > 0 if in a block comment */
static int blockcomment_startlinenum;

static const char linecomment_twochar[3] = AS_LINECOMMENT_TWOCHAR;
static const char linecomment_onechar[] = AS_LINECOMMENT_ONECHAR;

/*
 * Read an input line.
 *
 * Note that other than block comments, (primitive) tokens do not span
 * lines, so we don't have to worry about having to continue a token
 * started on the previous line, or about the last token on the line
 * not being complete.
 */
void parse_line(char *line, int linenum) {
   unsigned i, num, start;
   struct token *t;

   int ident=-1;	/* if >=0, the start of the current identifier */
   int string=-1;	/* if >=0, the start of the current string constant */
   int inesc=0;		/* true if in a backslash-escape in a string */
   int inws=0;		/* true if in whitespace */

   struct tokenarray tokens;

   /*
    * turn all whitespace into spaces
    * XXX: even inside string constants?
    */
   for (i=0; line[i]; i++) {
      if (strchr("\f\v\t", line[i])) {
	 line[i] = ' ';
      }
   }

   /*
    * tokenize
    */

   tokenarray_init(&tokens);

   for (i=0; line[i]; i++) {
      /*
       * Continuing whitespace
       */
      if (inws && line[i]==' ') {
         continue;
      }
      else if (inws) {
         inws = 0;
      }

      /*
       * Contents of string constants
       */
      if (string>=0 && inesc) {
	 inesc=0;
	 continue;
      }
      if (string>=0 && line[i]=='"') {
	 line[i]=0;
	 tokenarray_add(&tokens, token_create(TOK_STRING, line+string));
	 string = -1;
	 continue;
      }
      if (string>=0) {
	 if (line[i]=='\\') {
	    inesc = 1;
	 }
	 continue;
      }

      /*
       * Block comments -- note that the block comment delimiters are
       * target-independent.
       */
      if (line[i]=='/' && line[i+1]=='*') {
	 if (inblockcomment) {
#ifdef AS_BLOCKCOMMENTS_NEST
	    inblockcomment++;
#else
	    file_warn(linenum, "Open-comment sequence within comment");
#endif
	 }
	 else {
	    inblockcomment = 1;
	    blockcomment_startlinenum = linenum;
	 }
	 i++;
	 continue;
      }
      if (inblockcomment && line[i]=='*' && line[i+1]=='/') {
	 inblockcomment--;
	 i++;
	 continue;
      }
      if (inblockcomment) {
	 continue;
      }

      /*
       * identifiers
       */
      if (ident<0 && is_identfirstchar(line[i])) {
	 ident = i;
	 continue;
      }
      if (ident>=0 && is_identsecondchar(line[i])) {
	 continue;
      }
      if (ident>=0) {
	 int tmp = line[i];
	 line[i] = 0;
	 tokenarray_add(&tokens, token_create(TOK_IDENT, line+ident));
	 ident = -1;
	 line[i] = tmp;
	 /* no continue! still need to handle the current character */
      }

      /*
       * Single-line comments - the single-line comment delimiters are
       * target-specific, and there might be more than one. For now we
       * allow one two-character comment delimiter (kept in a single
       * string) and zero or more one-character comment delimiters,
       * all kept in one string.
       *
       * If there is no two-character comment delimiter the string
       * holding it contains "" and will not match this test. If there
       * are no one-character comment delimiters the string holding it
       * contains "" and will not match the strchr call.
       */
      if (line[i] == linecomment_twochar[0] &&
	  line[i+1] == linecomment_twochar[1]) {
	 /* drop remaining text */
	 break;
      }
      if (strchr(linecomment_onechar, line[i])) {
	 /* drop remaining text */
	 break;
      }

      /*
       * two-character punctuation
       */
      if (line[i]=='<' && line[i+1]=='<') {
	 tokenarray_add(&tokens, token_create(TOK_LTLT, NULL));
	 i++;
	 continue;
      }
      if (line[i]=='>' && line[i+1]=='>') {
	 tokenarray_add(&tokens, token_create(TOK_GTGT, NULL));
	 i++;
	 continue;
      }

      /*
       * one-character punctuation
       */
      switch (line[i]) {
       case ' ': tokenarray_add(&tokens, token_create(TOK_WS, NULL)); inws=1; break;
       case '"': string = i+1; break;
       case '(': tokenarray_add(&tokens, token_create(TOK_LPAREN, NULL)); break;
       case ')': tokenarray_add(&tokens, token_create(TOK_RPAREN, NULL)); break;
       case '[': tokenarray_add(&tokens, token_create(TOK_LBRACK, NULL)); break;
       case ']': tokenarray_add(&tokens, token_create(TOK_RBRACK, NULL)); break;
       case '{': tokenarray_add(&tokens, token_create(TOK_LBRACE, NULL)); break;
       case '}': tokenarray_add(&tokens, token_create(TOK_RBRACE, NULL)); break;
       case '!': tokenarray_add(&tokens, token_create(TOK_BANG, NULL)); break;
       case '#': tokenarray_add(&tokens, token_create(TOK_HASH, NULL)); break;
       case '$': tokenarray_add(&tokens, token_create(TOK_DOL, NULL)); break;
       case '%': tokenarray_add(&tokens, token_create(TOK_PCT, NULL)); break;
       case '&': tokenarray_add(&tokens, token_create(TOK_AMP, NULL)); break;
       case '*': tokenarray_add(&tokens, token_create(TOK_STAR, NULL)); break;
       case '+': tokenarray_add(&tokens, token_create(TOK_PLUS, NULL)); break;
       case ',': tokenarray_add(&tokens, token_create(TOK_COMMA, NULL)); break;
       case '-': tokenarray_add(&tokens, token_create(TOK_MINUS, NULL)); break;
       case '/': tokenarray_add(&tokens, token_create(TOK_SLASH, NULL)); break;
       case ':': tokenarray_add(&tokens, token_create(TOK_COLON, NULL)); break;
       case ';': tokenarray_add(&tokens, token_create(TOK_SEMIC, NULL)); break;
       case '<': tokenarray_add(&tokens, token_create(TOK_LT, NULL)); break;
       case '=': tokenarray_add(&tokens, token_create(TOK_EQ, NULL)); break;
       case '>': tokenarray_add(&tokens, token_create(TOK_GT, NULL)); break;
       case '?': tokenarray_add(&tokens, token_create(TOK_QUES, NULL)); break;
       case '@': tokenarray_add(&tokens, token_create(TOK_AT, NULL)); break;
       case '^': tokenarray_add(&tokens, token_create(TOK_CARET, NULL)); break;
       case '|': tokenarray_add(&tokens, token_create(TOK_BAR, NULL)); break;
       case '~': tokenarray_add(&tokens, token_create(TOK_TILDE, NULL)); break;
       default:
	file_err(linenum, "Illegal character `%c' in input", line[i]);
	break;
      }
   }

   /*
    * Because we guarantee a space at end of line below, we must have
    * seen the end of any identifier.
    */
   assert(ident<0);

   if (string>=0) {
      file_err(linenum, "Unterminated string constant");
   }

   /*
    * "Identifiers" that begin with a digit are numbers.
    */
   num = tokenarray_num(&tokens);
   for (i=0; i<num; i++) {
      t = tokenarray_get(&tokens, i);
      if (t->t_type==TOK_IDENT && is_digit(t->t_value[0])) {
	 t->t_type = TOK_NUMBER;
      }
   }

   /*
    * A separator token (often semicolon) introduces a completely new
    * instruction ("assembler line").
    */
   num = tokenarray_num(&tokens);
   start = 0;
#ifdef AS_SEPARATOR_TOKEN
   for (i=0; i<num; i++) {
      t = tokenarray_get(&tokens, i);
      if (t->t_type == AS_SEPARATOR_TOKEN) {
	 loadinstruction(linenum, &tokens, start, i);
	 start = i+1;
      }
   }
#endif
   loadinstruction(linenum, &tokens, start, num);

   num = tokenarray_num(&tokens);
   for (i=0; i<num; i++) {
      t = tokenarray_get(&tokens, i);
      if (t) {
	 token_destroy(t);
      }
   }

   tokenarray_setsize(&tokens, 0);
   tokenarray_cleanup(&tokens);
}

/*
 * Called after the last input line.
 */
void parse_eof(void) {
   if (inblockcomment) {
      file_err(blockcomment_startlinenum, "Unclosed block comment");
   }
}
