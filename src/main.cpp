#include "window/window.h"
#include "graphics/vertex_array.h"

int main() {
  Window window;

  float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
  };
  unsigned int indices[] = { 
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
  };
  VertexArray vertex_array(vertices, sizeof(vertices), indices, sizeof(indices));

  while (window.IsOpen()) {
    window.PollEvents();
    window.Clear();
    vertex_array.Bind();
    vertex_array.Draw();
    window.SwapBuffers();
  }
}
