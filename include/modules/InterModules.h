//
// Created by sooda on 16/6/8.
//

#ifndef CPPMARY_INTERMODULES_H
#define CPPMARY_INTERMODULES_H
#include <string>
#include "common.h"
#include "limonp/Logging.hpp"

namespace cppmary {
    class InterModules {
    public:
        InterModules();
        virtual ~InterModules();
        virtual std::string process(std::string input) = 0;
    protected:
        std::string name_;
    };
}


#endif //CPPMARY_INTERMODULES_H
