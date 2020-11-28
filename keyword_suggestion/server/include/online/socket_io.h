#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_SOCKET_IO_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_SOCKET_IO_H_

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "message.h"

namespace keyword_suggestion {

class SocketIo {
 public:
  explicit SocketIo(int fd);

  void ReadMessage(Message &msg);
  int WriteN(const Message *buffer, int n);

 private:
  int ReceivePeek(char *buffer, int n);

  int fd_;
};

}  // namespace keyword_suggestion

#endif
