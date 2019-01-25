./alewife ale-test/prog_disp_is_disabled1.ale -o prog_disp_is_disabled1.spec && \
./alewife ale-test/prog_disp_is_disabled2.ale -o prog_disp_is_disabled2.spec && \
./alewife ale-test/prog_disp_is_disabled3.ale -o prog_disp_is_disabled3.spec && \
./alewife ale-test/prog_disp_set_area.ale -o prog_disp_set_area.spec && \
#arm-3
./cassiopeia arm-swi-small/arm-tiny-3/arm-swi-tiny3.casp -verify prog_disp_is_disabled1.spec arm-swi-small/arm-tiny-3/prog_disp_is_disabled1.prog -o prog_disp_is_disabled1.arm.3.rkt && \
./cassiopeia arm-swi-small/arm-tiny-3/arm-swi-tiny3.casp -verify prog_disp_is_disabled2.spec arm-swi-small/arm-tiny-3/prog_disp_is_disabled2.prog -o prog_disp_is_disabled2.arm.3.rkt && \
./cassiopeia arm-swi-small/arm-tiny-3/arm-swi-tiny3.casp -verify prog_disp_is_disabled3.spec arm-swi-small/arm-tiny-3/prog_disp_is_disabled3.prog -o prog_disp_is_disabled3.arm.3.rkt && \
#arm-4
./cassiopeia arm-swi-small/arm-tiny-4/arm-swi-tiny4.casp -verify prog_disp_is_disabled1.spec arm-swi-small/arm-tiny-3/prog_disp_is_disabled1.prog -o prog_disp_is_disabled1.arm.4.rkt && \
./cassiopeia arm-swi-small/arm-tiny-4/arm-swi-tiny4.casp -verify prog_disp_is_disabled2.spec arm-swi-small/arm-tiny-4/prog_disp_is_disabled2.prog -o prog_disp_is_disabled2.arm.4.rkt && \
./cassiopeia arm-swi-small/arm-tiny-4/arm-swi-tiny4.casp -verify prog_disp_is_disabled3.spec arm-swi-small/arm-tiny-4/prog_disp_is_disabled3.prog -o prog_disp_is_disabled3.arm.4.rkt && \
#dis_set_area
./cassiopeia arm-swi-small/arm-tiny-3/arm-swi-tiny3.casp -verify prog_disp_set_area.spec arm-swi-small/arm-tiny-3/prog_disp_set_area.prog -o prog_disp_set_area.arm.3.rkt && \
./cassiopeia arm-swi-small/arm-tiny-4/arm-swi-tiny4.casp -verify prog_disp_set_area.spec arm-swi-small/arm-tiny-4/prog_disp_set_area.prog -o prog_disp_set_area.arm.4.rkt && \
raco make prog_disp_is_disabled1.arm.3.rkt && \
raco make prog_disp_is_disabled2.arm.3.rkt && \
raco make prog_disp_is_disabled3.arm.3.rkt && \
raco make prog_disp_set_area.arm.3.rkt && \
./cassiopeia x86-64-syscall/x86_tiny_4/x86-64-syscall-tiny4.casp -verify prog_disp_is_disabled1.spec x86-64-syscall/x86_tiny_4/prog_disp_is_disabled1.prog -o prog_disp_is_disabled1.x86.4.rkt && \
./cassiopeia x86-64-syscall/x86_tiny_4/x86-64-syscall-tiny4.casp -verify prog_disp_is_disabled2.spec x86-64-syscall/x86_tiny_4/prog_disp_is_disabled2.prog -o prog_disp_is_disabled2.x86.4.rkt && \
./cassiopeia x86-64-syscall/x86_tiny_4/x86-64-syscall-tiny4.casp -verify prog_disp_is_disabled3.spec x86-64-syscall/x86_tiny_4/prog_disp_is_disabled3.prog -o prog_disp_is_disabled3.x86.4.rkt && \
./cassiopeia x86-64-syscall/x86_tiny_3/x86-64-syscall-tiny3.casp -verify prog_disp_is_disabled1.spec x86-64-syscall/x86_tiny_3/prog_disp_is_disabled1.prog -o prog_disp_is_disabled1.x86.3.rkt && \
./cassiopeia x86-64-syscall/x86_tiny_3/x86-64-syscall-tiny3.casp -verify prog_disp_is_disabled2.spec x86-64-syscall/x86_tiny_3/prog_disp_is_disabled2.prog -o prog_disp_is_disabled2.x86.3.rkt && \
./cassiopeia x86-64-syscall/x86_tiny_3/x86-64-syscall-tiny3.casp -verify prog_disp_is_disabled3.spec x86-64-syscall/x86_tiny_3/prog_disp_is_disabled3.prog -o prog_disp_is_disabled3.x86.3.rkt && \
./cassiopeia x86-64-syscall/x86_tiny_2/x86-64-syscall-tiny2.casp -verify prog_disp_is_disabled1.spec x86-64-syscall/x86_tiny_2/prog_disp_is_disabled1.prog -o prog_disp_is_disabled1.x86.2.rkt && \
./cassiopeia x86-64-syscall/x86_tiny_1/x86-64-syscall-tiny1.casp -verify prog_disp_is_disabled1.spec x86-64-syscall/x86_tiny_1/prog_disp_is_disabled1.prog -o prog_disp_is_disabled1.x86.1.rkt && \
raco make prog_disp_is_disabled1.x86.4.rkt && \
raco make prog_disp_is_disabled2.x86.4.rkt && \
raco make prog_disp_is_disabled3.x86.4.rkt && \
raco make prog_disp_is_disabled1.x86.3.rkt && \
raco make prog_disp_is_disabled2.x86.3.rkt && \
raco make prog_disp_is_disabled3.x86.3.rkt && \
raco make prog_disp_is_disabled1.x86.2.rkt && \
raco make prog_disp_is_disabled1.x86.1.rkt && \
echo done
