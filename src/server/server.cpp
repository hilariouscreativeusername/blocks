#include "server.h"

BlocksServer::BlocksServer() : cartilage::Server(65432) { }

bool BlocksServer::OnClientConnect(std::shared_ptr<cartilage::Connection> client) {
  return true;
}

void BlocksServer::OnClientDisconnect(std::shared_ptr<cartilage::Connection> client) {

}

void BlocksServer::OnMessage(std::shared_ptr<cartilage::Connection> client, cartilage::Message& msg) {
  switch (msg.header.message_type) {
    case 0:
      CR_LOG_INFO("#%u: ping\n", client->GetID());
      client->Send(msg);
      break;
  }
}
