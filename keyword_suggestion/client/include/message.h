#ifndef KEYWORD_SUGGESTION_CLIENT_INCLUDE_MESSAGE_H_
#define KEYWORD_SUGGESTION_CLIENT_INCLUDE_MESSAGE_H_

namespace keyword_suggestion {

struct Message {
  int len;
  int id;
  char content[1024];
};

}  // namespace keyword_suggestion

#endif
