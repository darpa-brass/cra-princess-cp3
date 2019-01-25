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
(define sp-init (bits*))

(define R1 (box r1-init)) ; fewer regs
(define R2 (box r2-init))
(define R3 (box r3-init))
(define SP (box sp-init))

(define (empty-mem*)
  (define-symbolic* f (~> (bitvector bitwidth) (bitvector bitwidth)))
  (define b (bits*))
  (assert (forall [list b] (eq? (f b) zero)))
  f)

(define (get-mem mem addr)
  (mem addr))

(define (set-mem mem val addr)
  (define-symbolic* g (~> (bitvector bitwidth) (bitvector bitwidth)))
  (define b (bits*))
  (assert (forall [list b] (or (and (eq? b addr)
                             (eq? (g b) val))
                        (and (not (eq? b addr))
                             (eq? (mem b) (g b))))))
  g)

(define MEM
  (box (empty-mem*)))

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
  (assert (bvuge (unbox Raddr) zero))
  (assert (bvult (unbox Raddr) (bv 8 bitwidth)))
  (set-box! MEM (set-mem (unbox MEM) (unbox Rval) (unbox Raddr))))

(define (LD Rd Raddr)
  (assert (bvuge (unbox Raddr) zero))
  (assert (bvult (unbox Raddr) (bv 8 bitwidth)))
  (set-box! Rd (get-mem (unbox MEM) (unbox Raddr))))

(define-synthax reg*
  ([(_) (choose
         R1
         ;R2
         ;R3
         SP)]))
; 1 reg:
; 2 reg:
; 3 reg:

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

(define (save-ctx) (inst* 2))
(define (load-ctx) (inst* 2))

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
     ;(MOV-imm R2 r2-next)
     ;(MOV-imm R3 r3-next)
     (MOV-imm SP sp-next)
     (load-ctx)
     (assert (bveq (unbox R1) pre-r1))
     (assert (bveq (unbox R2) pre-r2))
     (assert (bveq (unbox R3) pre-r3))))

(define model
  (verify (correct r1-init r2-init r3-init sp-init)))

#|
(define model
  (synthesize
   #:forall (list r1-init r2-init r3-init sp-init r1-next r2-next r3-next sp-next)
   #:guarantee (correct r1-init r2-init r3-init sp-init)))
|#