// OptionsParser.h
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


#ifndef OPTIONSPARSER_H
#define OPTIONSPARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "Options.h"
#include "OptionsScanner.h"
#include "Mode.h"

class OptionsParser {
public:
    OptionsParser(Options& options, std::istream &in = std::cin):
    _options(options),_scanner(in){}

    int parse();

private:
    Options& _options;
    OptionsScanner _scanner;
    void error(char const *msg);    // called on (syntax) errors
};

#endif
