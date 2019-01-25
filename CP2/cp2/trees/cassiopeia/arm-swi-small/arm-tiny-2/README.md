# ARM Software Interrupt Sample Code (2 Register version) for Cassiopeia

Casp files:
* `arm-swi-tiny2.casp`: arm instruction description file

Prog & Spec files:
* `.prog`: sample prog files
* `.prog.spec`: the specification for prog files, including pre and post conditions
* `.prog.result`: the expected results for prog files

NOTE:
1. This version only contains R0, R14(LR), and the flag register.

2. We make some changes to all prog files to make sure it can run with this 2 register version (such as considering R14 as the stack pointer, and reusing R0, R14)

HOW TO RUN:
1. copy `./cassiopeia` to current directory

2. run `./cassiopeia arm-swi-tiny2.casp -interp <prog_file_name>`. all expected to work; expected results are in the `.prog.result` file.

3. compare the output results with the expected results.
