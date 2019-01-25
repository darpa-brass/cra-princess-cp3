#lang rosette
(require rosette/lib/synthax)
(provide (all-defined-out))

; register definitions
(define (regval32*) (define-symbolic* x (bitvector 32)) x)

(define r0_init (bv 0 32))
(define r1_init (bv 1 32))
(define r2_init (bv 0 32))
(define cpsr_init (bv 0 32))

(define R0 (box r0_init))
(define R1 (box r1_init))
(define R2 (box r2_init))
(define CPSR (box cpsr_init))

; unbox: return the content of box.
; set-box!: change the content of box

; function definitions
(define (arm32_wordtoint bv) (bitvector->natural bv))
(define (arm32_inttoword i) (bv i 32))

; conditional execution functions
(define (arm32_checkcond_eq op)
  (if (bveq op (bv #b0000 4))
      (if (bveq
           (extract 30 30 (unbox CPSR)) (bv 1 1))
          #t #f)
      #t))

(define (arm32_checkcond_ne op)
  (if (bveq op (bv #b0001 4))
      (if (bveq
           (extract 30 30 (unbox CPSR)) (bv 0 1))
          #t #f)
      #t))

(define (arm32_checkcond_hs op)
  (if (bveq op (bv #b0010 4))
      (if (bveq
           (extract 29 29 (unbox CPSR)) (bv 1 1))
          #t #f)
      #t))

(define (arm32_checkcond_lo op)
  (if (bveq op (bv #b0011 4))
      (if (bveq
           (extract 29 29 (unbox CPSR)) (bv 0 1))
          #t #f)
      #t))

(define (arm32_checkcond_mi op)
  (if (bveq op (bv #b0100 4))
      (if (bveq
           (extract 31 31 (unbox CPSR)) (bv 1 1))
          #t #f)
      #t))

(define (arm32_checkcond_pl op)
  (if (bveq op (bv #b0101 4))
      (if (bveq
           (extract 31 31 (unbox CPSR)) (bv 0 1))
          #t #f)
      #t))

(define (arm32_checkcond_vs op)
  (if (bveq op (bv #b0110 4))
      (if (bveq
           (extract 28 28 (unbox CPSR)) (bv 1 1))
          #t #f)
      #t))

(define (arm32_checkcond_vc op)
  (if (bveq op (bv #b0111 4))
      (if (bveq
           (extract 28 28 (unbox CPSR)) (bv 0 1))
          #t #f)
      #t))

(define (arm32_checkcond_hi op)
  (if (bveq op (bv #b1000 4))
      (if (and (bveq
                (extract 30 30 (unbox CPSR)) (bv 0 1))
               (bveq
                (extract 29 29 (unbox CPSR)) (bv 1 1)))
          #t #f)
      #t))

(define (arm32_checkcond_ls op)
  (if (bveq op (bv #b1001 4))
      (if (and (bveq
                (extract 30 30 (unbox CPSR)) (bv 1 1))
               (bveq
                (extract 29 29 (unbox CPSR)) (bv 0 1)))
          #t #f)
      #t))

(define (arm32_checkcond_ge op)
  (if (bveq op (bv #b1010 4))
      (if (bveq
           (extract 31 31 (unbox CPSR)) (extract 28 28 (unbox CPSR)))
          #t #f)
      #t))

(define (arm32_checkcond_lt op)
  (if (bveq op (bv #b1011 4))
      (if (not (bveq
                (extract 31 31 (unbox CPSR)) (extract 28 28 (unbox CPSR))))
          #t #f)
      #t))

(define (arm32_checkcond_gt op)
  (if (bveq op (bv #b1100 4))
      (if (and (bveq
                (extract 31 31 (unbox CPSR)) (extract 28 28 (unbox CPSR)))
               (bveq (extract 30 30 (unbox CPSR)) (bv 0 1)))
          #t #f)
      #t))

(define (arm32_checkcond_le op)
  (if (bveq op (bv #b1101 4))
      (if (or (not (bveq
                    (extract 31 31 (unbox CPSR)) (extract 28 28 (unbox CPSR))))
              (bveq (extract 30 30 (unbox CPSR)) (bv 1 1)))
          #t #f)
      #t))
  
(define (arm32_checkcond op)
  (and (arm32_checkcond_eq op) (arm32_checkcond_ne op)
       (arm32_checkcond_ne op) (arm32_checkcond_hs op)
       (arm32_checkcond_lo op) (arm32_checkcond_mi op)
       (arm32_checkcond_pl op) (arm32_checkcond_vs op)
       (arm32_checkcond_vc op) (arm32_checkcond_hi op)
       (arm32_checkcond_ls op) (arm32_checkcond_ge op)
       (arm32_checkcond_lt op) (arm32_checkcond_gt op)
       (arm32_checkcond_le op)))

; instruction descriptions
(define (ADD_imm Rd Rn Imm op)
  (if (arm32_checkcond op)
      (set-box! Rd (bvadd (unbox Rn) (concat (bv 0 20) Imm)))
      (void)))
  

(define (ADD_reg Rd Rn Rm op)
  (if (arm32_checkcond op)
      (set-box! Rd (bvadd (unbox Rn) (unbox Rm)))
      (void)))

(define (CMP_imm Rn Imm op)
  (if (arm32_checkcond op)
      (begin
        (define alu_out (bvsub (unbox Rn) (concat (bv 0 20) Imm)))
        (define N_bit
          (bvand alu_out (bv #x80000000 32)))
        (define Z_bit
          (if (bveq alu_out (bv 0 32))
              (bv #x40000000 32) (bv 0 32)))
        (define C_bit
          (if (bveq (extract 31 31 alu_out) (bv 0 1))
              (bv #x20000000 32) (bv 0 32)))
        (define flag_mask (bv #x0FFFFFFF 32))
        (define CPSR_unset (bvand (unbox CPSR) flag_mask))
        (define CPSR_final (bvor CPSR_unset N_bit Z_bit C_bit))
        (set-box! CPSR CPSR_final))
      (void)))

(define (CMP_reg Rn Rm op)
  (if (arm32_checkcond op)
      (begin
        (define alu_out (bvsub (unbox Rn) (unbox Rm)))
        (define N_bit
          (bvand alu_out (bv #x80000000 32)))
        (define Z_bit
          (if (bveq alu_out (bv 0 32))
              (bv #x40000000 32) (bv 0 32)))
        (define C_bit
          (if (bveq (extract 31 31 alu_out) (bv 0 1))
              (bv #x20000000 32) (bv 0 32)))
        (define flag_mask (bv #x0FFFFFFF 32))
        (define CPSR_unset (bvand (unbox CPSR) flag_mask))
        (define CPSR_final (bvor CPSR_unset N_bit Z_bit C_bit))
        (set-box! CPSR CPSR_final))
      (void)))

; generate the instruction list
; num indicates the number of the instruction list is (num + 1) 
(define-synthax (inst num)
  #:base (choose
          (ADD_imm (choose R0 R1 R2) (choose R0 R1 R2)
                   (?? (bitvector 12)) (?? (bitvector 4)))
          (ADD_reg (choose R0 R1 R2) (choose R0 R1 R2)
                   (choose R0 R1 R2) (?? (bitvector 4)))
          (CMP_imm (choose R0 R1 R2) (?? (bitvector 12)) (?? (bitvector 4)))
          (CMP_reg (choose R0 R1 R2) (choose R0 R1 R2) (?? (bitvector 4))))
  #:else (begin
           (choose
            (ADD_imm (choose R0 R1 R2) (choose R0 R1 R2)
                     (?? (bitvector 12)) (?? (bitvector 4)))
            (ADD_reg (choose R0 R1 R2) (choose R0 R1 R2)
                     (choose R0 R1 R2) (?? (bitvector 4)))
            (CMP_imm (choose R0 R1 R2) (?? (bitvector 12)) (?? (bitvector 4)))
            (CMP_reg (choose R0 R1 R2) (choose R0 R1 R2) (?? (bitvector 4))))
           (inst (- num 1))))

(current-bitwidth #f)
; synthesis part
(define model
 (synthesize
  #:forall (list r0_init r1_init)
  #:guarantee (begin
                (inst 2)
                (assert (bveq (unbox R2) (bv 0 32)))
                (assert (bveq (unbox R1) (bv 1 32)))
                (assert (or (bveq (unbox R1) (bv 0 32)) (bveq (unbox R1) (bv 1 32))))
                (assert (or (not (bveq (unbox R1) (bv 0 32)))
                             (and (bveq (unbox R0) (bv 5 32))
                                  (bveq (unbox CPSR) (bv #x60000000 32)))))
                (assert (or (not (bveq (unbox R1) (bv 1 32)))
                            (and (bveq (unbox R0) (bv 10 32))
                                  (bveq (unbox CPSR) (bv #x20000000 32))))))))

(print-forms model)
(evaluate (unbox R0) model)
(evaluate (unbox R1) model)
(evaluate (unbox R2) model)
(evaluate (unbox CPSR) model)
; get the model result: (print-forms model)
; get the content of the registers: (evaluate (unbox R0) model)