//
// Created by sooda on 16/6/3.
//
#include <iostream>
//#include "modules/TextToMaryXml.h"
#include "pugixml/pugixml.hpp"
//#include "common/WordsProcess.h"
#include "cppmary.h"
#include "features.h"
#include <time.h>
using namespace std;
using namespace cppmary;

SpeechSynthesiser::SpeechSynthesiser() {
    init();
}

SpeechSynthesiser::~SpeechSynthesiser() {

}

void SpeechSynthesiser::init() {
    WordsProcess::Instance()->LoadResource("data/jieba/");
    tokenizer_ = new cppmary::Tokenizer();
    std::string sylDictName = "test/pinyin_han.txt";
    std::string wordDictName = "test/mix_pinyin_word.txt";
    std::string sylDictStr = getFileString(sylDictName);
    std::string wordDictStr = getFileString(wordDictName);
    std::string lexiconDictName = "test/zh_ph64_lexicon.dict";
    std::string lexiconDictStr = getFileString(lexiconDictName);
    phonemiser_ = new cppmary::Phonemiser(wordDictStr, sylDictStr, lexiconDictStr);
    prosody_ = new cppmary::Prosody();
    pronuciation_ = new cppmary::Pronunciation();
    std::string allophoneSetName = "test/allophones.zh_PH64.xml";
    std::string allophoneSetStr = getFileString(allophoneSetName);
    //FeatureProcessorManager manager("zh", allophoneSetStr);
    manager_ = new FeatureProcessorManager("zh", allophoneSetStr);
    std::string trickyName = "test/trickyPhones.txt";
    std::string trickyStr = getFileString(trickyName);
    PhoneTranslator* phoneTranslator = new PhoneTranslator(trickyStr);
    std::string featureMapName = "test/hmmFeaturesMap1.txt";
    std::vector<string> featureName;
    std::vector<string> featureAlias;
    loadDict(featureName, featureAlias, featureMapName);
    std::vector<std::string> contextFeatureName = featureName;
    contextFeatureName.push_back("phone");
    contextFeatureName.push_back("prev_phone");
    contextFeatureName.push_back("prev_prev_phone");
    contextFeatureName.push_back("next_phone");
    contextFeatureName.push_back("next_next_phone");
    //TargetFeatureComputer featureComputer(manager, contextFeatureName);
    featureComputer_ = new TargetFeatureComputer((*manager_), contextFeatureName);
    std::cout << "context feature size: " << contextFeatureName.size() << std::endl;
    assert(featureName.size() == featureAlias.size());
    label_ = new LabelGenerator(manager_, featureComputer_, featureName, featureAlias, phoneTranslator);
    std::string modelName = "test/labixx.htsvoice";
    std::string modelStr = getFileString(modelName);
    htsengine_ = new HtsEngine(modelStr);
}


void SpeechSynthesiser::process(std::string input) {
    clock_t start = clock();
    std::string rawXml = cppmary::TextToMaryXml::getInstance().process(input);
    std::string tokenStr = tokenizer_->process(rawXml);
    std::string phoneStr = phonemiser_->process(tokenStr);
    std::string prodyStr = prosody_->process(phoneStr);
    std::string pronunStr = pronuciation_->process(prodyStr);
    std::string labelString = label_->process(pronunStr);
    std::cout << "before synthesis: " << (clock()-start) * 1000.0 / CLOCKS_PER_SEC << std::endl;
    htsengine_->process(labelString);
    std::cout << "totaltime: " << (clock()-start) * 1000.0 / CLOCKS_PER_SEC << std::endl;
}