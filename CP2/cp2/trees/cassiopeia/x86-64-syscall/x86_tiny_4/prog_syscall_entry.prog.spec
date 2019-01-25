PRE:
	sp switches to kernel stack
	RDI: syscall number
	RBX: syscall arg11
	RCX: user-space RIP

POST:
(VERSION 1)
	function arguments get ready: 
	RDI(RSP/buffer points to (syscallnum, arg11, rip))


(VERSION 2)
	function arguments get ready: 
	RDI(RSP/buffer points to (syscallnum, arg11, rip))