#pragma once

class Texture {
public:
  Texture(const char* path);
  ~Texture();

  void Bind();

private:
  unsigned int texture_id_;
};
