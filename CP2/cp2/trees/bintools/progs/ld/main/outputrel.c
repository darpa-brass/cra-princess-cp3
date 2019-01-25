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

#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include "common.h"

#include "array.h"
#include "genfmt.h"
#include "binfile.h"

#include "section.h"
#include "outputsym.h"
#include "outputrel.h"

DECLARRAY(genreloc, static inline);
DEFARRAY(genreloc, static inline);

static struct genrelocarray relocs;

void outputreloc_add(struct genreloc *gr) {
   genrelocarray_add(&relocs, gr);
}

static void doreloc(struct genreloc *gr) {
   u_machword val;

   val = outputsym_getaddr(gr->gr_symbol);

   machdep_do_reloc(gr->gr_code, gr->gr_section, gr->gr_offset, val,
		    gr->gr_addend);
}

void outputreloc_performall(void) {
   struct genreloc *gr;
   unsigned i, num;

   num = genrelocarray_num(&relocs);
   for (i=0; i<num; i++) {
      gr = genrelocarray_get(&relocs, i);
      doreloc(gr);
   }

   for (i=0; i<num; i++) {
      gr = genrelocarray_get(&relocs, i);
      genreloc_destroy(gr);
   }
   genrelocarray_setsize(&relocs, 0);
}

void outputreloc_markusedsyms(void) {
   struct genreloc *gr;
   unsigned i, num;

   outputsym_clearused();
   num = genrelocarray_num(&relocs);
   for (i=0; i<num; i++) {
      gr = genrelocarray_get(&relocs, i);
      outputsym_markused(gr->gr_symbol);
   }
}

void outputreloc_emit(struct binfile *bf) {
   struct genreloc *gr;
   unsigned i, num;

   num = genrelocarray_num(&relocs);
   for (i=0; i<num; i++) {
      gr = genrelocarray_get(&relocs, i);
      binfile_addreloc(bf, gr);
   }
}

////////////////////////////////////////////////////////////
// global init

void outputrel_setup(void) {
   genrelocarray_init(&relocs);
}

void outputrel_shutdown(void) {
   genrelocarray_cleanup(&relocs);
}

////////////////////////////////////////////////////////////
// bletch

/* XXX these should go away */
unsigned modimm_hack_a(int lineno, unsigned x) {
   (void)lineno;
   (void)x;
   assert(0);
   return 0;
}
unsigned modimm_hack_b(int lineno, unsigned x) {
   (void)lineno;
   (void)x;
   assert(0);
   return 0;
}
