//
// Created by sooda on 16/6/15.
//

#include <features.h>
#include "features/GenericFeatureProcessors.h"
#include "pugixml/pugixml.hpp"
#include "common.h"

namespace cppmary {

    /*
     * the token syllable of current phrase
     */
    PhraseNumSyls::PhraseNumSyls(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : 
                FeatureProcessor(name, possibleValues, navigator) {
    }

    PhraseNumSyls::~PhraseNumSyls() {
    }

    int PhraseNumSyls::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node phrase = MaryXml::getAncestor(segment, "phrase");
        if (phrase.empty()) {
            return 0;
        }
        syllable_walker tw;
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return nodes.size() > RAIL_LIMIT ? RAIL_LIMIT : nodes.size();
    }

    /*
     * the token amount of current phrase
     */
    PhraseNumWords::PhraseNumWords(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : 
                FeatureProcessor(name, possibleValues, navigator) {
    }

    PhraseNumWords::~PhraseNumWords() {
    }

    int PhraseNumWords::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node phrase = MaryXml::getAncestor(segment, "phrase");
        if (phrase.empty()) {
            return 0;
        }
        token_walker tw;
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return nodes.size() > RAIL_LIMIT ? RAIL_LIMIT : nodes.size();
    }

    /*
     * the syllable amount of current token
     */
    WordNumSyls::WordNumSyls(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : 
                FeatureProcessor(name, possibleValues, navigator) {
    }

    WordNumSyls::~WordNumSyls() {
    }

    int WordNumSyls::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node word = MaryXml::getAncestor(segment, "t");
        if (word.empty()) {
            return 0;
        }
        syllable_walker tw;
        word.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return nodes.size() > RAIL_LIMIT ? RAIL_LIMIT : nodes.size();
    }

    /*
     * the segment amount of current token
     */
    WordNumSegs::WordNumSegs(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : 
                FeatureProcessor(name, possibleValues, navigator) {
    }

    WordNumSegs::~WordNumSegs() {
    }

    int WordNumSegs::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node word = MaryXml::getAncestor(segment, "t");
        if (word.empty()) {
            return 0;
        }
        phone_walker tw;
        word.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return nodes.size() > RAIL_LIMIT ? RAIL_LIMIT : nodes.size();
    }

    /*
     * the segment amount of current syllable
     */
    SylNumSegs::SylNumSegs(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : 
                FeatureProcessor(name, possibleValues, navigator) {
    }

    SylNumSegs::~SylNumSegs() {
    }

    int SylNumSegs::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node syl = MaryXml::getAncestor(segment, "syllable");
        if (syl.empty()) {
            return 0;
        }
        phone_walker tw;
        syl.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return nodes.size() > RAIL_LIMIT ? RAIL_LIMIT : nodes.size();
    }

    /*
     * The Tobi accent of current syllable
     */
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

    /*
     * the current syllable is has accente attribute?
     */
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

    /*
     * the accented syllable amount from current phrase start
     */
    AccentedSylsFromPhraseStart::AccentedSylsFromPhraseStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    AccentedSylsFromPhraseStart::~AccentedSylsFromPhraseStart(){}

    int AccentedSylsFromPhraseStart::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        syllable_walker tw;
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

    /*
     * the accented syllable amount from current phrase end
     */
    AccentedSylsFromPhraseEnd::AccentedSylsFromPhraseEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    AccentedSylsFromPhraseEnd::~AccentedSylsFromPhraseEnd(){}

    int AccentedSylsFromPhraseEnd::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        syllable_walker tw;
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


    /*
     * the syllable amount from prev accented syllable
     */
    SylsFromPrevAccented::SylsFromPrevAccented(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    SylsFromPrevAccented::~SylsFromPrevAccented(){}

    int SylsFromPrevAccented::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        syllable_walker tw;
        pugi::xml_node phrase = MaryXml::getAncestor(syllable, "phrase");
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = 0;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (MaryXml::hasAttribute(node, "accent")) {
                count = 0;
            } else {
                count++;
            }
            if (node == syllable || count >= RAIL_LIMIT) {
                break;
            }
        }
        return count;
    }

    /*
     * the syllable amount to next accented syllable
     */
    SylsToNextAccented::SylsToNextAccented(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    SylsToNextAccented::~SylsToNextAccented(){}

    int SylsToNextAccented::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        syllable_walker tw;
        pugi::xml_node phrase = MaryXml::getAncestor(syllable, "phrase");
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = 0;
        int tempCount = 0;
        bool startCounter = false;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (!node.empty() && startCounter) {
                tempCount++;
            }
            if (node == syllable) {
                startCounter = true;
            }
            if (count >= RAIL_LIMIT) {
                break;
            }
            if (MaryXml::hasAttribute(node, "accent")) {
                count = tempCount;
                break;
            }
        }
        return count;
    }

    /*
     * the syllable amount from current phrase start
     */
    SylsFromPhraseStart::SylsFromPhraseStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    SylsFromPhraseStart::~SylsFromPhraseStart(){}

    int SylsFromPhraseStart::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        syllable_walker tw;
        pugi::xml_node phrase = MaryXml::getAncestor(syllable, "phrase");
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = 0;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (!node.empty()) {
                count++;
            }
            if (node == syllable || count >= RAIL_LIMIT) {
                break;
            }
        }
        return count;
    }

    /*
     * the syllable amount from current phrase end
     */
    SylsFromPhraseEnd::SylsFromPhraseEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    SylsFromPhraseEnd::~SylsFromPhraseEnd(){}

    int SylsFromPhraseEnd::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        syllable_walker tw;
        pugi::xml_node phrase = MaryXml::getAncestor(syllable, "phrase");
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = 0;
        bool startCounter = false;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (!node.empty() && startCounter) {
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

    /*
     * the segment amount from syllable start
     */
    SegsFromSylStart::SegsFromSylStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    SegsFromSylStart::~SegsFromSylStart(){}

    int SegsFromSylStart::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        phone_walker tw;
        pugi::xml_node syllable = MaryXml::getAncestor(segment, "syllable");
        syllable.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = 0;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (!node.empty()) {
                count++;
            }
            if (node == segment || count >= RAIL_LIMIT) {
                break;
            }
        }
        return count;
    }

    /*
     * the segment amount from syllable end
     */
    SegsFromSylEnd::SegsFromSylEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    SegsFromSylEnd::~SegsFromSylEnd(){}

    int SegsFromSylEnd::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        phone_walker tw;
        pugi::xml_node syllable = MaryXml::getAncestor(segment, "syllable");
        syllable.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = 0;
        bool startCounter = false;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (!node.empty() && startCounter) {
                count++;
            }
            if (node == segment) {
                startCounter = true;
            }
            if (count >= RAIL_LIMIT) {
                break;
            }
        }
        return count;
    }

}

