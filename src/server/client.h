#pragma once

#include <cartilage.hpp>

class World;

class BlocksClient : public cartilage::Client {
public:
  BlocksClient(const char* ip);

  void PingServer();
  void SendShutdownCommand();
  
  void CheckMessages(World& world);
};
