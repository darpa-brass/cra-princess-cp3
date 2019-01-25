PRE:
	RDI points to the disp struct
	OFFSETOF_DISP_X86_64_DISABLED_AREA is correct
	CF = 1 (after jump to save_disabled)


POST:
(VERSION 1)
	RDI points to the disp struct disabled area

(VERSION 2)
	RDI points to the disp struct disabled area