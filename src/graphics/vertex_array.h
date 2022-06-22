#pragma once

class VertexArray {
public:
  VertexArray(float* vertices, unsigned int num_vertices);
  ~VertexArray();

  void Bind();
  void Draw();

private:
  unsigned int vao_;
  unsigned int vbo_;
  unsigned int num_vertices_;
};
