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
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "utils.h"
#include "expr.h"
#include "reloc.h"
#include "label.h"
#include "section.h"
#include "sectionops.h"
#include "as.h"
#include "modeinfo.h"
#include "targetmatch.h"

/*
 * miscellaneous directives
 */

/*
 * XXX 20170710 a lot of integer arguments got changed from
 * u_machlarge (which is portable though broader than necessary) to
 * sized integer types, whose sizes may be target-dependent. This
 * needs to be sorted out later.
 */


/*
 * gcc emits
 *    .file 1 "hello.c"
 * so the operand has to be defined as an expression (x) instead of
 * just a quoted string (q), and we have to peel off the number.
 * XXX: what's the number for anyway?
 * (apparently it's the number of the file and you can have more than
 * one)
 *
 * update: only the mips gcc does; sparc64 gcc just emits a string.
 */
void directive_file_q(int linenum, const char *str) {
   static int where = -1;

   if (where>=0) {
      file_warn(linenum, "Warning: Duplicate .file directive");
      file_err(where, "First .file directive was here");
   }
   where = linenum;

   set_sourcefile(str);
}
void directive_file_x(int linenum, struct expr *e) {
   const char *str;

   if (e->x_type != EXPR_JUXTAPOSE ||
       e->x_u.u_juxtapose.arg1->x_type != EXPR_NUM ||
       e->x_u.u_juxtapose.arg2->x_type != EXPR_STR) {
      file_err(linenum, "Invalid .file directive");
   }
   str = e->x_u.u_juxtapose.arg2->x_u.u_str;
   directive_file_q(linenum, str);
}

void directive_gnu_attribute_n_n(int linenum,
				uint32_t code, uint32_t val) {
   // XXX ignore for now
   (void)linenum;
   (void)code;
   (void)val;
}

void directive_ident_q(int linenum, const char *str) {
   /* XXX ignore for now */
   (void)linenum;
   (void)str;
}

void directive_frame_r_n_r(int linenum, uint8_t framereg, uint32_t size, uint8_t rareg) {
   // XXX for now ignore this
   (void)linenum;
   (void)framereg;
   (void)size;
   (void)rareg;
}

void directive_mask_n_n(int linenum, uint32_t mask, uint32_t pos) {
   // XXX for now ignore this
   (void)linenum;
   (void)mask;
   (void)pos;
}

void directive_fmask_n_n(int linenum, uint32_t mask, uint32_t pos) {
   // XXX for now ignore this
   (void)linenum;
   (void)mask;
   (void)pos;
}

/*
 * XXX these are sparc64-specific and should be moved out when we figure
 * out how to do that. (they do nothing)
 */
void directive_proc_(int linenum) {
   (void)linenum;
}
void directive_proc_x(int linenum, struct expr *x) {
   (void)linenum;
   (void)x;
}
void directive_register_r_rtag(int linenum, uint8_t reg, uint8_t tag) {
   switch (reg) {
    case 2: /* %g2 */
    case 3: /* %g3 */
    case 6: /* %g6 */
    case 7: /* %g7 */
     (void)tag;
     break;
    default:
     file_err(linenum, "Invalid register for .register directive");
   }
}

/*
 * XXX these are arm-specific and should be moved out when we figure out
 * how to do that. (they do nothing)
 */
void directive_syntax_s(int linenum, struct expr *sym) {
   if (sym->x_type != EXPR_IDENT) {
      file_err(linenum, "Invalid .syntax directive");
   }
   if (!strcmp(sym->x_u.u_ident.ident, "divided")) {
      return;
   }
   else if (!strcmp(sym->x_u.u_ident.ident, "unified")) {
      // XXX we'll pretend for now
      //file_err(linenum, "Unified syntax not yet supported");
   }
   else {
      file_err(linenum, "Unknown syntax %s", sym->x_u.u_ident.ident);
   }
}
void directive_arch_s(int linenum, struct expr *sym) {
   (void)linenum;
   (void)sym;
}
void directive_arch_extension_s(int linenum, struct expr *sym) {
   (void)linenum;
   (void)sym;
}
void directive_cpu_s(int linenum, struct expr *sym) {
   (void)linenum;
   (void)sym;
}
void directive_cpu_x(int linenum, struct expr *sym) {
   (void)linenum;
   (void)sym;
}
void directive_fpu_s(int linenum, struct expr *sym) {
   (void)linenum;
   (void)sym;
}
void directive_arm_(int linenum) {
   (void)linenum;
}
void directive_thumb_(int linenum) {
   file_err(linenum, "thumb mode not yet supported");
}
void directive_code_n(int linenum, uint32_t size) {
   switch (size) {
    case 16: directive_thumb_(linenum); break;
    case 32: directive_arm_(linenum); break;
    default: file_err(linenum, "Invalid .code size %u", size); break;
   }
}
void directive_force_thumb_(int linenum) {
   file_err(linenum, "thumb mode not yet supported");
}
void directive_thumb_func_(int linenum) {
   file_err(linenum, "thumb mode not yet supported");
}
void directive_thumb_set_(int linenum) {
   file_err(linenum, "thumb mode not yet supported");
}
void directive_eabi_attribute_n_n(int linenum, uint32_t a, uint32_t b) {
   (void)linenum;
   (void)a;
   (void)b;
}
void directive_personality_s(int linenum, struct expr *sym) {
   (void)linenum;
   (void)sym;
}
void directive_personalityindex_n(int linenum, uint32_t n) {
   (void)linenum;
   (void)n;
}
void directive_fnstart_(int linenum) {
   (void)linenum;
}
void directive_fnend_(int linenum) {
   (void)linenum;
}
