PRE:
	R14 points to dispatcher saved area (or it could represent stack pointer)

POST:
(VERSION 1)
	R0 = saved_area.R0
	(or R0 restored from stack)

(VERSION 2)
	R0 = saved_area.R0
	(or R0 restored from stack)
