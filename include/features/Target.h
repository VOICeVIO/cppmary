//
// Created by sooda on 16/6/15.
//

#ifndef CPPMARY_TARGET_H
#define CPPMARY_TARGET_H
#include <string>
#include "pugixml/pugixml.hpp"

namespace cppmary {
    class Target {
        public:
            Target(std::string name, pugi::xml_node maryxmlElement);
            ~Target();
            pugi::xml_node getMaryElement();
            std::string getName();
            std::vector<int> getFeatureVector();
            void setFeatureVector(std::vector<int> featureVec);
            bool isSilence();

        private:
            std::string name_;
            std::vector<int> featureVector_;
            pugi::xml_node maryxmlElement_;
    };
}

#endif //CPPMARY_TARGET_H
