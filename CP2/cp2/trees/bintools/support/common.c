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

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "common.h"


static const char *progname;
static const char *filename;

void prog_setname(const char *pn) {
   progname = pn;
}

void file_setname(const char *fn) {
   filename = fn;
}

void file_clearname(void) {
   filename = NULL;
}

void prog_err(const char *fmt, ...) {
   va_list ap;

   assert(progname != NULL);
   fprintf(stderr, "%s: ", progname);

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);

   fprintf(stderr, "\n");
   exit(1);
}

void prog_warn(const char *fmt, ...) {
   va_list ap;

   assert(progname != NULL);
   fprintf(stderr, "%s: ", progname);

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);

   fprintf(stderr, "\n");
}

void file_err(int line, const char *fmt, ...) {
   va_list ap;

   // XXX ld doesn't set the filename when applying relocs
   //assert(filename != NULL);

   if (line == 0) {
      fprintf(stderr, "%s: ", filename ? filename : "<UNKNOWN>");
   }
   else {
      fprintf(stderr, "%s:%d: ", filename ? filename : "<UNKNOWN>", line);
   }

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);

   fprintf(stderr, "\n");
   exit(1);
}

void file_warn(int line, const char *fmt, ...) {
   va_list ap;

   // XXX ld doesn't set the filename when applying relocs
   //assert(filename != NULL);

   if (line == 0) {
      fprintf(stderr, "%s: ", filename ? filename : "<UNKNOWN>");
   }
   else {
      fprintf(stderr, "%s:%d: ", filename ? filename : "<UNKNOWN>", line);
   }

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);

   fprintf(stderr, "\n");
}

