#include "../../include/offline/dict_producer_zh.h"
#include "../../include/offline/split_tool_cppjieba.h"
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::ofstream;

namespace keyword_suggestion
{
//创建对象，并读取所有词源文件路径
DictProducer_zh::DictProducer_zh(const string &dir)
:_dir_zh(dir)
{
    DIR *pdir=opendir(_dir_zh.c_str());
    struct dirent *pdirent;
    while((pdirent=readdir(pdir)))
    {
        if(strcmp(pdirent->d_name,".")==0||strcmp(pdirent->d_name,"..")==0)
        {
            continue;
        }
        string abpath;
        abpath+=_dir_zh+"/"+pdirent->d_name;
        _files_zh.push_back(abpath);
    }
    closedir(pdir);
}
//初始化停用词集
void DictProducer_zh::createStopWords(const string &filepath)
{
    ifstream in(filepath);
    string word;
    while(getline(in,word))
    {
        _stopWords_zh[word]=1;
    }
}
//创建单词库：单词-词频
void DictProducer_zh::buildCnDict()
{
    //1.根据词源文件路径读取每篇文章
    for(auto &i:_files_zh)
    {
        ifstream in(i);
        string text;
        string line;
        vector<string> words;
        while(getline(in,line))
        {
            text+=line;
        }
        //2.对每一篇文章内容进行jieba分词
        words=SplitToolCppJieba::cut(text);
        for(auto &i:words)
        {
            if(_stopWords_zh.find(i)!=_stopWords_zh.end())
            {
                continue;
            }
            auto it=_dict_zh.begin();
            while(it!=_dict_zh.end())
            {
                if(it->first==i)
                {
                    it->second+=1;
                    break;
                }
                else
                {
                    ++it;
                }
            }
            if(it==_dict_zh.end())
            {
                _dict_zh.push_back(make_pair(i,1));
            }
        }
    }
}

//保存词典
void DictProducer_zh::storeDict(const string &filepath)
{
    ofstream out(filepath);
    for(auto &i:_dict_zh)
    {
        out<<i.first<<" "<<i.second<<endl;
    }
}
//调试:打印语料库文件目录
void DictProducer_zh::showFiles() const
{
    cout<<_dir_zh<<endl;
}
//调试：打印词典
void DictProducer_zh::showDict() const
{
    for(auto &i:_dict_zh)
    {
        cout<<i.first<<": "<<i.second<<endl;
    }
}

//创建中文索引，遍历字典中的每一个中文字节
void DictProducer_zh::buildCnIndex()
{
    for(size_t i=0;i<_dict_zh.size();++i)
    {
        for(size_t j=0;j<=_dict_zh[i].first.size();j+=3)
        {   
            string tmp;
            tmp=_dict_zh[i].first.substr(j,3);
            _index_zh[tmp].insert(i);
        }
    }
}

//保存索引文件路径
void DictProducer_zh::storeIndex(const string &filepath)
{
    ofstream out(filepath);

    for(auto &i:_index_zh)
    {
        out<<i.first<<" ";
        for(auto &j:i.second)
        {
            out<<j<<" ";
        }
        out<<endl;
    }
}

}//end of namespace keyword_suggestion
