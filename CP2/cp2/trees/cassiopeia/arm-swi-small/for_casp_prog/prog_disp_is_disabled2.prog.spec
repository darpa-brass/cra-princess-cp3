PRE:
	R2 points to the dispatcher structure
	OFFSETOF_DISP_CRIT_PC_LOW is correct (assume OFFSETOF_DISP_CRIT_PC_LOW = 0x0)


POST:
(VERSION 1)
	if R1.original_value == 0 then
		if disp->crit_pc_lo < lr then
			FLAG set: N
			FLAG clear: Z, C
			R1 points to disp->crit_pc_lo
		if disp->crit_pc_lo == lr then
			FLAG set: Z, C
			FLAG clear: N
			R1 points to disp->crit_pc_lo
		if disp->crit_pc_lo > lr then
			FLAG set: C
			FLAG clear: N, Z
			R1 = 0

	if R1.original_value == 1 then
		R1 = 1 (there should be a jump here)

(VERSION 2)
	((R1.original_value == 1) \/
		((disp->crit_pc_lo >= lr) \/ 
			((N == 1) /\ (Z == 0) /\ (C == 0) /\ (R1 points to disp->crit_pc_lo)))
	 /\ ((disp->crit_pc_lo <> lr) \/
			((N == 0) /\ (Z == 1) /\ (C == 1) /\ (R1 points to disp->crit_pc_lo)))
	 /\ ((disp->crit_pc_lo <= lr) \/
			((N == 0) /\ (Z == 0) /\ (C == 1) /\ (R1 == 0))))
	/\ ((R1.original_value == 0) \/
		(R1 == 1))
