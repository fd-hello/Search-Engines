#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_CONDITION_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_CONDITION_H_

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>

#include "mutex_lock.h"
#include "noncopyable.h"

namespace keyword_suggestion {

class Condition : Noncopyable {
 public:
  Condition(MutexLock &);

  ~Condition();

  void Wait();
  void Notify();
  void NotifyAll();

 private:
  MutexLock &mutex_;
  pthread_cond_t condition_;
};

}  // namespace keyword_suggestion

#endif
