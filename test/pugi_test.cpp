#include "pugixml/pugixml.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "common/util.h"


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

        std::cout << std::endl;
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
    pugi::xml_document doc;
    std::ifstream stream("test/pos.xml");
    pugi::xml_parse_result result = doc.load(stream);
    //print_doc("UTF8 file from wide stream", doc, result);
    transverse_base(doc);
}

int main() {
    //simple_test();
    //wide_char_test();
    narrow_char_test();
}

