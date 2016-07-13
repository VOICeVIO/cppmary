//
// Created by sooda on 16/6/3.
//

#ifndef CPPMARY_CPPMARY_H
#define CPPMARY_CPPMARY_H

#include "common.h"
#include "modules.h"
#include "feature.h"
#include <memory>

void synthesisSpeech(std::string input);

class SpeechSynthesiser {
public:
    SpeechSynthesiser(const std::string& dir);
    ~SpeechSynthesiser();
    void init(const std::string& configPath);
    void process(std::string input, std::string outfile);
private:
    std::shared_ptr<cppmary::InterModules> phonemiser_;
    std::shared_ptr<cppmary::InterModules> prosody_;
    std::shared_ptr<cppmary::InterModules> pronuciation_;
    std::shared_ptr<cppmary::InterModules> label_;
    std::shared_ptr<cppmary::InterModules> htsengine_;
    std::shared_ptr<cppmary::InterModules> tokenizer_;
    std::shared_ptr<cppmary::FeatureProcessorManager> manager_;
    std::shared_ptr<cppmary::TargetFeatureComputer> featureComputer_;
};
#endif //CPPMARY_CPPMARY_H
