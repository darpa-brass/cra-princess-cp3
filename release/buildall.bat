@echo off
cd ..
call sbt clean compile
call sbt test:compile test
call sbt package
call sbt packageSrc
call sbt packageDoc

cd release