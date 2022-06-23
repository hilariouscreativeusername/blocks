#pragma once

class TextureArray {
public:
  TextureArray(const char** paths, unsigned int num_textures);
  ~TextureArray();
  
  void Bind();
  
private:
  unsigned int texture_id_;
};
