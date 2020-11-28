#include "../../include/online/mutex_lock.h"

namespace keyword_suggestion {

MutexLock::MutexLock() {
  if (pthread_mutex_init(&mutex_, nullptr)) {
    perror("pthread_mutex_init");
  }
}

MutexLock::~MutexLock() {
  if (pthread_mutex_destroy(&mutex_)) {
    perror("pthread_mutex_destroy");
  }
}

void MutexLock::Lock() {
  if (pthread_mutex_lock(&mutex_)) {
    perror("pthread_mutex_lock");
  }
}

void MutexLock::Unlock() {
  if (pthread_mutex_unlock(&mutex_)) {
    perror("pthread_mutex_unlock");
  }
}

pthread_mutex_t* MutexLock::mutex_ptr() { return &mutex_; }

MutexLockGuard::MutexLockGuard(MutexLock& mutex) : mutex_(mutex) {
  mutex_.Lock();
}

MutexLockGuard::~MutexLockGuard() { mutex_.Unlock(); }

}  // namespace keyword_suggestion
