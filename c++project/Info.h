// Info.h
// Mara Kim
//
// Globals with program information
// This file captures version info
// defined externally in the Makefile

#ifndef INFO_H
#define INFO_H

#include <iostream>

extern const char *const program_name,
                  *const program_version,
                  *const revision_hash,
                  *const revision_status,
                  *const program_bug_address;

void print_version(std::ostream& ostream = std::cout);
void print_revision(std::ostream& ostream = std::cout);
void print_version(FILE* stream);
void print_revision(FILE* stream);

#endif // INFO_H
