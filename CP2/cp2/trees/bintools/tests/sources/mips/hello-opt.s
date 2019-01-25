	.file	1 "hello.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 1
	.abicalls
	.text
	.align	2
	.globl	puts
	.set	nomips16
	.ent	puts
	.type	puts, @function
puts:
	.frame	$sp,40,$31		# vars= 0, regs= 3/0, args= 16, gp= 8
	.mask	0x80030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$17,32($sp)
	sw	$16,28($sp)
	.cprestore	16
	sw	$31,36($sp)
	lb	$2,0($4)
	move	$17,$4
	beq	$2,$0,$L3
	move	$16,$0

$L7:
	lw	$25,%call16(putchar)($28)
	move	$4,$16
	jalr	$25
	addiu	$16,$16,1

	addu	$3,$17,$16
	lb	$3,0($3)
	lw	$28,16($sp)
	bne	$3,$0,$L7
	nop

$L3:
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	li	$4,10			# 0xa

	lw	$31,36($sp)
	move	$2,$17
	lw	$16,28($sp)
	lw	$17,32($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	puts
	.size	puts, .-puts
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"Hello, world\000"
	.section	.text.startup,"ax",@progbits
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
	.type	main, @function
main:
	.frame	$sp,32,$31		# vars= 0, regs= 1/0, args= 16, gp= 8
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	lw	$4,%got($LC0)($28)
	addiu	$sp,$sp,-32
	lw	$25,%got(puts)($28)
	sw	$31,28($sp)
	.cprestore	16
	jalr	$25
	addiu	$4,$4,%lo($LC0)

	lw	$31,28($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.3"
