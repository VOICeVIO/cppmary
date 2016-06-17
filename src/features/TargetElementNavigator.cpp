//
// Created by sooda on 16/6/15.
//

#include "features/TargetElementNavigator.h"
#include "common.h"

namespace cppmary {
    pugi::xml_node SegmentNavigator::getElement(Target target) {
        return target.getMaryElement();
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
        doc.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        int index = 0;
        for (int i = 0; i < nodes.size(); i++) {
            //is the node compre right?
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

}
