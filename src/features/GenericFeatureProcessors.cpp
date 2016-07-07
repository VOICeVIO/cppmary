//
// Created by sooda on 16/6/15.
//

#include "feature.h"
#include "features/GenericFeatureProcessors.h"
#include "pugixml/pugixml.hpp"
#include "common.h"

namespace cppmary {

    /*
     * the token syllable of current phrase
     */
    PhraseNumSyls::PhraseNumSyls(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) :
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
    PhraseNumWords::PhraseNumWords(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) :
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
    WordNumSyls::WordNumSyls(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) :
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
    WordNumSegs::WordNumSegs(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) :
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
    SylNumSegs::SylNumSegs(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) :
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
     * the phrase amount of current sentence
     */
    SentenceNumPhrases::SentenceNumPhrases(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) :
                FeatureProcessor(name, possibleValues, navigator) {
    }

    SentenceNumPhrases::~SentenceNumPhrases() {
    }

    int SentenceNumPhrases::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node sentence = MaryXml::getAncestor(segment, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        phrase_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return nodes.size() > RAIL_LIMIT ? RAIL_LIMIT : nodes.size();
    }

    /*
     * the word amount of current sentence
     */
    SentenceNumWords::SentenceNumWords(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) :
                FeatureProcessor(name, possibleValues, navigator) {
    }

    SentenceNumWords::~SentenceNumWords() {
    }

