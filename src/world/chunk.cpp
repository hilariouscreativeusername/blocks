#include "chunk.h"

Chunk::Chunk(int x, int z) {
  float vertices[] = {
  //  x      y      z     u     v
     0.5f,  0.5f, -5.0f, 1.0f, 0.0f, // top right
     0.5f, -0.5f, -5.0f, 1.0f, 1.0f, // bottom right
    -0.5f, -0.5f, -5.0f, 0.0f, 1.0f, // bottom left
    -0.5f,  0.5f, -5.0f, 0.0f, 0.0f, // top left 
  };
  unsigned int indices[] = { 
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
  };

  vertex_array_ = new VertexArray(vertices, sizeof(vertices), indices, sizeof(indices));
}

void Chunk::Draw() {
  vertex_array_->Draw();
}
