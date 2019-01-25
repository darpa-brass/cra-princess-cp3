# ARM Software Interrupt Sample Code for Cassiopeia

Folders:
* `/for_casp_asm`: sample assembly files borrowed from barrelfish (`/for_casp_asm/asm_old` is the old version, not expect to work with casp file)
* `/for_casp_prog`: sample prog files writen for cassiopeia (`/for_casp_prog/prog_old` is the old versio, not expect to work with casp file)
* `/from_bfish_asm`: arm assembly from barrelfish

Casp files:
* `arm-swi-small.casp`: arm instruction description file
* `arm-swi-old.casp`: old version for records (please ignore this)

ASM files:
* `asm_disp_is_disabled1.S`: check disabled flag
* `asm_disp_is_disabled2.S`: compare crit_pc_low and lr
* `asm_disp_is_disabled3.S`: compare crit_pc_high and lr
* `asm_disp_set_area.S`: set pointer to disabled/enabled saved area
* `asm_get_dispatcher.S`: set pointer to dispatcher
* `asm_swi_handler_entry.S`: push R0-R3 to stack for future save_context use (I think it should combine with save_context)
* `asm_save_context.S`: save registers into dispatcher saved area
* `asm_resume_context.S`: restore registers from dispatcher saved_area

Prog & Spec files:
* `.prog`: sample prog files (based on the asm files)
* `.prog.spec`: the specification for prog files, including pre and post conditions
* `.prog.result`: the expected results for prog files

abbytest files:
* `armasm.c`, `armasm_gen.py`, `armtest.c`, `armtest.h`, `armtest.gen.c`: used for fvp tests (running with old casp version, not update yet)
* `fvptest.c`: single instruction test file

HOW TO RUN:
1. copy `./cassiopeia` to current directory

2. run `./cassiopeia arm-swi-small.casp -interp for_casp_prog/<prog_file_name>`. all expected to work; expected results are in the `.prog.result` file.

3. compare the output results with the expected results.
