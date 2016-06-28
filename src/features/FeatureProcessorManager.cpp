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
        addFeatureProcessor(new PhraseNumWords("phrase_numwords", intValues, NULL));
        addFeatureProcessor(new SentenceNumPhrases("sentence_numphrases", intValues, NULL));
        addFeatureProcessor(new SentenceNumWords("sentence_numwords", intValues, NULL));

        addFeatureProcessor(new SylNumSegs("syl_numsegs", intValues, NULL));
        addFeatureProcessor(new WordNumSegs("word_numsegs", intValues, NULL));
        addFeatureProcessor(new WordNumSyls("word_numsyls", intValues, NULL));
        std::vector<std::string> zhToneValues;
        zhToneValues.assign(ZHTONES, ZHTONES+ZHTONE_NUM);
        TargetElementNavigator* syllableNav = new SyllableNavigator();
        TargetElementNavigator* prevSyllableNav = new PrevSyllableNavigator();
        TargetElementNavigator* prevPrevSyllableNav = new PrevPrevSyllableNavigator();
        TargetElementNavigator* nextSyllableNav = new NextSyllableNavigator();
        TargetElementNavigator* nextnextSyllableNav = new NextNextSyllableNavigator();
        TargetElementNavigator* wordNav = new WordNavigator();
        TargetElementNavigator* nextWordNav = new WordNavigator();
        TargetElementNavigator* prevWordNav =  new WordNavigator();
        TargetElementNavigator* firstSylInWord = new FirstSyllableInWordNavigator();
        TargetElementNavigator* lastSylInPhrase = new LastSyllableInPhraseNavigator();
        TargetElementNavigator* segmentNav = new SegmentNavigator();
        TargetElementNavigator* prevSegmentNav = new PrevSegmentNavigator();
        TargetElementNavigator* nextSegmentNav = new NextSegmentNavigator();
        TargetElementNavigator* lastWordNav = new LastWordInSentenceNavigator();
        addFeatureProcessor(new Zhtone("zh_tone", zhToneValues, syllableNav));
        addFeatureProcessor(new Zhtone("prev_zh_tone", zhToneValues, prevSyllableNav));
        addFeatureProcessor(new Zhtone("next_zhtone", zhToneValues, nextSyllableNav));
        addFeatureProcessor(new Zhtone("nextnext_zh_tone", zhToneValues, nextnextSyllableNav));
        addFeatureProcessor(new Zhtone("prevprev_zhtone", zhToneValues, prevPrevSyllableNav));
        addFeatureProcessor(new Zhtone("phrase_zhtone", zhToneValues, lastSylInPhrase));


        std::vector<std::string> tobiValues;
        tobiValues.assign(TOBIACCENTS, TOBIACCENTS+TOBIACCENT_NUM);
        addFeatureProcessor(new TobiAccent("tobi_accent", tobiValues, syllableNav));
        addFeatureProcessor(new TobiAccent("prev_accent", tobiValues, prevSyllableNav)); //注意这里是tobi accent
        addFeatureProcessor(new TobiAccent("prevprev_tobi_accent", tobiValues, prevPrevSyllableNav));
        addFeatureProcessor(new TobiAccent("next_accent", tobiValues, nextSyllableNav));
        addFeatureProcessor(new TobiAccent("nextnext_tobi_accent", tobiValues, nextnextSyllableNav));

        std::vector<std::string> posValues;
        posValues.assign(ZHPOS, ZHPOS+ZHPOS_NUM);
        addFeatureProcessor(new Pos("pos", posValues, wordNav));
        addFeatureProcessor(new Pos("next_pos", posValues, nextWordNav));
        addFeatureProcessor(new Pos("prev_pos", posValues, prevWordNav));

        std::vector<std::string> boolValues;
        boolValues.push_back("0");
        boolValues.push_back("1");
        addFeatureProcessor(new Accented("accented", boolValues, syllableNav));
        //addFeatureProcessor(new Accented("prev_accent", boolValues, prevSyllableNav));
        //addFeatureProcessor(new Accented("next_accent", boolValues, nextSyllableNav));
        addFeatureProcessor(new AccentedSylsFromPhraseStart("accented_syls_from_phrase_start", intValues, syllableNav));
        addFeatureProcessor(new AccentedSylsFromPhraseEnd("accented_syls_from_phrase_end", intValues, syllableNav));
        addFeatureProcessor(new SylsFromPrevAccented("syls_from_prev_accent", intValues, syllableNav));
        addFeatureProcessor(new SylsToNextAccented("syls_to_next_accent", intValues, syllableNav));

        addFeatureProcessor(new SegsFromSylStart("segs_from_syl_start", intValues, NULL));
        addFeatureProcessor(new SegsFromSylEnd("segs_from_syl_end", intValues, NULL));

        addFeatureProcessor(new SegsFromWordStart("segs_from_word_start", intValues, NULL));
        addFeatureProcessor(new SegsFromWordEnd("segs_from_word_end", intValues, NULL));

        addFeatureProcessor(new SylsFromPhraseStart("syls_from_phrase_start", intValues, syllableNav));
        addFeatureProcessor(new SylsFromPhraseEnd("syls_from_phrase_end", intValues, syllableNav));

        addFeatureProcessor(new SylsFromWordStart("syls_from_word_start", intValues, syllableNav));
        addFeatureProcessor(new SylsFromWordEnd("syls_from_word_end", intValues, syllableNav));

        addFeatureProcessor(new WordsFromPhraseStart("words_from_phrase_start", intValues, NULL));
        addFeatureProcessor(new WordsFromPhraseEnd("words_from_phrase_end", intValues, NULL));

        addFeatureProcessor(new WordsFromSentenceStart("words_from_sentence_start", intValues, NULL));
        addFeatureProcessor(new WordsFromSentenceEnd("words_from_sentence_end", intValues, NULL));

        addFeatureProcessor(new PhrasesFromSentenceStart("phrases_from_sentence_start", intValues, NULL));
        addFeatureProcessor(new PhrasesFromSentenceEnd("phrases_from_sentence_end", intValues, NULL));

        addFeatureProcessor(new SylBreak("syl_break", intValues, syllableNav));
        addFeatureProcessor(new SylBreak("prev_syl_break", intValues, prevSyllableNav));
        addFeatureProcessor(new BreakIndex("breakindex", intValues, syllableNav));

        std::vector<std::string> positionTypeValues;
        positionTypeValues.assign(POSITIONTYPE, POSITIONTYPE + POSITIONTYPE_NUM);
        addFeatureProcessor(new PositionType("position_type", positionTypeValues, syllableNav));
        addFeatureProcessor(new IsPause("is_pause", boolValues, segmentNav));
        addFeatureProcessor(new IsPause("prev_is_pause", boolValues, prevSegmentNav));
        addFeatureProcessor(new IsPause("next_is_pause", boolValues, nextSegmentNav));
        std::vector<std::string> puncValues;
        puncValues.assign(PUNCUATION, PUNCUATION+PUNC_NUM);
        addFeatureProcessor(new WordPunc("sentence_punc", puncValues, lastWordNav));
        addFeatureProcessor(new NextPunctuation("next_punctuation", puncValues, NULL));
        addFeatureProcessor(new PrevPunctuation("prev_punctuation", puncValues, NULL));

        addFeatureProcessor(new WordsToNextPunctuation("words_to_next_punctuation", intValues, wordNav));
        addFeatureProcessor(new WordsToPrevPunctuation("words_from_prev_punctuation", intValues, wordNav));

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
        TargetElementNavigator* prevSegmentNavigator = new PrevSegmentNavigator();
        TargetElementNavigator* prevPrevSegmentNavigator = new PrevPrevSyllableNavigator();
        TargetElementNavigator* nextSegmentNavigator = new NextSegmentNavigator();
        TargetElementNavigator* nextNextSegmentNavigator = new NextNextSegmentNavigator();
        addFeatureProcessor(new Phone("phone", pValues, segmentNavigator));
        addFeatureProcessor(new Phone("prev_phone", pValues, prevSegmentNavigator));
        addFeatureProcessor(new Phone("prev_prev_phone", pValues, prevPrevSegmentNavigator));
        addFeatureProcessor(new Phone("next_phone", pValues, nextSegmentNavigator));
        addFeatureProcessor(new Phone("next_next_phone", pValues, nextNextSegmentNavigator));
    }
}
