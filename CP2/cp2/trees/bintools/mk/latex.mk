# default settings (should be set by client makefile)
DOC?=somedoc
TEXFILES?=manual.tex
USE_BIBTEX?=no
EXTRAPASSES?=0

PDFLATEX=pdflatex
BIBTEX=bibtex

.if $(USE_BIBTEX) != "no"
TEXFILES+=../common/common.bib
.endif

TEXFILES+=../common/common.tex

.if $(EXTRAPASSES) > 0
PASSES!=echo $(EXTRAPASSES) | awk '{ for (i=0; i<$$1; i++) print i; }'
.else
PASSES=
.endif

############################################################

.SUFFIXES: .tex .pdf

all: manual.pdf

manual.pdf: $(TEXFILES)
	$(PDFLATEX) manual.tex
.if $(USE_BIBTEX) != "no"
	$(BIBTEX) ../common/common
.endif
.for P in $(PASSES)
	$(PDFLATEX) manual.tex
.endfor

install:
	cp manual.pdf ../$(DOC).pdf

clean distclean:
	rm -f *.log *.aux *.bbl *.blg
	rm -f manual.pdf

.PHONY: all install clean

