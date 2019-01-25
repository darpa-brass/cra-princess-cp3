PRE:
	R1 points to the dispatcher structure
	OFFSETOF_DISP_ENABLED_AREA is correct (assume OFFSETOF_DISP_ENABLED_AREA = 0x5)
	OFFSETOF_DISP_DISABLED_AREA is correct (assume OFFSETOF_DISP_DISABLED_AREA = 0x10)


POST:
(VERSION 1)
	if R0 == 0 then
		FLAG set: Z, C
		FLAG clear: N
		R1 points to dispatcher enabled area struct (context)

	if R0 == 1 then
		FLAG set: C
		FLAG clear: N, Z
		R1 points to dispatcher disabled area struct (context)

(VERSION 2)
	((R0 == 1) \/ 
		((N == 0) /\ (C == 1) /\ (Z == 1) /\ (R1 points to enabled area))) 
	/\ ((R0 == 0) \/ 
		((N == 0) /\ (C == 1) /\ (Z == 0) /\ (R1 points to disabled area)))
