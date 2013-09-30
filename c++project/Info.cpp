// Info.cpp
// Mara Kim
//
// Globals with program information

#include "Info.h"

// Initialize with external macro
const char *const program_name = __PROGRAM_NAME,
           *const program_version = __PROGRAM_VERSION,
           *const program_description = __PROGRAM_DESCRIPTION,
           *const revision_hash = __REVISION_HASH,
           *const revision_status = __REVISION_STATUS,
           *const program_bug_address = __PROGRAM_BUG_ADDRESS;

void print_version(std::ostream& ostream) {
    ostream << program_name << " " << program_version << "\n";
}

void print_revision(std::ostream& ostream) {
    ostream << revision_hash << "\n"
            << revision_status << "\n";
}

void print_version(FILE* stream) {
    fputs(program_name, stream);
    fputc(' ', stream);
    fputs(program_version, stream);
    fputc('\n', stream);
}

void print_revision(FILE* stream) {
    fputs(revision_hash , stream);
    fputc('\n', stream);
    fputs(revision_status , stream);
    fputc('\n', stream);
}
