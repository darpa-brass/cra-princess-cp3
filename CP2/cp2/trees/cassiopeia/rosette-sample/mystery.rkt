#lang rosette

(require rosette/lib/synthax)

(provide (all-defined-out))

; register definitions
(define (regval32*)
  (define-symbolic* x (bitvector 32))
  x)

(define r0_init (bv 0 32))
(define r1_init (bv 1 32))

(define R0 (box r0_init))
(define R1 (box r1_init))
; unbox: return the content of box.
; set-box!: change the content of box

; function definitions
(define (arm32_wordtoint bv) (bitvector->natural bv))
(define (arm32_inttoword i) (bv i 32))

; instruction descriptions
(define (ADD_imm Rd Rn Imm) 
  (set-box! Rd
            (integer->bitvector (+ (arm32_wordtoint (unbox Rn))
                                   (bitvector->natural Imm))
                                (bitvector 32))))

(define (ADD_reg Rd Rn Rm)
  (set-box! Rd
            (integer->bitvector (+ (arm32_wordtoint (unbox Rn))
                                   (arm32_wordtoint (unbox Rm)))
                                (bitvector 32))))

; generate the instruction list
; num indicates the number of the instruction list is (num + 1) 
(define-synthax (inst num)
  #:base (choose
          (ADD_imm (choose R0 R1) (choose R0 R1) (?? (bitvector 12)))
          (ADD_reg (choose R0 R1) (choose R0 R1) (choose R0 R1)))
  #:else (begin
           (choose
            (ADD_imm (choose R0 R1) (choose R0 R1) (?? (bitvector 12)))
            (ADD_reg (choose R0 R1) (choose R0 R1) (choose R0 R1)))
           (inst (- num 1))))

(inst 2)
;(assert (bveq (unbox R0) (bv 3 32)))
;(assert (bveq (unbox R0) (unbox R1))) ; crystal: see results before+after uncommenting this line
;(asserts)
(define asdf (unbox R0))
(define ghjk (unbox R1))

(define model
  (synthesize
   #:forall '()
   #:guarantee (begin
                 (assert (bveq (unbox R0) (bv 3 32)))
                 (assert (bveq (unbox R0) (unbox R1))))))
;(print-forms model)
(evaluate (unbox R0) model)
(evaluate (unbox R1) model)
(evaluate asdf model)
(evaluate ghjk model)

(define model2
  (synthesize
   #:forall '()
   #:guarantee (begin
                 (assert (and (bveq (unbox R0) (bv 3 32))
                              (bveq (unbox R0) (unbox R1)))))))
(evaluate (unbox R0) model2)
(evaluate (unbox R1) model2)
(evaluate asdf model2)
(evaluate ghjk model2)

; synthesis part
#|
(define model
  (synthesize
   #:forall '()
   #:guarantee (begin
                 (inst 4)
                 (assert (bveq (unbox R0) (bv 3 32)))
                 (assert (bveq (unbox R0) (unbox R1))))))

(print-forms model)

(set! r0_init (bv 0 32))
(set! r1_init (bv 1 32))

(set-box! R0 r0_init)
(set-box! R1 r1_init)
(begin
  (ADD_imm R1 R1 (bv #x01c 12))
  (begin
    (ADD_imm R0 R1 (bv #x006 12))
    (begin
      (ADD_imm R1 R1 (bv #x007 12))
      (begin (ADD_reg R1 R0 R1) (ADD_imm R1 R1 (bv #x01c 12))))))
(assert (bveq (unbox R0) (bv 3 32)))
(assert (bveq (unbox R0) (unbox R1)))
; get the model result: (print-forms model)
; get the content of the registers: (evaluate (unbox R0) model)
|#

#|
(define (reg32*)
  (define-symbolic* reg_idx integer?)
  (if (eq? reg_idx 0) R0 R1))

(define (inst_idx*)
  (define-symbolic* inst_idx integer?)
  inst_idx)

(define (imm12*)
  (define-symbolic* imm_val (bitvector 12))
  imm_val)

(define (inst* num)
  (if (eq? (inst_idx*) 0)
  ;(choose
      (ADD_imm (reg32*) (reg32*) (imm12*))
      (ADD_reg (reg32*) (reg32*) (reg32*))))

(define (my-build-list num)
  (define (aux i)
    (if (eq? i num) empty (append (list i) (aux (add1 i)))))
  (aux 0))
     
(define (prog* num)
  (map inst* (my-build-list num)))
  
; synthesis part
(define model
 (synthesize
  #:forall (list r0_init r1_init)
  #:guarantee (begin
                (prog* 2)
                (assert (eq? (unbox R0) (bv 3 32)))
                (assert (eq? (unbox R0) (unbox R1))))))
model
|#