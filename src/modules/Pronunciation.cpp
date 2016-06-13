//
// Created by sooda on 16/6/13.
//

#include "modules/Pronunciation.h"
#include "limonp/Logging.hpp"
#include <string>
#include "common.h"

namespace cppmary {
    /* 增加syllable的发音及特征
     *   <syllable accent="*" ph="H W aH nnH" pinyin="huan1" stress="1" zhtone="1">
     *   <ph p="H"/>
     *   <ph p="W"/>
     *   <ph p="aH"/>
     *   <ph p="nnH"/>
     *   </syllable>
     */
    std::string Pronunciation::process(std::string input) {
        XLOG(DEBUG) << "Pronunciation input: " << input;
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(input.c_str());
        pugi::xml_node phrases = doc.child("maryxml").child("p").child("s");
        for (pugi::xml_node phrase = phrases.first_child(); phrase; phrase = phrase.next_sibling()) {
            pugi::xml_node tokens = phrase.child("phrase");
            for (pugi::xml_node token = tokens.first_child(); token; token = token.next_sibling()) {
                std::string toneStr = token.attribute("toneseq").as_string();
                std::string pinyinStr = token.attribute("pinyinseq").as_string();
                std::cout << token.name() << " " << pinyinStr << std::endl;
                if (toneStr.empty()) {
                    continue;
                }

            }
        }
        std::string pronunStr = input;
        XLOG(DEBUG) << "Pronunciation output: " << pronunStr;
        return pronunStr;
    }
}