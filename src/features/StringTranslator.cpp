//
// Created by sooda on 16/6/16.
//

#include "features/StringTranslator.h"

namespace cppmary {
    StringTranslator::StringTranslator(std::vector<std::string> strs) {
        featureList_ = strs;
        for (int i = 0; i < strs.size(); i++) {
            map_[strs[i]] = i;
        }

        std::cout << "translate result " << std::endl;
        for (std::map<std::string, int>::iterator iter = map_.begin(); iter != map_.end(); ++iter) {
            std::cout << iter->first << " " << iter->second << std::endl;
        }
    }

    int StringTranslator::getValue(std::string s) {
        //TODO: deal with not contain the key
        int value = map_[s];
        return value;
    }

    std::vector<std::string> StringTranslator::getStringValues() {
        return featureList_;
    }

    bool StringTranslator::contain(std::string ph) {
       for (int i = 0; i < featureList_.size(); i++) { 
           if (featureList_[i] == ph) {
               return true;
           }
       }
       return false;
    }
}
