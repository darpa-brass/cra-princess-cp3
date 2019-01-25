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

#ifndef BACKEND_H
#define BACKEND_H

#include "array.h"

struct operand; /* from targetoper.h */
/* XXX: give this proper inlining */
DECLARRAY(operand, static UNUSED inline);
DEFARRAY(operand, static UNUSED inline);

/*
 * These are in match.c.
 */
const struct insnsig *backend_find_opcode(const char *opcode,
					  unsigned *numsigs_ret);
/* Note: the operands in the array are consumed. */
void backend_dispatch_opcode(int line, const char *opcode, const struct insnsig *sigs,
			     unsigned numsigs, struct operandarray *operands);

/* These are currently in labelops.c. */
void backend_add_label(int line, const char *label);
void backend_add_label_with_offfset(int line, const char *label, u_machword offset);
void backend_assign_label(int line, const char *label, const char *otherlabel);


/*
 * These are in modes.c.
 */
void backend_setup(void);
void backend_shutdown(void);


#endif /* BACKEND_H */
