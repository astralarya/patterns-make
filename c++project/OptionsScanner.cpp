// OptionsScanner.cpp
// Scans the OPTIONS_FILE for words
//
// Mara Kim

#include "OptionsScanner.h"

OptionsScanner::token OptionsScanner::lex() {
    // clear last matched
    _matched.clear();

    // Read next token
    int c = _istream.get();
    int last = 0;
    bool done = false;
    while(!done) {
        while(isspace(c)) {
            if(c == '\n')
                _state = VAR;
            c = _istream.get();
        }
        switch(c) {
        case EOF:
            return END;
        case '/':
            if(_istream.peek() == '*') {
                // C-style multiline comment
                _istream.get();
                c = _istream.get();
                while(c != '/' && last != '*' && c != EOF) {
                    last = c;
                    c = _istream.get();
                }
                c = _istream.get();
            } else if(_istream.peek() == '/') {
                while(c != '\n')
                    c = _istream.get();
                _state = VAR;
            } else {
                _matched.push_back(c);
                c = _istream.get();
            }
            break;
        case '"':
            // Read quoted string
            c = _istream.get();
            while((c != '"' || last == '\\') && c != EOF) {
                if(c != '\\' || last == '\\')
                    _matched.push_back(c);
                last = c;
                c = _istream.get();
            }
            done = true;
            break;
        default:
            // Read word
            while(!isspace(c) && c != EOF) {
                if(c == '/' && (_istream.peek() == '*' || _istream.peek() == '/')) {
                    _istream.putback(c);
                    break;
                }
                _matched.push_back(c);
                c = _istream.get();
            }
            done = true;
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
