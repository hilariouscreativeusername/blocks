#include <chrono>
#include <iostream>
#include <thread>

#include "entities/camera.h"
#include "graphics/shader.h"
#include "graphics/texture_array.h"
#include "server/client.h"
#include "server/server.h"
#include "window/window.h"
#include "world/chunk.h"
#include "world/world.h"

int main(int argc, char** argv) {
  const bool kIsHost = argc == 1;
  if (kIsHost) {
    std::cout << "Starting in host mode\n";
  }
  else {
    std::cout << "Starting in join mode\n";
  }

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
  
  std::thread* server_thread;
  if (kIsHost) {
    auto server = std::make_shared<BlocksServer>();
    server->Start();
    server_thread = new std::thread(StartServer, server);
  }

  BlocksClient client(kIsHost ? "127.0.0.1" : argv[1]);
  World world;

  auto last_frame = std::chrono::steady_clock::now();
  while (window.IsOpen()) {
    // Frame timing
    auto now = std::chrono::steady_clock::now();
    float frame_delta = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_frame).count() * 0.000000001f;
    last_frame = now;

    // Game logic
    client.CheckMessages(world);
    window.PollEvents();
    camera.FreeMove(frame_delta);
    client.SendUpdate(camera.Position());

    // Graphics stuff
    window.Clear();
    chunk_shader.Bind();
    world.RenderChunks();
    window.SwapBuffers();
  }
  
  // Shutdown server
  if (kIsHost) {
    client.SendShutdownCommand();
    server_thread->join();
    delete server_thread;
  }
}
