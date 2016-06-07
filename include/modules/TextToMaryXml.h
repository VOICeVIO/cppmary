//
// Created by sooda on 16/6/7.
//

#ifndef CPPMARY_TEXTTOMARYXML_H
#define CPPMARY_TEXTTOMARYXML_H
#include <string>

namespace cppmary {

    class TextToMaryXml {
    public:
        static TextToMaryXml &getInstance() {
            static TextToMaryXml instance;
            return instance;
        }

        std::string process(std::string text, std::string locale = "zh", std::string phoneset = "ph64");

    private:
        TextToMaryXml() { }

        TextToMaryXml(TextToMaryXml const &);
        void operator=(TextToMaryXml const &);
    };
}

#endif //CPPMARY_TEXTTOMARYXML_H
