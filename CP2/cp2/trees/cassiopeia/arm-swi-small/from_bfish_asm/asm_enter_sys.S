// NOTE: maybe not easy to synthesize~


// Macro to initialize system mode stack.
// Assumes that the GOT pointer is set.
//
; .macro init_sys_stack
;     ldr sp, cpu_stack_got_offset
;     ldr sp, [PIC_REGISTER, sp]
;     add sp, sp, #KERNEL_STACK_SIZE
; .endm


//
// Macro to initialize SVC pic register
//
; .macro load_got reg
;     // Read the PL1 thread ID register, where we stored the GOT address on
;     // boot.
;     mrc     p15, 0, \reg, c13, c0, 4
; .endm

//
// Macro to enter SYS mode with interrupts disabled.
// Set up stack and GOT pointer.
//
.macro enter_sys scratch
    clrex
    mov     \scratch, #(CPSR_IF_MASK | ARM_MODE_SYS)
    msr     cpsr_c, \scratch
//    load_got PIC_REGISTER
    mrc     p15, 0, PIC_REGISTER, c13, c0, 4
//    init_sys_stack
	ldr sp, cpu_stack_got_offset
    ldr sp, [PIC_REGISTER, sp]
    add sp, sp, #KERNEL_STACK_SIZE
.endm

// enter_sys r3
//
//     .type cpu_stack_got_offset, STT_OBJECT
// cpu_stack_got_offset:
//     .word kernel_stack(GOT)
//
// PIC_REGISTER = R9
// KERNEL_STACK_SIZE = 0x4000
// CPSR_IF_MASK = 0xc0
// ARM_MODE_SYS = 0x1f