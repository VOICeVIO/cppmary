//
// Created by sooda on 16/6/15.
//

#include "features/FeatureProcessor.h"

namespace cppmary {

    FeatureProcessor::FeatureProcessor () {

    }
    FeatureProcessor::~FeatureProcessor () {
        //XLOG(DEBUG) << "deconstruct FeatureProcessor ";
    }

    std::vector<std::string> FeatureProcessor ::getValues() {
        return std::vector<std::string>();
    }

    std::string FeatureProcessor::getName() {
        return "";
    }

    int FeatureProcessor::process(Target target) {
        return 0;
    }

    std::string FeatureProcessor::getPauseSymbol() {
        return "_";
    }

}