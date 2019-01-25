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
 * genfile: generic file interface
 *
 * A genfile can be either a stdio file or an arsubfile from arlib.
 * I/O errors cause a call to prog_err().
 */

#include <sys/types.h>
#include <sys/time.h> /* for futimes */
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "common.h"
#include "mem.h"
#include "arlib.h"
#include "genfile.h"
#include "arpvt.h"


enum genfile_types {
   GF_STDIO,
   GF_AR,
};

struct genfile {
   char *g_name;
   enum genfile_types g_type;
   union {
      FILE *u_stdio;
      struct arsubfile *u_ar;
   } g_u;
};

////////////////////////////////////////////////////////////
// error wrappers around syscall/library functions

/*
 * See explanation in arlib.c (where there's anothing copy of
 * this, which is too small to be worth setting up to share)
 */
static const char *geterrmsg(int e) {
   return (e == 0) ? "Unknown error" : strerror(e);
}

static void dofflush(const char *name, FILE *f) {
   errno = 0;
   if (fflush(f)) {
      /*
       * EBADF ordinarily means f isn't open for write.
       * For now, we'll take the risk that we might not detect if 
       * stdio gets screwed up and itself gets EBADF from something
       * else. FUTURE
       */
      if (errno == EBADF) {
	 return;
      }
      prog_err("%s: Error flushing output: %s", name, geterrmsg(errno));
   }
}

static void dofclose(const char *name, FILE *f) {
   if (fclose(f)) {
      prog_err("%s: Error closing file: %s", name, strerror(errno));
   }
}

static void dofseek(const char *name, FILE *f, off_t pos) {
   errno = 0;
   if (fseek(f, pos, SEEK_SET)) {
      prog_err("%s: fseek to offset %lld failed: %s",
	       name, (long long) pos, geterrmsg(errno));
   }
}

/* warning: use dofflush before calling this, just in case */
static void dochown(const char *name, FILE *f, uid_t uid, gid_t gid) {
   if (fchown(fileno(f), uid, gid)) {
      prog_warn("%s: Warning: fchown: %s", name, strerror(errno));
   }
}

/* warning: use dofflush before calling this, just in case */
static void dochmod(const char *name, FILE *f, mode_t mode) {
   if (fchmod(fileno(f), mode)) {
      prog_warn("%s: Warning: fchmod: %s", name, strerror(errno));
   }
}

/* warning: use dofflush before calling this */
static void doutimes(const char *name, FILE *f, time_t mtime) {
   struct timeval times[2];

   times[0].tv_sec = mtime;
   times[0].tv_usec = 0;
   times[1].tv_sec = mtime;
   times[1].tv_usec = 0;
   if (futimes(fileno(f), times)) {
      prog_err("%s: Could not set timestamp: %s", name, strerror(errno));
   }
}

/* warning: use dofflush before calling this */
static void dofstat(const char *name, FILE *f, struct stat *sb) {
   if (fstat(fileno(f), sb)<0) {
      prog_err("%s: fstat: %s", name, strerror(errno));
   }
}

/* warning: use dofflush before calling this */
static void doftruncate(const char *name, FILE *f, off_t pos) {
   if (ftruncate(fileno(f), pos)<0) {
      prog_err("%s: ftruncate: %s", name, strerror(errno));
   }
}

static size_t dofreadat(const char *name, FILE *f, off_t pos, 
			void *buf, size_t len) {
   size_t result;

   dofseek(name, f, pos);

   errno = 0;
   result = fread(buf, 1, len, f);
   if (result < len && ferror(f)) {
      prog_err("%s: Read error (%zu bytes at offset %lld): %s", 
	       name, len, (long long) pos, geterrmsg(errno));
   }

   return result;
}

static void dofwriteat(const char *name, FILE *f, off_t pos,
		       const void *buf, size_t len) {
   size_t result;

   dofseek(name, f, pos);

   errno = 0;
   result = fwrite(buf, 1, len, f);
   if (result < len) {
      prog_err("%s: Write error (%zu bytes at offset %lld): %s", 
	       name, len, (long long) pos, geterrmsg(errno));
   }
}

////////////////////////////////////////////////////////////
// core genfile ops

static struct genfile *genfile_create(const char *name, enum genfile_types t) {
   struct genfile *gf;

   gf = domalloc(sizeof(*gf));
   gf->g_name = dostrdup(name);
   gf->g_type = t;
   return gf;
}

static struct genfile *genfile_create_stdio(const char *name, FILE *f) {
   struct genfile *gf;

   gf = genfile_create(name, GF_STDIO);
   gf->g_u.u_stdio = f;
   return gf;
}

static struct genfile *genfile_create_ar(const char *name,
					 struct arsubfile *as) {
   struct genfile *gf;

   gf = genfile_create(name, GF_AR);
   gf->g_u.u_ar = as;
   return gf;
}

