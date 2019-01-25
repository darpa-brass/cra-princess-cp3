/*Software Interrupt (swi) code for armv7*/
    .type got_sys_syscall, STT_OBJECT
got_sys_syscall:
    .word sys_syscall(GOT)

/* The GOT offset of dcb_current. */
    .type dcb_current_idx, STT_OBJECT
dcb_current_idx:
    .word dcb_current(GOT)

    .arm
    /* The vector table and handler stubs are linked together, at a 4k-aligned
     * address, so that they can be remapped to the high vector address. */
    .section .text.vectors

    .globl exception_vectors
    
 .align 12
exception_vectors:
    /* Reset */
    b .
    /* Undefined instruction */
    b undef_handler
    /* System call */
    b swi_handler
    /* Prefetch abort */
    b pabt_handler
    /* Data abort */
    b dabt_handler
    /* Hypervisor trap */
    b .
    /* IRQ */
    b irq_handler
    /* FIQ */
    b fiq_handler

//
// Macro to initialize system mode stack.
// Assumes that the GOT pointer is set.
//
.macro init_sys_stack
    ldr sp, cpu_stack_got_offset
    ldr sp, [PIC_REGISTER, sp]
    add sp, sp, #KERNEL_STACK_SIZE
.endm

// Macro definition to get pointer to arch-specific dispatcher
//
// Logical equivalent of C function with same name
//
.macro get_dispatcher_shared_arm out tmp
    load_got \tmp
    ldr      \out, dcb_current_idx
    ldr      \out, [\tmp, \out]
    ldr      \out, [\out]        // out = dcb_current
    ldr      \out, [\out, #OFFSETOF_DCB_DISP] //now ptr to dispatcher_shared_arm
.endm

//
// Macro to determine if dispatcher is disabled.
//
// pc and disp arguments are unmodified.
// out contains result
//
.macro disp_is_disabled disp, pc, out
    // disp->disabled || (disp->crit_pc_lo <= pc && pc < disp->crit_pc_hi)
    ldrb    \out, [\disp, #OFFSETOF_DISP_DISABLED]
    cmp     \out, #1
    bhs     0f                      // disp->disabled >= 0      | disabled
                                    // disp->disabled = false
    ldr     \out, [\disp, #OFFSETOF_DISP_CRIT_PC_LOW]
    cmp     \out, \pc
    movhi   \out, #0
    bhi     0f                      // disp->crit_pc_low > pc   | enabled
    ldr     \out, [\disp, #OFFSETOF_DISP_CRIT_PC_HIGH]
    cmp     \pc, \out
    movhs   \out, #0                // pc >= disp->crit_pc_high | enabled
    movlo   \out, #1                // pc <  disp->crit_pc_high | disable
0:
.endm

//
// Macro to spill registers
//
// Assumptions:
//      - context is in scratch registers set {r0-r3}.
//      - spsr is also in scratch register set.
//      - stack holds spilled scratch registers.
//      - lr contains pc for context
// Side-effects:
//      - spills context
//      - pops scratch registers off stack (sp -> sp + 16).
//      - trashes spsr_reg
//
.macro save_context context, spsr_reg
    .if     CPSR_REG <> 0
    .err    "Invariant failure: CPSR offset != 0"
    .endif
    .if     PC_REG <> 16
    .err    "Invariant failure: PC offset != 16"
    .endif
    str     \spsr_reg, [\context, #(CPSR_REG * 4)]
    str     lr, [\context, #(PC_REG * 4)]
    add     \spsr_reg, \context, #(R4_REG * 4)
    stmia   \spsr_reg!, {r4-r14}^
    add     \spsr_reg, #8
    vstmia  \spsr_reg!, {d0-d15}
    vstmia  \spsr_reg!, {d16-d31}
    add     \spsr_reg, \context, #(R3_REG * 4)
    pop     {r4-r7}                         // Pop spilled scratch registers
    stmda   \spsr_reg!, {r4-r7}             // And Save them
.endm

//
// Macro to initialize SVC pic register
//
.macro load_got reg
    // Read the PL1 thread ID register, where we stored the GOT address on
    // boot.
    mrc     p15, 0, \reg, c13, c0, 4
.endm

//
// Macro to enter SYS mode with interrupts disabled.
// Set up stack and GOT pointer.
//
.macro enter_sys scratch
    clrex
    mov     \scratch, #(CPSR_IF_MASK | ARM_MODE_SYS)
    msr     cpsr_c, \scratch
    load_got PIC_REGISTER
    init_sys_stack
.endm
//
// void swi_handler(void)
//
// Entered in SVC mode, IRQ disabled, ARM state.
//
// r0 = encoded syscall ordinal
// r1 = syscall arg0
// r2 = syscall arg1
// ...
// r7 = syscall arg6
//
// For now the system saves the caller's context here, because
// some fraction of system calls do not return directly.
//
swi_handler:
    .if SYSCALL_REG <> 0
    .error "Syscall entry broken. Expected ordinal reg to be r0."
    .endif
    
    // Are we in kernel mode or not?
    stmfd   sp!, {r0-r3}                    // Save for scratch use
    mrs     r3, spsr                        // r3 = spsr until save_context
    ands    r1, r3, #ARM_MODE_PRIV
    bne     $swi_kernel
$swi_user:
    // System call from user space.  Save state.
    get_dispatcher_shared_arm r2 r0
    disp_is_disabled r2, lr, r1             // r1 = 1 if disabled, else 0
    cmp     r1, #0
    addeq   r0, r2, #OFFSETOF_DISP_ENABLED_AREA
    addne   r0, r2, #OFFSETOF_DISP_DISABLED_AREA
    save_context r0, r3                     // r0 = save area, r3 = scratch
    enter_sys r3
    // Removing these two instructions: they don't do anything
    // useful.
    //  ldr     r11, [r0, #48]                  // context->fp
    //  ldr     lr, [r0, #60]                   // context->lr
    // Now we call sys_syscall:
    // __attribute__((noreturn))
    // void sys_syscall(arch_registers_state_t* context,
    //                  uint32_t disabled,
    //                  struct dispatcher_shared_generic *disp);
    //  r0  = address of area context was saved to
    //  r1  = 0 if not disabled, != 0 if disabled
    //  r2  = kernel address of dispatcher
    //  r3  = scratch value
    ldr r3, got_sys_syscall
    ldr pc, [PIC_REGISTER, r3]
$swi_kernel:
    ldr r3, got_syscall_kernel
    ldr pc, [PIC_REGISTER, r3]