@
@ Copyright (c) 2002, 2016
@	The President and Fellows of Harvard College.
@
@ Written by David A. Holland.
@
@ Redistribution and use in source and binary forms, with or without
@ modification, are permitted provided that the following conditions
@ are met:
@ 1. Redistributions of source code must retain the above copyright
@    notice, this list of conditions and the following disclaimer.
@ 2. Redistributions in binary form must reproduce the above copyright
@    notice, this list of conditions and the following disclaimer in the
@    documentation and/or other materials provided with the distribution.
@ 3. Neither the name of the University nor the names of its contributors
@    may be used to endorse or promote products derived from this software
@    without specific prior written permission.
@
@ THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
@ ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
@ IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
@ ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
@ FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
@ DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
@ OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
@ HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
@ LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
@ OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
@ SUCH DAMAGE.
@

   .text
   .globl __start
__start:
   @
   @ 1. arithmetic
   @

   @ 1a. arithmetic with immediate forms
   @ for each, try
   @    - the three-register form
   @    - the two-register form where the destination is one of the sources
   @
   @	- the explicit immediate form with a small immediate
   @	- the explicit immediate form with a u16 or negative s16 immediate
   @	  (u16 if the field is 0-extended, negative s16 if sign-extended)
   @
   @    - the implicit immediate form with a small immediate
   @    - the implicit immediate form with a u16 immediate
   @    - the implicit immediate form with a negative s16 immediate
   @    - the implicit immediate form with a large (> u16) immediate
   @
   @    - the explicit immediate form with a small symbolic immediate
   @    - the implicit immediate form with a small symbolic immediate
   @    - the implicit immediate form with a full symbolic immediate
   @
   @ the arithmetic ops are:	
   @   add/addi   addu/addiu   sub/subi*  subu/subiu*
   @   and/andi   or/ori       xor/xori   nor/nori*
   @   seq*/seqi* sne*/snei*
   @   sgt*/sgti* sgtu*/sgtiu* sge*/sgei* sgeu*/sgeiu*
   @   slt/slti   sltu/sltiu   sle*/slei* sleu*/sleiu* 
   @
   @ (* indicates instructions that exist only as macros)
   @
   @ Note that gas doesn't have seqi/snei/sgti/sgtiu/sgei/sgeiu/slei/sleiu,
   @ but it does have the immediate macro forms of e.g. sge (so we
   @ probably need to as well) with the result that there's little to
   @ be gained by breaking the overall pattern.
   @

   @ add/addi
_add:
   add $t1, $t0, $v0
   add $t1, $t0
   addi $t2, $t0, 5
   addi $t3, $t0, -400
   add $t4, $t0, 1
   add $t5, $t0, 0x8070
   add $t6, $t0, -400
   add $t7, $t0, 0x40506070
   addi $t8, $t0, %lo(datum)
   nop @add $a0, $t0, %lo(datum)
   nop @add $a1, $t0, datum
   @ addu/addiu
_addu:
   addu $t1, $t0, $v0
   addu $t1, $t0
   addiu $t2, $t0, 5
   addiu $t3, $t0, -400
   addu $t4, $t0, 1
   addu $t5, $t0, 0x8070
   addu $t6, $t0, -400
   addu $t7, $t0, 0x40506070
   addiu $t8, $t0, %lo(datum)
   nop @addu $a0, $t0, %lo(datum)
   nop @addu $a1, $t0, datum
   @ sub/subi*
_sub:
   sub $t1, $t0, $v0
   sub $t1, $t0
   subi $t2, $t0, 5
   subi $t3, $t0, -400
   sub $t4, $t0, 1
   sub $t5, $t0, 0x8070
   sub $t6, $t0, -400
   sub $t6, $t0, 0x40506070
   subi $a0, $t0, %lo(datum)
   nop @ sub $a0, $t0, %lo(datum)
   nop @ sub $a1, $t0, datum
   @ subu/subiu*
_subu:
   subu $t1, $t0, $v0
   subu $t1, $t0
   subiu $t2, $t0, 5
   subiu $t3, $t0, -400
   subu $t4, $t0, 1
   subu $t5, $t0, 0x8070
   subu $t6, $t0, -400
   subu $t6, $t0, 0x40506070
   subiu $a0, $t0, %lo(datum)
   nop @ subu $a0, $t0, %lo(datum)
   nop @ subu $a1, $t0, datum

   @ and/andi
