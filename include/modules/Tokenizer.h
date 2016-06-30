//
// Created by sooda on 16/6/8.
//

#ifndef CPPMARY_TOKENIZER_H
#define CPPMARY_TOKENIZER_H
#include "InterModules.h"

namespace cppmary {
    class Tokenizer : public InterModules {
    public:
        Tokenizer();
        ~Tokenizer();
        virtual std::string process(std::string input);
    };
}

#endif //CPPMARY_TOKENIZER_H
