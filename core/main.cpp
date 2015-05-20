#include "src/gfx/window.h"
#include "src/gfx/shader.h"

#include "src/gfx/batchrenderer2d.h"
#include "src/gfx/renderable2d.h"
#include "src/gfx/sprite.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <time.h>
#include <vector>

  using namespace yengine;
  using namespace gfx;

int main()
{

  Window window("Yengine!", 960, 540);
  glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
  std::vector<Renderable2D*> sprites;
  glm::mat4 projection = glm::ortho<GLfloat>(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

  Shader shader("./src/shaders/basic-vert.glsl",
                "./src/shaders/basic-frag.glsl");
  shader.enable();
  shader.setUniformMat4("pr_matrix", projection);


  srand(time(NULL));

  for (float y = 0; y < 9.0f; y += 0.5) {
    for (float x = 0; x < 16.0f; x += 0.5) {
      sprites.push_back(new Sprite(x, y, 0.4f, 0.4f,
            glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
    }
  }

  BatchRenderer2D renderer;

  shader.setUniform2f("light_pos", glm::vec2(4.0f, 1.5f));
  shader.setUniform4f("colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));

  while (!window.closed())
  {
    double x, y;

    window.clear();
    window.getMousePosition(x, y);
    shader.setUniform2f("light_pos", glm::vec2(
        (float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f))
    );

    renderer.begin();
    for (int i = 0; i < (int) sprites.size(); i++)
      renderer.submit(sprites[i]);
    renderer.end();
    renderer.flush();

    window.update();
  }

  return 0;
}
