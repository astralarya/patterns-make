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
 * Define globals with program information.
 * Exposes the values captured from the Makefile
 */
#ifndef INFO_H
#define INFO_H

#include <iostream>

extern const char *const PROGRAM_NAME, /**< The name of the program. */
                        *PROGRAM_VERSION, /**< The version number of this executable. */
                        *PROGRAM_LICENSE, /**< The program license printed with '--version'. */
                        *PROGRAM_BUG_ADDRESS, /**< The email address for bug reports about this program. */
                        *REVISION_HASH, /**< The hexedecimal git object name of the current HEAD. */
                        *REVISION_STATUS, /**< The paths that have differences between
                                               the working directory and the current HEAD commit.  */
                        *REVISION_DIFF; /**< The changes between the working directory and the index. */

/** Print the version string
 *  (ie. PROGRAM_NAME + ' ' + PROGRAM_VERSION)
 *  \param ostream The output stream
 *  \param license Also print the PROGRAM_LICENSE
 */
void PRINT_VERSION(std::ostream& ostream = std::cout, bool license = true);

/** Print the version string and license info
 *  Called by GNU Argp
 *  \param stream The output stream
 *  \param license Also print the PROGRAM_LICENSE
 */
void PRINT_VERSION(FILE* stream, bool license = true);


/** Print revision info
 *  \param ostream The output stream
 *  \param version Print the version string
 *  \param hash Print the revision hash 
 *  \param status Print the revision status
 *  \param diff Print the diff of the working directory
 */
void PRINT_REVISION(std::ostream& ostream = std::cout, bool version = true, bool hash = true, bool status = true, bool diff = true);

/** Parse argument and print corresponding revision info.
 *  If arg is null, print all fields,
 *  otherwise look for the following characters and print the respective fields:    
 *  - [Vv] - print version
 *  - [Hh] - print hash
 *  - [Ss] - print status
 *  - [Dd] - print diff
 *  \param arg The flags specifying which fields to print
 *  \param ostream The output stream
 */
void PRINT_REVISION(char* arg, std::ostream& ostream = std::cout);

#endif // INFO_H
