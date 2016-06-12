//
// Created by sooda on 16/6/7.
//

#ifndef CPPMARY_CONVERTPINYIN_H
#define CPPMARY_CONVERTPINYIN_H

#include <iostream>
#include <map>
#include <string>

namespace cppmary {

    class ConvertPinyin {
    public:
        ConvertPinyin(const std::string &wordDictName, const std::string &syllableDictName);
        ConvertPinyin();
        ~ConvertPinyin();
        std::string getWordPinyin(std::string word);
        std::string getSyllablesPinyin(std::string word);
        std::string getWordsPinyin(std::string words);
        std::string getSyllablePinyin(std::string syllable);

        private:
        std::string wordDictName_;
        std::string syllableDictName_;
        std::map<std::string, std::string> syllableDict_;
        std::map<std::string, std::string> wordDict_;
    };

}



#endif //CPPMARY_CONVERTPINYIN_H
