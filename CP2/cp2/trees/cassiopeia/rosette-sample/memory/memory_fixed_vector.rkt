#lang rosette

(require rosette/lib/synthax)

(current-bitwidth 8) ; shorter bitwidth

(define bitwidth 8)

(define (bits*)
  (define-symbolic* b (bitvector bitwidth))
  b)

(define zero
  (bv 0 bitwidth))

(define r1-init (bits*))
(define r2-init (bits*))
(define r3-init (bits*))
(define sp-init (bits*))

(define R1 (box r1-init)) ; fewer regs
(define R2 (box r2-init))
(define R3 (box r3-init))
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

(define (ST Raddr Rval)
  (vector-set! MEM (bitvector->integer (unbox Raddr)) (unbox Rval)))

(define (LD Rd Raddr)
  (set-box! Rd (vector-ref MEM (bitvector->integer (unbox Raddr)))))

(define-synthax reg*
  ([(_) (choose
         R1
         R2
         R3
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
            (ST (reg*) (reg*))
            (LD (reg*) (reg*))
            '()) ; nop
    (inst* (- num 1))))

(define (save-ctx) (inst* 6))
(define (load-ctx) (inst* 6))

#|
(define (save-ctx)
  (MOV-imm SP (bv 3 bitwidth))
  (ST SP R1)
  (ADD-imm SP SP (bv 1 bitwidth))
  (ST SP R2)
  (ADD-imm SP SP (bv 1 bitwidth))
  (ST SP R3))

(define (load-ctx)
  (MOV-imm SP (bv 3 bitwidth))
  (LD R1 SP)
  (ADD-imm SP SP (bv 1 bitwidth))
  (LD R2 SP)
  (ADD-imm SP SP (bv 1 bitwidth))
  (LD R3 SP))
|#

(define r1-next (bits*))
(define r2-next (bits*))
(define r3-next (bits*))
(define sp-next (bits*))

(define (correct-save pre-r1 pre-r2 pre-r3 pre-sp)
  (begin
    (save-ctx)
    (assert (bveq (vector-ref MEM 3) pre-r1))
    (assert (bveq (vector-ref MEM 4) pre-r2))
    (assert (bveq (vector-ref MEM 5) pre-r3))))

(define (correct-load pre-r1 pre-r2 pre-r3 pre-sp)
  (begin
    (MOV-imm R1 r1-next) ; make zero
    (MOV-imm R2 r2-next)
    (MOV-imm R3 r3-next)
    (MOV-imm SP sp-next)
    (load-ctx)
    (assert (bveq (unbox R1) pre-r1))
    (assert (bveq (unbox R2) pre-r2))
    (assert (bveq (unbox R3) pre-r3))))

(writeln (current-inexact-milliseconds))

(define model-save
  (synthesize
   #:forall (list r1-init r2-init r3-init sp-init r1-next r2-next r3-next sp-next)
   #:guarantee (correct-save r1-init r2-init r3-init sp-init)))

(writeln (current-inexact-milliseconds))

(define model-load
  (synthesize
   #:forall (list r1-init r2-init r3-init sp-init r1-next r2-next r3-next sp-next)
   #:guarantee (correct-load r1-init r2-init r3-init sp-init)))

(writeln (current-inexact-milliseconds))

;(define model
;  (verify (correct r1-init r2-init r3-init sp-init)))
