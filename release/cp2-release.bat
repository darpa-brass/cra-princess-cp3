@echo off

rem Set script variables

set PROJECT_NAME=princess-cp2
set RELEASE_VERSION=1.0.0
set CPTOOLKIT_VERSION=1.3.0
set RELEASE_SCALA=2.12

cd ..

rem Create and populate the binary distribution directory structure

:CopyFiles
if not exist .\releases mkdir .\releases
cd releases
if exist .\%PROJECT_NAME%_%RELEASE_VERSION%-%RELEASE_SCALA% rmdir /S /Q .\%PROJECT_NAME%_%RELEASE_VERSION%-%RELEASE_SCALA%
mkdir .\%PROJECT_NAME%_%RELEASE_VERSION%-%RELEASE_SCALA%

cd .\%PROJECT_NAME%_%RELEASE_VERSION%-%RELEASE_SCALA%

xcopy /s /e ..\..\CP2\*.* .

rem mkdir lib
rem mkdir target\scala-%RELEASE_SCALA%
rem copy ..\..\cptoolkit\latest\evaluation\lib\evaluation_%RELEASE_SCALA%-%CPTOOLKIT_VERSION%.jar .\target\scala-%RELEASE_SCALA%\*.*

cd ..

:Done
echo.
echo Done!
echo.
echo PRINCESS-CP2 v%RELEASE_VERSION% is ready for distribution.
echo.

rem Clear script variables

set PROJECT_NAME=
set RELEASE_VERSION=
set CPTOOLKIT_VERSION=
set RELEASE_SCALA=
