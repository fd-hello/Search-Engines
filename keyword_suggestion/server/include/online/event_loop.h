#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_EVENT_LOOP_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_EVENT_LOOP_H_

#include <assert.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "acceptor.h"
#include "mutex_lock.h"
#include "tcp.h"

namespace keyword_suggestion {

class Tcp;
using TcpPtr = std::shared_ptr<Tcp>;
using TcpCallback = std::function<void(const TcpPtr &connection)>;
using Functor = std::function<void()>;

class EventLoop {
 public:
  EventLoop(Acceptor &acceptor);

  void Loop();
  void RunInLoop(Functor &&callback);
  void Unloop();

  void SetConnectedCallback(const TcpCallback &&callback);
  void SetReceivedCallback(const TcpCallback &&callback);
  void SetClosedCallback(const TcpCallback &&callback);

 private:
  int CreateEpollFd();
  void AddReadFd(int fd);
  void DeleteReadFd(int fd);
  void WaitEpollFd();
  void HandleNewConnection();
  void HandleMessage(int fd);

  int CreateEventfd();
  void HandleRead();
  void Wakeup();
  void DoPendingFunctors();

  TcpCallback Connected;
  TcpCallback Received;
  TcpCallback Closed;

  Acceptor &acceptor_;
  std::vector<struct epoll_event> event_list_;
  std::map<int, TcpPtr> connection_;
  int epoll_fd_;
  bool is_looping_;

  int event_fd_;
  std::vector<Functor> pending_functors_;
  MutexLock mutex_lock_;
};

}  // namespace keyword_suggestion

#endif
