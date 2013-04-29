// Options.h
// Mara Kim
//
// A singleton class which reads a
// configuration file and provides
// the values to the program

#include "Options.h"
#include "OptionsParser.h"

// Global static pointer that ensures a single instance
Options* Options::_Instance = NULL;

// Function call to return instance of this class
Options* Options::Instance()
{
    if(!_Instance) // if there is no instance of the class
    {
        _Instance = new Options;
        _Instance->_initialize();
    }

    return _Instance;
}

// Global static pointer that ensures a single instance
MetaOptions* MetaOptions::_Instance = NULL;

// Function call to return instance of this class
MetaOptions* MetaOptions::Instance()
{
    if(!_Instance) // if there is no instance of the class
    {
        _Instance = new MetaOptions;
    }

    return _Instance;
}


std::string MetaOptions::prop(properties i)
{
    return _properties[i];
}

void MetaOptions::set(properties i, std::string s)
{
    _properties[i] = s;
}


Options::Options():
_modes()
{
}

void Options::_initialize()
{
    std::ifstream options_file(MetaOptions::Instance()->prop(MetaOptions::EXECUTABLE_PATH) + OPTIONSFILE);
    OptionsParser p(this, options_file);
    p.parse();
    options_file.close();
}

void Options::_new(const Mode::type_map& properties)
{
    _properties = properties;
    for(auto mode = _modes.begin(); mode != _modes.end(); mode++)
        mode->second->_initialize(_properties);
}
