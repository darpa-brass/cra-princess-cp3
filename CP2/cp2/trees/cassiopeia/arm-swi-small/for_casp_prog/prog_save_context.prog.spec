PRE:
	R0 points to the dispatcher saved area
	R3 = SPSR
	original R0-R3 saved in stack

POST:
(VERSION 1)
	all register info stores in dispatcher saved area
	saved_area.CPSR = R3
	saved_area.PC = LR
	saved_area.R4-R14 = R4-R14
	saved_area.D0-D31 = D0-D31
	saved_area.R0-R3 = original R0-R3 from stack

(VERSION 2)
	all register info stores in dispatcher saved area
	saved_area.CPSR = R3
	saved_area.PC = LR
	saved_area.R4-R14 = R4-R14
	saved_area.D0-D31 = D0-D31
	saved_area.R0-R3 = original R0-R3 from stack
