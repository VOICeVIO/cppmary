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
        /*synthses data with label string*/
        virtual std::string process(std::string labelString);
        /*synthses data with label file*/
        void synthesisWithLableName(std::string labelFile);
    private:
        HTS_Engine engine_;
    };
}


#endif //CPPMARY_HTSENGINE_H
