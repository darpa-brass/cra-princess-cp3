PRE:
	R0 points to the dispatcher structure
	OFFSETOF_DISP_ENABLED_AREA is correct (assume OFFSETOF_DISP_ENABLED_AREA = 0x5)
	OFFSETOF_DISP_DISABLED_AREA is correct (assume OFFSETOF_DISP_DISABLED_AREA = 0x10)


POST:
(VERSION 1)
	if R14 == 0 then
		FLAG set: Z, C
		FLAG clear: N
		R0 points to dispatcher enabled area struct (context)

	if R14 == 1 then
		FLAG set: C
		FLAG clear: N, Z
		R0 points to dispatcher disabled area struct (context)

(VERSION 2)
	((R14 == 1) \/ 
		((N == 0) /\ (C == 1) /\ (Z == 1) /\ (R0 points to enabled area))) 
	/\ ((R14 == 0) \/ 
		((N == 0) /\ (C == 1) /\ (Z == 0) /\ (R0 points to disabled area)))
