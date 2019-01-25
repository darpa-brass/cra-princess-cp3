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
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <getopt.h>
#include <assert.h>
#include "common.h"

#include "version.h"
#include "array.h"
#include "host/installdirs.h"
#include "arlib.h"
#include "genfile.h"

static const char *basename(const char *path) {
   const char *s;

   s = strrchr(path, '/');
   if (s) {
      return s+1;
   }
   return path;
}

////////////////////////////////////////////////////////////

static void copy(struct genfile *from, struct genfile *to) {
   char buf[4096];
   off_t pos;
   size_t len;

   pos = 0;
   while (1) {
      len = genfile_readeof(from, pos, buf, sizeof(buf));
      if (len == 0) {
	 break;
      }
      genfile_write(to, pos, buf, len);
      pos += len;
   }
   genfile_setsize(to, pos);
}

static void print(const char *arfname, struct arfile *arf,
		  const char *subname, int verbose)
{
   struct genfile *from, *to;

   from = ar_opensubfile(arf, subname);
   if (!from) {
      prog_warn("%s: No entry %s in archive", arfname, subname);
      return;
   }

   to = genfile_getstdout();
   
   if (verbose) {
      printf("\n<%s>\n\n", subname);
   }
   
   copy(from, to);
   genfile_close(from);
}

static void printmode(int bits, int sbit, int schr) {
   putchar((bits & 4) ? 'r' : '-');
   putchar((bits & 2) ? 'w' : '-');
   if (sbit) {
      putchar((bits & 1) ? schr : toupper(schr));
   }
   else {
      putchar((bits & 1) ? 'x' : '-');
   }
}

static void show(const char *arfname, struct arfile *arf, 
		 const char *subname, int verbose) {
   struct genfile *g;

   g = ar_opensubfile(arf, subname);
   if (!g) {
      prog_warn("%s: No entry %s in archive", arfname, subname);
      return;
   }
   
   if (!verbose) {
      printf("%s\n", subname);
   }
   else {
      struct genfile_info gi;
      char time[128];
      struct tm *t;

      genfile_getinfo(g, &gi);

      t = localtime(&gi.gi_mtime);
      strftime(time, sizeof(time), "%b %e %H:%M %Y", t);
      
      printmode((gi.gi_mode & 0700) >> 6, gi.gi_mode & 04000, 's');
      printmode((gi.gi_mode & 0070) >> 3, gi.gi_mode & 02000, 's');
      printmode((gi.gi_mode & 0007), gi.gi_mode & 01000, 't');
      
      printf(" %u/%u %6ld %s %s\n", (unsigned) gi.gi_uid, (unsigned) gi.gi_gid,
	     (long) gi.gi_size, time, subname);
   }

   genfile_close(g);
}

static void add(struct arfile *arf, const char *bname, struct genfile *from) {
   struct genfile_info gi;
   struct genfile *to;

   genfile_getinfo(from, &gi);

   to = ar_newsubfile(arf, bname, gi.gi_size, gi.gi_mtime, 
		      gi.gi_mode, gi.gi_uid, gi.gi_gid);

   copy(from, to);
   genfile_close(to);
}

static void replace(struct genfile *from, struct genfile *to) {
   struct genfile_info gi;

   genfile_getinfo(from, &gi);

   genfile_setsize(to, gi.gi_size);
   genfile_touch(to, gi.gi_mtime);
   genfile_chmod(to, gi.gi_mode, gi.gi_uid, gi.gi_gid);
				
   copy(from, to);
}

static void insert(struct arfile *arf, const char *name, int upd, int verbose){
   struct genfile *subfile, *outsidefile;
   const char *bname;

   bname = basename(name);

   outsidefile = genfile_open(name, "r");
   subfile = ar_opensubfile(arf, bname);
   if (subfile == NULL) {
      add(arf, bname, outsidefile);
      if (verbose) {
	 printf("a - %s\n", name);
      }
   }
   else {
      int doreplace = 1;

      if (upd) {
	 struct genfile_info subinfo, outsideinfo;
	 
	 genfile_getinfo(subfile, &subinfo);
	 genfile_getinfo(outsidefile, &outsideinfo);
	 
	 /* note: posix says this should not be >= */
	 if (subinfo.gi_mtime > outsideinfo.gi_mtime) {
	    doreplace = 0;
	 }
      }

      if (doreplace) {
	 replace(outsidefile, subfile);
	 if (verbose) {
	    printf("r - %s\n", name);
	 }
      }
      genfile_close(subfile);
   }

   genfile_close(outsidefile);

}

static void extract(struct arfile *arf, const char *name, int oflag) {
   struct genfile *from, *to;
   const char *bname;

   bname = basename(name);

   from = ar_opensubfile(arf, bname);
   if (!from) {
      prog_err("No member %s in archive", bname);
   }

   to = genfile_open(name, "w");
   copy(from, to);

   if (oflag) {
      struct genfile_info gi;
      genfile_getinfo(from, &gi);
      genfile_touch(to, gi.gi_mtime);
   }

   genfile_close(to);
   genfile_close(from);
}

