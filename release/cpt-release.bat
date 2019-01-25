@echo off

rem Set script variables

set PROJECT_NAME=CPToolkit
set RELEASE_VERSION=1.3.0
set RELEASE_SCALA=2.12

rem Create and populate the binary distribution directory structure

cd ..\cptoolkit\latest

rem Evaluation JAR

if exist .\evaluation rmdir /S /Q .\evaluation
mkdir .\evaluation
cd .\evaluation
mkdir .\lib
mkdir .\api
mkdir .\src

copy ..\..\source\evaluation\lib\*.* .\lib
copy ..\..\source\evaluation\*.sh .
copy ..\..\source\evaluation\*.bat .
copy ..\..\..\properties\*.properties .
copy ..\..\source\evaluation\target\scala-%RELEASE_SCALA%\evaluation_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib
copy ..\..\source\evaluation\target\scala-%RELEASE_SCALA%\evaluation_%RELEASE_SCALA%-%RELEASE_VERSION%-javadoc.jar .\api
copy ..\..\source\evaluation\target\scala-%RELEASE_SCALA%\evaluation_%RELEASE_SCALA%-%RELEASE_VERSION%-sources.jar .\src
copy ..\..\..\pathplanner\target\scala-%RELEASE_SCALA%\pathplanner_%RELEASE_SCALA%-1.0.0.jar .\lib
copy ..\..\..\lib_managed\jars\org.scala-lang\scala-library\scala-library-%RELEASE_SCALA%.3.jar .\lib
copy ..\..\..\lib_managed\jars\net.liftweb\lift-json_%RELEASE_SCALA%\lift-json_%RELEASE_SCALA%-*.jar .\lib

cd ..

rem REMUS Manager JAR

if exist .\remus rmdir /S /Q .\remus
mkdir .\remus
cd .\remus
mkdir .\lib
mkdir .\api
mkdir .\src

copy ..\..\source\remus\lib\*.* .\lib
copy ..\..\..\properties\*.properties .
copy ..\..\source\remus\target\scala-%RELEASE_SCALA%\remus_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib
copy ..\..\source\remus\target\scala-%RELEASE_SCALA%\remus_%RELEASE_SCALA%-%RELEASE_VERSION%-javadoc.jar .\api
copy ..\..\source\remus\target\scala-%RELEASE_SCALA%\remus_%RELEASE_SCALA%-%RELEASE_VERSION%-sources.jar .\src
copy ..\..\..\lib_managed\jars\org.scala-lang\scala-library\scala-library-%RELEASE_SCALA%.3.jar .\lib
copy ..\..\..\lib_managed\jars\net.liftweb\lift-json_%RELEASE_SCALA%\lift-json_%RELEASE_SCALA%-3.2.0.jar .\lib

cd ..

rem REMUS Viewer Application

if exist .\remus-viewer rmdir /S /Q .\remus-viewer
mkdir .\remus-viewer
cd .\remus-viewer
mkdir .\lib
mkdir .\api
mkdir .\src

copy ..\..\source\remus-viewer\lib\*.* .\lib
copy ..\..\source\remus\lib\*.* .\lib
copy ..\..\source\remus-viewer\*.properties .
copy ..\..\source\remus-viewer\*.sh .
copy ..\..\source\remus-viewer\*.bat .
copy ..\..\source\remus-viewer\*.properties .
copy ..\..\source\remus-viewer\target\scala-%RELEASE_SCALA%\remusviewer_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib
copy ..\..\source\remus-viewer\target\scala-%RELEASE_SCALA%\remusviewer_%RELEASE_SCALA%-%RELEASE_VERSION%-javadoc.jar .\api
copy ..\..\source\remus-viewer\target\scala-%RELEASE_SCALA%\remusviewer_%RELEASE_SCALA%-%RELEASE_VERSION%-sources.jar .\src
copy ..\..\source\remus\target\scala-%RELEASE_SCALA%\remus_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib
copy ..\..\..\lib_managed\jars\org.scala-lang\scala-library\scala-library-%RELEASE_SCALA%.3.jar .\lib
copy ..\..\..\lib_managed\jars\net.liftweb\lift-json_%RELEASE_SCALA%\lift-json_%RELEASE_SCALA%-3.2.0.jar .\lib
copy ..\..\source\evaluation\target\scala-%RELEASE_SCALA%\evaluation_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib

cd ..

rem Mock Test Harness Web Service

if exist .\mockwebservice rmdir /S /Q .\mockwebservice
mkdir .\mockwebservice
cd .\mockwebservice
mkdir .\lib
mkdir .\api
mkdir .\src
mkdir .\config

copy ..\..\source\mockwebservice\lib\*.* .\lib
xcopy /s /e ..\..\source\mockwebservice\config\*.* .\config
copy ..\..\source\evaluation\lib\*.* .\lib
copy ..\..\..\properties\*.properties .
copy ..\..\source\mockwebservice\*.sh .
copy ..\..\source\mockwebservice\*.bat .
copy ..\..\source\mockwebservice\target\scala-%RELEASE_SCALA%\mockwebservice_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib
copy ..\..\source\mockwebservice\target\scala-%RELEASE_SCALA%\mockwebservice_%RELEASE_SCALA%-%RELEASE_VERSION%-javadoc.jar .\api
copy ..\..\source\mockwebservice\target\scala-%RELEASE_SCALA%\mockwebservice_%RELEASE_SCALA%-%RELEASE_VERSION%-sources.jar .\src
copy ..\..\..\lib_managed\jars\org.scala-lang\scala-library\scala-library-%RELEASE_SCALA%.3.jar .\lib
copy ..\..\..\lib_managed\jars\net.liftweb\lift-json_%RELEASE_SCALA%\lift-json_%RELEASE_SCALA%-3.2.0.jar .\lib
copy ..\..\source\evaluation\target\scala-%RELEASE_SCALA%\evaluation_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib
copy ..\..\..\pathplanner\target\scala-%RELEASE_SCALA%\pathplanner_%RELEASE_SCALA%-1.0.0.jar .\lib

cd ..

rem Documentation

copy ..\source\doc\*.pdf .

:Done
echo.
echo Done!
echo.
echo PRINCESS %PROJECT_NAME% v%RELEASE_VERSION% is ready for distribution.
echo.

rem Clear script variables

set PROJECT_NAME=
set RELEASE_VERSION=
set RELEASE_SCALA=
