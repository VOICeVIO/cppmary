//
// Created by sooda on 16/6/6.
//
#include "common/util.h"
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include "cppjieba/Unicode.hpp"

namespace cppmary {

    std::vector<std::string> split(const std::string &text, char sep) {
        std::vector<std::string> tokens;
        std::size_t start = 0, end = 0;
        while ((end = text.find(sep, start)) != std::string::npos) {
            tokens.push_back(text.substr(start, end - start));
            start = end + 1;
        }
        tokens.push_back(text.substr(start));
        return tokens;
    }

    // trim from start
    std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }

    // trim from end
    std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }

    // trim from both ends
    std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
    }

    void dumpStringMap(std::map<std::string, std::string> stringMap) {
        std::map<std::string, std::string>::iterator iter;
        for (iter = stringMap.begin(); iter != stringMap.end(); iter++) {
            std::cout << iter->first << " " << iter->second << std::endl;
        }
    }

    std::vector<std::string> getSyllablesStringVec(std::string& word) {
        cppjieba::RuneStrArray syllables;
        DecodeRunesInString(word, syllables);
        cppjieba::RuneStrArray::const_iterator iter;
        std::vector<std::string> sylsVec;
        for (iter = syllables.begin(); iter != syllables.end(); iter++) {
            std::string subStr = cppjieba::GetStringFromRunes(word, iter, iter);
            subStr = trim(subStr);
            if (subStr.empty()) {
                continue;
            }
            sylsVec.push_back(subStr);
        }
        return sylsVec;
    }

    std::string getMaryXmlHeaderWithLocale(std::string locale) {
        return std::string("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n") + "<maryxml version=\"0.4\"\n"
               + "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n" + "xmlns=\"http://mary.dfki.de/2002/MaryXML\"\n"
               + "xml:lang=\"" + locale + "\">\n";
    }
}
