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
#include <stdio.h> // for snprintf
#include <string.h>
#include <assert.h>
#include "common.h"

#include "genfile.h"
#include "binfile.h"
#include "elfbits.h"
#include "elfstrtab.h"
#include "binfile_elf.h"


static bool pos_eq(off_t pos, Elf_Off elfpos) {
   /* Elf_Off is unsigned... sigh */
   return (intmax_t)pos == (intmax_t)(uintmax_t)elfpos;
}

////////////////////////////////////////////////////////////
// relocsection

struct relocsection {
   struct relarray rels;
   bool is_rela;

   unsigned target_section;
   unsigned source_section;
};
DECLARRAY(relocsection, static UNUSED inline);
DEFARRAY(relocsection, static UNUSED inline);

static struct relocsection *relocsection_create(void) {
   struct relocsection *rs;

   rs = domalloc(sizeof(*rs));
   relarray_init(&rs->rels);
   rs->is_rela = false;
   rs->target_section = rs->source_section = 0;
   return rs;
}

static void relocsection_destroy(struct relocsection *rs) {
   relarray_setsize(&rs->rels, 0);
   relarray_cleanup(&rs->rels);
   dofree(rs, sizeof(*rs));
}

////////////////////////////////////////////////////////////

struct binfile *binfile_new(const char *name, struct genfile *gf,
			    enum bftypes type) {
   struct binfile *bf;
   unsigned etype = ET_REL;
   Elf_Shdr sh;
   Elf_Sym st;

   switch (type) {
    case BFT_OBJ: etype = ET_REL; break;
    case BFT_PROG: etype = ET_EXEC; break;
    case BFT_LIB: etype = ET_DYN; break;
   }

   bf = binfile_create(name, gf);
   bf->ehdr_loaded = true;
   bf->sections_loaded = true;
   bf->syms_loaded = true;
   bf->rels_loaded = true;
   bf->shstrtab = elfstrtab_new();
   bf->symstrtab = elfstrtab_new();

   memset(&bf->ehdr, 0, sizeof(bf->ehdr));
   bf->ehdr.e_ident[EI_MAG0] = ELFMAG0;
   bf->ehdr.e_ident[EI_MAG1] = ELFMAG1;
   bf->ehdr.e_ident[EI_MAG2] = ELFMAG2;
   bf->ehdr.e_ident[EI_MAG3] = ELFMAG3;
   bf->ehdr.e_ident[EI_CLASS] = TARGET_ELF_CLASS;
   bf->ehdr.e_ident[EI_DATA] = TARGET_ELF_ENDIANNESS;
   bf->ehdr.e_ident[EI_VERSION] = EV_CURRENT;
   bf->ehdr.e_ident[EI_OSABI] = 0; // XXX
   bf->ehdr.e_ident[EI_ABIVERSION] = 0; // XXX
   bf->ehdr.e_type = etype;
   bf->ehdr.e_machine = TARGET_ELF_MACHINE;
   bf->ehdr.e_version = EV_CURRENT;
   bf->ehdr.e_entry = 0;
   bf->ehdr.e_phoff = 0;
   bf->ehdr.e_shoff = 0;
   bf->ehdr.e_flags = 0;
   bf->ehdr.e_ehsize = sizeof(Elf_Ehdr);
   bf->ehdr.e_phentsize = sizeof(Elf_Phdr);
   bf->ehdr.e_phnum = 0;
   bf->ehdr.e_shentsize = sizeof(Elf_Shdr);
   bf->ehdr.e_shnum = 0;
   bf->ehdr.e_shstrndx = 0;

   /* section 0 is reserved */
   sh.sh_name = 0;
   sh.sh_type = SHT_NULL;
   sh.sh_flags = 0;
   sh.sh_addr = 0;
   sh.sh_offset = 0;
   sh.sh_size = 0;
   sh.sh_link = 0;
   sh.sh_info = 0;
   sh.sh_addralign = 0;
   sh.sh_entsize = 0;
   shdrarray_add(&bf->sections, sh);
   ptrarray_add(&bf->sectiondata, NULL);

   /* symbol 0 is reserved */
   st.st_name = 0;
   st.st_value = 0;
   st.st_size = 0;
   st.st_info = 0;
   st.st_other = 0;
   st.st_shndx = 0;
   symarray_add(&bf->syms, st);

   return bf;
}

