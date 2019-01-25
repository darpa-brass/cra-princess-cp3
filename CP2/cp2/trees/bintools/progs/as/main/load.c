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
#include <string.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "mem.h"
#include "utils.h"
#include "fparse.h"
#include "load.h"

/*
 * Read an input file, one (perhaps long) line at a time.
 */
static void loadfile(FILE *f) {
   char *buf, *s;
   size_t bufsize, newsize, len;
   int linenum;

   bufsize = 1024;
   buf = domalloc(bufsize);

   linenum = 1;
   while (fgets(buf, bufsize - 1, f)) {
      while (!strchr(buf, '\n')) {
	 if (bufsize >= 0x40000000) {
	    /* paranoia */
	    prog_err("Input line too long");
	 }
	 newsize = bufsize * 2;
	 buf = dorealloc(buf, bufsize, newsize);
	 bufsize = newsize;

	 len = strlen(buf);
	 if (!fgets(buf+len, bufsize-len - 1, f)) {
	    break;
	 }
      }

      /*
       * At this point, buf definitively contains a whole line. That 
       * is, either we have a newline, or we hit EOF and what we've
       * got is the last line with no newline at the end of the file.
       * Trim the newline if it exists, and assert that we have no
       * *more* than one line.
       */
      s = strchr(buf, '\n');
      if (s) {
	 assert(strlen(s)==1);
	 *s = 0;
      }

      // While this is tempting, it's wrong.
      //
      //s = strchr(buf, '#');
      //if (s) {
      //   /* comment */
      //   *s = 0;
      //}

      /*
       * We have carefully ensured that we have at least one extra slot
       * in the input buffer, so add a space at the end of the line. 
       * (This simplifies the tokenizer.)
       */

      assert(strlen(buf) < bufsize-1);
      strcat(buf, " ");

      parse_line(buf, linenum++);
   }

   parse_eof();
   dofree(buf, bufsize);
}

/*
 * Read the input, possibly from stdin.
 */
void load(const char *filename) {
   FILE *f;

   if (!filename || !strcmp(filename, "-")) {
      loadfile(stdin);
   }
   else {
      f = fopen(filename, "r");
      if (!f) {
	 prog_err("%s: Cannot open", filename);
      }
      loadfile(f);
      fclose(f);
   }
}
