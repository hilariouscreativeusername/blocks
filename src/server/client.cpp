#include "client.h"

#include <chrono>
#include <iostream>

BlocksClient::BlocksClient() {
  Connect("127.0.0.1", 65432);
}

 void BlocksClient::PingServer() {
  std::cout << "Pinging server\n";

  cartilage::Message msg;
  msg.header.message_type = 0;

  auto now = std::chrono::high_resolution_clock::now();
  msg << now;

  Send(msg);
}

void BlocksClient::CheckMessages() {
  while (!IncomingMessages().empty()) {
    cartilage::Message msg = IncomingMessages().pop_front().msg;
    
    switch (msg.header.message_type) {
      case 0:
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::steady_clock::time_point sent_time;
        msg >> sent_time;

        std::cout << "Ping round trip time: " << (std::chrono::duration<double>(now - sent_time).count() * 1000) << "ms\n";
        break;
    }
    
  }
}
