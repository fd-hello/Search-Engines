#include "../../include/online/condition.h"

namespace keyword_suggestion {

Condition::Condition(MutexLock &mutex) : mutex_(mutex) {
  if (pthread_cond_init(&condition_, nullptr)) {
    perror("pthread_cond_init");
  }
}

Condition::~Condition() {
  if (pthread_cond_destroy(&condition_)) {
    perror("pthread_cond_destroy");
  }
}

void Condition::Wait() {
  if (pthread_cond_wait(&condition_, mutex_.mutex_ptr())) {
    perror("pthread_cond_wait");
  }
}

void Condition::Notify() {
  if (pthread_cond_signal(&condition_)) {
    perror("pthread_cond_signal");
  }
}

void Condition::NotifyAll() {
  if (pthread_cond_broadcast(&condition_)) {
    perror("pthread_cond_broadcast");
  }
}

}  // namespace keyword_suggestion
