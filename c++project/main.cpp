// main.cpp
// A main function that reports help and version info 
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


#include "Info.h"
#include "Initializer.h"
#include "Options.h"
#include "Foo.h"
#include <iostream>

int main(int argc, char** argv) {
    // Initialize
    // argcount, argvector, argument usage, description
    Initializer init(argc, argv, "ARG0 ARG1",
                     "A Barebones C++ Project\v"
                     "Be sure to provide two non-option arguments!");

    // Describe options
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
                       Initializer::print_usage(state);
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
