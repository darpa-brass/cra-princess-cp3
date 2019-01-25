// precondition: 
// r2 points to the disp struct
// OFFSETOF_DISP_CRIT_PC_HIGH is correct

ldr     r1, [r2, #OFFSETOF_DISP_CRIT_PC_HIGH]
cmp     lr, r1

// C == 0 // pc <  disp->crit_pc_high | disable
movlo   r1, #1

// C == 1 // pc >= disp->crit_pc_high | enabled
movhs   r1, #0

// post condition: 
// if r1.original_value != 0 (r1 points to disp-> crit_pc_lo)
// 		set N, clear Z, C => N = 1; Z = 0; C = 0 if disp->crit_pc_hi > lr
//		set C, clear N, Z => N = 0; Z = 0; C = 1 if disp->crit_pc_hi < lr
// 		set Z, C, clear N => N = 0; Z = 1; C = 1 if disp->crit_pc_hi = lr

// 		r1 = 1 if disp->crit_pc_hi > lr
// 		r1 = 0 if disp->crit_pc_hi <= lr

// if r1.original_value == 0
//		r1 = 0 (no change)
