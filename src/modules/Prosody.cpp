//
// Created by sooda on 16/6/13.
//

#include "modules/Prosody.h"
#include "common.h"
#include "limonp/Logging.hpp"

namespace cppmary {
    Prosody::Prosody() {
        resetPuncinations(SPECIAL_PUNCINATIONS);
    }

    Prosody::~Prosody() {
        puncination_.clear();
    }

    bool Prosody::isPuncinatiion(std::string text) {
        cppjieba::RuneStrArray runes;
        if (!cppjieba::DecodeRunesInString(text, runes)) {
            XLOG(ERROR) << "decode " << text << " failed";
            return false;
        }
        if (runes.size() != 1) {
            return false;
        } else {
            return puncination_.end() != puncination_.find(runes[0].rune);
        }
    }

    std::string Prosody::process(std::string input) {
        //增加phase和bournary
        XLOG(DEBUG) << "Prosody input: " << input;
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(input.c_str());
        pugi::xml_node tokens = doc.child("maryxml").child("p").child("s");
        
        pugi::xml_node first, last;
        first = tokens.first_child();
        for (pugi::xml_node token = tokens.first_child(); token; token = token.next_sibling()) {
            last = token;
            std::string tokenValue(token.child_value());
            tokenValue = cppmary::trim(tokenValue);
            if (isPuncinatiion(tokenValue)) {
                pugi::xml_node newNode = tokens.insert_child_after("bounary", token);
                int breakindexValue = 3;
                if (last == tokens.last_child()) {
                    breakindexValue = 6;
                }
                newNode.append_attribute("breakindex") = breakindexValue;
                last = newNode;
                MaryXml::encloseNodesWithNewElement(first, last, "phrase");
                token = newNode.next_sibling();
                first = token;
            } 
        }
        if (last != tokens.last_child()) {
            last = tokens.last_child();
            pugi::xml_node newNode = tokens.insert_child_after("bounary", last);
            last = newNode;
            newNode.append_attribute("breakindex") = 6;
            MaryXml::encloseNodesWithNewElement(first, last, "phrase");
        }

        std::string prosodyStr = MaryXml::saveDoc2String(doc);
        XLOG(DEBUG) << " Prosody: " << prosodyStr;
        return prosodyStr;
    }

    bool Prosody::resetPuncinations(const std::string& s) {
        puncination_.clear();
        cppjieba::RuneStrArray runes;
        if (!cppjieba::DecodeRunesInString(s, runes)) {
            XLOG(ERROR) << "decode " << s << " failed";
            return false;
        }
        for (size_t i = 0; i < runes.size(); i++) {
            std::cout << i << " " << runes[i].rune << std::endl;
            if (!puncination_.insert(runes[i].rune).second) {
                XLOG(INFO) << s.substr(runes[i].offset, runes[i].len) << " already exists";
                return false;
            }
        }
        return true;
    }
}
