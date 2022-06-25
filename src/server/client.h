#pragma once

#include <cartilage.hpp>

class BlocksClient : public cartilage::Client {
public:
  BlocksClient();

  void PingServer();
  void SendShutdownCommand();
  
  void CheckMessages();
};
