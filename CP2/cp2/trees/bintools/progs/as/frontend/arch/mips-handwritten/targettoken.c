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
#include <errno.h>
#include "common.h"

#include "utils.h"
#include "token.h"

/*
 * MIPS token-processing functions
 *
 * Registers always begin with $, which may be followed either by a
 * number or by a two-character string name. (The common form of using
 * the name without $ requires cpp and regdefs.h.) We accept the names
 * of all registers with $, even though historically MIPS assemblers
 * only accepted some (e.g. $gp) and not others (e.g. $t0).
 *
 * XXX note that the names are per-ABI and we can't currently handle
 * that.
 */

/*
 * Check if S contains (only) a small decimal number less than BOUND.
 */
static bool smallnumberat(const char *s, unsigned bound) {
   unsigned long val;
   char *t;

   errno = 0;
   val = strtoul(s, &t, 10);
   return errno == 0 && *t == 0 && val < bound;
}

/*
 * Given a string, return the register number it represents, or -1
 * if it's not a register.
 *
 * XXX is there a different name for $0? I thought it was "z0" but gas
 * doesn't accept "$z0" even though it accepts everything else
 * e.g. "$t0". For now, we'll accept "$z0".
 */
static int getregister(const char *str) {
   static const struct {
      const char *name;
      int reg;
   } names[] = {
      { "z0", 0 },
      { "AT", 1 },
      { "v0", 2 },
      { "v1", 3 },
      { "a0", 4 },
      { "a1", 5 },
      { "a2", 6 },
      { "a3", 7 },
      { "t0", 8 },
      { "t1", 9 },
      { "t2", 10 },
      { "t3", 11 },
      { "t4", 12 },
      { "t5", 13 },
      { "t6", 14 },
      { "t7", 15 },
      { "s0", 16 },
      { "s1", 17 },
      { "s2", 18 },
      { "s3", 19 },
      { "s4", 20 },
      { "s5", 21 },
      { "s6", 22 },
      { "s7", 23 },
      { "t8", 24 },
      { "t9", 25 },
      { "k0", 26 },
      { "k1", 27 },
      { "gp", 28 },
      { "sp", 29 },
      { "s8", 30 }, {"fp", 30 },
      { "ra", 31 },
   };
   //static const unsigned numnames = ARRAYCOUNT(names); // XXX
   static const unsigned numnames = sizeof(names) / sizeof(names[0]);

   unsigned i;

   assert(str[0]!=0);

   for (i=0; i<numnames; i++) {
      if (!strcmp(str, names[i].name)) {
	 return names[i].reg;
      }
   }

   return -1;
}


/*
 * Search and edit the token array, which contains the tokens for a
 * single operand, and substitute derived tokens for primitive tokens
 * on a lexical basis. Entries in toks[] that are left NULL are
 * skipped by the calling code; there is no need to compact the array.
 *
 * For MIPS we recognize the following patterns:
 *
 *    $[0-9]+			Register.
 *    $ident			Register.
 *    ident			Symbol
 *    %ident			Operator.
 */

