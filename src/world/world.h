#pragma once

#include "chunk.h"

#include <tuple>
#include <map>
#include <memory>

class World {
public:
  void ReceiveChunk(int x, int y, int z, Block* blocks);

  void RenderChunks();

private:
  typedef std::map<std::tuple<int, int, int>, std::shared_ptr<Chunk>> ChunkMap;
  ChunkMap loaded_chunks_;
};
