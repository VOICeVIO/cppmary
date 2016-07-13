//
// Created by sooda on 16/6/3.
//
#include <iostream>
#include "pugixml/pugixml.hpp"
#include "cppmary.h"
#include "feature.h"
#include "limonp/Config.hpp"
#include <time.h>
using namespace std;
using namespace cppmary;

SpeechSynthesiser::SpeechSynthesiser(const std::string& confPath) {
    init(confPath);
}

SpeechSynthesiser::~SpeechSynthesiser() {
}

void SpeechSynthesiser::init(const std::string& confPath) {
    std::string basePath = getParentPath(confPath);
    limonp::Config config(confPath);
    std::cout << config.GetConfigInfo() << std::endl;
    std::string jiebaDictPath = basePath + config.Get("jieba_dict_path", "");
    std::string hmmModelPath = basePath + config.Get("hmm_model_path", "");
    std::string userDictPath = basePath + config.Get("user_dict_path", "");
    std::string sylDictName = basePath + config.Get("pinyin_dict_path", "");
    std::string wordDictName = basePath + config.Get("pinyin_word_path", "");
    std::string lexiconDictName = basePath + config.Get("lexicon_dict_path", "");
    std::string allophoneSetName = basePath + config.Get("allophone_path", "");
    std::string featureMapName = basePath + config.Get("feature_map_path", "");
    std::string trickyName = basePath + config.Get("tricky_phone_path", "");
    std::string modelName = basePath + config.Get("voice_path", "");
    std::string filterName = basePath + config.Get("mix_excitation_path", "");

    std::string jieba_buffer = getFileString(jiebaDictPath);
    std::string hmm_model_buffer = getFileString(hmmModelPath);
    std::string user_buffer = getFileString(userDictPath);

    JiebaSegment::Instance()->LoadResource(jieba_buffer,
                                           hmm_model_buffer,
                                           user_buffer);
    tokenizer_ = std::shared_ptr<cppmary::Tokenizer>(new cppmary::Tokenizer());
    std::string sylDictStr = getFileString(sylDictName);
    std::string wordDictStr = getFileString(wordDictName);
    std::string lexiconDictStr = getFileString(lexiconDictName);
    phonemiser_ = std::shared_ptr<cppmary::Phonemiser>(new cppmary::Phonemiser(wordDictStr, sylDictStr, lexiconDictStr));
    prosody_ = std::shared_ptr<cppmary::Prosody>(new cppmary::Prosody());
    pronuciation_ = std::shared_ptr<cppmary::Pronunciation>(new cppmary::Pronunciation());
    std::string allophoneSetStr = getFileString(allophoneSetName);
    manager_ = std::shared_ptr<FeatureProcessorManager>(new FeatureProcessorManager("zh", allophoneSetStr));
    std::string trickyStr = getFileString(trickyName);
    std::shared_ptr<PhoneTranslator> phoneTranslator = std::shared_ptr<PhoneTranslator>(new PhoneTranslator(trickyStr));
    std::vector<string> featureName;
    std::vector<string> featureAlias;
    loadDict(featureName, featureAlias, featureMapName);
    std::vector<std::string> contextFeatureName = featureName;
    contextFeatureName.push_back("phone");
    contextFeatureName.push_back("prev_phone");
    contextFeatureName.push_back("prev_prev_phone");
    contextFeatureName.push_back("next_phone");
    contextFeatureName.push_back("next_next_phone");
    featureComputer_ = std::shared_ptr<TargetFeatureComputer>(new TargetFeatureComputer(manager_, contextFeatureName));
    std::cout << "context feature size: " << contextFeatureName.size() << std::endl;
    assert(featureName.size() == featureAlias.size());
    label_ = std::shared_ptr<LabelGenerator>(new LabelGenerator(manager_, featureComputer_, featureName, featureAlias, phoneTranslator));
    std::string modelStr = getFileString(modelName);
    std::string filterStr = getFileString(filterName);
    htsengine_ = std::shared_ptr<HtsEngine>(new HtsEngine(modelStr, filterStr));
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
    //((cppmary::HtsEngine*)htsengine_)->setOutFile(outfile);
    std::shared_ptr<cppmary::HtsEngine> derived = std::dynamic_pointer_cast<cppmary::HtsEngine>(htsengine_);
    derived->setOutFile(outfile);
    htsengine_->process(labelString);
    std::cout << "totaltime: " << (clock()-start) * 1000.0 / CLOCKS_PER_SEC << std::endl;
}

std::string SpeechSynthesiser::getAllophone(const std::string& input) const {
    std::string rawXml = cppmary::TextToMaryXml::getInstance().process(input);
    std::string tokenStr = tokenizer_->process(rawXml);
    std::string phoneStr = phonemiser_->process(tokenStr);
    std::string prodyStr = prosody_->process(phoneStr);
    std::string pronunStr = pronuciation_->process(prodyStr);
    return pronunStr;
}
