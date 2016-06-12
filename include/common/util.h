//
// Created by sooda on 16/6/6.
//

#ifndef CPPMARY_STRINGUTIL_H
#define CPPMARY_STRINGUTIL_H

//
// Created by sooda on 16/6/6.
//
#include <string>
#include "common/util.h"
#include <vector>
#include <map>

namespace cppmary {

    std::vector<std::string> split(const std::string &text, char sep);

    // trim from start
    std::string &ltrim(std::string &s);

    // trim from end
    std::string &rtrim(std::string &s);

    // trim from both ends
    std::string &trim(std::string &s);

    void dumpStringMap(std::map<std::string, std::string> stringMap);

    std::vector<std::string> getSyllablesStringVec(std::string& word);



    std::string getFileString(std::string filepath);

    void loadDict(std::map<std::string, std::string>& dict, const std::string& filePath, const std::string& pattern = " ");



}


#endif //CPPMARY_STRINGUTIL_H
