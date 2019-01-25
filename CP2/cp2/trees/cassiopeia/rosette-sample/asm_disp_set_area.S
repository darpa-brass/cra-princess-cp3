// precondition:
// r2 points to the disp struct
// OFFSETOF_DISP_ENABLED_AREA is correct

cmp     r1, #0

// if Z == 1
addeq   r0, r2, #OFFSETOF_DISP_ENABLED_AREA

// if Z == 0
addne   r0, r2, #OFFSETOF_DISP_DISABLED_AREA

// postcondition: 
// set Z, C, clear N => N = 0; Z = 1; C = 1; if r1 == 0
// r0 points to the disp struct enabled area if r1 == 0

// set C, clear N, Z => N = 0; Z = 0; C = 1; if r1 == 1
// r0 points to the disp struct disabled area if r1 == 1
