//
// Created by sooda on 16/6/3.
//

//test the cppmary lib

#include <iostream>
#include "cppmary.h"

using namespace std;

int main() {
    std::string input;
    std::cout << "input text: " << std::endl;
    SpeechSynthesiser ttsEngine;
    while(cin >> input) {
        ttsEngine.process(input);
    }
}