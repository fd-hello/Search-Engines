#include "../../include/offline/split_tool_cppjieba.h"

const char* const DICT_PATH = "../lib/cppjieba-master/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../lib/cppjieba-master/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../lib/cppjieba-master/dict/user.dict.utf8";
const char* const IDF_PATH = "../lib/cppjieba-master/dict/idf.utf8";
const char* const STOP_WORD_PATH = "../lib/cppjieba-master/dict/stop_words.utf8";
using namespace cppjieba;
namespace keyword_suggestion
{

Jieba SplitToolCppJieba::_jieba(DICT_PATH, HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH);

vector<string> SplitToolCppJieba::cut(const string &sentence)
{
    vector<string> words;
    string s;
    s=sentence;
    vector<KeywordExtractor::Word> keywordres;
    int topk=10000;
    _jieba.extractor.Extract(s,keywordres,topk);
    
    for(size_t i=0;i<keywordres.size();++i)
    {
        words.push_back(keywordres[i].word);
    }
    //提取关键词之后将数字与字母从字典中去除
    for(auto i=words.begin();i!=words.end();)
    {
        if(isalnum((*i)[0]))
        {
            i=words.erase(i);
        }
        else
        {
            ++i;
        }
    }
    return words;
}
}//end of namespace keyword_suggestion
