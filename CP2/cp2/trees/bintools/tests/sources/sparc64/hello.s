	.file	"hello.c"
	.section	".text"
	.align 4
	.global puts
	.type	puts, #function
	.proc	0102
puts:
.LLFB0:
	.cfi_startproc
	.register	%g2, #scratch
	save	%sp, -192, %sp
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	stx	%i0, [%fp+2175]
	st	%g0, [%fp+2043]
	ba,pt	%xcc, .LL2
	 nop
.LL3:
	ld	[%fp+2043], %g1
	sra	%g1, 0, %g1
	mov	%g1, %o0
	call	putchar, 0
	 nop
	ld	[%fp+2043], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+2043]
.LL2:
	ld	[%fp+2043], %g1
	srl	%g1, 0, %g1
	ldx	[%fp+2175], %g2
	add	%g2, %g1, %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 0
	bne	%icc, .LL3
	 nop
	mov	10, %o0
	call	putchar, 0
	 nop
	ldx	[%fp+2175], %g1
	mov	%g1, %i0
	return	%i7+8
	 nop
	.cfi_endproc
.LLFE0:
	.size	puts, .-puts
	.section	".rodata"
	.align 8
.LLC0:
	.asciz	"Hello, world"
	.section	".text"
	.align 4
	.global main
	.type	main, #function
	.proc	04
main:
.LLFB1:
	.cfi_startproc
	save	%sp, -176, %sp
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	sethi	%h44(.LLC0), %g1
	or	%g1, %m44(.LLC0), %g1
	sllx	%g1, 12, %g1
	or	%g1, %l44(.LLC0), %o0
	call	puts, 0
	 nop
	mov	0, %g1
	sra	%g1, 0, %g1
	mov	%g1, %i0
	return	%i7+8
	 nop
	.cfi_endproc
.LLFE1:
	.size	main, .-main
	.ident	"GCC: (NetBSD nb1 20180203) 6.4.0"
