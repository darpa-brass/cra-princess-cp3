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

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <assert.h>
#include "common.h"

#include "version.h"
#include "host/installdirs.h"
#include "arlib.h"
#include "genfile.h"
#include "binfile.h"

static bool sysvformat = false;
static bool totals = false;
static int base = 10;

static bool failed = false;

static u_machword total_text = 0, total_data = 0, total_bss = 0;

static void showsysv(const char *name, struct binfile *bf) {
   struct gensect *gsx;
   unsigned n, i;
   u_machword total = 0;

   printf("%s  :\n", name);
   printf("%-16s %8s  %10s\n", "section", "size", "addr");

   n = binfile_numsections(bf);
   for (i=0; i<n; i++) {
      gsx = binfile_getsection(bf, i, 0);
      if (gsx==NULL) {
	 continue;
      }
      printf("%-16s ", gsx->gsx_name);
      if (base==10) {
	 printf("%8llu  %10llu\n",
		(unsigned long long) gsx->gsx_size, 
		(unsigned long long) gsx->gsx_vaddr);
      }
      else if (base==8) {
	 printf("0%7llo  0%9llo\n",
		(unsigned long long) gsx->gsx_size, 
		(unsigned long long) gsx->gsx_vaddr);
      }
      else {
	 printf("0x%6llx  0x%8llx\n",
		(unsigned long long) gsx->gsx_size, 
		(unsigned long long) gsx->gsx_vaddr);
      }
      total += gsx->gsx_size;
   }
   printf("%-16s ", "Total");
   if (base==10) {
      printf("%8llu\n", (unsigned long long) total);
   }
   else if (base==8) {
      printf("0%7llo\n", (unsigned long long) total);
   }
   else {
      printf("0x%6llx\n", (unsigned long long) total);
   }
   printf("\n\n");
}

static void printbsd(const char *name,
		     u_machword text, u_machword data, u_machword bss) {
   if (base==10) {
      printf("%-7llu %-7llu %-7llu", (unsigned long long) text, 
	     (unsigned long long) data, (unsigned long long) bss);
   }
   else if (base==8) {
      printf("0%-6llo 0%-6llo 0%-6llo", (unsigned long long) text, 
	     (unsigned long long) data, (unsigned long long) bss);
   }
   else {
      printf("0x%-5llx 0x%-5llx 0x%-5llx", (unsigned long long) text, 
	     (unsigned long long) data, (unsigned long long) bss);
   }

   if (base==8) {
      printf(" %-7llo", (unsigned long long) (text+data+bss));
   }
   else {
      printf(" %-7llu", (unsigned long long) (text+data+bss));
   }

   printf(" %-7llx", (unsigned long long) (text+data+bss));
   printf(" %s\n", name);
}

static void showbsd(const char *name, struct binfile *bf) {
   static int header=0;

   struct gensect *gsx;
   unsigned n, i;
   u_machword text=0, data=0, bss=0;

   n = binfile_numsections(bf);
   for (i=0; i<n; i++) {
      gsx = binfile_getsection(bf, i, 0);
      if (gsx==NULL) {
	 continue;
      }

      if ((gsx->gsx_flags & GSXF_LOADABLE)==0) {
	 continue;
      }

      if (gsx->gsx_flags & GSXF_ISBSS) {
	 bss += gsx->gsx_size;
      }
      else if (gsx->gsx_flags & GSXF_EXECPERM) {
	 text += gsx->gsx_size;
      }
      else {
	 data += gsx->gsx_size;
      }
   }

   if (!header) {
      header = 1;
      printf("%-7s %-7s %-7s %-7s %-7s %s\n", 
	     "text", "data", "bss", 
	     base==8 ? "oct" : "dec", "hex", "filename");
   }
   printbsd(name, text, data, bss);
   total_text += text;
   total_data += data;
   total_bss += bss;
}

static void readgenfile(const char *name, struct genfile *gen) {
   struct binfile *bf;

   bf = binfile_bind(name, gen);
   if (bf==NULL) {
      prog_warn("%s: Unsupported/invalid file format", name);
      genfile_close(gen);
      return;
   }

   if (sysvformat) {
      showsysv(name, bf);
   }
   else {
      showbsd(name, bf);
   }

   binfile_destroy(bf);
}

static void readarfile(const char *name, struct arfile *arf) {
   struct genfile *gen;
   unsigned n, i;
   const char *subname;
   char namebuf[256];

   n = ar_getnumfiles(arf);
   for (i=0; i<n; i++) {
      subname = ar_getname(arf, i);
      gen = ar_opensubfile(arf, subname);
      assert(gen != NULL);

      snprintf(namebuf, sizeof(namebuf), "%s (ex %s)", subname, name);

      readgenfile(namebuf, gen);	/* consumes gen */
   }
}

static void readfile(const char *name) {
   struct arfile *arf;
   struct genfile *gen;

   arf = ar_open(name, "r", false);
   if (arf != NULL) {
      readarfile(name, arf);
      ar_close(arf);
      return;
   }

   gen = genfile_open(name, "r");
   if (gen==NULL) {
      prog_warn("%s: %s", name, strerror(errno));
      failed = true;
      return;
   }

   readgenfile(name, gen);	/* consumes gen */
}

static void usage(void) {
   printf("Usage: %ssize [options] [objects...]\n", INSTALLTARGET);
   printf("   -A           System V format output\n");
   printf("   -B           BSD format output (default)\n");
   printf("   -d           Print in decimal (default)\n");
   printf("   -o           Print in octal\n");
   printf("   -x           Print in hex\n");
   printf("   -t           Print totals over all files\n");
   printf("   -V           Print version and exit\n");
   exit(1);
}

int main(int argc, char *argv[]) {
   prog_setname(INSTALLTARGET "size");

   int ch;
   while ((ch = getopt(argc, argv, "ABdoxtV"))!=-1) {
      switch (ch) {
       case 'A': sysvformat = true; break;
       case 'B': sysvformat = false; break;
       case 'd': base = 10; break;
       case 'o': base = 8; break;
       case 'x': base = 16; break;
       case 't': totals = true; break;
       case 'V':
	printf("bintools size (%ssize) version %s\n", INSTALLTARGET,
	       VERSION);
	return 0;
       default:
	usage();
	break;
      }
   }
   if (optind==argc) {
      readfile("a.out");
   }
   else {
      while (optind < argc) {
	 readfile(argv[optind++]);
      }
   }

   if (totals && !sysvformat) {
      printbsd("(TOTALS)", total_text, total_data, total_bss);
   }

   return failed ? 1 : 0;
}
