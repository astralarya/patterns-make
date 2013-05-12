#include "Foo.h"

void Foo::bar() {
    std::cout << "DB_HOST = " << Options::Instance()->get(DB_HOST) << std::endl;
    std::cout << "DB_NAME = " << Options::Instance()->get(DB_NAME) << std::endl;
    std::cout << "DB_USER = " << Options::Instance()->get(DB_USER) << std::endl;

    std::cout << "AVOGADRO = " << Options::Instance()->get(AVOGADRO) << std::endl;
    Options::Instance()->set(AVOGADRO,1);
    Options::Instance()->set(AVOGADRO,1,5.5);
    std::cout << "AVOGADRO = " << Options::Instance()->get(AVOGADRO) << std::endl;
    std::cout << "AVOGADRO[1] = " << Options::Instance()->get(AVOGADRO,1) << std::endl;

    Options::Instance()->set('a',true);
    std::cout << "'a'= " << Options::Instance()->get('a') << std::endl;
    std::cout << "'b'= " << Options::Instance()->get('b') << std::endl;
}
