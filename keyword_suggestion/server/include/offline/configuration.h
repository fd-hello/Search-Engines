#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_OFFLINE_CONFIGURATION_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_OFFLINE_CONFIGURATION_H_

#include <pwd.h>
#include <string.h>
#include <unistd.h>

#include <string>
#include <unordered_map>

namespace keyword_suggestion {

class Configuration {
  const int kPathSize = 1024;

 public:
  Configuration(const std::string &config);

  std::string GetPath(const std::string &config);
  std::string GetIp(std::string config);
  int GetPort(std::string config);

 private:
  std::string path_prefix_;
  std::unordered_map<std::string, std::string> config_;
};

}  // namespace keyword_suggestion

#endif
