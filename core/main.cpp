#include "src/gfx/window.h"
#include "src/gfx/shader.h"

#include "src/gfx/layers/tilelayer.h"
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

  Shader shader2("./src/shaders/basic-vert.glsl",
                "./src/shaders/basic-frag.glsl");
  Shader shader("./src/shaders/basic-vert.glsl",
                "./src/shaders/basic-frag.glsl");
  shader.enable();
  shader2.enable();
  shader.setUniform2f("light_pos", glm::vec2(4.0f, 1.5f));
  shader2.setUniform2f("light_pos", glm::vec2(4.0f, 1.5f));

  TileLayer layer(&shader);

  srand(time(NULL));

  for (float y = 0; y < 9.0f; y += 0.5) {
    for (float x = 0; x < 16.0f; x += 0.5) {
      layer.add(new Sprite(x, y, 0.4f, 0.4f,
            glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
    }
  }


  while (!window.closed())
  {
    double x, y;

    window.clear();
    window.getMousePosition(x, y);
    shader.setUniform2f("light_pos", glm::vec2(
        (float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f))
    );

    layer.render();

    window.update();
  }

  return 0;
}
