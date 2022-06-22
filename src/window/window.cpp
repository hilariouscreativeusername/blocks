#include "window.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window_utils.h"

Window::Window(unsigned int width, unsigned int height, bool use_vsync) {
  if (!glfwInit()) {
    std::cerr << "Error: glfw failed to initialise\n";
  }

  glfw_window_ = glfwCreateWindow(width, height, "Test Window", nullptr, nullptr);

  glfwMakeContextCurrent(glfw_window_);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Error: glad failed to initialise OpenGL context\n";
  }

  glClearColor(0.1f, 0.4f, 0.5f, 1.0f);

  glfwSwapInterval(use_vsync ? 1 : 0);

  // On window resize, set viewport size to the whole size of the window
  glfwSetWindowUserPointer(glfw_window_, this);
  glfwSetWindowSizeCallback(glfw_window_, [](GLFWwindow* glfw_window, int w, int h) {
    Window* window = (Window*)glfwGetWindowUserPointer(glfw_window);
    window->OnResize(w, h);
  });
  // Avoid repeating code - manually call OnResize to set viewport size
  OnResize(width, height);

  CenterWindow(glfw_window_);
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

void Window::OnResize(unsigned int width, unsigned int height) {
  glViewport(0, 0, width, height);
}
