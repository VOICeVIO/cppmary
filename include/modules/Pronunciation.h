//
// Created by sooda on 16/6/13.
//

#ifndef CPPMARY_PRONUNCIATION_H
#define CPPMARY_PRONUNCIATION_H
#include "modules/InterModules.h"

namespace cppmary {
    class Pronunciation : public InterModules {
        virtual std::string process(std::string input);
    };
}


#endif //CPPMARY_PRONUNCIATION_H
