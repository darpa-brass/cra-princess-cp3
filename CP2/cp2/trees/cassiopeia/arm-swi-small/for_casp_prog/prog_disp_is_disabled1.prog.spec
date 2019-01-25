PRE:
	R2 points to the dispatcher structure
	OFFSETOF_DISP_DISABLED is correct (assume OFFSETOF_DISP_DISABLED = 0x0)


POST:
(VERSION 1)
	if disp->disabled then
		FLAG set: Z, C
		FLAG clear: N
		R1 = 1

	if not disp->disabled then
		FLAG set: N
		FLAG clear: Z, C
		R1 = 0

(VERSION 2)
	((disp->disabled) \/ 
		((N == 1) /\ (C == 0) /\ (Z == 0) /\ (R1 == 0))) 
	/\ ((~disp->disabled) \/ 
		((N == 0) /\ (C == 1) /\ (Z == 1) /\ (R1 == 1)))
