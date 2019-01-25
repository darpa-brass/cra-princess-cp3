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
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "common.h"

#include "arlib.h"
#include "genfile.h"
#include "binfile.h"
#include "genfmt.h"
#include "targetdefs.h"

#include "dump.h"
#include "dumptbl.h"
#include "disasm.h"

static unsigned infoflags, prflags;

void dump_set_info(unsigned ifl) {
   infoflags = ifl;
}

void dump_set_presentation(unsigned pfl) {
   prflags = pfl;
}

////////////////////////////////////////////////////////////

static void disassemble_section(struct binfile *bf, struct gensect *gsx,
				unsigned sectindex) {
   struct disasm *ds;
   struct gensym *gsm;
   u_machword i;

   printf("Disassembly of section %s:\n", gsx->gsx_name);

   ds = ds_create(bf, gsx, sectindex);
   while (!ds_done(ds)) {
      char buf[4096];
      u_machword where, where2, size;

      where = ds_getvaddr(ds);
      ds_getinsn(ds, buf, sizeof(buf));
      where2 = ds_getvaddr(ds);
      size = where2-where;
      assert(size>0);

      gsm = get_sym_byaddr(where);
      if (gsm != NULL) {
	 printf("%08llx <%s>:\n", (unsigned long long) where, gsm->gsm_name);
      }
      printf("%4llx:   ", (unsigned long long) where);
      for (i=0; i<size; i++) {
	 unsigned ix;
	 uint8_t x;

	 ix = where - gsx->gsx_vaddr;
	 if (ix+i >= gsx->gsx_size) {
	    x = 0;
	 }
	 else {
	    x = ((uint8_t *)gsx->gsx_data)[ix+i];
	 }
	 printf("%02x ", x);
      }
      for (i=size; i<8; i++) {
	 printf("   ");
      }
      printf("%s\n", buf);
   }
   ds_destroy(ds);
}

static void hexdump_section(struct gensect *gsx) {
   uint8_t *data;
   u_machword count, vaddr;
   unsigned j;

   printf("Contents of section %s:\n", gsx->gsx_name);
   data = (uint8_t *)gsx->gsx_data;
   vaddr = gsx->gsx_vaddr;

   for (count=0; count<gsx->gsx_size; count+=16) {
      printf(" %04jx ", (uintmax_t)(vaddr + count));
      for (j=0; j<16; j++) {
	 if (count+j < gsx->gsx_size) {
	    printf("%02x", data[count+j]);
	 }
	 else {
	    printf("  ");
	 }
	 if (j%4==0) {
	    printf(" ");
	 }
      }
      printf(" ");
      for (j=0; j<16 && count+j < gsx->gsx_size; j++) {
	 uint8_t ch = data[count+j];
	 printf("%c", ch>=32 && ch<127 ? ch : '.');
      }
      printf("\n");
   }
}

static void dump_contents(struct binfile *bf) {
   unsigned nsect;
   struct gensect *gs;
   bool iscode;
   unsigned i;

   nsect = binfile_numsections(bf);
   for (i=0; i<nsect; i++) {
      gs = binfile_getsection(bf, i, 1);
      if (gs==NULL) {
	 /* internal/private section */
	 continue;
      }

      iscode = (gs->gsx_flags & GSXF_EXECPERM)!=0;
      if (iscode && (infoflags & INFO_CONTENTS_CODE)) {
	 if (prflags & PR_DIS_CODE) {
	    disassemble_section(bf, gs, i);
	 }
	 else {
	    hexdump_section(gs);
	 }
      }
      else if (!iscode && (infoflags & INFO_CONTENTS_DATA)) {
	 if (prflags & PR_DIS_DATA) {
	    disassemble_section(bf, gs, i);
	 }
	 else {
	    hexdump_section(gs);
	 }
      }
   }
}

static void dump_binfile(const char *filename, struct binfile *bf) {
   const char *format = "someformat"; // XXX

   dumptable_init(bf);

   printf("%s:     file format %s\n", filename, format);

   if (infoflags & INFO_HEADERS_O) {
      // XXX
      prog_warn("No support for file headers");
   }
   if (infoflags & INFO_HEADERS_BF) {
      // XXX
      prog_warn("No support for format-specific headers");
   }
   if (infoflags & INFO_HEADERS_SECTION) {
      // XXX
      prog_warn("No support for section headers");
   }
   if (infoflags & (INFO_CONTENTS_CODE|INFO_CONTENTS_DATA)) {
      dump_contents(bf);
   }
   if (infoflags & (INFO_DEBUG|INFO_DEBUG_RAW)) {
      // XXX
      prog_warn("No support for debug info");
   }
   if (infoflags & INFO_SYMS) {
      // XXX
      prog_warn("No support for syms");
   }
   if (infoflags & INFO_DYNSYMS) {
      // XXX
      prog_warn("No support for dynamic syms");
   }
   if (infoflags & INFO_RELOCS) {
      // XXX
      prog_warn("No support for relocs");
   }
   if (infoflags & INFO_DYNRELOCS) {
      // XXX
      prog_warn("No support for dynamic relocs");
   }

   dumptable_cleanup();
}

static void dump_genfile(const char *name, struct genfile *gf) {
   struct binfile *bf;

   bf = binfile_bind(name, gf);
   if (bf==NULL) {
      prog_warn("%s: Unsupported/invalid file format", name);
      genfile_close(gf);
      return;
   }
   dump_binfile(name, bf);
   binfile_destroy(bf);
}

static void dump_arfile(const char *name, struct arfile *arf) {
   struct genfile *gen;
   unsigned n, i;
   const char *subname;
   char namebuf[256];

   n = ar_getnumfiles(arf);
   for (i=0; i<n; i++) {
      subname = ar_getname(arf, i);
      gen = ar_opensubfile(arf, subname);
      assert(gen != NULL);

      snprintf(namebuf, sizeof(namebuf), "%s(%s)", name, subname);

      if (infoflags & INFO_HEADERS_AR) {
	 // XXX
	 prog_warn("No support for ar headers");
      }

      dump_genfile(namebuf, gen);        /* consumes gen */
   }
}

void dump(const char *filename) {
   struct arfile *arf;
   struct genfile *gen;

   arf = ar_open(filename, "r", false);
   if (arf != NULL) {
      dump_arfile(filename, arf);
      ar_close(arf);
      return;
   }

   gen = genfile_open(filename, "r");
   if (gen != NULL) {
      dump_genfile(filename, gen);	/* consumes gen */
      return;
   }

   prog_err("Cannot open %s: %s", filename, strerror(errno));
}
