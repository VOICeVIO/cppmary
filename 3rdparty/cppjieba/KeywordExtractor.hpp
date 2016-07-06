#ifndef CPPJIEBA_KEYWORD_EXTRACTOR_H
#define CPPJIEBA_KEYWORD_EXTRACTOR_H

#include <cmath>
#include <set>
#include "Jieba.hpp"

namespace cppjieba {
using namespace limonp;

/*utf8*/
class KeywordExtractor {
 public:
  struct Word {
    string word;
    vector<size_t> offsets;
    double weight;
  }; // struct Word

  KeywordExtractor(const string& dictPath, 
        const string& hmmFilePath, 
        const string& idfPath, 
        const string& stopWordPath, 
        const string& userDict = "",
        bool bufferflag = false)
    : segment_(dictPath, userDict) {
    LoadIdfDict(idfPath, bufferflag);
    LoadStopWordDict(stopWordPath, bufferflag);
  }
  KeywordExtractor(const DictTrie* dictTrie, 
        const HMMModel* model,
        const string& idfPath, 
        const string& stopWordPath,
        bool bufferflag = false)
    : segment_(dictTrie) {
    LoadIdfDict(idfPath, bufferflag);
    LoadStopWordDict(stopWordPath, bufferflag);
  }
    
  ~KeywordExtractor() {
  }

  void Extract(const string& sentence, vector<string>& keywords, size_t topN) const {
    vector<Word> topWords;
    Extract(sentence, topWords, topN);
    for (size_t i = 0; i < topWords.size(); i++) {
      keywords.push_back(topWords[i].word);
    }
  }

  void Extract(const string& sentence, vector<pair<string, double> >& keywords, size_t topN) const {
    vector<Word> topWords;
    Extract(sentence, topWords, topN);
    for (size_t i = 0; i < topWords.size(); i++) {
      keywords.push_back(pair<string, double>(topWords[i].word, topWords[i].weight));
    }
  }

  void Extract(const string& sentence, vector<Word>& keywords, size_t topN) const {
    vector<string> words;
    segment_.Cut(sentence, words);

    map<string, Word> wordmap;
    size_t offset = 0;
    for (size_t i = 0; i < words.size(); ++i) {
      size_t t = offset;
      offset += words[i].size();
      if (IsSingleWord(words[i]) || stopWords_.find(words[i]) != stopWords_.end()) {
        continue;
      }
      wordmap[words[i]].offsets.push_back(t);
      wordmap[words[i]].weight += 1.0;
    }
    if (offset != sentence.size()) {
      XLOG(ERROR) << "words illegal";
      return;
    }

    keywords.clear();
    keywords.reserve(wordmap.size());
    for (map<string, Word>::iterator itr = wordmap.begin(); itr != wordmap.end(); ++itr) {
      unordered_map<string, double>::const_iterator cit = idfMap_.find(itr->first);
      if (cit != idfMap_.end()) {
        itr->second.weight *= cit->second;
      } else {
        itr->second.weight *= idfAverage_;
      }
      itr->second.word = itr->first;
      keywords.push_back(itr->second);
    }
    topN = min(topN, keywords.size());
    partial_sort(keywords.begin(), keywords.begin() + topN, keywords.end(), Compare);
    keywords.resize(topN);
  }
 private:
  void LoadIdfDict(const string& idfPath, bool bufferflag) {
      if(bufferflag)
      {
          string line ;
          vector<string> buf;
          double idf = 0.0;
          double idfSum = 0.0;
          size_t lineno = 0;
          char *filebuffer= new char[idfPath.size()+1];
          strcpy(filebuffer, idfPath.c_str());
          
          for (char *tok = strtok(filebuffer, "\n"); tok != NULL; tok = strtok(NULL, "\n"),lineno++)
          {
              line=std::string(tok);
              if (line.empty()) {
                  XLOG(ERROR) << "lineno: " << lineno << " empty. skipped.";
                  continue;
              }
              Split(line, buf, " ");
              if (buf.size() != 2) {
                  XLOG(ERROR) << "line: " << line << ", lineno: " << lineno << " empty. skipped.";
                  continue;
              }
              idf = atof(buf[1].c_str());
              idfMap_[buf[0]] = idf;
              idfSum += idf;
          }
          assert(lineno);
          idfAverage_ = idfSum / lineno;
          assert(idfAverage_ > 0.0);
          delete [] filebuffer;
      }
      else
      {
          ifstream ifs(idfPath.c_str());
          XCHECK(ifs.is_open()) << "open " << idfPath << " failed";
          string line ;
          vector<string> buf;
          double idf = 0.0;
          double idfSum = 0.0;
          size_t lineno = 0;
          for (; getline(ifs, line); lineno++) {
              buf.clear();
              if (line.empty()) {
                  XLOG(ERROR) << "lineno: " << lineno << " empty. skipped.";
                  continue;
              }
              Split(line, buf, " ");
              if (buf.size() != 2) {
                  XLOG(ERROR) << "line: " << line << ", lineno: " << lineno << " empty. skipped.";
                  continue;
              }
              idf = atof(buf[1].c_str());
              idfMap_[buf[0]] = idf;
              idfSum += idf;
          }
          
          assert(lineno);
          idfAverage_ = idfSum / lineno;
          assert(idfAverage_ > 0.0);
      }
  }
  void LoadStopWordDict(const string& filePath, bool bufferflag) {
      if(bufferflag)
      {
          string line ;
          char *filebuffer= new char[filePath.size()+1];
          strcpy(filebuffer, filePath.c_str());
          
          for (char *tok = strtok(filebuffer, "\n"); tok != NULL; tok = strtok(NULL, "\n"))
          {
              line=std::string(tok);
              stopWords_.insert(line);
          }
          assert(stopWords_.size());
          delete []filebuffer;
      }
      else
      {
          ifstream ifs(filePath.c_str());
          XCHECK(ifs.is_open()) << "open " << filePath << " failed";
          string line ;
          while (getline(ifs, line)) {
              stopWords_.insert(line);
          }
          assert(stopWords_.size());
      }

  }

  static bool Compare(const Word& lhs, const Word& rhs) {
    return lhs.weight > rhs.weight;
  }

  //MixSegment segment_;
  MPSegment segment_;
  unordered_map<string, double> idfMap_;
  double idfAverage_;

  unordered_set<string> stopWords_;
}; // class KeywordExtractor

inline ostream& operator << (ostream& os, const KeywordExtractor::Word& word) {
  return os << "{\"word\": \"" << word.word << "\", \"offset\": " << word.offsets << ", \"weight\": " << word.weight << "}"; 
}

} // namespace cppjieba

#endif


