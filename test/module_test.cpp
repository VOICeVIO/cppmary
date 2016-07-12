//
// Created by sooda on 16/6/7.
//

#include <iostream>
//#include "modules/TextToMaryXml.h"
#include "pugixml/pugixml.hpp"
//#include "common/JiebaSegment.h"
#include "cppmary.h"
#include <fstream>
#include "feature.h"
#include <memory>
using namespace std;
using namespace cppmary;

void text2MaryTest() {
    std::string rawXml = cppmary::TextToMaryXml::getInstance().process("欢迎使用文本转语音服务!");
    std::cout << rawXml << std::endl;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(rawXml.c_str());
    std::cout << doc.child("maryxml").first_child().child_value() << std::endl;
    std::cout << "text2MaryTest done" << std::endl;
}

void TokenizerTest() {
    //JiebaSegment::Instance()->LoadResource("data/jieba/jieba.dict.utf8", "data/jieba/hmm_model.utf8", "data/jieba/user.dict.utf8");
    JiebaSegment::Instance()->LoadResource("data/jieba/");
    std::vector<std::string> words;
    JiebaSegment::Instance()->Cut("欢迎使用文本转语音服务!", words);
    for (int i = 0; i < words.size(); i++) {
        std::cout << words[i] << std::endl;
    }
}

void tokenModuleTest() {
    std::string jieba_buffer = getFileString("data/jieba/jieba.dict.utf8");
    std::string hmm_model_buffer = getFileString("data/jieba/hmm_model.utf8");;
    std::string user_buffer = getFileString("data/jieba/user.dict.utf8");
    JiebaSegment::Instance()->LoadResource(jieba_buffer,
                                           hmm_model_buffer,
                                           user_buffer);
    std::string rawXml = cppmary::TextToMaryXml::getInstance().process("欢迎使用文本转语音服务!");
    cppmary::InterModules* tokenizer = new cppmary::Tokenizer();
    std::string result = tokenizer->process(rawXml);
    std::cout << result << std::endl;
    std::cout << "tokenModuleTest done" << std::endl;
}

void phonemiserTest() {
    std::string rawXml = cppmary::TextToMaryXml::getInstance().process("欢迎使用文本转语音服务!");
    cppmary::InterModules* tokenizer = new cppmary::Tokenizer();
    std::string tokenStr = tokenizer->process(rawXml);
    std::string sylDictName = "data/pinyin_han.txt";
    std::string wordDictName = "data/mix_pinyin_word.txt";
    std::string sylDictStr = getFileString(sylDictName);
    std::string wordDictStr = getFileString(wordDictName);
    std::string lexiconDictName = "data/zh_ph64_lexicon.dict";
    std::string lexiconDictStr = getFileString(lexiconDictName);
    cppmary::InterModules* phonemiser = new cppmary::Phonemiser(wordDictStr, sylDictStr, lexiconDictStr);
    std::string phoneStr = phonemiser->process(tokenStr);
}

void prosodyTest() {
    std::string rawXml = cppmary::TextToMaryXml::getInstance().process("欢迎，使用。文本转！语音？服务!");
    cppmary::InterModules* tokenizer = new cppmary::Tokenizer();
    std::string tokenStr = tokenizer->process(rawXml);
    std::string sylDictName = "data/pinyin_han.txt";
    std::string wordDictName = "data/mix_pinyin_word.txt";
    std::string sylDictStr = getFileString(sylDictName);
    std::string wordDictStr = getFileString(wordDictName);
    std::string lexiconDictName = "data/zh_ph64_lexicon.dict";
    std::string lexiconDictStr = getFileString(lexiconDictName);
    cppmary::InterModules* phonemiser = new cppmary::Phonemiser(wordDictStr, sylDictStr, lexiconDictStr);
    std::string phoneStr = phonemiser->process(tokenStr);
    cppmary::InterModules* prosody = new cppmary::Prosody();
    std::string prodyStr = prosody->process(phoneStr);
}

void replaceTest() {
    std::string orig = "欢迎，使用。文本转！语音？服务!";
    std::string result = cppmary::replaceAll(orig, "，", ",");
    result = cppmary::replaceAll(result, "。", ".");
    std::cout << orig << " --> " << result << std::endl;
}


std::vector<Target> createTargetWithPauses(std::vector<pugi::xml_node> segmentsAndPauses,
                                           std::string pauseSymbol) {
    std::vector<Target> targets;
    if (segmentsAndPauses.size() == 0) {
        return targets;
    }
    //TODO: add final boundary
    for (int i = 0; i < segmentsAndPauses.size(); i++) {
        pugi::xml_node seg = segmentsAndPauses[i];
        std::string phone = seg.attribute("p").as_string();
        if (phone == "") {
            phone = pauseSymbol;
        }
        Target temp(phone, seg);
        targets.push_back(temp);
    }
    return targets;
}

