Testing the `arm.casp` example
------------------------------

1. Set up the [ARM compiler 6 toolchain](https://developer.arm.com/products/software-development-tools/compilers/arm-compiler/downloads/version-6).

2. Get the [ARM v7 uniprocessor FVP](https://developer.arm.com/products/system-design/fixed-virtual-platforms).

3. Configure tests: in armtest.h, change the number of tests, cassiopeia file, or type of tests if desired and save.

4. Compile the Cassiopeia interpreter as directed and move the executable into this directory.

5. Run by executing the following:

```
/usr/local/DS-5_v5.28.1/bin/suite_exec bash --norc
make clean
make
FVP_VE_Cortex-A9x1 armtest.axf
```

Testing a different machine description
---------------------------------------

1. In `armtest.h`, change the definition of `struct state` and all related macros. Update `enum instr_type` to include all defined instructions in your machine description, and change `NUM_INSTRS` accordingly.

2. In `armtest_gen.c`, add or remove cases for both `generate_test` functions based on the instructions that are defined.

3. In `armtest.c`, add or remove specific test cases for `run_tests_set`, ensuring that corner cases are covered for any new instructions. Then change `run_casp` to correctly set up an initial state for the Cassiopeia interpreter and parse its output.

4. In `armasm.c`, delete all code between the two asterisked lines. Update the registers assignments to reflect your machine state, and make sure to separately handle any special state components (like CPSR in ARM). Update `armasm_gen.py` to generate all of the `asm volatile` calls to cover all possible combinations of inputs and instructions. Copy and paste the output between the two askerisked lines.
