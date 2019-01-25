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

/*
 * In this toolchain, ranlib exists but does nothing. We just check the
 * target for being a valid .a file.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "common.h"

#include "arlib.h"
#include "version.h"
#include "host/installdirs.h"

static void check(const char *name) {
   struct arfile *af;

   af = ar_open(name, "r", false);
   if (!af) {
      prog_err("%s: Cannot open, or not ar file", name);
   }

   ar_close(af);
}

static void usage(void) {
   fprintf(stderr, "Usage: %sranlib [-vV] lib.a\n", INSTALLTARGET);
   fprintf(stderr, "   -v            Print version number and exit\n");
   fprintf(stderr, "   -V            (same as -v)\n");
   exit(1);
}

int main(int argc, char *argv[]) {
   int ch;

   prog_setname(INSTALLTARGET "ranlib");

   while ((ch = getopt(argc, argv, "vV"))!=-1) {
      switch (ch) {
       case 'v':
       case 'V':
	fprintf(stderr, "bintools ranlib (%sranlib) version %s\n", 
		INSTALLTARGET, VERSION);
	return 0;
       default:
	usage();
	break;
      }
   }
   if (optind != argc-1) {
      usage();
   }

   check(argv[optind]);

   return 0;
}
