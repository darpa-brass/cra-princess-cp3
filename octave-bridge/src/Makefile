CC=mkoctfile
INCLUDES=-I"${JAVA_HOME}\include" -I"${JAVA_HOME}\include\win32"
LIBDIRS=
#LIBS=-lmingw32 -loctave.dll

CFLAGS=$(INCLUDES) $(LIBDIRS)

octavebridge: call_octave_api.o jni_interface.o
	${CC} -v --link-stand-alone ${CFLAGS} -shared -o $@.dll $^ ${OBJS}
#	${CC} -v --link-stand-alone ${CFLAGS} -o $@ $^ ${OBJS}
	
.cpp.o:
	${CC} ${CFLAGS} -c $<
	
clean:
	rm -f *.o core *.core *.exe *.dll
