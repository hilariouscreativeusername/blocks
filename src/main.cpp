#include "entities/camera.h"
#include "graphics/vertex_array.h"
#include "graphics/shader.h"
#include "window/window.h"

#include <GLFW/glfw3.h>
#include <iostream>

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

  Camera camera(&window, &chunk_shader);

  window.PerformResizeCallbacks();
  while (window.IsOpen()) {
    window.PollEvents();
    camera.FreeMove();

    window.Clear();

    chunk_shader.Bind();

    vertex_array.Bind();
    vertex_array.Draw();

    window.SwapBuffers();
  }
}
