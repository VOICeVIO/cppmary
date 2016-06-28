//
// Created by sooda on 16/6/28.
//

#include "features/PhoneTranslator.h"
#include "common.h"

namespace cppmary {
    PhoneTranslator::PhoneTranslator(std::string trickyPath) {
       loadTrickyPhones(trickyPath);
    }

    PhoneTranslator::~PhoneTranslator() { }

    void PhoneTranslator::loadTrickyPhones(std::string trickyPath) {
        loadDict(trickyPhones_, trickyPath);
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





}
