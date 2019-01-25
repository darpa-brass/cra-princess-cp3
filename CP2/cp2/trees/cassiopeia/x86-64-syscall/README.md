# X86_64 Syscall Sample Code for Cassiopeia

Folders:
* `/for_casp_asm`: sample assembly files borrowed from barrelfish 
* `/for_casp_prog`: sample prog files writen for cassiopeia
* `/from_bfish_asm`: x86_64 assembly from barrelfish

Casp files:
* `x86-64-syscall.casp`: arm instruction description file

ASM files:
* `asm_disp_is_disabled1.S`: check disabled flag
* `asm_disp_is_disabled2.S`: compare crit_pc_low and lr
* `asm_disp_is_disabled3.S`: compare crit_pc_high and lr
* `asm_disp_set_area1.S`: set pointer to enabled saved area
* `asm_disp_set_area2.S`: set pointer to disabled saved area (x86_64 has two asm files about set_area because bfish uses jump in x86 instead of conditional execution in arm.)
* `asm_get_dispatcher.S`: set pointer to dispatcher
* `asm_syscall_entry.S`: push registers into stack and pass stack pointer as the only function argument (after Crystal's syscall reconfiguration); restore rip and flags after function return

Prog & Spec files:
* `.prog`: sample prog files (based on the asm files)
* `.prog.spec`: the specification for prog files, including pre and post conditions
* `.prog.result`: the expected results for prog files


HOW TO RUN:
1. copy `./cassiopeia` to current directory

2. run `./cassiopeia x86-64-syscall.casp -interp for_casp_prog/<prog_file_name>`. all expected to work; expected results are in the `.prog.result` file.

3. compare the output results with the expected results.
