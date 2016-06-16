//
// Created by sooda on 16/6/15.
//

#ifndef CPPMARY_MARYGENERICFEATUREPROCESSORS_H
#define CPPMARY_MARYGENERICFEATUREPROCESSORS_H

//通用特征定义MaryGenericFeatureProcessors的下半部分, 原本在例如,Phone, nextPhone等. 包含大量的类,大量的对象..
namespace cppmary {
    //class GenericFeatureProcessors {
    //};
    const int RAIL_LIMIT = 19;
    class PhraseNumSyls : public ByteValuedFeatureProcessor {
    public:
        virtual std::string getName();
        virtual std::vector<std::string> getValues();
        virtual int process(Target target);
        PhraseNumSyls();
        ~PhraseNumSyls();
    };
}


#endif //CPPMARY_MARYGENERICFEATUREPROCESSORS_H
