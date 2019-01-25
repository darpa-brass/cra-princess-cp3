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
 * arlib: library for manipulating ar files
 */

/*
 * MAJOR XXX - neither dispose/insert_file_region updates the offsets
 * in the headers!
 */

/*
 * The ar format we use is as follows. (This is allegedly the BSD format.)
 *
 * The file begins with the string "!<arch>\n".
 * This is followed by files, each of which has a 60-byte header.
 * The header is as follows:
 *    filename      16 bytes
 *    file mtime    12 bytes  (printed in decimal)
 *    owner uid     6 bytes   (printed in decimal)
 *    owner gid     6 bytes   (printed in decimal)
 *    file mode     8 bytes   (printed in octal)
 *    file size     10 bytes  (printed in decimal)
 *    cookie        2 bytes   (the characters "`\n")
 *
 * All padding/separation is with spaces. No additional separators occur,
 * so the fields may ram into each other.
 *
 * If the name is too long, or contains spaces, the string "#1/SIZE"
 * appears as the name, where SIZE is the length of the filename. The
 * filename is then inserted between the header and the file data.
 *
 * If the size of the file (plus the size of the filename, if necessary)
 * is odd, a single padding byte is inserted before the next header, to
 * align the size to a 16-bit boundary. The padding is not reflected in
 * the header.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h> /* for SIZE_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include "common.h"

#if !defined(SIZE_MAX) && defined(SIZE_T_MAX)
#define SIZE_MAX SIZE_T_MAX
#endif

#include "array.h"
#include "arlib.h"
#include "genfile.h"
#include "arpvt.h"

#define AR_MAGIC        "!<arch>\n"
#define AR_MAGIC_SIZE   8

/* in-memory per-file data */
struct arinfo {
   off_t hpos;		/* location in file of ar header */
   off_t dpos;		/* location in file of actual data */
   char *name;		/* name of this file */
   off_t size;		/* length of this file */
   time_t mtime;	/* modification time */
   uid_t uid;		/* file attributes */
   gid_t gid;
   mode_t mode;
};
DECLARRAY(arinfo, static UNUSED inline);
DEFARRAY(arinfo, static UNUSED inline);

/* whole .a file */
struct arfile {
   FILE *f;
   char *name;
   unsigned opencount;
   struct arinfoarray files;
   struct arinfo *indexfile;
};

/* open subfile */
struct arsubfile {
   struct arfile *container;
   struct arinfo *info;
};

/* in-file header */
struct arheader {
   char filename[16];
   char mtime[12];
   char uid[6];
   char gid[6];
   char mode[8];
   char size[10];
   char cookie[2];
};

////////////////////////////////////////////////////////////
// arinfo ops

static struct arinfo *arinfo_create(off_t size, time_t mtime,
				    uid_t uid, gid_t gid, mode_t mode) {
   struct arinfo *ai;

   ai = domalloc(sizeof(*ai));
   ai->hpos = 0;
   ai->dpos = 0;
   ai->name = NULL;
   ai->size = size;
   ai->mtime = mtime;
   ai->uid = uid;
   ai->gid = gid;
   ai->mode = mode;
   return ai;
}

static void arinfo_destroy(struct arinfo *ai) {
   if (ai->name != NULL) {
      dostrfree(ai->name);
   }
   dofree(ai, sizeof(*ai));
}

////////////////////////////////////////////////////////////
// arfile ops

static struct arfile *arfile_create(FILE *f, const char *name) {
   struct arfile *af;

   af = domalloc(sizeof(*af));
   af->f = f;
   af->opencount = 0;
   af->name = dostrdup(name);
   arinfoarray_init(&af->files);
   af->indexfile = NULL;
   return af;
}

static void arfile_destroy(struct arfile *af) {
   unsigned i, num;
   struct arinfo *ai;

   num = arinfoarray_num(&af->files);
   for (i=0; i<num; i++) {
      ai = arinfoarray_get(&af->files, i);
      arinfo_destroy(ai);
   }
   arinfoarray_setsize(&af->files, 0);
   arinfoarray_cleanup(&af->files);
   if (af->indexfile != NULL) {
      arinfo_destroy(af->indexfile);
   }

   fclose(af->f);
   dostrfree(af->name);
   dofree(af, sizeof(*af));
}

////////////////////////////////////////////////////////////
// arsubfile ops

