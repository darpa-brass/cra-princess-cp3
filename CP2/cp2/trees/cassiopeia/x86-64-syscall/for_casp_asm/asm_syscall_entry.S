/* regular syscall path */
syscall_path:
    /* Save user stack */
    movq    %rsp, user_stack_save(%rip)

    /* Get kernel stack */
    lea (KERNEL_STACK + KERNEL_STACK_SIZE)(%rip), %rsp

    pushq   %rcx            /* Save user-space RIP */
    pushq   %r11            /* Save user-space RFLAGS */

    pushq   %rbx            /* arg11 */
    pushq   %rbp            /* arg10 */
    pushq   %rax            /* arg9 */
    pushq   %r15            /* arg8 */
    pushq   %r14            /* arg7 */
    pushq   %r13            /* arg6 */
    pushq   %r12            /* arg5 */
    pushq   %r9             /* arg4 */
    pushq   %r8             /* arg3 */
    pushq   %r10            /* arg2 in r10, NOT rcx from syscall */

    /* syscall number is in rdi (1st function argument) */
    /* arg0 is in rsi (2nd function argument) */
    /* arg1 is in rdx (3rd function argument) */
    movq    %r11, %r8   /* 5th function argument is user's flags */
    movq    %rcx, %r9   /* 6th function argument is user's IP */
    movq    %rsp, %rcx  /* 4th function argument is pointer to arg buffer */

    callq   sys_syscall     /* Process system call in C */

    addq    $0x50, %rsp     /* Remove buffer from stack */
    popq    %r11            /* Restore RFLAGS */
    popq    %rcx            /* Restore RIP */
    movq    user_stack_save(%rip), %rsp /* Restore user stack */
    sysretq             /* Return to user-space */

    .bss
    .comm   user_stack_save, 8

/* Crystal's reconfigure version*/
/* Save user stack */
movq    %rsp, user_stack_save(%rip)

/* Get kernel stack */
lea (KERNEL_STACK + KERNEL_STACK_SIZE)(%rip), %rsp

pushq   %rcx            /* Save user-space RIP */
pushq   %r11            /* Save user-space RFLAGS */

pushq   %rbx            /* arg11 */
pushq   %rbp            /* arg10 */
pushq   %rax            /* arg9 */
pushq   %r15            /* arg8 */
pushq   %r14            /* arg7 */
pushq   %r13            /* arg6 */
pushq   %r12            /* arg5 */
pushq   %r9             /* arg4 */
pushq   %r8             /* arg3 */
pushq   %r10            /* arg2 in r10, NOT rcx from syscall */

pushq   %rdx            /* arg1 */
pushq   %rsi            /* arg0 */
pushq   %rdi            /* syscall number*/

/* syscall number is in rdi (1st function argument) */
/* arg0 is in rsi (2nd function argument) */
/* arg1 is in rdx (3rd function argument) */
; movq    %r11, %r8   /* 5th function argument is user's flags */
; movq    %rcx, %r9   /* 6th function argument is user's IP */
; movq    %rsp, %rcx  /* 4th function argument is pointer to arg buffer */

movq    %rsp, %rdi /* move the stack pointer to the 1st function argument*/

callq   sys_syscall     /* Process system call in C */

; addq    $0x50, %rsp     /* Remove buffer from stack */
addq    $0x68, %rsp     /* Remove buffer from stack - it's 13*8 instead of 10*8*/
popq    %r11            /* Restore RFLAGS */
popq    %rcx            /* Restore RIP */
movq    user_stack_save(%rip), %rsp /* Restore user stack */
sysretq             /* Return to user-space */

.bss
.comm   user_stack_save, 8
