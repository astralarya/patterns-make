// Foo.h
// An example object
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


#include "Foo.h"

void Foo::bar() {
    // Program arguments
    std::cout << "MYFOO=" << Options::Instance()->get(Project::FOO) << std::endl;
    std::cout << "SWITCH=" << (Options::Instance()->get(Project::SWITCH)?"true":"false") << std::endl;
    std::cout << "ARG0=" << Options::Instance()->get(Project::ARGUMENTS,0) << std::endl;
    std::cout << "ARG1=" << Options::Instance()->get(Project::ARGUMENTS,1) << std::endl;

    // Options file
    std::cout << "DB_HOST = " << Options::Instance()->get(Project::DB_HOST) << std::endl;
    std::cout << "DB_NAME = " << Options::Instance()->get(Project::DB_NAME) << std::endl;
    std::cout << "DB_USER = " << Options::Instance()->get(Project::DB_USER) << std::endl;
    std::cout << "AVOGADRO = " << Options::Instance()->get(Project::AVOGADRO) << std::endl;

    // Demonstrate options
    Options::Instance()->set(Project::AVOGADRO,1);
    Options::Instance()->set(Project::AVOGADRO,1,5.5);
    std::cout << "AVOGADRO = " << Options::Instance()->get(Project::AVOGADRO) << std::endl;
    std::cout << "AVOGADRO[1] = " << Options::Instance()->get(Project::AVOGADRO,1) << std::endl;
    std::cout << "NUMBERS = " << Options::Instance()->get(Project::NUMBERS) << std::endl;
    std::cout << "NUMBERS[1] = " << Options::Instance()->get(Project::NUMBERS,1) << std::endl;
    std::cout << "NUMBERS[2] = " << Options::Instance()->get(Project::NUMBERS,2) << std::endl;
    std::cout << "NUMBERS[3] = " << Options::Instance()->get(Project::NUMBERS,3) << std::endl;
    Options::Instance()->set('a',true);
    std::cout << "'a'= " << Options::Instance()->get('a') << std::endl;
    std::cout << "'b'= " << Options::Instance()->get('b') << std::endl;
    std::cout << "'c'= " << Options::Instance()->get('c') << std::endl;
}
