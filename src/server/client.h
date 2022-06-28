#pragma once

#include <cartilage.hpp>
#include <glm/vec3.hpp>

class World;

class BlocksClient : public cartilage::Client {
public:
  BlocksClient(const char* ip);

  void PingServer();
  void SendShutdownCommand();
  
  void SendUpdate(const glm::vec3& pos);
  void CheckMessages(World& world);
};
