//
// Created by sooda on 16/6/7.
//

#include <iostream>
//#include "modules/TextToMaryXml.h"
#include "pugixml/pugixml.hpp"
//#include "common/WordsProcess.h"
#include "cppmary.h"
using namespace std;

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

int main() {
    //text2MaryTest();
    //TokenizerTest();
    //tokenModuleTest();
    //phonemiserTest();
    prosodyTest();
    //replaceTest();
}
