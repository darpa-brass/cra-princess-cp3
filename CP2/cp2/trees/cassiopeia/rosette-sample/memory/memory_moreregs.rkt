#lang rosette

(require rosette/lib/synthax)

(current-bitwidth #f) ; shorter bitwidth

(define bitwidth 8)

(define (bits*)
  (define-symbolic* b (bitvector bitwidth))
  b)

(define zero
  (bv 0 bitwidth))

(define r1-init (bits*))
(define r2-init (bits*))
(define r3-init (bits*))
(define r4-init (bits*))
(define r5-init (bits*))
(define r6-init (bits*))
(define sp-init (bits*))

(define R1 (box r1-init)) ; fewer regs
(define R2 (box r2-init))
(define R3 (box r3-init))
(define R4 (box r4-init))
(define R5 (box r5-init))
(define R6 (box r6-init))
(define S1 (box zero))
(define S2 (box zero))
(define S3 (box zero))
(define S4 (box zero))
(define S5 (box zero))
(define S6 (box zero))
(define S7 (box zero))
(define S8 (box zero))
(define SP (box sp-init))

(define MEM (make-vector 8 zero)) ; shorter vector

(define (MOV-reg Rd Rn)
  (set-box! Rd (unbox Rn)))

(define (MOV-imm Rd Imm)
  (assert ((bitvector bitwidth) Imm))
  (set-box! Rd Imm))

(define (ADD-reg Rd Rn Rm)
  (set-box! Rd (bvadd (unbox Rn) (unbox Rm))))

(define (ADD-imm Rd Rn Imm)
  (set-box! Rd (bvadd (unbox Rn) Imm)))

(define-synthax reg*
  ([(_) (choose
         R1
         R2
         R3
         R4
         ;R5
         ;R6
         S1 S2 S3 S4 S5 S6 S7 S8
         SP)]))

(define-synthax imm*
  ([(_) (?? (bitvector bitwidth))]))

(define-synthax (inst* num)
  #:base '()
  #:else
  (begin
    (choose (MOV-reg (reg*) (reg*))
            (MOV-imm (reg*) (imm*))
            (ADD-reg (reg*) (reg*) (reg*))
            (ADD-imm (reg*) (reg*) (imm*))
            '()) ; nop
    (inst* (- num 1))))

(define (save-ctx) (inst* 4))
(define (load-ctx) (inst* 4))

#|
(define (save-ctx)
  (MOV-imm SP (bv 0 bitwidth))
  (ST SP R1)
  (ADD-imm SP SP (bv 1 bitwidth))
  (ST SP R2)
  (ADD-imm SP SP (bv 1 bitwidth))
  (ST SP R3))

(define (load-ctx)
  (MOV-imm SP (bv 0 bitwidth))
  (LD R1 SP)
  (ADD-imm SP SP (bv 1 bitwidth))
  (LD R2 SP)
  (ADD-imm SP SP (bv 1 bitwidth))
  (LD R3 SP))
|#

(define r1-next (bits*))
(define r2-next (bits*))
(define r3-next (bits*))
(define r4-next (bits*))
(define r5-next (bits*))
(define r6-next (bits*))
(define sp-next (bits*))

(define (correct pre-r1 pre-r2 pre-r3 pre-r4 pre-r5 pre-r6 pre-sp)
  (begin
     (save-ctx)
     (MOV-imm R1 r1-next) ; make zero
     (MOV-imm R2 r2-next)
     (MOV-imm R3 r3-next)
     (MOV-imm R4 r4-next)
     ;(MOV-imm R5 r5-next)
     ;(MOV-imm R6 r6-next)
     (MOV-imm SP sp-next)
     (load-ctx)
     (assert (bveq (unbox R1) pre-r1))
     (assert (bveq (unbox R2) pre-r2))
     (assert (bveq (unbox R3) pre-r3))
     (assert (bveq (unbox R4) pre-r4))
     (assert (bveq (unbox R5) pre-r5))
     (assert (bveq (unbox R6) pre-r6))))

;(define model
;  (verify (correct r1-init r2-init r3-init sp-init)))

(define model
  (synthesize
   #:forall (list r1-init r2-init r3-init r4-init r5-init r6-init sp-init
                  r1-next r2-next r3-next r4-next r5-next r6-next sp-next)
   #:guarantee (correct r1-init r2-init r3-init r4-init r5-init r6-init sp-init)))
