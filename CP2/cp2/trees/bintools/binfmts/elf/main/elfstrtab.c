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
#include <stdint.h> /* for SIZE_MAX (for buffer.h) */
#include <limits.h>
#include <assert.h>
#include "common.h"

#include "array.h"
#include "buffer.h"
#include "genfile.h"
#include "elfstrtab.h"

/* XXX why do we collect/track es_offsets? */

struct elfstrtab {
   struct buffer es_data;
   struct sizearray es_offsets;
};

static struct elfstrtab *elfstrtab_create(void) {
   struct elfstrtab *es;

   es = domalloc(sizeof(*es));
   buffer_init(&es->es_data);
   sizearray_init(&es->es_offsets);
   return es;
}

void elfstrtab_destroy(struct elfstrtab *es) {
   sizearray_setsize(&es->es_offsets, 0);
   sizearray_cleanup(&es->es_offsets);
   buffer_cleanup(&es->es_data);
   dofree(es, sizeof(*es));
}

struct elfstrtab *elfstrtab_new(void) {
   struct elfstrtab *es;

   es = elfstrtab_create();
   buffer_setsize(&es->es_data, 1);
   buffer_setbyte(&es->es_data, 0, 0);
   sizearray_add(&es->es_offsets, 0);
   return es;
}

struct elfstrtab *elfstrtab_load(struct genfile *from, off_t pos, size_t len) {
   struct elfstrtab *es;
   size_t i;

   if (len==0) {
      prog_err("%s: Corrupt ELF file (invalid string table size 0)",
	       genfile_getname(from));
   }

   es = elfstrtab_create();

   buffer_setsize(&es->es_data, len);
   genfile_read(from, pos, buffer_mapat(&es->es_data, 0, len), len);

   if (buffer_getbyte(&es->es_data, 0) != 0) {
      prog_err("%s: Corrupt ELF file (first entry in string table not \"\")",
	       genfile_getname(from));
   }
   if (buffer_getbyte(&es->es_data, len - 1) != 0) {
      prog_err("%s: Corrupt ELF file (last entry unterminated)",
	       genfile_getname(from));
   }

   i = 0;
   while (i < len) {
      sizearray_add(&es->es_offsets, i);
      /* skip to null terminator */
      i += strlen(buffer_mapat(&es->es_data, i, len - i));
      /* past null terminator */
      i++;
   }

   return es;
}

const char *elfstrtab_get(struct elfstrtab *es, size_t offset) {
   size_t size;

   /*
    * Sigh. Using the suffix of another name is ok, so we can't
    * enforce that the offset is at a string boundary.
    */

   size = buffer_getsize(&es->es_data);
   if (offset < size) {
      return buffer_mapat(&es->es_data, offset, size-offset);
   }
   return NULL;
}

size_t elfstrtab_add(struct elfstrtab *es, const char *str) {
   size_t size, here, len;
   unsigned i, num;

   /* see if we already have it */
   num = sizearray_num(&es->es_offsets);
   size = buffer_getsize(&es->es_data);
   for (i=0; i<num; i++) {
      here = sizearray_get(&es->es_offsets, i);
      if (!strcmp(buffer_mapat(&es->es_data, here, size-here), str)) {
	 return here;
      }
   }

   /* guess not */
   len = strlen(str) + 1;
   buffer_addblob(&es->es_data, str, len);
   sizearray_add(&es->es_offsets, size);
   return size;
}

size_t elfstrtab_getsize(struct elfstrtab *es) {
   return buffer_getsize(&es->es_data);
}

void *elfstrtab_getdata(struct elfstrtab *es) {
   return buffer_mapat(&es->es_data, 0, buffer_getsize(&es->es_data));
}

//void elfstrtab_save(struct elfstrtab *es, struct genfile *to, off_t pos) {
//   size_t size;
//
//   size = buffer_getsize(&es->es_data);
//   genfile_write(to, pos, buffer_mapat(&es->es_data, 0, size), size);
//}