_and:
   and $t1, $t0, $v0
   and $t1, $t0
   andi $t2, $t0, 16
   andi $t3, $t0, 0xaabb
   and $t4, $t0, 8
   and $t5, $t0, 0x8070
   and $t6, $t0, -400
   and $t7, $t0, 0x40506070
   andi $t8, $t0, %hi(datum)
   nop @and $a0, $t0, %lo(datum)
   nop @and $a1, $t0, datum
   @ or/ori
_or:
   or $t1, $t0, $v0
   or $t1, $t0
   ori $t2, $t0, 16
   ori $t3, $t0, 0xaabb
   or $t4, $t0, 8
   or $t5, $t0, 0x8070
   or $t6, $t0, -400
   or $t7, $t0, 0x40506070
   ori $t8, $t0, %hi(datum)
   nop @or $a0, $t0, %lo(datum)
   nop @or $a1, $t0, datum
   @ xor/xori
_xor:
   xor $t1, $t0, $v0
   xor $t1, $t0
   xori $t2, $t0, 16
   xori $t3, $t0, 0xaabb
   xor $t4, $t0, 8
   xor $t5, $t0, 0x8070
   xor $t6, $t0, -400
   xor $t7, $t0, 0x40506070
   xori $t8, $t0, %hi(datum)
   nop @xor $a0, $t0, %lo(datum)
   nop @xor $a1, $t0, datum
   @ nor/nori*
_nor:
   nor $t0, $t1, $t2
   nor $t1, $t0
   nori $t2, $t0, 16
   nori $t3, $t0, 0xaabb
   nor $t4, $t0, 8
   nor $t5, $t0, 0x8070
   nor $t6, $t0, -400
   nor $t7, $t0, 0x40506070
   nori $t8, $t0, %hi(datum)
   nop @nor $a0, $t0, %lo(datum)
   nop @nor $a1, $t0, datum

   @ seq/seqi
_seq:
   seq $t1, $t0, $v0
   seq $t1, $t0
   seqi $t2, $t0, 16
   seqi $t3, $t0, 0xaabb
   seq $t4, $t0, 8
   seq $t5, $t0, 0x8070
   seq $t6, $t0, -400
   seq $t7, $t0, 0x40506070
   seqi $t8, $t0, %hi(datum)
   nop @seq $a0, $t0, %lo(datum)
   nop @seq $a1, $t0, datum
   @ sne/snei
_sne:
   sne $t1, $t0, $v0
   sne $t1, $t0
   snei $t2, $t0, 16
   snei $t3, $t0, 0xaabb
   sne $t4, $t0, 8
   sne $t5, $t0, 0x8070
   sne $t6, $t0, -400
   sne $t7, $t0, 0x40506070
   snei $t8, $t0, %hi(datum)
   nop @sne $a0, $t0, %lo(datum)
   nop @sne $a1, $t0, datum

   @ sgt/sgti
_sgt:
   sgt $t1, $t0, $v0
   sgt $t1, $t0
   sgti $t2, $t0, 16
   sgti $t3, $t0, -400
   sgt $t4, $t0, 8
   sgt $t5, $t0, 0x8070
   sgt $t6, $t0, -400
   sgt $t7, $t0, 0x40506070
   sgti $t8, $t0, %lo(datum)
   nop @sgt $a0, $t0, %lo(datum)
   nop @sgt $a1, $t0, datum
   @ sgtu/sgtiu
_sgtu:
   sgtu $t1, $t0, $v0
   sgtu $t1, $t0
   sgtiu $t2, $t0, 16
   sgtiu $t3, $t0, -400
   sgtu $t4, $t0, 8
   sgtu $t5, $t0, 0x8070
   sgtu $t6, $t0, -400
   sgtu $t7, $t0, 0x40506070
   sgtiu $t8, $t0, %lo(datum)
   nop @sgtu $a0, $t0, %lo(datum)
   nop @sgtu $a1, $t0, datum
   @ sge/sgei
_sge:
   sge $t1, $t0, $v0
   sge $t1, $t0
   sgei $t2, $t0, 16
   sgei $t3, $t0, -400
   sge $t4, $t0, 8
   sge $t5, $t0, 0x8070
   sge $t6, $t0, -400
   sge $t7, $t0, 0x40506070
   sgei $t8, $t0, %lo(datum)
   nop @sge $a0, $t0, %lo(datum)
   nop @sge $a1, $t0, datum
   @ sgeu/sgeiu
