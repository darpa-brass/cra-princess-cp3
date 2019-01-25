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
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "utils.h"
#include "expr.h"
#include "section.h"
#include "reloc.h"
#include "sectionops.h"
#include "relocops.h"

/*
 * XXX this needs to exist, and since it's MD it should be generated
 * in targetreloc.c.
 */
static bool fits_field(u_machlarge val, enum reloc_field f) {
   (void)val;
   (void)f;
   return true;
}

/*
 * XXX this too (it's supposed to be a human-readable version of the type)
 */
static const char *target_reloc_field_desc(enum reloc_field f) {
   return target_reloc_field_name(f);
}

u_machlarge process_expr(int linenum, struct expr *x, enum reloc_field f,
			 u_machword offset) {
   u_machlarge val;
   struct reloc *r;
   
   r = compile_expr(linenum, x, &val);
   if (r) {
      r->r_field = f;
      r->r_offset = section_getsize(getcursection(linenum)) + offset;
      reloc_add(r, getcursection(linenum));
   }
   if (!fits_field(val, f)) {
      file_err(linenum, "Immediate value out of range: 0x%llx in %s field",
	       (unsigned long long)val, target_reloc_field_desc(f));
   }
   return val;
}
