// OptionsParser.cpp
// Mara Kim

#include "OptionsParser.h"

int OptionsParser::parse() {
    Mode::type_map param;

    bool done = false;
    std::string variable;
    while(!done) {
        switch(_scanner.lex()) {
        case OptionsScanner::VARIABLE:
            variable = _scanner.matched();
            break;
        case OptionsScanner::VALUE:
            param[variable].push_back(_scanner.matched());
            break;
        default:
            done = true;
        }
    }

    // Initialize Options
    _options._new(param);
    return 0;
}

inline void OptionsParser::error(char const *msg) {
    std::cerr << msg << '\n';
}

