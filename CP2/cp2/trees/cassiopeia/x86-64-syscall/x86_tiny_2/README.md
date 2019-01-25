# X86_64 Syscall Sample Code (2 Register version) for Cassiopeia

Casp files:
* `x86-64-syscall-tiny2.casp`: arm instruction description file

Prog & Spec files:
* `.prog`: sample prog files
* `.prog.spec`: the specification for prog files, including pre and post conditions
* `.prog.result`: the expected results for prog files

NOTE:
1. This version only contains RDI, RSP (stack pointer), and the flag register.

2. We make some changes to prog files to make sure it can run with this 2 register version (such as ignore user/kernel stack switch and considering RDI as current pc)

3. resume_context needs RCX (keeps the user space's ip), but we currently ignore RCX in this version -> we only have RDI and RSP.

HOW TO RUN:
1. copy `./cassiopeia` to current directory

2. run `./cassiopeia x86-64-syscall-tiny2.casp -interp <prog_file_name>`. all expected to work; expected results are in the `.prog.result` file.

3. compare the output results with the expected results.
