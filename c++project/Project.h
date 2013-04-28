// Project.h
// Mara Kim
//
// Globals to be included with Options.h

#include "Mode.h"

#ifndef PROJECT_H
#define PROJECT_H

// Options Filename
static const char* const OPTIONSFILE = "test.options";

// Typed Enums
enum string_mode{DB_HOST,DB_USER,DB_NAME};
template <>
struct Type<string_mode> {
    typedef std::string T;
};

enum float_mode{AVOGADRO};
template <>
struct Type<float_mode> {
    typedef float T;
};

#endif

#ifdef MAIN_CPP
/// Static Declarations ///

// Mode Signitures
template <>
typename TypeInfo<string_mode>::key_type TypeInfo<string_mode>::keys ({{DB_HOST, "DB_HOST"},{DB_USER,"DB_USER"},{DB_NAME,"DB_NAME"}});

template <>
typename TypeInfo<float_mode>::key_type TypeInfo<float_mode>::keys ({{AVOGADRO, "AVOGADRO_CONSTANT"}});

#endif


