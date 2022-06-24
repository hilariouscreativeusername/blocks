#pragma once

#include <cartilage.hpp>

class BlocksServer : public cartilage::Server {
public:
  BlocksServer();
  
protected:
  virtual bool OnClientConnect(std::shared_ptr<cartilage::Connection> client) override;
  virtual void OnClientDisconnect(std::shared_ptr<cartilage::Connection> client) override;
  virtual void OnMessage(std::shared_ptr<cartilage::Connection> client, cartilage::Message& msg) override;
  
public:
  bool FlagShutdown() const;
  
private:
  bool flag_shutdown_ = false;
};
