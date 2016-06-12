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

    std::string MaryXml::saveDoc2String(const pugi::xml_document& doc) {
        cppmary::xml_string_writer writer;
        doc.print(writer);
        return writer.result;
    }

    bool MaryXml::hasAttribute(const pugi::xml_node &node, const std::string& attributeName) {
        for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
            if (attr.name() == attributeName) {
                return true;
            }
        }
        return false;
    }

}