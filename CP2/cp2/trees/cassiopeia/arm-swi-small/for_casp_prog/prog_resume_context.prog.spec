PRE:
	R0 points to the dispatcher saved area
	all registers info in dispatcher saved area

POST:
(VERSION 1)
	CPSR set to supervisor mode
	Restore all register info from saved are to registers
	PC = LR for exception return

(VERSION 2)
	CPSR set to supervisor mode
	Restore all register info from saved are to registers
	PC = LR for exception return	
