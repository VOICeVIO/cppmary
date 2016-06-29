//
// Created by sooda on 16/6/7.
//

/*
 * accept utf8 string, then convert to pinyin string
 * */
#include <iostream>
#include "limonp/Logging.hpp"
#include "limonp/StringUtil.hpp"
#include "common/convertPinyin.h"
#include "common/util.h"
#include "cppjieba/Unicode.hpp"
#include <fstream>

namespace cppmary {
    ConvertPinyin::~ConvertPinyin() { }
    ConvertPinyin::ConvertPinyin(const std::string &wordDictName, const std::string &syllableDictName) {
        loadDict(wordDict_, wordDictName, ":", true);
        loadDict(syllableDict_,syllableDictName, " ", true);
    }

    //找每个字的拼音
    std::string ConvertPinyin::getSyllablePinyin(std::string syllable) {
        std::map<std::string, std::string>::iterator iter;
        iter = syllableDict_.find(syllable);
        if (iter != syllableDict_.end()) {
            return iter->second;
        } else {
            //return syllable;
            return "";
        }
    }

    //找不到词的拼音,需要找对词进行拆分,查找每个字的拼音
    std::string ConvertPinyin::getSyllablesPinyin(std::string word) {
        std::string result = "";
        std::vector<std::string> syllables = getSyllablesStringVec(word);
        for (int i = 0; i < syllables.size(); i++) {
            std::string syl = syllables[i];
            std::string syllablePinyin = getSyllablePinyin(syl);
            transform(syllablePinyin.begin(), syllablePinyin.end(), syllablePinyin.begin(), (int (*)(int))tolower);
            std::cout << syl << " " << syllablePinyin << std::endl;
            if (result.empty()) {
                result = syllablePinyin;
            } else {
                result = result + " " + syllablePinyin;
            }
        }
        return result;
    }

    std::string ConvertPinyin::getWordPinyin(std::string word) {
        std::map<std::string, std::string>::iterator iter;
        iter = wordDict_.find(word);
        if (iter != wordDict_.end()) {
            return iter->second;
        } else {
            return getSyllablesPinyin(word);
        }
    }

}
