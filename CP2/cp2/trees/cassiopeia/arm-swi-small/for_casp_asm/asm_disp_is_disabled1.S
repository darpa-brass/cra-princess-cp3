// precondition: 
// r2 points to the disp struct
// OFFSETOF_DISP_DISABLED is correct

ldrb    r1, [r2, #OFFSETOF_DISP_DISABLED]
cmp     r1, #1

// post condition: 
// set Z, C, clear N if disp->disabled
// r1 = 1 if disp->disabled

// set N, clear Z, C if not disp->disabled
// r1 = 0 if not disp->disabled

