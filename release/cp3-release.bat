@echo off

rem Set script variables

set PROJECT_NAME=princess-cp3
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

mkdir lib
for /r ..\..\lib_managed %%f in (*.jar) do @copy "%%f" .\lib\

copy ..\..\kalmanfilter\target\scala-%RELEASE_SCALA%\kalmanfilter_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib
copy ..\..\kalmanfilter-component\target\scala-%RELEASE_SCALA%\kalmanfiltercomponent_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib
copy ..\..\localizationalgorithm\target\scala-%RELEASE_SCALA%\localizationalgorithm_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib
copy ..\..\princess\target\scala-%RELEASE_SCALA%\princess_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib
copy ..\..\cptoolkit\latest\evaluation\lib\*.jar .\lib
copy ..\..\cptoolkit\latest\remus\lib\remus_%RELEASE_SCALA%-%CPTOOLKIT_VERSION%.jar .\lib
copy ..\..\cptoolkit\latest\remus\lib\messaging-0.1-SNAPSHOT.jar .\lib
copy ..\..\remus-client\target\scala-%RELEASE_SCALA%\remusclient_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib
copy ..\..\remus-client\lib\*.jar .\lib
copy ..\..\pathplanner\target\scala-%RELEASE_SCALA%\pathplanner_%RELEASE_SCALA%-%RELEASE_VERSION%.jar .\lib

rem Copy native libraries
copy ..\..\princess\lib\*.* .\lib
copy ..\..\octave-bridge\src\liboctavebridge.so .\lib
copy ..\..\octave-bridge\src\octavebridge.dll .\lib

xcopy /s /e ..\..\launcher\*.* .

rem Grizzly Service
copy ..\..\cptoolkit\latest\mockwebservice\lib\*.* .\lib
xcopy /s /e ..\..\cptoolkit\latest\mockwebservice\config\*.* .\config\*.*
copy ..\..\cptoolkit\latest\mockwebservice\*.sh .
copy ..\..\cptoolkit\latest\mockwebservice\*.bat .
copy ..\..\cptoolkit\latest\mockwebservice\*.properties .
copy ..\..\cptoolkit\latest\mockwebservice\lib\mockwebservice_%RELEASE_SCALA%-%CPTOOLKIT_VERSION%.jar .\lib

rem Copy all JavaDoc/ScalaDoc

mkdir api
copy ..\..\cptoolkit\latest\evaluation\api\evaluation_%RELEASE_SCALA%-%CPTOOLKIT_VERSION%-javadoc.jar .\api
copy ..\..\cptoolkit\latest\remus\api\remus_%RELEASE_SCALA%-%CPTOOLKIT_VERSION%-javadoc.jar .\api
copy ..\..\kalmanfilter\target\scala-%RELEASE_SCALA%\kalmanfilter_%RELEASE_SCALA%-%RELEASE_VERSION%-javadoc.jar .\api
copy ..\..\kalmanfilter-component\target\scala-%RELEASE_SCALA%\kalmanfiltercomponent_%RELEASE_SCALA%-%RELEASE_VERSION%-javadoc.jar .\api
copy ..\..\localizationalgorithm\target\scala-%RELEASE_SCALA%\localizationalgorithm_%RELEASE_SCALA%-%RELEASE_VERSION%-javadoc.jar .\api
copy ..\..\princess\target\scala-%RELEASE_SCALA%\princess_%RELEASE_SCALA%-%RELEASE_VERSION%-javadoc.jar .\api
copy ..\..\remus-client\target\scala-%RELEASE_SCALA%\remusclient_%RELEASE_SCALA%-%RELEASE_VERSION%-javadoc.jar .\api
copy ..\..\pathplanner\target\scala-%RELEASE_SCALA%\pathplanner_%RELEASE_SCALA%-%RELEASE_VERSION%-javadoc.jar .\api

rem Copy all source

mkdir src
copy ..\..\cptoolkit\latest\evaluation\src\evaluation_%RELEASE_SCALA%-%CPTOOLKIT_VERSION%-sources.jar .\src
copy ..\..\cptoolkit\latest\remus\src\remus_%RELEASE_SCALA%-%CPTOOLKIT_VERSION%-sources.jar .\src
copy ..\..\kalmanfilter\target\scala-%RELEASE_SCALA%\kalmanfilter_%RELEASE_SCALA%-%RELEASE_VERSION%-sources.jar .\src
copy ..\..\kalmanfilter-component\target\scala-%RELEASE_SCALA%\kalmanfiltercomponent_%RELEASE_SCALA%-%RELEASE_VERSION%-sources.jar .\src
copy ..\..\localizationalgorithm\target\scala-%RELEASE_SCALA%\localizationalgorithm_%RELEASE_SCALA%-%RELEASE_VERSION%-sources.jar .\src
copy ..\..\princess\target\scala-%RELEASE_SCALA%\princess_%RELEASE_SCALA%-%RELEASE_VERSION%-sources.jar .\src
copy ..\..\remus-client\target\scala-%RELEASE_SCALA%\remusclient_%RELEASE_SCALA%-%RELEASE_VERSION%-sources.jar .\src
copy ..\..\pathplanner\target\scala-%RELEASE_SCALA%\pathplanner_%RELEASE_SCALA%-%RELEASE_VERSION%-sources.jar .\src

rem Copy text files and runtime scripts

xcopy /s /e /y ..\..\CP3\*.* .\*.*

cd ..

:Done
echo.
echo Done!
echo.
echo PRINCESS-CP3 v%RELEASE_VERSION% is ready for distribution.
echo.

rem Clear script variables

set PROJECT_NAME=
set RELEASE_VERSION=
set CPTOOLKIT_VERSION=
set RELEASE_SCALA=
