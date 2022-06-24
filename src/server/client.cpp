#include "client.h"

#include <chrono>
#include <iostream>

#include "message_type.h"

BlocksClient::BlocksClient() {
  Connect("127.0.0.1", 65432);
}

 void BlocksClient::PingServer() {
  std::cout << "Pinging server\n";

  cartilage::Message msg;
  msg.header.message_type = MessageType::kPing;

  auto now = std::chrono::high_resolution_clock::now();
  msg << now;

  Send(msg);
}

void BlocksClient::SendShutdownCommand() {
  cartilage::Message msg;
  msg.header.message_type = MessageType::kShutdown;
  Send(msg);
}

void BlocksClient::CheckMessages() {
  while (!IncomingMessages().empty()) {
    cartilage::Message msg = IncomingMessages().pop_front().msg;
    
    switch (msg.header.message_type) {
      case MessageType::kPing:
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::steady_clock::time_point sent_time;
        msg >> sent_time;

        std::cout << "Ping round trip time: " << (std::chrono::duration<double>(now - sent_time).count() * 1000) << "ms\n";
        break;
    }
    
  }
}
