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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "version.h"
#include "host/installdirs.h"
#include "array.h"
#include "arlib.h"
#include "binfile.h"

#include "utils.h"
#include "loadfile.h"
#include "main.h"
#include "section.h"
#include "symtab.h"
#include "outputsym.h"
#include "outputrel.h"
#include "savefile.h"

static int failed=0;

void main_failed(void) {
   failed = 1;
}

////////////////////////////////////////////////////////////

static struct stringarray searchpath;
static size_t searchentrylen;

static void searchlibrary(const char *name) {
   unsigned i, num;
   size_t len;
   const char *entry;
   char *tmp;

   len = searchentrylen + strlen(name);
   len += 6; /* 6 additional chars: "/", "lib", and ".a" */

   tmp = domalloc(len+1);
   num = stringarray_num(&searchpath);
   for (i=0; i<num; i++) {
      entry = stringarray_get(&searchpath, i);
      snprintf(tmp, len+1, "%s/lib%s.a", entry, name);
      if (file_exists(tmp)) {
	 say(1, "-l%s -> %s", name, tmp);
	 loadfile(tmp, 0);
	 dostrfree(tmp);
	 return;
      }
   }
   prog_err("Cannot find library for -l%s", name);
}


////////////////////////////////////////////////////////////

struct cmdlinefile {
   const char *name;
   int flag;
};

DECLARRAY_FULL(cmdlinefilearray, struct cmdlinefile, static UNUSED inline);
DEFARRAY_FULL(cmdlinefilearray, struct cmdlinefile, static UNUSED inline);

static struct cmdlinefilearray cmdlinefiles;

static void addfile(const char *name, int flag) {
   struct cmdlinefile cf;

   cf.name = name;
   cf.flag = flag;
   cmdlinefilearray_add(&cmdlinefiles, cf);
}

static void usage(void) {
   fprintf(stderr, "Usage: %sld [options | files]\n", INSTALLTARGET);
   fprintf(stderr, "   -d            Force allocation of commons with -r\n");
   fprintf(stderr, "   -e entry      Choose entry point symbol [%s]\n",
	   ENTRY_SYM);
   fprintf(stderr, "   -g            (ignored for compatibility)\n");
   fprintf(stderr, "   -i            (same as -r)\n");
   fprintf(stderr, "   -llibrary     Link in the specified library\n");
   fprintf(stderr, "   -Ldir         Add DIR to the library search path\n");
   fprintf(stderr, "   -n            Make code read-only (default)\n");
   fprintf(stderr, "   -N            Make code read-write\n");
   fprintf(stderr, "   -o output     Set name of output file [a.out]\n");
   fprintf(stderr, "   -R file       Use FILE's symbols w/o linking it in\n");
   fprintf(stderr, "   -r            Incremental link; output is .o file\n");
   fprintf(stderr, "   -S            Strip debug info from output file\n");
   fprintf(stderr, "   -s            Strip all symbols from output file\n");
   fprintf(stderr, "   -Ttext addr   Set the base address for code,\n");
   fprintf(stderr, "   -Tdata addr      data, and bss respectively.\n");
   fprintf(stderr, "   -Tbss addr       The address must be in hex.\n");
   fprintf(stderr, "   -t            Print progress information\n");
   fprintf(stderr, "   -u sym        Force SYM to be treated as undefined\n");
   fprintf(stderr, "   -Ur           Like -r but resolves constructors\n");
   fprintf(stderr, "   -V            Just print version number\n");
   fprintf(stderr, "   -v            Verbose\n");
   fprintf(stderr, "   -X            Delete scratch symbols (.L*)\n");
   fprintf(stderr, "   -x            Delete all local symbols\n");
   exit(1);
}

