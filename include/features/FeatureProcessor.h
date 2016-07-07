//
// Created by sooda on 16/6/15.
//

#ifndef CPPMARY_FEATUREPROCESSOR_H
#define CPPMARY_FEATUREPROCESSOR_H
#include "Target.h"
#include <string>
#include <vector>
#include "TargetElementNavigator.h"
#include "StringTranslator.h"
#include "limonp/Logging.hpp"
#include <memory>

//通用特征定义MaryGenericFeatureProcessors的下半部分, 原本在例如,Phone, nextPhone等. 包含大量的类,大量的对象..

namespace cppmary {
    const int RAIL_LIMIT = 19;

class FeatureProcessor {
    public:
        virtual std::vector<std::string> getValues();
        virtual std::string getName();
        virtual int process(Target target);
        virtual std::string getPauseSymbol();
        FeatureProcessor(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator);
        virtual int countElementFromStart(std::vector<pugi::xml_node> nodes, pugi::xml_node current, std::string attrCondition = "");
        virtual int countElementToEnd(std::vector<pugi::xml_node> nodes, pugi::xml_node current, std::string attrCondition = "");
        virtual int disToPrevAttributeElement(std::vector<pugi::xml_node> nodes, pugi::xml_node current, std::string attr);
        virtual int disToNextAttributeElement(std::vector<pugi::xml_node> nodes, pugi::xml_node current, std::string attr);
        virtual ~FeatureProcessor ();
    protected:
        std::string name_;
        std::shared_ptr<TargetElementNavigator> navigator_;
        StringTranslator translator_;
    };
}



#endif //CPPMARY_FEATUREPROCESSOR_H
