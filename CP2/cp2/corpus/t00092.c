/*
 * This is a RANDOMLY GENERATED PROGRAM.
 *
 * Generator: csmith 2.3.0
 * Git version: 30dccd7
 * Options:   --take-no-union-field-addr --no-packed-struct --no-float --seed 3173930558
 * Seed:      3173930558
 */

#include "csmith.h"


static long __undefined;

/* --- Struct/Union Declarations --- */
struct S0 {
   uint16_t  f0;
   volatile int8_t  f1;
};

/* --- GLOBAL VARIABLES --- */
static volatile uint8_t g_2[8] = {9UL,249UL,9UL,9UL,249UL,9UL,9UL,249UL};
static int32_t g_4 = 0x6A1C17C7L;
static struct S0 g_5 = {0x583DL,0x0EL};/* VOLATILE GLOBAL g_5 */


/* --- FORWARD DECLARATIONS --- */
static struct S0  func_1(void);


/* --- FUNCTIONS --- */
/* ------------------------------------------ */
/* 
 * reads : g_2 g_4 g_5
 * writes: g_4
 */
static struct S0  func_1(void)
{ /* block id: 0 */
    int32_t *l_3[3];
    int i;
    for (i = 0; i < 3; i++)
        l_3[i] = &g_4;
    g_4 |= g_2[1];
    return g_5;
}




/* ---------------------------------------- */
int main (int argc, char* argv[])
{
    int i;
    int print_hash_value = 0;
    if (argc == 2 && strcmp(argv[1], "1") == 0) print_hash_value = 1;
    platform_main_begin();
    crc32_gentab();
    func_1();
    for (i = 0; i < 8; i++)
    {
        transparent_crc(g_2[i], "g_2[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_4, "g_4", print_hash_value);
    transparent_crc(g_5.f0, "g_5.f0", print_hash_value);
    transparent_crc(g_5.f1, "g_5.f1", print_hash_value);
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}

/************************ statistics *************************
XXX max struct depth: 1
breakdown:
   depth: 0, occurrence: 1
   depth: 1, occurrence: 1
XXX total union variables: 0

XXX non-zero bitfields defined in structs: 0
XXX zero bitfields defined in structs: 0
XXX const bitfields defined in structs: 0
XXX volatile bitfields defined in structs: 0
XXX structs with bitfields in the program: 0
breakdown:
XXX full-bitfields structs in the program: 0
breakdown:
XXX times a bitfields struct's address is taken: 0
XXX times a bitfields struct on LHS: 0
XXX times a bitfields struct on RHS: 0
XXX times a single bitfield on LHS: 0
XXX times a single bitfield on RHS: 0

XXX max expression depth: 1
breakdown:
   depth: 1, occurrence: 3

XXX total number of pointers: 1

XXX times a variable address is taken: 1
XXX times a pointer is dereferenced on RHS: 0
breakdown:
XXX times a pointer is dereferenced on LHS: 0
breakdown:
XXX times a pointer is compared with null: 0
XXX times a pointer is compared with address of another variable: 0
XXX times a pointer is compared with another pointer: 0
XXX times a pointer is qualified to be dereferenced: 0
XXX number of pointers point to pointers: 0
XXX number of pointers point to scalars: 1
XXX number of pointers point to structs: 0
XXX percent of pointers has null in alias set: 0
XXX average alias set size: 1

XXX times a non-volatile is read: 1
XXX times a non-volatile is write: 1
XXX times a volatile is read: 1
XXX    times read thru a pointer: 0
XXX times a volatile is write: 0
XXX    times written thru a pointer: 0
XXX times a volatile is available for access: 0
XXX percentage of non-volatile access: 66.7

XXX forward jumps: 0
XXX backward jumps: 0

XXX stmts: 2
XXX max block depth: 0
breakdown:
   depth: 0, occurrence: 2

XXX percentage a fresh-made variable is used: 66.7
XXX percentage an existing variable is used: 33.3
FYI: the random generator makes assumptions about the integer size. See platform.info for more details.
********************* end of statistics **********************/

