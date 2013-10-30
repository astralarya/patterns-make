# c++project
# a Makefile to manage a c++ project
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

# to compile, in a shell:
# make


# project specific

NAME=c++project
VERSION=0.5
BUG_ADDRESS=hacker.root@gmail.com
CFLAGS=-std=gnu++0x -Wall -O3 -pedantic -Weffc++
LDFLAGS=
DOXFILE=Doxyfile
OPTIONS_FILE=OPTIONS.rc
REVISION_FILE=VERSION.log
LICENSE_FILE=LICENSE.txt
MISC=logo.svg README.md .gitignore

# environment specific

GIT=git
SED=sed
AWK=awk
PRINTF=printf
TAR=tar
CXX=g++
DOX=doxygen
MV=mv
RM=rm
NANO=vim
FF=firefox
DOXINDEX=./html/index.html
ME=Makefile

# macros

EXECUTABLE=$(NAME)
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:.cpp=.o) $(GENERATEDC:.cc=.o)
DEPENDENCIES=$(OBJECTS:.o=.d)
EXTRA=
GENERATEDH=
GENERATEDC=
MANIFEST=$(SOURCES) $(HEADERS) $(EXTRA) $(DOXFILE) $(OPTIONS_FILE) $(REVISION_FILE) $(LICENSE_FILE) $(MISC) $(ME)
LICENSE=$(shell $(AWK) '{gsub(/["\\]/,"\\\\&");gsub(/\47/,"\\047")} {if (NR==1) printf "%s",$$0; else printf "\\n%s",$$0}' $(LICENSE_FILE))
GIT_HASH=$(shell $(AWK) 'NR==1 {printf "%s\\n",$$0}' $(REVISION_FILE))
GIT_STATUS=$(shell $(AWK) '/^$$/ {exit 0} {gsub(/["\\]/,"\\\\&");gsub(/\47/,"\\047")} {if (NR>2) printf "%s\\n",$$0; else if (NR==2) printf "\#\# %s\\n",$$0}' $(REVISION_FILE))
GIT_DIFF=$(shell $(AWK) 'BEGIN {flag=0} /^$$/ {flag=1} {if (flag==2) {gsub(/["\\]/,"\\\\&");gsub(/\47/,"\\047"); printf "%s\\n",$$0} else if (flag==1) flag=2}' $(REVISION_FILE))

# rules

build: hash $(MAIN) $(SOURCES) $(HEADERS) $(EXTRA) $(EXECUTABLE)

help:
	@$(PRINTF) '%b\n'\
	 '\n$(EXECUTABLE) $(VERSION)\n'\
	 'make build		- build project'\
	 'make clean		- delete generated files'\
	 'make rebuild		- clean and build'\
	 'make tar		- package project'\
	 'make dox		- generate and view documentation'\
	 ''\

rebuild: clean build

name:
	@$(PRINTF) '$(EXECUTABLE)\n'

hash $(REVISION_FILE):
	@$(GIT) rev-parse 2> /dev/null && $(GIT) rev-parse HEAD > $(REVISION_FILE) &&\
	 $(GIT) rev-parse --abbrev-ref HEAD >> $(REVISION_FILE) &&\
	 $(GIT) status --porcelain >> $(REVISION_FILE) && $(PRINTF) '\n' >> $(REVISION_FILE) &&\
	 $(GIT) diff >> $(REVISION_FILE) && $(PRINTF) 'Generate hash\n' || $(PRINTF) 'Using stored hash\n'
	@[ -e $(REVISION_FILE) ]

tar: hash $(MANIFEST)
	$(TAR) --transform 's,^,$(NAME)_$(VERSION)/,' -pczf $(NAME)_$(VERSION).tar.gz $(MANIFEST)

dox: $(DOXINDEX)
	$(FF) $(DOXINDEX)

doxbuild:
	$(DOX) $(DOXFILE)	

clean:
	$(RM) -rf $(OBJECTS) $(DEPENDENCIES) $(GENERATEDH) $(GENERATEDC) $(EXECUTABLE)

cleanall: clean
	$(RM) -rf $(EXECUTABLE)*.tar.gz html latex *~

.PHONY: all rebuild name hash tar dox doxbuild clean cleanall


$(EXECUTABLE): $(GENERATEDH) $(GENERATEDC) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(DOXINDEX): $(MAIN) $(SOURCES) $(HEADERS) $(GENERATED)
	$(DOX) $(DOXFILE)	

# pull in dependency info for *existing* .o files
-include $(DEPENDENCIES)

# Compile info into executable
Info.o: Info.cpp $(REVISION_FILE)
	$(CXX) $(CFLAGS) -c $< -o $@ -D __PROGRAM_NAME='"$(EXECUTABLE)"' -D __PROGRAM_VERSION='"$(VERSION)"' -D __REVISION_HASH='"$(GIT_HASH)"' -D __REVISION_STATUS='"$(GIT_STATUS)"' -D __REVISION_DIFF='"$(GIT_DIFF)"' -D __PROGRAM_BUG_ADDRESS='"$(BUG_ADDRESS)"' -D __PROGRAM_LICENSE='"$(LICENSE)"' -D __OPTIONS_FILE='"$(OPTIONS_FILE)"'
	@$(CXX) -MM $(CFLAGS) $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@
	@$(CXX) -MM $(CFLAGS) $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

%.o: %.c
	$(CXX) $(CFLAGS) -c $< -o $@
	@$(CXX) -MM $(CFLAGS) $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

%.o: %.cc
	$(CXX) $(CFLAGS) -c $< -o $@
	@$(CXX) -MM $(CFLAGS) $*.cc > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

