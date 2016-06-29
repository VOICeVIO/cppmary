//
// Created by sooda on 16/6/6.
//
#include "common/util.h"
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <fstream>
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

    std::vector<std::string> splitAndTrim(const std::string& text, char sep) {
        std::vector<std::string> tokens = split(text, sep);
        std::vector<std::string> trimTokens;
        for (int i = 0; i < tokens.size(); i++) {
            std::string tokenStr = tokens[i];
            tokenStr = trim(tokenStr);
            if (tokenStr.empty()) {
                continue;
            }
            trimTokens.push_back(tokenStr);
        }
        return trimTokens;
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


    std::string getFileString(const std::string& filepath) {
        std::ifstream is(filepath);
        std::string filebuffer="";
        if (is) {
            // get length of file:
            is.seekg (0, is.end);
            long long length = is.tellg();
            is.seekg (0, is.beg);
            char * buffer = new char [length];
            std::cout << "Reading " << filepath << " " << length << " characters... ";
            // read data as a block:
            is.read (buffer,length);
            if (is)
                std::cout << "all characters read successfully." << std::endl;
            else
                std::cout << "error: only " << is.gcount() << " could be read";
            is.close();
            // ...buffer contains the entire file...
            filebuffer = std::string(buffer,length);
            delete[] buffer;
        }
        return filebuffer;
    }

    void loadDict(std::map<std::string, std::string>& dict, const std::string& filePath, const std::string& pattern, bool bufferFlag) {
        std::string line;
        std::vector<std::string> buf;

        if (bufferFlag) {
            std::vector<std::string> bufferVec = limonp::Split(filePath,"\n");
            for (int i = 0; i < bufferVec.size(); i++) {
                std::string line = bufferVec[i];
                line = trim(line);
                limonp::Split(line, buf, pattern);
                assert(buf.size() >= 2);
                dict[trim(buf[0])] = trim(buf[1]);
            }
        } else {
            std::ifstream ifs(filePath.c_str());
            //ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            XCHECK(ifs.is_open()) << "open " << filePath << " failed.";
            for (size_t lineno = 0; getline(ifs, line); lineno++) {
                limonp::Split(line, buf, pattern);
                assert(buf.size() >= 2);
                dict[trim(buf[0])] = trim(buf[1]);
            }
        }
        //dumpStringMap(dict);
    }

    void loadDict(std::vector<std::string>& keys, std::vector<std::string>& values, const std::string& filePath, const std::string& pattern, bool bufferFlag) {
        std::string line;
        std::vector<std::string> buf;

        if (bufferFlag) {
            std::vector<std::string> bufferVec = limonp::Split(filePath,"\n");
            for (int i = 0; i < bufferVec.size(); i++) {
                std::string line = bufferVec[i];
                limonp::Split(line, buf, pattern);
                assert(buf.size() >= 2);
                keys.push_back(buf[0]);
                values.push_back(buf[1]);
            }
        } else {
            std::ifstream ifs(filePath.c_str());
            //ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            XCHECK(ifs.is_open()) << "open " << filePath << " failed.";
            for (size_t lineno = 0; getline(ifs, line); lineno++) {
                limonp::Split(line, buf, pattern);
                assert(buf.size() >= 2);
                keys.push_back(buf[0]);
                values.push_back(buf[1]);
            }
        }
    }

    std::string replaceAll(const std::string& orig, const std::string& replaceThis, const std::string& replaceWith) {
        std::string result = orig;
        while(result.find(replaceThis) != std::string::npos) {
            result.replace(result.find(replaceThis),replaceThis.size(),replaceWith);
        }
        return result;
    }
}
