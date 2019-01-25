#lang rosette

(require rosette/lib/angelic rosette/lib/match
         rackunit rosette/solver/smt/boolector)

(current-solver (boolector))

; Bit stuff
(define bitwidth 8)

(define (bits*)
  (define-symbolic* b (bitvector bitwidth))
  b)

(define zero (bv 0 bitwidth))



; An association list is a list of key-value pairs.
; We make it a struct just for convenience (we can call an assoclist
; as a procedure to retrieve a value).
(define (assoclist-get lst key)
  (let loop ([cases (assoclist-cases lst)])
    (cond [(null? cases) #f]
          [(equal? (caar cases) key) (cdar cases)]
          [else (loop (cdr cases))])))
(define (assoclist-set lst key val)
  (assoclist
   (let loop ([cases (assoclist-cases lst)])
     (cond [(null? cases) (list (cons key val))]
           [(equal? (caar cases) key) (cons (cons key val) (cdr cases))]
           [else (cons (car cases) (loop (cdr cases)))]))))
(struct assoclist (cases) #:transparent
  #:property prop:procedure assoclist-get)




; A machine state is two association lists -- the current state of registers
; and the current state of memory. Machine states are immutable, so executing
; a program returns a *new* state and leaves the initial state unchanged.
(struct state (reg mem) #:transparent)

(define MEMORY_SIZE 8)
(define REGISTERS '(SP R1 R2 R3 #|R4|#))
(define REGISTER_SIZE (length REGISTERS))

; Create a fresh machine state with arbitrary memory and register values
(define (fresh-state)
  (define m (assoclist (for/list ([i MEMORY_SIZE]) (cons (bv i bitwidth) (bits*)))))
  (define r (assoclist (for/list ([r REGISTERS]) (cons r (bits*)))))
  (state r m))



; The instructions our machine supports.
(struct MOV/reg (Rd Rn) #:transparent)
(struct MOV/imm (Rd Imm) #:transparent)
(struct ADD/reg (Rd Rn Rm) #:transparent)
(struct ADD/imm (Rd Rn Imm) #:transparent)
(struct ST (Raddr Rval) #:transparent)
(struct LD (Rd Raddr) #:transparent)
(struct NOP () #:transparent)

; Take a list of instructions, and an initial machine state,
; and return the machine state after executing those instructions.
(define (execute prog st)
  (for/fold ([st st]) ([insn prog])
    (match insn
      [(MOV/reg Rd Rn)
       (state (assoclist-set (state-reg st) Rd ((state-reg st) Rn))
              (state-mem st))]
      [(MOV/imm Rd Imm)
       (state (assoclist-set (state-reg st) Rd Imm)
              (state-mem st))]
      [(ADD/reg Rd Rn Rm)
       (state (assoclist-set (state-reg st) Rd (bvadd ((state-reg st) Rn)
                                                      ((state-reg st) Rm)))
              (state-mem st))]
      [(ADD/imm Rd Rn Imm)
       (state (assoclist-set (state-reg st) Rd (bvadd ((state-reg st) Rn)
                                                      Imm))
              (state-mem st))]
      [(ST Raddr Rval)
       (state (state-reg st)
              (assoclist-set (state-mem st)
                             ((state-reg st) Raddr)
                             ((state-reg st) Rval)))]
      [(LD Rd Raddr)
       (state (assoclist-set (state-reg st) Rd ((state-mem st) ((state-reg st) Raddr)))
              (state-mem st))]
      [(NOP) st])))



; Specifications for save and load that hard-code the expected addresses.
(define (correct-save pre-state post-state)
  (assert
   (and (bveq ((state-mem post-state) (bv 3 bitwidth))
              ((state-reg pre-state) 'R1))
        (bveq ((state-mem post-state) (bv 4 bitwidth))
              ((state-reg pre-state) 'R2))
        (bveq ((state-mem post-state) (bv 5 bitwidth))
              ((state-reg pre-state) 'R3))
        #|(bveq ((state-mem post-state) (bv 6 bitwidth))
              ((state-reg pre-state) 'R4)))|#)))
(define (correct-load pre-state post-state)
  (assert
   (and (bveq ((state-mem pre-state) (bv 3 bitwidth))
              ((state-reg post-state) 'R1))
        (bveq ((state-mem pre-state) (bv 4 bitwidth))
              ((state-reg post-state) 'R2))
        (bveq ((state-mem pre-state) (bv 5 bitwidth))
              ((state-reg post-state) 'R3))
        #|(bveq ((state-mem pre-state) (bv 6 bitwidth))
              ((state-reg post-state) 'R4))|#)))



; Reference implementations of save and load
(define save-ctx/reference
  (list
   (MOV/imm 'SP (bv 3 bitwidth))
   (ST 'SP 'R1)
   (ADD/imm 'SP 'SP (bv 1 bitwidth))
   (ST 'SP 'R2)
   (ADD/imm 'SP 'SP (bv 1 bitwidth))
   (ST 'SP 'R3)
   #|(ADD/imm 'SP 'SP (bv 1 bitwidth))
   (ST 'SP 'R4)|#))

(define load-ctx/reference
  (list
   (MOV/imm 'SP (bv 3 bitwidth))
   (LD 'R1 'SP)
   (ADD/imm 'SP 'SP (bv 1 bitwidth))
   (LD 'R2 'SP)
   (ADD/imm 'SP 'SP (bv 1 bitwidth))
   (LD 'R3 'SP)
   #|(ADD/imm 'SP 'SP (bv 1 bitwidth))
   (LD 'R4 'SP)|#))



; Some sanity checks -- save/load are correct implementations of their
; respective specs, and do not satisfy the other spec.
(module+ test
  (define st (fresh-state))
  (check-true (unsat? (verify (correct-save st (execute save-ctx/reference st)))))
  (check-true (unsat? (verify (correct-load st (execute load-ctx/reference st)))))
  (check-false (unsat? (verify (correct-save st (execute load-ctx/reference st)))))
  (check-false (unsat? (verify (correct-load st (execute save-ctx/reference st))))))



; Creating sketches of registers, immediates, and instructions.
(define (reg*)
  (choose* 'SP 'R1 'R2 'R3 #|'R4|#))
(define (imm*)
  (define-symbolic* imm (bitvector bitwidth))
  imm)
(define (inst*)
  ; A little trick: we re-use arguments across all possible
  ; instructions, which compresses the encoding a little.
  (define Ra (reg*))
  (define Rb (reg*))
  (define Rc (reg*))
  (define Imm (imm*))
  (choose* (MOV/reg Ra Rb)
           (MOV/imm Ra Imm)
           #;(ADD/reg Ra Rb Rc)
           #;(ADD/imm Ra Rb Imm)
           (ST Ra Rb)
           (LD Ra Rb)
           #;(NOP)))



; Sketches for save and load.
(define st (fresh-state))
(define save-ctx (for/list ([_ 6]) (inst*)))
(define load-ctx (for/list ([_ 6]) (inst*)))



; Synthesize save
(define model-save
  (time
   (synthesize
    #:forall (symbolics st)
    #:guarantee (correct-save st (execute save-ctx st)))))
(if (sat? model-save)
    (begin (printf "Save: ") (pretty-print (evaluate save-ctx model-save)))
    (printf "No solution for save.\n"))

; Synthesize load
(define model-load
  (time
   (synthesize
    #:forall (symbolics st)
    #:guarantee (correct-load st (execute load-ctx st)))))
(if (sat? model-load)
    (begin (printf "Load: ") (pretty-print (evaluate load-ctx model-load)))
    (printf "No solution for load.\n"))
