//
// Created by sooda on 16/6/15.
//

#ifndef CPPMARY_TARGETELEMENTNAVIGATOR_H
#define CPPMARY_TARGETELEMENTNAVIGATOR_H
#include "Target.h"
#include "pugixml/pugixml.hpp"

//原来的MaryGenericFeatureProcessors遍历部分
namespace cppmary {
    class TargetElementNavigator {
        public:
            virtual pugi::xml_node getElement(Target target) = 0;
    };

    class SegmentNavigator : public TargetElementNavigator {
        public:
            pugi::xml_node getElement(Target target);
    };

    class SyllableNavigator : public TargetElementNavigator {
        public:
            pugi::xml_node getElement(Target target);
    };

    class PrevSyllableNavigator : public TargetElementNavigator {
        public:
            pugi::xml_node getElement(Target target);
    };

    class NextSyllableNavigator : public TargetElementNavigator {
    public:
        pugi::xml_node getElement(Target target);
    };

    class NextNextSyllableNavigator : public TargetElementNavigator {
    public:
        pugi::xml_node getElement(Target target);
    };
}


#endif //CPPMARY_TARGETELEMENTNAVIGATOR_H