static struct arsubfile *arsubfile_create(struct arfile *af,
					  struct arinfo *ai) {
   struct arsubfile *as;

   as = domalloc(sizeof(*as));
   as->container = af;
   as->info = ai;
   as->container->opencount++;
   assert(as->container->opencount > 0);
   return as;
}

static void arsubfile_destroy(struct arsubfile *as) {
   assert(as->container->opencount > 0);
   as->container->opencount--;
   dofree(as, sizeof(*as));
}

////////////////////////////////////////////////////////////
// wrappers around library/system calls

/*
 * Workaround for the fact that some stdio implementations set
 * errno (which provides useful information) and others don't.
 *
 * Usage is:
 *    errno = 0;
 *    op();
 *    if (failed) {
 *       errmsg = geterrmsg(errno);
 *       prog_err("blah: %s", errmsg);
 *    }
 */
static const char *geterrmsg(int e) {
   return (e == 0) ? "Unknown error" : strerror(e);
}

static void ar_seek(struct arfile *af, off_t pos) {
   const char *errmsg;

   errno = 0;
   if (fseek(af->f, pos, SEEK_SET)) {
      errmsg = geterrmsg(errno);
      prog_err("%s: fseek to offset %lld failed: %s",
	       af->name, (long long) pos, errmsg);
   }
}

static void ar_flush(struct arfile *af) {
   const char *errmsg;

   errno = 0;
   if (fflush(af->f)) {
      errmsg = geterrmsg(errno);
      prog_err("%s: Error flushing output: %s", af->name, errmsg);
   }
}

static void ar_seekeof(struct arfile *af) {
   const char *errmsg;

   errno = 0;
   if (fseek(af->f, 0, SEEK_END)) {
      errmsg = geterrmsg(errno);
      prog_err("%s: fseek to EOF failed: %s", af->name, errmsg);
   }
}

static off_t ar_tell(struct arfile *af) {
   const char *errmsg;
   off_t pos;

   errno = 0;
   pos = ftell(af->f);
   if (pos == -1) {
      errmsg = geterrmsg(errno);
      prog_err("%s: ftell failed: %s", af->name, errmsg);
   }
   return pos;
}

/*
 * Note: because this may (does) use ar_seekeof to find the length,
 * the caller must seek explicitly afterwards. (We could save and
 * restore the position but in the cases where it's actually used,
 * this is silly.)
 */
static off_t ar_getsize(struct arfile *af) {
   ar_seekeof(af);
   return ar_tell(af);
}

static size_t ar_read(struct arfile *af, void *ptr, size_t len) {
   size_t result;
   const char *errmsg;

   errno = 0;
   result = fread(ptr, 1, len, af->f);
   if (result < len && ferror(af->f)) {
      errmsg = geterrmsg(errno);
      prog_err("%s: Read error: %s", af->name, errmsg);
   }
   return result;
}

static void ar_write(struct arfile *af, const void *ptr, size_t len) {
   size_t result;
   const char *errmsg;

   errno = 0;
   result = fwrite(ptr, 1, len, af->f);
   if (result < len || ferror(af->f)) {
      errmsg = geterrmsg(errno);
      prog_err("%s: Write error: %s", af->name, errmsg);
   }
}

static void ar_dispose_file_region(struct arfile *af,
				   off_t startpos, off_t endpos)
{
   char buf[4096];
   size_t len;
   off_t rpos, wpos;

   assert(endpos > startpos);
   assert(startpos >= 0);

   rpos = endpos;
   wpos = startpos;
   while (1) {
      ar_seek(af, rpos);
      len = ar_read(af, buf, sizeof(buf));
      if (len == 0) {
	 break;
      }
      ar_seek(af, wpos);
      ar_write(af, buf, len);
      rpos += len;
      wpos += len;
   }
   ar_flush(af);

   if (ftruncate(fileno(af->f), wpos) < 0) {
      prog_err("%s: ftruncate failed: %s", af->name, strerror(errno));
   }
}

static void ar_insert_file_region(struct arfile *af,
				  off_t startpos, off_t endpos)
{
   off_t eofpos, pos, amt, blockstart;
   size_t blocklen, result;
   char buf[4096];

   assert(endpos > startpos);
   assert(startpos >= 0);

   eofpos = ar_getsize(af);
   pos = eofpos;
   amt = endpos - startpos;

   while (pos > startpos) {
      blockstart = pos - sizeof(buf);
      if (blockstart < startpos) {
	 blockstart = startpos;
      }
      /* this cannot overflow blocklen */
      blocklen = pos-blockstart;

      ar_seek(af, blockstart);
      result = ar_read(af, buf, blocklen);
      if (result != blocklen) {
	 prog_err("%s: Hit unexpected EOF while inserting space", af->name);
      }
      ar_seek(af, blockstart + amt);
      ar_write(af, buf, blocklen);

      pos = blockstart;
   }
}

