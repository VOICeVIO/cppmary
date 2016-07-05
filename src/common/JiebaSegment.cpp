//  Created by SongchengWu on 15/9/29.
//  Copyright © 2015年 huanshi. All rights reserved.
//

#include "common/JiebaSegment.h"
#include "cppjieba/Jieba.hpp"
JiebaSegment* JiebaSegment::_instance=NULL;
JiebaSegment* JiebaSegment::Instance(){
    if( 0== _instance)
    {
        _instance = new JiebaSegment();
    }
    return _instance;
}

void JiebaSegment::LoadResource(std::string dir)
{
    if(_app!=NULL) {
        return;
    }

    cppjieba::Jieba* app=new cppjieba::Jieba(dir+"/jieba.dict.utf8",
                                   dir+"/hmm_model.utf8",
                                   dir+"/user.dict.utf8");
     _app=(cppjieba::Jieba*)app;
}

void JiebaSegment::LoadResource(std::string &jieba_buffer,
                              std::string &hmm_model_buffer,
                              std::string &user_buffer) {
    if (_app != NULL) {
        return;
    }
    cppjieba::Jieba* app=new cppjieba::Jieba(jieba_buffer,
                                              hmm_model_buffer,
                                              user_buffer,
                                              1);
    _app=(cppjieba::Jieba*)app;
}

void JiebaSegment::Cut(const std::string &sentence, std::vector<std::string> &words)
{
    if(_app==NULL) {
        return;
    }
    cppjieba::Jieba* app=(cppjieba::Jieba*)_app;
    app->Cut(sentence, words);
}

void JiebaSegment::Tag(const std::string& sentence, std::vector<std::pair<std::string, std::string> >& wordTags) {
    if(_app==NULL) {
        return;
    }
    cppjieba::Jieba* app=(cppjieba::Jieba*)_app;
    app->Tag(sentence, wordTags);
}

//void JiebaSegment::Extract(const std::string &sentence, std::vector<std::string> &words,int topN)
//{
//    if(_app==NULL)
//    {
//        return;
//    }
//    cppjieba::Jieba* app=(cppjieba::Jieba*)_app;
//    app->extract(sentence, words, topN);
//}

void JiebaSegment:: InsertNewWords(std::vector<std::string>& words)
{
    if(_app==NULL)
    {
        return;
    }
    cppjieba::Jieba* app=(cppjieba::Jieba*)_app;
    for(int i=0;i<words.size();i++)
    {
        app->InsertUserWord(words[i]);
    }
}
