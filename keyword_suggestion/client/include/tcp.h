#ifndef KEYWORD_SUGGESTION_CLIENT_INCLUDE_TCP_H_
#define KEYWORD_SUGGESTION_CLIENT_INCLUDE_TCP_H_

#include <cstdio>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "inet_address.h"
#include "message.h"
#include "noncopyable.h"
#include "socket.h"
#include "socket_io.h"

const size_t kMaxSize = 65536;

namespace keyword_suggestion {

class Tcp : Noncopyable {
 public:
  Tcp(int);
  ~Tcp();

  void ConvertToString() const;
  void RunInLoop();
  bool Send();
  void Receive();
  bool IsValid(char *word);
  bool IsLetter(char ch);
  void Shutdown();

 private:
  InetAddress GetSockAddr(int fd);
  InetAddress GetPeerAddr(int fd);

  Socket socket_;
  SocketIo socket_io_;
  InetAddress sock_addr_;
  InetAddress peer_addr_;
  bool is_shutdown_;
};

}  // namespace keyword_suggestion

#endif
