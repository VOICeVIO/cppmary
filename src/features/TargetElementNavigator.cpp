//
// Created by sooda on 16/6/15.
//

#include "features/TargetElementNavigator.h"

namespace cppmary {
    pugi::xml_node SegmentNavigator::getElement(Target target) {
        return target.getMaryElement();
    }
}
