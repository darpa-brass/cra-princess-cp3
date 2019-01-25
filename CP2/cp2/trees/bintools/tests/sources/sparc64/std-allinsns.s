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
   .globl __start
__start:
   !
   ! 1. arithmetic
   !

   ! 1a. arithmetic with immediate forms
   ! for each, try
   !    - the three-register form
   !    - the immediate form with a positive immediate
   !    - the immediate form with a negative immediate
   !    - the immediate form with a %lo immediate
   !    - the immediate form with a %ulo immediate
   !
   ! the arithmetic ops are:
   !   add addcc addc addccc sub subcc subc subccc
   !   and andcc andn andncc or  orcc  orn  orncc
   !   xor xorcc xnor xnorcc
   !   taddcc taddcctv tsubcc tsubcctv
   !   umul umulcc smul smulcc mulscc
   !   udiv udivcc sdiv sdivcc
   !   mulx sdivx udivx
   !   save restore
   !   popc (which has no first register)
   !

   ! add
_add:
   add %l1, %l0, %o0
   add %l1, 5, %o0
   add %l1, -17, %o0
   add %l1, %lo(datum), %o0
   add %l1, %ulo(datum), %o0
   ! addcc
_addcc:
   addcc %l1, %l0, %o0
   addcc %l1, 5, %o0
   addcc %l1, -17, %o0
   addcc %l1, %lo(datum), %o0
   addcc %l1, %ulo(datum), %o0
   ! addc
_addc:
   addc %l1, %l0, %o0
   addc %l1, 5, %o0
   addc %l1, -17, %o0
   addc %l1, %lo(datum), %o0
   addc %l1, %ulo(datum), %o0
   ! addccc
_addccc:
   addccc %l1, %l0, %o0
   addccc %l1, 5, %o0
   addccc %l1, -17, %o0
   addccc %l1, %lo(datum), %o0
   addccc %l1, %ulo(datum), %o0
   ! sub
_sub:
   sub %l1, %l0, %o0
   sub %l1, 5, %o0
   sub %l1, -17, %o0
   sub %l1, %lo(datum), %o0
   sub %l1, %ulo(datum), %o0
   ! subcc
_subcc:
   subcc %l1, %l0, %o0
   subcc %l1, 5, %o0
   subcc %l1, -17, %o0
   subcc %l1, %lo(datum), %o0
   subcc %l1, %ulo(datum), %o0
   ! subc
_subc:
   subc %l1, %l0, %o0
   subc %l1, 5, %o0
   subc %l1, -17, %o0
   subc %l1, %lo(datum), %o0
   subc %l1, %ulo(datum), %o0
   ! subccc
_subccc:
   subccc %l1, %l0, %o0
   subccc %l1, 5, %o0
   subccc %l1, -17, %o0
   subccc %l1, %lo(datum), %o0
   subccc %l1, %ulo(datum), %o0
   ! and
_and:
   and %l1, %l0, %o0
   and %l1, 5, %o0
   and %l1, -17, %o0
   and %l1, %lo(datum), %o0
   and %l1, %ulo(datum), %o0
   ! andcc
_andcc:
   andcc %l1, %l0, %o0
   andcc %l1, 5, %o0
   andcc %l1, -17, %o0
   andcc %l1, %lo(datum), %o0
   andcc %l1, %ulo(datum), %o0
   ! andn
_andn:
   andn %l1, %l0, %o0
   andn %l1, 5, %o0
   andn %l1, -17, %o0
   andn %l1, %lo(datum), %o0
   andn %l1, %ulo(datum), %o0
   ! andncc
_andncc:
   andncc %l1, %l0, %o0
   andncc %l1, 5, %o0
   andncc %l1, -17, %o0
   andncc %l1, %lo(datum), %o0
   andncc %l1, %ulo(datum), %o0
   ! or
_or:
   or %l1, %l0, %o0
   or %l1, 5, %o0
   or %l1, -17, %o0
   or %l1, %lo(datum), %o0
   or %l1, %ulo(datum), %o0
   ! orcc
_orcc:
   orcc %l1, %l0, %o0
   orcc %l1, 5, %o0
   orcc %l1, -17, %o0
   orcc %l1, %lo(datum), %o0
   orcc %l1, %ulo(datum), %o0
   ! orn
_orn:
   orn %l1, %l0, %o0
   orn %l1, 5, %o0
   orn %l1, -17, %o0
   orn %l1, %lo(datum), %o0
   orn %l1, %ulo(datum), %o0
   ! orncc
_orncc:
   orncc %l1, %l0, %o0
   orncc %l1, 5, %o0
   orncc %l1, -17, %o0
   orncc %l1, %lo(datum), %o0
   orncc %l1, %ulo(datum), %o0
   ! xor
_xor:
   xor %l1, %l0, %o0
   xor %l1, 5, %o0
   xor %l1, -17, %o0
   xor %l1, %lo(datum), %o0
   xor %l1, %ulo(datum), %o0
   ! xorcc
_xorcc:
   xorcc %l1, %l0, %o0
   xorcc %l1, 5, %o0
   xorcc %l1, -17, %o0
   xorcc %l1, %lo(datum), %o0
   xorcc %l1, %ulo(datum), %o0
   ! xnor
_xnor:
   xnor %l1, %l0, %o0
   xnor %l1, 5, %o0
   xnor %l1, -17, %o0
   xnor %l1, %lo(datum), %o0
   xnor %l1, %ulo(datum), %o0
   ! xnorcc
_xnorcc:
   xnorcc %l1, %l0, %o0
   xnorcc %l1, 5, %o0
   xnorcc %l1, -17, %o0
   xnorcc %l1, %lo(datum), %o0
   xnorcc %l1, %ulo(datum), %o0
   ! taddcc
_taddcc:
   taddcc %l1, %l0, %o0
   taddcc %l1, 5, %o0
   taddcc %l1, -17, %o0
   taddcc %l1, %lo(datum), %o0
   taddcc %l1, %ulo(datum), %o0
   ! taddcctv
_taddcctv:
   taddcctv %l1, %l0, %o0
   taddcctv %l1, 5, %o0
   taddcctv %l1, -17, %o0
   taddcctv %l1, %lo(datum), %o0
   taddcctv %l1, %ulo(datum), %o0
   ! tsubcc
_tsubcc:
   tsubcc %l1, %l0, %o0
   tsubcc %l1, 5, %o0
   tsubcc %l1, -17, %o0
   tsubcc %l1, %lo(datum), %o0
   tsubcc %l1, %ulo(datum), %o0
   ! tsubcctv
_tsubcctv:
   tsubcctv %l1, %l0, %o0
   tsubcctv %l1, 5, %o0
   tsubcctv %l1, -17, %o0
   tsubcctv %l1, %lo(datum), %o0
   tsubcctv %l1, %ulo(datum), %o0
   ! umul
_umul:
   umul %l1, %l0, %o0
   umul %l1, 5, %o0
   umul %l1, -17, %o0
   umul %l1, %lo(datum), %o0
   umul %l1, %ulo(datum), %o0
   ! umulcc
_umulcc:
   umulcc %l1, %l0, %o0
   umulcc %l1, 5, %o0
   umulcc %l1, -17, %o0
   umulcc %l1, %lo(datum), %o0
   umulcc %l1, %ulo(datum), %o0
   ! smul
_smul:
   smul %l1, %l0, %o0
   smul %l1, 5, %o0
   smul %l1, -17, %o0
   smul %l1, %lo(datum), %o0
   smul %l1, %ulo(datum), %o0
   ! smulcc
_smulcc:
   smulcc %l1, %l0, %o0
   smulcc %l1, 5, %o0
   smulcc %l1, -17, %o0
   smulcc %l1, %lo(datum), %o0
   smulcc %l1, %ulo(datum), %o0
   ! mulscc
_mulscc:
   mulscc %l1, %l0, %o0
   mulscc %l1, 5, %o0
   mulscc %l1, -17, %o0
   mulscc %l1, %lo(datum), %o0
   mulscc %l1, %ulo(datum), %o0
   ! udiv
_udiv:
   udiv %l1, %l0, %o0
   udiv %l1, 5, %o0
   udiv %l1, -17, %o0
   udiv %l1, %lo(datum), %o0
   udiv %l1, %ulo(datum), %o0
   ! udivcc
_udivcc:
   udivcc %l1, %l0, %o0
   udivcc %l1, 5, %o0
   udivcc %l1, -17, %o0
   udivcc %l1, %lo(datum), %o0
   udivcc %l1, %ulo(datum), %o0
   ! sdiv
_sdiv:
   sdiv %l1, %l0, %o0
   sdiv %l1, 5, %o0
   sdiv %l1, -17, %o0
   sdiv %l1, %lo(datum), %o0
   sdiv %l1, %ulo(datum), %o0
   ! sdivcc
_sdivcc:
   sdivcc %l1, %l0, %o0
   sdivcc %l1, 5, %o0
   sdivcc %l1, -17, %o0
   sdivcc %l1, %lo(datum), %o0
   sdivcc %l1, %ulo(datum), %o0
   ! save
_save:
   save %l1, %l0, %o0
   save %l1, 5, %o0
   save %l1, -17, %o0
   save %l1, %lo(datum), %o0
   save %l1, %ulo(datum), %o0
   ! restore
_restore:
   restore %l1, %l0, %o0
   restore %l1, 5, %o0
   restore %l1, -17, %o0
   restore %l1, %lo(datum), %o0
   restore %l1, %ulo(datum), %o0
   ! popc
_popc:
   popc %l0, %o0
   popc 5, %o0
   popc -17, %o0
   popc %lo(datum), %o0
   popc %ulo(datum), %o0

   !
   ! 1b. shift instructions
   !

   ! sll
_sll:
   sll %o0, 6, %o1
   sll %o0, %i0, %o1
   ! srl
_srl:
   srl %o0, 6, %o1
   srl %o0, %i0, %o1
   ! sra
_sra:
   sra %o0, 6, %o1
   sra %o0, %i0, %o1
   ! sllx
_sllx:
   sllx %o0, 6, %o1
   sllx %o0, 33, %o1
   sllx %o0, %i0, %o1
   ! srlx
_srlx:
   srlx %o0, 6, %o1
   srlx %o0, 33, %o1
   srlx %o0, %i0, %o1
   ! srax
_srax:
   srax %o0, 6, %o1
   srax %o0, 33, %o1
   srax %o0, %i0, %o1
_slln:
   slln %o0, 6, %o1
   slln %o0, %i0, %o1
_srln:
   srln %o0, 6, %o1
   srln %o0, %i0, %o1
_sran:
   sran %o0, 6, %o1
   sran %o0, %i0, %o1

   !
   ! 2. conditional moves
   !

   ! integer condition codes, integer move
_mova:
   mova %icc, %i0, %o1
   mova %icc, 6, %o1
   mova %icc, -8, %o1
   mova %icc, %lo(datum), %o1
   mova %icc, %ulo(datum), %o1
   mova %xcc, %i0, %o1
   mova %xcc, 6, %o1
   mova %xcc, -8, %o1
   mova %xcc, %lo(datum), %o1
   mova %xcc, %ulo(datum), %o1
_movn:
   movn %icc, %i0, %o1
   movn %icc, 6, %o1
   movn %icc, -8, %o1
   movn %icc, %lo(datum), %o1
   movn %icc, %ulo(datum), %o1
   movn %xcc, %i0, %o1
   movn %xcc, 6, %o1
   movn %xcc, -8, %o1
   movn %xcc, %lo(datum), %o1
   movn %xcc, %ulo(datum), %o1
_movne:
   movne %icc, %i0, %o1
   movne %icc, 6, %o1
   movne %icc, -8, %o1
   movne %icc, %lo(datum), %o1
   movne %icc, %ulo(datum), %o1
   movne %xcc, %i0, %o1
   movne %xcc, 6, %o1
   movne %xcc, -8, %o1
   movne %xcc, %lo(datum), %o1
   movne %xcc, %ulo(datum), %o1
_move:
   move %icc, %i0, %o1
   move %icc, 6, %o1
   move %icc, -8, %o1
   move %icc, %lo(datum), %o1
   move %icc, %ulo(datum), %o1
   move %xcc, %i0, %o1
   move %xcc, 6, %o1
   move %xcc, -8, %o1
   move %xcc, %lo(datum), %o1
   move %xcc, %ulo(datum), %o1
_movg:
   movg %icc, %i0, %o1
   movg %icc, 6, %o1
   movg %icc, -8, %o1
   movg %icc, %lo(datum), %o1
   movg %icc, %ulo(datum), %o1
   movg %xcc, %i0, %o1
   movg %xcc, 6, %o1
   movg %xcc, -8, %o1
   movg %xcc, %lo(datum), %o1
   movg %xcc, %ulo(datum), %o1
_movle:
   movle %icc, %i0, %o1
   movle %icc, 6, %o1
   movle %icc, -8, %o1
   movle %icc, %lo(datum), %o1
   movle %icc, %ulo(datum), %o1
   movle %xcc, %i0, %o1
   movle %xcc, 6, %o1
   movle %xcc, -8, %o1
   movle %xcc, %lo(datum), %o1
   movle %xcc, %ulo(datum), %o1
_movge:
   movge %icc, %i0, %o1
   movge %icc, 6, %o1
   movge %icc, -8, %o1
   movge %icc, %lo(datum), %o1
   movge %icc, %ulo(datum), %o1
   movge %xcc, %i0, %o1
   movge %xcc, 6, %o1
   movge %xcc, -8, %o1
   movge %xcc, %lo(datum), %o1
   movge %xcc, %ulo(datum), %o1
_movl:
   movl %icc, %i0, %o1
   movl %icc, 6, %o1
   movl %icc, -8, %o1
   movl %icc, %lo(datum), %o1
   movl %icc, %ulo(datum), %o1
   movl %xcc, %i0, %o1
   movl %xcc, 6, %o1
   movl %xcc, -8, %o1
   movl %xcc, %lo(datum), %o1
   movl %xcc, %ulo(datum), %o1
_movgu:
   movgu %icc, %i0, %o1
   movgu %icc, 6, %o1
   movgu %icc, -8, %o1
   movgu %icc, %lo(datum), %o1
   movgu %icc, %ulo(datum), %o1
   movgu %xcc, %i0, %o1
   movgu %xcc, 6, %o1
   movgu %xcc, -8, %o1
   movgu %xcc, %lo(datum), %o1
   movgu %xcc, %ulo(datum), %o1
_movleu:
   movleu %icc, %i0, %o1
   movleu %icc, 6, %o1
   movleu %icc, -8, %o1
   movleu %icc, %lo(datum), %o1
   movleu %icc, %ulo(datum), %o1
   movleu %xcc, %i0, %o1
   movleu %xcc, 6, %o1
   movleu %xcc, -8, %o1
   movleu %xcc, %lo(datum), %o1
   movleu %xcc, %ulo(datum), %o1
_movcc:
   movcc %icc, %i0, %o1
   movcc %icc, 6, %o1
   movcc %icc, -8, %o1
   movcc %icc, %lo(datum), %o1
   movcc %icc, %ulo(datum), %o1
   movcc %xcc, %i0, %o1
   movcc %xcc, 6, %o1
   movcc %xcc, -8, %o1
   movcc %xcc, %lo(datum), %o1
   movcc %xcc, %ulo(datum), %o1
_movcs:
   movcs %icc, %i0, %o1
   movcs %icc, 6, %o1
   movcs %icc, -8, %o1
   movcs %icc, %lo(datum), %o1
   movcs %icc, %ulo(datum), %o1
   movcs %xcc, %i0, %o1
   movcs %xcc, 6, %o1
   movcs %xcc, -8, %o1
   movcs %xcc, %lo(datum), %o1
   movcs %xcc, %ulo(datum), %o1
_movpos:
   movpos %icc, %i0, %o1
   movpos %icc, 6, %o1
   movpos %icc, -8, %o1
   movpos %icc, %lo(datum), %o1
   movpos %icc, %ulo(datum), %o1
   movpos %xcc, %i0, %o1
   movpos %xcc, 6, %o1
   movpos %xcc, -8, %o1
   movpos %xcc, %lo(datum), %o1
   movpos %xcc, %ulo(datum), %o1
_movneg:
   movneg %icc, %i0, %o1
   movneg %icc, 6, %o1
   movneg %icc, -8, %o1
   movneg %icc, %lo(datum), %o1
   movneg %icc, %ulo(datum), %o1
   movneg %xcc, %i0, %o1
   movneg %xcc, 6, %o1
   movneg %xcc, -8, %o1
   movneg %xcc, %lo(datum), %o1
   movneg %xcc, %ulo(datum), %o1
_movvc:
   movvc %icc, %i0, %o1
   movvc %icc, 6, %o1
   movvc %icc, -8, %o1
   movvc %icc, %lo(datum), %o1
   movvc %icc, %ulo(datum), %o1
   movvc %xcc, %i0, %o1
   movvc %xcc, 6, %o1
   movvc %xcc, -8, %o1
   movvc %xcc, %lo(datum), %o1
   movvc %xcc, %ulo(datum), %o1
_movvs:
   movvs %icc, %i0, %o1
   movvs %icc, 6, %o1
   movvs %icc, -8, %o1
   movvs %icc, %lo(datum), %o1
   movvs %icc, %ulo(datum), %o1
   movvs %xcc, %i0, %o1
   movvs %xcc, 6, %o1
   movvs %xcc, -8, %o1
   movvs %xcc, %lo(datum), %o1
   movvs %xcc, %ulo(datum), %o1
_movnz:
   movnz %icc, %i0, %o1
   movnz %icc, 6, %o1
   movnz %icc, -8, %o1
   movnz %icc, %lo(datum), %o1
   movnz %icc, %ulo(datum), %o1
   movnz %xcc, %i0, %o1
   movnz %xcc, 6, %o1
   movnz %xcc, -8, %o1
   movnz %xcc, %lo(datum), %o1
   movnz %xcc, %ulo(datum), %o1
_movz:
   movz %icc, %i0, %o1
   movz %icc, 6, %o1
   movz %icc, -8, %o1
   movz %icc, %lo(datum), %o1
   movz %icc, %ulo(datum), %o1
   movz %xcc, %i0, %o1
   movz %xcc, 6, %o1
   movz %xcc, -8, %o1
   movz %xcc, %lo(datum), %o1
   movz %xcc, %ulo(datum), %o1