////////////////////////////////////////////////////////////

static void ar_writeheader(struct arfile *af, struct arinfo *ai) {
   struct arheader ah;
   char tmp[32];
   bool writename;
   size_t namelen;

   /* assume already in the right place in the file */

   /* make sure we aren't the victim of unexpected structure padding */
   COMPILE_ASSERT(sizeof(struct arheader) == 60);

   /* XXX these need truncation checks when copying into the header */

   snprintf(tmp, sizeof(tmp), "%-12lld", (long long) ai->mtime);
   strncpy(ah.mtime, tmp, sizeof(ah.mtime));

   snprintf(tmp, sizeof(tmp), "%-6u", (unsigned) ai->uid);
   strncpy(ah.uid, tmp, sizeof(ah.uid));

   snprintf(tmp, sizeof(tmp), "%-6u", (unsigned) ai->gid);
   strncpy(ah.gid, tmp, sizeof(ah.gid));

   snprintf(tmp, sizeof(tmp), "%-8o", (unsigned) ai->mode);
   strncpy(ah.mode, tmp, sizeof(ah.mode));

   /* ai->size is off_t, not size_t, so print as long long */
   snprintf(tmp, sizeof(tmp), "%-10lld", (long long) ai->size);
   strncpy(ah.size, tmp, sizeof(ah.size));

   ah.cookie[0] = '`';
   ah.cookie[1] = '\n';

   namelen = strlen(ai->name);
   if (namelen > 16 || strchr(ai->name, ' ')) {
      writename = true;
      snprintf(tmp, sizeof(tmp), "#1/%-13zu", namelen);
   }
   else {
      writename = false;
      snprintf(tmp, sizeof(tmp), "%-16s", ai->name);
   }
   strncpy(ah.filename, tmp, sizeof(ah.filename));

   ar_write(af, &ah, sizeof(ah));
   if (writename) {
      ar_write(af, ai->name, namelen);
   }
}

static void ar_despace(char *s) {
   char *t;

   t = strchr(s, ' ');
   if (t) {
      *t = 0;
   }
}

/*
 * XXX: does this need to support negative numbers? And should it
 * explicitly know which types are signed and handle them differently?
 */

#define DECLARE_CONVERT(type, maxval) \
  static bool ar_convert_##type(const char *s, size_t len, int base,	\
				type *ret) {				\
     size_t i;								\
     type n, max = maxval;						\
     int digit;								\
									\
     assert(base <= 10);						\
									\
     n = 0;								\
     for (i=0; i<len; i++) {						\
	if (!isdigit((unsigned char)s[i])) {				\
	   break;							\
	}								\
	digit = s[i]-'0';						\
	if (digit >= base) {						\
	   return false;						\
	}								\
	if (n >= (max - digit)/base) {					\
	   return false;						\
	}								\
	n = n*base + digit;						\
     }									\
     *ret = n;								\
     return true;							\
  }

/* Uuuuuugh why can't we just have signed overflow that works? */
#define SIGNED_TYPE_MAX(t) (				\
	sizeof(t) == sizeof(int) ? INT_MAX :		\
	sizeof(t) == sizeof(long) ? LONG_MAX :		\
	sizeof(t) == sizeof(long long) ? LLONG_MAX :	\
	sizeof(struct { unsigned : (			\
		sizeof(t) == sizeof(int) ||		\
		sizeof(t) == sizeof(long) ||		\
		sizeof(t) == sizeof(long long)) 	\
			? 1 : -1; }))

#define UNSIGNED_TYPE_MAX(t) ((t)-1)

#define IS_UNSIGNED_TYPE(t) (((t)1)/((t)-1) == 0)
#define TYPE_MAX(t) \
   (IS_UNSIGNED_TYPE(t) ? UNSIGNED_TYPE_MAX(t) : SIGNED_TYPE_MAX(t))

/* sigh, linux... */
#ifndef UID_MAX
#define UID_MAX TYPE_MAX(uid_t)
#endif
#ifndef GID_MAX
#define GID_MAX TYPE_MAX(gid_t)
#endif

