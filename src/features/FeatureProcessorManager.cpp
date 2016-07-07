//
// Created by sooda on 16/6/15.
//

#include "features/FeatureProcessorManager.h"
#include "features/GenericFeatureProcessors.h"
#include "features/LanguageFeatureProcessors.h"

namespace cppmary {
    FeatureProcessorManager::FeatureProcessorManager(std::string localeString, std::string phonesetXmlStr) : phoneset_(phonesetXmlStr) {
        //locale process
        localeString_ = localeString;
        setupGenericFeatureProcessors();
        setupPhoneFeatureProcessors();
    }

    FeatureProcessorManager::FeatureProcessorManager(const FeatureProcessorManager& manager) {
        processors_ = manager.processors_;
        phoneset_ = manager.phoneset_;
        phonefeature2values_ = manager.phonefeature2values_;
        localeString_ = manager.localeString_;
    }

    FeatureProcessorManager::~FeatureProcessorManager() {
        XLOG(INFO) << "deconstruct FeatureProcessorManager ";
    }

    void FeatureProcessorManager::setupGenericFeatureProcessors() {

        std::vector<std::string> intValues;
        for (int i = 0; i <= RAIL_LIMIT; i++) {
            intValues.push_back(std::to_string(i));
        }
        addFeatureProcessor(std::shared_ptr<PhraseNumSyls>(new PhraseNumSyls("phrase_numsyls", intValues, NULL)));
        addFeatureProcessor(std::shared_ptr<PhraseNumWords>(new PhraseNumWords("phrase_numwords", intValues, NULL)));
        addFeatureProcessor(std::shared_ptr<SentenceNumPhrases>(new SentenceNumPhrases("sentence_numphrases", intValues, NULL)));
        addFeatureProcessor(std::shared_ptr<SentenceNumWords>(new SentenceNumWords("sentence_numwords", intValues, NULL)));

        addFeatureProcessor(std::shared_ptr<SylNumSegs>(new SylNumSegs("syl_numsegs", intValues, NULL)));
        addFeatureProcessor(std::shared_ptr<WordNumSegs>(new WordNumSegs("word_numsegs", intValues, NULL)));
        addFeatureProcessor(std::shared_ptr<WordNumSyls>(new WordNumSyls("word_numsyls", intValues, NULL)));
        std::vector<std::string> zhToneValues;
        zhToneValues.assign(ZHTONES, ZHTONES+ZHTONE_NUM);
        std::shared_ptr<TargetElementNavigator> syllableNav = std::shared_ptr<SyllableNavigator>(new SyllableNavigator());
        std::shared_ptr<TargetElementNavigator> prevSyllableNav = std::shared_ptr<PrevSyllableNavigator>(new PrevSyllableNavigator());
        std::shared_ptr<TargetElementNavigator> prevPrevSyllableNav = std::shared_ptr<PrevPrevSyllableNavigator>(new PrevPrevSyllableNavigator());
        std::shared_ptr<TargetElementNavigator> nextSyllableNav = std::shared_ptr<NextSyllableNavigator>(new NextSyllableNavigator());
        std::shared_ptr<TargetElementNavigator> nextNextSyllableNav = std::shared_ptr<NextNextSyllableNavigator>(new NextNextSyllableNavigator());
        std::shared_ptr<TargetElementNavigator> wordNav = std::shared_ptr<WordNavigator>(new WordNavigator());
        std::shared_ptr<TargetElementNavigator> nextWordNav = std::shared_ptr<WordNavigator>(new WordNavigator());
        std::shared_ptr<TargetElementNavigator> prevWordNav = std::shared_ptr<WordNavigator>(new WordNavigator());
        std::shared_ptr<TargetElementNavigator> firstSylInWord = std::shared_ptr<FirstSyllableInWordNavigator>(new FirstSyllableInWordNavigator());
        std::shared_ptr<TargetElementNavigator> lastSylInPhrase = std::shared_ptr<LastSyllableInPhraseNavigator>(new LastSyllableInPhraseNavigator());
        std::shared_ptr<TargetElementNavigator> segmentNav = std::shared_ptr<SegmentNavigator>(new SegmentNavigator());
        std::shared_ptr<TargetElementNavigator> prevSegmentNav = std::shared_ptr<PrevSegmentNavigator>(new PrevSegmentNavigator());
        std::shared_ptr<TargetElementNavigator> nextSegmentNav = std::shared_ptr<NextSegmentNavigator>(new NextSegmentNavigator());
        std::shared_ptr<TargetElementNavigator> lastWordNav = std::shared_ptr<LastWordInSentenceNavigator>(new LastWordInSentenceNavigator());
        addFeatureProcessor(std::shared_ptr<Zhtone>(new Zhtone("zhtone", zhToneValues, syllableNav)));
        addFeatureProcessor(std::shared_ptr<Zhtone>(new Zhtone("prev_zhtone", zhToneValues, prevSyllableNav)));
        addFeatureProcessor(std::shared_ptr<Zhtone>(new Zhtone("next_zhtone", zhToneValues, nextSyllableNav)));
        addFeatureProcessor(std::shared_ptr<Zhtone>(new Zhtone("nextnext_zhtone", zhToneValues, nextNextSyllableNav)));
        addFeatureProcessor(std::shared_ptr<Zhtone>(new Zhtone("prevprev_zhtone", zhToneValues, prevPrevSyllableNav)));
        addFeatureProcessor(std::shared_ptr<Zhtone>(new Zhtone("phrase_zhtone", zhToneValues, lastSylInPhrase)));


        std::vector<std::string> tobiValues;
        tobiValues.assign(TOBIACCENTS, TOBIACCENTS+TOBIACCENT_NUM);
        addFeatureProcessor(std::shared_ptr<TobiAccent>(new TobiAccent("tobi_accent", tobiValues, syllableNav)));
        addFeatureProcessor(std::shared_ptr<TobiAccent>(new TobiAccent("prev_tobi_accent", tobiValues, prevSyllableNav))); //注意这里是tobi accent
        addFeatureProcessor(std::shared_ptr<TobiAccent>(new TobiAccent("prevprev_tobi_accent", tobiValues, prevPrevSyllableNav)));
        addFeatureProcessor(std::shared_ptr<TobiAccent>(new TobiAccent("next_tobi_accent", tobiValues, nextSyllableNav)));
        addFeatureProcessor(std::shared_ptr<TobiAccent>(new TobiAccent("nextnext_tobi_accent", tobiValues, nextNextSyllableNav)));
        //addFeatureProcessor(new TobiAccent("prev_accent", tobiValues, prevSyllableNav)); //注意这里是tobi accent
        //addFeatureProcessor(new TobiAccent("next_accent", tobiValues, nextSyllableNav));

        std::vector<std::string> posValues;
        posValues.assign(ZHPOS, ZHPOS+ZHPOS_NUM);
        addFeatureProcessor(std::shared_ptr<Pos>(new Pos("pos", posValues, wordNav)));
        addFeatureProcessor(std::shared_ptr<Pos>(new Pos("next_pos", posValues, nextWordNav)));
        addFeatureProcessor(std::shared_ptr<Pos>(new Pos("prev_pos", posValues, prevWordNav)));

        std::vector<std::string> boolValues;
        boolValues.push_back("0");
        boolValues.push_back("1");
        addFeatureProcessor(std::shared_ptr<Accented>(new Accented("accented", boolValues, syllableNav)));
        //addFeatureProcessor(new Accented("prev_accent", boolValues, prevSyllableNav));
        //addFeatureProcessor(new Accented("next_accent", boolValues, nextSyllableNav));
        addFeatureProcessor(std::shared_ptr<AccentedSylsFromPhraseStart>(new AccentedSylsFromPhraseStart("accented_syls_from_phrase_start", intValues, syllableNav)));
        addFeatureProcessor(std::shared_ptr<AccentedSylsFromPhraseEnd>(new AccentedSylsFromPhraseEnd("accented_syls_from_phrase_end", intValues, syllableNav)));
        addFeatureProcessor(std::shared_ptr<SylsFromPrevAccented>(new SylsFromPrevAccented("syls_from_prev_accent", intValues, syllableNav)));
        addFeatureProcessor(std::shared_ptr<SylsToNextAccented>(new SylsToNextAccented("syls_to_next_accent", intValues, syllableNav)));

        addFeatureProcessor(std::shared_ptr<SegsFromSylStart>(new SegsFromSylStart("segs_from_syl_start", intValues, NULL)));
        addFeatureProcessor(std::shared_ptr<SegsFromSylEnd>(new SegsFromSylEnd("segs_from_syl_end", intValues, NULL)));

        addFeatureProcessor(std::shared_ptr<SegsFromWordStart>(new SegsFromWordStart("segs_from_word_start", intValues, NULL)));
        addFeatureProcessor(std::shared_ptr<SegsFromWordEnd>(new SegsFromWordEnd("segs_from_word_end", intValues, NULL)));

        addFeatureProcessor(std::shared_ptr<SylsFromPhraseStart>(new SylsFromPhraseStart("syls_from_phrase_start", intValues, syllableNav)));
        addFeatureProcessor(std::shared_ptr<SylsFromPhraseEnd>(new SylsFromPhraseEnd("syls_from_phrase_end", intValues, syllableNav)));

        addFeatureProcessor(std::shared_ptr<SylsFromWordStart>(new SylsFromWordStart("syls_from_word_start", intValues, syllableNav)));
        addFeatureProcessor(std::shared_ptr<SylsFromWordEnd>(new SylsFromWordEnd("syls_from_word_end", intValues, syllableNav)));

        addFeatureProcessor(std::shared_ptr<WordsFromPhraseStart>(new WordsFromPhraseStart("words_from_phrase_start", intValues, NULL)));
        addFeatureProcessor(std::shared_ptr<WordsFromPhraseEnd>(new WordsFromPhraseEnd("words_from_phrase_end", intValues, NULL)));

        addFeatureProcessor(std::shared_ptr<WordsFromSentenceStart>(new WordsFromSentenceStart("words_from_sentence_start", intValues, NULL)));
        addFeatureProcessor(std::shared_ptr<WordsFromSentenceEnd>(new WordsFromSentenceEnd("words_from_sentence_end", intValues, NULL)));

        addFeatureProcessor(std::shared_ptr<PhrasesFromSentenceStart>(new PhrasesFromSentenceStart("phrases_from_sentence_start", intValues, NULL)));
        addFeatureProcessor(std::shared_ptr<PhrasesFromSentenceEnd>(new PhrasesFromSentenceEnd("phrases_from_sentence_end", intValues, NULL)));

        addFeatureProcessor(std::shared_ptr<SylBreak>(new SylBreak("syl_break", intValues, syllableNav)));
        addFeatureProcessor(std::shared_ptr<SylBreak>(new SylBreak("prev_syl_break", intValues, prevSyllableNav)));
        addFeatureProcessor(std::shared_ptr<SylBreak>(new SylBreak("next_syl_break", intValues, nextSyllableNav)));
        addFeatureProcessor(std::shared_ptr<BreakIndex>(new BreakIndex("breakindex", intValues, syllableNav)));

        std::vector<std::string> positionTypeValues;
        positionTypeValues.assign(POSITIONTYPE, POSITIONTYPE + POSITIONTYPE_NUM);
        addFeatureProcessor(std::shared_ptr<PositionType>(new PositionType("position_type", positionTypeValues, syllableNav)));
        addFeatureProcessor(std::shared_ptr<IsPause>(new IsPause("is_pause", boolValues, segmentNav)));
        addFeatureProcessor(std::shared_ptr<IsPause>(new IsPause("prev_is_pause", boolValues, prevSegmentNav)));
        addFeatureProcessor(std::shared_ptr<IsPause>(new IsPause("next_is_pause", boolValues, nextSegmentNav)));
        std::vector<std::string> puncValues;
        puncValues.assign(PUNCUATION, PUNCUATION+PUNC_NUM);
        addFeatureProcessor(std::shared_ptr<WordPunc>(new WordPunc("sentence_punc", puncValues, lastWordNav)));
        addFeatureProcessor(std::shared_ptr<NextPunctuation>(new NextPunctuation("next_punctuation", puncValues, NULL)));
        addFeatureProcessor(std::shared_ptr<PrevPunctuation>(new PrevPunctuation("prev_punctuation", puncValues, NULL)));

        addFeatureProcessor(std::shared_ptr<WordsToNextPunctuation>(new WordsToNextPunctuation("words_to_next_punctuation", intValues, wordNav)));
        addFeatureProcessor(std::shared_ptr<WordsToPrevPunctuation>(new WordsToPrevPunctuation("words_from_prev_punctuation", intValues, wordNav)));

        std::vector<std::string> styleValues;
        styleValues.assign(STYLES, STYLES+STYLE_NUM);
        addFeatureProcessor(std::shared_ptr<Style>(new Style("style", styleValues, NULL)));

        //endtone
        std::vector<std::string> endtoneValues;
        styleValues.assign(ENDTONE, ENDTONE+ENDTONE_NUM);
        addFeatureProcessor(std::shared_ptr<TobiEndtone>(new TobiEndtone("tobi_endtone", endtoneValues, syllableNav)));
        addFeatureProcessor(std::shared_ptr<TobiEndtone>(new TobiEndtone("next_tobi_endtone", endtoneValues, nextSyllableNav)));
        addFeatureProcessor(std::shared_ptr<TobiEndtone>(new TobiEndtone("nextnext_tobi_endtone", endtoneValues, nextNextSyllableNav)));
        addFeatureProcessor(std::shared_ptr<TobiEndtone>(new TobiEndtone("prev_tobi_endtone", endtoneValues, prevSyllableNav)));
        addFeatureProcessor(std::shared_ptr<TobiEndtone>(new TobiEndtone("prevprev_tobi_endtone", endtoneValues, prevPrevSyllableNav)));
        addFeatureProcessor(std::shared_ptr<TobiEndtone>(new TobiEndtone("phrase_endtone", endtoneValues, lastSylInPhrase)));

        //onsetcoda
        std::vector<std::string> onsetcodaValues;
        onsetcodaValues.push_back("0");
        onsetcodaValues.push_back("onset");
        onsetcodaValues.push_back("coda");
        addFeatureProcessor(std::shared_ptr<SegOnsetCoda>(new SegOnsetCoda("onsetcoda", onsetcodaValues, NULL, phoneset_)));

    }

