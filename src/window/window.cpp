#include "window.h"

#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window_utils.h"

Window::Window(unsigned int width, unsigned int height, bool use_vsync) {
  if (!glfwInit()) {
    throw std::exception("Error: glfw failed to initialise");
  }

  glfw_window_ = glfwCreateWindow(width, height, "Test Window", nullptr, nullptr);

  glfwMakeContextCurrent(glfw_window_);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::exception("glad failed to initialise OpenGL context");
  }

  glClearColor(0.1f, 0.4f, 0.5f, 1.0f);

  glfwSwapInterval(use_vsync ? 1 : 0);

  // On window resize, set viewport size to the whole size of the window
  glfwSetWindowUserPointer(glfw_window_, this);
  glfwSetWindowSizeCallback(glfw_window_, [](GLFWwindow* glfw_window, int w, int h) {
    Window* window = (Window*)glfwGetWindowUserPointer(glfw_window);
    window->OnResize(w, h);
  });

  CenterWindow(glfw_window_);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

Window::~Window() {
  glfwDestroyWindow(glfw_window_);
  glfwTerminate();
}

void Window::PollEvents() {
  glfwPollEvents();

  // Update cursor position and calculate delta
  double x, y;
  glfwGetCursorPos(glfw_window_, &x, &y);
  cursor_delta_x_ = x - cursor_x_;
  cursor_delta_y_ = y - cursor_y_;
  cursor_x_ = x;
  cursor_y_ = y;
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

bool Window::IsKeyDown(int key) const {
  return glfwGetKey(glfw_window_, key) == GLFW_PRESS;
}

bool Window::IsCursorLocked() const {
  return glfwGetInputMode(glfw_window_, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

void Window::SetCursorLock(bool lock) {
  glfwSetInputMode(glfw_window_, GLFW_CURSOR, lock ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
  glfwSetInputMode(glfw_window_, GLFW_RAW_MOUSE_MOTION, lock ? GLFW_TRUE : GLFW_FALSE);
}

void Window::ToggleCursorLock() {
  SetCursorLock(!IsCursorLocked());
}

float Window::CursorX() const {
  return (float)cursor_x_;
}

float Window::CursorY() const {
  return (float)cursor_y_;
}

float Window::CursorDeltaX() const {
  return (float)cursor_delta_x_;
}

float Window::CursorDeltaY() const {
  return (float)cursor_delta_y_;
}

void Window::OnResize(unsigned int width, unsigned int height) {
  glViewport(0, 0, width, height);
  
  for (auto& func : resize_callbacks_) {
    func(width, height);
  }
}

void Window::PerformResizeCallbacks() {
  int x, y;
  glfwGetWindowSize(glfw_window_, &x, &y);
  OnResize(x, y);
}

void Window::AddResizeCallback(ResizeFunc resize_func) {
  resize_callbacks_.push_back(resize_func);
}
