#include "../include/configuration.h"

namespace keyword_suggestion {

Configuration::Configuration(const std::string &config) {
  FILE *path;
  char prefix[kPathSize] = {0}, index[1024] = {0}, content[1024] = {0};
  std::string config_path;

  getcwd(prefix, kPathSize);
  for (int i = strlen(prefix) - 1; prefix[i] != '/'; --i) {
    prefix[i] = '\0';
  }
  prefix[strlen(prefix) - 1] = '\0';
  path_prefix_ = static_cast<std::string>(prefix);
  config_path = path_prefix_ + "/conf/" + config + ".conf";

  path = fopen(config_path.c_str(), "rb");
  while (fscanf(path, "%s%s", index, content) != EOF) {
    config_[static_cast<std::string>(index)] = content;
  }
  fclose(path);
}

std::string Configuration::GetPath(const std::string &config) {
  return path_prefix_ + config_.find(config)->second;
}

std::string Configuration::GetIp(std::string config) {
  char buffer[kPathSize] = {0};

  ::strcpy(buffer, config.c_str());
  if (::strcmp(buffer, "deafult_ip")) {
    struct passwd *pwd = getpwuid(getuid());

    config = static_cast<std::string>(pwd->pw_name) + "_ip";
  }
  return config_.find(config)->second;
}

int Configuration::GetPort(std::string config) {
  char buffer[kPathSize] = {0};

  ::strcpy(buffer, config.c_str());
  if (::strcmp(buffer, "deafult_port")) {
    struct passwd *pwd = getpwuid(getuid());

    config = static_cast<std::string>(pwd->pw_name) + "_port";
  }
  return atoi(config_.find(config)->second.c_str());
}

}  // namespace keyword_suggestion
