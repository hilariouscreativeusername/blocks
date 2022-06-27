#pragma once

#include <cstddef>
#include <memory>
#include <unordered_map>

#include <cartilage.hpp>

#include "client_data.h"

class BlocksServer : public cartilage::Server {
public:
  BlocksServer();
  
protected:
  virtual bool OnClientConnect(std::shared_ptr<cartilage::Connection> client) override;
  virtual void OnClientDisconnect(std::shared_ptr<cartilage::Connection> client) override;
  virtual void OnMessage(std::shared_ptr<cartilage::Connection> client, cartilage::Message& msg) override;

public:
  bool FlagShutdown() const;

public:
  void LoadClientChunks();
  
private:
  bool flag_shutdown_ = false;

  std::unordered_map<std::shared_ptr<cartilage::Connection>, std::unique_ptr<ClientData>> client_data_;
};

void StartServer();
