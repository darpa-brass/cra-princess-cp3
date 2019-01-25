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

// save_context r0 r3
// \context = r0
// \spsr_reg = r3
// CPSR_REG = 0
// PC_REG = 16
// R3_REG = 4
// R4_REG = 5 
