/**
 * Testing entry
 */

#include "src/graphics/window.h"
#include <iostream>
#include <GL/glext.h>

using std::cout;
using std::endl;

using namespace yengine;
using namespace graphics;

int main ()
{

  Window window("yengine!", 800, 600);
  glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

  cout << glGetString(GL_VERSION) << endl;

  // current game loop
  while (!window.closed()) {
    window.clear();

    glBegin(GL_TRIANGLES);
      glVertex2f(-0.5f, -0.5f);
      glVertex2f(0.0f, 0.5f);
      glVertex2f(0.5f, -0.5f);
    glEnd();
    window.update();
  }

  return 0;
}