_movgeu:
   movgeu %icc, %i0, %o1
   movgeu %icc, 6, %o1
   movgeu %icc, -8, %o1
   movgeu %icc, %lo(datum), %o1
   movgeu %icc, %ulo(datum), %o1
   movgeu %xcc, %i0, %o1
   movgeu %xcc, 6, %o1
   movgeu %xcc, -8, %o1
   movgeu %xcc, %lo(datum), %o1
   movgeu %xcc, %ulo(datum), %o1
_movlu:
   movlu %icc, %i0, %o1
   movlu %icc, 6, %o1
   movlu %icc, -8, %o1
   movlu %icc, %lo(datum), %o1
   movlu %icc, %ulo(datum), %o1
   movlu %xcc, %i0, %o1
   movlu %xcc, 6, %o1
   movlu %xcc, -8, %o1
   movlu %xcc, %lo(datum), %o1
   movlu %xcc, %ulo(datum), %o1

   ! fpu condition codes, integer move
_mova:
   mova %fcc1, %i0, %o1
   mova %fcc1, 6, %o1
   mova %fcc2, -8, %o1
   mova %fcc3, %lo(datum), %o1
   mova %fcc3, %ulo(datum), %o1
_movn:
   movn %fcc1, %i0, %o1
   movn %fcc1, 6, %o1
   movn %fcc2, -8, %o1
   movn %fcc3, %lo(datum), %o1
   movn %fcc3, %ulo(datum), %o1
_movu:
   movu %fcc1, %i0, %o1
   movu %fcc1, 6, %o1
   movu %fcc2, -8, %o1
   movu %fcc3, %lo(datum), %o1
   movu %fcc3, %ulo(datum), %o1
_movg:
   movg %fcc1, %i0, %o1
   movg %fcc1, 6, %o1
   movg %fcc2, -8, %o1
   movg %fcc3, %lo(datum), %o1
   movg %fcc3, %ulo(datum), %o1
_movug:
   movug %fcc1, %i0, %o1
   movug %fcc1, 6, %o1
   movug %fcc2, -8, %o1
   movug %fcc3, %lo(datum), %o1
   movug %fcc3, %ulo(datum), %o1
_movl:
   movl %fcc1, %i0, %o1
   movl %fcc1, 6, %o1
   movl %fcc2, -8, %o1
   movl %fcc3, %lo(datum), %o1
   movl %fcc3, %ulo(datum), %o1
_movul:
   movul %fcc1, %i0, %o1
   movul %fcc1, 6, %o1
   movul %fcc2, -8, %o1
   movul %fcc3, %lo(datum), %o1
   movul %fcc3, %ulo(datum), %o1
_movlg:
   movlg %fcc1, %i0, %o1
   movlg %fcc1, 6, %o1
   movlg %fcc2, -8, %o1
   movlg %fcc3, %lo(datum), %o1
   movlg %fcc3, %ulo(datum), %o1
_movne:
   movne %fcc1, %i0, %o1
   movne %fcc1, 6, %o1
   movne %fcc2, -8, %o1
   movne %fcc3, %lo(datum), %o1
   movne %fcc3, %ulo(datum), %o1
_move:
   move %fcc1, %i0, %o1
   move %fcc1, 6, %o1
   move %fcc2, -8, %o1
   move %fcc3, %lo(datum), %o1
   move %fcc3, %ulo(datum), %o1
_movue:
   movue %fcc1, %i0, %o1
   movue %fcc1, 6, %o1
   movue %fcc2, -8, %o1
   movue %fcc3, %lo(datum), %o1
   movue %fcc3, %ulo(datum), %o1
_movge:
   movge %fcc1, %i0, %o1
   movge %fcc1, 6, %o1
   movge %fcc2, -8, %o1
   movge %fcc3, %lo(datum), %o1
   movge %fcc3, %ulo(datum), %o1
_movuge:
   movuge %fcc1, %i0, %o1
   movuge %fcc1, 6, %o1
   movuge %fcc2, -8, %o1
   movuge %fcc3, %lo(datum), %o1
   movuge %fcc3, %ulo(datum), %o1
_movle:
   movle %fcc1, %i0, %o1
   movle %fcc1, 6, %o1
   movle %fcc2, -8, %o1
   movle %fcc3, %lo(datum), %o1
   movle %fcc3, %ulo(datum), %o1
_movule:
   movule %fcc1, %i0, %o1
   movule %fcc1, 6, %o1
   movule %fcc2, -8, %o1
   movule %fcc3, %lo(datum), %o1
   movule %fcc3, %ulo(datum), %o1
_movo:
   movo %fcc1, %i0, %o1
   movo %fcc1, 6, %o1
   movo %fcc2, -8, %o1
   movo %fcc3, %lo(datum), %o1
   movo %fcc3, %ulo(datum), %o1
_movnz:
   movnz %fcc1, %i0, %o1
   movnz %fcc1, 6, %o1
   movnz %fcc2, -8, %o1
   movnz %fcc3, %lo(datum), %o1
   movnz %fcc3, %ulo(datum), %o1
_movz:
   movz %fcc1, %i0, %o1
   movz %fcc1, 6, %o1
   movz %fcc2, -8, %o1
   movz %fcc3, %lo(datum), %o1
   movz %fcc3, %ulo(datum), %o1

   ! integer register tests, integer move
movrz:
   movrz %i5, %i0, %o1
   movrz %i5, 6, %o1
   movrz %i5, -8, %o1
   movrz %i5, %lo, %o1
   movrz %i5, %ulo, %o1
movrlez:
   movrlez %i5, %i0, %o1
   movrlez %i5, 6, %o1
   movrlez %i5, -8, %o1
   movrlez %i5, %lo, %o1
   movrlez %i5, %ulo, %o1
movrlz:
   movrlz %i5, %i0, %o1
   movrlz %i5, 6, %o1
   movrlz %i5, -8, %o1
   movrlz %i5, %lo, %o1
   movrlz %i5, %ulo, %o1
movrnz:
   movrnz %i5, %i0, %o1
   movrnz %i5, 6, %o1
   movrnz %i5, -8, %o1
   movrnz %i5, %lo, %o1
   movrnz %i5, %ulo, %o1
movrgz:
   movrgz %i5, %i0, %o1
   movrgz %i5, 6, %o1
   movrgz %i5, -8, %o1
   movrgz %i5, %lo, %o1
   movrgz %i5, %ulo, %o1
movrgez:
   movrgez %i5, %i0, %o1
   movrgez %i5, 6, %o1
   movrgez %i5, -8, %o1
   movrgez %i5, %lo, %o1
   movrgez %i5, %ulo, %o1
movre:
   movre %i5, %i0, %o1
   movre %i5, 6, %o1
   movre %i5, -8, %o1
   movre %i5, %lo, %o1
   movre %i5, %ulo, %o1
movrne:
   movrne %i5, %i0, %o1
   movrne %i5, 6, %o1
   movrne %i5, -8, %o1
   movrne %i5, %lo, %o1
   movrne %i5, %ulo, %o1

   ! integer conditional codes, fpu move
_fmova:
   fmovsa %icc, %f4, %f5
   fmovsa %icc, %f5, %f7
   fmovda %icc, %f4, %f40
   fmovqa %icc, %f40, %f56
   fmovsa %xcc, %f4, %f5
   fmovsa %xcc, %f5, %f7
   fmovda %xcc, %f4, %f40
   fmovqa %xcc, %f40, %f56
_fmovn:
   fmovsn %icc, %f4, %f5
   fmovsn %icc, %f5, %f7
   fmovdn %icc, %f4, %f40
   fmovqn %icc, %f40, %f56
   fmovsn %xcc, %f4, %f5
   fmovsn %xcc, %f5, %f7
   fmovdn %xcc, %f4, %f40
   fmovqn %xcc, %f40, %f56
_fmovne:
   fmovsne %icc, %f4, %f5
   fmovsne %icc, %f5, %f7
   fmovdne %icc, %f4, %f40
   fmovqne %icc, %f40, %f56
   fmovsne %xcc, %f4, %f5
   fmovsne %xcc, %f5, %f7
   fmovdne %xcc, %f4, %f40
   fmovqne %xcc, %f40, %f56
_fmove:
   fmovse %icc, %f4, %f5
   fmovse %icc, %f5, %f7
   fmovde %icc, %f4, %f40
   fmovqe %icc, %f40, %f56
   fmovse %xcc, %f4, %f5
   fmovse %xcc, %f5, %f7
   fmovde %xcc, %f4, %f40
   fmovqe %xcc, %f40, %f56
_fmovg:
   fmovsg %icc, %f4, %f5
   fmovsg %icc, %f5, %f7
   fmovdg %icc, %f4, %f40
   fmovqg %icc, %f40, %f56
   fmovsg %xcc, %f4, %f5
   fmovsg %xcc, %f5, %f7
   fmovdg %xcc, %f4, %f40
   fmovqg %xcc, %f40, %f56
_fmovle:
   fmovsle %icc, %f4, %f5
   fmovsle %icc, %f5, %f7
   fmovdle %icc, %f4, %f40
   fmovqle %icc, %f40, %f56
   fmovsle %xcc, %f4, %f5
   fmovsle %xcc, %f5, %f7
   fmovdle %xcc, %f4, %f40
   fmovqle %xcc, %f40, %f56
_fmovge:
   fmovsge %icc, %f4, %f5
   fmovsge %icc, %f5, %f7
   fmovdge %icc, %f4, %f40
   fmovqge %icc, %f40, %f56
   fmovsge %xcc, %f4, %f5
   fmovsge %xcc, %f5, %f7
   fmovdge %xcc, %f4, %f40
   fmovqge %xcc, %f40, %f56
_fmovl:
   fmovsl %icc, %f4, %f5
   fmovsl %icc, %f5, %f7
   fmovdl %icc, %f4, %f40
   fmovql %icc, %f40, %f56
   fmovsl %xcc, %f4, %f5
   fmovsl %xcc, %f5, %f7
   fmovdl %xcc, %f4, %f40
   fmovql %xcc, %f40, %f56
_fmovgu:
   fmovsgu %icc, %f4, %f5
   fmovsgu %icc, %f5, %f7
   fmovdgu %icc, %f4, %f40
   fmovqgu %icc, %f40, %f56
   fmovsgu %xcc, %f4, %f5
   fmovsgu %xcc, %f5, %f7
   fmovdgu %xcc, %f4, %f40
   fmovqgu %xcc, %f40, %f56
_fmovleu:
   fmovsleu %icc, %f4, %f5
   fmovsleu %icc, %f5, %f7
   fmovdleu %icc, %f4, %f40
   fmovqleu %icc, %f40, %f56
   fmovsleu %xcc, %f4, %f5
   fmovsleu %xcc, %f5, %f7
   fmovdleu %xcc, %f4, %f40
   fmovqleu %xcc, %f40, %f56
_fmovcc:
   fmovscc %icc, %f4, %f5
   fmovscc %icc, %f5, %f7
   fmovdcc %icc, %f4, %f40
   fmovqcc %icc, %f40, %f56
   fmovscc %xcc, %f4, %f5
   fmovscc %xcc, %f5, %f7
   fmovdcc %xcc, %f4, %f40
   fmovqcc %xcc, %f40, %f56
_fmovcs:
   fmovscs %icc, %f4, %f5
   fmovscs %icc, %f5, %f7
   fmovdcs %icc, %f4, %f40
   fmovqcs %icc, %f40, %f56
   fmovscs %xcc, %f4, %f5
   fmovscs %xcc, %f5, %f7
   fmovdcs %xcc, %f4, %f40
   fmovqcs %xcc, %f40, %f56
_fmovpos:
   fmovspos %icc, %f4, %f5
   fmovspos %icc, %f5, %f7
   fmovdpos %icc, %f4, %f40
   fmovqpos %icc, %f40, %f56
   fmovspos %xcc, %f4, %f5
   fmovspos %xcc, %f5, %f7
   fmovdpos %xcc, %f4, %f40
   fmovqpos %xcc, %f40, %f56
_fmovneg:
   fmovsneg %icc, %f4, %f5
   fmovsneg %icc, %f5, %f7
   fmovdneg %icc, %f4, %f40
   fmovqneg %icc, %f40, %f56
   fmovsneg %xcc, %f4, %f5
   fmovsneg %xcc, %f5, %f7
   fmovdneg %xcc, %f4, %f40
   fmovqneg %xcc, %f40, %f56
_fmovvc:
   fmovsvc %icc, %f4, %f5
   fmovsvc %icc, %f5, %f7
   fmovdvc %icc, %f4, %f40
   fmovqvc %icc, %f40, %f56
   fmovsvc %xcc, %f4, %f5
   fmovsvc %xcc, %f5, %f7
   fmovdvc %xcc, %f4, %f40
   fmovqvc %xcc, %f40, %f56
_fmovvs:
   fmovsvs %icc, %f4, %f5
   fmovsvs %icc, %f5, %f7
   fmovdvs %icc, %f4, %f40
   fmovqvs %icc, %f40, %f56
   fmovsvs %xcc, %f4, %f5
   fmovsvs %xcc, %f5, %f7
   fmovdvs %xcc, %f4, %f40
   fmovqvs %xcc, %f40, %f56
_fmovnz:
   fmovsnz %icc, %f4, %f5
   fmovsnz %icc, %f5, %f7
   fmovdnz %icc, %f4, %f40
   fmovqnz %icc, %f40, %f56
   fmovsnz %xcc, %f4, %f5
   fmovsnz %xcc, %f5, %f7
   fmovdnz %xcc, %f4, %f40
   fmovqnz %xcc, %f40, %f56
_fmovz:
   fmovsz %icc, %f4, %f5
   fmovsz %icc, %f5, %f7
   fmovdz %icc, %f4, %f40
   fmovqz %icc, %f40, %f56
   fmovsz %xcc, %f4, %f5
   fmovsz %xcc, %f5, %f7
   fmovdz %xcc, %f4, %f40
   fmovqz %xcc, %f40, %f56
_fmovgeu:
   fmovsgeu %icc, %f4, %f5
   fmovsgeu %icc, %f5, %f7
   fmovdgeu %icc, %f4, %f40
   fmovqgeu %icc, %f40, %f56
   fmovsgeu %xcc, %f4, %f5
   fmovsgeu %xcc, %f5, %f7
   fmovdgeu %xcc, %f4, %f40
   fmovqgeu %xcc, %f40, %f56
_fmovlu:
   fmovslu %icc, %f4, %f5
   fmovslu %icc, %f5, %f7
   fmovdlu %icc, %f4, %f40
   fmovqlu %icc, %f40, %f56
   fmovslu %xcc, %f4, %f5
   fmovslu %xcc, %f5, %f7
   fmovdlu %xcc, %f4, %f40
   fmovqlu %xcc, %f40, %f56

   ! fpu conditional codes, fpu move
_fmova:
   fmovsa %fcc1, %f4, %f5
   fmovsa %fcc1, %f5, %f7
   fmovda %fcc1, %f4, %f40
   fmovqa %fcc1, %f40, %f56
_fmovn:
   fmovsn %fcc1, %f4, %f5
   fmovsn %fcc1, %f5, %f7
   fmovdn %fcc1, %f4, %f40
   fmovqn %fcc1, %f40, %f56
_fmovu:
   fmovsu %fcc1, %f4, %f5
   fmovsu %fcc1, %f5, %f7
   fmovdu %fcc1, %f4, %f40
   fmovqu %fcc1, %f40, %f56
_fmovg:
   fmovsg %fcc1, %f4, %f5
   fmovsg %fcc1, %f5, %f7
   fmovdg %fcc1, %f4, %f40
   fmovqg %fcc1, %f40, %f56
_fmovug:
   fmovsug %fcc1, %f4, %f5
   fmovsug %fcc1, %f5, %f7
   fmovdug %fcc1, %f4, %f40
   fmovqug %fcc1, %f40, %f56
_fmovl:
   fmovsl %fcc1, %f4, %f5
   fmovsl %fcc1, %f5, %f7
   fmovdl %fcc1, %f4, %f40
   fmovql %fcc1, %f40, %f56
_fmovul:
   fmovsul %fcc1, %f4, %f5
   fmovsul %fcc1, %f5, %f7
   fmovdul %fcc1, %f4, %f40
   fmovqul %fcc1, %f40, %f56
_fmovlg:
   fmovslg %fcc1, %f4, %f5
   fmovslg %fcc1, %f5, %f7
   fmovdlg %fcc1, %f4, %f40
   fmovqlg %fcc1, %f40, %f56
_fmovne:
   fmovsne %fcc1, %f4, %f5
   fmovsne %fcc1, %f5, %f7
   fmovdne %fcc1, %f4, %f40
   fmovqne %fcc1, %f40, %f56
_fmove:
   fmovse %fcc1, %f4, %f5
   fmovse %fcc1, %f5, %f7
   fmovde %fcc1, %f4, %f40
   fmovqe %fcc1, %f40, %f56
_fmovue:
   fmovsue %fcc1, %f4, %f5
   fmovsue %fcc1, %f5, %f7
   fmovdue %fcc1, %f4, %f40
   fmovque %fcc1, %f40, %f56
_fmovge:
   fmovsge %fcc1, %f4, %f5
   fmovsge %fcc1, %f5, %f7
   fmovdge %fcc1, %f4, %f40
   fmovqge %fcc1, %f40, %f56
_fmovuge:
   fmovsuge %fcc1, %f4, %f5
   fmovsuge %fcc1, %f5, %f7
   fmovduge %fcc1, %f4, %f40
   fmovquge %fcc1, %f40, %f56
_fmovle:
   fmovsle %fcc1, %f4, %f5
   fmovsle %fcc1, %f5, %f7
   fmovdle %fcc1, %f4, %f40
   fmovqle %fcc1, %f40, %f56
_fmovule:
   fmovsule %fcc1, %f4, %f5
   fmovsule %fcc1, %f5, %f7
   fmovdule %fcc1, %f4, %f40
   fmovqule %fcc1, %f40, %f56
_fmovo:
   fmovso %fcc1, %f4, %f5
   fmovso %fcc1, %f5, %f7
   fmovdo %fcc1, %f4, %f40
   fmovqo %fcc1, %f40, %f56
_fmovnz:
   fmovsnz %fcc1, %f4, %f5
   fmovsnz %fcc1, %f5, %f7
   fmovdnz %fcc1, %f4, %f40
   fmovqnz %fcc1, %f40, %f56
