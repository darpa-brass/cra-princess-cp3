/*
 * This is a RANDOMLY GENERATED PROGRAM.
 *
 * Generator: csmith 2.3.0
 * Git version: 30dccd7
 * Options:   --take-no-union-field-addr --no-packed-struct --no-float --seed 2771526844
 * Seed:      2771526844
 */

#include "csmith.h"


static long __undefined;

/* --- Struct/Union Declarations --- */
union U0 {
   const uint64_t  f0;
   uint32_t  f1;
   int16_t  f2;
   volatile uint32_t  f3;
   volatile uint64_t  f4;
};

/* --- GLOBAL VARIABLES --- */
static union U0 g_2[10] = {{0x3D42374B1B055CC2LL},{0x3D42374B1B055CC2LL},{0x3D42374B1B055CC2LL},{0x3D42374B1B055CC2LL},{0x3D42374B1B055CC2LL},{0x3D42374B1B055CC2LL},{0x3D42374B1B055CC2LL},{0x3D42374B1B055CC2LL},{0x3D42374B1B055CC2LL},{0x3D42374B1B055CC2LL}};


/* --- FORWARD DECLARATIONS --- */
static union U0  func_1(void);


/* --- FUNCTIONS --- */
/* ------------------------------------------ */
/* 
 * reads : g_2
 * writes:
 */
static union U0  func_1(void)
{ /* block id: 0 */
    return g_2[4];
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
    for (i = 0; i < 10; i++)
    {
        transparent_crc(g_2[i].f0, "g_2[i].f0", print_hash_value);
        transparent_crc(g_2[i].f1, "g_2[i].f1", print_hash_value);
        transparent_crc(g_2[i].f2, "g_2[i].f2", print_hash_value);
        transparent_crc(g_2[i].f3, "g_2[i].f3", print_hash_value);
        transparent_crc(g_2[i].f4, "g_2[i].f4", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}

/************************ statistics *************************
XXX max struct depth: 0
breakdown:
   depth: 0, occurrence: 1
XXX total union variables: 1

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
   depth: 1, occurrence: 1

XXX total number of pointers: 0

XXX times a non-volatile is read: 1
XXX times a non-volatile is write: 0
XXX times a volatile is read: 0
XXX    times read thru a pointer: 0
XXX times a volatile is write: 0
XXX    times written thru a pointer: 0
XXX times a volatile is available for access: 0
XXX percentage of non-volatile access: 100

XXX forward jumps: 0
XXX backward jumps: 0

XXX stmts: 1
XXX max block depth: 0
breakdown:
   depth: 0, occurrence: 1

XXX percentage a fresh-made variable is used: 100
XXX percentage an existing variable is used: 0
FYI: the random generator makes assumptions about the integer size. See platform.info for more details.
********************* end of statistics **********************/