_sgeu:
   sgeu $t1, $t0, $v0
   sgeu $t1, $t0
   sgeiu $t2, $t0, 16
   sgeiu $t3, $t0, -400
   sgeu $t4, $t0, 8
   sgeu $t5, $t0, 0x8070
   sgeu $t6, $t0, -400
   sgeu $t7, $t0, 0x40506070
   sgeiu $t8, $t0, %lo(datum)
   nop @sgeu $a0, $t0, %lo(datum)
   nop @sgeu $a1, $t0, datum
   
   @ slt/slti
_slt:
   slt $t1, $t0, $v0
   slt $t1, $t0
   slti $t2, $t0, 16
   slti $t3, $t0, -400
   slt $t4, $t0, 8
   slt $t5, $t0, 0x8070
   slt $t6, $t0, -400
   slt $t7, $t0, 0x40506070
   slti $t8, $t0, %lo(datum)
   nop @slt $a0, $t0, %lo(datum)
   nop @slt $a1, $t0, datum
   @ sltu/sltiu
_sltu:
   sltu $t1, $t0, $v0
   sltu $t1, $t0
   sltiu $t2, $t0, 16
   sltiu $t3, $t0, -400
   sltu $t4, $t0, 8
   sltu $t5, $t0, 0x8070
   sltu $t6, $t0, -400
   sltu $t7, $t0, 0x40506070
   sltiu $t8, $t0, %lo(datum)
   nop @sltu $a0, $t0, %lo(datum)
   nop @sltu $a1, $t0, datum
   @ sle/slei
_sle:
   sle $t1, $t0, $v0
   sle $t1, $t0
   slei $t2, $t0, 16
   slei $t3, $t0, -400
   sle $t4, $t0, 8
   sle $t5, $t0, 0x8070
   sle $t6, $t0, -400
   sle $t7, $t0, 0x40506070
   slei $t8, $t0, %lo(datum)
   nop @sle $a0, $t0, %lo(datum)
   nop @sle $a1, $t0, datum
   @ sleu/sleiu
_sleu:
   sleu $t1, $t0, $v0
   sleu $t1, $t0
   sleiu $t2, $t0, 16
   sleiu $t3, $t0, -400
   sleu $t4, $t0, 8
   sleu $t5, $t0, 0x8070
   sleu $t6, $t0, -400
   sleu $t7, $t0, 0x40506070
   sleiu $t8, $t0, %lo(datum)
   nop @sleu $a0, $t0, %lo(datum)
   nop @sleu $a1, $t0, datum

   @
   @ 1b. shift instructions
   @

   @ sll/sllv
_sll:
   sll $v0, $v1, 6
   sll $v0, $v1, $a0
   sllv $v0, $v1, $a0

   @ srl/srlv
_srl:
   srl $v0, $v1, 6
   srl $v0, $v1, $a0
   srlv $v0, $v1, $a0

   @ sra/srav
_sra:
   sra $v0, $v1, 6
   sra $v0, $v1, $a0
   srav $v0, $v1, $a0

   @ rol
_rol:
   rol $v0, $a0, $a1
   rol $v0, $a0, 4

   @ ror
_ror:
   ror $v0, $a0, $a1
   ror $v0, $a0, 4

   @
   @ 1c. multiply and divide
   @

   @ div/divu
   @
   @ The deal with div is that div $0, $v0, $v1 gives you the raw
   @ divide instruction. Otherwise you get the macro with the
   @ various tests. And div $v0, $v1 is short for div $v0, $v0, $v1.
   @ (Same for divu, though obviously the macro is different..)
   @
_div:
   div $0, $v0, $v1
   divu $0, $a0, $a1
   div $t0, $v0, $v1
   divu $t0, $a0, $a1
   div $v0, $v1
   divu $a0, $a1
   @ madd/maddu
_madd:
   madd $v0, $v1
   maddu $a0, $a1
   @ msub/msubu
_msub:
   msub $v0, $v1
   msubu $a0, $a1
   @ mul
_mul:
   mul $t0, $t1, $t2
   @ mult/multu
_mult:
   mult $v0, $v1
   multu $a0, $a1

   @
   @ 1d. miscellaneous arithmetic / integer ops without immediate forms
   @

   @ abs (macro)
_abs:
   abs $v0, $v1
   abs $v0
   @ clo, clz
