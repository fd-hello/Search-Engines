#include "../include/tcp.h"

namespace keyword_suggestion {

Tcp::Tcp(int fd)
    : socket_(fd),
      socket_io_(fd),
      sock_addr_(GetSockAddr(fd)),
      peer_addr_(GetPeerAddr(fd)),
      is_shutdown_(false) {}

Tcp::~Tcp() {
  if (!is_shutdown_) {
    Shutdown();
  }
}

void Tcp::ConvertToString() const {
  std::ostringstream oss;

  oss << sock_addr_.GetIp() << ":" << sock_addr_.GetPort() << " --> "
      << peer_addr_.GetIp() << ":" << peer_addr_.GetPort();
  printf("\e[1m[Client]\e[0m\n");
  printf("  %s has connected\n", oss.str().c_str());
}

void Tcp::RunInLoop() {
  bool inloop = true;

  while (inloop) {
    Receive();
    inloop = Send();
  }
}

void Tcp::Receive() {
  Message msg;

  socket_io_.ReadJson(msg);
}

bool Tcp::Send() {
  Message msg;

  printf("\e[1;32m[Client]\e[0m\n  ");
  while (1) {
    char buffer[kMaxSize];
    int offset = 0;
    std::string str;

    memset(&msg, 0, sizeof(msg));
    std::getline(std::cin, str);
    strcpy(buffer, str.c_str());

    if (!strcmp(buffer, "exit")) {
      return false;
    }

    while (offset < static_cast<int>(strlen(buffer))) {
      if (buffer[offset] == ' ') {
        ++offset;
      } else {
        break;
      }
    }
    if ((buffer[offset] == '1' || buffer[offset] == '2') &&
        buffer[offset + 1] == ' ') {
      msg.id = buffer[offset] - '0';
      sprintf(msg.content, "%s", buffer + offset + 2);
      if (!IsValid(msg.content)) {
        printf("\e[1m[Client]\e[0m\n");
        printf("  Please enter a valid word\n");
        printf("\e[1;32m[Client]\e[0m\n  ");
        continue;
      }
      msg.len = strlen(msg.content);
      break;
    } else {
      printf("\e[1m[Client]\e[0m\n");
      printf("  Please enter a valid ID\n");
      printf("\e[1;32m[Client]\e[0m\n  ");
    }
  }
  socket_io_.WriteN(&msg, sizeof(int) + sizeof(int) + msg.len);
  return true;
}

bool Tcp::IsValid(char *word) {
  if (word[0] & (1 << 7)) {
    for (size_t i = 1; i < strlen(word); ++i) {
      if (!(word[i] & (1 << 7))) {
        return false;
      }
    }
    return true;
  } else {
    for (size_t i = 0; i < strlen(word); ++i) {
      if (!IsLetter(word[i]) &&
          !(i && word[i] == '-' && IsLetter(word[i - 1]))) {
        return false;
      }
    }
    return true;
  }
}

bool Tcp::IsLetter(char ch) {
  return ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z');
}

void Tcp::Shutdown() {
  is_shutdown_ = true;
  socket_.ShutdownWrite();
}

InetAddress Tcp::GetSockAddr(int fd) {
  struct sockaddr_in addr;
  socklen_t len = sizeof(struct sockaddr);

  if (getsockname(socket_.fd(), reinterpret_cast<struct sockaddr *>(&addr),
                  &len) == -1) {
    perror("getsockname");
  }
  return InetAddress(addr);
}

InetAddress Tcp::GetPeerAddr(int fd) {
  struct sockaddr_in addr;
  socklen_t len = sizeof(struct sockaddr);

  if (getpeername(socket_.fd(), reinterpret_cast<struct sockaddr *>(&addr),
                  &len) == -1) {
    perror("getpeername");
  }
  return InetAddress(addr);
}

}  // namespace keyword_suggestion
