// main.cpp
// Mara Kim

#ifndef PROGRAM_NAME
#define PROGRAM_NAME
#endif
#ifndef SOURCE_VERSION
#define SOURCE_VERSION
#endif
#ifndef REVISION_HASH
#define REVISION_HASH
#endif
#ifndef REVISION_STATUS
#define REVISION_STATUS
#endif

#include "Initializer.h"
#include "Options.h"
#include "Foo.h"
#include <iostream>


inline void printshorthelp()
{
    // output usage info
    std::cout << "Usage: " << PROGRAM_NAME << '\n';
}

void printhelp()
{
    // output help
    printshorthelp();
    std::cout << "<Description>\n"
                 "Option\t\tGNU long option\t\tMeaning\n"
                 "-h, -?\t\t--help\t\t\tShow this message\n"
                 "-v\t\t--version\t\tOutput program version\n"
                 "-V\t\t--version-long\t\tOutput full program version\n";
}

void printversion()
{
    std::cout << PROGRAM_NAME << ' ' << SOURCE_VERSION << '\n';
}

void printrevision()
{
    std::cout << REVISION_HASH << '\n'
              << REVISION_STATUS << '\n';
}

int main(int argc, const char* argv[])
{

    // Initialize
    Initializer init(argc, argv);

    // process arguments
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
