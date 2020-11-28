#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_TCP_SERVER_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_TCP_SERVER_H_

#include "acceptor.h"
#include "event_loop.h"
#include "tcp.h"

namespace keyword_suggestion {

class TcpServer {
 public:
  TcpServer(int port, const std::string &ip = "0.0.0.0");

  void Start();
  void Stop();

  void SetConnectedCallback(const TcpCallback &&callback);
  void SetReceivedCallback(const TcpCallback &&callback);
  void SetClosedCallback(const TcpCallback &&callback);

 private:
  Acceptor acceptor_;
  EventLoop event_loop_;
};

}  // namespace keyword_suggestion

#endif
