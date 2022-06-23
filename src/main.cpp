#include <chrono>

#include "entities/camera.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "window/window.h"
#include "world/chunk.h"

constexpr float kMaxSecondsPerFrame = 1.0f / 120.0f; // Target fps - default 120
constexpr float kMaxSecondsPerTick = 1.0f / 20.0f;   // Tick rate  - always 20

int main() {
  Window window;

  Shader chunk_shader("src/shaders/chunk_shader.vert.glsl", "src/shaders/chunk_shader.frag.glsl");

  Texture texture("res/textures/test.png");

  Camera camera(&window, &chunk_shader);
  window.PerformResizeCallbacks();
  //window.SetCursorLock(true);

  Chunk chunk(0, 0);

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

      chunk.Draw();

      window.SwapBuffers();
    }
  }
}
