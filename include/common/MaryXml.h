//
// Created by sooda on 16/6/8.
//

#ifndef CPPMARY_MARYXML_H
#define CPPMARY_MARYXML_H
#include "pugixml/pugixml.hpp"
#include <string>

namespace cppmary {
    struct xml_string_writer : pugi::xml_writer {
        std::string result;
        virtual void write(const void *data, size_t size) {
            result.append(static_cast<const char *>(data), size);
        }
    };
    class MaryXml {
    public:
        static std::string getMaryXmlHeaderWithLocale(std::string locale);
        static void appendChild(pugi::xml_node doc, std::string childName);
    };
}


#endif //CPPMARY_MARYXML_H
