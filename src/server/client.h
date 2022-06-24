#pragma once

#include <cartilage.hpp>

class BlocksClient : cartilage::Client {
public:
  BlocksClient();

  void PingServer();
  void SendShutdownCommand();
  
  void CheckMessages();
};
