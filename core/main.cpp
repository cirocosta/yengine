/**
 * Testing entry
 */

#include <GLFW/glfw3.h>
#include <iostream>

#include "src/graphics/window.h"

using namespace yengine;
using namespace graphics;

int main ()
{

  Window window("yengine!", 800, 600);

  // current game loop
  while (!window.closed()) {
    window.update();
  }

  return 0;
}
