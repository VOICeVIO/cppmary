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

    Accented::Accented(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    Accented::~Accented() { }

    int Accented::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (!syllable.empty() && MaryXml::hasAttribute(syllable, "accent")) {
            return 1;
        } else {
            return 0;
        }
    }

    AccentedSylsFromPhraseStart::AccentedSylsFromPhraseStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    AccentedSylsFromPhraseStart::~AccentedSylsFromPhraseStart(){}

    int AccentedSylsFromPhraseStart::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        syllable_boundary_walker tw;
        pugi::xml_node phrase = MaryXml::getAncestor(syllable, "phrase");
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = 0;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (!node.empty() && MaryXml::hasAttribute(node, "accent")) {
                count++;
            }
            if (node == syllable || count >= RAIL_LIMIT) {
                break;
            }
        }
        return count;
    }

    AccentedSylsFromPhraseEnd::AccentedSylsFromPhraseEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    AccentedSylsFromPhraseEnd::~AccentedSylsFromPhraseEnd(){}

    int AccentedSylsFromPhraseEnd::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        syllable_boundary_walker tw;
        pugi::xml_node phrase = MaryXml::getAncestor(syllable, "phrase");
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = 0;
        bool startCounter = false;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (!node.empty() && MaryXml::hasAttribute(node, "accent") && startCounter) {
                count++;
            }
            if (node == syllable) {
                startCounter = true;
            }
            if (count >= RAIL_LIMIT) {
                break;
            }
        }
        return count;
    }


}

