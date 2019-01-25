PRE:
	sp switches to kernel stack
	RDI: syscall number

POST:
(VERSION 1)
	function arguments get ready: 
	RDI(RSP/buffer points to (syscallnum))


(VERSION 2)
	function arguments get ready: 
	RDI(RSP/buffer points to (syscallnum))