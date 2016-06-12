//
// Created by sooda on 16/6/12.
//

#include "modules/Phonemiser.h"
#include "limonp/Logging.hpp"
#include "pugixml/pugixml.hpp"
#include "common.h"

namespace cppmary {
    std::string Phonemiser::process(std::string input) {
        XLOG(DEBUG) << "phonemizer input: " << input;
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(input.c_str());
        pugi::xml_node paragraph = doc.child("maryxml").first_child();
        std::string text = paragraph.child_value();
        text = trim(text);
        std::cout << "text: " << text << std::endl;
        std::string phonemiserStr = input;
        XLOG(DEBUG) << "phonemizer output: " << phonemiserStr;
        return phonemiserStr;
    }
}
