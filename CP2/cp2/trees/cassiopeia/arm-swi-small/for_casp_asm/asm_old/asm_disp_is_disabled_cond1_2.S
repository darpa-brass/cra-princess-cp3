// precondition: 
// \disp points to the disp struct
// OFFSETOF_DISP_DISABLED is correct
// ~disp->disabled

ldrb    \out, [\disp, #OFFSETOF_DISP_DISABLED]
cmp     \out, #1

// post condition: 
// set N flag
// \out = 0

// \out = r1
// \disp = r2
