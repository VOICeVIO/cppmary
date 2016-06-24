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
    const int RAIL_LIMIT = 19;
    const int ZHTONE_NUM = 6;
    const int ZHPOS_NUM = 46;
    const int TOBIACCENT_NUM = 20;
    const std::string ZHTONES[ZHTONE_NUM] = {"0", "1", "2", "3", "4", "5"};
    const std::string ZHPOS[ZHPOS_NUM] = { "0", "AG", "A", "AD", "AN", "B", "C", "DG", "D", "E",
                                    "F", "G", "H", "I", "J", "K", "L", "M", "NG", "N",
                                    "NR", "NS", "NT", "NZ", "O", "P", "Q", "R", "S", "TG",
                                    "T", "U", "VG", "V", "VD", "VN", "W", "X", "Y", "Z",
                                    "NL","NW","VF","VX","VI","VL" };
    const std::string TOBIACCENTS[TOBIACCENT_NUM] = { "0", "*", "H*", "!H*", "^H*", "L*", "L+H*", "L*+H", "L+!H*", "L*+!H", 
        "L+^H*", "L*+^H", "H+L*", "H+!H*", "H+^H*", "!H+!H*", "^H+!H*", "^H+^H*", "H*+L", "!H*+L" };


    /*
     * the token syllable of current phrase
     */
    class PhraseNumSyls : public FeatureProcessor  {
    public:
        PhraseNumSyls(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~PhraseNumSyls();
        virtual int process(Target target);
    };

    /*
     * the token amount of current phrase
     */
    class PhraseNumWords : public FeatureProcessor  {
    public:
        PhraseNumWords(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~PhraseNumWords();
        virtual int process(Target target);
    };

    /*
     * the syllable amount of current token
     */
    class WordNumSyls : public FeatureProcessor  {
    public:
        WordNumSyls(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~WordNumSyls();
        virtual int process(Target target);
    };

    /*
     * the segment amount of current token
     */
    class WordNumSegs : public FeatureProcessor  {
    public:
        WordNumSegs(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~WordNumSegs();
        virtual int process(Target target);
    };

    /*
     * the segment amount of current syllable
     */
    class SylNumSegs : public FeatureProcessor  {
    public:
        SylNumSegs(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylNumSegs();
        virtual int process(Target target);
    };

    /*
     * The Tobi accent of current syllable
     */
    class TobiAccent : public FeatureProcessor {
    public:
        TobiAccent(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~TobiAccent();
        virtual int process(Target target);
    };

    /*
     * the current syllable is has accente attribute?
     */
    class Accented : public FeatureProcessor {
    public:
        Accented(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~Accented();
        virtual int process(Target target);
    };

    /*
     * the accented syllable amount from current phrase start
     */
    class AccentedSylsFromPhraseStart : public FeatureProcessor {
    public:
        AccentedSylsFromPhraseStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~AccentedSylsFromPhraseStart();
        virtual int process(Target target);
    };
    


    /*
     * the accented syllable amount from current phrase end
     */
    class AccentedSylsFromPhraseEnd : public FeatureProcessor {
    public:
        AccentedSylsFromPhraseEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~AccentedSylsFromPhraseEnd();
        virtual int process(Target target);
    };

    /*
     * the syllable amount from prev accented syllable
     */
    class SylsFromPrevAccented : public FeatureProcessor {
    public:
        SylsFromPrevAccented(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylsFromPrevAccented();
        virtual int process(Target target);
    };

    /*
     * the syllable amount to next accented syllable
     */
    class SylsToNextAccented : public FeatureProcessor {
    public:
        SylsToNextAccented(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylsToNextAccented();
        virtual int process(Target target);
    };

    /*
     * the syllable amount from current phrase start
     */
    class SylsFromPhraseStart : public FeatureProcessor {
    public:
        SylsFromPhraseStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylsFromPhraseStart();
        virtual int process(Target target);
    };

    /*
     * the syllable amount from current phrase end
     */
    class SylsFromPhraseEnd : public FeatureProcessor {
    public:
        SylsFromPhraseEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylsFromPhraseEnd();
        virtual int process(Target target);
    };

}


#endif //CPPMARY_MARYGENERICFEATUREPROCESSORS_H
