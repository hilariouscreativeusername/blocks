#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Entity {
public:
  virtual ~Entity() = default;

protected:
  glm::vec3 position_ = glm::vec3(0, 0, 0);
  glm::vec3 rotation_ = glm::vec3(0, 0, 0);
  glm::mat4 transform_ = glm::mat4(1);
};