void binfile_setentry(struct binfile *bf, u_machword entry) {
   bf->ehdr.e_entry = entry;
}

/*
 * Insert the mapping ID -> TARGET into TABLE. Set any new unused
 * slots to FILL.
 */
static void setlookup(struct uintarray *table, unsigned id,
		      unsigned target, unsigned fill) {
   unsigned i, n;

   n = uintarray_num(table);
   if (id >= n) {
      uintarray_setsize(table, id + 1);
      for (i=n; i<id; i++) {
	 uintarray_set(table, i, fill);
      }
   }
   uintarray_set(table, id, target);
}

void binfile_addsect(struct binfile *bf, struct gensect *gsx, unsigned id) {
   Elf_Shdr sh;
   unsigned ourid;

   /* anonymous sections are not permitted */
   assert(gsx->gsx_name != NULL);
   assert(strlen(gsx->gsx_name) > 0);

   sh.sh_name = elfstrtab_add(bf->shstrtab, gsx->gsx_name);

   if (gsx->gsx_flags & GSXF_ISNOTE) {
      sh.sh_type = SHT_NOTE;
   }
   else if (gsx->gsx_flags & GSXF_ISBSS) {
      sh.sh_type = SHT_NOBITS;
   }
   else {
      sh.sh_type = SHT_PROGBITS;
   }

   sh.sh_flags = 0;
   if (gsx->gsx_flags & GSXF_LOADABLE) {
      sh.sh_flags |= SHF_ALLOC;
   }
   if (gsx->gsx_flags & GSXF_WRITEPERM) {
      sh.sh_flags |= SHF_WRITE;
   }
   if (gsx->gsx_flags & GSXF_EXECPERM) {
      sh.sh_flags |= SHF_EXECINSTR;
   }

   sh.sh_addr = gsx->gsx_vaddr;
   sh.sh_offset = 0; /* later */
   sh.sh_size = gsx->gsx_size;
   sh.sh_link = 0;
   sh.sh_info = 0;
   /* gsx_align is a log; elf alignments are not */
   sh.sh_addralign = 1UL << gsx->gsx_align;
   sh.sh_entsize = 0;

#ifndef TARGET_ELF_MACHINE
#error wut
#endif
#if TARGET_ELF_MACHINE == EM_MIPS
   if (!strcmp(gsx->gsx_name, ".reginfo") && sh.sh_type == SHT_PROGBITS) {
      sh.sh_type = SHT_MIPS_REGINFO;
      sh.sh_entsize = 24;
   }
#endif

   /* Add the section header and the data pointer. */
   shdrarray_addx(&bf->sections, sh, &ourid);
   ptrarray_add(&bf->sectiondata, gsx->gsx_data);

   /* Update the section number mapping. */
   setlookup(&bf->section_lookup, id, ourid, 0 /* ELF invalid section */);
}

void binfile_addsym(struct binfile *bf, struct gensym *gsm, unsigned id) {
   Elf_Sym st;
   unsigned ourid;
   unsigned bind, type;

   if (gsm->gsm_name != NULL) {
      assert(strlen(gsm->gsm_name) > 0);
      st.st_name = elfstrtab_add(bf->symstrtab, gsm->gsm_name);
   }
   else {
      st.st_name = 0;
   }

   if (gsm->gsm_section == GSX_COMMON) {
      /* this seems to be the right thing */
      /* note: elf alignments are bytes, ours are powers of two */
      st.st_value = 1UL << gsm->gsm_align;
   }
   else {
      st.st_value = gsm->gsm_value;
   }
   st.st_size = gsm->gsm_size;
   
   switch (gsm->gsm_type) {
    case GSMT_UNKNOWN: type = STT_NOTYPE; break;
    case GSMT_CODE: type = STT_FUNC; break;
    case GSMT_DATA: type = STT_OBJECT; break;
    case GSMT_FILENAME: type = STT_FILE; break;
    default: assert(0); type = STT_NOTYPE; break;
   }

   switch (gsm->gsm_flags) {
    case 0: bind = STB_LOCAL; break;
    case GSMF_GLOBL: bind = STB_GLOBAL; break;
    case GSMF_GLOBL|GSMF_WEAK: bind = STB_WEAK; break;
    default: assert(0); bind = STB_LOCAL; break;
   }

   st.st_info = ELF_ST_INFO(bind, type);
   st.st_other = 0;

   switch (gsm->gsm_section) {
    case GSX_INVALID: assert(0); break;
    case GSX_UNDEF: st.st_shndx = SHN_UNDEF; break;
    case GSX_COMMON: st.st_shndx = SHN_COMMON; break;
    case GSX_ABS: st.st_shndx = SHN_ABS; break;
    default:
     /* translate generic section number to ELF section number */
     st.st_shndx = uintarray_get(&bf->section_lookup, gsm->gsm_section);
     break;
   }

   /* add the symbol */
   symarray_addx(&bf->syms, st, &ourid);

   /* Update the symbol number mapping. */
   setlookup(&bf->symbol_lookup, id, ourid, 0 /* ELF invalid symbol */);
}

