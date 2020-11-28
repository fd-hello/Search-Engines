#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_DICT_CN_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_DICT_CN_H_

#include "../../include/online/configuration.h"
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>


using std::set;
using std::string;
using std::unordered_map;
using std::vector;

namespace keyword_suggestion {

class Dict {
public:
    static Dict *createInstance();

    void loadLibfile();

    void initDictCn(const string &dictCnPath);
    void initIndexTableCn(const string &indexTableCnPath);

    void initDictEn(const string &dictEnPath);
    void initIndexTableEn(const string & indexTableEnPath);

    const vector<std::pair<string, int>> &getDictCn() const {return _dictCn;}
    const unordered_map<string, set<int>> &getIndexTableCn() const {return _indexTableCn;}

    const vector<std::pair<string,int>> &getDictEn() const  {return _dictEn;}
    const unordered_map<string,set<int>> &getIndexTableEn() const  {return _indexTableEn;}

private:
    //释放类
    class AutoRelease {
    public:
        AutoRelease() {}

        ~AutoRelease() {
            /* std::cout<<"~AutoRelease()"<<std::endl; */
            if (_pInstance) {
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };

    Dict() {}

    ~Dict() {}

private:
    static Dict *_pInstance;
    
    vector<std::pair<string, int>> _dictCn;         //中文词典
    unordered_map<string, set<int>> _indexTableCn;  //中文索引表
    
    vector<std::pair<string,int>> _dictEn;  //英文词典
    unordered_map<string,set<int>> _indexTableEn;  //英文索引文件


    static AutoRelease _auto;
};

}  // end of namespace keyword_suggestion

#endif