void featureTest(pugi::xml_node doc) {
    cppmary::phone_boundary_walker tw;
    doc.traverse(tw);
    std::vector<Target> targets = createTargetWithPauses(tw.nodes_, "_");

    std::string allophoneSetName = "data/allophones.zh_PH64.xml";
    pugi::xml_document doc1;
    pugi::xml_parse_result result = doc1.load_file(allophoneSetName.c_str());
    std::string alloStr = MaryXml::saveDoc2String(doc1);

    std::shared_ptr<FeatureProcessorManager> manager = std::shared_ptr<FeatureProcessorManager>(new FeatureProcessorManager("zh", alloStr));
    TargetFeatureComputer featureComputer(manager, "phone syl_break breakindex phrase_numsyls zh_tone segs_from_syl_start segs_from_syl_end syls_from_phrase_start syls_from_phrase_end syl_break is_pause words_from_phrase_start words_from_phrase_end words_from_sentence_start words_from_sentence_end phrases_from_sentence_start phrases_from_sentence_end sentence_punc next_punctuation prev_punctuation words_to_next_punctuation words_from_prev_punctuation position_type");
    //load feature map
    for (int i = 0; i < targets.size(); i++) {
        Target target = targets[i];
        std::vector<int> features = featureComputer.computeFeatureVector(target);
//        std::cout << target.getName() << "\t" ;
//        for (int j = 0; j < features.size(); j++) {
//            std::cout << features[j] << "\t";
//        }
//        std::cout << std::endl;
        std::string featureValues = featureComputer.toStringValue(features);
        std::cout << featureValues << std::endl;
    }
}

void pronunciationTest() {
    std::string jieba_buffer = getFileString("data/jieba/jieba.dict.utf8");
    std::string hmm_model_buffer = getFileString("data/jieba/hmm_model.utf8");;
    std::string user_buffer = getFileString("data/jieba/user.dict.utf8");
    JiebaSegment::Instance()->LoadResource(jieba_buffer,
                                           hmm_model_buffer,
                                           user_buffer);
    std::string rawXml = cppmary::TextToMaryXml::getInstance().process("这个世界上，为什么只有我这么帅呢？");
    cppmary::InterModules* tokenizer = new cppmary::Tokenizer();
    std::string tokenStr = tokenizer->process(rawXml);
    std::string sylDictName = "data/pinyin_han.txt";
    std::string wordDictName = "data/mix_pinyin_word.txt";
    std::string sylDictStr = getFileString(sylDictName);
    std::string wordDictStr = getFileString(wordDictName);
    std::string lexiconDictName = "data/zh_ph64_lexicon.dict";
    std::string lexiconDictStr = getFileString(lexiconDictName);
    cppmary::InterModules* phonemiser = new cppmary::Phonemiser(wordDictStr, sylDictStr, lexiconDictStr);
    std::string phoneStr = phonemiser->process(tokenStr);
    cppmary::InterModules* prosody = new cppmary::Prosody();
    std::string prodyStr = prosody->process(phoneStr);
    cppmary::InterModules* pronuciation = new cppmary::Pronunciation();
    std::string pronunStr = pronuciation->process(prodyStr);
}

void labelTest() {
    //std::string puncxmlName = "data/punc.xml";
    std::string puncxmlName = "data/labixx_example.xml";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(puncxmlName.c_str());
    featureTest(doc);
}

void allophoneTest() {
    std::string allophoneSetName = "data/allophones.zh_PH64.xml";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(allophoneSetName.c_str());
    std::string alloStr = MaryXml::saveDoc2String(doc);
    AllophoneSet phoneset(alloStr);
}

void LabelGeneratorTest() {
    //std::string puncxmlName = "data/labixx_example.xml";
    std::string puncxmlName = "data/allo710.xml";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(puncxmlName.c_str());
    std::string allophoneExample = MaryXml::saveDoc2String(doc);

    std::string allophoneSetName = "data/allophones.zh_PH64.xml";
    pugi::xml_document doc1;
    result = doc1.load_file(allophoneSetName.c_str());
    std::string allosetStr = MaryXml::saveDoc2String(doc1);

    std::shared_ptr<FeatureProcessorManager> manager = std::shared_ptr<FeatureProcessorManager>(new FeatureProcessorManager("zh", allosetStr));
    std::string trickyName = "data/trickyPhones.txt";
    std::string trickyStr = getFileString(trickyName);
    std::shared_ptr<PhoneTranslator> phoneTranslator = std::shared_ptr<PhoneTranslator>(new PhoneTranslator(trickyStr));
    //std::string featureMapName = basePath+"data/hmmFeaturesMap1.txt";
    std::string featureMapName = "data/hmmFeaturesMap.txt";
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
    std::shared_ptr<TargetFeatureComputer> featureComputer = std::shared_ptr<TargetFeatureComputer>(new TargetFeatureComputer(manager, contextFeatureName));
    InterModules* label = new LabelGenerator(manager, featureComputer, featureName, featureAlias, phoneTranslator);
    std::string labelString = label->process(allophoneExample);
    std::string modelName = "data/labixx710.htsvoice";
    std::string modelStr = getFileString(modelName);
    std::string filterName = "data/mix_excitation_5filters_199taps_48Kz.txt";
    std::string filterStr = getFileString(filterName);
    InterModules* htsengine = new HtsEngine(modelStr, filterStr);
    htsengine->process(labelString);
}

