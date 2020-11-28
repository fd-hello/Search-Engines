#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_OFFLINE_DICT_PRODUCER_EN_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_OFFLINE_DICT_PRODUCER_EN_H_

#include <dirent.h>
#include <string.h>
#include <unistd.h>

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "configuration.h"

namespace keyword_suggestion {

class DictProducerEn {
  const int kPathSize = 1024;

 public:
  DictProducerEn(const std::string &path);

  void BuildStopWordsLibEn(const std::string &path);
  void BuildDictEn();
  void BuildIndexEn();
  void StoreDictEn(const std::string &path);
  void StoreIndexEn(const std::string &path);
  void ShowDictEn() const;
  void ShowFilesEn() const;
  bool IsUpperCase(char character);
  bool IsLowerCase(char character);
  bool IsValid(char character);
  bool IsStopWord(const std::string &word);

 private:
  void PushDictEn(const std::string &word);
  std::vector<std::string> files_en();

  std::string dir_en_;
  std::vector<std::string> files_en_;
  std::map<std::string, int> dict_en_;
  std::unordered_map<std::string, int> stop_words_en_;
  std::map<char, std::set<int>> index_en_;
};

}  // namespace keyword_suggestion

#endif
