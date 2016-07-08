//
// Created by sooda on 16/6/30.
//

#include "modules/InterModules.h"
#include "limonp/Logging.hpp"

namespace cppmary {
    InterModules::InterModules() { }
    InterModules::~InterModules() {
        XLOG(DEBUG) << "deconstruct module " << name_;
    }
}
