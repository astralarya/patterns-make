// Info.cpp
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


/** \file Info.cpp
 * Initialize globals with program information.
 * Captures version information defined in the Makefile.
 */

#include "Info.h"
 
#ifndef __PROGRAM_NAME
/** Value of \$(EXECUTABLE) in Makefile */
#define __PROGRAM_NAME
#endif

#ifndef __PROGRAM_VERSION
/** Value of \$(VERSION) in Makefile */
#define __PROGRAM_VERSION
#endif

#ifndef __PROGRAM_LICENSE
/** Contents of file \$(LICENSE_FILE) defined in Makefile */
#define __PROGRAM_LICENSE
#endif

#ifndef __PROGRAM_BUG_ADDRESS
/** Value of \$(BUG_ADDRESS) in Makefile */
#define __PROGRAM_BUG_ADDRESS
#endif

#ifndef __REVISION_HASH
/** If compiled inside a git repository, the value of `git rev-parse HEAD` at compile time.
 *  Otherwise the last known value stored in file \$(REVISION_FILE) defined in Makefile.
 */
#define __REVISION_HASH
#endif

#ifndef __REVISION_STATUS
/** If compiled inside a git repository, the value of `git rev-parse --abbrev-ref HEAD` (with '## ' prefix)
 *  and `git status --porcelain` at compile time.
 *  Otherwise the last known value stored in file \$(REVISION_FILE) defined in Makefile.
 */
#define __REVISION_STATUS
#endif

#ifndef __REVISION_DIFF
/** If compiled inside a git repository, the value of `git diff` at compile time.
 *  Otherwise the last known value stored in file \$(REVISION_FILE) defined in Makefile.
 */
#define __REVISION_DIFF
#endif

#ifndef __OPTIONS_FILE
/** Value of \$(OPTIONS_FILE) in Makefile */
#define __OPTIONS_FILE
#endif

// Initialize with external macro
const char *const PROGRAM_NAME = __PROGRAM_NAME,
                 *PROGRAM_VERSION = __PROGRAM_VERSION,
                 *PROGRAM_LICENSE = __PROGRAM_LICENSE,
                 *PROGRAM_BUG_ADDRESS = __PROGRAM_BUG_ADDRESS,
                 *REVISION_HASH = __REVISION_HASH,
                 *REVISION_STATUS = __REVISION_STATUS,
                 *REVISION_DIFF = __REVISION_DIFF,
                 *OPTIONS_FILE = __OPTIONS_FILE;

void PRINT_VERSION(std::ostream& ostream, bool license) {
    ostream << PROGRAM_NAME << " " << PROGRAM_VERSION << "\n";
    if(license)
        ostream << PROGRAM_LICENSE << "\n";
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
            case 'V':
                version = true;
                break;
            case 'h':
            case 'H':
                hash = true;
                break;
            case 's':
            case 'S':
                status = true;
                break;
            case 'd':
            case 'D':
                diff = true;
                break;
            default:
                ;
            }
            c++;
        }
        PRINT_REVISION(ostream, version, hash, status, diff);
    } else
        PRINT_REVISION(ostream);
}

void PRINT_REVISION(std::ostream& ostream, bool version, bool hash, bool status, bool diff) {
    if(version)
        PRINT_VERSION(ostream,false);
    if(hash)
        ostream << REVISION_HASH;
    if(status)
        ostream << REVISION_STATUS;
    if(diff)
        ostream << REVISION_DIFF;

}

void PRINT_REVISION() {
    printf("%s %s\n%s%s%s",
        PROGRAM_NAME, PROGRAM_VERSION,
        REVISION_HASH,
        REVISION_STATUS,
        REVISION_DIFF);
}

void PRINT_VERSION(FILE* stream, bool license) {
    fputs(PROGRAM_NAME, stream);
    fputc(' ', stream);
    fputs(PROGRAM_VERSION, stream);
    fputc('\n', stream);
    if(license) {
        fputs(PROGRAM_LICENSE, stream);
        fputc('\n', stream);
    }
}

