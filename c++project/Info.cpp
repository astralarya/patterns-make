// Info.cpp
// Mara Kim
//
// Globals with program information

#include "Info.h"

const char* const program_name = PROGRAM_NAME,
          * const program_version = PROGRAM_VERSION,
          * const revision_hash = REVISION_HASH,
          * const revision_status = REVISION_STATUS;

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
