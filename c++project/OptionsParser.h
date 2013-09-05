// OptionsParser.h
// Parses the OPTIONSFILE and initializes Options
//
// Mara Kim

#ifndef OPTIONSparser_h
#define OPTIONSparser_h

#include <string>
#include <map>
#include "Options.h"
#include "Mode.h"

class OptionsParser
{
    public:
        OptionsParser(Options& options, std::istream &in = std::cin):
        _options(options),_istream(in){}

        int parse();

    private:
        std::istream& _istream;
        Options* _options;
        void error(char const *msg);    // called on (syntax) errors
};

#endif
