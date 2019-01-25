PRE:
	R2 points to the dispatcher structure
	OFFSETOF_DISP_CRIT_PC_HIGH is correct (assume OFFSETOF_DISP_CRIT_PC_HIGH = 0x0)


POST:
(VERSION 1)
	if R1.original_value != 0 then
		if disp->crit_pc_hi < lr then
			FLAG set: C
			FLAG clear: N, Z
			R1 = 0
		if disp->crit_pc_hi == lr then
			FLAG set: Z, C
			FLAG clear: N
			R1 = 0
		if disp->crit_pc_hi > lr then
			FLAG set: N
			FLAG clear: Z, C
			R1 = 1

	if R1.original_value == 0 then
		R1 = 0 (there should be a jump here)

(VERSION 2)
	((R1.original_value == 0) \/
		((disp->crit_pc_hi >= lr) \/ 
			((N == 0) /\ (Z == 0) /\ (C == 1) /\ (R1 == 0)))
	 /\ ((disp->crit_pc_hi <> lr) \/
			((N == 0) /\ (Z == 1) /\ (C == 1) /\ (R1 == 0)))
	 /\ ((disp->crit_pc_hi <= lr) \/
			((N == 1) /\ (Z == 0) /\ (C == 0) /\ (R1 == 1))))
	/\ ((R1.original_value == 1) \/
		(R1 == 0))
