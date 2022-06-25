#include "server.h"

#include "message_type.h"

BlocksServer::BlocksServer() : cartilage::Server(65432) { }

bool BlocksServer::OnClientConnect(std::shared_ptr<cartilage::Connection> client) {
  return true;
}

void BlocksServer::OnClientDisconnect(std::shared_ptr<cartilage::Connection> client) {

}

void BlocksServer::OnMessage(std::shared_ptr<cartilage::Connection> client, cartilage::Message& msg) {
  switch (msg.header.message_type) {
    case MessageType::kPing:
      CR_LOG_INFO("#%u: ping\n", client->GetID());
      client->Send(msg);
      break;
      
    case MessageType::kShutdown:
      flag_shutdown_ = true;
      break;
  }
}

bool BlocksServer::FlagShutdown() const {
  return flag_shutdown_;
}

void StartServer() {
  BlocksServer server;
  server.Start();

  while (!server.FlagShutdown()) {
    server.ProcessMessages();
  }
}
