#include <chrono>

#include "entities/camera.h"
#include "graphics/vertex_array.h"
#include "graphics/shader.h"
#include "window/window.h"

constexpr float kMaxSecondsPerFrame = 1.0f / 120.0f; // Target fps - default 120
constexpr float kMaxSecondsPerTick = 1.0f / 20.0f;   // Tick rate  - always 20

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
  //window.SetCursorLock(true);

  auto last_tick = std::chrono::steady_clock::now();
  auto last_frame = std::chrono::steady_clock::now();
  while (window.IsOpen()) {
    auto now = std::chrono::steady_clock::now();

    float tick_delta = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_tick).count() * 0.000000001f;
    if (tick_delta > kMaxSecondsPerTick) {
      last_tick = now;

      // Do game logic tick
    }

    float frame_delta = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_frame).count() * 0.000000001f;
    if (frame_delta > kMaxSecondsPerFrame) {
      last_frame = now;

      window.PollEvents();
      camera.FreeMove(frame_delta);

      window.Clear();

      chunk_shader.Bind();

      vertex_array.Bind();
      vertex_array.Draw();

      window.SwapBuffers();
    }
  }
}
