// precondition:
// dcb_current label points to dcb_current
// OFFSETOF_DCB_DISP is correct

movq dcb_current(%rip), %rcx /* rcx = dcb_current */
movq #OFFSETOF_DCB_DISP(%rcx), %rcx /* rcx = dcb_current->disp */

// postcondition: 
// rcx points to dispatcher