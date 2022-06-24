#include <chrono>

#include "entities/camera.h"
#include "graphics/shader.h"
#include "graphics/texture_array.h"
#include "window/window.h"
#include "world/chunk.h"

constexpr float kMaxSecondsPerFrame = 1.0f / 120.0f; // Target fps - default 120
constexpr float kMaxSecondsPerTick = 1.0f / 20.0f;   // Tick rate  - always 20

int main() {
  Window window;

  Shader chunk_shader("src/shaders/chunk_shader.vert.glsl", "src/shaders/chunk_shader.frag.glsl");

  const char* texture_paths[] = {
    "res/textures/andesite.png",
    "res/textures/basalt.png",
    "res/textures/dirt.png",
    "res/textures/grass_side.png",
    "res/textures/grass.png",
    "res/textures/grass.png",
    "res/textures/leaves_1.png",
    "res/textures/leaves_2.png",
    "res/textures/leaves_3.png",
    "res/textures/leaves_opaque.png",
    "res/textures/limestone.png",
    "res/textures/log_side.png",
    "res/textures/log.png",
    "res/textures/rhyolite.png",
  };
  TextureArray block_textures(texture_paths, 14);

  Camera camera(&window, &chunk_shader);
  window.PerformResizeCallbacks();
  //window.SetCursorLock(true);

  Chunk chunk1(0, 0, 0);
  Chunk chunk2(1, 0, 0);
  Chunk chunk3(1, 1, -1);

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

      chunk1.Draw();
      chunk2.Draw();
      chunk3.Draw();

      window.SwapBuffers();
    }
  }
}
