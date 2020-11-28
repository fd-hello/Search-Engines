#include "../../include/online/tcp_server.h"

namespace keyword_suggestion {

TcpServer::TcpServer(int port, const std::string &ip)
    : acceptor_(port, ip), event_loop_(acceptor_) {}

void TcpServer::Start() {
  acceptor_.Init();
  event_loop_.Loop();
}

void TcpServer::Stop() { event_loop_.Unloop(); }

void TcpServer::SetConnectedCallback(const TcpCallback &&callback) {
  event_loop_.SetConnectedCallback(std::move(callback));
}

void TcpServer::SetReceivedCallback(const TcpCallback &&callback) {
  event_loop_.SetReceivedCallback(std::move(callback));
}

void TcpServer::SetClosedCallback(const TcpCallback &&callback) {
  event_loop_.SetClosedCallback(std::move(callback));
}

}  // namespace keyword_suggestion
