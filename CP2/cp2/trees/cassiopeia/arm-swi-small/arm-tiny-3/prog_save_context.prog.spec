PRE:
	R14 points to dispatcher saved area (or it could represent stack pointer)

POST:
(VERSION 1)
	saved_area.R0 = R0
	saved_area.R1 = R1
	(or R0-R1 stored in stack)

(VERSION 2)
	saved_area.R0 = R0
	saved_area.R1 = R1
	(or R0-R1 stored in stack)
