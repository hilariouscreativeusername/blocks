#pragma once

#include "graphics/vertex_array.h"

class Chunk {
public:
  Chunk(int x, int z);

public:
  void Draw();

private:
  VertexArray* vertex_array_;
};
