#pragma once

class Shader {
public:
  Shader(const char* vert_path, const char* frag_path);

public:
  void Bind();
};
