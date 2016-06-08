//
// Created by sooda on 16/6/8.
//

#include "common/MaryXml.h"

namespace cppmary {
    std::string MaryXml::getMaryXmlHeaderWithLocale(std::string locale) {
        return std::string("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n") + "<maryxml version=\"0.4\"\n"
               + "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n" + "xmlns=\"http://mary.dfki.de/2002/MaryXML\"\n"
               + "xml:lang=\"" + locale + "\">\n";
    }

    void MaryXml::appendChild(pugi::xml_node doc, std::string childName) {
        doc.append_child(childName.c_str());
    }

}