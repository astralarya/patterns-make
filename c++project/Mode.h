// Mode.h
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


#ifndef MODE_H
#define MODE_H

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "Type.h"

class Options;


/** \brief Base mode class */
class Mode {
public:
    /** Value list */
    typedef std::vector<std::string> svector_type;
    /** Variable and its value list */
    typedef std::pair<std::string,svector_type> svpair_type;
    /** Map of variabls to their value lists */
    typedef std::map<std::string,svector_type> type_map;
};

/** \brief Template class to encapsulate a mode and its type.  */
template <class ENUM>
class Typed_Mode: public Mode {
public:
    /** Only allow use by Options */
    friend class Options;
    /** The variable type */
    typedef ENUM var_type;
    /** The value type */
    typedef typename TypeInfo<ENUM>::val_type val_type;
    /** The value reference type */
    typedef typename TypeInfo<ENUM>::ref_type ref_type;
    /** The value vector type */
    typedef typename TypeInfo<ENUM>::vec_type vec_type;
    /** The value init type */
    typedef typename TypeInfo<ENUM>::init_type init_type;
    /** The variable to value map type */
    typedef typename TypeInfo<ENUM>::map_type map_type;
    /** The map init type */
    typedef typename TypeInfo<ENUM>::defaults_type defaults_type;
    /** The map of strings to variables type */
    typedef typename TypeInfo<ENUM>::key_type key_type;

protected:
    /** Initialize the mode using the
     *  key-valuelist pairs read from the options file.
     *  Initialize defaults and assign the value lists of
     *  key matches in properties using
     *  TypeInfo<ENUM>::assign(value_type& val, std::string& str).
     *  \param properties Map of strings to string vectors
     */
    Typed_Mode(const type_map& properties):
    _map(TypeInfo<ENUM>::defaults),
    _keys(TypeInfo<ENUM>::keys),
    _init(TypeInfo<ENUM>::init) {
        // for each key in this Mode
        std::for_each(_keys.begin(), _keys.end(),
                      [this, &properties] (const typename key_type::value_type& key) {
                          // look for key in properties
                          auto finder = properties.find(key.second);
                          if(finder != properties.end()) {
                              // read the strings
                              vec_type vector;
                              std::for_each(finder->second.begin(), finder->second.end(),
                                            [this, &vector] (const std::string& str) {
                                                val_type input = _init;
                                                // Assign value
                                                this->_assign(input,str);
                                                vector.push_back(input);
                                            });
                              if(vector.size() > _map[key.first].size())
                                  _map[key.first].resize(vector.size());
                              std::copy(vector.begin(), vector.end(), _map[key.first].begin());
                          }
                      });
    }

    /** Set the value of an index of key in this mode
     *  \param key The key being set
     *  \param index The index being set
     *  \param value The new value
     */
    void set(const ENUM& mode, size_t index, const val_type& value) {
        if(index >= _map[mode].size())
            _map[mode].resize(index+1,_init);
        _map[mode][index] = value;
    }

    /** Get the value of an index of key in this mode
     *  \param key The key being fetched
     *  \param index The index being fetched
     */
    ref_type get(const ENUM& mode, size_t index) {
        if(index >= _map[mode].size())
            _map[mode].resize(index+1,_init);
        return _map[mode][index];
    }


private:
    void _assign(val_type& var,const std::string& str) {
        TypeInfo<ENUM>::assign(var,str);
    }
    map_type _map;
    const key_type& _keys;
    const init_type& _init;
};

#endif // MODE_H
