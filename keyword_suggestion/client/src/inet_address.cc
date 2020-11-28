#include "../include/inet_address.h"

namespace keyword_suggestion {

InetAddress::InetAddress(const struct sockaddr_in &addr) : addr_(addr) {}

InetAddress::InetAddress(int port, const std::string &ip) {
  ::memset(&addr_, 0, sizeof(addr_));
  addr_.sin_family = AF_INET;
  addr_.sin_port = htons(port);
  addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}

int InetAddress::GetPort() const { return ntohs(addr_.sin_port); }

std::string InetAddress::GetIp() const {
  return static_cast<std::string>(::inet_ntoa(addr_.sin_addr));
}

struct sockaddr_in InetAddress::addr() {
  return addr_;
}

struct sockaddr_in *InetAddress::addr_ptr() {
  return &addr_;
}

}  // namespace keyword_suggestion
