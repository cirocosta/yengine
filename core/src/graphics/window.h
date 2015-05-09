#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>

namespace yengine {
  namespace graphics {

    class Window
    {
    private:
      const char *m_Title;
      int m_Width, m_Height;
      GLFWwindow *m_Window;
      bool m_Closed;
    public:
      Window(const char *name, int width, int height);
      ~Window();

      bool closed() const;
      void update() const;
    private:
      bool init();
    };
  } // ns graphics
} // ns yengine


#endif // WINDOW_H
