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
   .set noat
   .globl __start
__start:
   # all general-purpose registers by symbolic name
   add $z0, $AT, $v0
   add $AT, $v0, $v1
   add $v0, $v1, $a0
   add $v1, $a0, $a1
   add $a0, $a1, $a2
   add $a1, $a2, $a3
   add $a2, $a3, $t0
   add $a3, $t0, $t1
   add $t0, $t1, $t2
   add $t1, $t2, $t3
   add $t2, $t3, $t4
   add $t3, $t4, $t5
   add $t4, $t5, $t6
   add $t5, $t6, $t7
   add $t6, $t7, $s0
   add $t7, $s0, $s1
   add $s0, $s1, $s2
   add $s1, $s2, $s3
   add $s2, $s3, $s4
   add $s3, $s4, $s5
   add $s4, $s5, $s6
   add $s5, $s6, $s7
   add $s6, $s7, $t8
   add $s7, $t8, $t9
   add $t8, $t9, $k0
   add $t9, $k0, $k1
   add $k0, $k1, $gp
   add $k1, $gp, $sp
   add $gp, $sp, $s8
   add $sp, $s8, $ra
   add $s8, $ra, $z0
   add $ra, $z0, $AT

   # and also by number
   add $0, $1, $2
   add $1, $2, $3
   add $2, $3, $4
   add $3, $4, $5
   add $4, $5, $6
   add $5, $6, $7
   add $6, $7, $8
   add $7, $8, $9
   add $8, $9, $10
   add $9, $10, $11
   add $10, $11, $12
   add $11, $12, $13
   add $12, $13, $14
   add $13, $14, $15
   add $14, $15, $16
   add $15, $16, $17
   add $16, $17, $18
   add $17, $18, $19
   add $18, $19, $20
   add $19, $20, $21
   add $20, $21, $22
   add $21, $22, $23
   add $22, $23, $24
   add $23, $24, $25
   add $24, $25, $26
   add $25, $26, $27
   add $26, $27, $28
   add $27, $28, $29
   add $28, $29, $30
   add $29, $30, $31
   add $30, $31, $0
   add $31, $0, $1
