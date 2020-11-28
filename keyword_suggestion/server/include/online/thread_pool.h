#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_THREAD_POOL_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_THREAD_POOL_H_

#include <memory>
#include <vector>

#include "task.h"
#include "task_queue.h"
#include "thread.h"

namespace keyword_suggestion {

class Thread;

class ThreadPool {
 public:
  ThreadPool(size_t thread_num, size_t queue_size);
  ~ThreadPool();

  void Start();
  void Stop();
  void AddTask(Task &&task);

 private:
  Task GetTask();
  void ThreadFunction();

  size_t thread_num_;
  size_t queue_size_;
  std::vector<std::unique_ptr<Thread>> thread_;
  TaskQueue task_queue_;
  bool is_exit_;
};

}  // namespace keyword_suggestion

#endif