void binfile_setsource(struct binfile *bf, const char *filename) {
   Elf_Sym st;

   st.st_name = elfstrtab_add(bf->symstrtab, filename);
   st.st_value = 0;
   st.st_size = 0;
   st.st_info = ELF_ST_INFO(STB_LOCAL, STT_FILE);
   st.st_other = 0;
   st.st_shndx = SHN_ABS;
   symarray_add(&bf->syms, st);
}

void binfile_addreloc(struct binfile *bf, struct genreloc *gr) {
   Elf_Rela er;
   unsigned sym, code, sect;
   bool isrela;

   er.r_offset = gr->gr_offset;
   er.r_addend = gr->gr_addend;

   sym = uintarray_get(&bf->symbol_lookup, gr->gr_symbol);
   if (gr->gr_code < 0) {
      code = -gr->gr_code;
      isrela = false;
   }
   else {
      code = gr->gr_code;
      isrela = true;
   }

   /* relocations are not allowed to use the invalid symbol */
   assert(sym != 0);

   er.r_info = ELF_R_INFO(sym, code);

   /* Translate the generic section number to the ELF section number. */
   sect = uintarray_get(&bf->section_lookup, gr->gr_section);

   /* Insert the relocation and its metadata. */
   relarray_add(&bf->rels, er);
   uintarray_add(&bf->relsects, sect);
   boolarray_add(&bf->rels_are_rela, isrela);
}

////////////////////////////////////////////////////////////

static void make_symtab_section(struct binfile *bf, int strtabsectnum) {
   Elf_Shdr sh;

   sh.sh_name = elfstrtab_add(bf->shstrtab, ".symtab");
   sh.sh_type = SHT_SYMTAB;
   sh.sh_flags = 0;
   sh.sh_addr = 0;
   sh.sh_offset = 0; /* later */
   sh.sh_size = symarray_num(&bf->syms) * sizeof(Elf_Sym);
   sh.sh_link = strtabsectnum;
   sh.sh_info = 0; /* XXX wrong */
   sh.sh_addralign = 1UL << TARGET_MAXALIGN;
   sh.sh_entsize = sizeof(Elf_Sym);
   shdrarray_add(&bf->sections, sh);
   ptrarray_add(&bf->sectiondata, NULL);
}

static void make_strtab_section(struct binfile *bf, const char *name, 
				struct elfstrtab *est) {
   Elf_Shdr sh;

   /* note: est may == bf->shstrtab */
   sh.sh_name = elfstrtab_add(bf->shstrtab, name);
   sh.sh_type = SHT_STRTAB;
   sh.sh_flags = 0;
   sh.sh_addr = 0;
   sh.sh_offset = 0; /* later */
   sh.sh_size = elfstrtab_getsize(est);
   sh.sh_link = 0;
   sh.sh_info = 0;
   sh.sh_addralign = 1;
   sh.sh_entsize = 0;
   shdrarray_add(&bf->sections, sh);
   ptrarray_add(&bf->sectiondata, elfstrtab_getdata(est));
}

