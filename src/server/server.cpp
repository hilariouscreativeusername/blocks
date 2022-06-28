#include "server.h"

#include "world/chunk_generator.h"
#include "message_type.h"
#include "world/block.h"
#include "world/chunk.h"

BlocksServer::BlocksServer() : cartilage::Server(65432) { }

bool BlocksServer::OnClientConnect(std::shared_ptr<cartilage::Connection> client) {
  client_data_.emplace(client, std::make_unique<ClientData>());

  return true;
}

void BlocksServer::OnClientDisconnect(std::shared_ptr<cartilage::Connection> client) {
  client_data_.erase(client);
}

void BlocksServer::OnMessage(std::shared_ptr<cartilage::Connection> client, cartilage::Message& msg) {
  switch (msg.header.message_type) {
    case MessageType::kPing: {
      CR_LOG_INFO("#%u: ping\n", client->GetID());
      client->Send(msg);
      break;
    }

    case MessageType::kClientUpdate: {
      auto& data = *client_data_[client];
      msg >> data.player_z_;
      msg >> data.player_y_;
      msg >> data.player_x_;
      break;
    }
      
    case MessageType::kShutdown: {
      flag_shutdown_ = true;
      break;
    }
  }
}

bool BlocksServer::FlagShutdown() const {
  return flag_shutdown_;
}

void BlocksServer::LoadClientChunks() {
  for (auto& client : client_data_) {
    auto& connection = *client.first;
    auto& data = *client.second;

    // TODO: figure out which chunk to load
    int load_x = 0, load_y = 0, load_z = 0;

    if (!data.IsChunkLoaded(load_x, load_y, load_z)) {
      cartilage::Message msg;
      msg.header.message_type = MessageType::kLoadChunk;

      // First send the coords of the loaded chunk
      msg << load_x << load_y << load_z;

      Block* blocks = nullptr;
      // TODO: Check if chunk previously generated and load it from disk if so

      // If chunk not previously loaded, generate it
      blocks = GenerateChunk(load_x, load_y, load_z);

      // Add block data to the message
      for (size_t i = 0; i < kChunkSize; ++i) {
        msg << blocks[i];
      }

      connection.Send(msg);

      data.FlagChunkLoaded(0, 0, 0);
      delete[] blocks;
    }
  }
}

void StartServer(std::shared_ptr<BlocksServer> server) {
  while (!server->FlagShutdown()) {
    server->ProcessMessages();

    server->LoadClientChunks();
  }
}
