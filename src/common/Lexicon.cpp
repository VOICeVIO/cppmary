//
// Created by sooda on 16/6/12.
//

#include "common/Lexicon.h"
#include "common.h"

namespace cppmary {
    Lexicon::~Lexicon() { }
    Lexicon::Lexicon(const std::string &lexiconDictName) {
        lexiconDictName_ = lexiconDictName;
        loadDict(lexiconDict_, lexiconDictName, "|");
    }

    //找每个字的拼音
    std::string Lexicon::getLexiconPhonemes(std::string syllable) {
        std::map<std::string, std::string>::iterator iter;
        iter = lexiconDict_.find(syllable);
        if (iter != lexiconDict_.end()) {
            return iter->second;
        } else {
            //return syllable;
            return "";
        }
    }
}