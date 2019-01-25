# ARM Software Interrupt Sample Code (4 Register version) for Cassiopeia

Casp files:
* `arm-swi-tiny4.casp`: arm instruction description file

Prog & Spec files:
* `.prog`: sample prog files
* `.prog.spec`: the specification for prog files, including pre and post conditions
* `.prog.result`: the expected results for prog files

NOTE:
1. This version only contains R0, R1, R2, R14(LR), and the flag register.

2. We make some changes to save_context and resume_context prog files to make sure it can run with this 4 register version (such as considering R14 as the stack pointer and storing the registers into memory)

HOW TO RUN:
1. copy `./cassiopeia` to current directory

2. run `./cassiopeia arm-swi-tiny4.casp -interp <prog_file_name>`. all expected to work; expected results are in the `.prog.result` file.

3. compare the output results with the expected results.
