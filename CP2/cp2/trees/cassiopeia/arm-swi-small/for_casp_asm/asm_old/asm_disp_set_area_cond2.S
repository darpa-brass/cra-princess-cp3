// precondition:
// r1 = 1
// r2 points to the disp struct
// OFFSETOF_DISP_DISABLED_AREA is correct

cmp     r1, #0

// Z == 0
addne   r0, r2, #OFFSETOF_DISP_DISABLED_AREA

// postcondition: 
// set C flag, clear N, Z flag => C = 1; N = 0; Z = 0
// r0 points to the disp struct disabled area