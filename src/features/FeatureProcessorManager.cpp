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
        std::map<std::string, ByteValuedFeatureProcessor*>::iterator iter;
        for (iter = byteProcessors_.begin(); iter != byteProcessors_.end(); ++iter) {
            delete iter->second;
        }
    }

    void FeatureProcessorManager::setupGenericFeatureProcessors() {
        addByteFeatureProcessor(new PhraseNumSyls());
        //add other
    }

    void FeatureProcessorManager::addByteFeatureProcessor(ByteValuedFeatureProcessor* fp) {
        byteProcessors_[fp->getName()] = fp;
    }

    ByteValuedFeatureProcessor* FeatureProcessorManager::getByteFeatureProcessor(std::string name) {
        //faild process
        return byteProcessors_[name];
    }
}
