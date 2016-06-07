//
// Created by sooda on 16/6/7.
//

#include "modules/TextToMaryXml.h"
#include "common/util.h"

namespace cppmary {
    std::string TextToMaryXml::process(std::string text, std::string locale, std::string phoneset) {
        return getMaryXmlHeaderWithLocale(locale) + "<p>\n" + text + "\n</p>\n</maryxml>" ;
    }
}