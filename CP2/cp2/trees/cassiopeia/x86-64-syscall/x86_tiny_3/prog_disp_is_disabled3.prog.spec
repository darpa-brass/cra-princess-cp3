PRE:
	RCXs points to the dispatcher structure
	RDI = faulting IP
	OFFSETOF_DISP_CRIT_PC_HIGH is correct
	CF = 0


POST:
(VERSION 1)
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

(VERSION 2)
	((disp->crit_pc_hi >= rbx) \/ 
		((CF == 0) /\ (ZF == 0)))
	/\ ((disp->crit_pc_hi <> rbx) \/
		((CF == 0) /\ (ZF == 1)))
	/\ ((disp->crit_pc_hi <= rbx) \/
		((CF == 1) /\ (ZF == 0)))
