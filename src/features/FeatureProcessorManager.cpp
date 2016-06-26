//
// Created by sooda on 16/6/15.
//

#include "features/FeatureProcessorManager.h"
#include "features/GenericFeatureProcessors.h"
#include "features/LanguageFeatureProcessors.h"

namespace cppmary {
    FeatureProcessorManager::FeatureProcessorManager(std::string localeString, std::string phonesetXmlStr) {
        //locale process
        localeString_ = localeString;
        setupGenericFeatureProcessors();
        AllophoneSet phonset(phonesetXmlStr);
        setupPhoneFeatureProcessors(phonset);
    }

    FeatureProcessorManager::~FeatureProcessorManager() {
        std::map<std::string, FeatureProcessor *>::iterator iter;
        for (iter = processors_.begin(); iter != processors_.end(); ++iter) {
            delete iter->second;
        }
    }

    void FeatureProcessorManager::setupGenericFeatureProcessors() {

        std::vector<std::string> intValues;
        for (int i = 0; i <= RAIL_LIMIT; i++) {
            intValues.push_back(std::to_string(i));
        }
        addFeatureProcessor(new PhraseNumSyls("phrase_numsyls", intValues, NULL));
        addFeatureProcessor(new SegsFromSylStart("segs_from_syl_start", intValues, NULL));
        addFeatureProcessor(new SegsFromSylEnd("segs_from_syl_end", intValues, NULL));
        std::vector<std::string> zhToneValues;
        zhToneValues.assign(ZHTONES, ZHTONES+ZHTONE_NUM);
        TargetElementNavigator* syllableNav = new SyllableNavigator();
        TargetElementNavigator* prevSyllableNav = new PrevSyllableNavigator();
        TargetElementNavigator* prevPrevSyllableNav = new PrevPrevSyllableNavigator();
        TargetElementNavigator* nextSyllableNav = new NextSyllableNavigator();
        TargetElementNavigator* nextnextSyllableNav = new NextNextSyllableNavigator();
        TargetElementNavigator* wordNav = new WordNavigator();
        TargetElementNavigator* firstSylInWord = new FirstSyllableInWordNavigator();
        TargetElementNavigator* lastSylInPhrase = new LastSyllableInPhraseNavigator();
        addFeatureProcessor(new Zhtone("zhtone", zhToneValues, syllableNav));
        addFeatureProcessor(new Zhtone("prev_zhtone", zhToneValues, prevSyllableNav));
        addFeatureProcessor(new Zhtone("next_zhtone", zhToneValues, nextSyllableNav));
        addFeatureProcessor(new Zhtone("nextnext_zhtone", zhToneValues, nextnextSyllableNav));
        addFeatureProcessor(new Zhtone("prevprev_zhtone", zhToneValues, prevPrevSyllableNav));
        addFeatureProcessor(new Zhtone("phrase_zhtone", zhToneValues, lastSylInPhrase));


        std::vector<std::string> tobiValues;
        tobiValues.assign(TOBIACCENTS, TOBIACCENTS+TOBIACCENT_NUM);
        addFeatureProcessor(new TobiAccent("tobiAccent", tobiValues, syllableNav));
        addFeatureProcessor(new TobiAccent("prev_tobiAccent", tobiValues, prevSyllableNav));
        addFeatureProcessor(new TobiAccent("prevprev_tobiAccent", tobiValues, prevPrevSyllableNav));
        addFeatureProcessor(new TobiAccent("next_tobiAccent", tobiValues, nextSyllableNav));
        addFeatureProcessor(new TobiAccent("nextnext_tobiAccent", tobiValues, nextnextSyllableNav));

        std::vector<std::string> posValues;
        posValues.assign(ZHPOS, ZHPOS+ZHPOS_NUM);
        addFeatureProcessor(new Pos("pos", posValues, wordNav));

        std::vector<std::string> boolValues;
        boolValues.push_back("0");
        boolValues.push_back("1");
        addFeatureProcessor(new Accented("accented", boolValues, syllableNav));
        addFeatureProcessor(new Accented("prev_accent", boolValues, prevSyllableNav));
        addFeatureProcessor(new AccentedSylsFromPhraseStart("accented_syls_from_phrase_start", intValues, syllableNav));
        addFeatureProcessor(new AccentedSylsFromPhraseEnd("accented_syls_from_phrase_end", intValues, syllableNav));
        addFeatureProcessor(new SylsFromPrevAccented("syls_from_prev_accent", intValues, syllableNav));

        addFeatureProcessor(new SylsFromPhraseStart("syls_from_phrase_start", intValues, syllableNav));
        addFeatureProcessor(new SylsFromPhraseEnd("syls_from_phrase_end", intValues, syllableNav));

        addFeatureProcessor(new WordsFromPhraseStart("words_from_phrase_start", intValues, NULL));
        addFeatureProcessor(new WordsFromPhraseEnd("words_from_phrase_end", intValues, NULL));

        addFeatureProcessor(new WordsFromSentenceStart("words_from_sentence_start", intValues, NULL));
        addFeatureProcessor(new WordsFromSentenceEnd("words_from_sentence_end", intValues, NULL));

        addFeatureProcessor(new PhrasesFromSentenceStart("phrases_from_sentence_start", intValues, NULL));
        addFeatureProcessor(new PhrasesFromSentenceEnd("phrases_from_sentence_end", intValues, NULL));

        addFeatureProcessor(new SylBreak("syl_break", intValues, syllableNav));

        std::vector<std::string> positionTypeValues;
        positionTypeValues.assign(POSITIONTYPE, POSITIONTYPE + POSITIONTYPE_NUM);
        addFeatureProcessor(new PositionType("position_type", positionTypeValues, syllableNav));
        addFeatureProcessor(new IsPause("is_pause", boolValues, NULL));
        std::vector<std::string> puncValues;
        puncValues.assign(PUNCUATION, PUNCUATION+PUNC_NUM);
        addFeatureProcessor(new WordPunc("word_punc", puncValues, NULL));
        addFeatureProcessor(new NextPunctuation("next_punc", puncValues, NULL));
        addFeatureProcessor(new PrevPunctuation("prev_punc", puncValues, NULL));

        addFeatureProcessor(new WordsToNextPunctuation("words_to_next_punc", intValues, wordNav));
        addFeatureProcessor(new WordsToPrevPunctuation("words_to_prev_punc", intValues, wordNav));

    }

    void FeatureProcessorManager::addFeatureProcessor(FeatureProcessor * fp) {
        processors_[fp->getName()] = fp;
    }

    FeatureProcessor * FeatureProcessorManager::getFeatureProcessor(std::string name) {
        //TODO: faild process
        return processors_[name];
    }

    void FeatureProcessorManager::setupPhoneFeatureProcessors(AllophoneSet phoneset) {
        std::vector<std::string> phoneValues;
        std::vector<std::string> pValues = phoneset.getAllophoneNames();
        std::string pauseSymbol = phoneset.getSilent().name();
        TargetElementNavigator* segmentNavigator = new SegmentNavigator();
        //addFeatureProcessor(new Phone("phone", pValues, pauseSymbol, segmentNavigator));
        addFeatureProcessor(new Phone("phone", pValues, segmentNavigator));
    }
}
