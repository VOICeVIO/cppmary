//
// Created by sooda on 16/6/3.
//

//test the cppmary lib

#include <iostream>
#include "cppmary.h"

using namespace std;

int main() {
    std::string input;
    SpeechSynthesiser *ttsEngine = new SpeechSynthesiser();
    input = "这个世界上，为什么只有我这么帅呢?";
    std::cout << "input text: " << std::endl;
    ttsEngine->process(input);
//    while(cin >> input) {
//        ttsEngine->process(input);
//    }
    delete ttsEngine;
    std::cout << "ok" << std::endl;

}