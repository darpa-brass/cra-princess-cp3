// precondition: 
// \disp points to the disp struct
// OFFSETOF_DISP_CRIT_PC_LOW is correct
// disp->crit_pc_lo < \pc
// ~disp_disabled

ldr     \out, [\disp, #OFFSETOF_DISP_CRIT_PC_LOW]
cmp     \out, \pc

// post condition: 
// set N flag and clear Z, C flag => N = 1; Z = 0; C = 0
// \out points to disp-> crit_pc_lo

// \out = r1
// \disp = r2
// \pc = lr
