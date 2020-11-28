#include "../include/socket_io.h"

namespace keyword_suggestion {

SocketIo::SocketIo(int fd) : fd_(fd) {}

void SocketIo::ReadJson(Message &msg) {
  char buffer[sizeof(msg)];
  std::string json_str;

  ReceivePeek(buffer, sizeof(msg));
  recv(fd_, &msg.len, sizeof(int), MSG_WAITALL);
  recv(fd_, &msg.id, sizeof(int), MSG_WAITALL);
  recv(fd_, &msg.content, msg.len, 0);

  json_str = static_cast<std::string>(msg.content);
  if (msg.id == 0) {
    printf("\e[1;36m[Server]\e[0m\n");
    printf("  %s\n", msg.content);
  } else if (msg.id == 100) {
    UnpackJson(json_str);
  }
}

void SocketIo::UnpackJson(const std::string &json_str) {
  Json::Reader *reader = new Json::Reader(Json::Features::strictMode());
  Json::Value root;
  std::string content;

  if (reader->parse(json_str, root)) {
    if (root.isArray()) {
      int array_size = root.size();

      printf("\e[1;36m[Server]\e[0m\n");
      content = root[static_cast<Json::Value::UInt>(0)]["candidate"].asString();
      if (!::strlen(content.c_str())) {
        printf("  Not found\n");
      } else {
        printf("  Condidate words:\n");
        for (int i = 0; i < array_size; ++i) {
          std::string word = root[i]["candidate"].asString();

          printf("  * %s\n", word.c_str());
        }
      }
    }
  }
}

int SocketIo::WriteN(const Message *msg, int n) {
  int ret, offset = n;
  const Message *ptr = msg;

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
