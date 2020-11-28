#include "../../include/online/task_queue.h"

namespace keyword_suggestion {

TaskQueue::TaskQueue(size_t queue_size)
    : queue_size_(queue_size),
      queue_(),
      mutex_(),
      not_empty_(mutex_),
      not_full_(mutex_),
      flag_(true) {}

bool TaskQueue::IsEmpty() const { return !queue_.size(); }

bool TaskQueue::IsFull() const {
  return static_cast<int>(queue_.size()) == queue_size_;
}

void TaskQueue::Push(const ElemType &element) {
  MutexLockGuard auto_lock(mutex_);

  while (IsFull()) {
    not_full_.Wait();
  }
  queue_.push(element);
  not_empty_.Notify();
}

ElemType TaskQueue::Pop() {
  MutexLockGuard auto_lock(mutex_);

  while (IsEmpty() && flag_) {
    not_empty_.Wait();
  }
  if (flag_) {
    ElemType element = queue_.front();

    queue_.pop();
    not_full_.Notify();
    return element;
  } else {
    return nullptr;
  }
}

void TaskQueue::WakeUp() {
  flag_ = false;
  not_empty_.NotifyAll();
}

}  // namespace keyword_suggestion
