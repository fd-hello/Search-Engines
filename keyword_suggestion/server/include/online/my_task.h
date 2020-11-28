#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_MY_TAKS_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_MY_TAKS_H_

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "dict.h"
#include "tcp.h"

using std::priority_queue;
using std::set;
using std::string;
using std::vector;

namespace keyword_suggestion {

struct MyResult {
  friend struct MyCompare;
  string _word;
  int _iFreq;
  int _iDist;
  MyResult(const string &word, int freq, int dist)
      : _word(word), _iFreq(freq), _iDist(dist) {}
};

struct MyCompare {
  bool operator()(const MyResult &lhs, const MyResult &rhs) {
    if (lhs._iDist != rhs._iDist) {
      return lhs._iDist > rhs._iDist;
    } else {
      if (lhs._iFreq != rhs._iFreq) {
        return lhs._iFreq > rhs._iFreq;
      } else {
        return lhs._word > rhs._word;
      }
    }
  }
};

class MyTask {
 public:
  MyTask(Message &msg, const TcpPtr &pConn);

  void execute();  //执行查询

 private:
  void statistic_cn(set<int> &iset);//进行计算
  void statistic_en(set<int> &iset);
  int distance(const string &rhs);  //最小编辑距离
  /* void response();  //响应客户端请求 */
  size_t nBytesCode(const char ch);
  size_t length(const string &str);
  void parseWord(vector<string> &chars);

  string packJson();
  void packMessage(string result);

 private:
  Message _msg;
  std::string _queryWord;
  keyword_suggestion::TcpPtr _pConn;
  priority_queue<MyResult, vector<MyResult>, MyCompare> _resultQue;
};
}  // end of namespace keyword_suggestion

#endif
