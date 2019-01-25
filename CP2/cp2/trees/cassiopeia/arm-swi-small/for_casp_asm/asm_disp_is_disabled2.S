// precondition: 
// r2 points to the disp struct
// OFFSETOF_DISP_CRIT_PC_LOW is correct

ldr     r1, [r2, #OFFSETOF_DISP_CRIT_PC_LOW]
cmp     r1, lr

// if Z == 0; C == 1, do move
movhi   r1, #0

// penlu:
// I do not understand these conditions...
// what does r1 end up having to do with disp->disabled?

// post condition: 

// if r1.original_value == 0 (not disp->disabled)
// 		set N, clear Z, C => N = 1; Z = 0; C = 0 if disp->crit_pc_lo < lr
// 		set Z, C, clear N => N = 0; Z = 1; C = 1 if disp->crit_pc_lo = lr
// 		set C, clear N, Z => N = 0; Z = 0; C = 1 if disp->crit_pc_lo > lr

// 		r1 points to disp-> crit_pc_lo (r1 != 0) if disp->crit_pc_lo <= lr
// 		r1 = 0 if disp->crit_pc_lo > lr

// if r1.original_value == 1 (disp->disabled)
// 		r1 = 1 (no change)