    void FeatureProcessorManager::addFeatureProcessor(std::shared_ptr<FeatureProcessor> fp) {
        std::cout << fp->getName() << " setup ";
        processors_[fp->getName()] = fp;
    }

    std::shared_ptr<FeatureProcessor> FeatureProcessorManager::getFeatureProcessor(std::string name) {
        //TODO: faild process
        return processors_[name];
    }

    void FeatureProcessorManager::setupPhoneFeatureProcessors() {
        std::vector<std::string> phoneValues;
        std::vector<std::string> pValues = phoneset_.getAllophoneNames();
        std::string pauseSymbol = phoneset_.getSilent().name();
        std::shared_ptr<TargetElementNavigator> segmentNavigator = std::shared_ptr<SegmentNavigator>(new SegmentNavigator());
        std::shared_ptr<TargetElementNavigator> prevSegmentNavigator = std::shared_ptr<PrevSegmentNavigator>(new PrevSegmentNavigator());
        std::shared_ptr<TargetElementNavigator> prevPrevSegmentNavigator = std::shared_ptr<PrevPrevSegmentNavigator>(new PrevPrevSegmentNavigator());
        std::shared_ptr<TargetElementNavigator> nextSegmentNavigator = std::shared_ptr<NextSegmentNavigator>(new NextSegmentNavigator());
        std::shared_ptr<TargetElementNavigator> nextNextSegmentNavigator = std::shared_ptr<NextNextSegmentNavigator>(new NextNextSegmentNavigator());
        addFeatureProcessor(std::shared_ptr<Phone>(new Phone("phone", pValues, segmentNavigator)));
        addFeatureProcessor(std::shared_ptr<Phone>(new Phone("prev_phone", pValues, prevSegmentNavigator)));
        addFeatureProcessor(std::shared_ptr<Phone>(new Phone("prev_prev_phone", pValues, prevPrevSegmentNavigator)));
        addFeatureProcessor(std::shared_ptr<Phone>(new Phone("next_phone", pValues, nextSegmentNavigator)));
        addFeatureProcessor(std::shared_ptr<Phone>(new Phone("next_next_phone", pValues, nextNextSegmentNavigator)));
    }
}
