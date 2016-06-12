//
// Created by sooda on 16/6/12.
//

#include "modules/Phonemiser.h"
#include "limonp/Logging.hpp"
#include "pugixml/pugixml.hpp"
#include "common.h"

namespace cppmary {
    std::string Phonemiser::process(std::string input) {
        XLOG(DEBUG) << "phonemizer input: " << input;
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(input.c_str());
        pugi::xml_node tokens = doc.child("maryxml").child("p").child("s");
        std::string sylDictName = "test/pinyin_han.txt";
        std::string wordDictName = "test/mix_pinyin_word.txt";
        cppmary::ConvertPinyin pinyinConverter(wordDictName, sylDictName);
        for (pugi::xml_node token = tokens.first_child(); token; token = token.next_sibling()) {
            std::string tokenValue(token.child_value());
            tokenValue = cppmary::trim(tokenValue);
            std::string tempPinyin = pinyinConverter.getWordPinyin(tokenValue);
            if (!tempPinyin.empty()) {
                std::vector<std::string> pinyins = cppmary::split(tempPinyin, ' ');
                assert(pinyins.size() >= 1);
                std::string pinyinseq = "";
                std::string toneseq = "";
                for (int i = 0; i < pinyins.size(); i++) {
                    std::string currentPinyin = cppmary::trim(pinyins[i]);
                    if (currentPinyin.empty()) {
                        continue;
                    } else {
                        char tone = currentPinyin.back();
                        assert(isdigit(tone));
                        if (pinyinseq.empty()) {
                            pinyinseq = currentPinyin;
                            toneseq = tone;
                        } else {
                            pinyinseq = pinyinseq + " - " + currentPinyin;
                            toneseq = toneseq + " - ";
                            toneseq.push_back(tone);
                        }
                    }
                }
                token.append_attribute("pinyinseq") = pinyinseq.c_str();
                token.append_attribute("toneseq") = toneseq.c_str();
            }
        }
        std::string phonemiserStr = MaryXml::saveDoc2String(doc);
        XLOG(DEBUG) << "phonemizer output: " << phonemiserStr;
        return phonemiserStr;
    }
}
