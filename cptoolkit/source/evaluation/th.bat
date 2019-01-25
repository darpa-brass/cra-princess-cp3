@echo off

set THCP=.\lib\*;.\target\scala-2.12\classes

java -cp %THCP% com.cra.princess.evaluation.TestHarnessAdapter %1 %2 %3 %4
