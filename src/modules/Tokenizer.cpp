//
// Created by sooda on 16/6/8.
//

#include "modules/Tokenizer.h"
#include <iostream>

namespace cppmary {
    std::string Tokenizer::process(std::string input) {
        std::cout << "string " << input << std::endl;
        return input + "result";
    }
}