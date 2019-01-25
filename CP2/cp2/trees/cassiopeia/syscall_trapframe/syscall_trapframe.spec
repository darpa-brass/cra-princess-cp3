X86_64:
	RDI: syscall number
	RSI: syscall arg0
	RDX: syscall arg1
	R10: syscall arg2, in stack
	R8: syscall arg3, in stack
	R9: syscall arg4, in stack
	R12: syscall arg5, in stack
	R13: syscall arg6, in stack
	R14: syscall arg7, in stack
	R15: syscall arg8, in stack
	RAX: syscall arg9, in stack
	RBP: syscall arg10, in stack
	RBX: syscall arg11, in stack
	RCX: user-space RIP, in stack
	R11: user-space RFLAGS, in stack

ARMv7:
	CPSR: svc mode SPSR (including flags), in disp.area
	R0: syscall number and syscall ordinal, in disp.area
	R1: syscall arg0, in disp.area
	R2: syscall arg1, in disp.area
	R3: syscall arg2, in disp.area
	R4: syscall arg3, in disp.area
	R5: syscall arg4, in disp.area
	R6: syscall arg5, in disp.area
	R7: syscall arg6, in disp.area
	R8: syscall arg7, in disp.area
	R9: syscall arg8, in disp.area
	R10: syscall arg9, in disp.area
	R11: syscall arg10, in disp.area
	R12: syscall arg11, in disp.area
	R13: user mode stack pointer, in disp.area
	R14: user mode link register, in disp.area
	PC: svc mode link register, in disp.area

