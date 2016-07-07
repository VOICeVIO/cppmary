//
// Created by sooda on 16/6/28.
//

#include "modules/HtsEngine.h"
#include "common.h"
#include "limonp/StringUtil.hpp"

namespace cppmary {
    HtsEngine::HtsEngine(const std::string& modelStr) {
        name_ = "HtsEngine";
        HTS_Engine_initialize(&engine_);
        size_t num_voices = 1;
        fn_voices_ = (char**)malloc(num_voices * sizeof(char*));
        char *fileContent = new char[modelStr.size()+1];
        memset(fileContent, 0, modelStr.size()+1);
        memcpy(fileContent, modelStr.c_str(), modelStr.size());
        int *sizes = new int[num_voices];
        sizes[0] = modelStr.size();
        fn_voices_[0] = fileContent;
        if (HTS_Engine_load_size(&engine_, fn_voices_, num_voices, sizes) != TRUE) {
            fprintf(stderr, "Error: HTS voices cannot be loaded.\n");
            free(fn_voices_);
            HTS_Engine_clear(&engine_);
            exit(1);
        }
        delete [] fileContent;
    }

    HtsEngine::HtsEngine(const std::string& modelStr, const std::string& filterStr) {
        name_ = "HtsEngine";
        HTS_Engine_initialize(&engine_);
        size_t num_voices = 1;
        fn_voices_ = (char**)malloc(num_voices * sizeof(char*));
        char *fileContent = new char[modelStr.size()+1];
        memset(fileContent, 0, modelStr.size()+1);
        memcpy(fileContent, modelStr.c_str(), modelStr.size());
        int *sizes = new int[num_voices];
        sizes[0] = modelStr.size();
        fn_voices_[0] = fileContent;
        int numM = 5;
        int orderM = 199;
        double* filter_data = new double[numM*orderM];
        std::vector<std::string> bufferVec = limonp::Split(filterStr,"\n");
        assert(bufferVec.size() == numM*orderM);
        for (int i = 0; i < numM*orderM; i++) {
            double d = std::stod(bufferVec[i]);
            filter_data[i] = d;
        }
        if (HTS_Engine_load_size_mix(&engine_, fn_voices_, num_voices, sizes, numM, orderM, filter_data) != TRUE) {
            fprintf(stderr, "Error: HTS voices cannot be loaded.\n");
            free(fn_voices_);
            HTS_Engine_clear(&engine_);
            exit(1);
        }

        delete [] filter_data;
        delete [] fileContent;
    }

    HtsEngine::~HtsEngine() {
        HTS_Engine_refresh(&engine_);
        //HTS_Engine_clear(&engine_);
        HTS_Engine_destory(&engine_);
        free(fn_voices_);
    }

    void HtsEngine::setOutFile(const std::string& outfile) {
        outfile_ = outfile;
    }

    /*synthses data with label string*/
    std::string HtsEngine::process(std::string labelString) {
        clock_t start = clock();
        std::vector<std::string> buffervec = limonp::Split(labelString,"\n");
        int lineNum = buffervec.size();

        char** lines = (char**)malloc((lineNum+1) * sizeof(char*));
        memset(lines, 0, (lineNum+1) * sizeof(char*));

        for (int i = 0; i < lineNum; i++) {
            char * lineBuf = new char[buffervec[i].size()+1];
            memset(lineBuf, 0, buffervec[i].size()+1);
            memcpy(lineBuf, buffervec[i].c_str(), buffervec[i].size());
            lines[i] = lineBuf;
        }

        if (HTS_Engine_synthesize_from_strings(&engine_, lines, lineNum) != TRUE) {
            fprintf(stderr, "Error: waveform cannot be synthesized.\n");
            HTS_Engine_clear(&engine_);
            exit(1);
        }
        std::cout << "synthesis time: " << (clock()-start) * 1000.0 / CLOCKS_PER_SEC << std::endl;
        if (outfile_.empty()) {
            outfile_ = "1.wav";
        }
        if (!outfile_.empty()) {
            FILE* wavfp = fopen(outfile_.c_str(), "wb");
            if (wavfp)
                HTS_Engine_save_riff(&engine_, wavfp);
            fclose(wavfp);
        }
        for (int i = 0; i < lineNum; i++) {
            delete [] lines[i];
        }
        free(lines);
        return labelString;
    }

    void HtsEngine::synthesisWithLableName(std::string labelFile) {
        if (HTS_Engine_synthesize_from_fn(&engine_, labelFile.c_str()) != TRUE) {
            fprintf(stderr, "Error: waveform cannot be synthesized.\n");
            HTS_Engine_clear(&engine_);
            exit(1);
        }
        FILE* wavfp = fopen("1.wav", "wb");
        if (wavfp)
            HTS_Engine_save_riff(&engine_, wavfp);
        fclose(wavfp);
    }
}
