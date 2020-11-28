#ifndef KEYWORD_SUGGESTION_CLIENT_INCLUDE_NONCOPYABLE_H_
#define KEYWORD_SUGGESTION_CLIENT_INCLUDE_NONCOPYABLE_H_

namespace keyword_suggestion {

class Noncopyable {
 protected:
  Noncopyable() = default;
  ~Noncopyable() = default;

 private:
  Noncopyable(const Noncopyable &) = delete;
  Noncopyable &operator=(const Noncopyable &) = delete;
};

}  // namespace keyword_suggestion

#endif
