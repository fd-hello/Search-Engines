#ifndef KEYWORD_SUGGESTION_CLIENT_INCLUDE_CONNECTOR_H_
#define KEYWORD_SUGGESTION_CLIENT_INCLUDE_CONNECTOR_H_

#include <string>

#include "inet_address.h"
#include "socket.h"

const int kBacklog = 8;

namespace keyword_suggestion {

class Connector {
 public:
  Connector(int port, const std::string &ip = "0.0.0.0");

  int Connect();

 private:
  InetAddress addr_;
  Socket socket_;
};

}  // namespace keyword_suggestion

#endif