static void genfile_destroy(struct genfile *gf) {
   switch (gf->g_type) {
    case GF_STDIO:
     dofflush(gf->g_name, gf->g_u.u_stdio);
     dofclose(gf->g_name, gf->g_u.u_stdio);
     break;
    case GF_AR:
     arsub_close(gf->g_u.u_ar);
     break;
   }
   dostrfree(gf->g_name);
   dofree(gf, sizeof(*gf));
}

////////////////////////////////////////////////////////////
// public interface

struct genfile *genfile_getstdout(void) {
   static struct genfile *genfile_stdout = NULL;

   if (genfile_stdout==NULL) {
      genfile_stdout = genfile_create_stdio("<standard output>", stdout);
   }
   return genfile_stdout;
}

struct genfile *genfile_from_arsubfile(const char *name, struct arsubfile *as){
   return genfile_create_ar(name, as);
}

struct genfile *genfile_open(const char *name, const char *mode) {
   FILE *f;

   errno = 0;
   f = fopen(name, mode);
   if (f == NULL) {
      prog_err("%s: Cannot open: %s", name, geterrmsg(errno));
   }

   return genfile_create_stdio(name, f);
}

void genfile_close(struct genfile *g) {
   genfile_destroy(g);
}

const char *genfile_getname(struct genfile *g) {
   return g->g_name;
}

/*
 * read where encountering EOF is an error
 */
void genfile_read(struct genfile *g, off_t pos, void *buf, size_t len) {
   size_t got;

   got = genfile_readeof(g, pos, buf, len);
   if (got < len) {
      prog_err("%s: Unexpected EOF (reading %zu bytes at offset %lld)", 
	       g->g_name, len, (long long) pos);
   }
}

/*
 * read where encountering EOF is ok
 */
size_t genfile_readeof(struct genfile *g, off_t pos, void *buf, size_t len) {
   size_t result = 0;

   switch (g->g_type) {
    case GF_STDIO:
     result = dofreadat(g->g_name, g->g_u.u_stdio, pos, buf, len);
     break;
    case GF_AR:
     result = arsub_readat(g->g_u.u_ar, pos, buf, len);
     break;
   }
   return result;
}

void genfile_write(struct genfile *g, off_t pos, const void *buf, size_t len) {
   switch (g->g_type) {
    case GF_STDIO:
     dofwriteat(g->g_name, g->g_u.u_stdio, pos, buf, len);
     break;
    case GF_AR:
     arsub_writeat(g->g_u.u_ar, pos, buf, len);
     break;
   }
}

void genfile_getinfo(struct genfile *g, struct genfile_info *gi) {
   struct stat sb;

   switch (g->g_type) {
    case GF_STDIO:
     dofflush(g->g_name, g->g_u.u_stdio);
     dofstat(g->g_name, g->g_u.u_stdio, &sb);
     gi->gi_size = sb.st_size;
     gi->gi_mtime = sb.st_mtime;
     gi->gi_mode = sb.st_mode & 07777;
     gi->gi_uid = sb.st_uid;
     gi->gi_gid = sb.st_gid;
     break;
    case GF_AR:
     arsub_getinfo(g->g_u.u_ar, gi);
     break;
   }
}

void genfile_setsize(struct genfile *g, off_t pos) {
   struct stat sb;

   switch (g->g_type) {
    case GF_STDIO:
     dofflush(g->g_name, g->g_u.u_stdio);
     dofstat(g->g_name, g->g_u.u_stdio, &sb);
     if (sb.st_size != pos) {
	doftruncate(g->g_name, g->g_u.u_stdio, pos);
     }
     break;
    case GF_AR:
     arsub_setsize(g->g_u.u_ar, pos);
     break;
   }
}

void genfile_touch(struct genfile *g, time_t mtime) {
   switch (g->g_type) {
    case GF_STDIO:
     dofflush(g->g_name, g->g_u.u_stdio);
     doutimes(g->g_name, g->g_u.u_stdio, mtime);
     break;
    case GF_AR:
     arsub_touch(g->g_u.u_ar, mtime);
     break;
   }
}

void genfile_chmod(struct genfile *g, mode_t mode, uid_t uid, gid_t gid) {
   struct stat sb;

   switch (g->g_type) {
    case GF_STDIO:
     dofflush(g->g_name, g->g_u.u_stdio);
     dofstat(g->g_name, g->g_u.u_stdio, &sb);
     if (sb.st_uid != uid || sb.st_gid != gid) {
	dochown(g->g_name, g->g_u.u_stdio, uid, gid);
     }
     if ((sb.st_mode & 07777) != mode) {
	dochmod(g->g_name, g->g_u.u_stdio, mode);
     }
     break;
    case GF_AR:
     arsub_chmod(g->g_u.u_ar, mode, uid, gid);
     break;
   }
}

