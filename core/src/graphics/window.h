#ifndef WINDOW_H
#define WINDOW_H

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

/**
 * WINDOw module encapsulates window creation
 * and maintance.
 */

#include <GL/glew.h>
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

      // although we're not using static methods
      // here anynore we could stick with an
      // INSTANCE static attribute (initialized
      // in the constructor) that holded
      // reference to a Window* instance

      bool m_Keys[MAX_KEYS];
      bool m_MouseButtons[MAX_BUTTONS];
      double mx;
      double my;
    public:
      Window(const char *name, int width, int height);
      ~Window();

      bool closed() const;
      void update();
      void clear() const;

      inline int getWidth() const { return m_Width; }
      inline int getHeight() const { return m_Height; }

      bool isKeyPressed(unsigned int keyCode) const;
      bool isMouseButtonPressed(unsigned int button) const;
      void getMousePosition(double& x, double& y) const;
    private:
      bool init();
      friend void mouse_button_callback(GLFWwindow* , int button,
                             int action, int mods);
      friend void key_callback(GLFWwindow* window, int key, int scancode,
                               int action, int mods);
      friend void cursor_position_callback(GLFWwindow* window, double xpos,
                                           double ypos);
    };
  } // ns graphics
} // ns yengine


#endif // WINDOW_H
