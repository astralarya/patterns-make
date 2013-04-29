#include <iostream>
#include "Options.h"

class test {
public:
    void foo() {
        std::cout << "DB_HOST = " << Options::Instance()->get(DB_HOST) << std::endl;
        std::cout << "DB_NAME = " << Options::Instance()->get(DB_NAME) << std::endl;
        std::cout << "DB_USER = " << Options::Instance()->get(DB_USER) << std::endl;

        std::cout << "AVOGADRO = " << Options::Instance()->get(AVOGADRO) << std::endl;
    };
    
};
