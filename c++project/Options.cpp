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
    }

    return _Instance;
}

Options::Options():
_properties(),
_modes() {
    std::ifstream options_file(exe_path() + OPTIONS_FILE);
    if(options_file.is_open()) {
        OptionsParser p(*this, options_file);
        p.parse();
        options_file.close();
    }
}

std::string Options::exe_path()
{
    char buffer[4096];
    ssize_t r = readlink ("/proc/self/exe", buffer, 4096);
    buffer[r] = 0;
    std::string path(buffer);
    size_t path_end = path.rfind('/') + 1;
    return path.substr(0,path_end);
}

void Options::_new(const Mode::type_map& properties)
{
    _properties = properties;
}
