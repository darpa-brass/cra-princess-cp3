CC=mkoctfile 
CFLAGS=-O2 -fno-stack-protector #-march=native -mtune=native
INCLUDES=-I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/win32"

pathPlannerJNI: pathplannerJNI.o transformed_pathplanner.o
	${CC} -v --link-stand-alone ${CFLAGS} ${INCLUDES} -shared -o $@.dll $^ ${OBJS}

.c.o:
	${CC} ${CFLAGS} ${INCLUDES} -c $<
clean:
	rm -f *.o core *.core *.dll 

