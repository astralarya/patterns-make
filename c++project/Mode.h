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
    virtual void _initialize(const type_map&) = 0;
    
};

// Template mode class
template <class ENUM>
class Typed_Mode: public Mode {
public:
    friend class MetaOptions;
    friend class Options;
    typedef ENUM my_enum;
    typedef typename Type<ENUM>::T my_type;
    typedef typename TypeInfo<ENUM>::init_type init_type;
    typedef typename TypeInfo<ENUM>::map_type map_type;
    typedef typename TypeInfo<ENUM>::defaults_type defaults_type;
    typedef typename TypeInfo<ENUM>::key_type key_type;

protected:
    // ctors
    Typed_Mode():
    map(),
    keys(TypeInfo<ENUM>::keys),
    defaults(TypeInfo<ENUM>::defaults),
    init(TypeInfo<ENUM>::init) {};

    map_type map;
    key_type& keys;
    defaults_type& defaults;
    init_type& init;

    // accessor functions
    void set(const ENUM& mode, size_t index, const typename Type<ENUM>::T& value)
    {
        if(index >= map[mode].size())
            map[mode].resize(index+1,init);
        map[mode][index] = value;
    }

    typename TypeInfo<ENUM>::ref_type get(const ENUM& mode, size_t index)
    {
        if(index >= map[mode].size())
            map[mode].resize(index+1,init);
        return map[mode][index];
    }

    // initializer
    void _initialize(const type_map& properties) {
        // for each key
        for(auto it = keys.begin(); it != keys.end(); it++) {
            if(!it->second.empty()) {
                // look for key
                auto finder = properties.find(it->second);
                if(finder != properties.end()) {
                    std::stringstream ss;
                    // copy the strings
                    if(finder->second.size()) {
                        for(auto reader = finder->second.begin(); reader != finder->second.end(); reader++) {
                            ss << *reader;
                            my_type input;
                            // use the insertion operator to set the variable
                            ss >> input;
                            map[it->first].push_back(input);
                            ss.str().clear();
                        }
                    } 
                }
            }
            _set_default(it->first);
        }
    }
private:
    inline void _set_default(ENUM mode) {
        auto def = defaults.find(mode);
        if(def != defaults.end())
            if(def->second.size() > map[mode].size())
                for(auto it = def->second.begin() + map[mode].size(); it != def->second.end(); it++)
                    map[mode].push_back(*it);
    }
};

#endif // MODE_H
