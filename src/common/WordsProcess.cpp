//  Created by SongchengWu on 15/9/29.
//  Copyright © 2015年 huanshi. All rights reserved.
//

#include "common/WordsProcess.h"
#include "cppjieba/Jieba.hpp"
WordsProcess* WordsProcess::_instance=NULL;
WordsProcess* WordsProcess::Instance(){
    if( 0== _instance)
    {
        _instance = new WordsProcess();
    }
    return _instance;
}

void WordsProcess::LoadResource(std::string dir)
{
    if(_app!=NULL) {
        return;
    }

    cppjieba::Jieba* app=new cppjieba::Jieba(dir+"/jieba.dict.utf8",
                                   dir+"/hmm_model.utf8",
                                   dir+"/user.dict.utf8");
     _app=(cppjieba::Jieba*)app;
}

//void WordsProcess::LoadResource(std::string &jieba_buffer,
//                  std::string &hmm_model_buffer,
//                  std::string &user_buffer,
//                  std::string &idf_buffer,
//                  std::string &stop_buffer)
//{
//    if(_app!=NULL)
//    {
//        return;
//    }
//
//    cppjieba::Jieba* app=new cppjieba::Jieba (jieba_buffer,
//                                              hmm_model_buffer,
//                                              user_buffer,
//                                              idf_buffer,
//                                              stop_buffer,1);
//    _app=(cppjieba::Jieba*)app;
//}

void WordsProcess::Cut(const std::string &sentence, std::vector<std::string> &words)
{
    if(_app==NULL) {
        return;
    }
    cppjieba::Jieba* app=(cppjieba::Jieba*)_app;
    app->Cut(sentence, words);
}

void WordsProcess::Tag(const std::string& sentence, std::vector<std::pair<std::string, std::string> >& wordTags) {
    if(_app==NULL) {
        return;
    }
    cppjieba::Jieba* app=(cppjieba::Jieba*)_app;
    app->Tag(sentence, wordTags);
}

//void WordsProcess::Extract(const std::string &sentence, std::vector<std::string> &words,int topN)
//{
//    if(_app==NULL)
//    {
//        return;
//    }
//    cppjieba::Jieba* app=(cppjieba::Jieba*)_app;
//    app->extract(sentence, words, topN);
//}

void WordsProcess:: InsertNewWords(std::vector<std::string>& words)
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
