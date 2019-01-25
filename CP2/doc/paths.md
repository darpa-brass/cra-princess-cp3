# Paths to be used in the cp2 container

Guiding principles:

 * This material runs in a container on top of an existing
operating system; therefore, we should avoid creating
directories that might conflict with OS-level or
Docker-level material.
   
 * Thus, everything we provide for this evaluation should live
inside the directory /cp2

The following directories are created in the Docker image, mirroring
the layout of the cp2 subdirectory of this tree.

|Path       |                  |Description
|---        |---               |---
|/cp2/sut   |                  | Python code for talking to the test harness (this drives the rest.) 
|           |                  |
|/cp2/trees |                  | Copies of our code 
|           | bintools/        |
|           | cassiopeia/      |
|           | alewife/         |
|           | [etc]            |
|           | prep-build.sh    | Script for compiling these (during image build)
|           | update-cassiopeia.sh | Script for updating the tree (offline only)
|           |                  |
|/cp2/software |               | Other software we're using
|           | racket/          | Racket
|           | rosette/         | Rosette
|           |                  |
|/cp2/toolchain |              | Work area for toolchain evaluation
|           | adapt-build.sh   | Adaptation-phase script for compiling the toolchain
|           | adapt-install.sh | Adaptation-phase script for installing the toolchain
|           | test-mkworkarea.sh | Script for creating work/
|           | test-docompile.sh  | Script for compiling the test program
|           | build/           | Work area for adaptation-phase toolchain compilation (by target architecture)
|           | installed/       | Installation tree for adapted toolchains (by target architecture)
|           | work/            | Work area for the test program
|           | work/test.c      | the input test program
|           | work/test.s      | compiler output
|           | work/test.o      | assembler output
|           | work/test        | linked/runnable test program
|           |                  |
|/cp2/synth |                  | Work area for synthesis
|           | perturb.sh       | Script for applying perturbations
|           | dosynth.sh       | Script for driving the synthesis phase
|           | doverify.sh      | Script for driving the verification phase
|           |                  |
|/cp2/cross |                  | Crosscompiler/cross environment material and work areas
|           | prep-install-cross.sh | Script for installing crossbuild nevironments
|           | build/           | Work area for any needed compiles (currently none)
|           | installed/       | Installation area for same (currently none)
|/cp2/snippets |               | Test snippets for OS synthesis
|/cp2/corpus |                 | Sample test corpus for toolchain
