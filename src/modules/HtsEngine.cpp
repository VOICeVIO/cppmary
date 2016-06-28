//
// Created by sooda on 16/6/28.
//

#include "modules/HtsEngine.h"

namespace cppmary {
    HtsEngine::HtsEngine(const std::string& modelName) {
        HTS_Engine_initialize(&engine_);
        size_t num_voices = 1;
        char **fn_voices = (char**)malloc(num_voices * sizeof(char*));
        char fileName[1024];
        memset(fileName, 0, sizeof(fileName));
        memcpy(fileName, modelName.c_str(), modelName.size());
        std::cout << fileName << std::endl;
        fn_voices[0] = fileName;
        if (HTS_Engine_load(&engine_, fn_voices, num_voices) != TRUE) {
            fprintf(stderr, "Error: HTS voices cannot be loaded.\n");
            free(fn_voices);
            HTS_Engine_clear(&engine_);
            exit(1);
        }
        free(fn_voices);
    }

    HtsEngine::~HtsEngine() {
        HTS_Engine_refresh(&engine_);
        HTS_Engine_clear(&engine_);
    }

    /*synthses data with label string*/
    std::string HtsEngine::process(std::string labelString) {
        size_t lineno;
        char *filebuffer= new char[labelString.size()+1];
        strcpy(filebuffer, labelString.c_str());

        std::vector<char*> bufPos;

        for (char *tok = strtok(filebuffer, "\n"); tok != NULL; tok = strtok(NULL, "\n"),lineno++) {
            bufPos.push_back(tok);
        }

        char** lines = (char**)malloc((lineno+1) * sizeof(char*));
        memset(lines, 0, (lineno+1) * sizeof(char*));
        for (int i = 0; i < lineno; i++) {
            lines[i] = bufPos[i];
            //std::cout << i << " ++++++++++ " << lines[i] << std::endl;
        }
        if (HTS_Engine_synthesize_from_strings(&engine_, lines, lineno) != TRUE) {
            fprintf(stderr, "Error: waveform cannot be synthesized.\n");
            HTS_Engine_clear(&engine_);
            exit(1);
        }
        FILE* wavfp = fopen("1.wav", "wb");
        if (wavfp)
            HTS_Engine_save_riff(&engine_, wavfp);
        fclose(wavfp);
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
