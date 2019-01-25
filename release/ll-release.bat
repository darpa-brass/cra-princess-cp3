@echo off
call buildall

call cpt-release

cd ..\..\release
call cp2-release

cd ..\release
call cp3-release
