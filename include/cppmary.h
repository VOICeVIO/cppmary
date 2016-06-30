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
    SpeechSynthesiser();
    ~SpeechSynthesiser();
    void init();
    void process(std::string input);
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
