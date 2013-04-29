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

#ifndef OPTIONSFILE
#define OPTIONSFILE
#endif

class OptionsParser;
class MetaOptions
{
    public:
        friend class Options;
        enum properties{EXECUTABLE_PATH};

        typedef std::map<properties,std::string> prop_map;
        std::string prop(properties i);
        void set(properties i, std::string s);

        static MetaOptions* Instance();

    private:
        static MetaOptions* _Instance;
        prop_map _properties;
};

class Options
{
    public:

        static Options* Instance();

        template <class ENUM>
        void set(ENUM mode, typename Type<ENUM>::T value)
        {
            if(_modes.find(typeid(ENUM).hash_code()) == _modes.end())
                _addmode<ENUM>();
            static_cast<Typed_Mode<ENUM>*>(_modes[typeid(ENUM).hash_code()])->set(mode,value);
        }

        template <class ENUM>
        typename Type<ENUM>::T get(ENUM mode)
        {
            if(_modes.find(typeid(ENUM).hash_code()) == _modes.end())
                _addmode<ENUM>();
            return static_cast<Typed_Mode<ENUM>*>(_modes[typeid(ENUM).hash_code()])->get(mode);
        }


        friend class OptionsParser;
    protected:
        void _new(Mode::type_map& properties);
    private:
        // make instantiation, copying, and assignment private
        Options();
        Options(Options const&);

        // read options file
        void _initialize();

        template <typename ENUM>
        void _addmode() {
            _modes[typeid(ENUM).hash_code()] = new Typed_Mode<ENUM>;
            _modes[typeid(ENUM).hash_code()]->_initialize(_properties);
            
        };

        static Options* _Instance;

        Mode::type_map _properties;

        typedef std::map<size_t,Mode*> mode_map;
        mode_map _modes;
};

#endif // OPTIONS_H
