//
// Created by sooda on 16/6/7.
//

#include "modules/TextToMaryXml.h"
#include "common.h"

namespace cppmary {
    std::string TextToMaryXml::process(const std::string& input, std::string locale, std::string phoneset) {
        std::string text = input;
        text = replaceAll(text, "，", ",");
        text = replaceAll(text, "、", ",");
        text = replaceAll(text, "？", "?");
        text = replaceAll(text, "！", "!");
        text = replaceAll(text, "。", ".");
        return MaryXml::getMaryXmlHeaderWithLocale(locale) + "<p>\n" + text + "\n</p>\n</maryxml>" ;
    }
}
