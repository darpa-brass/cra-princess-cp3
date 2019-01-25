// precondition: 
// \disp points to the disp struct
// OFFSETOF_DISP_CRIT_PC_HIGH is correct
// ~disp_disabled
// disp->crit_pc_lo <= \pc
// disp->crit_pc_hi < \pc

ldr     \out, [\disp, #OFFSETOF_DISP_CRIT_PC_HIGH]
cmp     \pc, \out

// C == 1 // pc >= disp->crit_pc_high | enabled
movhs   \out, #0

// post condition: 
// set C flag and clear N, Z flag => C = 1; N = 0; Z = 0
// \out = 0

// \out = r1
// \disp = r2
// \pc = lr
