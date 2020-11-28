#include "../../include/online/dict.h"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

namespace keyword_suggestion {
Dict* Dict::_pInstance = Dict::createInstance();

Dict::AutoRelease Dict::_auto;

Dict* Dict::createInstance() {
  if (_pInstance == nullptr) {
    _pInstance = new Dict();
  }
  return _pInstance;
}

void Dict::loadLibfile()
{
   Configuration path("path");
   initDictCn(path.GetPath("dict_zh"));
   initIndexTableCn(path.GetPath("index_zh"));

   initDictEn(path.GetPath("dict_en"));
   initIndexTableEn(path.GetPath("index_en"));
}

//将中文词库文件读到内存
void Dict::initDictCn(const string& dictCnPath) {
  ifstream ifs(dictCnPath);
  if (!ifs.good()) {
    std::cout << "the ifstream " << dictCnPath << " opened error" << std::endl;
    return;
  }
  string line;
  while (getline(ifs, line)) {
    istringstream iss(line);
    string word;
    int freq;
    iss >> word;
    iss >> freq;
    _dictCn.push_back(std::make_pair(word, freq));
  }
  ifs.close();
}

//将中文索引文件读取到内存
void Dict::initIndexTableCn(const string& indexTableCnPath) {
  ifstream ifs(indexTableCnPath);
  if (!ifs.good()) {
    std::cout << "the ifstream " << indexTableCnPath << " opened error"<< std::endl;
    return;
  }
  string line;
  while (getline(ifs, line)) {
    istringstream iss(line);
    string word;
    int index;
    iss >> word;
    while (iss >> index) {
      _indexTableCn[word].insert(index);
    }
  }
  ifs.close();
}

void Dict:: initDictEn(const string & dictEnPath)
{
    
    string line;
    ifstream ifs(dictEnPath);
    if(!ifs.good())
    {
        std::cout<<"the ifstream "<< dictEnPath <<" opened error"<<std::endl;
        return;
    }
    while(getline(ifs,line)){
        istringstream is(line);
        string word;
        int frequency;
        while(is>> word >> frequency){
            _dictEn.push_back({word,frequency});
        }
    }
    ifs.close();
}

void Dict::initIndexTableEn(const string &indexTableEnPath)
{
    
    string line;
    ifstream ifs(indexTableEnPath);
    if(!ifs.good())
    {
        std::cout<<"the ifstream "<< indexTableEnPath <<" opened error"<<std::endl;
        return;
    }
    while(getline(ifs,line)){
        istringstream is(line);
        string c;
        int ID;
        set<int> IDs;
        
        is >> c;
        while(is >> ID){
            IDs.insert(ID);
        }
        _indexTableEn.insert({c,IDs});
    }
    ifs.close();
}

}  // end of namespace keyword_suggestion
