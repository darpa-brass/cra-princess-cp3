// precondition:
// rcx points to the disp struct
// OFFSETOF_DISP_ENABLED_AREA is correct
// after jump to save_enabled

addq $#OFFSETOF_DISP_X86_64_ENABLED_AREA, %rcx /* rcx = enabled_save_area */

// postcondition: 
// RCX points to the disp struct enabled area
