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

#ifndef MIPS_TRELOC_H
#define MIPS_TRELOC_H


/*
 * MD modifiers that can appear in a relocation.
 * (must include RELOC_MOD_NONE)
 */
enum reloc_modifier {
   RELOC_MOD_NONE,
   RELOC_MOD_LO,		/* %lo() */
   RELOC_MOD_HI,		/* %hi() */
   RELOC_MOD_BRANCHOFFSET,	/* x >> 2 for branch instruction */
};

/*
 * Fields a relocation can be applied to.
 */
enum reloc_field {
   RELOC_FIELD_32,	/* 32-bit field at given byte offset */
   RELOC_FIELD_U16,	/* unsigned 16-bit field at given byte offset */
   RELOC_FIELD_S16,	/* signed 16-bit field at given byte offset */
   RELOC_FIELD_ANY16,	/* any-sign 16-bit field at given byte offset */
   RELOC_FIELD_BRANCH16,/* 16-bit branch offset at given byte offset */
			/* (18-bit 4-byte aligned value shifted right by 2) */
   RELOC_FIELD_JUMP26,	/* 26-bit jump target in 32-bit word at given offset */
			/* (28-bit 4-byte aligned value shifted right by 2) */
};

/* a value to initialize fresh reloc structs with */
#define RELOC_FIELD_DEFAULT	RELOC_FIELD_32


#endif /* MIPS_TRELOC_H */
