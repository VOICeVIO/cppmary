//
// Created by sooda on 16/6/12.
//

#ifndef CPPMARY_LEXICON_H
#define CPPMARY_LEXICON_H
#include <string>
#include <map>

namespace cppmary {
    class Lexicon {
    public:
        Lexicon(const std::string& lexiconDictName);
        ~Lexicon();
        void loadDict(std::map<std::string, std::string>& dict, const std::string& filePath, const std::string& pattern);
        std::string getLexiconPhonemes(std::string syllable);
    private:
        std::string lexiconDictName_;
        std::map<std::string, std::string> lexiconDict_;

    };
}


#endif //CPPMARY_LEXICON_H
