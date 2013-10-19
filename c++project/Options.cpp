// Options.cpp
//
// Copyright (C) 2013 Mara Kim
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see http://www.gnu.org/licenses/.


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
    std::string file = exe_path() + OPTIONS_FILE;
    std::ifstream options_file(file);
    if(options_file.is_open()) {
        OptionsParser p(*this, options_file);
        p.parse();
        options_file.close();
    } else
        std::cerr << "Cannot read OPTIONS_FILE: " << file << std::endl;
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
