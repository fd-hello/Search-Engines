#include "../../include/online/thread_pool.h"

#include <unistd.h>

namespace keyword_suggestion {

ThreadPool::ThreadPool(size_t thread_num, size_t queue_size)
    : thread_num_(thread_num),
      queue_size_(queue_size),
      task_queue_(queue_size_),
      is_exit_(false) {
  thread_.reserve(thread_num_);
}

ThreadPool::~ThreadPool() {
  if (!is_exit_) {
    Stop();
  }
}

void ThreadPool::Start() {
  for (size_t i = 0; i != thread_num_; i++) {
    std::unique_ptr<Thread> ptr(
        new Thread(std::bind(&ThreadPool::ThreadFunction, this)));
    thread_.push_back(std::move(ptr));
  }

  for (auto& thread : thread_) {
    thread->Start();
  }
}

void ThreadPool::Stop() {
  if (!is_exit_) {
    while (!task_queue_.IsEmpty()) {
      sleep(1);
    }
    is_exit_ = true;
    task_queue_.WakeUp();
    for (auto& thread : thread_) {
      thread->Join();
    }
  }
}

void ThreadPool::AddTask(Task&& ptr) { task_queue_.Push(std::move(ptr)); }

Task ThreadPool::GetTask() { return task_queue_.Pop(); }

void ThreadPool::ThreadFunction() {
  while (!is_exit_) {
    Task task = GetTask();

    if (task) {
      task();
    }
  }
}

}  // namespace keyword_suggestion
