//
// Created by sooda on 16/6/7.
//

#include <iostream>
//#include "modules/TextToMaryXml.h"
#include "pugixml/pugixml.hpp"
//#include "common/WordsProcess.h"
#include "cppmary.h"
#include "features.h"
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
    //WordsProcess::Instance()->LoadResource("data/jieba/jieba.dict.utf8", "data/jieba/hmm_model.utf8", "data/jieba/user.dict.utf8");
    WordsProcess::Instance()->LoadResource("data/jieba/");
    std::vector<std::string> words;
    WordsProcess::Instance()->Cut("欢迎使用文本转语音服务!", words);
    for (int i = 0; i < words.size(); i++) {
        std::cout << words[i] << std::endl;
    }
}

void tokenModuleTest() {
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
    cppmary::InterModules* phonemiser = new cppmary::Phonemiser();
    std::string phoneStr = phonemiser->process(tokenStr);
}

void prosodyTest() {
    std::string rawXml = cppmary::TextToMaryXml::getInstance().process("欢迎，使用。文本转！语音？服务!");
    cppmary::InterModules* tokenizer = new cppmary::Tokenizer();
    std::string tokenStr = tokenizer->process(rawXml);
    cppmary::InterModules* phonemiser = new cppmary::Phonemiser();
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

    std::string allophoneSetName = "test/allophones.zh.xml";
    pugi::xml_document doc1;
    pugi::xml_parse_result result = doc1.load_file(allophoneSetName.c_str());
    std::string alloStr = MaryXml::saveDoc2String(doc1);

    FeatureProcessorManager manager("zh", alloStr);
    //TargetFeatureComputer featureComputer(manager, "phrase_numsyls phone phrase_zhtone prevprev_zhtone prev_zh_tone zh_tone next_zhtone nextnext_zh_tone pos tobi_accent prev_accent prevprev_tobi_accent next_accent nextnext_tobi_accent accented accented_syls_from_phrase_start accented_syls_from_phrase_end syls_from_prev_accent");
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
    std::string rawXml = cppmary::TextToMaryXml::getInstance().process("这个世界上，为什么只有我这么帅呢？");
    cppmary::InterModules* tokenizer = new cppmary::Tokenizer();
    std::string tokenStr = tokenizer->process(rawXml);
    cppmary::InterModules* phonemiser = new cppmary::Phonemiser();
    std::string phoneStr = phonemiser->process(tokenStr);
    cppmary::InterModules* prosody = new cppmary::Prosody();
    std::string prodyStr = prosody->process(phoneStr);
    cppmary::InterModules* pronuciation = new cppmary::Pronunciation();
    std::string pronunStr = pronuciation->process(prodyStr);
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(pronunStr.c_str());
    featureTest(doc);
}

void labelTest() {
    //std::string puncxmlName = "test/punc.xml";
    std::string puncxmlName = "test/marytts_allophone_example.xml";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(puncxmlName.c_str());
    featureTest(doc);
}

void allophoneTest() {
    std::string allophoneSetName = "test/allophones.zh.xml";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(allophoneSetName.c_str());
    std::string alloStr = MaryXml::saveDoc2String(doc);
    AllophoneSet phoneset(alloStr);
}

void LabelGeneratorTest() {
    std::string puncxmlName = "test/marytts_allophone_example.xml";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(puncxmlName.c_str());
    std::string allophoneExample = MaryXml::saveDoc2String(doc);

    std::string allophoneSetName = "test/allophones.zh.xml";
    pugi::xml_document doc1;
    result = doc1.load_file(allophoneSetName.c_str());
    std::string allosetStr = MaryXml::saveDoc2String(doc1);

    FeatureProcessorManager manager("zh", allosetStr);
    //TargetFeatureComputer featureComputer(manager, "phrase_numsyls phone phrase_zhtone prevprev_zhtone prev_zh_tone zh_tone next_zhtone nextnext_zh_tone pos tobi_accent prev_accent prevprev_tobi_accent next_accent nextnext_tobi_accent accented accented_syls_from_phrase_start accented_syls_from_phrase_end syls_from_prev_accent");
    TargetFeatureComputer featureComputer(manager, "phone prev_phone prev_prev_phone next_phone next_next_phone phrase_numsyls phone phrase_zhtone prevprev_zhtone prev_zh_tone zh_tone next_zhtone nextnext_zh_tone pos tobi_accent prev_accent prevprev_tobi_accent next_accent nextnext_tobi_accent accented accented_syls_from_phrase_start accented_syls_from_phrase_end syls_from_prev_accent syl_break breakindex phrase_numsyls zh_tone segs_from_syl_start segs_from_syl_end syls_from_phrase_start syls_from_phrase_end syl_break is_pause words_from_phrase_start words_from_phrase_end words_from_sentence_start words_from_sentence_end phrases_from_sentence_start phrases_from_sentence_end sentence_punc next_punctuation prev_punctuation words_to_next_punctuation words_from_prev_punctuation position_type tobi_accent");

    std::string featureMapName = "test/hmmFeaturesMap1.txt";
//    std::map<std::string, std::string> hmmFeatureMap;
//    loadDict(hmmFeatureMap, featureMapName, " ");
//    std::map<std::string, std::string>::iterator iter;
//    for (iter = hmmFeatureMap.begin(); iter != hmmFeatureMap.end(); ++iter) {
//        std::cout << iter->first << " ===> " << iter->second << std::endl;
//    }


    InterModules* label = new LabelGenerator(&manager, &featureComputer, featureMapName);
    label->process(allophoneExample);

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
    LabelGeneratorTest();
}
