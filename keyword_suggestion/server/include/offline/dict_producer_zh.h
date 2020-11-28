#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_OFFLINE_DICT_PRODUCER_ZH_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_OFFLINE_DICT_PRODUCER_ZH_H_

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using std::map;
using std::ostream;
using std::pair;
using std::set;
using std::string;
using std::unordered_map;
using std::vector;

namespace keyword_suggestion {


class DictProducer_zh {
  friend ostream &operator<<(ostream &out, set<int> s);

 public:
  DictProducer_zh(const string &dir);

  void buildEnDict();                       //创建英文字典
  void buildCnDict();                       //创建中文字典
  void storeDict(const string &filepath);   //将词典写入文件
  void showFiles() const;                   //查看文件路径，作测试用
  void showDict() const;                    //查看词典，作为测试用
  void getFiles();                          //获取文件的绝对路径
  void pushDict(const string &word);        //存储某个单词
  void buildCnIndex();                      //创建中文索引
  void storeIndex(const string &filepath);  //将索引写入文件
  void createStopWords(const string &filepath);  //创建停用词库
  /* bool IsInStr(const string &lhs,const string
   * &rhs);//判断一个中文字符是否在当前字符串内 */
 private:
  string _dir_zh;                      //语料库文件存放路径
  vector<string> _files_zh;            //语料库文件的绝对路径集合
  vector<pair<string, int>> _dict_zh;  //词典
  unordered_map<string, int> _stopWords_zh;   //停用词
  unordered_map<string, set<int>> _index_zh;  //保存索引
};

}  // end of namespace keyword_suggestion

#endif
