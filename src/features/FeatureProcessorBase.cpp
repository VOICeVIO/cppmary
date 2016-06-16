//
// Created by sooda on 16/6/15.
//

#include "features/FeatureProcessorBase.h"

namespace cppmary {

    ByteValuedFeatureProcessor::ByteValuedFeatureProcessor() {

    }
    ByteValuedFeatureProcessor::~ByteValuedFeatureProcessor() {
        XLOG(DEBUG) << "deconstruct ByteValuedFeatureProcessor";
    }

    std::vector<std::string> ByteValuedFeatureProcessor::getValues() {
        return std::vector<std::string>();
    }

    std::string ByteValuedFeatureProcessor::getName() {
        return "";
    }

    int ByteValuedFeatureProcessor::process(Target target) {
        return 0;
    }

}