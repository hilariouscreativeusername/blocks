#include "window/window.h"
#include "graphics/vertex_array.h"

int main() {
  Window window;

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };
  VertexArray vertex_array(vertices, sizeof(vertices));

  while (window.IsOpen()) {
    window.PollEvents();
    window.Clear();
    vertex_array.Bind();
    vertex_array.Draw();
    window.SwapBuffers();
  }
}