_fmovz:
   fmovsz %fcc1, %f4, %f5
   fmovsz %fcc1, %f5, %f7
   fmovdz %fcc1, %f4, %f40
   fmovqz %fcc1, %f40, %f56

   ! integer register tests, fpu move
_fmovrz:
   fmovrsz %o3, %f4, %f5
   fmovrsz %o3, %f5, %f7
   fmovrdz %o3, %f4, %f40
   fmovrqz %o3, %f40, %f56
_fmovrlez:
   fmovrslez %o3, %f4, %f5
   fmovrslez %o3, %f5, %f7
   fmovrdlez %o3, %f4, %f40
   fmovrqlez %o3, %f40, %f56
_fmovrlz:
   fmovrslz %o3, %f4, %f5
   fmovrslz %o3, %f5, %f7
   fmovrdlz %o3, %f4, %f40
   fmovrqlz %o3, %f40, %f56
_fmovrnz:
   fmovrsnz %o3, %f4, %f5
   fmovrsnz %o3, %f5, %f7
   fmovrdnz %o3, %f4, %f40
   fmovrqnz %o3, %f40, %f56
_fmovrg:
   fmovrsg %o3, %f4, %f5
   fmovrsg %o3, %f5, %f7
   fmovrdg %o3, %f4, %f40
   fmovrqg %o3, %f40, %f56
_fmovrgez:
   fmovrsgez %o3, %f4, %f5
   fmovrsgez %o3, %f5, %f7
   fmovrdgez %o3, %f4, %f40
   fmovrqgez %o3, %f40, %f56
_fmovre:
   fmovrse %o3, %f4, %f5
   fmovrse %o3, %f5, %f7
   fmovrde %o3, %f4, %f40
   fmovrqe %o3, %f40, %f56
_fmovrne:
   fmovrsne %o3, %f4, %f5
   fmovrsne %o3, %f5, %f7
   fmovrdne %o3, %f4, %f40
   fmovrqne %o3, %f40, %f56

   !
   ! 3. branches
   !
1:
_brz:
   brz %i0, 1b
   brz,pt %i0, 1b
   brz,pn %i0, 1b
   brz,a %i0, 2f
   brz,a,pt %i0, 2f
   brz,a,pn %i0, 2f
_brlez:
   brlez %i0, 1b
   brlez,pt %i0, 1b
   brlez,pn %i0, 1b
   brlez,a %i0, 2f
   brlez,a,pt %i0, 2f
   brlez,a,pn %i0, 2f
_brlz:
   brlz %i0, 1b
   brlz,pt %i0, 1b
   brlz,pn %i0, 1b
   brlz,a %i0, 2f
   brlz,a,pt %i0, 2f
   brlz,a,pn %i0, 2f
_brnz:
   brnz %i0, 1b
   brnz,pt %i0, 1b
   brnz,pn %i0, 1b
   brnz,a %i0, 2f
   brnz,a,pt %i0, 2f
   brnz,a,pn %i0, 2f
_brgz:
   brgz %i0, 1b
   brgz,pt %i0, 1b
   brgz,pn %i0, 1b
   brgz,a %i0, 2f
   brgz,a,pt %i0, 2f
   brgz,a,pn %i0, 2f
_brgez:
   brgez %i0, 1b
   brgez,pt %i0, 1b
   brgez,pn %i0, 1b
   brgez,a %i0, 2f
   brgez,a,pt %i0, 2f
   brgez,a,pn %i0, 2f
_ba:
   ba %i0, 1b
   ba,a %0, 2f
   ba %icc, %i0, 1b
   ba,pt %icc, %i0, 1b
   ba,pn %icc, %i0, 1b
   ba,a %icc, %0, 2f
   ba,a,pt %icc, %0, 2f
   ba,a,pn %icc, %0, 2f
   ba %xcc, %i0, 1b
   ba,pt %xcc, %i0, 1b
   ba,pn %xcc, %i0, 1b
   ba,a %xcc, %0, 2f
   ba,a,pt %xcc, %0, 2f
   ba,a,pn %xcc, %0, 2f
_bn:
   bn %i0, 1b
   bn,a %0, 2f
   bn %icc, %i0, 1b
   bn,pt %icc, %i0, 1b
   bn,pn %icc, %i0, 1b
   bn,a %icc, %0, 2f
   bn,a,pt %icc, %0, 2f
   bn,a,pn %icc, %0, 2f
   bn %xcc, %i0, 1b
   bn,pt %xcc, %i0, 1b
   bn,pn %xcc, %i0, 1b
   bn,a %xcc, %0, 2f
   bn,a,pt %xcc, %0, 2f
   bn,a,pn %xcc, %0, 2f
_bne:
   bne %i0, 1b
   bne,a %0, 2f
   bne %icc, %i0, 1b
   bne,pt %icc, %i0, 1b
   bne,pn %icc, %i0, 1b
   bne,a %icc, %0, 2f
   bne,a,pt %icc, %0, 2f
   bne,a,pn %icc, %0, 2f
   bne %xcc, %i0, 1b
   bne,pt %xcc, %i0, 1b
   bne,pn %xcc, %i0, 1b
   bne,a %xcc, %0, 2f
   bne,a,pt %xcc, %0, 2f
   bne,a,pn %xcc, %0, 2f
_be:
   be %i0, 1b
   be,a %0, 2f
   be %icc, %i0, 1b
   be,pt %icc, %i0, 1b
   be,pn %icc, %i0, 1b
   be,a %icc, %0, 2f
   be,a,pt %icc, %0, 2f
   be,a,pn %icc, %0, 2f
   be %xcc, %i0, 1b
   be,pt %xcc, %i0, 1b
   be,pn %xcc, %i0, 1b
   be,a %xcc, %0, 2f
   be,a,pt %xcc, %0, 2f
   be,a,pn %xcc, %0, 2f
_bg:
   bg %i0, 1b
   bg,a %0, 2f
   bg %icc, %i0, 1b
   bg,pt %icc, %i0, 1b
   bg,pn %icc, %i0, 1b
   bg,a %icc, %0, 2f
   bg,a,pt %icc, %0, 2f
   bg,a,pn %icc, %0, 2f
   bg %xcc, %i0, 1b
   bg,pt %xcc, %i0, 1b
   bg,pn %xcc, %i0, 1b
   bg,a %xcc, %0, 2f
   bg,a,pt %xcc, %0, 2f
   bg,a,pn %xcc, %0, 2f
_ble:
   ble %i0, 1b
   ble,a %0, 2f
   ble %icc, %i0, 1b
   ble,pt %icc, %i0, 1b
   ble,pn %icc, %i0, 1b
   ble,a %icc, %0, 2f
   ble,a,pt %icc, %0, 2f
   ble,a,pn %icc, %0, 2f
   ble %xcc, %i0, 1b
   ble,pt %xcc, %i0, 1b
   ble,pn %xcc, %i0, 1b
   ble,a %xcc, %0, 2f
   ble,a,pt %xcc, %0, 2f
   ble,a,pn %xcc, %0, 2f
_bge:
   bge %i0, 1b
   bge,a %0, 2f
   bge %icc, %i0, 1b
   bge,pt %icc, %i0, 1b
   bge,pn %icc, %i0, 1b
   bge,a %icc, %0, 2f
   bge,a,pt %icc, %0, 2f
   bge,a,pn %icc, %0, 2f
   bge %xcc, %i0, 1b
   bge,pt %xcc, %i0, 1b
   bge,pn %xcc, %i0, 1b
   bge,a %xcc, %0, 2f
   bge,a,pt %xcc, %0, 2f
   bge,a,pn %xcc, %0, 2f
_bl:
   bl %i0, 1b
   bl,a %0, 2f
   bl %icc, %i0, 1b
   bl,pt %icc, %i0, 1b
   bl,pn %icc, %i0, 1b
   bl,a %icc, %0, 2f
   bl,a,pt %icc, %0, 2f
   bl,a,pn %icc, %0, 2f
   bl %xcc, %i0, 1b
   bl,pt %xcc, %i0, 1b
   bl,pn %xcc, %i0, 1b
   bl,a %xcc, %0, 2f
   bl,a,pt %xcc, %0, 2f
   bl,a,pn %xcc, %0, 2f
_bgu:
   bgu %i0, 1b
   bgu,a %0, 2f
   bgu %icc, %i0, 1b
   bgu,pt %icc, %i0, 1b
   bgu,pn %icc, %i0, 1b
   bgu,a %icc, %0, 2f
   bgu,a,pt %icc, %0, 2f
   bgu,a,pn %icc, %0, 2f
   bgu %xcc, %i0, 1b
   bgu,pt %xcc, %i0, 1b
   bgu,pn %xcc, %i0, 1b
   bgu,a %xcc, %0, 2f
   bgu,a,pt %xcc, %0, 2f
   bgu,a,pn %xcc, %0, 2f
_bleu:
   bleu %i0, 1b
   bleu,a %0, 2f
   bleu %icc, %i0, 1b
   bleu,pt %icc, %i0, 1b
   bleu,pn %icc, %i0, 1b
   bleu,a %icc, %0, 2f
   bleu,a,pt %icc, %0, 2f
   bleu,a,pn %icc, %0, 2f
   bleu %xcc, %i0, 1b
   bleu,pt %xcc, %i0, 1b
   bleu,pn %xcc, %i0, 1b
   bleu,a %xcc, %0, 2f
   bleu,a,pt %xcc, %0, 2f
   bleu,a,pn %xcc, %0, 2f
_bcc:
   bcc %i0, 1b
   bcc,a %0, 2f
   bcc %icc, %i0, 1b
   bcc,pt %icc, %i0, 1b
   bcc,pn %icc, %i0, 1b
   bcc,a %icc, %0, 2f
   bcc,a,pt %icc, %0, 2f
   bcc,a,pn %icc, %0, 2f
   bcc %xcc, %i0, 1b
   bcc,pt %xcc, %i0, 1b
   bcc,pn %xcc, %i0, 1b
   bcc,a %xcc, %0, 2f
   bcc,a,pt %xcc, %0, 2f
   bcc,a,pn %xcc, %0, 2f
_bcs:
   bcs %i0, 1b
   bcs,a %0, 2f
   bcs %icc, %i0, 1b
   bcs,pt %icc, %i0, 1b
   bcs,pn %icc, %i0, 1b
   bcs,a %icc, %0, 2f
   bcs,a,pt %icc, %0, 2f
   bcs,a,pn %icc, %0, 2f
   bcs %xcc, %i0, 1b
   bcs,pt %xcc, %i0, 1b
   bcs,pn %xcc, %i0, 1b
   bcs,a %xcc, %0, 2f
   bcs,a,pt %xcc, %0, 2f
   bcs,a,pn %xcc, %0, 2f
_bpos:
   bpos %i0, 1b
   bpos,a %0, 2f
   bpos %icc, %i0, 1b
   bpos,pt %icc, %i0, 1b
   bpos,pn %icc, %i0, 1b
   bpos,a %icc, %0, 2f
   bpos,a,pt %icc, %0, 2f
   bpos,a,pn %icc, %0, 2f
   bpos %xcc, %i0, 1b
   bpos,pt %xcc, %i0, 1b
   bpos,pn %xcc, %i0, 1b
   bpos,a %xcc, %0, 2f
   bpos,a,pt %xcc, %0, 2f
   bpos,a,pn %xcc, %0, 2f
_bneg:
   bneg %i0, 1b
   bneg,a %0, 2f
   bneg %icc, %i0, 1b
   bneg,pt %icc, %i0, 1b
   bneg,pn %icc, %i0, 1b
   bneg,a %icc, %0, 2f
   bneg,a,pt %icc, %0, 2f
   bneg,a,pn %icc, %0, 2f
   bneg %xcc, %i0, 1b
   bneg,pt %xcc, %i0, 1b
   bneg,pn %xcc, %i0, 1b
   bneg,a %xcc, %0, 2f
   bneg,a,pt %xcc, %0, 2f
   bneg,a,pn %xcc, %0, 2f
_bvc:
   bvc %i0, 1b
   bvc,a %0, 2f
   bvc %icc, %i0, 1b
   bvc,pt %icc, %i0, 1b
   bvc,pn %icc, %i0, 1b
   bvc,a %icc, %0, 2f
   bvc,a,pt %icc, %0, 2f
   bvc,a,pn %icc, %0, 2f
   bvc %xcc, %i0, 1b
   bvc,pt %xcc, %i0, 1b
   bvc,pn %xcc, %i0, 1b
   bvc,a %xcc, %0, 2f
   bvc,a,pt %xcc, %0, 2f
   bvc,a,pn %xcc, %0, 2f
_bvs:
   bvs %i0, 1b
   bvs,a %0, 2f
   bvs %icc, %i0, 1b
   bvs,pt %icc, %i0, 1b
   bvs,pn %icc, %i0, 1b
   bvs,a %icc, %0, 2f
   bvs,a,pt %icc, %0, 2f
   bvs,a,pn %icc, %0, 2f
   bvs %xcc, %i0, 1b
   bvs,pt %xcc, %i0, 1b
   bvs,pn %xcc, %i0, 1b
   bvs,a %xcc, %0, 2f
   bvs,a,pt %xcc, %0, 2f
   bvs,a,pn %xcc, %0, 2f
_bnz:
   bnz %i0, 1b
   bnz,a %0, 2f
   bnz %icc, %i0, 1b
   bnz,pt %icc, %i0, 1b
   bnz,pn %icc, %i0, 1b
   bnz,a %icc, %0, 2f
   bnz,a,pt %icc, %0, 2f
   bnz,a,pn %icc, %0, 2f
   bnz %xcc, %i0, 1b
   bnz,pt %xcc, %i0, 1b
   bnz,pn %xcc, %i0, 1b
   bnz,a %xcc, %0, 2f
   bnz,a,pt %xcc, %0, 2f
   bnz,a,pn %xcc, %0, 2f
_bz:
   bz %i0, 1b
   bz,a %0, 2f
   bz %icc, %i0, 1b
   bz,pt %icc, %i0, 1b
   bz,pn %icc, %i0, 1b
   bz,a %icc, %0, 2f
   bz,a,pt %icc, %0, 2f
   bz,a,pn %icc, %0, 2f
   bz %xcc, %i0, 1b
   bz,pt %xcc, %i0, 1b
   bz,pn %xcc, %i0, 1b
   bz,a %xcc, %0, 2f
   bz,a,pt %xcc, %0, 2f
   bz,a,pn %xcc, %0, 2f
_bgeu:
   bgeu %i0, 1b
   bgeu,a %0, 2f
   bgeu %icc, %i0, 1b
   bgeu,pt %icc, %i0, 1b
   bgeu,pn %icc, %i0, 1b
   bgeu,a %icc, %0, 2f
   bgeu,a,pt %icc, %0, 2f
   bgeu,a,pn %icc, %0, 2f
   bgeu %xcc, %i0, 1b
   bgeu,pt %xcc, %i0, 1b
   bgeu,pn %xcc, %i0, 1b
   bgeu,a %xcc, %0, 2f
   bgeu,a,pt %xcc, %0, 2f
   bgeu,a,pn %xcc, %0, 2f
_blu:
   blu %i0, 1b
   blu,a %0, 2f
   blu %icc, %i0, 1b
   blu,pt %icc, %i0, 1b
   blu,pn %icc, %i0, 1b
   blu,a %icc, %0, 2f
   blu,a,pt %icc, %0, 2f
   blu,a,pn %icc, %0, 2f
   blu %xcc, %i0, 1b
   blu,pt %xcc, %i0, 1b
   blu,pn %xcc, %i0, 1b
   blu,a %xcc, %0, 2f
   blu,a,pt %xcc, %0, 2f
   blu,a,pn %xcc, %0, 2f

_fba:
   fba 1b
   fba,a 1b
   fba %fcc1, 2f
   fba,pt %fcc1, 2f
   fba,pn %fcc1, 2f
   fba,a %fcc1, 2f
   fba,a,pt %fcc1, 2f
   fba,a,pn %fcc1, 2f
_fbn:
   fbn 1b
   fbn,a 1b
   fbn %fcc1, 2f
   fbn,pt %fcc1, 2f
   fbn,pn %fcc1, 2f
   fbn,a %fcc1, 2f
   fbn,a,pt %fcc1, 2f
   fbn,a,pn %fcc1, 2f
_fbu:
   fbu 1b
   fbu,a 1b
   fbu %fcc1, 2f
   fbu,pt %fcc1, 2f
   fbu,pn %fcc1, 2f
   fbu,a %fcc1, 2f
   fbu,a,pt %fcc1, 2f
   fbu,a,pn %fcc1, 2f
_fbg:
   fbg 1b
   fbg,a 1b
   fbg %fcc1, 2f
   fbg,pt %fcc1, 2f
   fbg,pn %fcc1, 2f
   fbg,a %fcc1, 2f
   fbg,a,pt %fcc1, 2f
   fbg,a,pn %fcc1, 2f
_fbug:
   fbug 1b
   fbug,a 1b
   fbug %fcc1, 2f
   fbug,pt %fcc1, 2f
   fbug,pn %fcc1, 2f
   fbug,a %fcc1, 2f
   fbug,a,pt %fcc1, 2f
   fbug,a,pn %fcc1, 2f
_fbl:
   fbl 1b
   fbl,a 1b
   fbl %fcc1, 2f
   fbl,pt %fcc1, 2f
   fbl,pn %fcc1, 2f
   fbl,a %fcc1, 2f
   fbl,a,pt %fcc1, 2f
   fbl,a,pn %fcc1, 2f
_fbul:
   fbul 1b
   fbul,a 1b
   fbul %fcc1, 2f
   fbul,pt %fcc1, 2f
   fbul,pn %fcc1, 2f
   fbul,a %fcc1, 2f
   fbul,a,pt %fcc1, 2f
   fbul,a,pn %fcc1, 2f
_fblg:
   fblg 1b
   fblg,a 1b
   fblg %fcc1, 2f
   fblg,pt %fcc1, 2f
   fblg,pn %fcc1, 2f
   fblg,a %fcc1, 2f
   fblg,a,pt %fcc1, 2f
   fblg,a,pn %fcc1, 2f
_fbne:
   fbne 1b
   fbne,a 1b
   fbne %fcc1, 2f
   fbne,pt %fcc1, 2f
   fbne,pn %fcc1, 2f
   fbne,a %fcc1, 2f
   fbne,a,pt %fcc1, 2f
   fbne,a,pn %fcc1, 2f