DECLARE_CONVERT(size_t, SIZE_MAX);
DECLARE_CONVERT(off_t, SIGNED_TYPE_MAX(off_t));
DECLARE_CONVERT(time_t, SIGNED_TYPE_MAX(off_t));
DECLARE_CONVERT(uid_t, UID_MAX);
DECLARE_CONVERT(gid_t, GID_MAX);
DECLARE_CONVERT(mode_t, UINT_MAX);


static void ar_load(struct arfile *af) {
   struct arheader header;
   struct arinfo *ai;
   off_t eof;
   unsigned fcount;

   off_t hpos;
   time_t mtime;
   off_t size;
   uid_t uid;
   gid_t gid;
   mode_t mode;
   size_t namesize;
   char name[sizeof(header.filename)+1];
   bool isindex, ignore;
   char *s;

   eof = ar_getsize(af);

   /* skip over magic string */
   ar_seek(af, AR_MAGIC_SIZE);

   fcount = 0;
   while (ar_tell(af) < eof) {
      isindex = false;
      ignore = false;

      fcount++;
      hpos = ar_tell(af);

      if (hpos % 2) {
	 hpos++;
	 ar_seek(af, hpos);
      }

      ar_read(af, &header, sizeof(header));

      if (header.cookie[0] != '`' || header.cookie[1] != '\n') {
	 prog_err("%s: Invalid ar header on file #%u", af->name, fcount);
      }

      if (!ar_convert_time_t(header.mtime, sizeof(header.mtime), 10, &mtime)) {
	 prog_err("%s: Time of file #%u is invalid", af->name, fcount);
      }
      if (!ar_convert_off_t(header.size, sizeof(header.size), 10, &size)) {
	 prog_err("%s: Size of file #%u is invalid", af->name, fcount);
      }
      if (!ar_convert_uid_t(header.uid, sizeof(header.uid), 10, &uid)) {
	 prog_err("%s: User ID of file #%u is invalid", af->name, fcount);
      }
      if (!ar_convert_gid_t(header.gid, sizeof(header.gid), 10, &gid)) {
	 prog_err("%s: Group ID of file #%u is invalid", af->name, fcount);
      }
      if (!ar_convert_mode_t(header.mode, sizeof(header.mode), 8, &mode)) {
	 prog_err("%s: File mode of file #%u is invalid", af->name, fcount);
      }

      ai = arinfo_create(size, mtime, uid, gid, mode);
      ai->hpos = hpos;

      if (memchr(header.filename, 0, sizeof(header.filename)) != NULL) {
	 prog_err("%s: File #%u has nulls in its name", af->name, fcount);
      }

      /* extract filename */
      if (!strncmp(header.filename, "#1/", 3)) {
	 if (!ar_convert_size_t(header.filename+3,
				sizeof(header.filename)-3, 10, &namesize)) {
	    prog_err("%s: Name length of file #%u is invalid",
		     af->name, fcount);
	 }
	 if (namesize==0) {
	    ai->name = dostrdup("");
	 }
	 else if (namesize > 1000000) {
	    prog_err("%s: Unreasonably long filename on file #%u",
		     af->name, fcount);
	 }
	 else {
	    ai->name = domalloc(namesize+1);
	    ar_read(af, ai->name, namesize);
	    ai->name[namesize] = 0;
	 }
      }
      else if ((s = memchr(header.filename, '/',
			   sizeof(header.filename))) != NULL) {
	 /* svr4 name */
	 *s = 0;
	 if (header.filename[0] == 0 && header.filename[1] == ' ') {
	    /* this is the svr4-style symbol index */
	    isindex = true;
	    ai->name = NULL;
	 }
	 if (header.filename[0] == 0 && header.filename[1] == '/') {
	    /* this is a svr4-style string table; for now ignore it */
	    /* XXX */
	    assert(!isindex);
	    ignore = true;
	    ai->name = NULL;
	 }
	 else if (header.filename[0] == 0) {
	    /* the rest of the name is a svr4-style stringtable index */
	    /* but ignore that, XXX */
	    /* (but we must restore the / so the name we use is unique) */
	    header.filename[0] = '/';
	    s = memchr(header.filename, ' ', sizeof(header.filename));
	    if (s) {
	       *s = 0;
	    }
	    else {
	       header.filename[sizeof(header.filename)-1] = 0;
	    }
	    strcpy(name, header.filename);
	    ai->name = dostrdup(name);
	 }
	 else {
	    strcpy(name, header.filename);
	    ai->name = dostrdup(name);
	 }
      }
      else {
	 strncpy(name, header.filename, sizeof(name) - 1);
	 name[sizeof(name) - 1] = 0;
	 ar_despace(name);
	 if (!strcmp(name, "__.SYMDEF")) {
	    /* this is the bsd-style symbol index */
	    isindex = true;
	    ai->name = NULL;
	 }
	 else {
	    ai->name = dostrdup(name);
	 }
      }
      ai->dpos = ar_tell(af);

      if (ignore) {
	 /* nothing */
      }
      else if (isindex) {
	 if (af->indexfile != NULL) {
	    prog_err("%s: Multiple ranlib index files", af->name);
	 }
	 af->indexfile = ai;
      }
      else {
	 arinfoarray_add(&af->files, ai);
      }

      ar_seek(af, ai->dpos + ai->size);

      if (ignore) {
	 /* do not do this until after the seek call... */
	 arinfo_destroy(ai);
      }
   }
}

