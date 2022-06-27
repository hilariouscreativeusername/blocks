#include "world.h"

void World::ReceiveChunk(int x, int y, int z, Block* blocks) {
  auto chunk = std::make_shared<Chunk>(x, y, z, blocks);
  chunk->GenerateMesh();
  loaded_chunks_.emplace(std::make_tuple(x, y, z), chunk);
}

void World::RenderChunks() {
  for (ChunkMap::iterator iter = loaded_chunks_.begin(); iter != loaded_chunks_.end(); ++iter) {
    iter->second->Draw();
  }
}
