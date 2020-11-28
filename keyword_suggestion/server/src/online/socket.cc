#include "../../include/online/socket.h"

namespace keyword_suggestion {

Socket::Socket() {
  fd_ = socket(PF_INET, SOCK_STREAM, 0);
  if (fd_ == -1) {
    perror("socket");
  }
}

Socket::Socket(int fd) : fd_(fd) {}

Socket::~Socket() { ::close(fd_); }

void Socket::ShutdownWrite() { ::shutdown(fd_, SHUT_WR); }

int Socket::fd() const { return fd_; }

}  // namespace keyword_suggestion
