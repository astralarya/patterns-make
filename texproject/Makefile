# texproject
# a Makefile to manage a LaTeX document
#
# Copyright (C) 2013 Mara Kim
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see http://www.gnu.org/licenses/.


# to commit, in a shell:
# make

# project specific

NAME=texproject
VERSION=0.0
MAIN=$(NAME).tex
FIGURES=
REVISION_FILE=VERSION.log
MISC=README.md .gitignore

# environment specific

LATEX=pdflatex
EVINCE=evince
GIT=git
TAR=tar
TFLAGS=-pczf
NANO=vim
AWK=awk
ECHO=echo
PRINTF=printf
RM=rm
ME=Makefile

# macros

TEXFILES=$(wildcard *.tex)
DOCUMENT=$(NAME).pdf
MANIFEST=$(TEXFILES) $(FIGURES) $(REVISION_FILE) $(MISC) $(ME)

# rules

all: doc view

doc: hash $(MAIN) $(TEXFILES) $(DOCUMENT)

rebuild: clean all

hash $(REVISION_FILE):
	@$(GIT) rev-parse 2> /dev/null && $(ECHO) $(NAME) $(VERSION) > $(REVISION_FILE) && $(GIT) rev-parse HEAD >> $(REVISION_FILE) && $(PRINTF) '## ' >> $(REVISION_FILE) && $(GIT) rev-parse --abbrev-ref HEAD >> $(REVISION_FILE) && $(GIT) status --porcelain >> $(REVISION_FILE) && $(ECHO) >> $(REVISION_FILE) && git diff >> $(REVISION_FILE) && $(ECHO) 'Generate hash' || $(ECHO) 'Using stored hash'
	@[ -e $(REVISION_FILE) ]

tar: hash $(MANIFEST)
	$(TAR) --transform 's,^,$(NAME)_$(VERSION)/,' -pczf $(NAME)_$(VERSION).tar.gz $(MANIFEST)

clean:
	$(RM) -f $(DOCUMENT) $(DVIFILE)

cleanall: clean
	$(RM) -f $(NAME)_*.tar.gz *.log *.aux *.toc *.tof *.nav *.out *.snm *.vrb

view: $(DOCUMENT)
	$(EVINCE) $(DOCUMENT)

.PHONY: all rebuild hash tar clean cleanall view

.SECONDARY:

$(DOCUMENT): $(MAIN) $(FIGURES) $(REVISION_FILE)
	$(LATEX) -jobname=$(NAME) $(MAIN)

