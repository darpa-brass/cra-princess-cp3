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
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "expr.h"
#include "as.h"
#include "match.h"
#include "backend.h"
#include "targetoper.h"

#if 0 /* obsolete */
//
// Returns true if the operand is ok for an instruction expecting an
// operand of the type given by CH (one of the following).
//    r  register
//    x  expression
//    s  symbol
//    n  number
//    i  miscellaneous loose identifier
//    q  string constant
//
static size_t operand_matches(const char *str, struct expr *x) {
   /*
    * XXX this is not complete
    */

   const char *t;
   size_t ret, len;

   t = strchr(str, ' ');
   if (t) {
      len = t - str;
      /* consume the separating space */
      ret = len + 1;
   }
   else {
      len = strlen(str);
      ret = len;
   }

   if (len == 1 && str[0]=='r' && 
       x->x_type == EXPR_TARGET && x->x_target.ttok == TTOK_REGISTER) {
      return ret;
   }
   if (len == 1 && str[0]=='q' && x->x_type == EXPR_STR) {
      return ret;
   }
   if (len == 1 && str[0]=='n' && x->x_type == EXPR_NUM) {
      return ret;
   }
   /* XXX kill off 's' */
   if (len == 1 && str[0]=='s' && x->x_type == EXPR_IDENT) {
      return ret;
   }
   if (len == 1 && str[0]=='i' && x->x_type == EXPR_IDENT) {
      return ret;
   }
   if (len == 1 && str[0]=='x') {
      return ret;
   }
   return 0;
}
#endif

/*
 * Compare function for bsearch.
 */
static int opcmp(const void *keyv, const void *av) {
   const char *key = (const char *)keyv;
   const struct insnmatch *val = (const struct insnmatch *)av;

   return strcmp(key, val->opcode);
}

/*
 * Find the first instruction in the match table with the given opcode
 * name.
 */
static unsigned findop(const char *opc) {
   struct insnmatch *p;
   unsigned ix;

   p = bsearch(opc, opcodes, numopcodes, sizeof(opcodes[0]), opcmp);
   if (p == NULL) {
      return numopcodes;
   }

   /* convert pointer to array index */
   ix = (p - opcodes);

#if 0 /* no longer needed */
   /* find the first one with the same name */
   while (ix>0 && !strcmp(opc, opcodes[ix-1].opcode)) {
      ix--;
   }
#endif

   return ix;
}

/*
 * Look up an opcode by name and return the table of signatures it
 * can have.
 */
const struct insnsig *backend_find_opcode(const char *opcode,
					  unsigned *numsigs_ret) {
   unsigned ix;

   ix = findop(opcode);
   if (ix == numopcodes) {
      return NULL;
   }
   *numsigs_ret = opcodes[ix].numsigs;
   return opcodes[ix].sigs;
}

/*
 * Check if the signature entry matches the operand list we have.
 */
static int matches(const struct insnsig *sig, struct operandarray *ops) {
   unsigned i, num, j, siglen;
   struct operand *oper;

   siglen = sig->siglen;
   num = operandarray_num(ops);

   if (sig->multisig) {
      assert(siglen>0);
      if (num % siglen != 0) {
	 return 0;
      }

      for (i=0; i<num; i += siglen) {
	 for (j=0; j<siglen; j++) {
	    oper = operandarray_get(ops, i+j);
	    if (!sig->sigmatchers[j](oper)) {
               return 0;
	    }
	 }
      }
   }
   else {
      if (siglen != num) {
         return 0;
      }
      for (i=0; i<num; i++) {
	 oper = operandarray_get(ops, i);
         if (!sig->sigmatchers[i](oper)) {
            return 0;
         }
      }
   }
   return 1;
}

/*
 * Assemble an instruction, using the list of operands from the given
 * input line.
 */
void backend_dispatch_opcode(int line, const char *opcode, const struct insnsig *sigs,
			     unsigned numsigs, struct operandarray *ops) {
   unsigned j;

   for (j=0; j<numsigs; j++) {
      if (matches(&sigs[j], ops)) {
         sigs[j].call_emit(line, ops);
         return;
      }
   }
   file_err(line, "Bad operands for %s", opcode);
}
