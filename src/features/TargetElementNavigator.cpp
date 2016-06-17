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
}
