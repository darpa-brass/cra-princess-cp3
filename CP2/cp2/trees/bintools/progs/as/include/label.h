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

#ifndef LABEL_H
#define LABEL_H

#include "targetdefs.h"
struct binfile;
struct labelhazinfo;

struct label; // opaque

// the source file name is treated as a special-case label
void set_sourcefile(const char *s);


// ways to interpret scratch labels
enum scratchlabelhow {
   SCRATCHLABELS_REFER,			// scratch labels as references ("1f")
   SCRATCHLABELS_DEFINE,		// scratch labels as definitions ("1:")
};

// convert a symbol name to a label reference.
// usages as operands are different from usages on the left (like foo:)
// because of the way scratch labels are interpreted.
struct label *label_declare(int linenum, const char *sym, enum scratchlabelhow s);

// special case of label_declare for getting a "." label
struct label *label_declaredot(int linenum);

// define a label that actually exists within the assembled code.
// called right after label_declare. restates the line number so that the
// characteristic line number for the label is henceforth the definition
// rather than the first usage.
void label_define(struct label *l, int linenum, unsigned sectnum, u_machword offset);
// similar, but for the special case of a "common" symbol (which doesn't
// have a real section)
void label_definecommon(struct label *l, int linenum, u_machword size,
			u_machword align);
// like label_define but copies another label
void label_assign(struct label *l, int linenum, struct label *otherl);

// set the size of a symbol
void label_setsize(struct label *l, u_machword size);

// property adjustments
void label_setlocal(struct label *l);
void label_setglobl(struct label *l);
void label_setextern(struct label *l);
void label_markused(struct label *l);
void label_setcode(struct label *l);
void label_setdata(struct label *l);
void label_sethazinfo(struct label *l, struct labelhazinfo *lh);

// property inquiries
const char *label_getname(struct label *l);	// returns symbol text
int label_getline(struct label *l);		// returns characteristic line
int label_isdot(struct label *l);		// true if label is "."
int label_isscratch(struct label *l);		// true if a scratch label (like 1:)
int label_isdefined(struct label *l);		// true if label_define() called
int label_isextern(struct label *l);		// true if label_setextern() called
//int label_isglobl(struct label *l);		// true if label_setglobl() called
int label_isexplicitlylocal(struct label *l);
unsigned label_getsection(struct label *l);	// returns section (only if defined)
u_machword label_getoffset(struct label *l);	// returns offset (only if defined)
struct labelhazinfo *label_gethazinfo(struct label *l);

// final processing routines
void check_scratch_labels(void);
void discard_temp_labels(void);
void sort_labels(void);
unsigned label_getnumber(struct label *l);
void dump_labels(void);
void emit_labels(struct binfile *bf);

#endif /* LABEL_H */
