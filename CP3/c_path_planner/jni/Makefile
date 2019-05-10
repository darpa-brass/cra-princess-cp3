CC=gcc -O3 -fno-stack-protector -march=native -mtune=native -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/win32" 
JCC=javac

all: TestJNI.class pathPlannerJNI.dll

pathPlannerJNI.dll: pathplannerJNI.o transformed_pathplanner.o
	${CC} -o pathPlannerJNI.dll pathplannerJNI.o transformed_pathplanner.o -shared
TestJNI.class: TestJNI.java
	${JCC} -h . TestJNI.java
clean:
	rm pathPlannerJNI.dll *.o *.class

