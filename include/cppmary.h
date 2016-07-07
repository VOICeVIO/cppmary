//
// Created by sooda on 16/6/3.
//

#ifndef CPPMARY_CPPMARY_H
#define CPPMARY_CPPMARY_H

#include "common.h"
#include "modules.h"
#include "feature.h"

void synthesisSpeech(std::string input);

class SpeechSynthesiser {
public:
    SpeechSynthesiser(std::string dir);
    ~SpeechSynthesiser();
    void init(std::string dir);
    void process(std::string input, std::string outfile);
private:
    cppmary::InterModules* phonemiser_;
    cppmary::InterModules* prosody_;
    cppmary::InterModules* pronuciation_;
    cppmary::InterModules* label_;
    cppmary::InterModules* htsengine_;
    cppmary::InterModules* tokenizer_;
    cppmary::FeatureProcessorManager *manager_;
    cppmary::TargetFeatureComputer *featureComputer_;
};
#endif //CPPMARY_CPPMARY_H
