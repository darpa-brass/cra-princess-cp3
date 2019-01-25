// precondition: 
// rcx points to the disp struct
// rbx = faulting IP
// OFFSETOF_DISP_CRIT_PC_HIGH is correct
// CF = 0

cmpq #OFFSETOF_DISP_X86_64_CRIT_PC_HIGH(%rcx), %rbx /* crit_pc_high > rip? */

// post condition: 
if disp->crit_pc_high < RBX then
	CF = 0
	ZF = 0
	/*also affected SF, OF, AF and PF*/
if disp->crit_pc_high == RBX then
	CF = 0
	ZF = 1
	/*also affected SF, OF, AF and PF*/
if disp->crit_pc_high > RBX then
	CF = 1
	ZF = 0
	/*also affected SF, OF, AF and PF*/
