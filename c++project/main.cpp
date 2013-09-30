// main.cpp
// Mara Kim
//
// A main function that reports help and version info

#include "Info.h"
#include "Initializer.h"
#include "Options.h"
#include "Foo.h"
#include <iostream>


int main(int argc, char** argv) {
    // Initialize
    // argcount, argvector, description, argument usage
    Initializer init(argc, argv, "A barebones C++ project", "ARG0 ARG1");

    // Describe options
    init.option("revision", 'V', 0, "Output revision",
                [&] (char* c, Initializer::state* s) -> int {
                    // output revision
                    print_version();
                    print_revision();
                    exit(0);
                },false,true);
    init.option("foo", 'f', "MYFOO", "Set MYFOO",
                [&] (char* arg, Initializer::state* s) -> int {
                    if(arg)
                        Options::Instance()->set(Project::FOO,arg);
                    return 0;
                },true);
    init.option("switch", 's', 0, "Set SWITCH = true",
                [&] (char* arg, Initializer::state* s) -> int {
                    Options::Instance()->set(Project::SWITCH,true);
                    return 0;
                },true);
    init.event(Initializer::ARG,
               [&] (char* arg, Initializer::state* state) -> int {
                   if(state->arg_num >= 2)
                       return Initializer::UNKNOWN;
                   Options::Instance()->set(Project::ARGUMENTS,state->arg_num,arg);
                   return 0;
               });

    // Parse arguments
    init.parse();

    // Welcome
    std::cout << "\nBarebones c++ Project:\n\n";

    // run program

    std::cout << Options::Instance()->get(Project::GREETING) << std::endl;

    std::cout << "MYFOO=" << Options::Instance()->get(Project::FOO) << std::endl;
    std::cout << "SWITCH=" << (Options::Instance()->get(Project::SWITCH)?"true":"false") << std::endl;
    std::cout << "ARG0=" << Options::Instance()->get(Project::ARGUMENTS,0) << std::endl;
    std::cout << "ARG1=" << Options::Instance()->get(Project::ARGUMENTS,1) << std::endl;
    Foo foo;
    foo.bar();

    return 0;
}
