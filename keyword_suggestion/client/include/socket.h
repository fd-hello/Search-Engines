#ifndef KEYWORD_SUGGESTION_CLIENT_INCLUDE_SOCKET_H_
#define KEYWORD_SUGGESTION_CLIENT_INCLUDE_SOCKET_H_

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

namespace keyword_suggestion {

class Socket {
 public:
  Socket();
  explicit Socket(int fd);
  ~Socket();

  void ShutdownWrite();

  int fd();

 private:
  int fd_;
};

}  // namespace keyword_suggestion

#endif
