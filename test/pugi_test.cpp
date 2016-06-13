#include "pugixml/pugixml.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "common.h"
#include "limonp/Logging.hpp"


bool try_imbue(std::wistream &stream, const char *name) {
    try {
        stream.imbue(std::locale(name));

        return true;
    }
    catch (const std::exception &) {
        return false;
    }
}

void simple_test() {
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("test/tree.xml");

    std::cout << "Load result: " << result.description() << ", mesh name: " <<
    doc.child("mesh").attribute("name").value() << std::endl;
}

void print_doc(const char *message, const pugi::xml_document &doc, const pugi::xml_parse_result &result) {
    std::cout << message
    << "\t: load result '" << result.description() << std::endl << doc.first_child().name()
    << " token " << doc.first_child().first_child().first_child().first_child().child_value()
    << std::endl;
}

void transverse_base(const pugi::xml_document &doc) {
    pugi::xml_node tokens = doc.child("maryxml").child("p").child("s");

    // tag::basic[]
    for (pugi::xml_node token = tokens.first_child(); token; token = token.next_sibling()) {
        std::string token_value(token.child_value());
        std::cout << "token: " << token.name() << " " << cppmary::trim(token_value) << std::endl;

        for (pugi::xml_attribute attr = token.first_attribute(); attr; attr = attr.next_attribute()) {
            std::cout << "name:  " << attr.name() << " value: " << attr.value();
        }

        std::cout << " posattribute: " << cppmary::MaryXml::hasAttribute(token, "pos") << std::endl;
    }
}

void wide_char_test() {
    pugi::xml_document doc;
    std::wifstream stream("test/pos.xml");

    if (try_imbue(stream, "en_US.UTF-8")) // try Linux encoding
    {
        pugi::xml_parse_result result = doc.load(stream);
        //print_doc("UTF8 file from wide stream", doc, result);
        transverse_base(doc);
    }
}

void narrow_char_test() {
    XLOG(INFO) << "in narrow char test" ;
    pugi::xml_document doc;
    std::ifstream stream("test/pos.xml");
    pugi::xml_parse_result result = doc.load(stream);
    //print_doc("UTF8 file from wide stream", doc, result);
    transverse_base(doc);
}

void maryxml_test() {
    pugi::xml_document doc;
    std::ifstream stream("test/pos.xml");
    pugi::xml_parse_result result = doc.load(stream);
    pugi::xml_node tokens = doc.child("maryxml").child("p").child("s");
    pugi::xml_node paragraph = doc.child("maryxml").child("p");
    std::cout << "is ancestor: " << cppmary::MaryXml::isAncestor(paragraph, tokens) << std::endl;
    std::cout << "is ancestor: " << cppmary::MaryXml::isAncestor(tokens, paragraph) << std::endl;

    pugi::xml_node common = cppmary::MaryXml::closestCommonAncestor(tokens, paragraph);
    std::cout << "common " <<  common.name() << std::endl;

    pugi::xml_node common1 = cppmary::MaryXml::closestCommonAncestor(paragraph, tokens);
    std::cout << "common1 " << common1.name() << std::endl;

    pugi::xml_node enclose = cppmary::MaryXml::encloseNodesWithNewElement(paragraph, tokens, "enclose");

    std::string encloseStr = cppmary::MaryXml::saveDoc2String(doc);
    std::cout << encloseStr << std::endl;


    //for (pugi::xml_node token = tokens.first_child(); token; token = token.next_sibling()) {
    //    std::string token_value(token.child_value());
    //    std::cout << token_value << std::endl;
    //}
}

int main() {
    //simple_test();
    //wide_char_test();
    //narrow_char_test();
    maryxml_test();
}

