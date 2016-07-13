//
// Created by sooda on 16/6/13.
//

#ifndef CPPMARY_PROSODY_H
#define CPPMARY_PROSODY_H
#include "InterModules.h"
#include "cppjieba/Unicode.hpp"
#include <string>
#include <set>


namespace cppmary {
    const char* const SPECIAL_PUNCINATIONS = " \t\n，。！？~,.!?";

    class Prosody : public InterModules {
    public:
        Prosody();
        ~Prosody();
        virtual std::string process(const std::string& input);
        bool resetPuncinations(const std::string& s);
        bool isPuncinatiion(std::string text);
    private:
        std::set<cppjieba::Rune> puncination_;
    };
}


#endif //CPPMARY_PROSODY_H
