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
#include <string.h>
#include <assert.h>
#include "common.h"

#include "array.h"
#include "genfmt.h"
#include "binfile.h"

#include "section.h"
#include "outputsym.h"

struct outputsym {
   struct gensym *gsm;
   unsigned defn;
   bool used;
};

DECLARRAY_FULL(symarray, struct outputsym, static inline);
DEFARRAY_FULL(symarray, struct outputsym, static inline);

static struct symarray syms;

unsigned outputsym_add(struct gensym *gsm) {
   struct outputsym os;
   unsigned ix;

   os.gsm = gsm;
   os.defn = symarray_num(&syms);
   os.used = false;
   symarray_addx(&syms, os, &ix);

   assert(ix == os.defn);
   return ix;
}

void outputsym_setdefn(unsigned oldid, unsigned newid) {
   symarray_getptr(&syms, oldid)->defn = newid;
}

u_machword outputsym_getaddr(unsigned symbol) {
   u_machword base;
   struct outputsym *os;

   os = symarray_getptr(&syms, symbol);
   symbol = os->defn;
   os = symarray_getptr(&syms, symbol);

   base = section_getbase(os->gsm->gsm_section);
   return base + os->gsm->gsm_value;
}

void outputsym_clearused(void) {
   unsigned i, num;

   num = symarray_num(&syms);
   for (i=0; i<num; i++) {
      symarray_getptr(&syms, i)->used = false;
   }
}

void outputsym_markused(unsigned symbol) {
   unsigned defn;

   defn = symarray_getptr(&syms, symbol)->defn;
   symarray_getptr(&syms, defn)->used = true;
}

void outputsym_emit(struct binfile *bf) {
   struct outputsym *os;
   unsigned pass, i;

   for (pass=0; pass<2; pass++) {
      unsigned num = symarray_num(&syms);
      for (i=0; i<num; i++) {
	 os = symarray_getptr(&syms, i);

	 if (os->defn != i) {
	    /* Don't output symbols that are defined by other symbols. */
	    continue;
	 }
	 
	 /*
	  * Then, only output symbols that either (1) have a name, or (2)
	  * are listed as used.
	  */
	 if (os->gsm->gsm_name == NULL && !os->used) {
	    continue;
	 }

	 /*
	  * Emit all globally bound symbols first.
	  */
	 if (pass==0 && (os->gsm->gsm_flags & GSMF_GLOBL) == 0) {
	    continue;
	 }
	 else if (pass==1 && (os->gsm->gsm_flags & GSMF_GLOBL) != 0) {
	    continue;
	 }

	 binfile_addsym(bf, os->gsm, i);
      }
   }
}

////////////////////////////////////////////////////////////
// global init

void outputsym_setup(void) {
   symarray_init(&syms);
}

void outputsym_shutdown(void) {
   symarray_setsize(&syms, 0);
   symarray_cleanup(&syms);
}
