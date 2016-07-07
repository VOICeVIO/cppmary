//
// Created by sooda on 16/6/15.
//

#include "features/TargetFeatureComputer.h"
#include "common.h"
#include "limonp/Logging.hpp"

namespace cppmary  {
    TargetFeatureComputer::TargetFeatureComputer(std::shared_ptr<FeatureProcessorManager> manager,
                                                 std::string featuresProcessorNames) {
        std::vector<std::string> featureNames = splitAndTrim(featuresProcessorNames, ' ');
        init(manager, featureNames);
    }

    TargetFeatureComputer::TargetFeatureComputer(std::shared_ptr<FeatureProcessorManager> manager,
                                                 std::vector<std::string> featureNamesVec) {
        init(manager, featureNamesVec);
    }

    void TargetFeatureComputer::init(std::shared_ptr<FeatureProcessorManager> manager,
                                                 std::vector<std::string> featureNamesVec) {
        processor_.clear();
        for (int i = 0; i < featureNamesVec.size(); i++) {
            std::shared_ptr<FeatureProcessor> fp = manager->getFeatureProcessor(featureNamesVec[i]);
            if (fp == NULL) {
                XLOG(ERROR) << "can not get feature process for " << featureNamesVec[i];
            } else {
                processor_.push_back(fp); // 包含大量指针的传递,这里需要使用引用计数
            }
        }
    }

    TargetFeatureComputer::~TargetFeatureComputer() {
        XLOG(INFO) << "deconstruct TargetFeatureComputer";
    }

    std::vector<int> TargetFeatureComputer::computeFeatureVector(Target target, std::map<std::string, std::pair<int, std::string> > *detail) {
        std::vector<int> features;
        for (int i = 0; i < processor_.size(); i++) {
            int feature = processor_[i]->process(target);
            if (NULL != detail) {
                std::string featureName = processor_[i]->getName();
                std::string featureStr = getFeatureValue(i, feature);
                std::pair<int, std::string> featurePair(feature, featureStr);
                (*detail)[featureName] = featurePair;
            }
            features.push_back(feature);
        }
        return features;
    }

    std::string TargetFeatureComputer::getFeatureValue(int processorIndex, int feature) {
        if (processorIndex >= processor_.size()) {
            XLOG(ERROR) << "feature index exceesd " << processorIndex;
            return "";
        }
        std::vector<std::string> featureValues = processor_[processorIndex]->getValues();
        if (feature > featureValues.size()) {
            return "0";
        } else {
            return featureValues[feature];
        }
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
