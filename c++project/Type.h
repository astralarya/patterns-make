// Type.h
// Mara Kim
//
// Associate one type with another

#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <vector>
#include <map>

// Type class to associate enums with types
template <class ENUM>
struct Type {
    typedef void T;
};

// Type info
template <typename ENUM>
struct TypeInfo {
    typedef std::map<ENUM,std::vector<typename Type<ENUM>::T> > map_type;
    typedef const std::map<ENUM,std::vector<typename Type<ENUM>::T> > defaults_type;
    typedef const std::map<ENUM,std::string> key_type;
    typedef typename Type<ENUM>::T my_type;
    typedef const typename Type<ENUM>::T init_type;
    static key_type keys;
    static defaults_type defaults;
    static init_type init;
};

#endif // TYPE_H
