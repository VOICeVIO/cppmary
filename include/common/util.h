//
// Created by sooda on 16/6/6.
//

#ifndef CPPMARY_STRINGUTIL_H
#define CPPMARY_STRINGUTIL_H

//
// Created by sooda on 16/6/6.
//
#include <string>
#include <vector>
#include <map>

namespace cppmary {

    std::vector<std::string> split(const std::string &text, char sep);
    std::vector<std::string> splitAndTrim(const std::string& text, char sep);

    // trim from start
    std::string &ltrim(std::string &s);

    // trim from end
    std::string &rtrim(std::string &s);

    // trim from both ends
    std::string &trim(std::string &s);

    void dumpStringMap(std::map<std::string, std::string> stringMap);

    std::vector<std::string> getSyllablesStringVec(std::string& word);



    std::string getFileString(const std::string& filepath);

    void loadDict(std::map<std::string, std::string>& dict, const std::string& filePath, const std::string& pattern = " ", bool bufferFlag = false);
    void loadDict(std::vector<std::string>& keys, std::vector<std::string>& values, const std::string& filePath, const std::string& pattern = " ", bool bufferFlag = false);

    std::string replaceAll(const std::string& orig, const std::string& replaceThis, const std::string& replaceWith);

    std::string replaceWith(const std::string& orig, const std::string& replaceThis, const std::string& replaceWith);

    std::string getParentPath(std::string location);



}


#endif //CPPMARY_STRINGUTIL_H
