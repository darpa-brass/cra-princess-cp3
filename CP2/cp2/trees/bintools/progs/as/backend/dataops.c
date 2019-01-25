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
 * Data-related directives.
 */

/*
 * XXX 20170710 a lot of integer arguments got changed from
 * u_machlarge (which is portable though broader than necessary) to
 * sized integer types, whose sizes may be target-dependent. This
 * needs to be sorted out later.
 */

void directive_space_n(int linenum, uint32_t lval) {
   u_machword val, i;

   val = (u_machword) lval;
   if ((u_machlarge)val != lval) {
      file_err(linenum, "Size too large");
   }

   /* XXX lame */
   for (i=0; i<val; i++) {
      addbyte(linenum, 0);
   }
}

static int octal_digit(int ch) {
   if (ch>='0' && ch<='7') {
      return ch-'0';
   }
   return -1;
}

static int hex_digit(int ch) {
   if (ch>='0' && ch<='9') {
      return ch-'0';
   }
   switch (ch) {
    case 'a': case 'A': return 10;
    case 'b': case 'B': return 11;
    case 'c': case 'C': return 12;
    case 'd': case 'D': return 13;
    case 'e': case 'E': return 14;
    case 'f': case 'F': return 15;
    default: break;
   }
   return -1;
}

void directive_ascii_q(int linenum, const char *str) {
   bool inesc;
   size_t i;
   int val;

   inesc = false;
   for (i=0; str[i]; i++) {
      if (inesc) {
	 inesc = false;
	 val = octal_digit(str[i]);
	 if (val >= 0) {
	    /* \123 - consume up to 3 octal digits */
	    if (octal_digit(str[i+1])>=0) {
	       val = val*8 + octal_digit(str[i+1]);
	       i++;
	    }
	    if (octal_digit(str[i+1])>=0) {
	       val = val*8 + octal_digit(str[i+1]);
	       i++;
	    }
	 }
	 else if (str[i]=='x' || str[i]=='X') {
	    i++;
	    val = hex_digit(str[i]);
	    if (hex_digit(str[i+1])>=0) {
	       val = val*16 + hex_digit(str[i+1]);
	       i++;
	    }
	 }
	 else switch (str[i]) {
	  case 'a': val = '\a'; break;
	  case 'b': val = '\b'; break;
	  case 'f': val = '\f'; break;
	  case 'n': val = '\n'; break;
	  case 'r': val = '\r'; break;
	  case 't': val = '\t'; break;
	  case 'v': val = '\v'; break;
	  case '"': val = '"'; break;
	  case '\\': val = '\\'; break;
	  default:
	   file_err(linenum, "Invalid escape sequence \\%c in string", str[i]);
	   break;
	 }
	 addbyte(linenum, val);
      }
      else {
	 if (str[i]=='\\') {
	    inesc = true;
	 }
	 else {
	    addbyte(linenum, (unsigned char)str[i]);
	 }
      }
   }
}

void directive_asciz_q(int linenum, const char *str) {
   directive_ascii_q(linenum, str);
   addbyte(linenum, 0);
}

void directive_8byte_x(int linenum, struct expr *x) {
   uint64_t val;

   val = process_expr_qword(linenum, x, 0);
   add64(linenum, val);
}

void directive_word_x(int linenum, struct expr *x) {
   u_machword val;

   val = process_expr_word(linenum, x, 0);
   add32(linenum, val);
}

void directive_4byte_x(int linenum, struct expr *x) {
   directive_word_x(linenum, x);
}

void directive_hword_x(int linenum, struct expr *x) {
   u_machword val;
   
   val = process_expr_hword(linenum, x, 0);
   add16(linenum, val & 0xffff);
}

void directive_half_x(int linenum, struct expr *x) {
   directive_hword_x(linenum, x);
}

void directive_short_x(int linenum, struct expr *x) {
   directive_hword_x(linenum, x);
}

void directive_2byte_x(int linenum, struct expr *x) {
   directive_hword_x(linenum, x);
}

void directive_byte_x(int linenum, struct expr *x) {
   u_machlarge val;
   struct reloc *r;

   r = compile_expr(linenum, x, &val);
   if (r) {
      file_err(linenum, "Illegal symbolic reference with `.byte'");
   }

   if (!fits_s8(val) && !fits_u8(val)) {
      file_err(linenum, "Constant out of range for `.byte'");
   }
   addbyte(linenum, val & 0xff);
}

void directive_int_x(int linenum, struct expr *x) {
   directive_word_x(linenum, x);
}

void directive_long_x(int linenum, struct expr *x) {
   directive_word_x(linenum, x);
}

/*
 * XXX: these are sparc64-specific and should be moved to code generation
 * when we figure out how to do that.
 */
void directive_nword_x(int linenum, struct expr *x) {
   directive_8byte_x(linenum, x);
}
void directive_xword_x(int linenum, struct expr *x) {
   directive_8byte_x(linenum, x);
}
void directive_skip_n(int linenum, uint32_t n) {
   directive_space_n(linenum, n);
}

/*
 * XXX this is arm-specific and should be moved
 */
void directive_inst_x(int linenum, struct expr *x) {
   directive_4byte_x(linenum, x);
}
