/*
 * Initializer.cpp
 *
 *      Author: mara
 */

#include "Initializer.h"

Initializer::Initializer(int argc, const char* argv[]):
_argc(argc),
_argv(argv){
    // check for arguments
    if(_argc > 1) {
        // process arguments
        std::set<char> _prevflags;
        std::string _prevlong;
        bool input = false;
        for(size_t i = 1; i < _argc; i++) {
            std::string s = _argv[i];
            if(input)
                _unusedextras[i] = s;
            else if(s == "--")
                input = true;
            else if(s.find("--") == 0) {
                s = s.substr(2);
                size_t eq = s.find('=');
                if(eq != std::string::npos) {
                    std::string extra = s.substr(eq + 1);
                    s = s.substr(0,eq);
                    _longflagextras[s][i] = extra;
                }
                _longflags.insert(s);
                _prevflags.clear();
                _prevlong = s;
            } else if(s.find("-") == 0) {
                _prevflags.clear();
                _prevlong.clear();
                for(size_t j = 1; j < s.length(); j++) {
                    _shortflags.insert(s[j]);
                    _prevflags.insert(s[j]);
                }
            } else {
                if(_prevflags.size())
                    for(std::set<char>::iterator it = _prevflags.begin();
                            it != _prevflags.end();
                            it++)
                        _shortflagextras[*it][i] = s;
                if(_prevlong.length())
                    _longflagextras[_prevlong][i] = s;
                _unusedextras[i] = s;
            }
        }
    }
}

Initializer::~Initializer() {
    // dtor
}

bool Initializer::noargs() {
    return _argc == 1;
}

bool Initializer::flag(char c) {
    return _shortflags.find(c) != _shortflags.end();
}

bool Initializer::flag(std::string s) {
    return _longflags.find(s) != _longflags.end();
}

std::string Initializer::extra(char c) {
    if(_shortflagextras[c].size()) {
        _unusedextras.erase(_shortflagextras[c].begin()->first);
        std::string r(_shortflagextras[c].begin()->second);
        _shortflagextras[c].erase(_shortflagextras[c].begin());
        return r;
    } else
        return "";
}

Initializer::extras_map Initializer::extras(char c) {
    for(extras_iterator it = _shortflagextras[c].begin(); it != _shortflagextras[c].end(); it++)
        _unusedextras.erase(it->first);
    return _shortflagextras[c];
}

std::string Initializer::extra(std::string s) {
    if(_longflagextras[s].size()) {
        _unusedextras.erase(_longflagextras[s].begin()->first);
        std::string r(_longflagextras[s].begin()->second);
        _longflagextras[s].erase(_longflagextras[s].begin());
        return r;
    } else
        return "";
}

Initializer::extras_map Initializer::extras(std::string s) {
    for(extras_iterator it = _longflagextras[s].begin(); it != _longflagextras[s].end(); it++)
        _unusedextras.erase(it->first);
    return _longflagextras[s];
}

std::string Initializer::extra() {
    if(_unusedextras.size()) {
        std::string r(_unusedextras.begin()->second);
        _unusedextras.erase(_unusedextras.begin());
        return r;
    } else
        return "";
}

Initializer::extras_map Initializer::extras() {
    return _unusedextras;
}

std::string Initializer::reportUnused() {
    std::stringstream ss;
    for(extras_iterator it = _unusedextras.begin();
            it != _unusedextras.end();
            it++)
    ss << "Ignored argument " << it->second << '\n';
    return ss.str();
}

