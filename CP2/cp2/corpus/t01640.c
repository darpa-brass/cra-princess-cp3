/*
 * This is a RANDOMLY GENERATED PROGRAM.
 *
 * Generator: csmith 2.3.0
 * Git version: 30dccd7
 * Options:   --take-no-union-field-addr --no-packed-struct --no-float --seed 3619970003
 * Seed:      3619970003
 */

#include "csmith.h"


static long __undefined;

/* --- Struct/Union Declarations --- */
struct S1 {
   signed f0 : 23;
   unsigned f1 : 22;
   unsigned f2 : 6;
};

struct S2 {
   const signed f0 : 25;
   unsigned f1 : 4;
   unsigned f2 : 26;
   const signed f3 : 31;
   int16_t  f4;
};

/* --- GLOBAL VARIABLES --- */
static volatile int32_t g_3 = 0x5AA96141L;/* VOLATILE GLOBAL g_3 */
static int32_t g_4 = 0x1F13B01DL;
static int32_t g_9 = 0xB9737E0DL;
static struct S1 g_10 = {-663,275,6};
static struct S1 * volatile g_11 = &g_10;/* VOLATILE GLOBAL g_11 */


/* --- FORWARD DECLARATIONS --- */
static struct S2  func_1(void);
static struct S1  func_5(uint16_t  p_6);


/* --- FUNCTIONS --- */
/* ------------------------------------------ */
/* 
 * reads : g_4 g_10 g_11
 * writes: g_4 g_9 g_10
 */
static struct S2  func_1(void)
{ /* block id: 0 */
    int16_t l_2[5];
    struct S2 l_12 = {5002,0,5971,5619,0x17F2L};
    int i;
    for (i = 0; i < 5; i++)
        l_2[i] = 0L;
    for (g_4 = 0; (g_4 <= 4); g_4 += 1)
    { /* block id: 3 */
        int i;
        (*g_11) = func_5(l_2[g_4]);
    }
    return l_12;
}


/* ------------------------------------------ */
/* 
 * reads : g_10
 * writes: g_9
 */
static struct S1  func_5(uint16_t  p_6)
{ /* block id: 4 */
    int32_t *l_7 = (void*)0;
    int32_t *l_8 = &g_9;
    (*l_8) = 0L;
    return g_10;
}




/* ---------------------------------------- */
int main (int argc, char* argv[])
{
    int print_hash_value = 0;
    if (argc == 2 && strcmp(argv[1], "1") == 0) print_hash_value = 1;
    platform_main_begin();
    crc32_gentab();
    func_1();
    transparent_crc(g_3, "g_3", print_hash_value);
    transparent_crc(g_4, "g_4", print_hash_value);
    transparent_crc(g_9, "g_9", print_hash_value);
    transparent_crc(g_10.f0, "g_10.f0", print_hash_value);
    transparent_crc(g_10.f1, "g_10.f1", print_hash_value);
    transparent_crc(g_10.f2, "g_10.f2", print_hash_value);
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}

/************************ statistics *************************
XXX max struct depth: 1
breakdown:
   depth: 0, occurrence: 0
   depth: 1, occurrence: 2
XXX total union variables: 0

XXX non-zero bitfields defined in structs: 7
XXX zero bitfields defined in structs: 0
XXX const bitfields defined in structs: 2
XXX volatile bitfields defined in structs: 0
XXX structs with bitfields in the program: 2
breakdown:
   indirect level: 0, occurrence: 2
XXX full-bitfields structs in the program: 1
breakdown:
   indirect level: 0, occurrence: 1
XXX times a bitfields struct's address is taken: 1
XXX times a bitfields struct on LHS: 0
XXX times a bitfields struct on RHS: 2
XXX times a single bitfield on LHS: 0
XXX times a single bitfield on RHS: 0

XXX max expression depth: 2
breakdown:
   depth: 1, occurrence: 5
   depth: 2, occurrence: 2

XXX total number of pointers: 3

XXX times a variable address is taken: 2
XXX times a pointer is dereferenced on RHS: 0
breakdown:
XXX times a pointer is dereferenced on LHS: 2
breakdown:
   depth: 1, occurrence: 2
XXX times a pointer is compared with null: 0
XXX times a pointer is compared with address of another variable: 0
XXX times a pointer is compared with another pointer: 0
XXX times a pointer is qualified to be dereferenced: 0

XXX max dereference level: 1
breakdown:
   level: 0, occurrence: 0
   level: 1, occurrence: 2
XXX number of pointers point to pointers: 0
XXX number of pointers point to scalars: 2
XXX number of pointers point to structs: 1
XXX percent of pointers has null in alias set: 33.3
XXX average alias set size: 1

XXX times a non-volatile is read: 4
XXX times a non-volatile is write: 4
XXX times a volatile is read: 0
XXX    times read thru a pointer: 0
XXX times a volatile is write: 1
XXX    times written thru a pointer: 0
XXX times a volatile is available for access: 1
XXX percentage of non-volatile access: 88.9

XXX forward jumps: 0
XXX backward jumps: 0

XXX stmts: 5
XXX max block depth: 1
breakdown:
   depth: 0, occurrence: 4
   depth: 1, occurrence: 1

XXX percentage a fresh-made variable is used: 100
XXX percentage an existing variable is used: 0
FYI: the random generator makes assumptions about the integer size. See platform.info for more details.
********************* end of statistics **********************/

