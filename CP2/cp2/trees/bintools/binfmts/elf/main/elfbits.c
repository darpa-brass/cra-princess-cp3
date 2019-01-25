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
#include <stdint.h>
#include "common.h"

#include "host/host.h"
#include "targetdefs.h"
#include "targetelfdefs.h"
#include "genfile.h"
#include "elf.h"
#include "elfbits.h"

#ifndef MY_BIG_ENDIAN
#error "MY_BIG_ENDIAN missing - include common.h"
#endif

#ifndef HOST_ENDIANNESS
#error "HOST_ENDIANNESS missing"
#endif

#if HOST_ENDIANNESS!=MY_BIG_ENDIAN && HOST_ENDIANNESS!=MY_LITTLE_ENDIAN
#error "HOST_ENDIANNESS has an invalid value"
#endif


#ifndef TARGET_ENDIANNESS
#error "TARGET_ENDIANNESS missing"
#endif

#if TARGET_ENDIANNESS!=MY_BIG_ENDIAN && TARGET_ENDIANNESS!=MY_LITTLE_ENDIAN
#error "TARGET_ENDIANNESS has an invalid value"
#endif


#ifndef TARGET_ELF_ENDIANNESS
#error "TARGET_ELF_ENDIANNESS missing"
#endif

#if TARGET_ELF_ENDIANNESS!=ELFDATA2MSB && TARGET_ELF_ENDIANNESS!=ELFDATA2LSB
#error "TARGET_ELF_ENDIANNESS has an invalid value"
#endif


#if TARGET_ENDIANNESS==MY_BIG_ENDIAN && TARGET_ELF_ENDIANNESS!=ELFDATA2MSB
#error "TARGET_ENDIANNESS and TARGET_ELF_ENDIANNESS mismatched"
#endif

#if TARGET_ENDIANNESS==MY_LITTLE_ENDIAN && TARGET_ELF_ENDIANNESS!=ELFDATA2LSB
#error "TARGET_ENDIANNESS and TARGET_ELF_ENDIANNESS mismatched"
#endif


#ifndef TARGET_ELF_CLASS
#error "TARGET_ELF_CLASS missing"
#endif


#if TARGET_ELF_CLASS!=ELFCLASS32 && TARGET_ELF_CLASS!=ELFCLASS64
#error "TARGET_ELF_CLASS has an invalid value"
#endif


#if TARGET_ENDIANNESS != HOST_ENDIANNESS
static void flip16(uint16_t *x) {
   uint16_t y = *x;
   *x = ((y&0xff) << 8) | ((y>>8) & 0xff);
}
static void flip32(uint32_t *x) {
   uint32_t y = *x;
   *x = ((y&0xff)<<24) | ((y&0xff00)<<8) | ((y>>8)&0xff00) | ((y>>24)&0xff);
}
static UNUSED void flip32s(int32_t *x) {
   uint32_t y = *x;
   flip32(&y);
   *x = y;
}

#if TARGET_ELF_CLASS==ELFCLASS64
static void flip64(uint64_t *x) {
   uint32_t left, right;

   left = (*x) & 0xffffffff;
   right = (*x) >> 32;
   flip32(&left);
   flip32(&right);
   *x = ((uint64_t)left << 32) | right;
}
static void flip64s(int64_t *x) {
   uint64_t y = *x;
   flip64(&y);
   *x = y;
}
#endif

#define FLIP16(k) (flip16(&(k)))
#define FLIP32(k) (flip32(&(k)))
#define FLIP64(k) (flip64(&(k)))
#define FLIP32s(k) (flip32s(&(k)))
#define FLIP64s(k) (flip64s(&(k)))

#else
#define FLIP16(k)
#define FLIP32(k)
#define FLIP64(k)
#define FLIP32s(k)
#define FLIP64s(k)
#endif

#if TARGET_ELF_CLASS==ELFCLASS32
#define FLIPADDR FLIP32
#define FLIPOFF  FLIP32
#define FLIPADDRs FLIP32s
#else
#define FLIPADDR FLIP64
#define FLIPOFF  FLIP64
#define FLIPADDRs FLIP64s
#endif


void elf_flip_ehdr(Elf_Ehdr *eh) {
   (void)eh;
   FLIP16(eh->e_type);
   FLIP16(eh->e_machine);
   FLIP32(eh->e_version);
   FLIPADDR(eh->e_entry);
   FLIPOFF(eh->e_phoff);
   FLIPOFF(eh->e_shoff);
   FLIP32(eh->e_flags);
   FLIP16(eh->e_ehsize);
   FLIP16(eh->e_phentsize);
   FLIP16(eh->e_phnum);
   FLIP16(eh->e_shentsize);
   FLIP16(eh->e_shnum);
   FLIP16(eh->e_shstrndx);
}

