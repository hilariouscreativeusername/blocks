#pragma once

struct GLFWwindow;

class Window {
public:
  Window();
  ~Window();

public:
  void PollEvents();
  void Clear();
  void SwapBuffers();

public:
  bool IsOpen() const;

private:
  GLFWwindow* glfw_window_;
};
