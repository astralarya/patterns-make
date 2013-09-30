# Mara Kim
#
# to compile, in a shell:
# make

# project specific

EXECUTABLE=myprog
VERSION=0.1
BUG_ADDRESS=hacker.root@gmail.com
CFLAGS=-std=gnu++0x -g
LDFLAGS=
DOXFILE=
OPTIONS_FILE=OPTIONS.rc
REVISION_FILE=VERSION.log
MISC=README.md .gitignore

# environment specific

GIT=git
SED=sed
TR=tr
ECHO=echo
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

SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:.cpp=.o) $(GENERATEDC:.cc=.o)
DEPENDENCIES=$(OBJECTS:.o=.d)
EXTRA=
GENERATEDH=
GENERATEDC=
MANIFEST=$(SOURCES) $(HEADERS) $(EXTRA) $(DOXFILE) $(OPTIONS_FILE) $(REVISION_FILE) $(MISC) $(ME)
GIT_HASH=$(shell $(SED) -e '2,$$d' $(REVISION_FILE))\n
GIT_STATUS=\#\# $(shell $(SED) -e '1,1d' -e '/^$$/,$$d' -e 's/\\/\\\\/g' -e 's/"/\\"/g' -e 's/\o047/\\047/g' -e '$$ ! s/$$/\\n/' $(REVISION_FILE) | $(TR) -d '\n')
GIT_DIFF=$(shell $(SED) -e '1,1d' -e '1,/^$$/d' -e 's/\\/\\\\/g' -e 's/"/\\"/g' -e 's/\o047/\\047/g' -e '$$ ! s/$$/\\n/' $(REVISION_FILE) | $(TR) -d '\n')

# rules

all: hash $(MAIN) $(SOURCES) $(HEADERS) $(LEXFILE) $(YACCFILE) $(EXTRA) $(EXECUTABLE)

rebuild: clean all

name:
	@$(ECHO) $(EXECUTABLE)

hash $(REVISION_FILE):
	@$(GIT) rev-parse 2> /dev/null && $(GIT) rev-parse HEAD > $(REVISION_FILE) && $(GIT) rev-parse --abbrev-ref HEAD >> $(REVISION_FILE) && $(GIT) status --porcelain >> $(REVISION_FILE) && echo >> $(REVISION_FILE) && git diff >> $(REVISION_FILE) && echo >> $(REVISION_FILE) && $(ECHO) 'Generate hash' || $(ECHO) 'Using stored hash'
	@[ -e $(REVISION_FILE) ]

tar: hash $(MANIFEST)
	$(TAR) --transform 's,^,$(EXECUTABLE)_$(VERSION)/,' -pczf $(EXECUTABLE)_$(VERSION).tar.gz $(MANIFEST)

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

Info.o: Info.cpp $(REVISION_FILE)
	$(CXX) $(CFLAGS) -c $< -o $@ -D __PROGRAM_NAME='"$(EXECUTABLE)"' -D __PROGRAM_VERSION='"$(VERSION)"' -D __REVISION_HASH='"$(GIT_HASH)"' -D __REVISION_STATUS='"$(GIT_STATUS)"' -D __REVISION_DIFF='"$(GIT_DIFF)"' -D __PROGRAM_BUG_ADDRESS='"$(BUG_ADDRESS)"'
	@$(CXX) -MM $(CFLAGS) $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

Options.o: Options.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ -D OPTIONS_FILE='"$(OPTIONS_FILE)"'
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

