PRE:
	CPSR sets to supervisor mode
	SPSR stores kernel/user mode info


POST:
(VERSION 1)
	store R0-R3 in stack
	R3 = SPSR
	if in kernel mode then
		FLAG clear: N, Z
		R1 = 1
	if in user mode then
		FLAG set: Z
		FLAG clear: N
		R1 = 0

(VERSION 2)
	(R0-R3 in stack) /\
	(R3 == SPSR) /\
	(((in user mode) \/ 
			((N == 0) /\ (Z == 0) /\ (R1 = 1)))
		/\ ((in kernel mode) \/ 
			((N == 0) /\ (Z == 1) /\ (R1 = 0))))
