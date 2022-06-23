#include "texture_array.h"

#include <cstddef>
#include <cstring>
#include <stdexcept>

#include <glad/glad.h>
#include <stb_image.h>

TextureArray::TextureArray(const char** paths, unsigned int num_textures) {
  if (num_textures < 1) {
    throw std::runtime_error("Trying to create an empty texture array");
  }

  // Load first texture to find width and height
  stbi_uc* first_tex_data = nullptr;
  int width, height, channels;
  first_tex_data = stbi_load(paths[0], &width, &height, &channels, 0);
  if (!first_tex_data) {
    throw std::runtime_error("Failed to load texture");
  }
  
  // Create temporary buffer to load all textures into
  size_t texture_size_bytes = width * height * channels;
  char* buffer = new char[texture_size_bytes * num_textures];
  
  // Copy first texture into buffer
  memcpy(buffer, first_tex_data, texture_size_bytes);
  stbi_image_free(first_tex_data);
  
  // For each texture after the first
  for (size_t i = 1; i < num_textures; ++i) {
    // Load the texture into cpu memory
    stbi_uc* next_tex_data = nullptr;
    int w, h, c;
	  next_tex_data = stbi_load(paths[i], &w, &h, &c, 0);
    if (!next_tex_data) {
      throw std::runtime_error("Failed to load texture");
    }

    // Copy it into the buffer with the other textures in this array
    memcpy(buffer + i * texture_size_bytes, next_tex_data, texture_size_bytes);
    stbi_image_free(next_tex_data);
  }
  
  // Determine storage format based on loaded texture properties
	GLenum internal_format = 0, data_format = 0;
  
	if (channels == 4) {
		internal_format = GL_RGBA8;
		data_format = GL_RGBA;
	}
	else if (channels == 3) {
		internal_format = GL_RGB8;
		data_format = GL_RGB;
	}
	
	if (!(internal_format & data_format)) {
		throw std::runtime_error("Unsupported image format");
	}

  // Texture array data is loaded - now upload it to the GPU
  glGenTextures(1, &texture_id_);
  glBindTexture(GL_TEXTURE_2D_ARRAY, texture_id_);
  // Upload pixel data.
  glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, internal_format, width, height, num_textures, 0, data_format, GL_UNSIGNED_BYTE, buffer);
  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}

TextureArray::~TextureArray() {
  glDeleteTextures(1, &texture_id_);
}

void TextureArray::Bind() {
  glBindTexture(GL_TEXTURE_2D_ARRAY, texture_id_);
}
