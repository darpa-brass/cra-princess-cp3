// precondition:
// r1 = 0
// r2 points to the disp struct
// OFFSETOF_DISP_ENABLED_AREA is correct

cmp     r1, #0

// Z == 1
addeq   r0, r2, #OFFSETOF_DISP_ENABLED_AREA

// postcondition: 
// set Z, C flag, clear N flag => Z = 1; C = 1; N = 0
// r0 points to the disp struct enabled area
