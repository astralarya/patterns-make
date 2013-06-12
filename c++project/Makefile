# Mara Kim
#
# to compile, in a shell:
# make

# project specific

EXECUTABLE=myprog
VERSION=0.1
CFLAGS=-std=c++0x -g
LDFLAGS=
DOXFILE=
OPTIONSFILE=$(EXECUTABLE).options
REVISION_FILE=VERSION.log
MISC=README.md

# environment specific

CXX=g++
LEX=flexc++
YACC=bisonc++
DOX=doxygen
TAR=tar
TFLAGS=-pczf
NANO=vim
FF=firefox
RM=rm
ECHO=echo
DOXINDEX=./html/index.html
ME=Makefile

# macros

LEXFILE=$(wildcard *.l)
YACCFILE=$(wildcard *.y)
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:.cpp=.o) $(GENERATEDC:.cc=.o)
DEPENDENCIES=$(OBJECTS:.o=.d)
EXTRA=$(LEXFILE:.l=Scanner.h) $(LEXFILE:.l=Scanner.ih) $(YACCFILE:.y=Parser.h) $(YACCFILE:.y=Parser.ih) $(YACCFILE:.y=.types.h)
GENERATEDH=$(LEXFILE:.l=Scannerbase.h) $(YACCFILE:.y=Parserbase.h)
GENERATEDC=$(LEXFILE:.l=Scanner.cc) $(YACCFILE:.y=Parser.cc)
MANIFEST=$(SOURCES) $(HEADERS) $(LEXFILE) $(YACCFILE) $(EXTRA) $(DOXFILE) $(OPTIONSFILE) $(REVISION_FILE) $(MISC) $(ME)

# rules

all: $(MAIN) $(SOURCES) $(HEADERS) $(LEXFILE) $(YACCFILE) $(EXTRA) $(EXECUTABLE)

again: hash all

rebuild: clean hash all

name:
	@$(ECHO) $(EXECUTABLE)

hash $(REVISION_FILE):
	@$(GIT) rev-parse && $(GIT) rev-parse HEAD > $(REVISION_FILE) && $(GIT) status -sb >> $(REVISION_FILE) && $(ECHO) 'Generate hash' || $(ECHO) 'Using stored hash'
	@[ -e $(REVISION_FILE) ]

tar: hash $(MANIFEST)
	$(TAR) $(TFLAGS) $(EXECUTABLE)_$(VERSION).tar.gz $(MANIFEST)

dox: $(DOXINDEX)
	$(FF) $(DOXINDEX)

doxbuild:
	$(DOX) $(DOXFILE)	

edit:
	$(NANO) $(ME)

clean:
	$(RM) -rf $(OBJECTS) $(DEPENDENCIES) $(GENERATEDH) $(GENERATEDC) $(EXECUTABLE)

cleanall: clean
	$(RM) -rf $(EXECUTABLE)*.tar.gz html latex *~

.PHONY: all again rebuild name hash tar dox doxbuild edit clean cleanall


$(EXECUTABLE): $(GENERATEDH) $(GENERATEDC) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(DOXINDEX): $(MAIN) $(SOURCES) $(HEADERS) $(GENERATED)
	$(DOX) $(DOXFILE)	

# pull in dependency info for *existing* .o files
-include $(DEPENDENCIES)

main.o: main.cpp $(REVISION_FILE)
	$(CXX) $(CFLAGS) -c $< -o $@ -D PROGRAM_NAME='"$(EXECUTABLE)"' -D SOURCE_VERSION='"$(VERSION)"' -D REVISION_HASH='"$(REVISION)"'
	$(CXX) -MM $(CFLAGS) $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@
	$(CXX) -MM $(CFLAGS) $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

%.o: %.c
	$(CXX) $(CFLAGS) -c $< -o $@
	$(CXX) -MM $(CFLAGS) $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

%.o: %.cc
	$(CXX) $(CFLAGS) -c $< -o $@
	$(CXX) -MM $(CFLAGS) $*.cc > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

%Parser.cc: %.y
	$(YACC) $(YACCFLAGS) $<

%Scanner.cc: %.l
	$(LEX) $(LEXFLAGS) $<

%Parserbase.h: %.y
	$(YACC) $(YACCFLAGS) $<

%Scannerbase.h: %.l
	$(LEX) $(LEXFLAGS) $<
