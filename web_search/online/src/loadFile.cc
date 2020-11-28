#include "../include/loadFile.h"
#include <vector>
using std::vector;

loadFile *loadFile::_loadFile=loadFile::getInstance();
loadFile::AutoRelease loadFile::_auto;

loadFile *loadFile::getInstance()
{
    if(!_loadFile)
    {
        _loadFile=new loadFile();
    }
    return _loadFile;
}

void loadFile::loadPageLib(const string &page_path,const string &offset_path,Configuration & conf)
{
    vector<string> vecfiles;

    ifstream in_page(page_path,std::ios::binary | std::ios::ate);
    if(!in_page.good())
    {
        cout<<"the ifstream "<<page_path<< "open failed "<<endl;
        return; 
    }

    ifstream in_offset(offset_path);
    if(!in_offset.good())
    {
        cout<<"the ifstream "<<offset_path<<" open failed "<<endl;
        return;
    }
//读取偏移库，根据偏移库获取网页库
    int id=0;
    int start=0;
    int len=0;
    string line;//获取偏移库的每一行
    while(getline(in_offset,line))
    {
        istringstream iss(line);
        iss>>id;
        iss>>start;
        iss>>len;
        string text(len,0);  //每一篇文章的内容
        _offsetLib[id]=std::make_pair(start,len);
        in_page.seekg(start,std::ios::beg);
        in_page.read(&text[0],len);
        /* cout<<text<<endl; */
        vecfiles.push_back(text);
    }

    for(size_t i=0;i!=vecfiles.size();++i)
    {
        WebPage w;
        w.processDoc(vecfiles[i]);
        w.createDictMap(conf);
        _pageLib[w.getDocId()]=w;
    }
}

void loadFile::loadInvertIndexTable(const string &invertIndex_path)
{
    ifstream ifs(invertIndex_path);
    if(!ifs.good())
    {
        cout<<"the ifstream "<<invertIndex_path<<" oen failed "<<endl;
        return;
    }
//读取倒排索引表
    string line;
    while(getline(ifs,line))
    {
        int docId;
        double weight;
        string word;

        istringstream iss(line);
        iss>>word;
        while(iss>>docId && iss>>weight)
        {
            _invertIndexTable[word].insert(std::make_pair(docId,weight));
        }
    }
}
//获取到内存中的网页库以及倒排索引表
unordered_map<int,WebPage>& loadFile::getPageLib()
{
    return _pageLib;
}
unordered_map<int,std::pair<int,int>> &loadFile::getOffSetLib()
{
    return _offsetLib;
}
unordered_map<string,set<std::pair<int,double>>> & loadFile::getInvertIndexTable()
{
    return _invertIndexTable;
}
