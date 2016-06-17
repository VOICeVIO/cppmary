//
// Created by sooda on 16/6/15.
//

#ifndef CPPMARY_MARYGENERICFEATUREPROCESSORS_H
#define CPPMARY_MARYGENERICFEATUREPROCESSORS_H
#include "TargetElementNavigator.h"
#include "StringTranslator.h"
#include <string>
#include <vector>

//通用特征定义MaryGenericFeatureProcessors的下半部分, 原本在例如,Phone, nextPhone等. 包含大量的类,大量的对象..
namespace cppmary {
    //class GenericFeatureProcessors {
    //};
    const int RAIL_LIMIT = 19;
    const std::string ZHTONES[6] = {"0", "1", "2", "3", "4", "5"};
    class PhraseNumSyls : public FeatureProcessor  {
    public:
        virtual std::string getName();
        virtual std::vector<std::string> getValues();
        virtual int process(Target target);
        PhraseNumSyls();
        ~PhraseNumSyls();
    };
    
    class Zhtone : public FeatureProcessor {
        public:
            virtual std::string getName();
            virtual std::vector<std::string> getValues();
            virtual int process(Target target);
            Zhtone(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
            ~Zhtone();
        private:
            std::string name_;
            TargetElementNavigator* navigator_;
            StringTranslator translator_;
    };
}


#endif //CPPMARY_MARYGENERICFEATUREPROCESSORS_H
