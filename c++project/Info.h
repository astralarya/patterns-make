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

void PRINT_VERSION(std::ostream& ostream = std::cout);
void PRINT_REVISION(std::ostream& ostream = std::cout);
void PRINT_VERSION(FILE* stream);
void PRINT_REVISION(FILE* stream);

#endif // INFO_H
