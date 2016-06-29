//
// Created by sooda on 16/6/28.
//

#ifndef CPPMARY_PHONETRANSLATOR_H
#define CPPMARY_PHONETRANSLATOR_H
#include <map>
#include <string>

namespace cppmary {
    class PhoneTranslator {
    public:
        PhoneTranslator(const std::string& trickyStr);
        ~PhoneTranslator();
        void loadTrickyPhones(const std::string& trickyPath);
        std::string replaceTrickyPhones(std::string lab);
        std::string replaceBackTrickyPhones(std::string lab);
    private:
        std::map<std::string, std::string> trickyPhones_;
        std::map<std::string, std::string> actualPhones_;
    };
}

#endif //CPPMARY_PHONETRANSLATOR_H
