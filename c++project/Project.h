// Project.h
// Mara Kim
//
// Globals to be included with Options.h


#ifndef PROJECT_H
#define PROJECT_H

#include "Mode.h"

// Project enums
namespace Project {
    enum string_mode{GREETING,DB_HOST,DB_USER,DB_NAME,ARGUMENTS,FOO};
    enum float_mode{AVOGADRO, NUMBERS};
    enum bool_mode{SWITCH};
}

// Typed modes
template <>
struct Type<Project::string_mode> {
    typedef std::string T;
};

template <>
struct Type<Project::float_mode> {
    typedef float T;
};

template <>
struct Type<Project::bool_mode> {
    typedef bool T;
};

template<>
struct Type<char> {
    typedef bool T;
};

#endif


#ifdef PROJECT_STATICS
/// Static Declarations ///

using namespace Project;

// Mode Signitures
template <>
typename TypeInfo<string_mode>::key_type TypeInfo<string_mode>::keys ({{GREETING, "GREETING"},{DB_HOST, "DB_HOST"},{DB_USER,"DB_USER"},{DB_NAME,"DB_NAME"}});
template <>
typename TypeInfo<string_mode>::defaults_type TypeInfo<string_mode>::defaults {{DB_HOST,{"A_DATABASE"}},{FOO,{"FOO!"}}};
template <>
typename TypeInfo<string_mode>::init_type TypeInfo<string_mode>::init {};
template <>
void TypeInfo<string_mode>::assign(std::string& var, const std::string& str) { var = str; }

template <>
typename TypeInfo<float_mode>::key_type TypeInfo<float_mode>::keys ({{AVOGADRO, "AVOGADRO_CONSTANT"},{NUMBERS, "NUMBERS"}});
template <>
typename TypeInfo<float_mode>::defaults_type TypeInfo<float_mode>::defaults {};
template <>
typename TypeInfo<float_mode>::init_type TypeInfo<float_mode>::init = 0;

template <>
typename TypeInfo<bool_mode>::key_type TypeInfo<bool_mode>::keys {};
template <>
typename TypeInfo<bool_mode>::defaults_type TypeInfo<bool_mode>::defaults {};
template <>
typename TypeInfo<bool_mode>::init_type TypeInfo<bool_mode>::init = false;

template <>
typename TypeInfo<char>::key_type TypeInfo<char>::keys {};
template <>
typename TypeInfo<char>::defaults_type TypeInfo<char>::defaults {{'c',{true}}};
template <>
typename TypeInfo<char>::init_type TypeInfo<char>::init = false;

#endif

