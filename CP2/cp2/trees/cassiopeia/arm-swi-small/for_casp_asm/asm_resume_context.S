; clrex // NOTE: We don't need this
// There is no SPSR in system mode, so switch to supervisor.
msr    CPSR_c, #(CPSR_IF_MASK | ARM_MODE_SVC)
// Load cpsr into LR and move regs to next entry (postindex op)
// LR = r14, used as scratch register.
// LDR = read word from memory
//        target register
//        /   use register containing "regs" as base register
//       /   /     post index: only base register is used for
//      /   /     /   addressing and the offset added afterwards
ldr    lr, [r0], #4
// set SPSR to value of lr == regs.cpsr
// restore cpsr
//        bits indicating SPSR
//       /      read from register lr
//      /      /
msr    spsr, lr
// Restore register r0 to r15, "^" means: cpsr := spsr
// Restore the non-banked registers.  Use LR as the index.
mov    lr, r0
//          will increment the base pointer
//         /
ldmia  lr!, {r0-r12}
// Restore the user stack pointer and link register.  n.b. LR is
// banked in SVC mode, so *our* LR isn't affected.  Also, this can't
// write back, so we've got to add the offset ourselves.
add lr, #5*4
vldmia lr!, {d0-d15}
vldmia lr, {d16-d31}
sub lr, #(5+32)*4
ldmia  lr, {r13, r14}^
// Load the (banked SVC) LR with the return address (add the offset
// that the last ldmia couldn't).
ldr    lr, [lr, #8]
// Exception return - LR_svc -> PC_usr, SPSR_svc -> CPSR
movs pc, lr


; CPSR_IF_MASK = 0xc0
; ARM_MODE_SVC = 0x13