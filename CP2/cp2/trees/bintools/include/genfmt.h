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

#ifndef GENFMT_H
#define GENFMT_H

#include "targetdefs.h"


/*
 * Generic section
 */
struct gensect {
   char *gsx_name;
   u_machword gsx_vaddr;
   u_machword gsx_size;
   u_machword gsx_align;
   unsigned gsx_flags;
   void *gsx_data;
};

/* flags for gsx_flags */
/*			 0x01 */
#define GSXF_ISNOTE      0x02
#define GSXF_ISBSS       0x04
#define GSXF_LOADABLE    0x08
#define GSXF_EXECPERM    0x10
#define GSXF_WRITEPERM   0x20
#define GSXF_READPERM    0x40


/*
 * Generic symbol
 */
struct gensym {
   char *gsm_name;		/* can be null */
   u_machword gsm_value;
   u_machword gsm_size;
   u_machword gsm_align;	/* GSX_COMMON only */
   unsigned gsm_section;	/* 0..n-1 or one of the special values below */
   int gsm_type;
   unsigned gsm_flags;
};

/* special sections for gsm_section (and gr_section) */
#define GSX_INVALID ((unsigned)(-1))
#define GSX_UNDEF   ((unsigned)(-2))
#define GSX_COMMON  ((unsigned)(-3))
#define GSX_ABS     ((unsigned)(-4))

/* types for gsm_type */
#define GSMT_UNKNOWN	'?'
#define GSMT_CODE	't'
#define GSMT_DATA	'd'
#define GSMT_FILENAME	'f'

/* flags for gsm_flags */
#define GSMF_GLOBL	0x01
#define GSMF_WEAK	0x02


/*
 * Generic relocation
 */
struct genreloc {
   u_machword gr_addend;		/* additional value for operation */
   u_machword gr_offset;		/* offset into section */
   unsigned gr_section;			/* section for operation activity */
   unsigned gr_symbol;			/* symbol to use for operation */
   int gr_code;				/* operation to perform */
};

/* special symbol for gr_symbol */
#define GSM_INVALID ((unsigned)-1)

/*
 * Functions in genfmt.c
 */
bool gensect_isspecialnum(unsigned sectnum);
struct gensect *gensect_create(const char *name);
void gensect_destroy(struct gensect *);

struct gensym *gensym_create(const char *name);
void gensym_destroy(struct gensym *);

struct genreloc *genreloc_create(void);
void genreloc_destroy(struct genreloc *);


#endif /* GENFMT_H */
