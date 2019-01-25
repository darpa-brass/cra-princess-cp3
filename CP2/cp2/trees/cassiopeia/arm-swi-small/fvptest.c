
#include <stdint.h>
#include <stdio.h>

int main(void)
{
  uint32_t r0_=1;
  printf("Address of r0_ is %x, value = %d\n", &r0_, r0_);
  asm volatile(
      "pop {r4-r5}\n\t"
      );
  printf("New address of r0_ is %x, vale = %d\n", &r0_, r0_);


}

/*
armclang -c --target=arm-arm-none-eabi -mcpu=Cortex-A9 -mfpu=none -g -O0 fvptest.c -o fvptest.o

armlink --ro-base=0x80000000 fvptest.o -o fvptest.axf

FVP_VE_Cortex-A9x1 fvptest.axf
*/
