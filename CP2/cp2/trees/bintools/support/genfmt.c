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

/*
 * genfmt: generic binary format
 *
 * File-format-independent in-memory structures for sections, symbols, and
 * relocs.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "mem.h"
#include "genfmt.h"

bool gensect_isspecialnum(unsigned sectnum) {
   switch (sectnum) {
    case GSX_INVALID:
    case GSX_UNDEF:
    case GSX_COMMON:
    case GSX_ABS:
     return true;
    default:
     break;
   }
   return false;
}

struct gensect *gensect_create(const char *name) {
   struct gensect *gsx;

   gsx = domalloc(sizeof(*gsx));
   assert(name != NULL);
   gsx->gsx_name = dostrdup(name);
   gsx->gsx_vaddr = 0;
   gsx->gsx_size = 0;
   gsx->gsx_align = 0;
   gsx->gsx_flags = 0;
   gsx->gsx_data = NULL;
   return gsx;
}

void gensect_destroy(struct gensect *gsx) {
   dostrfree(gsx->gsx_name);
   dofree(gsx->gsx_data, gsx->gsx_size);
   dofree(gsx, sizeof(*gsx));
}

struct gensym *gensym_create(const char *name) {
   struct gensym *gsm;

   gsm = domalloc(sizeof(*gsm));
   gsm->gsm_name = name ? dostrdup(name) : NULL;
   gsm->gsm_value = 0;
   gsm->gsm_size = 0;
   gsm->gsm_align = 0;
   gsm->gsm_section = GSX_INVALID;
   gsm->gsm_type = GSMT_UNKNOWN;
   gsm->gsm_flags = 0;
   return gsm;
}

void gensym_destroy(struct gensym *gsm) {
   dostrfree(gsm->gsm_name);
   dofree(gsm, sizeof(*gsm));
}

struct genreloc *genreloc_create(void) {
   struct genreloc *gr;

   gr = domalloc(sizeof(*gr));
   gr->gr_addend = 0;
   gr->gr_offset = 0;
   gr->gr_section = GSX_INVALID;
   gr->gr_symbol = GSM_INVALID;
   gr->gr_code = -1;
   return gr;
}

void genreloc_destroy(struct genreloc *gr) {
   dofree(gr, sizeof(*gr));
}
