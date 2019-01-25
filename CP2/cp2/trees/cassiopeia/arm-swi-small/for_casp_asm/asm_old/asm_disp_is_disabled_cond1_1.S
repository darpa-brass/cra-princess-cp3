// precondition: 
// \disp points to the disp struct
// OFFSETOF_DISP_DISABLED is correct
// disp->disabled

ldrb    \out, [\disp, #OFFSETOF_DISP_DISABLED]
cmp     \out, #1

// post condition: 
// set Z flag and C flag
// \out = 1

// \out = r1
// \disp = r2
