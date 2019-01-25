!
! Copyright (c) 2002, 2016
!	The President and Fellows of Harvard College.
!
! Written by David A. Holland.
!
! Redistribution and use in source and binary forms, with or without
! modification, are permitted provided that the following conditions
! are met:
! 1. Redistributions of source code must retain the above copyright
!    notice, this list of conditions and the following disclaimer.
! 2. Redistributions in binary form must reproduce the above copyright
!    notice, this list of conditions and the following disclaimer in the
!    documentation and/or other materials provided with the distribution.
! 3. Neither the name of the University nor the names of its contributors
!    may be used to endorse or promote products derived from this software
!    without specific prior written permission.
!
! THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
! ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
! ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
! FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
! DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
! OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
! HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
! LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
! OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
! SUCH DAMAGE.
!

   .text

   /* test a block comment */
   /*
    * test a multiline comment
    */
   .globl _start
_start:
   call main		! does call have a delay slot? not sure (XXX)
    nop			
1:
   setuw 3, %g1		! code for exit (in OS/161)
   setuw 0, %o0		! exit(0)
   ta %xcc, 0		! software ("user") trap 0 is syscall
   ba 1b
    nop			! does ba have a delay slot? think so (XXX)

   .globl putchar
putchar:
   ! XXX this is not necessarily actually valid sparc asm; not sure
   ! how you make stack frames for real. (and I can't be bothered to
   ! go find out right now.) this is a leaf so it doesn't need a
   ! register window, but it does need a local.
   add %sp, -8, %sp	! make stack frame
   stb %o0, [%sp + 0]	! place the character
   setuw 55, %g1	! code for write (in OS/161)
   setuw 1, %o0		! STDOUT_FILENO
   mov %sp, %o1		! address of character
   setuw 1, %o2		! length of buffer (1)
   ta %xcc, 0		! do it (syscall)
   add %sp, 8, %sp	! clear stack frame
   ret			! return
    nop			! does ret have a delay slot? not sure (XXX)

   !!!!!!!!!!


