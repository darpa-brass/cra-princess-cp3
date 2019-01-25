# Intended for Arm Compiler 6

TARGET=armtest.axf


CC=armclang
LD=armlink

# Select build rules based on Windows or Unix
DONE=@if [ -f $(1) ]; then echo Build completed.; fi
RM=rm -f $(1)

all: $(TARGET)
	$(call DONE,$(TARGET))
	
rebuild: clean all

clean:
	$(call RM,*.o)
	$(call RM,$(TARGET))
	
armasm.o: armasm.c
	$(CC) -c --target=arm-arm-none-eabi -mcpu=Cortex-A9 -mfpu=none -g -O0 $^ -o $@

armtest_gen.o: armtest_gen.c
	$(CC) -c --target=arm-arm-none-eabi -mcpu=Cortex-A9 -mfpu=none -g -O0 $^ -o $@

armtest.o: armtest.c
# Compile for best debug view (lowest optimization)
	$(CC) -c --target=arm-arm-none-eabi -mcpu=Cortex-A9 -mfpu=none -g -O0 $^ -o $@

$(TARGET): armasm.o armtest_gen.o armtest.o
# Link with specific base address to suit VE model memory layout
	$(LD) --ro-base=0x80000000 $^ -o $@
