#include "../../include/online/thread.h"

#include <stdio.h>

namespace keyword_suggestion {

namespace current_thread {

__thread const char *name = "this thread";

}

using ThreadCallback = Thread::ThreadCallback;

struct ThreadData {
  std::string name_;
  ThreadCallback callback_;

  ThreadData(const std::string &name, const ThreadCallback &callback)
      : name_(name), callback_(callback) {}

  void Run() {
    current_thread::name =
        (name_ == std::string()) ? "this thread" : name_.c_str();
    if (callback_) {
      callback_();
    }
  }
};

Thread::Thread(ThreadCallback &&callback, const std::string &name)
    : thread_id_(0),
      is_running_(false),
      callback_(std::move(callback)),
      name_(name) {}

Thread::~Thread() {
  if (is_running_) {
    pthread_detach(thread_id_);
  }
}

void Thread::Start() {
  ThreadData *thread_data = new ThreadData(name_, callback_);

  if (pthread_create(&thread_id_, nullptr, ThreadFunction, thread_data)) {
    perror("pthread_create");
    return;
  }
  is_running_ = true;
}

void Thread::Join() {
  if (is_running_) {
    pthread_join(thread_id_, nullptr);
    is_running_ = false;
  }
}

void *Thread::ThreadFunction(void *arg) {
  ThreadData *ptr = static_cast<ThreadData *>(arg);

  if (ptr) {
    ptr->Run();
  }
  delete ptr;
  return nullptr;
}

}  // namespace keyword_suggestion
