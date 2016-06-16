//
// Created by sooda on 16/6/15.
//

#ifndef CPPMARY_FEATUREPROCESSOR_H
#define CPPMARY_FEATUREPROCESSOR_H
#include "Target.h"
#include <string>
#include <vector>

//通用特征定义MaryGenericFeatureProcessors的下半部分, 原本在例如,Phone, nextPhone等. 包含大量的类,大量的对象..

namespace cppmary {

    class FeatureProcessorBase {
    public:
        virtual std::string getName() = 0;
    };

    class ByteValuedFeatureProcessor : public FeatureProcessorBase {
    public:
        virtual std::vector<std::string> getValues();
        virtual std::string getName();
        virtual int process(Target target);
        ByteValuedFeatureProcessor();
        virtual ~ByteValuedFeatureProcessor();
    };
}



#endif //CPPMARY_FEATUREPROCESSOR_H
