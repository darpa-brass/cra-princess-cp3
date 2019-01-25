// precondition: 
// \disp points to the disp struct
// OFFSETOF_DISP_CRIT_PC_HIGH is correct
// ~disp_disabled
// disp->crit_pc_lo <= \pc
// disp->crit_pc_hi > \pc


ldr     \out, [\disp, #OFFSETOF_DISP_CRIT_PC_HIGH]
cmp     \pc, \out

// C == 0 // pc <  disp->crit_pc_high | disable
movlo   \out, #1

// post condition: 
// set N flag and clear Z, C flag => N = 1; Z = 0; C = 0
// \out = 1

// \out = r1
// \disp = r2
// \pc = lr
