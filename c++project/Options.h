// Options.h
// Mara Kim
//
// A singleton class which reads a
// configuration file and provides
// the values to the program
//
// Usage:
// Options::Instance()->get(FOO)
//                      set(FOO)

#ifndef OPTIONS_H
#define OPTIONS_H

#include "Project.h"
#include <fstream>
#include <typeinfo>
#include <string>
#include <map>

class OptionsParser;

class Options
{
    public:
        friend class OptionsParser;

        static Options* Instance();

        template <class ENUM>
        inline void set(const ENUM& mode, const typename TypeInfo<ENUM>::my_type& value) {
            set<ENUM>(mode,0,value);
        }

        template <class ENUM>
        void set(const ENUM& mode, size_t index, const typename TypeInfo<ENUM>::my_type& value)
        {
            if(_modes.find(typeid(ENUM).hash_code()) == _modes.end())
                _addmode<ENUM>();
            static_cast<Typed_Mode<ENUM>*>(_modes[typeid(ENUM).hash_code()])->set(mode,index,value);
        }

        template <class ENUM>
        typename TypeInfo<ENUM>::ref_type get(const ENUM& mode, size_t index=0)
        {
            if(_modes.find(typeid(ENUM).hash_code()) == _modes.end())
                _addmode<ENUM>();
            return static_cast<Typed_Mode<ENUM>*>(_modes[typeid(ENUM).hash_code()])->get(mode,index);
        }

    protected:
        void _new(const Mode::type_map& properties);
    private:
        // make instantiation, copying, and assignment private
        Options();
        Options(Options const&);

        // get executable path
        std::string exe_path();

        // read options file
        void _initialize();

        template <typename ENUM>
        void _addmode() {
            _modes[typeid(ENUM).hash_code()] = new Typed_Mode<ENUM>(_properties);
        };

        static Options* _Instance;

        Mode::type_map _properties;

        typedef std::map<size_t,Mode*> mode_map;
        mode_map _modes;
};

#endif // OPTIONS_H
