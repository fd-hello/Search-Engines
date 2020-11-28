#ifndef KEYWORD_SUGGESTION_CLIENT_INCLUDE_INETADDRESS_H_
#define KEYWORD_SUGGESTION_CLIENT_INCLUDE_INETADDRESS_H_

#include <arpa/inet.h>
#include <string.h>

#include <string>

namespace keyword_suggestion {

class InetAddress {
 public:
  explicit InetAddress(const struct sockaddr_in &addr);
  InetAddress(int port, const std::string &ip = "0.0.0.0");

  int GetPort() const;
  std::string GetIp() const;

  struct sockaddr_in addr();
  struct sockaddr_in *addr_ptr();

 private:
  struct sockaddr_in addr_;
};

}  // namespace keyword_suggestion

#endif
