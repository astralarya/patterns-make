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
AWK=awk
ECHO=echo
GREP=grep
TEE=tee
MKDIR=mkdir
RM=rm
ME=Makefile

# macros

SQLFILES=$(wildcard *.sql)
COMMITFILES=$(SQLFILES:.sql=.log)
MANIFEST=$(SQLFILES) $(REVISION_FILE) $(ME)
HASH=$(shell $(AWK) 'NR==1 {printf "%s",$$0}' $(REVISION_FILE))
STATUS=$(shell $(AWK) '/^$$/ {exit 0} {gsub(/\\/,"\\\\\\\\");gsub(/&/,"\\\\\\\\&");gsub(/"/,"\\\"");gsub(/\47/,"\\\\047")} {if (NR>2) printf "\\\\n%s",$$0; else if (NR==2) printf "\#\# %s",$$0}' $(REVISION_FILE))
DIFF=$(shell $(AWK) 'BEGIN {flag=0} /^$$/ {flag=1} {if (flag>1) {gsub(/\\/,"\\\\\\\\");gsub(/&/,"\\\\\\\\&");gsub(/"/,"\\\"");gsub(/\47/,"\\\\047"); if (flag==2) {printf "%s",$$0; flag=3} else if (flag==3) printf"\\\\n%s",$$0} else if (flag==1) flag=2}' $(REVISION_FILE))

# rules

dev: $(DEVDB)

all: $(DBS)

live: $(LIVEDB)

hash $(REVISION_FILE):
	@$(GIT) rev-parse 2> /dev/null && $(GIT) rev-parse HEAD > $(REVISION_FILE) && $(GIT) rev-parse --abbrev-ref HEAD >> $(REVISION_FILE) && $(GIT) status --porcelain >> $(REVISION_FILE) && $(ECHO) >> $(REVISION_FILE) && git diff >> $(REVISION_FILE) && $(ECHO) 'Generate hash' || $(ECHO) 'Using stored hash'
	@[ -e $(REVISION_FILE) ]

tar: hash $(MANIFEST)
	$(TAR) --transform 's,^,$(NAME)_$(VERSION)/,' -pczf $(NAME)_$(VERSION).tar.gz $(MANIFEST)

clean:
	$(RM) -f $(addprefix */,$(COMMITFILES))

cleanall: clean
	$(RM) -f */$(LOG) $(NAME)_*.tar.gz

.PHONY: all dev live hash tar clean cleanall

.SECONDARY:

$(foreach DB,$(DBS),$(DB).db/$(VERSIONSQL:.sql=.log)): $(VERSIONSQL) $(REVISION_FILE)
	@$(ECHO) $<
	@$(DATE) > $@
	@$(AWK) '{gsub(/__DB_VERSION/,"$(VERSION)"); gsub(/__DB_HASH/,"$(HASH)"); gsub(/__DB_STATUS/,"$(STATUS)"); gsub(/__DB_DIFF/,"$(DIFF)"); print}' $< | $(PSQL) --quiet $(PFLAGS) -d $(@:.db/$(VERSIONSQL:.sql=.log)=) 2>&1 | $(TEE) -a $@ && $(ECHO) "RECORD VERSION"

%.db/$(LOG): hash %.db $(addprefix %.db/,$(COMMITFILES))
	@$(DATE) >> $@
	@$(ECHO) Commit $*
	@$(RM) -f $*.db/version.log

define db_commit
$(1).db/%.log: %.sql
	@$$(ECHO) $$<
	@$$(DATE) > $$@
	@$$(PSQL) $$(PFLAGS) -d $$(@:.db/$$*.log=) -f $$< 2>&1 | $$(TEE) -a $$@
endef

$(foreach DB,$(DBS),$(eval $(call db_commit,$(DB))))

%.db:
	$(MKDIR) -p $*.db

%: %.db/$(LOG)
	@$(ECHO) Done $*