_fbe:
   fbe 1b
   fbe,a 1b
   fbe %fcc1, 2f
   fbe,pt %fcc1, 2f
   fbe,pn %fcc1, 2f
   fbe,a %fcc1, 2f
   fbe,a,pt %fcc1, 2f
   fbe,a,pn %fcc1, 2f
_fbue:
   fbue 1b
   fbue,a 1b
   fbue %fcc1, 2f
   fbue,pt %fcc1, 2f
   fbue,pn %fcc1, 2f
   fbue,a %fcc1, 2f
   fbue,a,pt %fcc1, 2f
   fbue,a,pn %fcc1, 2f
_fbge:
   fbge 1b
   fbge,a 1b
   fbge %fcc1, 2f
   fbge,pt %fcc1, 2f
   fbge,pn %fcc1, 2f
   fbge,a %fcc1, 2f
   fbge,a,pt %fcc1, 2f
   fbge,a,pn %fcc1, 2f
_fbuge:
   fbuge 1b
   fbuge,a 1b
   fbuge %fcc1, 2f
   fbuge,pt %fcc1, 2f
   fbuge,pn %fcc1, 2f
   fbuge,a %fcc1, 2f
   fbuge,a,pt %fcc1, 2f
   fbuge,a,pn %fcc1, 2f
_fble:
   fble 1b
   fble,a 1b
   fble %fcc1, 2f
   fble,pt %fcc1, 2f
   fble,pn %fcc1, 2f
   fble,a %fcc1, 2f
   fble,a,pt %fcc1, 2f
   fble,a,pn %fcc1, 2f
_fbule:
   fbule 1b
   fbule,a 1b
   fbule %fcc1, 2f
   fbule,pt %fcc1, 2f
   fbule,pn %fcc1, 2f
   fbule,a %fcc1, 2f
   fbule,a,pt %fcc1, 2f
   fbule,a,pn %fcc1, 2f
_fbo:
   fbo 1b
   fbo,a 1b
   fbo %fcc1, 2f
   fbo,pt %fcc1, 2f
   fbo,pn %fcc1, 2f
   fbo,a %fcc1, 2f
   fbo,a,pt %fcc1, 2f
   fbo,a,pn %fcc1, 2f
_fbnz:
   fbnz 1b
   fbnz,a 1b
   fbnz %fcc1, 2f
   fbnz,pt %fcc1, 2f
   fbnz,pn %fcc1, 2f
   fbnz,a %fcc1, 2f
   fbnz,a,pt %fcc1, 2f
   fbnz,a,pn %fcc1, 2f
_fbz:
   fbz 1b
   fbz,a 1b
   fbz %fcc1, 2f
   fbz,pt %fcc1, 2f
   fbz,pn %fcc1, 2f
   fbz,a %fcc1, 2f
   fbz,a,pt %fcc1, 2f
   fbz,a,pn %fcc1, 2f
2:

   !
   ! 4. memory
   !
   ! The general forms of each are:
   !    register
   !    register + register
   !    register + imm
   !    imm + register
   !    register - imm
   !    imm
   !    -imm
   ! either in or not in brackets, and for the alternate ones followed by
   ! an asi number (register or register + register) or %asi (others).
   !
_flush:
   flush %l0
   flush %l0 + %l1
   flush %l0 + 3
   flush %l0 + %lo(datum)
   flush %l0 + %ulo(datum)
   flush 3 + %l0
   flush %lo(datum) + %l0
   flush %ulo(datum) + %l0
   flush %l0 - 4
   flush %l0 - %lo(datum) ! is this allowed?
   flush %l0 - %ulo(datum) ! is this allowed?
   flush 4
   flush -4
   flush %lo(datum)
   flush %ulo(datum)
   flush -%lo(datum) ! is this allowed?
   flush -%ulo(datum) ! is this allowed?

_cas:
   cas [%i0], %l0, %l1
_casl:
   casl [%i0], %l0, %l1
_casx:
   casx [%i0], %l0, %l1
_casxl:
   casxl [%i0], %l0, %l1
_casa:
   casa [%i0] #ASI_PRIMARY, %l0, %l1
   casa [%i0] %asi, %l0, %l1
_casxa:
   casxa [%i0] #ASI_PRIMARY, %l0, %l1
   casxa [%i0] %asi, %l0, %l1
_casn:
   casn [%i0], %l0, %l1
_casna:
   casna [%i0] #ASI_PRIMARY, %l0, %l1
   casna [%i0] %asi, %l0, %l1

_prefetch:
   prefetch [%l0], 6
   prefetch [%l0 + %l1], 6
   prefetch [%l0 + 3], 6
   prefetch [%l0 + %lo(datum)], 6
   prefetch [%l0 + %ulo(datum)], 6
   prefetch [3 + %l0], 6
   prefetch [%lo(datum) + %l0], 6
   prefetch [%ulo(datum) + %l0], 6
   prefetch [%l0 - 4], 6
   prefetch [%l0 - %lo(datum)], 6
   prefetch [%l0 - %ulo(datum)], 6
   prefetch [4], 6
   prefetch [%lo(datum)], 6
   prefetch [%ulo(datum)], 6
   prefetch [-%lo(datum)], 6
   prefetch [-%ulo(datum)], 6
_prefetcha:
   prefetcha [%l0] #ASI_PRIMARY, 6
   prefetcha [%l0 + %l1] #ASI_PRIMARY, 6
   prefetcha [%l0 + 3] %asi, 6
   prefetcha [%l0 + %lo(datum)] %asi, 6
   prefetcha [%l0 + %ulo(datum)] %asi, 6
   prefetcha [3 + %l0] %asi, 6
   prefetcha [%lo(datum) + %l0] %asi, 6
   prefetcha [%ulo(datum) + %l0] %asi, 6
   prefetcha [%l0 - 4] %asi, 6
   prefetcha [%l0 - %lo(datum)] %asi, 6
   prefetcha [%l0 - %ulo(datum)] %asi, 6
   prefetcha [4] %asi, 6
   prefetcha [%lo(datum)] %asi, 6
   prefetcha [%ulo(datum)] %asi, 6
   prefetcha [-%lo(datum)] %asi, 6
   prefetcha [-%ulo(datum)] %asi, 6
_ldstub:
   ldstub [%l0], %o2
   ldstub [%l0 + %l1], %o2
   ldstub [%l0 + 3], %o2
   ldstub [%l0 + %lo(datum)], %o2
   ldstub [%l0 + %ulo(datum)], %o2
   ldstub [3 + %l0], %o2
   ldstub [%lo(datum) + %l0], %o2
   ldstub [%ulo(datum) + %l0], %o2
   ldstub [%l0 - 4], %o2
   ldstub [%l0 - %lo(datum)], %o2
   ldstub [%l0 - %ulo(datum)], %o2
   ldstub [4], %o2
   ldstub [%lo(datum)], %o2
   ldstub [%ulo(datum)], %o2
   ldstub [-%lo(datum)], %o2
   ldstub [-%ulo(datum)], %o2
_ldstuba:
   ldstuba [%l0] #ASI_PRIMARY, %o2
   ldstuba [%l0 + %l1] #ASI_PRIMARY, %o2
   ldstuba [%l0 + 3] %asi, %o2
   ldstuba [%l0 + %lo(datum)] %asi, %o2
   ldstuba [%l0 + %ulo(datum)] %asi, %o2
   ldstuba [3 + %l0] %asi, %o2
   ldstuba [%lo(datum) + %l0] %asi, %o2
   ldstuba [%ulo(datum) + %l0] %asi, %o2
   ldstuba [%l0 - 4] %asi, %o2
   ldstuba [%l0 - %lo(datum)] %asi, %o2
   ldstuba [%l0 - %ulo(datum)] %asi, %o2
   ldstuba [4] %asi, %o2
   ldstuba [%lo(datum)] %asi, %o2
   ldstuba [%ulo(datum)] %asi, %o2
   ldstuba [-%lo(datum)] %asi, %o2
   ldstuba [-%ulo(datum)] %asi, %o2
_swap:
   swap [%l0], %o2
   swap [%l0 + %l1], %o2
   swap [%l0 + 3], %o2
   swap [%l0 + %lo(datum)], %o2
   swap [%l0 + %ulo(datum)], %o2
   swap [3 + %l0], %o2
   swap [%lo(datum) + %l0], %o2
   swap [%ulo(datum) + %l0], %o2
   swap [%l0 - 4], %o2
   swap [%l0 - %lo(datum)], %o2
   swap [%l0 - %ulo(datum)], %o2
   swap [4], %o2
   swap [%lo(datum)], %o2
   swap [%ulo(datum)], %o2
   swap [-%lo(datum)], %o2
   swap [-%ulo(datum)], %o2
_swapa:
   swapa [%l0] #ASI_PRIMARY, %o2
   swapa [%l0 + %l1] #ASI_PRIMARY, %o2
   swapa [%l0 + 3] %asi, %o2
   swapa [%l0 + %lo(datum)] %asi, %o2
   swapa [%l0 + %ulo(datum)] %asi, %o2
   swapa [3 + %l0] %asi, %o2
   swapa [%lo(datum) + %l0] %asi, %o2
   swapa [%ulo(datum) + %l0] %asi, %o2
   swapa [%l0 - 4] %asi, %o2
   swapa [%l0 - %lo(datum)] %asi, %o2
   swapa [%l0 - %ulo(datum)] %asi, %o2
   swapa [4] %asi, %o2
   swapa [%lo(datum)] %asi, %o2
   swapa [%ulo(datum)] %asi, %o2
   swapa [-%lo(datum)] %asi, %o2
   swapa [-%ulo(datum)] %asi, %o2
_ld:
   ld [%l0], %f2
   ld [%l0 + %l1], %f2
   ld [%l0 + 3], %f2
   ld [%l0 + %lo(datum)], %f2
   ld [%l0 + %ulo(datum)], %f2
   ld [3 + %l0], %f2
   ld [%lo(datum) + %l0], %f2
   ld [%ulo(datum) + %l0], %f2
   ld [%l0 - 4], %f2
   ld [%l0 - %lo(datum)], %f2
   ld [%l0 - %ulo(datum)], %f2
   ld [4], %f2
   ld [%lo(datum)], %f2
   ld [%ulo(datum)], %f2
   ld [-%lo(datum)], %f2
   ld [-%ulo(datum)], %f2
_lda:
   lda [%l0] #ASI_PRIMARY, %f2
   lda [%l0 + %l1] #ASI_PRIMARY, %f2
   lda [%l0 + 3] %asi, %f2
   lda [%l0 + %lo(datum)] %asi, %f2
   lda [%l0 + %ulo(datum)] %asi, %f2
   lda [3 + %l0] %asi, %f2
   lda [%lo(datum) + %l0] %asi, %f2
   lda [%ulo(datum) + %l0] %asi, %f2
   lda [%l0 - 4] %asi, %f2
   lda [%l0 - %lo(datum)] %asi, %f2
   lda [%l0 - %ulo(datum)] %asi, %f2
   lda [4] %asi, %f2
   lda [%lo(datum)] %asi, %f2
   lda [%ulo(datum)] %asi, %f2
   lda [-%lo(datum)] %asi, %f2
   lda [-%ulo(datum)] %asi, %f2
_ldd:
   ldd [%l0], %f2
   ldd [%l0 + %l1], %f2
   ldd [%l0 + 3], %f2
   ldd [%l0 + %lo(datum)], %f2
   ldd [%l0 + %ulo(datum)], %f2
   ldd [3 + %l0], %f2
   ldd [%lo(datum) + %l0], %f2
   ldd [%ulo(datum) + %l0], %f2
   ldd [%l0 - 4], %f2
   ldd [%l0 - %lo(datum)], %f2
   ldd [%l0 - %ulo(datum)], %f2
   ldd [4], %f2
   ldd [%lo(datum)], %f2
   ldd [%ulo(datum)], %f2
   ldd [-%lo(datum)], %f2
   ldd [-%ulo(datum)], %f2
_ldda:
   ldda [%l0] #ASI_PRIMARY, %f2
   ldda [%l0 + %l1] #ASI_PRIMARY, %f2
   ldda [%l0 + 3] %asi, %f2
   ldda [%l0 + %lo(datum)] %asi, %f2
   ldda [%l0 + %ulo(datum)] %asi, %f2
   ldda [3 + %l0] %asi, %f2
   ldda [%lo(datum) + %l0] %asi, %f2
   ldda [%ulo(datum) + %l0] %asi, %f2
   ldda [%l0 - 4] %asi, %f2
   ldda [%l0 - %lo(datum)] %asi, %f2
   ldda [%l0 - %ulo(datum)] %asi, %f2
   ldda [4] %asi, %f2
   ldda [%lo(datum)] %asi, %f2
   ldda [%ulo(datum)] %asi, %f2
   ldda [-%lo(datum)] %asi, %f2
   ldda [-%ulo(datum)] %asi, %f2
_ldq:
   ldq [%l0], %f2
   ldq [%l0 + %l1], %f2
   ldq [%l0 + 3], %f2
   ldq [%l0 + %lo(datum)], %f2
   ldq [%l0 + %ulo(datum)], %f2
   ldq [3 + %l0], %f2
   ldq [%lo(datum) + %l0], %f2
   ldq [%ulo(datum) + %l0], %f2
   ldq [%l0 - 4], %f2
   ldq [%l0 - %lo(datum)], %f2
   ldq [%l0 - %ulo(datum)], %f2
   ldq [4], %f2
   ldq [%lo(datum)], %f2
   ldq [%ulo(datum)], %f2
   ldq [-%lo(datum)], %f2
   ldq [-%ulo(datum)], %f2
_ldqa:
   ldqa [%l0] #ASI_PRIMARY, %f2
   ldqa [%l0 + %l1] #ASI_PRIMARY, %f2
   ldqa [%l0 + 3] %asi, %f2
   ldqa [%l0 + %lo(datum)] %asi, %f2
   ldqa [%l0 + %ulo(datum)] %asi, %f2
   ldqa [3 + %l0] %asi, %f2
   ldqa [%lo(datum) + %l0] %asi, %f2
   ldqa [%ulo(datum) + %l0] %asi, %f2
   ldqa [%l0 - 4] %asi, %f2
   ldqa [%l0 - %lo(datum)] %asi, %f2
   ldqa [%l0 - %ulo(datum)] %asi, %f2
   ldqa [4] %asi, %f2
   ldqa [%lo(datum)] %asi, %f2
   ldqa [%ulo(datum)] %asi, %f2
   ldqa [-%lo(datum)] %asi, %f2
   ldqa [-%ulo(datum)] %asi, %f2
_ldfsr:
   ldfsr [%l0], %fsr
   ldfsr [%l0 + %l1], %fsr
   ldfsr [%l0 + 3], %fsr
   ldfsr [%l0 + %lo(datum)], %fsr
   ldfsr [%l0 + %ulo(datum)], %fsr
   ldfsr [3 + %l0], %fsr
   ldfsr [%lo(datum) + %l0], %fsr
   ldfsr [%ulo(datum) + %l0], %fsr
   ldfsr [%l0 - 4], %fsr
   ldfsr [%l0 - %lo(datum)], %fsr
   ldfsr [%l0 - %ulo(datum)], %fsr
   ldfsr [4], %fsr
   ldfsr [%lo(datum)], %fsr
   ldfsr [%ulo(datum)], %fsr
   ldfsr [-%lo(datum)], %fsr
   ldfsr [-%ulo(datum)], %fsr
_ldxfsr:
   ldxfsr [%l0], %fsr
   ldxfsr [%l0 + %l1], %fsr
   ldxfsr [%l0 + 3], %fsr
   ldxfsr [%l0 + %lo(datum)], %fsr
   ldxfsr [%l0 + %ulo(datum)], %fsr
   ldxfsr [3 + %l0], %fsr
   ldxfsr [%lo(datum) + %l0], %fsr
   ldxfsr [%ulo(datum) + %l0], %fsr
   ldxfsr [%l0 - 4], %fsr
   ldxfsr [%l0 - %lo(datum)], %fsr
   ldxfsr [%l0 - %ulo(datum)], %fsr
   ldxfsr [4], %fsr
   ldxfsr [%lo(datum)], %fsr
   ldxfsr [%ulo(datum)], %fsr
   ldxfsr [-%lo(datum)], %fsr
   ldxfsr [-%ulo(datum)], %fsr
_ldsb:
   ldsb [%l0], %o2
   ldsb [%l0 + %l1], %o2
   ldsb [%l0 + 3], %o2
   ldsb [%l0 + %lo(datum)], %o2
   ldsb [%l0 + %ulo(datum)], %o2
   ldsb [3 + %l0], %o2
   ldsb [%lo(datum) + %l0], %o2
   ldsb [%ulo(datum) + %l0], %o2
   ldsb [%l0 - 4], %o2
   ldsb [%l0 - %lo(datum)], %o2
   ldsb [%l0 - %ulo(datum)], %o2
   ldsb [4], %o2
   ldsb [%lo(datum)], %o2
   ldsb [%ulo(datum)], %o2
   ldsb [-%lo(datum)], %o2
   ldsb [-%ulo(datum)], %o2
_ldsba:
   ldsba [%l0] #ASI_PRIMARY, %o2
   ldsba [%l0 + %l1] #ASI_PRIMARY, %o2
   ldsba [%l0 + 3] %asi, %o2
   ldsba [%l0 + %lo(datum)] %asi, %o2
   ldsba [%l0 + %ulo(datum)] %asi, %o2
   ldsba [3 + %l0] %asi, %o2
   ldsba [%lo(datum) + %l0] %asi, %o2
   ldsba [%ulo(datum) + %l0] %asi, %o2
   ldsba [%l0 - 4] %asi, %o2
   ldsba [%l0 - %lo(datum)] %asi, %o2
   ldsba [%l0 - %ulo(datum)] %asi, %o2
   ldsba [4] %asi, %o2
   ldsba [%lo(datum)] %asi, %o2
   ldsba [%ulo(datum)] %asi, %o2
   ldsba [-%lo(datum)] %asi, %o2
   ldsba [-%ulo(datum)] %asi, %o2
