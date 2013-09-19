// Mode.h
// Mara Kim
//
// A class to encapsulate a mode and its type
// A mode is any enumerator
// A type is any type that supports copy and
//   std::istream::operator>>
// Use Type<ENUM> to associate types


#ifndef MODE_H
#define MODE_H

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "Type.h"

class Options;


// Base mode class
class Mode {
public:
    typedef std::vector<std::string> svector_type;
    typedef std::pair<std::string,svector_type> svpair_type;
    typedef std::map<std::string,svector_type> type_map;
    virtual void _initialize(const type_map&) = 0;
    
};

// Template mode class
template <class ENUM>
class Typed_Mode: public Mode {
public:
    friend class MetaOptions;
    friend class Options;
    typedef ENUM my_enum;
    typedef typename TypeInfo<ENUM>::my_type my_type;
    typedef typename TypeInfo<ENUM>::ref_type ref_type;
    typedef typename TypeInfo<ENUM>::vec_type vec_type;
    typedef typename TypeInfo<ENUM>::init_type init_type;
    typedef typename TypeInfo<ENUM>::map_type map_type;
    typedef typename TypeInfo<ENUM>::defaults_type defaults_type;
    typedef typename TypeInfo<ENUM>::key_type key_type;

protected:
    // ctors
    Typed_Mode():
    _map(),
    _keys(TypeInfo<ENUM>::keys),
    _defaults(TypeInfo<ENUM>::defaults),
    _init(TypeInfo<ENUM>::init) {};


    // accessor functions
    void set(const ENUM& mode, size_t index, const my_type& value) {
        if(index >= _map[mode].size())
            _map[mode].resize(index+1,_init);
        _map[mode][index] = value;
    }

    ref_type get(const ENUM& mode, size_t index) {
        if(index >= _map[mode].size())
            _map[mode].resize(index+1,_init);
        return _map[mode][index];
    }

    // initializer
    void _initialize(const type_map& properties) {
        // set defaults
        for(auto it = _defaults.begin(); it != _defaults.end(); it++)
            _map[it->first] = it->second;

        // for each key
        for(auto it = _keys.begin(); it != _keys.end(); it++) {
            if(!it->second.empty()) {
                // look for key
                auto finder = properties.find(it->second);
                if(finder != properties.end()) {
                    std::stringstream ss;
                    // copy the strings
                    if(finder->second.size()) {
                        vec_type vector;
                        for(auto reader = finder->second.begin(); reader != finder->second.end(); reader++) {
                            ss << *reader;
                            my_type input;
                            // use the extraction operator to set the variable
                            ss >> input;
                            vector.push_back(input);
                            ss.str().clear();
                        }
                        if(vector.size() > _map[it->first].size())
                            _map[it->first].resize(vector.size());
                        std::copy(vector.begin(), vector.end(), _map[it->first].begin());
                    } 
                }
            }
        }
    }

private:
    map_type _map;
    key_type& _keys;
    defaults_type& _defaults;
    init_type& _init;
};

#endif // MODE_H
