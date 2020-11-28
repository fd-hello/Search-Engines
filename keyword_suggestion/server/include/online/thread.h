#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_THREAD_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_THREAD_H_

#include <pthread.h>

#include <functional>
#include <string>

#include "noncopyable.h"

namespace keyword_suggestion {

namespace current_thread {

extern __thread const char *name;

}

class Thread : public Noncopyable {
 public:
  using ThreadCallback = std::function<void()>;

  Thread(ThreadCallback &&callback, const std::string &name = std::string());
  ~Thread();

  void Start();
  void Join();

  pthread_t thread_id() const { return thread_id_; }
  std::string name() const { return name_; }

 private:
  static void *ThreadFunction(void *arg);

  pthread_t thread_id_;
  bool is_running_;
  ThreadCallback callback_;
  std::string name_;
};

}  // namespace keyword_suggestion

#endif
