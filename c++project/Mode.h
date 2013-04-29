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
#include "Type.h"

class Options;


// Base mode class
class Mode {
public:
    friend class Options;
    typedef std::vector<std::string> svector_type;
    typedef std::pair<std::string,svector_type> svpair_type;
    typedef std::map<std::string,svector_type> type_map;
    virtual void _initialize(type_map&) = 0;
    
};

// Template mode class
template <class ENUM>
class Typed_Mode: public Mode {
public:
    friend class MetaOptions;
    friend class Options;
    typedef ENUM my_enum;
    typedef typename Type<ENUM>::T my_type;
    typedef typename TypeInfo<ENUM>::map_type map_type;
    typedef typename TypeInfo<ENUM>::key_type key_type;

protected:
    // ctors
    Typed_Mode():
    map(),
    keys(TypeInfo<ENUM>::keys),
    defaults(TypeInfo<ENUM>::defaults),
    init(TypeInfo<ENUM>::init) {};

    map_type map;
    key_type keys;
    map_type defaults;
    my_type init;

    // accessor functions
    void set(ENUM mode, typename Type<ENUM>::T value)
    {
        map[mode] = value;
    }

    typename Type<ENUM>::T get(ENUM mode)
    {
        return map[mode];
    }

    // initializer
    void _initialize(type_map& properties) {
        for(auto it = keys.begin(); it != keys.end(); it++) {
            if(!it->second.empty()) {
                auto finder = properties.find(it->second);
                if(finder != properties.end()) {
                    std::stringstream ss;
                    // copy the string
                    ss << finder->second[0];
                    my_type input;
                    // use the insertion operator to set the variable
                    ss >> input;
                    map[it->first] = input;
                } else {
                    _set_default(it->first);
                }
            }
        }
    }
private:
    inline void _set_default(ENUM mode) {
        auto def = defaults.find(mode);
        if(def != defaults.end())
            map[mode] = defaults[mode];
        else
            map[mode] = init;
    }
};

#endif // MODE_H
