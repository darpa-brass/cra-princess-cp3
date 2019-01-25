PRE:
	R0 points to the dispatcher structure
	OFFSETOF_DISP_CRIT_PC_LOW is correct (assume OFFSETOF_DISP_CRIT_PC_LOW = 0x0)


POST:
(VERSION 1)
	if disp->crit_pc_lo < lr then
		FLAG set: N
		FLAG clear: Z, C
		R0 points to disp->crit_pc_lo
	if disp->crit_pc_lo == lr then
		FLAG set: Z, C
		FLAG clear: N
		R0 points to disp->crit_pc_lo
	if disp->crit_pc_lo > lr then
		FLAG set: C
		FLAG clear: N, Z
		R0 = 0

(VERSION 2)
	((disp->crit_pc_lo >= lr) \/ 
			((N == 1) /\ (Z == 0) /\ (C == 0) /\ (R0 points to disp->crit_pc_lo)))
	 /\ ((disp->crit_pc_lo <> lr) \/
			((N == 0) /\ (Z == 1) /\ (C == 1) /\ (R0 points to disp->crit_pc_lo)))
	 /\ ((disp->crit_pc_lo <= lr) \/
			((N == 0) /\ (Z == 0) /\ (C == 1) /\ (R0 == 0)))