static void binfile_makecustomsections(struct binfile *bf,
				       struct relocsectionarray *reldata) {
   Elf_Shdr sh;
   int symtabsect, strtabsect;
   unsigned i, num;

   /*
    * First, convert the symbol table to a section.
    */

   symtabsect = shdrarray_num(&bf->sections);
   strtabsect = symtabsect+1;

   make_symtab_section(bf, strtabsect);

   /*
    * Now do the string table for the symbol table.
    */
   make_strtab_section(bf, ".strtab", bf->symstrtab);

   /*
    * Now do relocs. We need one relocation section for each distinct
    * section targeted by at least one relocation.
    */

   /* Make a table for relocations grouped by target section. */
   relocsectionarray_setsize(reldata, shdrarray_num(&bf->sections));
   num = relocsectionarray_num(reldata);
   for (i=0; i<num; i++) {
      relocsectionarray_set(reldata, i, NULL);
   }

   num = relarray_num(&bf->rels);
   for (i=0; i<num; i++) {
      Elf_Rela *era;
      struct relocsection *rs;
      unsigned target;

      target = uintarray_get(&bf->relsects, i);

      rs = relocsectionarray_get(reldata, target);
      if (!rs) {
	 rs = relocsection_create();
	 rs->is_rela = boolarray_get(&bf->rels_are_rela, i);
	 rs->target_section = target;
	 rs->source_section = -1; /* not known until below */
	 relocsectionarray_set(reldata, target, rs);
      }

      assert(rs->is_rela == boolarray_get(&bf->rels_are_rela, i));

      era = relarray_getptr(&bf->rels, i);
      relarray_add(&rs->rels, *era);
   }

   /*
    * Now for each such group of relocs, make an ELF section.
    */
   num = relocsectionarray_num(reldata);
   for (i=0; i<num; i++) {
      struct relocsection *rs;
      
      rs = relocsectionarray_get(reldata, i);
      if (rs) {
	 char tmp[256];
	 const char *name;

	 assert(rs->target_section == i);

	 name = elfstrtab_get(bf->shstrtab,
			      shdrarray_getptr(&bf->sections, i)->sh_name);
	 if (rs->is_rela) {
	    snprintf(tmp, sizeof(tmp), ".rela%s", name);
	    sh.sh_type = SHT_RELA;
	    sh.sh_size = relarray_num(&rs->rels) * sizeof(Elf_Rela);
	    sh.sh_entsize = sizeof(Elf_Rela);
	 }
	 else {
	    snprintf(tmp, sizeof(tmp), ".rel%s", name);
	    sh.sh_type = SHT_REL;
	    sh.sh_size = relarray_num(&rs->rels) * sizeof(Elf_Rel);
	    sh.sh_entsize = sizeof(Elf_Rel);
	 }

	 sh.sh_name = elfstrtab_add(bf->shstrtab, tmp);
	 sh.sh_flags = SHF_INFO_LINK;
	 sh.sh_addr = 0;
	 sh.sh_offset = 0; /* later */
	 sh.sh_link = symtabsect;
	 sh.sh_info = rs->target_section;
	 sh.sh_addralign = 1UL << TARGET_MAXALIGN;

	 shdrarray_addx(&bf->sections, sh, &rs->source_section);
	 ptrarray_add(&bf->sectiondata, NULL);
      }
   }

   /*
    * Finally, make a section for the section strtab.
    * Note: must not modify bf->shstrtab after this point.
    */

   make_strtab_section(bf, ".shstrtab", bf->shstrtab);
}

/*
 * Our symbols are section-relative, but the symbols in the
 * output should be absolute. This works because except in 
 * executables, the section start addresses are 0.
 */
static void update_syms(struct binfile *bf) {
   unsigned i, num;
   unsigned section;
   Elf_Sym *sym;
   Elf_Shdr *sh;

   num = symarray_num(&bf->syms);
   for (i=0; i<num; i++) {
      sym = symarray_getptr(&bf->syms, i);
      section = sym->st_shndx;
      if (section >= SHN_LORESERVE && section <= SHN_HIRESERVE) {
	 /* this includes absolute symbols, commons, etc. */
	 continue;
      }

      sh = shdrarray_getptr(&bf->sections, sym->st_shndx);
      sym->st_value += sh->sh_addr;
   }
}

static void convert(Elf_Phdr *ph, const Elf_Shdr *sh) {
   switch (sh->sh_type) {
    case SHT_PROGBITS:
    case SHT_NOBITS:
     ph->p_type = PT_LOAD;
     break;
    case SHT_NOTE:
     ph->p_type = PT_NOTE;
     break;
    case SHT_MIPS_REGINFO:
     ph->p_type = PT_MIPS_REGINFO;
     break;
    default:
     assert(0);
     break;
   }

   ph->p_offset = sh->sh_offset;
   ph->p_vaddr = sh->sh_addr;
   ph->p_paddr = ph->p_vaddr;
   ph->p_memsz = sh->sh_size;
   ph->p_filesz = sh->sh_type == SHT_NOBITS ? 0 : ph->p_memsz;
   ph->p_align = sh->sh_addralign;

   ph->p_flags = PF_R;
   if (sh->sh_flags & SHF_WRITE) {
      ph->p_flags |= PF_W;
   }
   if (sh->sh_flags & SHF_EXECINSTR) {
      ph->p_flags |= PF_X;
   }
}

