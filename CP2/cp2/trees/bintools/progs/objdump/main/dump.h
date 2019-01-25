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

#ifndef DUMP_H
#define DUMP_H

/*
 * Info requested 
 */
#define INFO_HEADERS_AR		0x001
#define INFO_HEADERS_O		0x002
#define INFO_HEADERS_BF		0x004
#define INFO_HEADERS_SECTION	0x008
#define INFO_CONTENTS_CODE	0x010
#define INFO_CONTENTS_DATA	0x020
#define INFO_DEBUG		0x040
#define INFO_DEBUG_RAW		0x080
#define INFO_SYMS		0x100
#define INFO_DYNSYMS		0x200
#define INFO_RELOCS		0x400
#define INFO_DYNRELOCS		0x800

#define INFO_HEADERS_ALL	0x00f
#define INFO_CONTENTS_ALL	0x030

/*
 * Presentation flags
 */

#define PR_DIS_CODE		0x01
#define PR_DIS_DATA		0x02
#define PR_DIS_ADDSOURCE	0x04
#define PR_DIS_LINENUMBERS	0x08
#define PR_DIS_ZEROS		0x10
#define PR_DIS_RAWINSN		0x20
#define PR_DIS_PREFIXADDRS	0x40
#define PR_WIDE			0x80
#define PR_FILESTARTCTX		0x100

#define PR_DIS_ALL		0x03
#define PR_DIS_SOURCE		(PR_DIS_CODE|PR_DIS_ADDSOURCE)


void dump_set_info(unsigned infoflags);
void dump_set_presentation(unsigned prflags);

void dump(const char *file);

#endif /* DUMP_H */
