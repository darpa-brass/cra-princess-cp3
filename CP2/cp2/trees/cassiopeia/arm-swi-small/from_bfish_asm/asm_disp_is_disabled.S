//
// Macro to determine if dispatcher is disabled.
//
// pc and disp arguments are unmodified.
// out contains result
//
.macro disp_is_disabled disp, pc, out
    // disp->disabled || (disp->crit_pc_lo <= pc && pc < disp->crit_pc_hi)
    ldrb    \out, [\disp, #OFFSETOF_DISP_DISABLED]
    cmp     \out, #1
// if C == 1, do branch
//    bhs     0f                      // disp->disabled >= 0      | disabled
                                    // disp->disabled = false
    ldr     \out, [\disp, #OFFSETOF_DISP_CRIT_PC_LOW]
    cmp     \out, \pc
    movhi   \out, #0
// if C == 1 && Z == 0, do branch
//    bhi     0f                      // disp->crit_pc_low > pc   | enabled
    ldr     \out, [\disp, #OFFSETOF_DISP_CRIT_PC_HIGH]
    cmp     \pc, \out
    movhs   \out, #0                // pc >= disp->crit_pc_high | enabled
    movlo   \out, #1                // pc <  disp->crit_pc_high | disable
0:
.endm

// disp_is_disabled r2, lr, r1             // r1 = 1 if disabled, else 0