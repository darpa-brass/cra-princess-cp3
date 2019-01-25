# Set before including:
#   LIB
#   SRCS
#   MYCFLAGS
#
# Include defs.mk before including this file.
#

OBJS=$(SRCS:.c=.o)

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) -cruv $(LIB) $(OBJS)
	$(RANLIB) $(LIB)

.c.o:
	$(CC) $(MYCFLAGS) $(CFLAGS) -c $< -o $@

-include .depend
depend:
	$(CC) $(MYCFLAGS) $(CFLAGS) -MM $(SRCS) |\
		sed -f $(TOP)/mk/fixdeps.sed > .depend

install:
	@true

clean:
	rm -f $(LIB) *.a *.o arch/*/*.o *~ a.out

distclean sub-distclean: clean
	rm -f .depend

gentarget:;

.PHONY: all depend install clean distclean sub-distclean gentarget
