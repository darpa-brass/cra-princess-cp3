open Util

module A = Arg
module S = Sys
module P = Printf
module Opt = Options
module Pr  = Prettyast

let get_out_ch out =
  if out <> "" then open_out out
  else stdout

(* INTERP COMMAND *)
let interp casp_ast prog out_ch =
  let prog_ast = Lex.parse_with Parse.prog_file prog in
  (* cut out positions *)
  let c = List.map snd casp_ast in
  let p = List.map snd prog_ast in
  (* preprocessing passes *)
  let c = Process.process_casp c in
  let p = Process.process_prog c p in
  (* prog eval *)
  let final_state = Interpret.eval_prog c p in
  let _ =
    P.fprintf out_ch 
      "Interp results:\nMemory:\n============\n%s\nRegisters:\n============\n%s\n"
      (Interpret.string_of_mem final_state.mem)
      (Interpret.string_of_reg final_state.reg)
  in
  0

(* VERIFY COMMAND *)
let verify casp_ast spec prog out_ch =
  let (ghosts, spec_pre, spec_post) = Lex.parse_with Parse.spec_file spec in
  (*let _ =
    P.fprintf out_ch "precondition:\n%s\n" (Prettyast.string_of_expr spec_pre);
    P.fprintf out_ch "postcondition:\n%s\n" (Prettyast.string_of_expr spec_post);
  in*)
  let prog_ast = Lex.parse_with Parse.prog_file prog in
  let c = List.map snd casp_ast in
  let p = List.map snd prog_ast in
  let c = Process.process_casp c in
  let p = Process.process_prog c p in
  let _ = P.fprintf out_ch "%s\n" (Rosette.convert_casp c) in
  let _ = P.fprintf out_ch "%s\n" (Rosette.convert_prog p "prog") in
  let _ = P.fprintf out_ch "%s\n" (Rosette.convert_verify c "prog" ghosts spec_pre spec_post) in
  0

(* SYNTH COMMAND *)
let synth casp_ast spec out_ch =
  let (ghosts, spec_pre, spec_post) = Lex.parse_with Parse.spec_file spec in
  (*let _ =
    P.fprintf out_ch "precondition:\n%s\n" (Prettyast.string_of_expr spec_pre);
    P.fprintf out_ch "postcondition:\n%s\n" (Prettyast.string_of_expr spec_post);
  in*)
  let c = List.map snd casp_ast in
  let c = Process.process_casp c in
  let _ = P.fprintf out_ch "%s\n" (Rosette.convert_casp c) in
  let _ = P.fprintf out_ch "%s\n" (Rosette.convert_synth c ghosts spec_pre spec_post) in
  0

(* EXTRACT COMMAND *)
let extract casp_ast prog out_ch =
  let prog_ast = Lex.parse_with Parse.prog_file prog in
  let c = List.map snd casp_ast in
  let p = List.map snd prog_ast in
  let cr = Process.process_casp c in
  let p = Process.process_prog cr p in
  let _ = P.fprintf out_ch "%s\n" (Extract.to_asm c p) in
  0

let do_command cmd casp args pp verbose do_dump out_ch =
  (* parse machine description *)
  let casp_ast = Lex.parse_with Parse.casp_file casp in
  (* pretty print machine description *)
  let _ = if pp then
    Prettyast.string_of_casp casp_ast
    |> P.fprintf out_ch "Pretty printing casp AST:\n============\n%s\n============\nDone\n"
  in
  (* execute command *)
  match (cmd, args) with
  | (Some Opt.Interp, [prog]) -> interp casp_ast prog out_ch
  | (Some Opt.Verify, [spec; prog]) -> verify casp_ast spec prog out_ch
  | (Some Opt.Synth, [spec]) -> synth casp_ast spec out_ch
  | (Some Opt.Extract, [prog]) -> extract casp_ast prog out_ch
  | (Some Opt.Interp, _) ->
    failwith ("Interp got wrong number of args "^
              (string_of_int (List.length args))^
              ": expected 1 (prog)")
  | (Some Opt.Verify, _) ->
    failwith ("Verify got wrong number of args "^
              (string_of_int (List.length args))^
              ": expected 2 (spec, prog)")
  | (Some Opt.Synth, _) ->
    failwith ("Synth got wrong number of args "^
              (string_of_int (List.length args))^
              ": expected 1 (spec)")
  | (Some Opt.Extract, _) ->
    failwith ("Extract got wrong number of args "^
              (string_of_int (List.length args))^
              ": expected 1 (prog)")
  | (None, _) -> 0

let casp_main () = 
  (* extract settings from args *)
  let _   = Opt.parse_args () in
  let cmd = !Opt.cmd in
  let ff  = !Opt.files in
  let pp  = !Opt.do_print in
  let v   = !Opt.verbose in
  let dd  = !Opt.do_dump in
  let out = !Opt.outfile in
  (* open output channel *)
  let out_ch = get_out_ch out in
  (* if verbose, dump command list *)
  let _ = if v then
    (Opt.string_of_command_args ()) ^ "\n"
    |> output_string out_ch
  in
  (* turn on printing and dumping in submodules as well *)
  let print = fun s -> P.fprintf out_ch "%s" s in
  let _ =
    (if v then
      Interpret.print_verbose := print;
      Process.print_verbose := print;
      Type_check.print_verbose := print);
    (if dd then
      Interpret.print_dump := print;
      Process.print_dump := print;
      Type_check.print_dump := print)
  in
  match ff with
  | casp :: args -> do_command cmd casp args pp v dd out_ch
  | [] -> failwith "No files given!"
 
let _ = casp_main () |> exit

