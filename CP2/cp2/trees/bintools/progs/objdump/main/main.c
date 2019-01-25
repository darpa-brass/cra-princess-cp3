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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "common.h"
#include "version.h"
#include "host/installdirs.h"
#include "array.h"

#include "dump.h"


static unsigned info;
static unsigned present;

////////////////////////////////////////////////////////////

static void set_target(const char *name) {
   // XXX
   (void)name;
   fprintf(stderr, "Unsupported option\n");
}

static void set_arch(const char *name) {
   // XXX
   (void)name;
   fprintf(stderr, "Unsupported option\n");
}

static void set_big_endian(void) {
   // XXX
   fprintf(stderr, "Unsupported option\n");
}

static void set_little_endian(void) {
   // XXX
   fprintf(stderr, "Unsupported option\n");
}

////////////////////////////////////////////////////////////

static void add_disassembler_opt(const char *opt) {
   // XXX
   (void)opt;
   fprintf(stderr, "Unsupported option\n");
}

static void add_section_list(const char *stuff) {
   // XXX
   (void)stuff;
   fprintf(stderr, "Unsupported option\n");
}

static void set_start_address(const char *addr) {
   // XXX
   (void)addr;
   fprintf(stderr, "Unsupported option\n");
}

static void set_stop_address(const char *addr) {
   // XXX
   (void)addr;
   fprintf(stderr, "Unsupported option\n");
}

static void set_address_offset(const char *offset) {
   // XXX
   (void)offset;
   fprintf(stderr, "Unsupported option\n");
}

////////////////////////////////////////////////////////////

static void version(void) {
   fprintf(stderr, "bintools objdump (%sobjdump) version %s\n", INSTALLTARGET,
	   VERSION);
}

static void objdump_info(void) {
   version();
   // XXX
   fprintf(stderr, "No formats info available yet (this should be fixed)\n");
}

////////////////////////////////////////////////////////////

static void objdump_help_modes(void) {
   printf("Modes (at least one is required):\n");
   printf("   -a, --archive-headers        Dump ar(1) [library] headers\n");
   printf("   -f, --file-headers           Dump primary file headers\n");
   printf("   -p, --private-headers        Dump format-specific headers\n");
   printf("   -h, --[section-]headers      Dump section headers\n");
   printf("   -x, --all-headers            Dump all headers\n");
   printf("   -d, --disassemble            Disassemble code sections\n");
   printf("   -D, --disassemble-all        Disassemble all sections\n");
   printf("   -S, --source                 Disassemble showing source code\n");
   printf("   -f, --full-contents          Dump contents of all sections\n");
   printf("   -g, --debugging              Dump debug info\n");
   printf("   -G, --stabs                  Dump debug info in raw form\n");
   printf("   -t, --syms                   Dump symbol table\n");
   printf("   -T, --dynamic-syms           Dump dynamic linker symbols\n");
   printf("   -r, --reloc                  Dump relocation records\n");
   printf("   -R, --dynamic-reloc          Dump dynamic linker relocations\n");
   printf("   -i, --info                   List supported targets and exit\n");
   printf("   -V, --version                Print version info and exit\n");
   printf("   -H, --help                   Print help/usage info and exit\n");
   printf("       --help-modes             Print list of modes and exit\n");
   printf("       --help-options           Print list of options and exit\n");
}

static void objdump_help_options(void) {
   printf("Disassembly options:\n");
   printf("   -l, --line-numbers           Add line numbers\n");
   printf("   -z, --disassemble-zeros      Don't skip blocks of zeros\n");
   printf("       --prefix-addresses       Alternate symbol/address format\n");
   printf("       --show-raw-insn          Show hexdump of instructions\n");
   printf("       --no-show-raw-insn       ...or don't.\n");
   printf("       --file-start-context     ??? (Does nothing for now)\n");
   printf("\n");
   printf("General options:\n");
   printf("   -b NAME, --target=NAME       Select target for operation\n");
   printf("   -m NAME, --architecture=NAME Select processor architecture\n");
   printf("   -j NAME, --section=NAME      Dump only listed section(s)\n");
   printf("   -M OPT,\n");
   printf("     --disassembler-options=OPT Additional disassembler options\n");
   printf("   -EB, --endian=big            Force big-endian mode\n");
   printf("   -EL, --endian=little         Force little-endian mode\n");
   printf("   -w, --wide                   Format for >80 columns\n");
   printf("       --start-address=ADDR     Start dumping at address ADDR\n");
   printf("       --stop-address=ADDR      Stop dumping at address ADDR\n");
   printf("       --adjust-vma=NUM         Add NUM when printing addresses\n");
}