_clo:
   clo $t3, $t4
   clz $t4, $t5
   @ movn/movz
_movn:
   movn $6, $8, $10
   movz $6, $8, $10
   @ neg/negu expands to sub/subu
_neg:
   neg $v0, $v1
   neg $v0
   negu $v0, $v1
   negu $v0
   @ not expands to nor
_not:
   not $v0, $v1
   not $v0

   @
   @ 2. branches
   @
_branches:
1:
   b 1f
   bal subr
   bc1f 1b
   bc1f $cc3, 2f
   bc1t 1b
   bc1t $cc3, 2f
1:
   bc2f 1b
   bc2f $cc3, 2f
   bc2t 1b
   bc2t $cc3, 2f
2:
   beq $t0, $t1, 1b
   bne $t0, $t2, 2b
   bgez $t3, 2b
   bgezal $t4, subr
   bgtz $t5, 2b
   blez $t6, 2b
   bltz $t7, 2b
   bltzal $t4, subr

   @
   @ 2a. branches again, with noreorder
   @

   .set noreorder
_branches_again:
1:
   b 1f
     nop
   bal subr
     nop
   bc1f 1b
     nop
   bc1f $cc3, 2f
     nop
   bc1t 1b
     nop
   bc1t $cc3, 2f
     nop
1:
   bc2f 1b
     nop
   bc2f $cc3, 2f
     nop
   bc2t 1b
     nop
   bc2t $cc3, 2f
     nop
2:
   beq $t0, $t1, 1b
     nop
   bne $t0, $t2, 2b
     nop
   bgez $t3, 2b
     nop
   bgezal $t4, subr
     nop
   bgtz $t5, 2b
     nop
   blez $t6, 2b
     nop
   bltz $t7, 2b
     nop
   bltzal $t4, subr
     nop
   .set reorder

   @
   @ 3. jumps
   @
_jumps:
   j 1f
   j $v0
   jr $v1
1:
   jal subr
   jal $v0
   jalr $v0
   jal $0, subr
   jal $v0, subr
   jalr $0, $v0
   .set noreorder
   j 1f
     nop
   j $v0
     nop
   jr $v1
     nop
1:
   jal subr
     nop
   jal $v0
     nop
   jalr $v0
     nop
   jal $0, subr
     nop
   jal $v0, subr
     nop
   jalr $0, $v0
     nop
   .set reorder

   @
   @ 4. memory
   @
_lui:
   lui $v0, 0xffff
   lui $v0, %hi(datum)
_cache:
   cache 17, 0($t0)
   cache 17, 16($t0)
   cache 17, %lo(datum)($t0)
   cache 17, datum
_pref:
   pref 17, 0($t0)
   pref 17, 16($t0)
   pref 17, %lo(datum)($t0)
   pref 17, datum
_lb:
   lb $v0, 0($t0)
   lb $v0, 17($t0)
   lb $v0, %lo(datum)($t0)
   lb $v0, datum
_lbu:
   lbu $v0, 0($t0)
   lbu $v0, 17($t0)
   lbu $v0, %lo(datum)($t0)
   lbu $v0, datum
_lh:	
   lh $v0, 0($t0)
   lh $v0, 17($t0)
   lh $v0, %lo(datum)($t0)
   lh $v0, datum
_lhu:
   lhu $v0, 0($t0)
   lhu $v0, 17($t0)
   lhu $v0, %lo(datum)($t0)
   lhu $v0, datum
_lw:
   lw $v0, 0($t0)
   lw $v0, 17($t0)
   lw $v0, %lo(datum)($t0)
   lw $v0, datum
_lwl:
   lwl $v0, 0($t0)
   lwl $v0, 17($t0)
   lwl $v0, %lo(datum)($t0)
   lwl $v0, datum
_lwr:
   lwr $v0, 0($t0)
   lwr $v0, 17($t0)
   lwr $v0, %lo(datum)($t0)
   lwr $v0, datum
_ll:
   ll $v0, 0($t0)
   ll $v0, 17($t0)
   ll $v0, %lo(datum)($t0)
   ll $v0, datum
_lwc1:
   lwc1 $f2, 0($t0)
   lwc1 $f2, 17($t0)
   lwc1 $f2, %lo(datum)($t0)
   lwc1 $f2, datum