void elf_flip_phdr(Elf_Phdr *ph) {
   (void)ph;
   FLIP32(ph->p_type);
   FLIPOFF(ph->p_offset);
   FLIPADDR(ph->p_vaddr);
   FLIPADDR(ph->p_paddr);
   FLIPADDR(ph->p_filesz);
   FLIPADDR(ph->p_memsz);
   FLIP32(ph->p_flags);
   FLIPADDR(ph->p_align);
}

void elf_flip_shdr(Elf_Shdr *sh) {
   (void)sh;
   FLIP32(sh->sh_name);
   FLIP32(sh->sh_type);
   FLIPADDR(sh->sh_flags);
   FLIPADDR(sh->sh_addr);
   FLIPOFF(sh->sh_offset);
   FLIPADDR(sh->sh_size);
   FLIP32(sh->sh_link);
   FLIP32(sh->sh_info);
   FLIPADDR(sh->sh_addralign);
   FLIPADDR(sh->sh_entsize);
}

void elf_flip_sym(Elf_Sym *st) {
   (void)st;
   FLIP32(st->st_name);
   FLIPADDR(st->st_value);
   FLIPADDR(st->st_size);
   FLIP16(st->st_shndx);
}

void elf_flip_rel(Elf_Rel *r) {
   (void)r;
   FLIPADDR(r->r_offset);
   FLIPADDR(r->r_info);
}

void elf_flip_rela(Elf_Rela *r) {
   (void)r;
   FLIPADDR(r->r_offset);
   FLIPADDR(r->r_info);
   FLIPADDRs(r->r_addend);
}

#define ELFIO(what, type) \
   void elf_read_##what(struct genfile *g, off_t pos, type *obj) {      \
      genfile_read(g, pos, obj, sizeof(type));                          \
      elf_flip_##what(obj);                                             \
   }                                                                    \
   void elf_write_##what(struct genfile *g, off_t pos, const type *obj) {\
      type obj2;                                                        \
									\
      obj2 = *obj;                                                      \
      elf_flip_##what(&obj2);                                           \
      genfile_write(g, pos, &obj2, sizeof(type));                       \
   }
 
ELFIO(ehdr, Elf_Ehdr);
ELFIO(phdr, Elf_Phdr);
ELFIO(shdr, Elf_Shdr);
ELFIO(sym, Elf_Sym);
ELFIO(rel, Elf_Rel);
ELFIO(rela, Elf_Rela);

int elf_check_ehdr(const char *filename, Elf_Ehdr *eh) {
   if (eh->e_ident[EI_MAG0] != ELFMAG0 ||
       eh->e_ident[EI_MAG1] != ELFMAG1 ||
       eh->e_ident[EI_MAG2] != ELFMAG2 ||
       eh->e_ident[EI_MAG3] != ELFMAG3) {
      /* not ELF file */
      return -1;
   }
   if (eh->e_ident[EI_CLASS] != TARGET_ELF_CLASS) {
      prog_err("%s: ELF file has wrong word size", filename);
   }
   if (eh->e_ident[EI_DATA] != TARGET_ELF_ENDIANNESS) {
      prog_err("%s: ELF file has wrong endianness", filename);
   }
   if (eh->e_ident[EI_VERSION] != EV_CURRENT) {
      prog_err("%s: ELF file is wrong version", filename);
   }
   if (eh->e_machine != TARGET_ELF_MACHINE) {
      prog_err("%s: ELF file is for wrong target", filename);
   }
   switch (eh->e_type) {
    case ET_REL:  /* .o file */
    case ET_EXEC: /* executable */
    case ET_DYN:  /* .so file */
    case ET_CORE: /* core dump */
     break;
    default:
     prog_err("%s: ELF file has unknown type %u", filename, eh->e_type);
   }

   /* XXX: check EI_OSABI and EI_ABIVERSION? */

   if (eh->e_version != eh->e_ident[EI_VERSION]) {
      prog_err("%s: Corrupt ELF file (multiple ELF versions)", filename);
   }

   if (eh->e_shstrndx >= eh->e_shnum || eh->e_shstrndx==0) {
      prog_err("%s: Corrupt ELF file (bad/missing section name table)",
	       filename);
   }

   if (eh->e_phentsize < sizeof(Elf_Phdr) && eh->e_phnum > 0) {
      prog_err("%s: Corrupt ELF file: Invalid program header size", filename);
   }
   if (eh->e_shentsize < sizeof(Elf_Shdr) && eh->e_shnum > 0) {
      prog_err("%s: Corrupt ELF file: Invalid section header size", filename);
   }

   return 0;
}