void HtsEngineTest() {
    std::string modelName = "data/labixx710.htsvoice";
    std::string modelStr = getFileString(modelName);
    std::string filterName = "data/mix_excitation_5filters_199taps_48Kz.txt";
    std::string filterStr = getFileString(filterName);
    InterModules* htsengine = new HtsEngine(modelStr, filterStr);
    std::string labelName = "data/labixx.lab";
    //((HtsEngine*) htsengine)->synthesisWithLableName(labelName);
    std::string labelString = getFileString(labelName);
    htsengine->process(labelString);
}

void totalTest() {
    std::shared_ptr<cppmary::InterModules> phonemiser_;
    std::shared_ptr<cppmary::InterModules> prosody_;
    std::shared_ptr<cppmary::InterModules> pronuciation_;
    std::shared_ptr<cppmary::InterModules> label_;
    std::shared_ptr<cppmary::InterModules> htsengine_;
    std::shared_ptr<cppmary::InterModules> tokenizer_;
    std::shared_ptr<cppmary::FeatureProcessorManager> manager_;
    std::shared_ptr<cppmary::TargetFeatureComputer> featureComputer_;

    std::string basePath = "./";

    std::string jieba_buffer = getFileString(basePath+"data/jieba/jieba.dict.utf8");
    std::string hmm_model_buffer = getFileString(basePath+"data/jieba/hmm_model.utf8");;
    std::string user_buffer = getFileString(basePath+"data/jieba/user.dict.utf8");
    JiebaSegment::Instance()->LoadResource(jieba_buffer,
                                           hmm_model_buffer,
                                           user_buffer);
    tokenizer_ = std::shared_ptr<cppmary::Tokenizer>(new cppmary::Tokenizer());
    std::string sylDictName = basePath+"data/pinyin_han.txt";
    std::string wordDictName = basePath+"data/mix_pinyin_word.txt";
    std::string sylDictStr = getFileString(sylDictName);
    std::string wordDictStr = getFileString(wordDictName);
    std::string lexiconDictName = basePath+"data/zh_ph64_lexicon.dict";
    std::string lexiconDictStr = getFileString(lexiconDictName);
    phonemiser_ = std::shared_ptr<cppmary::Phonemiser>(new cppmary::Phonemiser(wordDictStr, sylDictStr, lexiconDictStr));
    prosody_ = std::shared_ptr<cppmary::Prosody>(new cppmary::Prosody());
    pronuciation_ = std::shared_ptr<cppmary::Pronunciation>(new cppmary::Pronunciation());
    std::string allophoneSetName = basePath+"data/allophones.zh_PH64.xml";
    std::string allophoneSetStr = getFileString(allophoneSetName);
    //FeatureProcessorManager manager("zh", allophoneSetStr);
    manager_ = std::shared_ptr<FeatureProcessorManager>(new FeatureProcessorManager("zh", allophoneSetStr));
    std::string trickyName = basePath+"data/trickyPhones.txt";
    std::string trickyStr = getFileString(trickyName);
    std::shared_ptr<PhoneTranslator> phoneTranslator = std::shared_ptr<PhoneTranslator>(new PhoneTranslator(trickyStr));
    //std::string featureMapName = basePath+"data/hmmFeaturesMap1.txt";
    std::string featureMapName = basePath+"data/hmmFeaturesMap.txt";
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
    featureComputer_ = std::shared_ptr<TargetFeatureComputer>(new TargetFeatureComputer(manager_, contextFeatureName));
    std::cout << "context feature size: " << contextFeatureName.size() << std::endl;
    assert(featureName.size() == featureAlias.size());
    label_ = std::shared_ptr<LabelGenerator>(new LabelGenerator(manager_, featureComputer_, featureName, featureAlias, phoneTranslator));
    std::string modelName = basePath+"data/labixx710.htsvoice";
    std::string modelStr = getFileString(modelName);
    std::string filterName = basePath+"data/mix_excitation_5filters_199taps_48Kz.txt";
    std::string filterStr = getFileString(filterName);
    htsengine_ = std::shared_ptr<HtsEngine>(new HtsEngine(modelStr, filterStr));

    //std::string input = "这个世界上，为什么只有我这么帅呢?";
    std::string input;
    std::string testFile = "data/input.txt";
    std::ifstream ifs(testFile.c_str());
    getline(ifs, input);
    ifs.close();
    std::string outfile = "total_test.wav";

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
    std::cout << "module total test ok" << std::endl;
}

int main() {
    //text2MaryTest();
    //TokenizerTest();
    //tokenModuleTest();
    //phonemiserTest();
    //replaceTest();
    //prosodyTest();
    //pronunciationTest();
    //labelTest();
    //allophoneTest();
    //LabelGeneratorTest();
    //HtsEngineTest();
    totalTest();
}

