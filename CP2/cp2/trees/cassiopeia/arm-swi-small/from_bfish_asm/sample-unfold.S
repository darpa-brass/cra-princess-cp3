/*Software Interrupt (swi) code for armv7*/

    .type got_sys_syscall, STT_OBJECT
got_sys_syscall:
    .word sys_syscall(GOT)

    .type dcb_current_idx, STT_OBJECT
dcb_current_idx:
    .word dcb_current(GOT)

    .type cpu_stack_got_offset, STT_OBJECT
cpu_stack_got_offset:
    .word kernel_stack(GOT)

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
    mrc     p15, 0, r0, c13, c0, 4
    ldr      r2, dcb_current_idx
    ldr      r2, [r0, r2]
    ldr      r2, [r2]        // out = dcb_current
    ldr      r2, [r2, #OFFSETOF_DCB_DISP] //now ptr to dispatcher_shared_arm

    // disp->disabled || (disp->crit_pc_lo <= pc && pc < disp->crit_pc_hi)
    ldrb    r1, [r2, #OFFSETOF_DISP_DISABLED]
    cmp     r1, #1
    bhs     0f                      // disp->disabled >= 0      | disabled
                                    // disp->disabled = false
    ldr     r1, [r2, #OFFSETOF_DISP_CRIT_PC_LOW]
    cmp     r1, lr
    movhi   r1, #0
    bhi     0f                      // disp->crit_pc_low > pc   | enabled
    ldr     r1, [r2, #OFFSETOF_DISP_CRIT_PC_HIGH]
    cmp     lr, r1
    movhs   r1, #0                // pc >= disp->crit_pc_high | enabled
    movlo   r1, #1                // pc <  disp->crit_pc_high | disable
0:

    cmp     r1, #0
    addeq   r0, r2, #OFFSETOF_DISP_ENABLED_AREA
    addne   r0, r2, #OFFSETOF_DISP_DISABLED_AREA

    .if     CPSR_REG <> 0
    .err    "Invariant failure: CPSR offset != 0"
    .endif
    .if     PC_REG <> 16
    .err    "Invariant failure: PC offset != 16"
    .endif
    str     r3, [r0, #(CPSR_REG * 4)]
    str     lr, [r0, #(PC_REG * 4)]
    add     r3, r0, #(R4_REG * 4)
    stmia   r3!, {r4-r14}^
    add     r3, #8
    vstmia  r3!, {d0-d15}
    vstmia  r3!, {d16-d31}
    add     r3, r0, #(R3_REG * 4)
    pop     {r4-r7}                         // Pop spilled scratch registers
    stmda   r3!, {r4-r7}             // And Save them

    clrex
    mov     r3, #(CPSR_IF_MASK | ARM_MODE_SYS)
    msr     cpsr_c, r3
    mrc     p15, 0, PIC_REGISTER, c13, c0, 4

    ldr sp, cpu_stack_got_offset
    ldr sp, [PIC_REGISTER, sp]
    add sp, sp, #KERNEL_STACK_SIZE

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