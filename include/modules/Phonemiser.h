//
// Created by sooda on 16/6/12.
//

#ifndef CPPMARY_PHONEMISER_H
#define CPPMARY_PHONEMISER_H

#include "modules/InterModules.h"

namespace cppmary {

    class Phonemiser : public InterModules {
        virtual std::string process(std::string input);
    };

}

#endif //CPPMARY_PHONEMISER_H
