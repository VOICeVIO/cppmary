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
    void Lexicon::loadDict(std::map<std::string, std::string>& dict, const std::string& filePath, const std::string& pattern) {
        std::ifstream ifs(filePath.c_str());
        XCHECK(ifs.is_open()) << "open " << filePath << " failed.";
        std::string line;
        std::vector<std::string> buf;

        for (size_t lineno = 0; getline(ifs, line); lineno++) {
            limonp::Split(line, buf, pattern);
            assert(buf.size() >= 2);
            dict[trim(buf[0])] = trim(buf[1]);
        }
        //dumpStringMap(dict);
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