static void binfile_setoffsets(struct binfile *bf) {
   Elf_Shdr *sh;
   unsigned numsections, i;
   off_t pos;

   /*
    * Set the offset fields in all the sections, assuming the file header
    * (ehdr + phdrs) is not going to exceed TARGET_PAGESIZE. (If it does,
    * we can fix it up later.)
    */

   numsections = shdrarray_num(&bf->sections);
   assert(numsections > 0);
   if (numsections == 1) {
      /* empty file? */
      return;
   }

   /*
    * This is gross. We should really arrange things so we know how
    * many phdrs we have, instead of having to do this hack.
    */
   if (bf->ehdr.e_type != ET_REL) {
      pos = shdrarray_getptr(&bf->sections, 1)->sh_addr % TARGET_PAGESIZE;
   }
   else {
      pos = sizeof(Elf_Ehdr);
   }

   for (i=1; i<numsections; i++) {
      sh = shdrarray_getptr(&bf->sections, i);
      if ((sh->sh_flags&SHF_ALLOC) != 0 && bf->ehdr.e_type != ET_REL) {
	 while (!pos_eq(pos % TARGET_PAGESIZE, sh->sh_addr % TARGET_PAGESIZE)){
	    pos++;
	 }
      }
      else {
	 while ((pos & sh->sh_addralign) != 0) {
	    pos++;
	 }
      }

      sh->sh_offset = pos;

      if (sh->sh_type != SHT_NOBITS) {
	 pos += sh->sh_size;
      }
   }

   while ((pos & ((1 << TARGET_MAXALIGN) - 1)) != 0) {
      pos++;
   }

   bf->ehdr.e_shoff = pos;

   update_syms(bf);
}

