/*
 * Initializer.cpp
 *
 *      Author: mara
 */

#include "Initializer.h"

Initializer::Initializer(int argc, char** argv, const char* progdoc, const char* argdoc):
_argc(argc),
_argv(argv),
_arg_opts(),
_arg_funcs(),
_argp() {
    _argp.options = _arg_opts.data();
    _argp.parser = _funcall;
    _argp.doc = progdoc;
    _argp.args_doc = argdoc;
}

void Initializer::option(const char* longflag, const int shortflag, const char* argument, const char* doc,
                         optFunc function,
                         const bool hidden, const bool arg_optional) {
    argp_option opt;
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
                    const bool hidden, const bool arg_optional) {
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

void Initializer::parse() {
    error_t status = argp_parse(&_argp,_argc,_argv,0,0,0);
    perror("");
}

Initializer::~Initializer() {
    // dtor
}

