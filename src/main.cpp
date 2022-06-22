#include <chrono>

#include "entities/camera.h"
#include "graphics/vertex_array.h"
#include "graphics/shader.h"
#include "window/window.h"

int main() {
  Window window(1280, 720, false);

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
  //window.SetCursorLock(true);

  auto last_time = std::chrono::steady_clock::now();
  while (window.IsOpen()) {
    auto now = std::chrono::steady_clock::now();
    float delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_time).count() * 0.00000001f;
    last_time = now;

    window.PollEvents();
    camera.FreeMove(delta_time);

    window.Clear();

    chunk_shader.Bind();

    vertex_array.Bind();
    vertex_array.Draw();

    window.SwapBuffers();
  }
}
