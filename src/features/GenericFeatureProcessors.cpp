//
// Created by sooda on 16/6/15.
//

#include <features.h>
#include "features/GenericFeatureProcessors.h"
#include "pugixml/pugixml.hpp"
#include "common.h"

namespace cppmary {

    /*
     * PhraseNumSyls
     */
    PhraseNumSyls::PhraseNumSyls(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : 
                FeatureProcessor(name, possibleValues, navigator) {
        XLOG(DEBUG) << "construct PhraseNumSyls";
    }

    PhraseNumSyls::~PhraseNumSyls() {
        //XLOG(DEBUG) << "deconstruct PhraseNumSyls";
    }

    int PhraseNumSyls::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0 ;
        }
        pugi::xml_node phrase = MaryXml::getAncestor(segment, "phrase");
        if (phrase.empty()) {
            return 0;
        }
        pugi::xml_node syls = phrase.child("t").child("syllable");
        int count = 0;
        for (pugi::xml_node iterNode = syls.first_child(); iterNode; iterNode = iterNode.next_sibling()) {
            count++;
            if (count == RAIL_LIMIT) {
                break;
            }
        }
        return count;
    }

    TobiAccent::TobiAccent(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    TobiAccent::~TobiAccent() { }

    int TobiAccent::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        std::string accent = syllable.attribute("accent").as_string();
        if (accent.empty()) {
            return 0;
        }
        return translator_.getValue(accent);
    }
}