_lwc2:
   lwc2 $c2.2, 0($t0)
   lwc2 $c2.2, 17($t0)
   lwc2 $c2.2, %lo(datum)($t0)
   lwc2 $c2.2, datum
_ldc1:
   ldc1 $f2, 0($t0)
   ldc1 $f2, 17($t0)
   ldc1 $f2, %lo(datum)($t0)
   ldc1 $f2, datum
_ldc2:
   ldc2 $c2.2, 0($t0)
   ldc2 $c2.2, 17($t0)
   ldc2 $c2.2, %lo(datum)($t0)
   ldc2 $c2.2, datum
_sb:
   sb $v0, 0($t0)
   sb $v0, 17($t0)
   sb $v0, %lo(datum)($t0)
   sb $v0, datum
_sh:
   sh $v0, 0($t0)
   sh $v0, 17($t0)
   sh $v0, %lo(datum)($t0)
   sh $v0, datum
_sw:
   sw $v0, 0($t0)
   sw $v0, 17($t0)
   sw $v0, %lo(datum)($t0)
   sw $v0, datum
_swl:
   swl $v0, 0($t0)
   swl $v0, 17($t0)
   swl $v0, %lo(datum)($t0)
   swl $v0, datum
_swr:
   swr $v0, 0($t0)
   swr $v0, 17($t0)
   swr $v0, %lo(datum)($t0)
   swr $v0, datum
_sc:
   sc $v0, 0($t0)
   sc $v0, 17($t0)
   sc $v0, %lo(datum)($t0)
   sc $v0, datum
_swc1:
   swc1 $f2, 0($t0)
   swc1 $f2, 17($t0)
   swc1 $f2, %lo(datum)($t0)
   swc1 $f2, datum
_swc2:
   swc2 $c2.2, 0($t0)
   swc2 $c2.2, 17($t0)
   swc2 $c2.2, %lo(datum)($t0)
   swc2 $c2.2, datum
_sdc1:
   sdc1 $f2, 0($t0)
   sdc1 $f2, 17($t0)
   sdc1 $f2, %lo(datum)($t0)
   sdc1 $f2, datum
_sdc2:
   sdc2 $c2.2, 0($t0)
   sdc2 $c2.2, 17($t0)
   sdc2 $c2.2, %lo(datum)($t0)
   sdc2 $c2.2, datum

_ulw:
   ulw $2, 0($t0)
   ulw $2, 17($t0)
   ulw $2, %lo(datum)($t0)
   ulw $2, datum
_usw:
   usw $2, 0($t0)
   usw $2, 17($t0)
   usw $2, %lo(datum)($t0)
   usw $2, datum


   @
   @ 5. conditional traps
   @
_tge:
   tge $v0, $v1
   tge $v0, $v1, 16
   tgei $v0, 12345
   tge $v0, 12345
_tgeu:
   tgeu $v0, $v1
   tgeu $v0, $v1, 16
   tgeiu $v0, 12345
   tgeu $v0, 12345
_tlt:
   tlt $v0, $v1
   tlt $v0, $v1, 16
   tlti $v0, 12345
   tlt $v0, 12345
_tltu:
   tltu $v0, $v1
   tltu $v0, $v1, 16
   tltiu $v0, 12345
   tltu $v0, 12345
_teq:
   teq $v0, $v1
   teq $v0, $v1, 16
   teqi $v0, 12345
   teq $v0, 12345
_tne:
   tne $v0, $v1
   tne $v0, $v1, 16
   tnei $v0, 12345
   tne $v0, 12345

   @
   @ 6. supervisor (cop0)
   @
_cop0:
   deret
   eret
   rfe
   mfc0 $4, $c0.5
   mtc0 $5, $c0.4
   mfc0 $4, $c0.5, 3
   mtc0 $5, $c0.4, 3
   tlbp
   tlbr
   tlbwi
   tlbwr
   wait

   @
   @ 7. floating point (cop1)
   @
_cop1:
   cfc1 $5, $f6
   ctc1 $7, $f8
   mfc1 $4, $f5
   mtc1 $5, $f4

_abs_s:
   abs.s $f6, $f7
   abs.d $f6, $f8
   add.s $f6, $f7, $f8
   add.d $f6, $f8, $f10
   ceil.w.s $f6, $f7
   ceil.w.d $f6, $f8
   cvt.d.s $f6, $f8
   cvt.d.w $f6, $f8
   @cvt.d.l $f6, $f8  @ 64-bit only (XXX)
   cvt.s.d $f6, $f8
   cvt.s.w $f6, $f8
   @cvt.s.l $f6, $f8  @ 64-bit only (XXX)
   cvt.w.s $f6, $f8
   cvt.w.d $f6, $f8
   div.s $f6, $f7, $f8
   div.d $f6, $f8, $f10
   floor.w.s $f6, $f7
   floor.w.d $f6, $f8
