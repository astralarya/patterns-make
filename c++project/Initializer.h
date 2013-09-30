// Initializer.h
// Parses command line arguments
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


#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#include <argp.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include "Info.h"

class Initializer {
public:
    typedef argp_state state;
    typedef std::function<int (char*,state*)> optFunc;
    typedef std::function<int ()> simpleOptFunc;
    typedef std::function<int (char*)> argOptFunc;
    enum event_t { ARG = ARGP_KEY_ARG, ARGS = ARGP_KEY_ARGS,
                   END = ARGP_KEY_END, NO_ARGS = ARGP_KEY_NO_ARGS,
                   INIT = ARGP_KEY_INIT, SUCCESS = ARGP_KEY_SUCCESS,
                   ERROR = ARGP_KEY_ERROR, FINI = ARGP_KEY_FINI };
    enum signal_t { GOOD = 0, UNKNOWN = ARGP_ERR_UNKNOWN };

    Initializer(int argc, char** argv, const char* argdoc = 0, const char* progdoc = 0);
    virtual ~Initializer();
    // Define options -- functions called for each option
    void option(const char* longflag, const int shortflag, const char* argument, const char* doc, optFunc function,
                const bool arg_optional = false, const bool hidden = false);
    void option(const std::vector<const char*>& longflags, const std::vector<int>& shortflags,
                const char* argument, const char* doc, optFunc function,
                const bool arg_optional = false, const bool hidden = false); /*
    void option(const char* longflag, const int shortflag, const char* argument, const char* doc, simpleOptFunc function,
                const bool hidden = false, const bool arg_optional = false);
    void option(const char* longflag, const int shortflag, const char* argument, const char* doc, argOptFunc function,
                const bool hidden = false, const bool arg_optional = false); */
    // Define argument functions -- called for each command line argument
    void event(event_t e, optFunc function);

    // Parse the arguments
    void parse();

    // hook to key handlers
    int argp_funcall(int key, char* arg, state* state);
    // Hook to print version
    static void print_version(FILE* stream, argp_state* state);
    // Print usage and exit
    void print_usage(state* state);
private:
    int _argc;
    char** _argv;
    std::vector<argp_option> _arg_opts;
    std::map<int, optFunc> _arg_funcs;
    argp _argp;
};

#endif /* INITIALIZER_H_ */
