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
	.frame	$fp,40,$31		# vars= 8, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	.cprestore	16
	sw	$4,40($fp)
	sw	$0,24($fp)
	b	$L2
	nop

$L3:
	lw	$2,24($fp)
	nop
	move	$4,$2
	lw	$2,%call16(putchar)($28)
	nop
	move	$25,$2
	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,24($fp)
	nop
	addiu	$2,$2,1
	sw	$2,24($fp)
$L2:
	lw	$3,40($fp)
	lw	$2,24($fp)
	nop
	addu	$2,$3,$2
	lb	$2,0($2)
	nop
	bne	$2,$0,$L3
	nop

	li	$4,10			# 0xa
	lw	$2,%call16(putchar)($28)
	nop
	move	$25,$2
	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$2,40($fp)
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	puts
	.size	puts, .-puts
	.rdata
	.align	2
$LC0:
	.ascii	"Hello, world\000"
	.text
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
	.type	main, @function
main:
	.frame	$fp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	.cprestore	16
	lw	$2,%got($LC0)($28)
	nop
	addiu	$4,$2,%lo($LC0)
	lw	$2,%got(puts)($28)
	nop
	move	$25,$2
	jalr	$25
	nop

	lw	$28,16($fp)
	move	$2,$0
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.3"
