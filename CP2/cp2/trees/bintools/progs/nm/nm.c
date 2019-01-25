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
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <getopt.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "version.h"
#include "host/installdirs.h"
#include "array.h"
#include "arlib.h"
#include "genfile.h"
#include "binfile.h"
#include "genfmt.h"

static bool gflag, nflag, oflag, pflag, Pflag, rflag, uflag;
static int printbase=16;

////////////////////////////////////////////////////////////

struct mysym {
   char *ms_name;
   u_machword ms_addr;
   unsigned char ms_type;
};

DECLARRAY_FULL(symarray, struct mysym, static inline);
DEFARRAY_FULL(symarray, struct mysym, static inline);
static struct symarray syms;

static void initsyms(void) {
   symarray_init(&syms);
}

static void cleansyms(void) {
   unsigned i, num;
   struct mysym *s;

   num = symarray_num(&syms);
   for (i=0; i<num; i++) {
      s = symarray_getptr(&syms, i);
      dostrfree(s->ms_name);
   }
   symarray_setsize(&syms, 0);
   symarray_cleanup(&syms);
}

static void addsym(const char *name, u_machword value, unsigned char type) {
   struct mysym ms;

   ms.ms_name = dostrdup(name);
   ms.ms_addr = value;
   ms.ms_type = type;

   symarray_add(&syms, ms);
}

static void printsyms(const char *filename) {
   unsigned i, num;
   struct mysym *s;
   char addr[64];
   const char *fmt;

   num = symarray_num(&syms);
   for (i=0; i<num; i++) {
      if (oflag) {
	 printf("%s:%s", filename, Pflag ? " " : "");
      }

      s = symarray_getptr(&syms, i);
      if (s->ms_type == 'U') {
	 addr[0] = 0;
      }
      else {
	 switch (printbase) {
	  case 8: fmt = "%08lo"; break;
	  case 10: fmt = "%08lu"; break;
	  case 16: fmt = "%08lx"; break;
	  default: assert(0); fmt = "???"; break;
	 }
	 snprintf(addr, sizeof(addr), fmt, (unsigned long) s->ms_addr); 
      }

      if (Pflag) {
	 /* posix format */
	 printf("%s %c %s\n", s->ms_name, s->ms_type, addr);
      }
      else {
	 /* bsd format */
	 /* XXX: %-8s is only for 32-bit targets! */
	 printf("%-8s %c %s\n", addr, s->ms_type, s->ms_name);
      }
   }
}

static int sort_numeric(const void *av, const void *bv) {
   const struct mysym *a, *b;

   a = (const struct mysym *)av;
   b = (const struct mysym *)bv;

   if (a->ms_addr < b->ms_addr) {
      return -1;
   }
   else if (a->ms_addr > b->ms_addr) {
      return 1;
   }
   return 0;
}

static int sort_name(const void *av, const void *bv) {
   const struct mysym *a, *b;

   a = (const struct mysym *)av;
   b = (const struct mysym *)bv;

   return strcmp(a->ms_name, b->ms_name);
}

static int rev_sort_numeric(const void *av, const void *bv) {
   return -sort_numeric(av, bv);
}

static int rev_sort_name(const void *av, const void *bv) {
   return -sort_name(av, bv);
}

static void sortsyms(int (*func)(const void *, const void *)) {
   qsort(symarray_getdata(&syms), symarray_num(&syms), sizeof(struct mysym),
	 func);
}

////////////////////////////////////////////////////////////

static unsigned char classify_symbol(struct binfile *bf, struct gensym *gsm) {
   unsigned char t;
   struct gensect *gsx;

   assert(gsm->gsm_section != GSX_INVALID);

   if (gsm->gsm_section == GSX_UNDEF) {
      t = 'U';
   }
   else if (gsm->gsm_section == GSX_ABS) {
      t = 'a';
   }
   else if (gsm->gsm_section == GSX_COMMON) {
      t = 'c';
   }
   else if (gsm->gsm_type == GSMT_CODE) {
      t = 't';
   }
   else if (gsm->gsm_type == GSMT_DATA) {
      gsx = binfile_getsection(bf, gsm->gsm_section, false);
      assert(gsx != NULL);
      if (gsx->gsx_flags & GSXF_ISBSS) {
	 t = 'b';
      }
      else if (gsx->gsx_flags & GSXF_WRITEPERM) {
	 t = 'd';
      }
      else {
	 t = 'r';
      }
   }
   else {
      t = '?';
   }

   if (gsm->gsm_flags & GSMF_WEAK) {
      t = 'W';
   }
   if (gsm->gsm_flags & GSMF_GLOBL) {
      t = toupper(t);
   }
   return t;
}