_mov_s:
   mov.s $f6, $f7
   mov.d $f6, $f8
   movf $6, $8, $cc4
   movf.s $f6, $f7, $cc4
   movf.d $f6, $f8, $cc4
   movt $6, $8, $cc4
   movt.s $f6, $f7, $cc4
   movt.d $f6, $f8, $cc4
   movn.s $f6, $f7, $10
   movn.d $f6, $f8, $10
   movz.s $f6, $f7, $10
   movz.d $f6, $f8, $10
_mul_s:
   mul.s $f6, $f7, $f8
   mul.d $f6, $f8, $f10
   neg.s $f6, $f7
   neg.d $f6, $f8
   round.w.s $f6, $f7
   round.w.d $f6, $f8
   sqrt.s $f6, $f7
   sqrt.d $f6, $f8
   sub.s $f6, $f7, $f8
   sub.d $f6, $f8, $f10
   trunc.w.s $f6, $f7
   trunc.w.d $f6, $f8
_c:
   c.f.s $f6, $f7
   c.f.s $cc2, $f6, $f7
   c.f.d $f6, $f8
   c.f.d $cc2, $f6, $f8
   c.un.s $f6, $f7
   c.un.s $cc2, $f6, $f7
   c.un.d $f6, $f8
   c.un.d $cc2, $f6, $f8
   c.eq.s $f6, $f7
   c.eq.s $cc2, $f6, $f7
   c.eq.d $f6, $f8
   c.eq.d $cc2, $f6, $f8
   c.ueq.s $f6, $f7
   c.ueq.s $cc2, $f6, $f7
   c.ueq.d $f6, $f8
   c.ueq.d $cc2, $f6, $f8
   c.olt.s $f6, $f7
   c.olt.s $cc2, $f6, $f7
   c.olt.d $f6, $f8
   c.olt.d $cc2, $f6, $f8
   c.ult.s $f6, $f7
   c.ult.s $cc2, $f6, $f7
   c.ult.d $f6, $f8
   c.ult.d $cc2, $f6, $f8
   c.ole.s $f6, $f7
   c.ole.s $cc2, $f6, $f7
   c.ole.d $f6, $f8
   c.ole.d $cc2, $f6, $f8
   c.ule.s $f6, $f7
   c.ule.s $cc2, $f6, $f7
   c.ule.d $f6, $f8
   c.ule.d $cc2, $f6, $f8
   c.sf.s $f6, $f7
   c.sf.s $cc2, $f6, $f7
   c.sf.d $f6, $f8
   c.sf.d $cc2, $f6, $f8
   c.ngle.s $f6, $f7
   c.ngle.s $cc2, $f6, $f7
   c.ngle.d $f6, $f8
   c.ngle.d $cc2, $f6, $f8
   c.seq.s $f6, $f7
   c.seq.s $cc2, $f6, $f7
   c.seq.d $f6, $f8
   c.seq.d $cc2, $f6, $f8
   c.ngl.s $f6, $f7
   c.ngl.s $cc2, $f6, $f7
   c.ngl.d $f6, $f8
   c.ngl.d $cc2, $f6, $f8
   c.lt.s $f6, $f7
   c.lt.s $cc2, $f6, $f7
   c.lt.d $f6, $f8
   c.lt.d $cc2, $f6, $f8
   c.nge.s $f6, $f7
   c.nge.s $cc2, $f6, $f7
   c.nge.d $f6, $f8
   c.nge.d $cc2, $f6, $f8
   c.le.s $f6, $f7
   c.le.s $cc2, $f6, $f7
   c.le.d $f6, $f8
   c.le.d $cc2, $f6, $f8
   c.ngt.s $f6, $f7
   c.ngt.s $cc2, $f6, $f7
   c.ngt.d $f6, $f8
   c.ngt.d $cc2, $f6, $f8

   @
   @ 8. cop2 and cop3
   @
