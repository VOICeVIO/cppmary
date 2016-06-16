//
// Created by sooda on 16/6/15.
//

#include "features/FeatureProcessorManager.h"
#include "features/GenericFeatureProcessors.h"

namespace cppmary {
    FeatureProcessorManager::FeatureProcessorManager(std::string localeString) {
        //locale process
        localeString_ = localeString;
        setupGenericFeatureProcessors();
        //setupPhoneFeature.. need to read allophone
    }

    FeatureProcessorManager::~FeatureProcessorManager() {
        std::map<std::string, FeatureProcessor *>::iterator iter;
        for (iter = processors_.begin(); iter != processors_.end(); ++iter) {
            delete iter->second;
        }
    }

    void FeatureProcessorManager::setupGenericFeatureProcessors() {
        addFeatureProcessor(new PhraseNumSyls());
        //add other
    }

    void FeatureProcessorManager::addFeatureProcessor(FeatureProcessor * fp) {
        processors_[fp->getName()] = fp;
    }

    FeatureProcessor * FeatureProcessorManager::getFeatureProcessor(std::string name) {
        //TODO: faild process
        return processors_[name];
    }
}
