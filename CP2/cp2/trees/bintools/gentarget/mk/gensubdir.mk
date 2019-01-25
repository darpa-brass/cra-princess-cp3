#
# Inside gentarget we can depend on BSD make, so this can be written
# to parallelize.
#

.if defined(TESTTARGETS)
TARGETS?=all run-tests show-diffs good
.else
TARGETS?=all depend diff install clean distclean
.endif

.for T in $(TARGETS)
$(T): before-$(T) .WAIT $(T)-sub .WAIT after-$(T)

before-$(T) after-$(T): ;

.for D in $(SUBDIRS)

.if $(D) == ".WAIT"
$(T)-sub: .WAIT
.else
$(T)-sub: $(T)-in-$(D)
$(T)-in-$(D):
	(cd $(D) && $(MAKE) $(T)) || exit 1
.PHONY: $(T)-in-$(D)
.endif # .WAIT

.if $(T) == "show-diffs"
# force test diffs to be printed sequentially so they don't get
# interspersed in the output (which helps nothing)
$(T)-sub: .WAIT
.endif  # show-diffs

.endfor # SUBDIRS

.PHONY: $(T) before-$(T) after-$(T) $(T)-sub
.endfor # TARGETS
