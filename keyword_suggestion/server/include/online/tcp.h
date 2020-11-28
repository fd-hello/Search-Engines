#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_TCP_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_TCP_H_

#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "event_loop.h"
#include "inet_address.h"
#include "message.h"
#include "noncopyable.h"
#include "socket.h"
#include "socket_io.h"

const size_t kMaxSize = 65536;

namespace keyword_suggestion {

class EventLoop;
class Tcp;
using TcpPtr = std::shared_ptr<Tcp>;
using TcpCallback = std::function<void(const TcpPtr &connection)>;

class Tcp : Noncopyable, public std::enable_shared_from_this<Tcp> {
 public:
  Tcp(int fd, EventLoop *event_loop);
  ~Tcp();

  void Send(const Message &msg);
  void SendInLoop(const Message &msg);
  Message Receive();
  std::string ConvertToString() const;
  void Shutdown();
  bool IsConnectionClosed();

  void SetConnectedCallback(const TcpCallback &callback);
  void SetReceivedCallback(const TcpCallback &callback);
  void SetClosedCallback(const TcpCallback &callback);
  void HandleConnectedCallback();
  void HandleReceivedCallback();
  void HandleClosedCallback();

 private:
  InetAddress GetSockAddr(int fd);
  InetAddress GetPeerAddr(int fd);

  TcpCallback Connected;
  TcpCallback Received;
  TcpCallback Closed;

  EventLoop *event_loop_;
  Socket socket_;
  SocketIo socket_io_;
  InetAddress sock_addr_;
  InetAddress peer_addr_;
  bool is_shutdown_;
};

}  // namespace keyword_suggestion

#endif
