//
// Created by sooda on 16/6/30.
//

#ifndef CPPMARY_MARYBASE_H
#define CPPMARY_MARYBASE_H
#include "ReferenceCounted.h"

namespace cppmary {

    class MaryBase : public ReferenceCounted {
    public:
        MaryBase();
        MaryBase(const MaryBase& base);
        virtual ~MaryBase();
    };
}


#endif //CPPMARY_MARYBASE_H
