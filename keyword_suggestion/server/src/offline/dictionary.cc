#include "../../include/offline/configuration.h"
#include "../../include/offline/dict_producer_en.h"
#include "../../include/offline/dict_producer_zh.h"
#include "../../include/offline/split_tool_cppjieba.h"

void Run();

int main() {
  Run();
  return 0;
}

void Run() {
  keyword_suggestion::Configuration path("path");
  keyword_suggestion::DictProducerEn dict_en(path.GetPath("corpus_en"));


  keyword_suggestion::DictProducer_zh dict_zh(path.GetPath("corpus_zh"));

  dict_zh.createStopWords(path.GetPath("stop_words_zh"));
  dict_zh.buildCnDict();
  dict_zh.buildCnIndex();
  dict_zh.storeDict(path.GetPath("dict_zh"));
  dict_zh.storeIndex(path.GetPath("index_zh"));

  dict_en.BuildStopWordsLibEn(path.GetPath("stop_words_en"));
  dict_en.BuildDictEn();
  dict_en.BuildIndexEn();
  dict_en.StoreDictEn(path.GetPath("dict_en"));
  dict_en.StoreIndexEn(path.GetPath("index_en"));
}
