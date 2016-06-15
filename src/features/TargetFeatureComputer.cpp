//
// Created by sooda on 16/6/15.
//

#include "features/TargetFeatureComputer.h"
#include "common.h"

namespace cppmary  {
    TargetFeatureComputer::TargetFeatureComputer(FeatureProcessorManager manager,
                                                 std::string featuresProcessorNames) {
        std::vector<std::string> featureNames = splitAndTrim(featuresProcessorNames, ' ');
        for (int i = 0; i < featureNames.size(); i++) {
            ByteValuedFeatureProcessor* fp = manager.getByteFeatureProcessor(featureNames[i]);
            if (fp == NULL) {
                XLOG(ERROR) << "can not get feature process for " << featureNames[i];
            } else {
                byteProcessor_.push_back(fp); // 包含大量指针的传递,这里需要使用引用计数
            }
        }
    }

    TargetFeatureComputer::~TargetFeatureComputer() { }

    std::vector<int> TargetFeatureComputer::computeFeatureVector(Target target) {
        std::vector<int> features;
        for (int i = 0; i < byteProcessor_.size(); i++) {
            int feature = byteProcessor_[i]->process(target);
            features.push_back(feature);
        }
        return features;
    }

    std::string toStringValue(std::vector<int> features) {
        if (features.empty()) {
            XLOG(ERROR) << "feature is empty";
            return "";
        }
        std::string featureStr = std::to_string(features[0]);
        for (int i = 1; i < features.size(); i++) {
            featureStr = featureStr + std::to_string(featureStr[i]);
        }
        return featureStr;
    }


}