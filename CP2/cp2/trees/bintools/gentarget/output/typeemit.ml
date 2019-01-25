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

module G = Gcode
open Typerep

let emit'type pos t = match t with
     PLAINTYPE "bool" -> G.BOOL
   | PLAINTYPE "string" -> G.POINTER (G.CONST G.CHAR)
   | PLAINTYPE name ->
        Pos.crashat pos ("Unknown type " ^ name ^ " while emitting code")
   | WIDTHTYPE ("int", width) -> G.INTBITS width
   | WIDTHTYPE ("uint", width) -> G.UINTBITS width
   | WIDTHTYPE (name, width) ->
        let name' = name ^ "(" ^ string_of_int width ^ ")" in
        Pos.crashat pos ("Unknown type " ^ name' ^ " while emitting code")
   | EXPRTYPE _t' ->
        G.POINTER (G.STRUCTTYPE "expr")
   | LISTTYPE _ ->
        Pos.crashat pos "Leftover list type while emitting code"
   | TMPTYPE _ ->
        Pos.crashat pos "Leftover scratch type while emitting code"
