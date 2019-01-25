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

#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "binfile.h"
#include "binfile_elf.h"

static unsigned numphdrs;
static unsigned lastflags;

void headersize_clear(void) {
   /*
    * Two program headers always appear: the null one (entry 0) and one
    * for the program header table.
    */
   numphdrs = 2;
   lastflags = 0;
}

void headersize_addsection(const char *name, unsigned flags) {
   (void)name;

   /* .data and .bss can go in the same phdr in ELF */
   flags &= ~GSXF_ISBSS;

   /* but the mips .reginfo rubbish has to have its own */

#ifndef TARGET_ELF_MACHINE
#error wut
#endif
#if TARGET_ELF_MACHINE == EM_MIPS
   if (!strcmp(name, ".reginfo")) {
      /* XXX this is entirely unprincipled */
      flags = 0xffffffff;
   }
#endif

   if (flags != lastflags) {
      lastflags = flags;
      numphdrs++;
   }
}

u_machword headersize_get(void) {
   return sizeof(Elf_Ehdr) + numphdrs*sizeof(Elf_Phdr);
}
