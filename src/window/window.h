#pragma once

struct GLFWwindow;

class Window {
public:
  Window();
  ~Window();

  void PollEvents();

  bool IsOpen() const;

private:
  GLFWwindow* glfw_window_;
};
