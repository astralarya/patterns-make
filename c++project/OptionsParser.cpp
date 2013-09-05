// OptionsParser.cpp
// Mara Kim

#include "OptionsParser.h"

int OptionsParser::parse() {
    Mode::type_map param;

    // Read OPTIONSFILE
    std::stringstream line;
    std::string buffer,
                variable;
    while(std::getline(_istream,buffer)) {
        line.str(buffer);
        bool first = true;
        while(std::getline(line,buffer,' '))
            if(first) {
                variable = buffer;
                first = false;
            } else
                param[variable].push_back(buffer);

        line.clear();
    }

    // Initialize Options
    _options._new(param);
    return 0;
}

inline void OptionsParser::error(char const *msg) {
    std::cerr << msg << '\n';
}

