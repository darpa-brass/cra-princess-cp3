// precondition: 
// \disp points to the disp struct
// OFFSETOF_DISP_CRIT_PC_LOW is correct
// disp->crit_pc_lo = \pc
// ~disp_disabled

ldr     \out, [\disp, #OFFSETOF_DISP_CRIT_PC_LOW]
cmp     \out, \pc

// post condition: 
// set Z, C flag and clear N flag => Z = 1; C = 1; N = 0
// \out points to disp-> crit_pc_lo

// \out = r1
// \disp = r2
// \pc = lr