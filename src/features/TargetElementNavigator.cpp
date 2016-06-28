//
// Created by sooda on 16/6/15.
//

#include "features/TargetElementNavigator.h"
#include "common.h"

namespace cppmary {

    pugi::xml_node TargetElementNavigator::prevElement(std::vector<pugi::xml_node> nodes, pugi::xml_node current) {
        int index = 0;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] == current) {
                index = i;
                break;
            }
        }
        if (index != 0) {
            return nodes[index-1];
        } else {
            return pugi::xml_node();
        }
    }

    pugi::xml_node TargetElementNavigator::prevPrevElement(std::vector<pugi::xml_node> nodes, pugi::xml_node current) {
        int index = 0;
        for (int i = 2; i < nodes.size(); i++) {
            if (nodes[i] == current) {
                index = i;
                break;
            }
        }
        if (index != 0) {
            return nodes[index-2];
        } else {
            return pugi::xml_node();
        }
    }

    pugi::xml_node TargetElementNavigator::nextElement(std::vector<pugi::xml_node> nodes, pugi::xml_node current) {
        int index = -1;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] == current) {
                index = i;
                break;
            }
        }
        if (index >= 0 && index < nodes.size()-1) {
            return nodes[index+1];
        } else {
            return pugi::xml_node();
        }
    }

    pugi::xml_node TargetElementNavigator::nextNextElement(std::vector<pugi::xml_node> nodes, pugi::xml_node current) {
        int index = -1;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] == current) {
                index = i;
                break;
            }
        }
        if (index >= 0 && index < nodes.size()-2) {
            return nodes[index+2];
        } else {
            return pugi::xml_node();
        }
    }

    pugi::xml_node SegmentNavigator::getElement(Target target) {
        return target.getMaryElement();
    }

    pugi::xml_node PrevSegmentNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }
        cppmary::phone_boundary_walker tw;
        pugi::xml_node doc = segment.root();
        doc.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return prevElement(nodes, segment);
    }

    pugi::xml_node PrevPrevSegmentNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }
        cppmary::phone_boundary_walker tw;
        pugi::xml_node doc = segment.root();
        doc.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return prevPrevElement(nodes, segment);
    }

    pugi::xml_node NextSegmentNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }
        cppmary::phone_boundary_walker tw;
        pugi::xml_node doc = segment.root();
        doc.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return nextElement(nodes, segment);
    }

    pugi::xml_node NextNextSegmentNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }
        cppmary::phone_boundary_walker tw;
        pugi::xml_node doc = segment.root();
        doc.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return nextNextElement(nodes, segment);
    }

    pugi::xml_node SyllableNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty() || strcmp(segment.name(), "ph")) {
            return pugi::xml_node();
        }
        pugi::xml_node syllable = segment.parent();
        if (strcmp(syllable.name(), "syllable")) {
            XLOG(ERROR) << "segment parent tag is wrong" << syllable.name();
        }
        return syllable;
    }

    pugi::xml_node WordNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (strcmp(segment.name(), "boundary") == 0) { //boundary没有token父节点
            return segment;
        }
        if (segment.empty()) {
            return pugi::xml_node();
        }
        pugi::xml_node word = MaryXml::getAncestor(segment, "t");
        if (word.empty()) {
            XLOG(ERROR) << "segment " << segment.name() << " have not word parent " << target.getName();
            return pugi::xml_node();
        }
        return word;
    }

    pugi::xml_node NextWordNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }
        pugi::xml_node current;
        if (strcmp(segment.name(), "ph") == 0) {
            current = MaryXml::getAncestor(segment, "t");
            if (current.empty()) {
                return pugi::xml_node();
            }
        } else { //boundary
            current = segment;
        }

        pugi::xml_node sentence = MaryXml::getAncestor(segment, "s");
        if (sentence.empty()) {
            return pugi::xml_node();
        }
        token_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return nextElement(nodes, current);
    }

    pugi::xml_node PrevWordNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }
        pugi::xml_node current;
        if (strcmp(segment.name(), "ph") == 0) {
            current = MaryXml::getAncestor(segment, "t");
            if (current.empty()) {
                return pugi::xml_node();
            }
        } else { //boundary
            current = segment;
        }

        pugi::xml_node sentence = MaryXml::getAncestor(segment, "s");
        if (sentence.empty()) {
            return pugi::xml_node();
        }
        token_walker tw;
        sentence.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int index = 0;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] == current) {
                index = i;
                break;
            }
        }
        if (index != 0) {
            return nodes[index-1];
        } else {
            return pugi::xml_node();
        }
    }

    pugi::xml_node PrevSyllableNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }

        pugi::xml_node current;
        if (strcmp(segment.name(), "ph") == 0) {
            pugi::xml_node syllable = segment.parent();
            if (syllable.empty()) {
                return pugi::xml_node();
            }
            current = syllable;
        } else {
            current = segment;
        }

        syllable_boundary_walker tw;
        pugi::xml_node doc = segment.root();
        //pugi::xml_node doc = segment.parent().parent(); //traverse subtree by setting the root node
        doc.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return prevElement(nodes, current);
    }

    pugi::xml_node PrevPrevSyllableNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }

        pugi::xml_node current;
        if (strcmp(segment.name(), "ph") == 0) {
            pugi::xml_node syllable = segment.parent();
            if (syllable.empty()) {
                return pugi::xml_node();
            }
            current = syllable;
        } else {
            current = segment;
        }

        syllable_boundary_walker tw;
        pugi::xml_node doc = segment.root();
        doc.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return prevPrevElement(nodes, current);
    }


    pugi::xml_node NextSyllableNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }
        pugi::xml_node current;
        if (strcmp(segment.name(), "ph") == 0) {
            pugi::xml_node syllable = segment.parent();
            if (syllable.empty()) {
                return pugi::xml_node();
            }
            current = syllable;
        } else {
            current = segment;
        }
        syllable_boundary_walker tw;
        pugi::xml_node doc = segment.root();
        doc.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int index = -1;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] == current) {
                index = i;
                break;
            }
        }
        if (index >= 0 && index < nodes.size()-1) {
            return nodes[index+1];
        } else {
            return pugi::xml_node();
        }
    }

    pugi::xml_node NextNextSyllableNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }
        pugi::xml_node current;
        if (strcmp(segment.name(), "ph") == 0) {
            pugi::xml_node syllable = segment.parent();
            if (syllable.empty()) {
                return pugi::xml_node();
            }
            current = syllable;
        } else {
            current = segment;
        }
        syllable_boundary_walker tw;
        pugi::xml_node doc = segment.root();
        doc.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        return nextNextElement(nodes, current);
    }

    pugi::xml_node LastSyllableInPhraseNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }
        pugi::xml_node phrase = MaryXml::getAncestor(segment, "phrase");
        if (phrase.empty()) {
            return pugi::xml_node();
        }
        syllable_walker tw;
        phrase.traverse(tw);
        pugi::xml_node last = tw.nodes_.back();
        if (last.empty()) {
            XLOG(ERROR) << "segment " << segment.name() << " have not last syllable " << target.getName();
            return pugi::xml_node();
        }
        return last;
    }

    pugi::xml_node LastSyllableInWordNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }
        pugi::xml_node word;
        if (strcmp(segment.name(), "ph") == 0) {
            word = MaryXml::getAncestor(segment, "t");
            if (word.empty()) {
                return pugi::xml_node();
            }
        } else { //boundary
            return pugi::xml_node();
        }
        syllable_walker tw;
        word.traverse(tw);
        pugi::xml_node last = tw.nodes_.back();
        if (last.empty()) {
            XLOG(ERROR) << "segment " << segment.name() << " have not last syllable " << target.getName();
            return pugi::xml_node();
        }
        return last;
    }

    pugi::xml_node FirstSyllableInWordNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }
        pugi::xml_node word;
        if (strcmp(segment.name(), "ph") == 0) {
            word = MaryXml::getAncestor(segment, "t");
            if (word.empty()) {
                return pugi::xml_node();
            }
        } else { //boundary
            return pugi::xml_node();
        }
        syllable_walker tw;
        word.traverse(tw);
        pugi::xml_node last = tw.nodes_.front();
        if (last.empty()) {
            XLOG(ERROR) << "segment " << segment.name() << " have not last syllable " << target.getName();
            return pugi::xml_node();
        }
        return last;
    }

    pugi::xml_node LastWordInSentenceNavigator::getElement(Target target) {
        pugi::xml_node segment = target.getMaryElement();
        if (segment.empty()) {
            return pugi::xml_node();
        }
        pugi::xml_node sentence = MaryXml::getAncestor(segment, MaryXml::SENTENCE);
        token_walker tw;
        sentence.traverse(tw);
        pugi::xml_node last = tw.nodes_.back();
        if (last.empty()) {
            return pugi::xml_node();
        }
        return last;
    }


}
