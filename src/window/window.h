#pragma once

struct GLFWwindow;

class Window {
public:
  Window();

private:
  GLFWwindow* glfw_window_;
};
