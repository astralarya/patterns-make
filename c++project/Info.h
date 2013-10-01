// Info.h
//
// Copyright (C) 2013 Mara Kim
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see http://www.gnu.org/licenses/.


/** \file Info.h
 * Globals with program information
 * Captures version information defined in the Makefile
 */
#ifndef INFO_H
#define INFO_H

#include <iostream>

extern const char *const PROGRAM_NAME, /**< The name of the program */
                        *PROGRAM_VERSION, /**< The version number of this executable */
                        *PROGRAM_LICENSE, /**< The program license printed with '--version' */
                        *PROGRAM_BUG_ADDRESS, /**< The email address for bug reports about this program */
                        *REVISION_HASH, /**< The hexedecimal git object name of the current HEAD */
                        *REVISION_STATUS, /**< The paths that have differences between
                                               the index file and the current HEAD commit  */
                        *REVISION_DIFF; /**< The changes between the working tree and the index */

void PRINT_VERSION(std::ostream& ostream = std::cout, bool license = false);
void PRINT_REVISION(char* arg, std::ostream& ostream = std::cout);
void PRINT_REVISION(std::ostream& ostream = std::cout, bool version = true, bool hash = true, bool status = true, bool diff = true);
void PRINT_VERSION(FILE* stream);
void PRINT_REVISION(FILE* stream);

#endif // INFO_H
