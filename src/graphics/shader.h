#pragma once

class Shader {
public:
  Shader(const char* vert_path, const char* frag_path);
  ~Shader();

public:
  void Bind();

private:
  unsigned int shader_program_;
};
