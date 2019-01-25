PRE:
	RDI: syscall number
	RSI: syscall arg0
	RDX: syscall arg1
	R10: syscall arg2
	R8: syscall arg3
	R9: syscall arg4
	R12: syscall arg5
	R13: syscall arg6
	R14: syscall arg7
	R15: syscall arg8
	RAX: syscall arg9
	RBP: syscall arg10
	RBX: syscall arg11
	RCX: user-space RIP
	R11: user-space RFLAGS
	user_stack_save is correct, user_stack_save = 8
	KERNEL_STACK + KERNEL_STACK_SIZE is correct, assume KERNEL_STACK + KERNEL_STACK_SIZE = 160

POST:
(VERSION 1)
	sp switches to kernel stack
	function arguments get ready: 
	RDI(RSP/buffer points to (syscallnum, arg0-arg11, rip, rflags))


(VERSION 2)
	sp switches to kernel stack
	function arguments get ready: 
	RDI(RSP/buffer points to (syscallnum, arg0-arg11, rip, rflags))