/*
 * This is a RANDOMLY GENERATED PROGRAM.
 *
 * Generator: csmith 2.3.0
 * Git version: 30dccd7
 * Options:   --take-no-union-field-addr --no-packed-struct --no-float --seed 507419827
 * Seed:      507419827
 */

#include "csmith.h"


static long __undefined;

/* --- Struct/Union Declarations --- */
/* --- GLOBAL VARIABLES --- */
static volatile int32_t g_2[6] = {0x13F1A073L,0x543BEB71L,0x13F1A073L,0x13F1A073L,0x543BEB71L,0x13F1A073L};
static int32_t g_3 = 0x46507E67L;


/* --- FORWARD DECLARATIONS --- */
static int8_t  func_1(void);


/* --- FUNCTIONS --- */
/* ------------------------------------------ */
/* 
 * reads : g_3 g_2
 * writes: g_3
 */
static int8_t  func_1(void)
{ /* block id: 0 */
    for (g_3 = 0; (g_3 <= 8); ++g_3)
    { /* block id: 3 */
        return g_3;
    }
    return g_2[1];
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
    for (i = 0; i < 6; i++)
    {
        transparent_crc(g_2[i], "g_2[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_3, "g_3", print_hash_value);
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}

/************************ statistics *************************
XXX max struct depth: -1
breakdown:
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

XXX max expression depth: 2
breakdown:
   depth: 1, occurrence: 2
   depth: 2, occurrence: 1

XXX total number of pointers: 0

XXX times a non-volatile is read: 2
XXX times a non-volatile is write: 1
XXX times a volatile is read: 1
XXX    times read thru a pointer: 0
XXX times a volatile is write: 0
XXX    times written thru a pointer: 0
XXX times a volatile is available for access: 2
XXX percentage of non-volatile access: 75

XXX forward jumps: 0
XXX backward jumps: 0

XXX stmts: 3
XXX max block depth: 1
breakdown:
   depth: 0, occurrence: 2
   depth: 1, occurrence: 1

XXX percentage a fresh-made variable is used: 0
XXX percentage an existing variable is used: 100
FYI: the random generator makes assumptions about the integer size. See platform.info for more details.
********************* end of statistics **********************/

