//
// Created by sooda on 16/6/8.
//

#include "common/MaryXml.h"

namespace cppmary {
    const char* MaryXml::MARYXML = "maryxml";
    const char* MaryXml::PARAGRAPH = "p";
    const char* MaryXml::SENTENCE = "s";
    const char* MaryXml::VOICE = "voice";
    const char* MaryXml::PHRASE = "phrase";
    const char* MaryXml::MARK = "mark";
    const char* MaryXml::SAYAS = "say-as";
    const char* MaryXml::PHONOLOGY = "phonology";
    const char* MaryXml::PROSODY = "prosody";
    const char* MaryXml::AUDIO = "audio";
    const char* MaryXml::BOUNDARY = "boundary";
    const char* MaryXml::MTU = "mtu";
    const char* MaryXml::TOKEN = "t";
    const char* MaryXml::SYLLABLE = "syllable";
    const char* MaryXml::PHONE = "ph";
    const char* MaryXml::NONVERBAL = "vocalization";

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

    pugi::xml_node MaryXml::getNextSiblingElement(pugi::xml_node current) {
        pugi::xml_node node = current;
        if (node.empty()) {
            return pugi::xml_node();
        }
        while (!(node = node.next_sibling()).empty()) {
            if (node.type() == pugi::node_element && strcmp(node.name(), current.name()) == 0) {
                return node;
            }
        }
        return pugi::xml_node();
    }

    pugi::xml_node MaryXml::getPrevSiblingElement(pugi::xml_node current) {
        pugi::xml_node node = current;
        if (node.empty()) {
            return pugi::xml_node();
        }
        while (!(node = node.previous_sibling()).empty()) {
            if (node.type() == pugi::node_element && strcmp(node.name(), current.name()) == 0) {
                return node;
            }
        }
        return pugi::xml_node();
    }

    int MaryXml::getTokenPositionType(const std::vector<pugi::xml_node>& tokens, int currentIndex, std::string & punc) {
        if (tokens.size() <= 1) {
            return tokenPositionType::TOKEN_LESS;
        }
        if (currentIndex == 0) {
            return tokenPositionType::SENTENCE_FIRST; //句首
        }
        if (currentIndex == tokens.size() - 2 || currentIndex == tokens.size() - 1) { 
            //处理复杂情况:多个标点符号, 无标点符号token的情况
            if (!hasAttribute(tokens.back(), "ph")) {
                punc = tokens.back().child_value();
            }
            return tokenPositionType::SENTENCE_END; //句尾
        }
        //assert(currentIndex > 0);
        //assert(currentIndex < tokens.size() -1);
        pugi::xml_node token = tokens[currentIndex];
        pugi::xml_node prevToken = tokens[currentIndex - 1];
        pugi::xml_node nextToken = tokens[currentIndex + 1];
        if (!hasAttribute(nextToken, "ph")) {
            if (!hasAttribute(tokens.back(), "ph")) {
                punc = tokens.back().child_value();
            }
            return tokenPositionType::BEFORE_PUNC; //标点符号前分词
        } else if (!hasAttribute(prevToken, "ph")) {
            return tokenPositionType::AFTER_PUNC; //标点符号后分词
        } else {
            return tokenPositionType::SENTENCE_OTHER; //其他位置
        }
    }

    int MaryXml::getSyllablePositionType(int totalSyllable, int currentIndex) {
        int syllablePosition = 0;
        if (totalSyllable == 1) {
            syllablePosition = syllablePositionType::SINGLE; //单个字分词
        } else {
            if (currentIndex == 0) {
                syllablePosition = syllablePositionType::TOKEN_FIRST; //分词第一个字
            } else if (currentIndex == totalSyllable-1) {
                syllablePosition = syllablePositionType::TOKEN_END; //分词最后一个字
            } else {
                syllablePosition = syllablePositionType::TOKEN_OTHER; //分词其他位置
            }
        }
        return syllablePosition;
    }

}