void target_scantokens(int line, struct tokenarray *toks) {
   unsigned i, num;
   struct token *t0, *t1;
   int regnum;
   char tmp[4], *s;
   size_t len;

   (void)line;

   num = tokenarray_num(toks);
   assert(num > 0);

   /*
    * Look for registers, which are certain identifiers beginning with
    * a '$'.
    */
   for (i=0; i<num; i++) {
      t0 = tokenarray_get(toks, i);
      if (t0 == NULL) {
	 continue;
      }
      if (t0->t_type != TOK_IDENT || t0->t_value[0] != '$') {
	 continue;
      }

      /* $f0-$f31 are floating point regs */
      if (t0->t_value[1] == 'f' && smallnumberat(t0->t_value+2, 32)) {
	 /* XXX should mark it explicitly as an fp register */
	 t0->t_type = TOK_TARGET;
	 t0->t_ttype = TTOK_REGCLASS_FPREG;
	 s = dostrdup(t0->t_value + 2);
	 dostrfree(t0->t_value);
	 t0->t_value = s;
	 continue;
      }

      /* $cc0-$cc7 are fpu condition code registers */
      if (t0->t_value[1] == 'c' && t0->t_value[2] == 'c' &&
	  smallnumberat(t0->t_value+3, 8)) {
#if 1 /* woo */
	 t0->t_type = TOK_TARGET;
	 t0->t_ttype = TTOK_REGCLASS_FPCC;
         /* the value should be the number, not the symbol */
	 s = dostrdup(t0->t_value + 3);
#else
	 t0->t_type = TOK_NUMBER;
	 s = dostrdup(t0->t_value + 3);
#endif
	 dostrfree(t0->t_value);
	 t0->t_value = s;
	 continue;
      }

      /* $c[023].0-31 are cop0/2/3 regs (only) */
      /* XXX: should this be $c0.n or $cop0.n? */
      if (t0->t_value[1] == 'c' && t0->t_value[2] == '0' &&
	  t0->t_value[3] == '.' &&
	  smallnumberat(t0->t_value+4, 32)) {
	 t0->t_type = TOK_TARGET;
	 t0->t_ttype = TTOK_REGCLASS_COP0REG;
	 s = dostrdup(t0->t_value + 4);
	 dostrfree(t0->t_value);
	 t0->t_value = s;
	 continue;
      }
      if (t0->t_value[1] == 'c' && t0->t_value[2] == '2' &&
	  t0->t_value[3] == '.' &&
	  smallnumberat(t0->t_value+4, 32)) {
	 t0->t_type = TOK_TARGET;
	 t0->t_ttype = TTOK_REGCLASS_COP2REG;
	 s = dostrdup(t0->t_value + 4);
	 dostrfree(t0->t_value);
	 t0->t_value = s;
	 continue;
      }
      if (t0->t_value[1] == 'c' && t0->t_value[2] == '3' &&
	  t0->t_value[3] == '.' &&
	  smallnumberat(t0->t_value+4, 32)) {
	 t0->t_type = TOK_TARGET;
	 t0->t_ttype = TTOK_REGCLASS_COP3REG;
	 s = dostrdup(t0->t_value + 4);
	 dostrfree(t0->t_value);
	 t0->t_value = s;
	 continue;
      }

      /* $0-$31 are general regs or cop0/2/3 regs, but not fpu regs  */
      if (smallnumberat(t0->t_value+1, 32)) {
	 t0->t_type = TOK_TARGET;
#if 0 /* XXX */
	 t0->t_ttype = TTOK_ANYREGISTER;
#else
	 t0->t_ttype = TTOK_REGCLASS_GENERALREG;
#endif
	 s = dostrdup(t0->t_value + 1);
	 dostrfree(t0->t_value);
	 t0->t_value = s;
	 continue;
      }

      /* $name are general regs (only) */
      regnum = getregister(t0->t_value+1);
      if (regnum >= 0) {
	 t0->t_type = TOK_TARGET;
	 t0->t_ttype = TTOK_REGCLASS_GENERALREG;
	 snprintf(tmp, sizeof(tmp), "%d", regnum);
	 dostrfree(t0->t_value);
	 t0->t_value = dostrdup(tmp);
	 continue;
      }

      /* other identifiers beginning with $ are just identifiers */
   }

   /* Look for modifiers (like %lo) */
   for (i=0; i<num-1; i++) {
      t0 = tokenarray_get(toks, i);
      t1 = tokenarray_get(toks, i+1);
      if (t0 == NULL || t1 == NULL) {
	 continue;
      }
      if (t0->t_type == TOK_PCT) {
	 if (t1->t_type == TOK_IDENT) {
	    t1->t_type = TOK_MODIFIER;
	    token_destroy(t0);
	    tokenarray_set(toks, i, NULL);
	 }
      }
   }

   /* Look for symbols */
   for (i=0; i<num; i++) {
      t0 = tokenarray_get(toks, i);
      if (t0 == NULL) {
	 continue;
      }
      if (t0->t_type==TOK_NUMBER) {
	 if (t0->t_value[0] != '0' ||
	     (t0->t_value[1] != 'x' && t0->t_value[1] != 'X')) {
	    len = strlen(t0->t_value);
	    assert(len > 0);
	    if (t0->t_value[len-1] == 'f' ||
		t0->t_value[len-1] == 'b') {
	       /* decimal number followed by f or b is a scratch label */
	       t0->t_type = TOK_IDENT;
	    }
	 }
      }
   }

   /*
    * Look for @ident, as seen in .type foo,@function; fold the @ into
    * the identifier. XXX: is this really the best way to handle this?
    * There isn't any other form of expression we can really use to
    * hold this, but maybe we should have a MI form of expression
    * specifically for symbol types.
    *
    * Note that the identifier will have been made into a TOK_SYMBOL by
    * the above loop; change it back.
    */
   for (i=0; i < num-1; i++) {
      t0 = tokenarray_get(toks, i);
      t1 = tokenarray_get(toks, i+1);
      if (t0==NULL || t1== NULL) {
	 continue;
      }
      if (t0->t_type == TOK_AT && t1->t_type == TOK_IDENT) {
	 /* XXX don't leak the old string */
	 t1->t_value = dostrdup2("@", t1->t_value);
	 token_destroy(t0);
	 tokenarray_set(toks, i, NULL);
      }
   }
}
