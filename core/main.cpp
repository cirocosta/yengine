#include "src/graphics/window.h"
#include "src/graphics/shader.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

int main()
{
  using namespace yengine;
  using namespace graphics;

  Window window("Yengine!", 960, 540);
  glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

  GLfloat vertices[] =
  {
    0, 0 ,0,
    0, 3, 0,
    8, 3, 0,
    8, 0, 0
  };

  GLushort indices[] =
  {
    0, 1, 2,
    2, 3, 0
  };

  GLfloat colorsA[] =
  {
    1, 0, 1, 1,
    1, 0, 1, 1,
    1, 0, 1, 1,
    1, 0, 1, 1,
  };

  GLfloat colorsB[] =
  {
    0.2f, 0.3f, 0.8f, 1,
    0.2f, 0.3f, 0.8f, 1,
    0.2f, 0.3f, 0.8f, 1,
    0.2f, 0.3f, 0.8f, 1,
  };

  VertexArray sprite1, sprite2;
  IndexBuffer ibo(indices, 6);

  sprite1.addBuffer(new Buffer(vertices, 4*3, 3), 0);
  sprite1.addBuffer(new Buffer(colorsA, 4*4, 4), 1);

  sprite2.addBuffer(new Buffer(vertices, 4*3, 3), 0);
  sprite2.addBuffer(new Buffer(colorsB, 4*4, 4), 1);

  glm::mat4 ortho = glm::ortho<GLfloat>(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

  Shader shader("./src/shaders/basic-vert.glsl",
                "./src/shaders/basic-frag.glsl");
  shader.enable();
  shader.setUniformMat4("pr_matrix", ortho);
  shader.setUniformMat4("ml_matrix",
    glm::translate<GLfloat>(glm::mat4(1.0f), glm::vec3(4, 3, 0)));

  shader.setUniform2f("light_pos", glm::vec2(4.0f, 1.5f));
  shader.setUniform4f("colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));

  while (!window.closed())
  {
    window.clear();
    double x, y;
    window.getMousePosition(x, y);
    shader.setUniform2f("light_pos", glm::vec2(
        (float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f))
    );

    sprite1.bind();
    ibo.bind();
    shader.setUniformMat4("ml_matrix", glm::translate<GLfloat>(
          glm::mat4(1.0f), glm::vec3(4, 3, 0)));
    glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
    ibo.unbind();
    sprite1.unbind();

    sprite2.bind();
    ibo.bind();
    shader.setUniformMat4("ml_matrix", glm::translate<GLfloat>(
          glm::mat4(1.0f), glm::vec3(0, 0, 0)));
    glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
    ibo.unbind();
    sprite2.unbind();

    window.update();
  }

  return 0;
}
