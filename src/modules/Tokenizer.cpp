//
// Created by sooda on 16/6/8.
//

#include "modules/Tokenizer.h"
#include <iostream>
#include "common.h"
#include "pugixml/pugixml.hpp"
#include "limonp/Logging.hpp"

namespace cppmary {
    std::string Tokenizer::process(std::string input) {
        XLOG(DEBUG) << "tokenizer input: " << input;
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(input.c_str());
        pugi::xml_node paragraph = doc.child("maryxml").first_child();
        std::string text = paragraph.child_value();
        text = trim(text);
        //std::vector<std::string> words;
        std::vector<std::pair<std::string, std::string> > wordTags;
        WordsProcess::Instance()->LoadResource("data/jieba/");
        WordsProcess::Instance()->Tag(text, wordTags);
        pugi::xml_node textNode = paragraph.first_child();
        paragraph.remove_child(textNode);
        for (int i = 0; i < wordTags.size(); i++) {
            pugi::xml_node token = paragraph.append_child("t");
            token.append_child(pugi::node_pcdata).set_value(wordTags[i].first.c_str());
            std::string pos = wordTags[i].second;
            transform(pos.begin(), pos.end(), pos.begin(), (int (*)(int))toupper);
            token.append_attribute("pos") = pos.c_str();
        }
        cppmary::xml_string_writer writer;
        doc.print(writer);
        std::string tokenStr = writer.result;
        XLOG(DEBUG) << "tokenizer output: " << tokenStr;
        return tokenStr;
    }
}