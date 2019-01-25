GENTOP=.
include $(GENTOP)/mk/genbase.mk

SUBDIRS=support $(WAIT) \
	parsetrees $(WAIT) \
	parsers reps $(WAIT) output $(WAIT) \
	tools testprogs $(WAIT) targets
# don't build tests by default
# tests

include $(GENTOP)/mk/gensubdir.mk

test:
	(cd tests && $(MAKE))

.PHONY: test

