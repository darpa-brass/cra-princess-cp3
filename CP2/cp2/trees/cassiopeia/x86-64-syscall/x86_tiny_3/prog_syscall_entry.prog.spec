PRE:
	sp switches to kernel stack
	RDI: syscall number
	RCX: user-space RIP

POST:
(VERSION 1)
	function arguments get ready: 
	RDI(RSP/buffer points to (syscallnum, rip))


(VERSION 2)
	function arguments get ready: 
	RDI(RSP/buffer points to (syscallnum, rip))