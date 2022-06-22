#include "window.h"

#include <GLFW/glfw3.h>

Window::Window() {
  glfwInit();

  glfw_window_ = glfwCreateWindow(1280, 720, "Test Window", nullptr, nullptr);
}