_cop2:
   cfc2 $5, $c2.6
   ctc2 $7, $c2.8
   cop2 0
   cop2 0x1ffffff
   mfc2 $4, $c2.5
   mtc2 $5, $c2.4
   mfc2 $4, $c2.5, 3
   mtc2 $5, $c2.4, 3

   @
   @ 9. misc
   @
_break:
   break
   @ apparently break takes two 10-bit numbers instead of one 20-bit number
   break 0x6
   break 0x6,0xeb
   sdbbp
   sdbbp 1771
   syscall
   syscall 1771
_mvhilo:
   mfhi $v0
   mflo $v1
   mthi $t0
   mtlo $t1
_nop:
   nop
   ssnop
   sync

   @
   @ 10. misc macros
   @

_lc:
   move	$v0, $v1
   la	$v0, datum
   li   $v0, 0
   li   $v0, 0x1
   li   $v0, -0x1
   li   $v0, -0xbeef
   li   $v0, 0xbeef
   li   $v0, 0xdead0000
   li	$v0, 0xdeadbeef

   @ b appears in the branches section
   @ bal appears in the branches section
   @beqz $v0, 1f
   @bnez $v0, 1f
   @bge $v0, $v1, 1f
   @bgel $v0, $v1, 1f
   @bgeu $v0, $v1, 1f
   @bgeul $v0, $v1, 1f
   @bgt $v0, $v1, 1f
   @bgtl $v0, $v1, 1f
   @bgtu $v0, $v1, 1f
   @bgtul $v0, $v1, 1f
   @ble $v0, $v1, 1f
   @blel $v0, $v1, 1f
   @bleu $v0, $v1, 1f
   @bleul $v0, $v1, 1f
   @blt $v0, $v1, 1f
   @bltl $v0, $v1, 1f
   @bltu $v0, $v1, 1f
   @bltul $v0, $v1, 1f
   @
   @beq $v0, 12345, label
   @bne $v0, 12345, label
   @bge $v0, 12345, label
   @bgeu $v0, 12345, label
   @bgt $v0, 12345, label
   @bgtu $v0, 12345, label
   @ble $v0, 12345, label
   @bleu $v0, 12345, label
   @blt $v0, 12345, label
   @bltu $v0, 12345, label
   @
   @ these are messy
   @div $v0, $a0, $a1
   @divu $v0, $a0, $a1
   @mul $v0, $a0, $a1 @ XXX for old mips expands to multu and mflo
   @mulo $v0, $a0, $a1
   @mulou $v0, $a0, $a1
   @rem $v0, $a0, $a1
   @remu $v0, $a0, $a1
   @
   @ XXX the memory ops above should have lw $t0, 0xdeadbeef($t1)
   @ (supposed to be able to expand large offsets)
   @
   @l.s $f4, datum
   @s.s $f4, datum
   @l.d $f4, datum  (which expands differently depending fpu type)
   @s.d $f4, datum  (which expands differently depending fpu type)
   @ XXX are l.s $f4, offset($t0) etc. supposed to exist?
   @
   @ XXX for mips-I teq et al. are supposed to expand to a branch
   @ around a break instruction.
   @
   @abs.d $f6
   @neg.d $f6
   @cvt.d.s $f6
   @cvt.d.l $f6
   @cvt.d.w $f6
   @cvt.s.d $f6
   @cvt.s.l $f6
   @cvt.s.w $f6
   @cvt.l.d $f6
   @cvt.l.s $f6
   @cvt.w.d $f6
   @cvt.w.s $f6
   @
   @ XXX apparently on mips1 ceil.w.*, floor.w.*, round.w.*, and
   @ trunc.w.* are supposed to expand to macros that save the fpu
   @ control word, set the rounding mode, and do cvt.w.*.
   @
   @add.d $f6, $f8
   @div.d $f6, $f8
   @mul.d $f6, $f8
   @sub.d $f6, $f8
   @ the .s forms for these aren't listed but should obviously exist
   @
   @ XXX the old idt mips doc refers to a recip.s / recip.d in mips-iv
   @ (that does 1/x): recip.d $f6, $f8
   @ and also a rsqrt.[ds] that does 1/sqrt(x).
   @
   @mtc1.d $v0, $f6  @ move a pair (XXX will depend on fpu type)
   @
   @li.d $a0, imm	@ XXX what format is imm here?
   @li.d $f4, imm
   @li.s $a0, imm
   @li.s $f4, imm
   @

subr:
   jr $ra

   .data
datum:
   .word 0x01234567
