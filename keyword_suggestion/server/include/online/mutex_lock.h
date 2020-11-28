#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_MUTEX_LOCK_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_MUTEX_LOCK_H_

#include <mutex>

#include "noncopyable.h"

namespace keyword_suggestion {

class MutexLock : Noncopyable {
 public:
  MutexLock();

  ~MutexLock();

  void Lock();
  void Unlock();

  pthread_mutex_t *mutex_ptr();

 private:
  pthread_mutex_t mutex_;
};

class MutexLockGuard {
 public:
  MutexLockGuard(MutexLock &);

  ~MutexLockGuard();

 private:
  MutexLock &mutex_;
};

}  // namespace keyword_suggestion

#endif
