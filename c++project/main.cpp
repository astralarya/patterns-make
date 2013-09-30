// main.cpp
// Mara Kim
//
// A main function that reports help and version info


#include "Initializer.h"
#include "Options.h"
#include "Foo.h"
#include <iostream>

void printwelcome() {
    // Welcome
    std::cout << "\n<Welcome>\n\n";
}

const char* program_name = PROGRAM_NAME;
const char* program_version = SOURCE_VERSION;

void printrevision() {
    std::cout << PROGRAM_NAME " " SOURCE_VERSION "\n"
                 REVISION_HASH "\n"
                 REVISION_STATUS "\n";
}

int main(int argc, char** argv) {
    // Initialize
    Initializer init(argc, argv, "A barebones c++ project", "ARG1 ARG2");

    // process arguments
    bool stop = true;
    init.option("foo", 'f', 0, "Run the program",
                [&] (char* c, Initializer::state* s) {
                    stop = false;
                });
    init.option("version-long", 'V', 0, "Output full program version",
                [&] (char* c, Initializer::state* s) {
                    // output revision
                    printrevision();
                },false,true);
    init.parse();

    if(stop)
        return 0;
    else
        printwelcome();


    // run program

    std::cout << Options::Instance()->get(Project::GREETING) << std::endl;

    Foo foo;
    foo.bar();

    return 0;
}
