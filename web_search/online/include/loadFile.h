#ifndef _LOADFILE_H__
#define _LOADFILE_H__

#include "WebPage.h"
#include "../include/configuration.h"
#include <unordered_map>
#include <string>
using std::string;
using std::unordered_map;
using std::pair;

class loadFile
{
public:
    static loadFile* getInstance();//获取单例对象
    void loadPageLib(const string &page_path,const string &offset_path,Configuration  & conf);//加载网页库和偏移库
    void loadInvertIndexTable(const string &path);//加载倒排索引库

    unordered_map<int,WebPage> &getPageLib();
    unordered_map<int,std::pair<int,int>> &getOffSetLib();
    unordered_map<string,set<std::pair<int,double>>> &getInvertIndexTable();
private:
    class AutoRelease
    {
    public:
        AutoRelease(){}
        ~AutoRelease()
        {
            if(_loadFile)
            {
                delete _loadFile;
                _loadFile=nullptr;
            }
        }
    };
loadFile(){}
~loadFile(){}

private:
    static loadFile* _loadFile;
    unordered_map<int,WebPage> _pageLib;//网页库
    unordered_map<int,std::pair<int,int>> _offsetLib;//网页偏移库
    unordered_map<string,set<std::pair<int,double>>> _invertIndexTable;//倒排索引库

    static AutoRelease _auto;
};


#endif
