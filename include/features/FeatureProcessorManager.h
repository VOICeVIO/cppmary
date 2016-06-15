//
// Created by sooda on 16/6/15.
//

#ifndef CPPMARY_FEATUREPROCESSORMANAGER_H
#define CPPMARY_FEATUREPROCESSORMANAGER_H
#include <map>
#include <string>
#include "FeatureProcessorBase.h"


namespace cppmary {
    class FeatureProcessorManager {
        public:
            FeatureProcessorManager(std::string localeString);
            ~FeatureProcessorManager();
            void setupGenericFeatureProcessors();
            void addByteFeatureProcessor(ByteValuedFeatureProcessor* fp);
            ByteValuedFeatureProcessor* getByteFeatureProcessor(std::string name);

        private:
            std::string localeString_;
            std::map<std::string, ByteValuedFeatureProcessor*> byteProcessors_;
            std::map<std::string, std::vector<std::string> > phonefeature2values_;

    };
}


#endif //CPPMARY_FEATUREPROCESSORMANAGER_H
