// OptionsParser.cpp
// Parses the OPTIONS_FILE and initializes Options
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

