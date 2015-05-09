/**
 * Testing entry
 */

#include <iostream>
#include <GLFW/glfw3.h>

int main ()
{
  if (!glfwInit())
    std::cout << "Error" << std::endl;
  else
    std::cout << "success!" << std::endl;

  return 0;
}
