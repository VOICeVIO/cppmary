//
// Created by sooda on 16/6/28.
//

#include "features/PhoneTranslator.h"
#include "common.h"

namespace cppmary {
    PhoneTranslator::PhoneTranslator(const std::string& trickyStr) {
       loadTrickyPhones(trickyStr);
    }

    PhoneTranslator::~PhoneTranslator() { }

    void PhoneTranslator::loadTrickyPhones(const std::string& trickyStr) {
        loadDict(trickyPhones_, trickyStr, " ", true);
        std::map<std::string, std::string>::iterator iter;
        for (iter = trickyPhones_.begin(); iter != trickyPhones_.end(); iter++) {
            actualPhones_[iter->second] = iter->first;
        }
    }

    std::string PhoneTranslator::replaceTrickyPhones(std::string lab) {
        std::string s = lab;
        std::map<std::string, std::string>::iterator iter;
        iter = trickyPhones_.find(lab);
        if (iter != trickyPhones_.end()) {
            s = iter->second;
        }
        return s;
    }

    std::string PhoneTranslator::replaceBackTrickyPhones(std::string lab) {
        std::string s = lab;
        std::map<std::string, std::string>::iterator iter;
        iter = actualPhones_.find(lab);
        if (iter != actualPhones_.end()) {
            s = iter->second;
        }
        return s;
    }

    std::string PhoneTranslator::replacePunc(std::string lab) {
        std::string s = lab;
        s = replaceWith(s, ".", "pt");
        s = replaceWith(s, ",", "cm");
        s = replaceWith(s, "(", "op");
        s = replaceWith(s, ")", "cp");
        s = replaceWith(s, "?", "in");
        s = replaceWith(s, "\"", "qt");
        return s;
    }

    std::string PhoneTranslator::replaceBackPunc(std::string lab) {
        std::string s = lab;
        s = replaceWith(s, "pt", ".");
        s = replaceWith(s, "cm", ",");
        s = replaceWith(s, "op", "(");
        s = replaceWith(s, "cp", ")");
        s = replaceWith(s, "in", "?");
        s = replaceWith(s, "qt", "\"");
        return s;
    }

    std::string PhoneTranslator::replaceToBI(std::string lab) {
        std::string s = lab;
        s = replaceAll(s, "*", "st");
        s = replaceAll(s, "%", "pc");
        s = replaceAll(s, "^", "ht");
        return s;
    }

    std::string PhoneTranslator::replaceBackToBI(std::string lab) {
        std::string s = lab;
        s = replaceAll(s, "st", "*");
        s = replaceAll(s, "pc", "%");
        s = replaceAll(s, "ht", "^");
        return s;
    }




}
