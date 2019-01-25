open Batteries
open Util

module A = Arg
module S = Sys
module P = Printf

(* represent actions to be performed *)
type command =
| Interp  (* input prog, output, dump *)
| Verify  (* input spec, input prog, dump *)
| Synth   (* input spec, output, dump *)
| Extract (* input prog, output, dump *)

let string_of_command = function
  | Interp -> "Interp"
  | Verify -> "Verify"
  | Synth -> "Synth"
  | Extract -> "Extract"

let cmd:   command option ref = ref None
let files: string list ref    = ref []

let do_print: bool ref    = ref false
let verbose:  bool ref    = ref false
let do_dump:  bool ref    = ref false
let outfile:  string ref  = ref ""

let string_of_command_args () =
  let out_name =
    if !outfile = "" then "<stdout>"
    else !outfile
  in
  let dump_name =
    if !do_dump then " with intermediate dumps"
    else ""
  in
  match (!cmd, !files) with
  (* command with good args *)
  | (Some Interp, [casp; prog]) ->
    P.sprintf "Interpret instrs from %s and output to %s%s" prog out_name dump_name
  | (Some Verify, [casp; spec; prog]) ->
    P.sprintf "Verify instrs in %s against spec %s%s" prog spec dump_name
  | (Some Synth, [casp; spec]) ->
    P.sprintf "Synthesize for spec %s and output to %s%s" spec out_name dump_name
  | (Some Extract, [casp; prog]) ->
    P.sprintf "Extract ASM from %s and output to %s%s" prog out_name dump_name
  (* wrong arg counts *)
  | (Some c, _) ->
    P.sprintf "%s got wrong number of args: [%s]"
              (string_of_command c)
              (String.concat ";" !files)
  (* no command *)
  | (None, _) ->
    P.sprintf "No command given. Args: [%s]" (String.concat "\n" !files)

let opts = [
  ("-interp", A.Unit (fun () -> cmd := Some Interp),
          "[prog] : interpret prog file");
  ("-verify", A.Unit (fun () -> cmd := Some Verify),
          "[spec] [prog] : verify prog against spec");
  ("-synth", A.Unit (fun () -> cmd := Some Synth),
          "[spec] : synthesize prog from spec");
  ("-extract", A.Unit (fun () -> cmd := Some Extract),
          "[prog] : extract ASM from prog file");
  ("-pp", A.Set do_print, ": print parsed files");
  ("-v", A.Set verbose, ": print diagnostics");
  ("-o", A.Set_string outfile, ": set file for outputs");
  ("-d", A.Set do_dump, ": dump intermediate info for this command")]

let usage = [
  "Usage: " ++ exe ++ " [command] casp [files...] [-pp] [-v] [-d] [-o file]";
  "       [command] := -interp | -verify | -synth | -extract";
  "";
  "Cassiopeia accepts a command indicating what action it should perform.";
  "A command might expect some files. The accepted file types are as follows:";
  " * prog : files containing a list of instructions";
  " * spec : files containing pre-/post-condition specs";
  "The following describes flags and possible commands with their expected arguments:"]
  |> String.concat "\n"

let parse_args () =
  A.parse opts (arl files) usage

