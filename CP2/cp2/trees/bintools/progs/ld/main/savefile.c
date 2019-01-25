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
#include <string.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "genfile.h"
#include "binfile.h"

#include "section.h"
#include "outputsym.h"
#include "outputrel.h"
#include "savefile.h"

static void dochmod(struct genfile *gf) {
   struct genfile_info gi;
   mode_t mode;

   genfile_getinfo(gf, &gi);

   mode = gi.gi_mode & 0777;

   /* turn on execute bits where there are read bits */
   mode = mode | ((mode & 0444) >> 2);

   genfile_chmod(gf, mode, gi.gi_uid, gi.gi_gid);
}

void savefile(const char *output, enum bftypes type, u_machword entry) {
   struct genfile *gf;
   struct binfile *bf;

   gf = genfile_open(output, "w");
   if (gf==NULL) {
      prog_err("%s: Cannot open output file", output);
   }
   dochmod(gf);

   bf = binfile_new(output, gf, type);
   assert(bf != NULL);

   section_emit(bf);
   outputsym_emit(bf);
   outputreloc_emit(bf);

   binfile_setentry(bf, entry);

   binfile_write(bf);
   binfile_destroy(bf);
}
