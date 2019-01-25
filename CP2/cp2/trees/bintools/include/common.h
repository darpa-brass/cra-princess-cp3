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

#ifndef COMMON_H
#define COMMON_H


/*
 * Declaration and annotation tools (many compiler-sensitive)
 */

#if defined(__clang__) || defined(__GNUC__)
#define PF(a,b) __attribute__((__format__(__printf__, a, b)))
#define NORETURN __attribute__((__noreturn__))
#define UNUSED __attribute__((__unused__))
#if defined(__clang__) || defined(__GNUC_STDC_INLINE__)
#define INLINE inline
#else
#define INLINE extern inline
#endif

#else /* some other compiler */
#define PF(a,b)
#define NORETURN
#defune UNUSED
#define INLINE inline
#endif

#define ARRAYCOUNT(a) (sizeof(a) / sizeof((a)[0]))
#define COMPILE_ASSERT(x) ((void)sizeof(struct { unsigned : ((x) ? 1 : -1); }))


/*
 * Global constants
 */

#define MY_BIG_ENDIAN     4321
#define MY_LITTLE_ENDIAN  1234

#define MY_TWOS_COMPLEMENT	2
#define MY_ONES_COMPLEMENT	1
#define MY_SIGN_MAGNITUDE	(-1)

/*
 * Base functions in common.c
 */

void prog_setname(const char *pn);
NORETURN PF(1,2) void prog_err(const char *fmt, ...);
PF(1,2) void prog_warn(const char *fmt, ...);

void file_setname(const char *fn);
void file_clearname(void);
NORETURN PF(2,3) void file_err(int line, const char *fmt, ...);
PF(2,3) void file_warn(int line, const char *fmt, ...);


#endif /* COMMON_H */
