#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window() {
  glfwInit();

  glfw_window_ = glfwCreateWindow(1280, 720, "Test Window", nullptr, nullptr);

  glfwMakeContextCurrent(glfw_window_);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

  glViewport(0, 0, 1280, 720);
  glClearColor(0.1f, 0.4f, 0.5f, 1.0f);
}

Window::~Window() {
  glfwDestroyWindow(glfw_window_);
  glfwTerminate();
}

void Window::PollEvents() {
  glfwPollEvents();
}

void Window::Clear() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers() {
  glfwSwapBuffers(glfw_window_);
}

bool Window::IsOpen() const {
  return !glfwWindowShouldClose(glfw_window_);
}
