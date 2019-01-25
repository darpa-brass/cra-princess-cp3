// precondition:
// SVC mode, spsr exists


// Are we in kernel mode or not?
stmfd   sp!, {r0-r3}
mrs     r3, spsr
ands    r1, r3, #ARM_MODE_PRIV

// if Z == 0, then do branch to kernel syscall
// bne     $swi_kernel

// post condition:
// store r0-r3 in stack
// r3 = spsr

// r1 = 1 if in kernel mode
// clear N, Z => N = 0; Z = 0 if in kernel mode

// r1 = 0 if in user mode
// set Z, clear N => N = 0; Z = 1 if in user mode



// ARM_MODE_PRIV = 0x0f
