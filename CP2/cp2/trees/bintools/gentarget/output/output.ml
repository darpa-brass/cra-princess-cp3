(*
 * Copyright (c) 2017
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
 *)

(*
 * Output a file from Gcode.
 * (Or, for now at least, Ccode.)
 *)

type eithercode = G of Gcode.file | C of Ccode.stmt list 

let commonoutput dumpinfo filename ecode =
   let ccode = match ecode with
        C ccode -> ccode
      | G gcode -> begin
           Dumpinfo.trydump' "gcode" dumpinfo Gdump.dump gcode;
           Gtoc.gtoc gcode
        end
   in
   Dumpinfo.trydump' "ccode" dumpinfo Cdump.dump ccode;

   let text = Ctotext.ctotext ccode in

   let text = Text.format dumpinfo text in
   let str = Text.string_of_texts text in

   Util.writeout filename (Util.autogenstr ^ str)

let output' dumpinfo filename ccode =
   commonoutput dumpinfo filename (C ccode)

let output dumpinfo filename gcode =
   commonoutput dumpinfo filename (G gcode)
