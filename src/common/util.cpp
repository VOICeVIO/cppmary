//
// Created by sooda on 16/6/6.
//
#include "common/util.h"
#include <vector>
#include <string>
#include <functional>
#include <iostream>

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
}
