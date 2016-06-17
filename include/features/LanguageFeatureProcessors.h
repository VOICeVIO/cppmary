//
// Created by sooda on 16/6/16.
//

#ifndef CPPMARY_LANGUAGEFEATUREPROCESSORS_H
#define CPPMARY_LANGUAGEFEATUREPROCESSORS_H
#include <vector>
#include <string>
#include "StringTranslator.h"
#include "Target.h"

namespace cppmary {
    class Phone : public FeatureProcessor {
    public:
        Phone(std::string name, std::vector<std::string> possibleValues, std::string pausesymbol);
        ~Phone();
        virtual std::string getName();
        virtual std::vector<std::string> getValues();
        virtual int process(Target target);
    private:
        std::string name_;
        StringTranslator translator_;
    };
}


#endif //CPPMARY_LANGUAGEFEATUREPROCESSORS_H
