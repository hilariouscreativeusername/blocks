#pragma once

#include "block.h"
#include "graphics/vertex_array.h"

#include <cstddef>

static constexpr size_t kChunkWidth  = 16;
static constexpr size_t kChunkHeight = 16;
static constexpr size_t kChunkDepth  = 16;

class Chunk {
public:
  Chunk(int x, int z);

public:
  void Draw();

private:
  VertexArray* vertex_array_;

  Block blocks_[kChunkWidth * kChunkHeight * kChunkDepth];
};
