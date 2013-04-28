# sqlproject
# a Makefile to manage a sql repository for database
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

NAME=sqlproject
DBNAME=mydb
DBUSER=myuser
VERSION=0.0
LOG=commit.log
MISC=README.md

# environment specific

SQLEXT=.sql
LOGEXT=.log
DATE=date
PSQL=psql
PFLAGS=-U $(DBUSER) $(DBNAME) -f
TAR=tar
TFLAGS=-pczf
NANO=vim
RM=rm
ME=Makefile

# macros

SQLFILES=$(wildcard *$(SQLEXT))
COMMITFILES=$(addprefix .,$(SQLFILES:$(SQLEXT)=$(LOGEXT)))
GENERATED=$(COMMITFILES)
MANIFEST=$(SQLFILES) $(COMMITFILES) $(LOG) $(MISC) $(ME)

# rules

all: commit

commit: $(LOG)

tar: $(NAME)_$(VERSION).tar.gz

clean:
	$(RM) -f $(GENERATED)

cleanall: clean
	$(RM) -f $(LOG) $(NAME)_*.tar.gz

edit:
	$(NANO) $(ME)

.PHONY: all commit tar clean cleanall edit

$(NAME)_$(VERSION).tar.gz: $(MANIFEST)
	$(RM) -f $(NAME)_*.tar.gz
	$(TAR) $(TFLAGS) $(NAME)_$(VERSION).tar.gz $(MANIFEST)

$(LOG): $(COMMITFILES)
	$(DATE) >> $(LOG)

.%$(LOGEXT): %$(SQLEXT)
	$(PSQL) $(PFLAGS) $<
	$(DATE) > $@

