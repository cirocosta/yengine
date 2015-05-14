/**
 * Testing entry
 */

#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include <GL/glext.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

using std::cout;
using std::endl;

using namespace yengine;
using namespace graphics;

int main ()
{
  Window window("yengine!", 800, 600);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  GLfloat vertices[] = {
    4, 3, 0,
    12, 3, 0,
    4, 6, 0,
    4, 6, 0,
    12, 6, 0,
    12, 3, 0
  };

  glm::mat4 projection = glm::ortho<GLfloat>(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 0.0f);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  Shader shader("./src/shaders/basic-vert.glsl", "./src/shaders/basic-frag.glsl");
  shader.enable();
  shader.setUniformMat4("pr_matrix", projection);
  shader.setUniform4f("colour", glm::vec4(0.2f, 0.4f, 0.1f, 1.0f));
  shader.setUniform2f("light_pos", glm::vec2(0.0, 0.0));

  // current game loop
  while (!window.closed()) {
    window.clear();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    window.update();
  }

  return 0;
}
