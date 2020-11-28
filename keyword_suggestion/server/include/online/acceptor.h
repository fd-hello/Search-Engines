#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_ACCEPTOR_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_ACCEPTOR_H_

#include <string>

#include "inet_address.h"
#include "socket.h"

const int kBacklog = 8;

namespace keyword_suggestion {

class Acceptor {
 public:
  Acceptor(int port, const std::string &ip = "0.0.0.0");

  void Init();
  int Accept();
  int GetFd() const;

 private:
  void SetReusePort(bool arg);
  void SetReuseAddr(bool arg);
  void Bind();
  void Listen();

  InetAddress addr_;
  Socket socket_;
};

}  // namespace keyword_suggestion

#endif
