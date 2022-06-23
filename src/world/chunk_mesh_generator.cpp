#include "chunk_mesh_generator.h"

VertexArray* GenerateMesh(Block* blocks) {
  // After chunk is either loaded from disk or generated, generate mesh
  float vertices[] = {
  // x     y     z     u     v
    1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top right
    1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom right
    0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
    0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // top left 
  };
  unsigned int indices[] = { 
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
  };

  return new VertexArray(vertices, sizeof(vertices), indices, sizeof(indices));
}
