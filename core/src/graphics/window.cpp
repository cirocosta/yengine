#include "window.h"

namespace yengine { namespace graphics {

  void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
  void mouse_button_callback(GLFWwindow* window, int button,
                             int action, int mods);
  void key_callback(GLFWwindow* window, int key, int s, int action, int m);
  void windowResize(GLFWwindow *window, int width, int height);

  Window::Window(const char *title, int width, int height)
  {
    m_Title = title;
    m_Width = width;
    m_Height = height;

    if (!init())
      glfwTerminate();

    for (int i = 0; i < MAX_KEYS; i++)
      m_Keys[i] = false;

    for (int i = 0; i < MAX_BUTTONS; i++)
      m_MouseButtons[i] = false;
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
    glfwSetWindowUserPointer(m_Window, this);
    glfwSetWindowSizeCallback(m_Window, &windowResize);
    glfwSetKeyCallback(m_Window, key_callback);
    glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
    glfwSetCursorPosCallback(m_Window, cursor_position_callback);


    if (glewInit() != GLEW_OK) {
      std::cout << "could not initialize glew" << std::endl;
      return false;
    }

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

  bool Window::isMouseButtonPressed(unsigned int button) const
  {
    if (button >= MAX_BUTTONS)
      return false;

    return m_MouseButtons[button];
  }

  void Window::getMousePosition(double &x, double &y) const
  {
    x = mx;
    y = my;
  }

  bool Window::isKeyPressed(unsigned int keyCode) const
  {
    if (keyCode >= MAX_KEYS)
      return false;

    return m_Keys[keyCode];
  }

  void windowResize(GLFWwindow *window, int width, int height)
  {
    glViewport(0, 0, width, height);
  }

  void key_callback(GLFWwindow* window, int key, int s, int action, int m)
  {
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    win->m_Keys[key] = action != GLFW_RELEASE;
  }

  void mouse_button_callback(GLFWwindow* window, int button,
                             int action, int mods)
  {
    Window *win = (Window*)glfwGetWindowUserPointer(window);
    win->m_MouseButtons[button] = action != GLFW_RELEASE;
  }

    void cursor_position_callback(GLFWwindow* window, double xpos,
                                         double ypos)
    {
      Window *win = (Window*)glfwGetWindowUserPointer(window);
      win->mx = xpos;
      win->my = ypos;
    }

}} // graphics  // yengine

