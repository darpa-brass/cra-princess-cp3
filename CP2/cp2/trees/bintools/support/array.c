/*
 * Copyright (c) 2009, 2014 David A. Holland.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Author nor the names of any contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#define ARRAYINLINE
#include "array.h"

void *array_realloc(void *v, size_t elemsize, unsigned num, unsigned *maxp) {
   unsigned newmax;
   void *newv;

   newmax = *maxp;
   while (num > newmax) {
      newmax = newmax ? newmax*2 : 4;
   }
   newv = dorealloc(v, *maxp * elemsize, newmax * elemsize);
   *maxp = newmax;
   return newv;
}

void array_shiftright(void *v, size_t elemsize, unsigned lp, unsigned rp) {
   unsigned char *ucp = v;
   unsigned movers;
   size_t baseoffset;

   ARRAYASSERT(lp < rp);

   movers = rp - lp;
   baseoffset = rp * elemsize;
   memmove(ucp + baseoffset + elemsize, ucp + baseoffset, movers * elemsize);
}

void array_shiftleft(void *v, size_t elemsize, unsigned lp, unsigned rp) {
   unsigned char *ucp = v;
   unsigned movers;
   size_t baseoffset;

   ARRAYASSERT(lp < rp);

   movers = rp - lp;
   baseoffset = rp * elemsize;
   memmove(ucp + baseoffset - elemsize, ucp + baseoffset, movers * elemsize);
}
