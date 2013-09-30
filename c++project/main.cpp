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
    Initializer init(argc, argv, "ARG0 ARG1",
                     "A Barebones C++ Project\v"
                     "Be sure to provide two non-option arguments!");

    // Describe options
    init.option(0, '#', "FILTER", 0, // output revision hash
                [&] (char* arg, Initializer::state* state) -> int {
                    PRINT_REVISION(arg);
                    exit(0);
                },true,true);
    init.option("foo", 'f', "MYFOO", "Set MYFOO",
                [&] (char* arg, Initializer::state* s) -> int {
                    if(arg)
                        Options::Instance()->set(Project::FOO,arg);
                    return 0;
                });
    init.option("switch", 's', 0, "Set SWITCH = true",
                [&] (char* arg, Initializer::state* s) -> int {
                    Options::Instance()->set(Project::SWITCH,true);
                    return 0;
                });
    init.event(Initializer::ARG, // Handle arguments
               [&] (char* arg, Initializer::state* state) -> int {
                   if(state->arg_num >= 2)
                       return Initializer::UNKNOWN;
                   Options::Instance()->set(Project::ARGUMENTS,state->arg_num,arg);
                   return 0;
               });
    init.event(Initializer::END, // Check argument count
               [&] (char* arg, Initializer::state* state) -> int {
                   if(state->arg_num < 2)
                       init.print_usage(state);
                   return 0;
               });

    // Parse arguments
    init.parse();

    // run program

    std::cout << "\nBegin Example:\n\n";

    std::cout << Options::Instance()->get(Project::GREETING) << std::endl;
    std::cout << "MYFOO=" << Options::Instance()->get(Project::FOO) << std::endl;
    std::cout << "SWITCH=" << (Options::Instance()->get(Project::SWITCH)?"true":"false") << std::endl;
    std::cout << "ARG0=" << Options::Instance()->get(Project::ARGUMENTS,0) << std::endl;
    std::cout << "ARG1=" << Options::Instance()->get(Project::ARGUMENTS,1) << std::endl;
    Foo foo;
    foo.bar();

    return 0;
}
