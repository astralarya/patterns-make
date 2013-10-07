// Project.h
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


/** \file Project.h
 *  Globals defining option types
 */

#ifndef PROJECT_H
#define PROJECT_H

#include "Mode.h"

/** Project enums */
namespace Project {
    enum string_mode{GREETING,DB_HOST,DB_USER,DB_NAME,ARGUMENTS,FOO};
    enum float_mode{AVOGADRO, NUMBERS, MYNUM};
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
bool TypeInfo<string_mode>::assign(std::string& var, const std::string& str) { var = str; return var==str; }

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

