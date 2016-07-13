//
// Created by sooda on 16/6/16.
//

#include "features/Allophone.h"
#include "limonp/Logging.hpp"

namespace cppmary {
    Allophone::Allophone(pugi::xml_node node, std::vector<std::string> featureNames) {
        name_ = node.attribute("ph").as_string();
        std::string vc;
        std::string isTone;
        if (name_ == "") {
            XLOG(ERROR) << "allophone must have ph attribute";
            return;
        }
        std::string tagName = node.name();
        if (tagName == "consonant") {
            vc = "-";
            isTone = "-";
        } else if (tagName == "vowel") {
            vc = "+";
            isTone = "-";
        } else if (tagName == "silence") {
            vc = "0";
            isTone = "-";
        } else if(tagName == "tone") {
            vc = "0";
            isTone = "+";
        } else {
            XLOG(ERROR) << "tagname unrecognize " << tagName;
            return;
        }
        features_["vc"] = vc;
        features_["isTone"] = isTone;
        for (int i = 0; i < featureNames.size(); i++) {
            std::string feature = featureNames[i];
            std::string featureValue = node.attribute(feature.c_str()).as_string();
            if (featureValue == "") {
                featureValue = "0";
            }
            features_[feature] = featureValue;
        }
//        XLOG(DEBUG) << "allophone attribute: " << name_;
//        std::map<std::string, std::string>::iterator iter;
//        for (iter = features_.begin(); iter != features_.end(); ++iter) {
//            XLOG(DEBUG) << iter->first << " " << iter->second;
//        }
    }

    Allophone::Allophone() {
        name_ = "";
    }

    Allophone::~Allophone() {

    }

    std::string Allophone::getAttribute(pugi::xml_node node, std::string attr) {
        std::string val = node.attribute(attr.c_str()).as_string();
        return val;
    }

    std::string Allophone::name() {
        return name_;
    }

    bool Allophone::isVowel() {
        return ("+" == features_["vc"]);
    }

    bool Allophone::isDiphthong() {
        assert(isVowel());
        return ("d" == features_["vlng"]);
    }

    bool Allophone::isSyllabic() {
        return isVowel();
    }

    bool Allophone::isConsonant() {
        return ("-" == features_["vc"]);
    }

    bool Allophone::isVoiced() {
        return (isVowel() || ("+" == features_["cvox"]));
    }

    bool Allophone::isSonorant() {
        return ("lnr" == features_["ctype"]);
    }

    bool Allophone::isLiquid() {
        return ("l" == features_["ctype"]);
    }

    bool Allophone::isNasal() {
        return ("n" == features_["ctype"]);
    }

    bool Allophone::isGlide() {
        return ("r" == features_["ctype"] && !isVowel());
    }

    bool Allophone::isFricative() {
        return ("f" == features_["ctype"]);
    }

    bool Allophone::isPlosive() {
        return ("s" == features_["ctype"]);
    }

    bool Allophone::isAffricate() {
        return ("a" == features_["ctype"]);
    }

    bool Allophone::isPause() {
        return "0" == features_["vc"] && "-" == features_["isTone"];
    }

    bool Allophone::isTone() {
        return "+" == features_["isTone"];
    }

    std::map<std::string, std::string> Allophone::getFeatures() {
        return features_;
    }

    std::string Allophone::getFeature(std::string feat) {
        return features_[feat];
    }
}
