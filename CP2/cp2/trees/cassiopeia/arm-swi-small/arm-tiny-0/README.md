# ARM Software Interrupt Sample Code (0 Register version) for Cassiopeia

Casp files:
* `arm-swi-tiny0.casp`: arm instruction description file

Prog & Spec files:
* `.prog`: sample prog files
* `.prog.spec`: the specification for prog files, including pre and post conditions
* `.prog.result`: the expected results for prog files

NOTE:
1. This version only contains the flag register.

HOW TO RUN:
1. copy `./cassiopeia` to current directory

2. run `./cassiopeia arm-swi-tiny0.casp -interp <prog_file_name>`. all expected to work; expected results are in the `.prog.result` file.

3. compare the output results with the expected results.
