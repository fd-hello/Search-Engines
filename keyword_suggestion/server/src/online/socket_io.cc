#include "../../include/online/socket_io.h"

namespace keyword_suggestion {

SocketIo::SocketIo(int fd) : fd_(fd) {}

void SocketIo::ReadMessage(Message &msg) {
  char buffer[sizeof(msg)];

  ReceivePeek(buffer, sizeof(msg));
  memset(&msg, 0, sizeof(msg));
  recv(fd_, &msg.len, sizeof(int), MSG_WAITALL);
  recv(fd_, &msg.id, sizeof(int), MSG_WAITALL);
  recv(fd_, &msg.content, msg.len, 0);
}

int SocketIo::WriteN(const Message *buffer, int n) {
  int ret, offset = n;
  const Message *ptr = buffer;

  while (offset > 0) {
    ret = ::write(fd_, ptr, offset);
    if (ret == -1) {
      if (errno == EINTR) {
        continue;
      }
      perror("write");
      return n - offset;
    } else {
      offset -= ret;
      ptr += ret;
    }
  }
  return n - offset;
}

int SocketIo::ReceivePeek(char *buffer, int n) {
  int ret;

  do {
    ret = ::recv(fd_, buffer, n, MSG_PEEK);
  } while (ret == -1 && errno == EINTR);
  return ret;
}

}  // namespace keyword_suggestion
