#!/bin/sh
# prep-build.sh - build additional software
#
# This script arranges the following:
#    - Racket
#    - Rosette
#    - Boolector
#
# Note: Rosette specifically needs Racket 6.6.

RACKET_FILE=racket-6.6-x86_64-linux.sh
ROSETTE_COMMIT=4d75e7e12e85779208f46231263742363dcbece7

echo "cd /cp2/software/racket"
cd /cp2/software/racket || exit 1
# assume the script contains bashisms and use bash, not sh
echo "bash $RACKET_FILE --unix-style --dest /cp2/software/installed"
bash $RACKET_FILE --unix-style --dest /cp2/software/installed || exit 1

echo "cd /cp2/software/rosette/rosette"
cd /cp2/software/rosette/rosette || exit 1
PATH=$PATH:/cp2/software/installed/bin
echo "raco pkg install"
raco pkg install || exit 1

echo "cd /cp2/software/boolector"
cd /cp2/software/boolector/boolector || exit 1
make || exit 1

echo "ln -s /cp2/software/boolector/boolector/boolector/bin/boolector /cp2/rosette/rosette/bin/boolector"
ln -s /cp2/software/boolector/boolector/boolector/bin/boolector /cp2/software/rosette/rosette/bin/boolector || exit 1


exit 0
