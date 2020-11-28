#include "../include/configuration.h"
#include "../include/connector.h"
#include "../include/tcp.h"

void Run();

int main() {
  Run();
  return 0;
}

void Run() {
  keyword_suggestion::Configuration net("net");
  keyword_suggestion::Connector connector(net.GetPort("default_port"),
                                          net.GetIp("default_ip"));
  keyword_suggestion::Tcp tcp(connector.Connect());

  tcp.RunInLoop();
}
