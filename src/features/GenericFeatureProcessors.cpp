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
        if (phrase.empty()) {
            return 0;
        }
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementFromStart(nodes, syllable, "accent");
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
        if (phrase.empty()) {
            return 0;
        }
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementToEnd(nodes, syllable, "accent");
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
        if (phrase.empty()) {
            return 0;
        }
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int dis = disToPrevAttributeElement(nodes, syllable, "accent");
        return dis;
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
        if (phrase.empty()) {
            return 0;
        }
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int dis = disToNextAttributeElement(nodes, syllable, "accent");
        return dis;
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
        if (phrase.empty()) {
            return 0;
        }
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementFromStart(nodes, syllable);
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
        if (phrase.empty()) {
            return 0;
        }
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementToEnd(nodes, syllable);
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
        if (syllable.empty()) {
            return 0;
        }
        syllable.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementFromStart(nodes, segment);
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
        pugi::xml_node syllable = MaryXml::getAncestor(segment, "syllable");
        if (syllable.empty()) {
            return 0;
        }
        phone_walker tw;
        syllable.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementToEnd(nodes, segment);
        return count;
    }

    /*
     * the segment amount from word start
     */
    SegsFromWordStart::SegsFromWordStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    SegsFromWordStart::~SegsFromWordStart(){}

    int SegsFromWordStart::process(Target target) {
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
        int count = countElementFromStart(nodes, segment);
        return count;
    }
    
    /*
     * the segment amount from word end
     */
    SegsFromWordEnd::SegsFromWordEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    SegsFromWordEnd::~SegsFromWordEnd(){}

    int SegsFromWordEnd::process(Target target) {
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
        int count = countElementToEnd(nodes, segment);
        return count;
    }


    /*
     * the syllable amount from word start
     */
    SylsFromWordStart::SylsFromWordStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    SylsFromWordStart::~SylsFromWordStart(){}

    int SylsFromWordStart::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        pugi::xml_node word = MaryXml::getAncestor(syllable, "t");
        if (word.empty()) {
            return 0;
        }
        syllable_walker tw;
        word.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementFromStart(nodes, syllable);
        return count;
    }
    
    /*
     * the syllable amout from word end
     */
    SylsFromWordEnd::SylsFromWordEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    SylsFromWordEnd::~SylsFromWordEnd(){}

    int SylsFromWordEnd::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        pugi::xml_node word = MaryXml::getAncestor(syllable, "t");
        if (word.empty()) {
            return 0;
        }
        syllable_walker tw;
        word.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementToEnd(nodes, syllable);
        return count;
    }

    /*
     * determinines the break level after this syllable
     */
    SylBreak::SylBreak(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    SylBreak::~SylBreak(){}

    int SylBreak::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        //next_sibling elment work?
        //pugi::xml_node nextSyllable = syllable.next_sibling(syllable.name());
        pugi::xml_node nextSyllable = MaryXml::getNextSiblingElement(syllable);
        if (!nextSyllable.empty()) {
            return 0;
        }
        pugi::xml_node sentence = MaryXml::getAncestor(syllable, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        token_boundary_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;

        pugi::xml_node word = syllable.parent();
        if (word.empty()) {
            return 0;
        }
        bool startPosition = false;
        pugi::xml_node nextNode;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (startPosition) {
                if (strcmp(node.name(), MaryXml::BOUNDARY) == 0 || ( (strcmp(node.name(), MaryXml::TOKEN) == 0) && MaryXml::hasAttribute(node, "ph"))) {
                    nextNode = node;
                    break;
                }
            }
            if (nodes[i] == word) {
                startPosition = true;
            }
        }

        if (nextNode.empty()) {
            return 4;
        }
        if (strcmp(nextNode.name(), "t") == 0) {
            return 1;
        }
        std::string biIndex = nextNode.attribute("breakindex").as_string();
        if (biIndex.empty()) {
            return 1;
        }
        int bi = std::stoi(biIndex);
        if (bi >= 4) {
            return 4;
        } else if(bi == 3) {
            return 3;
        }
        return 1;
    }
        

    /*
     * classifies the syllable as "single", "final", "initial" or "mid"
     */
    PositionType::PositionType(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    PositionType::~PositionType(){}

    int PositionType::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        std::string type;
        if (MaryXml::getNextSiblingElement(syllable).empty()) {
            if (MaryXml::getPrevSiblingElement(syllable).empty()) {
                type = "single";
            } else {
                type = "final";
            }
        } else if (MaryXml::getPrevSiblingElement(syllable).empty()) {
            type = "initial";
        } else {
            type = "mid";
        }
        return translator_.getValue(type);
    }







}

