//
// Created by sooda on 16/6/3.
//
#include <iostream>
//#include "modules/TextToMaryXml.h"
#include "pugixml/pugixml.hpp"
//#include "common/WordsProcess.h"
#include "cppmary.h"
#include "feature.h"
#include <time.h>
using namespace std;
using namespace cppmary;

SpeechSynthesiser::SpeechSynthesiser(std::string dir) {
    init(dir);
}

SpeechSynthesiser::~SpeechSynthesiser() {
    manager_->ReleaseRef();
    phonemiser_->ReleaseRef();
    prosody_->ReleaseRef();
    pronuciation_->ReleaseRef();
    featureComputer_->ReleaseRef();
    tokenizer_->ReleaseRef();
    label_->ReleaseRef();
    htsengine_->ReleaseRef();

}

void SpeechSynthesiser::init(std::string dir) {
    std::string jieba_buffer = getFileString(dir+"data/jieba/jieba.dict.utf8");
    std::string hmm_model_buffer = getFileString(dir+"data/jieba/hmm_model.utf8");;
    std::string user_buffer = getFileString(dir+"data/jieba/user.dict.utf8");
    JiebaSegment::Instance()->LoadResource(jieba_buffer,
                                           hmm_model_buffer,
                                           user_buffer);
    tokenizer_ = new cppmary::Tokenizer();
    std::string sylDictName = dir+"data/pinyin_han.txt";
    std::string wordDictName = dir+"data/mix_pinyin_word.txt";
    std::string sylDictStr = getFileString(sylDictName);
    std::string wordDictStr = getFileString(wordDictName);
    std::string lexiconDictName = dir+"data/zh_ph64_lexicon.dict";
    std::string lexiconDictStr = getFileString(lexiconDictName);
    phonemiser_ = new cppmary::Phonemiser(wordDictStr, sylDictStr, lexiconDictStr);
    prosody_ = new cppmary::Prosody();
    pronuciation_ = new cppmary::Pronunciation();
    std::string allophoneSetName = dir+"data/allophones.zh_PH64.xml";
    std::string allophoneSetStr = getFileString(allophoneSetName);
    //FeatureProcessorManager manager("zh", allophoneSetStr);
    manager_ = new FeatureProcessorManager("zh", allophoneSetStr);
    std::string trickyName = dir+"data/trickyPhones.txt";
    std::string trickyStr = getFileString(trickyName);
    PhoneTranslator* phoneTranslator = new PhoneTranslator(trickyStr);
    phoneTranslator->AddRef();
    //std::string featureMapName = dir+"data/hmmFeaturesMap1.txt";
    std::string featureMapName = dir+"data/hmmFeaturesMap.txt";
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
    featureComputer_ = new TargetFeatureComputer(manager_, contextFeatureName);
    std::cout << "context feature size: " << contextFeatureName.size() << std::endl;
    assert(featureName.size() == featureAlias.size());
    label_ = new LabelGenerator(manager_, featureComputer_, featureName, featureAlias, phoneTranslator);
    std::string modelName = dir+"data/labixx23.htsvoice";
    std::string modelStr = getFileString(modelName);
    std::string filterName = dir+"data/mix_excitation_5filters_199taps_48Kz.txt";
    std::string filterStr = getFileString(filterName);
    tokenizer_->AddRef();
    htsengine_ = new HtsEngine(modelStr, filterStr);
    manager_->AddRef();
    htsengine_->AddRef();
    phonemiser_->AddRef();
    prosody_->AddRef();
    pronuciation_->AddRef();
    featureComputer_->AddRef();
    label_->AddRef();
    phoneTranslator->ReleaseRef();
}


void SpeechSynthesiser::process(std::string input, std::string outfile) {
    clock_t start = clock();
    std::string rawXml = cppmary::TextToMaryXml::getInstance().process(input);
    std::string tokenStr = tokenizer_->process(rawXml);
    std::string phoneStr = phonemiser_->process(tokenStr);
    std::string prodyStr = prosody_->process(phoneStr);
    std::string pronunStr = pronuciation_->process(prodyStr);
    std::string labelString = label_->process(pronunStr);
    std::cout << "before synthesis: " << (clock()-start) * 1000.0 / CLOCKS_PER_SEC << std::endl;
    ((cppmary::HtsEngine*)htsengine_)->setOutFile(outfile);
    htsengine_->process(labelString);
    std::cout << "totaltime: " << (clock()-start) * 1000.0 / CLOCKS_PER_SEC << std::endl;
}
