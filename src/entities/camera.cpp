#include "camera.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

constexpr glm::vec3 kXAxis = glm::vec3(1, 0, 0);
constexpr glm::vec3 kYAxis = glm::vec3(0, 1, 0);

Camera::Camera(Window* window, Shader* chunk_shader) : window_(window), chunk_shader_(chunk_shader) {
  auto recalc_projection = [&](float width, float height) {
    glm::mat4 perspective_projection = glm::perspectiveFov(45.0f, width, height, 0.1f, 1000.0f);
    
    chunk_shader_->Bind();
    chunk_shader_->UploadUniform(perspective_projection, "u_projection");
  };

  window_->AddResizeCallback(recalc_projection);
}

void Camera::FreeMove() {
  if (window_->IsKeyDown(GLFW_KEY_LEFT))       { rotation_.x -= 0.05f; }
  if (window_->IsKeyDown(GLFW_KEY_RIGHT))      { rotation_.x += 0.05f; }
  if (window_->IsKeyDown(GLFW_KEY_UP))         { rotation_.y -= 0.05f; }
  if (window_->IsKeyDown(GLFW_KEY_DOWN))       { rotation_.y += 0.05f; }

  glm::mat4 view = glm::rotate(glm::mat4(1), rotation_.x, kYAxis);
  view = glm::rotate(view, rotation_.y, kXAxis);

  if (window_->IsKeyDown(GLFW_KEY_W))          { position_.z += 0.05f; }
  if (window_->IsKeyDown(GLFW_KEY_S))          { position_.z -= 0.05f; }
  if (window_->IsKeyDown(GLFW_KEY_A))          { position_.x += 0.05f; }
  if (window_->IsKeyDown(GLFW_KEY_D))          { position_.x -= 0.05f; }
  if (window_->IsKeyDown(GLFW_KEY_SPACE))      { position_.y -= 0.05f; }
  if (window_->IsKeyDown(GLFW_KEY_LEFT_SHIFT)) { position_.y += 0.05f; }

  view = glm::translate(view, position_);

  chunk_shader_->Bind();
  chunk_shader_->UploadUniform(view, "u_view");
}
