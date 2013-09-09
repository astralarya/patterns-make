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
DEVDB=mydbdev
LIVEDB=mydb
DBS=$(DEVDB) $(LIVEDB)
DBUSER=myuser
VERSION=0.0
REVISION_FILE=VERSION.log
MISC=README.md

# environment specific

VERSIONSQL=version.sql
LOG=commit.log
DATE=date
PSQL=psql
PFLAGS=-U $(DBUSER)
GIT=git
TAR=tar
TFLAGS=-pczf
NANO=vim
SED=sed
TR=tr
HEAD=head
TAIL=tail
ECHO=echo
GREP=grep
TEE=tee
MKDIR=mkdir
RM=rm
ME=Makefile

# macros

SQLFILES=$(wildcard *.sql)
COMMITFILES=$(SQLFILES:.sql=.log)
MANIFEST=$(SQLFILES) $(REVISION_FILE) $(MISC) $(ME)
HASH=$(shell $(HEAD) -n 1 $(REVISION_FILE))
STATUS=\#\# $(shell $(TAIL) -n +2 $(REVISION_FILE) | $(SED) -e 's/\\/\\\\/g' -e 's/"/\\"/g' -e 's/\o047/\\047/g' -e '$$ ! s/$$/\\n/' | $(TR) -d '\n')

# rules

dev: $(DEVDB)

all: $(DBS)

live: $(LIVEDB)

hash $(REVISION_FILE):
	@$(GIT) rev-parse 2> /dev/null && $(GIT) rev-parse HEAD > $(REVISION_FILE) && $(GIT) rev-parse --abbrev-ref HEAD >> $(REVISION_FILE) && $(GIT) status --porcelain >> $(REVISION_FILE) && git diff --minimal >> $(REVISION_FILE) && $(ECHO) 'Generate hash' || $(ECHO) 'Using stored hash'
	@[ -e $(REVISION_FILE) ]

tar: hash $(NAME)_$(VERSION).tar.gz

clean:
	$(RM) -f $(addprefix */,$(COMMITFILES))

cleanall: clean
	$(RM) -f */$(LOG) $(NAME)_*.tar.gz

.PHONY: all dev live hash tar clean cleanall

.SECONDARY:

$(NAME)_$(VERSION).tar.gz: $(MANIFEST)
	$(RM) -f $(NAME)_*.tar.gz
	$(TAR) $(TFLAGS) $(NAME)_$(VERSION).tar.gz $(MANIFEST)

$(foreach DB,$(DBS),$(DB).db/$(VERSIONSQL:.sql=.log)): $(VERSIONSQL) $(REVISION_FILE)
	@$(ECHO) $<
	@$(DATE) > $@
	@$(SED) -e 's/DB_NAME/$(LIVEDB)/g' -e 's/DB_VERSION/$(VERSION)/' -e 's/DB_HASH/$(HASH)/' -e 's/DB_STATUS/$(STATUS)/' $< | $(PSQL) $(PFLAGS) -d $(@:.db/$(VERSIONSQL:.sql=.log)=) &>> $@
	@$(GREP) ": " $@ || true

%.db/$(LOG): hash %.db $(addprefix %.db/,$(COMMITFILES))
	@$(DATE) >> $@
	@$(ECHO) Commit $*
	@$(RM) -f $*.db/version.log

define db_commit
$(1).db/%.log: %.sql
	@$$(ECHO) $$<
	@$$(DATE) > $$@
	@$$(PSQL) $$(PFLAGS) -d $$(@:.db/$$*.log=) -f $$< &>> $$@
	@$$(GREP) ": " $$@ || true
endef

$(foreach DB,$(DBS),$(eval $(call db_commit,$(DB))))

%.db:
	$(MKDIR) -p $*.db

%: %.db/$(LOG)
	@$(ECHO) Done $*

