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

#ifndef BUFFER_H
#define BUFFER_H

//#include <stdint.h>
//#include <string.h>
//#include <limits.h>
//#include <assert.h>

#if !defined(SIZE_MAX) && defined(SIZE_T_MAX)
#define SIZE_MAX SIZE_T_MAX
#endif


/*
 * Extendable memory buffer.
 */

#define BUFFERS_CHECKED

#ifdef BUFFERS_CHECKED
#define BUFFERASSERT assert
#else
#define BUFFERASSERT(x) ((void)(x))
#endif

#ifndef BUFFERINLINE
#define BUFFERINLINE INLINE
#endif

struct buffer {
   char *data;
   size_t cursize, maxsize;
};

BUFFERINLINE void buffer_init(struct buffer *b);
void buffer_cleanup(struct buffer *b);
struct buffer *buffer_create(void);
void buffer_destroy(struct buffer *b);

BUFFERINLINE size_t buffer_getsize(struct buffer *b);
void buffer_setsize(struct buffer *b, size_t newsize);

BUFFERINLINE char buffer_getbyte(struct buffer *b, size_t offset);
BUFFERINLINE void buffer_setbyte(struct buffer *b, size_t offset, char byte);

BUFFERINLINE void buffer_getblob(struct buffer *b, size_t offset,
				 void *buf, size_t len);
BUFFERINLINE void buffer_setblob(struct buffer *b, size_t offset,
				 const void *bytes, size_t len);

BUFFERINLINE void buffer_addbyte(struct buffer *b, char byte);
BUFFERINLINE void buffer_addblob(struct buffer *b,
				 const void *bytes, size_t len);

BUFFERINLINE void *buffer_mapat(struct buffer *b, size_t offset, size_t len);

////////////////////////////////////////////////////////////

BUFFERINLINE void buffer_init(struct buffer *b) {
   b->data = NULL;
   b->cursize = b->maxsize = 0;
}

BUFFERINLINE size_t buffer_getsize(struct buffer *b) {
   return b->cursize;
}

BUFFERINLINE char buffer_getbyte(struct buffer *b, size_t offset) {
   BUFFERASSERT(offset < b->cursize);
   return b->data[offset];
}

BUFFERINLINE void buffer_setbyte(struct buffer *b, size_t offset, char byte) {
   BUFFERASSERT(offset < b->cursize);
   b->data[offset] = byte;
}

BUFFERINLINE void buffer_getblob(struct buffer *b, size_t offset,
				 void *buf, size_t len) {
   BUFFERASSERT(offset <= SIZE_MAX - len);
   BUFFERASSERT(offset + len <= b->cursize);
   memcpy(buf, b->data + offset, len);
}

BUFFERINLINE void buffer_setblob(struct buffer *b, size_t offset,
				 const void *bytes, size_t len) {
   BUFFERASSERT(offset <= SIZE_MAX - len);
   BUFFERASSERT(offset + len <= b->cursize);
   memcpy(b->data + offset, bytes, len);
}

BUFFERINLINE void buffer_addbyte(struct buffer *b, char byte) {
   size_t offset;

   offset = b->cursize;
   buffer_setsize(b, offset + 1);
   buffer_setbyte(b, offset, byte);
}

BUFFERINLINE void buffer_addblob(struct buffer *b,
				 const void *bytes, size_t len) {
   size_t offset;

   offset = b->cursize;
   buffer_setsize(b, offset + len);
   buffer_setblob(b, offset, bytes, len);
}

BUFFERINLINE void *buffer_mapat(struct buffer *b, size_t offset, size_t len) {
   BUFFERASSERT(offset <= SIZE_MAX - len);
   BUFFERASSERT(offset + len <= b->cursize);
   return b->data + offset;
}


#endif /* BUFFER_H */
