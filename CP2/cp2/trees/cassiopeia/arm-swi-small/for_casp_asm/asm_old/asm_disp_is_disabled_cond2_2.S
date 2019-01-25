// precondition: 
// \disp points to the disp struct
// OFFSETOF_DISP_CRIT_PC_LOW is correct
// disp->crit_pc_lo > \pc
// ~disp_disabled

ldr     \out, [\disp, #OFFSETOF_DISP_CRIT_PC_LOW]
cmp     \out, \pc

// if C == 1 and Z == 0, do move
movhi   \out, #0

// post condition: 
// set C flag and clear N, Z flag => C = 1; N = 0; Z = 0
// \out = 0

// \out = r1
// \disp = r2
// \pc = lr
