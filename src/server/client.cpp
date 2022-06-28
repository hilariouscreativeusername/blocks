#include "client.h"

#include <chrono>
#include <iostream>

#include "message_type.h"
#include "world/world.h"

BlocksClient::BlocksClient(const char* ip) {
  Connect(ip, 65432);
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

void BlocksClient::SendUpdate(const glm::vec3& pos) {
  cartilage::Message msg;
  msg.header.message_type = MessageType::kClientUpdate;
  msg << pos.x << pos.y << pos.z;
  Send(msg);
}

void BlocksClient::CheckMessages(World& world) {
  while (!IncomingMessages().empty()) {
    cartilage::Message msg = IncomingMessages().pop_front().msg;
    
    switch (msg.header.message_type) {
      case MessageType::kPing: {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::steady_clock::time_point sent_time;
        msg >> sent_time;

        std::cout << "Ping round trip time: " << (std::chrono::duration<double>(now - sent_time).count() * 1000) << "ms\n";
        break;
      }

      case MessageType::kLoadChunk: {
        // Read data from message in reverse order to the order it was packed
        Block* blocks = new Block[kChunkSize];
        for (size_t i = kChunkSize; i --> 0 ;) {
          msg >> blocks[i];
        }

        int chunk_x, chunk_y, chunk_z;
        msg >> chunk_x >> chunk_y >> chunk_z;

        world.ReceiveChunk(chunk_x, chunk_y, chunk_z, blocks);
        break;
      }
    }
  }
}
