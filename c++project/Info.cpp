// Info.cpp
// Mara Kim
//
// Globals with program information

#include "Info.h"

// Initialize with external macro
const char *const PROGRAM_NAME = __PROGRAM_NAME,
           *const PROGRAM_VERSION = __PROGRAM_VERSION,
           *const REVISION_HASH = __REVISION_HASH,
           *const REVISION_STATUS = __REVISION_STATUS,
           *const REVISION_DIFF = __REVISION_DIFF,
           *const PROGRAM_BUG_ADDRESS = __PROGRAM_BUG_ADDRESS;

void PRINT_VERSION(std::ostream& ostream) {
    ostream << PROGRAM_NAME << " " << PROGRAM_VERSION << "\n";
}

void PRINT_REVISION(char* arg, std::ostream& ostream) {
    bool version = false,
         hash = false,
         status = false,
         diff = false;
    if(arg) {
        char *c = arg;
        while(*c) {
            switch(*c) {
            case 'v':
                version = true;
                break;
            case 'h':
                hash = true;
                break;
            case 's':
                status = true;
                break;
            case 'd':
                diff = true;
                break;
            default:
                ;
            }
            c++;
        }
        PRINT_REVISION(version,hash,status,diff);
    } else
        PRINT_REVISION();
}

void PRINT_REVISION(bool version, bool hash, bool status, bool diff, std::ostream& ostream) {
    if(version)
        PRINT_VERSION(ostream);
    if(hash)
        ostream << REVISION_HASH << "\n";
    if(status)
        ostream << REVISION_STATUS;
    if(diff)
        ostream << REVISION_DIFF << "\n";

}

void PRINT_VERSION(FILE* stream) {
    fputs(PROGRAM_NAME, stream);
    fputc(' ', stream);
    fputs(PROGRAM_VERSION, stream);
    fputc('\n', stream);
}

