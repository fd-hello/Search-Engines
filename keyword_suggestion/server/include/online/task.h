#ifndef KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_TASK_H_
#define KEYWORD_SUGGESTION_SERVER_INCLUDE_ONLINE_TASK_H_

#include <functional>

namespace keyword_suggestion {

using Task = std::function<void()>;

}

#endif
