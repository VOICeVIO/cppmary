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
        addFeatureProcessor(new PhraseNumSyls());
        std::vector<std::string> zhToneValues;
        zhToneValues.assign(ZHTONES, ZHTONES+6);
        TargetElementNavigator* syllableNav = new SyllableNavigator();
        TargetElementNavigator* prevSyllableNav = new PrevSyllableNavigator();
        TargetElementNavigator* nextSyllableNav = new NextSyllableNavigator();
        TargetElementNavigator* nextnextSyllableNav = new NextNextSyllableNavigator();
        TargetElementNavigator* wordNav = new WordNavigator();
        addFeatureProcessor(new Zhtone("zhtone", zhToneValues, syllableNav));
        addFeatureProcessor(new Zhtone("prev_zhtone", zhToneValues, prevSyllableNav));
        addFeatureProcessor(new Zhtone("next_zhtone", zhToneValues, nextSyllableNav));
        addFeatureProcessor(new Zhtone("nextnext_zhtone", zhToneValues, nextnextSyllableNav));

        std::vector<std::string> posValues;
        posValues.assign(ZHPOS, ZHPOS+46);
        addFeatureProcessor(new Pos("pos", posValues, wordNav));


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
        addFeatureProcessor(new Phone("phone", pValues, pauseSymbol, segmentNavigator));
    }
}
