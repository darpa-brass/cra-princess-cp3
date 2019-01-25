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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include "common.h"

#include "version.h"
#include "host/installdirs.h"
#include "genfile.h"
#include "binfile.h"

#include "label.h"
#include "section.h"
#include "reloc.h"
#include "load.h"
#include "backend.h"

static void usage(void) {
   fprintf(stderr, "Usage: %sas [-Lv] [-o output] [input.s]\n", INSTALLTARGET);
   fprintf(stderr, "   -L            Keep local compiler symbols\n");
   fprintf(stderr, "   -v            Verbose (print version)\n");
   fprintf(stderr, "   -o output     Set output name (default a.out)\n");
   exit(1);
}

int main(int argc, char *argv[]) {
   const char *output = "a.out";
   bool haveoutput = false;
   const char *input = NULL;
   int keeplocal=0;
   int verbose=0;
   int ch;

   /* Set the program name for error messages */
   prog_setname(INSTALLTARGET "as");

   /* process the command line args */
   while ((ch = getopt(argc, argv, "Lo:v"))!=-1) {
      switch (ch) {
       case 'L': keeplocal=1; break;
       case 'o':
	 if (haveoutput) {
	    prog_warn("Multiple output files specified; using last one");
	 }
	 output = optarg;
	 haveoutput = true;
	 break;
       case 'v': verbose++; break;
       default: usage(); break;
      }
   }
   if (optind < argc) {
      input = argv[optind++];
   }
   if (optind < argc) {
      usage();
   }

   /*
    * Global setup of various modules
    */

   if (verbose > 0) {
      fprintf(stderr, "bintools assembler (%sas) version %s\n", INSTALLTARGET,
	      VERSION);
   }

   section_setup();
   backend_setup();

   //binfmt_init();

   /* Set the input file name for error messages */
   file_setname(input ? input : "<standard input>");

   /*
    * Read the input
    */

   /* Load the input file. */
   load(input);

   /* Check that all "jmp 1f"-type references got resolved */
   check_scratch_labels();

   /* Resolve relocations we can */
   process_relocs();

   /* Make adjustments to the labels */
   if (!keeplocal) {
      discard_temp_labels();
   }
   sort_labels();

   /* If there are magic target-specific sections, build them now */
   target_generate_special_sections();

   /*
    * Emit the output
    */

   if (verbose>1) {
      /* Dump to stdout */
      dump_sections();
      dump_relocs();
      dump_labels();
   }

   struct genfile *gf;
   struct binfile *bf;

   /* Open the output file */
   gf = genfile_open(output, "w");
   if (gf==NULL) {
      prog_err("Could not open %s", output);
   }

   /* Wrap it in an abstract-binary-format file */
   bf = binfile_new(output, gf, BFT_OBJ);
   assert(bf != NULL);

   /* Dump the output into the binfile */
   emit_sections(bf);
   emit_labels(bf);
   emit_relocs(bf);

   /* Write out the binfile */
   binfile_write(bf);

   /*
    * Global cleanup
    */

   binfile_destroy(bf);

   backend_shutdown();
   section_shutdown();

   return 0;
}
