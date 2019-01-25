# how to build PIC output
TARGET_PIC_ASFLAGS=-PIC

# Additional single-file tests that are not standard ones (std-*)
EXTRATESTS=

# Programs to test the linker (these will also be used as single-file tests)
PROGRAMS=hello #hello-pic hello-opt
SOURCES.hello=hello hello-support
SOURCES.hello-pic=hello-pic hello-support
SOURCES.hello-opt=hello-opt hello-support
