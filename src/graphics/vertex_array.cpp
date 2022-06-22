#include "vertex_array.h"

#include <glad/glad.h>

VertexArray::VertexArray(float* vertices, unsigned int num_vertices, unsigned int* indices, unsigned int num_indices) {
  num_indices_ = num_indices;

  // Create and bind vertex array object
  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  // Create and bind vertex buffer
  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

  // Upload vertex data to vertex buffer
  glBufferData(GL_ARRAY_BUFFER, num_vertices, vertices, GL_STATIC_DRAW);
 
  // Tell OpenGL how to interpret the vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Create and bind index buffer
  glGenBuffers(1, &ibo_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);

  // Upload index data to index buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices, indices, GL_STATIC_DRAW);

  // We have finished performing operations on the VBO and it is now associated with the VAO, so unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Don't unbind the index buffer
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &vao_);
  glDeleteBuffers(1, &vbo_);
}

void VertexArray::Bind() {
  glBindVertexArray(vao_);
}

void VertexArray::Draw() {
  glDrawElements(GL_TRIANGLES, num_indices_, GL_UNSIGNED_INT, 0);
}
