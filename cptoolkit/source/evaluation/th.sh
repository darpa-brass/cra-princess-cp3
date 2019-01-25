#!/bin/bash -eu

CP=./lib/*;./target/scala-2.12/classes

CMD="java -cp $CP com.cra.princess.evaluation.TestHarnessAdapter $1 $2 $3 $4"

echo $CMD
$CMD
