PRE:
	RCX points to the dispatcher structure
	OFFSETOF_DISP_DISABLED is correct (assume OFFSETOF_DISP_DISABLED = 10)


POST:
(VERSION 1)
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

(VERSION 2)
	((disp->disabled) \/ 
		((CF == 0) /\ (SF == 0) /\ (ZF == 1))) 
	/\ ((~disp->disabled) \/ 
		((CF == 0) /\ (SF == 0) /\ (ZF == 0))) 
