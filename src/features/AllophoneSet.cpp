//
// Created by sooda on 16/6/16.
//

#include "features/AllophoneSet.h"
#include "common.h"
#include <set>

namespace cppmary {
    AllophoneSet::AllophoneSet(std::string xmlStr) {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(xmlStr.c_str());
        std::string xmlLang = doc.child("allophones").attribute("xml:lang").as_string();
        localeStr_ = xmlLang;
        name_ = doc.attribute("name").as_string();
        std::string features = doc.child("allophones").attribute("features").as_string();
        std::vector<std::string> featureNames = splitAndTrim(features, ' ');
        cppmary::phoneset_walker tw;
        doc.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;

        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            Allophone ap(node, featureNames);
            std::string phoneName = node.attribute("ph").as_string();
            if (allophones_.find(phoneName)!=allophones_.end()) {
                XLOG(ERROR) << "dupplicate feature value" << phoneName;
                return;
            }
            allophones_[phoneName] = ap;
            allophoneNames_.push_back(phoneName);
            if (ap.isPause()) {
                silence_ = ap;
            }
        }
        //TODO: check slient null
        for (int i = 0; i < featureNames.size(); i++) {
            std::string feature = featureNames[i];
            std::set<std::string> featureSet;
            std::map<std::string, Allophone>::iterator iter;
            for (iter = allophones_.begin(); iter != allophones_.end(); ++iter) {
                Allophone current = iter->second;
                featureSet.insert(current.getFeature(feature));
            }
            std::set<std::string>::iterator valueIter;
            valueIter = featureSet.find("0");
            if (valueIter != featureSet.end()) {
                featureSet.erase(valueIter);
            }
            std::vector<std::string> featureValues;
            std::cout << "set size: " << featureSet.size() << std::endl;
            featureValues.push_back("0");
            for (std::set<std::string>::iterator setIter = featureSet.begin(); setIter != featureSet.end(); ++setIter) {
                std::string temp = *setIter;
                std::cout << "ss: " << temp << std::endl;
                featureValues.push_back(temp);
            }
            featureValuesMap_[feature] = featureValues;
        }

        std::vector<std::string> vcValues;
        vcValues.push_back("0");
        vcValues.push_back("+");
        vcValues.push_back("-");
        featureValuesMap_["vc"] = vcValues;
    }
    
    AllophoneSet::~AllophoneSet() {

    }

    Allophone AllophoneSet::getAllophone(std::string ph) {
        return allophones_[ph];
    }

    Allophone AllophoneSet::getSilent() {
        return silence_;
    }

    std::vector<std::string> AllophoneSet::getAllophoneNames() {
        return allophoneNames_;
    }


}
