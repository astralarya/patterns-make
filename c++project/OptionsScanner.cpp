// OptionsScanner.cpp
// Scans the OPTIONS_FILE for words
//
// Mara Kim

#include "OptionsScanner.h"

OptionsScanner::token OptionsScanner::lex() {
    // clear last matched
    _matched.clear();

    // Read next token
    int c;
    c = _istream.get();
    while(isspace(c)) {
        if(c == '\n')
            _state = VAR;
        c = _istream.get();
    }
    switch(c) {
    //case '"':
    case EOF:
        return END;
    default:
        while(!isspace(c) && c != EOF) {
            _matched.push_back(c);
            c = _istream.get();
        }
    }

    // Transition state and return
    if(_state == VAR) {
        _state = VAL;
        return VARIABLE;
    } else {
        if(c == '\n')
            _state = VAR;
        return VALUE;
    }
}

const std::string& OptionsScanner::matched() const {
    return _matched;
}
