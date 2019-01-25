PRE:
	RCX points to the disp struct
	OFFSETOF_DISP_X86_64_DISABLED_AREA is correct
	CF = 1 (after jump to save_disabled)


POST:
(VERSION 1)
	RCX points to the disp struct disabled area

(VERSION 2)
	RCX points to the disp struct disabled area