_ldsh:
   ldsh [%l0], %o2
   ldsh [%l0 + %l1], %o2
   ldsh [%l0 + 3], %o2
   ldsh [%l0 + %lo(datum)], %o2
   ldsh [%l0 + %ulo(datum)], %o2
   ldsh [3 + %l0], %o2
   ldsh [%lo(datum) + %l0], %o2
   ldsh [%ulo(datum) + %l0], %o2
   ldsh [%l0 - 4], %o2
   ldsh [%l0 - %lo(datum)], %o2
   ldsh [%l0 - %ulo(datum)], %o2
   ldsh [4], %o2
   ldsh [%lo(datum)], %o2
   ldsh [%ulo(datum)], %o2
   ldsh [-%lo(datum)], %o2
   ldsh [-%ulo(datum)], %o2
_ldsha:
   ldsha [%l0] #ASI_PRIMARY, %o2
   ldsha [%l0 + %l1] #ASI_PRIMARY, %o2
   ldsha [%l0 + 3] %asi, %o2
   ldsha [%l0 + %lo(datum)] %asi, %o2
   ldsha [%l0 + %ulo(datum)] %asi, %o2
   ldsha [3 + %l0] %asi, %o2
   ldsha [%lo(datum) + %l0] %asi, %o2
   ldsha [%ulo(datum) + %l0] %asi, %o2
   ldsha [%l0 - 4] %asi, %o2
   ldsha [%l0 - %lo(datum)] %asi, %o2
   ldsha [%l0 - %ulo(datum)] %asi, %o2
   ldsha [4] %asi, %o2
   ldsha [%lo(datum)] %asi, %o2
   ldsha [%ulo(datum)] %asi, %o2
   ldsha [-%lo(datum)] %asi, %o2
   ldsha [-%ulo(datum)] %asi, %o2
_ldsw:
   ldsw [%l0], %o2
   ldsw [%l0 + %l1], %o2
   ldsw [%l0 + 3], %o2
   ldsw [%l0 + %lo(datum)], %o2
   ldsw [%l0 + %ulo(datum)], %o2
   ldsw [3 + %l0], %o2
   ldsw [%lo(datum) + %l0], %o2
   ldsw [%ulo(datum) + %l0], %o2
   ldsw [%l0 - 4], %o2
   ldsw [%l0 - %lo(datum)], %o2
   ldsw [%l0 - %ulo(datum)], %o2
   ldsw [4], %o2
   ldsw [%lo(datum)], %o2
   ldsw [%ulo(datum)], %o2
   ldsw [-%lo(datum)], %o2
   ldsw [-%ulo(datum)], %o2
_ldswa:
   ldswa [%l0] #ASI_PRIMARY, %o2
   ldswa [%l0 + %l1] #ASI_PRIMARY, %o2
   ldswa [%l0 + 3] %asi, %o2
   ldswa [%l0 + %lo(datum)] %asi, %o2
   ldswa [%l0 + %ulo(datum)] %asi, %o2
   ldswa [3 + %l0] %asi, %o2
   ldswa [%lo(datum) + %l0] %asi, %o2
   ldswa [%ulo(datum) + %l0] %asi, %o2
   ldswa [%l0 - 4] %asi, %o2
   ldswa [%l0 - %lo(datum)] %asi, %o2
   ldswa [%l0 - %ulo(datum)] %asi, %o2
   ldswa [4] %asi, %o2
   ldswa [%lo(datum)] %asi, %o2
   ldswa [%ulo(datum)] %asi, %o2
   ldswa [-%lo(datum)] %asi, %o2
   ldswa [-%ulo(datum)] %asi, %o2
_ldub:
   ldub [%l0], %o2
   ldub [%l0 + %l1], %o2
   ldub [%l0 + 3], %o2
   ldub [%l0 + %lo(datum)], %o2
   ldub [%l0 + %ulo(datum)], %o2
   ldub [3 + %l0], %o2
   ldub [%lo(datum) + %l0], %o2
   ldub [%ulo(datum) + %l0], %o2
   ldub [%l0 - 4], %o2
   ldub [%l0 - %lo(datum)], %o2
   ldub [%l0 - %ulo(datum)], %o2
   ldub [4], %o2
   ldub [%lo(datum)], %o2
   ldub [%ulo(datum)], %o2
   ldub [-%lo(datum)], %o2
   ldub [-%ulo(datum)], %o2
_lduba:
   lduba [%l0] #ASI_PRIMARY, %o2
   lduba [%l0 + %l1] #ASI_PRIMARY, %o2
   lduba [%l0 + 3] %asi, %o2
   lduba [%l0 + %lo(datum)] %asi, %o2
   lduba [%l0 + %ulo(datum)] %asi, %o2
   lduba [3 + %l0] %asi, %o2
   lduba [%lo(datum) + %l0] %asi, %o2
   lduba [%ulo(datum) + %l0] %asi, %o2
   lduba [%l0 - 4] %asi, %o2
   lduba [%l0 - %lo(datum)] %asi, %o2
   lduba [%l0 - %ulo(datum)] %asi, %o2
   lduba [4] %asi, %o2
   lduba [%lo(datum)] %asi, %o2
   lduba [%ulo(datum)] %asi, %o2
   lduba [-%lo(datum)] %asi, %o2
   lduba [-%ulo(datum)] %asi, %o2
_lduh:
   lduh [%l0], %o2
   lduh [%l0 + %l1], %o2
   lduh [%l0 + 3], %o2
   lduh [%l0 + %lo(datum)], %o2
   lduh [%l0 + %ulo(datum)], %o2
   lduh [3 + %l0], %o2
   lduh [%lo(datum) + %l0], %o2
   lduh [%ulo(datum) + %l0], %o2
   lduh [%l0 - 4], %o2
   lduh [%l0 - %lo(datum)], %o2
   lduh [%l0 - %ulo(datum)], %o2
   lduh [4], %o2
   lduh [%lo(datum)], %o2
   lduh [%ulo(datum)], %o2
   lduh [-%lo(datum)], %o2
   lduh [-%ulo(datum)], %o2
_lduha:
   lduha [%l0] #ASI_PRIMARY, %o2
   lduha [%l0 + %l1] #ASI_PRIMARY, %o2
   lduha [%l0 + 3] %asi, %o2
   lduha [%l0 + %lo(datum)] %asi, %o2
   lduha [%l0 + %ulo(datum)] %asi, %o2
   lduha [3 + %l0] %asi, %o2
   lduha [%lo(datum) + %l0] %asi, %o2
   lduha [%ulo(datum) + %l0] %asi, %o2
   lduha [%l0 - 4] %asi, %o2
   lduha [%l0 - %lo(datum)] %asi, %o2
   lduha [%l0 - %ulo(datum)] %asi, %o2
   lduha [4] %asi, %o2
   lduha [%lo(datum)] %asi, %o2
   lduha [%ulo(datum)] %asi, %o2
   lduha [-%lo(datum)] %asi, %o2
   lduha [-%ulo(datum)] %asi, %o2
_lduw:
   lduw [%l0], %o2
   lduw [%l0 + %l1], %o2
   lduw [%l0 + 3], %o2
   lduw [%l0 + %lo(datum)], %o2
   lduw [%l0 + %ulo(datum)], %o2
   lduw [3 + %l0], %o2
   lduw [%lo(datum) + %l0], %o2
   lduw [%ulo(datum) + %l0], %o2
   lduw [%l0 - 4], %o2
   lduw [%l0 - %lo(datum)], %o2
   lduw [%l0 - %ulo(datum)], %o2
   lduw [4], %o2
   lduw [%lo(datum)], %o2
   lduw [%ulo(datum)], %o2
   lduw [-%lo(datum)], %o2
   lduw [-%ulo(datum)], %o2
_lduwa:
   lduwa [%l0] #ASI_PRIMARY, %o2
   lduwa [%l0 + %l1] #ASI_PRIMARY, %o2
   lduwa [%l0 + 3] %asi, %o2
   lduwa [%l0 + %lo(datum)] %asi, %o2
   lduwa [%l0 + %ulo(datum)] %asi, %o2
   lduwa [3 + %l0] %asi, %o2
   lduwa [%lo(datum) + %l0] %asi, %o2
   lduwa [%ulo(datum) + %l0] %asi, %o2
   lduwa [%l0 - 4] %asi, %o2
   lduwa [%l0 - %lo(datum)] %asi, %o2
   lduwa [%l0 - %ulo(datum)] %asi, %o2
   lduwa [4] %asi, %o2
   lduwa [%lo(datum)] %asi, %o2
   lduwa [%ulo(datum)] %asi, %o2
   lduwa [-%lo(datum)] %asi, %o2
   lduwa [-%ulo(datum)] %asi, %o2
_ldx:
   ldx [%l0], %o2
   ldx [%l0 + %l1], %o2
   ldx [%l0 + 3], %o2
   ldx [%l0 + %lo(datum)], %o2
   ldx [%l0 + %ulo(datum)], %o2
   ldx [3 + %l0], %o2
   ldx [%lo(datum) + %l0], %o2
   ldx [%ulo(datum) + %l0], %o2
   ldx [%l0 - 4], %o2
   ldx [%l0 - %lo(datum)], %o2
   ldx [%l0 - %ulo(datum)], %o2
   ldx [4], %o2
   ldx [%lo(datum)], %o2
   ldx [%ulo(datum)], %o2
   ldx [-%lo(datum)], %o2
   ldx [-%ulo(datum)], %o2
_ldxa:
   ldxa [%l0] #ASI_PRIMARY, %o2
   ldxa [%l0 + %l1] #ASI_PRIMARY, %o2
   ldxa [%l0 + 3] %asi, %o2
   ldxa [%l0 + %lo(datum)] %asi, %o2
   ldxa [%l0 + %ulo(datum)] %asi, %o2
   ldxa [3 + %l0] %asi, %o2
   ldxa [%lo(datum) + %l0] %asi, %o2
   ldxa [%ulo(datum) + %l0] %asi, %o2
   ldxa [%l0 - 4] %asi, %o2
   ldxa [%l0 - %lo(datum)] %asi, %o2
   ldxa [%l0 - %ulo(datum)] %asi, %o2
   ldxa [4] %asi, %o2
   ldxa [%lo(datum)] %asi, %o2
   ldxa [%ulo(datum)] %asi, %o2
   ldxa [-%lo(datum)] %asi, %o2
   ldxa [-%ulo(datum)] %asi, %o2
_ldn:
   ldn [%l0], %o2
   ldn [%l0 + %l1], %o2
   ldn [%l0 + 3], %o2
   ldn [%l0 + %lo(datum)], %o2
   ldn [%l0 + %ulo(datum)], %o2
   ldn [3 + %l0], %o2
   ldn [%lo(datum) + %l0], %o2
   ldn [%ulo(datum) + %l0], %o2
   ldn [%l0 - 4], %o2
   ldn [%l0 - %lo(datum)], %o2
   ldn [%l0 - %ulo(datum)], %o2
   ldn [4], %o2
   ldn [%lo(datum)], %o2
   ldn [%ulo(datum)], %o2
   ldn [-%lo(datum)], %o2
   ldn [-%ulo(datum)], %o2
_ldna:
   ldna [%l0] #ASI_PRIMARY, %o2
   ldna [%l0 + %l1] #ASI_PRIMARY, %o2
   ldna [%l0 + 3] %asi, %o2
   ldna [%l0 + %lo(datum)] %asi, %o2
   ldna [%l0 + %ulo(datum)] %asi, %o2
   ldna [3 + %l0] %asi, %o2
   ldna [%lo(datum) + %l0] %asi, %o2
   ldna [%ulo(datum) + %l0] %asi, %o2
   ldna [%l0 - 4] %asi, %o2
   ldna [%l0 - %lo(datum)] %asi, %o2
   ldna [%l0 - %ulo(datum)] %asi, %o2
   ldna [4] %asi, %o2
   ldna [%lo(datum)] %asi, %o2
   ldna [%ulo(datum)] %asi, %o2
   ldna [-%lo(datum)] %asi, %o2
   ldna [-%ulo(datum)] %asi, %o2
_ldd:
   ldd [%l0], %o2
   ldd [%l0 + %l1], %o2
   ldd [%l0 + 3], %o2
   ldd [%l0 + %lo(datum)], %o2
   ldd [%l0 + %ulo(datum)], %o2
   ldd [3 + %l0], %o2
   ldd [%lo(datum) + %l0], %o2
   ldd [%ulo(datum) + %l0], %o2
   ldd [%l0 - 4], %o2
   ldd [%l0 - %lo(datum)], %o2
   ldd [%l0 - %ulo(datum)], %o2
   ldd [4], %o2
   ldd [%lo(datum)], %o2
   ldd [%ulo(datum)], %o2
   ldd [-%lo(datum)], %o2
   ldd [-%ulo(datum)], %o2
_ldda:
   ldda [%l0] #ASI_PRIMARY, %o2
   ldda [%l0 + %l1] #ASI_PRIMARY, %o2
   ldda [%l0 + 3] %asi, %o2
   ldda [%l0 + %lo(datum)] %asi, %o2
   ldda [%l0 + %ulo(datum)] %asi, %o2
   ldda [3 + %l0] %asi, %o2
   ldda [%lo(datum) + %l0] %asi, %o2
   ldda [%ulo(datum) + %l0] %asi, %o2
   ldda [%l0 - 4] %asi, %o2
   ldda [%l0 - %lo(datum)] %asi, %o2
   ldda [%l0 - %ulo(datum)] %asi, %o2
   ldda [4] %asi, %o2
   ldda [%lo(datum)] %asi, %o2
   ldda [%ulo(datum)] %asi, %o2
   ldda [-%lo(datum)] %asi, %o2
   ldda [-%ulo(datum)] %asi, %o2
_ld:
   ld [%l0], %o2
   ld [%l0 + %l1], %o2
   ld [%l0 + 3], %o2
   ld [%l0 + %lo(datum)], %o2
   ld [%l0 + %ulo(datum)], %o2
   ld [3 + %l0], %o2
   ld [%lo(datum) + %l0], %o2
   ld [%ulo(datum) + %l0], %o2
   ld [%l0 - 4], %o2
   ld [%l0 - %lo(datum)], %o2
   ld [%l0 - %ulo(datum)], %o2
   ld [4], %o2
   ld [%lo(datum)], %o2
   ld [%ulo(datum)], %o2
   ld [-%lo(datum)], %o2
   ld [-%ulo(datum)], %o2
_lda:
   lda [%l0] #ASI_PRIMARY, %o2
   lda [%l0 + %l1] #ASI_PRIMARY, %o2
   lda [%l0 + 3] %asi, %o2
   lda [%l0 + %lo(datum)] %asi, %o2
   lda [%l0 + %ulo(datum)] %asi, %o2
   lda [3 + %l0] %asi, %o2
   lda [%lo(datum) + %l0] %asi, %o2
   lda [%ulo(datum) + %l0] %asi, %o2
   lda [%l0 - 4] %asi, %o2
   lda [%l0 - %lo(datum)] %asi, %o2
   lda [%l0 - %ulo(datum)] %asi, %o2
   lda [4] %asi, %o2
   lda [%lo(datum)] %asi, %o2
   lda [%ulo(datum)] %asi, %o2
   lda [-%lo(datum)] %asi, %o2
   lda [-%ulo(datum)] %asi, %o2
_st:
   st %f2, [%l0]
   st %f2, [%l0 + %l1]
   st %f2, [%l0 + 3]
   st %f2, [%l0 + %lo(datum)]
   st %f2, [%l0 + %ulo(datum)]
   st %f2, [3 + %l0]
   st %f2, [%lo(datum) + %l0]
   st %f2, [%ulo(datum) + %l0]
   st %f2, [%l0 - 4]
   st %f2, [%l0 - %lo(datum)]
   st %f2, [%l0 - %ulo(datum)]
   st %f2, [4]
   st %f2, [%lo(datum)]
   st %f2, [%ulo(datum)]
   st %f2, [-%lo(datum)]
   st %f2, [-%ulo(datum)]
_sta:
   sta %f2, [%l0] #ASI_PRIMARY
   sta %f2, [%l0 + %l1] #ASI_PRIMARY
   sta %f2, [%l0 + 3] %asi
   sta %f2, [%l0 + %lo(datum)] %asi
   sta %f2, [%l0 + %ulo(datum)] %asi
   sta %f2, [3 + %l0] %asi
   sta %f2, [%lo(datum) + %l0] %asi
   sta %f2, [%ulo(datum) + %l0] %asi
   sta %f2, [%l0 - 4] %asi
   sta %f2, [%l0 - %lo(datum)] %asi
   sta %f2, [%l0 - %ulo(datum)] %asi
   sta %f2, [4] %asi
   sta %f2, [%lo(datum)] %asi
   sta %f2, [%ulo(datum)] %asi
   sta %f2, [-%lo(datum)] %asi
   sta %f2, [-%ulo(datum)] %asi
_std:
   std %f2, [%l0]
   std %f2, [%l0 + %l1]
   std %f2, [%l0 + 3]
   std %f2, [%l0 + %lo(datum)]
   std %f2, [%l0 + %ulo(datum)]
   std %f2, [3 + %l0]
   std %f2, [%lo(datum) + %l0]
   std %f2, [%ulo(datum) + %l0]
   std %f2, [%l0 - 4]
   std %f2, [%l0 - %lo(datum)]
   std %f2, [%l0 - %ulo(datum)]
   std %f2, [4]
   std %f2, [%lo(datum)]
   std %f2, [%ulo(datum)]
   std %f2, [-%lo(datum)]
   std %f2, [-%ulo(datum)]
_stda:
   stda %f2, [%l0] #ASI_PRIMARY
   stda %f2, [%l0 + %l1] #ASI_PRIMARY
   stda %f2, [%l0 + 3] %asi
   stda %f2, [%l0 + %lo(datum)] %asi
   stda %f2, [%l0 + %ulo(datum)] %asi
   stda %f2, [3 + %l0] %asi
   stda %f2, [%lo(datum) + %l0] %asi
   stda %f2, [%ulo(datum) + %l0] %asi
   stda %f2, [%l0 - 4] %asi
   stda %f2, [%l0 - %lo(datum)] %asi
   stda %f2, [%l0 - %ulo(datum)] %asi
   stda %f2, [4] %asi
   stda %f2, [%lo(datum)] %asi
   stda %f2, [%ulo(datum)] %asi
   stda %f2, [-%lo(datum)] %asi
   stda %f2, [-%ulo(datum)] %asi