/*
 * Consumes the genfile.
 */
static void readbinfile(struct genfile *gf, const char *filename) {
   struct binfile *bf;
   unsigned i, nsyms;
   struct gensym *gsm;

   bf = binfile_bind(filename, gf);
   if (bf == NULL) {
      prog_err("%s: Unrecognized file format", filename);
   }

   nsyms = binfile_numsymbols(bf);
   if (nsyms == 0) {
      fprintf(stderr, "%s: no symbols\n", filename);
      return;
   }

   initsyms();

   for (i=0; i<nsyms; i++) {
      gsm = binfile_getsymbol(bf, i);
      if (gsm == NULL) {
	 /* symbol doesn't exist, or is format-internal */
	 continue;
      }
      if (gflag && (gsm->gsm_flags & GSMF_GLOBL) == 0) {
	 /* gflag == externs only */
	 continue;
      }
      if (uflag && gsm->gsm_section != GSX_UNDEF) {
	 /* uflags == undefined only */
	 continue;
      }
      if (gsm->gsm_type == GSMT_FILENAME) {
	 /* don't print these */
	 continue;
      }
      if (gsm->gsm_name == NULL) {
	 /* no name to print, skip it */
	 continue;
      }

      addsym(gsm->gsm_name, gsm->gsm_value, classify_symbol(bf, gsm));
   }

   if (nflag) {
      sortsyms(rflag ? rev_sort_numeric : sort_numeric);
   }
   else if (!pflag) {
      sortsyms(rflag ? rev_sort_name : sort_name);
   }
   printsyms(filename);
   cleansyms();

   binfile_destroy(bf);
}

static void readfile(const char *filename) {
   struct arfile *arf;
   struct genfile *nmfile;

   arf = ar_open(filename, "r", false);
   if (arf) {
      const char *subfile;
      char *errname;
      unsigned i;

      for (i=0; i<ar_getnumfiles(arf); i++) {
	 subfile = ar_getname(arf, i);
	 nmfile = ar_opensubfile(arf, subfile);
	 assert(nmfile != NULL);

	 errname = ar_mkreportname(arf, subfile);

	 readbinfile(nmfile, errname);

	 //genfile_close(nmfile);
	 dostrfree(errname);
      }
   }
   else {
      nmfile = genfile_open(filename, "r");
      if (!nmfile) {
	 prog_err("Cannot open %s", filename);
      }

      readbinfile(nmfile, filename);

      //genfile_close(nmfile);
   }
}

////////////////////////////////////////////////////////////

static void usage(void) {
   fprintf(stderr, "Usage: %snm [-ABgnopPruvV] [-t radix] [files]\n", 
	   INSTALLTARGET);
   fprintf(stderr, "   -A            (same as -o)\n");
   fprintf(stderr, "   -B            BSD output format (default)\n");
   fprintf(stderr, "   -g            Global symbols only\n");
   fprintf(stderr, "   -n            Sort by address (numerically)\n");
   fprintf(stderr, "   -o            Print filename on each line\n");
   fprintf(stderr, "   -p            Don't sort (default: sort by name)\n");
   fprintf(stderr, "   -P            POSIX output format\n");
   fprintf(stderr, "   -r            Reverse sort\n");
   fprintf(stderr, "   -t d|o|x      Set radix for printing addresses\n");
   fprintf(stderr, "                   (decimal, octal, or hex)\n");
   fprintf(stderr, "   -u            Undefined symbols only\n");
   fprintf(stderr, "   -v            (same as -n)\n");
   fprintf(stderr, "   -V            Print version and exit\n");
   exit(1);
}


int main(int argc, char *argv[]) {
   int ch;

   prog_setname(INSTALLTARGET "nm");

   while ((ch = getopt(argc, argv, "ABgnopPrt:uvV"))!=-1) {
      switch (ch) {
       case 'A': oflag = true; break;
       case 'B': Pflag = false; break;
       case 'g': gflag = true; break;
       case 'n': nflag = true; break;
       case 'o': oflag = true; break;
       case 'p': pflag = true; break;
       case 'P': Pflag = true; break;
       case 'r': rflag = true; break;
       case 't': 
	if (!strcmp(optarg, "d")) printbase=10;
	else if (!strcmp(optarg, "o")) printbase=8;
	else if (!strcmp(optarg, "x")) printbase=16;
	else usage();
	break;
       case 'u': uflag = true; break;
       case 'v': nflag = true; break;
       case 'V':
	fprintf(stderr, "bintools nm (%snm) version %s\n", INSTALLTARGET,
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

   return 0;
}
