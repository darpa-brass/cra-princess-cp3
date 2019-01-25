	.cpu cortex-a8
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.arm
	.syntax divided
	.file	"hello.c"
	.text
	.align	2
	.global	puts
	.type	puts, %function
puts:
.LFB0:
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	.cfi_def_cfa_register 12
	stmfd	sp!, {fp, ip, lr, pc}
	.cfi_offset 11, -16
	.cfi_offset 13, -12
	.cfi_offset 14, -8
	sub	fp, ip, #4
	.cfi_def_cfa 11, 4
	sub	sp, sp, #16
	str	r0, [fp, #-24]
	mov	r3, #0
	str	r3, [fp, #-16]
	b	.L2
.L3:
	ldr	r3, [fp, #-16]
	mov	r0, r3
	bl	putchar
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L2:
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-16]
	add	r3, r2, r3
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3
	mov	r0, #10
	bl	putchar
	ldr	r3, [fp, #-24]
	mov	r0, r3
	sub	sp, fp, #12
	.cfi_def_cfa 13, 16
	ldmfd	sp, {fp, sp, pc}
	.cfi_endproc
.LFE0:
	.size	puts, .-puts
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Hello, world\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB1:
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	.cfi_def_cfa_register 12
	stmfd	sp!, {fp, ip, lr, pc}
	.cfi_offset 11, -16
	.cfi_offset 13, -12
	.cfi_offset 14, -8
	sub	fp, ip, #4
	.cfi_def_cfa 11, 4
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	puts
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (NetBSD nb1 20171112) 5.5.0"
