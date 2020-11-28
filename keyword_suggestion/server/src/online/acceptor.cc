#include "../../include/online/acceptor.h"

namespace keyword_suggestion {

Acceptor::Acceptor(int port, const std::string &ip)
    : addr_(port, ip), socket_() {}

void Acceptor::Init() {
  SetReusePort(true);
  SetReuseAddr(true);
  Bind();
  Listen();
}

int Acceptor::Accept() {
  int peer = ::accept(socket_.fd(), nullptr, nullptr);

  if (peer == -1) {
    perror("accept");
  }
  return peer;
}

int Acceptor::GetFd() const { return socket_.fd(); }

void Acceptor::SetReusePort(bool arg) {
  int opt_val = arg;

  if (setsockopt(socket_.fd(), SOL_SOCKET, SO_REUSEPORT, &opt_val,
                 sizeof(opt_val)) < 0) {
    perror("setsockopt");
  }
}

void Acceptor::SetReuseAddr(bool arg) {
  int opt_val = arg;

  if (setsockopt(socket_.fd(), SOL_SOCKET, SO_REUSEADDR, &opt_val,
                 sizeof(opt_val)) < 0) {
    perror("setsockopt");
  }
}

void Acceptor::Bind() {
  int ret = ::bind(socket_.fd(),
                   reinterpret_cast<struct sockaddr *>(addr_.addr_ptr()),
                   sizeof(struct sockaddr));

  if (ret == -1) {
    perror("bind");
  }
}

void Acceptor::Listen() {
  int ret = ::listen(socket_.fd(), kBacklog);

  if (ret == -1) {
    perror("listen");
  }
}

}  // namespace keyword_suggestion
