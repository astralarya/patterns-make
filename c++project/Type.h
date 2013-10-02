// Type.h
// Associate one type with another
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


#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <sstream>
#include <vector>
#include <map>

/** \brief Template type class to associate enums with types */
template <class ENUM>
struct Type {
    /** The type of values associated with keys of type ENUM */
    typedef void T;
};

/** \brief Template class that dependently defines typedefs and functions
  *        based on Type<ENUM> */
template <typename ENUM>
struct TypeInfo {
    /** The type of values associated with keys of type ENUM */
    typedef typename Type<ENUM>::T val_type;
    /** Value type reference */
    typedef typename std::vector<typename Type<ENUM>::T>::reference ref_type;
    /** Vector of values */
    typedef typename std::vector<typename Type<ENUM>::T> vec_type;
    /** Map of variables to vectors of values */
    typedef std::map<ENUM,std::vector<typename Type<ENUM>::T> > map_type;
    /** Const map of variables to vectors of values */
    typedef const std::map<ENUM,std::vector<typename Type<ENUM>::T> > defaults_type;
    /** Const map of variables to strings */
    typedef const std::map<ENUM,std::string> key_type;
    /** Const value */
    typedef const typename Type<ENUM>::T init_type;

    /** Initialize val_type using input string str.
     *  \param val The value being initialized
     *  \param str The input string
     */
    static void assign(val_type& val, const std::string& str) {
        std::stringstream(str) >> val;
    }

    /** Static map of variables to string keys.
     *  Used by Typed_Mode<ENUM> during initialization to
     *  read values from the OPTIONS_FILE */
    static key_type keys;

    /** Static map of variables to value vectors
     *  Used by Typed_Mode<ENUM> during initialization to
     *  set the default values of the defined variables */
    static defaults_type defaults;

    /** Static value type.
     *  Used by Typed_Mode<ENUM> as the default values of
     *  indexes that have not been previously set. */
    static init_type init;
};

#endif // TYPE_H
