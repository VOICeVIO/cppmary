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
            virtual pugi::xml_node prevElement(std::vector<pugi::xml_node> nodes, pugi::xml_node current);
            virtual pugi::xml_node prevPrevElement(std::vector<pugi::xml_node> nodes, pugi::xml_node current);
            virtual pugi::xml_node nextElement(std::vector<pugi::xml_node> nodes, pugi::xml_node current);
            virtual pugi::xml_node nextNextElement(std::vector<pugi::xml_node> nodes, pugi::xml_node current);
    };

    class SegmentNavigator : public TargetElementNavigator {
        public:
            pugi::xml_node getElement(Target target);
    };

    class PrevSegmentNavigator : public TargetElementNavigator {
        public:
            pugi::xml_node getElement(Target target);
    };

    class WordNavigator : public TargetElementNavigator {
    public:
        pugi::xml_node getElement(Target target);
    };

    class NextWordNavigator : public TargetElementNavigator {
    public:
        pugi::xml_node getElement(Target target);
    };

    class PrevWordNavigator : public TargetElementNavigator {
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

    class PrevPrevSyllableNavigator : public TargetElementNavigator {
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

    class LastSyllableInPhraseNavigator : public TargetElementNavigator {
    public:
        pugi::xml_node getElement(Target target);
    };

    class LastSyllableInWordNavigator : public TargetElementNavigator {
    public:
        pugi::xml_node getElement(Target target);
    };

    class FirstSyllableInWordNavigator : public TargetElementNavigator {
    public:
        pugi::xml_node getElement(Target target);
    };
}


#endif //CPPMARY_TARGETELEMENTNAVIGATOR_H
