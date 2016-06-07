//
// Created by sooda on 16/6/6.
//

#ifndef CPPMARY_STRINGUTIL_H
#define CPPMARY_STRINGUTIL_H

//
// Created by sooda on 16/6/6.
//
#include <string>
#include "common/stringUtils.h"
#include <vector>

namespace cppmary {

    std::vector<std::string> split(const std::string &text, char sep);

    // trim from start
    std::string &ltrim(std::string &s);

    // trim from end
    std::string &rtrim(std::string &s);

    // trim from both ends
    std::string &trim(std::string &s);

}


#endif //CPPMARY_STRINGUTIL_H