static void objdump_help(void) {
   printf("Usage: %sobjdump [-modes|options] file...\n", INSTALLTARGET);
   printf("   At least one mode and one file are required.\n");
   printf("   Use --help-modes for a complete list of modes.\n");
   printf("   Use --help-options for a complete list of options.\n");
   printf("\n");
   printf("Common modes:\n");
   printf("   -h, --section-headers        Dump section headers\n");
   printf("   -d, --disassemble            Disassemble code sections\n");
   printf("   -s, --full-contents          Dump all section data\n");
   printf("   -i, --info                   List supported targets and exit\n");
   printf("   -V, --version                Print version info and exit\n");
   printf("\n");
   printf("Common options:\n");
   printf("   -C, --demangle               Demangle C++ symbols\n");
   printf("   -w, --wide                   Format for >80 columns\n");
   printf("       --start-address=ADDR     Start dumping at address ADDR\n");
   printf("       --stop-address=ADDR      Stop dumping at address ADDR\n");
}

////////////////////////////////////////////////////////////

struct args {
   int argc;
   char **argv;
   int ind;		/* current index of argv */
   int chrind;		/* current index of argv[ind] */
};

static const char *getoptarg(struct args *a) {
   const char *retval;

   if (a->argv[a->ind][a->chrind+1]==0) {
      if (a->argv[a->ind+1]==NULL) {
	 prog_err("Option -%c requires an argument", 
		  a->argv[a->ind][a->chrind]);
      }
      a->ind++;
      retval =  a->argv[a->ind];
   }
   else {
      retval = a->argv[a->ind] + a->chrind + 1;
   }

   /* either way, set chrind so as to terminate the loop on characters. */
   a->chrind = strlen(a->argv[a->ind])-1;

   return retval;
}

////////////////////////////////////////////////////////////

struct option {
   int shortform;
   const char *longform;
   unsigned infoflags;
   unsigned presentflags;
};

static const struct option simpleoptions[] = {
   /* modes - one is required */
   { 'a', "--archive-headers",	  INFO_HEADERS_AR,      0 },
   { 'f', "--file-headers",	  INFO_HEADERS_O,       0 },
   { 'p', "--private-headers",	  INFO_HEADERS_BF,      0 },
   { 'h', "--section-headers",	  INFO_HEADERS_SECTION, 0 },
   { 'h', "--headers",		  INFO_HEADERS_SECTION, 0 },
   { 'x', "--all-headers",	  INFO_HEADERS_ALL,     0 },
   { 'd', "--disassemble",	  INFO_CONTENTS_CODE,   PR_DIS_CODE, },
   { 'D', "--disassemble-all", 	  INFO_CONTENTS_ALL,    PR_DIS_ALL},
   { 'S', "--source",		  INFO_CONTENTS_CODE,   PR_DIS_SOURCE },
   { 's', "--full-contents",	  INFO_CONTENTS_ALL,    0 },
   { 'g', "--debugging", 	  INFO_DEBUG,           0 },
   { 'G', "--stabs", 		  INFO_DEBUG_RAW,       0 },
   { 't', "--syms",		  INFO_SYMS,            0 },
   { 'T', "--dynamic-syms",	  INFO_DYNSYMS,         0 },
   { 'r', "--reloc",		  INFO_RELOCS,          0 },
   { 'R', "--dynamic-reloc",      INFO_DYNRELOCS,       0 },

   /* options */
   { 'l', "--line-numbers",       0,                    PR_DIS_LINENUMBERS },
   { 'w', "--wide",               0,                    PR_WIDE },
   { 'z', "--disassemble-zeros",  0,                    PR_DIS_ZEROS },
   { 0,   "--prefix-addresses",   0,                    PR_DIS_PREFIXADDRS },
   { 0,   "--show-raw-insn",      0,                    PR_DIS_RAWINSN },
   { 0,   "--file-start-context", 0,                    PR_FILESTARTCTX },

   { -1, NULL, 0, 0 }
};

