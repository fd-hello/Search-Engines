#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_OFFLINE_SPLIT_TOOL_CPPJIEBA_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_OFFLINE_SPLIT_TOOL_CPPJIEBA_H_


#include "../../lib/cppjieba-master/include/Jieba.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace keyword_suggestion {

class SplitToolCppJieba 
{
public:
  static vector<string> cut(const string &sentence);
private:
  static cppjieba::Jieba _jieba;
};

}  // end of namespace keyword_suggestion

#endif
