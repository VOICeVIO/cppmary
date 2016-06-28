//
// Created by sooda on 16/6/28.
//

#ifndef CPPMARY_HTSENGINE_H
#define CPPMARY_HTSENGINE_H
#include "../../3rdparty/hts_engine/HTS_engine.h"

namespace cppmary {
    class HtsEngine : public InterModules {
    public:
        HtsEngine(const std::string& modelName);
        ~HtsEngine();
        //the input is label filename or its string;
        virtual std::string process(std::string labelFile);
    private:
        HTS_Engine engine_;
    };
}


#endif //CPPMARY_HTSENGINE_H
