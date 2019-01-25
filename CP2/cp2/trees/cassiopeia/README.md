# Cassiopeia
Machine description language towards synthesizer assistance for operating system development/porting.

```
Usage: ./cassiopeia [command] casp [files...] [-pp] [-v] [-d] [-o file]
       [command] := -interp | -verify | -synth | -extract

Cassiopeia accepts a command indicating what action it should perform.
A command might expect some files. The accepted file types are as follows:
 * prog : files containing a list of instructions
 * spec : files containing pre-/post-condition specs
The following describes flags and possible commands with their expected arguments:
  -interp [prog] : interpret prog file
  -verify [spec] [prog] : verify prog against spec
  -synth [spec] : synthesize prog from spec
  -extract [prog] : extract ASM from prog file
  -pp : print parsed files
  -v : print diagnostics
  -o : set file for outputs
  -d : dump intermediate info for this command
  -help  Display this list of options
  --help  Display this list of options
```
