# Set before including:
#   PROG
#   SRCS
#   MYCFLAGS
#   MYLIBS
#
# Include defs.mk before including this file.
#

all: new-$(PROG)

OBJS=$(SRCS:.c=.o)

new-$(PROG): $(OBJS) $(MYLIBS)
	$(CC) $(LDFLAGS) $(OBJS) $(MYLIBS) $(LIBS) -o new-$(PROG)

.c.o:
	$(CC) $(MYCFLAGS) $(CFLAGS) -c $< -o $@

-include .depend
depend:
	$(CC) $(MYCFLAGS) $(CFLAGS) -MM $(SRCS) |\
		sed -f $(TOP)/mk/fixdeps.sed > .depend

install:
	$(INSTALL) -c new-$(PROG) $(PREFIX)/bin/$(INSTALLTARGET)$(PROG)

clean:
	rm -f new-$(PROG) *.o arch/*/*.o *~ a.out

distclean sub-distclean: clean
	rm -f .depend

gentarget:;

.PHONY: all depend install clean distclean sub-distclean gentarget;
