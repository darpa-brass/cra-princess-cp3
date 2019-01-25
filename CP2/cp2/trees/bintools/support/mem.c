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

#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "mem.h"

void *domalloc(size_t len) {
   void *ret;

   ret = malloc(len);
   if (ret == NULL) {
      prog_err("Out of memory");
   }
   return ret;
}

void *dorealloc(void *oldptr, size_t oldlen, size_t newlen) {
   void *newptr;

   (void)oldlen;
   newptr = realloc(oldptr, newlen);
   if (newptr == NULL) {
      prog_err("Out of memory");
   }
   return newptr;
}

void dofree(void *ptr, size_t len) {
   (void)len;
   free(ptr);
}

char *dostrdup(const char *s) {
   size_t slen;
   char *r;

   slen = strlen(s);
   r = domalloc(slen + 1);
   strcpy(r, s);
   return r;
}

char *dostrndup(const char *s, size_t slen) {
   char *r;

   r = domalloc(slen + 1);
   memcpy(r, s, slen);
   r[slen] = 0;
   return r;
}

char *dostrdup2(const char *s, const char *t) {
   size_t slen, tlen;
   char *r;

   slen = strlen(s);
   tlen = strlen(t);
   r = domalloc(slen + tlen + 1);
   strcpy(r, s);
   strcpy(r+slen, t);
   return r;
}

char *dostrdup3(const char *s, const char *t, const char *u) {
   size_t slen, tlen, ulen;
   char *r;

   slen = strlen(s);
   tlen = strlen(t);
   ulen = strlen(u);
   r = domalloc(slen + tlen + ulen + 1);
   strcpy(r, s);
   strcpy(r+slen, t);
   strcpy(r+slen+tlen, u);
   return r;
}

void dostrfree(char *s) {
   dofree(s, strlen(s)+1);
}
