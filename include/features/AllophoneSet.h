//
// Created by sooda on 16/6/16.
//

#ifndef CPPMARY_ALLOPHONESET_H
#define CPPMARY_ALLOPHONESET_H
#include <string>
#include <map>
#include "Allophone.h"
#include "pugixml/pugixml.hpp"

namespace cppmary {
    class AllophoneSet {
        public:
            AllophoneSet(std::string xmlStr);
            AllophoneSet();
            ~AllophoneSet();

            Allophone getAllophone(std::string ph);
            Allophone getSilent();
            std::string getPhoneFeature(std::string ph, std::string featureName);
            std::vector<std::string> getAllophoneNames();

    private:
            std::map<std::string, Allophone> allophones_;
            std::map<std::string, std::vector<std::string> > featureValuesMap_;
            std::vector<std::string> allophoneNames_;
            std::string name_;
            std::string localeStr_;
            Allophone silence_; //Allophone没有默认构造函数,这个应该会出错?
    };

}

#endif //CPPMARY_ALLOPHONESET_H
