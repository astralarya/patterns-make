# sqlproject
# Mara Kim
#
# to commit, in a shell:
# make

# project specific

NAME=sqlproject
DBNAME=mydb
DBUSER=myuser
VERSION=0.0
LOG=commit.log

# environment specific

SQLEXT=.sql
LOGEXT=.log
DATE=date
PSQL=pqsl
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
MANIFEST=$(SQLFILES) $(COMMITFILES) $(LOG) $(ME)

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

.PHONY: commit tar clean cleanall edit

$(NAME)_$(VERSION).tar.gz: $(MANIFEST)
	$(RM) -f $(NAME)_*.tar.gz
	$(TAR) $(TFLAGS) $(NAME)_$(VERSION).tar.gz $(MANIFEST)

$(LOG): $(COMMITFILES)
	$(DATE) >> $(LOG)

.%$(LOGEXT): %
	$(PSQL) $(PFLAGS) $<
	$(DATE) > $@

