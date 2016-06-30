//
// Created by sooda on 16/6/13.
//

#include "modules/Pronunciation.h"
#include "limonp/Logging.hpp"
#include <string>
#include "common.h"

namespace cppmary {

    Pronunciation::Pronunciation() {
        name_ = "Pronunciation";
    }

    Pronunciation::~Pronunciation() { }

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
            //phrase.print(std::cout, "", pugi::format_raw);
            for (pugi::xml_node token = phrase.first_child(); token; token = token.next_sibling()) {
                std::string toneStr = token.attribute("toneseq").as_string();
                std::string pinyinStr = token.attribute("pinyinseq").as_string();
                std::string phoneStr = token.attribute("ph").as_string();
                if (toneStr.empty() || pinyinStr.empty() || phoneStr.empty()) {
                    continue;
                }
                std::vector<std::string> tones = splitAndTrim(toneStr, '-');
                std::vector<std::string> pinyins = splitAndTrim(pinyinStr, '-');
                std::vector<std::string> phones = splitAndTrim(phoneStr, '-');
                assert(tones.size() == pinyins.size());
                assert(tones.size() == phones.size());
                for (int i = 0; i < pinyins.size(); i++) {
                    std::string phone = phones[i];
                    std::string pinyin = pinyins[i];
                    std::string tone = tones[i];
                    std::vector<std::string> sylPhones = splitAndTrim(phone, ' ');
                    pugi::xml_node syllable =  token.append_child("syllable");
                    //add accent for test; TODO: use the true accent instead
                    syllable.append_attribute("accent") = "H*";
                    syllable.append_attribute("ph") = phone.c_str();
                    syllable.append_attribute("zhtone") = tone.c_str();
                    syllable.append_attribute("pinyin") = pinyin.c_str();
                    for (int i = 0; i < sylPhones.size(); i++) {
                        std::string sylPhone = sylPhones[i];
                        if (sylPhone.empty()) {
                            continue;
                        }
                        syllable.append_child("ph").append_attribute("p") = sylPhone.c_str();
                    }
                }
            }
        }
        //doc.save_file("test/punc.xml");
        std::string pronunStr = MaryXml::saveDoc2String(doc);
        XLOG(DEBUG) << "Pronunciation output: " << pronunStr;
        return pronunStr;
    }
}