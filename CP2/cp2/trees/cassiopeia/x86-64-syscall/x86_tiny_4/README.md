# X86_64 Syscall Sample Code (4 Register version) for Cassiopeia

Casp files:
* `x86-64-syscall-tiny4.casp`: arm instruction description file

Prog & Spec files:
* `.prog`: sample prog files
* `.prog.spec`: the specification for prog files, including pre and post conditions
* `.prog.result`: the expected results for prog files

NOTE:
1. This version only contains RCX, RBX, RDI, RSP (stack pointer), and the flag register.

2. We make some changes to get_dispatcher, save_context and resume_context prog files to make sure it can run with this 4 register version (such as ignore user/kernel stack switch and considering RDI as current pc)

HOW TO RUN:
1. copy `./cassiopeia` to current directory

2. run `./cassiopeia x86-64-syscall-tiny4.casp -interp <prog_file_name>`. all expected to work; expected results are in the `.prog.result` file.

3. compare the output results with the expected results.
