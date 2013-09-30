// OptionsScanner.h
// Scans the OPTIONS_FILE for variables and values
//
// Copyright (C) 2013 Mara Kim
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see http://www.gnu.org/licenses/.


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
