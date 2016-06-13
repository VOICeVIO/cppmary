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

    bool MaryXml::isAncestor(pugi::xml_node ancestor, pugi::xml_node node) {
        pugi::xml_node p = node;
        while(!(p = p.parent()).empty()) {
            if (ancestor == p) {
                return true;
            }
        }
        return false;
    }

    pugi::xml_node MaryXml::getAncestor(pugi::xml_node node, std::string ancestorName) {
        pugi::xml_node p = node;
        while ( !(p=p.parent()).empty()) {
            if (p.name() == ancestorName) {
                return p;
            }
        }
        return pugi::xml_node();
    }

    pugi::xml_node MaryXml::getClosetAncestorWithAttribute(pugi::xml_node node, std::string ancestorName, std::string attributeName) {
        for (pugi::xml_node a = getAncestor(node, ancestorName); !a.empty(); a = getAncestor(a, ancestorName)) {
            if (a.type() == pugi::node_element && hasAttribute(a, attributeName)) {
                return a;
            }
        }
        return pugi::xml_node();
    }

    pugi::xml_node MaryXml::closestCommonAncestor(pugi::xml_node first, pugi::xml_node last) {
        if (first.empty() || last.empty()) {
            return pugi::xml_node();
        }
        pugi::xml_node a = first.parent();
        while (!a.empty() && !isAncestor(a, last)) {
            a = a.parent();
        }
        return a;
    }

    pugi::xml_node MaryXml::encloseNodesWithNewElement(pugi::xml_node first, pugi::xml_node last, std::string newElementName) {
        if (first.empty() || last.empty()){
            return pugi::xml_node();
        }
        pugi::xml_node a = closestCommonAncestor(first, last);
        if (a.empty()) {
            return a;
        }
        pugi::xml_node childA = first;
        while (childA.parent() != a) {
            childA = childA.parent();
        }
        pugi::xml_node childZ = last;
        while (childZ.parent() != a) {
            childZ = childZ.parent();
        }
        pugi::xml_node newElement = a.insert_child_before(newElementName.c_str(), childA);

        pugi::xml_node c = childA;
        pugi::xml_node helper;
        while (!c.empty() && c != childZ) {
            helper = c.next_sibling();
            newElement.append_move(c);
            c = helper;
        }
        newElement.append_move(childZ);
        return newElement;
    }

}
