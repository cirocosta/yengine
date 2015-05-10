#include "window.h"

namespace yengine { namespace graphics {

  void windowResize(GLFWwindow *window, int width, int height)
  {
    glViewport(0, 0, width, height);
  }

  Window::Window(const char *title, int width, int height)
  {
    m_Title = title;
    m_Width = width;
    m_Height = height;

    if (!init())
      glfwTerminate();
  }

  Window::~Window()
  {
    // destroys all the remaining windows and
    // cursors, as well as restoring any other
    // things associated with them.
    glfwTerminate();
  }

  bool Window::init()
  {
    if (!glfwInit()) {
      std::cout << "Failed to initialize GLFW" << std::endl;

      return false;
    }

    // GLFWwindow encapsulates both a window and
    // a context, which are inseparably linked.
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

    if (!m_Window) {
      glfwTerminate();
      std::cout << "Failed to create window!" << std::endl;

      return false;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetWindowSizeCallback(m_Window, &windowResize);
    return true;
  }

  bool Window::closed() const
  {
    // closing a window happens by setting a
    // flag. 'windowShouldClose' checks the flag
    return glfwWindowShouldClose(m_Window) == 1;
  }

  void Window::clear() const
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  // updates the screen at a given time.
  void Window::update()
  {
    // processes all pending events that are
    // ready in the queue
    glfwPollEvents();

    /* glfwGetFramebufferSize(m_Window, &m_Width, &m_Height); */

    // we need to swap buffers as glfw windows
    // are by default double buffered, meaning
    // that we have 2 rendering buffers, a front
    // and a back buffer. The front is the one
    // being displayed while that back is the one
    // we render to.
    glfwSwapBuffers(m_Window);
  }


}} // graphics  // yengine
