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

#ifndef ELFBITS_H
#define ELFBITS_H

struct genfile; /* from genfile.h */


#include "elf.h"

void elf_flip_ehdr(Elf_Ehdr *eh);
void elf_flip_phdr(Elf_Phdr *ph);
void elf_flip_shdr(Elf_Shdr *sh);
void elf_flip_sym(Elf_Sym *st);
void elf_flip_rel(Elf_Rel *r);
void elf_flip_rela(Elf_Rela *r);

void elf_read_ehdr(struct genfile *g, off_t pos, Elf_Ehdr *eh);
void elf_read_phdr(struct genfile *g, off_t pos, Elf_Phdr *ph);
void elf_read_shdr(struct genfile *g, off_t pos, Elf_Shdr *sh);
void elf_read_sym(struct genfile *g, off_t pos, Elf_Sym *st);
void elf_read_rel(struct genfile *g, off_t pos, Elf_Rel *r);
void elf_read_rela(struct genfile *g, off_t pos, Elf_Rela *r);

void elf_write_ehdr(struct genfile *g, off_t pos, const Elf_Ehdr *eh);
void elf_write_phdr(struct genfile *g, off_t pos, const Elf_Phdr *ph);
void elf_write_shdr(struct genfile *g, off_t pos, const Elf_Shdr *sh);
void elf_write_sym(struct genfile *g, off_t pos, const Elf_Sym *st);
void elf_write_rel(struct genfile *g, off_t pos, const Elf_Rel *r);
void elf_write_rela(struct genfile *g, off_t pos, const Elf_Rela *r);

/* returns 0 on success, -1 on non-elf file; aborts on corrupt elf file */
int elf_check_ehdr(const char *filename, Elf_Ehdr *eh);


#endif /* ELFBITS_H */
