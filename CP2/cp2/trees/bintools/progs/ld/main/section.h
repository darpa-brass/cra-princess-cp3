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

struct gensect;
struct binfile;

#include "targetdefs.h"


unsigned section_add(const char *fromfile, struct gensect *gsx,
		     u_machword *offset);
void section_layout(u_machword textorg, u_machword dataorg, u_machword bssorg,
		    bool impure);

u_machword section_getbase(unsigned sectnum);

u_machword section_fetch8(unsigned sectnum, u_machword offset);
u_machword section_fetch16(unsigned sectnum, u_machword offset);
u_machword section_fetch32(unsigned sectnum, u_machword offset);
u_machword section_fetch64(unsigned sectnum, u_machword offset);
void section_store8(unsigned sectnum, u_machword offset, u_machword val);
void section_store16(unsigned sectnum, u_machword offset, u_machword val);
void section_store32(unsigned sectnum, u_machword offset, u_machword val);
void section_store64(unsigned sectnum, u_machword offset, u_machword val);

void section_emit(struct binfile *bf);

void section_setup(void);
void section_shutdown(void);

#endif /* SECTION_H */
