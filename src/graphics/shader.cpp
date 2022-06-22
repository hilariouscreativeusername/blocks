#include "shader.h"

#include <fstream>
#include <string>
#include <sstream>

#include <glad/glad.h>

unsigned int CompileShader(const char* shader_path, GLenum shader_type) {
  // Read whole shader source file into a string
  std::ifstream shader_file(shader_path);
  if (!shader_file.is_open()) {
    throw std::exception("Unable to open shader file");
  }
  std::stringstream string_buffer;
  string_buffer << shader_file.rdbuf();
  std::string code = string_buffer.str();
	const GLchar* source_ptr = (const GLchar*)code.c_str();

  unsigned int shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &source_ptr, 0);
  glCompileShader(shader);
  // Check for compile errors
  int success;
  char info_log[512]{};
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, info_log);
    throw std::exception(info_log);
  }

  return shader;
}

Shader::Shader(const char* vert_path, const char* frag_path) {
  unsigned int vert_shader = CompileShader(vert_path, GL_VERTEX_SHADER);
  unsigned int frag_shader = CompileShader(frag_path, GL_FRAGMENT_SHADER);

  // Link shaders
  shader_program_ = glCreateProgram();
  glAttachShader(shader_program_, vert_shader);
  glAttachShader(shader_program_, frag_shader);
  glLinkProgram(shader_program_);

  // Check for linking errors
  int success;
  char info_log[512]{};
  glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program_, 512, NULL, info_log);
    throw std::exception(info_log);
  }

  // Cleanup shaders
  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);
}

Shader::~Shader() {
  glDeleteProgram(shader_program_);
}

void Shader::Bind() {
  glUseProgram(shader_program_);
}
