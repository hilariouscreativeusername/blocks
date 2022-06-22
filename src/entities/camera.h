#pragma once

#include "entity.h"
#include "graphics/shader.h"
#include "window/window.h"

class Camera : public Entity {
public:
  Camera(Window* window, Shader* chunk_shader);

public:
  void FreeMove(float delta_time);

private:
  Window* window_;
  Shader* chunk_shader_;
};