_stdq:
   stdq %f2, [%l0]
   stdq %f2, [%l0 + %l1]
   stdq %f2, [%l0 + 3]
   stdq %f2, [%l0 + %lo(datum)]
   stdq %f2, [%l0 + %ulo(datum)]
   stdq %f2, [3 + %l0]
   stdq %f2, [%lo(datum) + %l0]
   stdq %f2, [%ulo(datum) + %l0]
   stdq %f2, [%l0 - 4]
   stdq %f2, [%l0 - %lo(datum)]
   stdq %f2, [%l0 - %ulo(datum)]
   stdq %f2, [4]
   stdq %f2, [%lo(datum)]
   stdq %f2, [%ulo(datum)]
   stdq %f2, [-%lo(datum)]
   stdq %f2, [-%ulo(datum)]
_stdqa:
   stdqa %f2, [%l0] #ASI_PRIMARY
   stdqa %f2, [%l0 + %l1] #ASI_PRIMARY
   stdqa %f2, [%l0 + 3] %asi
   stdqa %f2, [%l0 + %lo(datum)] %asi
   stdqa %f2, [%l0 + %ulo(datum)] %asi
   stdqa %f2, [3 + %l0] %asi
   stdqa %f2, [%lo(datum) + %l0] %asi
   stdqa %f2, [%ulo(datum) + %l0] %asi
   stdqa %f2, [%l0 - 4] %asi
   stdqa %f2, [%l0 - %lo(datum)] %asi
   stdqa %f2, [%l0 - %ulo(datum)] %asi
   stdqa %f2, [4] %asi
   stdqa %f2, [%lo(datum)] %asi
   stdqa %f2, [%ulo(datum)] %asi
   stdqa %f2, [-%lo(datum)] %asi
   stdqa %f2, [-%ulo(datum)] %asi
_stfsr:
   stfsr %fsr, [%l0]
   stfsr %fsr, [%l0 + %l1]
   stfsr %fsr, [%l0 + 3]
   stfsr %fsr, [%l0 + %lo(datum)]
   stfsr %fsr, [%l0 + %ulo(datum)]
   stfsr %fsr, [3 + %l0]
   stfsr %fsr, [%lo(datum) + %l0]
   stfsr %fsr, [%ulo(datum) + %l0]
   stfsr %fsr, [%l0 - 4]
   stfsr %fsr, [%l0 - %lo(datum)]
   stfsr %fsr, [%l0 - %ulo(datum)]
   stfsr %fsr, [4]
   stfsr %fsr, [%lo(datum)]
   stfsr %fsr, [%ulo(datum)]
   stfsr %fsr, [-%lo(datum)]
   stfsr %fsr, [-%ulo(datum)]
_stxfsr:
   stxfsr %fsr, [%l0]
   stxfsr %fsr, [%l0 + %l1]
   stxfsr %fsr, [%l0 + 3]
   stxfsr %fsr, [%l0 + %lo(datum)]
   stxfsr %fsr, [%l0 + %ulo(datum)]
   stxfsr %fsr, [3 + %l0]
   stxfsr %fsr, [%lo(datum) + %l0]
   stxfsr %fsr, [%ulo(datum) + %l0]
   stxfsr %fsr, [%l0 - 4]
   stxfsr %fsr, [%l0 - %lo(datum)]
   stxfsr %fsr, [%l0 - %ulo(datum)]
   stxfsr %fsr, [4]
   stxfsr %fsr, [%lo(datum)]
   stxfsr %fsr, [%ulo(datum)]
   stxfsr %fsr, [-%lo(datum)]
   stxfsr %fsr, [-%ulo(datum)]
_stb:
   stb %o2, [%l0]
   stb %o2, [%l0 + %l1]
   stb %o2, [%l0 + 3]
   stb %o2, [%l0 + %lo(datum)]
   stb %o2, [%l0 + %ulo(datum)]
   stb %o2, [3 + %l0]
   stb %o2, [%lo(datum) + %l0]
   stb %o2, [%ulo(datum) + %l0]
   stb %o2, [%l0 - 4]
   stb %o2, [%l0 - %lo(datum)]
   stb %o2, [%l0 - %ulo(datum)]
   stb %o2, [4]
   stb %o2, [%lo(datum)]
   stb %o2, [%ulo(datum)]
   stb %o2, [-%lo(datum)]
   stb %o2, [-%ulo(datum)]
_stba:
   stba %o2, [%l0] #ASI_PRIMARY
   stba %o2, [%l0 + %l1] #ASI_PRIMARY
   stba %o2, [%l0 + 3] %asi
   stba %o2, [%l0 + %lo(datum)] %asi
   stba %o2, [%l0 + %ulo(datum)] %asi
   stba %o2, [3 + %l0] %asi
   stba %o2, [%lo(datum) + %l0] %asi
   stba %o2, [%ulo(datum) + %l0] %asi
   stba %o2, [%l0 - 4] %asi
   stba %o2, [%l0 - %lo(datum)] %asi
   stba %o2, [%l0 - %ulo(datum)] %asi
   stba %o2, [4] %asi
   stba %o2, [%lo(datum)] %asi
   stba %o2, [%ulo(datum)] %asi
   stba %o2, [-%lo(datum)] %asi
   stba %o2, [-%ulo(datum)] %asi
_sth:
   sth %o2, [%l0]
   sth %o2, [%l0 + %l1]
   sth %o2, [%l0 + 3]
   sth %o2, [%l0 + %lo(datum)]
   sth %o2, [%l0 + %ulo(datum)]
   sth %o2, [3 + %l0]
   sth %o2, [%lo(datum) + %l0]
   sth %o2, [%ulo(datum) + %l0]
   sth %o2, [%l0 - 4]
   sth %o2, [%l0 - %lo(datum)]
   sth %o2, [%l0 - %ulo(datum)]
   sth %o2, [4]
   sth %o2, [%lo(datum)]
   sth %o2, [%ulo(datum)]
   sth %o2, [-%lo(datum)]
   sth %o2, [-%ulo(datum)]
_stha:
   stha %o2, [%l0] #ASI_PRIMARY
   stha %o2, [%l0 + %l1] #ASI_PRIMARY
   stha %o2, [%l0 + 3] %asi
   stha %o2, [%l0 + %lo(datum)] %asi
   stha %o2, [%l0 + %ulo(datum)] %asi
   stha %o2, [3 + %l0] %asi
   stha %o2, [%lo(datum) + %l0] %asi
   stha %o2, [%ulo(datum) + %l0] %asi
   stha %o2, [%l0 - 4] %asi
   stha %o2, [%l0 - %lo(datum)] %asi
   stha %o2, [%l0 - %ulo(datum)] %asi
   stha %o2, [4] %asi
   stha %o2, [%lo(datum)] %asi
   stha %o2, [%ulo(datum)] %asi
   stha %o2, [-%lo(datum)] %asi
   stha %o2, [-%ulo(datum)] %asi
_stw:
   stw %o2, [%l0]
   stw %o2, [%l0 + %l1]
   stw %o2, [%l0 + 3]
   stw %o2, [%l0 + %lo(datum)]
   stw %o2, [%l0 + %ulo(datum)]
   stw %o2, [3 + %l0]
   stw %o2, [%lo(datum) + %l0]
   stw %o2, [%ulo(datum) + %l0]
   stw %o2, [%l0 - 4]
   stw %o2, [%l0 - %lo(datum)]
   stw %o2, [%l0 - %ulo(datum)]
   stw %o2, [4]
   stw %o2, [%lo(datum)]
   stw %o2, [%ulo(datum)]
   stw %o2, [-%lo(datum)]
   stw %o2, [-%ulo(datum)]
_stwa:
   stwa %o2, [%l0] #ASI_PRIMARY
   stwa %o2, [%l0 + %l1] #ASI_PRIMARY
   stwa %o2, [%l0 + 3] %asi
   stwa %o2, [%l0 + %lo(datum)] %asi
   stwa %o2, [%l0 + %ulo(datum)] %asi
   stwa %o2, [3 + %l0] %asi
   stwa %o2, [%lo(datum) + %l0] %asi
   stwa %o2, [%ulo(datum) + %l0] %asi
   stwa %o2, [%l0 - 4] %asi
   stwa %o2, [%l0 - %lo(datum)] %asi
   stwa %o2, [%l0 - %ulo(datum)] %asi
   stwa %o2, [4] %asi
   stwa %o2, [%lo(datum)] %asi
   stwa %o2, [%ulo(datum)] %asi
   stwa %o2, [-%lo(datum)] %asi
   stwa %o2, [-%ulo(datum)] %asi
_stx:
   stx %o2, [%l0]
   stx %o2, [%l0 + %l1]
   stx %o2, [%l0 + 3]
   stx %o2, [%l0 + %lo(datum)]
   stx %o2, [%l0 + %ulo(datum)]
   stx %o2, [3 + %l0]
   stx %o2, [%lo(datum) + %l0]
   stx %o2, [%ulo(datum) + %l0]
   stx %o2, [%l0 - 4]
   stx %o2, [%l0 - %lo(datum)]
   stx %o2, [%l0 - %ulo(datum)]
   stx %o2, [4]
   stx %o2, [%lo(datum)]
   stx %o2, [%ulo(datum)]
   stx %o2, [-%lo(datum)]
   stx %o2, [-%ulo(datum)]
_stxa:
   stxa %o2, [%l0] #ASI_PRIMARY
   stxa %o2, [%l0 + %l1] #ASI_PRIMARY
   stxa %o2, [%l0 + 3] %asi
   stxa %o2, [%l0 + %lo(datum)] %asi
   stxa %o2, [%l0 + %ulo(datum)] %asi
   stxa %o2, [3 + %l0] %asi
   stxa %o2, [%lo(datum) + %l0] %asi
   stxa %o2, [%ulo(datum) + %l0] %asi
   stxa %o2, [%l0 - 4] %asi
   stxa %o2, [%l0 - %lo(datum)] %asi
   stxa %o2, [%l0 - %ulo(datum)] %asi
   stxa %o2, [4] %asi
   stxa %o2, [%lo(datum)] %asi
   stxa %o2, [%ulo(datum)] %asi
   stxa %o2, [-%lo(datum)] %asi
   stxa %o2, [-%ulo(datum)] %asi
_stn:
   stn %o2, [%l0]
   stn %o2, [%l0 + %l1]
   stn %o2, [%l0 + 3]
   stn %o2, [%l0 + %lo(datum)]
   stn %o2, [%l0 + %ulo(datum)]
   stn %o2, [3 + %l0]
   stn %o2, [%lo(datum) + %l0]
   stn %o2, [%ulo(datum) + %l0]
   stn %o2, [%l0 - 4]
   stn %o2, [%l0 - %lo(datum)]
   stn %o2, [%l0 - %ulo(datum)]
   stn %o2, [4]
   stn %o2, [%lo(datum)]
   stn %o2, [%ulo(datum)]
   stn %o2, [-%lo(datum)]
   stn %o2, [-%ulo(datum)]
_stna:
   stna %o2, [%l0] #ASI_PRIMARY
   stna %o2, [%l0 + %l1] #ASI_PRIMARY
   stna %o2, [%l0 + 3] %asi
   stna %o2, [%l0 + %lo(datum)] %asi
   stna %o2, [%l0 + %ulo(datum)] %asi
   stna %o2, [3 + %l0] %asi
   stna %o2, [%lo(datum) + %l0] %asi
   stna %o2, [%ulo(datum) + %l0] %asi
   stna %o2, [%l0 - 4] %asi
   stna %o2, [%l0 - %lo(datum)] %asi
   stna %o2, [%l0 - %ulo(datum)] %asi
   stna %o2, [4] %asi
   stna %o2, [%lo(datum)] %asi
   stna %o2, [%ulo(datum)] %asi
   stna %o2, [-%lo(datum)] %asi
   stna %o2, [-%ulo(datum)] %asi
_std:
   std %o2, [%l0]
   std %o2, [%l0 + %l1]
   std %o2, [%l0 + 3]
   std %o2, [%l0 + %lo(datum)]
   std %o2, [%l0 + %ulo(datum)]
   std %o2, [3 + %l0]
   std %o2, [%lo(datum) + %l0]
   std %o2, [%ulo(datum) + %l0]
   std %o2, [%l0 - 4]
   std %o2, [%l0 - %lo(datum)]
   std %o2, [%l0 - %ulo(datum)]
   std %o2, [4]
   std %o2, [%lo(datum)]
   std %o2, [%ulo(datum)]
   std %o2, [-%lo(datum)]
   std %o2, [-%ulo(datum)]
_stda:
   stda %o2, [%l0] #ASI_PRIMARY
   stda %o2, [%l0 + %l1] #ASI_PRIMARY
   stda %o2, [%l0 + 3] %asi
   stda %o2, [%l0 + %lo(datum)] %asi
   stda %o2, [%l0 + %ulo(datum)] %asi
   stda %o2, [3 + %l0] %asi
   stda %o2, [%lo(datum) + %l0] %asi
   stda %o2, [%ulo(datum) + %l0] %asi
   stda %o2, [%l0 - 4] %asi
   stda %o2, [%l0 - %lo(datum)] %asi
   stda %o2, [%l0 - %ulo(datum)] %asi
   stda %o2, [4] %asi
   stda %o2, [%lo(datum)] %asi
   stda %o2, [%ulo(datum)] %asi
   stda %o2, [-%lo(datum)] %asi
   stda %o2, [-%ulo(datum)] %asi
_stsb:
   stsb %o2, [%l0]
   stsb %o2, [%l0 + %l1]
   stsb %o2, [%l0 + 3]
   stsb %o2, [%l0 + %lo(datum)]
   stsb %o2, [%l0 + %ulo(datum)]
   stsb %o2, [3 + %l0]
   stsb %o2, [%lo(datum) + %l0]
   stsb %o2, [%ulo(datum) + %l0]
   stsb %o2, [%l0 - 4]
   stsb %o2, [%l0 - %lo(datum)]
   stsb %o2, [%l0 - %ulo(datum)]
   stsb %o2, [4]
   stsb %o2, [%lo(datum)]
   stsb %o2, [%ulo(datum)]
   stsb %o2, [-%lo(datum)]
   stsb %o2, [-%ulo(datum)]
_stsba:
   stsba %o2, [%l0] #ASI_PRIMARY
   stsba %o2, [%l0 + %l1] #ASI_PRIMARY
   stsba %o2, [%l0 + 3] %asi
   stsba %o2, [%l0 + %lo(datum)] %asi
   stsba %o2, [%l0 + %ulo(datum)] %asi
   stsba %o2, [3 + %l0] %asi
   stsba %o2, [%lo(datum) + %l0] %asi
   stsba %o2, [%ulo(datum) + %l0] %asi
   stsba %o2, [%l0 - 4] %asi
   stsba %o2, [%l0 - %lo(datum)] %asi
   stsba %o2, [%l0 - %ulo(datum)] %asi
   stsba %o2, [4] %asi
   stsba %o2, [%lo(datum)] %asi
   stsba %o2, [%ulo(datum)] %asi
   stsba %o2, [-%lo(datum)] %asi
   stsba %o2, [-%ulo(datum)] %asi
_stub:
   stub %o2, [%l0]
   stub %o2, [%l0 + %l1]
   stub %o2, [%l0 + 3]
   stub %o2, [%l0 + %lo(datum)]
   stub %o2, [%l0 + %ulo(datum)]
   stub %o2, [3 + %l0]
   stub %o2, [%lo(datum) + %l0]
   stub %o2, [%ulo(datum) + %l0]
   stub %o2, [%l0 - 4]
   stub %o2, [%l0 - %lo(datum)]
   stub %o2, [%l0 - %ulo(datum)]
   stub %o2, [4]
   stub %o2, [%lo(datum)]
   stub %o2, [%ulo(datum)]
   stub %o2, [-%lo(datum)]
   stub %o2, [-%ulo(datum)]
_stuba:
   stuba %o2, [%l0] #ASI_PRIMARY
   stuba %o2, [%l0 + %l1] #ASI_PRIMARY
   stuba %o2, [%l0 + 3] %asi
   stuba %o2, [%l0 + %lo(datum)] %asi
   stuba %o2, [%l0 + %ulo(datum)] %asi
   stuba %o2, [3 + %l0] %asi
   stuba %o2, [%lo(datum) + %l0] %asi
   stuba %o2, [%ulo(datum) + %l0] %asi
   stuba %o2, [%l0 - 4] %asi
   stuba %o2, [%l0 - %lo(datum)] %asi
   stuba %o2, [%l0 - %ulo(datum)] %asi
   stuba %o2, [4] %asi
   stuba %o2, [%lo(datum)] %asi
   stuba %o2, [%ulo(datum)] %asi
   stuba %o2, [-%lo(datum)] %asi
   stuba %o2, [-%ulo(datum)] %asi
_stsh:
   stsh %o2, [%l0]
   stsh %o2, [%l0 + %l1]
   stsh %o2, [%l0 + 3]
   stsh %o2, [%l0 + %lo(datum)]
   stsh %o2, [%l0 + %ulo(datum)]
   stsh %o2, [3 + %l0]
   stsh %o2, [%lo(datum) + %l0]
   stsh %o2, [%ulo(datum) + %l0]
   stsh %o2, [%l0 - 4]
   stsh %o2, [%l0 - %lo(datum)]
   stsh %o2, [%l0 - %ulo(datum)]
   stsh %o2, [4]
   stsh %o2, [%lo(datum)]
   stsh %o2, [%ulo(datum)]
   stsh %o2, [-%lo(datum)]
   stsh %o2, [-%ulo(datum)]
_stsha:
   stsha %o2, [%l0] #ASI_PRIMARY
   stsha %o2, [%l0 + %l1] #ASI_PRIMARY
   stsha %o2, [%l0 + 3] %asi
   stsha %o2, [%l0 + %lo(datum)] %asi
   stsha %o2, [%l0 + %ulo(datum)] %asi
   stsha %o2, [3 + %l0] %asi
   stsha %o2, [%lo(datum) + %l0] %asi
   stsha %o2, [%ulo(datum) + %l0] %asi
   stsha %o2, [%l0 - 4] %asi
   stsha %o2, [%l0 - %lo(datum)] %asi
   stsha %o2, [%l0 - %ulo(datum)] %asi
   stsha %o2, [4] %asi
   stsha %o2, [%lo(datum)] %asi
   stsha %o2, [%ulo(datum)] %asi
   stsha %o2, [-%lo(datum)] %asi
   stsha %o2, [-%ulo(datum)] %asi
