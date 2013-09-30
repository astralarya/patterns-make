// Info.cpp
// Globals with program information
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


#include "Info.h"

// Initialize with external macro
const char *const PROGRAM_NAME = __PROGRAM_NAME,
           *const PROGRAM_VERSION = __PROGRAM_VERSION,
           *const PROGRAM_BUG_ADDRESS = __PROGRAM_BUG_ADDRESS,
           *const REVISION_HASH = __REVISION_HASH,
           *const REVISION_STATUS = __REVISION_STATUS,
           *const REVISION_DIFF = __REVISION_DIFF;

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
        PRINT_REVISION(version,hash,status,diff);
    } else
        PRINT_REVISION();
}

void PRINT_REVISION(bool version, bool hash, bool status, bool diff, std::ostream& ostream) {
    if(version)
        PRINT_VERSION(ostream);
    if(hash)
        ostream << REVISION_HASH;
    if(status)
        ostream << REVISION_STATUS;
    if(diff)
        ostream << REVISION_DIFF;

}

void PRINT_VERSION(FILE* stream) {
    fputs(PROGRAM_NAME, stream);
    fputc(' ', stream);
    fputs(PROGRAM_VERSION, stream);
    fputc('\n', stream);
}

