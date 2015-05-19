#include "window.h"

namespace yengine { namespace graphics {
  void framebuffer_size_callback(GLFWwindow* win, int w, int h);
  void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
  void mouse_button_callback(GLFWwindow* window, int button,
                             int action, int mods);
  void key_callback(GLFWwindow* window, int key, int s, int action, int m);
  void window_resize(GLFWwindow *window, int width, int height);

  Window::Window(const char *title, int width, int height)
    : m_Title(title), m_Width(width), m_Height(height)
  {
    if (!init())
      glfwTerminate();

    for (int i = 0; i < MAX_KEYS; i++)
      m_Keys[i] = false;

    for (int i = 0; i < MAX_BUTTONS; i++)
      m_MouseButtons[i] = false;
  }

  Window::~Window()
  {
    glfwTerminate();
  }

  bool Window::init()
  {
    if (!glfwInit()) {
      std::cerr << "Failed to initialize GLFW" << std::endl;

      return false;
    }

    // GLFWwindow encapsulates both a window and
    // a context, which are inseparably linked.
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

    if (!m_Window) {
      glfwTerminate();
      std::cerr << "Failed to create window!" << std::endl;

      return false;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, this);
    glfwSetWindowSizeCallback(m_Window, window_resize);
    glfwSetKeyCallback(m_Window, key_callback);
    glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
    glfwSetCursorPosCallback(m_Window, cursor_position_callback);

    if (glewInit() != GLEW_OK) {
      std::cerr << "could not initialize glew" << std::endl;
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
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
      std::cout << "Errrrrror:" << err << std::endl;

    glfwPollEvents();
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

  void window_resize(GLFWwindow *window, int width, int height)
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

  void framebuffer_size_callback(GLFWwindow *window, int width, int height)
  {
    Window *win = (Window*)glfwGetWindowUserPointer(window);
    win->m_Width = width;
    win->m_Height = height;
  }

}} // graphics  // yengine

