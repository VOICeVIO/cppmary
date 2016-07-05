//
//  jieba.h
//  jieba
//
//  Created by SongchengWu on 15/9/29.
//  Copyright © 2015年 huanshi. All rights reserved.
//
#ifndef WORDS_PROCESS_H
#define WORDS_PROCESS_H
#include "stdio.h"
#include <vector>
#include <string>
#include <utility>
class JiebaSegment{
public:
    static JiebaSegment* Instance();
    void LoadResource(std::string dir);
    void LoadResource(std::string &jieba_buffer,
                      std::string &hmm_model_buffer,
                      std::string &user_buffer);
    void Cut(const std::string& sentence, std::vector<std::string>& words);
    void Tag(const std::string& sentence, std::vector<std::pair<std::string, std::string> >& wordTags);
    void Extract(const std::string& sentence,std::vector<std::string>&words,int topN=1);
    void InsertNewWords(std::vector<std::string>& words);
protected:
    JiebaSegment(void)
    {
        _app=NULL;
    }
    virtual ~JiebaSegment(void)
    {
    }
    static JiebaSegment* _instance;
    void* _app;
};
#endif