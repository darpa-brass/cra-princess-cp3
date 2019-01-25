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
#include "sectionops.h"
#include "as.h"
#include "modeinfo.h"
#include "targetmatch.h"

/*
 * debug info directives (currently stubbed out)
 */

/*
 * XXX 20170710 a lot of integer arguments got changed from
 * u_machlarge (which is portable though broader than necessary) to
 * sized integer types, whose sizes may be target-dependent. This
 * needs to be sorted out later.
 */

void directive_cfi_startproc_(int linenum) {
   (void)linenum;
}

void directive_cfi_endproc_(int linenum) {
   (void)linenum;
}

void directive_cfi_signal_frame_(int linenum) {
   (void)linenum;
}

void directive_cfi_def_cfa_r_n(int linenum, uint8_t reg, uint32_t val) {
   (void)linenum;
   (void)reg;
   (void)val;
}

void directive_cfi_def_cfa_n_n(int linenum, uint32_t reg, uint32_t val) {
   (void)linenum;
   (void)reg;
   (void)val;
}

void directive_cfi_offset_r_n(int linenum, uint8_t reg, uint32_t offset) {
   (void)linenum;
   (void)reg;
   (void)offset;
}

void directive_cfi_offset_n_n(int linenum, uint32_t reg, uint32_t offset) {
   (void)linenum;
   (void)reg;
   (void)offset;
}

void directive_cfi_return_column_r(int linenum, uint8_t reg) {
   (void)linenum;
   (void)reg;
}

void directive_cfi_window_save_(int linenum) {
   (void)linenum;
}

void directive_cfi_register_n_n(int linenum, uint32_t r1, uint32_t r2) {
   (void)linenum;
   (void)r1;
   (void)r2;
}

void directive_cfi_def_cfa_register_n(int linenum, uint32_t val) {
   (void)linenum;
   (void)val;
}
