//
// Created by sooda on 16/6/28.
//

#ifndef CPPMARY_HTSENGINE_H
#define CPPMARY_HTSENGINE_H
#include "../../3rdparty/hts_engine/HTS_engine.h"
#include "modules/InterModules.h"
#include <string>

namespace cppmary {
    class HtsEngine : public InterModules {
    public:
        HtsEngine(const std::string& modelName);
        HtsEngine(const std::string& modelName, const std::string& filterStr);
        ~HtsEngine();
        /*synthses data with label string*/
        virtual std::string process(std::string labelString);
        /*synthses data with label file*/
        void synthesisWithLableName(std::string labelFile);
    private:
        HTS_Engine engine_;
        char** fn_voices_;
    };
}


#endif //CPPMARY_HTSENGINE_H
