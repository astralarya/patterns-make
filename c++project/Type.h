// Type.h
// Mara Kim
//
// Associate one type with another

#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <map>

// Type class to associate enums with types
template <class ENUM>
struct Type {
    typedef void T;
};

// Type info
template <typename ENUM>
struct TypeInfo {
    typedef std::map<ENUM,typename Type<ENUM>::T> map_type;
    typedef std::map<ENUM,std::string> key_type;
    typedef typename Type<ENUM>::T my_type;
    static key_type keys;
    static map_type defaults;
    static my_type init;
};

#endif // TYPE_H
