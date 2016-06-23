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
    //TODO: add final bounary
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
    TargetFeatureComputer featureComputer(manager, "phrase_numsyls phone phrase_zhtone prevprev_zhtone prev_zhtone zhtone next_zhtone nextnext_zhtone pos tobiAccent prev_tobiAccent prevprev_tobiAccent next_tobiAccent nextnext_tobiAccent accented accented_syls_from_phrase_start accented_syls_from_phrase_end syls_from_prev_accent");
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
    std::string rawXml = cppmary::TextToMaryXml::getInstance().process("欢迎，使用。文本转！语音？服务!");
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
    std::string puncxmlName = "test/punc.xml";
    //std::string puncxmlName = "test/allophone_v1.xml";
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

int main() {
    //text2MaryTest();
    //TokenizerTest();
    //tokenModuleTest();
    //phonemiserTest();
    //replaceTest();
    //prosodyTest();
    //pronunciationTest();
    labelTest();
    //allophoneTest();
}
