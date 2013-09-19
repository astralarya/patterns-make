#include "Foo.h"

void Foo::bar() {
    std::cout << "DB_HOST = " << Options::Instance()->get(Project::DB_HOST) << std::endl;
    std::cout << "DB_NAME = " << Options::Instance()->get(Project::DB_NAME) << std::endl;
    std::cout << "DB_USER = " << Options::Instance()->get(Project::DB_USER) << std::endl;
    std::cout << "USERNAME = " << Options::Instance()->get(Project::USERNAME) << std::endl;

    std::cout << "AVOGADRO = " << Options::Instance()->get(Project::AVOGADRO) << std::endl;
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
