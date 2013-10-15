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
REVISION_FILE=VERSION.log
MISC=README.md

# environment specific

VERSIONSQL=version.sql
LATEX=latex
DVIPDF=dvipdf
GIT=git
TAR=tar
TFLAGS=-pczf
NANO=vim
AWK=awk
ECHO=echo
RM=rm
ME=Makefile

# macros

TEXFILES=$(wildcard *.tex)
DVIFILES=$(TEXFILES:.tex=.dvi)
DOCUMENT=$(MAIN:.tex=.pdf)
MANIFEST=$(LEXFILES) $(REVISION_FILE) $(ME)
HASH=$(shell $(AWK) 'NR==1 {printf "%s",$$0}' $(REVISION_FILE))
STATUS=$(shell $(AWK) '/^$$/ {exit 0} {gsub(/\\/,"\\\\\\\\");gsub(/&/,"\\\\\\\\&");gsub(/"/,"\\\"");gsub(/\47/,"\\\\047")} {if (NR>2) printf "\\\\n%s",$$0; else if (NR==2) printf "\#\# %s",$$0}' $(REVISION_FILE))
DIFF=$(shell $(AWK) 'BEGIN {flag=0} /^$$/ {flag=1} {if (flag>1) {gsub(/\\/,"\\\\\\\\");gsub(/&/,"\\\\\\\\&");gsub(/"/,"\\\"");gsub(/\47/,"\\\\047"); if (flag==2) {printf "%s",$$0; flag=3} else if (flag==3) printf"\\\\n%s",$$0} else if (flag==1) flag=2}' $(REVISION_FILE))

# rules

all: hash $(MAIN) $(TEXFILES) $(DOCUMENT)

rebuild: clean all

hash $(REVISION_FILE):
	@$(GIT) rev-parse 2> /dev/null && $(ECHO) $(NAME) $(VERSION) > $(REVISION_FILE) && $(GIT) rev-parse HEAD >> $(REVISION_FILE) && $(GIT) rev-parse --abbrev-ref HEAD >> $(REVISION_FILE) && $(GIT) status --porcelain >> $(REVISION_FILE) && $(ECHO) >> $(REVISION_FILE) && git diff >> $(REVISION_FILE) && $(ECHO) 'Generate hash' || $(ECHO) 'Using stored hash'
	@[ -e $(REVISION_FILE) ]

tar: hash $(NAME)_$(VERSION).tar.gz

clean:
	$(RM) -f $(DOCUMENT) $(DVIFILES)

cleanall: clean
	$(RM) -f */$(LOG) $(NAME)_*.tar.gz

.PHONY: all rebuild hash tar clean cleanall

.SECONDARY:

$(NAME)_$(VERSION).tar.gz: $(MANIFEST)
	$(RM) -f $(NAME)_*.tar.gz
	$(TAR) $(TFLAGS) $(NAME)_$(VERSION).tar.gz $(MANIFEST)

%.dvi: %.tex
	$(LATEX) $<

%.pdf: %.dvi
	$(DVIPDF) $<

