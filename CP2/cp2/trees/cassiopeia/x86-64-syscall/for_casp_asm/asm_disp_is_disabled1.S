// precondition: 
// rcx points to the disp struct
// OFFSETOF_DISP_DISABLED is correct

cmpl $0, #OFFSETOF_DISP_DISABLED(%rcx) /* disp->disabled ? */

// post condition: 
if disp->disabled then
	CF = 0
	SF = 0
	ZF = 0
	/*also affected OF, AF and PF*/
else 
	CF = 0
	SF = 0
	ZF = 1
	/*also affected OF, AF and PF*/