static void binfile_makephdrs(struct binfile *bf, struct phdrarray *phdrss) {
   Elf_Shdr *sh;
   Elf_Phdr ph, ph2;
   Elf_Phdr *php1, *php2;
   unsigned i, numsections, numphdrs;
   u_machword gap;

   /* first entry is reserved */
   ph.p_type = PT_NULL;
   ph.p_offset = 0;
   ph.p_vaddr = 0;
   ph.p_paddr = 0;
   ph.p_filesz = 0;
   ph.p_memsz = 0;
   ph.p_flags = 0;
   ph.p_align = 0;

   phdrarray_add(phdrss, ph);

   /* second entry is for the table itself */
   sh = shdrarray_getptr(&bf->sections, 0);
   ph.p_type = PT_PHDR;
   ph.p_offset = sizeof(Elf_Ehdr);
   ph.p_vaddr = (sh->sh_addr & (TARGET_PAGESIZE - 1)) + ph.p_offset;
   ph.p_paddr = ph.p_vaddr;
   ph.p_filesz = 0; /* update lower down */
   ph.p_memsz = 0;
   ph.p_flags = PF_R | PF_W;
   ph.p_align = 1UL << TARGET_MAXALIGN;

   phdrarray_add(phdrss, ph);

   /* subsequent entries are for the sections */

   assert(sh->sh_type == SHT_NULL);

   bool valid = false;
   numsections = shdrarray_num(&bf->sections);
   for (i=1; i<numsections; i++) {
      sh = shdrarray_getptr(&bf->sections, i);
      if ((sh->sh_flags & SHF_ALLOC) == 0) {
	 if (valid) {
	    phdrarray_add(phdrss, ph);
	    valid = false;
	 }
	 continue;
      }

      if (!valid) {
	 convert(&ph, sh);
	 valid = true;
	 //prog_warn("phdr %d type %u flags 0x%x", phdrs.num(), ph.p_type,
	 //	   ph.p_flags);
	 continue;
      }

      /*
       * ph is a valid phdr - see if this section can be glued onto it
       */
      convert(&ph2, sh);
      if (ph.p_type == ph2.p_type && ph.p_flags == ph2.p_flags) {
	 /* yes */

	 assert(ph2.p_vaddr >= (ph.p_vaddr + ph.p_memsz));
	 gap = ph2.p_vaddr - (ph.p_vaddr + ph.p_memsz);

	 ph.p_filesz += gap + ph2.p_filesz;
	 ph.p_memsz += gap + ph2.p_memsz;
	 continue;
      }

      /* no */
      phdrarray_add(phdrss, ph);
      ph = ph2;
      //prog_warn("phdr %d type %u flags 0x%x", phdrs.num(), ph.p_type,
      //	ph.p_flags);
   }
   if (valid) {
      phdrarray_add(phdrss, ph);
   }

   numphdrs = phdrarray_num(phdrss);
   u_machword tothdr = sizeof(Elf_Ehdr) + numphdrs*sizeof(Elf_Phdr);
   if (tothdr >= TARGET_PAGESIZE) {
      unsigned count = tothdr / TARGET_PAGESIZE;
      for (i=1; i<numsections; i++) {
	 sh = shdrarray_getptr(&bf->sections, i);
	 sh->sh_offset += count*TARGET_PAGESIZE;
      }
      for (i=2; i<numphdrs; i++) {
	 phdrarray_getptr(phdrss, i)->p_offset += count*TARGET_PAGESIZE;
      }
   }

   php1 = phdrarray_getptr(phdrss, 1);
   php2 = phdrarray_getptr(phdrss, 2);

   /* phdrs[1] describes the phdrs table */
   php1->p_filesz = php1->p_memsz = numphdrs*sizeof(Elf_Phdr);

   bf->ehdr.e_phoff = sizeof(Elf_Ehdr);

   /* If this fails, something broke badly above */
   sh = shdrarray_getptr(&bf->sections, 1);
   assert(php2->p_offset == sh->sh_offset);

   /*
    * Fail if we don't fit. Note that the test is >, not !=, because
    * alignment requirements might push php2->p_offset higher.
    */
   if (php1->p_offset + php1->p_filesz > php2->p_offset) {
      u_machword seen, expected;

      seen = php1->p_filesz / sizeof(Elf_Phdr);
      expected = (php2->p_offset - php1->p_offset) / sizeof(Elf_Phdr);
      prog_warn("Program header table size prediction failed");
      prog_warn("Expected %llu headers, got %llu",
		(unsigned long long) expected,
		(unsigned long long) seen);
      prog_warn("Headers go from 0x%llx to 0x%llx",
		(unsigned long long) php1->p_offset,
		(unsigned long long) (php1->p_offset + php1->p_filesz));
      prog_warn("Contents begin at 0x%llx",
		(unsigned long long) php2->p_offset);
      prog_err("This is a bug - please report what you did to trigger it");
   }
}

