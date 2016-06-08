//
// Created by sooda on 16/6/8.
//

#ifndef CPPMARY_INTERMODULES_H
#define CPPMARY_INTERMODULES_H
#include <string>

namespace cppmary {
    class InterModules {
    public:
        virtual std::string process(std::string input) = 0;
    };
}


#endif //CPPMARY_INTERMODULES_H
