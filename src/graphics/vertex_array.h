#pragma once

class VertexArray {
public:
  VertexArray(float* vertices, unsigned int num_vertices, unsigned int* indices, unsigned int num_indices);
  ~VertexArray();

  void Bind();
  void Draw();

private:
  unsigned int vao_;
  unsigned int vbo_;
  unsigned int ibo_;
  unsigned int num_indices_;
};
