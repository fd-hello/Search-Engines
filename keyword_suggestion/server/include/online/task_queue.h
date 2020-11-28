#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_TASK_QUEUE_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_TASK_QUEUE_H_

#include <queue>

#include "condition.h"
#include "mutex_lock.h"
#include "task.h"

namespace keyword_suggestion {

using ElemType = Task;

class TaskQueue {
 public:
  TaskQueue(size_t);

  bool IsEmpty() const;
  bool IsFull() const;
  void Push(const ElemType &element);
  ElemType Pop();
  void WakeUp();

 private:
  int queue_size_;
  std::queue<ElemType> queue_;
  MutexLock mutex_;
  Condition not_empty_;
  Condition not_full_;
  bool flag_;
};

}  // namespace keyword_suggestion

#endif
