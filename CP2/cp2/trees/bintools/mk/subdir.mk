
#
# Since portable make has no loops or iteration, we need to write this
# all out. Provide all recursive targets we might want anywhere,
# including those that don't make sense some places.
#

.SUFFIXES: -sub

all:        before-all        $(WAIT) all-sub        $(WAIT) after-all
depend:     before-depend     $(WAIT) depend-sub     $(WAIT) after-depend
install:    before-install    $(WAIT) install-sub    $(WAIT) after-install
clean:      before-clean      $(WAIT) clean-sub      $(WAIT) after-clean
distclean:  before-distclean  $(WAIT) distclean-sub  $(WAIT) after-distclean
gentarget:  before-gentarget  $(WAIT) gentarget-sub  $(WAIT) after-gentarget
run-tests:  before-run-tests  $(WAIT) run-tests-sub  $(WAIT) after-run-tests
show-diffs: before-show-diffs $(WAIT) show-diffs-sub $(WAIT) after-show-diffs
good:       before-good       $(WAIT) good-sub       $(WAIT) after-good

before-all before-depend before-install before-clean before-distclean \
 before-gentarget \
 before-run-tests before-show-diffs before-good: ;

after-all after-depend after-install after-clean after-distclean \
 after-gentarget \
 after-run-tests after-show-diffs after-good: ;

all-sub depend-sub install-sub clean-sub distclean-sub \
 gentarget-sub \
 run-tests-sub show-diffs-sub good-sub:
	@for d in $(SUBDIRS); do \
	    if [ $$d != .WAIT ]; then \
		echo "(cd $$d && $(MAKE) ${@:-sub=})" && \
		(cd $$d && $(MAKE) ${@:-sub=}) || exit 1; \
	    fi; \
	 done

.PHONY: all depend install clean distclean
.PHONY: gentarget
.PHONY: run-tests show-diffs good
.PHONY: before-all before-depend before-install before-clean before-distclean
.PHONY: before-gentarget
.PHONY: before-run-tests before-show-diffs before-good
.PHONY: after-all after-depend after-install after-clean after-distclean
.PHONY: after-gentarget
.PHONY: after-run-tests after-show-diffs after-good
.PHONY: all-sub depend-sub install-sub clean-sub distclean-sub
.PHONY: gentarget-sub
.PHONY: run-tests-sub show-diffs-sub good-sub