_stuh:
   stuh %o2, [%l0]
   stuh %o2, [%l0 + %l1]
   stuh %o2, [%l0 + 3]
   stuh %o2, [%l0 + %lo(datum)]
   stuh %o2, [%l0 + %ulo(datum)]
   stuh %o2, [3 + %l0]
   stuh %o2, [%lo(datum) + %l0]
   stuh %o2, [%ulo(datum) + %l0]
   stuh %o2, [%l0 - 4]
   stuh %o2, [%l0 - %lo(datum)]
   stuh %o2, [%l0 - %ulo(datum)]
   stuh %o2, [4]
   stuh %o2, [%lo(datum)]
   stuh %o2, [%ulo(datum)]
   stuh %o2, [-%lo(datum)]
   stuh %o2, [-%ulo(datum)]
_stuha:
   stuha %o2, [%l0] #ASI_PRIMARY
   stuha %o2, [%l0 + %l1] #ASI_PRIMARY
   stuha %o2, [%l0 + 3] %asi
   stuha %o2, [%l0 + %lo(datum)] %asi
   stuha %o2, [%l0 + %ulo(datum)] %asi
   stuha %o2, [3 + %l0] %asi
   stuha %o2, [%lo(datum) + %l0] %asi
   stuha %o2, [%ulo(datum) + %l0] %asi
   stuha %o2, [%l0 - 4] %asi
   stuha %o2, [%l0 - %lo(datum)] %asi
   stuha %o2, [%l0 - %ulo(datum)] %asi
   stuha %o2, [4] %asi
   stuha %o2, [%lo(datum)] %asi
   stuha %o2, [%ulo(datum)] %asi
   stuha %o2, [-%lo(datum)] %asi
   stuha %o2, [-%ulo(datum)] %asi
_st:
   st %o2, [%l0]
   st %o2, [%l0 + %l1]
   st %o2, [%l0 + 3]
   st %o2, [%l0 + %lo(datum)]
   st %o2, [%l0 + %ulo(datum)]
   st %o2, [3 + %l0]
   st %o2, [%lo(datum) + %l0]
   st %o2, [%ulo(datum) + %l0]
   st %o2, [%l0 - 4]
   st %o2, [%l0 - %lo(datum)]
   st %o2, [%l0 - %ulo(datum)]
   st %o2, [4]
   st %o2, [%lo(datum)]
   st %o2, [%ulo(datum)]
   st %o2, [-%lo(datum)]
   st %o2, [-%ulo(datum)]
_sta:
   sta %o2, [%l0] #ASI_PRIMARY
   sta %o2, [%l0 + %l1] #ASI_PRIMARY
   sta %o2, [%l0 + 3] %asi
   sta %o2, [%l0 + %lo(datum)] %asi
   sta %o2, [%l0 + %ulo(datum)] %asi
   sta %o2, [3 + %l0] %asi
   sta %o2, [%lo(datum) + %l0] %asi
   sta %o2, [%ulo(datum) + %l0] %asi
   sta %o2, [%l0 - 4] %asi
   sta %o2, [%l0 - %lo(datum)] %asi
   sta %o2, [%l0 - %ulo(datum)] %asi
   sta %o2, [4] %asi
   sta %o2, [%lo(datum)] %asi
   sta %o2, [%ulo(datum)] %asi
   sta %o2, [-%lo(datum)] %asi
   sta %o2, [-%ulo(datum)] %asi
_stsw:
   stsw %o2, [%l0]
   stsw %o2, [%l0 + %l1]
   stsw %o2, [%l0 + 3]
   stsw %o2, [%l0 + %lo(datum)]
   stsw %o2, [%l0 + %ulo(datum)]
   stsw %o2, [3 + %l0]
   stsw %o2, [%lo(datum) + %l0]
   stsw %o2, [%ulo(datum) + %l0]
   stsw %o2, [%l0 - 4]
   stsw %o2, [%l0 - %lo(datum)]
   stsw %o2, [%l0 - %ulo(datum)]
   stsw %o2, [4]
   stsw %o2, [%lo(datum)]
   stsw %o2, [%ulo(datum)]
   stsw %o2, [-%lo(datum)]
   stsw %o2, [-%ulo(datum)]
_stswa:
   stswa %o2, [%l0] #ASI_PRIMARY
   stswa %o2, [%l0 + %l1] #ASI_PRIMARY
   stswa %o2, [%l0 + 3] %asi
   stswa %o2, [%l0 + %lo(datum)] %asi
   stswa %o2, [%l0 + %ulo(datum)] %asi
   stswa %o2, [3 + %l0] %asi
   stswa %o2, [%lo(datum) + %l0] %asi
   stswa %o2, [%ulo(datum) + %l0] %asi
   stswa %o2, [%l0 - 4] %asi
   stswa %o2, [%l0 - %lo(datum)] %asi
   stswa %o2, [%l0 - %ulo(datum)] %asi
   stswa %o2, [4] %asi
   stswa %o2, [%lo(datum)] %asi
   stswa %o2, [%ulo(datum)] %asi
   stswa %o2, [-%lo(datum)] %asi
   stswa %o2, [-%ulo(datum)] %asi
_stuw:
   stuw %o2, [%l0]
   stuw %o2, [%l0 + %l1]
   stuw %o2, [%l0 + 3]
   stuw %o2, [%l0 + %lo(datum)]
   stuw %o2, [%l0 + %ulo(datum)]
   stuw %o2, [3 + %l0]
   stuw %o2, [%lo(datum) + %l0]
   stuw %o2, [%ulo(datum) + %l0]
   stuw %o2, [%l0 - 4]
   stuw %o2, [%l0 - %lo(datum)]
   stuw %o2, [%l0 - %ulo(datum)]
   stuw %o2, [4]
   stuw %o2, [%lo(datum)]
   stuw %o2, [%ulo(datum)]
   stuw %o2, [-%lo(datum)]
   stuw %o2, [-%ulo(datum)]
_stuwa:
   stuwa %o2, [%l0] #ASI_PRIMARY
   stuwa %o2, [%l0 + %l1] #ASI_PRIMARY
   stuwa %o2, [%l0 + 3] %asi
   stuwa %o2, [%l0 + %lo(datum)] %asi
   stuwa %o2, [%l0 + %ulo(datum)] %asi
   stuwa %o2, [3 + %l0] %asi
   stuwa %o2, [%lo(datum) + %l0] %asi
   stuwa %o2, [%ulo(datum) + %l0] %asi
   stuwa %o2, [%l0 - 4] %asi
   stuwa %o2, [%l0 - %lo(datum)] %asi
   stuwa %o2, [%l0 - %ulo(datum)] %asi
   stuwa %o2, [4] %asi
   stuwa %o2, [%lo(datum)] %asi
   stuwa %o2, [%ulo(datum)] %asi
   stuwa %o2, [-%lo(datum)] %asi
   stuwa %o2, [-%ulo(datum)] %asi
      
   !
   ! 5. conditional traps
   !
   
_ta:
   ta %icc, [%l0]
   ta %icc, [%l0 + %l1]
   ta %icc, [%l0 + 3]
   ta %icc, [3 + %l0]
   ta %icc, [%l0 - 4]
   ta %icc, [4]
   ta %xcc, [%l0]
   ta %xcc, [%l0 + %l1]
   ta %xcc, [%l0 + 3]
   ta %xcc, [3 + %l0]
   ta %xcc, [%l0 - 4]
   ta %xcc, [4]
_tn:
   tn %icc, [%l0]
   tn %icc, [%l0 + %l1]
   tn %icc, [%l0 + 3]
   tn %icc, [3 + %l0]
   tn %icc, [%l0 - 4]
   tn %icc, [4]
   tn %xcc, [%l0]
   tn %xcc, [%l0 + %l1]
   tn %xcc, [%l0 + 3]
   tn %xcc, [3 + %l0]
   tn %xcc, [%l0 - 4]
   tn %xcc, [4]
_tne:
   tne %icc, [%l0]
   tne %icc, [%l0 + %l1]
   tne %icc, [%l0 + 3]
   tne %icc, [3 + %l0]
   tne %icc, [%l0 - 4]
   tne %icc, [4]
   tne %xcc, [%l0]
   tne %xcc, [%l0 + %l1]
   tne %xcc, [%l0 + 3]
   tne %xcc, [3 + %l0]
   tne %xcc, [%l0 - 4]
   tne %xcc, [4]
_te:
   te %icc, [%l0]
   te %icc, [%l0 + %l1]
   te %icc, [%l0 + 3]
   te %icc, [3 + %l0]
   te %icc, [%l0 - 4]
   te %icc, [4]
   te %xcc, [%l0]
   te %xcc, [%l0 + %l1]
   te %xcc, [%l0 + 3]
   te %xcc, [3 + %l0]
   te %xcc, [%l0 - 4]
   te %xcc, [4]
_tg:
   tg %icc, [%l0]
   tg %icc, [%l0 + %l1]
   tg %icc, [%l0 + 3]
   tg %icc, [3 + %l0]
   tg %icc, [%l0 - 4]
   tg %icc, [4]
   tg %xcc, [%l0]
   tg %xcc, [%l0 + %l1]
   tg %xcc, [%l0 + 3]
   tg %xcc, [3 + %l0]
   tg %xcc, [%l0 - 4]
   tg %xcc, [4]
_tle:
   tle %icc, [%l0]
   tle %icc, [%l0 + %l1]
   tle %icc, [%l0 + 3]
   tle %icc, [3 + %l0]
   tle %icc, [%l0 - 4]
   tle %icc, [4]
   tle %xcc, [%l0]
   tle %xcc, [%l0 + %l1]
   tle %xcc, [%l0 + 3]
   tle %xcc, [3 + %l0]
   tle %xcc, [%l0 - 4]
   tle %xcc, [4]
_tge:
   tge %icc, [%l0]
   tge %icc, [%l0 + %l1]
   tge %icc, [%l0 + 3]
   tge %icc, [3 + %l0]
   tge %icc, [%l0 - 4]
   tge %icc, [4]
   tge %xcc, [%l0]
   tge %xcc, [%l0 + %l1]
   tge %xcc, [%l0 + 3]
   tge %xcc, [3 + %l0]
   tge %xcc, [%l0 - 4]
   tge %xcc, [4]
_tl:
   tl %icc, [%l0]
   tl %icc, [%l0 + %l1]
   tl %icc, [%l0 + 3]
   tl %icc, [3 + %l0]
   tl %icc, [%l0 - 4]
   tl %icc, [4]
   tl %xcc, [%l0]
   tl %xcc, [%l0 + %l1]
   tl %xcc, [%l0 + 3]
   tl %xcc, [3 + %l0]
   tl %xcc, [%l0 - 4]
   tl %xcc, [4]
_tgu:
   tgu %icc, [%l0]
   tgu %icc, [%l0 + %l1]
   tgu %icc, [%l0 + 3]
   tgu %icc, [3 + %l0]
   tgu %icc, [%l0 - 4]
   tgu %icc, [4]
   tgu %xcc, [%l0]
   tgu %xcc, [%l0 + %l1]
   tgu %xcc, [%l0 + 3]
   tgu %xcc, [3 + %l0]
   tgu %xcc, [%l0 - 4]
   tgu %xcc, [4]
_tleu:
   tleu %icc, [%l0]
   tleu %icc, [%l0 + %l1]
   tleu %icc, [%l0 + 3]
   tleu %icc, [3 + %l0]
   tleu %icc, [%l0 - 4]
   tleu %icc, [4]
   tleu %xcc, [%l0]
   tleu %xcc, [%l0 + %l1]
   tleu %xcc, [%l0 + 3]
   tleu %xcc, [3 + %l0]
   tleu %xcc, [%l0 - 4]
   tleu %xcc, [4]
_tcc:
   tcc %icc, [%l0]
   tcc %icc, [%l0 + %l1]
   tcc %icc, [%l0 + 3]
   tcc %icc, [3 + %l0]
   tcc %icc, [%l0 - 4]
   tcc %icc, [4]
   tcc %xcc, [%l0]
   tcc %xcc, [%l0 + %l1]
   tcc %xcc, [%l0 + 3]
   tcc %xcc, [3 + %l0]
   tcc %xcc, [%l0 - 4]
   tcc %xcc, [4]
_tcs:
   tcs %icc, [%l0]
   tcs %icc, [%l0 + %l1]
   tcs %icc, [%l0 + 3]
   tcs %icc, [3 + %l0]
   tcs %icc, [%l0 - 4]
   tcs %icc, [4]
   tcs %xcc, [%l0]
   tcs %xcc, [%l0 + %l1]
   tcs %xcc, [%l0 + 3]
   tcs %xcc, [3 + %l0]
   tcs %xcc, [%l0 - 4]
   tcs %xcc, [4]
_tpos:
   tpos %icc, [%l0]
   tpos %icc, [%l0 + %l1]
   tpos %icc, [%l0 + 3]
   tpos %icc, [3 + %l0]
   tpos %icc, [%l0 - 4]
   tpos %icc, [4]
   tpos %xcc, [%l0]
   tpos %xcc, [%l0 + %l1]
   tpos %xcc, [%l0 + 3]
   tpos %xcc, [3 + %l0]
   tpos %xcc, [%l0 - 4]
   tpos %xcc, [4]
_tneg:
   tneg %icc, [%l0]
   tneg %icc, [%l0 + %l1]
   tneg %icc, [%l0 + 3]
   tneg %icc, [3 + %l0]
   tneg %icc, [%l0 - 4]
   tneg %icc, [4]
   tneg %xcc, [%l0]
   tneg %xcc, [%l0 + %l1]
   tneg %xcc, [%l0 + 3]
   tneg %xcc, [3 + %l0]
   tneg %xcc, [%l0 - 4]
   tneg %xcc, [4]
_tvc:
   tvc %icc, [%l0]
   tvc %icc, [%l0 + %l1]
   tvc %icc, [%l0 + 3]
   tvc %icc, [3 + %l0]
   tvc %icc, [%l0 - 4]
   tvc %icc, [4]
   tvc %xcc, [%l0]
   tvc %xcc, [%l0 + %l1]
   tvc %xcc, [%l0 + 3]
   tvc %xcc, [3 + %l0]
   tvc %xcc, [%l0 - 4]
   tvc %xcc, [4]
_tvs:
   tvs %icc, [%l0]
   tvs %icc, [%l0 + %l1]
   tvs %icc, [%l0 + 3]
   tvs %icc, [3 + %l0]
   tvs %icc, [%l0 - 4]
   tvs %icc, [4]
   tvs %xcc, [%l0]
   tvs %xcc, [%l0 + %l1]
   tvs %xcc, [%l0 + 3]
   tvs %xcc, [3 + %l0]
   tvs %xcc, [%l0 - 4]
   tvs %xcc, [4]
_tnz:
   tnz %icc, [%l0]
   tnz %icc, [%l0 + %l1]
   tnz %icc, [%l0 + 3]
   tnz %icc, [3 + %l0]
   tnz %icc, [%l0 - 4]
   tnz %icc, [4]
   tnz %xcc, [%l0]
   tnz %xcc, [%l0 + %l1]
   tnz %xcc, [%l0 + 3]
   tnz %xcc, [3 + %l0]
   tnz %xcc, [%l0 - 4]
   tnz %xcc, [4]
_tz:
   tz %icc, [%l0]
   tz %icc, [%l0 + %l1]
   tz %icc, [%l0 + 3]
   tz %icc, [3 + %l0]
   tz %icc, [%l0 - 4]
   tz %icc, [4]
   tz %xcc, [%l0]
   tz %xcc, [%l0 + %l1]
   tz %xcc, [%l0 + 3]
   tz %xcc, [3 + %l0]
   tz %xcc, [%l0 - 4]
   tz %xcc, [4]
_tgeu:
   tgeu %icc, [%l0]
   tgeu %icc, [%l0 + %l1]
   tgeu %icc, [%l0 + 3]
   tgeu %icc, [3 + %l0]
   tgeu %icc, [%l0 - 4]
   tgeu %icc, [4]
   tgeu %xcc, [%l0]
   tgeu %xcc, [%l0 + %l1]
   tgeu %xcc, [%l0 + 3]
   tgeu %xcc, [3 + %l0]
   tgeu %xcc, [%l0 - 4]
   tgeu %xcc, [4]
_tlu:
   tlu %icc, [%l0]
   tlu %icc, [%l0 + %l1]
   tlu %icc, [%l0 + 3]
   tlu %icc, [3 + %l0]
   tlu %icc, [%l0 - 4]
   tlu %icc, [4]
   tlu %xcc, [%l0]
   tlu %xcc, [%l0 + %l1]
   tlu %xcc, [%l0 + 3]
   tlu %xcc, [3 + %l0]
   tlu %xcc, [%l0 - 4]
   tlu %xcc, [4]

   !
   ! 6. supervisor
   !
_rdpr:
   rdpr %tpc, %o2
   rdpr %tnpc, %o2
   rdpr %tstate, %o2
   rdpr %tt, %o2
   rdpr %tick, %o2
   rdpr %tba, %o2
   rdpr %pstate, %o2
   rdpr %tl, %o2
   rdpr %pil, %o2
   rdpr %cwp, %o2
   rdpr %cansave, %o2
   rdpr %canrestore, %o2
   rdpr %cleanwin, %o2
   rdpr %otherwin, %o2
   rdpr %wstate, %o2
   rdpr %fq, %o2
   rdpr %ver, %o2
_wrpr:
   wrpr %o2, %i2, %tpc
   wrpr %o2, 8, %tpc
   wrpr %o2, %i2, %tnpc
   wrpr %o2, 8, %tnpc
   wrpr %o2, %i2, %tstate
   wrpr %o2, 8, %tstate
   wrpr %o2, %i2, %tt
   wrpr %o2, 8, %tt
   wrpr %o2, %i2, %tick
   wrpr %o2, 8, %tick
   wrpr %o2, %i2, %tba
   wrpr %o2, 8, %tba
   wrpr %o2, %i2, %pstate
   wrpr %o2, 8, %pstate
   wrpr %o2, %i2, %tl
   wrpr %o2, 8, %tl
   wrpr %o2, %i2, %pil
   wrpr %o2, 8, %pil
   wrpr %o2, %i2, %cwp
   wrpr %o2, 8, %cwp
   wrpr %o2, %i2, %cansave
   wrpr %o2, 8, %cansave
   wrpr %o2, %i2, %canrestore
   wrpr %o2, 8, %canrestore
   wrpr %o2, %i2, %cleanwin
   wrpr %o2, 8, %cleanwin
   wrpr %o2, %i2, %otherwin
   wrpr %o2, 8, %otherwin
   wrpr %o2, %i2, %wstate
   wrpr %o2, 8, %wstate
   wrpr %o2, %i2, %fq
   wrpr %o2, 8, %fq
   wrpr %o2, %i2, %ver
   wrpr %o2, 8, %ver
