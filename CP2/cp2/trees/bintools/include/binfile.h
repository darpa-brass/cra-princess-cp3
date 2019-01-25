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

#ifndef BINFILE_H
#define BINFILE_H

#include "targetdefs.h"
#include "genfmt.h"
struct genfile; /* from genfile.h */


struct binfile; // opaque

/*
 * File types for binfile_new and binfile_gettype
 */
enum bftypes {
	BFT_OBJ = 1,	/* .o file */
	BFT_LIB = 2,	/* .so file */
	BFT_PROG = 3,	/* executable */
};

/*
 * header size computation
 */

void headersize_clear(void);
void headersize_addsection(const char *name, unsigned flags);
u_machword headersize_get(void);

/*
 * binfile
 */

struct binfile *binfile_bind(const char *name, struct genfile *gf);
struct binfile *binfile_new(const char *name, struct genfile *gf,
			    enum bftypes type);
void binfile_destroy(struct binfile *bf);

const char *binfile_getname(struct binfile *bf);
enum bftypes binfile_gettype(struct binfile *bf);

/*
 * Sections
 */
unsigned binfile_numsections(struct binfile *bf);
struct gensect *binfile_getsection(struct binfile *bf, unsigned which,
				   bool loaddata);

/*
 * Symbols
 */
unsigned binfile_numsymbols(struct binfile *bf);
struct gensym *binfile_getsymbol(struct binfile *bf, unsigned which);
const char *binfile_getprovidedsymbol(struct binfile *bf, unsigned which);

/*
 * Relocs
 */
unsigned binfile_numrelocs(struct binfile *bf);
struct genreloc *binfile_getreloc(struct binfile *bf, unsigned which);

/*
 * Output
 */
void binfile_addsect(struct binfile *bf, struct gensect *gsx, unsigned id);
void binfile_addsym(struct binfile *bf, struct gensym *gsm, unsigned id);
void binfile_addreloc(struct binfile *bf, struct genreloc *gr);
void binfile_setentry(struct binfile *bf, u_machword addr);
void binfile_setsource(struct binfile *bf, const char *filename);
void binfile_write(struct binfile *bf);


#endif /* BINFILE_H */
