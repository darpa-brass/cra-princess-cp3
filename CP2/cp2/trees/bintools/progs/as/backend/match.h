/*
 * Copyright (c) 2002, 2016, 2017
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

#ifndef MATCH_H
#define MATCH_H

struct operand; /* from targetoper.h */
struct operandarray;

/*
 * Operand match function
 */
typedef bool (*opmatchfn)(struct operand *);

/*
 * Structures used by generated code in targetmatch.c
 */

/* one operand signature for a given opcode */
struct insnsig {
   const opmatchfn *sigmatchers; /* matching function for each operand */
   unsigned siglen;		/* number of elements in signature */
   int multisig;		/* if true, allow multiple operand sets */
   void (*call_emit)(int, struct operandarray *);
};

/* one opcode */
struct insnmatch {
   const char *opcode;		/* opcode string */
   const struct insnsig *sigs;	/* signatures that exist */
   unsigned numsigs;
};

/* MD data in tmatch.c */
extern const struct insnmatch opcodes[];
extern const unsigned numopcodes;


#endif /* MATCH_H */
