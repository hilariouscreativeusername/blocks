#pragma once

#include <glm/mat4x4.hpp>

class Shader {
public:
  Shader(const char* vert_path, const char* frag_path);
  ~Shader();

public:
  void Bind();

  void UploadUniform(const glm::mat4& matrix, const char* uniform_name);

private:
  unsigned int shader_program_;
};
