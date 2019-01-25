PRE:
	RCXs points to the dispatcher structure
	RDI = faulting IP
	OFFSETOF_DISP_CRIT_PC_LOW is correct
	ZF = 1


POST:
(VERSION 1)
	if disp->crit_pc_low < RBX then
		CF = 0
		ZF = 0
		/*also affected SF, OF, AF and PF*/
	if disp->crit_pc_low == RBX then
		CF = 0
		ZF = 1
		/*also affected SF, OF, AF and PF*/
	if disp->crit_pc_low > RBX then
		CF = 1
		ZF = 0
		/*also affected SF, OF, AF and PF*/

(VERSION 2)
	((disp->crit_pc_lo >= rbx) \/ 
		((CF == 0) /\ (ZF == 0)))
	/\ ((disp->crit_pc_lo <> rbx) \/
		((CF == 0) /\ (ZF == 1)))
	/\ ((disp->crit_pc_lo <= rbx) \/
		((CF == 1) /\ (ZF == 0)))
