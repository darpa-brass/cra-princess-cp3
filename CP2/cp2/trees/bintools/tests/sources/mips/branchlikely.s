#
# Copyright (c) 2002, 2016
#	The President and Fellows of Harvard College.
#
# Written by David A. Holland.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. Neither the name of the University nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

   .text
   .globl __start
__start:
   #
   # Branch likely. These are not in std-allinsns.s because they
   # suck and are deprecated and in the long run will need some
   # flag or setting to be allowed.
   #

1:
   bc1fl 1b
   bc1fl $cc3, 2f
   bc1tl 1b
   bc1tl $cc3, 2f
1:
   bc2fl 1b
   bc2fl $cc3, 2f
   bc2tl 1b
   bc2tl $cc3, 2f
2:
   beql $t0, $t1, 1b
   bnel $t0, $t2, 2b
   bgezl $t3, 2b
   bgezall $t4, subr
   bgtzl $t5, 2b
   blezl $t6, 2b
   bltzl $t7, 2b
   bltzall $t4, subr

   #
   # With noreorder.
   #

   .set noreorder
1:
   bc1fl 1b
     nop
   bc1fl $cc3, 2f
     nop
   bc1tl 1b
     nop
   bc1tl $cc3, 2f
     nop
1:
   bc2fl 1b
     nop
   bc2fl $cc3, 2f
     nop
   bc2tl 1b
     nop
   bc2tl $cc3, 2f
     nop
2:
   beql $t0, $t1, 1b
     nop
   bnel $t0, $t2, 2b
     nop
   bgezl $t3, 2b
     nop
   bgezall $t4, subr
     nop
   bgtzl $t5, 2b
     nop
   blezl $t6, 2b
     nop
   bltzl $t7, 2b
     nop
   bltzall $t4, subr
     nop
   .set reorder

subr:
   jr $ra
