/*
 * Initializer.h
 *
 *      Author: mara
 */

#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#include <argp.h>
#include <stdio.h>
#include <vector>
#include <map>

class Initializer {
public:
    typedef argp_state state;
    typedef void (*optFunc)(char*,state*);

    Initializer(int argc, char** argv, const char* progdoc = 0, const char* argdoc = 0);
    virtual ~Initializer();
    void option(const char* longflag, const int shortflag, const char* argument, const char* doc, optFunc function,
                const bool hidden = false, const bool arg_optional = false);
    void option(const std::vector<const char*>& longflags, const std::vector<int>& shortflags,
                const char* argument, const char* doc, optFunc function,
                const bool hidden = false, const bool arg_optional = false);
    void parse();
private:
    static int _funcall(int key, char* arg, state* state);
    int _argc;
    char** _argv;
    std::vector<argp_option> _arg_opts;
    std::map<int, optFunc> _arg_funcs;
    argp _argp;
};

#endif /* INITIALIZER_H_ */
