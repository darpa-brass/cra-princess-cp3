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
#include <string.h>
#include <assert.h>
#include "common.h"

#include "targetdefs.h"
#include "utils.h"
#include "expr.h"
#include "reloc.h"
#include "label.h"
#include "section.h"
#include "as.h"
#include "modeinfo.h"
#include "backend.h"
#include "targetmatch.h" /* for directive decls */

/*
 * Modes and directives for modes.
 */

struct modestate {
   struct modestate *prev;
   int linenum;
   bool states[NUMMODES];
};

static struct modestate *mode;

static void do_set_push(int linenum) {
   struct modestate *newmode;
   unsigned i;

   newmode = domalloc(sizeof(*newmode));
   newmode->prev = mode;
   newmode->linenum = linenum;
#if NUMMODES > 0
   for (i=0; i<NUMMODES; i++) {
      newmode->states[i] = mode->states[i];
   }
#else
   (void)i;
#endif
   mode = newmode;
}

static void do_set_pop(int linenum) {
   struct modestate *oldmode;

   oldmode = mode;
   mode = oldmode->prev;
   if (mode == NULL) {
      file_err(linenum, "Unbalanced .set pop");
   }
   dofree(oldmode, sizeof(*oldmode));
}

/* XXX this should really use indexes rather than strings */
bool modeison(const char *name) {
   unsigned i;

#if NUMMODES > 0
   for (i=0; i<NUMMODES; i++) {
      if (!strcmp(name, modeinfo[i].name)) {
	 return mode->states[i];
      }
   }
#else
   (void)i;
   (void)name;
#endif
   assert(!"modeison: invalid mode name");
   return false;
}

void directive_set_s(int linenum, struct expr *symlx) {
   struct label *syml;
   const char *sym;
   unsigned i;

   assert(symlx->x_type == EXPR_IDENT);
   syml = symlx->x_u.u_ident.sym;
   sym = label_getname(syml);

   if (!strcmp(sym, "push")) {
      do_set_push(linenum);
      return;
   }
   else if (!strcmp(sym, "pop")) {
      do_set_pop(linenum);
      return;
   }

#if NUMMODES > 0
   for (i=0; i<NUMMODES; i++) {
      if (!strcmp(sym, modeinfo[i].name)) {
	 if (modeinfo[i].setfunc) {
	    modeinfo[i].setfunc(linenum, true);
	 }
	 else {
	    mode->states[i] = true;
	 }
	 
	 return;
      }
      else if (!strncmp(sym, "no", 2) && !strcmp(sym+2, modeinfo[i].name)) {
	 if (modeinfo[i].setfunc) {
	    modeinfo[i].setfunc(linenum, false);
	 }
	 else {
	    mode->states[i] = false;
	 }
	 return;
      }
   }
#else
   (void)i;
#endif
   file_err(linenum, "Invalid .set directive");
}

void directive_unset_s(int linenum, struct expr *symlx) {
   struct label *syml;
   const char *sym;
   unsigned i;

   assert(symlx->x_type == EXPR_IDENT);
   syml = symlx->x_u.u_ident.sym;
   sym = label_getname(syml);

#if NUMMODES > 0
   for (i=0; i<NUMMODES; i++) {
      if (!strcmp(sym, modeinfo[i].name)) {
	 if (modeinfo[i].setfunc != NULL) {
	    modeinfo[i].setfunc(linenum, false);
	 }
	 else {
	    mode->states[i] = false;
	 }
	 return;
      }
      else if (!strncmp(sym, "no", 2) && !strcmp(sym+2, modeinfo[i].name)) {
	 if (modeinfo[i].setfunc != NULL) {
	    modeinfo[i].setfunc(linenum, true);
	 }
	 else {
	    mode->states[i] = true;
	 }
	 return;
      }
   }
#else
   (void)i;
   (void)sym;
#endif
   file_err(linenum, "Invalid .unset directive");
}

////////////////////////////////////////////////////////////
// global setup/shutdown

/*
 * For now this file is the only file in backend/ requiring
 * initialization.
 */

void backend_setup(void) {
   unsigned i;

   mode = domalloc(sizeof(*mode));
   mode->prev = NULL;
   mode->linenum = 0;
#if NUMMODES > 0
   for (i=0; i<NUMMODES; i++) {
      mode->states[i] = modeinfo[i].defval;
   }
#else
   (void)i;
#endif
}

void backend_shutdown(void) {
   if (mode->prev != NULL) {
      while (mode->prev->prev != NULL) {
	 file_warn(mode->prev->linenum, "Unbalanced .set push");
	 do_set_pop(0);
      }
      file_err(mode->linenum, "Unbalanced .set push");
   }
   dofree(mode, sizeof(*mode));
   mode = NULL;
}
