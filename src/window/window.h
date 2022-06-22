#pragma once

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

private:
  GLFWwindow* glfw_window_;
};