struct arfile *ar_open(const char *name, const char *mode, bool isnew) {
   FILE *f;
   struct arfile *af;
   char tmp[AR_MAGIC_SIZE];

   f = fopen(name, mode);
   if (!f) {
      return NULL;
   }

   af = arfile_create(f, name);

   if (isnew) {
      ar_seek(af, 0);
      ar_write(af, AR_MAGIC, AR_MAGIC_SIZE);
   }

   ar_seek(af, 0);
   if (ar_read(af, tmp, AR_MAGIC_SIZE) != AR_MAGIC_SIZE) {
      arfile_destroy(af);
      return NULL;
   }
   if (memcmp(tmp, AR_MAGIC, sizeof(tmp))) {
      /* not ar file */
      arfile_destroy(af);
      return NULL;
   }

   ar_load(af);
   return af;
}

void ar_close(struct arfile *af) {
   if (af->opencount > 0) {
      prog_err("Internal error: %u subfiles still open in %s",
	       af->opencount, af->name);
   }
   arfile_destroy(af);
}

unsigned ar_getnumfiles(struct arfile *af) {
   return arinfoarray_num(&af->files);
}

const char *ar_getname(struct arfile *af, unsigned whichfile) {
   return arinfoarray_get(&af->files, whichfile)->name;
}

////////////////////////////////////////////////////////////

#define NO_FILE ((unsigned)-1)

static unsigned ar_findfile(struct arfile *af, const char *name) {
   struct arinfo *ai;
   unsigned i, num;

   num = arinfoarray_num(&af->files);
   for (i=0; i<num; i++) {
      ai = arinfoarray_get(&af->files, i);
      if (!strcmp(ai->name, name)) {
	 return i;
      }
   }
   return NO_FILE;
}

void ar_remove(struct arfile *af, const char *name) {
   struct arinfo *ai;
   unsigned ix;

   ix = ar_findfile(af, name);
   if (ix == NO_FILE) {
      prog_err("%s: No member %s in archive", af->name, name);
   }

   ai = arinfoarray_get(&af->files, ix);
   ar_dispose_file_region(af, ai->hpos, ai->dpos + ai->size);

   arinfoarray_remove(&af->files, ix);
}

////////////////////////////////////////////////////////////

struct genfile *ar_opensubfile(struct arfile *af, const char *name) {
   struct arsubfile *as;
   unsigned ix;

   ix = ar_findfile(af, name);
   if (ix == NO_FILE) {
      return NULL;
   }

   as = arsubfile_create(af, arinfoarray_get(&af->files, ix));
   return genfile_from_arsubfile(name, as);
}

struct genfile *ar_newsubfile(struct arfile *af, const char *name,
			      off_t size, time_t mtime, mode_t mode,
			      uid_t uid, gid_t gid)
{
   struct arinfo *ai;
   struct arsubfile *as;
   off_t endpos;
   unsigned ix;

   ix = ar_findfile(af, name);
   if (ix != NO_FILE) {
      prog_err("%s: %s already exists in archive", af->name, name);
   }

   ar_seekeof(af);

   ai = arinfo_create(size, mtime, uid, gid, mode);
   ai->hpos = ar_tell(af);
   ai->name = dostrdup(name);
   ar_writeheader(af, ai);
   ai->dpos = ar_tell(af);
   endpos = ai->dpos + ai->size;
   if (endpos % 2) endpos++;
   ar_seek(af, endpos-1);

   /* expand the underlying file */
   ar_write(af, " ", 1);

   arinfoarray_add(&af->files, ai);

   as = arsubfile_create(af, ai);
   return genfile_from_arsubfile(name, as);
}

