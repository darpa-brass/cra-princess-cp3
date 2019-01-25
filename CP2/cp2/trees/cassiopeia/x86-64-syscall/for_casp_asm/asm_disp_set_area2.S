// precondition:
// rcx points to the disp struct
// OFFSETOF_DISP_X86_64_DISABLED_AREA is correct
// CF = 1 (after jump to save_disabled)

addq $#OFFSETOF_DISP_X86_64_DISABLED_AREA, %rcx /* rcx = disabled_save_area */

// postcondition: 
// RCX points to the disp struct disabled area
