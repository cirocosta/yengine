#include "src/graphics/window.h"
#include "src/graphics/shader.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/simple2drenderer.h"
#include "src/graphics/renderable2d.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

int main()
{
  using namespace yengine;
  using namespace graphics;

  Window window("Yengine!", 960, 540);
  glClearColor(0.0f, 0.0f, 0.1f, 1.0f);


  glm::mat4 ortho = glm::ortho<GLfloat>(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
  Shader shader("./src/shaders/basic-vert.glsl",
                "./src/shaders/basic-frag.glsl");
  shader.enable();
  shader.setUniformMat4("pr_matrix", ortho);

  Renderable2D* sprite = new Renderable2D(glm::vec3(4, 4, 0), glm::vec2(4, 4),
                                          glm::vec4(1,0,1,1), shader);
  Renderable2D* sprite2 = new Renderable2D(glm::vec3(7, 1, 0), glm::vec2(2, 3),
                                          glm::vec4(0.2f,0,1,1), shader);
  Simple2DRenderer renderer;

  while (!window.closed())
  {
    window.clear();
    double x, y;
    window.getMousePosition(x, y);
    shader.setUniform2f("light_pos", glm::vec2(
        (float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f))
    );

    renderer.submit(sprite);
    renderer.submit(sprite2);
    renderer.flush();

    window.update();
  }

  return 0;
}
