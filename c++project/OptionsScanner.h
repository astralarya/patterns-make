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

/** Tokenizes an input stream
 *  into variables and values
 */
class OptionsScanner {
public:
    /** Initialize the scanner
     *  \param istream The input stream
     */
    OptionsScanner(std::istream &istream = std::cin):
    _istream(in),
    _matched(),
    _state(VAR) {}

    /** Tokens recognized by the scanner */
    enum token { VARIABLE, /**< A variable */
                 VALUE, /**< A value */
                 END /**< EOF */
               }; 

    /** Scanner states */
    enum state { VAR, /**< Scanning a variable */
                 VAL /**< Scanning a value */
               };

    /** Scan for the next token in the stream
     *  \return The matched token
     */
    token lex();

    /** Get the matched text
     *  \return The text matched by the last call to lex().
     */
    const std::string& matched() const;

private:
    std::istream& _istream;
    std::string _matched;
    state _state;
};

#endif // OPTIONSSCANNER_H