    int SentenceNumWords::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node sentence = MaryXml::getAncestor(segment, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        token_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return nodes.size() > RAIL_LIMIT ? RAIL_LIMIT : nodes.size();
    }
    /*
     * The edge type of current word
     */
    Edge::Edge(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    Edge::~Edge() { }

    int Edge::process(Target target) {
        pugi::xml_node token = navigator_->getElement(target);
        if (token.empty()) {
            return 0;
        }
        pugi::xml_node sentence = MaryXml::getAncestor(token, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        std::string type;
        token_boundary_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        pugi::xml_node prevToken = navigator_->prevElement(nodes, token);
        pugi::xml_node nextToken = navigator_->nextElement(nodes, token);
        if (nextToken.empty()) {
            if (prevToken.empty()) {
                type = "others";
            } else {
                type = "outbound";
            }
        } else if (prevToken.empty()) {
            type = "outbound";
        } else {
            std::string nextTokenPos = nextToken.attribute("pos").as_string();
            if (nextTokenPos == "X") {
                type = "outbound";
            } else {
                type = "others";
            }
            std::string bi = nextToken.attribute("breakindex").as_string();
            if (!bi.empty()) {
                int biValue = std::stoi(bi);
                if (biValue == 3) {
                    type = "innerbound";
                }
            }
            std::string pbi = prevToken.attribute("breakindex").as_string();
            if (!pbi.empty()) {
                int biValue = std::stoi(pbi);
                if (biValue == 3) {
                    type = "innerbound";
                }
            }
        }
        return translator_.getValue(type);
    }

    /*
     * The style of current target
     */
    Style::Style(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    Style::~Style() { }

    int Style::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node prosody = MaryXml::getAncestor(segment, MaryXml::PROSODY);
        if (prosody.empty()) {
            return 0;
        } else {
            std::string style = prosody.attribute("style").as_string();
            if (style.empty()) {
                style = "0";
            }
            return translator_.getValue(style);
        }
    }

    /*
     * The Tobi endtone of current syllable
     */
    TobiEndtone::TobiEndtone(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    TobiEndtone::~TobiEndtone() { }

    int TobiEndtone::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        pugi::xml_node sentence = MaryXml::getAncestor(syllable, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        phone_boundary_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        bool start = false;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (start == true) {
                if (strcmp(node.name(), MaryXml::BOUNDARY) == 0) {
                    return 0;
                } else {
                    std::string endtone = node.attribute("tone").as_string();
                    if (endtone.empty()) {
                        return 0;
                    } else {
                        return translator_.getValue(endtone);
                    }
                }
            }
            if (node == syllable) {
                start = true;
            }
        }
        return 0;
    }

    /*
     * The Tobi accent of current syllable
     */
    TobiAccent::TobiAccent(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    Accented::Accented(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    AccentedSylsFromPhraseStart::AccentedSylsFromPhraseStart(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    AccentedSylsFromPhraseEnd::AccentedSylsFromPhraseEnd(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    SylsFromPrevAccented::SylsFromPrevAccented(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    SylsToNextAccented::SylsToNextAccented(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    SylsFromPhraseStart::SylsFromPhraseStart(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    SylsFromPhraseEnd::SylsFromPhraseEnd(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
     * the word amount from current phrase start
     */
    WordsFromPhraseStart::WordsFromPhraseStart(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    WordsFromPhraseStart::~WordsFromPhraseStart(){}

    int WordsFromPhraseStart::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node phrase = MaryXml::getAncestor(segment, MaryXml::PHRASE);
        if (phrase.empty()) {
            return 0;
        }
        pugi::xml_node current;
        pugi::xml_node word = MaryXml::getAncestor(segment, MaryXml::TOKEN);
        if (word.empty()) {
            current = segment;
        } else {
            current = word;
        }
        //token_boundary_walker tw; //diff from marytts for boundary
        token_walker tw;
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementFromStart(nodes, current);
        return count;
    }

    /*
     * the word amount from current phrase end
     */
    WordsFromPhraseEnd::WordsFromPhraseEnd(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    WordsFromPhraseEnd::~WordsFromPhraseEnd(){}

    int WordsFromPhraseEnd::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node phrase = MaryXml::getAncestor(segment, MaryXml::PHRASE);
        if (phrase.empty()) {
            return 0;
        }
        pugi::xml_node current;
        pugi::xml_node word = MaryXml::getAncestor(segment, MaryXml::TOKEN);
        if (word.empty()) {
            current = segment;
        } else {
            current = word;
        }
        token_walker tw;
        //token_boundary_walker tw; //diff from marytts for boundary
        phrase.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementToEnd(nodes, current);
        return count;
    }

    /*
     * the word amount from current sentence start
     */
    WordsFromSentenceStart::WordsFromSentenceStart(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    WordsFromSentenceStart::~WordsFromSentenceStart(){}

    int WordsFromSentenceStart::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node sentence = MaryXml::getAncestor(segment, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        pugi::xml_node current;
        pugi::xml_node word = MaryXml::getAncestor(segment, MaryXml::TOKEN);
        if (word.empty()) {
            current = segment;
        } else {
            current = word;
        }
        token_walker tw;
        //token_boundary_walker tw; //diff from marytts for boundary
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementFromStart(nodes, current);
        return count;
    }


    /*
     * the word amount from current sentence end
     */
    WordsFromSentenceEnd::WordsFromSentenceEnd(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    WordsFromSentenceEnd::~WordsFromSentenceEnd(){}

    int WordsFromSentenceEnd::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node sentence = MaryXml::getAncestor(segment, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        pugi::xml_node current;
        pugi::xml_node word = MaryXml::getAncestor(segment, MaryXml::TOKEN);
        if (word.empty()) {
            current = segment;
        } else {
            current = word;
        }
        token_walker tw;
        //token_boundary_walker tw; //diff from marytts for boundary
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementToEnd(nodes, current);
        return count;
    }


    /*
     * the phrase amount from current sentence start
     */
    PhrasesFromSentenceStart::PhrasesFromSentenceStart(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    PhrasesFromSentenceStart::~PhrasesFromSentenceStart(){}

    int PhrasesFromSentenceStart::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node sentence = MaryXml::getAncestor(segment, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        pugi::xml_node current;
        pugi::xml_node phrase = MaryXml::getAncestor(segment, MaryXml::PHRASE);
        if (phrase.empty()) {
            current = segment;
        } else {
            current = phrase;
        }
        phrase_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementFromStart(nodes, current);
        return count;
    }

    /*
     * the phrase amount from current sentence end
     */
    PhrasesFromSentenceEnd::PhrasesFromSentenceEnd(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    PhrasesFromSentenceEnd::~PhrasesFromSentenceEnd(){}

    int PhrasesFromSentenceEnd::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node sentence = MaryXml::getAncestor(segment, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        pugi::xml_node current;
        pugi::xml_node phrase = MaryXml::getAncestor(segment, MaryXml::PHRASE);
        if (phrase.empty()) {
            current = segment;
        } else {
            current = phrase;
        }
        phrase_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = countElementToEnd(nodes, current);
        return count;
    }


    /*
     * the segment amount from syllable start
     */
    SegsFromSylStart::SegsFromSylStart(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    SegsFromSylEnd::SegsFromSylEnd(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    SegsFromWordStart::SegsFromWordStart(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    SegsFromWordEnd::SegsFromWordEnd(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    SylsFromWordStart::SylsFromWordStart(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    SylsFromWordEnd::SylsFromWordEnd(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
    SylBreak::SylBreak(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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
        try {
            int bi = std::stoi(biIndex);
            if (bi >= 4) {
                return 4;
            } else if (bi == 3) {
                return 3;
            }
        } catch (std::exception e) {
            XLOG(ERROR) << e.what() << std::endl;
        }
        return 1;
    }

    /*
     * determinines the breakIndex
     */
    BreakIndex::BreakIndex(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    BreakIndex::~BreakIndex(){}

    int BreakIndex::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node word = MaryXml::getAncestor(segment, MaryXml::TOKEN);
        if (word.empty()) {
            return 0;
        }
        //pugi::xml_node nextPhone = MaryXml::getNextSiblingElement(segment);
        phone_walker phoneTw;
        word.traverse(phoneTw);
        pugi::xml_node nextPhone;
        int index = 0;
        std::vector<pugi::xml_node> phoneNodes = phoneTw.nodes_;
        for (int i = phoneNodes.size()-2; i >= 0; i--) {
            pugi::xml_node node = phoneNodes[i];
            if (node == segment) {
                index = i + 1;
            }
        }
        if (index != 0) {
            return 0;
        }
        pugi::xml_node sentence = MaryXml::getAncestor(segment, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        token_boundary_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
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
        try {
            int bi = std::stoi(biIndex);
            if (bi > 6) {
                bi = 6;
            } else if (bi < 3) {
                bi = 2;
            }
            return bi;
        } catch (std::exception e) {
            XLOG(ERROR) << e.what() << std::endl;
        }
        return 1;
    }
        

    /*
     * classifies the syllable as "single", "final", "initial" or "mid"
     */
    PositionType::PositionType(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
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


    /*
     * check if segment is pause
     */
    IsPause::IsPause(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    IsPause::~IsPause(){}

    int IsPause::process(Target target) {
        pugi::xml_node segment = navigator_->getElement(target);
        if (segment.empty()) {
            return 0;
        }
        if (strcmp(segment.name(), MaryXml::BOUNDARY) == 0) {
            return 1;
        }
        return 0;
    }


    /*
     * determine the word puctuation
     */
    WordPunc::WordPunc(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    WordPunc::~WordPunc(){}

    int WordPunc::process(Target target) {
        pugi::xml_node word = navigator_->getElement(target);
        pugi::xml_node sentence = MaryXml::getAncestor(word, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        pugi::xml_node nextToken = MaryXml::getNextSiblingElement(word);
        if (nextToken.empty() || strcmp(nextToken.name(), MaryXml::TOKEN) || MaryXml::hasAttribute(nextToken, "ph")) {
            return 0;
        }
        std::string text = nextToken.child_value();
        text = trim(text);
        return translator_.getValue(text);
    }

    /*
     * determine the next word puctuation
     */
    NextPunctuation::NextPunctuation(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    NextPunctuation::~NextPunctuation(){}

    int NextPunctuation::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node word = MaryXml::getAncestor(segment, MaryXml::TOKEN);
        pugi::xml_node sentence = MaryXml::getAncestor(segment, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }

        token_punc_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        bool startPosition = false;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (startPosition) {
                if (MaryXml::hasAttribute(node, "ph")) {
                    continue;
                }
                std::string text = node.child_value();
                text = trim(text);
                return translator_.getValue(text);
            }
            if (node == word) {
                startPosition = true;
            }
        }
        return 0;
    }


    /*
     * determine the prev word puctuation
     */
    PrevPunctuation::PrevPunctuation(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    PrevPunctuation::~PrevPunctuation(){}

    int PrevPunctuation::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        pugi::xml_node word = MaryXml::getAncestor(segment, MaryXml::TOKEN);
        pugi::xml_node sentence = MaryXml::getAncestor(segment, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        token_punc_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        bool startPosition = false;
        for (int i = nodes.size()-1; i >= 0; i--) {
            pugi::xml_node node = nodes[i];
            if (startPosition) {
                if (MaryXml::hasAttribute(node, "ph")) {
                    continue;
                }
                std::string text = node.child_value();
                text = trim(text);
                return translator_.getValue(text);
            }
            if (node == word) {
                startPosition = true;
            }
        }
        return 0;
    }


    /*
     * determine distance to next punctuation in the sentence
     */
    WordsToNextPunctuation::WordsToNextPunctuation(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    WordsToNextPunctuation::~WordsToNextPunctuation(){}

    int WordsToNextPunctuation::process(Target target) {
        pugi::xml_node word = navigator_->getElement(target);
        if (!MaryXml::hasAttribute(word, "ph")) {
            return 0;
        }
        if (word.empty()) {
            return 0;
        }
        pugi::xml_node sentence = MaryXml::getAncestor(word, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        token_punc_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = 0;
        for (int i = nodes.size()-1; i >= 0; i--) {
            pugi::xml_node node = nodes[i];
            if (node.empty()) {
                continue;
            }
            if (MaryXml::hasAttribute(node, "ph")) {
                count++;
            } else {
                std::string text = node.child_value();
                text = trim(text);
                //int punc = translator_.getValue(text);
                //if (punc > 0) {
                //    count = 0;
                //} else {
                //    count++;
                //}
                count = 0;
            }
            if (node == word || count >= RAIL_LIMIT) {
                break;
            }
        }
        return count;
    }



    /*
     * determine distance to prev punctuation in the sentence
     * the posssibleValue is punc value, not feature value。。
     */
    WordsToPrevPunctuation::WordsToPrevPunctuation(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) : FeatureProcessor(name, possibleValues, navigator) {
    }

    WordsToPrevPunctuation::~WordsToPrevPunctuation(){}

    int WordsToPrevPunctuation::process(Target target) {
        pugi::xml_node word = navigator_->getElement(target);
        if (word.empty()) {
            return 0;
        }
        if (!MaryXml::hasAttribute(word, "ph")) {
            return 0;
        }
        pugi::xml_node sentence = MaryXml::getAncestor(word, MaryXml::SENTENCE);
        if (sentence.empty()) {
            return 0;
        }
        token_punc_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int count = 0;
        for (int i = 0; i < nodes.size(); i++) {
            pugi::xml_node node = nodes[i];
            if (node.empty()) {
                continue;
            }
            if (MaryXml::hasAttribute(node, "ph")) {
                count++;
            } else {
                std::string text = node.child_value();
                text = trim(text);
                count = 0;
                //int punc = translator_.getValue(text);
                //if (punc > 0) {
                //    count = 0;
                //} else {
                //    count++;
                //}
            }
            if (node == word || count >= RAIL_LIMIT) {
                break;
            }
        }
        return count;
    }

    /*
     * onset or coda
     */
    SegOnsetCoda::SegOnsetCoda(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator, AllophoneSet phonset) : FeatureProcessor(name, possibleValues, navigator), phoneset_(phonset) {
    }

    SegOnsetCoda::~SegOnsetCoda(){}

    int SegOnsetCoda::process(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return 0;
        }
        if (strcmp(segment.name(), MaryXml::PHONE) != 0) {
            return 0;
        }

        while (!(segment = MaryXml::getNextSiblingElement(segment)).empty()) {
            std::string ph = segment.attribute("p").as_string();
            if (ph.empty()) {
                continue;
            }
            if (phoneset_.getPhoneFeature(ph, "vc") == "+") {
                return translator_.getValue("onset");
            }
        }
        return translator_.getValue("coda");
    }


}