void arsub_setsize(struct arsubfile *as, off_t size) {
   struct arfile *af;
   struct arinfo *ai;

   af = as->container;
   ai = as->info;

   if (size < ai->size) {
      ar_dispose_file_region(af, ai->dpos + size, ai->dpos + ai->size);
   }
   else if (size > ai->size) {
      ar_insert_file_region(af, ai->dpos + ai->size, ai->dpos + size);
   }
   ai->size = size;

   ar_seek(af, ai->hpos);
   ar_writeheader(af, ai);
   assert(ai->dpos == ar_tell(af));
}

void arsub_touch(struct arsubfile *as, time_t mtime) {
   struct arfile *af;
   struct arinfo *ai;

   af = as->container;
   ai = as->info;

   ai->mtime = mtime;

   ar_seek(af, ai->hpos);
   ar_writeheader(af, ai);
   assert(ai->dpos == ar_tell(af));
}

void arsub_chmod(struct arsubfile *as, mode_t mode, uid_t uid, gid_t gid) {
   struct arfile *af;
   struct arinfo *ai;

   af = as->container;
   ai = as->info;

   ai->uid = uid;
   ai->gid = gid;
   ai->mode = mode;

   ar_seek(af, ai->hpos);
   ar_writeheader(af, ai);
   assert(ai->dpos == ar_tell(af));
}

void arsub_close(struct arsubfile *as) {
   arsubfile_destroy(as);
}

size_t arsub_readat(struct arsubfile *as, off_t pos, void *buf, size_t len) {
   struct arfile *af;
   struct arinfo *ai;
   off_t maxlen;

   af = as->container;
   ai = as->info;

   if (pos >= ai->size) {
      /* EOF */
      return 0;
   }

   /*
    * If off_t is larger than size_t, and we have a very large file,
    * ai_size - pos might be greater than SIZE_MAX, so we should
    * cast len to off_t to widen it before comparing. However, if
    * off_t is smaller than size_t (or the same size, as off_t is
    * signed) this might truncate len or make it negative. To deal
    * with this, write two versions of the comparison conditioned on
    * the type sizes and rely on the compiler to sort it out. Note
    * that we know that maxlen is positive because of the previous
    * check above, so even if the sizes are the same casting maxlen
    * to size_t will not blow up.
    */
   maxlen = ai->size - pos;
   if ((sizeof(off_t) > sizeof(size_t) && (off_t)len > maxlen) ||
       (sizeof(off_t) <= sizeof(size_t) && len > (size_t)maxlen)) {
      len = maxlen;
   }

   ar_seek(af, ai->dpos + pos);
   return ar_read(af, buf, len);
}

void arsub_writeat(struct arsubfile *as, off_t pos, const void *buf,
		   size_t len)
{
   struct arfile *af;
   struct arinfo *ai;
   off_t maxlen;

   af = as->container;
   ai = as->info;

   if (pos >= ai->size) {
      prog_err("%s (in %s): Write at %ld is past EOF", as->info->name,
	       af->name, (long) pos);
   }

   /*
    * See note above.
    */
   maxlen = ai->size - pos;
   if ((sizeof(off_t) > sizeof(size_t) && (off_t)len > maxlen) ||
       (sizeof(off_t) <= sizeof(size_t) && len > (size_t)maxlen)) {
      prog_err("%s (in %s): Write of %zu bytes at %lld goes past EOF",
	       as->info->name, af->name, len, (long long) pos);
   }

   ar_seek(af, ai->dpos + pos);
   ar_write(af, buf, len);
}

void arsub_getinfo(const struct arsubfile *as, struct genfile_info *gi) {
   gi->gi_size = as->info->size;
   gi->gi_mtime = as->info->mtime;
   gi->gi_mode = as->info->mode;
   gi->gi_uid = as->info->uid;
   gi->gi_gid = as->info->gid;
}

////////////////////////////////////////////////////////////

char *ar_mkreportname(struct arfile *arf, const char *subname) {
   size_t len;
   char *s;

   len = strlen(arf->name) + strlen(subname) + 3;

   s = domalloc(len);
   strcpy(s, arf->name);
   strcat(s, "(");
   strcat(s, subname);
   strcat(s, ")");
   return s;
}
