#include "../include/connector.h"

namespace keyword_suggestion {

Connector::Connector(int port, const std::string &ip)
    : addr_(port, ip), socket_() {}

int Connector::Connect() {
  int ret = ::connect(socket_.fd(),
                      reinterpret_cast<struct sockaddr *>(addr_.addr_ptr()),
                      sizeof(addr_.addr()));

  if (ret == -1) {
    perror("connect");
  }
  return socket_.fd();
}

}  // namespace keyword_suggestion
