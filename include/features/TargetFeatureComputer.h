//
// Created by sooda on 16/6/15.
//

#ifndef CPPMARY_TARGETFEATURECOMPUTER_H
#define CPPMARY_TARGETFEATURECOMPUTER_H
#include <vector>
#include "FeatureProcessorManager.h"
#include "FeatureProcessorBase.h"

namespace cppmary {
    class TargetFeatureComputer {
    public:
        TargetFeatureComputer(FeatureProcessorManager& manager, std::string featuresProcessorNames);
        ~TargetFeatureComputer();
        //Feature vector 暂时用std::vector<int>保存
        std::vector<int> computeFeatureVector(Target target);
        std::string toStringValue(std::vector<int> featureVector);
    private:
        std::vector<ByteValuedFeatureProcessor* > byteProcessor_;
        //std::vector<PhraseNumSyls* > byteProcessor_;
    };

}

#endif //CPPMARY_TARGETFEATURECOMPUTER_H
