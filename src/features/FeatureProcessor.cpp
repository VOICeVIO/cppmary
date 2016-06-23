//
// Created by sooda on 16/6/15.
//

#include "features/FeatureProcessor.h"

namespace cppmary {

    FeatureProcessor::FeatureProcessor(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : 
        translator_(possibleValues), name_(name), navigator_(navigator) {

    }

    FeatureProcessor::~FeatureProcessor () {
        XLOG(DEBUG) << "deconstruct FeatureProcessor " << name_;
    }

    std::vector<std::string> FeatureProcessor ::getValues() {
        return translator_.getStringValues();
    }

    std::string FeatureProcessor::getName() {
        return name_;
    }

    int FeatureProcessor::process(Target target) {
        std::cout << "precess feature in base" << std::endl;
        return 0;
    }

    std::string FeatureProcessor::getPauseSymbol() {
        return "_";
    }
}
