//
// Created by sooda on 16/6/16.
//

#ifndef CPPMARY_ALLOPHONE_H
#define CPPMARY_ALLOPHONE_H
#include <string>
#include <vector>
#include <map>
#include "pugixml/pugixml.hpp"

namespace cppmary {
    class Allophone {
        public:
            Allophone(pugi::xml_node node, std::vector<std::string> featureNames);
            Allophone();
            std::string getAttribute(pugi::xml_node e, std::string attr);
            ~Allophone();
            std::string name();
            bool isVowel();
            bool isDiphthong();
            bool isSyllabic();
            bool isConsonant();
            bool isVoiced();
            bool isSonorant();
            bool isLiquid();
            bool isNasal();
            bool isGlide();
            bool isFricative();
            bool isPlosive();
            bool isAffricate();
            bool isPause();
            bool isTone();
            std::map<std::string, std::string> getFeatures();
            std::string getFeature(std::string feat);
        private:
            std::string name_;
            std::map<std::string, std::string> features_;
    };
}


#endif //CPPMARY_ALLOPHONE_H
