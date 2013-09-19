// OptionsScanner.h
// Scans the OPTIONS_FILE for words
//
// Mara Kim

#ifndef OPTIONSSCANNER_H
#define OPTIONSSCANNER_H

#include <iostream>
#include <cctype>

class OptionsScanner {
public:
    OptionsScanner(std::istream &in = std::cin):
    _istream(in),
    _matched(),
    _state(VAR) {}

    enum token {VARIABLE, VALUE, END};
    enum state {VAR, VAL};

    token lex();
    const std::string& matched() const;

private:
    std::istream& _istream;
    std::string _matched;
    state _state;
};

#endif // OPTIONSSCANNER_H
