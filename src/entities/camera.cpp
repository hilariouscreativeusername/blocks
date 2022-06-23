#include "camera.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

constexpr glm::vec3 kXAxis = glm::vec3(1, 0, 0);
constexpr glm::vec3 kYAxis = glm::vec3(0, 1, 0);

constexpr float kLookSensitivity = 5.0f;
constexpr float kWalkSpeed = 7.0f;

Camera::Camera(Window* window, Shader* chunk_shader) : window_(window), chunk_shader_(chunk_shader) {
  auto recalc_projection = [&](float width, float height) {
    glm::mat4 perspective_projection = glm::perspectiveFov(45.0f, width, height, 0.1f, 1000.0f);
    
    chunk_shader_->Bind();
    chunk_shader_->UploadUniform(perspective_projection, "u_projection");
  };

  window_->AddResizeCallback(recalc_projection);
}

void Camera::FreeMove(float delta_time) {
  float delta_look = kLookSensitivity * delta_time;
  float delta_mouse_look = delta_look * 0.01f;
  float delta_walk = kWalkSpeed * delta_time;
 
  // Calculate rotation
  // Rotation with mouse
  static bool lock_pressed_last_frame = false;
  if (window_->IsKeyDown(GLFW_KEY_E) && !lock_pressed_last_frame) {
    window_->ToggleCursorLock();
  }
  lock_pressed_last_frame = window_->IsKeyDown(GLFW_KEY_E);

  if (window_->IsCursorLocked()) {
    rotation_.x += window_->CursorDeltaY() * delta_mouse_look;
    rotation_.y += window_->CursorDeltaX() * delta_mouse_look;
  }

  // Rotation with arrow keys
  if (window_->IsKeyDown(GLFW_KEY_UP))         { rotation_.x -= delta_look; }
  if (window_->IsKeyDown(GLFW_KEY_DOWN))       { rotation_.x += delta_look; }
  if (window_->IsKeyDown(GLFW_KEY_LEFT))       { rotation_.y -= delta_look; }
  if (window_->IsKeyDown(GLFW_KEY_RIGHT))      { rotation_.y += delta_look; }

  rotation_.x = std::clamp(rotation_.x, -1.57f, 1.57f);

  glm::mat4 view = glm::rotate(glm::mat4(1), rotation_.x, kXAxis);
  view = glm::rotate(view, rotation_.y, kYAxis);

  // Calculate movement
  glm::vec3 xzmove = glm::vec3(0.0f, 0.0f, 0.0f);

  if (window_->IsKeyDown(GLFW_KEY_W))          { xzmove.z =  1.0f; }
  if (window_->IsKeyDown(GLFW_KEY_S))          { xzmove.z = -1.0f; }
  if (window_->IsKeyDown(GLFW_KEY_A))          { xzmove.x =  1.0f; }
  if (window_->IsKeyDown(GLFW_KEY_D))          { xzmove.x = -1.0f; }
  if (xzmove.x != 0.0f || xzmove.z != 0.0f) {
    xzmove = glm::normalize(glm::rotateY(xzmove, -rotation_.y));
    position_ += xzmove * delta_walk;
  }

  if (window_->IsKeyDown(GLFW_KEY_SPACE))      { position_.y -= delta_walk; }
  if (window_->IsKeyDown(GLFW_KEY_LEFT_SHIFT)) { position_.y += delta_walk; }

  view = glm::translate(view, position_);

  chunk_shader_->Bind();
  chunk_shader_->UploadUniform(view, "u_view");
}
