//
// Created by sooda on 16/6/3.
//

//test the cppmary lib

#include <iostream>
#include <fstream>
#include "cppmary.h"

using namespace std;

int main() {
    std::string input;
    SpeechSynthesiser *ttsEngine = new SpeechSynthesiser("./");
    std::string testFile = "data/input.txt";
    std::ifstream ifs(testFile.c_str());
    getline(ifs, input);
    ifs.close();
    //input = "你好hello";
    std::cout << "input text: " << input << std::endl;
    std::string outfile = "2.wav";
    ttsEngine->process(input, outfile);
    delete ttsEngine;
    std::cout << "ok" << std::endl;

}