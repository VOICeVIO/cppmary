//
// Created by sooda on 16/6/16.
//

#ifndef CPPMARY_STRINGTRANSLATOR_H
#define CPPMARY_STRINGTRANSLATOR_H
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "common/MaryBase.h"

namespace cppmary {
    class StringTranslator : public MaryBase {
        public:
            StringTranslator(std::vector<std::string> strs);
            virtual ~StringTranslator();
            int getValue(std::string s);
            std::vector<std::string> getStringValues();
            bool contain(std::string ph);

        private:
            std::vector<std::string> featureList_;
            std::map<std::string, int> map_;
    };
}


#endif //CPPMARY_STRINGTRANSLATOR_H
