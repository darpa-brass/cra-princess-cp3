# X86_64 Syscall Sample Code (3 Register version) for Cassiopeia

Casp files:
* `x86-64-syscall-tiny3.casp`: arm instruction description file

Prog & Spec files:
* `.prog`: sample prog files
* `.prog.spec`: the specification for prog files, including pre and post conditions
* `.prog.result`: the expected results for prog files

NOTE:
1. This version only contains RCX, RDI, RSP (stack pointer), and the flag register.

2. We make some changes to prog files to make sure it can run with this 3 register version (such as ignore user/kernel stack switch and considering RDI as current ip or faulting ip)

HOW TO RUN:
1. copy `./cassiopeia` to current directory

2. run `./cassiopeia x86-64-syscall-tiny3.casp -interp <prog_file_name>`. all expected to work; expected results are in the `.prog.result` file.

3. compare the output results with the expected results.
