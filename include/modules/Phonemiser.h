//
// Created by sooda on 16/6/12.
//

#ifndef CPPMARY_PHONEMISER_H
#define CPPMARY_PHONEMISER_H

#include "modules/InterModules.h"
#include "common.h"

namespace cppmary {

    class Phonemiser : public InterModules {
    public:
        Phonemiser(const std::string& wordDictStr, const std::string& sylDictStr, const std::string& lexiconDictStr);
        virtual std::string process(const std::string& input);
    private:
        cppmary::Lexicon lexiconTranslator_;
        cppmary::ConvertPinyin pinyinConverter_;
    };

}

#endif //CPPMARY_PHONEMISER_H
