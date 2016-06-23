//
// Created by sooda on 16/6/15.
//

#include "features/TargetFeatureComputer.h"
#include "common.h"

namespace cppmary  {
    TargetFeatureComputer::TargetFeatureComputer(FeatureProcessorManager& manager,
                                                 std::string featuresProcessorNames) {
        processor_.clear();
        std::vector<std::string> featureNames = splitAndTrim(featuresProcessorNames, ' ');
        for (int i = 0; i < featureNames.size(); i++) {
            FeatureProcessor * fp = manager.getFeatureProcessor(featureNames[i]);
            if (fp == NULL) {
                XLOG(ERROR) << "can not get feature process for " << featureNames[i];
            } else {
                processor_.push_back(fp); // 包含大量指针的传递,这里需要使用引用计数
            }
        }
    }

    TargetFeatureComputer::~TargetFeatureComputer() { }

    std::vector<int> TargetFeatureComputer::computeFeatureVector(Target target) {
        std::vector<int> features;
        for (int i = 0; i < processor_.size(); i++) {
            int feature = processor_[i]->process(target);
            features.push_back(feature);
        }
        return features;
    }

    std::string TargetFeatureComputer::getFeatureValue(int processorIndex, int feature) {
        if (processorIndex >= processor_.size()) {
            XLOG(ERROR) << "feature index exceesd " << processorIndex;
            return "";
        }
        return processor_[processorIndex]->getValues()[feature];
    }

    std::string TargetFeatureComputer::toStringValue(std::vector<int> features) {
        if (features.empty()) {
            XLOG(ERROR) << "feature is empty";
            return "";
        }
        std::string featureStr = getFeatureValue(0, features[0]);
        for (int i = 1; i < features.size(); i++) {
            featureStr = featureStr + "\t" + getFeatureValue(i, features[i]);
        }
        return featureStr;
    }


}