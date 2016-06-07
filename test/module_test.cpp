//
// Created by sooda on 16/6/7.
//

#include <iostream>
#include "modules/TextToMaryXml.h"
#include "pugixml/pugixml.hpp"
using namespace std;

void text2MaryTest() {
    std::string rawXml = cppmary::TextToMaryXml::getInstance().process("欢迎使用文本转语音服务!");
    std::cout << rawXml << std::endl;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(rawXml.c_str());
    std::cout << doc.child("maryxml").first_child().child_value() << std::endl;
    std::cout << "text2MaryTest done" << std::endl;
}

int main() {
    text2MaryTest();
}