//
// Created by sooda on 16/6/15.
//

#include "features/FeatureProcessor.h"

namespace cppmary {

    FeatureProcessor::FeatureProcessor(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : 
        translator_(possibleValues), name_(name), navigator_(navigator) {

    }

    FeatureProcessor::~FeatureProcessor () {
        XLOG(INFO) << "deconstruct FeatureProcessor " << name_;
    }

    std::vector<std::string> FeatureProcessor ::getValues() {
        return translator_.getStringValues();
    }

    std::string FeatureProcessor::getName() {
        return name_;
    }

    int FeatureProcessor::process(Target target) {
        std::cout << "precess feature in base" << std::endl;
        return 0;
    }

    std::string FeatureProcessor::getPauseSymbol() {
        return "_";
    }

    int FeatureProcessor::countElementFromStart(std::vector<pugi::xml_node> nodes, pugi::xml_node current, std::string attrCondition) {
        int count = 0;
        int tempCount = 0;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            bool isBuffer = true;
            if (!attrCondition.empty()) {
                isBuffer = MaryXml::hasAttribute(node, attrCondition);
            }
            if (node == current || tempCount >= RAIL_LIMIT) {
                count = tempCount;
                break;
            }
            if (!node.empty() && isBuffer) {
                tempCount++;
            }
        }
        return count;
    }

    int FeatureProcessor::countElementToEnd(std::vector<pugi::xml_node> nodes, pugi::xml_node current, std::string attrCondition) {
        int count = 0;
        bool startCounter = false;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            bool isBuffer = true;
            if (!attrCondition.empty()) {
                isBuffer = MaryXml::hasAttribute(node, attrCondition);
            }
            if (!node.empty() && isBuffer && startCounter) {
                count++;
            }
            if (node == current) {
                startCounter = true;
            }
            if (count >= RAIL_LIMIT) {
                break;
            }
        }
        return count;
    }

    int FeatureProcessor::disToPrevAttributeElement(std::vector<pugi::xml_node> nodes, pugi::xml_node current, std::string attr) {
        int count = 0;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (node.empty()) {
                continue;
            }
            if (MaryXml::hasAttribute(node, attr)) {
                count = 0;
            } else {
                count++;
            }
            if (node == current || count >= RAIL_LIMIT) {
                break;
            }
        }
        return count;
    }

    int FeatureProcessor::disToNextAttributeElement(std::vector<pugi::xml_node> nodes, pugi::xml_node current, std::string attr) {
        int count = 0;
        int tempCount = 0;
        bool startCounter = false;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (!node.empty() && startCounter) {
                tempCount++;
            }
            if (node == current) {
                startCounter = true;
            }
            if (count >= RAIL_LIMIT) {
                break;
            }
            if (MaryXml::hasAttribute(node, attr)) {
                count = tempCount;
                break;
            }
        }
        return count;
    }


}