static void other_long_option(const char *option) {
   if (!strcmp(option, "--no-show-raw-insn")) {
      present &= ~(unsigned)PR_DIS_RAWINSN;
   }
   else if (!strcmp(option, "--version")) {
      version();
      exit(0);
   }
   else if (!strcmp(option, "--info")) {
      objdump_info();
      exit(0);
   }
   else if (!strcmp(option, "--help")) {
      objdump_help();
      exit(0);
   }
   else if (!strcmp(option, "--help-modes")) {
      objdump_help_modes();
      exit(0);
   }
   else if (!strcmp(option, "--help-options")) {
      objdump_help_options();
      exit(0);
   }
   else if (!strncmp(option, "--target=", 9)) {
      set_target(option+9);
   }
   else if (!strncmp(option, "--architecture=", 15)) {
      set_arch(option+15);
   }
   else if (!strncmp(option, "--section=", 10)) {
      add_section_list(option+10);
   }
   else if (!strncmp(option, "--disassembler-options=", 23)) {
      add_disassembler_opt(option+23);
   }
   else if (!strncmp(option, "--endian=", 9)) {
      const char *endianness = option+9;
      if (!strcmp(endianness, "big")) {
	 set_big_endian();
      }
      else if (!strcmp(endianness, "little")) {
	 set_little_endian();
      }
      else {
	 prog_err("Invalid --endian value (should be `big' or `little')");
      }
   }
   else if (!strncmp(option, "--start-address=", 16)) {
      set_start_address(option+16);
   }
   else if (!strncmp(option, "--stop-address=", 15)) {
      set_stop_address(option+15);
   }
   else if (!strncmp(option, "--adjust-vma=", 13)) {
      set_address_offset(option+13);
   }
   else {
      prog_err("Unknown option %s; try --help", option);
   }
}

static void long_option(struct args *a) {
   const char *opt;
   int i;

   opt = a->argv[a->ind];
   for (i=0; simpleoptions[i].shortform>=0; i++) {
      if (!strcmp(opt, simpleoptions[i].longform)) {
	 info |= simpleoptions[i].infoflags;
	 present |= simpleoptions[i].presentflags;
	 return;
      }
   }
   other_long_option(opt);
}

static void other_short_option(struct args *a) {
   int ch, ch2;

   ch = a->argv[a->ind][a->chrind];
   switch (ch) {
    case 'V': version(); exit(0); break;
    case 'i': objdump_info(); exit(0); break;
    case 'H': objdump_help(); exit(0); break;
    case 'b': set_target(getoptarg(a)); break;
    case 'm': set_arch(getoptarg(a)); break;
    case 'j': add_section_list(getoptarg(a)); break;
    case 'M': add_disassembler_opt(getoptarg(a)); break;
    case 'E': {
       ch2 = a->argv[a->ind][a->chrind+1];
       if (ch2=='B') {
	  set_big_endian();
       }
       else if (ch2=='L') {
	  set_little_endian();
       }
       else {
	  prog_err("Invalid -E option (should be -EB or -EL)");
       }
       break;
    }
    default:
     prog_err("Unknown option -%c; try --help", ch);
     break;
   }
}

static void short_option(struct args *a) {
   int i, ch;

   ch = a->argv[a->ind][a->chrind];
   for (i=0; simpleoptions[i].shortform>=0; i++) {
      if (ch==simpleoptions[i].shortform) {
	 info |= simpleoptions[i].infoflags;
	 present |= simpleoptions[i].presentflags;
	 return;
      }
   }
   other_short_option(a);
}

static void short_options(struct args *a) {
   assert(a->argv[a->ind][0]=='-');
   for (a->chrind=1; a->argv[a->ind][a->chrind]; a->chrind++) {
      short_option(a);
   }
}


int main(int argc, char *argv[]) {
   struct stringarray files;
   struct args a;
   unsigned i, num;

   prog_setname(INSTALLTARGET "objdump");

   /*
    * boy does objdump have a lot of options.
    * we can't even use getopt, because getopt that can handle gnu-style
    * long options isn't standard.
    */

   stringarray_init(&files);

   a.argc = argc;
   a.argv = argv;
   for (a.ind=1; a.ind<argc; a.ind++) {
      if (!strncmp(a.argv[a.ind], "--", 2)) {
	 long_option(&a);
      }
      else if (a.argv[a.ind][0]=='-') {
	 short_options(&a);
      }
      else {
	 stringarray_add(&files, a.argv[a.ind]);
      }
   }

   if (stringarray_num(&files) == 0 || info == 0) {
      fprintf(stderr, "Usage: %sobjdump [-modes|options] file...\n", 
	      INSTALLTARGET);
      fprintf(stderr, "   At least one mode and one file are required.\n");
      fprintf(stderr, "   Try --help for help.\n");
      fprintf(stderr, "   Use --help-modes for a complete list of modes.\n");
      fprintf(stderr, "   Use --help-options for a complete list of "
	      "options.\n");
      exit(1);
   }

   dump_set_info(info);
   dump_set_presentation(present);

   num = stringarray_num(&files);
   for (i=0; i<num; i++) {
      dump(stringarray_get(&files, i));
   }

   stringarray_setsize(&files, 0);
   stringarray_cleanup(&files);

   return 0;
}