int main(int argc, char *argv[]) {
   int i;
   unsigned j, num;
   struct cmdlinefile file;

   int tflag=0, Vflag=0;
   int nflag=1;
   int dflag=0, rflag=0, Uflag=0;
   int Sflag=0, sflag=0, Xflag=0, xflag=0;

   const char *entry = ENTRY_SYM;
   u_machword entryaddr = 0;
   const char *output = "a.out";

   u_machword textorg = DEFAULT_TEXTORG;
   u_machword dataorg = DEFAULT_DATAORG;
   u_machword bssorg = DEFAULT_BSSORG;

   prog_setname(INSTALLTARGET "ld");

   outputsym_setup();
   outputrel_setup();
   section_setup();
   symtab_setup();
   stringarray_init(&searchpath);
   cmdlinefilearray_init(&cmdlinefiles);

   /*
    * Do NOT use getopt.
    */
   for (i=1; i<argc; i++) {
      if (argv[i][0]=='-' && argv[i][1]!=0 && argv[i][2]==0) {
	 switch (argv[i][1]) {
	  case 'd': dflag = 1; break;
	  case 'g': break;
	  case 'i': rflag = 1; break;
	  case 'n': nflag = 1; break;
	  case 'N': nflag = 0; break;
	  case 'r': rflag = 1; break;
	  case 'S': Sflag = 1; break;
	  case 's': sflag = 1; break;
	  case 't': tflag = 1; break;
	  case 'V': Vflag = 1; break;
	  case 'v': verbose++; break;
	  case 'X': Xflag = 1; break;
	  case 'x': xflag = 1; break;

	  case 'e': 
	   if (i==argc-1) usage();
	   entry = argv[++i];
	   break;
	  case 'o':
	   if (i==argc-1) usage();
	   output = argv[++i];
	   break;
	  case 'R':
	   if (i==argc-1) usage();
	   addfile(argv[++i], 'R');
	   break;
	  case 'u': 
	   if (i==argc-1) usage();
	   symbol_commandline_undef(argv[++i]);
	   break;
	  default:
	   usage();
	   break;
	 }
      }
      else if (argv[i][0]=='-' && argv[i][1]=='l') {
	 addfile(argv[i]+2, 'l');
      }
      else if (argv[i][0]=='-' && argv[i][1]=='L') {
	 char *dir = argv[i]+2;
	 size_t len = strlen(dir);
	 if (len > searchentrylen) {
	    searchentrylen = len;
	 }
	 stringarray_add(&searchpath, dir);
      }
      else if (!strcmp(argv[i], "-nostdlib")) {
	 /* has no effect - default search path is empty */
      }
      else if (!strcmp(argv[i], "-Ur")) {
	 rflag = 1;
	 Uflag = 1;
      }
      else if (!strcmp(argv[i], "-Ttext")) {
	 if (i==argc-1) usage();
	 textorg = strtoul(argv[++i], NULL, 16);
      }
      else if (!strcmp(argv[i], "-Tdata")) {
	 if (i==argc-1) usage();
	 dataorg = strtoul(argv[++i], NULL, 16);
      }
      else if (!strcmp(argv[i], "-Tbss")) {
	 if (i==argc-1) usage();
	 bssorg = strtoul(argv[++i], NULL, 16);
      }
      else if (argv[i][0]=='-') {
	 usage();
      }
      else {
	 addfile(argv[i], 0);
      }
   }

   if (Vflag || verbose > 0) {
      fprintf(stderr, "bintools ld (%sld) version %s\n", INSTALLTARGET,
	      VERSION);
      if (Vflag) {
	 return 0;
      }
   }

   if (cmdlinefilearray_num(&cmdlinefiles) == 0) {
      prog_err("No input files");
   }

   say(2, "Entry point symbol: %s", entry);
   //symtab_setentry(entry);

   num = cmdlinefilearray_num(&cmdlinefiles);
   for (j=0; j<num; j++) {
      file = cmdlinefilearray_get(&cmdlinefiles, j);
      if (tflag) {
	 say(0, "Loading %s", file.name);
      }
      switch (file.flag) {
       case 'R':
	loadfile(file.name, 1);
	break;
       case 'l':
	searchlibrary(file.name);
	break;
       case 0:
	loadfile(file.name, 0);
	break;
       default:
	assert(0);
	break;
      }
   }

   if (!rflag) {
      symtab_noundefs(1);
   }

   if (failed) {
      return 1;
   }

   if (!rflag || dflag) {
      symtab_alloc_commons();
   }

   if (!rflag || Uflag) {
      // XXX? I don't think we need to do anything special
      // symtab_arrange_constructors();
   }

   if (!rflag && !nflag) {
      /* generate impure executable - XXX */
      prog_warn("Warning: no support for -N (ignoring)");
   }

   if (!rflag) {
      bool impure = !nflag;

      /* lay out program and perform relocations */
      section_layout(textorg, dataorg, bssorg, impure);

      symtab_noundefs(0);
   }

   symtab_push_definitions();

   if (!rflag) {
      outputreloc_performall();
   }

   if (!rflag) {
      unsigned entrysym;

      entrysym = symtab_find(entry);
      if (entrysym == GSM_INVALID) {
	 prog_err("Cannot find entry point symbol %s", entry);
      }
      entryaddr = outputsym_getaddr(entrysym);
   }

   outputreloc_markusedsyms();

   if (Sflag || sflag) {
      /* strip debug info - XXX */
      prog_warn("Warning: no support for -S (ignoring");
   }

   if (sflag) {
      /* strip all symbols - XXX */
      prog_warn("Warning: no support for -s (ignoring");
   }
   else if (xflag) {
      /* strip all local symbols - XXX */
      prog_warn("Warning: no support for -x (ignoring");
   }
   else if (Xflag) {
      /* strip all temporary-local symbols - XXX */
      prog_warn("Warning: no support for -X (ignoring");
   }

   savefile(output, rflag ? BFT_OBJ : BFT_PROG, entryaddr);

   if (failed) {
      remove(output);
   }

   stringarray_setsize(&searchpath, 0);
   stringarray_cleanup(&searchpath);
   cmdlinefilearray_setsize(&cmdlinefiles, 0);
   cmdlinefilearray_cleanup(&cmdlinefiles);
   symtab_shutdown();
   section_shutdown();
   outputrel_shutdown();
   outputsym_shutdown();

   return failed;
}
