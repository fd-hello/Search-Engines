#ifndef KEYWORD_SUGGESTION_CLIENT_INCLUDE_SOCKET_IO_H_
#define KEYWORD_SUGGESTION_CLIENT_INCLUDE_SOCKET_IO_H_

#include <errno.h>
#include <json/json.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "message.h"

namespace keyword_suggestion {

class SocketIo {
 public:
  explicit SocketIo(int fd);

  void ReadJson(Message &msg);
  void UnpackJson(const std::string &json_str);
  int WriteN(const Message *msg, int n);

 private:
  int ReceivePeek(char *buffer, int n);

  int fd_;
};

}  // namespace keyword_suggestion

#endif
