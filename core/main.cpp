/**
 * Testing entry
 */

#include "src/graphics/window.h"
#include <GL/glext.h>
#include <glm/vec2.hpp>
#include <iostream>


using std::cout;
using std::endl;

using namespace yengine;
using namespace graphics;

int main ()
{

  Window window("yengine!", 800, 600);
  glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
  glm::vec2 vector (1.0f, 2.0f);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  cout << glGetString(GL_VERSION) << endl;
  cout << vector.x << endl;

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

  glDrawArrays(GL_ARRAY_BUFFER, 0, 5);

  return 0;
}
