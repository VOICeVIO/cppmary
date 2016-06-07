//
// Created by sooda on 16/6/7.
//

/*
 * accept utf8 string, then convert to pinyin string
 * */
#include <iostream>
#include "cppjieba/limonp/Logging.hpp"
#include "cppjieba/limonp/StringUtil.hpp"
#include "common/convertPinyin.h"
#include "common/util.h"
#include <fstream>

#define _DEBUG

namespace cppmary {
    ConvertPinyin::~ConvertPinyin() { }
    ConvertPinyin::ConvertPinyin(const std::string &wordDictName, const std::string &syllableDictName) {
        loadDict(wordDict_, wordDictName, ":");
        loadDict(syllableDict_,syllableDictName);
    }

    void ConvertPinyin::loadDict(std::map<std::string, std::string>& dict, const std::string& filePath, const std::string& pattern) {
        std::ifstream ifs(filePath.c_str());
        XCHECK(ifs.is_open()) << "open " << filePath << " failed.";
        std::string line;
        std::vector<std::string> buf;

        for (size_t lineno = 0; getline(ifs, line); lineno++) {
            limonp::Split(line, buf, pattern);
//#ifdef _DEBUG
//            for (int i = 0; i < buf.size(); i++) {
//                std::cout << buf[i] << " ";
//            }
//            std::cout << std::endl;
//#endif
            assert(buf.size() >= 2);
            dict[trim(buf[0])] = trim(buf[1]);
        }
        //dumpStringMap(dict);
    }

}
