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

  bool IsKeyDown(int key) const;

public:
  bool IsCursorLocked() const;
  void SetCursorLock(bool lock);
  void ToggleCursorLock();
  
public:
  float CursorX() const;
  float CursorY() const;
  float CursorDeltaX() const;
  float CursorDeltaY() const;

private:
  void OnResize(unsigned int width, unsigned int height);

public:
  void PerformResizeCallbacks();
  typedef std::function<void(float, float)> ResizeFunc;
  void AddResizeCallback(ResizeFunc resize_func);

private:
  double cursor_delta_x_;
  double cursor_delta_y_;
  double cursor_x_;
  double cursor_y_;

  GLFWwindow* glfw_window_;
  std::vector<ResizeFunc> resize_callbacks_;
};
