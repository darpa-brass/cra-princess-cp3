TOP=.
include $(TOP)/mk/base.mk

SUBDIRS=support binfmts progs

include $(TOP)/mk/subdir.mk

#
# Before installing, create the installation dirs.
#

before-install: installdirs
installdirs:
	$(INSTALL) -d $(DESTDIR)$(PREFIX)
	$(INSTALL) -d $(DESTDIR)$(PREFIX)/bin

#
# After distclean (must be last so defs.mk isn't deleted while still
# being used), delete test results and then the current build config.
#

after-distclean: cleanhere
cleanhere:
	#$(MAKE) cleantest # XXX reenable sometime
	rm -f defs.mk include/host/*.h

.PHONY: after-distclean

#
# Tests
#

test:
	(cd tests && $(MAKE))

cleantest:
	(cd tests && $(MAKE) clean)

.PHONY: cleanhere test cleantest
