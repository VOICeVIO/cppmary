//
// Created by sooda on 16/6/15.
//

#include "features/GenericFeatureProcessors.h"
#include "pugixml/pugixml.hpp"

namespace cppmary {
    std::string PhraseNumSyls::getName() {
        return "phrase_numsyls";
    }

    std::vector<std::string> PhraseNumSyls::getValues() {
        std::vector<std::string> values;
        for (int i = 0; i <= RAIL_LIMIT; i++) {
            values.push_back(std::to_string(i));
        }
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
}

