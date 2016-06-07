//
// Created by sooda on 16-6-6.
//
#include "cppjieba/Unicode.hpp"
#include <iostream>
#include <string>
#include "common/convertPinyin.h"

void utf8_test() {
    std::string test_str = "欢迎使用文本转语音服务";
    cppjieba::RuneStrArray sentence;
    DecodeRunesInString(test_str, sentence);
    cppjieba::RuneStrArray::const_iterator iter;
    cppjieba::RuneStrArray::const_iterator left;
    cppjieba::RuneStrArray::const_iterator right;
    int index = 0;
    int left_index = 3;
    int right_index = 5;
    for (iter = sentence.begin(); iter != sentence.end(); iter++) {
        std::cout << iter->rune << std::endl;
        if (index == left_index) {
            left = iter;
        } else if (index == right_index) {
            right = iter;
        }
        index++;
    }
    std::string subStr = GetStringFromRunes(test_str, left, right);
    std::cout << subStr << std::endl;
}

void pinyin_test() {
    std::string sylDictName = "test/pinyin_han.txt";
    std::string wordDictName = "test/mix_pinyin_word.txt";
    cppmary::ConvertPinyin pinyinConverter(wordDictName, sylDictName);
    std::cout << pinyinConverter.getWordPinyin("你好") << std::endl;
    std::cout << pinyinConverter.getWordPinyin("只得") << std::endl;
    std::cout << pinyinConverter.getWordPinyin("你。好的?") << std::endl;
    std::cout << "convert pinyin done" << std::endl;
}

int main() {
    //utf8_test();
    pinyin_test();
}