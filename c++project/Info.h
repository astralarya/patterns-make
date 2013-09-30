// Info.h
// Mara Kim
//
// Globals with program information
// This file captures version info
// defined externally in the Makefile

#ifndef INFO_H
#define INFO_H

#include <iostream>

extern const char *const PROGRAM_NAME,
                  *const PROGRAM_VERSION,
                  *const REVISION_HASH,
                  *const REVISION_STATUS,
                  *const PROGRAM_BUG_ADDRESS;

void print_version(std::ostream& ostream = std::cout);
void print_revision(std::ostream& ostream = std::cout);
void print_version(FILE* stream);
void print_revision(FILE* stream);

#endif // INFO_H
