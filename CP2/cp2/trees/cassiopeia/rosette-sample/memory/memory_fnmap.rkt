#lang rosette

(require rosette/lib/synthax rosette/solver/smt/boolector)

(current-bitwidth 8) ; shorter bitwidth
(current-solver (boolector))

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

(define (empty-mem addr) zero)
(define MEM
  (box empty-mem))

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
  (define loc (unbox Raddr))
  (assert (bvuge loc zero))
  (assert (bvult loc (bv 8 bitwidth)))
  (define val (unbox Rval))
  (define prev-mem (unbox MEM))
  (define (next-mem addr)
    (assert (bvuge addr zero))
    (assert (bvult addr (bv 8 bitwidth))) ; 8-slot memory
    (if (bveq loc addr)
        val
        (prev-mem addr)))
  (set-box! MEM next-mem))

(define (LD Rd Raddr)
  (set-box! Rd ((unbox MEM) (unbox Raddr))))

(define-synthax reg*
  ([(_) (choose
         R1
         R2
         R3
         SP)]))
; 1 reg: <1 second
; 2 reg: ~1 minute
; 3 reg:

(define-synthax imm*
  ([(_) (?? (bitvector bitwidth))]))

(define-synthax (inst* num)
  #:base '()
  #:else
  (begin
    (define Ra (reg*))
    (define Rb (reg*))
    (define Rc (reg*))
    (define imm (imm*))
    (choose (MOV-reg Ra Rb)
            (MOV-imm Ra imm)
            (ADD-reg Ra Rb Rc)
            (ADD-imm Ra Rb imm)
            (ST Ra Rb)
            (LD Ra Rb)
            '()) ; nop
    (inst* (- num 1))))

(define (save-ctx) (inst* 6))
(define (load-ctx) (inst* 6))

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
(define sp-next (bits*))

(define (correct pre-r1 pre-r2 pre-r3 pre-sp)
  (begin
     (save-ctx)
     (MOV-imm R1 r1-next) ; make zero
     (MOV-imm R2 r2-next)
     (MOV-imm R3 r3-next)
     (MOV-imm SP sp-next)
     (load-ctx)
     (assert (bveq (unbox R1) pre-r1))
     (assert (bveq (unbox R2) pre-r2))
     (assert (bveq (unbox R3) pre-r3))))

;(define model
;  (verify (correct r1-init r2-init r3-init sp-init)))


(define model
  (time (synthesize
   #:forall (list r1-init r2-init r3-init sp-init r1-next r2-next r3-next sp-next)
   #:guarantee (correct r1-init r2-init r3-init sp-init))))
