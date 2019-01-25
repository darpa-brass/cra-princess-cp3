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

#ifndef TARGET_MIPS_H
#define TARGET_MIPS_H

/*
 * Basic target definitions for mips
 */

typedef int8_t    s_machbyte;
typedef uint8_t  u_machbyte;
typedef int32_t   s_machword;
typedef uint32_t u_machword;
typedef int64_t   s_machlarge;
typedef uint64_t u_machlarge;

#define AS_ALIGNS_BY_LOGVALUE
#define AS_COMM_ALIGNS_BY_VALUE

#define TEMP_LABEL_PREFIX  "$L"
#define ENTRY_SYM          "__start"

#define DEFAULT_TEXTORG   0x00400000
#define DEFAULT_DATAORG   0x0
#define DEFAULT_BSSORG    0x0

#define TARGET_MAXALIGN   2	/* maximum required alignment - log2 */
#define TARGET_PAGESIZE   4096

#define TARGET_TEXT_ALIGNMENT	4  /* default alignment for .text - log2 */
#define TARGET_RDATA_ALIGNMENT	4  /* .rdata */
#define TARGET_DATA_ALIGNMENT	4  /* .data */
#define TARGET_BSS_ALIGNMENT	4  /* .bss */

/* XXX ultimately need to do both endiannesses for mips */
#define TARGET_ENDIANNESS   MY_BIG_ENDIAN

#define TARGET_INTEGERS     MY_TWOS_COMPLEMENT

/* this should be true for ELF (maybe also legacy COFF) output */
#define MIPS_ISSUE_REGINFO

#endif /* TARGET_MIPS_H */
