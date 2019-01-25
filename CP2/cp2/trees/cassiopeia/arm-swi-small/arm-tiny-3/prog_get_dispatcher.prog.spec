PRE:
	R0 = Thread ID Privileged Read Write only Register
	dcb_current label points to dcb_current (assume address is 0x20)
	OFFSETOF_DCB_DISP is correct (assume OFFSETOF_DCB_DISP = 0x30)


POST:
(VERSION 1)
	R1 points to dispatcher_shared_arm structure

(VERSION 2)
	R1 points to dispatcher_shared_arm structure	
