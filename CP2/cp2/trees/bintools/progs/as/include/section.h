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

#ifndef SECTION_H
#define SECTION_H

#include "targetdefs.h"
struct binfile; /* from binfile.h */


#define UNDEFINED_SECTION ((unsigned)-2)	/* matches GSX_UNDEF */

unsigned getsection(const char *name, bool haveflags,
		    bool insns, bool readonly, bool isbss);
const char *section_name(unsigned snum);

/* this updates the section alignment requirement */
void require_section_alignment(unsigned snum, u_machword alignment);
/* and this also pads the current section contents to that alignment */
void align_section(unsigned snum, u_machword alignment);

void dump_sections(void);
void emit_sections(struct binfile *bf);

void section_addbyte(unsigned snum, int linenum, u_machbyte a);
int section_isaligned(unsigned snum, u_machword alignment);
bool section_isbss(unsigned snum);
bool section_iscode(unsigned snum);
u_machword section_getsize(unsigned snum);

u_machword section_get64(unsigned snum, u_machword offset);
u_machword section_get32(unsigned snum, u_machword offset);
u_machword section_get16(unsigned snum, u_machword offset);
u_machword section_get8(unsigned snum, u_machword offset);
void section_put64(unsigned snum, u_machword offset, u_machword val);
void section_put32(unsigned snum, u_machword offset, u_machword val);
void section_put16(unsigned snum, u_machword offset, u_machword val);
void section_put8(unsigned snum, u_machword offset, u_machword val);

void section_setup(void);
void section_shutdown(void);


#endif /* SECTION_H */
