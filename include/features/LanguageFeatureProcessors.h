//
// Created by sooda on 16/6/16.
//

#ifndef CPPMARY_LANGUAGEFEATUREPROCESSORS_H
#define CPPMARY_LANGUAGEFEATUREPROCESSORS_H
#include <vector>
#include <string>
#include "StringTranslator.h"
#include "Target.h"
#include "TargetElementNavigator.h"

namespace cppmary {
    class Phone : public FeatureProcessor {
    public:
        Phone(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* segmentNavigator);
        virtual ~Phone();
        virtual int process(Target target);
    };

    class Pos : public FeatureProcessor {
    public:
        Pos(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* wordNavigator);
        virtual ~Pos();
        virtual int process(Target target);
    };

    class Zhtone : public FeatureProcessor {
    public:
        Zhtone(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~Zhtone();
        virtual int process(Target target);
    };
}


#endif //CPPMARY_LANGUAGEFEATUREPROCESSORS_H
