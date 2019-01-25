/*
 * Copyright (c) 2016
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
#include <stdint.h> /* for SIZE_MAX (for buffer.h) */
#include <limits.h>
#include <assert.h>
#include "common.h"

#include "mem.h"
#define BUFFERINLINE
#include "buffer.h"

void buffer_cleanup(struct buffer *b) {
   dofree(b->data, b->maxsize);
   b->data = NULL;
   b->cursize = b->maxsize = 0;
}

struct buffer *buffer_create(void) {
   struct buffer *b;

   b = domalloc(sizeof(*b));
   buffer_init(b);
   return b;
}

void buffer_destroy(struct buffer *b) {
   buffer_cleanup(b);
   dofree(b, sizeof(*b));
}

void buffer_setsize(struct buffer *b, size_t newsize) {
   size_t newmax;

   if (newsize < b->cursize) {
      if (newsize == 0) {
	 dofree(b->data, b->maxsize);
	 b->data = NULL;
	 b->maxsize = 0;
      }
      b->cursize = newsize;
      return;
   }
   if (newsize > b->maxsize) {
      newmax = b->maxsize ? b->maxsize * 2 : 16;
      while (newmax < newsize) {
	 newmax *= 2;
      }
      b->data = dorealloc(b->data, b->maxsize, newmax);
      b->maxsize = newmax;
   }
   b->cursize = newsize;
}
