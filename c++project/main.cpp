// main.cpp
// Mara Kim
//
// A main function that reports help and version info


#include "Initializer.h"
#include "Options.h"
#include "Foo.h"
#include <iostream>


inline void printshorthelp()
{
    // output usage info
    std::cout <<  "<Description>\n"
                  "Usage: " PROGRAM_NAME "\n";
}

void printhelp()
{
    // output help
    printshorthelp();
    std::cout << "Option\t\tGNU long option\t\tMeaning\n"
                 "-f\t\t--foo\t\t\tRun the program\n"
                 "-h, -?\t\t--help\t\t\tShow this message\n"
                 "-v\t\t--version\t\tOutput program version\n"
                 "-V\t\t--version-long\t\tOutput full program version\n";
}

void printversion()
{
    std::cout << PROGRAM_NAME " " SOURCE_VERSION "\n";
}

void printrevision()
{
    std::cout << REVISION_HASH "\n"
                 REVISION_STATUS "\n";
}

int main(int argc, const char* argv[])
{

    // Initialize
    Initializer init(argc, argv);

    // process arguments
    if(init.noargs()) {
        printshorthelp();
        std::cout << "Try --help\n";
        return 0;
    }
    bool stop = false;
    if(init.flag("version") ||
       init.flag('v') ) {
        // output version
        printversion();
        stop = true;
    }
    if(init.flag("version-long") ||
       init.flag('V') ) {
        // output revision
        printversion();
        printrevision();
        stop = true;
    }
    if(init.flag("help") ||
       init.flag('h') ||
       init.flag('?')) {
        printhelp();
        stop = true;
    }

    if(stop) {
        return 0;
    }


    // run program

    Foo foo;
    foo.bar();

    return 0;
}
