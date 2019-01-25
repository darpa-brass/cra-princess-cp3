PRE:
	sp points to arguments buffer (syscallnum, arg0-arg11, rip, rflags)
	user_stack_save is correct, user_stack_save = 8

POST:
(VERSION 1)
	restore R11 from stack
	restore RCX from stack
	sp switches to user stack


(VERSION 2)
	restore R11 from stack
	restore RCX from stack
	sp switches to user stack