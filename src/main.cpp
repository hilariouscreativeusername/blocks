#include "window/window.h"

int main() {
  Window window;

  while (window.IsOpen()) {
    window.PollEvents();
    window.Clear();
    window.SwapBuffers();
  }
}
