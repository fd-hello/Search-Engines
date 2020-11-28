#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_MESSAGE_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_MESSAGE_H_

namespace keyword_suggestion {

struct Message {
  int len;
  int id;
  char content[1024];
};

}  // end of namespace keyword_suggestion

#endif
