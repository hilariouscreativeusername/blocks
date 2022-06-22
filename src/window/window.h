#pragma once

#include <functional>
#include <vector>

struct GLFWwindow;

class Window {
public:
  Window(unsigned int width = 1280, unsigned int height = 720, bool use_vsync = true);
  ~Window();

public:
  void PollEvents();
  void Clear();
  void SwapBuffers();

public:
  bool IsOpen() const;

private:
  void OnResize(unsigned int width, unsigned int height);

public:
  void PerformResizeCallbacks();
  typedef std::function<void(float, float)> ResizeFunc;
  void AddResizeCallback(ResizeFunc resize_func);

private:
  GLFWwindow* glfw_window_;
  std::vector<ResizeFunc> resize_callbacks_;
};
