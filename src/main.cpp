#include <chrono>
#include <thread>

#include "entities/camera.h"
#include "graphics/shader.h"
#include "graphics/texture_array.h"
#include "server/client.h"
#include "server/server.h"
#include "window/window.h"
#include "world/chunk.h"

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
  
  BlocksServer server;
  server.Start();
  auto server_loop = [&]() {
    while (!server.FlagShutdown()) {
      server.ProcessMessages();
    }
  };
  std::thread server_thread(server_loop);
  
  BlocksClient client;

  auto last_frame = std::chrono::steady_clock::now();
  while (window.IsOpen()) {
    auto now = std::chrono::steady_clock::now();
    float frame_delta = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_frame).count() * 0.000000001f;
    last_frame = now;

    client.CheckMessages();

    window.PollEvents();
    camera.FreeMove(frame_delta);

    window.Clear();

    chunk_shader.Bind();
    // Render chunks here

    window.SwapBuffers();
  }
  
  client.SendShutdownCommand();
  server_thread.join();
}
