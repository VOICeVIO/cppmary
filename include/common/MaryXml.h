//
// Created by sooda on 16/6/8.
//

#ifndef CPPMARY_MARYXML_H
#define CPPMARY_MARYXML_H
#include "pugixml/pugixml.hpp"
#include <string>
#include <cstring>
#include <vector>

namespace cppmary {

    enum tokenPositionType {
        TOKEN_LESS = 0,
        SENTENCE_FIRST = 1,
        SENTENCE_END = 2,
        BEFORE_PUNC = 3,
        AFTER_PUNC = 4,
        SENTENCE_OTHER = 5
    };

    enum syllablePositionType {
        SINGLE = 1,
        TOKEN_FIRST = 2,
        TOKEN_END = 3,
        TOKEN_OTHER = 4
    };

    struct xml_string_writer : pugi::xml_writer {
        std::string result;
        virtual void write(const void *data, size_t size) {
            result.append(static_cast<const char *>(data), size);
        }
    };

    struct token_walker: pugi::xml_tree_walker {
        virtual bool for_each(pugi::xml_node& node) {
            if (node.type() == pugi::node_element && (strcmp(node.name(), "t") == 0 && !(std::string(node.attribute("ph").as_string()).empty()))) {
                nodes_.push_back(node);
            }
            return true;
        }
        std::vector<pugi::xml_node> nodes_;
    };

    struct token_boundary_walker: pugi::xml_tree_walker {
        virtual bool for_each(pugi::xml_node& node) {
            if (node.type() == pugi::node_element && ((strcmp(node.name(), "t") == 0 && !(std::string(node.attribute("ph").as_string()).empty())) || strcmp(node.name(), "boundary") == 0)) {
                nodes_.push_back(node);
            }
            return true;
        }
        std::vector<pugi::xml_node> nodes_;
    };

    struct token_punc_walker: pugi::xml_tree_walker {
        virtual bool for_each(pugi::xml_node& node) {
            if (node.type() == pugi::node_element && (strcmp(node.name(), "t") == 0)) {
                nodes_.push_back(node);
            }
            return true;
        }
        std::vector<pugi::xml_node> nodes_;
    };

    struct token_boundary_punc_walker: pugi::xml_tree_walker {
        virtual bool for_each(pugi::xml_node& node) {
            if (node.type() == pugi::node_element && ((strcmp(node.name(), "t") == 0) || (strcmp(node.name(), "boundary") == 0)) ) {
                nodes_.push_back(node);
            }
            return true;
        }
        std::vector<pugi::xml_node> nodes_;
    };

    struct phrase_walker: pugi::xml_tree_walker {
        virtual bool for_each(pugi::xml_node& node) {
            if (node.type() == pugi::node_element && (strcmp(node.name(), "phrase") == 0)) {
                nodes_.push_back(node);
            }
            return true;
        }
        std::vector<pugi::xml_node> nodes_;
    };

    struct phone_boundary_walker: pugi::xml_tree_walker {
        virtual bool for_each(pugi::xml_node& node) {
            if (node.type() == pugi::node_element && ((strcmp(node.name(), "ph") == 0) || (strcmp(node.name(), "boundary") == 0)) ) {
                nodes_.push_back(node);
            }
            return true;
        }
        std::vector<pugi::xml_node> nodes_;
    };
    

    struct phone_walker: pugi::xml_tree_walker {
        virtual bool for_each(pugi::xml_node& node) {
            if (node.type() == pugi::node_element && ((strcmp(node.name(), "ph") == 0))) {
                nodes_.push_back(node);
            }
            return true;
        }
        std::vector<pugi::xml_node> nodes_;
    };

    struct syllable_boundary_walker: pugi::xml_tree_walker {
        virtual bool for_each(pugi::xml_node& node) {
            if (node.type() == pugi::node_element && ((strcmp(node.name(), "syllable") == 0) || (strcmp(node.name(), "boundary") == 0)) ) {
                nodes_.push_back(node);
            }
            return true;
        }
        std::vector<pugi::xml_node> nodes_;
    };

    struct syllable_walker: pugi::xml_tree_walker {
        virtual bool for_each(pugi::xml_node& node) {
            if (node.type() == pugi::node_element && ((strcmp(node.name(), "syllable") == 0)) ) {
                nodes_.push_back(node);
            }
            return true;
        }
        std::vector<pugi::xml_node> nodes_;
    };

    struct phoneset_walker: pugi::xml_tree_walker {
        virtual bool for_each(pugi::xml_node& node) {
            if (node.type() == pugi::node_element && ((strcmp(node.name(), "vowel") == 0) || (strcmp(node.name(), "consonant") == 0) ||
                        (strcmp(node.name(), "silence") == 0) || (strcmp(node.name(), "tone") == 0) )) {
                nodes_.push_back(node);
            }
            return true;
        }
        std::vector<pugi::xml_node> nodes_;
    };

    class MaryXml {
    public:
        static std::string getMaryXmlHeaderWithLocale(std::string locale);
        static std::string saveDoc2String(const pugi::xml_document& doc);
        static void appendChild(pugi::xml_node doc, std::string childName);
        static bool hasAttribute(const pugi::xml_node& node, const std::string& attributeName);
        static bool isAncestor(pugi::xml_node ancestor, pugi::xml_node node);
        static pugi::xml_node getAncestor(pugi::xml_node node, std::string ancestorName);
        static pugi::xml_node getClosetAncestorWithAttribute(pugi::xml_node node, std::string ancestorName, std::string attributeName);
        static pugi::xml_node closestCommonAncestor(pugi::xml_node first, pugi::xml_node last);
        static pugi::xml_node encloseNodesWithNewElement(pugi::xml_node first, pugi::xml_node last, std::string newElementName);
        static const char* getMaryDataTypeStr(int enumVal);
        static pugi::xml_node getNextSiblingElement(pugi::xml_node current);
        static pugi::xml_node getPrevSiblingElement(pugi::xml_node current);
        static int getTokenPositionType(const std::vector<pugi::xml_node> & tokens, int currentIndex, std::string& punc);
        static int getSyllablePositionType(int totalSyllable, int currentIndex);

        static const char* MARYXML;
        static const char* PARAGRAPH;
        static const char* SENTENCE;
        static const char* VOICE;
        static const char* PHRASE;
        static const char* MARK;
        static const char* SAYAS;
        static const char* PHONOLOGY;
        static const char* PROSODY;
        static const char* AUDIO;
        static const char* BOUNDARY;
        static const char* MTU;
        static const char* TOKEN;
        static const char* SYLLABLE;
        static const char* PHONE;
        static const char* NONVERBAL;
    };
}


#endif //CPPMARY_MARYXML_H
