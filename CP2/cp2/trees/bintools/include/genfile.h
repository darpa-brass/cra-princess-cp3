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

#ifndef GENFILE_H
#define GENFILE_H


struct genfile;  /* opaque */

struct genfile_info {
   off_t gi_size;
   time_t gi_mtime;
   mode_t gi_mode;
   uid_t gi_uid;
   gid_t gi_gid;
};

struct genfile *genfile_getstdout(void);
struct genfile *genfile_open(const char *name, const char *mode);
void genfile_close(struct genfile *g);

const char *genfile_getname(struct genfile *g);
void genfile_read(struct genfile *g, off_t pos, void *buf, size_t len);
size_t genfile_readeof(struct genfile *g, off_t pos, void *buf, size_t len);
void genfile_write(struct genfile *g, off_t pos, const void *buf, size_t len);
void genfile_getinfo(struct genfile *g, struct genfile_info *gi);
void genfile_setsize(struct genfile *g, off_t pos);
void genfile_touch(struct genfile *g, time_t mtime);
void genfile_chmod(struct genfile *g, mode_t mode, uid_t uid, gid_t gid);


#endif /* GENFILE_H */
