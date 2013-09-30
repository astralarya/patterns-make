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
    Initializer init(argc, argv, "A barebones C++ project", "ARG1 ARG2");

    // process arguments
    bool stop = true;
    init.option("foo", 'f', 0, "Run the program",
                [&] (char* c, Initializer::state* s) {
                    stop = false;
                });
    init.option("revision", 'V', 0, "Output revision",
                [&] (char* c, Initializer::state* s) {
                    // output revision
                    print_version();
                    print_revision();
                },false,true);
    init.parse();

    if(stop)
        return 0;

    // Welcome
    std::cout << "\nBarebones c++ Project:\n\n";

    // run program

    std::cout << Options::Instance()->get(Project::GREETING) << std::endl;

    Foo foo;
    foo.bar();

    return 0;
}