_supervisormisc:
   done
   retry
   flushw
   saved
   restored

   !
   ! 7. floating point arithmetic
   !
   ! exercise the fp register number encoding as follows:
   !    for the s forms, use f4, f6, f7
   !    for the d/q forms, use f4, f40, f56
   !

   ! 3 registers
_fadd:
   fadds f4, f6, f7
   faddd f4, f40, f56
   faddq f4, f40, f56
_fsub:
   fsubs f4, f6, f7
   fsubd f4, f40, f56
   fsubq f4, f40, f56
_fmul:
   fmuls f4, f6, f7
   fmuld f4, f40, f56
   fmulq f4, f40, f56
_fdiv:
   fdivs f4, f6, f7
   fdivd f4, f40, f56
   fdivq f4, f40, f56
_fsmuld:
   fsmuld f4, f6, f8
   fsmuld f5, f7, f8
_fdmulq:
   fdmulq f4, f6, f8

   ! fcc and 2 registers
_fcmp:
   fcmps %fcc1, f4, f7
   fcmps %fcc1, f6, f7
   fcmpd %fcc1, f4, f56
   fcmpq %fcc1, f4, f56
_fcmpe:
   fcmpes %fcc1, f4, f7
   fcmpes %fcc1, f6, f7
   fcmped %fcc1, f4, f56
   fcmpeq %fcc1, f4, f56

   ! 2 registers
_fmov:
   fmovs f4, f7
   fmovs f6, f7
   fmovd f4, f56
   fmovq f4, f56
_fneg:
   fmovs f4, f7
   fnegs f6, f7
   fmovd f4, f56
   fnegq f4, f56
_fabs:
   fmovs f4, f7
   fabss f6, f7
   fmovd f4, f56
   fabsq f4, f56
_fsqrt:
   fmovs f4, f7
   fsqrts f6, f7
   fmovd f4, f56
   fsqrtq f4, f56

   ! f*to*
_ftox:
   fstox f4, f8
   fstox f5, f40
   fstox f7, f56
   fdtox f4, f8
   fdtox f40, f56
   fqtox f4, f8
   fqtox f40, f56
_ftoi:
   fstoi f4, f8
   fstoi f5, f9
   fstoi f7, f11
   fdtoi f4, f8
   fdtoi f40, f9
   fdtoi f40, f11
   fqtoi f4, f8
   fqtoi f40, f9
   fqtoi f40, f11
_fxto:
   fxtos f8, f4
   fxtos f40, f5
   fxtos f56, f7
   fxtod f8, f4
   fxtod f56, f40
   fxtoq f8, f4
   fxtoq f56, f40
_fito:
   fitos f8, f4
   fitos f9, f5
   fitos f11, f7
   fitod f8, f4
   fitod f9, f40
   fitod f11, f40
   fitoq f8, f4
   fitoq f9, f40
   fitoq f11, f40
_fto:
   fstod f4, f8
   fstod f5, f40
   fstod f7, f40
   fstoq f4, f8
   fstoq f5, f40
   fstoq f7, f40
   fdtos f4, f8
   fdtos f40, f9
   fdtos f40, f11
   fqtos f4, f8
   fqtos f40, f9
   fqtos f40, f11
   fdtoq f4, f8
   fdtoq f40, f56
   fqtod f4, f8
   fqtod f40, f56

   !
   ! 8. misc
   !
_membar:
   membar #Sync
   membar #MemIssue
   membar #Lookaside
   membar #StoreStore
   membar #LoadStore
   membar #StoreLoad
   membar #LoadLoad
   membar #LoadLoad|#StoreStore
   membar #LoadStore|#StoreStore
   membar #StoreLoad|#StoreStore
   membar #LoadLoad|#StoreStore|#Sync
   membar #LoadStore|#StoreStore|#MemIssue
   membar #StoreLoad|#StoreStore|#Lookaside
_stbar:
   stbar
_call:
   call subr
_jmpl:
   jmpl %l0, %o7
   jmpl %l0 + %l1, %o7
   jmpl %l0 + 3, %o7
   jmpl %l0 + %lo(datum), %o7
   jmpl %l0 + %ulo(datum), %o7
   jmpl 3 + %l0, %o7
   jmpl %lo(datum) + %l0, %o7
   jmpl %ulo(datum) + %l0, %o7
   jmpl %l0 - 4, %o7
   jmpl %l0 - %lo(datum), %o7
   jmpl 4, %o7
   jmpl -4, %o7
   jmpl %lo(datum), %o7
   jmpl %ulo(datum), %o7
   jmpl -%lo(datum), %o7
   jmpl -%ulo(datum), %o7
_jmp:
   jmp %l0
   jmp %l0 + %l1
   jmp %l0 + 3
   jmp %l0 + %lo(datum)
   jmp %l0 + %ulo(datum)
   jmp 3 + %l0
   jmp %lo(datum) + %l0
   jmp %ulo(datum) + %l0
   jmp %l0 - 4
   jmp %l0 - %lo(datum)
   jmp %l0 - %ulo(datum)
   jmp 4
   jmp -4
   jmp %lo(datum)
   jmp %ulo(datum)
   jmp -%lo(datum)
   jmp -%ulo(datum)
_call:
   call %l0
   call %l0 + %l1
   call %l0 + 3
   call %l0 + %lo(datum)
   call %l0 + %ulo(datum)
   call 3 + %l0
   call %lo(datum) + %l0
   call %ulo(datum) + %l0
   call %l0 - 4
   call %l0 - %lo(datum)
   call %l0 - %ulo(datum)
   call 4
   call -4
   call %lo(datum)
   call %ulo(datum)
   call -%lo(datum)
   call -%ulo(datum)
_return:
   return %l0
   return %l0 + %l1
   return %l0 + 3
   return %l0 + %lo(datum)
   return %l0 + %ulo(datum)
   return 3 + %l0
   return %lo(datum) + %l0
   return %ulo(datum) + %l0
   return %l0 - 4
   return %l0 - %lo(datum)
   return %l0 - %ulo(datum)
   return 4
   return -4
   return %lo(datum)
   return %ulo(datum)
   return -%lo(datum)
   return -%ulo(datum)
_ret:
   ret
   retl
_illtrap:	
   illtrap 0xfeeb1e
_sir:
   sir 72
   sir -9
_rd:
   rd %y, %o3
   rd %ccr, %o3
   rd %asi, %o3
   rd %tick, %o3
   rd %pc, %o3
   rd %fprs, %o3
   rd %asr7, %o3
   rd %asr8, %o3
   rd %asr9, %o3
   rd %asr10, %o3
   rd %asr11, %o3
   rd %asr12, %o3
   rd %asr13, %o3
   rd %asr14, %o3
   rd %asr16, %o3
   rd %asr17, %o3
   rd %asr18, %o3
   rd %asr19, %o3
   rd %asr20, %o3
   rd %asr21, %o3
   rd %asr22, %o3
   rd %asr23, %o3
   rd %asr24, %o3
   rd %asr25, %o3
   rd %asr26, %o3
   rd %asr27, %o3
   rd %asr28, %o3
   rd %asr29, %o3
   rd %asr30, %o3
   rd %asr31, %o3
_wr:
   wr %o3, %i2, %y
   wr %o3, 6, %y
   wr %o3, %i2, %ccr
   wr %o3, 6, %ccr
   wr %o3, %i2, %asi
   wr %o3, 6, %asi
   wr %o3, %i2, %tick
   wr %o3, 6, %tick
   wr %o3, %i2, %pc
   wr %o3, 6, %pc
   wr %o3, %i2, %fprs
   wr %o3, 6, %fprs
   wr %o3, %i2, %asr7
   wr %o3, 6, %asr7
   wr %o3, %i2, %asr8
   wr %o3, 6, %asr8
   wr %o3, %i2, %asr9
   wr %o3, 6, %asr9
   wr %o3, %i2, %asr10
   wr %o3, 6, %asr10
   wr %o3, %i2, %asr11
   wr %o3, 6, %asr11
   wr %o3, %i2, %asr12
   wr %o3, 6, %asr12
   wr %o3, %i2, %asr13
   wr %o3, 6, %asr13
   wr %o3, %i2, %asr14
   wr %o3, 6, %asr14
   wr %o3, %i2, %asr16
   wr %o3, 6, %asr16
   wr %o3, %i2, %asr17
   wr %o3, 6, %asr17
   wr %o3, %i2, %asr18
   wr %o3, 6, %asr18
   wr %o3, %i2, %asr19
   wr %o3, 6, %asr19
   wr %o3, %i2, %asr20
   wr %o3, 6, %asr20
   wr %o3, %i2, %asr21
   wr %o3, 6, %asr21
   wr %o3, %i2, %asr22
   wr %o3, 6, %asr22
   wr %o3, %i2, %asr23
   wr %o3, 6, %asr23
   wr %o3, %i2, %asr24
   wr %o3, 6, %asr24
   wr %o3, %i2, %asr25
   wr %o3, 6, %asr25
   wr %o3, %i2, %asr26
   wr %o3, 6, %asr26
   wr %o3, %i2, %asr27
   wr %o3, 6, %asr27
   wr %o3, %i2, %asr28
   wr %o3, 6, %asr28
   wr %o3, %i2, %asr29
   wr %o3, 6, %asr29
   wr %o3, %i2, %asr30
   wr %o3, 6, %asr30
   wr %o3, %i2, %asr31
   wr %o3, 6, %asr31
_movasr:
   mov %y, %o3
   mov %o3, %y
   mov %ccr, %o3
   mov %o3, %ccr
   mov %asi, %o3
   mov %o3, %asi
   mov %tick, %o3
   mov %o3, %tick
   mov %pc, %o3
   mov %o3, %pc
   mov %fprs, %o3
   mov %o3, %fprs
   mov %asr7, %o3
   mov %o3, %asr7
   mov %asr8, %o3
   mov %o3, %asr8
   mov %asr9, %o3
   mov %o3, %asr9
   mov %asr10, %o3
   mov %o3, %asr10
   mov %asr11, %o3
   mov %o3, %asr11
   mov %asr12, %o3
   mov %o3, %asr12
   mov %asr13, %o3
   mov %o3, %asr13
   mov %asr14, %o3
   mov %o3, %asr14
   mov %asr16, %o3
   mov %o3, %asr16
   mov %asr17, %o3
   mov %o3, %asr17
   mov %asr18, %o3
   mov %o3, %asr18
   mov %asr19, %o3
   mov %o3, %asr19
   mov %asr20, %o3
   mov %o3, %asr20
   mov %asr21, %o3
   mov %o3, %asr21
   mov %asr22, %o3
   mov %o3, %asr22
   mov %asr23, %o3
   mov %o3, %asr23
   mov %asr24, %o3
   mov %o3, %asr24
   mov %asr25, %o3
   mov %o3, %asr25
   mov %asr26, %o3
   mov %o3, %asr26
   mov %asr27, %o3
   mov %o3, %asr27
   mov %asr28, %o3
   mov %o3, %asr28
   mov %asr29, %o3
   mov %o3, %asr29
   mov %asr30, %o3
   mov %o3, %asr30
   mov %asr31, %o3
   mov %o3, %asr31
_impl1:
   impl1 6, 0x1eeef
_impl2:
   impl2 6, 0x1eeef

   !
   ! 9. misc macros
   !

_nop:
   nop
_cmp:
   cmp %i0, %i1
   cmp %i0, 3
   cmp %i0, -5
   cmp %i0, %lo(datum)
   cmp %i0, %ulo(datum)
_save:
   save
   restore
_iprefetch:
   iprefetch subr
_tst:
   tst %o2
_signx:
   signx %o2, %o3
   signx %o2
_not:
   not %o2, %o3
   not %o2
_neg:
   neg %o2, %o3
   neg %o2
_sethi:
   sethi 0xbeef0, %o0
   sethi %hi(datum), %o0
   sethi %uhi(datum), %o0
_set:
   setuw 0xfadecade, %o0
   setuw 0xfadec000, %o0
   setuw 0xade, %o0
   setsw 0xfadecade, %o0
   setsw 0xfadec000, %o0
   setsw 0xade, %o0
   set 0xfadecade, %o0
   set 0xfadec000, %o0
   set 0xade, %o0
_setx:
   setx 0xfadecadebadeaade, %l0, %o0
   setx 0xfadecadebadea000, %l0, %o0
   setx 0xfadecade00000ade, %l0, %o0
   setx 0xfadec000badeaade, %l0, %o0
   setx 0x00000adebadeaade, %l0, %o0
   setx 0xfadecade00000000, %l0, %o0
   setx 0xfadec000badea000, %l0, %o0
   setx 0x00000adebadea000, %l0, %o0
   setx 0xfadec00000000ade, %l0, %o0
   setx 0x00000ade00000ade, %l0, %o0
   setx 0x00000000badeaade, %l0, %o0
   setx 0x0000000000000ade, %l0, %o0
   setx 0x00000000badea000, %l0, %o0
   setx 0x00000ade00000000, %l0, %o0
   setx 0xfadec00000000000, %l0, %o0
   setx 0xfadecade00000000, %l0, %o0
   setx 0xfadec00000000000, %l0, %o0
   setx 0x0000000000000000, %l0, %o0
_inc:
   inc %o0
   inc 6, %o0
   inc -8, %o0
   inc %lo(datum), %o0
   inc %ulo(datum), %o0
   inc -%lo(datum), %o0
   inc -%ulo(datum), %o0
_inccc:
   inccc %o0
   inccc 6, %o0
   inccc -8, %o0
   inccc %lo(datum), %o0
   inccc %ulo(datum), %o0
   inccc -%lo(datum), %o0
   inccc -%ulo(datum), %o0
_dec:
   dec %o0
   dec 6, %o0
   dec -8, %o0
   dec %lo(datum), %o0
   dec %ulo(datum), %o0
   dec -%lo(datum), %o0
   dec -%ulo(datum), %o0
_deccc:
   deccc %o0
   deccc 6, %o0
   deccc -8, %o0
   deccc %lo(datum), %o0
   deccc %ulo(datum), %o0
   deccc -%lo(datum), %o0
   deccc -%ulo(datum), %o0

_btst:
   btst %o0, %i0
   btst 6, %i0
   btst -8, %i0
   btst %lo(datum), %i0
   btst %ulo(datum), %i0
   btst -%lo(datum), %i0
   btst -%ulo(datum), %i0
_bset:
   bset %o0, %i0
   bset 6, %i0
   bset -8, %i0
   bset %lo(datum), %i0
   bset %ulo(datum), %i0
   bset -%lo(datum), %i0
   bset -%ulo(datum), %i0
_bclr:
   bclr %o0, %i0
   bclr 6, %i0
   bclr -8, %i0
   bclr %lo(datum), %i0
   bclr %ulo(datum), %i0
   bclr -%lo(datum), %i0
   bclr -%ulo(datum), %i0
_btog:
   btog %o0, %i0
   btog 6, %i0
   btog -8, %i0
   btog %lo(datum), %i0
   btog %ulo(datum), %i0
   btog -%lo(datum), %i0
   btog -%ulo(datum), %i0
_clr_:
   clr %o0
   clruw %o0, %o1
   clruw %o0
_clrb:
   clrb [%l0]
   clrb [%l0 + %l1]
   clrb [%l0 + 3]
   clrb [%l0 + %lo(datum)]
   clrb [%l0 + %ulo(datum)]
   clrb [3 + %l0]
   clrb [%lo(datum) + %l0]
   clrb [%ulo(datum) + %l0]
   clrb [%l0 - 4]
   clrb [%l0 - %lo(datum)]
   clrb [%l0 - %ulo(datum)]
   clrb [4]
   clrb [%lo(datum)]
   clrb [%ulo(datum)]
   clrb [-%lo(datum)]
   clrb [-%ulo(datum)]
_clrh:
   clrh [%l0]
   clrh [%l0 + %l1]
   clrh [%l0 + 3]
   clrh [%l0 + %lo(datum)]
   clrh [%l0 + %ulo(datum)]
   clrh [3 + %l0]
   clrh [%lo(datum) + %l0]
   clrh [%ulo(datum) + %l0]
   clrh [%l0 - 4]
   clrh [%l0 - %lo(datum)]
   clrh [%l0 - %ulo(datum)]
   clrh [4]
   clrh [%lo(datum)]
   clrh [%ulo(datum)]
   clrh [-%lo(datum)]
   clrh [-%ulo(datum)]
_clr:
   clr [%l0]
   clr [%l0 + %l1]
   clr [%l0 + 3]
   clr [%l0 + %lo(datum)]
   clr [%l0 + %ulo(datum)]
   clr [3 + %l0]
   clr [%lo(datum) + %l0]
   clr [%ulo(datum) + %l0]
   clr [%l0 - 4]
   clr [%l0 - %lo(datum)]
   clr [%l0 - %ulo(datum)]
   clr [4]
   clr [%lo(datum)]
   clr [%ulo(datum)]
   clr [-%lo(datum)]
   clr [-%ulo(datum)]
_clrx:
   clrx [%l0]
   clrx [%l0 + %l1]
   clrx [%l0 + 3]
   clrx [%l0 + %lo(datum)]
   clrx [%l0 + %ulo(datum)]
   clrx [3 + %l0]
   clrx [%lo(datum) + %l0]
   clrx [%ulo(datum) + %l0]
   clrx [%l0 - 4]
   clrx [%l0 - %lo(datum)]
   clrx [%l0 - %ulo(datum)]
   clrx [4]
   clrx [%lo(datum)]
   clrx [%ulo(datum)]
   clrx [-%lo(datum)]
   clrx [-%ulo(datum)]
_mov:
   mov %o0, %i0
   mov 6, %o0
   mov -8, %o0
   mov %lo(datum), %o0
   mov %ulo(datum), %o0
   mov -%lo(datum), %o0
   mov -%ulo(datum), %o0

subr:
   jr $ra

   .data
datum:
   .word 0x01234567
