/*
 * Initializer.cpp
 *
 *      Author: mara
 */

#include "Initializer.h"

extern "C" int Initializer_argp_funcall(int key, char* arg, struct argp_state *state) {
    return ((Initializer*)state->input)->argp_funcall(key, arg, state);
}

void Initializer::print_version(FILE* stream, argp_state* state) {
    // Global print_version defined in Info.h
    ::print_version(stream);
}

void (*argp_program_version_hook) (FILE *stream, struct argp_state *state) = Initializer::print_version;

const char* argp_program_bug_address = program_bug_address;


Initializer::Initializer(int argc, char** argv, const char* progdoc, const char* argdoc):
_argc(argc),
_argv(argv),
_arg_opts(),
_arg_funcs(),
_argp() {
    _argp.parser = Initializer_argp_funcall;
    _argp.doc = progdoc;
    _argp.args_doc = argdoc;
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

void Initializer::event(event_t e, optFunc function) {
    _arg_funcs[e] = function;
}

void Initializer::parse() {
    struct argp_option opt = {0};
    _arg_opts.push_back(opt);
    _argp.options = _arg_opts.data();
    error_t status = argp_parse(&_argp,_argc,_argv,0,0,this);
    if(status)
        perror("argp_parse():");
}

int Initializer::argp_funcall(int key, char* arg, state* state) {
    auto finder = _arg_funcs.find(key);
    if(finder != _arg_funcs.end())
        return finder->second(arg,state);
    else
        return ARGP_ERR_UNKNOWN;
}

void Initializer::print_usage(state* state) {
    argp_usage(state);
}
