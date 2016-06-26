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
    const int POSITIONTYPE_NUM = 5;
    const std::string ZHTONES[ZHTONE_NUM] = {"0", "1", "2", "3", "4", "5"};
    const std::string ZHPOS[ZHPOS_NUM] = { "0", "AG", "A", "AD", "AN", "B", "C", "DG", "D", "E",
                                    "F", "G", "H", "I", "J", "K", "L", "M", "NG", "N",
                                    "NR", "NS", "NT", "NZ", "O", "P", "Q", "R", "S", "TG",
                                    "T", "U", "VG", "V", "VD", "VN", "W", "X", "Y", "Z",
                                    "NL","NW","VF","VX","VI","VL" };
    const std::string TOBIACCENTS[TOBIACCENT_NUM] = { "0", "*", "H*", "!H*", "^H*", "L*", "L+H*", "L*+H", "L+!H*", "L*+!H", 
        "L+^H*", "L*+^H", "H+L*", "H+!H*", "H+^H*", "!H+!H*", "^H+!H*", "^H+^H*", "H*+L", "!H*+L" };
    const std::string POSITIONTYPE[POSITIONTYPE_NUM] = {"0", "single", "final", "initial", "mid"};


    /*
     * the token syllable of current phrase
     * @navigator: null
     */
    class PhraseNumSyls : public FeatureProcessor  {
    public:
        PhraseNumSyls(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~PhraseNumSyls();
        virtual int process(Target target);
    };

    /*
     * the token amount of current phrase
     * @navigator: null
     */
    class PhraseNumWords : public FeatureProcessor  {
    public:
        PhraseNumWords(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~PhraseNumWords();
        virtual int process(Target target);
    };

    /*
     * the syllable amount of current token
     * @navigator: null
     */
    class WordNumSyls : public FeatureProcessor  {
    public:
        WordNumSyls(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~WordNumSyls();
        virtual int process(Target target);
    };

    /*
     * the segment amount of current token
     * @navigator: null
     */ class WordNumSegs : public FeatureProcessor  {
    public:
        WordNumSegs(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~WordNumSegs();
        virtual int process(Target target);
    };

    /*
     * the segment amount of current syllable
     * @navigator: null
     */
    class SylNumSegs : public FeatureProcessor  {
    public:
        SylNumSegs(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylNumSegs();
        virtual int process(Target target);
    };

    /*
     * The Tobi accent of current syllable
     * @navigator: syllableNavigator
     */
    class TobiAccent : public FeatureProcessor {
    public:
        TobiAccent(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~TobiAccent();
        virtual int process(Target target);
    };

    /*
     * the current syllable is has accente attribute?
     * @navigator: syllableNavigator
     */
    class Accented : public FeatureProcessor {
    public:
        Accented(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~Accented();
        virtual int process(Target target);
    };

    /*
     * the accented syllable amount from current phrase start
     * @navigator: syllableNavigator
     */
    class AccentedSylsFromPhraseStart : public FeatureProcessor {
    public:
        AccentedSylsFromPhraseStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~AccentedSylsFromPhraseStart();
        virtual int process(Target target);
    };
    
    /*
     * the accented syllable amount from current phrase end
     * @navigator: syllableNavigator
     */
    class AccentedSylsFromPhraseEnd : public FeatureProcessor {
    public:
        AccentedSylsFromPhraseEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~AccentedSylsFromPhraseEnd();
        virtual int process(Target target);
    };

    /*
     * the syllable amount from prev accented syllable
     * @navigator: syllableNavigator
     * @type: dis
     */
    class SylsFromPrevAccented : public FeatureProcessor {
    public:
        SylsFromPrevAccented(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylsFromPrevAccented();
        virtual int process(Target target);
    };

    /*
     * the syllable amount to next accented syllable
     * @navigator: syllableNavigator
     * @type: dis
     */
    class SylsToNextAccented : public FeatureProcessor {
    public:
        SylsToNextAccented(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylsToNextAccented();
        virtual int process(Target target);
    };

    /*
     * the syllable amount from current phrase start
     * @navigator: syllableNavigator
     * @type: count
     */
    class SylsFromPhraseStart : public FeatureProcessor {
    public:
        SylsFromPhraseStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylsFromPhraseStart();
        virtual int process(Target target);
    };

    /*
     * the syllable amount from current phrase end
     * @navigator: syllableNavigator
     * @type: count
     */
    class SylsFromPhraseEnd : public FeatureProcessor {
    public:
        SylsFromPhraseEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylsFromPhraseEnd();
        virtual int process(Target target);
    };

    /*
     * the segment amount from syllable start
     * @navigator: null
     * @type: count
     */
    class SegsFromSylStart : public FeatureProcessor {
    public:
        SegsFromSylStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SegsFromSylStart();
        virtual int process(Target target);
    };

    /*
     * the segment amount from syllable end
     * @navigator: null
     * @type: count
     */
    class SegsFromSylEnd : public FeatureProcessor {
    public:
        SegsFromSylEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SegsFromSylEnd();
        virtual int process(Target target);
    };

    /*
     * the segment amount from word start
     * @navigator: null
     * @type: count
     */
    class SegsFromWordStart : public FeatureProcessor {
    public:
        SegsFromWordStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SegsFromWordStart();
        virtual int process(Target target);
    };

    /*
     * the segment amount from word end
     * @navigator: null
     * @type: count
     */
    class SegsFromWordEnd : public FeatureProcessor {
    public:
        SegsFromWordEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SegsFromWordEnd();
        virtual int process(Target target);
    };

    /*
     * the syllable from word start
     * @navigator: syllableNavigator
     * @type: count
     */
    class SylsFromWordStart : public FeatureProcessor {
    public:
        SylsFromWordStart(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylsFromWordStart();
        virtual int process(Target target);
    };

    /*
     * the syllable from word end
     * @navigator: syllableNavigator
     * @type: count
     */
    class SylsFromWordEnd : public FeatureProcessor {
    public:
        SylsFromWordEnd(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylsFromWordEnd();
        virtual int process(Target target);
    };

    /*
     * determinines the break level after this syllable
     * @navigator: syllableNavigator
     */
    class SylBreak : public FeatureProcessor {
    public:
        SylBreak(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~SylBreak();
        virtual int process(Target target);
    };


    /*
     * classifies the syllable as "single", "final", "initial" or "mid"
     * @navigator: syllableNavigator
     */
    class PositionType : public FeatureProcessor {
    public:
        PositionType(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~PositionType();
        virtual int process(Target target);
    };


}


#endif //CPPMARY_MARYGENERICFEATUREPROCESSORS_H
