#include "../../include/offline/dict_producer_en.h"

namespace keyword_suggestion {

DictProducerEn::DictProducerEn(const std::string &path) {
  DIR *dir_ptr;
  struct dirent *dirent_ptr;

  dir_en_ = path;
  dir_ptr = opendir(dir_en_.c_str());
  if (dir_ptr == nullptr) {
    perror("opendir");
    exit(-1);
  }
  while ((dirent_ptr = readdir(dir_ptr)) != nullptr) {
    std::string file_path;

    if (!strcmp(dirent_ptr->d_name, ".") || !strcmp(dirent_ptr->d_name, "..")) {
      continue;
    } else {
      file_path = dir_en_ + '/' + static_cast<std::string>(dirent_ptr->d_name);
      files_en_.push_back(file_path);
    }
  }
  closedir(dir_ptr);
}

void DictProducerEn::BuildStopWordsLibEn(const std::string &path) {
  FILE *stop_words_lib = fopen(path.c_str(), "rb");
  char buffer[1024] = {0};

  while (fscanf(stop_words_lib, "%s", buffer) != EOF) {
    stop_words_en_[static_cast<std::string>(buffer)] = stop_words_en_.size();
  }
  fclose(stop_words_lib);
}

void DictProducerEn::BuildDictEn() {
  FILE *corpus;
  char buffer[1024] = {0};
  int count = 0;

  while (count < static_cast<int>(files_en_.size())) {
    corpus = fopen(files_en_[count++].c_str(), "rb");
    while (fscanf(corpus, "%s", buffer) != EOF) {
      for (int i = 0, offset = 0, len = static_cast<int>(strlen(buffer));
           i < len; ++i) {
        if ((IsValid(buffer[i]) && i != len - 1) ||
            (buffer[i] == '-' && i - offset && IsValid(buffer[i + 1]))) {
          if (IsUpperCase(buffer[i])) {
            buffer[i] += 'a' - 'A';
          }
        } else {
          if (!IsValid(buffer[i])) {
            buffer[i] = '\0';
          }
          if (IsUpperCase(buffer[i])) {
            buffer[i] += 'a' - 'A';
          }
          if (i - offset || IsValid(buffer[i])) {
            std::string word = buffer + offset;

            if (!IsStopWord(word)) {
              std::map<std::string, int>::iterator iter = dict_en_.find(word);

              if (iter != dict_en_.end()) {
                iter->second++;
              } else {
                dict_en_[word] = 1;
              }
            }
          }
          offset = i + 1;
        }
      }
    }
    fclose(corpus);
  }
}

void DictProducerEn::BuildIndexEn() {
  std::map<std::string, int>::iterator iter = dict_en_.begin();

  for (int idx = 0; iter != dict_en_.end(); ++iter, ++idx) {
    std::string word = iter->first;

    for (auto c : word) {
      if (IsLowerCase(c) || c == '-') {
        std::map<char, std::set<int>>::iterator index_iter = index_en_.find(c);

        if (index_iter == index_en_.end()) {
          std::set<int> tmp;

          tmp.insert(idx);
          index_en_[c] = tmp;
        } else {
          index_iter->second.insert(idx);
        }
      }
    }
  }
}

void DictProducerEn::StoreDictEn(const std::string &path) {
  FILE *dict = fopen(path.c_str(), "wb+");

  for (const auto &iter : dict_en_) {
    fprintf(dict, "%s %d\n", iter.first.c_str(), iter.second);
  }
  fclose(dict);
}

void DictProducerEn::StoreIndexEn(const std::string &path) {
  FILE *index = fopen(path.c_str(), "wb+");

  for (const auto &iter : index_en_) {
    fprintf(index, "%c", iter.first);
    for (const auto &set_iter : iter.second) {
      fprintf(index, " %d", set_iter);
    }
    fprintf(index, "\n");
  }
  fclose(index);
}

void DictProducerEn::ShowDictEn() const {
  for (const auto &iter : dict_en_) {
    printf("%s %d\n", iter.first.c_str(), iter.second);
  }
}

void DictProducerEn::ShowFilesEn() const {
  int count = 0;

  while (count < static_cast<int>(files_en_.size())) {
    printf("%s\n", files_en_[count++].c_str());
  }
}

bool DictProducerEn::IsUpperCase(char character) {
  return 'A' <= character && character <= 'Z';
}

bool DictProducerEn::IsLowerCase(char character) {
  return 'a' <= character && character <= 'z';
}

bool DictProducerEn::IsValid(char character) {
  return IsUpperCase(character) || IsLowerCase(character);
}

bool DictProducerEn::IsStopWord(const std::string &word) {
  return !(stop_words_en_.find(word) == stop_words_en_.end());
}

void DictProducerEn::PushDictEn(const std::string &word) {
  std::map<std::string, int>::iterator iter = dict_en_.find(word);

  if (iter != dict_en_.end()) {
    iter->second++;
  } else {
    printf("Not found\n");
  }
}

std::vector<std::string> DictProducerEn::files_en() { return files_en_; }

}  // namespace keyword_suggestion
