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

FULLCFLAGS=$(CFLAGS) -D'PROGRAM_NAME="$(EXECUTABLE)"' -D'SOURCE_VERSION="$(VERSION)"' -D'OPTIONSFILE="$(OPTIONSFILE)"'
LEXFILE=$(wildcard *.l)
YACCFILE=$(wildcard *.y)
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:.cpp=.o) $(GENERATEDC:.cc=.o)
DEPENDENCIES=$(OBJECTS:.o=.d)
EXTRA=$(LEXFILE:.l=Scanner.h) $(LEXFILE:.l=Scanner.ih) $(YACCFILE:.y=Parser.h) $(YACCFILE:.y=Parser.ih) $(YACCFILE:.y=.types.h)
GENERATEDH=$(LEXFILE:.l=Scannerbase.h) $(YACCFILE:.y=Parserbase.h)
GENERATEDC=$(LEXFILE:.l=Scanner.cc) $(YACCFILE:.y=Parser.cc)
MANIFEST=$(SOURCES) $(HEADERS) $(LEXFILE) $(YACCFILE) $(EXTRA) $(DOXFILE) $(OPTIONSFILE) $(MISC) $(ME)

# rules

all: $(MAIN) $(SOURCES) $(HEADERS) $(LEXFILE) $(YACCFILE) $(EXTRA) $(EXECUTABLE)

rebuild: clean all

name:
	$(ECHO) $(EXECUTABLE)

tar: $(MANIFEST)
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

.PHONY: all rebuild name tar dox doxbuild edit clean cleanall



$(EXECUTABLE): $(GENERATEDH) $(GENERATEDC) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(DOXINDEX): $(MAIN) $(SOURCES) $(HEADERS) $(GENERATED)
	$(DOX) $(DOXFILE)	

# pull in dependency info for *existing* .o files
-include $(DEPENDENCIES)

%.o: %.cpp
	$(CXX) $(FULLCFLAGS) -c $< -o $@
	$(CXX) -MM $(FULLCFLAGS) $*.cpp > $*.d

%.o: %.c
	$(CXX) $(FULLCFLAGS) -c $< -o $@
	$(CXX) -MM $(FULLCFLAGS) $*.c > $*.d

%.o: %.cc
	$(CXX) $(FULLCFLAGS) -c $< -o $@
	$(CXX) -MM $(FULLCFLAGS) $*.cc > $*.d

%Parser.cc: %.y
	$(YACC) $(YACCFLAGS) $<

%Scanner.cc: %.l
	$(LEX) $(LEXFLAGS) $<

%Parserbase.h: %.y
	$(YACC) $(YACCFLAGS) $<

%Scannerbase.h: %.l
	$(LEX) $(LEXFLAGS) $<
