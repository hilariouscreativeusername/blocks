#include <glm/gtc/matrix_transform.hpp>

#include "window/window.h"
#include "graphics/vertex_array.h"
#include "graphics/shader.h"

int main() {
  Window window;

  float vertices[] = {
     0.5f,  0.5f, -5.0f,  // top right
     0.5f, -0.5f, -5.0f,  // bottom right
    -0.5f, -0.5f, -5.0f,  // bottom left
    -0.5f,  0.5f, -5.0f   // top left 
  };
  unsigned int indices[] = { 
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
  };
  VertexArray vertex_array(vertices, sizeof(vertices), indices, sizeof(indices));

  Shader chunk_shader("src/shaders/chunk_shader.vert.glsl", "src/shaders/chunk_shader.frag.glsl");

  glm::mat4 perspective_projection = glm::perspectiveFov(45.0f, 1280.0f, 720.0f, 0.1f, 1000.0f);

  while (window.IsOpen()) {
    window.PollEvents();
    window.Clear();

    chunk_shader.Bind();
    chunk_shader.UploadUniform(perspective_projection, "u_projection");

    vertex_array.Bind();
    vertex_array.Draw();

    window.SwapBuffers();
  }
}
