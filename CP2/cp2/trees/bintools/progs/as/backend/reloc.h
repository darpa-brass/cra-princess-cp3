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

#ifndef RELOC_H
#define RELOC_H

#include "targetdefs.h"
#include "targetreloc.h"
struct binfile; /* from binfile.h */


/*
 * Binary-format-independent relocations. This includes relocations
 * that the binary format can't represent but that we can resolve
 * after assembling, like differences between local symbols.
 *
 * There are four parts to this:
 *    - an expression, currently either a symbol or the difference of
 *      two symbols;
 *    - a constant addend, maybe 0;
 *    - a modifier, maybe null;
 *    - a machine-dependent field code that indicates exactly what
 *      bits to operate on at the given offset. (This also encodes the
 *      field size.)
 *
 * The computed expression is always mod((sym1 - sym2) + addend), and
 * the results are placed in the selected field.
 *
 * In addition we store the line number of the input file (in case the
 * relocation is unrepresentable in the output), the offset and
 * section number the offset applies in, and also the current section
 * offset when the relocation was entered. (This last is the value to
 * use for the "." symbol.)
 *
 * The modifiers are machine-dependent but typical ones are things
 * like "lo" and "hi", as well as "got" and "plt".
 *
 * XXX: can the section for r_offset and r_curpos ever be different?
 * (Probably not.)
 */

struct label;
struct expr;

struct reloc {
   int r_linenum;		/* characteristic line number */
   unsigned r_sectnum;		/* section to edit */
   u_machword r_offset;		/* place to edit */
   u_machword r_curpos;		/* current section offset when entered */

   /* Expression: either sym1 (if sym2 is null) or sym1 - sym2 (otherwise) */
   struct label *r_sym1;
   struct label *r_sym2;

   /* addend */
   u_machword r_addend;

   /* modifier (enumeration is MD) */
   enum reloc_modifier r_modifier;

   /* field code (enumeration is MD) */
   enum reloc_field r_field;
};

/*
 * MI functions in reloc.c
 */
struct reloc *reloc_create(int linenum, enum reloc_modifier,
			   struct label *s1, struct label *s2,
			   u_machword addend);
void reloc_destroy(struct reloc *);

void reloc_add(struct reloc *r, unsigned sect);

void dump_relocs(void);

void process_relocs(void);
void emit_relocs(struct binfile *bf);


/*
 * MI function in compile.c
 *
 * Note: compile_expr sets:
 *    r_linenum
 *    r_sym1/r_sym2
 *    r_addend
 *    r_modifier
 *
 * The caller should then set r_sectnum/r_offset/r_curpos and also r_field.
 */
struct reloc *compile_expr(int linenum, struct expr *x, u_machlarge *extraval);

/*
 * MD (target-specific) functions in targetreloc.c
 */
enum reloc_modifier target_reloc_getmodifier(const char *name);
const char *target_reloc_modifier_name(enum reloc_modifier mod);
const char *target_reloc_field_name(enum reloc_field f);
u_machword target_modifier_apply(int linenum, enum reloc_modifier mod,
				 u_machword value);
void target_reloc_apply(struct reloc *r, u_machword value);
void target_reloc_preoutput(struct reloc *r);
int target_reloc_code(struct reloc *r);
/* XXX change the name of these to have "target" in it */
/* XXX also let's have a systematic notion of names for various sizes... */
u_machword process_expr_qword(int linenum, struct expr *x, unsigned offset);
u_machword process_expr_word(int linenum, struct expr *x, unsigned offset);
u_machword process_expr_hword(int linenum, struct expr *x, unsigned offset);


#endif /* RELOC_H */