////////////////////////////////////////////////////////////

static void showall(const char *arfname, struct arfile *arf, int verbose) {
   unsigned i;

   for (i=0; i<ar_getnumfiles(arf); i++) {
      show(arfname, arf, ar_getname(arf, i), verbose);
   }
}

static void printall(const char *arfname, struct arfile *arf, int verbose) {
   unsigned i;

   for (i=0; i<ar_getnumfiles(arf); i++) {
      print(arfname, arf, ar_getname(arf, i), verbose);
   }
}

////////////////////////////////////////////////////////////

static void usage(void) {
   fprintf(stderr, "Usage: %sar -{dprtx} [-cloqsSuv] [-V] lib.a files\n",
	   INSTALLTARGET);
   fprintf(stderr, "   -d            Delete files from archive\n");
   fprintf(stderr, "   -p            Print files from archive to stdout\n");
   fprintf(stderr, "   -q            Quick-append files to archive\n");
   fprintf(stderr, "   -r            Insert files in archive\n");
   fprintf(stderr, "   -t            List files in archive\n");
   fprintf(stderr, "   -x            Extract files from archive\n");
   fprintf(stderr, "         Must choose exactly one of -dprtx.\n");
   fprintf(stderr, "   -c            Expect to create archive (-r only)\n");
   fprintf(stderr, "   -o            Keep original date stamps (-x only)\n");
   fprintf(stderr, "   -u            Update; insert only newer files"
	   " (-r only)\n");
   fprintf(stderr, "   -v            Verbose\n");
   fprintf(stderr, "   -V            Print version number\n");
   fprintf(stderr, "   -lsS          Ignored for compatibility\n");
   exit(1);
}

int main(int argc, char *argv[]) {
   int op = -1;
   int cflag=0, oflag=0, uflag=0, verbose=0;
   const char *archive;
   const char *file;
   struct stringarray files;
   unsigned i;
   int j;
   int ch;

   prog_setname(INSTALLTARGET "ar");
   stringarray_init(&files);

   while ((ch = getopt(argc, argv, "dpqrtxclosSuvV"))!=-1) {
      switch (ch) {
       case 'd':
       case 'p':
       case 'q':
       case 'r':
       case 't':
       case 'x':
	if (op>=0) usage();
	op = ch;
	break;
       case 'c': cflag=1; break;
       case 'l': /* nothing */ break;
       case 'o': oflag=1; break;
       case 's': /* nothing */ break;
       case 'S': /* nothing */ break;
       case 'u': uflag=1; break;
       case 'v': verbose++; break;
       case 'V': 
	fprintf(stderr, "bintools ar (%sar) version %s\n", INSTALLTARGET,
		VERSION);
	return 0;
       default:
	usage();
	break;
      }
   }
   if (optind==argc) {
      usage();
   }
   archive = argv[optind++];
   for (j=optind; j<argc; j++) {
      stringarray_add(&files, argv[j]);
   }

   if (uflag && op != 'r') {
      usage();
   }
   if (oflag && op != 'x') {
      usage();
   }

   const char *mode = NULL;
   switch (op) {
    case 'd': mode = "r+"; break;
    case 'p': mode = "r"; break;
    case 'q': mode = "r+"; break;
    case 'r': mode = "r+"; break;
    case 't': mode = "r"; break;
    case 'x': mode = "r"; break;
    default: usage(); break;
   }

   struct arfile *arf = ar_open(archive, mode, false);
   if (!arf && (op=='r' || op == 'q')) {
      if (!cflag) {
	 prog_warn("Warning: creating %s", archive);
      }
      arf = ar_open(archive, "w+", true);
   }
   if (!arf) {
      prog_err("Could not open %s, or not an ar file\n", archive);
   }

   if (op=='t' && stringarray_num(&files) == 0) {
      showall(archive, arf, verbose);
   }
   else if (op=='p' && stringarray_num(&files) == 0) {
      printall(archive, arf, verbose);
   }
   else {
      for (i=0; i<stringarray_num(&files); i++) {
	 file = stringarray_get(&files, i);
	 switch (op) {
	  case 'd': 
	   ar_remove(arf, file);
	   if (verbose) {
	      printf("d - %s\n", file);
	   }
	   break;
	  case 'p':
	   print(archive, arf, file, verbose);
	   break;
	  case 'q':
	  case 'r':
	   insert(arf, file, uflag, verbose);
	   break;
	  case 't':
	   show(archive, arf, file, verbose);
	   break;
	  case 'x':
	   extract(arf, file, oflag);
	   if (verbose) {
	      printf("x - %s\n", file);
	   }
	   break;
	 }
      }
   }
   ar_close(arf);

   return 0;
}
