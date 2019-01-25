pre: true
post:
let r1loc: 8 bit = Mem[3,1] in
let r2loc: 8 bit = Mem[4,1] in
let r3loc: 8 bit = Mem[5,1] in
let r1b: bool = R1_orig == r1loc in
let r2b: bool = R2_orig == r2loc in
let r3b: bool = R3_orig == r3loc in
let fst: bool = r1b && r2b in
fst && r3b
