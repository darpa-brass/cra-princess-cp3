#!/usr/bin/env bash

OUT=$1
IN=$2

# generate the prefix:
# let whatever = "\ ...
echo -n "let " > $OUT
head -n 1 $IN | sed 's/^#//' | tr -d "\n" >> $OUT
echo " = \"\\" >> $OUT

# body of file
# escape encountered quotes and backslashes
# replace newline with escaped newline and continuation
tail -n +2 $IN | sed 's/\\/\\\\/g' | sed 's/"/\\"/g' | sed 's/$/\\n\\/' >> $OUT

# trailing quote
echo "\"" >> $OUT
