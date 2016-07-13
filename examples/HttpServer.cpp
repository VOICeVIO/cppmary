//
// Created by sooda on 16/7/13.
//

#include <unistd.h>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <string.h>
#include "limonp/Config.hpp"
#include "limonp/thread_pool_server.h"
#include "cppjieba/Jieba.hpp"
#include "cppmary.h"

using namespace cppjieba;

class ReqHandler: public IRequestHandler {
public:
    ReqHandler(const SpeechSynthesiser& engine) : ttsEngine_(engine){
    }

    virtual ~ReqHandler() {
    }

    virtual bool DoGET(const HttpReqInfo& httpReq, string& strSnd) {
        string sentence, method, format;
        string tmp;
        vector<string> words;
        httpReq.GET("key", tmp);
        URLDecode(tmp, sentence);
        httpReq.GET("method", method);
        httpReq.GET("format", format);
        process(sentence, method, format, strSnd);
        return true;
    }

    virtual bool DoPOST(const HttpReqInfo& httpReq, string& strSnd) {
        vector<string> words;
        process(httpReq.GetBody(), "MIX", "simple", strSnd);
        return true;
    }

    void process(const string& sentence,
             const string& method,
             const string& format,
             string& strSnd) const {
        strSnd = ttsEngine_.getAllophone(sentence);
    }
private:
    SpeechSynthesiser ttsEngine_;
};

bool Run(int argc, char** argv) {
    if (argc < 2) {
        return false;
    }
    Config conf(argv[1]);
    if (!conf) {
        return false;
    }
    int port = conf.Get("port", 1339);
    int threadNumber = conf.Get("thread_number", 4);

    XLOG(INFO) << "config info: " << conf.GetConfigInfo();

    SpeechSynthesiser engine(SpeechSynthesiser("data/labixx.conf"));

    ReqHandler reqHandler(engine);
    ThreadPoolServer server(threadNumber, port, reqHandler);
    return server.Start();
}

int main(int argc, char* argv[]) {
    if (!Run(argc, argv)) {
        printf("usage: %s <config_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
