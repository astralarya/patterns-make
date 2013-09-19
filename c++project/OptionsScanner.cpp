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
    int last = 0;
    switch(c) {
    case EOF:
        return END;
    case '"':
        c = _istream.get();
        while((c != '"' || last == '\\') && c != EOF) {
            if(c != '\\' || last == '\\')
                _matched.push_back(c);
            last = c;
            c = _istream.get();
        }
        break;
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
