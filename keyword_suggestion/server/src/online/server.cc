#include <functional>

#include "../../include/online/configuration.h"
#include "../../include/online/my_task.h"
#include "../../include/online/dict.h"
#include "../../include/online/tcp_server.h"
#include "../../include/online/thread_pool.h"

keyword_suggestion::ThreadPool *thread_pool_ptr = nullptr;

void Run();
void Connected(const keyword_suggestion::TcpPtr &connection);
void Received(const keyword_suggestion::TcpPtr &connection);
void Closed(const keyword_suggestion::TcpPtr &connection);

int main() {
  Run();
  return 0;
}

void Run() {
  keyword_suggestion::ThreadPool thread_pool(4, 10);

  thread_pool.Start();
  thread_pool_ptr = &thread_pool;

  keyword_suggestion::Configuration net("net");

  keyword_suggestion::Dict::createInstance()->loadLibfile(); 

  keyword_suggestion::TcpServer tcp_server(net.GetPort("default_port"), net.GetIp("default_ip"));

  tcp_server.SetConnectedCallback(Connected);
  tcp_server.SetReceivedCallback(Received);
  tcp_server.SetClosedCallback(Closed);
  tcp_server.Start();
}

void Connected(const keyword_suggestion::TcpPtr &connection) {
  keyword_suggestion::Message msg;

  printf("\e[1m[Server]\e[0m\n");
  printf("  %s has connected\n", connection->ConvertToString().c_str());
  strcpy(msg.content, "Welcome");
  msg.len = strlen(msg.content);
  msg.id = 0;
  connection->Send(msg);
}

void Received(const keyword_suggestion::TcpPtr &connection)
{
  keyword_suggestion::Message msg;

  memset(&msg, 0, sizeof(msg));
  msg = connection->Receive();

  printf("\e[1;36m[Client]\e[0m\n");
  printf("  %s\n", msg.content);

  keyword_suggestion::MyTask task(msg, connection);
  thread_pool_ptr->AddTask(std::bind(&keyword_suggestion::MyTask::execute, task));
}

void Closed(const keyword_suggestion::TcpPtr &connection)
{
  printf("\e[1m[Server]\e[0m\n");
  printf("  The connection is closed\n");
}
