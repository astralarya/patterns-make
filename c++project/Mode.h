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
    // ctor
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
                                                my_type input = _init;
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


private:
    void _assign(my_type& var,const std::string& str) {
        TypeInfo<ENUM>::assign(var,str);
    }
    map_type _map;
    const key_type& _keys;
    const init_type& _init;
};

#endif // MODE_H
