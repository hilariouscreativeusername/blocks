#pragma once

#include "block.h"
#include "graphics/vertex_array.h"

#include <cstddef>

static constexpr size_t kChunkWidth  = 16;
static constexpr size_t kChunkHeight = 16;
static constexpr size_t kChunkDepth  = 16;
static constexpr size_t kChunkSize = kChunkWidth * kChunkHeight * kChunkDepth;

class Chunk {
public:
  Chunk(int x, int y, int z, Block* blocks);
  ~Chunk();
  
public:
  void GenerateMesh();

public:
  void Draw();

private:
  VertexArray* vertex_array_ = nullptr;
  int chunkx_, chunky_, chunkz_;
  Block* blocks_;
};
