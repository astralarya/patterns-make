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
#include <functional>
#include <map>

class Initializer {
public:
    typedef argp_state state;
    typedef std::function<void (char*,state*)> optFunc;
    typedef std::function<void ()> simpleOptFunc;
    typedef std::function<void (char*)> argOptFunc;

    Initializer(int argc, char** argv, const char* progdoc = 0, const char* argdoc = 0);
    virtual ~Initializer();
    void option(const char* longflag, const int shortflag, const char* argument, const char* doc, optFunc function,
                const bool arg_optional = false, const bool hidden = false);
    /*
    void option(const char* longflag, const int shortflag, const char* argument, const char* doc, simpleOptFunc function,
                const bool hidden = false, const bool arg_optional = false);
    void option(const char* longflag, const int shortflag, const char* argument, const char* doc, argOptFunc function,
                const bool hidden = false, const bool arg_optional = false);
    */
    void option(const std::vector<const char*>& longflags, const std::vector<int>& shortflags,
                const char* argument, const char* doc, optFunc function,
                const bool arg_optional = false, const bool hidden = false);
    void parse();

    int argp_funcall(int key, char* arg, state* state);
private:
    int _argc;
    char** _argv;
    std::vector<argp_option> _arg_opts;
    std::map<int, optFunc> _arg_funcs;
    argp _argp;
};

#endif /* INITIALIZER_H_ */
