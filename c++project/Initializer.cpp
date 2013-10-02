// Initializer.cpp
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


#include "Initializer.h"

extern "C" {
    int Initializer_argp_funcall(int key, char* arg, struct argp_state *state) {
        return ((Initializer*)state->input)->argp_funcall(key, arg, state);
    }
}

void Initializer_argp_program_version_hook(FILE* stream, argp_state* state) {
    // Global PRINT_VERSION defined in Info.h
    PRINT_VERSION(stream);
}

void (*argp_program_version_hook) (FILE *stream, struct argp_state *state) = Initializer_argp_program_version_hook;

const char* argp_program_bug_address = PROGRAM_BUG_ADDRESS;


Initializer::Initializer(int argc, char** argv, const char* argdoc, const char* progdoc):
_argc(argc),
_argv(argv),
_arg_opts(),
_arg_funcs(),
_argp() {
    // Initialize Argp parser
    _argp.parser = Initializer_argp_funcall;
    _argp.args_doc = argdoc;
    _argp.doc = progdoc;

    // Define -# option to retrieve detailed version info
    option(0, '#', "FILTER", 0, // output revision hash
           [&] (char* arg, Initializer::state* state) -> int {
               PRINT_REVISION(arg);
               exit(0);
           },true,true);
}

Initializer::~Initializer() {
    // dtor
}

void Initializer::option(const char* longflag, const int shortflag, const char* argument, const char* doc,
                         optFunc function,
                         const bool arg_optional, const bool hidden) {
    struct argp_option opt = {0};
    opt.name = longflag;
    opt.key = shortflag;
    opt.arg = argument;
    opt.doc = doc;
    if(arg_optional)
        opt.flags = opt.flags | OPTION_ARG_OPTIONAL;
    if(hidden)
        opt.flags = opt.flags | OPTION_HIDDEN;
    _arg_opts.push_back(opt);
    _arg_funcs[opt.key] = function;
}

void Initializer::option(const std::vector<const char*>& longflags, const std::vector<int>& shortflags,
                         const char* argument, const char* doc, optFunc function,
                         const bool arg_optional, const bool hidden) {
    struct argp_option opt = {0};
    bool first = true;
    auto long_it = longflags.begin();
    auto short_it = shortflags.begin();
    while(long_it != longflags.end() || short_it != shortflags.end()) {
        argp_option opt;
        if(long_it != longflags.end())
            opt.name = *long_it;
        if(short_it != shortflags.end())
            opt.key = *short_it;
        if(first) {
            first = false;
            opt.arg = argument;
            opt.doc = doc;
            if(arg_optional)
                opt.flags = opt.flags | OPTION_ARG_OPTIONAL;
            if(hidden)
                opt.flags = opt.flags | OPTION_HIDDEN;
            _arg_funcs[opt.key] = function;
        } else
            opt.flags = opt.flags | OPTION_ALIAS;
        _arg_opts.push_back(opt);

        // Increment
        if(long_it != longflags.end())
            long_it++;
        if(short_it != shortflags.end())
            short_it++;
    }
}

void Initializer::event(event_t event, optFunc function) {
    _arg_funcs[event] = function;
}

error_t Initializer::parse() {
    struct argp_option opt = {0};
    _arg_opts.push_back(opt);
    _argp.options = _arg_opts.data();
    error_t status = argp_parse(&_argp,_argc,_argv,ARGP_IN_ORDER,0,this);
    if(status)
        perror("argp_parse():");
    _arg_opts.pop_back();
    return status;
}

int Initializer::argp_funcall(int key, char* arg, state* state) {
    auto finder = _arg_funcs.find(key);
    if(finder != _arg_funcs.end())
        return finder->second(arg,state);
    else
        return UNKNOWN;
}

void Initializer::print_usage(state* state) {
    argp_usage(state);
}
