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
        Lexicon(const std::string& lexiconDictStr);
        ~Lexicon();
        std::string getLexiconPhonemes(std::string syllable);
    private:
        std::map<std::string, std::string> lexiconDict_;

    };
}


#endif //CPPMARY_LEXICON_H
