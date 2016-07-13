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
    std::string Pronunciation::process(const std::string& input) {
        XLOG(DEBUG) << "Pronunciation input: " << input;
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(input.c_str());
        token_punc_walker tw;
        doc.traverse(tw);
        std::vector<pugi::xml_node> nodes = tw.nodes_;
        const int tobiaccentNum = 18;
        const std::string tobiAccents[tobiaccentNum] = { "0", "*", "H*",  "L*", "!H*", "^H*","L+H*", "L*+H", "L+!H*", "L*+!H",
                                                          "L+^H*", "L*+^H",  "H+!H*","H+L*", "H+^H*", "!H+!H*", "^H+!H*", "^H+^H*"};
        for (int tokenIndex = 0; tokenIndex < nodes.size(); tokenIndex++) {
            pugi::xml_node token = nodes[tokenIndex];
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
            std::string punc = "";
            int tokenPosition = MaryXml::getTokenPositionType(nodes, tokenIndex, punc);
            for (int syllableIndex = 0; syllableIndex < pinyins.size(); syllableIndex++) {
                std::string phone = phones[syllableIndex];
                std::string pinyin = pinyins[syllableIndex];
                std::string tone = tones[syllableIndex];
                std::vector<std::string> sylPhones = splitAndTrim(phone, ' ');
                pugi::xml_node syllable =  token.append_child("syllable");
                //add accent for test; TODO: use the true accent instead
                //setLabixxAccent();
                int syllablePosition = MaryXml::getSyllablePositionType(pinyins.size(), syllableIndex);
                int toneValue = std::stod(tone);
                int accentType = 0;
                if (toneValue > 0 && toneValue <= 5) {
                    accentType = getLabixxAccent(tokenPosition, syllablePosition, toneValue, punc);
                }
                std::string accentValue = tobiAccents[accentType];
                XLOG(DEBUG) << "toneConvert: " << pinyin << " " <<  toneValue << " -> accent:  " << accentType << " " << accentValue;
                syllable.append_attribute("accent") = accentValue.c_str();
                syllable.append_attribute("ph") = phone.c_str();
                syllable.append_attribute("zhtone") = tone.c_str();
                syllable.append_attribute("pinyin") = pinyin.c_str();
                for (int phoneIndex = 0; phoneIndex < sylPhones.size(); phoneIndex++) {
                    std::string sylPhone = sylPhones[phoneIndex];
                    if (sylPhone.empty()) {
                        continue;
                    }
                    syllable.append_child("ph").append_attribute("p") = sylPhone.c_str();
                }
            }
        }
        doc.save_file("data/punc.xml");
        std::string pronunStr = MaryXml::saveDoc2String(doc);
        XLOG(DEBUG) << "Pronunciation output: " << pronunStr;
        return pronunStr;
    }

    int Pronunciation::getLabixxAccent(int tokenPosition, int syllablePosition, int toneValue, std::string punc) {
        int accentValue = toneValue;
        std::map<int, int> normalMap;
        normalMap[1] = 8;
        normalMap[2] = 9;
        normalMap[3] = 12;
        normalMap[4] = 15;
        normalMap[5] = 8;
        if (tokenPosition == tokenPositionType::SENTENCE_FIRST) { //句首
            if (syllablePosition == syllablePositionType::SINGLE) {
                //句首单字
                accentValue = toneValue;
                if (toneValue == 3) accentValue = 14;
                if (toneValue == 2) accentValue = 11;
                if (toneValue == 4) accentValue = normalMap[toneValue];
                if (toneValue == 1) accentValue = normalMap[toneValue];
            } else if (syllablePosition == syllablePositionType::TOKEN_FIRST) {
                //句首分词第一个字
                accentValue = toneValue;
                if (toneValue == 3) accentValue = 12;
                if (toneValue == 2) accentValue = normalMap[toneValue];
            } else if (syllablePosition == syllablePositionType::TOKEN_END) {
                //句首分词最后一个字
                accentValue = normalMap[toneValue];
                if (toneValue == 3) accentValue = 14;
                if (toneValue == 2) accentValue = normalMap[toneValue];
                if (toneValue == 4) accentValue = normalMap[toneValue];
                if (toneValue == 1) accentValue = normalMap[toneValue];
            } else {
                //句首其他位置
                accentValue = toneValue;
                if (toneValue == 3) accentValue = 14;
            }
        } else if (tokenPosition == tokenPositionType::SENTENCE_END) { //句尾
            if (syllablePosition == syllablePositionType::TOKEN_END
                    || syllablePosition == syllablePositionType::SINGLE) {
                accentValue = normalMap[toneValue];
                if (toneValue == 3) accentValue = 14;
                if (toneValue == 4) accentValue = normalMap[toneValue];
                if (toneValue == 1) accentValue = normalMap[toneValue];
            }
        } else if (tokenPosition == tokenPositionType::BEFORE_PUNC) { //句中标点符号前
            if (syllablePosition == syllablePositionType::TOKEN_END
                    || syllablePosition == syllablePositionType::SINGLE) {
                accentValue = normalMap[toneValue];
                if (toneValue == 3) accentValue = 14;
                if (toneValue == 4) accentValue = normalMap[toneValue];
                if (toneValue == 1) accentValue = normalMap[toneValue];
            }
        } else if (tokenPosition == tokenPositionType::AFTER_PUNC) { //标点符号后
            if (syllablePosition == syllablePositionType::SINGLE) { //单字
                accentValue = toneValue;
                if (toneValue == 3) accentValue = 12;
                if (toneValue == 2) accentValue = normalMap[toneValue];
                if (toneValue == 4) accentValue = normalMap[toneValue];
            } else if (syllablePosition == syllablePositionType::TOKEN_FIRST) { //分词第一个字
                accentValue = toneValue;
                if (toneValue == 3) accentValue = 12;
                if (toneValue == 2) accentValue = normalMap[toneValue];
                if (toneValue == 4) accentValue = normalMap[toneValue];
            } else if (syllablePosition == syllablePositionType::TOKEN_END) {//分词最后一个字
                accentValue = normalMap[toneValue];
                if (toneValue == 3) accentValue = 12;
                if (toneValue == 2) accentValue = normalMap[toneValue];
                if (toneValue == 4) accentValue = normalMap[toneValue];
                if (toneValue == 1) accentValue = normalMap[toneValue];
            } else { //其他位置
                accentValue = toneValue;
            }
        } else {
            if (syllablePosition == syllablePositionType::TOKEN_END) {//分词最后一个字
                accentValue = normalMap[toneValue];
            }
        }
        return accentValue;
    }
}
