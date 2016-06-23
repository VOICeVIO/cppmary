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
    const std::string ZHPOS[46] = { "0", "AG", "A", "AD", "AN", "B", "C", "DG", "D", "E",
                                    "F", "G", "H", "I", "J", "K", "L", "M", "NG", "N",
                                    "NR", "NS", "NT", "NZ", "O", "P", "Q", "R", "S", "TG",
                                    "T", "U", "VG", "V", "VD", "VN", "W", "X", "Y", "Z",
                                    "NL","NW","VF","VX","VI","VL" };
    class PhraseNumSyls : public FeatureProcessor  {
    public:
        virtual std::string getName();
        virtual std::vector<std::string> getValues();
        virtual int process(Target target);
        PhraseNumSyls(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        ~PhraseNumSyls();
    };
    
    class Zhtone : public FeatureProcessor {
        public:
            virtual std::string getName();
            virtual std::vector<std::string> getValues();
            virtual int process(Target target);
            Zhtone(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
            ~Zhtone();
    };

}


#endif //CPPMARY_MARYGENERICFEATUREPROCESSORS_H
