//
// Created by sooda on 16/6/15.
//

#include "features/Target.h"

namespace cppmary {
    Target::Target(std::string name, pugi::xml_node maryxmlElement) {
        name_ = name;
        maryxmlElement_ = maryxmlElement;
    }

    Target::Target(const Target &target) {
        name_ = target.name_;
        maryxmlElement_ = target.maryxmlElement_;
    }

    Target::~Target() {
    }

    bool Target::isSilence() {
        std::string silentceSymbol = "_";
        if (name_.find(silentceSymbol) != std::string::npos) {
            return true;
        } else {
            return false;
        }
    }

    std::string Target::getName() {
        return name_;
    }

    pugi::xml_node Target::getMaryElement() {
        return maryxmlElement_;
    }

    std::vector<int> Target::getFeatureVector() {
        return featureVector_;
    }

    void Target::setFeatureVector(std::vector<int> featureVec) {
        featureVector_ = featureVec;
    }


}
