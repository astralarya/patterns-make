/*
 * Initializer.h
 *
 *  Created on: Dec 14, 2012
 *      Author: mara
 */

#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#include "Options.h"
#include <string>
#include <set>
#include <map>

class Initializer {
public:
	Initializer(int argc, const char* argv[]);
	virtual ~Initializer();
	bool noargs();
	bool flag(char c);
	bool flag(std::string s);
	typedef std::map<int,std::string> extras_map;
	typedef extras_map::iterator extras_iterator;
	extras_map extras();
	extras_map extras(char c);
	extras_map extras(std::string s);
	std::string reportUnused();
private:
	int _argc;
	const char** _argv;
	std::set<char> _shortflags;
	std::set<std::string> _longflags;
	std::map<char,extras_map> _shortflagextras;
	std::map<std::string,extras_map> _longflagextras;
	extras_map _unusedextras;
	std::string pre_path(const char* c);
};

#endif /* INITIALIZER_H_ */
