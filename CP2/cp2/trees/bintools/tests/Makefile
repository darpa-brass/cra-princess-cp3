all: run-tests .WAIT show-diffs

depend install: ;

run-tests show-diffs good clean:
	(cd singlefile && $(MAKE) $@)
	(cd multifile && $(MAKE) $@)

.PHONY: all run-tests show-diffs depend install clean
