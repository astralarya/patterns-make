// Project.h
// Mara Kim
//
// Globals to be included with Options.h


#ifndef PROJECT_H
#define PROJECT_H

#include "Mode.h"

// Typed modes
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

template<>
struct Type<char> {
    typedef bool T;
};

#endif


#ifdef PROJECT_STATICS
/// Static Declarations ///

// Mode Signitures
template <>
typename TypeInfo<string_mode>::key_type TypeInfo<string_mode>::keys ({{DB_HOST, "DB_HOST"},{DB_USER,"DB_USER"},{DB_NAME,"DB_NAME"}});
template <>
typename TypeInfo<string_mode>::defaults_type TypeInfo<string_mode>::defaults {};
template <>
typename TypeInfo<string_mode>::init_type TypeInfo<string_mode>::init {};

template <>
typename TypeInfo<float_mode>::key_type TypeInfo<float_mode>::keys ({{AVOGADRO, "AVOGADRO_CONSTANT"}});
template <>
typename TypeInfo<float_mode>::defaults_type TypeInfo<float_mode>::defaults {};
template <>
typename TypeInfo<float_mode>::init_type TypeInfo<float_mode>::init = 0;

template <>
typename TypeInfo<char>::key_type TypeInfo<char>::keys {};
template <>
typename TypeInfo<char>::defaults_type TypeInfo<char>::defaults {};
template <>
typename TypeInfo<char>::init_type TypeInfo<char>::init = false;

#endif

