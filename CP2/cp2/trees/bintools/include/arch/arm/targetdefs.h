/* Automatically generated; do not edit */

#ifndef TARGETDEFS_H
#define TARGETDEFS_H
typedef int8_t s_machbyte;
typedef uint8_t u_machbyte;
typedef int32_t s_machword;
typedef uint32_t u_machword;
typedef int64_t s_machlarge;
typedef uint64_t u_machlarge;
#undef AS_ALIGNS_BY_VALUE
#define AS_ALIGNS_BY_LOGVALUE
#define AS_COMM_ALIGNS_BY_VALUE
#undef AS_COMM_ALIGNS_BY_LOGVALUE
#define TEMP_LABEL_PREFIX ".L"
#define ENTRY_SYM "_start"
#define DEFAULT_TEXTORG 65536
#define DEFAULT_DATAORG 0
#define DEFAULT_BSSORG 0
#define TARGET_MAXALIGN 4
#define TARGET_PAGESIZE 4096
#define TARGET_TEXT_ALIGNMENT 4
#define TARGET_RDATA_ALIGNMENT 4
#define TARGET_DATA_ALIGNMENT 4
#define TARGET_BSS_ALIGNMENT 4
#define TARGET_ENDIANNESS MY_LITTLE_ENDIAN
#define TARGET_INTENCODING MY_TWOS_COMPLEMENT
#undef MIPS_ISSUE_REGINFO
#endif /* TARGETDEFS_H */
