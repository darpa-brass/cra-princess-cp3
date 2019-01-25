!
! Copyright (c) 2002, 2016, 2018
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
   .globl __start
__start:
   ! all general-purpose registers by [giol]-name
   add %g0, %g1, %g2
   add %g1, %g2, %g3
   add %g2, %g3, %g4
   add %g3, %g4, %g5
   add %g4, %g5, %g6
   add %g5, %g6, %g7
   add %g6, %g7, %o0
   add %g7, %o0, %o1
   add %o0, %o1, %o2
   add %o1, %o2, %o3
   add %o2, %o3, %o4
   add %o3, %o4, %o5
   add %o4, %o5, %o6
   add %o5, %o6, %o7
   add %o6, %o7, %l0
   add %o7, %l0, %l1
   add %l0, %l1, %l2
   add %l1, %l2, %l3
   add %l2, %l3, %l4
   add %l3, %l4, %l5
   add %l4, %l5, %l6
   add %l5, %l6, %l7
   add %l6, %l7, %i0
   add %l7, %i0, %i1
   add %i0, %i1, %i2
   add %i1, %i2, %i3
   add %i2, %i3, %i4
   add %i3, %i4, %i5
   add %i4, %i5, %i6
   add %i5, %i6, %i7
   add %i6, %i7, %g0
   add %i7, %g0, %g1

   ! and also by r-name
   add %r0, %r1, %r2
   add %r1, %r2, %r3
   add %r2, %r3, %r4
   add %r3, %r4, %r5
   add %r4, %r5, %r6
   add %r5, %r6, %r7
   add %r6, %r7, %r8
   add %r7, %r8, %r9
   add %r8, %r9, %r10
   add %r9, %r10, %r11
   add %r10, %r11, %r12
   add %r11, %r12, %r13
   add %r12, %r13, %r14
   add %r13, %r14, %r15
   add %r14, %r15, %r16
   add %r15, %r16, %r17
   add %r16, %r17, %r18
   add %r17, %r18, %r19
   add %r18, %r19, %r20
   add %r19, %r20, %r21
   add %r20, %r21, %r22
   add %r21, %r22, %r23
   add %r22, %r23, %r24
   add %r23, %r24, %r25
   add %r24, %r25, %r26
   add %r25, %r26, %r27
   add %r26, %r27, %r28
   add %r27, %r28, %r29
   add %r28, %r29, %r30
   add %r29, %r30, %r31
   add %r30, %r31, %r0
   add %r31, %r0, %r1