void binfile_write(struct binfile *bf) {
   struct phdrarray phdrs;
   struct relocsectionarray reldata;
   off_t pos;
   unsigned i, j, numphdrs, numsections, numsyms, numrels;
   struct relocsection *rs;
   Elf_Shdr *sh;
   void *data;

   phdrarray_init(&phdrs);
   relocsectionarray_init(&reldata);

   /* convert all symbols, relocs, etc. to sections */
   binfile_makecustomsections(bf, &reldata);

   /* place sections in file */
   binfile_setoffsets(bf);

   if (bf->ehdr.e_type != ET_REL) {
      /* make the program headers; this also places the sections in the file */
      binfile_makephdrs(bf, &phdrs);
   }

   /* the number of sections is now final */
   numphdrs = phdrarray_num(&phdrs);
   numsections = shdrarray_num(&bf->sections);

   bf->ehdr.e_shnum = numsections;
   bf->ehdr.e_phnum = numphdrs;
   bf->ehdr.e_shstrndx = bf->ehdr.e_shnum - 1;

   /*
    * Now we can actually write stuff.
    */

   pos = 0;

   /* executable header */
   elf_write_ehdr(bf->gf, pos, &bf->ehdr);
   pos += sizeof(Elf_Ehdr);

   /* program headers */
   if (phdrarray_num(&phdrs) > 0) {
      assert(pos_eq(pos, bf->ehdr.e_phoff));
   }
   for (i=0; i<numphdrs; i++) {
      elf_write_phdr(bf->gf, pos, phdrarray_getptr(&phdrs, i));
      pos += sizeof(Elf_Phdr);
   }

   /* section data */
   for (i=1; i<numsections; i++) {
      sh = shdrarray_getptr(&bf->sections, i);

      if ((sh->sh_flags & SHF_ALLOC) != 0 && bf->ehdr.e_type != ET_REL) {
	 while (!pos_eq(pos % TARGET_PAGESIZE, sh->sh_addr % TARGET_PAGESIZE)){
	    pos++;
	 }
      }
      else {
	 while ((pos & sh->sh_addralign) != 0) {
	    pos++;
	 }
      }

      assert(pos_eq(pos, sh->sh_offset));
      data = ptrarray_get(&bf->sectiondata, i);
      if (data) {
	 // XXX why should we have NOBITS and data?
	 if (sh->sh_type != SHT_NOBITS) {
	    assert(sh->sh_type == SHT_PROGBITS ||
		   sh->sh_type == SHT_NOTE ||
		   sh->sh_type == SHT_STRTAB ||
		   sh->sh_type == SHT_MIPS_REGINFO);
	    genfile_write(bf->gf, pos, data, sh->sh_size);
	    //prog_warn("writing: 0x%x at 0x%llx", sh->sh_size, pos);
	    pos += sh->sh_size;
	 }
      }
      else {
	 switch (sh->sh_type) {
	  case SHT_NULL:
	   break;
	  case SHT_NOBITS:
	   break;
	  case SHT_SYMTAB:
	   numsyms = symarray_num(&bf->syms);
	   assert(numsyms*sizeof(Elf_Sym) == sh->sh_size);
	   //prog_warn("writing: 0x%x at 0x%llx", sh->sh_size, pos);
	   for (j=0; j<numsyms; j++) {
	      elf_write_sym(bf->gf, pos, symarray_getptr(&bf->syms, j));
	      pos += sizeof(Elf_Sym);
	   }
	   break;
	  case SHT_REL:
	   {
	      Elf_Rel er;
	      Elf_Rela *era;

	     //prog_warn("writing: 0x%x at 0x%llx", sh->sh_size, pos);
	     rs = relocsectionarray_get(&reldata, sh->sh_info);
	     assert(rs != NULL);
	     numrels = relarray_num(&rs->rels);
	     assert(numrels * sizeof(Elf_Rel) == sh->sh_size);
	     for (j=0; j<numrels; j++) {
		era = relarray_getptr(&rs->rels, j);
		er.r_offset = era->r_offset;
		er.r_info = era->r_info;
		//assert(era->r_addend == 0); // XXX notyet (?)
		elf_write_rel(bf->gf, pos, &er);
		pos += sizeof(Elf_Rel);
	     }
	   }
	   break;
	  case SHT_RELA:
	   {
	     //prog_warn("writing: 0x%x at 0x%llx", sh->sh_size, pos);
	     rs = relocsectionarray_get(&reldata, sh->sh_info);
	     assert(rs != NULL);
	     numrels = relarray_num(&rs->rels);
	     assert(numrels * sizeof(Elf_Rela) == sh->sh_size);
	     for (j=0; j<numrels; j++) {
		elf_write_rela(bf->gf, pos, relarray_getptr(&rs->rels, j));
		pos += sizeof(Elf_Rela);
	     }
	   }
	   break;
	  default:
	   prog_err("Attempted to write section of improper/unsupported "
		    "type %d", sh->sh_type);
	   break;
	 }
      }
   }

   /* section headers */

   while ((pos & ((1UL<<TARGET_MAXALIGN)-1))!=0) {
      pos++;
   }

   assert(pos_eq (pos, bf->ehdr.e_shoff));
   for (i=0; i<numsections; i++) {
      elf_write_shdr(bf->gf, pos, shdrarray_getptr(&bf->sections, i));
      pos += sizeof(Elf_Shdr);
   }

   /* done! */

   for (i=0; i<relocsectionarray_num(&reldata); i++) {
      rs = relocsectionarray_get(&reldata, i);
      if (rs) {
	 relocsection_destroy(rs);
      }
   }

   phdrarray_setsize(&phdrs, 0);
   relocsectionarray_setsize(&reldata, 0);

   phdrarray_cleanup(&phdrs);
   relocsectionarray_cleanup(&reldata);
}
